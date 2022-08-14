#pragma once

#include "relive_tlvs_serialization.hpp"
#include "../AliveLibAO/SecurityOrb.hpp"
#include "../AliveLibAE/SecurityOrb.hpp"
#include "../AliveLibAE/Path.hpp"
#include "../AliveLibAE/Abe.hpp"
#include "../AliveLibAO/Abe.hpp"
#include "../AliveLibAE/LiftPoint.hpp"
#include "../AliveLibAO/LiftPoint.hpp"
#include "../AliveLibAE/Dove.hpp"
#include "../AliveLibAO/Dove.hpp"
#include "../AliveLibAE/RockSack.hpp"
#include "../AliveLibAO/RockSack.hpp"
#include "../AliveLibAO/ZBall.hpp"
#include "../AliveLibAE/FallingItem.hpp"
#include "../AliveLibAO/FallingItem.hpp"
#include "../AliveLibAO/PullRingRope.hpp"
#include "../AliveLibAE/PullRingRope.hpp"
#include "../AliveLibAO/TimedMine.hpp"
#include "../AliveLibAE/TimedMine.hpp"
#include "../AliveLibAO/HoistRocksEffect.hpp"
#include "../AliveLibAO/TrapDoor.hpp"
#include "../AliveLibAE/TrapDoor.hpp"
#include "../AliveLibAO/LCDScreen.hpp"
#include "../AliveLibAE/LCDScreen.hpp"
#include "../AliveLibAE/Mine.hpp"
#include "../AliveLibAO/Mine.hpp"
#include "../AliveLibAE/InvisibleSwitch.hpp"
#include "../AliveLibAO/InvisibleSwitch.hpp"
#include "../AliveLibAE/ElectricWall.hpp"
#include "../AliveLibAO/ElectricWall.hpp"
#include "../AliveLibAE/BoomMachine.hpp"
#include "../AliveLibAO/BoomMachine.hpp"

// Convert an AO or AE TLV to a relive TLV

namespace relive {

    // also used for AO
    static reliveScale From(const ::Scale_short scale)
    {
        switch (scale)
        {
            case Scale_short::eFull_0:
                return reliveScale::eFull;
            case Scale_short::eHalf_1:
                return reliveScale::eHalf;
        }
        ALIVE_FATAL("Bad scale");
    }

    //static reliveScale From(const ::Scale_int scale)
    //{
    //    switch (scale)
    //    {
    //    case Scale_int::eFull_0:
    //        return reliveScale::eFull;
    //    case Scale_int::eHalf_1:
    //        return reliveScale::eHalf;
    //    }
    //    ALIVE_FATAL("Bad scale");
    //}

    static reliveChoice From(const ::Choice_short choice)
    {
        switch (choice)
        {
        case Choice_short::eNo_0:
            return reliveChoice::eNo;
        case Choice_short::eYes_1:
            return reliveChoice::eYes;
        }
        ALIVE_FATAL("Bad choice");
    }

    static reliveXDirection From(const ::XDirection_short xdirection)
    {
        switch (xdirection)
        {
        case XDirection_short::eLeft_0:
            return reliveXDirection::eLeft;
        case XDirection_short::eRight_1:
            return reliveXDirection::eRight;
        }
        ALIVE_FATAL("Bad x direction");
    }

    static reliveSwitchOp From(const AO::SwitchOp op)
    {
        switch (op)
        {
            case AO::SwitchOp::eSetTrue_0:
                return reliveSwitchOp::eSetTrue;
            case AO::SwitchOp::eSetFalse_1:
                return reliveSwitchOp::eSetFalse;
            case AO::SwitchOp::eToggle_2:
                return reliveSwitchOp::eToggle;
            case AO::SwitchOp::eIncrement_3:
                return reliveSwitchOp::eIncrement;
            case AO::SwitchOp::eDecrement_4:
                return reliveSwitchOp::eDecrement;
        }
        ALIVE_FATAL("Bad switch operator");
    }

