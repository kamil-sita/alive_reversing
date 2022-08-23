#include "stdafx.h"
#include "Fleech.hpp"
#include "Function.hpp"
#include "SwitchStates.hpp"
#include "Game.hpp"
#include "Abe.hpp"
#include "MusicController.hpp"
#include "stdlib.hpp"
#include "../relive_lib/Events.hpp"
#include "SnoozeParticle.hpp"
#include "Dove.hpp"
#include "Blood.hpp"
#include "../relive_lib/Shadow.hpp"
#include "Particle.hpp"
#include "../relive_lib/ScreenManager.hpp"
#include "ShadowZone.hpp"
#include "Gibs.hpp"
#include "../relive_lib/ObjectIds.hpp"
#include "PlatformBase.hpp"
#include "../relive_lib/PsxDisplay.hpp"
#include "Sfx.hpp"
#include "SlamDoor.hpp"
#include "Sound/Midi.hpp"
#include "Sys_common.hpp"
#include "Grid.hpp"
#include "../relive_lib/Math.hpp"
#include "AnimationCallBacks.hpp"

ALIVE_VAR(1, 0x5BC20C, u8, sFleechRandomIdx_5BC20C, 0);
ALIVE_VAR(1, 0x5BC20E, s16, sFleechCount_5BC20E, 0);

const TFleechMotionFn sFleech_motion_table_551798[19] = {
    &Fleech::Motion_0_Sleeping,
    &Fleech::Motion_1_WakingUp,
    &Fleech::Motion_2_Unknown,
    &Fleech::Motion_3_Idle,
    &Fleech::Motion_4_Crawl,
    &Fleech::Motion_5_PatrolCry,
    &Fleech::Motion_6_Knockback,
    &Fleech::Motion_7_StopCrawling,      //Stop due to being aligned vertically with target
    &Fleech::Motion_8_StopMidCrawlCycle,
    &Fleech::Motion_9_Fall,
    &Fleech::Motion_10_Land,
    &Fleech::Motion_11_RaiseHead,
    &Fleech::Motion_12_Climb,
    &Fleech::Motion_13_SettleOnGround,
    &Fleech::Motion_14_ExtendTongueFromEnemy,
    &Fleech::Motion_15_RetractTongueFromEnemey,
    &Fleech::Motion_16_DeathByFalling,
    &Fleech::Motion_17_SleepingWithTongue,
    &Fleech::Motion_18_Consume};

enum eFleechMotions
{
    Motion_0_Sleeping,
    Motion_1_WakingUp,
    Motion_2_Unknown,
    Motion_3_Idle,
    Motion_4_Crawl,
    Motion_5_PatrolCry,
    Motion_6_Knockback,
    Motion_7_StopCrawling,
    Motion_8_StopMidCrawlCycle,
    Motion_9_Fall,
    Motion_10_Land,
    Motion_11_RaiseHead,
    Motion_12_Climb,
    Motion_13_SettleOnGround,
    Motion_14_ExtendTongueFromEnemy,
    Motion_15_RetractTongueFromEnemey,
    Motion_16_DeathByFalling,
    Motion_17_SleepingWithTongue,
    Motion_18_Consume
};

const SfxDefinition stru_5518E0[20] = {
    {0u, 6u, 50u, 30u, -127, 127},
    {0u, 6u, 49u, 127u, 0, 0},
    {0u, 6u, 54u, 127u, 0, 0},
    {0u, 1u, 36u, 35u, 0, 0},
    {0u, 1u, 37u, 35u, 0, 0},
    {0u, 6u, 52u, 100u, 0, 0},
    {0u, 6u, 50u, 30u, -127, 0},
    {0u, 6u, 50u, 40u, 500, 600},
    {0u, 6u, 50u, 30u, 300, 400},
    {0u, 3u, 59u, 100u, 256, 384},
    {0u, 4u, 65u, 80u, 0, 0},
    {0u, 4u, 65u, 55u, 0, 0},
    {0u, 4u, 65u, 85u, 0, 0},
    {0u, 4u, 65u, 100u, 127, 127},
    {0u, 6u, 61u, 70u, -127, 127},
    {0u, 6u, 62u, 70u, -127, 127},
    {0u, 6u, 63u, 70u, -127, 127},
    {0u, 0u, 0u, 0u, 0, 0},
    {0u, 0u, 0u, 0u, 0, 0},
    {0u, 0u, 0u, 0u, 0, 0}};


const TFleechBrainFn sFleechAiTable[4] = {
    &Fleech::Brain_0_Patrol,
    &Fleech::Brain_1_ChasingAbe,
    &Fleech::Brain_2_Scared,
    &Fleech::Brain_3_Death};

enum eFleechBrains
{
    eBrain_0_Patrol = 0,
    eBrain_1_ChasingAbe = 1,
    eBrain_2_Scared = 2,
    eBrain_3_Death = 3
};

static u8 Fleech_NextRandom()
{
    return sRandomBytes_546744[sFleechRandomIdx_5BC20C++];
}

Fleech::Fleech(Path_Fleech* pTlv, s32 tlvInfo)
    : BaseAliveGameObject(2)
{
    mXPos = FP_FromInteger(pTlv->mTopLeft.x);
    mYPos = FP_FromInteger(pTlv->mTopLeft.y);
    mBaseGameObjectTlvInfo = tlvInfo;

    if (pTlv->mScale == Scale_short::eHalf_1)
    {
        mSpriteScale = FP_FromDouble(0.5);
    }
    else
    {
        mSpriteScale = FP_FromInteger(1);
    }

    Init();

    mTlvInfo = tlvInfo;
    field_124_brain_state = eFleechBrains::eBrain_0_Patrol;
    field_11C_obj_id = -1;
    field_170_danger_obj = -1;

    mAnim.mFlags.Set(AnimFlags::eBit5_FlipX, pTlv->mFacing == XDirection_short::eLeft_0);

    mFleechFlags.Set(FleechFlags::eAsleep, pTlv->mAsleep == Choice_short::eYes_1);
    mFleechFlags.Set(FleechFlags::eGoesToSleep, pTlv->mGoesToSleep == Choice_short::eYes_1);
    mFleechFlags.Set(FleechFlags::ePersistant, pTlv->mPersistant == Choice_short::eYes_1);

    field_140_max_anger = 2;
    field_158_chase_delay = 10;

    field_142_attack_anger_increaser = pTlv->mAttackAngerIncreaser + 2;
    field_144_wake_up_switch_id = pTlv->mWakeUpSwitchId;
    field_146_wake_up_switch_anger_value = pTlv->mWakeUpSwitchAngerValue;
    field_148_wake_up_switch_value = SwitchStates_Get(pTlv->mWakeUpSwitchId) & 0xFFFF;
    field_14A_can_wake_up_switch_id = pTlv->mCanWakeUpSwitchId;
    field_150_patrol_range = FP_GetExponent(FP_FromInteger(pTlv->mPatrolRangeInGrids) * ScaleToGridSize(mSpriteScale));
    field_15C_lost_target_timeout = pTlv->mLostTargetTimeout;

    InitTonguePolys();

    field_13E_current_anger = 0;

    if (pTlv->mHanging == Choice_short::eYes_1)
    {
        field_160_hoistX = (pTlv->mBottomRight.x + pTlv->mTopLeft.x) / 2;
        field_166_angle = Fleech_NextRandom();
        mYPos -= FP_FromInteger(pTlv->mTopLeft.y - pTlv->mBottomRight.y);
        TongueHangingFromWall((pTlv->mBottomRight.x + pTlv->mTopLeft.x) / 2, pTlv->mTopLeft.y);
        mCurrentMotion = eFleechMotions::Motion_17_SleepingWithTongue;
        SetAnim();
    }
    else if (mFleechFlags.Get(FleechFlags::eAsleep))
    {
        mCurrentMotion = eFleechMotions::Motion_0_Sleeping;
        SetAnim();
    }
    else
    {
        mCurrentMotion = eFleechMotions::Motion_3_Idle;
        field_13E_current_anger = field_140_max_anger + (field_142_attack_anger_increaser - field_140_max_anger) / 2;
    }
}

const static AnimId sFleechAnimFromMotion[19] = {
    AnimId::Fleech_Sleeping,
    AnimId::Fleech_WakingUp,
    AnimId::Fleech_Unused,
    AnimId::Fleech_Idle,
    AnimId::Fleech_Crawl,
    AnimId::Fleech_PatrolCry,
    AnimId::Fleech_Knockback,
    AnimId::Fleech_StopCrawling,
    AnimId::Fleech_StopMidCrawlCycle,
    AnimId::Fleech_Fall,
    AnimId::Fleech_Land,
    AnimId::Fleech_RaiseHead,
    AnimId::Fleech_Climb,
    AnimId::Fleech_SettleOnGround,
    AnimId::Fleech_ExtendTongueFromEnemy,
    AnimId::Fleech_RetractTongueFromEnemey,
    AnimId::Fleech_DeathByFalling,
    AnimId::Fleech_SleepingWithTongue,
    AnimId::Fleech_Consume};

ALIVE_VAR(1, 0x551840, s32, current_target_object_id_551840, -1);

s32 Fleech::CreateFromSaveState(const u8* pBuffer)
{
    auto pState = reinterpret_cast<const Fleech_State*>(pBuffer);

    auto pTlv = static_cast<Path_Fleech*>(sPathInfo->TLV_From_Offset_Lvl_Cam(pState->mTlvInfo));
    if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kFleechResID, FALSE, FALSE))
    {
        ResourceManager::LoadResourceFile_49C170("FLEECH.BAN", nullptr);
    }

    if (!ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kFleeBlowResID_580, FALSE, FALSE))
    {
        ResourceManager::LoadResourceFile_49C170("FLEEBLOW.BAN", nullptr);
    }

    auto pFleech = relive_new Fleech(pTlv, pState->mTlvInfo);
    if (pFleech)
    {
        pFleech->mBaseGameObjectTlvInfo = pState->field_4_obj_id;

        pFleech->BaseAliveGameObjectPathTLV = nullptr;
        pFleech->BaseAliveGameObjectCollisionLine = nullptr;

        pFleech->BaseAliveGameObject_PlatformId = pState->mPlatformId;

        pFleech->mXPos = pState->mXPos;
        pFleech->mYPos = pState->mYPos;
        pFleech->mVelX = pState->mVelX;
        pFleech->mVelY = pState->mVelY;

        pFleech->mCurrentPath = pState->mPathNumber;
        pFleech->mCurrentLevel = MapWrapper::FromAESaveData(pState->mLvlNumber);
        pFleech->mSpriteScale = pState->mSpriteScale;

        pFleech->mRGB.SetRGB(pState->mRingRed, pState->mRingGreen, pState->mRingBlue);

        pFleech->mCurrentMotion = pState->field_28_current_motion;
        pFleech->mAnim.Set_Animation_Data(sFleechAnimFromMotion[pFleech->mCurrentMotion], nullptr);
        pFleech->mAnim.mCurrentFrame = pState->field_2A_anim_current_frame;
        pFleech->mAnim.mFrameChangeCounter = pState->field_2C_frame_change_counter;

        pFleech->mAnim.mFlags.Set(AnimFlags::eBit5_FlipX, pState->field_26_bFlipX & 1);
        pFleech->mAnim.mFlags.Set(AnimFlags::eBit3_Render, pState->field_2E_bRender & 1);

        pFleech->mBaseGameObjectFlags.Set(BaseGameObject::eDrawable_Bit4, pState->field_2F_bDrawable & 1);

        if (IsLastFrame(&pFleech->mAnim))
        {
            pFleech->mAnim.mFlags.Set(AnimFlags::eBit18_IsLastFrame);
        }
        pFleech->mHealth = pState->mHealth;
        pFleech->mCurrentMotion = pState->mCurrentMotion;
        pFleech->mNextMotion = pState->mNextMotion;

        pFleech->BaseAliveGameObjectLastLineYPos = FP_FromInteger(pState->mLastLineYPos);

        pFleech->mBaseAliveGameObjectFlags.Set(Flags_114::e114_Bit9_RestoredFromQuickSave);

        pFleech->BaseAliveGameObjectCollisionLineType = pState->mCollisionLineType;
        pFleech->mTlvInfo = pState->mTlvInfo;
        pFleech->field_11C_obj_id = pState->field_44_obj_id;
        pFleech->field_120_unused = pState->field_48_unused;
        pFleech->mTongueState = pState->mTongueState;
        pFleech->mTongueSubState = pState->mTongueSubState;
        pFleech->mEnemyXPos = pState->mEnemyXPos;
        pFleech->mEnemyYPos = pState->mEnemyYPos;
        pFleech->mTongueOriginX = pState->mTongueOriginX;
        pFleech->mTongueOriginY = pState->mTongueOriginY;
        pFleech->mTongueDestinationX = pState->mTongueDestinationX;
        pFleech->mTongueDestinationY = pState->mTongueDestinationY;
        pFleech->field_188 = pState->field_5A;

        pFleech->mTongueFlags.Set(TongueFlags::eTongueActive, pState->field_5C_tongue_active_flag & 1);
        pFleech->mTongueFlags.Set(TongueFlags::eRender, pState->field_5D_render_flag & 1);

        pFleech->field_124_brain_state = pState->field_5E_brain_state;
        pFleech->field_126_brain_sub_state = pState->field_60_state;
        pFleech->field_12C_shrivel_timer = pState->field_64_shrivel_timer;
        pFleech->field_128 = pState->field_62;
        sFleechRandomIdx_5BC20C = pState->field_68_fleech_random_idx;
        pFleech->field_130_bDidMapFollowMe = pState->field_6A_bDidMapFollowMe;
        pFleech->field_134_unused = pState->field_6C_unused;
        pFleech->field_138_velx_factor = pState->field_70_velx_factor;
        pFleech->field_13C_unused = pState->field_74_unused;
        pFleech->field_13E_current_anger = pState->field_76_current_anger;
        pFleech->field_140_max_anger = pState->field_78_max_anger;
        pFleech->field_142_attack_anger_increaser = pState->field_7A_attack_anger;
        pFleech->field_144_wake_up_switch_id = pState->field_7C_wakeup_id;
        pFleech->field_146_wake_up_switch_anger_value = pState->field_7E_wake_up_switch_anger_value;
        pFleech->field_148_wake_up_switch_value = pState->field_80_wake_up_switch_value;
        pFleech->field_14A_can_wake_up_switch_id = pState->field_82_can_wake_up_id;
        pFleech->field_14C_EventXPos = pState->field_84_EventXPos;
        pFleech->field_14E_ScrabParamiteEventXPos = pState->field_86_ScrabParamiteEventXPos;
        pFleech->field_150_patrol_range = pState->field_88_patrol_range;
        pFleech->field_152_old_xpos = pState->field_8A_old_xpos;
        pFleech->field_154 = pState->field_8C;
        pFleech->field_156_rnd_crawl = pState->field_8E_rnd_crawl;
        pFleech->field_158_chase_delay = pState->field_90_chase_delay;
        pFleech->field_15A_chase_timer = pState->field_92_chase_timer;
        pFleech->field_15C_lost_target_timeout = pState->field_94_lost_target_timeout;
        pFleech->field_15E_lost_target_timer = pState->field_96_lost_target_timer;
        pFleech->field_160_hoistX = pState->field_98_hoistX;
        pFleech->field_162_hoistY = pState->field_9A_hoistY;
        pFleech->field_164_always_0 = pState->field_9C_always_0;
        pFleech->field_166_angle = pState->field_9E_angle;
        pFleech->field_168_hoistY_distance = pState->field_A0_hoistY_distance;
        pFleech->field_16C_hoistX_distance = pState->field_A4_hoistX_distance;
        pFleech->field_170_danger_obj = pState->field_A8;

        if (pState->field_4_obj_id == pState->field_AC_obj_id)
        {
            current_target_object_id_551840 = pFleech->mBaseGameObjectId;
        }

        pFleech->mFleechFlags.Set(FleechFlags::eHoistDone, pState->mFleechStateFlags.Get(Fleech_State::eHoistDone));
        pFleech->mFleechFlags.Set(FleechFlags::eChasingOrScaredCrawlingLeft, pState->mFleechStateFlags.Get(Fleech_State::eChasingOrScaredCrawlingLeft));
        pFleech->mFleechFlags.Set(FleechFlags::eShrivelDeath, pState->mFleechStateFlags.Get(Fleech_State::eShrivelDeath));
        pFleech->mFleechFlags.Set(FleechFlags::eScaredSound, pState->mFleechStateFlags.Get(Fleech_State::eScaredSound));
        pFleech->mFleechFlags.Set(FleechFlags::eAsleep, pState->mFleechStateFlags.Get(Fleech_State::eAsleep));
        pFleech->mFleechFlags.Set(FleechFlags::eGoesToSleep, pState->mFleechStateFlags.Get(Fleech_State::eGoesToSleep));
        pFleech->mFleechFlags.Set(FleechFlags::ePersistant, pState->mFleechStateFlags.Get(Fleech_State::ePersistant));
    }

    return sizeof(Fleech_State);
}

