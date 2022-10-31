#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "../relive_lib/BaseAnimatedWithPhysicsGameObject.hpp"

class AnimationUnknown;

namespace AO {

class ParamiteWeb final : public BaseAnimatedWithPhysicsGameObject
{
public:
    ParamiteWeb(FP xpos, s32 bottom, s32 top, FP scale);
    ~ParamiteWeb();

    virtual void VUpdate() override;
    virtual void VScreenChanged() override;
    virtual void VRender(PrimHeader** ppOt) override;

public:
    s32 field_D4[4] = {};
    s16 field_E4_number_of_segments = 0;
    s16 field_E6_segment_length = 0;
    s16 field_E8_ttl = 0;
    s16 field_EA_ttl_remainder = 0;
    AnimationUnknown* field_EC_pRes = nullptr;
    s16 field_F0_bEnabled = 0;
};

} // namespace AO
