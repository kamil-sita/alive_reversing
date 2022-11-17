#include "stdafx.h"
#include "Door.hpp"
#include "Function.hpp"
#include "stdlib.hpp"
#include "../relive_lib/SwitchStates.hpp"
#include "../relive_lib/Events.hpp"
#include "Sfx.hpp"
#include "Abe.hpp"
#include "MusicTrigger.hpp"
#include "Sound/Midi.hpp"
#include "DDCheat.hpp"
#include "BaseAliveGameObject.hpp"
#include "Grid.hpp"
#include "Map.hpp"
#include "Path.hpp"

struct Door_Info final
{
    s32 field_0_frameTableOffset_closed;
    s32 field_4_frameTableOffset_open;
    s32 field_8_maxW;
    s32 field_C_maxH;
};
ALIVE_ASSERT_SIZEOF(Door_Info, 0x10);

const static AnimId sDoorAnimIdTable[16][2] = {
    {AnimId::Door_Mines_Closed, AnimId::Door_Mines_Open},
    {AnimId::Door_Mines_Closed, AnimId::Door_Mines_Open},
    {AnimId::Door_Temple_Closed, AnimId::Door_Temple_Open},
    {AnimId::Door_Temple_Closed, AnimId::Door_Temple_Open},
    {AnimId::Door_Temple_Closed, AnimId::Door_Temple_Open},
    {AnimId::Door_Feeco_Closed, AnimId::Door_Feeco_Open},
    {AnimId::Door_Barracks_Closed, AnimId::Door_Barracks_Open},
    {AnimId::Door_Temple_Closed, AnimId::Door_Temple_Open},
    {AnimId::Door_Bonewerkz_Closed, AnimId::Door_Bonewerkz_Open},
    {AnimId::Door_Brewery_Closed, AnimId::Door_Brewery_Open},
    {AnimId::Door_Brewery_Closed, AnimId::Door_Brewery_Open},
    {AnimId::Door_Temple_Closed, AnimId::Door_Temple_Open},
    {AnimId::Door_Feeco_Closed, AnimId::Door_Feeco_Open},
    {AnimId::Door_Barracks_Closed, AnimId::Door_Barracks_Open},
    {AnimId::Door_Bonewerkz_Closed, AnimId::Door_Bonewerkz_Open},
    {AnimId::Door_Mines_Closed, AnimId::Door_Mines_Open}};

const static AnimId sTrainDoorAnimIds[] =
{
    AnimId::Door_Train_Closed,
    AnimId::Door_Train_Closing
};

Door::Door()
    : BaseAnimatedWithPhysicsGameObject(0)
{
}

void Door::LoadAnimations()
{
    const AnimId doorAnimIds[] =
    {
        AnimId::Door_Mines_Closed,
        AnimId::Door_Mines_Open,
        AnimId::Door_Temple_Closed,
        AnimId::Door_Temple_Open,
        AnimId::Door_Feeco_Closed,
        AnimId::Door_Feeco_Open,
        AnimId::Door_Barracks_Closed,
        AnimId::Door_Barracks_Open,
        AnimId::Door_Bonewerkz_Closed,
        AnimId::Door_Bonewerkz_Open,
        AnimId::Door_Brewery_Closed,
        AnimId::Door_Brewery_Open,
        AnimId::Door_BarracksMetal_Open,
        AnimId::Door_BarracksMetal_Closed
    };

    for (auto& animId : doorAnimIds)
    {
        mLoadedAnims.push_back(ResourceManagerWrapper::LoadAnimation(animId));
    }
}

