#include "stdafx_ao.h"
#include "GasEmitter.hpp"
#include "../AliveLibAE/stdlib.hpp"
#include "Game.hpp"
#include "Sfx.hpp"
#include "Math.hpp"
#include "Midi.hpp"
#include "GasCountDown.hpp"
#include "../relive_lib/Particle.hpp"
#include "Path.hpp"

namespace AO {

static GasEmitter* sMainGasEmitter = nullptr;
static u32 sGasEmitterAudioMask = 0;

GasEmitter::GasEmitter(relive::Path_GasEmitter* pTlv, const Guid& tlvId)
    : BaseGameObject(true, 0)
{
    SetType(ReliveTypes::eNone);

    mTlvId = tlvId;

    mEmitterXPos = FP_FromInteger(pTlv->mTopLeftX);
    mEmitterYPos = FP_FromInteger(pTlv->mTopLeftY);

    mSmokeScale = FP_FromInteger(1);

    mEmitPower = Math_NextRandom() % 4;
}

GasEmitter::~GasEmitter()
{
    Path::TLV_Reset(mTlvId, -1, 0, 0);

    if (sMainGasEmitter == this)
    {
        sMainGasEmitter = 0;
        SND_Stop_Channels_Mask(sGasEmitterAudioMask);
        sGasEmitterAudioMask = 0;
    }
}

void GasEmitter::VStopAudio()
{
    if (sMainGasEmitter == this)
    {
        sMainGasEmitter = 0;
        SND_Stop_Channels_Mask(sGasEmitterAudioMask);
        sGasEmitterAudioMask = 0;
    }
}

void GasEmitter::VScreenChanged()
{
    SetDead(true);
}

void GasEmitter::VUpdate()
{
    if (gGasOn && !(sGnFrame + mEmitPower % 4))
    {
        New_Smoke_Particles(mEmitterXPos, mEmitterYPos, mSmokeScale, 3, RGB16{ 32, 128, 32 });

        if (!sMainGasEmitter)
        {
            SfxPlayMono(relive::SoundEffects::Gas1, 127);
            sMainGasEmitter = this;
            sGasEmitterAudioMask = SfxPlayMono(relive::SoundEffects::Gas2, 127);
        }
    }
}

} // namespace AO
