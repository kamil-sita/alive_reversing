#include "stdafx.h"
#include "SnoozeParticle.hpp"
#include "Events.hpp"
#include "Function.hpp"
#include "Game.hpp"
#include "PsxDisplay.hpp"
#include "ScreenManager.hpp"
#include "Sfx.hpp"
#include "stdlib.hpp"

const s16 xPositionDeltaEntries_560408[39] = {
    1,
    0,
    0,
    1,
    0,
    0,
    1,
    0,
    1,
    0,
    1,
    1,
    1,
    0,
    1,
    0,
    1,
    0,
    0,
    1,
    0,
    0,
    0,
    -1,
    0,
    -1,
    0,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    0,
    -1,
    0,
    0,
    0,
    -3};


const s16 zVerts[8] = {
    -4,
    -4,
    4,
    -4,
    -4,
    4,
    4,
    4};

const PSX_Point explosionVerts[6][2] = {
    {{-3, -4}, {-6, -7}},
    {{3, -4}, {6, -7}},
    {{4, -1}, {7, -1}},
    {{-4, 1}, {-7, 1}},
    {{-3, 4}, {-6, 7}},
    {{3, 4}, {6, 7}}};

SnoozeParticle::SnoozeParticle(FP xpos, FP ypos, Layer layer, FP scale)
    : BaseGameObject(TRUE, 0)
{
    mBaseGameObjectFlags.Set(BaseGameObject::eDrawable_Bit4);

    SetType(ReliveTypes::eSnoozeParticle);
    gObjListDrawables->Push_Back(this);

    field_20_x_start = xpos;
    field_24_y_start = ypos;
    field_28_x = xpos;
    field_2C_y = ypos;

    // Interesting calc.. ??
    field_34_dy = (FP_FromDouble(0.15) * FP_FromInteger(Math_NextRandom())) / FP_FromInteger(256);
    field_34_dy += FP_FromDouble(0.35);
    field_34_dy = field_34_dy * FP_FromInteger(-1);

    field_40_layer = layer;

    field_38_scale = scale * FP_FromDouble(0.4);

    field_3C_scale_dx = FP_FromDouble(0.30);
    field_3C_scale_dx = field_3C_scale_dx / (FP_FromInteger(20) / -field_34_dy);

    field_42_r = 0;
    field_44_g = 0;
    field_46_b = 0;
    field_1E4_state = SnoozeParticleState::eRising_0;
    field_4A_count_down = 1;
    field_48_idx = Math_NextRandom() % 36;
    field_30_dx = FP_FromDouble(xPositionDeltaEntries_560408[field_48_idx]);
    field_48_idx++;
}

SnoozeParticle::~SnoozeParticle()
{
    if (mBaseGameObjectFlags.Get(BaseGameObject::eDrawable_Bit4))
    {
        gObjListDrawables->Remove_Item(this);
    }
}

void SnoozeParticle::VUpdate()
{
    if (Event_Get(kEventDeathReset))
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }
    if (!sNum_CamSwappers_5C1B66)
    {
        switch (field_1E4_state)
        {
            case SnoozeParticleState::eRising_0:
                if (field_2C_y >= field_24_y_start - FP_FromInteger(20))
                {
                    if (field_42_r < 70 && field_44_g < 70 && field_46_b < 20)
                    {
                        field_42_r += 14;
                        field_44_g += 14;
                        field_46_b += 4;
                    }

                    field_38_scale += field_3C_scale_dx;

                    if (field_48_idx > 36)
                    {
                        field_48_idx = 0;
                    }

                    const FP field_48_idx_toFP = FP_FromInteger(xPositionDeltaEntries_560408[field_48_idx]);
                    field_30_dx = field_48_idx_toFP;
                    field_28_x += field_48_idx_toFP;
                    field_2C_y += field_34_dy;
                    field_48_idx += 1;
                }
                else
                {
                    field_1E4_state = SnoozeParticleState::eBlowingUp_2;
                }
                break;

            case SnoozeParticleState::eUnused_1:
                break;

            case SnoozeParticleState::eBlowingUp_2:
                field_42_r /= 2; //fade to transparent
                field_44_g /= 2;
                field_46_b /= 2;
                field_28_x += field_30_dx;
                field_2C_y += field_34_dy;

                if (field_4A_count_down > 0)
                {
                    field_4A_count_down--;
                }
                else
                {
                    SFX_Play_Mono(SoundEffect::ZPop_4, 0, field_38_scale);
                    mBaseGameObjectFlags.Set(BaseGameObject::eDead);
                }
                break;
        }
    }
}

