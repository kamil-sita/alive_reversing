#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "BaseAliveGameObject.hpp"

namespace relive
{
    struct Path_Paramite;
}

#define PARAMITE_MOTIONS_ENUM(ENTRY)        \
    ENTRY(M_Idle_0_489FB0)                  \
    ENTRY(M_WalkBegin_1_48A7B0)             \
    ENTRY(M_Walking_2_48A2D0)               \
    ENTRY(M_Running_3_48AA00)               \
    ENTRY(M_Turn_4_48B180)                  \
    ENTRY(M_Hop_5_48B5B0)                   \
    ENTRY(M_Unused_6_48A930)                \
    ENTRY(M_WalkRunTransition_7_48B0C0)     \
    ENTRY(M_WalkEnd_8_48A870)               \
    ENTRY(M_RunBegin_9_48AF10)              \
    ENTRY(M_RunEnd_10_48B000)               \
    ENTRY(M_Falling_11_48B200)              \
    ENTRY(M_JumpUpBegin_12_48BE40)          \
    ENTRY(M_JumpUpMidair_13_48BAF0)         \
    ENTRY(M_JumpUpLand_14_48BF00)           \
    ENTRY(M_RopePull_15_48D930)             \
    ENTRY(M_CloseAttack_16_48DDA0)          \
    ENTRY(M_Landing_17_48B590)              \
    ENTRY(M_Unused_18_48DF60)               \
    ENTRY(M_Knockback_19_48BF50)            \
    ENTRY(M_GameSpeakBegin_20_48C010)       \
    ENTRY(M_PreHiss_21_48C180)              \
    ENTRY(M_Hiss1_22_48C3E0)                \
    ENTRY(M_Hiss2_23_48C600)                \
    ENTRY(M_Empty_24_48C680)                \
    ENTRY(M_AllOYaGameSpeakBegin_25_48C6A0) \
    ENTRY(M_Hiss3_26_48C6F0)                \
    ENTRY(M_PostHiss_27_48C780)             \
    ENTRY(M_GameSpeakEnd_28_48C8B0)         \
    ENTRY(M_GetDepossessedBegin_29_48D9D0)  \
    ENTRY(M_GetDepossessedEnd_30_48DB50)    \
    ENTRY(M_RunningAttack_31_48C9E0)        \
    ENTRY(M_Empty_32_48D740)                \
    ENTRY(M_SurpriseWeb_33_48D760)          \
    ENTRY(M_WebLeaveDown_34_48D870)         \
    ENTRY(M_WebIdle_35_48D400)              \
    ENTRY(M_WebGoingUp_36_48D000)           \
    ENTRY(M_WebGoingDown_37_48CC60)         \
    ENTRY(M_WebGrab_38_48D6C0)              \
    ENTRY(M_WebLeaveUp_39_48D8C0)           \
    ENTRY(M_Eating_40_48A0F0)               \
    ENTRY(M_Death_41_48D8E0)                \
    ENTRY(M_Squawk_42_48D900)               \
    ENTRY(M_Attack_43_48DB70)

#define MAKE_ENUM(VAR) VAR,
enum eParamiteMotions : s32
{
    PARAMITE_MOTIONS_ENUM(MAKE_ENUM)
};

class Meat;
class Paramite;
using TParamiteBrainFn = s16 (Paramite::*)();
using TParamiteMotionFn = void (Paramite::*)();

enum class LevelIds : s16;
enum class GameSpeakEvents : s16;

class PullRingRope;


enum class ParamiteSpeak : s8
{
    CMon_or_Attack_0 = 0,
    Stay_1 = 1,
    DoIt_2 = 2,
    LoudStep_3 = 3,
    SlightStep_4 = 4,
    Howdy_5 = 5,
    ClimbingWeb_6 = 6,
    DetectedMeat_7 = 7,
    None_8 = 8,
    AllYa_9 = 9,
    None_10 = 10,
    None_11 = 11,
};

struct Paramite_State final
{
    AETypes field_0_type;
    s16 field_2_pad;
    FP field_4_xpos;
    FP field_8_ypos;
    FP field_C_velx;
    FP field_10_vely;
    s16 field_14_path_number;
    LevelIds field_16_lvl_number;
    FP field_18_sprite_scale;
    s16 field_1C_r;
    s16 field_1E_g;
    s16 field_20_b;
    s16 field_22_flip_x;
    s16 field_24_current_motion;
    s16 field_26_anim_current_frame;
    s16 field_28_frame_change_counter;
    s8 field_2A_render;
    s8 field_2B_drawable;
    FP field_2C_health;
    s16 field_30_current_motion;
    s16 field_32_next_motion;
    s16 field_34_last_line_ypos;
    s16 field_36_line_type;
    s16 field_38_padding;
    s16 field_3A_padding;
    Guid field_3C_tlvInfo;
    Guid field_40_meat_id;
    Guid field_44_web_id;
    Guid field_48_obj_id;
    Guid field_4C_pull_ring_rope_id;
    s32 field_50_brain_idx;
    s16 field_54_padding;
    s16 field_56_padding;
    s16 field_58_brain_ret;
    s16 field_5A_padding;
    s32 field_5C_timer;
    s32 field_60_depossession_timer;
    FP field_64_velx_offset;
    s32 field_68_timer;
    LevelIds field_6C_return_level;
    s16 field_6E_return_path;
    s16 field_70_return_camera;
    s16 field_72_input;
    s16 field_74_next_brain_ret;

