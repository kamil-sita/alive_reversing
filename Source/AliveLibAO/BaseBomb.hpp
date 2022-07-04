#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "BaseAnimatedWithPhysicsGameObject.hpp"

namespace AO {

class BaseBomb final : public BaseAnimatedWithPhysicsGameObject
{
public:
    BaseBomb(FP xpos, FP ypos, s32 /*unused*/, FP scale);

    void DealDamageRect(const PSX_RECT* pRect);

    virtual void VUpdate() override;

    FP field_E4_scale = {};
};
ALIVE_ASSERT_SIZEOF(BaseBomb, 0xE8);

} // namespace AO