    static reliveSwitchOp From(const ::SwitchOp op)
    {
        switch (op)
        {
        case ::SwitchOp::eSetTrue_0:
            return reliveSwitchOp::eSetTrue;
        case ::SwitchOp::eSetFalse_1:
            return reliveSwitchOp::eSetFalse;
        case ::SwitchOp::eToggle_2:
            return reliveSwitchOp::eToggle;
        case ::SwitchOp::eIncrement_3:
            return reliveSwitchOp::eIncrement;
        case ::SwitchOp::eDecrement_4:
            return reliveSwitchOp::eDecrement;
        }
        ALIVE_FATAL("Bad switch operator");
    }

class Path_ShadowZone_Converter
{
public:
    static Path_ShadowZone From(const AO::Path_ShadowZone& tlv)
    {
        Path_ShadowZone r;
        r.mRGB.SetRGB(tlv.field_1C_r, tlv.field_1E_g, tlv.field_20_b);
        r.mScale = From(tlv.field_24_scale);
        return r;
    }

    static Path_ShadowZone From(const ::Path_ShadowZone& tlv)
    {
        Path_ShadowZone r;
        r.mRGB.SetRGB(tlv.field_14_r, tlv.field_16_g, tlv.field_18_b);
        r.mScale = From(tlv.field_1C_scale);
        return r;
    }

private:
    static Path_ShadowZone::Scale From(::ShadowZoneScale aeScale)
    {
        switch (aeScale)
        {
            case ::ShadowZoneScale::eHalf_1:
                return Path_ShadowZone::Scale::eHalf;
            case ::ShadowZoneScale::eFull_2:
                return Path_ShadowZone::Scale::eFull;
            case ::ShadowZoneScale::eBoth_0:
                return Path_ShadowZone::Scale::eBoth;
        }
        ALIVE_FATAL("Bad AE shadow scale");
    }

    static Path_ShadowZone::Scale From(AO::ShadowZoneScale aoScale)
    {
        switch (aoScale)
        {
            case AO::ShadowZoneScale::eHalf_1:
                return Path_ShadowZone::Scale::eHalf;
            case AO::ShadowZoneScale::eFull_2:
                return Path_ShadowZone::Scale::eFull;
            case AO::ShadowZoneScale::eBoth_0:
                return Path_ShadowZone::Scale::eBoth;
        }
        ALIVE_FATAL("Bad AO shadow scale");
    }
};

class Path_SecurityOrb_Converter
{
public:
    static Path_SecurityOrb From(const AO::Path_SecurityOrb& tlv)
    {
        Path_SecurityOrb r;
        r.mScale = relive::From(tlv.mScale);
        r.mDisabledResources = tlv.mDisabledResources;
        return r;
    }

    static Path_SecurityOrb From(const ::Path_SecurityOrb& tlv)
    {
        Path_SecurityOrb r;
        r.mScale = relive::From(tlv.mScale);
        r.mDisabledResources = tlv.mDisabledResources;
        return r;
    }
};

class Path_ContinuePoint_Converter
{
public:
    static Path_ContinuePoint From(const AO::Path_ContinuePoint& tlv)
    {
        Path_ContinuePoint r;
        r.field_18_zone_number = tlv.field_18_zone_number;
        r.field_1A_clear_from_id = tlv.field_1A_clear_from_id;
        r.field_1C_clear_to_id = tlv.field_1C_clear_to_id;
        r.field_1E_elum_restarts = relive::From(tlv.field_1E_elum_restarts);
        r.field_20_abe_direction = From(tlv.field_20_abe_direction);
        return r;
    }

    static Path_ContinuePoint From(const ::Path_ContinuePoint& tlv)
    {
        Path_ContinuePoint r;
        r.field_10_scale = From(tlv.field_10_scale);
        r.field_12_save_file_id = tlv.field_12_save_file_id;
        return r;
    }

private:
    static relive::Path_ContinuePoint::spawnDirection From(AO::Path_ContinuePoint::spawnDirection spawnDirection)
    {
        switch (spawnDirection)
        {
            case AO::Path_ContinuePoint::spawnDirection::eRight_0:
                return relive::Path_ContinuePoint::spawnDirection::eRight;
            case AO::Path_ContinuePoint::spawnDirection::eLeft_1:
                return relive::Path_ContinuePoint::spawnDirection::eLeft;
        }
        ALIVE_FATAL("Bad spawn direction");
    }

