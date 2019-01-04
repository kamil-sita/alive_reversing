#include "stdafx.h"
#include "Shadow.hpp"
#include "Function.hpp"
#include "ResourceManager.hpp"
#include "Game.hpp"

EXPORT Shadow* Shadow::ctor_4AC990()
{
    SetVTable(&field_18_animation, 0x544290); // gVtbl_animation_2a_544290

    BYTE** ppAnimRes = ResourceManager::GetLoadedResource_49C2A0(ResourceManager::Resource_Animation, ResourceID::kRockShadowResID, TRUE, FALSE);
    field_18_animation.Init_40A030(240, gObjList_animations_5C1A24, 0, 64, 6u, ppAnimRes, 1u, 0, 0);

    field_14_flags.Clear(Flags::eBit1);
    field_14_flags.Set(Flags::eBit2);

    field_18_animation.field_B_render_mode = 2;

    field_18_animation.field_4_flags.Clear(AnimFlags::eBit3_Render);
    field_18_animation.field_4_flags.Clear(AnimFlags::eBit16_bBlending);

    field_18_animation.field_4_flags.Set(AnimFlags::eBit2_Animate);
    field_18_animation.field_4_flags.Set(AnimFlags::eBit8_Loop);
    field_18_animation.field_4_flags.Set(AnimFlags::eBit15_bSemiTrans);
    field_18_animation.field_4_flags.Set(AnimFlags::eBit17);
    field_18_animation.field_4_flags.Set(AnimFlags::eBit18_IsLastFrame);
    field_18_animation.field_4_flags.Set(AnimFlags::eBit20);
    field_18_animation.field_4_flags.Set(AnimFlags::eBit21);

    return this;
}

EXPORT void Shadow::dtor_4ACA30()
{
    field_18_animation.vCleanUp_40C630();
}

EXPORT void Shadow::Calculate_Position_4ACA50(FP /*xpos*/, FP /*ypos*/, PSX_RECT* /*frameRect*/, FP /*spriteScale*/, __int16 /*scale*/)
{
    NOT_IMPLEMENTED();
}

EXPORT void Shadow::Render_4ACE60(int** /*pOt*/)
{
    NOT_IMPLEMENTED();
}