s32 Fleech::VGetSaveState(u8* pSaveBuffer)
{
    if (mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit7_Electrocuted))
    {
        return 0;
    }

    auto pState = reinterpret_cast<Fleech_State*>(pSaveBuffer);

    pState->field_0_type = AETypes::eFleech_50;
    pState->field_4_obj_id = mBaseGameObjectTlvInfo;
    pState->mXPos = mXPos;
    pState->mYPos = mYPos;
    pState->mVelX = mVelX;
    pState->mVelY = mVelY;
    pState->field_70_velx_factor = field_138_velx_factor;
    pState->mPathNumber = mCurrentPath;
    pState->mLvlNumber = MapWrapper::ToAE(mCurrentLevel);
    pState->mSpriteScale = mSpriteScale;
    pState->mRingRed = mRGB.r;
    pState->mRingGreen = mRGB.g;
    pState->mRingBlue = mRGB.b;
    pState->field_26_bFlipX = mAnim.mFlags.Get(AnimFlags::eBit5_FlipX);
    pState->field_28_current_motion = mCurrentMotion;
    pState->field_2A_anim_current_frame = mAnim.mCurrentFrame;
    pState->field_2C_frame_change_counter = mAnim.mFrameChangeCounter;
    pState->field_2F_bDrawable = mBaseGameObjectFlags.Get(BaseGameObject::eDrawable_Bit4);
    pState->field_2E_bRender = mAnim.mFlags.Get(AnimFlags::eBit3_Render);
    pState->mHealth = mHealth;
    pState->mCurrentMotion = mCurrentMotion;
    pState->mNextMotion = mNextMotion;
    pState->mLastLineYPos = FP_GetExponent(BaseAliveGameObjectLastLineYPos);

    if (BaseAliveGameObjectCollisionLine)
    {
        pState->mCollisionLineType = BaseAliveGameObjectCollisionLine->mLineType;
    }
    else
    {
        pState->mCollisionLineType = -1;
    }

    if (BaseAliveGameObject_PlatformId != -1)
    {
        BaseGameObject* pObj = sObjectIds.Find_Impl(BaseAliveGameObject_PlatformId);
        if (pObj)
        {
            pState->mPlatformId = pObj->mBaseGameObjectTlvInfo;
        }
    }
    else
    {
        pState->mPlatformId = -1;
    }

    if (field_11C_obj_id != -1)
    {
        BaseGameObject* pObj = sObjectIds.Find_Impl(field_11C_obj_id);
        if (pObj)
        {
            pState->field_44_obj_id = pObj->mBaseGameObjectTlvInfo;
        }
    }
    else
    {
        pState->field_44_obj_id = -1;
    }

    pState->mTlvInfo = mTlvInfo;
    pState->field_48_unused = field_120_unused;
    pState->mTongueState = mTongueState;
    pState->mTongueSubState = mTongueSubState;
    pState->mEnemyXPos = mEnemyXPos;
    pState->mEnemyYPos = mEnemyYPos;
    pState->mTongueOriginX = mTongueOriginX;
    pState->mTongueOriginY = mTongueOriginY;
    pState->mTongueDestinationX = mTongueDestinationX;
    pState->mTongueDestinationY = mTongueDestinationY;
    pState->field_5A = field_188;
    pState->field_5C_tongue_active_flag = mTongueFlags.Get(TongueFlags::eTongueActive);
    pState->field_5D_render_flag = mTongueFlags.Get(TongueFlags::eRender);
    pState->field_5E_brain_state = field_124_brain_state;
    pState->field_60_state = field_126_brain_sub_state;
    pState->field_64_shrivel_timer = field_12C_shrivel_timer - sGnFrame;
    pState->field_62 = field_128;
    pState->field_68_fleech_random_idx = sFleechRandomIdx_5BC20C;
    pState->field_6A_bDidMapFollowMe = field_130_bDidMapFollowMe;
    pState->field_6C_unused = field_134_unused;
    pState->field_70_velx_factor = field_138_velx_factor;
    pState->field_74_unused = field_13C_unused;
    pState->field_76_current_anger = field_13E_current_anger;
    pState->field_78_max_anger = field_140_max_anger;
    pState->field_7A_attack_anger = field_142_attack_anger_increaser;
    pState->field_7C_wakeup_id = field_144_wake_up_switch_id;
    pState->field_7E_wake_up_switch_anger_value = field_146_wake_up_switch_anger_value;
    pState->field_80_wake_up_switch_value = field_148_wake_up_switch_value;
    pState->field_82_can_wake_up_id = field_14A_can_wake_up_switch_id;
    pState->field_84_EventXPos = field_14C_EventXPos;
    pState->field_86_ScrabParamiteEventXPos = field_14E_ScrabParamiteEventXPos;
    pState->field_88_patrol_range = field_150_patrol_range;
    pState->field_8A_old_xpos = field_152_old_xpos;
    pState->field_8C = field_154;
    pState->field_8E_rnd_crawl = field_156_rnd_crawl;
    pState->field_90_chase_delay = field_158_chase_delay;
    pState->field_92_chase_timer = field_15A_chase_timer;
    pState->field_94_lost_target_timeout = field_15C_lost_target_timeout;
    pState->field_96_lost_target_timer = field_15E_lost_target_timer;
    pState->field_98_hoistX = field_160_hoistX;
    pState->field_9A_hoistY = field_162_hoistY;
    pState->field_9C_always_0 = field_164_always_0;
    pState->field_9E_angle = field_166_angle;
    pState->field_A0_hoistY_distance = field_168_hoistY_distance;
    pState->field_A4_hoistX_distance = field_16C_hoistX_distance;

    if (field_170_danger_obj != -1)
    {
        BaseGameObject* pObj = sObjectIds.Find_Impl(field_170_danger_obj);
        if (pObj)
        {
            pState->field_A8 = pObj->mBaseGameObjectTlvInfo;
        }
    }
    else
    {
        pState->field_A8 = -1;
    }

    if (current_target_object_id_551840 == mBaseGameObjectId)
    {
        pState->field_AC_obj_id = mBaseGameObjectTlvInfo;
    }
    else
    {
        pState->field_AC_obj_id = -1;
    }

    pState->mFleechStateFlags.Set(Fleech_State::eHoistDone, mFleechFlags.Get(FleechFlags::eHoistDone));
    pState->mFleechStateFlags.Set(Fleech_State::eChasingOrScaredCrawlingLeft, mFleechFlags.Get(FleechFlags::eChasingOrScaredCrawlingLeft));
    pState->mFleechStateFlags.Set(Fleech_State::eShrivelDeath, mFleechFlags.Get(FleechFlags::eShrivelDeath));
    pState->mFleechStateFlags.Set(Fleech_State::eScaredSound, mFleechFlags.Get(FleechFlags::eScaredSound));
    pState->mFleechStateFlags.Set(Fleech_State::eAsleep, mFleechFlags.Get(FleechFlags::eAsleep));
    pState->mFleechStateFlags.Set(Fleech_State::eGoesToSleep, mFleechFlags.Get(FleechFlags::eGoesToSleep));
    pState->mFleechStateFlags.Set(Fleech_State::ePersistant, mFleechFlags.Get(FleechFlags::ePersistant));

    return sizeof(Fleech_State);
}

void Fleech::Motion_0_Sleeping()
{
    if (mNextMotion == -1)
    {
        if (mAnim.mCurrentFrame || sGnFrame & 3)
        {
            if (mAnim.mCurrentFrame == 4 && !(sGnFrame & 3))
            {
                Sound(FleechSound::SleepingExhale_4);

                if (gMap.Is_Point_In_Current_Camera(mCurrentLevel, mCurrentPath, mXPos, mYPos, 0))
                {
                    const FP yPos = (mSpriteScale * FP_FromInteger(-20)) + mYPos;
                    FP xOff = {};
                    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        xOff = -(mSpriteScale * FP_FromInteger(10));
                    }
                    else
                    {
                        xOff = (mSpriteScale * FP_FromInteger(10));
                    }
                    relive_new SnoozeParticle(xOff + mXPos, yPos, mAnim.mRenderLayer, mAnim.field_14_scale);
                }
            }
        }
        else
        {
            Sound(FleechSound::SleepingInhale_3);
        }
    }
    else
    {
        mCurrentMotion = mNextMotion;
        mNextMotion = -1;
    }
}

void Fleech::Motion_1_WakingUp()
{
    for (s32 i = 0; i < gBaseGameObjects->Size(); i++)
    {
        auto pObj = gBaseGameObjects->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if (pObj->Type() == ReliveTypes::eSnoozeParticle)
        {
            static_cast<SnoozeParticle*>(pObj)->mState = SnoozeParticle::SnoozeParticleState::eBlowingUp_2;
        }
    }

    if (mNextMotion != -1)
    {
        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            mCurrentMotion = mNextMotion;
            mNextMotion = -1;
            Sound(FleechSound::WakeUp_6);
        }
    }
}

// this function is actually used
void Fleech::Motion_2_Unknown()
{
    if (mNextMotion != -1)
    {
        if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            mCurrentMotion = mNextMotion;
            mNextMotion = -1;
        }
    }
}

void Fleech::Motion_3_Idle()
{
    if (!CanMove())
    {
        if (mNextMotion == -1)
        {
            FP hitX = {};
            FP hitY = {};
            PathLine* pLine = nullptr;
            if (mCurrentMotion == eFleechMotions::Motion_3_Idle && mAnim.mCurrentFrame == 0 && !sCollisions->Raycast(mXPos - FP_FromInteger(5), mYPos - FP_FromInteger(5), mXPos + FP_FromInteger(5), mYPos + FP_FromInteger(1), &pLine, &hitX, &hitY, mScale == Scale::Fg ? kFgFloor : kBgFloor))
            {
                field_138_velx_factor = FP_FromInteger(0);
                BaseAliveGameObjectLastLineYPos = mYPos;
                mCurrentMotion = eFleechMotions::Motion_9_Fall;
            }
        }
        else
        {
            mCurrentMotion = mNextMotion;
            mNextMotion = -1;
        }
    }
}

const FP sFleechCrawlVelX_544FA0[7] = {
    FP_FromDouble(3.8364105224609375),
    FP_FromDouble(3.36883544921875),
    FP_FromDouble(4.6882781982421875),
    FP_FromDouble(4.9884185791015625),
    FP_FromDouble(2.5774078369140625),
    FP_FromDouble(3.3113861083984375),
    FP_FromDouble(2.2292022705078125)};

void Fleech::Motion_4_Crawl()
{
    if (mAnim.mCurrentFrame > 6)
    {
        mAnim.mCurrentFrame = 0;
    }

    FP velXTable = {};
    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        velXTable = -sFleechCrawlVelX_544FA0[mAnim.mCurrentFrame];
    }
    else
    {
        velXTable = sFleechCrawlVelX_544FA0[mAnim.mCurrentFrame];
    }

    mVelX = (mSpriteScale * velXTable);

    const FP k1Directed = FP_FromInteger((mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) != 0) ? -1 : 1);
    if (WallHit(FP_FromInteger((mSpriteScale >= FP_FromInteger(1)) ? 10 : 5), ScaleToGridSize(mSpriteScale) * k1Directed))
    {
        ToIdle();
    }
    else
    {
        MoveAlongFloor();
        if (mCurrentMotion == eFleechMotions::Motion_4_Crawl)
        {
            if (mAnim.mCurrentFrame == 4)
            {
                Sound(FleechSound::CrawlRNG1_14);
            }
            else if (mAnim.mCurrentFrame == 6)
            {
                if (field_130_bDidMapFollowMe == 0)
                {
                    field_130_bDidMapFollowMe = 1;
                    MapFollowMe(TRUE);
                }

                if (mNextMotion == eFleechMotions::Motion_3_Idle)
                {
                    mCurrentMotion = eFleechMotions::Motion_8_StopMidCrawlCycle;
                    mNextMotion = -1;
                }
                else if (mNextMotion != -1)
                {
                    mCurrentMotion = mNextMotion;
                    mNextMotion = -1;
                }
            }
            else
            {
                field_130_bDidMapFollowMe = 0;
            }
        }
    }
}

void Fleech::Motion_5_PatrolCry()
{
    if (mAnim.mCurrentFrame == 0)
    {
        Sound(FleechSound::PatrolCry_0);
        field_13C_unused = 1;
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle();
    }
}

void Fleech::Motion_6_Knockback()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mAnim.mFlags.Toggle(AnimFlags::eBit5_FlipX);
        ToIdle();
    }
}

void Fleech::Motion_7_StopCrawling()
{
    const FP k1Directed = FP_FromInteger(mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) != 0 ? -1 : 1);
    if (WallHit(FP_FromInteger(mSpriteScale >= FP_FromInteger(1) ? 10 : 5), ScaleToGridSize(mSpriteScale) * k1Directed))
    {
        ToIdle();
    }
    else if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        MapFollowMe(TRUE);
        if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
        {
            mVelX = (ScaleToGridSize(mSpriteScale) / FP_FromInteger(7));
            mAnim.mFlags.Clear(AnimFlags::eBit5_FlipX);
        }
        else
        {
            mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(7));
            mAnim.mFlags.Set(AnimFlags::eBit5_FlipX);
        }
        mCurrentMotion = eFleechMotions::Motion_4_Crawl;
    }
}

void Fleech::Motion_8_StopMidCrawlCycle()
{
    const FP k1Directed = FP_FromInteger(mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) ? -1 : 1); // TODO: Correct way around ??
    if (WallHit(
            FP_FromInteger(mSpriteScale >= FP_FromInteger(1) ? 10 : 5),
            ScaleToGridSize(mSpriteScale) * k1Directed)
        || mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle();
    }
}

void Fleech::Motion_9_Fall()
{
    mVelY += mSpriteScale * FP_FromDouble(1.8);

    if (mVelY > (mSpriteScale * FP_FromInteger(20)))
    {
        mVelY = (mSpriteScale * FP_FromInteger(20));
    }

    if (mVelX > FP_FromInteger(0))
    {
        if (mVelX > FP_FromDouble(3.6))
        {
            mVelX = FP_FromDouble(3.6);
        }
    }
    else if (mVelX < FP_FromInteger(0))
    {
        if (mVelX < FP_FromDouble(-3.6))
        {
            mVelX = FP_FromDouble(-3.6);
        }
    }

    if (mVelX > FP_FromInteger(0))
    {
        mVelX -= mSpriteScale * field_138_velx_factor;
        if (mVelX < FP_FromInteger(0))
        {
            mVelX = FP_FromInteger(0);
        }
    }
    else if (mVelX < FP_FromInteger(0))
    {
        mVelX += mSpriteScale * field_138_velx_factor;
        if (mVelX > FP_FromInteger(0))
        {
            mVelX = FP_FromInteger(0);
        }
    }

    const FP xpos = mXPos;
    const FP ypos = mYPos - FP_FromInteger((mSpriteScale >= FP_FromInteger(1) ? 10 : 5));
    mXPos += mVelX;
    mYPos += mVelY;

    FP hitX = {};
    FP hitY = {};
    PathLine* pLine = nullptr;
    if (sCollisions->Raycast(
            xpos,
            ypos,
            mXPos,
            mYPos,
            &pLine,
            &hitX,
            &hitY,
            mScale == Scale::Fg ? kFgFloorCeilingOrWalls : kBgFloorCeilingOrWalls))
    {
        switch (pLine->mLineType)
        {
            case 0u:
            case 4u:
            case 32u:
            case 36u:
                BaseAliveGameObjectCollisionLine = pLine;
                mXPos = hitX;
                mYPos = hitY;
                MapFollowMe(TRUE);
                if (BaseAliveGameObjectCollisionLine->mLineType == eLineTypes::eDynamicCollision_32 || BaseAliveGameObjectCollisionLine->mLineType == eLineTypes::eBackgroundDynamicCollision_36)
                {
                    const PSX_RECT bRect = VGetBoundingRect();
                    VOnCollisionWith(
                        {bRect.x, static_cast<s16>(bRect.y + 5)},
                        {bRect.w, static_cast<s16>(FP_GetExponent(mYPos) + 5)},
                        ObjList_5C1B78,
                        1,
                        (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection);
                }
                if (mYPos - BaseAliveGameObjectLastLineYPos <= FP_FromInteger((mSpriteScale >= FP_FromInteger(1) ? 20 : 10)) * FP_FromInteger(15))
                {
                    mCurrentMotion = eFleechMotions::Motion_10_Land;
                }
                else
                {
                    mCurrentMotion = eFleechMotions::Motion_16_DeathByFalling;
                }
                break;

            case 1u:
            case 2u:
            case 5u:
            case 6u:
                mXPos = hitX - mVelX;
                mYPos = hitY;
                MapFollowMe(TRUE);
                mVelX = FP_FromInteger(0);
                break;

            default:
                return;
        }
    }
}

void Fleech::Motion_10_Land()
{
    if (mAnim.mCurrentFrame == 0)
    {
        Sound(FleechSound::LandOnFloor_9);
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle();
    }
}

void Fleech::Motion_11_RaiseHead()
{
    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mFleechFlags.Clear(FleechFlags::eHoistDone);
        mCurrentMotion = eFleechMotions::Motion_12_Climb;

        mVelX = FP_FromInteger(0);
        mVelY = FP_FromInteger(-1);

        const s16 yOff = mSpriteScale >= FP_FromInteger(1) ? 0 : -10;
        auto pHoist = static_cast<Path_Hoist*>(sPathInfo->TLV_Get_At_4DB4B0(
            field_160_hoistX,
            FP_GetExponent(mYPos - FP_FromInteger((yOff + 20))),
            field_160_hoistX,
            FP_GetExponent(mYPos - FP_FromInteger((yOff + 20))),
            TlvTypes::Hoist_2));

        if (pHoist->mHoistType == Path_Hoist::Type::eOffScreen)
        {
            const FP doubleYOff = FP_FromInteger(yOff + 20) * FP_FromInteger(2);
            pHoist = static_cast<Path_Hoist*>(sPathInfo->TLV_Get_At_4DB4B0(
                field_160_hoistX,
                FP_GetExponent(FP_FromInteger(pHoist->mTopLeft.y) - doubleYOff),
                field_160_hoistX,
                FP_GetExponent(FP_FromInteger(pHoist->mTopLeft.y) - doubleYOff),
                TlvTypes::Hoist_2));

            field_162_hoistY = pHoist->mTopLeft.y;
        }
        BaseAliveGameObjectLastLineYPos = mYPos;
        field_168_hoistY_distance = mYPos - FP_FromInteger(field_162_hoistY);
        BaseAliveGameObjectCollisionLine = nullptr;
        field_16C_hoistX_distance = FP_Abs(mXPos - FP_FromInteger(field_160_hoistX));

        if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
        {
            field_166_angle = -64;
        }
        else
        {
            field_166_angle = 64;
        }
        field_164_always_0 = 0;
        sub_42BA10();
    }
    else if (mAnim.mCurrentFrame < 4)
    {
        mXPos += FP_FromInteger((mAnim.mFlags.Get(AnimFlags::eBit5_FlipX)) != 0 ? 1 : -1);
    }
}

void Fleech::Motion_12_Climb()
{
    if (!TongueActive())
    {
        if (mFleechFlags.Get(FleechFlags::eHoistDone))
        {
            mCurrentMotion = eFleechMotions::Motion_13_SettleOnGround;
            return;
        }

        const FP velYOff = FP_FromInteger(field_164_always_0) * FP_FromDouble(0.045);
        mVelY -= mSpriteScale * (FP_FromDouble(0.7) - velYOff);
        if (field_164_always_0 > 0)
        {
            field_164_always_0--;
        }

        const FP xOff = (Math_Cosine_496CD0(field_166_angle) * (field_16C_hoistX_distance * ((mYPos - FP_FromInteger(field_162_hoistY)) / field_168_hoistY_distance)));

        FP pX1 = {};
        if (xOff < FP_FromInteger(0))
        {
            pX1 = xOff + mXPos;
        }
        else
        {
            pX1 = mXPos;
        }

        const FP pY1 = mVelY + mYPos - FP_FromInteger(mSpriteScale < FP_FromInteger(1) ? 10 : 20);

        FP pX2;
        if (xOff < FP_FromInteger(0))
        {
            pX2 = mXPos;
        }
        else
        {
            pX2 = xOff + mXPos;
        }

        PathLine* pLine = nullptr;
        FP hitX = {};
        FP hitY = {};
        if (sCollisions->Raycast(pX1, pY1, pX2, mVelY + mYPos, &pLine, &hitX, &hitY, mScale == Scale::Fg ? kFgWalls : kBgWalls))
        {
            switch (pLine->mLineType)
            {
                case 1u:
                case 5u:
                    Sound(FleechSound::LandOnFloor_9);
                    // TODO: Somewhat suspect that these branches are equal - OG bug?
                    if (field_166_angle >= 64u && field_166_angle > 192u)
                    {
                        field_166_angle = -128 - field_166_angle;
                    }
                    else
                    {
                        field_166_angle = -128 - field_166_angle;
                    }
                    break;

                case 2u:
                case 6u:
                    Sound(FleechSound::LandOnFloor_9);
                    if (field_166_angle > 64u && field_166_angle < 128u)
                    {
                        field_166_angle = -128 - field_166_angle;
                    }
                    else if (field_166_angle > 128 && field_166_angle < 192)
                    {
                        field_166_angle = -128 - field_166_angle;
                    }
                    break;

                default:
                    break;
            }
        }

        mXPos = xOff + FP_FromInteger(field_160_hoistX);
        field_166_angle = field_166_angle + 16;
        mYPos += mVelY;

        if (mYPos <= FP_FromInteger(field_162_hoistY))
        {
            mXPos = FP_FromInteger(field_160_hoistX);
            mYPos = FP_FromInteger(field_162_hoistY);
            mVelY = FP_FromInteger(0);
            mFleechFlags.Set(FleechFlags::eHoistDone);
        }
        return;
    }
}

