#include "stdafx_ao.h"
#include "Function.hpp"
#include "ThrowableArray.hpp"
#include "../AliveLibAE/stdlib.hpp"
#include "ResourceManager.hpp"
#include "Map.hpp"
#include "Throwable.hpp"
#include "PathData.hpp"

namespace AO {

ThrowableArray* gThrowableArray = nullptr;

void LoadRockTypes(EReliveLevelIds levelNumber, u16 path)
{
    bool bDoLoadingLoop = FALSE;
    const u8 throwableTypeIdx = Path_Get_Bly_Record_434650(levelNumber, path)->field_C_overlay_id & 0xFF;

    switch (word_4CF158[throwableTypeIdx])
    {
        case AOTypes::eGrenade_40:
            break;

        case AOTypes::eMeat_54:
            break;

        case AOTypes::eRock_70:

            break;

        default:
            break;
    }

    if (bDoLoadingLoop)
    {
        ResourceManager::LoadingLoop_41EAD0(FALSE);
    }
}

void ThrowableArray::VRender(PrimHeader** /*ppOt*/)
{
    //Nothing to do here
}

void ThrowableArray::VUpdate()
{
    if (field_12_flags & 1)
    {
        LoadRockTypes(gMap.mCurrentLevel, gMap.mCurrentPath);
        Add(0);
        field_12_flags &= ~1u;
        mBaseGameObjectFlags.Clear(Options::eUpdatable_Bit2);
    }
}

void ThrowableArray::VScreenChanged()
{
    if (gMap.mNextLevel != EReliveLevelIds::eMenu && gMap.mNextLevel != EReliveLevelIds::eCredits)
    {
        if (word_4CF158[gMap.mOverlayId] != word_4CF158[gMap.GetOverlayId()])
        {
            if (!(field_12_flags & 1))
            {
                mBaseGameObjectFlags.Set(Options::eUpdatable_Bit2);
                field_12_flags |= 1;
                Remove(0);
            }
        }
    }
    else
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }
}

ThrowableArray::~ThrowableArray()
{
    gThrowableArray = nullptr;
    if (field_10_count > 0)
    {
        Remove(field_10_count);
    }

}

ThrowableArray::ThrowableArray()
    : BaseGameObject(TRUE, 0)
{
    mBaseGameObjectFlags.Clear(Options::eUpdatable_Bit2);
    field_10_count = 0;
    gThrowableArray = this;
    field_12_flags &= ~7u;
}

void ThrowableArray::Remove(s16 count)
{
    field_10_count -= count;

    if (field_10_count > 0)
    {
        if (!(field_12_flags & 1))
        {
            return;
        }
    }
    else
    {
        if (field_12_flags & 4)
        {
            field_12_flags &= ~4;
        }
    }

    if (field_12_flags & 2)
    {
        switch (word_4CF158[gMap.mOverlayId])
        {
            case AOTypes::eGrenade_40:
                break;

            case AOTypes::eMeat_54:
                break;

            case AOTypes::eRock_70:
                break;

            default:
                break;
        }
        field_12_flags &= ~2;
    }
}

void ThrowableArray::Add(s16 count)
{
    if (field_10_count == 0)
    {
        if (!(field_12_flags & 4))
        {
            field_12_flags |= 4;
        }
    }

    if (field_10_count == 0 || (field_12_flags & 1))
    {
        if (!(field_12_flags & 2))
        {
            switch (word_4CF158[gMap.mOverlayId])
            {
                case AOTypes::eGrenade_40:
                    break;

                case AOTypes::eMeat_54:
                    break;

                case AOTypes::eRock_70:
                    break;

                default:
                    break;
            }

            field_12_flags |= 2;
        }
    }

    field_10_count += count;
}

} // namespace AO
