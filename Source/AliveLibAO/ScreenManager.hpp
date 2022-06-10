#pragma once

#include "../AliveLibCommon/Function.hpp"
#include "../relive_lib/BaseGameObject.hpp"
#include "FixedPoint.hpp"
#include "Primitives.hpp"
#include "Layer.hpp"

namespace AO {

enum class LevelIds : s16;


struct DirtyBits final
{
    u16 mData[20]; // 20 Columns

    bool GetTile(s32 x, s32 y)
    {
        return mData[x] & (1 << y) ? true : false;
    }

    void SetTile(s32 x, s32 y, bool b)
    {
        if (b)
        {
            mData[x] |= 1 << y;
        }
        else
        {
            mData[x] &= ~(1 << y);
        }
    }
};
ALIVE_ASSERT_SIZEOF(DirtyBits, 0x28);

struct SprtTPage final
{
    Prim_Sprt mSprt;
    Prim_SetTPage mTPage;
};

class ScreenManager final : public BaseGameObject
{
public:
    ScreenManager(u8** ppBits, FP_Point* pCameraOffset);

    virtual void VScreenChanged() override;
    virtual void VUpdate() override;
    virtual void VRender(PrimHeader** ppOt) override;

    void Init(u8** ppBits);
    void MoveImage();
    void DecompressCameraToVRam(u16** ppBits);
    void UnsetDirtyBits_FG1();

    void InvalidateRect(s32 x, s32 y, s32 width, s32 height, s32 idx);
    void InvalidateRectCurrentIdx(s32 x, s32 y, s32 width, s32 height);
    void InvalidateRect_Idx3(s32 x, s32 y, s32 width, s32 height);
    void InvalidateRect_IdxPlus4(s32 x, s32 y, s32 width, s32 height, s32 idx);

    s32 GetTPage(TPageMode tp, TPageAbr abr, s32* xpos, s32* ypos);
    void sub_406FF0();

    FP_Point* mCamPos;
    s16 field_14_xpos;
    u16 field_16_ypos;
    SprtTPage* mScreenSprites;
    s16 mUPos;
    s16 mVpos;
    s16 mCamWidth;
    s16 mCamHeight;
    u16 mIdx;
    u16 mYIdx;
    u16 mXIdx;
    s16 mFlags;
    DirtyBits field_58_20x16_dirty_bits[6];
};
ALIVE_ASSERT_SIZEOF(ScreenManager, 0x148);

ALIVE_VAR_EXTERN(ScreenManager*, pScreenManager_4FF7C8);

} // namespace AO