void Fleech::Motion_13_SettleOnGround()
{
    if (!mAnim.mCurrentFrame)
    {
        SetTongueState5();

        PathLine* pLine = nullptr;
        FP hitX = {};
        FP hitY = {};
        if (sCollisions->Raycast(
                mXPos - FP_FromInteger(5),
                mYPos - FP_FromInteger(5),
                mXPos + FP_FromInteger(5),
                mYPos + FP_FromInteger(5),
                &pLine,
                &hitX,
                &hitY,
                mScale == Scale::Fg ? kFgFloor : kBgFloor))
        {
            BaseAliveGameObjectCollisionLine = pLine;
            MapFollowMe(TRUE);
        }
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        Fleech::ToIdle();
    }
}

void Fleech::Motion_14_ExtendTongueFromEnemy()
{
    if (field_11C_obj_id == sActiveHero->mBaseGameObjectId && (sActiveHero->CantBeDamaged_44BAB0() || sActiveHero->mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit8_bInvisible)))
    {
        ToIdle();
    }
    else if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        PullTargetIn();
        mCurrentMotion = eFleechMotions::Motion_15_RetractTongueFromEnemey;
    }
}

void Fleech::Motion_15_RetractTongueFromEnemey()
{
    if (IsActiveHero(sObjectIds.Find_Impl(field_11C_obj_id)) && ((sActiveHero->CantBeDamaged_44BAB0()) || sActiveHero->mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit8_bInvisible)))
    {
        sub_42B8C0();
        ToIdle();
    }
    else
    {
        if (!TongueActive())
        {
            ToIdle();
        }

        if (mNextMotion == eFleechMotions::Motion_18_Consume)
        {
            mCurrentMotion = eFleechMotions::Motion_18_Consume;
            mNextMotion = -1;
        }
    }
}

void Fleech::Motion_16_DeathByFalling()
{
    if (mHealth > FP_FromInteger(0))
    {
        relive_new Blood(mXPos, mYPos - FP_FromInteger(8), FP_FromInteger(0), -FP_FromInteger(5), mSpriteScale, 50);

        Sound(FleechSound::DeathByHeight_12);
        Sound(FleechSound::Scared_7);

        mHealth = FP_FromInteger(0);
        field_124_brain_state = eFleechBrains::eBrain_3_Death;
        mFleechFlags.Set(FleechFlags::eShrivelDeath);
        mNextMotion = -1;
        field_12C_shrivel_timer = sGnFrame + 127;
        sFleechCount_5BC20E--;
    }
}

void Fleech::Motion_17_SleepingWithTongue()
{
    if (mNextMotion != -1)
    {
        SetTongueState1();
        mCurrentMotion = mNextMotion;
        mNextMotion = -1;
    }
    else
    {
        if (mAnim.mCurrentFrame || sGnFrame & 3)
        {
            if (mAnim.mCurrentFrame == 4 && !(sGnFrame & 3))
            {
                Sound(FleechSound::SleepingExhale_4);
                if (gMap.Is_Point_In_Current_Camera(mCurrentLevel, mCurrentPath, mXPos, mYPos, 0))
                {
                    const FP yPos = (mSpriteScale * FP_FromInteger(-20)) + mYPos;
                    FP xOff = {};
                    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        xOff = -(mSpriteScale * FP_FromInteger(10));
                    }
                    else
                    {
                        xOff = (mSpriteScale * FP_FromInteger(10));
                    }
                    relive_new SnoozeParticle(xOff + mXPos, yPos, mAnim.mRenderLayer, mAnim.field_14_scale);
                }
            }
        }
        else
        {
            Sound(FleechSound::SleepingInhale_3);
        }

        mXPos = FP_FromInteger(field_160_hoistX) + (Math_Cosine_496CD0(field_166_angle) * FP_FromInteger(4)) - FP_FromInteger(mXOffset);
        field_166_angle += 2;
    }
}

void Fleech::Motion_18_Consume()
{
    if (mAnim.mCurrentFrame == 2)
    {
        Sound(FleechSound::Digesting_2);
    }
    else if (mAnim.mCurrentFrame == 15 && field_11C_obj_id == sActiveHero->mBaseGameObjectId)
    {
        sActiveHero->SetAsDead_459430();

        Sound(FleechSound::Burp_1);

        for (s32 i = 0; i < 3; i++)
        {
            auto pDove = relive_new Dove(
                AnimId::Dove_Flying,
                mXPos,
                mYPos + FP_FromInteger(10),
                mSpriteScale);

            if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
            {
                pDove->mXPos += (mSpriteScale * FP_FromInteger(15));
            }
            else
            {
                pDove->mXPos -= (mSpriteScale * FP_FromInteger(15));
            }

            pDove->mSpriteScale = mSpriteScale;
        }
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle();
    }
}

Fleech::~Fleech()
{
    field_170_danger_obj = -1;
    if (mTlvInfo != 0xFFFF)
    {
        Path::TLV_Reset(mTlvInfo, -1, 0, mHealth <= FP_FromInteger(0));
    }

    MusicController::static_PlayMusic(MusicController::MusicTypes::eNone_0, this, 0, 0);
    ResetTarget();

    if (mCurrentMotion == 18)
    {
        if (sActiveHero)
        {
            if (field_11C_obj_id == sActiveHero->mBaseGameObjectId)
            {
                sActiveHero->SetAsDead_459430();
            }
        }
    }
    field_11C_obj_id = -1;

    if (!mFleechFlags.Get(FleechFlags::eShrivelDeath))
    {
        sFleechCount_5BC20E--;
    }
}

void Fleech::VUpdate()
{
    if (mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit9_RestoredFromQuickSave))
    {
        mBaseAliveGameObjectFlags.Clear(Flags_114::e114_Bit9_RestoredFromQuickSave);
        if (BaseAliveGameObjectCollisionLineType == -1)
        {
            BaseAliveGameObjectCollisionLine = nullptr;
        }
        else
        {
            sCollisions->Raycast(
                mXPos,
                mYPos - FP_FromInteger(20),
                mXPos,
                mYPos + FP_FromInteger(20),
                &BaseAliveGameObjectCollisionLine,
                &mXPos,
                &mYPos,
                CollisionMask(static_cast<eLineTypes>(BaseAliveGameObjectCollisionLineType)));
        }
        BaseAliveGameObjectCollisionLineType = 0;
        field_11C_obj_id = BaseGameObject::RefreshId(field_11C_obj_id);
        field_170_danger_obj = BaseGameObject::RefreshId(field_170_danger_obj);
        BaseAliveGameObject_PlatformId = BaseGameObject::RefreshId(BaseAliveGameObject_PlatformId);
    }

    if (EventGet(kEventDeathReset))
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }

    if ((FP_Abs(mXPos - sControlledCharacter->mXPos) <= FP_FromInteger(750) && FP_Abs(mYPos - sControlledCharacter->mYPos) <= FP_FromInteger(520)) || mFleechFlags.Get(FleechFlags::ePersistant))
    {
        const auto oldMotion = mCurrentMotion;

        field_126_brain_sub_state = (this->*sFleechAiTable[field_124_brain_state])();

        TongueUpdate();

        if (mYPos < FP_FromInteger(0))
        {
            mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        }

        const FP oldY = mYPos;
        const FP oldX = mXPos;

        (this->*sFleech_motion_table_551798[mCurrentMotion])();

        if (oldX != mXPos || oldY != mYPos)
        {
            BaseAliveGameObjectPathTLV = sPathInfo->TlvGetAt(
                nullptr,
                mXPos,
                mYPos,
                mXPos,
                mYPos);
            VOnTlvCollision(BaseAliveGameObjectPathTLV);
        }

        if (oldMotion == mCurrentMotion)
        {
            if (field_128)
            {
                mCurrentMotion = mPreviousMotion;
                SetAnim();
                mAnim.SetFrame(mBaseAliveGameObjectLastAnimFrame);
                field_128 = 0;
            }
        }
        else
        {
            SetAnim();
        }
    }
    else
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }
}

void Fleech::VRender(PrimHeader** ot)
{
    if (UpdateDelay() == 0)
    {
        BaseAnimatedWithPhysicsGameObject::VRender(ot);
        RenderEx(ot);
    }
}

void Fleech::RenderEx(PrimHeader** ot)
{
    if (mTongueFlags.Get(Fleech::TongueFlags::eRender))
    {
        FP tongueBlock_X[5] = {};
        FP tongueBlock_Y[5] = {};

        const s16 camX = FP_GetExponent(pScreenManager->CamXPos());
        const s16 camY = FP_GetExponent(pScreenManager->CamYPos());

        tongueBlock_X[0] = FP_FromInteger(mTongueOriginX - camX);
        tongueBlock_Y[0] = FP_FromInteger(mTongueOriginY - camY);
        tongueBlock_X[4] = FP_FromInteger(mTongueDestinationX - camX);
        tongueBlock_Y[4] = FP_FromInteger(mTongueDestinationY - camY);

        const FP distanceX_squared = (tongueBlock_X[0] - tongueBlock_X[4]) * (tongueBlock_X[0] - tongueBlock_X[4]);
        const FP distanceY_squared = (tongueBlock_Y[0] - tongueBlock_Y[4]) * (tongueBlock_Y[0] - tongueBlock_Y[4]);
        const FP distanceXY_squareRoot = Math_SquareRoot_FP_Wrapper(distanceY_squared + distanceX_squared);
        const FP Tan_fp = Math_Tan_496F70(
            tongueBlock_Y[0] - tongueBlock_Y[4],
            tongueBlock_X[4] - tongueBlock_X[0]);
        const FP distanceCosine = Math_Cosine_496CD0(static_cast<u8>(FP_GetExponent(Tan_fp)));
        const FP SineTan = Math_Sine_496DD0(static_cast<u8>(FP_GetExponent(Tan_fp)));

        for (s32 i = 0; i < 4; i++)
        {
            const FP distanceXY_squareRoot_multiplied = distanceXY_squareRoot * FP_FromInteger(i + 1) * FP_FromDouble(0.25);
            const FP cosineIt_times_field188 = Math_Cosine_496CD0(static_cast<u8>(32 * (i + 1))) * FP_FromInteger(field_188);
            tongueBlock_X[i + 1] = tongueBlock_X[0] + SineTan * distanceXY_squareRoot_multiplied - cosineIt_times_field188 * distanceCosine;
            tongueBlock_Y[i + 1] = tongueBlock_Y[0] + SineTan * cosineIt_times_field188 + distanceCosine * distanceXY_squareRoot_multiplied;
        }

        const FP lastTongueBlockModX = tongueBlock_X[4] - FP_FromInteger(mTongueDestinationX + 0xFFFF * camX);
        const FP lastTongueBlockModY = tongueBlock_Y[4] - FP_FromInteger(mTongueDestinationY + 0xFFFF * camY);
        for (s32 i = 0; i < 4; i++)
        {
            const FP lastTongueBlockModX_mult = lastTongueBlockModX * FP_FromInteger(i + 1);
            const FP lastTongueBlockModY_mult = lastTongueBlockModY * FP_FromInteger(i + 1);
            tongueBlock_X[i + 1] -= lastTongueBlockModX_mult * FP_FromDouble(0.25);
            tongueBlock_Y[i + 1] -= lastTongueBlockModY_mult * FP_FromDouble(0.25);
        }

        for (s32 i = 0; i < 4; i++)
        {
            s16 r = static_cast<s16>((i + 1) * 150 / 4);
            s16 g = static_cast<s16>((i + 1) * 100 / 4);
            s16 b = static_cast<s16>((i + 1) * 100 / 4);
            s16 r2 = static_cast<s16>(i * 150 / 4);
            s16 g2 = static_cast<s16>(i * 100 / 4);
            s16 b2 = static_cast<s16>(i * 100 / 4);

            const FP currTongueBlock_Y = tongueBlock_Y[i];
            const FP currTongueBlock_X = tongueBlock_X[i];

            ShadowZone::ShadowZones_Calculate_Colour(
                FP_GetExponent(currTongueBlock_X + FP_FromInteger(camX)),
                FP_GetExponent(currTongueBlock_Y + FP_FromInteger(camY)),
                mScale,
                &r,
                &g,
                &b);
            ShadowZone::ShadowZones_Calculate_Colour(
                FP_GetExponent(currTongueBlock_X + FP_FromInteger(camX)),
                FP_GetExponent(currTongueBlock_Y + FP_FromInteger(camY)),
                mScale,
                &r2,
                &g2,
                &b2);

            Poly_G4* currTonguePoly1 = &mTonguePolys1[i][gPsxDisplay.mBufferIndex];

            const s32 tonguePolyX1 = PsxToPCX(FP_GetExponent(currTongueBlock_X));
            const s32 tonguePolyY1 = FP_GetExponent(currTongueBlock_Y);
            const s32 tonguePolyX2 = PsxToPCX(FP_GetExponent(tongueBlock_X[i + 1]));
            const s32 tonguePolyY2 = FP_GetExponent(tongueBlock_Y[i + 1]);

            SetXY0(
                currTonguePoly1,
                static_cast<s16>(tonguePolyX1),
                static_cast<s16>(tonguePolyY1 - 1));
            SetXY1(
                currTonguePoly1,
                static_cast<s16>(tonguePolyX2),
                static_cast<s16>(tonguePolyY2 - 1));
            SetXY2(
                currTonguePoly1,
                static_cast<s16>(tonguePolyX1),
                static_cast<s16>(tonguePolyY1 + 1));
            SetXY3(
                currTonguePoly1,
                static_cast<s16>(tonguePolyX2),
                static_cast<s16>(tonguePolyY2 + 1));

            SetRGB0(
                currTonguePoly1,
                static_cast<u8>(r2),
                static_cast<u8>(g2),
                static_cast<u8>(b2));
            SetRGB1(
                currTonguePoly1,
                static_cast<u8>(r),
                static_cast<u8>(g),
                static_cast<u8>(b));
            SetRGB2(
                currTonguePoly1,
                static_cast<u8>(r2),
                static_cast<u8>(g2),
                static_cast<u8>(b2));
            SetRGB3(
                currTonguePoly1,
                static_cast<u8>(r),
                static_cast<u8>(g),
                static_cast<u8>(b));

            OrderingTable_Add(OtLayer(ot, mAnim.mRenderLayer), &currTonguePoly1->mBase.header);

            Poly_G4* currTonguePoly2 = &mTonguePolys2[i][gPsxDisplay.mBufferIndex];

            s32 minus_one_one_switch = -1;
            if (FP_GetExponent(Tan_fp) <= 64 || FP_GetExponent(Tan_fp) >= 192)
            {
                minus_one_one_switch = 1;
            }

            SetXY0(
                currTonguePoly2,
                static_cast<s16>(tonguePolyX1 - minus_one_one_switch),
                static_cast<s16>(tonguePolyY1 - 1));
            SetXY1(
                currTonguePoly2,
                static_cast<s16>(tonguePolyX2 - minus_one_one_switch),
                static_cast<s16>(tonguePolyY2 - 1));
            SetXY2(
                currTonguePoly2,
                static_cast<s16>(tonguePolyX1 + minus_one_one_switch),
                static_cast<s16>(tonguePolyY1 + 1));
            SetXY3(
                currTonguePoly2,
                static_cast<s16>(tonguePolyX2 + minus_one_one_switch),
                static_cast<s16>(tonguePolyY2 + 1));

            SetRGB0(
                currTonguePoly2,
                static_cast<u8>(r2),
                static_cast<u8>(g2),
                static_cast<u8>(b2));
            SetRGB1(
                currTonguePoly2,
                static_cast<u8>(r),
                static_cast<u8>(g),
                static_cast<u8>(b));
            SetRGB2(
                currTonguePoly2,
                static_cast<u8>(r2),
                static_cast<u8>(g2),
                static_cast<u8>(b2));
            SetRGB3(
                currTonguePoly2,
                static_cast<u8>(r),
                static_cast<u8>(g),
                static_cast<u8>(b));

            OrderingTable_Add(OtLayer(ot, mAnim.mRenderLayer), &currTonguePoly2->mBase.header);

            s16 invRect_x;
            s16 invRect_y;
            s16 invRect_w;
            s16 invRect_h;

            const s16 smallerof1andBaseX = std::min(
                currTonguePoly2->mVerts[1].mVert.x,
                currTonguePoly2->mBase.vert.x);
            const s16 biggerof2and0X = std::max(
                currTonguePoly2->mVerts[0].mVert.x,
                currTonguePoly2->mVerts[2].mVert.x);

            const s16 smallerof0andBaseY = std::min(
                currTonguePoly2->mVerts[0].mVert.y,
                currTonguePoly2->mBase.vert.y);
            const s16 biggerof1and2Y = std::max(
                currTonguePoly2->mVerts[1].mVert.y,
                currTonguePoly2->mVerts[2].mVert.y);

            if (smallerof1andBaseX < biggerof2and0X)
            {
                invRect_x = smallerof1andBaseX;
                invRect_w = biggerof2and0X;
            }
            else
            {
                invRect_x = biggerof2and0X;
                invRect_w = smallerof1andBaseX;
            }

            if (smallerof0andBaseY < biggerof1and2Y)
            {
                invRect_y = smallerof0andBaseY;
                invRect_h = biggerof1and2Y;
            }
            else
            {
                invRect_y = biggerof1and2Y;
                invRect_h = smallerof0andBaseY;
            }

            pScreenManager->InvalidateRectCurrentIdx(
                invRect_x,
                invRect_y,
                invRect_w,
                invRect_h);
        }
        const s32 tPage = PSX_getTPage(TPageMode::e4Bit_0, TPageAbr::eBlend_0, 0, 0);
        Init_SetTPage(&field_40C[gPsxDisplay.mBufferIndex], 1, 0, tPage);
        OrderingTable_Add(OtLayer(ot, mAnim.mRenderLayer), &field_40C[gPsxDisplay.mBufferIndex].mBase);
        return;
    }
}

void Fleech::VScreenChanged()
{
    if (gMap.mCurrentLevel != gMap.mNextLevel || gMap.mCurrentPath != gMap.mNextPath || gMap.mOverlayId != gMap.GetOverlayId())
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        field_11C_obj_id = -1;
        field_170_danger_obj = -1;
    }
}

void Fleech::VOnTlvCollision(Path_TLV* pTlv)
{
    while (pTlv)
    {
        if (pTlv->mTlvType32 == TlvTypes::DeathDrop_4)
        {
            mHealth = FP_FromInteger(0);
            mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        }
        pTlv = sPathInfo->TlvGetAt(pTlv, mXPos, mYPos, mXPos, mYPos);
    }
}

