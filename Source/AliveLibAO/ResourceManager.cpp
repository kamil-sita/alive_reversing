#include "stdafx_ao.h"
#include "ResourceManager.hpp"
#include "../relive_lib/Function.hpp"
#include "../relive_lib/GameObjects/Particle.hpp"
#include "../AliveLibAE/stdlib.hpp"
#include "../relive_lib/PsxDisplay.hpp"
#include "../relive_lib/Psx.hpp"
#include "../AliveLibAE/PsxRender.hpp"
#include "GameAutoPlayer.hpp"

namespace AO {

s16 bHideLoadingIcon_5076A0 = 0;
s32 loading_ticks_5076A4 = 0;

void Game_ShowLoadingIcon_445EB0()
{
    AnimResource res = ResourceManagerWrapper::LoadAnimation(AnimId::Loading_Icon2);
    auto pParticle = relive_new Particle(FP_FromInteger(0), FP_FromInteger(0), res);
    if (pParticle)
    {
        pParticle->GetAnimation().SetSemiTrans(false);
        pParticle->GetAnimation().SetBlending(true);

        pParticle->GetAnimation().SetRenderLayer(Layer::eLayer_0);

        // This was doing something odd with OT index.. I think its trying to simulate double buffering by
        // using other parts of the OT while another part is drawn, but it was bugged because it cleared the other anyway
        // on PC it seems fine to just always start at zero.
        PrimHeader* local_ot[42] = {};
        PSX_ClearOTag(local_ot, 42);

        pParticle->GetAnimation().VRender(320, 220, local_ot, 0, 0);

        PSX_DrawOTag(local_ot);

        PSX_ClearOTag(local_ot, 42);

        pParticle->GetAnimation().VRender(320, gPsxDisplay.mHeight + 220, local_ot, 0, 0);

        PSX_DrawOTag(local_ot);

        PSX_PutDispEnv_4F5890();
        pParticle->SetDead(true);
        bHideLoadingIcon_5076A0 = true;
    }
}

void ResourceManager::LoadingLoop(s16)
{
    GetGameAutoPlayer().DisableRecorder();

    /*
    while (gFilesPending_507714 > 0)
    {
        SYS_EventsPump();

        for (s32 i = 0; i < gLoadingFiles->Size(); i++)
        {
            BaseGameObject* pObjIter = gLoadingFiles->ItemAt(i);
            if (!pObjIter)
            {
                break;
            }

            if (!pObjIter->GetDead())
            {
                pObjIter->VUpdate();
            }

            if (pObjIter->GetDead())
            {
                i = gLoadingFiles->RemoveAt(i);
                relive_delete pObjIter;
            }
        }

        Odd_Sleep_48DD90(16u);
        PSX_VSync(0);

        loading_ticks_5076A4++;

        if (bShowLoadingIcon)
        {
            if (!bHideLoadingIcon_5076A0 && loading_ticks_5076A4 > 180)
            {
                Game_ShowLoadingIcon_445EB0();
            }
        }
    }
    */

    GetGameAutoPlayer().EnableRecorder();
}


s32 ResourceManager::SEQ_HashName_454EA0(const char_type* seqFileName)
{
    return ResourceManagerWrapper::SEQ_HashName(seqFileName);
}

} // namespace AO
