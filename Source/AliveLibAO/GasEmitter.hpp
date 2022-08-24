#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "Map.hpp"
#include "../relive_lib/BaseGameObject.hpp"

namespace AO {

struct Path_GasEmitter final : public Path_TLV
{
    // No fields
};

class GasEmitter final : public BaseGameObject
{
public:
    GasEmitter(relive::Path_GasEmitter* pTlv, s32 tlvInfo);
    ~GasEmitter();

    virtual void VStopAudio() override;
    virtual void VScreenChanged() override;
    virtual void VUpdate() override;

    s32 field_10_tlvInfo = 0;
    s32 field_14_emit_power = 0;
    FP field_18_xpos = {};
    FP field_1C_ypos = {};
    FP field_20_fp_not_used = {};
};
ALIVE_ASSERT_SIZEOF(GasEmitter, 0x24);

} // namespace AO