s16 Fleech::IsScrabOrParamiteNear(FP radius)
{
    BaseAliveGameObject* pNearestScrabOrParamite = nullptr;
    for (s32 i = 0; i < gBaseGameObjects->Size(); i++)
    {
        BaseGameObject* pBaseObj = gBaseGameObjects->ItemAt(i);
        if (!pBaseObj)
        {
            break;
        }

        if (pBaseObj->mBaseGameObjectFlags.Get(BaseGameObject::eIsBaseAliveGameObject_Bit6))
        {
            auto pObj = static_cast<BaseAliveGameObject*>(pBaseObj);
            if ((pObj->Type() == ReliveTypes::eScrab || pObj->Type() == ReliveTypes::eParamite) && pObj->mHealth > FP_FromInteger(0))
            {
                if (pObj->mSpriteScale == mSpriteScale)
                {
                    bool check = false;
                    if (mYPos >= pObj->mYPos)
                    {
                        if (mYPos - pObj->mYPos > (FP_FromInteger(mSpriteScale >= FP_FromInteger(1) ? 20 : 10) * FP_FromInteger(2)))
                        {
                            if (mYPos < pObj->mYPos)
                            {
                                if (pObj->mYPos - mYPos <= (FP_FromInteger(mSpriteScale >= FP_FromInteger(1) ? 2 : 1)))
                                {
                                    check = true;
                                }
                            }
                        }
                        else
                        {
                            check = true;
                        }
                    }
                    else
                    {
                        if (pObj->mYPos - mYPos <= (FP_FromInteger(mSpriteScale >= FP_FromInteger(1) ? +2 : 1)))
                        {
                            check = true;
                        }
                    }

                    if (check)
                    {
                        if (VIsObjNearby(radius, pObj))
                        {
                            if (!WallHit(FP_FromInteger(mSpriteScale >= FP_FromInteger(1) ? 10 : 5), pObj->mXPos - mXPos))
                            {
                                if (!pNearestScrabOrParamite)
                                {
                                    pNearestScrabOrParamite = pObj;
                                }
                                else if (FP_GetExponent(FP_Abs(pObj->mXPos - mXPos)) < FP_GetExponent(FP_Abs(pNearestScrabOrParamite->mXPos - mXPos)))
                                {
                                    pNearestScrabOrParamite = pObj;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (pNearestScrabOrParamite)
    {
        field_170_danger_obj = pNearestScrabOrParamite->mBaseGameObjectId;
        return 1;
    }

    field_170_danger_obj = -1;
    return 0;
}

const TintEntry kFleechTints_551844[15] = {
    {EReliveLevelIds::eMines, 127u, 127u, 127u},
    {EReliveLevelIds::eNecrum, 137u, 137u, 137u},
    {EReliveLevelIds::eMudomoVault, 127u, 127u, 127u},
    {EReliveLevelIds::eMudancheeVault, 127u, 127u, 127u},
    {EReliveLevelIds::eFeeCoDepot, 127u, 127u, 127u},
    {EReliveLevelIds::eBarracks, 127u, 127u, 127u},
    {EReliveLevelIds::eMudancheeVault_Ender, 127u, 127u, 127u},
    {EReliveLevelIds::eBonewerkz, 127u, 127u, 127u},
    {EReliveLevelIds::eBrewery, 127u, 127u, 127u},
    {EReliveLevelIds::eBrewery_Ender, 127u, 127u, 127u},
    {EReliveLevelIds::eMudomoVault_Ender, 127u, 127u, 127u},
    {EReliveLevelIds::eFeeCoDepot_Ender, 127u, 127u, 127u},
    {EReliveLevelIds::eBarracks_Ender, 127u, 127u, 127u},
    {EReliveLevelIds::eBonewerkz_Ender, 127u, 127u, 127u},
    {EReliveLevelIds::eNone, 127u, 127u, 127u}};

s32 Animation_OnFrame_Fleech_449A60(BaseGameObject* pObj, s16* pData)
{
    reinterpret_cast<Fleech*>(pObj)->VOnFrame(pData);
    return 1;
}

void Fleech::Init()
{
    const AnimRecord& rec = AnimRec(AnimId::Fleech_Idle);
    field_10_resources_array.SetAt(0, ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, rec.mResourceId, TRUE, FALSE));
    field_10_resources_array.SetAt(1, ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, AEResourceID::kFleeBlowResID_580, TRUE, FALSE));

    Animation_Init(AnimId::Fleech_Idle, field_10_resources_array.ItemAt(0));

    mAnim.mFnPtrArray = kFleech_Anim_Frame_Fns_55EFD0;

    SetType(ReliveTypes::eFleech);

    mBaseGameObjectFlags.Set(BaseGameObject::eCanExplode_Bit7);
    mBaseAliveGameObjectFlags.Set(Flags_114::e114_Bit6_SetOffExplosives);

    mFleechFlags.Clear(FleechFlags::eShrivelDeath);
    mFleechFlags.Clear(FleechFlags::eScaredSound);

    mVisualFlags.Set(VisualFlags::eDoPurpleLightEffect);

    field_12C_shrivel_timer = 0;
    field_126_brain_sub_state = 0;
    mNextMotion = -1;
    BaseAliveGameObject_PlatformId = -1;
    field_128 = 0;
    field_11C_obj_id = -1;
    field_170_danger_obj = -1;
    field_15E_lost_target_timer = 0;

    SetTint(&kFleechTints_551844[0], gMap.mCurrentLevel);

    if (mSpriteScale == FP_FromInteger(1))
    {
        mAnim.mRenderLayer = Layer::eLayer_SlogFleech_34;
        mScale = Scale::Fg;
    }
    else
    {
        mAnim.mRenderLayer = Layer::eLayer_SlogFleech_Half_15;
        mScale = Scale::Bg;
    }

    FP hitX = {};
    FP hitY = {};
    if (sCollisions->Raycast(
            mXPos,
            mYPos,
            mXPos,
            mYPos + FP_FromInteger(24),
            &BaseAliveGameObjectCollisionLine,
            &hitX,
            &hitY,
            mScale == Scale::Fg ? kFgFloor : kBgFloor)
        == 1)
    {
        mYPos = hitY;
    }

    MapFollowMe(TRUE);

    VStackOnObjectsOfType(ReliveTypes::eFleech);

    mShadow = relive_new Shadow();

    sFleechCount_5BC20E++;
}

void Fleech::InitTonguePolys()
{
    mTongueFlags.Clear(TongueFlags::eTongueActive);
    mTongueFlags.Clear(TongueFlags::eRender);

    mTongueOriginX = FP_GetExponent(mXPos);
    mTongueOriginY = FP_GetExponent(FP_FromInteger(2) * ((FP_FromInteger(mSpriteScale >= FP_FromInteger(1) ? -10 : -5)) + mYPos));

    mTongueState = 1;

    mTongueDestinationX = -1;
    mTongueDestinationY = -1;

    for (s32 i = 0; i < 4; i++)
    {
        for (s32 j = 0; j < 2; j++)
        {
            PolyG4_Init(&mTonguePolys1[i][j]);
            SetRGB0(&mTonguePolys1[i][j], 150, 100, 100);
            SetRGB1(&mTonguePolys1[i][j], 150, 100, 100);
            SetRGB2(&mTonguePolys1[i][j], 150, 100, 100);
            SetRGB3(&mTonguePolys1[i][j], 150, 100, 100);
            Poly_Set_SemiTrans(&mTonguePolys1[i][j].mBase.header, FALSE);

            PolyG4_Init(&mTonguePolys2[i][j]);
            SetRGB0(&mTonguePolys2[i][j], 150, 100, 100);
            SetRGB1(&mTonguePolys2[i][j], 150, 100, 100);
            SetRGB2(&mTonguePolys2[i][j], 150, 100, 100);
            SetRGB3(&mTonguePolys2[i][j], 150, 100, 100);
            Poly_Set_SemiTrans(&mTonguePolys2[i][j].mBase.header, TRUE);
        }
    }
}

void Fleech::SetAnim()
{
    u8** ppRes = ResBlockForMotion(mCurrentMotion);
    mAnim.Set_Animation_Data(sFleechAnimFromMotion[mCurrentMotion], ppRes);
}

void Fleech::ResetTarget()
{
    if (current_target_object_id_551840 == mBaseGameObjectId)
    {
        current_target_object_id_551840 = -1;
    }
}

s16 Fleech::GotNoTarget()
{
    return current_target_object_id_551840 == -1 && !mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit7_Electrocuted);
}

void Fleech::SetTarget()
{
    current_target_object_id_551840 = mBaseGameObjectId;
}

void Fleech::TongueHangingFromWall(s16 target_x, s16 target_y)
{
    mTongueFlags.Set(TongueFlags::eRender);
    mTongueState = 2;
    mTongueDestinationY = target_y;
    mTongueDestinationX = target_x;
    field_188 = 0;
}

void Fleech::TongueUpdate()
{
    auto pTarget = static_cast<BaseAliveGameObject*>(sObjectIds.Find_Impl(field_11C_obj_id));
    if (!gMap.Is_Point_In_Current_Camera(mCurrentLevel, mCurrentPath, mXPos, mYPos, 0))
    {
        mTongueFlags.Clear(TongueFlags::eRender);
    }

    switch (mTongueState)
    {
        case 1:
            mTongueFlags.Clear(TongueFlags::eTongueActive);
            mTongueFlags.Clear(TongueFlags::eRender);
            return;

        case 2:
        case 4:
            mTongueFlags.Set(TongueFlags::eRender);
            return;

        case 3:
            mTongueFlags.Set(TongueFlags::eRender);
            switch (mTongueSubState++)
            {
                case 0:
                    mTongueDestinationX = field_160_hoistX;
                    mTongueDestinationY = field_162_hoistY;
                    Sound(FleechSound::LedgeHoist_11);
                    break;

                case 1:
                    field_188 = 6;
                    break;

                case 2:
                    field_188 = -6;
                    break;

                case 3:
                    field_188 = 3;
                    break;

                case 4:
                    field_188 = -3;
                    break;

                case 5:
                    field_188 = 0;
                    mTongueState = 4;
                    mTongueFlags.Clear(TongueFlags::eTongueActive);
                    break;
                default:
                    break;
            }
            return;

        case 5:
        case 10:
            mTongueState = 1;
            return;

        case 6:
            if (pTarget)
            {
                const PSX_RECT bRect = pTarget->VGetBoundingRect();

                mTongueFlags.Set(TongueFlags::eRender);
                mEnemyXPos = FP_GetExponent(pTarget->mXPos);
                mEnemyYPos = (bRect.y + bRect.h) >> 1;
                mTongueDestinationY = (bRect.y + bRect.h) >> 1;
                mTongueDestinationX = mEnemyXPos;

                const FP v12 = (FP_FromInteger(mSpriteScale >= FP_FromInteger(1) ? 20 : 10) * FP_FromInteger(7));
                if (FP_FromInteger(Math_Distance(
                        FP_GetExponent(mXPos),
                        FP_GetExponent(mYPos),
                        mTongueDestinationX, mTongueDestinationY))
                    <= v12)
                {
                    switch (mTongueSubState++)
                    {
                        case 0:
                        {
                            Sound(FleechSound::LickTarget_10);
                            relive_new Blood(
                                FP_FromInteger(mEnemyXPos),
                                FP_FromInteger(mEnemyYPos),
                                mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) != 0 ? FP_FromInteger(2) : FP_FromInteger(-2),
                                FP_FromInteger(1),
                                mSpriteScale, 20);
                            break;
                        }

                        case 1:
                            field_188 = 9;
                            break;

                        case 2:
                            field_188 = -6;
                            ResetTarget();
                            break;

                        case 3:
                            field_188 = 5;
                            break;

                        case 4:
                            field_188 = -3;
                            break;

                        case 5:
                            mTongueState = 9;
                            field_188 = 0;
                            if (pTarget->mHealth > FP_FromInteger(0))
                            {
                                pTarget->VTakeDamage(this);
                                if (pTarget->mHealth <= FP_FromInteger(0))
                                {
                                    mTongueState = 7;
                                    mTongueSubState = 0;
                                    Sound(FleechSound::Devour_8);
                                }
                            }
                            break;
                        default:
                            break;
                    }
                }
                else
                {
                    mTongueFlags.Clear(TongueFlags::eTongueActive);
                    mTongueState = 1;
                }
            }
            else
            {
                sub_42B8C0();
            }
            return;

        case 7:
            if (pTarget)
            {
                const PSX_RECT bRect = pTarget->VGetBoundingRect();

                switch (mTongueSubState++)
                {
                    case 4:
                        mNextMotion = eFleechMotions::Motion_18_Consume;
                        [[fallthrough]];
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                    case 5:
                        if (mTongueSubState == 5 && pTarget->Type() == ReliveTypes::eScrab)
                        {
                            pTarget->mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
                        }
                        pTarget->mXPos -= (pTarget->mXPos - mXPos) * FP_FromDouble(0.25);
                        pTarget->mYPos -= (pTarget->mYPos - mYPos) * FP_FromDouble(0.25);
                        break;

                    case 6:
                        mTongueFlags.Clear(TongueFlags::eRender);
                        mTongueState = 8;
                        pTarget->mAnim.mFlags.Clear(AnimFlags::eBit3_Render);
                        pTarget->mXPos = mXPos;
                        pTarget->mYPos = mYPos;
                        if (IsActiveHero(pTarget))
                        {
                            sActiveHero->FleechDeath_459350();
                        }
                        break;

                    default:
                        break;
                }

                mEnemyXPos = FP_GetExponent(pTarget->mXPos);
                mTongueDestinationX = mEnemyXPos;
                mEnemyYPos = (bRect.y + bRect.h) >> 1;
                mTongueDestinationY = (bRect.y + bRect.h) >> 1;
            }
            else
            {
                sub_42B8C0();
            }
            return;

        case 8:
            mTongueFlags.Clear(TongueFlags::eTongueActive);
            mTongueState = 1;
            return;

        case 9:
            if (pTarget)
            {
                const PSX_RECT bRect = pTarget->VGetBoundingRect();
                mEnemyXPos = FP_GetExponent((mXPos + pTarget->mXPos) * FP_FromDouble(0.5));
                mEnemyYPos = (bRect.y + bRect.h) >> 1;
                mTongueDestinationX = FP_GetExponent((mXPos + pTarget->mXPos) * FP_FromDouble(0.5));
                mTongueDestinationY = (bRect.y + bRect.h) >> 1;
                mTongueFlags.Clear(TongueFlags::eTongueActive);
                mTongueState = 1;
            }
            else
            {
                sub_42B8C0();
            }
            break;

        default:
            break;
    }
}

void Fleech::ToIdle()
{
    MapFollowMe(TRUE);
    field_138_velx_factor = FP_FromInteger(0);
    mVelX = FP_FromInteger(0);
    mVelY = FP_FromInteger(0);
    mCurrentMotion = eFleechMotions::Motion_3_Idle;
    mNextMotion = -1;
    field_134_unused = 60 * sRandomBytes_546744[sFleechRandomIdx_5BC20C++] / 256 + sGnFrame + 120;
}

const SfxDefinition getSfxDef(FleechSound effectId)
{
    return stru_5518E0[static_cast<s32>(effectId)];
}

s32 Fleech::Sound(FleechSound soundId)
{
    SfxDefinition effectDef = getSfxDef(soundId);
    s16 defaultSndIdxVol = effectDef.field_3_default_volume;
    if (soundId == FleechSound::CrawlRNG1_14)
    {
        const s32 rndIdx = Math_RandomRange(14, 16);
        effectDef = getSfxDef(static_cast<FleechSound>(rndIdx));
        defaultSndIdxVol = effectDef.field_3_default_volume + Math_RandomRange(-10, 10);
    }

    if (mSpriteScale == FP_FromDouble(0.5))
    {
        defaultSndIdxVol = 2 * defaultSndIdxVol / 3;
    }

    s16 volumeLeft = 0;
    s16 volumeRight = defaultSndIdxVol;
    const CameraPos direction = gMap.GetDirection(
        mCurrentLevel,
        mCurrentPath,
        mXPos,
        mYPos);

    PSX_RECT pRect = {};
    gMap.Get_Camera_World_Rect(direction, &pRect);
    switch (direction)
    {
        case CameraPos::eCamCurrent_0:
            volumeLeft = volumeRight;
            break;
        case CameraPos::eCamTop_1:
        case CameraPos::eCamBottom_2:
        {
            volumeLeft = FP_GetExponent(FP_FromInteger(defaultSndIdxVol * 2) / FP_FromInteger(3));
            volumeRight = volumeLeft;
        }
        break;
        case CameraPos::eCamLeft_3:
        {
            const FP percentHowFar = (FP_FromInteger(pRect.w) - mXPos) / FP_FromInteger(368);
            volumeLeft = volumeRight - FP_GetExponent(percentHowFar * FP_FromInteger(volumeRight - (volumeRight / 3)));
            volumeRight = volumeRight - FP_GetExponent(percentHowFar * FP_FromInteger(volumeRight));
        }
        break;
        case CameraPos::eCamRight_4:
        {
            const FP percentHowFar = (mXPos - FP_FromInteger(pRect.x)) / FP_FromInteger(368);
            volumeLeft = volumeRight - FP_GetExponent(percentHowFar * FP_FromInteger(volumeRight));
            volumeRight = volumeRight - FP_GetExponent(percentHowFar * FP_FromInteger(volumeRight - (volumeRight / 3)));
        }
        break;
        default:
            return 0;
    }

    return SFX_SfxDefinition_Play_Stereo(
        &effectDef,
        volumeLeft,
        volumeRight,
        effectDef.field_4_pitch_min,
        effectDef.field_6_pitch_max);
}

u8** Fleech::ResBlockForMotion(s32 /*motion*/)
{
    return field_10_resources_array.ItemAt(0);
}

s16 Fleech::CanMove()
{
    if (mNextMotion == eFleechMotions::Motion_6_Knockback)
    {
        mCurrentMotion = eFleechMotions::Motion_6_Knockback;
        mNextMotion = -1;
        return 1;
    }

    if (mNextMotion != eFleechMotions::Motion_4_Crawl)
    {
        return 0;
    }

    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mVelX = -(ScaleToGridSize(mSpriteScale) / FP_FromInteger(7));
    }
    else
    {
        mVelX = (ScaleToGridSize(mSpriteScale) / FP_FromInteger(7));
    }

    const FP yDist = FP_FromInteger(mSpriteScale >= FP_FromInteger(1) ? 10 : 5);
    const FP xDist = ScaleToGridSize(mSpriteScale) * FP_FromInteger(mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) ? -1 : 1); // TODO: Correct way around ?
    if (!WallHit(yDist, xDist) && !HandleEnemyStopperOrSlamDoor(1))
    {
        mCurrentMotion = eFleechMotions::Motion_4_Crawl;
        mNextMotion = -1;
        return 1;
    }

    ToIdle();
    return 0;
}

s16 Fleech::HandleEnemyStopperOrSlamDoor(s32 velX)
{
    const FP kGridSize = ScaleToGridSize(mSpriteScale);
    FP nextXPos = {};
    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        nextXPos = mXPos - (kGridSize * FP_FromInteger(velX));
    }
    else
    {
        nextXPos = (kGridSize * FP_FromInteger(velX)) + mXPos;
    }

    FP stopperXPos = {};
    if (mXPos <= nextXPos)
    {
        stopperXPos = nextXPos;
    }
    else
    {
        stopperXPos = mXPos;
    }

    auto pStopper = static_cast<Path_EnemyStopper*>(sPathInfo->TLV_Get_At_4DB4B0(
        FP_GetExponent(stopperXPos),
        FP_GetExponent(mYPos),
        FP_GetExponent(stopperXPos),
        FP_GetExponent(mYPos),
        TlvTypes::EnemyStopper_47));

    if (pStopper && (pStopper->mStopDirection == (nextXPos >= mXPos ? Path_EnemyStopper::StopDirection::Right_1 : Path_EnemyStopper::StopDirection::Left_0)) && SwitchStates_Get(pStopper->mSwitchId))
    {
        return 1;
    }

    FP slamDoorXPos = mXPos;
    if (mXPos <= nextXPos)
    {
        slamDoorXPos = nextXPos;
    }

    if (mXPos > nextXPos)
    {
        slamDoorXPos = nextXPos;
    }

    auto pSlamDoor = static_cast<Path_SlamDoor*>(sPathInfo->TLV_Get_At_4DB4B0(
        FP_GetExponent(slamDoorXPos),
        FP_GetExponent(mYPos),
        FP_GetExponent(slamDoorXPos),
        FP_GetExponent(mYPos),
        TlvTypes::SlamDoor_85));

    return (pSlamDoor && ((pSlamDoor->mStartClosed == Choice_short::eYes_1 && !SwitchStates_Get(pSlamDoor->mSwitchId)) || (pSlamDoor->mStartClosed == Choice_short::eNo_0 && SwitchStates_Get(pSlamDoor->mSwitchId))));
}

s32 Fleech::UpdateWakeUpSwitchValue()
{
    const s16 curSwitchValue = static_cast<s16>(SwitchStates_Get(field_144_wake_up_switch_id));
    const s16 wakeUpValue = field_148_wake_up_switch_value;

    if (curSwitchValue == wakeUpValue)
    {
        return 0;
    }

    if (curSwitchValue)
    {
        field_148_wake_up_switch_value = curSwitchValue;
        return (curSwitchValue - wakeUpValue) ? 1 : 0;
    }
    else
    {
        field_148_wake_up_switch_value = 0;
        return 1;
    }
}

s16 Fleech::VTakeDamage(BaseGameObject* pFrom)
{
    if (mHealth <= FP_FromInteger(0))
    {
        return 0;
    }

    sub_42B8C0();
    ResetTarget();

    switch (pFrom->Type())
    {
        case ReliveTypes::eBullet:
        case ReliveTypes::eDrill:
        case ReliveTypes::eBaseBomb:
        case ReliveTypes::eExplosion:
        case ReliveTypes::eSlig:
        {
            Sound(FleechSound::Scared_7);
            mHealth = FP_FromInteger(0);

            relive_new Gibs(GibType::Fleech_10, mXPos, mYPos, mVelX, mVelY, mSpriteScale, 0);

            const PSX_RECT bRect = VGetBoundingRect();
            relive_new Blood(
                FP_FromInteger((bRect.x + bRect.w) / 2),
                FP_FromInteger((bRect.y + bRect.h) / 2),
                FP_FromInteger(0),
                FP_FromInteger(0),
                mSpriteScale, 50);

            mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        }
        break;


        case ReliveTypes::eRockSpawner:
            Sound(FleechSound::Scared_7);
            mHealth = FP_FromInteger(0);
            field_124_brain_state = eFleechBrains::eBrain_3_Death;
            mNextMotion = -1;
            field_12C_shrivel_timer = sGnFrame + 127;
            mCurrentMotion = eFleechMotions::Motion_3_Idle;
            SetAnim();
            mAnim.mFlags.Set(AnimFlags::eBit2_Animate);
            break;

        case ReliveTypes::eParamite:
            Sound(FleechSound::Dismember_13);
            [[fallthrough]];

        case ReliveTypes::eScrab:
        {
            relive_new Gibs(GibType::Fleech_10, mXPos, mYPos, mVelX, mVelY, mSpriteScale, 0);

            if (static_cast<BaseAliveGameObject*>(pFrom)->mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
            {
                relive_new Blood(mXPos, mYPos - FP_FromInteger(8), -FP_FromInteger(5), -FP_FromInteger(5), mSpriteScale, 50);
            }
            else
            {
                relive_new Blood(mXPos, mYPos - FP_FromInteger(8), FP_FromInteger(5), -FP_FromInteger(5), mSpriteScale, 50);
            }

            if (!mFleechFlags.Get(FleechFlags::eScaredSound))
            {
                mFleechFlags.Set(FleechFlags::eScaredSound);
                Sound(FleechSound::Scared_7);
            }

            mHealth = FP_FromInteger(0);
            field_124_brain_state = eFleechBrains::eBrain_3_Death;
            mCurrentMotion = eFleechMotions::Motion_3_Idle;
            field_12C_shrivel_timer = sGnFrame + 127;
            mNextMotion = -1;
            SetAnim();
            mAnim.mFlags.Set(AnimFlags::eBit2_Animate);
            mFleechFlags.Set(FleechFlags::eShrivelDeath);
            mBaseGameObjectFlags.Set(BaseGameObject::eDead);
            sFleechCount_5BC20E--;
        }
        break;

        case ReliveTypes::eElectrocute:
            mBaseGameObjectFlags.Set(BaseGameObject::eDead);
            mHealth = FP_FromInteger(0);
            field_124_brain_state = eFleechBrains::eBrain_3_Death;
            break;

        default:
            Sound(FleechSound::Scared_7);
            mBaseAliveGameObjectFlags.Set(Flags_114::e114_Bit7_Electrocuted);
            sub_42B8C0();
            break;
    }
    return 1;
}

void Fleech::VOnTrapDoorOpen()
{
    auto pPlatform = static_cast<PlatformBase*>(sObjectIds.Find_Impl(BaseAliveGameObject_PlatformId));
    if (pPlatform)
    {
        pPlatform->VRemove(this);
        BaseAliveGameObject_PlatformId = -1;
    }
}

void Fleech::SetTongueState1()
{
    mTongueState = 1;
}

void Fleech::IncreaseAnger()
{
    if (gMap.Is_Point_In_Current_Camera(mCurrentLevel, mCurrentPath, mXPos, mYPos, 0))
    {
        IBaseAnimatedWithPhysicsGameObject* pEvent = IsEventInRange(kEventSpeaking, mXPos, mYPos, AsEventScale(mScale));

        if (!pEvent)
        {
            pEvent = IsEventInRange(kEventAlarm, mXPos, mYPos, AsEventScale(mScale));
        }

        if (!pEvent)
        {
            pEvent = IsEventInRange(kEventLoudNoise, mXPos, mYPos, AsEventScale(mScale));
        }

        if (pEvent)
        {
            if ((!IsActiveHero(pEvent) || !sActiveHero->mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit8_bInvisible)) && gMap.Is_Point_In_Current_Camera(mCurrentLevel, mCurrentPath, pEvent->mXPos, pEvent->mYPos, 0))
            {
                field_13E_current_anger += field_142_attack_anger_increaser;
                if (VOnSameYLevel(static_cast<BaseAnimatedWithPhysicsGameObject*>(pEvent)))
                {
                    if (pEvent->Type() == ReliveTypes::eScrab || pEvent->Type() == ReliveTypes::eParamite)
                    {
                        field_14E_ScrabParamiteEventXPos = FP_GetExponent(pEvent->mXPos);
                    }
                    else
                    {
                        field_14C_EventXPos = FP_GetExponent(pEvent->mXPos);
                    }
                }
            }
        }

        pEvent = IsEventInRange(kEventNoise, mXPos, mYPos, AsEventScale(mScale));
        if (pEvent)
        {
            if (VIsObjNearby(ScaleToGridSize(mSpriteScale) * FP_FromInteger(6),static_cast<BaseAnimatedWithPhysicsGameObject*>(pEvent)))
            {
                if ((!IsActiveHero(pEvent) || !sActiveHero->mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit8_bInvisible)) && gMap.Is_Point_In_Current_Camera(mCurrentLevel, mCurrentPath, pEvent->mXPos, pEvent->mYPos, 0))
                {
                    field_13E_current_anger += field_140_max_anger;
                }
            }
        }
    }
}

