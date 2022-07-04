#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "../relive_lib/BaseGameObject.hpp"
#include "Layer.hpp"

namespace AO {

class DeathGas final : public BaseGameObject
{
public:
    DeathGas(Layer layer, s32 amount);
    ~DeathGas();

    virtual void VUpdate() override;
    virtual void VScreenChanged() override;
    virtual void VRender(PrimHeader** ppOt) override;

    s16 field_10_total = 0;
    s16 field_12_unused = 0;
    s16 field_14_amount = 0;
    s16 field_16_flag = 0;
    Layer field_18_layer = Layer::eLayer_0;
    s16 field_1A = 0;
    s16 field_1C = 0;
    s16 field_1E = 0;
};
ALIVE_ASSERT_SIZEOF(DeathGas, 0x20);

} // namespace AO