    static relive::Path_ContinuePoint::Scale From(::Path_ContinuePoint::Scale scale)
    {
        switch (scale)
        {
            case ::Path_ContinuePoint::Scale::eNone_0:
                return relive::Path_ContinuePoint::Scale::eNone;
            case ::Path_ContinuePoint::Scale::eHalf_1:
                return relive::Path_ContinuePoint::Scale::eHalf;
            case ::Path_ContinuePoint::Scale::eFull_2:
                return relive::Path_ContinuePoint::Scale::eFull;
        }
        ALIVE_FATAL("Bad scale");
    }
};

class Path_LiftPoint_Converter
{
public:
    static Path_LiftPoint From(const AO::Path_LiftPoint& tlv)
    {
        Path_LiftPoint r;
        r.field_10_lift_point_id = tlv.field_18_lift_point_id;
        r.field_12_bStart_point = relive::From(tlv.field_1A_bstart_point);
        r.field_16_lift_point_stop_type = From(tlv.field_1E_lift_point_stop_type);
        r.field_18_scale = relive::From(tlv.field_20_scale);
        r.field_1A_bIgnore_lift_mover = relive::From(tlv.field_22_bIgnore_lift_mover);
        return r;
    }

    static Path_LiftPoint From(const ::Path_LiftPoint& tlv)
    {
        Path_LiftPoint r;
        r.field_10_lift_point_id = tlv.field_10_lift_point_id;
        r.field_12_bStart_point = relive::From(tlv.field_12_bStart_point);
        r.field_16_lift_point_stop_type = From(tlv.field_16_lift_point_stop_type);
        r.field_18_scale = relive::From(tlv.field_18_scale);
        r.field_1A_bIgnore_lift_mover = relive::From(tlv.field_1A_bIgnore_lift_mover);
        return r;
    }

private:
    static relive::Path_LiftPoint::LiftPointStopType From(AO::LiftPointStopType stopType)
    {
        switch (stopType)
        {
            case AO::LiftPointStopType::eTopFloor_0:
                return relive::Path_LiftPoint::LiftPointStopType::eTopFloor;
            case AO::LiftPointStopType::eBottomFloor_1:
                return relive::Path_LiftPoint::LiftPointStopType::eBottomFloor;
            case AO::LiftPointStopType::eMiddleFloor_2:
                return relive::Path_LiftPoint::LiftPointStopType::eMiddleFloor;
            case AO::LiftPointStopType::eMiddleLockFloor_3:
                return relive::Path_LiftPoint::LiftPointStopType::eMiddleLockFloor;
            case AO::LiftPointStopType::eStartPointOnly_4:
                return relive::Path_LiftPoint::LiftPointStopType::eStartPointOnly;
        }
        ALIVE_FATAL("Bad lift point stop type");
    }

    static relive::Path_LiftPoint::LiftPointStopType From(::LiftPointStopType stopType)
    {
        switch (stopType)
        {
            case ::LiftPointStopType::eTopFloor_0:
                return relive::Path_LiftPoint::LiftPointStopType::eTopFloor;
            case ::LiftPointStopType::eBottomFloor_1:
                return relive::Path_LiftPoint::LiftPointStopType::eBottomFloor;
            case ::LiftPointStopType::eMiddleFloor_2:
                return relive::Path_LiftPoint::LiftPointStopType::eMiddleFloor;
            case ::LiftPointStopType::eMiddleLockFloor_3:
                return relive::Path_LiftPoint::LiftPointStopType::eMiddleLockFloor;
            case ::LiftPointStopType::eStartPointOnly_4:
                return relive::Path_LiftPoint::LiftPointStopType::eStartPointOnly;
        }
        ALIVE_FATAL("Bad lift point stop type");
    }
};

class Path_Dove_Converter
{
public:
    static Path_Dove From(const AO::Path_Dove& tlv)
    {
        Path_Dove r;
        r.mDoveCount = tlv.mDoveCount;
        r.mPixelPerfect = relive::From(tlv.mPixelPerfect);
        r.mScale = relive::From(tlv.mScale);
        return r;
    }

    static Path_Dove From(const ::Path_Dove& tlv)
    {
        Path_Dove r;
        r.mDoveCount = tlv.mDoveCount;
        r.mPixelPerfect = relive::From(tlv.mPixelPerfect);
        r.mScale = relive::From(tlv.mScale);
        return r;
    }
};

class Path_RockSack_Converter
{
public:
    static Path_RockSack From(const AO::Path_RockSack& tlv)
    {
        Path_RockSack r;
        r.field_10_fall_direction = relive::From(tlv.field_18_fall_direction);
        r.field_12_x_vel = tlv.field_1A_x_vel;
        r.field_14_y_vel = tlv.field_1C_y_vel;
        r.field_16_scale = relive::From(tlv.field_1E_scale);
        r.field_18_rock_amount = tlv.field_20_rock_amount;
        return r;
    }