Door::Door(relive::Path_Door* pTlvData, const Guid& tlvId)
    : BaseAnimatedWithPhysicsGameObject(0)
{
    SetType(ReliveTypes::eDoor);

    LoadAnimations();

    field_F4_tlvInfo = tlvId;
    field_F8_door_type = pTlvData->mDoorType;
    field_FE_start_state = pTlvData->mStartState;

    if (pTlvData->mCloseOnExit == relive::reliveChoice::eYes)
    {
        if (pTlvData->mTlvSpecificMeaning)
        {
            field_FE_start_state = relive::Path_Door::DoorStates::eClosed;
        }
    }

    field_100_switch_id = pTlvData->mSwitchId;
    if (pTlvData->mSwitchId == 1)
    {
        field_100_switch_id = 0;
    }

    field_FA_door_number = pTlvData->mDoorId;
    if (gMap.mCurrentLevel == EReliveLevelIds::eFeeCoDepot)
    {
        switch (field_FA_door_number)
        {
            case 30000:
                if (gVisitedBonewerkz)
                {
                    field_FE_start_state = relive::Path_Door::DoorStates::eClosed;
                }
                break;

            case 30001:
            case 30004:
                if (gVisitedBarracks)
                {
                    field_FE_start_state = relive::Path_Door::DoorStates::eClosed;
                }
                break;

            case 30002:
                if (gVisitedBonewerkz)
                {
                    SwitchStates_Set(255u, 1);
                }

                if (gVisitedBarracks)
                {
                    SwitchStates_Set(254u, 1);
                }

                if (gVisitedFeecoEnder)
                {
                    SwitchStates_Set(255u, 0);
                    SwitchStates_Set(254u, 0);
                }
                break;

            case 30003:
                if (gVisitedBonewerkz)
                {
                    if (gVisitedBarracks)
                    {
                        if (gVisitedFeecoEnder)
                        {
                            field_FE_start_state = relive::Path_Door::DoorStates::eOpen;
                        }
                    }
                    if (gVisitedBonewerkz)
                    {
                        SwitchStates_Set(250u, 1);
                    }
                }

                if (gVisitedBarracks)
                {
                    SwitchStates_Set(251u, 1);
                }
                if (gVisitedFeecoEnder)
                {
                    SwitchStates_Set(253u, 1);
                }
                break;
            default:
                break;
        }
    }

    if (field_F8_door_type == relive::Path_Door::DoorTypes::eTasksDoor)
    {
        field_102_hub_ids[0] = pTlvData->mHub1;
        field_102_hub_ids[1] = pTlvData->mHub2;
        field_102_hub_ids[2] = pTlvData->mHub3;
        field_102_hub_ids[3] = pTlvData->mHub4;
        field_102_hub_ids[4] = pTlvData->mHub5;
        field_102_hub_ids[5] = pTlvData->mHub6;
        field_102_hub_ids[6] = pTlvData->mHub7;
        field_102_hub_ids[7] = pTlvData->mHub8;

        if (SwitchStates_Get(field_102_hub_ids[0]) && SwitchStates_Get(field_102_hub_ids[1]) && SwitchStates_Get(field_102_hub_ids[2]) && SwitchStates_Get(field_102_hub_ids[3]) && SwitchStates_Get(field_102_hub_ids[4]) && SwitchStates_Get(field_102_hub_ids[5]) && SwitchStates_Get(field_102_hub_ids[6]) && SwitchStates_Get(field_102_hub_ids[7]))
        {
            SwitchStates_Do_Operation(field_100_switch_id, relive::reliveSwitchOp::eSetTrue);
        }
        else
        {
            SwitchStates_Do_Operation(field_100_switch_id, relive::reliveSwitchOp::eSetFalse);
        }
    }

    if (field_FE_start_state == relive::Path_Door::DoorStates::eOpen)
    {
        if (SwitchStates_Get(field_100_switch_id))
        {
            // Its open but the switch id is on which causes it to close
            field_FC_current_state = relive::Path_Door::DoorStates::eClosed;
        }
        else
        {
            field_FC_current_state = relive::Path_Door::DoorStates::eOpen;
        }
    }
    else
    {
        if (SwitchStates_Get(field_100_switch_id))
        {
            // Its closed but the id is on which causes it to open
            field_FC_current_state = relive::Path_Door::DoorStates::eOpen;
        }
        else
        {
            field_FC_current_state = relive::Path_Door::DoorStates::eClosed;
        }
    }

    if ((sActiveHero->mCurrentMotion == eAbeMotions::Motion_114_DoorEnter || sActiveHero->mCurrentMotion == eAbeMotions::Motion_115_DoorExit) && field_FC_current_state == relive::Path_Door::DoorStates::eClosed && field_FA_door_number == sActiveHero->field_1A0_door_id)
    {
        // Force open is abe is in the door
        field_FC_current_state = relive::Path_Door::DoorStates::eOpen;
    }

    if (field_F8_door_type == relive::Path_Door::DoorTypes::eTasksDoorWithSecretMusic)
    {
        field_102_hub_ids[0] = pTlvData->mHub1;
        field_102_hub_ids[1] = pTlvData->mHub2;
        field_102_hub_ids[2] = pTlvData->mHub3;
        field_102_hub_ids[3] = pTlvData->mHub4;
        field_102_hub_ids[4] = pTlvData->mHub5;
        field_102_hub_ids[5] = pTlvData->mHub6;
        field_102_hub_ids[6] = pTlvData->mHub7;
        field_102_hub_ids[7] = pTlvData->mHub8;
    }

    const AnimId closedDoor = sDoorAnimIdTable[static_cast<s32>(MapWrapper::ToAE(gMap.mCurrentLevel))][0];
    const AnimId openDoor = sDoorAnimIdTable[static_cast<s32>(MapWrapper::ToAE(gMap.mCurrentLevel))][1];

    const AnimRecord& openRec = AnimRec(openDoor);
    if (openRec.mFrameTableOffset == 0)
    {
        mBaseGameObjectFlags.Clear(BaseGameObject::eDrawable_Bit4);
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        return;
    }

    if (field_FC_current_state == relive::Path_Door::DoorStates::eOpen)
    {
        if (gMap.mOverlayId == 108)
        {
            Animation_Init(GetAnimRes(AnimId::Door_BarracksMetal_Open));
        }
        else
        {
            Animation_Init(GetAnimRes(openDoor));
        }
    }
    else
    {
        if (gMap.mOverlayId == 108)
        {
            Animation_Init(GetAnimRes(AnimId::Door_BarracksMetal_Closed));
        }
        else
        {
            Animation_Init(GetAnimRes(closedDoor));
        }
    }

    if (pTlvData->mScale != relive::reliveScale::eFull)
    {
        if (pTlvData->mScale == relive::reliveScale::eHalf)
        {
            SetSpriteScale(FP_FromDouble(0.5));
            SetScale(Scale::Bg);
            GetAnimation().SetRenderLayer(Layer::eLayer_BeforeShadow_Half_6);
        }
    }
    else
    {
        SetSpriteScale(FP_FromInteger(1));
        SetScale(Scale::Fg);
        GetAnimation().SetRenderLayer(Layer::eLayer_BeforeShadow_25);
    }

    FP* xOff = &mXPos;
    FP* yOff = &mYPos;

    FP tlvXMid = FP_FromInteger((pTlvData->mTopLeftX + pTlvData->mBottomRightX) / 2);
    PathLine* pathLine = nullptr;

    if (sCollisions->Raycast(
            tlvXMid,
            FP_FromInteger(pTlvData->mTopLeftY),
            tlvXMid,
            FP_FromInteger(pTlvData->mBottomRightY),
            &pathLine,
            xOff,
            yOff,
            (GetScale() == Scale::Fg) ? kFgFloorCeilingOrWalls : kBgFloorCeilingOrWalls))
    {
        // Move up off the line we hit
        *yOff -= FP_FromInteger(12) * GetSpriteScale();

        // Snap on X
        *xOff = FP_FromInteger(SnapToXGrid(GetSpriteScale(), FP_GetExponent(*xOff)));
    }
    else
    {
        // Couldn't glue to the floor.. just use the TLV pos
        *xOff = FP_FromInteger(pTlvData->mTopLeftX + 12);
        *yOff = FP_FromInteger(pTlvData->mTopLeftY + 24);
    }

    // Add on the TLV offset
    *xOff += FP_FromInteger(pTlvData->mDoorOffsetX);
    *yOff += FP_FromInteger(pTlvData->mDoorOffsetY);

    // Another OWI special
    FP yAdjustHack = {};
    if ((gMap.mCurrentLevel != EReliveLevelIds::eBarracks && gMap.mCurrentLevel != EReliveLevelIds::eBarracks_Ender) || gMap.mOverlayId == 108)
    {
        if (gMap.mCurrentLevel == EReliveLevelIds::eBonewerkz || gMap.mCurrentLevel == EReliveLevelIds::eBonewerkz_Ender)
        {
            yAdjustHack = FP_FromInteger(10) * GetSpriteScale();
        }
    }
    else
    {
        yAdjustHack = FP_FromInteger(14) * GetSpriteScale();
    }
    *yOff += yAdjustHack;

    if (field_FC_current_state == relive::Path_Door::DoorStates::eOpen)
    {
        GetAnimation().mFlags.Clear(AnimFlags::eRender);
    }

    GetAnimation().mFlags.Clear(AnimFlags::eAnimate);
    mVisualFlags.Set(VisualFlags::eDoPurpleLightEffect);
}