s16 Fleech::AngerFleech(BaseAliveGameObject* pObj)
{
    if (!pObj || (IsActiveHero(pObj) && sActiveHero->mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit8_bInvisible)))
    {
        return FALSE;
    }

    if (FP_Abs(pObj->mXPos - mXPos) >= ScaleToGridSize(mSpriteScale) * FP_FromInteger(10) ||
        FP_Abs(pObj->mYPos - mYPos) >= ScaleToGridSize(mSpriteScale) * FP_FromInteger(1) ||
        pObj->mSpriteScale != mSpriteScale)
    {
        return FALSE;
    }

    return TRUE;
}

s32 Fleech::TongueActive()
{
    return mTongueFlags.Get(TongueFlags::eTongueActive);
}

void Fleech::PullTargetIn()
{
    auto pTarget = static_cast<BaseAliveGameObject*>(sObjectIds.Find_Impl(field_11C_obj_id));
    if (pTarget)
    {
        mTongueFlags.Set(TongueFlags::eTongueActive);
        mTongueFlags.Set(TongueFlags::eRender);
        mTongueState = 6;
        mTongueSubState = 0;

        const PSX_RECT bRect = pTarget->VGetBoundingRect();

        mEnemyXPos = FP_GetExponent(pTarget->mXPos);
        mEnemyYPos = (bRect.y + bRect.h) / 2;
        mTongueDestinationX = FP_GetExponent(((FP_FromInteger(mEnemyXPos) + mXPos) / FP_FromInteger(2)));
        field_188 = 0;
        mTongueDestinationY = FP_GetExponent(((FP_FromInteger(mEnemyYPos) + mYPos) / FP_FromInteger(2)));
    }
}

void Fleech::sub_42B8C0()
{
    ResetTarget();

    if (mTongueState > 1)
    {
        mTongueState = 10;
        mTongueDestinationX = FP_GetExponent(((FP_FromInteger(mTongueDestinationX)) + mXPos) / FP_FromInteger(2));
        field_188 = 0;
        mTongueDestinationY = FP_GetExponent(((FP_FromInteger(mTongueDestinationY)) + mYPos) / FP_FromInteger(2));
    }
    else
    {
        mTongueFlags.Clear(TongueFlags::eRender);
        mTongueState = 1;
    }
}

void Fleech::sub_42BA10()
{
    mTongueFlags.Set(TongueFlags::eTongueActive);
    mTongueFlags.Set(TongueFlags::eRender);
    mTongueState = 3;
    mTongueSubState = 0;
    mTongueDestinationX = FP_GetExponent(((FP_FromInteger(field_160_hoistX)) + mXPos) / FP_FromInteger(2));
    field_188 = 0;
    mTongueDestinationY = FP_GetExponent(((FP_FromInteger(field_162_hoistY)) + mYPos) / FP_FromInteger(2));
}

void Fleech::SetTongueState5()
{
    mTongueState = 5;
}

BaseAliveGameObject* Fleech::FindMudOrAbe()
{
    BaseAliveGameObject* pRet = nullptr;
    FP lastDist = FP_FromInteger(gPsxDisplay.mWidth);
    for (s32 i = 0; i < gBaseAliveGameObjects->Size(); i++)
    {
        auto pObj = gBaseAliveGameObjects->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if ((pObj->Type() == ReliveTypes::eMudokon || pObj->Type() == ReliveTypes::eAbe) && pObj->mScale == mScale && pObj->mHealth > FP_FromInteger(0))
        {
            const FP dist = FP_FromInteger(
                Math_Distance(
                    FP_GetExponent(pObj->mXPos),
                    FP_GetExponent(pObj->mYPos),
                    FP_GetExponent(mXPos),
                    FP_GetExponent(mYPos)));

            if (dist < lastDist && FP_GetExponent(mXPos) / 375 == (FP_GetExponent(pObj->mXPos) / 375) && FP_GetExponent(mYPos) / 260 == (FP_GetExponent(pObj->mYPos) / 260))
            {
                lastDist = dist;
                pRet = pObj;
            }
        }
    }
    return pRet;
}

void Fleech::MoveAlongFloor()
{
    auto pPlatform = static_cast<PlatformBase*>(sObjectIds.Find_Impl(BaseAliveGameObject_PlatformId));

    const FP prev_xpos = mXPos;
    const FP prev_ypos = mYPos;

    if (BaseAliveGameObjectCollisionLine)
    {
        PathLine* pOldLine = BaseAliveGameObjectCollisionLine;
        BaseAliveGameObjectCollisionLine = BaseAliveGameObjectCollisionLine->MoveOnLine(&mXPos, &mYPos, mVelX);
        if (BaseAliveGameObjectCollisionLine && (mScale == Scale::Fg ? kFgFloor : kBgFloor).Mask() == CollisionMask(BaseAliveGameObjectCollisionLine->mLineType).Mask())
        {
            if (pPlatform)
            {
                if (BaseAliveGameObjectCollisionLine->mLineType != eLineTypes::eDynamicCollision_32 && BaseAliveGameObjectCollisionLine->mLineType != eLineTypes::eBackgroundDynamicCollision_36)
                {
                    pPlatform->VRemove(this);
                    BaseAliveGameObject_PlatformId = -1;
                }
            }
            else if (BaseAliveGameObjectCollisionLine->mLineType == eLineTypes::eDynamicCollision_32 || BaseAliveGameObjectCollisionLine->mLineType == eLineTypes::eBackgroundDynamicCollision_36)
            {
                const PSX_RECT bRect = VGetBoundingRect();
                const PSX_Point xy = {bRect.x, static_cast<s16>(bRect.y + 5)};
                const PSX_Point wh = {bRect.w, static_cast<s16>(bRect.h + 5)};
                VOnCollisionWith(xy, wh, ObjList_5C1B78, 1, (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection);
            }
        }
        else if (field_124_brain_state != eFleechBrains::eBrain_0_Patrol)
        {
            VOnTrapDoorOpen();
            field_138_velx_factor = FP_FromInteger(0);
            BaseAliveGameObjectLastLineYPos = mYPos;
            mXPos = prev_xpos + mVelX;
            mCurrentMotion = eFleechMotions::Motion_9_Fall;
        }
        else
        {
            mXPos = prev_xpos;
            mYPos = prev_ypos;
            BaseAliveGameObjectCollisionLine = pOldLine;
            mCurrentMotion = eFleechMotions::Motion_6_Knockback;
        }
    }
    else
    {
        BaseAliveGameObjectLastLineYPos = prev_ypos;
        field_138_velx_factor = FP_FromInteger(0);
        mCurrentMotion = eFleechMotions::Motion_9_Fall;
    }
}

// attack radius?
s16 Fleech::IsNear(BaseAliveGameObject* pObj)
{
    if (pObj && mSpriteScale == pObj->mSpriteScale &&
        FP_GetExponent(FP_Abs(mXPos - pObj->mXPos)) <= 750 &&
        FP_GetExponent(FP_Abs(mYPos - pObj->mYPos)) <= 260)
    {
        return TRUE;
    }
    return FALSE;
}

void Fleech::VOnThrowableHit(BaseGameObject* /*pFrom*/)
{
    field_13E_current_anger += field_142_attack_anger_increaser;
}

bool Fleech::Collision(s16 alwaysOne)
{
    const FP kGridSize = ScaleToGridSize(mSpriteScale);
    const FP quaterScaled = (kGridSize * FP_FromDouble(0.25));

    FP x2 = {};
    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        x2 = mXPos - (quaterScaled * FP_FromInteger(alwaysOne >= 0 ? 1 : -1));
    }
    else
    {
        x2 = (kGridSize * FP_FromInteger(alwaysOne)) + mXPos;
    }

    FP x1 = {};
    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        x1 = mXPos - (kGridSize * FP_FromInteger(alwaysOne));
    }
    else
    {
        x1 = (quaterScaled * FP_FromInteger(alwaysOne >= 0 ? 1 : -1)) + mXPos;
    }

    const FP y2 = mYPos + FP_FromInteger(2);
    const FP y1 = mYPos - FP_FromInteger(2);

    PathLine* pLine = nullptr;
    FP hitX = {};
    FP hitY = {};
    return sCollisions->Raycast(x1, y1, x2, y2, &pLine, &hitX, &hitY, mScale == Scale::Fg ? kFgFloor : kBgFloor) == 0;
}

Path_Hoist* Fleech::TryGetHoist(s32 xDistance, s16 bIgnoreDirection)
{
    if (mCurrentMotion == eFleechMotions::Motion_9_Fall)
    {
        return nullptr;
    }

    const FP yAmount = FP_FromInteger(mSpriteScale < FP_FromInteger(1) ? 10 : 20);
    const FP y1 = mYPos - yAmount;
    const FP y2 = y1 - (yAmount * FP_FromInteger(1));

    const FP xSnapped = FP_FromInteger(SnapToXGrid(mSpriteScale, FP_GetExponent(mXPos)));
    FP xCheck = {};
    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        xCheck = xSnapped - (ScaleToGridSize(mSpriteScale) * FP_FromInteger(xDistance));
    }
    else
    {
        xCheck = (ScaleToGridSize(mSpriteScale) * FP_FromInteger(xDistance)) + xSnapped;
    }

    auto pHoist = static_cast<Path_Hoist*>(sPathInfo->TLV_Get_At_4DB4B0(
        FP_GetExponent(std::min(xCheck, mXPos)),
        FP_GetExponent(y2),
        FP_GetExponent(std::max(xCheck, mXPos)),
        FP_GetExponent(y1),
        TlvTypes::Hoist_2));

    if (!pHoist)
    {
        return nullptr;
    }

    if (WallHit(
            FP_FromInteger(mSpriteScale < FP_FromInteger(1) ? 5 : 10),
            FP_FromInteger(pHoist->mTopLeft.x + (mSpriteScale < FP_FromInteger(1) ? 6 : 12)) - mXPos))
    {
        return nullptr;
    }

    if (HandleEnemyStopperOrSlamDoor(xDistance))
    {
        return nullptr;
    }

    if (pHoist->field_16_scale != (mSpriteScale < FP_FromInteger(1) ? Scale_short::eHalf_1 : Scale_short::eFull_0) || mYPos - FP_FromInteger(pHoist->mTopLeft.y) > FP_FromInteger(mSpriteScale >= FP_FromInteger(1) ? 20 : 10) * FP_FromDouble(5.5))
    {
        return nullptr;
    }

    if (bIgnoreDirection)
    {
        return pHoist;
    }

    if (pHoist->mGrabDirection == (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) ? Path_Hoist::GrabDirection::eFacingLeft : Path_Hoist::GrabDirection::eFacingRight) || pHoist->mGrabDirection == Path_Hoist::GrabDirection::eFacingAnyDirection)
    {
        return pHoist;
    }

    return nullptr;
}

void Fleech::VOnFrame(s16* pData)
{
    FP xpos = {};
    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
    {
        xpos = mXPos - (mSpriteScale * FP_FromInteger(pData[0]));
    }
    else
    {
        xpos = (mSpriteScale * FP_FromInteger(pData[0])) + mXPos;
    }

    mTongueOriginX = FP_GetExponent(xpos) + mXOffset;
    mTongueOriginY = FP_GetExponent((mSpriteScale * FP_FromInteger(pData[1])) + mYPos);
}

const s8 byte_551984[] = {
    0,
    0,
    5,
    0,
    5,
    5,
    5,
    5,
    5,
    5,
    5,
    5,
    0,
    0,
    0,
    0};

enum Brain_0_Patrol
{
    State_0_Init = 0,
    eSleeping_1 = 1,
    State_2 = 2,
    eGoingBackToSleep = 3,
    eAlerted_4 = 4,
    eHearingScrabOrParamite_5 = 5,
    State_6 = 6,
    State_7 = 7,
    eAlertedByAbe_8 = 8,
    State_9 = 9,
    State_10 = 10,
};

s16 Fleech::Brain_0_Patrol()
{
    auto pTarget = static_cast<BaseAliveGameObject*>(sObjectIds.Find_Impl(field_11C_obj_id));
    if (!pTarget || pTarget->mBaseGameObjectFlags.Get(BaseGameObject::eDead) || pTarget->mHealth <= FP_FromInteger(0) || pTarget->mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit8_bInvisible))
    {
        field_11C_obj_id = -1;
        pTarget = nullptr;
    }

    if (gMap.Is_Point_In_Current_Camera(mCurrentLevel, mCurrentPath, mXPos, mYPos, 0))
    {
        MusicController::static_PlayMusic(static_cast<MusicController::MusicTypes>(byte_551984[field_126_brain_sub_state]), this, 0, 0);
    }
    else
    {
        MusicController::static_PlayMusic(MusicController::MusicTypes::eNone_0, this, 0, 0);
    }

    switch (field_126_brain_sub_state)
    {
        case Brain_0_Patrol::State_0_Init:
            return Brain_Patrol_State_0();

        case Brain_0_Patrol::eSleeping_1:
            return Brain_Patrol_State_1();

        case Brain_0_Patrol::State_2:
            return Brain_Patrol_State_2();

        case Brain_0_Patrol::eGoingBackToSleep:
            return Brain_Patrol_State_3();

        case Brain_0_Patrol::eAlerted_4:
            return Brain_Patrol_State_4(pTarget);

        case Brain_0_Patrol::eHearingScrabOrParamite_5:
            return Brain_Patrol_State_5();

        case Brain_0_Patrol::State_6:
            return Brain_Patrol_State_6();

        case Brain_0_Patrol::State_7:
            return Brain_Patrol_State_7();

        case Brain_0_Patrol::eAlertedByAbe_8:
            return Brain_Patrol_State_8(pTarget);

        case Brain_0_Patrol::State_9:
            return Brain_Patrol_State_9();

        case Brain_0_Patrol::State_10:
            return Brain_Patrol_State_10();

        default:
            return field_126_brain_sub_state;
    }
}

