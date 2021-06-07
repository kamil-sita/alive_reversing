#include "relive_config.h"
#include "logger.hpp"
#include "FunctionFwd.hpp"
#include "SDL_main.h"
#include "Io.hpp"
#include "Sys.hpp"
#include "../AliveLibAE/Sound/PsxSpuApi.hpp"
#include "../AliveLibAE/LvlArchive.hpp"
#include "../AliveLibAE/Abe.hpp"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "GL/glew.h"

#include "../AliveLibAE/MusicController.hpp"
#include "../AliveLibAE/MusicTrigger.hpp"
#include "../AliveLibAE/BackgroundMusic.hpp"
#include "../AliveLibAE/PathData.hpp"
#include "../AliveLibAE/stdlib.hpp"
#include "../AliveLibAE/Sound/Midi.hpp"
#include "../AliveLibAE/AmbientSound.hpp"
#include "../AliveLibAE/BaseGameObject.hpp"
#include "../AliveLibAE/ObjectIds.hpp"


#define FLUIDSYNTH_NOT_A_DLL

#include "fluidsynth.h"
#include <string>

bool CC RunningAsInjectedDll()
{
    return false;
}

static std::vector<u8> ReadLvlFile(LvlArchive& archive, const char_type* fileName)
{
    LvlFileRecord* pFileRec = archive.Find_File_Record_433160(fileName);
    if (!pFileRec)
    {
        ALIVE_FATAL("Failed find file in lvl");
    }
    std::vector<u8> fileContent;
    fileContent.resize(pFileRec->field_10_num_sectors * 2048);
    sLvlArchive_5BC520.Read_File_4330A0(pFileRec, fileContent.data());
    fileContent.resize(pFileRec->field_14_file_size);
    return fileContent;
}

static void WriteVec(const char_type* fileName, const std::vector<u8>& vec)
{
    auto hFile = fopen(fileName, "wb");
    if (hFile)
    {
        fwrite(vec.data(), 1, vec.size(), hFile);
        fclose(hFile);
    }
}

s32 CC SND_SoundsDat_Get_Sample_Len_4FC400(VabHeader* pVabHeader, VabBodyRecord* pVabBody, s32 idx);
BOOL CC sub_4FC470(VabHeader* pVabHeader, VabBodyRecord* pVabBody, s32 idx);
u32* CC SND_SoundsDat_Get_Sample_Offset_4FC3D0(VabHeader* pVabHeader, VabBodyRecord* pBodyRecords, s32 idx);

s32 CC SND_SoundsDat_Read(FILE* file, VabHeader* pVabHeader, VabBodyRecord* pVabBody, s32 idx, void* pBuffer)
{
    const s32 sampleOffset = *SND_SoundsDat_Get_Sample_Offset_4FC3D0(pVabHeader, pVabBody, idx); // = field_8_fileOffset
    const s32 sampleLen = SND_SoundsDat_Get_Sample_Len_4FC400(pVabHeader, pVabBody, idx);
    if (sampleOffset == -1)
    {
        return 0;
    }

    fseek(file, sampleOffset, 0);
    fread(pBuffer, 1, sampleLen * 2, file);

    return sampleLen;
}


void PCToPsxVab(bool isAe, const char_type* lvlName, const char_type* vhName, const char_type* vbName)
{
    ResourceManager::Init_49BCE0();

    LvlArchive archive;

    if (!archive.Open_Archive_432E80(lvlName))
    {
        ALIVE_FATAL("Failed to open lvl");
    }

    auto vhData = ReadLvlFile(archive, vhName);
    auto pHeader = reinterpret_cast<VabHeader*>(vhData.data());
    WriteVec(vhName, vhData);

    auto vbData = ReadLvlFile(archive, vbName);
    auto pBody = reinterpret_cast<VabBodyRecord*>(vbData.data());

    s32 vagCount = pHeader->field_16_num_vags;
    if (vagCount > 255)
    {
        vagCount = 255;
    }

    if (isAe)
    {
        auto hDat = fopen("sounds.dat", "rb");
        if (!hDat)
        {
            ALIVE_FATAL("Failed to open sounds.dat");
        }

        for (s32 i = 0; i < vagCount; i++)
        {
            s32 sampleLen = SND_SoundsDat_Get_Sample_Len_4FC400(pHeader, pBody, i);
            if (sampleLen < 4000 && !sub_4FC470(pHeader, pBody, i))
            {
                sampleLen *= 2;
            }
            sampleLen = pBody->field_0_length_or_duration;

            std::vector<u8> tempBuffer;
            tempBuffer.resize(sampleLen);
            // SND_SoundsDat_Read(hDat, pHeader, pBody, i, tempBuffer.data());

            fseek(hDat, pBody->field_8_fileOffset, SEEK_SET);
            fread(tempBuffer.data(), 1, sampleLen, hDat);

            const std::string name = std::string(vbName) + "_" + std::to_string(i) + ".raw";
            WriteVec(name.c_str(), tempBuffer);
        }
        fclose(hDat);
    }

    archive.Free_433130();
}