bool Door::vIsOpen()
{
    return field_FC_current_state == relive::Path_Door::DoorStates::eOpen;
}

void Door::vOpen()
{
    if (field_FC_current_state != relive::Path_Door::DoorStates::eOpen)
    {
        field_FC_current_state = relive::Path_Door::DoorStates::eOpening;
    }
}

void Door::vClose()
{
    if (field_FC_current_state != relive::Path_Door::DoorStates::eClosed)
    {
        field_FE_start_state = relive::Path_Door::DoorStates::eClosed;
        field_FC_current_state = relive::Path_Door::DoorStates::eClosing;
        relive::Path_TLV* pTlv = sPathInfo->TLV_From_Offset_Lvl_Cam(field_F4_tlvInfo);
        pTlv->mTlvSpecificMeaning = 1;
    }
}

void Door::vSetOpen()
{
    field_FC_current_state = relive::Path_Door::DoorStates::eOpen;
}

void Door::vSetClosed()
{
    field_FC_current_state = relive::Path_Door::DoorStates::eClosed;
}

void Door::PlaySound()
{
    s16 volume = 0;
    if (field_F8_door_type != relive::Path_Door::DoorTypes::eBasicDoor || GetSpriteScale() != FP_FromInteger(1))
    {
        volume = 60;
    }
    else
    {
        volume = 90;
    }

    SFX_Play_Pitch(relive::SoundEffects::DoorEffect, volume, 900);
    SFX_Play_Pitch(relive::SoundEffects::DoorEffect, volume, 0);
}

