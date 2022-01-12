#include "GameAutoPlayer.hpp"
#include "Sys_common.hpp"
#include "BaseGameObject.hpp"
#include "BaseAliveGameObject.hpp"
#include "Input.hpp"
#include "Game.hpp"
#include "Slig.hpp"

namespace AO {
void Recorder::SaveObjectStates()
{
    mFile.Write(gnFrameCount_507670);

    const u32 objCount = gBaseGameObject_list_9F2DF0->Size();
    mFile.Write(objCount);

    for (u32 i = 0; i < objCount; i++)
    {
        BaseGameObject* pObj = gBaseGameObject_list_9F2DF0->ItemAt(i);
        const s16 objType = static_cast<s16>(pObj->field_4_typeId);
        mFile.Write(objType);
        mFile.Write(pObj->field_6_flags.Raw().all);
        mFile.Write(pObj->field_8_update_delay);
        mFile.Write(pObj->field_C_refCount);


        if (pObj->field_6_flags.Get(BaseGameObject::eIsBaseAliveGameObject_Bit6))
        {
            auto pAliveObj = static_cast<BaseAliveGameObject*>(pObj);

            mFile.Write(pAliveObj->field_10_anim.field_10_frame_delay);
            mFile.Write(pAliveObj->field_10_anim.field_14_scale.fpValue);
            mFile.Write(pAliveObj->field_10_anim.field_18_frame_table_offset);
            mFile.Write(pAliveObj->field_10_anim.field_90_pal_depth);
            mFile.Write(pAliveObj->field_10_anim.field_92_current_frame);

            mFile.Write(pAliveObj->field_A8_xpos.fpValue);
            mFile.Write(pAliveObj->field_AC_ypos.fpValue);
            
            mFile.Write(pAliveObj->field_B0_path_number);
            mFile.Write(static_cast<s16>(pAliveObj->field_B2_lvl_number));

            mFile.Write(pAliveObj->field_B4_velx.fpValue);
            mFile.Write(pAliveObj->field_B8_vely.fpValue);

            mFile.Write(pAliveObj->field_BC_sprite_scale);
            mFile.Write(pAliveObj->field_C0_r);
            mFile.Write(pAliveObj->field_C2_g);
            mFile.Write(pAliveObj->field_C4_b);
            mFile.Write(pAliveObj->field_C6_scale);
            mFile.Write(pAliveObj->field_C8_yOffset);
            mFile.Write(pAliveObj->field_CA_xOffset);
            mFile.Write(pAliveObj->field_CC_bApplyShadows);

            mFile.Write(pAliveObj->field_D4_collection_rect.x);
            mFile.Write(pAliveObj->field_D4_collection_rect.y);
            mFile.Write(pAliveObj->field_D4_collection_rect.w);
            mFile.Write(pAliveObj->field_D4_collection_rect.h);

            mFile.Write(pAliveObj->field_E4_previous_motion);
            mFile.Write(pAliveObj->field_E6_last_anim_frame);
            mFile.Write(pAliveObj->field_E8_LastLineYPos.fpValue);

            mFile.Write(pAliveObj->field_EC);
            mFile.Write(pAliveObj->field_EE_type);

            mFile.Write(pAliveObj->field_FC_current_motion);
            mFile.Write(pAliveObj->field_FE_next_motion);
            mFile.Write(pAliveObj->field_100_health);
            mFile.Write(pAliveObj->field_104_pending_resource_count);
            mFile.Write(pAliveObj->field_106_shot);
            mFile.Write(pAliveObj->field_108_bMotionChanged);
            mFile.Write(pAliveObj->field_10A_flags.Raw().all);

        }
    }
}

void Player::ValidateObject(s32 idx, bool logTypes)
{
    s16 objType = 0;
    mFile.Read(objType);

    if (logTypes)
    {
        LOG_INFO(objType);
    }

    if (idx < gBaseGameObject_list_9F2DF0->Size())
    {
        BaseGameObject* pObj = gBaseGameObject_list_9F2DF0->ItemAt(idx);
        if (static_cast<s16>(pObj->field_4_typeId) != objType)
        {
            LOG_ERROR("Got " << static_cast<s16>(pObj->field_4_typeId) << " type but expected " << objType);
            ALIVE_FATAL("Object type de-sync");
        }

        ValidField(pObj->field_6_flags.Raw().all, "flags");
        ValidField(pObj->field_8_update_delay, "update delay");
        ValidField(pObj->field_C_refCount, "ref count");

        if (pObj->field_6_flags.Get(BaseGameObject::eIsBaseAliveGameObject_Bit6))
        {
            auto pAliveObj = static_cast<BaseAliveGameObject*>(pObj);

            ValidField(pAliveObj->field_10_anim.field_10_frame_delay, "frame delay");
            ValidField(pAliveObj->field_10_anim.field_14_scale.fpValue, "scale");
            ValidField(pAliveObj->field_10_anim.field_18_frame_table_offset, "frame table offset");
            ValidField(pAliveObj->field_10_anim.field_90_pal_depth, "pal depth");
            ValidField(pAliveObj->field_10_anim.field_92_current_frame, "current frame");

            ValidField(pAliveObj->field_A8_xpos.fpValue, "xpos");
            ValidField(pAliveObj->field_AC_ypos.fpValue, "ypos");

            ValidField(pAliveObj->field_B0_path_number, "path number");
            ValidField(static_cast<s16>(pAliveObj->field_B2_lvl_number), "lvl number");
            ValidField(pAliveObj->field_B4_velx.fpValue, "xvel");
            ValidField(pAliveObj->field_B8_vely.fpValue, "yvel");
            ValidField(pAliveObj->field_BC_sprite_scale.fpValue, "sprite scale");
            ValidField(pAliveObj->field_C0_r, "r");
            ValidField(pAliveObj->field_C2_g, "g");
            ValidField(pAliveObj->field_C4_b, "b");
            ValidField(pAliveObj->field_C6_scale, "scale");
            ValidField(pAliveObj->field_C8_yOffset, "yoff");
            ValidField(pAliveObj->field_CA_xOffset, "xoff");
            ValidField(pAliveObj->field_CC_bApplyShadows, "apply shadow");
            ValidField(pAliveObj->field_D4_collection_rect.x.fpValue, "rect x");
            ValidField(pAliveObj->field_D4_collection_rect.y.fpValue, "rect y");
            ValidField(pAliveObj->field_D4_collection_rect.w.fpValue, "rect w");
            ValidField(pAliveObj->field_D4_collection_rect.h.fpValue, "rect h");

            ValidField(pAliveObj->field_E4_previous_motion, "prev motion");
            ValidField(pAliveObj->field_E6_last_anim_frame, "last anim frame");
            ValidField(pAliveObj->field_E8_LastLineYPos.fpValue, "last line ypos");
            ValidField(pAliveObj->field_EC, "f_ec");
            ValidField(pAliveObj->field_EE_type, "ee_type");
            ValidField(pAliveObj->field_FC_current_motion, "current motion");
            ValidField(pAliveObj->field_FE_next_motion, "next motion");
            ValidField(pAliveObj->field_100_health.fpValue, "health");
            ValidField(pAliveObj->field_104_pending_resource_count, "pending resource count");
            ValidField(pAliveObj->field_106_shot, "shot");
            ValidField(pAliveObj->field_108_bMotionChanged, "motion changed");
            ValidField(pAliveObj->field_10A_flags.Raw().all, "flags 10A");

            if (pAliveObj->field_4_typeId == Types::eSlig_88)
            {
                // TODO: Extra slig validation
                //auto pSlig = static_cast<Slig*>(pAliveObj);
            }
        }

        if (mValidationFailed)
        {
            ALIVE_FATAL("Object de-synced");
        }
    }
}

void Player::ValidateObjectStates()
{
    u32 gnFrame = 0;
    mFile.Read(gnFrame);
    if (gnFrame != gnFrameCount_507670)
    {
        ALIVE_FATAL("GnFrame de-sync");
    }

    u32 objCount = 0;
    mFile.Read(objCount);

    if (static_cast<u32>(gBaseGameObject_list_9F2DF0->Size()) != objCount)
    {
        LOG_INFO("Loaded objects...");
        for (s32 i = 0; i < gBaseGameObject_list_9F2DF0->Size(); i++)
        {
            LOG_INFO(static_cast<s16>(gBaseGameObject_list_9F2DF0->ItemAt(i)->field_4_typeId));
        }

        LOG_INFO("Recorded objects...");
        for (u32 i = 0; i < objCount; i++)
        {
            ValidateObject(i, true);
        }

        LOG_ERROR("Got " << gBaseGameObject_list_9F2DF0->Size() << " objects but expected " << objCount);
        ALIVE_FATAL("Object count de-sync");
    }

    for (u32 i = 0; i < objCount; i++)
    {
        ValidateObject(i, false);
    }
}

u32 GameAutoPlayer::ReadInput(u32 padIdx)
{
    return Input().Input_Read_Pad(padIdx);
}

GameAutoPlayer gGameAutoPlayer;
} // namespace AO