    enum Flags_76 : s16
    {
        eBit1_unused = 0x1,
        eBit2_running = 0x2,
        eBit3_hissed_or_left_screen = 0x4,
        eBit4_prevent_depossession = 0x8,
        eBit5_spawned = 0x10,
        eBit6_alerted = 0x20,
        eBit7_can_be_possessed = 0x40,
    };

    BitField16<Flags_76> field_76_flags;
};
//ALIVE_ASSERT_SIZEOF_ALWAYS(Paramite_State, 0x78);

class Paramite final : public BaseAliveGameObject
{
public:
    Paramite(relive::Path_Paramite* pTlv, const Guid& tlvId);
    ~Paramite();

    void LoadAnimations();
    virtual void VUpdate() override;
    virtual void VRender(PrimHeader** ppOt) override;
    virtual s16 VOnSameYLevel(BaseAnimatedWithPhysicsGameObject* pOther) override;

    virtual void VUnPosses() override;
    virtual void VPossessed() override;
    virtual s16 VTakeDamage(BaseGameObject* pFrom) override;
    virtual void VOnTlvCollision(relive::Path_TLV* pTlv) override;
    virtual void VOnTrapDoorOpen() override;
    virtual s32 VGetSaveState(u8* pSaveBuffer) override;

    static s32 CreateFromSaveState(const u8* pBuffer);

    void HandleDDCheat();
    void HandleBrainsAndMotions();

    s16 Brain_0_Patrol_4835B0();
	s16 Brain_Patrol_State_1_IdleForAbe(BaseAliveGameObject* pObj);
	s16 Brain_Patrol_State_2_FearingAbe(BaseAliveGameObject* pObj);
	s16 Brain_Patrol_State_3_RunningFromAbe(BaseAliveGameObject* pObj);
	s16 Brain_Patrol_State_4_ApproachingAbe(BaseAliveGameObject* pObj);
	s16 Brain_Patrol_State_5_StopApproachingAbe(BaseAliveGameObject* pObj);
	s16 Brain_Patrol_State_8_StuckToWall(BaseAliveGameObject* pObj);
    s16 Brain_Patrol_State_12_Idle(BaseAliveGameObject* pObj);

    s16 Brain_1_Death_484CD0();

    s16 Brain_2_ChasingAbe_4859D0();
	s16 Brain_ChasingAbe_State_0_Inactive(BaseAliveGameObject* pObj);
	s16 Brain_ChasingAbe_State_1_Attacking(BaseAliveGameObject* pObj);
	s16 Brain_ChasingAbe_State_2_ToWarning();
	s16 Brain_ChasingAbe_State_3_Warning();
	s16 Brain_ChasingAbe_State_4_CloseAttack();
	s16 Brain_ChasingAbe_State_5_ToChasing(BaseAliveGameObject* pObj);
	s16 Brain_ChasingAbe_State_6_QuickAttack();
	s16 Brain_ChasingAbe_State_7_Chasing(BaseAliveGameObject* pObj);
	s16 Brain_ChasingAbe_State_8_Jumping();
	s16 Brain_ChasingAbe_State_9_TurningWhileChasing();
	s16 Brain_ChasingAbe_State_10_Turning(BaseAliveGameObject* pObj);
	s16 Brain_ChasingAbe_State_11_Walking(BaseAliveGameObject* pObj);
	s16 Brain_ChasingAbe_State_12_WalkingToHop(BaseAliveGameObject* pObj);
	s16 Brain_ChasingAbe_State_13_Eating();
	s16 Brain_ChasingAbe_State_14_Idle();
    s16 Brain_ChasingAbe_State_15_Panic();

    s16 Brain_3_SurpriseWeb_4851B0();
    s16 Brain_4_Unused_48F8F0();

    s16 Brain_5_SpottedMeat_486880();
	s16 Brain_SpottedMeat_State_0_Idle(Meat* pMeat);
	s16 Brain_SpottedMeat_State_1_Running(Meat* pMeat);
	s16 Brain_SpottedMeat_State_2_Walking(Meat* pMeat);
	s16 Brain_SpottedMeat_State_3_Jumping();
	s16 Brain_SpottedMeat_State_4_Turning(Meat* pMeat);
	s16 Brain_SpottedMeat_State_5_AttentiveToMeat(Meat* pMeat);
    s16 Brain_SpottedMeat_State_6_Eating(Meat* pMeat);

