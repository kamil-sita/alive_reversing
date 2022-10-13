#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "../relive_lib/BaseAnimatedWithPhysicsGameObject.hpp"
#include "../relive_lib/Primitives.hpp"
#include "Font.hpp"
#include "Path.hpp"

enum class EReliveLevelIds : s16;

namespace AO {

enum buttonType : u16
{
    eCircle_0 = 0,
    eSquare_1 = 1,
    eTriangle_2 = 2,
    eNone_3 = 3
};

class MainMenuFade final : public BaseAnimatedWithPhysicsGameObject
{
public:
    MainMenuFade(s32 xpos, s32 ypos, buttonType buttonType, s32 bDestroyOnDone);

    void LoadAnimations();

    virtual void VUpdate() override;
    virtual void VRender(PrimHeader** ppOt) override;

    s16 mRgbValue;
    s16 mRgbModifier;
    s16 field_E8_bDestroyOnDone;
};

struct MainMenuTransition_Polys final
{
    Poly_G3 field_0_polys[8];
};
ALIVE_ASSERT_SIZEOF(MainMenuTransition_Polys, 0x100);

// TODO: Move to own file
class MainMenuTransition final : public ::BaseGameObject
{
public:
    MainMenuTransition(Layer layer, s32 fadeDirection, s32 bKillWhenDone, s32 speed, TPageAbr abr);
    ~MainMenuTransition();

    virtual void VUpdate() override;
    virtual void VScreenChanged() override;
    virtual void VRender(PrimHeader** ppOt) override;

    void StartTrans_436560(Layer layer, s16 fadeDirection, s16 bKillWhenDone, s16 speed);

    s16 field_10_current_Value = 0;
    s16 field_12_change_by_speed = 0;
    s16 field_14_fade_direction = 0;
    s16 field_16_bDone = 0;
    s16 field_18_bKillOnDone = 0;
    MainMenuTransition_Polys field_1C_polys[2] = {};
    Prim_SetTPage field_21C_tPage[2] = {};
    Layer field_23C_layer = Layer::eLayer_0;
    s16 field_23E_width = 0;
    s16 field_240_k120 = 0;
    s16 field_242_idx = 0;
    s8 field_246_colour_fade_value = 0;
};

struct Path_TLV;

enum class MainMenuOptions : s16
{
    eGameSpeak_0 = 0,
    eBegin_1 = 1,
    eQuit_2 = 2,
    eLoad_3 = 3,
    eOptions_4 = 4
};

enum class GameSpeakOptions : s16
{
    eWait_0 = 0,
    eHello_1 = 1,
    eFollowMe_2 = 2,
    eAngry_3 = 3,
    eWhistleHigh_4 = 4,
    eWhistleLow_5 = 5,
    eLaugh_6 = 6,
    eFart_7 = 7,
    eChant_8 = 8,
    eMainMenu_9 = 9
};

enum class OptionsMenuOptions : s16
{
    eController_0 = 0,
    eSound_1 = 1,
    eMainMenu_2 = 2
};

enum class RemapOptions : s16
{
    eRun_0 = 0,
    eSneak_1 = 1,
    eJump_2 = 2,
    eSpeakLeft_3 = 3,
    eAction_4 = 4,
    eThrow_5 = 5,
    eCrouch_6 = 6,
    eSpeakRight_7 = 7
};

enum class MotionsOptions : s16
{
    eMotions_0 = 0,
    eGameSpeak_1 = 1,
    eExit_2 = 2
};

enum class SoundOptions : s16
{
    eStereo_0 = 0,
    eMono_1 = 1,
    eExit_2 = 2
};

union MenuOption
{
    MainMenuOptions mainmenu;
    GameSpeakOptions gamespeak_menu;
    OptionsMenuOptions options_menu;
    RemapOptions remap_menu;
    MotionsOptions motions_menu;
    SoundOptions sound_menu;
    s16 raw;
};

class Menu final : public BaseAnimatedWithPhysicsGameObject
{
public:
    Menu(relive::Path_TLV* pTlv, const Guid& tlvId);
    ~Menu();

    void LoadAnimations();

    virtual void VUpdate() override;
    virtual void VRender(PrimHeader** ppOt) override;
    virtual void VScreenChanged() override;

    void ProgressInProgressFilesLoading();