s16 Fleech::Brain_Patrol_State_0()
{
    field_156_rnd_crawl = Fleech_NextRandom() & 0x3F;
    field_15A_chase_timer = 0;
    field_152_old_xpos = FP_GetExponent(mXPos);
    field_14C_EventXPos = -1;
    field_14E_ScrabParamiteEventXPos = -1;

    if (field_13E_current_anger > field_140_max_anger)
    {
        return Brain_0_Patrol::eAlerted_4;
    }

    if (mCurrentMotion == eFleechMotions::Motion_0_Sleeping)
    {
        return Brain_0_Patrol::eSleeping_1;
    }

    if (mCurrentMotion != eFleechMotions::Motion_17_SleepingWithTongue && !mFleechFlags.Get(FleechFlags::eGoesToSleep))
    {
        return Brain_0_Patrol::eAlerted_4;
    }

    if (mCurrentMotion == eFleechMotions::Motion_0_Sleeping || mCurrentMotion == eFleechMotions::Motion_17_SleepingWithTongue)
    {
        return Brain_0_Patrol::eSleeping_1;
    }

    return Brain_0_Patrol::eGoingBackToSleep;
}

s16 Fleech::Brain_Patrol_State_1()
{
    if (!SwitchStates_Get(field_14A_can_wake_up_switch_id))
    {
        return field_126_brain_sub_state;
    }

    if (!(static_cast<s32>(sGnFrame) % 16))
    {
        if (field_13E_current_anger > 0)
        {
            field_13E_current_anger--;
        }
    }

    IncreaseAnger();

    if (UpdateWakeUpSwitchValue())
    {
        const s16 v11 = (field_142_attack_anger_increaser - field_140_max_anger) / 2;
        if (field_13E_current_anger < v11 + field_140_max_anger)
        {
            field_13E_current_anger = field_140_max_anger + v11;
        }
    }

    if (!IsScrabOrParamiteNear(ScaleToGridSize(mSpriteScale) * FP_FromInteger(8)))
    {
        if (field_13E_current_anger <= field_140_max_anger)
        {
            return field_126_brain_sub_state;
        }

        if (mCurrentMotion == eFleechMotions::Motion_17_SleepingWithTongue)
        {
            mNextMotion = eFleechMotions::Motion_9_Fall;
            BaseAliveGameObjectLastLineYPos = mYPos;
            return Brain_0_Patrol::eAlerted_4;
        }
    }
    else
    {
        BaseGameObject* pDangerObj = sObjectIds.Find_Impl(field_170_danger_obj);
        if (pDangerObj && pDangerObj->Type() != ReliveTypes::eParamite)
        {
            if (mCurrentMotion == eFleechMotions::Motion_17_SleepingWithTongue)
            {
                mNextMotion = eFleechMotions::Motion_9_Fall;
                BaseAliveGameObjectLastLineYPos = mYPos;
                return Brain_0_Patrol::eAlerted_4;
            }
        }
        else
        {
            field_170_danger_obj = -1;
            if (field_13E_current_anger <= field_140_max_anger)
            {
                return field_126_brain_sub_state;
            }

            if (mCurrentMotion == eFleechMotions::Motion_17_SleepingWithTongue)
            {
                mNextMotion = eFleechMotions::Motion_9_Fall;
                BaseAliveGameObjectLastLineYPos = mYPos;
                return Brain_0_Patrol::eAlerted_4;
            }
        }
    }
    mNextMotion = eFleechMotions::Motion_1_WakingUp;
    return Brain_0_Patrol::State_2;
}

s16 Fleech::Brain_Patrol_State_2()
{
    if (mCurrentMotion != eFleechMotions::Motion_1_WakingUp)
    {
        return field_126_brain_sub_state;
    }

    if (BaseAliveGameObjectCollisionLine)
    {
        mNextMotion = eFleechMotions::Motion_5_PatrolCry;
    }
    else
    {
        mNextMotion = eFleechMotions::Motion_9_Fall;
        BaseAliveGameObjectLastLineYPos = mYPos;
    }
    return Brain_0_Patrol::eAlerted_4;
}

s16 Fleech::Brain_Patrol_State_3()
{
    if (mCurrentMotion == eFleechMotions::Motion_3_Idle)
    {
        mNextMotion = eFleechMotions::Motion_2_Unknown;
    }

    if (mCurrentMotion != eFleechMotions::Motion_2_Unknown)
    {
        return field_126_brain_sub_state;
    }

    field_13E_current_anger = 0;
    mNextMotion = eFleechMotions::Motion_0_Sleeping;
    return Brain_0_Patrol::eSleeping_1;
}

s16 Fleech::Brain_Patrol_State_4(BaseAliveGameObject* pTarget)
{
    if (field_11C_obj_id == -1)
    {
        pTarget = FindMudOrAbe();
        if (pTarget)
        {
            field_11C_obj_id = pTarget->mBaseGameObjectId;
        }
    }

    if (!(static_cast<s32>(sGnFrame) % 32))
    {
        if (field_13E_current_anger > 0)
        {
            field_13E_current_anger--;
        }
    }

    if (IsScrabOrParamiteNear(ScaleToGridSize(mSpriteScale) * FP_FromInteger(8)))
    {
        auto pDangerObj = static_cast<BaseAliveGameObject*>(sObjectIds.Find_Impl(field_170_danger_obj));
        if (pDangerObj == sControlledCharacter)
        {
            field_124_brain_state = eFleechBrains::eBrain_2_Scared;
            return 0;
        }

        if (VIsObjNearby(FP_FromInteger(2) * ScaleToGridSize(mSpriteScale), pDangerObj))
        {
            const s16 v27 = (field_142_attack_anger_increaser - field_140_max_anger) / 2;
            if (field_13E_current_anger < v27 + field_140_max_anger)
            {
                field_13E_current_anger = field_140_max_anger + v27;
            }
            field_14E_ScrabParamiteEventXPos = FP_GetExponent(pDangerObj->mXPos); // TODO: abs ?
        }
    }

    // TODO: Check OFSUB branches
    if (field_14E_ScrabParamiteEventXPos >= 0)
    {
        if ((FP_FromInteger(field_14E_ScrabParamiteEventXPos) > mXPos && !mAnim.mFlags.Get(AnimFlags::eBit5_FlipX)) || (FP_FromInteger(field_14E_ScrabParamiteEventXPos) < mXPos && mAnim.mFlags.Get(AnimFlags::eBit5_FlipX)))
        {
            if (mCurrentMotion == eFleechMotions::Motion_4_Crawl)
            {
                mCurrentMotion = eFleechMotions::Motion_7_StopCrawling;
            }
            else if (mCurrentMotion == eFleechMotions::Motion_3_Idle)
            {
                mCurrentMotion = eFleechMotions::Motion_6_Knockback;
            }
        }
        return Brain_0_Patrol::eHearingScrabOrParamite_5;
    }

    IncreaseAnger();

    if (AngerFleech(pTarget))
    {
        field_13E_current_anger += field_142_attack_anger_increaser;
    }

    if (UpdateWakeUpSwitchValue())
    {
        field_13E_current_anger += field_146_wake_up_switch_anger_value;
    }

    if (pTarget)
    {
        if (!pTarget->mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit8_bInvisible) && VOnSameYLevel(pTarget) && gMap.Is_Point_In_Current_Camera(mCurrentLevel, mCurrentPath, pTarget->mXPos, pTarget->mYPos, 0) && gMap.Is_Point_In_Current_Camera(mCurrentLevel, mCurrentPath, mXPos, mYPos, 0) && !WallHit(FP_FromInteger(mSpriteScale >= FP_FromInteger(1) ? 10 : 5), pTarget->mXPos - mXPos))
        {
            field_13E_current_anger = field_142_attack_anger_increaser + 1;
            return Brain_0_Patrol::eAlertedByAbe_8;
        }

        if (field_13E_current_anger > field_142_attack_anger_increaser && !pTarget->mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit8_bInvisible) && field_170_danger_obj == -1)
        {
            return Brain_0_Patrol::eAlertedByAbe_8;
        }
    }

    field_15A_chase_timer = 0;
    Path_Hoist* pHoist = TryGetHoist(0, 0);
    if (pHoist)
    {
        if (mCurrentMotion == eFleechMotions::Motion_4_Crawl)
        {
            mNextMotion = eFleechMotions::Motion_8_StopMidCrawlCycle;
        }
        else if (mCurrentMotion != eFleechMotions::Motion_3_Idle)
        {
            mNextMotion = eFleechMotions::Motion_3_Idle;
        }
        field_160_hoistX = pHoist->mTopLeft.x + (mSpriteScale >= FP_FromInteger(1) ? 12 : 6);
        field_162_hoistY = pHoist->mTopLeft.y;
        return 9;
    }

    if (!(Fleech_NextRandom() % 32) && mCurrentMotion == eFleechMotions::Motion_3_Idle)
    {
        mCurrentMotion = eFleechMotions::Motion_6_Knockback;
        return field_126_brain_sub_state;
    }

    if (mCurrentMotion == eFleechMotions::Motion_4_Crawl)
    {
        if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
        {
            if (mXPos < FP_FromInteger(field_154))
            {
                mNextMotion = eFleechMotions::Motion_8_StopMidCrawlCycle;
            }
        }
        else if (mXPos > FP_FromInteger(field_154))
        {
            mNextMotion = eFleechMotions::Motion_8_StopMidCrawlCycle;
        }
    }

    if (mCurrentMotion == eFleechMotions::Motion_3_Idle)
    {
        if (field_14C_EventXPos >= 0)
        {
            if (field_150_patrol_range > 0)
            {
                if (FP_FromInteger(field_14C_EventXPos) <= mXPos)
                {
                    s16 patrolRangeDelta = FP_GetExponent(mXPos) - field_150_patrol_range;
                    if (field_14C_EventXPos > patrolRangeDelta)
                    {
                        patrolRangeDelta = field_14C_EventXPos;
                    }
                    field_154 = patrolRangeDelta;

                    if (!mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        mCurrentMotion = eFleechMotions::Motion_6_Knockback;
                    }
                }
                else
                {
                    s16 patrolRangeDelta = field_150_patrol_range + FP_GetExponent(mXPos);
                    if (field_14C_EventXPos <= patrolRangeDelta)
                    {
                        patrolRangeDelta = field_14C_EventXPos;
                    }
                    field_154 = patrolRangeDelta;

                    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        mCurrentMotion = eFleechMotions::Motion_6_Knockback;
                    }
                }

                mNextMotion = eFleechMotions::Motion_4_Crawl;
                field_14C_EventXPos = -1;
            }
            else
            {
                // TODO: Check __OFSUB__ on else branch
                if (FP_FromInteger(field_14C_EventXPos) > mXPos)
                {
                    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        mCurrentMotion = eFleechMotions::Motion_6_Knockback;
                        field_14C_EventXPos = -1;
                    }
                }
                else if (FP_FromInteger(field_14C_EventXPos) < mXPos)
                {
                    if (!mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        mCurrentMotion = eFleechMotions::Motion_6_Knockback;
                        field_14C_EventXPos = -1;
                    }
                }
            }
        }
        else
        {
            if (field_150_patrol_range > 0)
            {
                if (field_156_rnd_crawl > 0)
                {
                    field_156_rnd_crawl--;
                }
                else
                {
                    if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        field_154 = FP_GetExponent(mXPos) - Fleech_NextRandom() * (FP_GetExponent(mXPos) + field_150_patrol_range - field_152_old_xpos) / 255;
                    }
                    else
                    {
                        field_154 = FP_GetExponent(mXPos) + Fleech_NextRandom() * (field_150_patrol_range + field_152_old_xpos - FP_GetExponent(mXPos)) / 255;
                    }
                    field_156_rnd_crawl = Fleech_NextRandom() & 0x3F;
                    mNextMotion = eFleechMotions::Motion_4_Crawl;
                }
            }
        }
    }

    if (!mFleechFlags.Get(FleechFlags::eGoesToSleep) || (field_13E_current_anger >= field_140_max_anger && gMap.Is_Point_In_Current_Camera(mCurrentLevel, mCurrentPath, mXPos, mYPos, 0)))
    {
        if ((Fleech_NextRandom() % 64) || mCurrentMotion != eFleechMotions::Motion_3_Idle)
        {
            return field_126_brain_sub_state;
        }
        mCurrentMotion = eFleechMotions::Motion_5_PatrolCry;
        return field_126_brain_sub_state;
    }
    field_13E_current_anger = 0;
    mNextMotion = eFleechMotions::Motion_2_Unknown;
    return Brain_0_Patrol::eGoingBackToSleep;
}

s16 Fleech::Brain_Patrol_State_5()
{
    if (mCurrentMotion == eFleechMotions::Motion_7_StopCrawling || mCurrentMotion == eFleechMotions::Motion_6_Knockback)
    {
        return field_126_brain_sub_state;
    }

    if ((FP_FromInteger(field_14E_ScrabParamiteEventXPos) > mXPos && !mAnim.mFlags.Get(AnimFlags::eBit5_FlipX)) ||
        (FP_FromInteger(field_14E_ScrabParamiteEventXPos) < mXPos && mAnim.mFlags.Get(AnimFlags::eBit5_FlipX)))
    {
        if (mCurrentMotion != eFleechMotions::Motion_4_Crawl)
        {
            if (mCurrentMotion == eFleechMotions::Motion_3_Idle)
            {
                mCurrentMotion = eFleechMotions::Motion_6_Knockback;
            }
        }
        else
        {
            mCurrentMotion = eFleechMotions::Motion_7_StopCrawling;
        }
        return field_126_brain_sub_state;
    }

    field_14E_ScrabParamiteEventXPos = -1;
    mNextMotion = eFleechMotions::Motion_4_Crawl;
    CanMove();
    return Brain_0_Patrol::State_6;
}

s16 Fleech::Brain_Patrol_State_6()
{
    auto pDangerObj = static_cast<BaseAnimatedWithPhysicsGameObject*>(sObjectIds.Find_Impl(field_170_danger_obj));
    if (mCurrentMotion != eFleechMotions::Motion_4_Crawl ||
        (pDangerObj && (VIsObjNearby(ScaleToGridSize(mSpriteScale) * FP_FromInteger(5), pDangerObj))))
    {
        if (mCurrentMotion != eFleechMotions::Motion_3_Idle)
        {
            return field_126_brain_sub_state;
        }
    }
    else
    {
        mNextMotion = eFleechMotions::Motion_3_Idle;
    }
    return Brain_0_Patrol::State_7;
}

s16 Fleech::Brain_Patrol_State_7()
{
    if (mCurrentMotion != eFleechMotions::Motion_3_Idle)
    {
        return field_126_brain_sub_state;
    }
    return Brain_0_Patrol::eAlerted_4;
}

s16 Fleech::Brain_Patrol_State_8(BaseAliveGameObject* pTarget)
{
    if (IsActiveHero(pTarget) && sActiveHero->mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit8_bInvisible))
    {
        return Brain_0_Patrol::State_0_Init;
    }

    if (field_15A_chase_timer < field_158_chase_delay)
    {
        field_15A_chase_timer++;
        return field_126_brain_sub_state;
    }

    field_124_brain_state = eFleechBrains::eBrain_1_ChasingAbe;
    return Brain_0_Patrol::State_0_Init;
}

s16 Fleech::Brain_Patrol_State_9()
{
    if (mCurrentMotion != eFleechMotions::Motion_3_Idle)
    {
        return field_126_brain_sub_state;
    }
    if ((mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) && FP_FromInteger(field_160_hoistX) > mXPos) || (!mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) && FP_FromInteger(field_160_hoistX) < mXPos))
    {
        mCurrentMotion = eFleechMotions::Motion_6_Knockback;
        return field_126_brain_sub_state;
    }
    mNextMotion = eFleechMotions::Motion_11_RaiseHead;
    return Brain_0_Patrol::State_10;
}

s16 Fleech::Brain_Patrol_State_10()
{
    if (mCurrentMotion != eFleechMotions::Motion_3_Idle)
    {
        return field_126_brain_sub_state;
    }
    field_152_old_xpos = FP_GetExponent(mXPos);
    return Brain_0_Patrol::eAlerted_4;
}

const s8 byte_551784[] = {
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    7,
    0};

enum Brain_1_ChasingAbe
{
    eInit_0 = 0,
    eChasingAbe_1 = 1,
    eUnknown_2 = 2,
    eContinueChaseAfterFall_3 = 3,
    eBlockedByWall_4 = 4,
    eUnknown_5 = 5,
    eScrabOrParamiteNearby_6 = 6,
    eUnknown_7 = 7,
    eFleechUnknown_8 = 8,
    eUnknown_9 = 9,
    eAbeIsInTongueRange_10 = 10,
    eIsAbeDead_11 = 11,
    eUnknown_12 = 12,
    eBackToPatrol_13 = 13,
    ePrepareToHoist_14 = 14,
    eHoistDone_15 = 15,
    eGoBackToChasingAbe_16 = 16
};