    static Path_RockSack From(const ::Path_RockSack& tlv)
    {
        Path_RockSack r;
        r.field_10_fall_direction = relive::From(tlv.field_10_fall_direction);
        r.field_12_x_vel = tlv.field_12_x_vel;
        r.field_14_y_vel = tlv.field_14_y_vel;
        r.field_16_scale = relive::From(tlv.field_16_scale);
        r.field_18_rock_amount = tlv.field_18_rock_amount;
        return r;
    }
};

class Path_ZBall_Converter
{
public:
    static Path_ZBall From(const AO::Path_ZBall& tlv)
    {
        Path_ZBall r;
        r.mStartPos = From(tlv.mStartPos);
        r.mScale = relive::From(tlv.mScale);
        r.mSpeed = From(tlv.mSpeed);
        return r;
    }

private:
    static relive::Path_ZBall::StartPos From(AO::Path_ZBall::StartPos startPos)
    {
        switch (startPos)
        {
            case AO::Path_ZBall::StartPos::eCenter_0:
                return relive::Path_ZBall::StartPos::eCenter;
            case AO::Path_ZBall::StartPos::eOut_1:
                return relive::Path_ZBall::StartPos::eOut;
            case AO::Path_ZBall::StartPos::eIn_2:
                return relive::Path_ZBall::StartPos::eIn;
        }
        ALIVE_FATAL("Bad start pos");
    }

    static relive::Path_ZBall::Speed From(AO::Path_ZBall::Speed speed)
    {
        switch (speed)
        {
            case AO::Path_ZBall::Speed::eNormal_0:
                return relive::Path_ZBall::Speed::eNormal;
            case AO::Path_ZBall::Speed::eFast_1:
                return relive::Path_ZBall::Speed::eFast;
            case AO::Path_ZBall::Speed::eSlow_2:
                return relive::Path_ZBall::Speed::eSlow;
        }
        ALIVE_FATAL("Bad speed");
    }
};

class Path_FallingItem_Converter
{
public:
    static Path_FallingItem From(const AO::Path_FallingItem& tlv)
    {
        Path_FallingItem r;
        r.mSwitchId = tlv.field_18_switch_id;
        r.mScale = relive::From(tlv.field_1A_scale);
        r.mFallInterval = tlv.field_1C_fall_interval;
        r.mMaxFallingItems = tlv.field_1E_max_falling_items;
        r.mResetSwitchIdAfterUse = relive::From(tlv.field_20_reset_switch_id_after_use);
        return r;
    }

    static Path_FallingItem From(const ::Path_FallingItem& tlv)
    {
        Path_FallingItem r;
        r.mSwitchId = tlv.field_10_switch_id;
        r.mScale = relive::From(tlv.field_12_scale);
        r.mFallInterval = tlv.field_14_fall_interval;
        r.mMaxFallingItems = tlv.field_16_max_falling_items;
        r.mResetSwitchIdAfterUse = relive::From(tlv.field_18_reset_switch_id_after_use);
        return r;
    }
};

class Path_PullRingRope_Converter
{
public:
    static Path_PullRingRope From(const AO::Path_PullRingRope& tlv)
    {
        Path_PullRingRope r;
        r.mSwitchId = tlv.field_18_switch_id;
        r.mAction = relive::From(tlv.field_1A_action);
        r.mRopeLength = tlv.field_1C_rope_length;
        r.mScale = relive::From(tlv.field_1E_scale);
        r.mOnSound = From(tlv.field_20_on_sound);
        r.mOffSound = From(tlv.field_22_off_sound);
        r.mSoundDirection = From(tlv.field_24_sound_direction);
        return r;
    }

