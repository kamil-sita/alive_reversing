#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "../relive_lib/EffectBase.hpp"
#include "../relive_lib/Layer.hpp"

namespace AO {

class DeathFadeOut final : public EffectBase
{
public:
    DeathFadeOut(Layer layer, s32 direction, bool destroyOnDone, s32 speed, TPageAbr abr);

    void Init(Layer layer, s16 direction, s16 destroyOnDone, s32 speed);
    virtual void VScreenChanged() override;
    virtual void VUpdate() override;
    virtual void VRender(PrimHeader** ppOt) override;


private:
    s16 field_68_current_fade_rgb = 0;
    s16 field_6A_speed = 0;
    s16 field_6C_direction = 0;

public:
    s16 field_6E_bDone = 0;

private:
    s16 field_70_destroy_on_done = 0;
    s16 field_72 = 0;
};

} // namespace AO