class Sequencer final
{
public:
    Sequencer()
    {
        settings = new_fluid_settings();

        synth = new_fluid_synth(settings);

    }

    ~Sequencer()
    {
        for (fluid_player_t* player : mSeqPlayers)
        {
            delete_fluid_player(player);
        }
        delete_fluid_synth(synth);
        delete_fluid_settings(settings);
    }

    bool LoadSoundFont(const char* fileName)
    {
        sfont_id = fluid_synth_sfload(synth, fileName, 1);
        if (sfont_id == FLUID_FAILED)
        {
            LOG_ERROR("Failed to load sound font");
            return false;
        }
        return true;
    }

    void PlaySeq(const char* fileName)
    {
        //fluid_sequencer_t* pSequncer = new_fluid_sequencer2(0);

        fluid_player_t* player = new_fluid_player(synth);
        if (fluid_player_add(player, fileName) != FLUID_OK)
        {
            LOG_ERROR("Failed to open midi");
        }
        fluid_player_play(player);
        mSeqPlayers.push_back(player);
    }

    static void AudioCallBackStatic(void* userdata, Uint8* stream, int len)
    {
        reinterpret_cast<Sequencer*>(userdata)->RenderAudio(stream, len);
    }

    void RenderAudio(Uint8* stream, int lenBytes)
    {
        fluid_synth_write_s16(synth, lenBytes / (2 * sizeof(short)), stream, 0, 2, stream, 1, 2);
        
        //done = fluid_player_get_status(player1) == FLUID_PLAYER_DONE;
        //done |= fluid_player_get_status(player2) == FLUID_PLAYER_DONE;
    }

public:
    fluid_settings_t* settings = nullptr;
    fluid_synth_t* synth = nullptr;
    int sfont_id = FLUID_FAILED;
    std::vector<fluid_player_t*> mSeqPlayers;
};

static void AESoundInit()
{
    gBaseAliveGameObjects_5C1B7C = ae_new<DynamicArrayT<BaseAliveGameObject>>();
    gBaseAliveGameObjects_5C1B7C->ctor_40CA60(20);

    gBaseGameObject_list_BB47C4 = ae_new<DynamicArrayT<BaseGameObject>>();
    gBaseGameObject_list_BB47C4->ctor_40CA60(20);

    sObjectIds_5C1B70.ctor_449AE0(20);

    ResourceManager::Init_49BCE0();

    pResourceManager_5C1BB0 = ae_new<ResourceManager>();
    pResourceManager_5C1BB0->ctor_464910();

    SND_Init_4CA1F0();
    SND_Init_Ambiance_4CB480();
    MusicController::Create_47FC40();
}

