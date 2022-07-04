#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "BaseAnimatedWithPhysicsGameObject.hpp"
#include "Map.hpp"
#include "../AliveLibAE/Path.hpp"

namespace AO {

struct Path_ZBall final : public Path_TLV
{
    enum class StartPos : s16
    {
        eCenter_0 = 0,
        eOut_1 = 1,
        eIn_2 = 2
    };

    enum class Speed : s16
    {
        eNormal_0 = 0,
        eFast_1 = 1,
        eSlow_2 = 2
    };

    StartPos field_18_start_pos;
    Scale_short field_1A_scale;
    Speed field_1C_speed;
    s16 field_1E_pad;
};
ALIVE_ASSERT_SIZEOF_ALWAYS(Path_ZBall, 0x20);

class ZBall final : public BaseAnimatedWithPhysicsGameObject
{
public:
    ZBall(Path_ZBall* pTlv, s32 tlvInfo);

    virtual void VUpdate() override;

    s32 field_E4_tlvInfo = 0;
    s16 field_E8_bFrameAbove12 = 0;
    s16 field_EA_sound_pitch = 0;
};
ALIVE_ASSERT_SIZEOF(ZBall, 0xEC);

} // namespace AO