    static Path_PullRingRope From(const ::Path_PullRingRope& tlv)
    {
        Path_PullRingRope r;
        r.mSwitchId = tlv.field_10_switch_id;
        r.mAction = relive::From(tlv.field_12_action);
        r.mRopeLength = tlv.field_14_rope_length;
        r.mScale = relive::From(tlv.field_16_scale);
        r.mOnSound = From(tlv.field_18_on_sound);
        r.mOffSound = From(tlv.field_1A_off_sound);
        r.mSoundDirection = From(tlv.field_1C_sound_direction);
        return r;
    }

private:
    static relive::Path_PullRingRope::PullRingSwitchSound From(AO::PullRingSwitchSound switchSound)
    {
        switch (switchSound)
        {
            case AO::PullRingSwitchSound::eNone_0:
                return relive::Path_PullRingRope::PullRingSwitchSound::eNone;
            case AO::PullRingSwitchSound::eWellExit_1:
                return relive::Path_PullRingRope::PullRingSwitchSound::eWellExit;
            case AO::PullRingSwitchSound::RingBellHammer_2:
                return relive::Path_PullRingRope::PullRingSwitchSound::RingBellHammer;
            case AO::PullRingSwitchSound::eDoorEffect_3:
                return relive::Path_PullRingRope::PullRingSwitchSound::eDoorEffect;
        }
        ALIVE_FATAL("Bad pull ring switch sound");
    }

    static relive::Path_PullRingRope::PullRingSoundDirection From(AO::PullRingSoundDirection soundDir)
    {
        switch (soundDir)
        {
            case AO::PullRingSoundDirection::eLeftAndRight_0:
                return relive::Path_PullRingRope::PullRingSoundDirection::eLeftAndRight;
            case AO::PullRingSoundDirection::eLeft_1:
                return relive::Path_PullRingRope::PullRingSoundDirection::eLeft;
            case AO::PullRingSoundDirection::eRight_2:
                return relive::Path_PullRingRope::PullRingSoundDirection::eRight;
        }
        ALIVE_FATAL("Bad pull ring sound direction");
    }

    static relive::Path_PullRingRope::PullRingSwitchSound From(::PullRingSwitchSound switchSound)
    {
        switch (switchSound)
        {
        case ::PullRingSwitchSound::eNone_0:
            return relive::Path_PullRingRope::PullRingSwitchSound::eNone;
        case ::PullRingSwitchSound::eWellExit_1:
            return relive::Path_PullRingRope::PullRingSwitchSound::eWellExit;
        case ::PullRingSwitchSound::eRingBellHammer_2:
            return relive::Path_PullRingRope::PullRingSwitchSound::RingBellHammer;
        case ::PullRingSwitchSound::eDoorEffect_3:
            return relive::Path_PullRingRope::PullRingSwitchSound::eDoorEffect;
        }
        ALIVE_FATAL("Bad pull ring switch sound");
    }

    static relive::Path_PullRingRope::PullRingSoundDirection From(::PullRingSoundDirection soundDir)
    {
        switch (soundDir)
        {
        case ::PullRingSoundDirection::eLeftAndRight_0:
            return relive::Path_PullRingRope::PullRingSoundDirection::eLeftAndRight;
        case ::PullRingSoundDirection::eLeft_1:
            return relive::Path_PullRingRope::PullRingSoundDirection::eLeft;
        case ::PullRingSoundDirection::eRight_2:
            return relive::Path_PullRingRope::PullRingSoundDirection::eRight;
        }
        ALIVE_FATAL("Bad pull ring sound direction");
    }
};

class Path_TimedMine_Converter
{
public:
    static Path_TimedMine From(const AO::Path_TimedMine& tlv)
    {
        Path_TimedMine r;
        r.mSwitchId = tlv.field_18_switch_id;
        r.mState = tlv.field_1A_state;
        r.mScale = relive::From(tlv.field_1C_scale);
        r.mTicksUntilExplosion = tlv.mTicksUntilExplosion;
        r.mDisabledResources = tlv.mDisabledResources;
        return r;
    }

    static Path_TimedMine From(const ::Path_TimedMine& tlv)
    {
        Path_TimedMine r;
        r.mSwitchId = tlv.field_10_switch_id;
        r.mState = tlv.field_12_state;
        r.mScale = relive::From(tlv.field_14_scale);
        r.mTicksUntilExplosion = tlv.mTicksUntilExplosion;
        r.mDisabledResources = tlv.mDisabledResources;
        return r;
    }
};

class Path_Hoist_Converter
{
public:
    static Path_Hoist From(const AO::Path_Hoist& tlv)
    {
        Path_Hoist r;
        r.mHoistType = From(tlv.field_18_hoist_type);
        r.mGrabDirection= From(tlv.field_1A_grab_direction);
        return r;
    }

