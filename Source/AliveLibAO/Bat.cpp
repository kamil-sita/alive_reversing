#include "stdafx_ao.h"
#include "Function.hpp"
#include "Bat.hpp"
#include "ResourceManager.hpp"
#include "Collisions.hpp"
#include "Math.hpp"
#include "Events.hpp"
#include "Game.hpp"
#include "Sfx.hpp"
#include "Abe.hpp"
#include "CameraSwapper.hpp"
#include "stdlib.hpp"
#include "Midi.hpp"

namespace AO {

Bat::Bat(Path_Bat* pTlv, s32 tlvInfo)
{
    mBaseGameObjectTypeId = ReliveTypes::eBat;

    const AnimRecord rec = AO::AnimRec(AnimId::Bat);
    u8** ppRes = ResourceManager::GetLoadedResource(ResourceManager::Resource_Animation, rec.mResourceId, 1, 0);
    
    if (!ppRes)
    {
        mBaseGameObjectFlags.Clear(BaseGameObject::eDrawable_Bit4);
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        return;
    }

    Animation_Init(AnimId::Bat, ppRes);
    mAnim.mRenderLayer = Layer::eLayer_SligGreeterFartsBats_33;

    FP hitX = {};
    FP hitY = {};
    // OG Bug fix, if bat isn't spawned on a line then we crash
    // so mBatLine is checked here and in VUpdate
    sCollisions->Raycast(
        FP_FromInteger(pTlv->mTopLeft.x),
        FP_FromInteger(pTlv->mTopLeft.y),
        FP_FromInteger(pTlv->mBottomRight.x),
        FP_FromInteger(pTlv->mBottomRight.y),
        &mBatLine,
        &hitX,
        &hitY,
        CollisionMask(eTrackLine_8));

    mTlvInfo = tlvInfo;

    if (mBatLine)
    {
        mXPos = FP_FromInteger(mBatLine->mRect.x);
        mYPos = FP_FromInteger(mBatLine->mRect.y);
    }

    mTicksBeforeMoving = pTlv->mTicksBeforeMoving;
    mBatSpeed = FP_FromRaw(pTlv->mSpeed << 8);

    if (pTlv->mScale == Scale_short::eHalf_1)
    {
        mSpriteScale = FP_FromDouble(0.5);
        mScale = Scale::Bg;
        mAnim.mRenderLayer = Layer::eLayer_BeforeShadow_Half_6;
    }
    else
    {
        mSpriteScale = FP_FromInteger(1);
        mScale = Scale::Fg;
        mAnim.mRenderLayer = Layer::eLayer_BeforeShadow_25;
    }

    mBatState = BatStates::eSetTimer_0;
    mAttackTarget = nullptr;
    mAttackDuration = pTlv->mAttackDuration;
}

Bat::~Bat()
{
    if (mAttackTarget)
    {
        mAttackTarget->mBaseGameObjectRefCount--;
    }
    gMap.TLV_Reset(mTlvInfo, -1, 0, 0);
}

void Bat::VScreenChanged()
{
    mBaseGameObjectFlags.Set(BaseGameObject::eDead);
}

void Bat::FlyTo(FP xpos, FP ypos, FP* xSpeed, FP* ySpeed)
{
    const FP xd = FP_Abs(xpos - mEnemyXPos);
    if (xd > FP_FromInteger(350))
    {
        mXPos += *xSpeed;
    }

    const FP yd = FP_Abs(ypos - mEnemyYPos);
    if (yd > FP_FromInteger(200))
    {
        mYPos += *ySpeed;
    }

    mEnemyXPos = xpos;
    mEnemyYPos = ypos;

    *xSpeed = xpos + FP_FromInteger((Math_NextRandom() & 63) - 32);
    *xSpeed = *xSpeed - mXPos;

    *ySpeed = ypos + FP_FromInteger((Math_NextRandom() & 31) - 8);
    *ySpeed = *ySpeed - mYPos;

    const s32 ySpeedi = FP_GetExponent(*ySpeed);
    const s32 xSpeedi = FP_GetExponent(*xSpeed);
    FP x_final = FP_FromInteger(Math_SquareRoot_Int_4511B0((ySpeedi * ySpeedi) + (xSpeedi * xSpeedi)));
    if (FP_GetExponent(x_final) == 0)
    {
        LOG_WARNING("Fixing divide by zero crash");
        x_final += FP_FromInteger(1);
    }

    mVelX = (FP_FromInteger(8) * *xSpeed) / x_final;
    mVelY = (FP_FromInteger(8) * *ySpeed) / x_final;

    mXPos += mVelX;
    mYPos += mVelY;
}

void Bat::VUpdate()
{
    if (EventGet(kEventDeathReset))
    {
        mBaseGameObjectFlags.Set(Options::eDead);
    }

    if (sNumCamSwappers_507668 != 0)
    {
        return;
    }

    FP xSpeed = {};
    FP ySpeed = {};

    switch (mBatState)
    {
        case BatStates::eSetTimer_0:
            mBatState = BatStates::eInit_1;
            mTimer = sGnFrame + mTicksBeforeMoving;
            break;

        case BatStates::eInit_1:
            if (static_cast<s32>(sGnFrame) > mTimer)
            {
                mBatState = BatStates::eStartMoving_2;
                mBatVelX = FP_FromInteger(0);
                mAnim.Set_Animation_Data(AnimId::Bat_Unknown, nullptr);
            }
            break;

        case BatStates::eStartMoving_2:
            if (mBatVelX < mBatSpeed)
            {
                mBatVelX += FP_FromDouble(1.8);
                if (mBatVelX > mBatSpeed)
                {
                    mBatVelX = mBatSpeed;
                }
            }

            if (mBatLine)
            {
                mBatLine = mBatLine->MoveOnLine(&mXPos, &mYPos, mBatVelX);
            }

            if (mAnim.mFlags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                mBatState = BatStates::eFlying_3;
                mAnim.Set_Animation_Data(AnimId::Bat_Flying, nullptr);
                mTimer = sGnFrame + Math_RandomRange(0, 90);
            }
            break;

        case BatStates::eFlying_3:
            if (mBatVelX < mBatSpeed)
            {
                mBatVelX += FP_FromDouble(1.8);
                if (mBatVelX > mBatSpeed)
                {
                    mBatVelX = mBatSpeed;
                }
            }

            if (!(mAnim.mCurrentFrame % 3))
            {
                SfxPlayMono(static_cast<SoundEffect>(Math_RandomRange(SoundEffect::Bat1_41, SoundEffect::Bat2_42) & 0xFF), Math_RandomRange(20, 26), 0);
            }

            if (static_cast<s32>(sGnFrame) > mTimer)
            {
                SND_SEQ_PlaySeq_4775A0(SeqId::eBatSqueaking_18, 1, 1);
                mTimer = sGnFrame + Math_RandomRange(120, 240);
            }

            if (mBatLine)
            {
                mBatLine = mBatLine->MoveOnLine(&mXPos, &mYPos, mBatVelX);
            }

            if (!mBatLine)
            {
                mBaseGameObjectFlags.Set(Options::eDead);
            }

            if (!sActiveHero->field_2A8_flags.Get(Flags_2A8::e2A8_Bit6_bShrivel))
            {
                for (s32 i = 0; i < gBaseAliveGameObjects_4FC8A0->Size(); i++)
                {
                    BaseAliveGameObject* pObjIter = gBaseAliveGameObjects_4FC8A0->ItemAt(i);
                    if (!pObjIter)
                    {
                        break;
                    }

                    if (pObjIter->mBaseGameObjectTypeId != ReliveTypes::SecurityOrb && pObjIter->mBaseGameObjectTypeId != ReliveTypes::eSlig && pObjIter->mBaseGameObjectTypeId != ReliveTypes::eSlog)
                    {
                        const PSX_RECT bObjRect = pObjIter->VGetBoundingRect();
                        if (FP_GetExponent(mXPos) >= bObjRect.x && FP_GetExponent(mXPos) <= bObjRect.w && FP_GetExponent(mYPos) >= bObjRect.y && FP_GetExponent(mYPos) <= bObjRect.h && pObjIter->mSpriteScale == mSpriteScale)
                        {
                            for (s32 j = 0; j < gBaseGameObjects->Size(); j++)
                            {
                                BaseGameObject* pMaybeBat = gBaseGameObjects->ItemAt(j);
                                if (!pMaybeBat)
                                {
                                    break;
                                }

                                if (pMaybeBat->mBaseGameObjectTypeId == ReliveTypes::eBat)
                                {
                                    auto pBat = static_cast<Bat*>(pMaybeBat);

                                    pBat->mAttackTarget = pObjIter;
                                    pBat->mAttackTarget->mBaseGameObjectRefCount++;

                                    pBat->mBatState = BatStates::eAttackTarget_4;
                                    pBat->mAnim.Set_Animation_Data(AnimId::Bat_Flying, nullptr);

                                    pBat->mTimer = 0;
                                    pBat->mAttackDurationTimer = sGnFrame + pBat->mAttackDuration;

                                    pBat->mEnemyXPos = pBat->mAttackTarget->mXPos;
                                    pBat->mEnemyYPos = pBat->mAttackTarget->mYPos;
                                }
                            }
                        }
                    }
                }
            }
            break;

        case BatStates::eAttackTarget_4:
        {
            if (mAttackTarget->mBaseGameObjectFlags.Get(BaseGameObject::eDead) || EventGet(kEventDeathReset))
            {
                mBaseGameObjectFlags.Set(Options::eDead);
                return;
            }

            const PSX_RECT bRect = mAttackTarget->VGetBoundingRect();
            FlyTo(
                FP_FromInteger((bRect.w + bRect.x) / 2),
                FP_FromInteger((bRect.h + bRect.y) / 2),
                &xSpeed,
                &ySpeed);

            if (FP_Abs(xSpeed) < FP_FromInteger(10))
            {
                if (FP_Abs(ySpeed) < FP_FromInteger(20) && static_cast<s32>(sGnFrame) > mTimer)
                {
                    mAttackTarget->VTakeDamage(this);
                    mTimer = sGnFrame + 30;
                    SND_SEQ_PlaySeq_4775A0(SeqId::eBatSqueaking_18, 1, 1);
                }
            }

            if (mAttackDurationTimer <= static_cast<s32>(sGnFrame))
            {
                mAttackTarget->mBaseGameObjectRefCount--;
                mAttackTarget = nullptr;
                mBatState = BatStates::eFlyAwayAndDie_5;
            }
        }
        break;

        case BatStates::eFlyAwayAndDie_5:
        {
            FlyTo(mXPos, mYPos - FP_FromInteger(40), &xSpeed, &ySpeed);
            if (EventGet(kEventDeathReset))
            {
                mBaseGameObjectFlags.Set(Options::eDead);
            }
        }
        break;

        default:
            return;
    }
}

} // namespace AO
