#pragma once

#include "../relive_lib/BaseGameObject.hpp"
#include "../relive_lib/MapWrapper.hpp"

class BaseAliveGameObject;

enum class LevelIds : s16;

// NOTE: Called MusicEnv in real game (derived from AE PC demo)
class MusicController final : public BaseGameObject
{
public:
    enum class MusicTypes : s16
    {
        eTypeNull = -1,
        eNone_0 = 0,
        eType1 = 1,
        eChime_2 = 2,
        eDrumAmbience_3 = 3,
        eTension_4 = 4,
        eSlogTension_5 = 5,
        eSlogChaseTension_6 = 6,
        eIntenseChase_7 = 7,
        eSoftChase_8 = 8,
        ePossessed_9 = 9,
        eDeathDrumShort_10 = 10,
        eDeathLong_11 = 11, //death jingle?
        eSecretAreaShort_12 = 12,
        eSecretAreaLong_13 = 13,
    };

    MusicController();
    ~MusicController();

    static s32 Create();
    static void SetBaseTimeStamp();
    static void Shutdown();
    static void UpdateMusicTime();
    static MusicTypes static_GetMusicType(u16* seq1, u16* seq2, u32* seqTime);

    MusicTypes GetMusicType(u16* seq, u16* seq2, u32* seqTime);

    virtual void VScreenChanged() override;
    virtual void VUpdate() override;

    void EnableMusic(s16 enable);
    void SetMusicVolumeDelayed(s16 vol, s16 delay);
    void UpdateVolumeState();
    void PlayMusic(MusicTypes typeToSet, const BaseGameObject* pObj, s16 bFlag4, s8 bFlag0x20);

    void UpdateMusic();
    void UpdateAmbiance();

    static void static_PlayMusic(MusicTypes typeToSet, const BaseGameObject* pObj, s16 bFlag4, s8 bFlag0x20);
    static void static_EnableMusic(s16 bOn);

private:
    u16 field_20_vol = 0;
    u16 field_22_vol = 0;
    EReliveLevelIds field_24_currentLevelID = EReliveLevelIds::eNone;
    Guid field_28_object_id;
    s16 field_2C_flags_and_seq_idx = 0;
    u32 field_30_music_time = 0;
    u32 field_34_music_start_time = 0;
    u32 field_38_unused = 0;
    u32 field_3C_unused = 0;
    s16 field_40_flags_and_idx = 0;
    MusicTypes field_42_type = MusicTypes::eNone_0;
    s32 field_44 = 0;
    u32 field_48_last_music_frame = 0;
    u16 field_4C_state = 0;
    u16 field_4E_starting_volume = 0;
    u16 field_50_current_vol = 0;
    u16 field_52_target_volume = 0;
    u32 field_54_music_volume_change_time = 0;
    bool mMusicEnabled = false;
    bool mScreenChanged = false;
    bool mMusicDead = false;
    bool mUnknown4 = false;
    bool mAmbientMusicEnabled = false;
    bool mUnPause = false;
    bool mUnknown7 = false;
};


extern MusicController* gMusicController;
