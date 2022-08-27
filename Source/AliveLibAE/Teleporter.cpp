#include "stdafx.h"
#include "Teleporter.hpp"
#include "Function.hpp"
#include "../relive_lib/ScreenManager.hpp"
#include "SwitchStates.hpp"
#include "stdlib.hpp"
#include "Map.hpp"
#include "../relive_lib/ObjectIds.hpp"
#include "Abe.hpp"
#include "Sfx.hpp"
#include "Particle.hpp"
#include "Game.hpp"
#include "../relive_lib/Events.hpp"
#include "Spark.hpp"
#include "ParticleBurst.hpp"
#include "Electrocute.hpp"

Teleporter::Teleporter(relive::Path_Teleporter* pTlv, u32 tlvInfo)
    : BaseGameObject(TRUE, 0)
{
    field_4C_pTlv = pTlv; // TODO: Don't think this is used, and it can become a dangling ptr?
    field_34_mTlvData = pTlv->field_10_data;
    field_20_tlvInfo = tlvInfo;

    field_24_global_y1 = FP_GetExponent((FP_FromInteger(pTlv->mTopLeftY) - pScreenManager->CamYPos()));
    field_28_global_y2 = FP_GetExponent((FP_FromInteger(pTlv->mBottomRightY) - pScreenManager->CamYPos()));
    field_26_global_x1 = FP_GetExponent((FP_FromInteger(pTlv->mTopLeftX) - pScreenManager->CamXPos()));
    field_2A_global_x2 = FP_GetExponent((FP_FromInteger(pTlv->mBottomRightX) - pScreenManager->CamXPos()));

    field_2C_switch_state = SwitchStates_Get(field_34_mTlvData.mSwitchId);

    field_54_effect_created = 0;

    field_32_bDestroySelf = 0;
    field_30_state = TeleporterState::eWaitForSwitchOn_0;
    field_50_objId = -1;
}

Teleporter::~Teleporter()
{
    Path::TLV_Reset(field_20_tlvInfo, -1, 0, 0);
}

void Teleporter::VScreenChanged()
{
    if (gMap.mCurrentLevel != gMap.mNextLevel)
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }
    field_32_bDestroySelf = 1;
}

Electrocute* Teleporter::Create_ElectrocuteEffect()
{
    return relive_new Electrocute(sControlledCharacter, TRUE, FALSE);
}

const PSX_Point kSparkOffs_563988[8] = {
    {-15, 46},
    {-20, 29},
    {-15, 12},
    {0, 2},
    {16, 12},
    {19, 28},
    {15, 45},
    {0, 0}};

void Teleporter::SpawnRingSparks(Path_Teleporter_Data* pTlvData)
{
    PSX_Point abeSpawnPos = {};
    gMap.Get_Abe_Spawn_Pos(&abeSpawnPos);

    const s16 xOrg = pTlvData->mElectricX - abeSpawnPos.x;
    const s16 yOrg = pTlvData->mElectricY - abeSpawnPos.y;

    for (auto& sparkOffs : kSparkOffs_563988)
    {
        s32 sparkX = 0;
        s32 sparkY = 0;
        if (pTlvData->mScale != Scale_short::eFull_0)
        {
            sparkX = xOrg + (sparkOffs.x / 2);
            sparkY = yOrg + (sparkOffs.y / 2);
        }
        else
        {
            sparkX = xOrg + (sparkOffs.x);
            sparkY = yOrg + (sparkOffs.y);
        }

        relive_new Spark(FP_FromInteger(sparkX), FP_FromInteger(sparkY), FP_FromInteger(1), 9, -31, 159, SparkType::eBigChantParticle_1);
    }
}