Door::~Door()
{
    Path::TLV_Reset(field_F4_tlvInfo, -1, 0, 0);
}

void Door::VUpdate()
{
    if (EventGet(kEventDeathReset))
    {
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
    }

    if (sActiveHero->mCurrentMotion == eAbeMotions::Motion_114_DoorEnter || sActiveHero->mCurrentMotion == eAbeMotions::Motion_115_DoorExit)
    {
        if (field_FC_current_state == relive::Path_Door::DoorStates::eClosed && field_FA_door_number == sActiveHero->field_1A0_door_id)
        {
            GetAnimation().mFlags.Clear(AnimFlags::eRender);
            field_FC_current_state = relive::Path_Door::DoorStates::eOpen;
        }
    }
    else
    {
        field_FA_door_number = -1;
        if (field_F8_door_type == relive::Path_Door::DoorTypes::eTasksDoorWithSecretMusic || field_F8_door_type == relive::Path_Door::DoorTypes::eTasksDoor)
        {
            if (SwitchStates_Get(field_102_hub_ids[0])
                && SwitchStates_Get(field_102_hub_ids[1])
                && SwitchStates_Get(field_102_hub_ids[2])
                && SwitchStates_Get(field_102_hub_ids[3])
                && SwitchStates_Get(field_102_hub_ids[4])
                && SwitchStates_Get(field_102_hub_ids[5])
                && SwitchStates_Get(field_102_hub_ids[6])
                && SwitchStates_Get(field_102_hub_ids[7]))
            {
                if (!SwitchStates_Get(field_100_switch_id) && field_F8_door_type == relive::Path_Door::DoorTypes::eTasksDoorWithSecretMusic)
                {
                    SND_SEQ_Play(SeqId::SecretMusic_32, 1, 127, 127);
                    relive_new MusicTrigger(relive::Path_MusicTrigger::MusicTriggerMusicType::eChime, relive::Path_MusicTrigger::TriggeredBy::eTimer, 0, 0);
                }
                SwitchStates_Do_Operation(field_100_switch_id, relive::reliveSwitchOp::eSetTrue);
            }
            else
            {
                SwitchStates_Do_Operation(field_100_switch_id, relive::reliveSwitchOp::eSetFalse);
            }
        }
        switch (field_FC_current_state)
        {
            case relive::Path_Door::DoorStates::eOpen:
                GetAnimation().mFlags.Clear(AnimFlags::eRender);

                if ((!field_FE_start_state && SwitchStates_Get(field_100_switch_id))
                    || (field_FE_start_state == relive::Path_Door::DoorStates::eClosed && !SwitchStates_Get(field_100_switch_id)))
                {
                    field_FC_current_state = relive::Path_Door::DoorStates::eClosing;
                    if (gMap.mOverlayId == 108)
                    {
                        GetAnimation().Set_Animation_Data(GetAnimRes(AnimId::Door_BarracksMetal_Open));
                    }
                    else
                    {
                        GetAnimation().Set_Animation_Data(GetAnimRes(sDoorAnimIdTable[static_cast<s32>(MapWrapper::ToAE(gMap.mCurrentLevel))][1]));
                    }

                    GetAnimation().mFlags.Clear(AnimFlags::eLoopBackwards);
                    GetAnimation().mFlags.Set(AnimFlags::eRender);
                }
                break;

            case relive::Path_Door::DoorStates::eClosed:
                GetAnimation().mFlags.Set(AnimFlags::eRender);
                GetAnimation().mFlags.Set(AnimFlags::eAnimate);

                if ((field_FE_start_state == relive::Path_Door::DoorStates::eClosed && SwitchStates_Get(field_100_switch_id)) || (field_FE_start_state == relive::Path_Door::DoorStates::eOpen && !SwitchStates_Get(field_100_switch_id)))
                {
                    field_FC_current_state = relive::Path_Door::DoorStates::eOpening;
                    if (gMap.mOverlayId == 108)
                    {
                        GetAnimation().Set_Animation_Data(GetAnimRes(AnimId::Door_BarracksMetal_Open));
                    }
                    else
                    {
                        GetAnimation().Set_Animation_Data(GetAnimRes(sDoorAnimIdTable[static_cast<s32>(MapWrapper::ToAE(gMap.mCurrentLevel))][1]));
                    }

                    GetAnimation().SetFrame(3);
                    GetAnimation().mFlags.Set(AnimFlags::eLoopBackwards);
                    GetAnimation().mFlags.Set(AnimFlags::eRender);
                    PlaySound();
                }
                break;

            case relive::Path_Door::DoorStates::eOpening:
                GetAnimation().mFlags.Set(AnimFlags::eRender);
                GetAnimation().mFlags.Set(AnimFlags::eAnimate);

                if (GetAnimation().mFlags.Get(AnimFlags::eIsLastFrame))
                {
                    field_FC_current_state = relive::Path_Door::DoorStates::eOpen;
                }
                break;

            case relive::Path_Door::DoorStates::eClosing:
                GetAnimation().mFlags.Set(AnimFlags::eRender);
                GetAnimation().mFlags.Set(AnimFlags::eAnimate);

                if (GetAnimation().mFlags.Get(AnimFlags::eIsLastFrame))
                {
                    field_FC_current_state = relive::Path_Door::DoorStates::eClosed;
                    PlaySound();
                }
                break;

            default:
                return;
        }
    }
}

