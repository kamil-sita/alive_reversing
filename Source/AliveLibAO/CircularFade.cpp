#include "stdafx_ao.h"
#include "CircularFade.hpp"
#include "Function.hpp"
#include "ScreenManager.hpp"
#include "ResourceManager.hpp"
#include "PsxDisplay.hpp"
#include "stdlib.hpp"

namespace AO {

CircularFade::CircularFade(FP xpos, FP ypos, FP scale, s16 direction, s8 destroyOnDone)
{
    if (direction)
    {
        field_1A8_fade_colour = 0;
    }
    else
    {
        field_1A8_fade_colour = 255;
    }

    // NOTE: Inlined
    VFadeIn(static_cast<s8>(direction), destroyOnDone);

    const u8 fade_rgb = static_cast<u8>((field_1A8_fade_colour * 60) / 100);
    mBaseAnimatedWithPhysicsGameObject_Blue = fade_rgb;
    mBaseAnimatedWithPhysicsGameObject_Green = fade_rgb;
    mBaseAnimatedWithPhysicsGameObject_Red = fade_rgb;

    const AnimRecord& rec = AO::AnimRec(AnimId::Circular_Fade);
    u8** ppRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, rec.mResourceId, 1, 0);
    Animation_Init_417FD0(rec.mFrameTableOffset, rec.mMaxW, rec.mMaxH, ppRes, 1);

    mApplyShadows &= ~1u;

    mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Clear(AnimFlags::eBit16_bBlending);
    mBaseAnimatedWithPhysicsGameObject_SpriteScale.fpValue = scale.fpValue * 2;
    mBaseAnimatedWithPhysicsGameObject_Anim.field_14_scale.fpValue = scale.fpValue * 2;

    mBaseAnimatedWithPhysicsGameObject_XPos = xpos;
    mBaseAnimatedWithPhysicsGameObject_YPos = ypos;
    mBaseAnimatedWithPhysicsGameObject_Anim.mRenderMode = TPageAbr::eBlend_2;
    mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer = Layer::eLayer_FadeFlash_40;
    mBaseAnimatedWithPhysicsGameObject_Red = field_1A8_fade_colour;
    mBaseAnimatedWithPhysicsGameObject_Green = field_1A8_fade_colour;
    mBaseAnimatedWithPhysicsGameObject_Blue = field_1A8_fade_colour;

    Init_SetTPage_495FB0(&field_188_tPage[0], 0, 0, PSX_getTPage_4965D0(TPageMode::e16Bit_2, TPageAbr::eBlend_2, 0, 0));
    Init_SetTPage_495FB0(&field_188_tPage[1], 0, 0, PSX_getTPage_4965D0(TPageMode::e16Bit_2, TPageAbr::eBlend_2, 0, 0));
}