void main_loop()
{
    SDL_Window* window = NULL;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow(
        "sound test",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 480,
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
    );

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create context
    SDL_GLContext mContext = SDL_GL_CreateContext(window);
    glewInit();

    if (mContext == NULL)
    {
        LOG_ERROR("OpenGL context could not be created! SDL Error: " << SDL_GetError());
        return;
    }
    else
    {
        // Initialize GLEW
        glewExperimental = GL_TRUE;
        GLenum glewError = glewInit();
        if (glewError != GLEW_OK)
        {
            LOG_ERROR("Error initializing GLEW! " << glewGetErrorString(glewError));
        }

        // Use Vsync
        if (SDL_GL_SetSwapInterval(1) < 0)
        {
            LOG_ERROR("Warning: Unable to set VSync! SDL Error: " << SDL_GetError());
        }
    }

    ImGui::CreateContext();

    // Setup IMGUI for texture debugging
    ImGui_ImplSDL2_InitForOpenGL(window, mContext);
    ImGui_ImplOpenGL3_Init("#version 150");

    Sequencer seq;
    seq.LoadSoundFont("C:\\Users\\paul\\Downloads\\Abe2MidiPlayer\\oddworld.sf2");

    SDL_AudioSpec mAudioDeviceSpec = {};
    mAudioDeviceSpec.callback = Sequencer::AudioCallBackStatic;
    mAudioDeviceSpec.format = AUDIO_S16;
    mAudioDeviceSpec.channels = 2;
    mAudioDeviceSpec.freq = 44100;
    mAudioDeviceSpec.samples = 2048;
    mAudioDeviceSpec.userdata = &seq;
    /*
    if (SDL_OpenAudio(&mAudioDeviceSpec, NULL) < 0)
    {
        LOG_ERROR("Couldn't open SDL audio: " << SDL_GetError());
        return;
    }
    SDL_PauseAudio(0);
    */

    bool quit = false;
    SDL_Event e;

    
    BackgroundMusic* pBgMusic = nullptr;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        ImGui::Begin("AE Sound");

        struct Name2Lvl
        {
            const char* mDisplayName;
            LevelIds mLevelId;
        };
        
        const static Name2Lvl kAELvls[] =
        {
            {"Menu", LevelIds::eMenu_0},
            {"Mines", LevelIds::eMines_1},
            {"Necrum", LevelIds::eNecrum_2},
            {"MudomoVault", LevelIds::eMudomoVault_3},
            {"MudancheeVault", LevelIds::eMudancheeVault_4},
            {"FeeCoDepot", LevelIds::eFeeCoDepot_5},
            {"Barracks", LevelIds::eBarracks_6},
            {"MudancheeVault_Ender", LevelIds::eMudancheeVault_Ender_7},
            {"Bonewerkz", LevelIds::eBonewerkz_8},
            {"Brewery", LevelIds::eBrewery_9},
            {"Brewery_Ender", LevelIds::eBrewery_Ender_10},
            {"MudomoVault_Ender", LevelIds::eMudomoVault_Ender_11},
            {"FeeCoDepot_Ender", LevelIds::eFeeCoDepot_Ender_12},
            {"Barracks_Ender", LevelIds::eBarracks_Ender_13},
            {"Bonewerkz_Ende", LevelIds::eBonewerkz_Ender_14},
            {"NotUsed", LevelIds::eNotUsed_15},
            {"Credits", LevelIds::eCredits_16}
        };

        static MusicController fakeObj = {};
        fakeObj.field_8_object_id = 99;

        struct Name2Music
        {
            const char* mDisplayName;
            MusicController::MusicTypes mType;
        };
        const static Name2Music kMusicTypes[] = 
        {
            { "null", MusicController::MusicTypes::eTypeNull },
            { "none", MusicController::MusicTypes::eNone_0 },
            { "type1", MusicController::MusicTypes::eType1 },
            { "chime", MusicController::MusicTypes::eChime_2 },
            { "type3", MusicController::MusicTypes::eType3 },
            { "tension", MusicController::MusicTypes::eTension_4 },
            { "slog tension", MusicController::MusicTypes::eSlogTension_5 },
            { "slog chase tension", MusicController::MusicTypes::eSlogChaseTension_6 },
            { "slog chase", MusicController::MusicTypes::eSlogChase_7 },
            { "chase", MusicController::MusicTypes::eChase_8 },
            { "possessed", MusicController::MusicTypes::ePossessed_9 },
            { "death short", MusicController::MusicTypes::eDeathShort_10 },
            { "death long", MusicController::MusicTypes::eDeathLong_11 },
            { "secret area short", MusicController::MusicTypes::eSecretAreaShort_12 },
            { "secret area long", MusicController::MusicTypes::eSecretAreaLong_13 },
        };
        
        for (const Name2Music musicPair : kMusicTypes)
        {
            if (ImGui::Button(musicPair.mDisplayName))
            {
                MusicController::PlayMusic_47FD60(musicPair.mType, &fakeObj, TRUE, TRUE);
            }
        }

        for (const Name2Lvl& nameAndLvl : kAELvls)
        {
            if (ImGui::CollapsingHeader(nameAndLvl.mDisplayName))
            {
                const PathRoot& pathData = sPathData_559660.paths[static_cast<s32>(nameAndLvl.mLevelId)];
                if (pathData.field_0_pBlyArrayPtr)
                {
                    if (ImGui::Button("Play"))
                    {
                        AESoundInit();

                        gMap_5C3030.field_0_current_level = nameAndLvl.mLevelId;

                        sLvlArchive_5BC520.Free_433130();
                        sLvlArchive_5BC520.Open_Archive_432E80((std::string(pathData.field_14_lvl_name) + ".LVL").c_str());

                        //SND_Reset_4C9FB0();

                        SND_Load_VABS_4CA350(pathData.field_8_pMusicInfo, pathData.field_10_reverb);
                        SND_Load_Seqs_4CAED0(sSeqData_558D50.mSeqs, pathData.field_C_bsq_file_name);

                        pBgMusic = ae_new<BackgroundMusic>();
                        if (pBgMusic)
                        {
                            pBgMusic->ctor_4CB110(pathData.field_12_bg_music_id);
                        }

                        MusicController::EnableMusic_47FE10(1);
                    }
                }
            }
        }

        ImGui::End();

        if (gBaseGameObject_list_BB47C4)
        {
            for (s32 baseObjIdx = 0; baseObjIdx < gBaseGameObject_list_BB47C4->Size(); baseObjIdx++)
            {
                BaseGameObject* pBaseGameObject = gBaseGameObject_list_BB47C4->ItemAt(baseObjIdx);
                pBaseGameObject->VUpdate();
            }
            SsSeqCalledTbyT_4FDC80();
        }

        if (pMusicController_5C3020)
        {
            ImGui::Begin("Music controller");

            ImGui::Text("field_20_vol = %d", pMusicController_5C3020->field_20_vol);
            ImGui::Text("field_22_vol = %d", pMusicController_5C3020->field_22_vol);
            ImGui::Text("field_24_currentLevelID = %d", static_cast<u32>(pMusicController_5C3020->field_24_currentLevelID));
            ImGui::Text("field_28_object_id = %d", pMusicController_5C3020->field_28_object_id);

            ImGui::Text("field_2C_flags_and_seq_idx = %d", pMusicController_5C3020->field_2C_flags_and_seq_idx);

            ImGui::Text("field_30_music_time = %d", pMusicController_5C3020->field_30_music_time);
            ImGui::Text("field_34_music_start_time = %d", pMusicController_5C3020->field_34_music_start_time);
            ImGui::Text("field_40_flags_and_idx = %d", pMusicController_5C3020->field_40_flags_and_idx);

            ImGui::Text("field_42_type = %d", static_cast<u32>(pMusicController_5C3020->field_42_type));
            ImGui::Text("field_44_timer = %d", pMusicController_5C3020->field_44_timer);
            ImGui::Text("field_48_last_music_frame = %d", pMusicController_5C3020->field_48_last_music_frame);

            ImGui::Text("field_4C_state = %d", pMusicController_5C3020->field_4C_state);
            ImGui::Text("field_4E_starting_volume = %d", pMusicController_5C3020->field_4E_starting_volume);
            ImGui::Text("field_50_current_vol = %d", pMusicController_5C3020->field_50_current_vol);
            ImGui::Text("field_52_target_volume = %d", pMusicController_5C3020->field_52_target_volume);
            ImGui::Text("field_54_music_volume_change_time = %d", pMusicController_5C3020->field_54_music_volume_change_time);
            ImGui::Text("e58_AmbientMusicEnabled_Bit5 = %d", pMusicController_5C3020->field_58_flags.Get(MusicController::e58_AmbientMusicEnabled_Bit5));
            ImGui::Text("e58_MusicEnabled_Bit1 = %d", pMusicController_5C3020->field_58_flags.Get(MusicController::e58_MusicEnabled_Bit1));
            ImGui::Text("e58_ScreenChanged_Bit2 = %d", pMusicController_5C3020->field_58_flags.Get(MusicController::e58_ScreenChanged_Bit2));
            ImGui::Text("e58_ObjectChangingState_Bit3 = %d", pMusicController_5C3020->field_58_flags.Get(MusicController::e58_ObjectChangingState_Bit3));
            ImGui::Text("e58_ForceChange_Bit6 = %d", pMusicController_5C3020->field_58_flags.Get(MusicController::e58_ForceChange_Bit6));

            ImGui::End();
        }

        /*
        ImGui::Begin("Test");

      
        if (ImGui::Button("Sfx test"))
        {
            fluid_synth_program_change(seq.synth, 0, 24);
            fluid_synth_noteon(seq.synth, 0, 65, 127);
           // Mudokon_SFX_457EC0(MudSounds::eDeathDropScream_15, 127, -2000, nullptr);
        }

        for (int i = 0; i < 27; i++)
        {
            std::string name("PS1 SEQ.mid");
            if (i != 0)
            {
                name = std::to_string(i) + name;
            }

            if (ImGui::Button(name.c_str()))
            {
                seq.PlaySeq(("C:\\Users\\paul\\Downloads\\Abe2MidiPlayer\\midi\\" + name).c_str());
            }
        }

        ImGui::End();
        */

        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(window);
        SDL_Delay(10);
    }
    ImGui_ImplSDL2_Shutdown();

    SDL_GL_DeleteContext(mContext);
    SDL_DestroyWindow(window);

    SDL_PauseAudio(1);
    SDL_QuitSubSystem(SDL_INIT_AUDIO);

    SDL_Quit();
    return;
}

s32 main(s32 /*argc*/, char_type** /*argv*/)
{
#if _WIN32
    ::AllocConsole();
    ::freopen("CONOUT$", "w", stdout);
    ::SetConsoleTitleA("Debug Console");
    ::SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
    RedirectIoStream(true);
#endif

    LOG_INFO("fluid synth version: " << fluid_version_str());

    main_loop();

    //PCToPsxVab(true, "ST.LVL", "MONK.VH", "MONK.VB");

    return 0;
}
