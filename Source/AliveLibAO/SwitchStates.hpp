#pragma once

#include "../AliveLibCommon/Function.hpp"

namespace AO {

struct SwitchStates final
{
    s8 mData[256];
};

void SwitchStates_Set(u16 idx, s8 value);
s16 SwitchStates_Get(u16 idx);

enum class SwitchOp : s16
{
    eSetTrue_0 = 0,
    eSetFalse_1 = 1,
    eToggle_2 = 2,
    eIncrement_3 = 3,
    eDecrement_4 = 4,
};

void SwitchStates_Do_Operation(s16 idx, relive::reliveSwitchOp operation);

void SwitchStates_Add(u16 idx, s8 value);
void SwitchStates_ClearAll();

ALIVE_VAR_EXTERN(SwitchStates, sSwitchStates_505568);

} // namespace AO