s16 Fleech::Brain_1_ChasingAbe()
{
    auto pObj = static_cast<BaseAliveGameObject*>(sObjectIds.Find_Impl(field_11C_obj_id));
    if (pObj)
    {
        if (pObj->mBaseGameObjectFlags.Get(BaseGameObject::eDead) || (IsActiveHero(pObj) && sActiveHero->mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit8_bInvisible)))
        {
            field_11C_obj_id = -1;
            pObj = nullptr;
        }
    }

    if (gMap.Is_Point_In_Current_Camera(mCurrentLevel, mCurrentPath, mXPos, mYPos, 0))
    {
        MusicController::static_PlayMusic(static_cast<MusicController::MusicTypes>(byte_551784[field_126_brain_sub_state]), this, 0, 0);
    }
    else
    {
        MusicController::static_PlayMusic(MusicController::MusicTypes::eNone_0, this, 0, 0);
    }

    switch (field_126_brain_sub_state)
    {
        case Brain_1_ChasingAbe::eInit_0:
            return Brain_ChasingAbe_State_0(pObj);
        case Brain_1_ChasingAbe::eChasingAbe_1:
            return Brain_ChasingAbe_State_1(pObj);
        case Brain_1_ChasingAbe::eUnknown_2:
            return Brain_ChasingAbe_State_2(pObj);
        case Brain_1_ChasingAbe::eContinueChaseAfterFall_3:
        case Brain_1_ChasingAbe::eGoBackToChasingAbe_16:
            if (mCurrentMotion != eFleechMotions::Motion_3_Idle)
            {
                return field_126_brain_sub_state;
            }
            return Brain_1_ChasingAbe::eChasingAbe_1;

        case Brain_1_ChasingAbe::eBlockedByWall_4:
        {
            if (!pObj || pObj->mHealth <= FP_FromInteger(0))
            {
                return Brain_1_ChasingAbe::eBackToPatrol_13;
            }

            BaseAliveGameObject* pMudOrAbe = FindMudOrAbe();
            if (pMudOrAbe)
            {
                if (pMudOrAbe->mBaseGameObjectId != field_11C_obj_id)
                {
                    pObj = pMudOrAbe;
                    field_11C_obj_id = pMudOrAbe->mBaseGameObjectId;
                }
            }

            mFleechFlags.Clear(FleechFlags::eChasingOrScaredCrawlingLeft);
            if (!WallHit(FP_FromInteger(mSpriteScale >= FP_FromInteger(1) ? 10 : 5), ScaleToGridSize(mSpriteScale)))
            {
                return Brain_1_ChasingAbe::eChasingAbe_1;
            }

            Path_Hoist* pHoist = TryGetHoist(0, FALSE);
            if (pHoist)
            {
                mNextMotion = eFleechMotions::Motion_3_Idle;
                field_160_hoistX = pHoist->mTopLeft.x + (mSpriteScale < FP_FromInteger(1) ? 6 : 12);
                field_162_hoistY = pHoist->mTopLeft.y;
                return Brain_1_ChasingAbe::ePrepareToHoist_14;
            }
            [[fallthrough]];
        }

        case Brain_1_ChasingAbe::eUnknown_5:
            if (!pObj || pObj->mHealth <= FP_FromInteger(0))
            {
                return Brain_1_ChasingAbe::eBackToPatrol_13;
            }

            if (mCurrentMotion != eFleechMotions::Motion_3_Idle)
            {
                return field_126_brain_sub_state;
            }

            if (IsActiveHero(pObj) &&
                VOnSameYLevel(sActiveHero) &&
                gMap.Is_Point_In_Current_Camera(mCurrentLevel, mCurrentPath, sActiveHero->mXPos, sActiveHero->mYPos, 0) &&
                gMap.Is_Point_In_Current_Camera(mCurrentLevel, mCurrentPath, mXPos, mYPos, 0) &&
                !WallHit(FP_FromInteger((mSpriteScale >= FP_FromInteger(1) ? 10 : 5)), sActiveHero->mXPos - mXPos))
            {
                return Brain_1_ChasingAbe::eChasingAbe_1;
            }

            if (!IsNear(pObj))
            {
                return Brain_1_ChasingAbe::eUnknown_2;
            }

            if (mFleechFlags.Get(FleechFlags::eChasingOrScaredCrawlingLeft))
            {
                if (pObj->mXPos <= mXPos - FP_FromInteger(2))
                {
                    return field_126_brain_sub_state;
                }
            }
            else
            {
                if (pObj->mXPos >= mXPos + FP_FromInteger(2))
                {
                    return field_126_brain_sub_state;
                }
            }
            return Brain_1_ChasingAbe::eChasingAbe_1;

        case Brain_1_ChasingAbe::eScrabOrParamiteNearby_6:
            if (mCurrentMotion != eFleechMotions::Motion_7_StopCrawling && mCurrentMotion != eFleechMotions::Motion_6_Knockback && mNextMotion != -1)
            {
                return field_126_brain_sub_state;
            }
            mNextMotion = eFleechMotions::Motion_4_Crawl;
            return Brain_1_ChasingAbe::eUnknown_7;

        case Brain_1_ChasingAbe::eUnknown_7:
        {
            auto v70 = static_cast<BaseAnimatedWithPhysicsGameObject*>(sObjectIds.Find_Impl(field_170_danger_obj));
            if (mCurrentMotion != eFleechMotions::Motion_4_Crawl || (v70 && VIsObjNearby(ScaleToGridSize(mSpriteScale) * FP_FromInteger(5), v70)))
            {
                if (mCurrentMotion != eFleechMotions::Motion_3_Idle && mNextMotion != -1)
                {
                    return field_126_brain_sub_state;
                }
                mNextMotion = eFleechMotions::Motion_6_Knockback;
            }
            else
            {
                mNextMotion = eFleechMotions::Motion_7_StopCrawling;
            }
            return Brain_1_ChasingAbe::eUnknown_9;
        }

        case Brain_1_ChasingAbe::eFleechUnknown_8:
            if (mCurrentMotion != eFleechMotions::Motion_3_Idle)
            {
                return field_126_brain_sub_state;
            }
            mNextMotion = eFleechMotions::Motion_4_Crawl;
            return Brain_1_ChasingAbe::eUnknown_9;

        case Brain_1_ChasingAbe::eUnknown_9:
            return Brain_ChasingAbe_State_9(pObj);

        case Brain_1_ChasingAbe::eAbeIsInTongueRange_10:
            if (pObj)
            {
                if (mCurrentMotion == eFleechMotions::Motion_14_ExtendTongueFromEnemy)
                {
                    return Brain_1_ChasingAbe::eIsAbeDead_11;
                }
                else if (mNextMotion == eFleechMotions::Motion_14_ExtendTongueFromEnemy)
                {
                    return field_126_brain_sub_state;
                }

                ResetTarget();
                return Brain_1_ChasingAbe::eChasingAbe_1;
            }
            sub_42B8C0();
            return Brain_1_ChasingAbe::eBackToPatrol_13;

        case Brain_1_ChasingAbe::eIsAbeDead_11:
            if (pObj)
            {
                if (mCurrentMotion != eFleechMotions::Motion_3_Idle)
                {
                    return field_126_brain_sub_state;
                }

                ResetTarget();

                if (pObj->mHealth <= FP_FromInteger(0))
                {
                    return Brain_1_ChasingAbe::eBackToPatrol_13;
                }

                if (VIsObj_GettingNear_On_X(pObj))
                {
                    mCurrentMotion = eFleechMotions::Motion_6_Knockback;
                    return Brain_1_ChasingAbe::eUnknown_12;
                }

                return Brain_1_ChasingAbe::eChasingAbe_1;
            }
            sub_42B8C0();
            return Brain_1_ChasingAbe::eBackToPatrol_13;

        case Brain_1_ChasingAbe::eUnknown_12:
            if (pObj)
            {
                if (mCurrentMotion != eFleechMotions::Motion_3_Idle)
                {
                    return field_126_brain_sub_state;
                }
                if (!Collision(1))
                {
                    mNextMotion = eFleechMotions::Motion_4_Crawl;
                }
                return Brain_1_ChasingAbe::eChasingAbe_1;
            }
            sub_42B8C0();
            return Brain_1_ChasingAbe::eBackToPatrol_13;

        case Brain_1_ChasingAbe::eBackToPatrol_13:
            mNextMotion = eFleechMotions::Motion_3_Idle;
            field_124_brain_state = eFleechBrains::eBrain_0_Patrol;
            field_13E_current_anger = field_140_max_anger + (field_142_attack_anger_increaser - field_140_max_anger) / 2;
            return Brain_1_ChasingAbe::eInit_0;

        case Brain_1_ChasingAbe::ePrepareToHoist_14:
            if (mCurrentMotion != eFleechMotions::Motion_3_Idle)
            {
                return field_126_brain_sub_state;
            }
            if ((mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) && FP_FromInteger(field_160_hoistX) > mXPos) || (!mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) && FP_FromInteger(field_160_hoistX) < mXPos))
            {
                mCurrentMotion = eFleechMotions::Motion_6_Knockback;
                return field_126_brain_sub_state;
            }
            mNextMotion = eFleechMotions::Motion_11_RaiseHead;
            return Brain_1_ChasingAbe::eHoistDone_15;

        case Brain_1_ChasingAbe::eHoistDone_15:
            if (mCurrentMotion != eFleechMotions::Motion_13_SettleOnGround)
            {
                return field_126_brain_sub_state;
            }
            return Brain_1_ChasingAbe::eGoBackToChasingAbe_16;

        default:
            return field_126_brain_sub_state;
    }
}

s16 Fleech::Brain_ChasingAbe_State_9(BaseAliveGameObject* pObj)
{
    if (!IsScrabOrParamiteNear(ScaleToGridSize(mSpriteScale) * FP_FromInteger(6)))
    {
        return 1;
    }

    auto pDangerObj = static_cast<BaseAliveGameObject*>(sObjectIds.Find_Impl(field_170_danger_obj));
    if (pDangerObj == sControlledCharacter)
    {
        if (Collision(1) || HandleEnemyStopperOrSlamDoor(1) || WallHit(FP_FromInteger(mSpriteScale >= FP_FromInteger(1) ? 10 : 5), ScaleToGridSize(mSpriteScale) * FP_FromInteger(mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) != 0 ? -1 : 1)))
        {
            mCurrentMotion = eFleechMotions::Motion_6_Knockback;
            field_124_brain_state = eFleechBrains::eBrain_2_Scared;
            return 0;
        }
    }

    if (mCurrentMotion != eFleechMotions::Motion_3_Idle)
    {
        mNextMotion = eFleechMotions::Motion_3_Idle;
        return field_126_brain_sub_state;
    }

    if (IsScrabOrParamiteNear(ScaleToGridSize(mSpriteScale) * FP_FromInteger(5)))
    {
        auto v82 = static_cast<BaseAnimatedWithPhysicsGameObject*>(sObjectIds.Find_Impl(field_170_danger_obj));
        if (VIsFacingMe(v82))
        {
            mCurrentMotion = eFleechMotions::Motion_6_Knockback;
        }
        return 8;
    }

    if (!pObj || !IsNear(pObj))
    {
        return 13;
    }

    if (pObj->mXPos < mXPos)
    {
        if (pDangerObj->mXPos > mXPos)
        {
            return 1;
        }
    }

    if (pDangerObj->mXPos < mXPos)
    {
        return 1;
    }

    if (pObj->mXPos <= mXPos)
    {
        if (pDangerObj->mXPos > mXPos)
        {
            return 1;
        }
    }

    if (!(Fleech_NextRandom() % 32) && mCurrentMotion == eFleechMotions::Motion_3_Idle)
    {
        mCurrentMotion = eFleechMotions::Motion_6_Knockback;
        return field_126_brain_sub_state;
    }

    if ((Fleech_NextRandom() % 64) || mCurrentMotion != eFleechMotions::Motion_3_Idle)
    {
        return field_126_brain_sub_state;
    }
    mCurrentMotion = eFleechMotions::Motion_5_PatrolCry;
    return field_126_brain_sub_state;
}

s16 Fleech::Brain_ChasingAbe_State_2(BaseAliveGameObject* pObj)
{
    if (!pObj || pObj->mHealth <= FP_FromInteger(0))
    {
        return Brain_1_ChasingAbe::eBackToPatrol_13;
    }

    if (IsNear(pObj))
    {
        return Brain_1_ChasingAbe::eChasingAbe_1;
    }

    if (VIsFacingMe(pObj) || mCurrentMotion == eFleechMotions::Motion_7_StopCrawling || mCurrentMotion == eFleechMotions::Motion_6_Knockback)
    {
        if (mCurrentMotion != eFleechMotions::Motion_4_Crawl)
        {
            mNextMotion = eFleechMotions::Motion_4_Crawl;
        }

        if (IsScrabOrParamiteNear(ScaleToGridSize(mSpriteScale) * FP_FromInteger(5)))
        {
            auto v56 = static_cast<BaseAnimatedWithPhysicsGameObject*>(sObjectIds.Find_Impl(field_170_danger_obj));
            if (VIsFacingMe(v56))
            {
                mNextMotion = eFleechMotions::Motion_7_StopCrawling;
            }
            Sound(FleechSound::Scared_7);
            return Brain_1_ChasingAbe::eScrabOrParamiteNearby_6;
        }

        if (field_15E_lost_target_timer < field_15C_lost_target_timeout)
        {
            field_15E_lost_target_timer++;
            Path_Hoist* pHoist = TryGetHoist(1, FALSE);
            if (pHoist)
            {
                mNextMotion = eFleechMotions::Motion_3_Idle;
                field_160_hoistX = pHoist->mTopLeft.x + (mSpriteScale < FP_FromInteger(1) ? 6 : 12);
                field_162_hoistY = pHoist->mTopLeft.y;
                return 14;
            }

            if (Fleech_NextRandom() % 64)
            {
                return field_126_brain_sub_state;
            }

            mCurrentMotion = eFleechMotions::Motion_5_PatrolCry;
            return field_126_brain_sub_state;
        }

        field_15E_lost_target_timer = 0;
        field_124_brain_state = eFleechBrains::eBrain_0_Patrol;
        field_13E_current_anger = field_142_attack_anger_increaser - 1;
        return Brain_1_ChasingAbe::eInit_0;
    }
    else if (mCurrentMotion == eFleechMotions::Motion_4_Crawl) // TODO: Check v52 was cur motion
    {
        mNextMotion = eFleechMotions::Motion_7_StopCrawling;
        return field_126_brain_sub_state;
    }
    else
    {
        mNextMotion = eFleechMotions::Motion_6_Knockback;
        return field_126_brain_sub_state;
    }
}

s16 Fleech::Brain_ChasingAbe_State_0(BaseAliveGameObject* pObj)
{
    if (!pObj)
    {
        field_11C_obj_id = -1;
        BaseAliveGameObject* pMudOrAbe = FindMudOrAbe();
        if (!pMudOrAbe)
        {
            return 13;
        }
        field_11C_obj_id = pMudOrAbe->mBaseGameObjectId;
    }
    field_120_unused = 0;
    field_15E_lost_target_timer = 0;
    mNextMotion = eFleechMotions::Motion_4_Crawl;
    Sound(FleechSound::PatrolCry_0);
    return 1;
}

s16 Fleech::Brain_ChasingAbe_State_1(BaseAliveGameObject* pObj)
{
    if (!pObj || pObj->mHealth <= FP_FromInteger(0))
    {
        return Brain_1_ChasingAbe::eBackToPatrol_13;
    }

    // Is moving?
    if (mVelX != FP_FromInteger(0))
    {
        // Check for blocked by wall
        const FP k1Directed = FP_FromInteger((mAnim.mFlags.Get(AnimFlags::eBit5_FlipX)) != 0 ? -1 : 1);
        if (WallHit(FP_FromInteger(mSpriteScale >= FP_FromInteger(1) ? 10 : 5), ScaleToGridSize(mSpriteScale) * k1Directed))
        {
            mNextMotion = eFleechMotions::Motion_8_StopMidCrawlCycle;
            mFleechFlags.Set(FleechFlags::eChasingOrScaredCrawlingLeft, mVelX < FP_FromInteger(0));
            return Brain_1_ChasingAbe::eBlockedByWall_4;
        }

        // Check for enemy stopper or slam door
        if (HandleEnemyStopperOrSlamDoor(1))
        {
            mNextMotion = eFleechMotions::Motion_8_StopMidCrawlCycle;
            mFleechFlags.Set(FleechFlags::eChasingOrScaredCrawlingLeft, mVelX < FP_FromInteger(0));

            FP xOffset = mXPos;
            if (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX))
            {
                xOffset -= ScaleToGridSize(mSpriteScale);
            }
            else
            {
                xOffset += ScaleToGridSize(mSpriteScale);
            }

            FP slamDoorX = xOffset;
            if (mXPos <= xOffset)
            {
                slamDoorX = mXPos;
            }

            FP slamDoorW = mXPos;
            if (mXPos <= xOffset)
            {
                slamDoorW = xOffset;
            }

            Path_TLV* pSlamDoor = sPathInfo->TLV_Get_At_4DB4B0(
                FP_GetExponent(slamDoorX),
                FP_GetExponent(mYPos),
                FP_GetExponent(slamDoorW),
                FP_GetExponent(mYPos),
                TlvTypes::SlamDoor_85);

            if (pSlamDoor)
            {
                return Brain_1_ChasingAbe::eBlockedByWall_4;
            }
            return Brain_1_ChasingAbe::eUnknown_5;
        }
    }

    // Check for danger object
    if (IsScrabOrParamiteNear(ScaleToGridSize(mSpriteScale) * FP_FromInteger(5)))
    {
        auto pDangerObj = static_cast<BaseAliveGameObject*>(sObjectIds.Find_Impl(field_170_danger_obj));
        if (VIsFacingMe(pDangerObj))
        {
            if (mCurrentMotion == eFleechMotions::Motion_4_Crawl)
            {
                mNextMotion = eFleechMotions::Motion_7_StopCrawling;
                Sound(FleechSound::Scared_7);
                return Brain_1_ChasingAbe::eScrabOrParamiteNearby_6;
            }

            if (mCurrentMotion == eFleechMotions::Motion_3_Idle)
            {
                mNextMotion = eFleechMotions::Motion_6_Knockback;
            }
        }

        Sound(FleechSound::Scared_7);
        return Brain_1_ChasingAbe::eScrabOrParamiteNearby_6;
    }

    // Check for food object
    BaseAliveGameObject* pAbeOrMud = FindMudOrAbe();
    if (pAbeOrMud)
    {
        if (pAbeOrMud->mBaseGameObjectId != field_11C_obj_id)
        {
            pObj = pAbeOrMud;
            field_11C_obj_id = pAbeOrMud->mBaseGameObjectId;
        }
    }

    // Can we get to them on this level?
    if (VOnSameYLevel(pObj))
    {
        if (VIsObjNearby(ScaleToGridSize(mSpriteScale) * FP_FromInteger(3), pObj))
        {
            if (pObj->mSpriteScale == mSpriteScale &&
                VIsFacingMe(pObj) &&
                !WallHit(FP_FromInteger(mSpriteScale >= FP_FromInteger(1) ? 10 : 5), pObj->mXPos - mXPos) &&
                GotNoTarget() &&
                gMap.Is_Point_In_Current_Camera(mCurrentLevel, mCurrentPath, mXPos, mYPos, 0))
            {
                SetTarget();
                mNextMotion = eFleechMotions::Motion_14_ExtendTongueFromEnemy;
                return Brain_1_ChasingAbe::eAbeIsInTongueRange_10;
            }
        }
    }

    // Can we get to a hanging abe?
    if (IsActiveHero(pObj) && pObj->mCurrentMotion == eAbeMotions::Motion_67_LedgeHang_454E20 && mYPos > pObj->mYPos)
    {
        if (mYPos - pObj->mYPos <= (ScaleToGridSize(mSpriteScale) * FP_FromInteger(6)))
        {
            if (VIsObjNearby(ScaleToGridSize(mSpriteScale) * FP_FromInteger(2), pObj))
            {
                if (pObj->mSpriteScale == mSpriteScale
                    && VIsFacingMe(pObj) && !WallHit(FP_FromInteger(mSpriteScale >= FP_FromInteger(1) ? 10 : 5), pObj->mXPos - mXPos) && GotNoTarget() && gMap.Is_Point_In_Current_Camera(mCurrentLevel, mCurrentPath, mXPos, mYPos, 0))
                {
                    SetTarget();
                    mNextMotion = eFleechMotions::Motion_14_ExtendTongueFromEnemy;
                    return Brain_1_ChasingAbe::eAbeIsInTongueRange_10;
                }
            }
        }
    }

    if (pObj->mYPos >= mYPos - (FP_FromInteger(mSpriteScale >= FP_FromInteger(1) ? 18 : 9)) || pObj->mSpriteScale != mSpriteScale)
    {
        return Brain_ChasingAbe_State1_Helper(pObj);
    }

    // Find hoist in front us?
    Path_Hoist* pHoist = TryGetHoist(1, FALSE);
    if (pHoist)
    {
        mNextMotion = eFleechMotions::Motion_3_Idle;
        field_160_hoistX = pHoist->mTopLeft.x + (mSpriteScale >= FP_FromInteger(1) ? 12 : 6);
        field_162_hoistY = pHoist->mTopLeft.y;
        return Brain_1_ChasingAbe::ePrepareToHoist_14;
    }

    // Find host in front or behind us?
    pHoist = TryGetHoist(0, TRUE);
    if (pHoist)
    {
        if (mCurrentMotion == eFleechMotions::Motion_3_Idle)
        {
            // TODO: Check left VS flip is correct
            if ((pHoist->mGrabDirection == Path_Hoist::GrabDirection::eFacingLeft && mAnim.mFlags.Get(AnimFlags::eBit5_FlipX)) && pHoist->mGrabDirection != Path_Hoist::GrabDirection::eFacingAnyDirection)
            {
                mCurrentMotion = eFleechMotions::Motion_6_Knockback;
            }

            mNextMotion = eFleechMotions::Motion_3_Idle;
            field_160_hoistX = pHoist->mTopLeft.x + (mSpriteScale >= FP_FromInteger(1) ? 12 : 6);
            field_162_hoistY = pHoist->mTopLeft.y;
            return Brain_1_ChasingAbe::ePrepareToHoist_14;
        }
        else
        {
            mNextMotion = eFleechMotions::Motion_3_Idle;
            return field_126_brain_sub_state;
        }
    }

    // Look 12 ahead fora hoist
    s32 k12BlocksCheck = 1;
    do
    {
        pHoist = TryGetHoist(k12BlocksCheck, TRUE);
        if (pHoist)
        {
            mNextMotion = eFleechMotions::Motion_4_Crawl;
            field_160_hoistX = pHoist->mTopLeft.x + (mSpriteScale >= FP_FromInteger(1) ? 12 : 6);
            field_162_hoistY = pHoist->mTopLeft.y;
            return field_126_brain_sub_state;
        }

        ++k12BlocksCheck;
    }
    while (k12BlocksCheck <= 12);

    // Look 8 behind for a hoist
    s32 k8BlocksCheck = 1;
    while (1)
    {
        pHoist = TryGetHoist(-k8BlocksCheck, 1);
        if (pHoist)
        {
            switch (mCurrentMotion)
            {
                case eFleechMotions::Motion_4_Crawl:
                    mNextMotion = eFleechMotions::Motion_7_StopCrawling;
                    break;

                case eFleechMotions::Motion_3_Idle:
                    mCurrentMotion = eFleechMotions::Motion_6_Knockback;
                    break;

                case eFleechMotions::Motion_6_Knockback:
                case eFleechMotions::Motion_7_StopCrawling:
                    mNextMotion = eFleechMotions::Motion_4_Crawl;
                    break;
            }

            field_160_hoistX = pHoist->mTopLeft.x + (mSpriteScale >= FP_FromInteger(1) ? 12 : 6);
            field_162_hoistY = pHoist->mTopLeft.y;
            return field_126_brain_sub_state;
        }

        if (++k8BlocksCheck > 8)
        {
            return Brain_ChasingAbe_State1_Helper(pObj);
        }
    }
}

