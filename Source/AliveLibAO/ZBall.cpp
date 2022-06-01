#include "stdafx_ao.h"
#include "Function.hpp"
#include "ZBall.hpp"
#include "ResourceManager.hpp"
#include "stdlib.hpp"
#include "Events.hpp"
#include "Sfx.hpp"
#include "BaseAliveGameObject.hpp"

namespace AO {

ALIVE_VAR(1, 0x9F1DCC, ZBall*, gCenter_ZBall_9F1DCC, nullptr);
ALIVE_VAR(1, 0x9F1DD0, ZBall*, gOutZBall_9F1DD0, nullptr);

s16* Animation_OnFrame_ZBallSmacker(void* pObj, s16* pData)
{
    auto pZBall = static_cast<ZBall*>(pObj);
    for (s32 i = 0; i < gBaseGameObjects->Size(); i++)
    {
        BaseGameObject* pBase = gBaseGameObjects->ItemAt(i);
        if (!pBase)
        {
            break;
        }

        if (pBase->mFlags.Get(BaseGameObject::eIsBaseAliveGameObject_Bit6))
        {
            // If the object is within the ZBall rect then smack it
            auto pAliveObj = static_cast<BaseAliveGameObject*>(pBase);

            PSX_RECT bRect = {};
            pAliveObj->VGetBoundingRect(&bRect, 1);

            if (bRect.x <= (FP_GetExponent(pZBall->field_A8_xpos) + pData[2]) && bRect.w >= (FP_GetExponent(pZBall->field_A8_xpos) + pData[0]) && bRect.h >= (FP_GetExponent(pZBall->field_AC_ypos) + pData[1]) && bRect.y <= (FP_GetExponent(pZBall->field_AC_ypos) + pData[3]))
            {
                pAliveObj->VTakeDamage(pZBall);
            }
        }
    }

    return pData + 4; // A rect I guess ?
}

ZBall::ZBall(Path_ZBall* pTlv, s32 tlvInfo)
{
    field_4_typeId = Types::eZBall_92;

    field_C4_b = 128;
    field_C2_g = 128;
    field_C0_r = 128;

    switch (pTlv->field_1C_speed)
    {
        case Path_ZBall::Speed::eNormal_0:
        {
            const AnimRecord& rec1 = AO::AnimRec(AnimId::Swinging_Ball_Normal);
            u8** ppRes1 = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, rec1.mResourceId, 1, 0);
            Animation_Init_417FD0(rec1.mFrameTableOffset, rec1.mMaxW, rec1.mMaxH, ppRes1, 1);
            break;
        }

        case Path_ZBall::Speed::eFast_1:
        {
            const AnimRecord& rec2 = AO::AnimRec(AnimId::Swinging_Ball_Fast);
            u8** ppRes2 = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, rec2.mResourceId, 1, 0);
            Animation_Init_417FD0(rec2.mFrameTableOffset, rec2.mMaxW, rec2.mMaxH, ppRes2, 1);
            break;
        }

        case Path_ZBall::Speed::eSlow_2:
        {
            const AnimRecord& rec3 = AO::AnimRec(AnimId::Swinging_Ball_Slow);
            u8** ppRes3 = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, rec3.mResourceId, 1, 0);
            Animation_Init_417FD0(rec3.mFrameTableOffset, rec3.mMaxW, rec3.mMaxH, ppRes3, 1);
            break;
        }

    }

    field_A8_xpos = FP_FromInteger(pTlv->field_10_top_left.field_0_x);
    field_AC_ypos = FP_FromInteger(pTlv->field_10_top_left.field_2_y);

    if (gMap.mCurrentLevel == LevelIds::eForestTemple_4)
    {
        switch (pTlv->field_18_start_pos)
        {
            case Path_ZBall::StartPos::eCenter_0:
                field_10_anim.SetFrame(6u);
                gCenter_ZBall_9F1DCC = this;
                field_EA_sound_pitch = -800;
                break;

            case Path_ZBall::StartPos::eOut_1:
                field_10_anim.SetFrame(0);
                gOutZBall_9F1DD0 = this;
                field_EA_sound_pitch = -400;
                break;

            case Path_ZBall::StartPos::eIn_2:
                field_10_anim.SetFrame(13u);
                field_EA_sound_pitch = 0;
                break;
        }

        field_10_anim.VDecode();
    }

    if (pTlv->field_1A_scale != Scale_short::eFull_0)
    {
        field_BC_sprite_scale = FP_FromDouble(0.5);
        field_C6_scale = 0;
    }

    field_E4_tlvInfo = tlvInfo;
    field_10_anim.field_1C_fn_ptr_array = kZBall_Anim_Frame_Fns_4CEBF8;
}

void ZBall::VUpdate()
{
    if (Event_Get(kEventDeathReset_4))
    {
        mFlags.Set(Options::eDead);
    }

    if (gCenter_ZBall_9F1DCC == this || gOutZBall_9F1DD0 == this)
    {
        if (field_10_anim.field_92_current_frame == 0 || field_10_anim.field_92_current_frame == 13)
        {
            SFX_Play_Pitch(SoundEffect::ZBall_62, 50, field_EA_sound_pitch, nullptr);
        }
    }

    if (gCenter_ZBall_9F1DCC == this)
    {
        if (field_10_anim.field_92_current_frame == 3 || field_10_anim.field_92_current_frame == 16)
        {
            SFX_Play_Pitch(SoundEffect::SackWobble_34, 40, field_EA_sound_pitch - 2400, nullptr);
        }
    }

    if (field_10_anim.field_92_current_frame <= 6 || field_10_anim.field_92_current_frame >= 19)
    {
        if (field_BC_sprite_scale == FP_FromInteger(1))
        {
            field_10_anim.field_C_layer = Layer::eLayer_Foreground_36;
        }
        else
        {
            field_10_anim.field_C_layer = Layer::eLayer_Foreground_Half_17;
        }
    }
    else if (field_BC_sprite_scale == FP_FromInteger(1))
    {
        field_10_anim.field_C_layer = Layer::eLayer_BeforeWell_22;
    }
    else
    {
        field_10_anim.field_C_layer = Layer::eLayer_BeforeWell_Half_3;
    }

    // Pointless because never seems to be read
    field_E8_bFrameAbove12 = field_10_anim.field_92_current_frame >= 13;

    if (!gMap.Is_Point_In_Current_Camera_4449C0(
            field_B2_lvl_number,
            field_B0_path_number,
            field_A8_xpos,
            field_AC_ypos,
            0))
    {
        mFlags.Set(Options::eDead);
        if (field_E4_tlvInfo != -1)
        {
            gMap.TLV_Reset_446870(field_E4_tlvInfo, -1, 0, 0);
        }
    }
}

} // namespace AO