void Door::VScreenChanged()
{
    mBaseGameObjectFlags.Set(BaseGameObject::eDead);
}

// ================================================================================================

FP sTrainDoorXPos_BB4AA0 = {};
FP sTrainDoorYPos_BB4AA4 = {};

void TrainDoor::LoadAnimations()
{
    for (auto& animId : sTrainDoorAnimIds)
    {
        mLoadedAnims.push_back(ResourceManagerWrapper::LoadAnimation(animId));
    }
}

TrainDoor::TrainDoor(relive::Path_TrainDoor* pTlv, const Guid& tlvId)
{
    SetType(ReliveTypes::eDoor);
    field_F4_tlvInfo = tlvId;

    LoadAnimations();

    Animation_Init(GetAnimRes(AnimId::Door_Train_Closing));

    mXPos = FP_FromInteger(pTlv->mTopLeftX + 12);
    mYPos = FP_FromInteger(pTlv->mTopLeftY + 24);

    sTrainDoorXPos_BB4AA0 = mXPos;
    sTrainDoorYPos_BB4AA4 = mYPos;

    if (pTlv->mTlvSpecificMeaning)
    {
        GetAnimation().Set_Animation_Data(GetAnimRes(AnimId::Door_Train_Closed));
        field_FC_current_state = relive::Path_Door::DoorStates::eClosed;
    }
    else
    {
        GetAnimation().mFlags.Clear(AnimFlags::eAnimate);
        GetAnimation().mFlags.Clear(AnimFlags::eRender);
        field_FC_current_state = relive::Path_Door::DoorStates::eOpen;
    }
    GetAnimation().mFlags.Set(AnimFlags::eFlipX, pTlv->mDirection == relive::reliveXDirection::eRight);
}

TrainDoor::~TrainDoor()
{
    if (field_FC_current_state == relive::Path_Door::DoorStates::eOpen)
    {
        Path::TLV_Reset(field_F4_tlvInfo, -1, 0, 0);
    }
    else
    {
        Path::TLV_Reset(field_F4_tlvInfo, 1, 0, 0);
    }
}

void TrainDoor::VUpdate()
{
    if (field_FC_current_state == relive::Path_Door::DoorStates::eOpen)
    {
        // Wait for Abe to GTFO
        if (sActiveHero->mCurrentMotion != eAbeMotions::Motion_115_DoorExit && sActiveHero->mCurrentMotion != eAbeMotions::Motion_114_DoorEnter)
        {
            // Then close
            GetAnimation().Set_Animation_Data(GetAnimRes(AnimId::Door_Train_Closing));
            GetAnimation().mFlags.Set(AnimFlags::eAnimate);
            GetAnimation().mFlags.Set(AnimFlags::eRender);
            field_FC_current_state = relive::Path_Door::DoorStates::eClosed;
        }
    }

    mXPos = sTrainDoorXPos_BB4AA0 + FP_FromInteger(sTweakX_5C1BD0);
    mYPos = sTrainDoorYPos_BB4AA4 + FP_FromInteger(sTweakY_5C1BD4);
}
