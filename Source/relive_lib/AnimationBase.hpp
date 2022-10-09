#pragma once

#include "Primitives.hpp"
#include "Layer.hpp"
#include "ResourceManagerWrapper.hpp"
#include "DynamicArray.hpp"
#include "../AliveLibCommon/BitField.hpp"

enum AnimFlags
{
    eBit1 = 0x1, // unused
    eAnimate = 0x2,
    eRender = 0x4,
    eBit4 = 0x8, // unused
    eFlipX = 0x10,
    eFlipY = 0x20,
    eSwapXY = 0x40,
    eLoop = 0x80,
    eBit9 = 0x100, // unused
    eBit10_alternating_flag = 0x200, // unused
    eBit11_bToggle_Bit10 = 0x400, // unused
    eForwardLoopCompleted = 0x800,

    // Bit 13 = Colour depth related.
    eIs8Bit = 0x1000,

    // Bit 14 = Transparency enabled.
    eIs16Bit = 0x2000,

    eSemiTrans = 0x4000,
    eBlending = 0x8000,
    eBit17_bOwnPal = 0x10000, // unused
    eIsLastFrame = 0x20000,
    eLoopBackwards = 0x40000,
    eIgnorePosOffset = 0x80000,
    eBit21 = 0x100000, // unused
    eBit22_DeadMode = 0x200000, // unused
    eBit23 = 0x400000, // unused
    eBit24 = 0x800000, // unused

    //eBit25_bDecompressDone = 0x1000000,
};

class AnimationBase
{
public:
    static void CreateAnimationArray();
    static void FreeAnimationArray();

    virtual ~AnimationBase() { }

    virtual void VDecode() = 0;

    virtual void VRender(s32 xpos, s32 ypos, PrimHeader** ppOt, s16 width, s32 height) = 0;

    virtual void VCleanUp() = 0;

    static void AnimateAll(DynamicArrayT<AnimationBase>* pAnimations);

    BitField32<AnimFlags> mFlags = {};
    AnimResource mAnimRes;
    u8 mRed = 0;
    u8 mGreen = 0;
    u8 mBlue = 0;
    TPageAbr mRenderMode = TPageAbr::eBlend_0;
    Layer mRenderLayer = Layer::eLayer_0;
    u32 mFrameChangeCounter = 0;

    static DynamicArrayT<AnimationBase>* gAnimations;
};