void Teleporter::VUpdate()
{
    Electrocute* pObj = static_cast<Electrocute*>(sObjectIds.Find(field_50_objId, ReliveTypes::eElectrocute));

    switch (field_30_state)
    {
        case TeleporterState::eWaitForSwitchOn_0:
        {
            if (field_32_bDestroySelf)
            {
                mBaseGameObjectFlags.Set(BaseGameObject::eDead);
            }

            if (SwitchStates_Get(field_34_mTlvData.mSwitchId) == field_2C_switch_state)
            {
                return;
            }

            field_2C_switch_state = SwitchStates_Get(field_34_mTlvData.mSwitchId);

            if (!sPathInfo->TLV_Get_At_4DB4B0(
                    FP_GetExponent(sControlledCharacter->mXPos),
                    FP_GetExponent(sControlledCharacter->mYPos),
                    FP_GetExponent(sControlledCharacter->mXPos),
                    FP_GetExponent(sControlledCharacter->mYPos),
                    ReliveTypes::eTeleporter))
            {
                return;
            }

            if (sControlledCharacter->mBaseAliveGameObjectFlags.Get(Flags_114::e114_Bit10_Teleporting))
            {
                return;
            }

            field_30_state = TeleporterState::eIntoTeleporter_1;
            field_50_objId = Teleporter::Create_ElectrocuteEffect()->mBaseGameObjectId;

            SFX_Play_Pitch(SoundEffect::Zap1_49, 60, -400);
            sControlledCharacter->mBaseAliveGameObjectFlags.Set(Flags_114::e114_Bit10_Teleporting);

            SpawnRingSparks(&field_34_mTlvData);
        }
        break;

        case TeleporterState::eIntoTeleporter_1:
        {
            if (pObj)
            {
                if (pObj->VSub_4E6630() || field_54_effect_created)
                {
                    if (!(pObj->mBaseGameObjectFlags.Get(BaseGameObject::eDead)))
                    {
                        return;
                    }
                }

                // Only create the effects once (disable this if you like a crazy amount of sparks and things)
                if (!field_54_effect_created)
                {
                    // Spawn the falling "red" sparks from Abe's feet that appear after you enter the teleporter
                    if (field_34_mTlvData.mScale != Scale_short::eFull_0)
                    {
                        // Steam/smoke effect at Abe's body
                        New_Smoke_Particles(
                            sControlledCharacter->mXPos,
                            sControlledCharacter->mYPos - FP_FromInteger(9), // 18/2
                            sControlledCharacter->mSpriteScale,
                            3,
                            128u,
                            128u,
                            128u);

                        relive_new ParticleBurst(sControlledCharacter->mXPos,
                                              sControlledCharacter->mYPos - FP_FromInteger(9), // 18/2
                                              9u,
                                              FP_FromDouble(0.5),
                                              BurstType::eBigRedSparks_3,
                                              9);
                    }
                    else
                    {
                        // Steam/smoke effect at Abe's body
                        New_Smoke_Particles(
                            sControlledCharacter->mXPos,
                            sControlledCharacter->mYPos - FP_FromInteger(18),
                            sControlledCharacter->mSpriteScale,
                            3,
                            128u,
                            128u,
                            128u);

                       relive_new ParticleBurst(sControlledCharacter->mXPos,
                                                                    sControlledCharacter->mYPos - FP_FromInteger(18),
                                                                    9u,
                                                                    FP_FromInteger(1),
                                                                    BurstType::eBigRedSparks_3,
                                                                    9);
                    }
                    field_54_effect_created = 1;
                }

                if (!(pObj->mBaseGameObjectFlags.Get(BaseGameObject::eDead)))
                {
                    return;
                }
            }

            sControlledCharacter->mAnim.mFlags.Clear(AnimFlags::eBit3_Render);

            gMap.mTeleporterTransition = 1;

            const CameraSwapEffects effect = kPathChangeEffectToInternalScreenChangeEffect_55D55C[field_34_mTlvData.mWipeEffect];
            s16 bForceChange = 0;
            if (effect == CameraSwapEffects::ePlay1FMV_5 || effect == CameraSwapEffects::eUnknown_11)
            {
                bForceChange = 1;
            }

            gMap.SetActiveCam(
                MapWrapper::FromAE(field_34_mTlvData.mDestLevel),
                field_34_mTlvData.mDestPath,
                field_34_mTlvData.mDestCamera,
                effect,
                field_34_mTlvData.mMovieId,
                bForceChange);

            sControlledCharacter->SetUpdateDelay(3);
            sActiveHero->field_1A0_door_id = field_34_mTlvData.mOtherTeleporterId;
            field_30_state = TeleporterState::eTeleporting_2;
        }
        break;

        case TeleporterState::eTeleporting_2:
        {
            gMap.mTeleporterTransition = 0;

            relive::Path_Teleporter* pTeleporterTlv = static_cast<relive::Path_Teleporter*>(sPathInfo->TLV_First_Of_Type_In_Camera(ReliveTypes::eTeleporter, 0));
            Path_Teleporter_Data tlvData = pTeleporterTlv->mData;
            if (tlvData.mTeleporterId != field_34_mTlvData.mOtherTeleporterId)
            {
                while (pTeleporterTlv)
                {
                    pTeleporterTlv = static_cast<relive::Path_Teleporter*>(sPathInfo->TLV_Next_Of_Type(pTeleporterTlv, ReliveTypes::eTeleporter));
                    tlvData = pTeleporterTlv->mData;

                    if (tlvData.mTeleporterId == field_34_mTlvData.mOtherTeleporterId)
                    {
                        break;
                    }
                }
            }

            SFX_Play_Pitch(SoundEffect::Zap1_49, 60, -300, tlvData.mScale != Scale_short::eFull_0 ? FP_FromDouble(0.5) : FP_FromInteger(1));
            SpawnRingSparks(&tlvData);

            if (tlvData.mScale != Scale_short::eFull_0)
            {
                if (sControlledCharacter->mScale == Scale::Fg)
                {
                    sControlledCharacter->mVelX *= FP_FromDouble(0.5);
                    sControlledCharacter->mVelY *= FP_FromDouble(0.5);
                }
                sControlledCharacter->mSpriteScale = FP_FromDouble(0.5);
                sControlledCharacter->mAnim.mRenderLayer = Layer::eLayer_AbeMenu_Half_13;
                sControlledCharacter->mScale = Scale::Bg;
            }
            else
            {
                if (sControlledCharacter->mScale == Scale::Bg)
                {
                    sControlledCharacter->mVelX *= FP_FromInteger(2);
                    sControlledCharacter->mVelY *= FP_FromInteger(2);
                }
                sControlledCharacter->mSpriteScale = FP_FromInteger(1);
                sControlledCharacter->mAnim.mRenderLayer = Layer::eLayer_AbeMenu_32;
                sControlledCharacter->mScale = Scale::Fg;
            }

            // XPos = TLV xpos + TLV middle point
            sControlledCharacter->mXPos = FP_FromInteger(pTeleporterTlv->mTopLeftX) + FP_FromInteger((pTeleporterTlv->Width()) / 2);

            sControlledCharacter->MapFollowMe(TRUE);

            PathLine* pPathLine = nullptr;
            FP hitX = {};
            FP hitY = {};
            if (sCollisions->Raycast(
                    sControlledCharacter->mXPos,
                    FP_FromInteger(pTeleporterTlv->mTopLeftY),
                    sControlledCharacter->mXPos,
                    FP_FromInteger(pTeleporterTlv->mBottomRightY),
                    &pPathLine,
                    &hitX,
                    &hitY,
                    sControlledCharacter->mScale == Scale::Fg ? kFgFloorCeilingOrWalls : kBgFloorCeilingOrWalls))
            {
                sControlledCharacter->BaseAliveGameObjectCollisionLine = pPathLine;
                sControlledCharacter->mYPos = hitY;
            }
            else
            {
                sControlledCharacter->BaseAliveGameObjectCollisionLine = nullptr;
                sControlledCharacter->mYPos = FP_FromInteger(pTeleporterTlv->mTopLeftY);
                sControlledCharacter->BaseAliveGameObjectLastLineYPos = sControlledCharacter->mYPos;
            }
            field_30_state = TeleporterState::eOutOfTeleporter_4;
        }
        break;

        case TeleporterState::eOutOfTeleporter_4:
        {
            // Visual effects.
            const PSX_RECT bRect = sControlledCharacter->VGetBoundingRect();

            // White flash in the middle of Abe's body.
            New_DestroyOrCreateObject_Particle(
                FP_FromInteger((bRect.x + bRect.w) / 2),
                FP_FromInteger((bRect.y + bRect.h) / 2) + (sControlledCharacter->mSpriteScale * FP_FromInteger(60)),
                sControlledCharacter->mSpriteScale);

            // Spawn the falling "red" sparks from Abe's feet that appear after you've arrived at the destination.
            if (sControlledCharacter->mSpriteScale == FP_FromDouble(0.5))
            {
                relive_new ParticleBurst(sControlledCharacter->mXPos,
                                                            sControlledCharacter->mYPos - FP_FromInteger(9),
                                                            6u,
                                                            FP_FromDouble(0.5),
                                                            BurstType::eBigRedSparks_3,
                                                            9);
            }
            else
            {
                relive_new ParticleBurst(sControlledCharacter->mXPos,
                                                            sControlledCharacter->mYPos - FP_FromInteger(18),
                                                            6u,
                                                            FP_FromInteger(1),
                                                            BurstType::eBigRedSparks_3,
                                                            9);
            }

            field_54_effect_created = 0;
            sControlledCharacter->mAnim.mFlags.Set(AnimFlags::eBit3_Render);
            sControlledCharacter->mBaseAliveGameObjectFlags.Clear(Flags_114::e114_Bit10_Teleporting);
            field_2C_switch_state = SwitchStates_Get(field_34_mTlvData.mSwitchId);
            field_30_state = TeleporterState::eWaitForSwitchOn_0;
        }
        break;
    }
}