s16 Fleech::Brain_ChasingAbe_State1_Helper(BaseAliveGameObject* pObj)
{
    if (pObj->mYPos < mYPos - FP_FromInteger((mSpriteScale >= FP_FromInteger(1) ? 18 : 9)) && pObj->mSpriteScale == mSpriteScale && IsNear(pObj))
    {
        const FP v45 = mXPos - pObj->mXPos;
        if (FP_Abs(v45) < ScaleToGridSize(mSpriteScale) * FP_FromDouble(0.5))
        {
            return Brain_1_ChasingAbe::eBackToPatrol_13;
        }
    }

    if (!VIsFacingMe(pObj) && mCurrentMotion == eFleechMotions::Motion_4_Crawl)
    {
        mNextMotion = eFleechMotions::Motion_7_StopCrawling;
    }

    if (mCurrentMotion == eFleechMotions::Motion_3_Idle)
    {
        if (VIsFacingMe(pObj))
        {
            const FP v48 = FP_FromInteger((mAnim.mFlags.Get(AnimFlags::eBit5_FlipX)) != 0 ? -1 : 1);
            if (WallHit(
                    FP_FromInteger(mSpriteScale >= FP_FromInteger(1) ? 10 : 5),
                    ScaleToGridSize(mSpriteScale) * v48))
            {
                mFleechFlags.Set(FleechFlags::eChasingOrScaredCrawlingLeft, mAnim.mFlags.Get(AnimFlags::eBit5_FlipX));
                return Brain_1_ChasingAbe::eBlockedByWall_4;
            }
            mNextMotion = eFleechMotions::Motion_4_Crawl;
        }
        else
        {
            mCurrentMotion = eFleechMotions::Motion_6_Knockback;
        }
    }

    if (mCurrentMotion == eFleechMotions::Motion_7_StopCrawling)
    {
        mNextMotion = eFleechMotions::Motion_4_Crawl;
    }

    if (mCurrentMotion == eFleechMotions::Motion_9_Fall)
    {
        return Brain_1_ChasingAbe::eContinueChaseAfterFall_3;
    }

    if (IsNear(pObj))
    {
        return field_126_brain_sub_state;
    }

    if (!VIsFacingMe(pObj))
    {
        if (mCurrentMotion != eFleechMotions::Motion_7_StopCrawling && mCurrentMotion != eFleechMotions::Motion_6_Knockback)
        {
            if (mCurrentMotion == eFleechMotions::Motion_4_Crawl)
            {
                mNextMotion = eFleechMotions::Motion_7_StopCrawling;
                return Brain_1_ChasingAbe::eUnknown_2;
            }
            mNextMotion = eFleechMotions::Motion_6_Knockback;
        }
    }
    return Brain_1_ChasingAbe::eUnknown_2;
}

const s8 byte_5518B0[16] = {
    6,
    6,
    6,
    6,
    6,
    5,
    5,
    5,
    5,
    6,
    6,
    6,
    6,
    0,
    0,
    0};

enum Brain_2_Scared
{
    eScared_0 = 0,
    eReactToDanger_1 = 1,
    eCrawl_2 = 2,
    eLookForHoist_3 = 3,
    eCornered_4 = 4,
    eCorneredPrepareAttack_5 = 5,
    eCorneredAttack_6 = 6,
    eCheckIfEnemyDead_7 = 7,
    eEnemyStillAlive_8 = 8,
    ePatrolArea_9 = 9,
    ePrepareToHoist_10 = 10,
    eHoisting_11 = 11,
};

s16 Fleech::Brain_2_Scared()
{
    auto pDangerObj = static_cast<BaseAliveGameObject*>(sObjectIds.Find_Impl(field_170_danger_obj));
    if (pDangerObj && pDangerObj->mHealth > FP_FromInteger(0))
    {
        // Danger target is dead, check if there is another one who is still alive.
        IsScrabOrParamiteNear(ScaleToGridSize(mSpriteScale) * FP_FromInteger(8));
    }

    pDangerObj = static_cast<BaseAliveGameObject*>(sObjectIds.Find_Impl(field_170_danger_obj));
    if (pDangerObj)
    {
        if (pDangerObj->mBaseGameObjectFlags.Get(BaseGameObject::eDead))
        {
            field_170_danger_obj = -1;
            pDangerObj = 0;
        }
    }

    if (gMap.Is_Point_In_Current_Camera(mCurrentLevel, mCurrentPath, mXPos, mYPos, 0))
    {
        MusicController::static_PlayMusic(static_cast<MusicController::MusicTypes>(byte_5518B0[field_126_brain_sub_state]), this, 0, 0);
    }
    else
    {
        MusicController::static_PlayMusic(MusicController::MusicTypes::eNone_0, this, 0, 0);
    }

    switch (field_126_brain_sub_state)
    {
        case Brain_2_Scared::eScared_0:
            if (!pDangerObj || pDangerObj != sControlledCharacter)
            {
                return Brain_2_Scared::ePatrolArea_9;
            }

            if (!VIsFacingMe(pDangerObj))
            {
                mNextMotion = eFleechMotions::Motion_4_Crawl;
                Sound(FleechSound::Scared_7);
                return Brain_2_Scared::eReactToDanger_1;
            }

            if (mCurrentMotion == eFleechMotions::Motion_3_Idle)
            {
                mCurrentMotion = eFleechMotions::Motion_6_Knockback;
                mNextMotion = eFleechMotions::Motion_4_Crawl;
                Sound(FleechSound::Scared_7);
                return Brain_2_Scared::eReactToDanger_1;
            }

            if (mCurrentMotion != eFleechMotions::Motion_4_Crawl)
            {
                Sound(FleechSound::Scared_7);
                return Brain_2_Scared::eReactToDanger_1;
            }

            mNextMotion = eFleechMotions::Motion_7_StopCrawling;
            Sound(FleechSound::Scared_7);
            return Brain_2_Scared::eReactToDanger_1;

        case Brain_2_Scared::eReactToDanger_1:
        {
            if (!pDangerObj || pDangerObj->mHealth <= FP_FromInteger(0) || pDangerObj != sControlledCharacter)
            {
                return Brain_2_Scared::ePatrolArea_9;
            }

            if (mVelX != FP_FromInteger(0))
            {
                const FP v9 = FP_FromInteger((mAnim.mFlags.Get(AnimFlags::eBit5_FlipX)) != 0 ? -1 : 1);
                if (WallHit(FP_FromInteger(mSpriteScale >= FP_FromInteger(0) ? 10 : 5), ScaleToGridSize(mSpriteScale) * v9))
                {
                    mNextMotion = eFleechMotions::Motion_8_StopMidCrawlCycle;
                    mFleechFlags.Set(FleechFlags::eChasingOrScaredCrawlingLeft, mVelX < FP_FromInteger(0));
                    return Brain_2_Scared::eLookForHoist_3;
                }

                if (mVelX != FP_FromInteger(0) && (Collision(1) || HandleEnemyStopperOrSlamDoor(1)))
                {
                    mNextMotion = eFleechMotions::Motion_8_StopMidCrawlCycle;
                    mFleechFlags.Set(FleechFlags::eChasingOrScaredCrawlingLeft, mVelX < FP_FromInteger(0));
                    return Brain_2_Scared::eCornered_4;
                }
            }

            Path_Hoist* pHoist = TryGetHoist(1, 0);
            if (pHoist)
            {
                mNextMotion = eFleechMotions::Motion_8_StopMidCrawlCycle;
                field_160_hoistX = pHoist->mTopLeft.x + 12;
                field_162_hoistY = pHoist->mTopLeft.y;
                return Brain_2_Scared::ePrepareToHoist_10;
            }

            if (VIsFacingMe(pDangerObj))
            {
                if (mCurrentMotion == eFleechMotions::Motion_4_Crawl)
                {
                    mNextMotion = eFleechMotions::Motion_7_StopCrawling;
                }
            }

            if (mCurrentMotion == eFleechMotions::Motion_3_Idle)
            {
                if (VIsFacingMe(pDangerObj))
                {
                    mCurrentMotion = eFleechMotions::Motion_6_Knockback;
                }
                else
                {
                    const FP k1Directed = FP_FromInteger(mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) != 0 ? -1 : 1);
                    if (WallHit(
                            FP_FromInteger(mSpriteScale >= FP_FromInteger(1) ? 10 : 5),
                            ScaleToGridSize(mSpriteScale) * k1Directed))
                    {
                        mFleechFlags.Set(FleechFlags::eChasingOrScaredCrawlingLeft, mAnim.mFlags.Get(AnimFlags::eBit5_FlipX));
                        return Brain_2_Scared::eCornered_4;
                    }
                    mNextMotion = eFleechMotions::Motion_4_Crawl;
                }
            }

            if (mCurrentMotion != eFleechMotions::Motion_9_Fall)
            {
                return field_126_brain_sub_state;
            }
            return Brain_2_Scared::eCrawl_2;
        }

        case Brain_2_Scared::eCrawl_2:
            if (mCurrentMotion == eFleechMotions::Motion_3_Idle)
            {
                mCurrentMotion = eFleechMotions::Motion_4_Crawl;
                return Brain_2_Scared::eReactToDanger_1;
            }
            return field_126_brain_sub_state;

        case Brain_2_Scared::eLookForHoist_3:
        {
            const FP v22 = FP_FromInteger((mFleechFlags.Get(FleechFlags::eChasingOrScaredCrawlingLeft)) != 0 ? -1 : 1);
            if (!WallHit(FP_FromInteger(mSpriteScale >= FP_FromInteger(1) ? 10 : 5), ScaleToGridSize(mSpriteScale) * v22))
            {
                return Brain_2_Scared::eReactToDanger_1;
            }

            Path_Hoist* pHoist = TryGetHoist(0, 0);
            if (pHoist)
            {
                if (mCurrentMotion != eFleechMotions::Motion_3_Idle)
                {
                    mNextMotion = eFleechMotions::Motion_3_Idle;
                }

                field_160_hoistX = pHoist->mTopLeft.x + (mSpriteScale >= FP_FromInteger(1) ? 12 : 6);
                field_162_hoistY = pHoist->mTopLeft.y;
                return Brain_2_Scared::ePrepareToHoist_10;
            }
            [[fallthrough]];
        }

        case Brain_2_Scared::eCornered_4:
        {
            if (!pDangerObj || pDangerObj != sControlledCharacter)
            {
                return Brain_2_Scared::ePatrolArea_9;
            }

            if (mCurrentMotion != eFleechMotions::Motion_3_Idle)
            {
                return field_126_brain_sub_state;
            }

            if (mFleechFlags.Get(FleechFlags::eChasingOrScaredCrawlingLeft))
            {
                if (pDangerObj->mXPos < mXPos)
                {
                    return Brain_2_Scared::eReactToDanger_1;
                }
            }
            else if (pDangerObj->mXPos > mXPos)
            {
                return Brain_2_Scared::eReactToDanger_1;
            }

            if (VOnSameYLevel(pDangerObj) && 
                VIsObjNearby(ScaleToGridSize(mSpriteScale) * FP_FromInteger(3), pDangerObj) &&
                pDangerObj->mSpriteScale == mSpriteScale &&
                VIsFacingMe(pDangerObj) &&
                !WallHit(FP_FromInteger(mSpriteScale >= FP_FromInteger(1) ? 10 : 5), pDangerObj->mXPos - mXPos) &&
                GotNoTarget())
            {
                field_11C_obj_id = field_170_danger_obj;
                return Brain_2_Scared::eCorneredPrepareAttack_5;
            }
            else
            {
                if ((Fleech_NextRandom() % 32) || mCurrentMotion != eFleechMotions::Motion_3_Idle)
                {
                    return field_126_brain_sub_state;
                }
                mCurrentMotion = eFleechMotions::Motion_6_Knockback;
                return field_126_brain_sub_state;
            }
            break;
        }

        case Brain_2_Scared::eCorneredPrepareAttack_5:
            if (!pDangerObj || pDangerObj != sControlledCharacter)
            {
                return Brain_2_Scared::ePatrolArea_9;
            }

            if (VIsFacingMe(pDangerObj) || mCurrentMotion != eFleechMotions::Motion_3_Idle)
            {
                if (!VOnSameYLevel(pDangerObj))
                {
                    return field_126_brain_sub_state;
                }

                if (!VIsObjNearby(ScaleToGridSize(mSpriteScale) * FP_FromInteger(3), pDangerObj))
                {
                    return field_126_brain_sub_state;
                }

                if (pDangerObj->mSpriteScale != mSpriteScale)
                {
                    return field_126_brain_sub_state;
                }

                if (!VIsFacingMe(pDangerObj))
                {
                    return field_126_brain_sub_state;
                }

                if (WallHit(
                        FP_FromInteger(mSpriteScale >= FP_FromInteger(1) ? 10 : 5),
                        pDangerObj->mXPos - mXPos)
                    || !GotNoTarget())
                {
                    return field_126_brain_sub_state;
                }

                SetTarget();
                mNextMotion = eFleechMotions::Motion_14_ExtendTongueFromEnemy;
                return Brain_2_Scared::eCorneredAttack_6;
            }
            else
            {
                mCurrentMotion = eFleechMotions::Motion_6_Knockback;
                return field_126_brain_sub_state;
            }
            break;

        case Brain_2_Scared::eCorneredAttack_6:
            if (pDangerObj)
            {
                if (mCurrentMotion == eFleechMotions::Motion_14_ExtendTongueFromEnemy)
                {
                    return Brain_2_Scared::eCheckIfEnemyDead_7;
                }
                else
                {
                    if (mNextMotion == eFleechMotions::Motion_14_ExtendTongueFromEnemy)
                    {
                        return field_126_brain_sub_state;
                    }
                    ResetTarget();
                    return Brain_2_Scared::eReactToDanger_1;
                }
            }
            else
            {
                sub_42B8C0();
                return Brain_2_Scared::ePatrolArea_9;
            }
            break;

        case Brain_2_Scared::eCheckIfEnemyDead_7:
            if (pDangerObj)
            {
                if (mCurrentMotion != eFleechMotions::Motion_3_Idle)
                {
                    return field_126_brain_sub_state;
                }

                ResetTarget();

                if (pDangerObj->mHealth <= FP_FromInteger(0))
                {
                    return Brain_2_Scared::ePatrolArea_9;
                }
                mCurrentMotion = eFleechMotions::Motion_6_Knockback;
                return Brain_2_Scared::eEnemyStillAlive_8;
            }
            else
            {
                sub_42B8C0();
                return Brain_2_Scared::ePatrolArea_9;
            }
            break;

        case Brain_2_Scared::eEnemyStillAlive_8:
            if (pDangerObj)
            {
                if (mCurrentMotion != eFleechMotions::Motion_3_Idle)
                {
                    return field_126_brain_sub_state;
                }
                return Brain_2_Scared::eCorneredPrepareAttack_5;
            }
            else
            {
                sub_42B8C0();
                return Brain_2_Scared::ePatrolArea_9;
            }
            break;

        case Brain_2_Scared::ePatrolArea_9:
            mNextMotion = eFleechMotions::Motion_3_Idle;
            field_170_danger_obj = -1;
            field_11C_obj_id = -1;
            field_124_brain_state = eFleechBrains::eBrain_0_Patrol;
            return Brain_2_Scared::eScared_0;

        case Brain_2_Scared::ePrepareToHoist_10:
            if (mCurrentMotion != eFleechMotions::Motion_3_Idle)
            {
                return field_126_brain_sub_state;
            }
            if ((!mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) || FP_FromInteger(field_160_hoistX) <= mXPos) &&
                (mAnim.mFlags.Get(AnimFlags::eBit5_FlipX) || FP_FromInteger(field_160_hoistX) >= mXPos))
            {
                mNextMotion = eFleechMotions::Motion_11_RaiseHead;
                return Brain_2_Scared::eHoisting_11;
            }
            else
            {
                mCurrentMotion = eFleechMotions::Motion_6_Knockback;
                return field_126_brain_sub_state;
            }
            break;

        case Brain_2_Scared::eHoisting_11:
            if (mCurrentMotion != eFleechMotions::Motion_13_SettleOnGround)
            {
                return field_126_brain_sub_state;
            }
            return Brain_2_Scared::ePatrolArea_9;

        default:
            return field_126_brain_sub_state;
    }
}

s16 Fleech::Brain_3_Death()
{
    field_11C_obj_id = -1;
    MusicController::static_PlayMusic(MusicController::MusicTypes::eNone_0, this, 0, 0);

    if (field_12C_shrivel_timer < static_cast<s32>(sGnFrame + 80))
    {
        mSpriteScale -= FP_FromDouble(0.022);
        mRGB.r -= 2;
        mRGB.g -= 2;
        mRGB.b -= 2;
    }

    if (static_cast<s32>(sGnFrame) < field_12C_shrivel_timer - 24)
    {
        DeathSmokeEffect(false);
    }

    if (mSpriteScale < FP_FromInteger(0))
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }

    return 100;
}