void SnoozeParticle::VRender(PrimHeader** ppOt)
{
    PSX_RECT rectToInvalidate = {};
    FP_Point* pCamPos = pScreenManager->mCamPos;
    const s16 bufIdx = gPsxDisplay_5C1130.field_C_buffer_index;

    if (field_1E4_state == SnoozeParticleState::eBlowingUp_2)
    {
        const s16 xInScreen = FP_GetExponent(field_28_x - pCamPos->field_0_x);
        const s16 yInScreen = FP_GetExponent(field_2C_y - pCamPos->field_4_y);

        for (s32 i = 0; i < ALIVE_COUNTOF(explosionVerts); i++)
        {
            Line_G2* pZExplosionLine = &field_A4_G2_lines[bufIdx][i];
            LineG2_Init(pZExplosionLine);

            const s32 scaledLineRelativeStartX = FP_GetExponent(FP_FromInteger(explosionVerts[i][0].field_0_x) * field_38_scale);
            const s32 scaledLineRelativeStartY = FP_GetExponent(FP_FromInteger(explosionVerts[i][0].field_2_y) * field_38_scale);
            const s32 scaledLineRelativeEndX = FP_GetExponent(FP_FromInteger(explosionVerts[i][1].field_0_x) * field_38_scale);
            const s32 scaledLineRelativeEndY = FP_GetExponent(FP_FromInteger(explosionVerts[i][1].field_2_y) * field_38_scale);
            SetXY0(pZExplosionLine,
                   static_cast<s16>(PsxToPCX(xInScreen + scaledLineRelativeStartX, 11)),
                   static_cast<s16>(yInScreen + scaledLineRelativeStartY));
            SetXY1(pZExplosionLine,
                   static_cast<s16>(PsxToPCX(xInScreen + scaledLineRelativeEndX, 11)),
                   static_cast<s16>(yInScreen + scaledLineRelativeEndY));

            SetRGB0(pZExplosionLine,
                    static_cast<u8>(field_42_r / 2),
                    static_cast<u8>(field_44_g / 2),
                    static_cast<u8>(field_46_b / 2));
            SetRGB1(pZExplosionLine,
                    static_cast<u8>(field_42_r),
                    static_cast<u8>(field_44_g),
                    static_cast<u8>(field_46_b));

            Poly_Set_SemiTrans_4F8A60(&pZExplosionLine->mBase.header, 1);
            OrderingTable_Add_4F8AA0(OtLayer(ppOt, field_40_layer), &pZExplosionLine->mBase.header);
        }
        rectToInvalidate.x = static_cast<s16>(PsxToPCX(xInScreen - 8, 0));
        rectToInvalidate.w = static_cast<s16>(PsxToPCX(xInScreen + 8, 0));
        rectToInvalidate.y = static_cast<s16>(yInScreen - 8);
        rectToInvalidate.h = static_cast<s16>(yInScreen + 8);
    }
    else
    {
        Line_G4* pZLine = &field_4C_G4_lines[bufIdx];
        LineG4_Init(pZLine);

        const s16 xInScreen = FP_GetExponent(field_28_x - FP_FromInteger(FP_GetExponent(pCamPos->field_0_x)));
        const s16 yInScreen = FP_GetExponent(field_2C_y - FP_FromInteger(FP_GetExponent(pCamPos->field_4_y)));

        const s16 RectX_v_Psx = xInScreen + FP_GetExponent(FP_FromInteger(zVerts[0]) * field_38_scale);
        const s16 RectW_v_Psx = xInScreen + FP_GetExponent(FP_FromInteger(zVerts[5]) * field_38_scale);

        const s16 rectX_v = PsxToPCX(RectX_v_Psx, 11);
        const s16 rectY_v = FP_GetExponent(FP_FromInteger(zVerts[1]) * field_38_scale) + yInScreen;
        const s16 rectW_v = PsxToPCX(RectW_v_Psx, 11);
        const s16 rectH_v = yInScreen + FP_GetExponent(FP_FromInteger(zVerts[7]) * field_38_scale);

        SetXY0(pZLine,
               rectX_v,
               rectY_v);
        SetXY1(pZLine,
               static_cast<s16>(PsxToPCX(xInScreen + FP_GetExponent(FP_FromInteger(zVerts[2]) * field_38_scale), 11)),
               yInScreen + FP_GetExponent(FP_FromInteger(zVerts[3]) * field_38_scale));
        SetXY2(pZLine,
               static_cast<s16>(PsxToPCX(xInScreen + FP_GetExponent(FP_FromInteger(zVerts[4]) * field_38_scale), 11)),
               yInScreen + FP_GetExponent(FP_FromInteger(zVerts[5]) * field_38_scale));
        SetXY3(pZLine,
               rectW_v,
               rectH_v);

        SetRGB0(pZLine,
                static_cast<u8>(field_42_r * 8 / 10),
                static_cast<u8>(field_44_g * 8 / 10),
                static_cast<u8>(field_46_b * 8 / 10));
        SetRGB1(pZLine,
                static_cast<u8>(field_42_r),
                static_cast<u8>(field_44_g),
                static_cast<u8>(field_46_b));
        SetRGB2(pZLine,
                static_cast<u8>(field_42_r * 7 / 10),
                static_cast<u8>(field_44_g * 7 / 10),
                static_cast<u8>(field_46_b * 7 / 10));
        SetRGB3(pZLine,
                static_cast<u8>(field_42_r / 2),
                static_cast<u8>(field_44_g / 2),
                static_cast<u8>(field_46_b / 2));

        Poly_Set_SemiTrans_4F8A60(&pZLine->mBase.header, 1);
        OrderingTable_Add_4F8AA0(OtLayer(ppOt, field_40_layer), &pZLine->mBase.header);
        rectToInvalidate.x = rectX_v;
        rectToInvalidate.y = rectY_v;
        rectToInvalidate.w = rectW_v;
        rectToInvalidate.h = rectH_v;
    }
    Prim_SetTPage* thisTPage = &field_1C4_tPage[bufIdx];
    const s32 tPage = PSX_getTPage_4F60E0(TPageMode::e4Bit_0, TPageAbr::eBlend_1, 0, 0);
    Init_SetTPage_4F5B60(thisTPage, 1, 0, tPage);
    OrderingTable_Add_4F8AA0(OtLayer(ppOt, field_40_layer), &thisTPage->mBase);

    pScreenManager->InvalidateRect_40EC90(
        rectToInvalidate.x, rectToInvalidate.y,
        rectToInvalidate.w, rectToInvalidate.h,
        pScreenManager->mIdx);
}

void SnoozeParticle::VScreenChanged()
{
    mBaseGameObjectFlags.Set(BaseGameObject::eDead);
}