    void WaitForDoorToOpen();
    void WaitForAbesHeadPoppingThroughDoor();
    void AbePopThroughDoor();
    void CopyRight_Update();
    void FMV_Select_Update();
    void SayHelloWaitForLoading();
    void WaitForAbeSayHello();
    void MainScreen_Update();
    void GoToSelectedMenuPage();
    void WaitForSpeakFinishAndStartChangeEffect();
    void ToNextMenuPage();
    void ToLoading();
    void ToGameSpeak_Update();
    void To_FMV_Or_Level_Select_Update();
    void Update_NoRefs();
    void To_Load_Update();
    void To_Options_Update();
    void Loading_Update();
    void NewGameStart();
    void Options_Update();
    void Options_WaitForAbeSpeak_Update();
    void Option_GoTo_Selected_Update();
    void Options_To_Selected_After_Cam_Change_Update();
    void To_Options_Controller_Update();
    void To_Options_Sound_Update();
    void To_MainScreen_Update();
    void Options_Sound_Update();
    void Options_WaitForAbeSayOK_Update();
    void Options_WaitForScreenTrans_Update();
    void To_MainOptions_Screen_After_Camera_Change_Update();
    void GameSpeak_Update();
    void FMV_Or_Level_Select_To_Back_Update();
    void To_Credits_Update();
    void Level_Cheat_To_Loading_Update();
    void Options_Controller_Update();
    void GoTo_ControllerConfigure_Or_Back_AfterScreenTrans_Update();
    void Goto_ConfigureController_OrSave_SettingIni_Update();
    void To_ButtonRemap_Update();
    void ButtonRemap_Update();
    void To_LoadSave_Update();
    void LoadSave_Update();
    void SaveLoadFailed_Update();
    void To_ShowAbeMotions_ChangeCamera_Update();
    void To_ShowAbeMotions_SaveSettings_Update();
    void To_ToggleMotions_Update();
    void Credits_Update();
    void CreditsEnd_BackTo_FMV_Or_Level_List_Update();

    void Load_Update();
    void CycleGameSpeakIdleAnims();

    static s32 StringsEqual(const void* pStr1, const void* pStr2);

    // Compared via address
    void ToggleMotions_Update();
    void Toggle_Motions_Screens_Update();

    void MotionsScreen_Back_Update();

    void Motions_ToOptions_Update();

    void To_MainScreenOrLoad_Update();

    void Load_BackToMainScreen_Update();

    void GameSpeakBack_WaitForAbeGoodbye_Update();

    void GamespeakBack_WaitForScreenTrans_Update();

    void GameSpeak_To_MainScreen_Update();

    void ToggleMotions_Render(PrimHeader** ppOt);
    void SaveLoadFailed_Render(PrimHeader** ppOt);
    void ButtonRemap_Render(PrimHeader** ppOt);
    void Options_Sound_Render(PrimHeader** ppOt);
    void Options_Controller_Render(PrimHeader** ppOt);
    void Empty_Render(PrimHeader** ppOt);
    void FMV_Or_Level_Select_Render(PrimHeader** ppOt);
    void MainScreen_Render(PrimHeader** ppOt);
    void GameSpeak_Render(PrimHeader** ppOt);
    void Render_NoRefs(PrimHeader** ppOt);
    void Load_Render(PrimHeader** ppOt);
    void Options_Render(PrimHeader** ppOt);

    void FMV_Or_Level_Select_Back_Update();

    static void OnResourceLoaded(Menu* pMenu);

    static void RenderElement(s32 xpos, s32 ypos, s32 input_command, PrimHeader** ot, AliveFont* pFont, s32* pPolyOffset);

   // u8** field_E4_res_array[6] = {};
    FontContext mFontContext;
    PalResource mPal;
    AliveFont mFont;
    Animation mButtonAnim;

    using TUpdateFn = decltype(&Menu::WaitForDoorToOpen);

    TUpdateFn mFnUpdate = nullptr;

    using TRenderFn = decltype(&Menu::Empty_Render);

    TRenderFn mFnRender = nullptr;

    Guid field_1D4_tlvInfo;
    s32 field_1D8_timer = 0;
    s32 mIdleInputCounter = 0;
    MenuOption mSelectedButtonIndex;
    s16 mButtonRgb = 0;
    s16 mButtonRgbModifier = 0;
    MainMenuTransition* mMenuTrans = nullptr;
    MainMenuFade* mMenuFade1 = nullptr;
    MainMenuFade* mMenuFade2 = nullptr;
    const char_type* field_1F4_text = nullptr;
    bool mLoadSave = false;
    s16 field_204_flags = 0;
    s32 mCurrentCreditsCamera = 0;
    bool mUsingLvlSelectCheat = false;
    EReliveLevelIds mLvlSelectCheatLevel = EReliveLevelIds::eNone;
    s16 mLvlSelectCheatPath = 0;
    s16 mLvlSelectCheatCamera = 0;
    s16 mLvlSelectCheatAbeSpawnX = 0;
    s16 mLvlSelectCheatAbeSpawnY = 0;
    s16 field_218_previous_fmv_or_level_selection = 0;
    FP field_21C = {};
    FP field_220 = {};
    bool mToFmvSelect = false;
    bool mToLevelSelect = false;
    FP field_228 = {};
    FP field_22C = {};
    s32 field_230_bGoBack = 0;
};

extern s32 gMainMenuInstanceCount;
extern u8 gJoyResId;

} // namespace AO