    static Path_Hoist From(const ::Path_Hoist& tlv)
    {
        Path_Hoist r;
        r.mHoistType = From(tlv.field_10_type);
        r.mGrabDirection = From(tlv.field_12_grab_direction);
        return r;
    }

private:
    static relive::Path_Hoist::Type From(AO::Path_Hoist::Type type)
    {
        switch (type)
        {
        case AO::Path_Hoist::Type::eNextFloor:
            return relive::Path_Hoist::Type::eNextFloor;
        case AO::Path_Hoist::Type::eNextEdge:
            return relive::Path_Hoist::Type::eNextEdge;
        case AO::Path_Hoist::Type::eOffScreen:
            return relive::Path_Hoist::Type::eOffScreen;
        }
        ALIVE_FATAL("Bad hoist type");
    }

    static relive::Path_Hoist::Type From(::Path_Hoist::Type type)
    {
        switch (type)
        {
        case ::Path_Hoist::Type::eNextFloor:
            return relive::Path_Hoist::Type::eNextFloor;
        case ::Path_Hoist::Type::eNextEdge:
            return relive::Path_Hoist::Type::eNextEdge;
        case ::Path_Hoist::Type::eOffScreen:
            return relive::Path_Hoist::Type::eOffScreen;
        }
        ALIVE_FATAL("Bad hoist type");
    }

    static relive::Path_Hoist::GrabDirection From(AO::Path_Hoist::GrabDirection grabDir)
    {
        switch (grabDir)
        {
        case AO::Path_Hoist::GrabDirection::eFacingLeft:
            return relive::Path_Hoist::GrabDirection::eFacingLeft;
        case AO::Path_Hoist::GrabDirection::eFacingRight:
            return relive::Path_Hoist::GrabDirection::eFacingRight;
        case AO::Path_Hoist::GrabDirection::eFacingAnyDirection:
            return relive::Path_Hoist::GrabDirection::eFacingAnyDirection;
        }
        ALIVE_FATAL("Bad hoist grab direction");
    }

    static relive::Path_Hoist::GrabDirection From(::Path_Hoist::GrabDirection grabDir)
    {
        switch (grabDir)
        {
        case ::Path_Hoist::GrabDirection::eFacingLeft:
            return relive::Path_Hoist::GrabDirection::eFacingLeft;
        case ::Path_Hoist::GrabDirection::eFacingRight:
            return relive::Path_Hoist::GrabDirection::eFacingRight;
        case ::Path_Hoist::GrabDirection::eFacingAnyDirection:
            return relive::Path_Hoist::GrabDirection::eFacingAnyDirection;
        }
        ALIVE_FATAL("Bad hoist grab direction");
    }
};

class Path_TrapDoor_Converter
{
public:
    static Path_TrapDoor From(const AO::Path_TrapDoor& tlv)
    {
        Path_TrapDoor r;
        r.mSwitchId = tlv.mSwitchId;
        r.mStartState = From(tlv.mStartState);
        r.mSelfClosing = relive::From(tlv.field_1C_self_closing);
        r.mScale = relive::From(tlv.field_1E_scale);
        r.mDirection = relive::From(tlv.field_22_direction);
        r.field_1C_xOff = tlv.field_24_xOff;
        return r;
    }

    static Path_TrapDoor From(const ::Path_TrapDoor& tlv)
    {
        Path_TrapDoor r;
        r.mSwitchId = tlv.mSwitchId;
        r.mStartState = From(tlv.mStartState);
        r.mSelfClosing = relive::From(tlv.mSelfClosing);
        r.mScale = relive::From(tlv.field_16_scale);
        r.mDirection = relive::From(tlv.mDirection);
        r.field_1C_xOff = tlv.field_1C_xOff;
        r.mStayOpenTime = tlv.mStayOpenTime;
        return r;
    }

private:
    static relive::Path_TrapDoor::StartState From(AO::Path_TrapDoor::StartState startState)
    {
        switch (startState)
        {
            case AO::Path_TrapDoor::StartState::eOpen_0:
                return relive::Path_TrapDoor::StartState::eOpen;
            case AO::Path_TrapDoor::StartState::eClosed_1:
                return relive::Path_TrapDoor::StartState::eClosed;
        }
        ALIVE_FATAL("Bad trap door start state");
    }