void CircularFade::VRender(PrimHeader** ppOt)
{
    const u8 fade_rgb = static_cast<u8>((field_1A8_fade_colour * 60) / 100);

    mBaseAnimatedWithPhysicsGameObject_Red = fade_rgb;
    mBaseAnimatedWithPhysicsGameObject_Blue = fade_rgb;
    mBaseAnimatedWithPhysicsGameObject_Green = fade_rgb;

    mBaseAnimatedWithPhysicsGameObject_Anim.mRed = fade_rgb;
    mBaseAnimatedWithPhysicsGameObject_Anim.mGreen = fade_rgb;
    mBaseAnimatedWithPhysicsGameObject_Anim.mBlue = fade_rgb;

    mBaseAnimatedWithPhysicsGameObject_Anim.VRender(
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos + (FP_FromInteger(pScreenManager_4FF7C8->field_14_xpos + mBaseAnimatedWithPhysicsGameObject_XOffset)) - pScreenManager_4FF7C8->mCamPos->field_0_x),
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos + (FP_FromInteger(pScreenManager_4FF7C8->field_16_ypos + mBaseAnimatedWithPhysicsGameObject_YOffset)) - pScreenManager_4FF7C8->mCamPos->field_4_y),
        ppOt,
        0,
        0);
    PSX_RECT frameRect = {};
    mBaseAnimatedWithPhysicsGameObject_Anim.Get_Frame_Rect(&frameRect);
    pScreenManager_4FF7C8->InvalidateRect(
        frameRect.x,
        frameRect.y,
        frameRect.w,
        frameRect.h,
        pScreenManager_4FF7C8->mIdx);

    frameRect.h--;
    frameRect.w--;

    if (frameRect.y < 0)
    {
        frameRect.y = 0;
    }

    if (frameRect.x < 0)
    {
        frameRect.x = 0;
    }

    if (frameRect.w >= 640)
    {
        frameRect.w = 639;
    }

    if (frameRect.h >= 240)
    {
        frameRect.h = 240;
    }

    const u8 fadeColour = static_cast<u8>(field_1A8_fade_colour);


    Prim_Tile* pTile = &field_E8[gPsxDisplay_504C78.field_A_buffer_index];
    Init_Tile(pTile);
    SetRGB0(pTile, fadeColour, fadeColour, fadeColour);
    SetXY0(pTile, 0, 0);
    pTile->field_14_w = gPsxDisplay_504C78.field_0_width;
    pTile->field_16_h = frameRect.y;
    Poly_Set_SemiTrans_498A40(&pTile->mBase.header, 1);
    OrderingTable_Add_498A80(OtLayer(ppOt, mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer), &pTile->mBase.header);

    Prim_Tile* pTile2_1 = &field_110[gPsxDisplay_504C78.field_A_buffer_index];
    Init_Tile(pTile2_1);
    SetRGB0(pTile2_1, fadeColour, fadeColour, fadeColour);

    s16 w = 0;
    if (mBaseAnimatedWithPhysicsGameObject_Anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        w = frameRect.x + 1;
    }
    else
    {
        w = frameRect.x;
    }
    SetXY0(pTile2_1, 0, frameRect.y);
    pTile2_1->field_14_w = w;
    pTile2_1->field_16_h = frameRect.h - frameRect.y;
    Poly_Set_SemiTrans_498A40(&pTile2_1->mBase.header, 1);
    OrderingTable_Add_498A80(OtLayer(ppOt, mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer), &pTile2_1->mBase.header);

    Prim_Tile* pTile2 = &field_138[gPsxDisplay_504C78.field_A_buffer_index];
    Init_Tile(pTile2);
    SetRGB0(pTile2, fadeColour, fadeColour, fadeColour);
    SetXY0(pTile2, frameRect.w + 1, frameRect.y);
    pTile2->field_14_w = gPsxDisplay_504C78.field_0_width - frameRect.w;
    pTile2->field_16_h = frameRect.h - frameRect.y;
    Poly_Set_SemiTrans_498A40(&pTile2->mBase.header, 1);
    OrderingTable_Add_498A80(OtLayer(ppOt, mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer), &pTile2->mBase.header);

    Prim_Tile* pTile3 = &field_160[gPsxDisplay_504C78.field_A_buffer_index];
    Init_Tile(pTile3);
    SetRGB0(pTile3, fadeColour, fadeColour, fadeColour);
    SetXY0(pTile3, 0, frameRect.h);
    pTile3->field_14_w = gPsxDisplay_504C78.field_0_width;
    pTile3->field_16_h = gPsxDisplay_504C78.field_2_height - frameRect.h;
    Poly_Set_SemiTrans_498A40(&pTile3->mBase.header, 1);
    OrderingTable_Add_498A80(OtLayer(ppOt, mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer), &pTile3->mBase.header);
    OrderingTable_Add_498A80(OtLayer(ppOt, mBaseAnimatedWithPhysicsGameObject_Anim.mRenderLayer), &field_188_tPage[gPsxDisplay_504C78.field_A_buffer_index].mBase);

    if (field_1A8_fade_colour < 255)
    {
        pScreenManager_4FF7C8->InvalidateRectCurrentIdx(
            0,
            0,
            gPsxDisplay_504C78.field_0_width,
            gPsxDisplay_504C78.field_2_height);
    }

    if ((field_1A8_fade_colour == 255 && field_E4_flags.Get(CircularFade::eBit1_FadeIn)) || (field_1A8_fade_colour == 0 && !field_E4_flags.Get(CircularFade::eBit1_FadeIn)))
    {
        field_E4_flags.Set(CircularFade::eBit2_Done);

        if (field_E4_flags.Get(CircularFade::eBit3_DestroyOnDone))
        {
            mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        }
    }
}

void CircularFade::VUpdate()
{
    if ((!field_E4_flags.Get(Flags::eBit4_NeverSet) && !field_E4_flags.Get(Flags::eBit2_Done)))
    {
        field_1A8_fade_colour += field_1AA_speed;
        if (field_E4_flags.Get(Flags::eBit1_FadeIn))
        {
            if (field_1A8_fade_colour > 255)
            {
                field_1A8_fade_colour = 255;
            }
        }
        else if (field_1A8_fade_colour < 0)
        {
            field_1A8_fade_colour = 0;
        }
    }
}

s8 CircularFade::VFadeIn(u8 direction, s8 destroyOnDone)
{
    field_E4_flags.Set(Flags::eBit1_FadeIn, direction);

    field_E4_flags.Clear(Flags::eBit2_Done);
    field_E4_flags.Clear(Flags::eBit4_NeverSet);

    field_E4_flags.Set(Flags::eBit3_DestroyOnDone, destroyOnDone);


    if (field_E4_flags.Get(Flags::eBit1_FadeIn))
    {
        field_1AA_speed = 12;
    }
    else
    {
        field_1AA_speed = -12;
    }
    return static_cast<s8>(field_E4_flags.Raw().all);
}

void CircularFade::VScreenChanged()
{
    // Empty
}

s32 CircularFade::VDone()
{
    return field_E4_flags.Get(Flags::eBit2_Done);
}

CircularFade* Make_Circular_Fade(FP xpos, FP ypos, FP scale, s16 direction, s8 destroyOnDone)
{
    return relive_new CircularFade(xpos, ypos, scale, direction, destroyOnDone);
}

} // namespace AO