    s16 Brain_6_Possessed_484BC0();
    s16 Brain_7_DeathDrop_484FF0();
    s16 Brain_8_ControlledByGameSpeak_48DFC0();
    s16 Brain_9_ParamiteSpawn_48ED80();

public:
    void M_Idle_0_489FB0();
    void M_WalkBegin_1_48A7B0();
    void M_Walking_2_48A2D0();
    void M_Running_3_48AA00();
    void M_Turn_4_48B180();
    void M_Hop_5_48B5B0();
    void M_Unused_6_48A930();
    void M_WalkRunTransition_7_48B0C0();
    void M_WalkEnd_8_48A870();
    void M_RunBegin_9_48AF10();
    void M_RunEnd_10_48B000();
    void M_Falling_11_48B200();
    void M_JumpUpBegin_12_48BE40();
    void M_JumpUpMidair_13_48BAF0();
    void M_JumpUpLand_14_48BF00();
    void M_RopePull_15_48D930();
    void M_CloseAttack_16_48DDA0();
    void M_Landing_17_48B590();
    void M_Unused_18_48DF60();
    void M_Knockback_19_48BF50();
    void M_GameSpeakBegin_20_48C010();
    void M_PreHiss_21_48C180();
    void M_Hiss1_22_48C3E0();
    void M_Hiss2_23_48C600();
    void M_Empty_24_48C680();
    void M_AllOYaGameSpeakBegin_25_48C6A0();
    void M_Hiss3_26_48C6F0();
    void M_PostHiss_27_48C780();
    void M_GameSpeakEnd_28_48C8B0();
    void M_GetDepossessedBegin_29_48D9D0();
    void M_GetDepossessedEnd_30_48DB50();
    void M_RunningAttack_31_48C9E0();
    void M_Empty_32_48D740();
    void M_SurpriseWeb_33_48D760();
    void M_WebLeaveDown_34_48D870();
    void M_WebIdle_35_48D400();
    void M_WebGoingUp_36_48D000();
    void M_WebGoingDown_37_48CC60();
    void M_WebGrab_38_48D6C0();
    void M_WebLeaveUp_39_48D8C0();
    void M_Eating_40_48A0F0();
    void M_Death_41_48D8E0();
    void M_Squawk_42_48D900();
    void M_Attack_43_48DB70();

private:
    void SetBrain(TParamiteBrainFn fn);
    bool BrainIs(TParamiteBrainFn fn);

private:

    s16 Find_Paramite();
    void vUpdateAnim();
    Meat* FindMeat();
    s16 IsNear(Paramite* pOther);
    u8** ResBlockForMotion(s16 motion);
    s16 AnotherParamiteNear();
    PathLine* WebCollision(FP yOff, FP xOff);
    void ToHop();
    s16 CanIAcceptAGameSpeakCommand();
    s16 HandleEnemyStopper(s16 numGridBlocks);
    PullRingRope* FindPullRope();
    s16 NextPlayerInputMotion();
    s16 FindTarget();
    s16 ToNextMotion();
    void ToIdle();
    void ToKnockBack();
    void MoveOnLine();
    void CheckForPlatform();
    void HandleStopWalking();
    void HandleInputRunning();
    static s16 StableDelay();
    void Sound(ParamiteSpeak soundId, s16 pitch_min);
    void UpdateSlurgWatchPoints();
    GameSpeakEvents LastSpeak();


private:
    Guid field_118_meat_id;
    Guid field_11C_web_id;
    Guid field_120_obj_id;
    Guid field_124_pull_ring_rope_id;
    TParamiteBrainFn mBrainState = nullptr;
    s16 mBrainSubState = 0;
    s16 field_12E_surprise_web_delay_timer = 0;
    s32 field_130_timer = 0;
    s16 field_134_meat_eating_time = 0;
    s16 field_136_alone_chase_delay = 0;
    s32 field_138_depossession_timer = 0;
    FP field_13C_velx_offset = {};
    Guid field_140_tlvInfo;
    s32 field_144_group_chase_delay = 0;
    s32 field_148_timer = 0;
    s16 field_14C_surprise_web_switch_id = 0;
    EReliveLevelIds mAbeLevel = EReliveLevelIds::eNone;
    s16 mAbePath = 0;
    s16 mAbeCamera = 0;
    s32 field_154_input = 0;
    s16 field_158_next_brain_ret = 0;
    s16 field_15A_paramite_next_motion = 0;
    s16 field_15C_paramite_xOffset = 0;
    s32 field_160_last_event_index = 0;
    s16 field_174_unused = 0;
    s16 field_176_unused = 0;
    enum Flags_178 : s16
    {
        eBit1_hiss_before_attack = 0x1,
        eBit2_running = 0x2,
        eBit3_hissed_or_left_screen = 0x4,
        eBit4_out_of_sight = 0x8,
        eBit5_prevent_depossession = 0x10,
        eBit6_spawned = 0x20,
        eBit7_alerted = 0x40,
        eBit8_bAttack_fleeches = 0x80,
        eBit9_padding = 0x100,
        eBit10_padding = 0x200,
        eBit11_padding = 0x400,
        eBit12_padding = 0x800,
        eBit13_padding = 0x1000,
        eBit14_padding = 0x2000,
        eBit15_padding = 0x4000,
    };
    BitField16<Flags_178> field_178_flags = {};
};
ALIVE_ASSERT_SIZEOF(Paramite, 0x17C);
