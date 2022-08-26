#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "BaseAliveGameObject.hpp"
#include "../relive_lib/Animation.hpp"
#include "PlatformBase.hpp"
#include "Map.hpp"
#include "../AliveLibAE/Path.hpp"
#include "../relive_lib/data_conversion/relive_tlvs.hpp"

namespace AO {

enum class LiftPointStopType : s16
{
    eTopFloor_0 = 0,
    eBottomFloor_1 = 1,
    eMiddleFloor_2 = 2,
    eMiddleLockFloor_3 = 3,
    eStartPointOnly_4 = 4,
};

struct Path_Pulley final : public Path_TLV
{
    Scale_int scale;
};

struct Path_LiftPoint final : public Path_TLV
{
    s16 mLiftPointId;
    Choice_short mIsStartPoint;
    s16 field_1C_lift_type;
    LiftPointStopType mLiftPointStopType;
    Scale_short mScale;
    Choice_short mIgnoreLiftMover;
};

class Rope;

class LiftPoint final : public PlatformBase
{
public:
    enum Flags
    {
        // These have been shuffled around compared to AE for more pain
        eBit1 = 0x1, // Not used ?
        eBit2_bTopFloor = 0x2,
        eBit3_bMiddleFloor = 0x4,
        eBit4_bBottomFloor = 0x8,
        eBit5_bHasPulley = 0x10,
        eBit6_bMoveToFloorLevel = 0x20,
        eBit7_bIgnoreLiftMover = 0x40,
        eBit8_KeepOnMiddleFloor = 0x80,
    };
    LiftPoint(relive::Path_LiftPoint* pTlv, Map* pPath, const TLVUniqueId& tlvId);
    ~LiftPoint();

    void Move(FP xSpeed, FP ySpeed, s32 not_used);

    void StayOnFloor(s16 floor, relive::Path_LiftPoint* pTlv);

    void Sub_Unknown(relive::Path_TLV* pTlv);

    // flags & 0x2 && !flags & 0x20
    bool OnTopFloor() const;

    // flags & 0x8 && !flags & 0x20
    bool OnBottomFloor() const;

    // flags & 4 && !(flags & 0x20);
    bool OnMiddleFloor() const;

    // flags & 2 && !(flags & 0x20); // OnTopFloor
    // flags & 4 && !(flags & 0x20); // OnMiddleFloor
    // flags & 8 && !(flags & 0x20); // OnBottomFloor
    bool OnAnyFloor() const;

    bool OnAFloorLiftMoverCanUse() const;

    virtual void VUpdate() override;
    virtual void VRender(PrimHeader** ppOt) override;
    virtual void VScreenChanged() override;

    void CreatePulleyIfExists(s16 camX, s16 camY);

    s16 field_12C_bMoving = 0;
    s16 field_12E = 0;
    relive::Path_LiftPoint::LiftPointStopType mLiftPointStopType = relive::Path_LiftPoint::LiftPointStopType::eTopFloor;
    s16 field_132 = 0;
    Rope* field_134_pRope2 = nullptr;
    Rope* field_138_pRope1 = nullptr;
    Animation field_13C_lift_wheel;
    Animation field_1D4_pulley_anim;
    s16 field_26C_pulley_xpos = 0;
    s16 field_26E_pulley_ypos = 0;
    FP field_270_floorYLevel = {};
    u8** field_274_ppRes = nullptr;
    s16 field_278_lift_point_id = 0;
    BitField16<Flags> field_27A_flags = {};
};

ALIVE_ASSERT_SIZEOF(LiftPoint, 0x27C);

} // namespace AO