    static relive::Path_TrapDoor::StartState From(::Path_TrapDoor::StartState startState)
    {
        switch (startState)
        {
        case ::Path_TrapDoor::StartState::eOpen_0:
            return relive::Path_TrapDoor::StartState::eOpen;
        case ::Path_TrapDoor::StartState::eClosed_1:
            return relive::Path_TrapDoor::StartState::eClosed;
        }
        ALIVE_FATAL("Bad trap door start state");
    }
};

class Path_LCDScreen_Converter
{
public:
    static Path_LCDScreen From(const AO::Path_LCDScreen& tlv)
    {
        Path_LCDScreen r;
        r.field_10_message_1_id = tlv.field_18_message_1_id;
        r.field_12_message_rand_min_id = tlv.field_1A_message_rand_min;
        r.field_14_message_rand_max_id = tlv.field_1C_message_rand_max;
        return r;
    }

    static Path_LCDScreen From(const ::Path_LCDScreen& tlv)
    {
        Path_LCDScreen r;
        r.field_10_message_1_id = tlv.field_10_message_1_id;
        r.field_12_message_rand_min_id = tlv.field_12_message_rand_min_id;
        r.field_14_message_rand_max_id = tlv.field_14_message_rand_max_id;
        r.field_16_message_2_id = tlv.field_16_message_2_id;
        r.field_18_toggle_message_switch_id = tlv.field_18_toggle_message_switch_id;
        return r;
    }
};

class Path_Mine_Converter
{
public:
    static Path_Mine From(const AO::Path_Mine& tlv)
    {
        Path_Mine r;
        r.field_10_num_patterns = tlv.field_18_num_patterns;
        r.field_12_pattern= tlv.field_1A_pattern;
        r.field_14_scale = relive::From(tlv.field_1C_scale);
        r.field_16_disabled_resources = tlv.field_1E_disabled_resources;
        r.field_18_persist_offscreen = relive::From(tlv.field_20_persists_offscreen);
        return r;
    }

    static Path_Mine From(const ::Path_Mine& tlv)
    {
        Path_Mine r;
        r.field_10_num_patterns = tlv.field_10_num_patterns;
        r.field_12_pattern = tlv.field_12_pattern;
        r.field_14_scale = relive::From(tlv.field_14_scale);
        r.field_16_disabled_resources = tlv.field_16_disabled_resources;
        r.field_18_persist_offscreen = relive::From(tlv.field_18_persist_offscreen);
        return r;
    }
};

class Path_InvisibleSwitch_Converter
{
public:
    static Path_InvisibleSwitch From(const AO::Path_InvisibleSwitch& tlv)
    {
        Path_InvisibleSwitch r;
        r.field_10_switch_id = tlv.field_18_switch_id;
        r.field_12_action = relive::From(tlv.field_1A_action);
        r.field_14_delay = tlv.field_1C_delay;
        r.field_16_set_off_alarm = relive::From(tlv.field_1E_set_off_alarm);
        r.field_18_scale = From(tlv.field_20_scale);
        return r;
    }

    static Path_InvisibleSwitch From(const ::Path_InvisibleSwitch& tlv)
    {
        Path_InvisibleSwitch r;
        r.field_10_switch_id = tlv.field_10_switch_id;
        r.field_12_action = relive::From(tlv.field_12_action);
        r.field_14_delay = tlv.field_14_delay;
        r.field_16_set_off_alarm = relive::From(tlv.field_16_set_off_alarm);
        r.field_18_scale = From(tlv.field_18_scale);
        return r;
    }

private:
    static relive::Path_InvisibleSwitch::InvisibleSwitchScale From(AO::InvisibleSwitchScale scale)
    {
        switch (scale)
        {
            case AO::InvisibleSwitchScale::eHalf_0:
                return relive::Path_InvisibleSwitch::InvisibleSwitchScale::eHalf;
            case AO::InvisibleSwitchScale::eFull_1:
                return relive::Path_InvisibleSwitch::InvisibleSwitchScale::eFull;
            case AO::InvisibleSwitchScale::eAny_2:
                return relive::Path_InvisibleSwitch::InvisibleSwitchScale::eAny;
        }
        ALIVE_FATAL("Bad invisible switch scale");
    }

