#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "../relive_lib/BaseGameObject.hpp"
#include "Font.hpp"

class GasCountDown final : public BaseGameObject
{
public:
    GasCountDown(relive::Path_GasCountDown* pTlv, const Guid& tlvId);
    ~GasCountDown();
    
    virtual void VScreenChanged() override;
    virtual void VRender(PrimHeader** ppOt) override;
    virtual void VUpdate() override;

private:
    void DealDamage();

private:
    PalResource mPal;
    FontContext mFontContext = {};
    AliveFont mFont = {};
    Guid mTlvId;
    s16 mGasXPos = 0;
    s16 mGasYPos = 0;
    s16 mStartTimerSwitchId = 0;
    s16 field_72_stop_timer_switch_id = 0;
    s16 mGasTimeLeft = 0;
    u16 field_76_gas_countdown_timer = 0;
};

extern s16 gGasOn;
extern s32 gGasTimer;