    static relive::Path_InvisibleSwitch::InvisibleSwitchScale From(::InvisibleSwitchScale scale)
    {
        switch (scale)
        {
        case ::InvisibleSwitchScale::eHalf_0:
            return relive::Path_InvisibleSwitch::InvisibleSwitchScale::eHalf;
        case ::InvisibleSwitchScale::eFull_1:
            return relive::Path_InvisibleSwitch::InvisibleSwitchScale::eFull;
        case ::InvisibleSwitchScale::eAny_2:
            return relive::Path_InvisibleSwitch::InvisibleSwitchScale::eAny;
        }
        ALIVE_FATAL("Bad invisible switch scale");
    }
};


class Path_ElectricWall_Converter
{
public:
    static Path_ElectricWall From(const AO::Path_ElectricWall& tlv)
    {
        Path_ElectricWall r;
        r.field_10_scale = relive::From(tlv.field_18_scale);
        r.field_12_switch_id = tlv.field_1A_switch_id;
        r.field_14_start_state = From(tlv.field_1C_start_state);
        return r;
    }

    static Path_ElectricWall From(const ::Path_ElectricWall& tlv)
    {
        Path_ElectricWall r;
        r.field_10_scale = relive::From(tlv.field_10_scale);
        r.field_12_switch_id = tlv.field_12_switch_id;
        r.field_14_start_state = From(tlv.field_14_start_state);
        return r;
    }

private:
    static relive::Path_ElectricWall::ElectricWallStartState From(AO::ElectricWallStartState startState)
    {
        switch (startState)
        {
        case AO::ElectricWallStartState::eOff_0:
            return relive::Path_ElectricWall::ElectricWallStartState::eOff;
        case AO::ElectricWallStartState::eOn_1:
            return relive::Path_ElectricWall::ElectricWallStartState::eOn;
        }
        ALIVE_FATAL("Bad electric wall start state");
    }

    static relive::Path_ElectricWall::ElectricWallStartState From(::ElectricWallStartState startState)
    {
        switch (startState)
        {
        case ::ElectricWallStartState::eOff_0:
            return relive::Path_ElectricWall::ElectricWallStartState::eOff;
        case ::ElectricWallStartState::eOn_1:
            return relive::Path_ElectricWall::ElectricWallStartState::eOn;
        }
        ALIVE_FATAL("Bad electric wall start state");
    }
};

class Path_BoomMachine_Converter
{
public:
    static Path_BoomMachine From(const AO::Path_BoomMachine& tlv)
    {
        Path_BoomMachine r;
        r.field_10_scale = relive::From(tlv.field_18_scale);
        r.field_12_nozzle_side = From(tlv.field_1A_nozzle_side);
        r.field_14_disabled_resources = tlv.field_1C_disabled_resources;
        r.field_16_number_of_grenades = tlv.field_1E_number_of_grenades;
        return r;
    }

    static Path_BoomMachine From(const ::Path_BoomMachine& tlv)
    {
        Path_BoomMachine r;
        r.field_10_scale = relive::From(tlv.field_10_scale);
        r.field_12_nozzle_side = From(tlv.field_12_nozzle_side);
        r.field_14_disabled_resources = tlv.field_14_disabled_resources;
        r.field_16_number_of_grenades = tlv.field_16_number_of_grenades;
        return r;
    }

private:
    static relive::Path_BoomMachine::NozzleSide From(AO::Path_BoomMachine::NozzleSide nozzleSide)
    {
        switch (nozzleSide)
        {
        case AO::Path_BoomMachine::NozzleSide::eRight_0:
            return relive::Path_BoomMachine::NozzleSide::eRight;
        case AO::Path_BoomMachine::NozzleSide::eLeft_1:
            return relive::Path_BoomMachine::NozzleSide::eLeft;
        }
        ALIVE_FATAL("Bad boom machine nozzle side");
    }

    static relive::Path_BoomMachine::NozzleSide From(::Path_BoomMachine::NozzleSide nozzleSide)
    {
        switch (nozzleSide)
        {
        case ::Path_BoomMachine::NozzleSide::eRight_0:
            return relive::Path_BoomMachine::NozzleSide::eRight;
        case ::Path_BoomMachine::NozzleSide::eLeft_1:
            return relive::Path_BoomMachine::NozzleSide::eLeft;
        }
        ALIVE_FATAL("Bad boom machine nozzle side");
    }
};

} // namespace relive
