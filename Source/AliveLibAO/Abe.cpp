#include "stdafx_ao.h"
#include "Function.hpp"
#include "Abe.hpp"
#include "BellSong.hpp"
#include "Blood.hpp"
#include "BoomMachine.hpp"
#include "Bullet.hpp"
#include "CheatController.hpp"
#include "HoistRocksEffect.hpp"
#include "DeathBirdParticle.hpp"
#include "DemoPlayback.hpp"
#include "Door.hpp"
#include "Dove.hpp"
#include "ThrowableArray.hpp"
#include "Elum.hpp"
#include "Flash.hpp"
#include "LiftPoint.hpp"
#include "ResourceManager.hpp"
#include "Shadow.hpp"
#include "Game.hpp"
#include "stdlib.hpp"
#include "Midi.hpp"
#include "Movie.hpp"
#include "CircularFade.hpp"
#include "DeathFadeOut.hpp"
#include "Throwable.hpp"
#include "OrbWhirlWind.hpp"
#include "Particle.hpp"
#include "PossessionFlicker.hpp"
#include "PullRingRope.hpp"
#include "PsxDisplay.hpp"
#include "ScreenManager.hpp"
#include "ThrowableTotalIndicator.hpp"
#include "Events.hpp"
#include "DDCheat.hpp"
#include "LiftPoint.hpp"
#include "Well.hpp"
#include "Input.hpp"
#include "PullRingRope.hpp"
#include "ScreenShake.hpp"
#include "Sfx.hpp"
#include "MusicController.hpp"
#include "AbilityRing.hpp"
#include "MusicTrigger.hpp"
#include "Math.hpp"
#include "Input.hpp"
#include "Grenade.hpp"
#include "Collisions.hpp"
#include "BirdPortal.hpp"
#include "Rope.hpp"
#include "SaveGame.hpp"
#include "BeeSwarm.hpp"
#include "Shrykull.hpp"
#include "Lever.hpp"
#include "GameSpeak.hpp"
#include "ZBall.hpp"
#include "Gibs.hpp"

#include "Sys_common.hpp"

#include "TestAnimation.hpp"

namespace AO {

ALIVE_VAR(1, 0x5076E4, s16, gAbeInvulnerableCheat_5076E4, 0);
ALIVE_VAR(1, 0x5076F8, s16, gAbeInvisibleCheat_5076F8, 0);

ALIVE_VAR_EXTERN(SaveData, gSaveBuffer_505668);

using TAbeMotionFunction = decltype(&Abe::Motion_0_Idle_423520);

#define MAKE_STRINGS(VAR) #VAR,
const char_type* const sAbeMotionNames[] = {
    AO_ABE_MOTIONS_ENUM(MAKE_STRINGS)};

const TAbeMotionFunction sAbeMotionMachineTable_4C5F08[] = {
    &Abe::Motion_0_Idle_423520,
    &Abe::Motion_1_WalkLoop_423F90,
    &Abe::Motion_2_StandingTurn_426040,
    &Abe::Motion_3_Fall_42E7F0,
    &Abe::Motion_4_WalkToIdle_4243C0,
    &Abe::Motion_5_MidWalkToIdle_424490,
    &Abe::Motion_6_WalkBegin_424300,
    &Abe::Motion_7_Speak_42F950,
    &Abe::Motion_8_Speak_42F9D0,
    &Abe::Motion_9_Speak_42FA50,
    &Abe::Motion_10_Speak_42FAD0,
    &Abe::Motion_11_Speak_42FB50,
    &Abe::Motion_12_Speak_42FBD0,
    &Abe::Motion_13_Speak_42FC50,
    &Abe::Motion_14_Speak_42FCD0,
    &Abe::Motion_15_Null_42A210,
    &Abe::Motion_16_HoistBegin_426E40,
    &Abe::Motion_17_HoistIdle_4269E0,
    &Abe::Motion_18_HoistLand_426EB0,
    &Abe::Motion_19_CrouchIdle_4284C0,
    &Abe::Motion_20_CrouchToStand_428AF0,
    &Abe::Motion_21_StandToCrouch_427F40,
    &Abe::Motion_22_CrouchSpeak_428A30,
    &Abe::Motion_23_CrouchSpeak_428A90,
    &Abe::Motion_24_RollBegin_427A20,
    &Abe::Motion_25_RollLoop_427BB0,
    &Abe::Motion_26_RollEnd_427EA0,
    &Abe::Motion_27_RunSlideStop_425B60,
    &Abe::Motion_28_RunTurn_425CE0,
    &Abe::Motion_29_HopBegin_4267B0,
    &Abe::Motion_30_HopMid_4264D0,
    &Abe::Motion_31_HopLand_426940,
    &Abe::Motion_32_RunJumpBegin_427440,
    &Abe::Motion_33_RunJumpMid_426FA0,
    &Abe::Motion_34_RunJumpLand_427560,
    &Abe::Motion_35_RunLoop_425060,
    &Abe::Motion_36_DunnoBegin_423260,
    &Abe::Motion_37_DunnoMid_4232C0,
    &Abe::Motion_38_DunnoEnd_423310,
    &Abe::Motion_39_CrouchTurn_4288C0,
    &Abe::Motion_40_RunToRoll_427AE0,
    &Abe::Motion_41_StandingToRun_425530,
    &Abe::Motion_42_SneakLoop_424BB0,
    &Abe::Motion_43_WalkToSneak_424790,
    &Abe::Motion_44_SneakToWalk_4249A0,
    &Abe::Motion_45_MidWalkToSneak_424890,
    &Abe::Motion_46_MidSneakToWalk_424AA0,
    &Abe::Motion_47_SneakBegin_424ED0,
    &Abe::Motion_48_SneakToIdle_424F80,
    &Abe::Motion_49_MidSneakToIdle_424FF0,
    &Abe::Motion_50_WalkToRun_424560,
    &Abe::Motion_51_MidWalkToRun_424670,
    &Abe::Motion_52_RunToWalk_4255E0,
    &Abe::Motion_53_MidRunToWalk_4256E0,
    &Abe::Motion_54_RunTurnToRun_425EA0,
    &Abe::Motion_55_RunTurnToWalk_425F70,
    &Abe::Motion_56_RunJumpLandRun_4278E0,
    &Abe::Motion_57_RunJumpLand_Walk_427980,
    &Abe::Motion_58_ToSpeak_42F8D0,
    &Abe::Motion_59_DeathDropFall_42CBE0,
    &Abe::Motion_60_Dead_42C4C0,
    &Abe::Motion_61_Respawn_42CD20,
    &Abe::Motion_62_LoadedSaveSpawn_45ADD0,
    &Abe::Motion_63_TurnToRun_42A0A0,
    &Abe::Motion_64_LedgeAscend_428B60,
    &Abe::Motion_65_LedgeDescend_428C00,
    &Abe::Motion_66_LedgeHang_428D90,
    &Abe::Motion_67_ToOffScreenHoist_428C50,
    &Abe::Motion_68_LedgeHangWobble_428E50,
    &Abe::Motion_69_RingRopePullHang_4299B0,
    &Abe::Motion_70_Knockback_428FB0,
    &Abe::Motion_71_KnockbackGetUp_429240,
    &Abe::Motion_72_PushWall_4292A0,
    &Abe::Motion_73_RollingKnockback_4291D0,
    &Abe::Motion_74_JumpIntoWell_430EC0,
    &Abe::Motion_75_ToInsideOfAWellLocal_431090,
    &Abe::Motion_76_ToWellShotOut_431720,
    &Abe::Motion_77_WellBegin_430F10,
    &Abe::Motion_78_InsideWellLocal_4310A0,
    &Abe::Motion_79_WellShotOut_431730,
    &Abe::Motion_80_ToWellBegin_430EF0,
    &Abe::Motion_81_InsideWellExpress_431320,
    &Abe::Motion_82_WellExpressShotOut_4315A0,
    &Abe::Motion_83_ToWellBegin_430F00,
    &Abe::Motion_84_ToInsideWellLocal_431080,
    &Abe::Motion_85_ToWellShotOut_431710,
    &Abe::Motion_86_FallLandDie_42EDD0,
    &Abe::Motion_87_ToFall_428FA0,
    &Abe::Motion_88_HandstoneBegin_430590,
    &Abe::Motion_89_HandstoneEnd_430E80,
    &Abe::Motion_90_GrenadeMachineUse_430EA0,
    &Abe::Motion_91_FallingFromGrab_429780,
    &Abe::Motion_92_ForceDownFromHoist_4297C0,
    &Abe::Motion_93_WalkOffEdge_429840,
    &Abe::Motion_94_RunOffEdge_429860,
    &Abe::Motion_95_SneakOffEdge_429880,
    &Abe::Motion_96_HopToFall_4298A0,
    &Abe::Motion_97_RunJumpToFall_429930,
    &Abe::Motion_98_LandSoft_42ED40,
    &Abe::Motion_99_HoistBeginLong_426DC0,
    &Abe::Motion_100_RollOffLedge_429950,
    &Abe::Motion_101_LeverUse_429970,
    &Abe::Motion_102_ElumWalkLoop_42DCA0,
    &Abe::Motion_103_ElumIdle_42DCD0,
    &Abe::Motion_104_ElumRunSlideStop_42DF00,
    &Abe::Motion_105_ElumRunTurn_42DF10,
    &Abe::Motion_106_Null_42DF20,
    &Abe::Motion_107_ElumHopBegin_42DF30,
    &Abe::Motion_108_ElumHopMid_42DF40,
    &Abe::Motion_109_ElumHopLand_42DF50,
    &Abe::Motion_110_ElumRunJumpBegin_42DF60,
    &Abe::Motion_111_ElumRunJumpMid_42DF70,
    &Abe::Motion_112_ElumRunJumpLand_42DF80,
    &Abe::Motion_113_ElumTurn_42DF90,
    &Abe::Motion_114_ElumRunLoop_42DFA0,
    &Abe::Motion_115_ElumSpeak_4299F0,
    &Abe::Motion_116_Null_42DFB0,
    &Abe::Motion_117_ElumWalkBegin_42DFC0,
    &Abe::Motion_118_ElumRunBegin_42DFD0,
    &Abe::Motion_119_Null_42DFE0,
    &Abe::Motion_120_ElumRunToWalk_42DFF0,
    &Abe::Motion_121_ElumMidRunToWalk_42E000,
    &Abe::Motion_122_ElumRunTurnToRun_42E010,
    &Abe::Motion_123_ElumRunTurnToWalk_42E020,
    &Abe::Motion_124_ElumWalkEnd_42DCB0,
    &Abe::Motion_125_ElumMidWalkEnd_42DCC0,
    &Abe::Motion_126_ElumBeesStruggling_42E080,
    &Abe::Motion_127_SlapBomb_429A20,
    &Abe::Motion_128_KnockForward_429330,
    &Abe::Motion_129_RollingKnockForward_4294F0,
    &Abe::Motion_130_KnockForwardGetUp_429560,
    &Abe::Motion_131_LiftUseUp_42F150,
    &Abe::Motion_132_LiftUseDown_42F170,
    &Abe::Motion_133_LiftGrabBegin_42EF20,
    &Abe::Motion_134_LiftGrabEnd_42EFE0,
    &Abe::Motion_135_LiftGrabIdle_42F000,
    &Abe::Motion_136_ElumMountEnd_42E110,
    &Abe::Motion_137_ElumUnmountBegin_42E2B0,
    &Abe::Motion_138_ElumUnmountEnd_42E390,
    &Abe::Motion_139_ElumMountBegin_42E090,
    &Abe::Motion_140_BeesStruggling_423F30,
    &Abe::Motion_141_BeesStrugglingOnLift_42F390,
    &Abe::Motion_142_RockThrowStandingHold_429CE0,
    &Abe::Motion_143_RockThrowStandingThrow_429FD0,
    &Abe::Motion_144_RockThrowStandingEnd_429DE0,
    &Abe::Motion_145_RockThrowCrouchingHold_428930,
    &Abe::Motion_146_RockThrowCrouchingThrow_4289F0,
    &Abe::Motion_147_ShotRolling_4295C0,
    &Abe::Motion_148_Shot_4296A0,
    &Abe::Motion_149_PickupItem_42A030,
    &Abe::Motion_150_Chant_42FD50,
    &Abe::Motion_151_ChantEnd_430530,
    &Abe::Motion_152_ElumFallOffEdge_42E030,
    &Abe::Motion_153_ElumFall_42E040,
    &Abe::Motion_154_ElumLand_42E050,
    &Abe::Motion_155_ElumJumpToFall_42E060,
    &Abe::Motion_156_DoorEnter_42D370,
    &Abe::Motion_157_DoorExit_42D780,
    &Abe::Motion_158_ElumKnockback_42E070,
    &Abe::Motion_159_Idle_RubEyes_423360,
    &Abe::Motion_160_Idle_Stretch_Arms_4233A0,
    &Abe::Motion_161_Idle_Yawn_4233E0,
    &Abe::Motion_162_ToShrykull_42F410,
    &Abe::Motion_163_ShrykullEnd_42F520,
    &Abe::Motion_164_PoisonGasDeath_42A120};

const AnimId sAbeFrameOffsetTable_4C61A0[166] = {
    AnimId::Mudokon_Idle,
    AnimId::Mudokon_Walk,
    AnimId::Mudokon_StandingTurn,
    AnimId::Mudokon_Idle,
    AnimId::Mudokon_WalkToIdle,
    AnimId::Mudokon_WalkToIdle,
    AnimId::Mudokon_WalkBegin,
    AnimId::Mudokon_Speak1,
    AnimId::Mudokon_Speak3,
    AnimId::Mudokon_Speak2,
    AnimId::Mudokon_SpeakFart,
    AnimId::Mudokon_Speak1,
    AnimId::Mudokon_Speak2,
    AnimId::Mudokon_Speak3,
    AnimId::Mudokon_SpeakFart,
    AnimId::Mudokon_AO_M_15_Null,
    AnimId::Mudokon_HoistBegin,
    AnimId::Mudokon_HoistIdle,
    AnimId::Mudokon_LandSoft,
    AnimId::Mudokon_CrouchIdle,
    AnimId::Mudokon_CrouchToStand,
    AnimId::Mudokon_StandToCrouch,
    AnimId::Mudokon_CrouchSpeak1,
    AnimId::Mudokon_CrouchSpeak2,
    AnimId::Mudokon_RollBegin,
    AnimId::Mudokon_Rolling,
    AnimId::Mudokon_RollingEnd_Unused,
    AnimId::Mudokon_RunSlideStop,
    AnimId::Mudokon_RunSlideTurn,
    AnimId::Mudokon_HopBegin,
    AnimId::Mudokon_HopMid,
    AnimId::Mudokon_HopLand,
    AnimId::Mudokon_RunJumpBegin,
    AnimId::Mudokon_RunJumpMid,
    AnimId::Mudokon_RunJumpLand,
    AnimId::Mudokon_Run,
    AnimId::Mudokon_DunnoBegin,
    AnimId::Mudokon_DunnoMid,
    AnimId::Mudokon_DunnoEnd,
    AnimId::Mudokon_CrouchTurn,
    AnimId::Mudokon_RunToRoll,
    AnimId::Mudokon_StandToRun,
    AnimId::Mudokon_Sneak,
    AnimId::Mudokon_WalkToSneak,
    AnimId::Mudokon_SneakToWalk,
    AnimId::Mudokon_MidWalkToSneak,
    AnimId::Mudokon_MidSneakToWalk,
    AnimId::Mudokon_SneakBegin,
    AnimId::Mudokon_SneakToIdle,
    AnimId::Mudokon_MidSneakToIdle,
    AnimId::Mudokon_WalkToRun,
    AnimId::Mudokon_MidWalkToRun,
    AnimId::Mudokon_RunToWalk,
    AnimId::Mudokon_MidRunToWalk,
    AnimId::Mudokon_RunTurnToRun,
    AnimId::Mudokon_RunTurnToWalk,
    AnimId::Mudokon_RunJumpLandRun,
    AnimId::Mudokon_RunJumpLandWalk,
    AnimId::Mudokon_ToSpeak,
    AnimId::Mudokon_CrouchIdle, // double check these
    AnimId::Mudokon_CrouchIdle,
    AnimId::Mudokon_CrouchIdle,
    AnimId::Mudokon_CrouchIdle,
    AnimId::Mudokon_TurnToRun,
    AnimId::Mudokon_LedgeAscend,
    AnimId::Mudokon_LedgeDescend,
    AnimId::Mudokon_LedgeHang,
    AnimId::Mudokon_LedgeHang,
    AnimId::Mudokon_LedgeHangWobble,
    AnimId::Mudokon_RingRopePullHang,
    AnimId::Mudokon_Knockback,
    AnimId::Mudokon_KnockbackGetUp,
    AnimId::Mudokon_PushWall,
    AnimId::Mudokon_RollingKnockback,
    AnimId::Mudokon_JumpIntoWell,
    AnimId::Mudokon_Well_Idle,
    AnimId::Mudokon_Well_Idle,
    AnimId::Mudokon_WellBegin,
    AnimId::Mudokon_Well_Idle,
    AnimId::Mudokon_Well_Idle,
    AnimId::Mudokon_WellBegin,
    AnimId::Mudokon_Well_Idle,
    AnimId::Mudokon_Well_Idle,
    AnimId::Mudokon_WellBegin,
    AnimId::Mudokon_Well_Idle,
    AnimId::Mudokon_Well_Idle,
    AnimId::Mudokon_FallLandDie,
    AnimId::Mudokon_Fall,
    AnimId::Mudokon_HandstoneBegin, 
    AnimId::Mudokon_HandstoneEnd,
    AnimId::Mudokon_GrenadeMachineUse,
    AnimId::Mudokon_FallingFromGrab,
    AnimId::Mudokon_FallingFromGrab,
    AnimId::Mudokon_WalkOffEdge,
    AnimId::Mudokon_RunOffEdge,
    AnimId::Mudokon_SneakOffEdge,
    AnimId::Mudokon_HopToFall,
    AnimId::Mudokon_RunJumpToFall,
    AnimId::Mudokon_AO_LandSoft_Long,
    AnimId::Mudokon_AO_HoistBegin_Long,
    AnimId::Mudokon_RollOffEdge,
    AnimId::Mudokon_LeverUse,
    AnimId::Mudokon_ElumWalkLoop,
    AnimId::Mudokon_ElumIdle,
    AnimId::Mudokon_ElumRunSlideStop,
    AnimId::Mudokon_ElumRunTurn,
    AnimId::Mudokon_AO_M_106_Null,
    AnimId::Mudokon_ElumHopBegin,
    AnimId::Mudokon_ElumHopMid,
    AnimId::Mudokon_ElumHopLand,
    AnimId::Mudokon_ElumRunJumpBegin,
    AnimId::Mudokon_ElumRunJumpMid,
    AnimId::Mudokon_ElumRunJumpLand,
    AnimId::Mudokon_ElumTurn,
    AnimId::Mudokon_ElumRunLoop,
    AnimId::Mudokon_ElumSpeak,
    AnimId::Mudokon_AO_M_116_Null,
    AnimId::Mudokon_ElumWalkBegin,
    AnimId::Mudokon_ElumRunBegin,
    AnimId::Mudokon_AO_M_119_Null,
    AnimId::Mudokon_ElumRunToWalk,
    AnimId::Mudokon_ElumMidRunToWalk,
    AnimId::Mudokon_ElumRunTurnToRun,
    AnimId::Mudokon_ElumRunTurnToWalk,
    AnimId::Mudokon_ElumWalkEnd,
    AnimId::Mudokon_ElumMidWalkEnd,
    AnimId::Mudokon_ElumBeesStruggling,
    AnimId::Mudokon_SlapBomb,
    AnimId::Mudokon_KnockForward,
    AnimId::Mudokon_RollingKnockForward,
    AnimId::Mudokon_Idle, // knock forward get up?
    AnimId::Mudokon_AO_Null, // lift use up
    AnimId::Mudokon_AO_LiftUse, // lift use down
    AnimId::Mudokon_LiftGrabBegin,
    AnimId::Mudokon_LiftGrabEnd,
    AnimId::Mudokon_LiftGrabIdle,
    AnimId::Mudokon_ElumMountEnd,
    AnimId::Mudokon_ElumUnmountBegin,
    AnimId::Mudokon_ElumUnmountEnd,
    AnimId::Mudokon_ElumMountBegin,
    AnimId::Mudokon_Struggle,
    AnimId::Mudokon_Struggle,
    AnimId::Mudokon_RockThrowStandingHold,
    AnimId::Mudokon_RockThrowStandingThrow,
    AnimId::Mudokon_RockThrowStandingEnd,
    AnimId::Mudokon_RockThrowCrouchingHold,
    AnimId::Mudokon_RockThrowCrouchingThrow,
    AnimId::Mudokon_ZShotRolling,
    AnimId::Mudokon_ZShot,
    AnimId::Mudokon_PickupItem,
    AnimId::Mudokon_Chant,
    AnimId::Mudokon_ChantEnd,
    AnimId::Mudokon_ElumFallOffEdge,
    AnimId::Mudokon_ElumFall,
    AnimId::Mudokon_ElumLand,
    AnimId::Mudokon_ElumJumpToFall,
    AnimId::Mudokon_DoorEnter,
    AnimId::Mudokon_DoorExit,
    AnimId::Mudokon_ElumKnockback,
    AnimId::Mudokon_Idle_RubEyes,
    AnimId::Mudokon_Idle_StretchArms,
    AnimId::Mudokon_Idle_Yawn,
    AnimId::Mudokon_AO_ToShrykull,
    AnimId::Mudokon_AO_ShrykullEnd,
    AnimId::Mudokon_PoisonGasDeath,
    AnimId::None};

/*const s32 sAbeFrameOffsetTable_4C61A0[166] = {
    55968,
    55888,
    56144,
    55968,
    55868,
    55868,
    55848,
    56108,
    56072,
    56036,
    56000,
    56108,
    56036,
    56072,
    56000,
    255776,
    255484,
    255532,
    255436,
    255600,
    255568,
    255384,
    256660,
    256700,
    255196,
    255216,
    255272,
    256424,
    255868,
    256584,
    256636,
    256544,
    256008,
    255312,
    256028,
    256312,
    255716,
    255688,
    256180,
    255968,
    256272,
    255788,
    256048,
    256252,
    256160,
    256404,
    256292,
    255828,
    255668,
    255848,
    255628,
    255808,
    256232,
    256384,
    255948,
    255648,
    255292,
    255364,
    256136,
    255600,
    255600,
    255600,
    255600,
    256524,
    54208,
    54348,
    54308,
    54308,
    54480,
    54448,
    48272,
    48332,
    48460,
    48404,
    19644,
    19624,
    19624,
    19476,
    19624,
    19624,
    19476,
    19624,
    19624,
    19476,
    19624,
    19624,
    7880,
    5560,
    15484,
    15428,
    15608,
    40652,
    40652,
    40680,
    40708,
    40752,
    40852,
    40836,
    40868,
    40772,
    40816,
    10988,
    144920,
    145132,
    145736,
    145804,
    145000,
    145104,
    145164,
    145196,
    145220,
    145688,
    145240,
    145456,
    145312,
    145512,
    145588,
    145608,
    145548,
    145416,
    145436,
    145568,
    145272,
    145292,
    145648,
    145668,
    145860,
    6360,
    16772,
    16712,
    55968,
    21744,
    21644,
    21696,
    21720,
    21612,
    23568,
    13716,
    34676,
    16256,
    21496,
    21496,
    30440,
    30328,
    30568,
    30512,
    30368,
    23996,
    24044,
    5828,
    9516,
    9564,
    21672,
    21700,
    21724,
    21780,
    17520,
    17568,
    11652,
    9860,
    13152,
    12392,
    8240,
    8280,
    27748,
    0};*/

ALIVE_VAR(1, 0x507678, Abe*, sActiveHero_507678, nullptr);
ALIVE_VAR(1, 0x50767C, BaseAliveGameObject*, sControlledCharacter_50767C, nullptr);

SfxDefinition sSFXList_4C6638[49] = {
    {0, 3, 69, 60, -1, 1, 0},
    {0, 3, 70, 60, -1, 1, 0},
    {0, 3, 59, 67, -1, 1, 0},
    {0, 3, 61, 67, -1, 1, 0},
    {0, 3, 58, 52, -1, 1, 0},
    {0, 3, 67, 45, -1, 1, 0},
    {0, 3, 57, 60, -1, 1, 0},
    {0, 3, 65, 50, -1, 1, 0},
    {0, 3, 68, 60, -1, 1, 0},
    {0, 3, 72, 70, -1, 1, 0},
    {0, 4, 36, 50, -127, 0, 0},
    {0, 4, 37, 50, -127, 0, 0},
    {0, 4, 38, 50, -127, 0, 0},
    {0, 4, 36, 55, 0, 127, 0},
    {0, 4, 37, 55, 0, 127, 0},
    {0, 4, 38, 55, 0, 127, 0},
    {0, 4, 59, 50, -1, 1, 0},
    {0, 4, 72, 127, -1, 1, 0},
    {0, 4, 80, 127, -1, 1, 0},
    {0, 11, 61, 60, -1, 0, 0},
    {0, 11, 62, 60, -1, 1, 0},
    {0, 11, 64, 60, -1, 1, 0},
    {0, 11, 65, 50, -1, 1, 0},
    {0, 11, 64, 50, -1, 1, 0},
    {0, 11, 66, 50, -1, 1, 0},
    {0, 23, 60, 90, 0, 0, 0},
    {0, 23, 61, 90, 0, 0, 0},
    {0, 23, 62, 90, 0, 0, 0},
    {0, 23, 63, 90, 0, 0, 0},
    {0, 23, 64, 90, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 58, 61, 97, 0, 0, 0},
    {0, 58, 60, 97, 0, 0, 0},
    {0, 59, 60, 127, 0, 0, 0},
    {0, 59, 61, 127, 0, 0, 0},
    {0, 59, 62, 127, 0, 0, 0},
    {0, 59, 63, 110, 0, 0, 0},
    {0, 60, 61, 127, 0, 0, 0},
    {0, 60, 63, 127, 0, 0, 0},
    {0, 61, 55, 127, 0, 0, 0},
    {0, 61, 56, 127, 0, 0, 0},
    {0, 61, 57, 127, 0, 0, 0},
    {0, 61, 58, 127, 0, 0, 0},
    {0, 61, 59, 127, 0, 0, 0},
    {0, 61, 60, 127, 0, 0, 0},
    {0, 61, 61, 127, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 65, 60, 127, 0, 0, 0},
    {0, 65, 64, 80, 0, 0, 0}};

s32 Environment_SFX_42A220(EnvironmentSfx sfxId, s32 volume, s32 pitchMin, BaseAliveGameObject* pAliveObj)
{
    s16 sndIndex = 0;
    switch (sfxId)
    {
        case EnvironmentSfx::eSlideStop_0:
            sndIndex = 11;
            volume = 40;
            break;
        case EnvironmentSfx::eWalkingFootstep_1:
            sndIndex = Math_RandomRange_450F20(10, 12);
            if (volume == 0)
            {
                volume = Math_RandomRange_450F20(54, 58);
            }
            break;
        case EnvironmentSfx::eRunningFootstep_2:
            sndIndex = Math_RandomRange_450F20(13, 15);
            if (volume == 0)
            {
                volume = Math_RandomRange_450F20(66, 70);
            }
            break;
        case EnvironmentSfx::eSneakFootstep_3:
            sndIndex = 5;
            break;
        case EnvironmentSfx::eRunSlide_4:
            sndIndex = 4;
            break;
        case EnvironmentSfx::eLandingSoft_5:
        {
            s32 v4 = 0;
            s32 v5 = 0;
            if (volume > 0 || !pAliveObj || pAliveObj->field_BC_sprite_scale != FP_FromDouble(0.5))
            {
                v4 = SFX_SfxDefinition_Play_4770F0(&sSFXList_4C6638[2], volume, pitchMin, 0x7FFF);
                v5 = SFX_SfxDefinition_Play_4770F0(&sSFXList_4C6638[48], volume, pitchMin, 0x7FFF);
            }
            else
            {
                v4 = SFX_SfxDefinition_Play_4770F0(
                    &sSFXList_4C6638[2],
                    sSFXList_4C6638[2].field_C_default_volume / 2,
                    pitchMin,
                    0x7FFF);
                v5 = SFX_SfxDefinition_Play_4770F0(
                    &sSFXList_4C6638[48],
                    sSFXList_4C6638[18].field_C_default_volume / 2,
                    pitchMin,
                    0x7FFF);
            }
            return v5 | v4;
        }
        case EnvironmentSfx::eHitGroundSoft_6:
            sndIndex = 2;
            break;
        case EnvironmentSfx::eDeathNoise_7:
            sndIndex = 16;
            break;
        case EnvironmentSfx::eRollingNoise_8:
            sndIndex = 6;
            break;
        case EnvironmentSfx::eGenericMovement_9:
        case EnvironmentSfx::eRunJumpOrLedgeHoist_11:
        {
            s32 result = 0;
            if (pAliveObj && pAliveObj->field_BC_sprite_scale == FP_FromDouble(0.5))
            {
                result = SFX_Play_Mono(SoundEffect::AbeGenericMovement_37, 20, 0);
            }
            else
            {
                result = SFX_Play_Mono(SoundEffect::AbeGenericMovement_37, 35, 0);
            }
            return result;
        }
        case EnvironmentSfx::eExhaustingHoistNoise_10:
        case EnvironmentSfx::eExhaustingElumMount_16:
            sndIndex = 19;
            break;
        case EnvironmentSfx::eUnknown_12:
            sndIndex = 25;
            break;
        case EnvironmentSfx::eKnockback_13:
            if (gMap.mCurrentLevel == EReliveLevelIds::eRuptureFarms
                || gMap.mCurrentLevel == EReliveLevelIds::eBoardRoom
                || gMap.mCurrentLevel == EReliveLevelIds::eRuptureFarmsReturn)
            {
                sndIndex = 2;
            }
            else
            {
                sndIndex = 9;
            }
            break;
        case EnvironmentSfx::eElumHitWall_14:
            sndIndex = 17;
            break;
        case EnvironmentSfx::eFallingDeathScreamHitGround_15:
            return 0;
        case EnvironmentSfx::eMountElumSmackNoise_17:
            sndIndex = 20;
            break;
        case EnvironmentSfx::eElumGetMountedNoise_18:
            sndIndex = 21;
            break;
        case EnvironmentSfx::eAbeMountedElumNoise_19:
            sndIndex = 22;
            break;
        case EnvironmentSfx::eElumHowl_20:
            sndIndex = 23;
            break;
        case EnvironmentSfx::eElumOkay_21:
            sndIndex = 24;
            break;
        default:
            break;
    }
    if (volume == 0)
    {
        volume = sSFXList_4C6638[sndIndex].field_C_default_volume;
    }
    if (pAliveObj)
    {
        if (pAliveObj->field_BC_sprite_scale == FP_FromDouble(0.5))
        {
            volume *= 2;
            volume /= 3;
        }
    }
    return SFX_SfxDefinition_Play_4770F0(&sSFXList_4C6638[sndIndex], volume, pitchMin, 0x7FFF);
}

s32 Mudokon_SFX_42A4D0(MudSounds idx, s32 volume, s32 pitch, BaseAliveGameObject* pHero)
{
    if (idx == MudSounds::eLaugh1_8
        && pHero == sActiveHero_507678
        && (gMap.mCurrentLevel == EReliveLevelIds::eRuptureFarmsReturn || gMap.mCurrentLevel == EReliveLevelIds::eBoardRoom))
    {
        idx = MudSounds::eLaugh2_11;
    }
    if (idx == MudSounds::eOops_16)
    {
        if (pHero && pHero->field_BC_sprite_scale == FP_FromDouble(0.5))
        {
            SND_SEQ_Play_477760(SeqId::eAbeOops_23, 1, 85, 85);
            return 0;
        }
        else
        {
            SND_SEQ_Play_477760(SeqId::eAbeOops_23, 1, 110, 110);
            return 0;
        }
    }
    else
    {
        auto idxShort = static_cast<s16>(idx);
        if (volume == 0)
        {
            volume = sSFXList_4C6638[idxShort + 30].field_C_default_volume;
        }
        if (pHero)
        {
            if (pHero->field_BC_sprite_scale == FP_FromDouble(0.5))
            {
                volume *= 2;
                volume /= 3;
            }
        }
        return SFX_SfxDefinition_Play_4770F0(&sSFXList_4C6638[idxShort + 30], volume, pitch, pitch);
    }
}

void Abe::VOnTrapDoorOpen()
{
    if (mLiftPoint)
    {
        if (!field_2A8_flags.Get(Flags_2A8::e2A8_Bit6_bShrivel))
        {
            VSetMotion(eAbeMotions::Motion_93_WalkOffEdge_429840);
        }

        mLiftPoint->VRemove(this);
        mLiftPoint->mBaseGameObjectRefCount--;
        mLiftPoint = nullptr;
        BaseAliveGameObjectLastLineYPos = mBaseAnimatedWithPhysicsGameObject_YPos;
    }
}

const TintEntry sAbeTints_4C6438[] = {
    {EReliveLevelIds::eStockYards, 25u, 25u, 25u},
    {EReliveLevelIds::eStockYardsReturn, 25u, 25u, 25u},
    {EReliveLevelIds::eDesert, 125u, 125u, 95u},
    {EReliveLevelIds::eDesertTemple, 120u, 120u, 90u},
    {EReliveLevelIds::eNone, 102u, 102u, 102u}};


Abe::Abe(s32 frameTableOffset, s32 /*r*/, s32 /*g*/, s32 /*b*/)
{
    mBaseGameObjectTypeId = ReliveTypes::eAbe;

    mBaseGameObjectFlags.Set(Options::eSurviveDeathReset_Bit9);

    Init_GameStates();

    // Zero out the resource array
    field_1A4_resources = {};

    if (!ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbebasicAOResID, 1, 0))
    {
        ResourceManager::LoadResourceFile_455270("ABEBSIC.BAN", nullptr);
        ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbebasicAOResID, 1, 0);
    }

    field_1A4_resources.res[0] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbebasicAOResID, 0, 0);

    if (!ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbebsic1AOResID, 1, 0))
    {
        ResourceManager::LoadResourceFile_455270("ABEBSIC1.BAN", nullptr);
        ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbebsic1AOResID, 1, 0);
    }

    field_1A4_resources.res[45] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbebsic1AOResID, 0, 0);

    if (!ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeedgeAOResID, 1, 0))
    {
        ResourceManager::LoadResourceFile_455270("ABEEDGE.BAN", nullptr);
        ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeedgeAOResID, 1, 0);
    }

    if (!ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeknfdAOResID, 1, 0))
    {
        ResourceManager::LoadResourceFile_455270("ABEKNFD.BAN", nullptr);
        ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeknfdAOResID, 1, 0);
    }

    if (!ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeommAOResID, 1, 0))
    {
        ResourceManager::LoadResourceFile_455270("ABEOMM.BAN", nullptr);
        ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeommAOResID, 1, 0);
    }

    if (!ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeknbkAOResID, 1, 0))
    {
        ResourceManager::LoadResourceFile_455270("ABEKNBK.BAN", nullptr);
        ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeknbkAOResID, 1, 0);
    }

    ResourceManager::LoadResourceFile_455270("ABENOELM.BND", nullptr);
    ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbefallAOResID, 1, 0);
    ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbesmashAOResID, 1, 0);
    ResourceManager::LoadResourceFile_455270("OMMFLARE.BAN", nullptr);
    ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kOmmflareAOResID, 1, 0);
    ResourceManager::LoadResourceFile_455270("SQBSMK.BAN", nullptr);
    ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kSquibSmokeAOResID, 1, 0);
    ResourceManager::LoadResourceFile_455270("BLOODROP.BAN", nullptr);
    ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kBloodropAOResID, 1, 0);
    if (!ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kObjectShadowAOResID, 0, 0))
    {
        ResourceManager::LoadResourceFile_455270("SHADOW.BAN", nullptr);
    }
    ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kObjectShadowAOResID, 1, 0);
    ResourceManager::LoadResourceFile_455270("DEADFLR.BAN", nullptr);
    ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kDeathFlareAOResID, 1, 0);
    ResourceManager::LoadResourceFile_455270("DOVBASIC.BAN", nullptr);
    ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kDovbasicAOResID, 1, 0);

    field_128_resource_idx = 45;
    Animation_Init_417FD0(frameTableOffset, 135, 80, field_1A4_resources.res[45], 1);

    field_10_anim.field_1C_fn_ptr_array = kAbe_Anim_Frame_Fns_4CEBEC;

    PSX_Point pPoint = {};
    gMap.GetCurrentCamCoords(&pPoint);
    mBaseAnimatedWithPhysicsGameObject_XPos = FP_FromInteger(pPoint.field_0_x + XGrid_Index_To_XPos(field_BC_sprite_scale, 4));
    mBaseAnimatedWithPhysicsGameObject_YPos = FP_FromInteger(pPoint.field_2_y + 240);
    field_120_x_vel_slow_by = FP_FromInteger(0);
    field_124_unused = 0;
    BaseAliveGameObjectLastLineYPos = mBaseAnimatedWithPhysicsGameObject_YPos;
    field_B4_velx = FP_FromInteger(0);
    field_B8_vely = FP_FromInteger(0);
    BaseAliveGameObjectCollisionLine = nullptr;
    mCurrentMotion = eAbeMotions::Motion_3_Fall_42E7F0;

    field_112_prev_motion = -1;
    field_10_anim.mRenderLayer = Layer::eLayer_AbeMenu_32;
    field_15C_pThrowable = nullptr;
    field_19C_throwable_count = 0;
    field_198_pThrowable = nullptr;
    field_1A0_portal = 0;
    field_158_pDeathFadeout = nullptr;
    field_164_pCircularFade = nullptr;
    field_188_pOrbWhirlWind = nullptr;
    field_18C_pObjToPossess = nullptr;
    field_138_zone_top_left = {};
    field_13C_zone_bottom_right = {};
    field_140_saved_camera = -1;
    mBaseAliveGameObjectFlags.Set(Flags_10A::e10A_Bit4_SetOffExplosives);

    field_2AA_flags.Clear(Flags_2AA::e2AA_Bit1);
    field_2AA_flags.Clear(Flags_2AA::e2AA_Bit2_bSfxPlaying);
    field_2AA_flags.Clear(Flags_2AA::e2AA_Bit3_ElumMountBegin);
    field_2AA_flags.Clear(Flags_2AA::e2AA_Bit4_ElumMountEnd);
    field_2AA_flags.Clear(Flags_2AA::e2AA_Bit5_ElumUnmountBegin);

    field_14C_saved_sprite_scale = field_BC_sprite_scale;
    field_144_saved_level = gMap.mCurrentLevel;
    field_142_saved_path = -1;
    field_148_clear_from_id = 0;
    field_14A_clear_to_id = 0;
    field_146_zone_number = 0;
    field_150_saved_ring_timer = 0;
    field_154_bSavedHaveShrykull = 0;

    field_2A8_flags.Raw().all = 0;
    field_2A8_flags.Set(Flags_2A8::e2A8_Bit8_bLandSoft);

    // Changes Abe's "default" colour depending on the level we are in
    SetTint_418750(sAbeTints_4C6438, gMap.mCurrentLevel);

    field_10_anim.mAnimFlags.Set(AnimFlags::eBit15_bSemiTrans);
    field_10_anim.mRenderMode = TPageAbr::eBlend_0;

    field_10C_prev_held = 0; // lowest to base class
    mBaseAliveGameObjectLastAnimFrame = 0;
    field_110_state.raw = 0;
    field_168_ring_pulse_timer = 0;
    field_114_gnFrame = sGnFrame;
    BaseAliveGameObjectPathTLV = nullptr;
    field_160_pRope = nullptr;
    mLiftPoint = nullptr;
    field_130_say = -1;
    field_134_auto_say_timer = 0;
    field_EC = 1;
    field_12A_unused = 161;

    // Set Abe to be the current player controlled object
    sControlledCharacter_50767C = this;

    // Create shadow
    field_D0_pShadow = ao_new<Shadow>();

    // Animation test code
    //auto testAnim = ao_new<TestAnimation>(); testAnim->ctor();
}

Abe::~Abe()
{
    MusicController::ClearObject(this);

    SND_Seq_Stop_477A60(SeqId::eMudokonChant1_11);

    u8** ppRes = nullptr;

    ppRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbebasicAOResID, 0, 0);
    if (ppRes)
    {
        if (field_10_anim.field_20_ppBlock != ppRes)
        {
            ResourceManager::FreeResource_455550(ppRes);
        }
    }

    ppRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbebsic1AOResID, 0, 0);
    if (ppRes)
    {
        if (field_10_anim.field_20_ppBlock != ppRes)
        {
            ResourceManager::FreeResource_455550(ppRes);
        }
    }

    ppRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeedgeAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    ppRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbefallAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    ppRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeknbkAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    ppRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeknfdAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    ppRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeommAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    ppRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbesmashAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    ppRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kOmmflareAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    ppRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kBloodropAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    ppRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kObjectShadowAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    ppRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kDeathFlareAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    ppRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kDovbasicAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    ppRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kSquibSmokeAOResID, 0, 0);
    ResourceManager::FreeResource_455550(ppRes);

    if (field_158_pDeathFadeout)
    {
        field_158_pDeathFadeout->mBaseGameObjectRefCount--;
        field_158_pDeathFadeout->mBaseGameObjectFlags.Set(Options::eDead);
        field_158_pDeathFadeout = nullptr;
    }

    if (field_15C_pThrowable)
    {
        field_15C_pThrowable->mBaseGameObjectRefCount--;
        field_15C_pThrowable->mBaseGameObjectFlags.Set(Options::eDead);
        field_15C_pThrowable = nullptr;
    }

    if (field_160_pRope)
    {
        field_160_pRope->mBaseGameObjectRefCount--;
        field_160_pRope->mBaseGameObjectFlags.Set(Options::eDead);
        field_160_pRope = nullptr;
    }

    if (field_164_pCircularFade)
    {
        field_164_pCircularFade->mBaseGameObjectRefCount--;
        field_164_pCircularFade->mBaseGameObjectFlags.Set(Options::eDead);
        field_164_pCircularFade = nullptr;
    }

    if (field_188_pOrbWhirlWind)
    {
        field_188_pOrbWhirlWind->mBaseGameObjectRefCount--;
        field_188_pOrbWhirlWind->mBaseGameObjectFlags.Set(Options::eDead);
        field_188_pOrbWhirlWind = nullptr;
    }

    if (field_18C_pObjToPossess)
    {
        field_18C_pObjToPossess->mBaseGameObjectRefCount--;
        field_18C_pObjToPossess->mBaseGameObjectFlags.Set(Options::eDead);
        field_18C_pObjToPossess = nullptr;
    }

    if (field_198_pThrowable)
    {
        field_198_pThrowable->mBaseGameObjectRefCount--;
        field_198_pThrowable->mBaseGameObjectFlags.Set(Options::eDead);
        field_198_pThrowable = nullptr;
    }

    sActiveHero_507678 = nullptr;

    // OG fix for going back to menu with DDCheat on and then it crashes reading a deleted pointer
    // ditto for the ending where MeatSaw/Invisible switch screen change/update funcs read it.
    sControlledCharacter_50767C = nullptr;
}

const u32 sAbe_xVel_table_4BB118[8] = {262144, 262144, 0, 4294705152, 4294705152, 4294705152, 0, 262144};
const u32 sAbe_yVel_table_4BB138[8] = {0, 4294705152, 4294705152, 4294705152, 0, 262144, 262144, 262144};

void Abe::VUpdate()
{
    if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit1))
    {
        if (gAbeInvulnerableCheat_5076E4)
        {
            mHealth = FP_FromInteger(1);
        }

        if (!Input_IsChanting())
        {
            field_2A8_flags.Clear(Flags_2A8::e2A8_Bit7);
        }

        if (sDDCheat_FlyingEnabled_50771C && sControlledCharacter_50767C == this)
        {
            VOnTrapDoorOpen();

            const FP old_y = mBaseAnimatedWithPhysicsGameObject_YPos;
            field_2A8_flags.Clear(Flags_2A8::e2A8_Bit6_bShrivel);
            BaseAliveGameObjectLastLineYPos = old_y;
            mCurrentMotion = eAbeMotions::Motion_87_ToFall_428FA0;
            BaseAliveGameObjectCollisionLine = nullptr;

            if (Input().IsAnyPressed(0xF000u))
            {
                const s32 dir = Input().Dir();
                field_B4_velx = FP_FromRaw(sAbe_xVel_table_4BB118[dir] * 2);
                field_B8_vely = FP_FromRaw(sAbe_yVel_table_4BB138[dir]);

                if (Input().IsAnyPressed(sInputKey_Run_4C65A8))
                {
                    field_B4_velx += FP_FromRaw(sAbe_xVel_table_4BB118[dir]);
                    field_B8_vely += FP_FromRaw(sAbe_yVel_table_4BB138[dir]);
                }

                mBaseAnimatedWithPhysicsGameObject_XPos += field_B4_velx;
                mBaseAnimatedWithPhysicsGameObject_YPos += field_B8_vely;

                PSX_Point mapSize = {};
                gMap.Get_map_size(&mapSize);

                if (mBaseAnimatedWithPhysicsGameObject_XPos < FP_FromInteger(0))
                {
                    mBaseAnimatedWithPhysicsGameObject_XPos = FP_FromInteger(0);
                }

                if (mBaseAnimatedWithPhysicsGameObject_XPos >= FP_FromInteger(mapSize.field_0_x))
                {
                    mBaseAnimatedWithPhysicsGameObject_XPos = FP_FromInteger(mapSize.field_0_x) - FP_FromInteger(1);
                }

                if (mBaseAnimatedWithPhysicsGameObject_YPos < FP_FromInteger(0))
                {
                    mBaseAnimatedWithPhysicsGameObject_YPos = FP_FromInteger(0);
                }

                if (mBaseAnimatedWithPhysicsGameObject_YPos >= FP_FromInteger(mapSize.field_2_y))
                {
                    mBaseAnimatedWithPhysicsGameObject_YPos = FP_FromInteger(mapSize.field_2_y) - FP_FromInteger(1);
                    SetActiveCameraDelayedFromDir_401C90();
                    return;
                }
            }
            else
            {
                field_B4_velx = FP_FromInteger(0);
                field_B8_vely = FP_FromInteger(0);
            }
            SetActiveCameraDelayedFromDir_401C90();
        }
        else
        {
            field_10_anim.mAnimFlags.Set(AnimFlags::eBit2_Animate);


            // Execute the current state
            s16 motion_idx = mCurrentMotion;
            const FP oldX = mBaseAnimatedWithPhysicsGameObject_XPos;
            const FP oldY = mBaseAnimatedWithPhysicsGameObject_YPos;
            (this->*sAbeMotionMachineTable_4C5F08[motion_idx])();

            if (BaseAliveGameObjectCollisionLine)
            {
                // Snap to a whole number so we are "on" the line
                mBaseAnimatedWithPhysicsGameObject_YPos = FP_NoFractional(mBaseAnimatedWithPhysicsGameObject_YPos);
            }

            if (!field_2A8_flags.Get(Flags_2A8::e2A8_Bit6_bShrivel))
            {
                // Did position change?
                if (oldX != mBaseAnimatedWithPhysicsGameObject_XPos || oldY != mBaseAnimatedWithPhysicsGameObject_YPos || sControlledCharacter_50767C == gElum_507680)
                {
                    // Get the TLV we are on
                    BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446060(
                        nullptr,
                        mBaseAnimatedWithPhysicsGameObject_XPos,
                        mBaseAnimatedWithPhysicsGameObject_YPos,
                        mBaseAnimatedWithPhysicsGameObject_XPos,
                        mBaseAnimatedWithPhysicsGameObject_YPos);

                    VOn_TLV_Collision(BaseAliveGameObjectPathTLV);
                }

                if (field_106_shot)
                {
                    motion_idx = field_112_prev_motion;
                    ToKnockback_422D90(1, 0);
                    mCurrentMotion = motion_idx;
                    mNextMotion = 0;
                    field_112_prev_motion = 0;
                    field_108_bMotionChanged = 1;
                    field_106_shot = 0;
#if ORIGINAL_GAME_FIXES || ORIGINAL_GAME_FIX_DEATH_DELAY_AO
                    field_2A8_flags.Clear(Flags_2A8::e2A8_Bit2_return_to_previous_motion); // OG Change - Fixes "Death Delay Glitch"
#endif
                }

                if (Event_Get(kEventScreenShake))
                {
                    if (IsStanding_41FC10())
                    {
                        ToKnockback_422D90(1, 0);
                    }
                }

                if (motion_idx != mCurrentMotion || field_108_bMotionChanged)
                {
                    field_108_bMotionChanged = FALSE;

                    if (mCurrentMotion != eAbeMotions::Motion_15_Null_42A210 && !field_2A8_flags.Get(Flags_2A8::e2A8_Bit6_bShrivel))
                    {
                        const AnimRecord& rec = AO::AnimRec(sAbeFrameOffsetTable_4C61A0[mCurrentMotion]);
                        field_10_anim.Set_Animation_Data(
                            rec.mFrameTableOffset,
                            StateToAnimResource_4204F0(mCurrentMotion));

                        field_12C_timer = sGnFrame;

                        if (motion_idx == eAbeMotions::Motion_15_Null_42A210 || motion_idx == eAbeMotions::Motion_62_LoadedSaveSpawn_45ADD0)
                        {
                            field_10_anim.SetFrame(mBaseAliveGameObjectLastAnimFrame);
                        }
                    }
                }
                else if (field_2A8_flags.Get(Flags_2A8::e2A8_Bit2_return_to_previous_motion))
                {
                    mCurrentMotion = mPreviousMotion;
                    const AnimRecord& rec = AO::AnimRec(sAbeFrameOffsetTable_4C61A0[mCurrentMotion]);
                    field_10_anim.Set_Animation_Data(
                        rec.mFrameTableOffset,
                        StateToAnimResource_4204F0(mCurrentMotion));

                    field_12C_timer = sGnFrame;
                    field_10_anim.SetFrame(mBaseAliveGameObjectLastAnimFrame);
                    field_2A8_flags.Clear(Flags_2A8::e2A8_Bit2_return_to_previous_motion);
                }

                if (field_11C_regen_health_timer <= static_cast<s32>(sGnFrame) && mHealth > FP_FromInteger(0))
                {
                    mHealth = FP_FromInteger(1);
                }

                if (field_168_ring_pulse_timer)
                {
                    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit3_Render))
                    {
                        if (static_cast<s32>(sGnFrame) <= field_168_ring_pulse_timer || field_16C_bHaveShrykull)
                        {
                            if (!(sGnFrame % 32))
                            {
                                PSX_RECT bRect = {};
                                VGetBoundingRect(&bRect, 1);
                                AbilityRing::Factory(
                                    FP_FromInteger((bRect.w + bRect.x) / 2),
                                    FP_FromInteger((bRect.h + bRect.y) / 2),
                                    field_16C_bHaveShrykull != 0 ? RingTypes::eShrykull_Pulse_Small_4 : RingTypes::eExplosive_Pulse_0);
                                SFX_Play_Pitch(SoundEffect::PossessEffect_21, 25, 2650, 0);
                            }
                        }
                        else
                        {
                            field_168_ring_pulse_timer = 0;
                        }
                    }
                }

                if (Event_Get(kEventMudokonDead))
                {
                    field_130_say = 16;
                    field_134_auto_say_timer = sGnFrame + Math_RandomRange_450F20(22, 30);
                    ao_new<MusicTrigger>(MusicTriggerMusicType::eDeathDrumShort_1, TriggeredBy::eTouching_1, 0, 90);
                }

                if (field_130_say >= 0 && static_cast<s32>(sGnFrame) >= field_134_auto_say_timer)
                {
                    if (gMap.Is_Point_In_Current_Camera_4449C0(
                            field_B2_lvl_number,
                            field_B0_path_number,
                            mBaseAnimatedWithPhysicsGameObject_XPos,
                            mBaseAnimatedWithPhysicsGameObject_YPos,
                            0))
                    {
                        if (mCurrentMotion != eAbeMotions::Motion_150_Chant_42FD50
                            && mCurrentMotion != eAbeMotions::Motion_7_Speak_42F950
                            && mCurrentMotion != eAbeMotions::Motion_8_Speak_42F9D0
                            && mCurrentMotion != eAbeMotions::Motion_9_Speak_42FA50
                            && mCurrentMotion != eAbeMotions::Motion_10_Speak_42FAD0
                            && mCurrentMotion != eAbeMotions::Motion_11_Speak_42FB50
                            && mCurrentMotion != eAbeMotions::Motion_12_Speak_42FBD0
                            && mCurrentMotion != eAbeMotions::Motion_13_Speak_42FC50
                            && mCurrentMotion != eAbeMotions::Motion_14_Speak_42FCD0)
                        {
                            if (mCurrentMotion == eAbeMotions::Motion_0_Idle_423520 || mCurrentMotion == eAbeMotions::Motion_15_Null_42A210)
                            {
                                field_108_bMotionChanged = TRUE;
                                if (field_130_say == 5 || field_130_say == 16)
                                {
                                    mCurrentMotion = eAbeMotions::Motion_10_Speak_42FAD0;
                                }
                                else
                                {
                                    mCurrentMotion = eAbeMotions::Motion_9_Speak_42FA50;
                                }
                            }
                            if (field_130_say == 5)
                            {
                                Event_Broadcast(kEventMudokonComfort, sActiveHero_507678);
                            }
                            Mudokon_SFX_42A4D0(static_cast<MudSounds>(field_130_say), 0, 0, this);
                        }
                    }
                    field_130_say = -1;
                }

                if (field_2A8_flags.Get(Flags_2A8::e2A8_Bit12_bParamoniaDone) && field_2A8_flags.Get(Flags_2A8::e2A8_eBit13_bScrabaniaDone))
                {
                    if (!field_2A8_flags.Get(Flags_2A8::e2A8_eBit15_bGiveShrykullFromBigFace) && gMap.mLevel == EReliveLevelIds::eLines)
                    {
                        LOG_INFO("Set e2A8_eBit15_bGiveShrykullFromBigFace");
                        field_2A8_flags.Set(Flags_2A8::e2A8_eBit15_bGiveShrykullFromBigFace);
                    }
                }

                if (field_2A8_flags.Get(Flags_2A8::e2A8_eBit15_bGiveShrykullFromBigFace))
                {
                    static bool bLogged = false;
                    if (!bLogged)
                    {
                        LOG_INFO("Have e2A8_eBit15_bGiveShrykullFromBigFace " << static_cast<s32>(gMap.mCurrentLevel));
                        bLogged = true;
                    }

                    if (!field_2A8_flags.Get(Flags_2A8::e2A8_eBit14_bGotShrykullFromBigFace) && gMap.mCurrentLevel == EReliveLevelIds::eLines)
                    {
                        LOG_INFO("Set field_16C_bHaveShrykull TRUE");
                        if (!ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbemorphAOResID, 1, 0))
                        {
                            ResourceManager::LoadResourceFile_455270("ABEMORPH.BAN", nullptr);
                            ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbemorphAOResID, 1, 0);
                        }
                        if (!ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kShrmorphAOResID, 1, 0))
                        {
                            ResourceManager::LoadResourceFile_455270("SHRMORPH.BAN", nullptr);
                            ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kShrmorphAOResID, 1, 0);
                        }
                        if (!ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kSplineAOResID, 1, 0))
                        {
                            ResourceManager::LoadResourceFile_455270("SPLINE.BAN", nullptr);
                            ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kSplineAOResID, 1, 0);
                        }
                        field_16C_bHaveShrykull = TRUE;
                        field_168_ring_pulse_timer = sGnFrame + 32000;
                        field_2A8_flags.Set(Flags_2A8::e2A8_eBit14_bGotShrykullFromBigFace);
                    }
                }
            }
        }
    }
}

void Abe::VRender(PrimHeader** ppOt)
{
    // When in death shrivel don't reset scale else can't shrivel into a black blob
    if (!(field_2A8_flags.Get(Flags_2A8::e2A8_Bit6_bShrivel)))
    {
        field_10_anim.field_14_scale = field_BC_sprite_scale;
    }

    if (mCurrentMotion != eAbeMotions::Motion_15_Null_42A210 && mCurrentMotion != eAbeMotions::Motion_78_InsideWellLocal_4310A0 && mCurrentMotion != eAbeMotions::Motion_81_InsideWellExpress_431320 && mCurrentMotion != eAbeMotions::Motion_84_ToInsideWellLocal_431080 && mCurrentMotion != eAbeMotions::Motion_75_ToInsideOfAWellLocal_431090)
    {
        BaseAnimatedWithPhysicsGameObject::VRender(ppOt);
    }
}

void Abe::Free_Shrykull_Resources_42F4C0()
{
    ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbemorphAOResID, 0, 0));
    ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kShrmorphAOResID, 0, 0));
    ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kSplineAOResID, 0, 0));
}

void Abe::FreeElumRes_420F80()
{
    if (mCurrentMotion == eAbeMotions::Motion_139_ElumMountBegin_42E090)
    {
        field_2AA_flags.Set(Flags_2AA::e2AA_Bit3_ElumMountBegin);
    }
    else
    {
        field_2AA_flags.Clear(Flags_2AA::e2AA_Bit3_ElumMountBegin);
    }

    if (mCurrentMotion == eAbeMotions::Motion_136_ElumMountEnd_42E110)
    {
        field_2AA_flags.Set(Flags_2AA::e2AA_Bit4_ElumMountEnd);
    }
    else
    {
        field_2AA_flags.Clear(Flags_2AA::e2AA_Bit4_ElumMountEnd);
    }

    if (mCurrentMotion == eAbeMotions::Motion_137_ElumUnmountBegin_42E2B0)
    {
        field_2AA_flags.Set(Flags_2AA::e2AA_Bit5_ElumUnmountBegin);
    }
    else
    {
        field_2AA_flags.Clear(Flags_2AA::e2AA_Bit5_ElumUnmountBegin);
    }

    ElumFree_4228F0();

    while (!ResourceManager::FreeResource_455550(field_1A4_resources.res[58]))
    {
        // Empty
    }

    field_1A4_resources.res[58] = nullptr;
    ResourceManager::FreeResource_455550(field_1A4_resources.res[46]);

    field_1A4_resources.res[46] = nullptr;
    if (gElum_507680)
    {
        gElum_507680->VFreeMountedResources_411200();
    }

    if (mCurrentMotion != eAbeMotions::Motion_138_ElumUnmountEnd_42E390)
    {
        field_104_pending_resource_count++;
        ResourceManager::LoadResourceFile("ABEBSIC.BAN", BaseAliveGameObject::OnResourceLoaded_4019A0, this);

        if (!ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAneprmntAOResID, 0, 0))
        {
            field_104_pending_resource_count++;
            ResourceManager::LoadResourceFile("ANEPRMNT.BAN", BaseAliveGameObject::OnResourceLoaded_4019A0, this);
        }

        if (gElum_507680)
        {
            if (gElum_507680->field_144_bRespawnOnDead)
            {
                field_104_pending_resource_count++;
                ResourceManager::LoadResourceFile("ELMPRMNT.BAN", BaseAliveGameObject::OnResourceLoaded_4019A0, this);

                if (!ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kElmaloneAOResID_230, 0, 0))
                {
                    field_104_pending_resource_count++;
                    ResourceManager::LoadResourceFile("ELMALONE.BAN", BaseAliveGameObject::OnResourceLoaded_4019A0, this);
                }
            }
        }

        field_104_pending_resource_count++;
        ResourceManager::LoadResourceFile("ABENOELM.BND", BaseAliveGameObject::OnResourceLoaded_4019A0, this);

        if (!ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeommAOResID, 0, 0))
        {
            field_104_pending_resource_count++;
            ResourceManager::LoadResourceFile("ABEOMM.BAN", BaseAliveGameObject::OnResourceLoaded_4019A0, this);
        }
    }
}

void Abe::ToDeathDropFall_42C3D0()
{
    field_2A8_flags.Set(Flags_2A8::e2A8_Bit6_bShrivel);
    mCurrentMotion = eAbeMotions::Motion_59_DeathDropFall_42CBE0;
    field_114_gnFrame = 0;
    mHealth = FP_FromInteger(0);
    MusicController::static_PlayMusic(MusicController::MusicTypes::eType0, this, 1, 0);
}

Bool32 Abe::IsStanding_41FC10()
{
    return mCurrentMotion == eAbeMotions::Motion_0_Idle_423520
        || mCurrentMotion == eAbeMotions::Motion_1_WalkLoop_423F90
        || mCurrentMotion == eAbeMotions::Motion_27_RunSlideStop_425B60
        || mCurrentMotion == eAbeMotions::Motion_28_RunTurn_425CE0
        || mCurrentMotion == eAbeMotions::Motion_35_RunLoop_425060
        || mCurrentMotion == eAbeMotions::Motion_2_StandingTurn_426040
        || mCurrentMotion == eAbeMotions::Motion_36_DunnoBegin_423260
        || mCurrentMotion == eAbeMotions::Motion_37_DunnoMid_4232C0
        || mCurrentMotion == eAbeMotions::Motion_38_DunnoEnd_423310
        || mCurrentMotion == eAbeMotions::Motion_4_WalkToIdle_4243C0
        || mCurrentMotion == eAbeMotions::Motion_5_MidWalkToIdle_424490
        || mCurrentMotion == eAbeMotions::Motion_6_WalkBegin_424300
        || mCurrentMotion == eAbeMotions::Motion_41_StandingToRun_425530
        || mCurrentMotion == eAbeMotions::Motion_42_SneakLoop_424BB0
        || mCurrentMotion == eAbeMotions::Motion_43_WalkToSneak_424790
        || mCurrentMotion == eAbeMotions::Motion_44_SneakToWalk_4249A0
        || mCurrentMotion == eAbeMotions::Motion_45_MidWalkToSneak_424890
        || mCurrentMotion == eAbeMotions::Motion_46_MidSneakToWalk_424AA0
        || mCurrentMotion == eAbeMotions::Motion_47_SneakBegin_424ED0
        || mCurrentMotion == eAbeMotions::Motion_48_SneakToIdle_424F80
        || mCurrentMotion == eAbeMotions::Motion_49_MidSneakToIdle_424FF0
        || mCurrentMotion == eAbeMotions::Motion_50_WalkToRun_424560
        || mCurrentMotion == eAbeMotions::Motion_51_MidWalkToRun_424670
        || mCurrentMotion == eAbeMotions::Motion_52_RunToWalk_4255E0
        || mCurrentMotion == eAbeMotions::Motion_53_MidRunToWalk_4256E0
        || mCurrentMotion == eAbeMotions::Motion_54_RunTurnToRun_425EA0
        || mCurrentMotion == eAbeMotions::Motion_55_RunTurnToWalk_425F70
        || mCurrentMotion == eAbeMotions::Motion_58_ToSpeak_42F8D0
        || mCurrentMotion == eAbeMotions::Motion_7_Speak_42F950
        || mCurrentMotion == eAbeMotions::Motion_8_Speak_42F9D0
        || mCurrentMotion == eAbeMotions::Motion_9_Speak_42FA50
        || mCurrentMotion == eAbeMotions::Motion_10_Speak_42FAD0
        || mCurrentMotion == eAbeMotions::Motion_11_Speak_42FB50
        || mCurrentMotion == eAbeMotions::Motion_12_Speak_42FBD0
        || mCurrentMotion == eAbeMotions::Motion_13_Speak_42FC50
        || mCurrentMotion == eAbeMotions::Motion_14_Speak_42FCD0
        || mCurrentMotion == eAbeMotions::Motion_101_LeverUse_429970
        || mCurrentMotion == eAbeMotions::Motion_140_BeesStruggling_423F30
        || mCurrentMotion == eAbeMotions::Motion_143_RockThrowStandingThrow_429FD0
        || mCurrentMotion == eAbeMotions::Motion_142_RockThrowStandingHold_429CE0
        || mCurrentMotion == eAbeMotions::Motion_144_RockThrowStandingEnd_429DE0
        || mCurrentMotion == eAbeMotions::Motion_150_Chant_42FD50
        || mCurrentMotion == eAbeMotions::Motion_151_ChantEnd_430530
        || mCurrentMotion == eAbeMotions::Motion_159_Idle_RubEyes_423360
        || mCurrentMotion == eAbeMotions::Motion_160_Idle_Stretch_Arms_4233A0
        || mCurrentMotion == eAbeMotions::Motion_161_Idle_Yawn_4233E0
        || mCurrentMotion == eAbeMotions::Motion_164_PoisonGasDeath_42A120;
}

void Abe::FollowLift_42EE90()
{
    if (mLiftPoint)
    {
        field_B8_vely = mLiftPoint->field_B8_vely;
        if (mLiftPoint->mBaseGameObjectFlags.Get(BaseGameObject::eDead))
        {
            mLiftPoint->VOnPickUpOrSlapped();
            field_2A8_flags.Set(Flags_2A8::e2A8_Bit1);
        }
        SetActiveCameraDelayedFromDir_401C90();
    }
}

void Abe::ExitShrykull_42F440(s16 bResetRingTimer)
{
    field_10_anim.mAnimFlags.Set(AnimFlags::eBit2_Animate);
    field_10_anim.mAnimFlags.Set(AnimFlags::eBit3_Render);

    mCurrentMotion = eAbeMotions::Motion_163_ShrykullEnd_42F520;

    field_108_bMotionChanged = 1;
    field_114_gnFrame = 1;

    if (bResetRingTimer)
    {
        field_168_ring_pulse_timer = 0;
    }
}

s16 Abe::RunTryEnterWell_425880()
{
    if (!Input().IsAnyPressed(sInputKey_Up_4C6598) || field_10_anim.field_92_current_frame < 4)
    {
        return 0;
    }

    auto pWellLocal = static_cast<Path_WellLocal*>(gMap.TLV_Get_At_446260(
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
        TlvTypes::WellLocal_11));
    if (pWellLocal)
    {
        if ((pWellLocal->field_18_scale == Scale_short::eFull_0 && field_BC_sprite_scale == FP_FromInteger(1)) ||
            (pWellLocal->field_18_scale == Scale_short::eHalf_1 && field_BC_sprite_scale == FP_FromDouble(0.5)))
        {
            field_2A8_flags.Clear(Flags_2A8::e2A8_Bit4_snap_abe);
            BaseAliveGameObjectPathTLV = pWellLocal;
            mCurrentMotion = eAbeMotions::Motion_77_WellBegin_430F10;
            return 1;
        }
    }

    auto pWellExpress = static_cast<Path_WellExpress*>(gMap.TLV_Get_At_446260(
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
        TlvTypes::WellExpress_45));
    if (pWellExpress)
    {
        if ((pWellExpress->field_18_scale == Scale_short::eFull_0 && field_BC_sprite_scale == FP_FromInteger(1)) ||
            (pWellExpress->field_18_scale == Scale_short::eHalf_1 && field_BC_sprite_scale == FP_FromDouble(0.5)))
        {
            field_2A8_flags.Clear(Flags_2A8::e2A8_Bit4_snap_abe);
            BaseAliveGameObjectPathTLV = pWellExpress;
            mCurrentMotion = eAbeMotions::Motion_80_430EF0;
        }
    }

    return 0;
}

void Abe::ChangeChantState_430510(s16 bKeepChanting)
{
    if (bKeepChanting)
    {
        field_110_state.chant = ChantStates::eChantingForBirdPortal_6;
    }
    else
    {
        field_110_state.chant = ChantStates::eIdleChanting_0;
    }
}

BaseAliveGameObject* Abe::FindObjectToPossess_421410()
{
    for (s32 i = 0; i < gBaseAliveGameObjects_4FC8A0->Size(); i++)
    {
        BaseAliveGameObject* pObj = gBaseAliveGameObjects_4FC8A0->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if (pObj->mBaseGameObjectFlags.Get(BaseGameObject::eIsBaseAliveGameObject_Bit6))
        {
            if (pObj->mBaseAliveGameObjectFlags.Get(Flags_10A::e10A_Bit1_Can_Be_Possessed))
            {
                if (pObj->mBaseGameObjectTypeId != ReliveTypes::eSlig || (pObj->Is_In_Current_Camera_417CC0() == CameraPos::eCamCurrent_0 && pObj->mHealth > FP_FromInteger(0)))
                {
                    return pObj;
                }
            }
        }
    }
    return nullptr;
}

void Abe::Get_Shrykull_Resources_42F480()
{
    ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbemorphAOResID, 1, 0);
    ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kShrmorphAOResID, 1, 0);
    ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kSplineAOResID, 1, 0);
}

void Abe::ToDieFinal_42C400()
{
    field_2A8_flags.Set(Flags_2A8::e2A8_Bit6_bShrivel);
    mCurrentMotion = eAbeMotions::Motion_60_Dead_42C4C0;
    field_114_gnFrame = 0;
    mHealth = FP_FromInteger(0);
    MusicController::static_PlayMusic(MusicController::MusicTypes::eDeathLong_14, this, 1, 0);
}

void Abe::ToKnockback_422D90(s16 bKnockbackSound, s16 bDelayedAnger)
{
    if (sControlledCharacter_50767C->mBaseGameObjectTypeId != ReliveTypes::eSlig || mHealth <= FP_FromInteger(0))
    {
        SND_Seq_Stop_477A60(SeqId::eMudokonChant1_11);
        field_2AA_flags.Clear(Flags_2AA::e2AA_Bit3_ElumMountBegin);
        field_2AA_flags.Clear(Flags_2AA::e2AA_Bit4_ElumMountEnd);
        field_2AA_flags.Clear(Flags_2AA::e2AA_Bit5_ElumUnmountBegin);

        if (field_188_pOrbWhirlWind)
        {
            field_188_pOrbWhirlWind->ToStop();
            field_188_pOrbWhirlWind = nullptr;
        }

        if (field_B4_velx != FP_FromInteger(0))
        {
            mBaseAnimatedWithPhysicsGameObject_XPos -= field_B4_velx;
        }

        MapFollowMe_401D30(1);

        field_B4_velx = FP_FromInteger(0);
        if (field_B8_vely < FP_FromInteger(0))
        {
            field_B8_vely = FP_FromInteger(0);
        }

        field_114_gnFrame = sGnFrame + 10;

        if (bKnockbackSound)
        {
            Mudokon_SFX_42A4D0(MudSounds::eKnockbackOuch_10, 0, Math_RandomRange_450F20(-127, 127), this);
            Environment_SFX_42A220(EnvironmentSfx::eKnockback_13, 0, 0x7FFF, this);
        }

        if (!field_1A4_resources.res[0] && !field_104_pending_resource_count)
        {
            sControlledCharacter_50767C = this;
            BaseAliveGameObjectLastLineYPos = mBaseAnimatedWithPhysicsGameObject_YPos;
            BaseAliveGameObjectCollisionLine = nullptr;
            mBaseAnimatedWithPhysicsGameObject_YPos -= (field_BC_sprite_scale * FP_FromInteger(20));
            VOnTrapDoorOpen();
            FreeElumRes_420F80();
        }

        mCurrentMotion = eAbeMotions::Motion_70_Knockback_428FB0;

        if (bDelayedAnger)
        {
            field_130_say = 5;
            field_134_auto_say_timer = sGnFrame + 27;
        }

        if (field_198_pThrowable)
        {
            field_198_pThrowable->VToDead();
            field_198_pThrowable = nullptr;
            if (gInfiniteGrenades_5076EC == 0)
            {
                field_19C_throwable_count++;
            }
        }
    }
}

u8** Abe::StateToAnimResource_4204F0(s16 motion)
{
    s16 res_idx = 0;

    if (motion < eAbeMotions::Motion_15_Null_42A210)
    {
        res_idx = 45;
    }
    else if (motion < eAbeMotions::Motion_64_LedgeAscend_428B60)
    {
        res_idx = 0;
    }
    else if (motion < eAbeMotions::Motion_70_Knockback_428FB0)
    {
        res_idx = 32;
    }
    else if (motion < eAbeMotions::Motion_74_JumpIntoWell_430EC0)
    {
        res_idx = 16;
    }
    else if (motion < eAbeMotions::Motion_86_FallLandDie_42EDD0)
    {
        res_idx = 37;
    }
    else if (motion < eAbeMotions::Motion_87_ToFall_428FA0)
    {
        res_idx = 9;
    }
    else if (motion < eAbeMotions::Motion_88_HandstoneBegin_430590)
    {
        res_idx = 10;
    }
    else if (motion < eAbeMotions::Motion_91_FallingFromGrab_429780)
    {
        res_idx = 11;
    }
    else if (motion < eAbeMotions::Motion_101_LeverUse_429970)
    {
        res_idx = 33;
    }
    else if (motion < eAbeMotions::Motion_102_ElumWalkLoop_42DCA0)
    {
        res_idx = 1;
    }
    else if (motion < eAbeMotions::Motion_127_SlapBomb_429A20)
    {
        res_idx = 46;
    }
    else if (motion < eAbeMotions::Motion_128_KnockForward_429330)
    {
        res_idx = 3;
    }
    else if (motion < eAbeMotions::Motion_131_LiftUseUp_42F150)
    {
        res_idx = 17;
    }
    else if (motion < eAbeMotions::Motion_136_ElumMountEnd_42E110)
    {
        res_idx = 43;
    }
    else if (motion < eAbeMotions::Motion_137_ElumUnmountBegin_42E2B0)
    {
        res_idx = 56;
    }
    else if (motion < eAbeMotions::Motion_138_ElumUnmountEnd_42E390)
    {
        res_idx = 58;
    }
    else if (motion < eAbeMotions::Motion_139_ElumMountBegin_42E090)
    {
        res_idx = 59;
    }
    else if (motion < eAbeMotions::Motion_140_BeesStruggling_423F30)
    {
        res_idx = 61;
    }
    else if (motion < eAbeMotions::Motion_142_RockThrowStandingHold_429CE0)
    {
        res_idx = 6;
    }
    else if (motion < eAbeMotions::Motion_147_ShotRolling_4295C0)
    {
        res_idx = 4;
    }
    else if (motion < eAbeMotions::Motion_149_PickupItem_42A030)
    {
        res_idx = 18;
    }
    else if (motion < eAbeMotions::Motion_150_Chant_42FD50)
    {
        res_idx = 2;
    }
    else if (motion < eAbeMotions::Motion_152_ElumFallOffEdge_42E030)
    {
        res_idx = 38;
    }
    else if (motion < eAbeMotions::Motion_156_DoorEnter_42D370)
    {
        res_idx = 54;
    }
    else if (motion < eAbeMotions::Motion_158_ElumKnockback_42E070)
    {
        res_idx = 35;
    }
    else if (motion < eAbeMotions::Motion_159_Idle_RubEyes_423360)
    {
        res_idx = 52;
    }
    else if (motion < eAbeMotions::Motion_160_Idle_Stretch_Arms_4233A0)
    {
        res_idx = 22;
    }
    else if (motion < eAbeMotions::Motion_161_Idle_Yawn_4233E0)
    {
        res_idx = 23;
    }
    else if (motion < eAbeMotions::Motion_162_ToShrykull_42F410)
    {
        res_idx = 21;
    }
    else if (motion >= eAbeMotions::Motion_164_PoisonGasDeath_42A120)
    {
        res_idx = 64;
        if (motion >= 165)
        {
            res_idx = motion;
        }
    }
    else
    {
        res_idx = 63;
    }


    if (res_idx == field_128_resource_idx)
    {
        return field_1A4_resources.res[field_128_resource_idx];
    }

    if (field_128_resource_idx)
    {
        if (field_128_resource_idx != 45 && field_128_resource_idx != 46)
        {
            ResourceManager::FreeResource_455550(field_1A4_resources.res[field_128_resource_idx]);
            field_1A4_resources.res[field_128_resource_idx] = nullptr;
        }
    }
    if (res_idx)
    {
        if (res_idx != 45 && res_idx != 46)
        {
            s32 resourceID = res_idx + 10;
            if (res_idx >= 46)
            {
                resourceID = res_idx + 54;
            }

            u8** ppRes = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, resourceID, 1, 0);
            if (!ppRes)
            {
                LOG_ERROR("Abe resource failed to load " << resourceID);
            }
            field_1A4_resources.res[res_idx] = ppRes;
        }
    }
    field_128_resource_idx = res_idx;
    return field_1A4_resources.res[res_idx];
}

void Abe::ToIdle_422D50()
{
    field_120_x_vel_slow_by = FP_FromInteger(0);
    field_B4_velx = FP_FromInteger(0);
    field_B8_vely = FP_FromInteger(0);
    field_114_gnFrame = sGnFrame;
    mCurrentMotion = eAbeMotions::Motion_0_Idle_423520;
    field_10C_prev_held = 0;
    field_10E_released_buttons = 0;
}

void Abe::MoveForward_422FC0()
{
    FollowLift_42EE90();

    const FP old_x = mBaseAnimatedWithPhysicsGameObject_XPos;

    if (BaseAliveGameObjectCollisionLine)
    {
        BaseAliveGameObjectCollisionLine = BaseAliveGameObjectCollisionLine->MoveOnLine(
            &mBaseAnimatedWithPhysicsGameObject_XPos,
            &mBaseAnimatedWithPhysicsGameObject_YPos,
            field_B4_velx);
    }

    // TODO: Check mask is correct
    const s32 mask = field_BC_sprite_scale != FP_FromDouble(0.5) ? 1 : 0x10;
    if (BaseAliveGameObjectCollisionLine && (mask & (1 << BaseAliveGameObjectCollisionLine->field_8_type)))
    {
        if (mLiftPoint)
        {
            if (BaseAliveGameObjectCollisionLine->field_8_type != eLineTypes ::eUnknown_32 &&
                BaseAliveGameObjectCollisionLine->field_8_type != eLineTypes::eUnknown_36)
            {
                mLiftPoint->VRemove(this);
                mLiftPoint->mBaseGameObjectRefCount--;
                mLiftPoint = nullptr;
            }
        }
        else if (BaseAliveGameObjectCollisionLine->field_8_type == eLineTypes::eUnknown_32 ||
                BaseAliveGameObjectCollisionLine->field_8_type == eLineTypes::eUnknown_36)
        {
            PSX_RECT bRect = {};
            VGetBoundingRect(&bRect, 1);
            bRect.y += 5;
            bRect.h += 5;
            bRect.w += 5; // TODO: Seems wrong - same in AE

            VOnCollisionWith(
                {bRect.x, bRect.y},
                {bRect.w, bRect.h},
                ObjListPlatforms_50766C,
                1,
                (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection_401C10);
        }
    }
    else
    {
        BaseAliveGameObjectCollisionLine = nullptr;

        if (mLiftPoint)
        {
            mLiftPoint->VRemove(this);
            mLiftPoint->mBaseGameObjectRefCount--;
            mLiftPoint = nullptr;
        }

        field_10C_prev_held = 0;
        switch (mCurrentMotion)
        {
            case eAbeMotions::Motion_1_WalkLoop_423F90:
            case eAbeMotions::Motion_6_WalkBegin_424300:
            case eAbeMotions::Motion_4_WalkToIdle_4243C0:
            case eAbeMotions::Motion_5_MidWalkToIdle_424490:
                mCurrentMotion = eAbeMotions::Motion_93_WalkOffEdge_429840;
                break;

            case eAbeMotions::Motion_35_RunLoop_425060:
            case eAbeMotions::Motion_41_StandingToRun_425530:
                mCurrentMotion = eAbeMotions::Motion_94_RunOffEdge_429860;
                break;

            case eAbeMotions::Motion_40_RunToRoll_427AE0:
            case eAbeMotions::Motion_24_RollBegin_427A20:
            case eAbeMotions::Motion_25_RollLoop_427BB0:
            case eAbeMotions::Motion_26_RollEnd_427EA0:
                mCurrentMotion = eAbeMotions::Motion_100_RollOffLedge_429950;
                break;

            default:
                mCurrentMotion = eAbeMotions::Motion_95_SneakOffEdge_429880;
                break;
        }

        mBaseAnimatedWithPhysicsGameObject_XPos = old_x + field_B4_velx;
        BaseAliveGameObjectLastLineYPos = mBaseAnimatedWithPhysicsGameObject_YPos;

        // TODO: OG bug, dead code due to switch default case ?
        if (mCurrentMotion == eAbeMotions::Motion_70_Knockback_428FB0 || mCurrentMotion == eAbeMotions::Motion_128_KnockForward_429330)
        {
            field_120_x_vel_slow_by = FP_FromDouble(0.67); // TODO: Check
        }
    }
}

void Abe::ElumFree_4228F0()
{
    if (field_2AA_flags.Get(Flags_2AA::e2AA_Bit4_ElumMountEnd))
    {
        ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kElumUnknownAOResID_110, 1, 0));
        ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kElumAneMountAOResID_223, 1, 0));
        ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kElmprmntAOResID__222, 0, 0));

        if (gElum_507680->mCurrentMotion != eElumMotions::Motion_1_Idle_412990)
        {
            gElum_507680->Vsub_416120();
        }
    }

    if (field_2AA_flags.Get(Flags_2AA::e2AA_Bit4_ElumMountEnd))
    {
        ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeWElmAOResID_100, 1, 0));
        ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kElumUnknownAOResID_112, 1, 0));
        ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kElumRideAOResID_220, 1, 0));
        ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kElumPdmntAOResID_221, 1, 0));
    }

    if (field_2AA_flags.Get(Flags_2AA::e2AA_Bit5_ElumUnmountBegin))
    {
        ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeANEDSMNTAOResID_113, 1, 0));
        ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kElumANEDSMNTAOResID_224, 1, 0));
        ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kElumPdmntAOResID_221, 0, 0));

        if (gElum_507680->mCurrentMotion != eElumMotions::Motion_1_Idle_412990)
        {
            gElum_507680->Vsub_416120();
        }
    }
}

s16 Abe::DoGameSpeak_42F5C0(u16 input)
{
    if (Input_IsChanting())
    {
        field_114_gnFrame = sGnFrame + 90;
        SND_SEQ_PlaySeq_4775A0(SeqId::eMudokonChant1_11, 0, 1);
        field_110_state.chant = ChantStates::eIdleChanting_0;
        return eAbeMotions::Motion_150_Chant_42FD50;
    }

#if ORIGINAL_PS1_BEHAVIOR // OG Change - Faster check for GameSpeak
    const bool leftGameSpeakPressed = (input & eLeftGamespeak);
    const bool rightGameSpeakPressed = (input & eRightGameSpeak);
#else
    const bool leftGameSpeakPressed = Input().IsAnyPressed(sInputKey_LeftGameSpeakEnabler_4C65B8);
    const bool rightGameSpeakPressed = Input().IsAnyPressed(sInputKey_RightGameSpeakEnabler_4C65DC);
#endif

    if (leftGameSpeakPressed)
    {
        if (input & sInputKey_GameSpeak2_4C65BC)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eFollowMe_10);
            Mudokon_SFX_42A4D0(MudSounds::eFollowMe_4, 0, 0, this);
            if (mCurrentMotion == eAbeMotions::Motion_14_Speak_42FCD0)
            {
                field_108_bMotionChanged = 1;
            }
            return eAbeMotions::Motion_14_Speak_42FCD0;
        }
        if (input & sInputKey_GameSpeak4_4C65C4)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eWait_12);
            Mudokon_SFX_42A4D0(MudSounds::eWait_6, 0, 0, this);
            if (mCurrentMotion == eAbeMotions::Motion_14_Speak_42FCD0)
            {
                field_108_bMotionChanged = 1;
            }
            return eAbeMotions::Motion_13_Speak_42FC50;
        }
        if (input & sInputKey_GameSpeak1_4C65C8)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eHello_9);
            Mudokon_SFX_42A4D0(MudSounds::eHello_3, 0, 0, this);
            if (mCurrentMotion == eAbeMotions::Motion_9_Speak_42FA50)
            {
                field_108_bMotionChanged = 1;
            }
            return eAbeMotions::Motion_9_Speak_42FA50;
        }
        if (input & sInputKey_GameSpeak3_4C65C0)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eAnger_11);
            Mudokon_SFX_42A4D0(MudSounds::eAngry_5, 0, 0, this);
            if (mCurrentMotion == eAbeMotions::Motion_10_Speak_42FAD0)
            {
                field_108_bMotionChanged = 1;
            }
            return eAbeMotions::Motion_10_Speak_42FAD0;
        }
    }

    if (rightGameSpeakPressed)
    {
        if (input & sInputKey_GameSpeak6_4C65E8)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eWhistleHigh_1);
            Mudokon_SFX_42A4D0(MudSounds::eWhistleHigh_1, 0, 0, this);
            if (mCurrentMotion == eAbeMotions::Motion_9_Speak_42FA50)
            {
                field_108_bMotionChanged = 1;
            }
            return eAbeMotions::Motion_9_Speak_42FA50;
        }
        if (input & sInputKey_GameSpeak5_4C65EC)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eWhistleLow_2);
            Mudokon_SFX_42A4D0(MudSounds::eWhistleLow_2, 0, 0, this);
            if (mCurrentMotion == eAbeMotions::Motion_8_Speak_42F9D0)
            {
                field_108_bMotionChanged = 1;
            }
            return eAbeMotions::Motion_8_Speak_42F9D0;
        }
        if (input & sInputKey_GameSpeak8_4C65E0)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eLaugh_4);
            Mudokon_SFX_42A4D0(MudSounds::eLaugh1_8, 0, 0, this);
            if (mCurrentMotion == eAbeMotions::Motion_12_Speak_42FBD0)
            {
                field_108_bMotionChanged = 1;
            }
            return eAbeMotions::Motion_12_Speak_42FBD0;
        }
        if (input & sInputKey_GameSpeak7_4C65E4)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eFart_3);
            Mudokon_SFX_42A4D0(MudSounds::eFart_7, 0, 0, this);
            if (sEnableFartGasCheat_507704)
            {
                FP xPos = mBaseAnimatedWithPhysicsGameObject_XPos;
                if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    xPos += (FP_FromInteger(12) * field_BC_sprite_scale);
                }
                else
                {
                    xPos -= (FP_FromInteger(12) * field_BC_sprite_scale);
                }
                New_Smoke_Particles_419A80(
                    xPos,
                    mBaseAnimatedWithPhysicsGameObject_YPos - (FP_FromInteger(24) * field_BC_sprite_scale),
                    FP_FromDouble(0.5) * field_BC_sprite_scale,
                    3,
                    1);
            }
            field_130_say = 8;
            field_134_auto_say_timer = sGnFrame + 15;
            if (mCurrentMotion == eAbeMotions::Motion_10_Speak_42FAD0)
            {
                field_108_bMotionChanged = 1;
            }
            return eAbeMotions::Motion_10_Speak_42FAD0;
        }
    }
    return -1;
}

void Abe::SyncToElum_42D850(s16 elumMotion)
{
    if (mCurrentMotion != eAbeMotions::Motion_137_ElumUnmountBegin_42E2B0 && mCurrentMotion != eAbeMotions::Motion_138_ElumUnmountEnd_42E390)
    {
        switch (elumMotion)
        {
            case eElumMotions::Motion_1_Idle_412990:
                mCurrentMotion = eAbeMotions::Motion_103_ElumIdle_42DCD0;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                BaseAliveGameObjectCollisionLine = gElum_507680->BaseAliveGameObjectCollisionLine;
                break;

            case eElumMotions::Motion_3_WalkLoop_412C90:
                mCurrentMotion = eAbeMotions::Motion_102_ElumWalkLoop_42DCA0;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                BaseAliveGameObjectCollisionLine = gElum_507680->BaseAliveGameObjectCollisionLine;
                break;

            case eElumMotions::Motion_4_Turn_4140F0:
                mCurrentMotion = eAbeMotions::Motion_113_ElumTurn_42DF90;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                break;

            case eElumMotions::Motion_5_WalkToIdle_4132D0:
                mCurrentMotion = eAbeMotions::Motion_124_ElumWalkEnd_42DCB0;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                break;

            case eElumMotions::Motion_6_MidWalkToIdle_4133F0:
                mCurrentMotion = eAbeMotions::Motion_125_ElumMidWalkEnd_42DCC0;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                break;

            case eElumMotions::Motion_7_IdleToWalk1_413200:
                mCurrentMotion = eAbeMotions::Motion_116_Null_42DFB0;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                break;

            case eElumMotions::Motion_8_IdleToWalk2_413270:
                mCurrentMotion = eAbeMotions::Motion_117_ElumWalkBegin_42DFC0;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                break;

            case eElumMotions::Motion_12_RunTurn_414520:
                mCurrentMotion = eAbeMotions::Motion_105_ElumRunTurn_42DF10;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                break;

            case eElumMotions::Motion_13_RunTurnToWalk_4147C0:
                mCurrentMotion = eAbeMotions::Motion_123_ElumRunTurnToWalk_42E020;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                break;

            case eElumMotions::Motion_21_Land_414A20:
                mCurrentMotion = eAbeMotions::Motion_153_ElumFall_42E040;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                BaseAliveGameObjectCollisionLine = nullptr;
                break;

            case eElumMotions::Motion_22_RunOffEdge_415810:
                mCurrentMotion = eAbeMotions::Motion_154_ElumLand_42E050;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                BaseAliveGameObjectCollisionLine = gElum_507680->BaseAliveGameObjectCollisionLine;
                break;

            case eElumMotions::Motion_23_WalkOffEdge_415E90:
                mCurrentMotion = eAbeMotions::Motion_152_ElumFallOffEdge_42E030;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                BaseAliveGameObjectCollisionLine = nullptr;
                break;

            case eElumMotions::Motion_24_JumpToFall_415ED0:
                mCurrentMotion = eAbeMotions::Motion_155_ElumJumpToFall_42E060;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                BaseAliveGameObjectCollisionLine = nullptr;
                break;

            case eElumMotions::Motion_30_HopBegin_414E30:
                mCurrentMotion = eAbeMotions::Motion_107_ElumHopBegin_42DF30;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                BaseAliveGameObjectCollisionLine = nullptr;
                break;

            case eElumMotions::Motion_31_HopMid_414C70:
                mCurrentMotion = eAbeMotions::Motion_108_ElumHopMid_42DF40;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                break;

            case eElumMotions::Motion_32_HopLand_415140:
                mCurrentMotion = eAbeMotions::Motion_109_ElumHopLand_42DF50;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                BaseAliveGameObjectCollisionLine = gElum_507680->BaseAliveGameObjectCollisionLine;
                break;

            case eElumMotions::Motion_33_RunJumpBegin_415400:
                mCurrentMotion = eAbeMotions::Motion_110_ElumRunJumpBegin_42DF60;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                BaseAliveGameObjectCollisionLine = nullptr;
                break;

            case eElumMotions::Motion_34_RunJumpMid_415240:
                mCurrentMotion = eAbeMotions::Motion_111_ElumRunJumpMid_42DF70;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                break;

            case eElumMotions::Motion_35_RunJumpLand_415580:
                mCurrentMotion = eAbeMotions::Motion_112_ElumRunJumpLand_42DF80;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                BaseAliveGameObjectCollisionLine = gElum_507680->BaseAliveGameObjectCollisionLine;
                break;

            case eElumMotions::Motion_36_RunLoop_413720:
                mCurrentMotion = eAbeMotions::Motion_114_ElumRunLoop_42DFA0;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                BaseAliveGameObjectCollisionLine = gElum_507680->BaseAliveGameObjectCollisionLine;
                break;

            case eElumMotions::Motion_37_RunSlideStop_4142E0:
                mCurrentMotion = eAbeMotions::Motion_104_ElumRunSlideStop_42DF00;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                break;

            case eElumMotions::Motion_38_RunTurnToRun_414810:
                mCurrentMotion = eAbeMotions::Motion_122_ElumRunTurnToRun_42E010;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                break;

            case eElumMotions::Motion_39_IdleToRun_413B00:
                mCurrentMotion = eAbeMotions::Motion_118_ElumRunBegin_42DFD0;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                break;

            case eElumMotions::Motion_40_WalkToRun_4134B0:
                mCurrentMotion = eAbeMotions::Motion_119_Null_42DFE0;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                break;

            case eElumMotions::Motion_41_MidWalkToRun_413560:
                mCurrentMotion = eAbeMotions::Motion_120_ElumRunToWalk_42DFF0;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                break;

            case eElumMotions::Motion_43_MidRunToWalk_413E20:
                mCurrentMotion = eAbeMotions::Motion_121_ElumMidRunToWalk_42E000;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                break;

            case eElumMotions::Motion_50_Knockback_415DC0:
                mCurrentMotion = eAbeMotions::Motion_158_ElumKnockback_42E070;
                ToNewElumSyncMotion_422520(gElum_507680->field_10_anim.field_92_current_frame);
                break;

            default:
                break;
        }
    }
}

void Abe::PickUpThrowabe_Or_PressBomb_428260(FP fpX, s32 fpY, s16 bStandToCrouch)
{
    BaseAliveGameObject* pSlapableOrCollectable = nullptr;
    for (s32 i = 0; i < gBaseGameObjects->Size(); i++)
    {
        BaseGameObject* pObj = gBaseGameObjects->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if (pObj->mBaseGameObjectFlags.Get(BaseGameObject::eInteractive_Bit8))
        {
            BaseAliveGameObject* pAliveObj = static_cast<BaseAliveGameObject*>(pObj);
            if (fpX >= pAliveObj->mBaseAliveGameObjectCollectionRect.x && fpX <= pAliveObj->mBaseAliveGameObjectCollectionRect.w)
            {
                const FP yPos = FP_FromInteger(fpY);
                if (yPos >= pAliveObj->mBaseAliveGameObjectCollectionRect.y && yPos <= pAliveObj->mBaseAliveGameObjectCollectionRect.h)
                {
                    pSlapableOrCollectable = pAliveObj;
                    pSlapableOrCollectable->mBaseGameObjectRefCount++;
                    field_15C_pThrowable = static_cast<BaseThrowable*>(pSlapableOrCollectable);
                    break;
                }
            }
        }
    }


    if (pSlapableOrCollectable)
    {
        bool tryToSlapOrCollect = false;

        switch (pSlapableOrCollectable->mBaseGameObjectTypeId)
        {
            case ReliveTypes::eTimedMine:
            case ReliveTypes::eUXB:
                mCurrentMotion = eAbeMotions::Motion_127_SlapBomb_429A20;
                if (bStandToCrouch)
                {
                    field_15C_pThrowable->mBaseGameObjectRefCount--;
                    field_15C_pThrowable = nullptr;
                }
                tryToSlapOrCollect = true;
                break;

            case ReliveTypes::eGrenade:
            case ReliveTypes::eMeat:
            case ReliveTypes::eRock:
                mCurrentMotion = eAbeMotions::Motion_149_PickupItem_42A030;
                field_19C_throwable_count += static_cast<s8>(field_15C_pThrowable->VGetCount());

                if (!bThrowableIndicatorExists_504C70)
                {
                    const FP v16 = (field_BC_sprite_scale * FP_FromInteger(-30)) + mBaseAnimatedWithPhysicsGameObject_YPos;
                    ao_new<ThrowableTotalIndicator>(
                                                                          (field_BC_sprite_scale * FP_FromInteger(0)) + mBaseAnimatedWithPhysicsGameObject_XPos,
                                                                               v16,
                                                                               field_10_anim.mRenderLayer,
                                                                               field_10_anim.field_14_scale,
                                                                               field_19C_throwable_count,
                                                                               1);
                }
                tryToSlapOrCollect = true;
                break;

            case ReliveTypes::eMine:
                field_15C_pThrowable->mBaseGameObjectRefCount--;
                field_15C_pThrowable = nullptr;
                tryToSlapOrCollect = true;
                break;

            default:
                return;
        }

        if (tryToSlapOrCollect)
        {
            if (mCurrentMotion == eAbeMotions::Motion_149_PickupItem_42A030)
            {
                if (bStandToCrouch)
                {
                    SFX_Play_Mono(SoundEffect::PickupItem_33, 0, this);
                    field_15C_pThrowable->mBaseGameObjectRefCount--;
                    field_15C_pThrowable->VOnPickUpOrSlapped();
                    field_15C_pThrowable = nullptr;
                    mCurrentMotion = eAbeMotions::Motion_19_CrouchIdle_4284C0;
                }
            }
        }
    }
}

void Abe::CrouchingGameSpeak_427F90()
{
    field_10C_prev_held |= Input().Held();

    if (Input().IsAnyPressed(sInputKey_LeftGameSpeakEnabler_4C65B8))
    {
        if (field_10C_prev_held & sInputKey_GameSpeak2_4C65BC)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eFollowMe_10);
            Mudokon_SFX_42A4D0(MudSounds::eFollowMe_4, 0, 0, this);
            mCurrentMotion = eAbeMotions::Motion_22_CrouchSpeak_428A30;
        }
        else if (field_10C_prev_held & sInputKey_GameSpeak4_4C65C4)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eWait_12);
            Mudokon_SFX_42A4D0(MudSounds::eWait_6, 0, 0, this);
            mCurrentMotion = eAbeMotions::Motion_23_CrouchSpeak_428A90;
        }
        else if (field_10C_prev_held & sInputKey_GameSpeak1_4C65C8)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eHello_9);
            Mudokon_SFX_42A4D0(MudSounds::eHello_3, 0, 0, this);
            mCurrentMotion = eAbeMotions::Motion_22_CrouchSpeak_428A30;
        }
        else if (field_10C_prev_held & sInputKey_GameSpeak3_4C65C0)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eAnger_11);
            Mudokon_SFX_42A4D0(MudSounds::eAngry_5, 0, 0, this);
            mCurrentMotion = eAbeMotions::Motion_23_CrouchSpeak_428A90;
        }
    }
    else if (Input().IsAnyPressed(sInputKey_RightGameSpeakEnabler_4C65DC))
    {
        if (field_10C_prev_held & sInputKey_GameSpeak6_4C65E8)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eWhistleHigh_1);
            Mudokon_SFX_42A4D0(MudSounds::eWhistleHigh_1, 0, 0, this);
            mCurrentMotion = eAbeMotions::Motion_23_CrouchSpeak_428A90;
        }
        else if (field_10C_prev_held & sInputKey_GameSpeak5_4C65EC)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eWhistleLow_2);
            Mudokon_SFX_42A4D0(MudSounds::eWhistleLow_2, 0, 0, this);
            mCurrentMotion = eAbeMotions::Motion_22_CrouchSpeak_428A30;
        }
        else if (field_10C_prev_held & sInputKey_GameSpeak8_4C65E0)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eLaugh_4);
            Mudokon_SFX_42A4D0(MudSounds::eLaugh1_8, 0, 0, this);
            mCurrentMotion = eAbeMotions::Motion_23_CrouchSpeak_428A90;
        }
        else if (field_10C_prev_held & sInputKey_GameSpeak7_4C65E4)
        {
            pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eFart_3);
            Mudokon_SFX_42A4D0(MudSounds::eFart_7, 0, 0, this);
            if (sEnableFartGasCheat_507704)
            {
                FP xPos = {};
                if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    xPos = mBaseAnimatedWithPhysicsGameObject_XPos + FP_FromDouble(10) * field_BC_sprite_scale;
                }
                else
                {
                    xPos = mBaseAnimatedWithPhysicsGameObject_XPos - FP_FromDouble(10) * field_BC_sprite_scale;
                }
                New_Smoke_Particles_419A80(
                    xPos,
                    mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromDouble(6) * field_BC_sprite_scale,
                    field_BC_sprite_scale * FP_FromDouble(0.5),
                    3,
                    1);
            }
            field_130_say = 8;
            mCurrentMotion = eAbeMotions::Motion_22_CrouchSpeak_428A30;
            field_134_auto_say_timer = sGnFrame + 15;
        }
    }
}

void Abe::FallOnBombs_4231B0()
{
    PSX_RECT bOurRect = {};
    VGetBoundingRect(&bOurRect, 1);

    for (s32 i = 0; i < gBaseAliveGameObjects_4FC8A0->Size(); i++)
    {
        BaseAliveGameObject* pObjIter = gBaseAliveGameObjects_4FC8A0->ItemAt(i);
        if (!pObjIter)
        {
            break;
        }

        if (pObjIter->mBaseGameObjectTypeId == ReliveTypes::eMine || pObjIter->mBaseGameObjectTypeId == ReliveTypes::eUXB)
        {
            PSX_RECT objRect = {};
            pObjIter->VGetBoundingRect(&objRect, 1);

            if (bOurRect.x <= objRect.w
                && bOurRect.w >= objRect.x
                && bOurRect.h >= objRect.y
                && bOurRect.y <= objRect.h)
            {
                pObjIter->VTakeDamage(this);
            }
        }
    }
}

s16 Abe::ToLeftRightMovement_422AA0()
{
    field_B8_vely = FP_FromInteger(0);
    if (sControlledCharacter_50767C != this)
    {
        return 0;
    }

    const FP gridSize = ScaleToGridSize(field_BC_sprite_scale);
    const Bool32 flipX = field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX);

    if ((flipX && Input().IsAnyPressed(sInputKey_Right_4C6590)) || (!flipX && Input().IsAnyPressed(sInputKey_Left_4C6594)))
    {
        mCurrentMotion = eAbeMotions::Motion_2_StandingTurn_426040;
        return 1;
    }

    if (Input().IsAnyPressed(sInputKey_Right_4C6590) || Input().IsAnyPressed(sInputKey_Left_4C6594))
    {
        const FP directionX = FP_FromInteger(Input().IsAnyPressed(sInputKey_Right_4C6590) ? 1 : -1);

        if (Input().IsAnyPressed(sInputKey_Run_4C65A8))
        {
            field_B4_velx = directionX * (gridSize / FP_FromInteger(4));
            mCurrentMotion = eAbeMotions::Motion_41_StandingToRun_425530;
        }
        else if (Input().IsAnyPressed(sInputKey_Sneak_4C65AC))
        {
            field_B4_velx = directionX * (gridSize / FP_FromInteger(10));
            mCurrentMotion = eAbeMotions::Motion_47_SneakBegin_424ED0;
        }
        else
        {
            field_B4_velx = directionX * (gridSize / FP_FromInteger(9));
            mCurrentMotion = eAbeMotions::Motion_6_WalkBegin_424300;
        }

        if (!WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), directionX * gridSize))
        {
            if (!WallHit_401930(field_BC_sprite_scale * FP_FromInteger(20), directionX * gridSize))
            {
                return 1;
            }
        }

        if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(20), directionX * gridSize))
        {
            field_B4_velx = FP_FromInteger(0);
            mCurrentMotion = eAbeMotions::Motion_72_PushWall_4292A0;
            Environment_SFX_42A220(EnvironmentSfx::eGenericMovement_9, 0, 0x7FFF, this);
            return 0;
        }

        mCurrentMotion = eAbeMotions::Motion_21_StandToCrouch_427F40;
        return 1;
    }

    return 0;
}


void Abe::MoveWithVelocity_4257F0(FP speed)
{
    if (field_B4_velx > FP_FromInteger(0))
    {
        field_B4_velx = field_B4_velx - (field_BC_sprite_scale * speed);
        if (field_B4_velx < FP_FromInteger(0))
        {
            field_B4_velx = FP_FromInteger(0);
        }
    }
    else if (field_B4_velx < FP_FromInteger(0))
    {
        field_B4_velx = (field_BC_sprite_scale * speed) + field_B4_velx;
        if (field_B4_velx > FP_FromInteger(0))
        {
            field_B4_velx = FP_FromInteger(0);
        }
    }

    if (FP_GetExponent(field_B4_velx))
    {
        MoveForward_422FC0();
    }
}

void Abe::ToNewElumSyncMotion_422520(s16 elum_frame)
{
    const AnimRecord& rec = AO::AnimRec(sAbeFrameOffsetTable_4C61A0[mCurrentMotion]);
    field_10_anim.Set_Animation_Data(
        rec.mFrameTableOffset,
        StateToAnimResource_4204F0(mCurrentMotion));

    field_12C_timer = sGnFrame;
    field_10_anim.SetFrame(elum_frame + 1);
    field_10_anim.mAnimFlags.Set(AnimFlags::eBit5_FlipX, gElum_507680->field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX));
}

void Abe::SetActiveControlledCharacter_421480()
{
    field_2A8_flags.Set(Flags_2A8::e2A8_Bit7);
    sControlledCharacter_50767C = this;
}

PullRingRope* Abe::GetPullRope_422580()
{
    for (s32 i = 0; i < gBaseGameObjects->Size(); i++)
    {
        BaseGameObject* pObj = gBaseGameObjects->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if (pObj->mBaseGameObjectTypeId == ReliveTypes::ePullRingRope)
        {
            PullRingRope* pRope = static_cast<PullRingRope*>(pObj);

            PSX_RECT bRect = {};
            pRope->VGetBoundingRect(&bRect, 1);

            if ((mBaseAnimatedWithPhysicsGameObject_YPos - pRope->mBaseAnimatedWithPhysicsGameObject_YPos - (field_BC_sprite_scale * FP_FromInteger(80))) <= FP_FromInteger(0))
            {
                if (mBaseAnimatedWithPhysicsGameObject_XPos > FP_FromInteger(bRect.x) && mBaseAnimatedWithPhysicsGameObject_XPos < FP_FromInteger(bRect.w))
                {
                    return pRope;
                }
            }
        }
    }
    return nullptr;
}

void Abe::Free_Resources_422870()
{
    if (field_1A4_resources.res[0])
    {
        ResourceManager::FreeResource_455550(field_1A4_resources.res[0]);
        field_1A4_resources.res[0] = nullptr;
    }
}

void Abe::Load_Basic_Resources_4228A0()
{
    if (!ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbebasicAOResID, 0, 0) && !ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbebasicAOResID, 1, 0))
    {
        ResourceManager::LoadResourceFile_455270("ABEBSIC.BAN", nullptr);
        ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbebasicAOResID, 1, 0);
    }
}

void Abe::LoadMountElumResources_42E690()
{
    ResourceManager::FreeResource_455550(field_1A4_resources.res[0]);
    field_1A4_resources.res[0] = nullptr;

    field_1A4_resources.res[10] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbefallAOResID, 0, 0);
    ResourceManager::FreeResource_455550(field_1A4_resources.res[10]);
    field_1A4_resources.res[10] = nullptr;

    field_1A4_resources.res[38] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeommAOResID, 0, 0);
    ResourceManager::FreeResource_455550(field_1A4_resources.res[38]);
    field_1A4_resources.res[38] = nullptr;

    field_1A4_resources.res[9] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbesmashAOResID, 0, 0);
    ResourceManager::FreeResource_455550(field_1A4_resources.res[9]);
    field_1A4_resources.res[9] = nullptr;

    if (!ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAneprmntAOResID, 0, 0))
    {
        ResourceManager::LoadResourceFile_455270("ANEPRMNT.BAN", nullptr);
        field_1A4_resources.res[61] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAneprmntAOResID, 1, 0);
    }

    field_104_pending_resource_count++;
    ResourceManager::LoadResourceFile("ANEMOUNT.BND", BaseAliveGameObject::OnResourceLoaded_4019A0, this);
}

void Abe::ElumKnockForward_42E780(s32 /*not_used*/)
{
    ToKnockback_422D90(1, 1);
    mCurrentMotion = eAbeMotions::Motion_128_KnockForward_429330;
    mNextMotion = eAbeMotions::Motion_0_Idle_423520;
    field_108_bMotionChanged = 1;
    const AnimRecord& rec = AO::AnimRec(sAbeFrameOffsetTable_4C61A0[mCurrentMotion]);
    field_10_anim.Set_Animation_Data(
        rec.mFrameTableOffset,
        StateToAnimResource_4204F0(eAbeMotions::Motion_128_KnockForward_429330));

    sControlledCharacter_50767C = sActiveHero_507678;
    gElum_507680->field_154_bAbeForcedDownFromElum = 1;
}

s16 Abe::TryMountElum_42E600()
{
    if (gElum_507680)
    {
        if (FP_Abs(mBaseAnimatedWithPhysicsGameObject_XPos - gElum_507680->mBaseAnimatedWithPhysicsGameObject_XPos) <= FP_FromInteger(2) && FP_Abs(mBaseAnimatedWithPhysicsGameObject_YPos - gElum_507680->mBaseAnimatedWithPhysicsGameObject_YPos) <= FP_FromInteger(2))
        {
            if (gElum_507680->field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX) != field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
            {
                mNextMotion = eAbeMotions::Motion_139_ElumMountBegin_42E090;
                return eAbeMotions::Motion_2_StandingTurn_426040;
            }

            if (gElum_507680->mCurrentMotion != eElumMotions::Motion_1_Idle_412990
                || gElum_507680->field_128_brain_idx == 1
                || gElum_507680->field_170_flags.Get(Elum::Flags_170::eStrugglingWithBees_Bit1))
            {
                return eAbeMotions::Motion_0_Idle_423520;
            }

            LoadMountElumResources_42E690();
            return eAbeMotions::Motion_139_ElumMountBegin_42E090;
        }
    }
    return eAbeMotions::Motion_0_Idle_423520;
}

void Abe::BulletDamage_4220B0(Bullet* pBullet)
{
    PSX_RECT rect = {};
    VGetBoundingRect(&rect, 1);

    enum class ShootKind
    {
        eEverythingElse_0 = 0,
        eHanging_1 = 1,
        eRolling_2 = 2,
    };

    if (mCurrentMotion == eAbeMotions::Motion_137_ElumUnmountBegin_42E2B0
        || mCurrentMotion == eAbeMotions::Motion_136_ElumMountEnd_42E110
        || mCurrentMotion == eAbeMotions::Motion_138_ElumUnmountEnd_42E390
        || mCurrentMotion == eAbeMotions::Motion_139_ElumMountBegin_42E090
        || !gMap.Is_Point_In_Current_Camera_4449C0(
            field_B2_lvl_number,
            field_B0_path_number,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos,
            1)
        || mHealth <= FP_FromInteger(0))
    {
        return;
    }

    ShootKind shootKind = ShootKind::eEverythingElse_0;
    if (mCurrentMotion == eAbeMotions::Motion_24_RollBegin_427A20
        || mCurrentMotion == eAbeMotions::Motion_25_RollLoop_427BB0
        || mCurrentMotion == eAbeMotions::Motion_26_RollEnd_427EA0
        || mCurrentMotion == eAbeMotions::Motion_39_CrouchTurn_4288C0
        || mCurrentMotion == eAbeMotions::Motion_19_CrouchIdle_4284C0)
    {
        shootKind = ShootKind::eRolling_2;
    }
    else if (mCurrentMotion == eAbeMotions::Motion_64_LedgeAscend_428B60
             || mCurrentMotion == eAbeMotions::Motion_66_LedgeHang_428D90
             || mCurrentMotion == eAbeMotions::Motion_68_LedgeHangWobble_428E50
             || mCurrentMotion == eAbeMotions::Motion_65_LedgeDescend_428C00
             || mCurrentMotion == eAbeMotions::Motion_67_ToOffScreenHoist_428C50)
    {
        shootKind = ShootKind::eHanging_1;
    }

    mHealth = FP_FromInteger(0);
    field_106_shot = 1;

    switch (pBullet->field_10_type)
    {
        case BulletType::ePossessedSlig_0:
        case BulletType::eNormalBullet_1:
        {
            FP bloodXOff = {};
            if (pBullet->field_20_x_distance > FP_FromInteger(0))
            {
                bloodXOff = FP_FromInteger(-24);
            }
            else
            {
                bloodXOff = FP_FromInteger(24);
            }

            ao_new<Blood>(
                mBaseAnimatedWithPhysicsGameObject_XPos,
                pBullet->field_1C_ypos,
                bloodXOff,
                FP_FromInteger(0),
                field_BC_sprite_scale,
                50);

            switch (shootKind)
            {
                case ShootKind::eEverythingElse_0:
                {
                    if (field_1A4_resources.res[0])
                    {
                        ToKnockback_422D90(1, 1);
                    }
                    else
                    {
                        ElumKnockForward_42E780(1);
                    }
                    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX) != (pBullet->field_20_x_distance > FP_FromInteger(0)))
                    {
                        mCurrentMotion = eAbeMotions::Motion_128_KnockForward_429330;
                    }
                    field_108_bMotionChanged = 1;
                    field_106_shot = 0;

                    if (pBullet->field_20_x_distance >= FP_FromInteger(0))
                    {
                        field_B4_velx = field_BC_sprite_scale * FP_FromDouble(7.8);
                    }
                    else
                    {
                        field_B4_velx = -field_BC_sprite_scale * FP_FromDouble(7.8);
                    }
                    break;
                }
                case ShootKind::eHanging_1:
                {
                    mCurrentMotion = eAbeMotions::Motion_92_ForceDownFromHoist_4297C0;
                    field_108_bMotionChanged = 1;
                    field_106_shot = 0;
                    field_114_gnFrame = 0;
                    break;
                }
                case ShootKind::eRolling_2:
                {
                    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX) == (pBullet->field_20_x_distance > FP_FromInteger(0)))
                    {
                        mNextMotion = eAbeMotions::Motion_73_RollingKnockback_4291D0;
                    }
                    else
                    {
                        mNextMotion = eAbeMotions::Motion_129_RollingKnockForward_4294F0;
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case BulletType::eZBullet_2:
        {
            if (field_BC_sprite_scale == FP_FromDouble(0.5))
            {
                field_106_shot = 0;
                mHealth = FP_FromInteger(1);
                return;
            }
            if (Bullet::InZBulletCover(FP_FromInteger(rect.x), FP_FromInteger(rect.y), rect))
            {
                field_106_shot = 0;
                mHealth = FP_FromInteger(1);
                return;
            }
            if (shootKind != ShootKind::eEverythingElse_0)
            {
                if (shootKind == ShootKind::eHanging_1)
                {
                    mCurrentMotion = eAbeMotions::Motion_92_ForceDownFromHoist_4297C0;
                    field_108_bMotionChanged = 1;
                    field_106_shot = 0;
                    field_114_gnFrame = 0;
                }
                else if (shootKind == ShootKind::eRolling_2)
                {
                    mNextMotion = eAbeMotions::Motion_147_ShotRolling_4295C0;
                }
            }
            if (mCurrentMotion != eAbeMotions::Motion_114_ElumRunLoop_42DFA0)
            {
                if (field_1A4_resources.res[0])
                {
                    mNextMotion = eAbeMotions::Motion_148_Shot_4296A0;
                }
                else
                {
                    ElumKnockForward_42E780(1);
                    mCurrentMotion = eAbeMotions::Motion_148_Shot_4296A0;
                    field_108_bMotionChanged = 1;
                    field_106_shot = 0;
                }
            }

            if (mCurrentMotion != eAbeMotions::Motion_114_ElumRunLoop_42DFA0 || shootKind != ShootKind::eEverythingElse_0)
            {
                ao_new<Blood>(
                    mBaseAnimatedWithPhysicsGameObject_XPos,
                    mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromInteger(45),
                    FP_FromInteger(0),
                    FP_FromInteger(0),
                    FP_FromInteger(1),
                    50);

                break;
            }
        }
        default:
            break;
    }

    if (field_106_shot)
    {
        field_112_prev_motion = mNextMotion;
    }

    Environment_SFX_42A220(EnvironmentSfx::eElumHitWall_14, 0, 0x7FFF, this);
    Mudokon_SFX_42A4D0(MudSounds::eKnockbackOuch_10, 127, 0, this);
    Environment_SFX_42A220(EnvironmentSfx::eDeathNoise_7, 0, 0x7FFF, this);
    SFX_Play_Pitch(SoundEffect::Eating1_79, 0, -500, this);
    SFX_Play_Mono(SoundEffect::KillEffect_78, 0, this);
}

Bool32 Abe::NearDoorIsOpen()
{
    for (s32 i = 0; i < gBaseGameObjects->Size(); i++)
    {
        BaseGameObject* pObj = gBaseGameObjects->ItemAt(i);
        if (!pObj)
        {
            break;
        }

        if (pObj->mBaseGameObjectTypeId == ReliveTypes::eDoor)
        {
            auto pDoor = static_cast<Door*>(pObj);
            PSX_RECT Rect = {};
            VGetBoundingRect(&Rect, 1);
            PSX_RECT Rect2 = {};
            pDoor->VGetBoundingRect(&Rect2, 1);

            if (Rect.x <= Rect2.w && Rect.w >= Rect2.x && Rect.h >= Rect2.y && Rect.y <= Rect2.h)
            {
                return pDoor->vIsOpen_40E800();
            }
        }
    }

    // We didn't find a door - so for some reason that makes no sense return that it is open...
    return TRUE;
}

s16 Abe::RunTryEnterDoor_4259C0()
{
    if (!Input().IsAnyPressed(sInputKey_Up_4C6598))
    {
        return 0;
    }
    if (mBaseAliveGameObjectFlags.Get(Flags_10A::e10A_Bit5_Electrocuted))
    {
        return 0;
    }
    if (field_10_anim.field_92_current_frame < 4)
    {
        return 0;
    }

    // Are we actually on a door?
    Path_TLV* pDoorTlv = gMap.TLV_Get_At_446260(
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
        TlvTypes::Door_6);

    if (!pDoorTlv)
    {
        return 0;
    }

    if (!NearDoorIsOpen())
    {
        return 0;
    }

    BaseAliveGameObjectPathTLV = pDoorTlv;
    field_110_state.raw = 0;
    mCurrentMotion = eAbeMotions::Motion_156_DoorEnter_42D370;
    mBaseAnimatedWithPhysicsGameObject_XPos = FP_FromInteger((pDoorTlv->field_14_bottom_right.field_0_x + pDoorTlv->field_10_top_left.field_0_x) / 2);
    MapFollowMe_401D30(TRUE);
    return 1;
}

s16 Abe::MoveLiftUpOrDown_42F190(FP yVelocity)
{
    auto pLiftPoint = static_cast<LiftPoint*>(mLiftPoint);

    pLiftPoint->Move(FP_FromInteger(0), yVelocity, 0);
    FollowLift_42EE90();

    if (gBeeInstanceCount_5076B0 && gBeesNearAbe_5076AC)
    {
        return eAbeMotions::Motion_141_BeesStrugglingOnLift_42F390;
    }
    if (sControlledCharacter_50767C == this && !field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame) && field_10_anim.field_92_current_frame != 5)
    {
        return mCurrentMotion;
    }
    if (yVelocity >= FP_FromInteger(0))
    {
        if (yVelocity > FP_FromInteger(0))
        {
            if (pLiftPoint->OnBottomFloor())
            {
                return eAbeMotions::Motion_135_LiftGrabIdle_42F000;
            }
            if (Input().IsAnyPressed(sInputKey_Down_4C659C))
            {
                return eAbeMotions::Motion_132_LiftUseDown_42F170;
            }
            if (Input().IsAnyPressed(sInputKey_Up_4C6598))
            {
                return eAbeMotions::Motion_131_LiftUseUp_42F150;
            }
        }
    }
    else
    {
        if (pLiftPoint->OnTopFloor())
        {
            return eAbeMotions::Motion_135_LiftGrabIdle_42F000;
        }
        if (Input().IsAnyPressed(sInputKey_Up_4C6598))
        {
            return eAbeMotions::Motion_131_LiftUseUp_42F150;
        }
        if (Input().IsAnyPressed(sInputKey_Down_4C659C))
        {
            return eAbeMotions::Motion_132_LiftUseDown_42F170;
        }
    }

    if (Input().Pressed() && pLiftPoint->OnAnyFloor() && !(pLiftPoint->field_12C_bMoving & 1))
    {
        return eAbeMotions::Motion_134_LiftGrabEnd_42EFE0;
    }

    pLiftPoint->Move(FP_FromInteger(0), FP_FromInteger(0), 0);
    return eAbeMotions::Motion_135_LiftGrabIdle_42F000;
}

void Abe::VScreenChanged()
{
    if (sControlledCharacter_50767C == this || sControlledCharacter_50767C == gElum_507680)
    {
        field_B2_lvl_number = gMap.mLevel;
        field_B0_path_number = gMap.mPath;
    }

    // Level has changed?
    if (gMap.mCurrentLevel != gMap.mLevel)
    {
        // Set the correct tint for this map
        SetTint_418750(sAbeTints_4C6438, gMap.mLevel);

        if (gMap.mCurrentLevel != EReliveLevelIds::eMenu)
        {
            if (field_19C_throwable_count > 0)
            {
                if (gpThrowableArray_50E26C)
                {
                    gpThrowableArray_50E26C->Remove(field_19C_throwable_count);
                }
            }

            field_19C_throwable_count = 0;

            ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource_4554F0(ResourceManager::ResourceType::Resource_Palt, AOResourceID::kAberockAOResID, 0, 0));

            if (field_168_ring_pulse_timer > 0 && field_16C_bHaveShrykull)
            {
                Free_Shrykull_Resources_42F4C0();
            }

            field_168_ring_pulse_timer = 0;
        }

        if (gMap.mLevel == EReliveLevelIds::eCredits || gMap.mLevel == EReliveLevelIds::eMenu)
        {
            // Remove Abe for menu/credits levels?
            mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        }
    }
}



void Abe::VOn_TLV_Collision(Path_TLV* pTlv)
{
    while (pTlv)
    {
        if (pTlv->field_4_type == TlvTypes::ContinuePoint_0)
        {
            Path_ContinuePoint* pContinuePointTlv = static_cast<Path_ContinuePoint*>(pTlv);

            if ((pContinuePointTlv->field_18_zone_number != field_146_zone_number || field_144_saved_level != gMap.mCurrentLevel) && !mBaseAliveGameObjectFlags.Get(Flags_10A::e10A_Bit5_Electrocuted) && mCurrentMotion != eAbeMotions::Motion_156_DoorEnter_42D370)
            {
                field_146_zone_number = pContinuePointTlv->field_18_zone_number;
                field_148_clear_from_id = pContinuePointTlv->field_1A_clear_from_id;
                field_14A_clear_to_id = pContinuePointTlv->field_1C_clear_to_id;

                field_138_zone_top_left = pContinuePointTlv->field_10_top_left;
                field_13C_zone_bottom_right = pContinuePointTlv->field_14_bottom_right;

                field_14C_saved_sprite_scale = field_BC_sprite_scale;

                field_2A8_flags.Set(Flags_2A8::e2A8_eBit16_AbeSpawnDir, pContinuePointTlv->field_20_abe_direction == Path_ContinuePoint::spawnDirection::eLeft_1);

                const auto bHaveShry = field_168_ring_pulse_timer - sGnFrame;
                field_150_saved_ring_timer = bHaveShry < 0 ? 0 : bHaveShry;
                field_154_bSavedHaveShrykull = field_16C_bHaveShrykull;

                field_144_saved_level = gMap.mCurrentLevel;
                field_142_saved_path = gMap.mCurrentPath;
                field_140_saved_camera = gMap.mCurrentCamera;

                if (gRestartRuptureFarmsSavedMuds_5076C8 == 0 && gMap.mCurrentLevel == EReliveLevelIds::eRuptureFarmsReturn && gMap.mCurrentPath == 19 && gMap.mCurrentCamera == 3)
                {
                    gRestartRuptureFarmsKilledMuds_5076C4 = sKilledMudokons_5076BC;
                    gRestartRuptureFarmsSavedMuds_5076C8 = sRescuedMudokons_5076C0;
                }
                gOldKilledMuds_5076D0 = sKilledMudokons_5076BC;
                gOldSavedMuds_5076D4 = sRescuedMudokons_5076C0;

                SaveGame::SaveToMemory(&gSaveBuffer_505668);

                const FP camXPos = FP_NoFractional(pScreenManager_4FF7C8->field_10_pCamPos->field_0_x - FP_FromInteger(pScreenManager_4FF7C8->field_14_xpos));

                FP indicator_xpos = {};
                if (mBaseAnimatedWithPhysicsGameObject_XPos - camXPos >= FP_FromInteger(384 / 2)) // mid screen x
                {
                    indicator_xpos = mBaseAnimatedWithPhysicsGameObject_XPos - ScaleToGridSize(field_BC_sprite_scale);
                }
                else
                {
                    indicator_xpos = ScaleToGridSize(field_BC_sprite_scale) + mBaseAnimatedWithPhysicsGameObject_XPos;
                }
                const FP indicator_ypos = mBaseAnimatedWithPhysicsGameObject_YPos + (field_BC_sprite_scale * FP_FromInteger(-50));

                ao_new<ThrowableTotalIndicator>(indicator_xpos, indicator_ypos, field_10_anim.mRenderLayer,
                                                                            field_10_anim.field_14_scale, 11, 1);
            }
        }
        else if (pTlv->field_4_type == TlvTypes::DeathDrop_5)
        {
            Mudokon_SFX_42A4D0(MudSounds::eDeathDropScream_17, 0, 0, this);

            Event_Broadcast(kEventNoise, this);
            Event_Broadcast(kEventSuspiciousNoise, this);
            Event_Broadcast(kEventLoudNoise, this);
            Event_Broadcast(kEventSpeaking, this);

            if (!field_1A4_resources.res[0] && sControlledCharacter_50767C != this)
            {
                sControlledCharacter_50767C = sActiveHero_507678;
                FreeElumRes_420F80();
            }
            ToDeathDropFall_42C3D0();
        }

        // To next TLV
        pTlv = gMap.TLV_Get_At_446060(pTlv, mBaseAnimatedWithPhysicsGameObject_XPos, mBaseAnimatedWithPhysicsGameObject_YPos, mBaseAnimatedWithPhysicsGameObject_XPos, mBaseAnimatedWithPhysicsGameObject_YPos);
    }
}

s16 Abe::HandleDoAction_429A70()
{
    s16 mountMotion = TryMountElum_42E600();
    if (mountMotion != eAbeMotions::Motion_0_Idle_423520)
    {
        return mountMotion;
    }

    Path_TLV* pTlv = gMap.TLV_Get_At_446060(
        nullptr,
        mBaseAnimatedWithPhysicsGameObject_XPos,
        mBaseAnimatedWithPhysicsGameObject_YPos,
        mBaseAnimatedWithPhysicsGameObject_XPos,
        mBaseAnimatedWithPhysicsGameObject_YPos);

    while (pTlv)
    {
        switch (pTlv->field_4_type.mType)
        {
            case TlvTypes::WellLocal_11:
                BaseAliveGameObjectPathTLV = pTlv;
                return eAbeMotions::Motion_77_WellBegin_430F10;

            case TlvTypes::Lever_26:
                if (FP_FromInteger(FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos) - pTlv->field_10_top_left.field_0_x) < ScaleToGridSize(field_BC_sprite_scale))
                {
                    // Wrong dir
                    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        return eAbeMotions::Motion_36_DunnoBegin_423260;
                    }

                    // Get switch
                    auto pSwitch = static_cast<Lever*>(FindObjectOfType_418280(
                        ReliveTypes::eLever,
                        mBaseAnimatedWithPhysicsGameObject_XPos + ScaleToGridSize(field_BC_sprite_scale),
                        mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromInteger(5)));

                    // Pull it
                    if (pSwitch)
                    {
                        pSwitch->VPull(mBaseAnimatedWithPhysicsGameObject_XPos < pSwitch->mBaseAnimatedWithPhysicsGameObject_XPos);
                        return eAbeMotions::Motion_101_LeverUse_429970;
                    }
                }
                else if (FP_FromInteger(pTlv->field_14_bottom_right.field_0_x - FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos)) < ScaleToGridSize(field_BC_sprite_scale))
                {
                    // Wrong dir
                    if (!field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        return eAbeMotions::Motion_36_DunnoBegin_423260;
                    }

                    // Get switch
                    auto pSwitch = static_cast<Lever*>(FindObjectOfType_418280(
                        ReliveTypes::eLever,
                        mBaseAnimatedWithPhysicsGameObject_XPos - ScaleToGridSize(field_BC_sprite_scale),
                        mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromInteger(5)));

                    // Pull it
                    if (pSwitch)
                    {
                        pSwitch->VPull(mBaseAnimatedWithPhysicsGameObject_XPos < pSwitch->mBaseAnimatedWithPhysicsGameObject_XPos);
                        return eAbeMotions::Motion_101_LeverUse_429970;
                    }
                }
                break;

            case TlvTypes::WellExpress_45:
                BaseAliveGameObjectPathTLV = pTlv;
                return eAbeMotions::Motion_80_430EF0;

            case TlvTypes::BoomMachine_97:
            {
                auto pBoomMachine = static_cast<BoomMachine*>(FindObjectOfType_418280(
                    ReliveTypes::eGrenadeMachine,
                    mBaseAnimatedWithPhysicsGameObject_XPos,
                    mBaseAnimatedWithPhysicsGameObject_YPos - (field_BC_sprite_scale * FP_FromInteger(25))));

                if (pBoomMachine && pBoomMachine->VIsButtonOn())
                {
                    pBoomMachine->VHandleButton();
                    return eAbeMotions::Motion_90_GrenadeMachineUse_430EA0;
                }
                return eAbeMotions::Motion_36_DunnoBegin_423260;
            }

            default:
                break;
        }

        pTlv = gMap.TLV_Get_At_446060(
            pTlv,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos);
    }
    return eAbeMotions::Motion_36_DunnoBegin_423260;
}

s16 Abe::VTakeDamage(BaseGameObject* pFrom)
{
    SND_Seq_Stop_477A60(SeqId::eMudokonChant1_11);

    const auto old_say = field_130_say;
    field_130_say = -1;

    if (field_188_pOrbWhirlWind)
    {
        field_188_pOrbWhirlWind->ToStop();
        field_188_pOrbWhirlWind = nullptr;
    }

    if (field_18C_pObjToPossess)
    {
        field_18C_pObjToPossess->mBaseGameObjectRefCount--;
        field_18C_pObjToPossess = nullptr;
    }

    switch (mCurrentMotion)
    {
        case eAbeMotions::Motion_74_JumpIntoWell_430EC0:
        case eAbeMotions::Motion_75_ToInsideOfAWellLocal_431090:
        case eAbeMotions::Motion_76_ToWellShotOut_431720:
        case eAbeMotions::Motion_77_WellBegin_430F10:
        case eAbeMotions::Motion_78_InsideWellLocal_4310A0:
        case eAbeMotions::Motion_79_WellShotOut_431730:
        case eAbeMotions::Motion_80_430EF0:
        case eAbeMotions::Motion_81_InsideWellExpress_431320:
        case eAbeMotions::Motion_82_WellExpressShotOut_4315A0:
        case eAbeMotions::Motion_83_430F00:
        case eAbeMotions::Motion_84_ToInsideWellLocal_431080:
        case eAbeMotions::Motion_85_ToWellShotOut_431710:
        case eAbeMotions::Motion_156_DoorEnter_42D370:
        case eAbeMotions::Motion_157_DoorExit_42D780:
        case eAbeMotions::Motion_162_ToShrykull_42F410:
        case eAbeMotions::Motion_163_ShrykullEnd_42F520:
            return 0;
    }

    if (gAbeInvulnerableCheat_5076E4 || field_2A8_flags.Get(Flags_2A8::e2A8_Bit6_bShrivel) || !field_10_anim.mAnimFlags.Get(AnimFlags::eBit3_Render))
    {
        return 0;
    }

    field_11C_regen_health_timer = sGnFrame + 900;

    auto oldHp = mHealth;

    switch (pFrom->mBaseGameObjectTypeId)
    {
        case ReliveTypes::eBat:
            if (mHealth > FP_FromInteger(0))
            {
                mHealth -= FP_FromInteger(1);
                if (mHealth > FP_FromInteger(0))
                {
                    Mudokon_SFX_42A4D0(MudSounds::eKnockbackOuch_10, 0, 0, this);
                }
                else
                {
                    Mudokon_SFX_42A4D0(MudSounds::eKnockbackOuch_10, 0, 0, this);
                    Environment_SFX_42A220(EnvironmentSfx::eDeathNoise_7, 0, 0x7FFF, this);
                    mHealth = FP_FromInteger(0);
                    field_106_shot = 1;
                    field_112_prev_motion = eAbeMotions::Motion_128_KnockForward_429330;
                    mNextMotion = eAbeMotions::Motion_128_KnockForward_429330;
                    if (mCurrentMotion != eAbeMotions::Motion_64_LedgeAscend_428B60
                        && mCurrentMotion != eAbeMotions::Motion_66_LedgeHang_428D90
                        && mCurrentMotion != eAbeMotions::Motion_68_LedgeHangWobble_428E50
                        && mCurrentMotion != eAbeMotions::Motion_65_LedgeDescend_428C00
                        && mCurrentMotion != eAbeMotions::Motion_67_ToOffScreenHoist_428C50)
                    {
                        break;
                    }
                    else
                    {
                        mCurrentMotion = eAbeMotions::Motion_92_ForceDownFromHoist_4297C0;
                        field_108_bMotionChanged = 1;
                        field_106_shot = 0;
                        field_114_gnFrame = 0;
                        return 1;
                    }
                }
            }
            break;

        case ReliveTypes::eGasClock:
            if (mHealth > FP_FromInteger(0))
            {
                if (mCurrentMotion == eAbeMotions::Motion_64_LedgeAscend_428B60
                    || mCurrentMotion == eAbeMotions::Motion_66_LedgeHang_428D90
                    || mCurrentMotion == eAbeMotions::Motion_68_LedgeHangWobble_428E50
                    || mCurrentMotion == eAbeMotions::Motion_65_LedgeDescend_428C00
                    || mCurrentMotion == eAbeMotions::Motion_67_ToOffScreenHoist_428C50)
                {
                    mCurrentMotion = eAbeMotions::Motion_92_ForceDownFromHoist_4297C0;
                    field_106_shot = 0;
                    field_114_gnFrame = 0;
                    field_108_bMotionChanged = 1;
                    return 1;
                }

                if (IsStanding_41FC10())
                {
                    mHealth = FP_FromInteger(0);
                    mCurrentMotion = eAbeMotions::Motion_164_PoisonGasDeath_42A120;
                    field_108_bMotionChanged = 1;
                    field_114_gnFrame = 1;
                }
                else
                {
                    if (mCurrentMotion != eAbeMotions::Motion_70_Knockback_428FB0 && mCurrentMotion != eAbeMotions::Motion_71_KnockbackGetUp_429240)
                    {
                        ToKnockback_422D90(1, 1);
                        field_108_bMotionChanged = 1;
                    }
                }
            }
            break;

        case ReliveTypes::eElectricWall:
            Mudokon_SFX_42A4D0(MudSounds::eOops_16, 0, 0, this);
            break;

        case ReliveTypes::eBaseBomb:
        case ReliveTypes::eExplosion:
            if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit3_Render))
            {
                if (mHealth > FP_FromInteger(0))
                {
                    field_106_shot = 1;
                    field_112_prev_motion = eAbeMotions::Motion_70_Knockback_428FB0;
                    mNextMotion = eAbeMotions::Motion_70_Knockback_428FB0;
                }

                mHealth = FP_FromInteger(0);
                field_C4_b = 30;
                field_C2_g = 30;
                field_C0_r = 30;

                ao_new<Gibs>(
                    GibType::Abe_0,
                    mBaseAnimatedWithPhysicsGameObject_XPos,
                    mBaseAnimatedWithPhysicsGameObject_YPos,
                    FP_FromInteger(0),
                    FP_FromInteger(0),
                    field_BC_sprite_scale);

                field_10_anim.mAnimFlags.Clear(AnimFlags::eBit3_Render);
                field_D0_pShadow->field_14_flags.Clear(Shadow::eBit2_Enabled);
            }
            break;

        case ReliveTypes::eSecurityClaw:
        case ReliveTypes::SecurityOrb:
            field_130_say = 5;
            field_134_auto_say_timer = sGnFrame + 27;
            // The zap makes Abe drop his stuff everywhere
            for (s32 i = 0; i < field_19C_throwable_count; i++)
            {
                field_198_pThrowable = Make_Throwable(mBaseAnimatedWithPhysicsGameObject_XPos, mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromInteger(30), 0);

                const FP rand1 = FP_FromRaw((Math_NextRandom() - 127) << 11); // TODO: Wat?
                const FP rand2 = (FP_FromDouble(0.03125) * FP_FromRaw(Math_NextRandom())) - FP_FromInteger(2);
                field_198_pThrowable->VThrow(rand1, rand2);
                field_198_pThrowable->field_BC_sprite_scale = field_BC_sprite_scale;
                field_198_pThrowable->VTimeToExplodeRandom();
                field_198_pThrowable = nullptr;
            }
            field_19C_throwable_count = 0;
            break;

        case ReliveTypes::eRockSpawner:
            if (mHealth > FP_FromInteger(0))
            {
                field_108_bMotionChanged = 1;
                mHealth = FP_FromInteger(0);

                if (mCurrentMotion == eAbeMotions::Motion_64_LedgeAscend_428B60
                    || mCurrentMotion == eAbeMotions::Motion_66_LedgeHang_428D90
                    || mCurrentMotion == eAbeMotions::Motion_68_LedgeHangWobble_428E50
                    || mCurrentMotion == eAbeMotions::Motion_65_LedgeDescend_428C00
                    || mCurrentMotion == eAbeMotions::Motion_67_ToOffScreenHoist_428C50)
                {
                    mCurrentMotion = eAbeMotions::Motion_92_ForceDownFromHoist_4297C0;
                    field_108_bMotionChanged = 1;
                    field_106_shot = 0;
                    field_114_gnFrame = 0;
                    return 1;
                }
                ToKnockback_422D90(1, 1);
                SFX_Play_Mono(SoundEffect::KillEffect_78, 127);
            }
            break;

        case ReliveTypes::eMeatSaw:
            if (mHealth > FP_FromInteger(0))
            {
                field_108_bMotionChanged = 1;
                mHealth = FP_FromInteger(0);
                ToKnockback_422D90(1, 1);
                field_C4_b = 30;
                field_C2_g = 30;
                field_C0_r = 30;

                ao_new<Gibs>(
                    GibType::Abe_0,
                    mBaseAnimatedWithPhysicsGameObject_XPos,
                    mBaseAnimatedWithPhysicsGameObject_YPos,
                    FP_FromInteger(0),
                    FP_FromInteger(0),
                    field_BC_sprite_scale);

                ao_new<Gibs>(
                    GibType::Abe_0,
                    mBaseAnimatedWithPhysicsGameObject_XPos,
                    mBaseAnimatedWithPhysicsGameObject_YPos,
                    FP_FromInteger(0),
                    FP_FromInteger(0),
                    field_BC_sprite_scale);

                field_10_anim.mAnimFlags.Clear(AnimFlags::eBit3_Render);
            }
            break;

        case ReliveTypes::eParamite:
        case ReliveTypes::eScrab:
        case ReliveTypes::eSlog:
            if (mHealth > FP_FromInteger(0))
            {
                auto pAliveObj = static_cast<BaseAliveGameObject*>(pFrom);
                mHealth = FP_FromInteger(0);
                PSX_RECT abeRect = {};
                VGetBoundingRect(&abeRect, 1);
                if (pAliveObj->field_B4_velx <= FP_FromInteger(0))
                {
                    ao_new<Blood>(
                        mBaseAnimatedWithPhysicsGameObject_XPos,
                        FP_FromInteger(abeRect.h + abeRect.y) / FP_FromInteger(2),
                        FP_FromInteger(-24),
                        FP_FromInteger(0),
                        field_BC_sprite_scale,
                        50);
                }
                else
                {
                    ao_new<Blood>(
                        mBaseAnimatedWithPhysicsGameObject_XPos,
                        FP_FromInteger(abeRect.h + abeRect.y) / FP_FromInteger(2),
                        FP_FromInteger(24),
                        FP_FromInteger(0),
                        field_BC_sprite_scale,
                        50);
                }

                if (mCurrentMotion == eAbeMotions::Motion_64_LedgeAscend_428B60
                    || mCurrentMotion == eAbeMotions::Motion_66_LedgeHang_428D90
                    || mCurrentMotion == eAbeMotions::Motion_68_LedgeHangWobble_428E50
                    || mCurrentMotion == eAbeMotions::Motion_65_LedgeDescend_428C00
                    || mCurrentMotion == eAbeMotions::Motion_67_ToOffScreenHoist_428C50)
                {
                    mCurrentMotion = eAbeMotions::Motion_92_ForceDownFromHoist_4297C0;
                    field_108_bMotionChanged = 1;
                    field_106_shot = 0;
                    field_114_gnFrame = 0;
                    return 1;
                }

                if (mCurrentMotion >= eAbeMotions::Motion_102_ElumWalkLoop_42DCA0
                    && mCurrentMotion <= eAbeMotions::Motion_125_ElumMidWalkEnd_42DCC0)
                {
                    mNextMotion = eAbeMotions::Motion_148_Shot_4296A0;
                    field_112_prev_motion = eAbeMotions::Motion_148_Shot_4296A0;
                    field_106_shot = 1;
                    return 1;
                }

                ToKnockback_422D90(1, 1);
                field_108_bMotionChanged = 1;

                if (pAliveObj->mBaseAnimatedWithPhysicsGameObject_XPos < mBaseAnimatedWithPhysicsGameObject_XPos)
                {
                    if (!(field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX)))
                    {
                        mCurrentMotion = eAbeMotions::Motion_128_KnockForward_429330;
                    }
                }
                else if (pAliveObj->mBaseAnimatedWithPhysicsGameObject_XPos > mBaseAnimatedWithPhysicsGameObject_XPos)
                {
                    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        mCurrentMotion = eAbeMotions::Motion_128_KnockForward_429330;
                    }
                }

                if (pAliveObj->field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    field_B4_velx = (field_BC_sprite_scale * FP_FromDouble(-7.8));
                }
                else
                {
                    field_B4_velx = (field_BC_sprite_scale * FP_FromDouble(7.8));
                }

                SFX_Play_Mono(SoundEffect::KillEffect_78, 127, 0);
                if (pAliveObj->mBaseGameObjectTypeId != ReliveTypes::eParamite)
                {
                    SFX_Play_Mono(SoundEffect::FallingItemHit_53, 90);
                }
            }
            break;

        case ReliveTypes::eAbilityRing:
            return 0;

        case ReliveTypes::eRollingBall:
            if (mHealth > FP_FromInteger(0))
            {
                field_108_bMotionChanged = 1;
                mHealth = FP_FromInteger(0);
                if (mCurrentMotion == eAbeMotions::Motion_64_LedgeAscend_428B60
                    || mCurrentMotion == eAbeMotions::Motion_66_LedgeHang_428D90
                    || mCurrentMotion == eAbeMotions::Motion_68_LedgeHangWobble_428E50
                    || mCurrentMotion == eAbeMotions::Motion_65_LedgeDescend_428C00
                    || mCurrentMotion == eAbeMotions::Motion_67_ToOffScreenHoist_428C50)
                {
                    mCurrentMotion = eAbeMotions::Motion_92_ForceDownFromHoist_4297C0;
                    field_108_bMotionChanged = 1;
                    field_106_shot = 0;
                    field_114_gnFrame = 0;
                    return 1;
                }

                auto pAliveObj = static_cast<BaseAliveGameObject*>(pFrom);

                ToKnockback_422D90(1, 1);

                if (pAliveObj->mBaseAnimatedWithPhysicsGameObject_XPos < mBaseAnimatedWithPhysicsGameObject_XPos)
                {
                    if (!field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        mCurrentMotion = eAbeMotions::Motion_128_KnockForward_429330;
                    }
                }
                else if (pAliveObj->mBaseAnimatedWithPhysicsGameObject_XPos > mBaseAnimatedWithPhysicsGameObject_XPos)
                {
                    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        mCurrentMotion = eAbeMotions::Motion_128_KnockForward_429330;
                    }
                }

                if (pAliveObj->field_B4_velx >= FP_FromInteger(0))
                {
                    field_B4_velx = (field_BC_sprite_scale * FP_FromDouble(7.8));
                }
                else
                {
                    field_B4_velx = (field_BC_sprite_scale * FP_FromDouble(-7.8));
                }

                SFX_Play_Mono(SoundEffect::KillEffect_78, 127, 0);
            }
            break;

        case ReliveTypes::eUnknown:
            break;

        case ReliveTypes::eZBall:
            if (mHealth > FP_FromInteger(0))
            {
                field_106_shot = 1;
                mHealth = FP_FromInteger(0);
                if (static_cast<ZBall*>(pFrom)->field_E8_bFrameAbove12 == 1)
                {
                    field_112_prev_motion = eAbeMotions::Motion_148_Shot_4296A0;
                    mNextMotion = eAbeMotions::Motion_148_Shot_4296A0;
                }
                else
                {
                    field_112_prev_motion = eAbeMotions::Motion_147_ShotRolling_4295C0;
                    mNextMotion = eAbeMotions::Motion_147_ShotRolling_4295C0;
                }
            }
            break;

        case ReliveTypes::eBeeSwarm:
            if (mHealth > FP_FromInteger(0))
            {
                mHealth -= FP_FromDouble(0.15);
                if (mHealth > FP_FromInteger(0))
                {
                    const auto rnd_sfx = Math_RandomRange_450F20(0, 127) >= 64 ? MudSounds::eBeesStruggle_18 : MudSounds::eKnockbackOuch_10;
                    const FP v16 = (FP_FromInteger(1) - sActiveHero_507678->mHealth) / FP_FromDouble(0.15);
                    const s16 calc_pitch = Math_RandomRange_450F20(200 * FP_GetExponent(v16), 200 * FP_GetExponent(v16) + 1);
                    Mudokon_SFX_42A4D0(rnd_sfx, 0, calc_pitch, this);
                }
                else
                {
                    Mudokon_SFX_42A4D0(MudSounds::eKnockbackOuch_10, 0, 1000, this);
                    Environment_SFX_42A220(EnvironmentSfx::eDeathNoise_7, 0, 0x7FFF, this);
                    mHealth = FP_FromInteger(0);
                    field_106_shot = 1;
                    field_112_prev_motion = eAbeMotions::Motion_128_KnockForward_429330;
                    mNextMotion = eAbeMotions::Motion_128_KnockForward_429330;
                    if (mCurrentMotion == eAbeMotions::Motion_64_LedgeAscend_428B60
                        || mCurrentMotion == eAbeMotions::Motion_66_LedgeHang_428D90
                        || mCurrentMotion == eAbeMotions::Motion_68_LedgeHangWobble_428E50
                        || mCurrentMotion == eAbeMotions::Motion_65_LedgeDescend_428C00
                        || mCurrentMotion == eAbeMotions::Motion_67_ToOffScreenHoist_428C50)
                    {
                        mCurrentMotion = eAbeMotions::Motion_92_ForceDownFromHoist_4297C0;
                        field_108_bMotionChanged = 1;
                        field_106_shot = 0;
                        field_114_gnFrame = 0;
                        return 1;
                    }

                    if (!field_1A4_resources.res[0])
                    {
                        ElumKnockForward_42E780(1);
                        field_106_shot = 0;
                    }
                }

                if (mCurrentMotion == eAbeMotions::Motion_103_ElumIdle_42DCD0)
                {
                    mCurrentMotion = eAbeMotions::Motion_126_ElumBeesStruggling_42E080;
                    field_108_bMotionChanged = 1;
                }
            }
            break;

        case ReliveTypes::eElectrocute:
            field_10_anim.mAnimFlags.Clear(AnimFlags::eBit3_Render);
            ToDieFinal_42C400();
            break;

        case ReliveTypes::eBullet:
            // NOTE: This was in the default case! The type may not be bullet in there which would corrupt memory or crash
            BulletDamage_4220B0(static_cast<Bullet*>(pFrom));
            if (!field_106_shot)
            {
                field_130_say = old_say;
                oldHp = FP_FromInteger(0);
            }
            break;

        default:
            break;
    }

    if (sControlledCharacter_50767C->mBaseAliveGameObjectFlags.Get(Flags_10A::e10A_Bit2_bPossesed))
    {
        if (mHealth == FP_FromInteger(0))
        {
            sControlledCharacter_50767C->VUnPosses();
            field_2A8_flags.Set(Flags_2A8::e2A8_Bit7);
            sControlledCharacter_50767C = this;
        }
    }

    return oldHp > FP_FromInteger(0) ? 1 : 0;
}

static bool IsSameScaleAsHoist(Path_Hoist* pHoist, BaseAliveGameObject* pObj)
{
    auto width = pHoist->field_14_bottom_right.field_0_x - pHoist->field_10_top_left.field_0_x;

    //The width is used to determine the layer as there is no layer property in the TLV
    if (pObj->field_BC_sprite_scale == FP_FromInteger(1))
    {
        return width > 18;
    }
    else
    {
        return width <= 18;
    }
}

static bool IsFacingSameDirectionAsHoist(Path_Hoist* pHoist, BaseAliveGameObject* pObj)
{
    if (pHoist->field_1A_grab_direction == Path_Hoist::GrabDirection::eFacingLeft && !pObj->field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        return false;
    }
    else if (pHoist->field_1A_grab_direction == Path_Hoist::GrabDirection::eFacingRight && pObj->field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        return false;
    }
    return true;
}

void Abe::TryHoist_423420()
{
    mCurrentMotion = eAbeMotions::Motion_16_HoistBegin_426E40;

    auto pHoist = static_cast<Path_Hoist*>(gMap.TLV_Get_At_446260(
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
        TlvTypes::Hoist_3));

    if (pHoist && IsSameScaleAsHoist(pHoist, this))
    {
        if (FP_FromInteger(pHoist->field_14_bottom_right.field_2_y - pHoist->field_10_top_left.field_2_y) <= field_BC_sprite_scale * FP_FromInteger(95))
        {
            mCurrentMotion = eAbeMotions::Motion_16_HoistBegin_426E40;
        }
        else
        {
            mCurrentMotion = eAbeMotions::Motion_99_HoistBeginLong_426DC0;
        }
        if (!IsFacingSameDirectionAsHoist(pHoist, this))
        {
            mNextMotion = mCurrentMotion;
            mCurrentMotion = eAbeMotions::Motion_2_StandingTurn_426040;
        }
        BaseAliveGameObjectPathTLV = pHoist;
    }
}

void Abe::Motion_0_Idle_423520()
{
    FollowLift_42EE90();
    if (Input_IsChanting() && !field_2A8_flags.Get(Flags_2A8::e2A8_Bit7))
    {
        if (field_168_ring_pulse_timer && field_16C_bHaveShrykull)
        {
            mCurrentMotion = eAbeMotions::Motion_162_ToShrykull_42F410;
        }
        else
        {
            field_114_gnFrame = sGnFrame + 90;
            mCurrentMotion = eAbeMotions::Motion_150_Chant_42FD50;
            SND_SEQ_PlaySeq_4775A0(SeqId::eMudokonChant1_11, 0, 1);
        }
        field_110_state.raw = 0;
        return;
    }
    if (Input().IsAnyPressed(sInputKey_LeftGameSpeakEnabler_4C65B8 | sInputKey_RightGameSpeakEnabler_4C65DC))
    {
        const auto held = Input().Held();
        if (held & 0xF0)
        {
            field_10C_prev_held = held;
            mCurrentMotion = eAbeMotions::Motion_58_ToSpeak_42F8D0;
            return;
        }
    }
    if (Input().IsAnyPressed(sInputKey_Hop_4C65A0))
    {
        if (Input().IsAnyPressed(sInputKey_Up_4C6598))
        {
            TryHoist_423420();
        }
        else if (!Input().IsAnyPressed(sInputKey_LeftGameSpeakEnabler_4C65B8 | sInputKey_RightGameSpeakEnabler_4C65DC))
        {
            mCurrentMotion = eAbeMotions::Motion_29_HopBegin_4267B0;
            auto pObj = IntoBirdPortal_402350(2);
            if (pObj)
            {
                if (pObj->field_10_portal_type != PortalType::eAbe_0)
                {
                    pObj = nullptr;
                }
                field_19E_portal_sub_state = PortalSubStates::eJumpingInsidePortal_0;
            }
            field_1A0_portal = pObj;
        }
        return;
    }

    if (ToLeftRightMovement_422AA0())
    {
        return;
    }

    if (Input().IsAnyPressed(sInputKey_Down_4C659C))
    {
        if (mLiftPoint)
        {
            const FP liftPlatformXMidPoint = FP_FromInteger((BaseAliveGameObjectCollisionLine->field_0_rect.x + BaseAliveGameObjectCollisionLine->field_0_rect.w) / 2);
            const FP halfGrid = ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(2);

            if (mLiftPoint->mBaseGameObjectTypeId == ReliveTypes::eLiftPoint && FP_Abs(mBaseAnimatedWithPhysicsGameObject_XPos - liftPlatformXMidPoint) < halfGrid)
            {
                //AO exclusive - Abe only uses lift facing one side
                if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    mCurrentMotion = eAbeMotions::Motion_2_StandingTurn_426040;
                    mNextMotion = eAbeMotions::Motion_133_LiftGrabBegin_42EF20;
                }
                else
                {
                    mCurrentMotion = eAbeMotions::Motion_133_LiftGrabBegin_42EF20;
                }
                return;
            }
        }


        const auto pHoist = static_cast<Path_Hoist*>(gMap.TLV_Get_At_446260(
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos + FP_FromInteger(16)),
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos + FP_FromInteger(16)),
            TlvTypes::Hoist_3));

        if (pHoist)
        {
            if (!IsSameScaleAsHoist(pHoist, this))
            {
                return;
            }

            if (IsFacingSameDirectionAsHoist(pHoist, this))
            {
                mCurrentMotion = eAbeMotions::Motion_65_LedgeDescend_428C00;
            }
            else
            {
                mNextMotion = eAbeMotions::Motion_65_LedgeDescend_428C00;
                mCurrentMotion = eAbeMotions::Motion_2_StandingTurn_426040;
            }
        }
        else
        {
            mCurrentMotion = eAbeMotions::Motion_21_StandToCrouch_427F40;
        }
        return;
    }
    if (Input().IsAnyPressed(sInputKey_FartRoll_4C65B0))
    {
        mCurrentMotion = eAbeMotions::Motion_21_StandToCrouch_427F40;
    }

    bool handleDoActionOrThrow = false;
    if (Input().IsAnyPressed(sInputKey_Up_4C6598))
    {
        if (mLiftPoint)
        {
            if (mLiftPoint->mBaseGameObjectTypeId == ReliveTypes::eLiftPoint)
            {
                const FP halfGrid = ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(2);
                const FP liftPlatformXMidPoint = FP_FromInteger((BaseAliveGameObjectCollisionLine->field_0_rect.x + BaseAliveGameObjectCollisionLine->field_0_rect.w) / 2);
                const FP xPosToMidLiftPlatformDistance = FP_Abs(mBaseAnimatedWithPhysicsGameObject_XPos - liftPlatformXMidPoint);
                if (xPosToMidLiftPlatformDistance < halfGrid)
                {
                    //AO exclusive - Abe only uses lift facing one side
                    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        mCurrentMotion = eAbeMotions::Motion_2_StandingTurn_426040;
                        mNextMotion = eAbeMotions::Motion_133_LiftGrabBegin_42EF20;
                    }
                    else
                    {
                        mCurrentMotion = eAbeMotions::Motion_133_LiftGrabBegin_42EF20;
                    }
                    return;
                }
            }
        }

        mCurrentMotion = TryMountElum_42E600();
        if (mCurrentMotion != eAbeMotions::Motion_0_Idle_423520)
        {
            return;
        }
        auto pTlv = gMap.TLV_Get_At_446060(
            nullptr,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos);

        while (pTlv)
        {
            switch (pTlv->field_4_type.mType)
            {
                case TlvTypes::Door_6:
                {
                    if (NearDoorIsOpen() && !mBaseAliveGameObjectFlags.Get(Flags_10A::e10A_Bit5_Electrocuted))
                    {
                        BaseAliveGameObjectPathTLV = pTlv;
                        field_110_state.raw = 0;
                        mCurrentMotion = eAbeMotions::Motion_156_DoorEnter_42D370;
                    }
                    else
                    {
                        if (Input().IsAnyHeld(sInputKey_Up_4C6598))
                        {
                            mCurrentMotion = eAbeMotions::Motion_36_DunnoBegin_423260;
                        }
                    }
                    return;
                }
                case TlvTypes::WellLocal_11:
                {
                    auto well = static_cast<Path_WellLocal*>(pTlv);
                    if ((well->field_18_scale != Scale_short::eFull_0 || field_BC_sprite_scale != FP_FromInteger(1)) &&
                        (well->field_18_scale != Scale_short::eHalf_1 || field_BC_sprite_scale != FP_FromDouble(0.5)))
                    {
                        break;
                    }
                    field_2A8_flags.Clear(Flags_2A8::e2A8_Bit4_snap_abe);
                    BaseAliveGameObjectPathTLV = pTlv;
                    mCurrentMotion = eAbeMotions::Motion_77_WellBegin_430F10;
                    return;
                }
                case TlvTypes::WellExpress_45:
                {
                    auto well = static_cast<Path_WellExpress*>(pTlv);
                    if ((well->field_18_scale != Scale_short::eFull_0 || field_BC_sprite_scale != FP_FromInteger(1)) &&
                        (well->field_18_scale != Scale_short::eHalf_1 || field_BC_sprite_scale != FP_FromDouble(0.5)))
                    {
                        break;
                    }
                    field_2A8_flags.Clear(Flags_2A8::e2A8_Bit4_snap_abe);
                    BaseAliveGameObjectPathTLV = pTlv;
                    mCurrentMotion = eAbeMotions::Motion_80_430EF0;
                    return;
                }
                case TlvTypes::MovieStone_51:
                case TlvTypes::BellSongStone_54:
                case TlvTypes::DemoPlaybackStone_96:
                case TlvTypes::HandStone_100:
                {
                    BaseAliveGameObjectPathTLV = pTlv;
                    mCurrentMotion = eAbeMotions::Motion_88_HandstoneBegin_430590;
                    field_110_state.stone = StoneStates::eHandstoneStart_0;
                    return;
                }
                case TlvTypes::BoomMachine_97:
                {
                    auto pMachineButton = static_cast<BoomMachine*>(FindObjectOfType_418280(
                        ReliveTypes::eGrenadeMachine,
                        mBaseAnimatedWithPhysicsGameObject_XPos,
                        mBaseAnimatedWithPhysicsGameObject_YPos - field_BC_sprite_scale * FP_FromInteger(25)));
                    if (pMachineButton)
                    {
                        pMachineButton->VHandleButton();
                        mCurrentMotion = eAbeMotions::Motion_90_GrenadeMachineUse_430EA0;
                    }
                    else
                    {
                        mCurrentMotion = eAbeMotions::Motion_36_DunnoBegin_423260;
                    }
                    break;
                }
                default:
                    break;
            }

            pTlv = gMap.TLV_Get_At_446060(
                pTlv,
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos,
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos);
        }
        if (mCurrentMotion == eAbeMotions::Motion_0_Idle_423520)
        {
            TryHoist_423420();
        }
        handleDoActionOrThrow = true;
    }

    if (!Input().IsAnyPressed(sInputKey_Up_4C6598) || handleDoActionOrThrow)
    {
        if (Input().IsAnyHeld(sInputKey_ThrowItem_4C65B4) && mCurrentMotion == eAbeMotions::Motion_0_Idle_423520)
        {
            if (field_19C_throwable_count > 0 || gInfiniteGrenades_5076EC)
            {
                field_198_pThrowable = Make_Throwable(
                    mBaseAnimatedWithPhysicsGameObject_XPos,
                    mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromInteger(40),
                    0);

                if (bThrowableIndicatorExists_504C70 == 0)
                {
                    const FP xOffSet = field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX) ? FP_FromInteger(15) : FP_FromInteger(-15) * field_BC_sprite_scale;

                    ao_new<ThrowableTotalIndicator>(mBaseAnimatedWithPhysicsGameObject_XPos + xOffSet,
                                                                                    mBaseAnimatedWithPhysicsGameObject_YPos + field_BC_sprite_scale * FP_FromInteger(-50),
                                                                                    field_10_anim.mRenderLayer,
                                                                                    field_10_anim.field_14_scale,
                                                                                    field_19C_throwable_count,
                                                                                    TRUE);
                }
                mCurrentMotion = eAbeMotions::Motion_142_RockThrowStandingHold_429CE0;

                if (gInfiniteGrenades_5076EC == 0)
                {
                    field_19C_throwable_count--;
                }
            }
            else
            {
                mCurrentMotion = eAbeMotions::Motion_36_DunnoBegin_423260;
            }
        }
        else
        {
            if (Input().IsAnyHeld(sInputKey_DoAction_4C65A4))
            {
                mCurrentMotion = HandleDoAction_429A70();
            }
            else if (gBeeInstanceCount_5076B0 && gBeesNearAbe_5076AC)
            {
                mCurrentMotion = eAbeMotions::Motion_140_BeesStruggling_423F30;
            }
            else if (sGnFrame - field_114_gnFrame > 150)
            {
                u16 loaded = 0;
                field_114_gnFrame = sGnFrame;


#if 0
                // Force load idle anims to restore the feature, it kinda sucks though
                if (!ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeyawnAOResID, 0, 0))
                {
                    ResourceManager::LoadResourceFile_455270("ABEYAWN.BAN", nullptr, ResourceManager::BlockAllocMethod::eFirstMatching);
                }
                if (!ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAberubAOResID, 0, 0))
                {
                    ResourceManager::LoadResourceFile_455270("ABERUB.BAN", nullptr, ResourceManager::BlockAllocMethod::eFirstMatching);
                }
                if (!ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbesizeAOResID, 0, 0))
                {
                    ResourceManager::LoadResourceFile_455270("ABESIZE.BAN", nullptr, ResourceManager::BlockAllocMethod::eFirstMatching);
                }
#endif

                if (ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeyawnAOResID, 0, 0)) //yawn ABEYAWN.BAN
                {
                    loaded |= 1;
                }
                if (ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAberubAOResID, 0, 0)) // rub ABERUB.BAN
                {
                    loaded |= 2;
                }
                if (ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbesizeAOResID, 0, 0)) // size ABESIZE.BAN
                {
                    loaded |= 4;
                }
                const s16 rnd = Math_RandomRange_450F20(0, 2);
                if ((1 << rnd) & loaded)
                {
                    switch (rnd)
                    {
                        case 0:
                        {
                            mCurrentMotion = eAbeMotions::Motion_161_Idle_Yawn_4233E0;
                            break;
                        }
                        case 1:
                        {
                            mCurrentMotion = eAbeMotions::Motion_159_Idle_RubEyes_423360;
                            break;
                        }
                        case 2:
                        {
                            mCurrentMotion = eAbeMotions::Motion_160_Idle_Stretch_Arms_4233A0;
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        }
    }
}

void Abe::Motion_1_WalkLoop_423F90()
{
    field_10C_prev_held |= Input().Pressed();

    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    MoveForward_422FC0();

    if (mCurrentMotion == eAbeMotions::Motion_1_WalkLoop_423F90)
    {
        switch (field_10_anim.field_92_current_frame)
        {
            case 2:
            {
                if ((field_B4_velx > FP_FromInteger(0) && Input().IsAnyPressed(sInputKey_Left_4C6594)) || (field_B4_velx < FP_FromInteger(0) && Input().IsAnyPressed(sInputKey_Right_4C6590)))
                {
                    mCurrentMotion = eAbeMotions::Motion_5_MidWalkToIdle_424490;
                    field_10C_prev_held = 0;
                    return;
                }

                if (field_10C_prev_held & sInputKey_Hop_4C65A0)
                {
                    mNextMotion = eAbeMotions::Motion_30_HopMid_4264D0;
                    mCurrentMotion = eAbeMotions::Motion_5_MidWalkToIdle_424490;
                    field_10C_prev_held = 0;
                    return;
                }

                if (!Input().IsAnyPressed(sInputKey_Right_4C6590 | sInputKey_Left_4C6594))
                {
                    mCurrentMotion = eAbeMotions::Motion_5_MidWalkToIdle_424490;
                    field_10C_prev_held = 0;
                }
                else
                {
                    FP directedScale = {};
                    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        directedScale = -ScaleToGridSize(field_BC_sprite_scale);
                    }
                    else
                    {
                        directedScale = ScaleToGridSize(field_BC_sprite_scale);
                    }

                    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), directedScale * FP_FromDouble(1.5)))
                    {
                        mCurrentMotion = eAbeMotions::Motion_5_MidWalkToIdle_424490;
                        field_10C_prev_held = 0;
                        return;
                    }
                    else
                    {
                        field_10C_prev_held = 0;
                    }
                }
                break;
            }

            case 11:
                if ((field_B4_velx <= FP_FromInteger(0) || !(Input().IsAnyPressed(sInputKey_Left_4C6594))) && (field_B4_velx >= FP_FromInteger(0) || !(Input().IsAnyPressed(sInputKey_Right_4C6590))))
                {
                    if (field_10C_prev_held & sInputKey_Hop_4C65A0)
                    {
                        mNextMotion = eAbeMotions::Motion_30_HopMid_4264D0;
                    }
                    else if (Input().IsAnyPressed(sInputKey_Right_4C6590 | sInputKey_Left_4C6594))
                    {
                        FP directedScale = {};
                        if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                        {
                            directedScale = -ScaleToGridSize(field_BC_sprite_scale);
                        }
                        else
                        {
                            directedScale = ScaleToGridSize(field_BC_sprite_scale);
                        }

                        if (!WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), directedScale * FP_FromDouble(1.5)))
                        {
                            field_10C_prev_held = 0;
                            return;
                        }
                    }
                }
                mCurrentMotion = eAbeMotions::Motion_4_WalkToIdle_4243C0;
                field_10C_prev_held = 0;
                return;

            case 5:
                Environment_SFX_42A220(EnvironmentSfx::eWalkingFootstep_1, 0, 0x7FFF, this);

                if (!field_2A8_flags.Get(Flags_2A8::e2A8_Bit3_WalkToRun))
                {
                    field_2A8_flags.Set(Flags_2A8::e2A8_Bit3_WalkToRun);
                    MapFollowMe_401D30(1);
                }

                if (Input().IsAnyPressed(sInputKey_Run_4C65A8))
                {
                    mCurrentMotion = eAbeMotions::Motion_51_MidWalkToRun_424670;
                }
                else if (Input().IsAnyPressed(sInputKey_Sneak_4C65AC))
                {
                    mCurrentMotion = eAbeMotions::Motion_43_WalkToSneak_424790;
                }
                break;

            case 14:
                Environment_SFX_42A220(EnvironmentSfx::eWalkingFootstep_1, 0, 0x7FFF, this);

                if (!field_2A8_flags.Get(Flags_2A8::e2A8_Bit3_WalkToRun))
                {
                    field_2A8_flags.Set(Flags_2A8::e2A8_Bit3_WalkToRun);
                    MapFollowMe_401D30(1);
                }

                if (Input().IsAnyPressed(sInputKey_Run_4C65A8))
                {
                    mCurrentMotion = eAbeMotions::Motion_50_WalkToRun_424560;
                }
                else if (Input().IsAnyPressed(sInputKey_Sneak_4C65AC))
                {
                    mCurrentMotion = eAbeMotions::Motion_45_MidWalkToSneak_424890;
                }
                break;

            default:
                field_2A8_flags.Clear(Flags_2A8::e2A8_Bit3_WalkToRun);
                break;
        }
    }
}

void Abe::Motion_2_StandingTurn_426040()
{
    FollowLift_42EE90();

    if (field_10_anim.field_92_current_frame == 4)
    {
        if (Input().IsAnyPressed(sInputKey_Run_4C65A8) && Input().IsAnyPressed(sInputKey_Right_4C6590 | sInputKey_Left_4C6594))
        {
#if ORIGINAL_GAME_FIXES || ORIGINAL_GAME_FIX_AUTO_TURN
            mNextMotion = eAbeMotions::Motion_0_Idle_423520; // OG Change - Fixes "Auto-Turn" bug
#endif

            mCurrentMotion = eAbeMotions::Motion_63_TurnToRun_42A0A0;
            field_10_anim.mAnimFlags.Toggle(AnimFlags::eBit5_FlipX);

            if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
            {
                field_B4_velx = -(ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(4));
            }
            else
            {
                field_B4_velx = (ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(4));
            }
            return;
        }
    }

    if (!field_10_anim.field_92_current_frame)
    {
        Environment_SFX_42A220(EnvironmentSfx::eGenericMovement_9, 0, 0x7FFF, this);
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_10_anim.mAnimFlags.Toggle(AnimFlags::eBit5_FlipX);

        if (mNextMotion)
        {
            // OG bug: this local variable allows you to "store" your next state if you face the opposite
            // ledge direction and press down/up and then interrupt it by running away before you hoist.
            const s16 kNext_state = mNextMotion;
            if (mNextMotion != eAbeMotions::Motion_139_ElumMountBegin_42E090)
            {
                if (mNextMotion == eAbeMotions::Motion_101_LeverUse_429970)
                {
                    Lever* pSwitch;
                    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        pSwitch = static_cast<Lever*>(FindObjectOfType_418280(ReliveTypes::eLever, mBaseAnimatedWithPhysicsGameObject_XPos - ScaleToGridSize(field_BC_sprite_scale), mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromInteger(5)));
                    }
                    else
                    {
                        pSwitch = static_cast<Lever*>(FindObjectOfType_418280(ReliveTypes::eLever, mBaseAnimatedWithPhysicsGameObject_XPos + ScaleToGridSize(field_BC_sprite_scale), mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromInteger(5)));
                    }

                    if (pSwitch)
                    {
                        pSwitch->VPull(mBaseAnimatedWithPhysicsGameObject_XPos < pSwitch->mBaseAnimatedWithPhysicsGameObject_XPos);
                    }
                }
                mNextMotion = eAbeMotions::Motion_0_Idle_423520;
                mCurrentMotion = kNext_state;
                return;
            }

            if (gElum_507680)
            {
                if (gElum_507680->mCurrentMotion == eElumMotions::Motion_1_Idle_412990 && !(gElum_507680->field_170_flags.Get(Elum::Flags_170::eStrugglingWithBees_Bit1)))
                {
                    LoadMountElumResources_42E690();
                    mNextMotion = eAbeMotions::Motion_0_Idle_423520;
                    mCurrentMotion = kNext_state;
                    return;
                }
            }
            mNextMotion = eAbeMotions::Motion_0_Idle_423520;
        }
        else
        {
            if (ToLeftRightMovement_422AA0())
            {
                field_10_anim.Set_Animation_Data(field_10_anim.field_18_frame_table_offset, 0);
                return;
            }
        }
        ToIdle_422D50();
    }
}

static bool isEdgeGrabbable(Path_Edge* pEdge, BaseAliveGameObject* pObj)
{
    if (pEdge->field_18_grab_direction == Path_Edge::GrabDirection::eFacingLeft && pObj->field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        return true;
    }
    else if (pEdge->field_18_grab_direction == Path_Edge::GrabDirection::eFacingRight && !pObj->field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        return true;
    }
    else if (pEdge->field_18_grab_direction == Path_Edge::GrabDirection::eFacingAnyDirection)
    {
        return true;
    }

    return false;
}

void Abe::Motion_3_Fall_42E7F0()
{
    if (field_B4_velx > FP_FromInteger(0))
    {
        field_B4_velx -= (field_BC_sprite_scale * field_120_x_vel_slow_by);
        if (field_B4_velx < FP_FromInteger(0))
        {
            field_B4_velx = FP_FromInteger(0);
        }
    }
    else if (field_B4_velx < FP_FromInteger(0))
    {
        field_B4_velx += (field_BC_sprite_scale * field_120_x_vel_slow_by);
        if (field_B4_velx > FP_FromInteger(0))
        {
            field_B4_velx = FP_FromInteger(0);
        }
    }

    FP hitX = {};
    FP hitY = {};
    PathLine* pPathLine = nullptr;
    const s32 bCollision = InAirCollision_4019C0(&pPathLine, &hitX, &hitY, FP_FromDouble(1.8));
    SetActiveCameraDelayedFromDir_401C90();

    BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446060(
        nullptr,
        mBaseAnimatedWithPhysicsGameObject_XPos,
        mBaseAnimatedWithPhysicsGameObject_YPos,
        mBaseAnimatedWithPhysicsGameObject_XPos,
        mBaseAnimatedWithPhysicsGameObject_YPos);

    if (BaseAliveGameObjectPathTLV)
    {
        if (mHealth > FP_FromInteger(0))
        {
            if (BaseAliveGameObjectPathTLV->field_4_type == TlvTypes::WellLocal_11 || BaseAliveGameObjectPathTLV->field_4_type == TlvTypes::WellExpress_45)
            {
                // The well must be on the same scale/layer
                Path_WellBase* pWellBase = static_cast<Path_WellBase*>(BaseAliveGameObjectPathTLV);
                if ((pWellBase->field_18_scale == Scale_short::eFull_0 && field_BC_sprite_scale == FP_FromInteger(1)) ||
                    (pWellBase->field_18_scale == Scale_short::eHalf_1 && field_BC_sprite_scale == FP_FromDouble(0.5)))
                {
                    field_2A8_flags.Set(Flags_2A8::e2A8_Bit4_snap_abe);
                    mCurrentMotion = eAbeMotions::Motion_74_JumpIntoWell_430EC0;
                    return;
                }
            }
        }
    }

    if (bCollision)
    {
        switch (pPathLine->field_8_type)
        {
            case eLineTypes::eFloor_0:
            case eLineTypes::eBackgroundFloor_4:
            case eLineTypes::eUnknown_32:
            case eLineTypes::eUnknown_36:
            {
                mBaseAnimatedWithPhysicsGameObject_XPos = hitX;
                mBaseAnimatedWithPhysicsGameObject_YPos = hitY;
                BaseAliveGameObjectCollisionLine = pPathLine;
                MapFollowMe_401D30(1);
                field_114_gnFrame = sGnFrame + 30;
                if (mBaseAnimatedWithPhysicsGameObject_YPos - BaseAliveGameObjectLastLineYPos > FP_FromInteger(240))
                {
                    BaseAliveGameObjectLastLineYPos += FP_FromInteger(240);
                }

                Path_SoftLanding* pSoftLanding = static_cast<Path_SoftLanding*>(gMap.TLV_Get_At_446260(
                    FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
                    FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                    FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
                    FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                    TlvTypes::SoftLanding_114));

                if (field_2A8_flags.Get(Flags_2A8::e2A8_Bit8_bLandSoft)
                    || (pSoftLanding && mHealth > FP_FromInteger(0))
                    || ((mBaseAnimatedWithPhysicsGameObject_YPos - BaseAliveGameObjectLastLineYPos) < (field_BC_sprite_scale * FP_FromInteger(180))
                        && (mHealth > FP_FromInteger(0) || gAbeInvulnerableCheat_5076E4)))
                {
                    mCurrentMotion = eAbeMotions::Motion_98_LandSoft_42ED40;
                }
                else
                {
                    mHealth = FP_FromInteger(0);
                    mCurrentMotion = eAbeMotions::Motion_86_FallLandDie_42EDD0;
                    field_11C_regen_health_timer = sGnFrame + 900;
                }
                mPreviousMotion = eAbeMotions::Motion_3_Fall_42E7F0;

                PSX_Point xy{FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos - FP_FromInteger(25)), FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromInteger(25))};
                PSX_Point wh{FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos + FP_FromInteger(25)), FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos + FP_FromInteger(25))};
                VOnCollisionWith(
                    xy,
                    wh,
                    ObjListPlatforms_50766C,
                    1,
                    reinterpret_cast<TCollisionCallBack>(&BaseAliveGameObject::OnTrapDoorIntersection_401C10));
                break;
            }
            case eLineTypes::eWallLeft_1:
            case eLineTypes::eWallRight_2:
            case eLineTypes::eBackgroundWallLeft_5:
            case eLineTypes::eBackgroundWallRight_6:
                mBaseAnimatedWithPhysicsGameObject_XPos = hitX;
                mBaseAnimatedWithPhysicsGameObject_YPos = hitY;
                ToKnockback_422D90(1, 1);
                break;
            default:
                return;
        }
        return;
    }

    if (mHealth <= FP_FromInteger(0))
    {
        return;
    }

    bool tryToHang = false;
    Path_Edge* pEdge = static_cast<Path_Edge*>(gMap.TLV_Get_At_446260(
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos - field_BC_sprite_scale * FP_FromInteger(80)),
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
        TlvTypes::Edge_4));

    if (pEdge)
    {
        if (pEdge->field_1A_can_grab == Choice_short::eYes_1 && isEdgeGrabbable(pEdge, this))
        {
            tryToHang = true;
        }
        BaseAliveGameObjectPathTLV = pEdge;
    }
    else
    {
        Path_Hoist* pHoist = static_cast<Path_Hoist*>(gMap.TLV_Get_At_446260(
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos - field_BC_sprite_scale * FP_FromInteger(20)),
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos - field_BC_sprite_scale * FP_FromInteger(20)),
            TlvTypes::Hoist_3));

        if (pHoist)
        {
            if (IsFacingSameDirectionAsHoist(pHoist, this))
            {
                tryToHang = true;
            }
        }

        BaseAliveGameObjectPathTLV = pHoist;
    }

    if (tryToHang)
    {
        if (field_B4_velx == FP_FromInteger(0))
        {
            return;
        }

        mBaseAnimatedWithPhysicsGameObject_XPos = FP_FromInteger((BaseAliveGameObjectPathTLV->field_10_top_left.field_0_x + BaseAliveGameObjectPathTLV->field_14_bottom_right.field_0_x) / 2);

        MapFollowMe_401D30(TRUE);

        if (sCollisions->RayCast(
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos - field_BC_sprite_scale * FP_FromInteger(20) - field_BC_sprite_scale * FP_FromInteger(80),
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos,
                &pPathLine,
                &hitX,
                &hitY,
                field_BC_sprite_scale != FP_FromDouble(0.5) ? 1 : 0x10))
        {
            field_B4_velx = FP_FromInteger(0);
            field_B8_vely = FP_FromInteger(0);
            mBaseAnimatedWithPhysicsGameObject_YPos = hitY;
            BaseAliveGameObjectCollisionLine = pPathLine;
            mCurrentMotion = eAbeMotions::Motion_68_LedgeHangWobble_428E50;
            field_D0_pShadow->field_14_flags.Set(Shadow::Flags::eBit1_ShadowAtBottom);
        }
    }
}

void Abe::Motion_4_WalkToIdle_4243C0()
{
    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    MoveForward_422FC0();

    if (field_10_anim.field_92_current_frame != 0)
    {
        if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            MapFollowMe_401D30(1);

            if (mNextMotion == eAbeMotions::Motion_30_HopMid_4264D0)
            {
                mNextMotion = eAbeMotions::Motion_0_Idle_423520;
                mCurrentMotion = eAbeMotions::Motion_29_HopBegin_4267B0;

                field_1A0_portal = IntoBirdPortal_402350(2);
                if (field_1A0_portal)
                {
                    if (field_1A0_portal->field_10_portal_type != PortalType::eAbe_0)
                    {
                        field_1A0_portal = nullptr;
                    }
                }

                if (field_1A0_portal)
                {
                    field_19E_portal_sub_state = PortalSubStates::eJumpingInsidePortal_0;
                }
            }
            else
            {
                ToIdle_422D50();
            }
        }
    }
    else
    {
        Environment_SFX_42A220(EnvironmentSfx::eWalkingFootstep_1, 0, 0x7FFF, this);
    }
}

void Abe::Motion_5_MidWalkToIdle_424490()
{
    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    MoveForward_422FC0();

    if (field_10_anim.field_92_current_frame)
    {
        if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            MapFollowMe_401D30(1);
            if (mNextMotion == eAbeMotions::Motion_30_HopMid_4264D0)
            {
                mNextMotion = 0;
                mCurrentMotion = eAbeMotions::Motion_29_HopBegin_4267B0;
                field_1A0_portal = IntoBirdPortal_402350(2);
                if (field_1A0_portal)
                {
                    if (field_1A0_portal->field_10_portal_type != PortalType::eAbe_0)
                    {
                        field_1A0_portal = nullptr;
                    }
                }

                if (field_1A0_portal)
                {
                    field_19E_portal_sub_state = PortalSubStates::eJumpingInsidePortal_0;
                }
            }
            else
            {
                ToIdle_422D50();
            }
        }
    }
    else
    {
        Environment_SFX_42A220(EnvironmentSfx::eWalkingFootstep_1, 0, 0x7FFF, this);
    }
}

void Abe::Motion_6_WalkBegin_424300()
{
    field_10C_prev_held |= Input().Pressed();

    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_1_WalkLoop_423F90;
    }

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
    {
        ToIdle_422D50();
    }
    else
    {
        MoveForward_422FC0();
    }
}

void Abe::Motion_7_Speak_42F950()
{
    Motion_58_ToSpeak_42F8D0();
}

void Abe::Motion_8_Speak_42F9D0()
{
    Motion_58_ToSpeak_42F8D0();
}

void Abe::Motion_9_Speak_42FA50()
{
    Motion_58_ToSpeak_42F8D0();
}

void Abe::Motion_10_Speak_42FAD0()
{
    Motion_58_ToSpeak_42F8D0();
}

void Abe::Motion_11_Speak_42FB50()
{
    Motion_58_ToSpeak_42F8D0();
}

void Abe::Motion_12_Speak_42FBD0()
{
    Motion_58_ToSpeak_42F8D0();
}

void Abe::Motion_13_Speak_42FC50()
{
    Motion_58_ToSpeak_42F8D0();
}

void Abe::Motion_14_Speak_42FCD0()
{
    Motion_58_ToSpeak_42F8D0();
}

void Abe::Motion_15_Null_42A210()
{
    // Empty
}

void Abe::Motion_16_HoistBegin_426E40()
{
    FollowLift_42EE90();

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        BaseAliveGameObjectLastLineYPos = mBaseAnimatedWithPhysicsGameObject_YPos;
        const FP velY = field_BC_sprite_scale * FP_FromInteger(-8);
        field_B8_vely = velY;
        mBaseAnimatedWithPhysicsGameObject_YPos += velY;
        VOnTrapDoorOpen();
        mCurrentMotion = eAbeMotions::Motion_17_HoistIdle_4269E0;
        BaseAliveGameObjectCollisionLine = nullptr;
    }
}

void Abe::Motion_17_HoistIdle_4269E0()
{
    PathLine* pPathLine = nullptr;
    FP hitX = {};
    FP hitY = {};
    const auto bCollision = InAirCollision_4019C0(&pPathLine, &hitX, &hitY, FP_FromDouble(1.8));
    SetActiveCameraDelayedFromDir_401C90();
    if (bCollision)
    {
        switch (pPathLine->field_8_type)
        {
            case eLineTypes::eFloor_0:
            case eLineTypes::eBackgroundFloor_4:
            case eLineTypes::eUnknown_32:
            case eLineTypes::eUnknown_36:
            {
                mBaseAnimatedWithPhysicsGameObject_XPos = hitX;
                mBaseAnimatedWithPhysicsGameObject_YPos = hitY;

                MapFollowMe_401D30(1);

                BaseAliveGameObjectCollisionLine = pPathLine;

                mCurrentMotion = eAbeMotions::Motion_18_HoistLand_426EB0;
                mPreviousMotion = eAbeMotions::Motion_17_HoistIdle_4269E0;

                PSX_RECT rect = {};
                VGetBoundingRect(&rect, 1);
                rect.y += 5;
                rect.h += 5;

                VOnCollisionWith(
                    {rect.x, rect.y},
                    {rect.w, rect.h},
                    ObjListPlatforms_50766C,
                    1,
                    (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection_401C10);
                break;
            }
        }
        return;
    }

    field_160_pRope = GetPullRope_422580();
    if (field_160_pRope)
    {
        if (field_160_pRope->Pull(this))
        {
            mCurrentMotion = eAbeMotions::Motion_69_RingRopePullHang_4299B0;
            mNextMotion = eAbeMotions::Motion_0_Idle_423520;
            field_160_pRope->mBaseGameObjectRefCount++;
            return;
        }
        field_160_pRope = nullptr;
    }

    if (field_B8_vely >= FP_FromInteger(0))
    {
        auto pHoist = static_cast<Path_Hoist*>(gMap.TLV_Get_At_446260(
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
            TlvTypes::Hoist_3));
        BaseAliveGameObjectPathTLV = pHoist;
        if (pHoist && IsSameScaleAsHoist(pHoist, this))
        {
            if (IsFacingSameDirectionAsHoist(pHoist, this))
            {
                if (pHoist->field_18_hoist_type == Path_Hoist::Type::eOffScreen)
                {
                    if (gMap.SetActiveCameraDelayed(Map::MapDirections::eMapTop_2, this, -1))
                    {
                        PSX_Prevent_Rendering_44FFB0();
                        mCurrentMotion = eAbeMotions::Motion_67_ToOffScreenHoist_428C50;
                        return;
                    }
                    mBaseAnimatedWithPhysicsGameObject_YPos -= field_BC_sprite_scale * FP_FromInteger(80);
                    field_D0_pShadow->field_14_flags.Set(Shadow::Flags::eBit1_ShadowAtBottom);
                }

                mCurrentMotion = eAbeMotions::Motion_66_LedgeHang_428D90;
                Environment_SFX_42A220(EnvironmentSfx::eWalkingFootstep_1, 0, 127, this);


                if (sCollisions->RayCast(
                        mBaseAnimatedWithPhysicsGameObject_XPos,
                        mBaseAnimatedWithPhysicsGameObject_YPos - field_BC_sprite_scale * FP_FromInteger(80),
                        mBaseAnimatedWithPhysicsGameObject_XPos,
                        mBaseAnimatedWithPhysicsGameObject_YPos,
                        &pPathLine,
                        &hitX,
                        &hitY,
                        field_BC_sprite_scale != FP_FromDouble(0.5) ? 1 : 0x10))
                {
                    mBaseAnimatedWithPhysicsGameObject_YPos = hitY;
                    BaseAliveGameObjectCollisionLine = pPathLine;
                    field_B8_vely = FP_FromInteger(0);
                    if (!mLiftPoint)
                    {
                        if (pPathLine->field_8_type == eLineTypes::eUnknown_32 ||
                            pPathLine->field_8_type == eLineTypes::eUnknown_36)
                        {
                            PSX_RECT rect = {};
                            VGetBoundingRect(&rect, 1);
                            rect.y += 5;
                            rect.h += 5;

                            VOnCollisionWith(
                                {rect.x, rect.y},
                                {rect.w, rect.h},
                                ObjListPlatforms_50766C,
                                1,
                                (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection_401C10);
                        }
                    }
                    field_D0_pShadow->field_14_flags.Set(Shadow::Flags::eBit1_ShadowAtBottom);
                }
                else
                {
                    mCurrentMotion = eAbeMotions::Motion_17_HoistIdle_4269E0;
                }
            }
        }
        else
        {
            BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446060(
                nullptr,
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos,
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos);
        }
    }
}

void Abe::Motion_18_HoistLand_426EB0()
{
    FollowLift_42EE90();

    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (field_10_anim.field_92_current_frame == 2)
    {
        if (mPreviousMotion == 3)
        {
            Environment_SFX_42A220(EnvironmentSfx::eLandingSoft_5, 0, 0x7FFF, this);
        }
        else
        {
            Environment_SFX_42A220(EnvironmentSfx::eHitGroundSoft_6, 0, 0x7FFF, this);
        }

        if (Input().IsAnyPressed(sInputKey_Hop_4C65A0))
        {
            if (Input().IsAnyPressed(sInputKey_Up_4C6598))
            {
                mCurrentMotion = eAbeMotions::Motion_16_HoistBegin_426E40;
            }
            else
            {
                mCurrentMotion = eAbeMotions::Motion_29_HopBegin_4267B0;
                field_1A0_portal = IntoBirdPortal_402350(2);

                if (field_1A0_portal)
                {
                    if (field_1A0_portal->field_10_portal_type != PortalType::eAbe_0)
                    {
                        field_1A0_portal = nullptr;
                    }
                }

                if (field_1A0_portal)
                {
                    field_19E_portal_sub_state = PortalSubStates::eJumpingInsidePortal_0;
                }
            }
        }
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_19_CrouchIdle_4284C0()
{
    if (!BaseAliveGameObjectCollisionLine)
    {
        mCurrentMotion = eAbeMotions::Motion_100_RollOffLedge_429950;
        return;
    }

    FollowLift_42EE90();

    if (Input().IsAllPressed(5) && Input().IsAllHeld(5))
    {
        Mudokon_SFX_42A4D0(MudSounds::eDunno_15, 0, 0, this);
        mCurrentMotion = eAbeMotions::Motion_23_CrouchSpeak_428A90;
        return;
    }

    // Crouching game speak
    CrouchingGameSpeak_427F90();

    field_10C_prev_held = 0;
    field_10E_released_buttons = 0;

    if (mCurrentMotion == eAbeMotions::Motion_22_CrouchSpeak_428A30 || mCurrentMotion == eAbeMotions::Motion_23_CrouchSpeak_428A90)
    {
        Event_Broadcast(kEventSpeaking, this);
        return;
    }


    // Hit bombs/pick up items ?
    if (Input().IsAnyHeld(sInputKey_DoAction_4C65A4))
    {
        if (!Input().IsAnyPressed(sInputKey_Right_4C6590 | sInputKey_Left_4C6594))
        {
            FP gridSize = {};
            if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
            {
                gridSize = -ScaleToGridSize(field_BC_sprite_scale);
            }
            else
            {
                gridSize = ScaleToGridSize(field_BC_sprite_scale);
            }

            PickUpThrowabe_Or_PressBomb_428260(
                gridSize + mBaseAnimatedWithPhysicsGameObject_XPos,
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromInteger(5)),
                0);
        }
    }


    // Crouching throw stuff
    if (Input().IsAnyHeld(sInputKey_ThrowItem_4C65B4))
    {
        if (mCurrentMotion == eAbeMotions::Motion_19_CrouchIdle_4284C0)
        {
            if (field_19C_throwable_count > 0 || gInfiniteGrenades_5076EC)
            {
                field_198_pThrowable = Make_Throwable(
                    mBaseAnimatedWithPhysicsGameObject_XPos,
                    mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromInteger(40),
                    0);

                if (!bThrowableIndicatorExists_504C70)
                {
                    const FP yOff = mBaseAnimatedWithPhysicsGameObject_YPos + (field_BC_sprite_scale * FP_FromInteger(-30));
                    const FP xOff = field_BC_sprite_scale * (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX) ? FP_FromInteger(-10) : FP_FromInteger(10));
                    ao_new<ThrowableTotalIndicator>(mBaseAnimatedWithPhysicsGameObject_XPos + xOff,
                                                                             yOff,
                                                                             field_10_anim.mRenderLayer,
                                                                             field_10_anim.field_14_scale,
                                                                             field_19C_throwable_count,
                                                                             1);
                }

                mCurrentMotion = eAbeMotions::Motion_145_RockThrowCrouchingHold_428930;

                if (!gInfiniteGrenades_5076EC)
                {
                    field_19C_throwable_count--;
                }

                return;
            }
        }

        if (!field_19C_throwable_count && !gInfiniteGrenades_5076EC)
        {
            Mudokon_SFX_42A4D0(MudSounds::eDunno_15, 0, 0, this);
            mCurrentMotion = eAbeMotions::Motion_23_CrouchSpeak_428A90;
            return;
        }
    }

    // Try to stand up
    if (Input().IsAnyHeld(sInputKey_Up_4C6598) || Input().IsAnyHeld(sInputKey_FartRoll_4C65B0))
    {
        PathLine* pLine = nullptr;
        FP hitX = {};
        FP hitY = {};
        if (!sCollisions->RayCast(
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos,
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos - (field_BC_sprite_scale * FP_FromInteger(60)),
                &pLine,
                &hitX,
                &hitY,
                field_BC_sprite_scale != FP_FromDouble(0.5) ? 8 : 0x80))
        {
            mCurrentMotion = eAbeMotions::Motion_20_CrouchToStand_428AF0;
            return;
        }
    }

    // Crouching turns
    if (Input().IsAnyPressed(sInputKey_Right_4C6590))
    {
        if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
        {
            mCurrentMotion = eAbeMotions::Motion_39_CrouchTurn_4288C0;
        }
        else
        {
            mCurrentMotion = eAbeMotions::Motion_24_RollBegin_427A20;
            field_10E_released_buttons = 0;
        }
    }

    if (Input().IsAnyPressed(sInputKey_Left_4C6594))
    {
        if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
        {
            mCurrentMotion = eAbeMotions::Motion_24_RollBegin_427A20;
            field_10E_released_buttons = 0;
        }
        else
        {
            mCurrentMotion = eAbeMotions::Motion_39_CrouchTurn_4288C0;
        }
    }
}

void Abe::Motion_20_CrouchToStand_428AF0()
{
    FollowLift_42EE90();

    if (field_10_anim.field_92_current_frame == 3)
    {
        if (Input().IsAnyPressed(0xA000)) // TODO: Flags
        {
            ToLeftRightMovement_422AA0();
        }
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_21_StandToCrouch_427F40()
{
    FollowLift_42EE90();

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        PickUpThrowabe_Or_PressBomb_428260(
            mBaseAnimatedWithPhysicsGameObject_XPos,
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromInteger(5)),
            1);
        mCurrentMotion = eAbeMotions::Motion_19_CrouchIdle_4284C0;
    }
}

void Abe::Motion_22_CrouchSpeak_428A30()
{
    Motion_23_CrouchSpeak_428A90();
}

void Abe::Motion_23_CrouchSpeak_428A90()
{
    field_10C_prev_held |= Input().Held();

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_19_CrouchIdle_4284C0;

        CrouchingGameSpeak_427F90();

        if (mCurrentMotion == eAbeMotions::Motion_22_CrouchSpeak_428A30 || mCurrentMotion == eAbeMotions::Motion_23_CrouchSpeak_428A90)
        {
            Event_Broadcast(kEventSpeaking, this);
        }

        field_10C_prev_held = 0;
    }
}

void Abe::Motion_24_RollBegin_427A20()
{
    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        field_B4_velx = -(ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(4));
    }
    else
    {
        field_B4_velx = (ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(4));
    }

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(20), field_B4_velx))
    {
        ToKnockback_422D90(1, 1);

        mCurrentMotion = eAbeMotions::Motion_73_RollingKnockback_4291D0;
    }
    else
    {
        MoveForward_422FC0();

        if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            if (mCurrentMotion == eAbeMotions::Motion_24_RollBegin_427A20)
            {
                mCurrentMotion = eAbeMotions::Motion_25_RollLoop_427BB0;
            }
        }
    }
}

Bool32 Abe::Is_Celling_Above()
{
    FP hitY = {};
    FP hitX = {};
    PathLine* pLine = nullptr;
    return sCollisions->RayCast(
               mBaseAnimatedWithPhysicsGameObject_XPos,
               mBaseAnimatedWithPhysicsGameObject_YPos,
               mBaseAnimatedWithPhysicsGameObject_XPos,
               mBaseAnimatedWithPhysicsGameObject_YPos - (field_BC_sprite_scale * FP_FromInteger(60)),
               &pLine,
               &hitX,
               &hitY,
               field_BC_sprite_scale != FP_FromDouble(0.5) ? 8 : 128)
        != 0;
}

void Abe::Motion_25_RollLoop_427BB0()
{
    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    field_10E_released_buttons |= Input().Released();

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(20), field_B4_velx))
    {
        ToKnockback_422D90(1, 1);
        mCurrentMotion = eAbeMotions::Motion_73_RollingKnockback_4291D0;
    }
    else
    {
        MoveForward_422FC0();

        if (mCurrentMotion == eAbeMotions::Motion_25_RollLoop_427BB0)
        {
            if (field_10_anim.field_92_current_frame == 1 || field_10_anim.field_92_current_frame == 5 || field_10_anim.field_92_current_frame == 9)
            {
                if (!Input().IsAnyPressed(sInputKey_Run_4C65A8)
                    || Input().IsAnyPressed(sInputKey_FartRoll_4C65B0)
                    || Is_Celling_Above()
                    || field_12C_timer + 9 >= static_cast<s32>(sGnFrame))
                {
                    if (field_10E_released_buttons && sInputKey_FartRoll_4C65B0)
                    {
                        if (!Is_Celling_Above() && field_12C_timer + 9 < static_cast<s32>(sGnFrame))
                        {
                            ToLeftRightMovement_422AA0();
                            field_10E_released_buttons = 0;
                        }
                    }
                }
                else
                {
                    ToLeftRightMovement_422AA0();
                    field_10C_prev_held = 0;
                }
            }
            else if (field_10_anim.field_92_current_frame == 0 || field_10_anim.field_92_current_frame == 4 || field_10_anim.field_92_current_frame == 8)
            {
                MapFollowMe_401D30(TRUE);

                if ((field_B4_velx > FP_FromInteger(0) && !Input().IsAnyPressed(sInputKey_Right_4C6590)) || (field_B4_velx < FP_FromInteger(0) && !Input().IsAnyPressed(sInputKey_Left_4C6594)))
                {
                    mCurrentMotion = eAbeMotions::Motion_19_CrouchIdle_4284C0;
                    field_B4_velx = FP_FromInteger(0);
                }
            }

            if (field_10_anim.field_92_current_frame == 0 || field_10_anim.field_92_current_frame == 6)
            {
                Environment_SFX_42A220(EnvironmentSfx::eRollingNoise_8, 0, 0x7FFF, this);
            }
        }
    }
}

void Abe::Motion_26_RollEnd_427EA0()
{
    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(20), field_B4_velx))
    {
        ToKnockback_422D90(1, 1);
        mCurrentMotion = eAbeMotions::Motion_73_RollingKnockback_4291D0;
    }
    else
    {
        MoveForward_422FC0();

        if (mCurrentMotion == eAbeMotions::Motion_26_RollEnd_427EA0)
        {
            if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                MapFollowMe_401D30(1);
                mCurrentMotion = eAbeMotions::Motion_19_CrouchIdle_4284C0;
                field_B4_velx = FP_FromInteger(0);
            }
        }
    }
}

void Abe::Motion_27_RunSlideStop_425B60()
{
    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
    {
        ToKnockback_422D90(1, 1);
    }
    else
    {
        MoveWithVelocity_4257F0(FP_FromDouble(0.375));
        if (mCurrentMotion == eAbeMotions::Motion_27_RunSlideStop_425B60
            && !RunTryEnterWell_425880()
            && !RunTryEnterDoor_4259C0())
        {
            if (field_10_anim.field_92_current_frame >= 9)
            {
                if (field_10_anim.field_92_current_frame == 15)
                {
                    Environment_SFX_42A220(EnvironmentSfx::eSlideStop_0, 0, 0x7FFF, this);
                    MapFollowMe_401D30(1);

                    if (!ToLeftRightMovement_422AA0())
                    {
                        ToIdle_422D50();
                    }
                }
            }
            else if ((field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX) && Input().IsAnyPressed(sInputKey_Right_4C6590)) || (!field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX) && Input().IsAnyPressed(sInputKey_Left_4C6594)))
            {
                field_2A8_flags.Set(Flags_2A8::e2A8_Bit2_return_to_previous_motion);
                mPreviousMotion = eAbeMotions::Motion_28_RunTurn_425CE0;
                mBaseAliveGameObjectLastAnimFrame = field_10_anim.field_92_current_frame;
            }
        }
    }
}

void Abe::Motion_28_RunTurn_425CE0()
{
    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
    {
        ToKnockback_422D90(1, 1);
    }
    else
    {
        MoveWithVelocity_4257F0(FP_FromDouble(0.375));
        if (mCurrentMotion == eAbeMotions::Motion_28_RunTurn_425CE0
            && !RunTryEnterWell_425880()
            && !RunTryEnterDoor_4259C0())
        {
            if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                MapFollowMe_401D30(TRUE);

                const FP gridSize = ScaleToGridSize(field_BC_sprite_scale);
                if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    if (Input().IsAnyPressed(sInputKey_Run_4C65A8))
                    {
                        field_B4_velx = gridSize / FP_FromInteger(4);
                        mCurrentMotion = eAbeMotions::Motion_54_RunTurnToRun_425EA0;
                    }
                    else
                    {
                        field_B4_velx = gridSize / FP_FromInteger(9);
                        mCurrentMotion = eAbeMotions::Motion_55_RunTurnToWalk_425F70;
                    }
                }
                else
                {
                    FP velX = {};
                    if (Input().IsAnyPressed(sInputKey_Run_4C65A8))
                    {
                        velX = gridSize / FP_FromInteger(4);
                        mCurrentMotion = eAbeMotions::Motion_54_RunTurnToRun_425EA0;
                    }
                    else
                    {
                        velX = gridSize / FP_FromInteger(9);
                        mCurrentMotion = eAbeMotions::Motion_55_RunTurnToWalk_425F70;
                    }
                    field_B4_velx = -velX;
                }
            }
        }
    }
}

void Abe::Motion_29_HopBegin_4267B0()
{
    FollowLift_42EE90();

    if (field_10_anim.field_92_current_frame == 9)
    {
        const FP velX = field_BC_sprite_scale * (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX) ? FP_FromInteger(-17) : FP_FromInteger(17));
        field_B4_velx = velX;

        if (!field_1A0_portal)
        {
            if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
            {
                Event_Broadcast(kEventNoise, this);
                Event_Broadcast(kEventSuspiciousNoise, this);
                field_B4_velx = FP_FromInteger(0);
                ToKnockback_422D90(1, 1);
                return;
            }
        }
        mBaseAnimatedWithPhysicsGameObject_XPos += field_B4_velx;
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        BaseAliveGameObjectLastLineYPos = mBaseAnimatedWithPhysicsGameObject_YPos;
        const FP velX = field_BC_sprite_scale * (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX) ? FP_FromDouble(-13.57) : FP_FromDouble(13.57));
        field_B4_velx = velX;
        mBaseAnimatedWithPhysicsGameObject_XPos += velX;

        const FP velY = field_BC_sprite_scale * FP_FromDouble(-2.7);
        field_B8_vely = velY;
        mBaseAnimatedWithPhysicsGameObject_YPos += velY;

        VOnTrapDoorOpen();

        mCurrentMotion = eAbeMotions::Motion_30_HopMid_4264D0;
        BaseAliveGameObjectCollisionLine = nullptr;

        if (!field_1A0_portal)
        {
            field_1A0_portal = IntoBirdPortal_402350(2);
            if (field_1A0_portal)
            {
                if (field_1A0_portal->field_10_portal_type != PortalType::eAbe_0)
                {
                    field_1A0_portal = nullptr;
                }
            }

            if (field_1A0_portal)
            {
                field_19E_portal_sub_state = PortalSubStates::eJumpingInsidePortal_0;
            }
        }
    }
}

void Abe::IntoPortalStates_4262A0()
{
    switch (field_19E_portal_sub_state)
    {
        case PortalSubStates::eJumpingInsidePortal_0:
        {
            PSX_RECT bRect = {};
            VGetBoundingRect(&bRect, 1);

            if ((field_B4_velx > FP_FromInteger(0) && FP_FromInteger(bRect.x) > field_1A0_portal->field_18_xpos) || (field_B4_velx < FP_FromInteger(0) && FP_FromInteger(bRect.w) < field_1A0_portal->field_18_xpos))
            {
                field_10_anim.mAnimFlags.Clear(AnimFlags::eBit3_Render);
                field_B8_vely = FP_FromInteger(0);
                field_B4_velx = FP_FromInteger(0);
                field_1A0_portal->VKillPortalClipper();
                field_1A0_portal->VGiveShrykull(TRUE);
                field_19E_portal_sub_state = PortalSubStates::eSetNewActiveCamera_1;
            }
            field_B8_vely += field_BC_sprite_scale * FP_FromDouble(1.8);
            mBaseAnimatedWithPhysicsGameObject_XPos += field_B4_velx;
            mBaseAnimatedWithPhysicsGameObject_YPos += field_B8_vely;
            return;
        }
        case PortalSubStates::eSetNewActiveCamera_1:
        {
            if (field_1A0_portal->VStateIs16())
            {
                EReliveLevelIds level = {};
                u16 path = 0;
                u16 camera = 0;
                CameraSwapEffects screenChangeEffect = {};
                u16 movieId = 0;
                field_1A0_portal->VGetMapChange(&level, &path, &camera, &screenChangeEffect, &movieId);
                gMap.SetActiveCam(level, path, camera, screenChangeEffect, movieId, FALSE);
                field_19E_portal_sub_state = PortalSubStates::eSetNewAbePosition_4;
            }
            break;
        }
        case PortalSubStates::eHopOutOfPortal_2:
        {
            if (field_1A0_portal->VStateIs20())
            {
                field_1A0_portal->VPortalClipper(0);
                field_10_anim.mAnimFlags.Set(AnimFlags::eBit3_Render);
                mCurrentMotion = eAbeMotions::Motion_29_HopBegin_4267B0;
                field_1A0_portal->VIncreaseTimerAndKillPortalClipper();
                field_1A0_portal = 0;
            }
            break;
        }
        case PortalSubStates::eSetNewAbePosition_4:
        {
            field_1A0_portal->VExitPortal();
            field_19E_portal_sub_state = PortalSubStates::eHopOutOfPortal_2;
            field_10_anim.mAnimFlags.Set(AnimFlags::eBit5_FlipX, field_1A0_portal->field_12_side == PortalSide::eLeft_1);

            if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
            {
                mBaseAnimatedWithPhysicsGameObject_XPos = ScaleToGridSize(field_BC_sprite_scale) + field_1A0_portal->field_20_exit_x;
            }
            else
            {
                mBaseAnimatedWithPhysicsGameObject_XPos = field_1A0_portal->field_20_exit_x - ScaleToGridSize(field_BC_sprite_scale);
            }

            mBaseAnimatedWithPhysicsGameObject_YPos = field_1A0_portal->field_24_exit_y;
            field_B8_vely = FP_FromInteger(0);
            field_120_x_vel_slow_by = FP_FromInteger(0);
            break;
        }
        default:
            return;
    }
}

void Abe::Motion_30_HopMid_4264D0()
{
    if (field_1A0_portal)
    {
        IntoPortalStates_4262A0();
    }
    else
    {
        if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
        {
            Event_Broadcast(kEventNoise, this);
            Event_Broadcast(kEventSuspiciousNoise, this);
            if (gMap.TLV_Get_At_446260(
                    FP_GetExponent(field_B4_velx + mBaseAnimatedWithPhysicsGameObject_XPos),
                    FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos - field_BC_sprite_scale * FP_FromInteger(50)),
                    FP_GetExponent(field_B4_velx + mBaseAnimatedWithPhysicsGameObject_XPos),
                    FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos - field_BC_sprite_scale * FP_FromInteger(50)),
                    TlvTypes::ElumStart_38))
            {
                SFX_Play_Mono(SoundEffect::RingBellHammer_9, 0, 0);
            }
            mNextMotion = eAbeMotions::Motion_0_Idle_423520;
            ToKnockback_422D90(1, 1);
        }
        else
        {
            PathLine* pLine = nullptr;
            FP hitX = {};
            FP hitY = {};

            // this has to be called before SetActiveCameraDelayedFromDir_401C90,
            // due to both of them modifying the same private fields in a fixed order
            Bool32 hasCollidedWithAir = InAirCollision_4019C0(&pLine, &hitX, &hitY, FP_FromDouble(1.80));

            SetActiveCameraDelayedFromDir_401C90();

            if (hasCollidedWithAir)
            {
                Event_Broadcast(kEventNoise, this);
                Event_Broadcast(kEventSuspiciousNoise, this);
                switch (pLine->field_8_type)
                {
                    case eLineTypes::eFloor_0:
                    case eLineTypes::eBackgroundFloor_4:
                    case eLineTypes::eUnknown_32:
                    case eLineTypes::eUnknown_36:
                    {
                        Environment_SFX_42A220(EnvironmentSfx::eHitGroundSoft_6, 0, 0x7FFF, this);
                        BaseAliveGameObjectCollisionLine = pLine;
                        field_B8_vely = FP_FromInteger(0);
                        mCurrentMotion = eAbeMotions::Motion_31_HopLand_426940;

                        PSX_RECT rect = {};
                        VGetBoundingRect(&rect, 1);
                        rect.y += 5;
                        rect.h += 5;

                        VOnCollisionWith(
                            {rect.x, rect.y},
                            {rect.w, rect.h},
                            ObjListPlatforms_50766C,
                            1,
                            (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection_401C10);
                        mBaseAnimatedWithPhysicsGameObject_XPos = hitX;
                        mBaseAnimatedWithPhysicsGameObject_YPos = hitY;
                        field_B4_velx = FP_FromInteger(0);
                        MapFollowMe_401D30(1);
                        mNextMotion = eAbeMotions::Motion_0_Idle_423520;
                        return;
                    }
                    default:
                        break;
                }
            }
            if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                if (mCurrentMotion == eAbeMotions::Motion_30_HopMid_4264D0)
                {
                    field_B4_velx = FP_FromRaw(field_B4_velx.fpValue / 2);
                    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                    {
                        mBaseAnimatedWithPhysicsGameObject_XPos += field_BC_sprite_scale * FP_FromInteger(5);
                    }
                    else
                    {
                        mBaseAnimatedWithPhysicsGameObject_XPos -= field_BC_sprite_scale * FP_FromInteger(5);
                    }
                    field_120_x_vel_slow_by = FP_FromDouble(0.55);
                    mBaseAnimatedWithPhysicsGameObject_YPos += field_BC_sprite_scale * FP_FromInteger(2);
                    mCurrentMotion = eAbeMotions::Motion_96_HopToFall_4298A0;
                    mNextMotion = eAbeMotions::Motion_0_Idle_423520;
                }
            }
        }
    }
}

void Abe::Motion_31_HopLand_426940()
{
    FollowLift_42EE90();

    if (field_10_anim.field_92_current_frame == 2 && Input().IsAnyPressed(sInputKey_Hop_4C65A0))
    {
        field_2A8_flags.Set(Flags_2A8::e2A8_Bit2_return_to_previous_motion);
        mPreviousMotion = eAbeMotions::Motion_29_HopBegin_4267B0;
        mBaseAliveGameObjectLastAnimFrame = 5;
    }
    else
    {
        if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            if (!ToLeftRightMovement_422AA0())
            {
                ToIdle_422D50();
            }
        }
    }
}

void Abe::Motion_32_RunJumpBegin_427440()
{
    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
    {
        ToKnockback_422D90(1, 1);
    }
    else
    {
        FollowLift_42EE90();

        mBaseAnimatedWithPhysicsGameObject_XPos += field_B4_velx;
        if (field_10_anim.field_92_current_frame == 0)
        {
            Environment_SFX_42A220(EnvironmentSfx::eRunJumpOrLedgeHoist_11, 0, 0x7FFF, this);
        }

        if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            BaseAliveGameObjectLastLineYPos = mBaseAnimatedWithPhysicsGameObject_YPos;

            if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
            {
                field_B4_velx = (field_BC_sprite_scale * FP_FromDouble(-7.6));
            }
            else
            {
                field_B4_velx = (field_BC_sprite_scale * FP_FromDouble(7.6));
            }

            field_B8_vely = (field_BC_sprite_scale * FP_FromDouble(-9.6));
            mBaseAnimatedWithPhysicsGameObject_YPos += field_B8_vely;
            VOnTrapDoorOpen();
            mCurrentMotion = eAbeMotions::Motion_33_RunJumpMid_426FA0;
            BaseAliveGameObjectCollisionLine = nullptr;
        }
    }
}

void Abe::Motion_33_RunJumpMid_426FA0()
{
    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (field_1A0_portal)
    {
        IntoPortalStates_4262A0();
        return;
    }
    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
    {
        if (gMap.TLV_Get_At_446260(
                FP_GetExponent(field_B4_velx + mBaseAnimatedWithPhysicsGameObject_XPos),
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos - field_BC_sprite_scale * FP_FromInteger(50)),
                FP_GetExponent(field_B4_velx + mBaseAnimatedWithPhysicsGameObject_XPos),
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos - field_BC_sprite_scale * FP_FromInteger(50)),
                TlvTypes::ElumStart_38))
        {
            SFX_Play_Mono(SoundEffect::RingBellHammer_9, 0, 0);
        }
        mNextMotion = eAbeMotions::Motion_0_Idle_423520;
        ToKnockback_422D90(1, 1);
        return;
    }

    FP hitX = {};
    FP hitY = {};
    PathLine* pLine = nullptr;
    auto bCollision = InAirCollision_4019C0(&pLine, &hitX, &hitY, FP_FromDouble(1.8));

    SetActiveCameraDelayedFromDir_401C90();

    if (bCollision)
    {
        switch (pLine->field_8_type)
        {
            case eLineTypes::eFloor_0:
            case eLineTypes::eBackgroundFloor_4:
            case eLineTypes::eUnknown_32:
            case eLineTypes::eUnknown_36:
            {
                BaseAliveGameObjectCollisionLine = pLine;
                mCurrentMotion = eAbeMotions::Motion_34_RunJumpLand_427560;
                mBaseAnimatedWithPhysicsGameObject_XPos = hitX;
                mBaseAnimatedWithPhysicsGameObject_YPos = hitY;

                PSX_RECT rect = {};
                VGetBoundingRect(&rect, 1);
                rect.y += 5;
                rect.h += 5;

                if (pLine->field_8_type == eLineTypes::eUnknown_32)
                {
                    VOnCollisionWith(
                        {rect.x, rect.y},
                        {rect.w, rect.h},
                        ObjListPlatforms_50766C,
                        1,
                        (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection_401C10);
                }
                mNextMotion = eAbeMotions::Motion_0_Idle_423520;
                return;
            }
        }
    }
    else
    {
        auto pHoist = static_cast<Path_Hoist*>(gMap.TLV_Get_At_446260(
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos - field_B4_velx),
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos - field_B4_velx),
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
            TlvTypes::Hoist_3));

        bool checkCollision = false;
        if (pHoist)
        {
            BaseAliveGameObjectPathTLV = pHoist;

            if (IsSameScaleAsHoist(pHoist, this) && (IsFacingSameDirectionAsHoist(pHoist, this)) && pHoist->field_18_hoist_type != Path_Hoist::Type::eOffScreen)
            {
                checkCollision = true;
            }
        }
        else
        {
            auto pEdgeTlv = static_cast<Path_Edge*>(gMap.TLV_Get_At_446260(
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos - field_B4_velx),
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos - field_B4_velx),
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                TlvTypes::Edge_4));
            BaseAliveGameObjectPathTLV = pEdgeTlv;
            if (pEdgeTlv && pEdgeTlv->field_1A_can_grab == Choice_short::eYes_1)
            {
                if (isEdgeGrabbable(pEdgeTlv, this))
                {
                    checkCollision = true;
                }
            }
        }
        if (checkCollision)
        {
            if (sCollisions->RayCast(
                    mBaseAnimatedWithPhysicsGameObject_XPos,
                    mBaseAnimatedWithPhysicsGameObject_YPos - field_BC_sprite_scale * FP_FromInteger(100),
                    mBaseAnimatedWithPhysicsGameObject_XPos,
                    mBaseAnimatedWithPhysicsGameObject_YPos,
                    &pLine,
                    &hitX,
                    &hitY,
                    field_BC_sprite_scale != FP_FromDouble(0.5) ? 1 : 16))
            {
                mBaseAnimatedWithPhysicsGameObject_XPos = FP_FromInteger(
                    (BaseAliveGameObjectPathTLV->field_14_bottom_right.field_0_x + BaseAliveGameObjectPathTLV->field_10_top_left.field_0_x) / 2);
                MapFollowMe_401D30(TRUE);
                mBaseAnimatedWithPhysicsGameObject_YPos = hitY;
                mCurrentMotion = eAbeMotions::Motion_68_LedgeHangWobble_428E50;
                field_D0_pShadow->field_14_flags.Set(Shadow::Flags::eBit1_ShadowAtBottom);
                BaseAliveGameObjectCollisionLine = pLine;
                field_B4_velx = FP_FromInteger(0);
                field_B8_vely = FP_FromInteger(0);
                mNextMotion = eAbeMotions::Motion_0_Idle_423520;
                if (!mLiftPoint)
                {
                    if (pLine->field_8_type == eLineTypes ::eUnknown_32 ||
                        pLine->field_8_type == eLineTypes::eUnknown_36)
                    {
                        PSX_RECT rect = {};
                        VGetBoundingRect(&rect, 1);
                        rect.y += 5;
                        rect.h += 5;

                        VOnCollisionWith(
                            {rect.x, rect.y},
                            {rect.w, rect.h},
                            ObjListPlatforms_50766C,
                            1,
                            (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection_401C10);
                    }
                }
            }
        }
        else
        {
            BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446060(
                nullptr,
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos,
                mBaseAnimatedWithPhysicsGameObject_XPos,
                mBaseAnimatedWithPhysicsGameObject_YPos);
        }
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (mCurrentMotion == eAbeMotions::Motion_33_RunJumpMid_426FA0)
        {
            field_120_x_vel_slow_by = FP_FromDouble(0.75);
            mCurrentMotion = eAbeMotions::Motion_97_RunJumpToFall_429930;
            mNextMotion = eAbeMotions::Motion_0_Idle_423520;
        }
    }
}

void Abe::Motion_34_RunJumpLand_427560()
{
    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        Environment_SFX_42A220(EnvironmentSfx::eHitGroundSoft_6, 0, 0x7FFF, this);
        MapFollowMe_401D30(1);

        if (Input().IsAnyPressed(sInputKey_Left_4C6594))
        {
            if (!(sInputKey_Hop_4C65A0 & field_10C_prev_held))
            {
                if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    if (Input().IsAnyPressed(sInputKey_Run_4C65A8))
                    {
                        mCurrentMotion = eAbeMotions::Motion_56_RunJumpLandRun_4278E0;
                        field_B4_velx = -(ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(4));
                    }
                    else
                    {
                        if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), -ScaleToGridSize(field_BC_sprite_scale)))
                        {
                            mCurrentMotion = eAbeMotions::Motion_27_RunSlideStop_425B60;
                            field_B4_velx = -(ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(4));
                        }
                        else
                        {
                            mCurrentMotion = eAbeMotions::Motion_57_RunJumpLand_Walk_427980;
                            field_B4_velx = -(ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(9));
                        }
                    }
                    return;
                }

                mCurrentMotion = eAbeMotions::Motion_28_RunTurn_425CE0;
                field_B4_velx = (ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(4));
                Environment_SFX_42A220(EnvironmentSfx::eRunSlide_4, 0, 0x7FFF, this);
                return;
            }

            field_1A0_portal = IntoBirdPortal_402350(3);
            if (field_1A0_portal)
            {
                if (field_1A0_portal->field_10_portal_type != PortalType::eAbe_0)
                {
                    field_1A0_portal = nullptr;
                }
            }

            if (field_1A0_portal)
            {
                field_19E_portal_sub_state = PortalSubStates::eJumpingInsidePortal_0;
            }

            mCurrentMotion = eAbeMotions::Motion_32_RunJumpBegin_427440;
            field_10C_prev_held = 0;
            return;
        }

        if (Input().IsAnyPressed(sInputKey_Right_4C6590))
        {
            if (sInputKey_Hop_4C65A0 & field_10C_prev_held)
            {
                field_1A0_portal = IntoBirdPortal_402350(3);
                if (field_1A0_portal)
                {
                    if (field_1A0_portal->field_10_portal_type != PortalType::eAbe_0)
                    {
                        field_1A0_portal = nullptr;
                    }
                }

                if (field_1A0_portal)
                {
                    field_19E_portal_sub_state = PortalSubStates::eJumpingInsidePortal_0;
                }

                mCurrentMotion = eAbeMotions::Motion_32_RunJumpBegin_427440;
                field_10C_prev_held = 0;
                return;
            }

            if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
            {
                mCurrentMotion = eAbeMotions::Motion_28_RunTurn_425CE0;
                Environment_SFX_42A220(EnvironmentSfx::eRunSlide_4, 0, 0x7FFF, this);
                return;
            }

            if (Input().IsAnyPressed(sInputKey_Run_4C65A8))
            {
                field_B4_velx = (ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(4));
                mCurrentMotion = eAbeMotions::Motion_56_RunJumpLandRun_4278E0;
            }
            else
            {
                if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), ScaleToGridSize(field_BC_sprite_scale)))
                {
                    mCurrentMotion = eAbeMotions::Motion_27_RunSlideStop_425B60;
                    field_B4_velx = (ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(4));
                }
                else
                {
                    field_B4_velx = (ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(9));
                    mCurrentMotion = eAbeMotions::Motion_57_RunJumpLand_Walk_427980;
                }
            }
        }
        else
        {
            if (!(sInputKey_Hop_4C65A0 & field_10C_prev_held))
            {
                mCurrentMotion = eAbeMotions::Motion_27_RunSlideStop_425B60;
                if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    field_B4_velx = -(ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(4));
                    Environment_SFX_42A220(EnvironmentSfx::eRunSlide_4, 0, 0x7FFF, this);
                }
                else
                {
                    field_B4_velx = (ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(4));
                    Environment_SFX_42A220(EnvironmentSfx::eRunSlide_4, 0, 0x7FFF, this);
                }
                return;
            }

            field_1A0_portal = IntoBirdPortal_402350(3);
            if (field_1A0_portal)
            {
                if (field_1A0_portal->field_10_portal_type != PortalType::eAbe_0)
                {
                    field_1A0_portal = nullptr;
                }
            }

            if (field_1A0_portal)
            {
                field_19E_portal_sub_state = PortalSubStates::eJumpingInsidePortal_0;
            }

            mCurrentMotion = eAbeMotions::Motion_29_HopBegin_4267B0;
            field_10C_prev_held = 0;
        }
    }
}

bool Abe::CheckForPortalAndRunJump()
{
    if (field_10C_prev_held & sInputKey_Hop_4C65A0)
    {
        field_1A0_portal = IntoBirdPortal_402350(3);
        if (field_1A0_portal)
        {
            if (field_1A0_portal->field_10_portal_type != PortalType::eAbe_0)
            {
                field_1A0_portal = nullptr;
            }
            else
            {
                field_19E_portal_sub_state = PortalSubStates::eJumpingInsidePortal_0;
            }
        }

        mCurrentMotion = eAbeMotions::Motion_32_RunJumpBegin_427440;
        field_10C_prev_held = 0;
        return true;
    }
    return false;
}

void Abe::Motion_35_RunLoop_425060()
{
    field_10C_prev_held |= Input().Pressed();

    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
    {
        ToKnockback_422D90(1, 1);
        return;
    }

    MoveForward_422FC0();

    if (mCurrentMotion != eAbeMotions::Motion_35_RunLoop_425060)
    {
        return;
    }

    if (field_10_anim.field_92_current_frame == 0 || field_10_anim.field_92_current_frame == 8)
    {
        if (!field_2A8_flags.Get(e2A8_Bit3_WalkToRun))
        {
            field_2A8_flags.Set(e2A8_Bit3_WalkToRun);
            MapFollowMe_401D30(TRUE);
        }

        CheckForPortalAndRunJump();
    }
    else if (field_10_anim.field_92_current_frame == 4 || field_10_anim.field_92_current_frame == 12)
    {
        Environment_SFX_42A220(EnvironmentSfx::eRunningFootstep_2, 0, 0x7FFF, this);

        // Snap
        if (!field_2A8_flags.Get(e2A8_Bit3_WalkToRun))
        {
            field_2A8_flags.Set(e2A8_Bit3_WalkToRun);
            MapFollowMe_401D30(TRUE);
        }

        // Check turning in middle of run (pressing reverse direction of movement)
        if ((field_B4_velx > FP_FromInteger(0) && Input().IsAnyPressed(sInputKey_Left_4C6594)) || (field_B4_velx < FP_FromInteger(0) && Input().IsAnyPressed(sInputKey_Right_4C6590)))
        {
            mCurrentMotion = eAbeMotions::Motion_28_RunTurn_425CE0;
            Environment_SFX_42A220(EnvironmentSfx::eRunSlide_4, 0, 0x7FFF, this);
            field_10C_prev_held = 0;
            return;
        }

        // Check jumping into a portal
        if (CheckForPortalAndRunJump())
        {
            return;
        }

        // Running to roll
        if (field_10C_prev_held & sInputKey_FartRoll_4C65B0)
        {
            mCurrentMotion = eAbeMotions::Motion_40_RunToRoll_427AE0;

            // For some reason dont clear released in the frame 12 case
            if (field_10_anim.field_92_current_frame == 4)
            {
                field_10E_released_buttons = 0;
            }
            field_10C_prev_held = 0;
            return;
        }

        // No longer running
        if (!Input().IsAnyPressed(sInputKey_Right_4C6590) && !Input().IsAnyPressed(sInputKey_Left_4C6594))
        {
            mCurrentMotion = eAbeMotions::Motion_27_RunSlideStop_425B60;
            Environment_SFX_42A220(EnvironmentSfx::eRunSlide_4, 0, 0x7FFF, this);
            field_10C_prev_held = 0;
            return;
        }

        // Continue running
        if (Input().IsAnyPressed(sInputKey_Run_4C65A8))
        {
            field_10C_prev_held = 0;
            return;
        }

        // Stop running
        FP gridSize = {};
        if (field_B4_velx >= FP_FromInteger(0))
        {
            gridSize = ScaleToGridSize(field_BC_sprite_scale);
        }
        else
        {
            gridSize = -ScaleToGridSize(field_BC_sprite_scale);
        }

        if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), gridSize))
        {
            ToKnockback_422D90(1, 1);
        }
        else
        {
            if (field_10_anim.field_92_current_frame == 4)
            {
                mCurrentMotion = eAbeMotions::Motion_52_RunToWalk_4255E0;
            }
            else
            {
                mCurrentMotion = eAbeMotions::Motion_53_MidRunToWalk_4256E0;
            }
        }

        field_10C_prev_held = 0;
    }
    else
    {
        field_2A8_flags.Clear(e2A8_Bit3_WalkToRun);
    }
}

void Abe::Motion_36_DunnoBegin_423260()
{
    FollowLift_42EE90();

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        Mudokon_SFX_42A4D0(MudSounds::eDunno_15, 0, 0, this);

        if (Input().IsAnyPressed(sInputKey_DoAction_4C65A4 | sInputKey_ThrowItem_4C65B4))
        {
            mCurrentMotion = eAbeMotions::Motion_37_DunnoMid_4232C0;
        }
        else
        {
            mCurrentMotion = eAbeMotions::Motion_38_DunnoEnd_423310;
        }
    }
}

void Abe::Motion_37_DunnoMid_4232C0()
{
    FollowLift_42EE90();

    if (!Input().IsAnyPressed(sInputKey_DoAction_4C65A4 | sInputKey_ThrowItem_4C65B4) || field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_38_DunnoEnd_423310;
    }
}

void Abe::Motion_38_DunnoEnd_423310()
{
    FollowLift_42EE90();

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_39_CrouchTurn_4288C0()
{
    FollowLift_42EE90();

    if (field_10_anim.field_92_current_frame)
    {
        if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            field_10_anim.mAnimFlags.Toggle(AnimFlags::eBit5_FlipX);

            if (mNextMotion == eAbeMotions::Motion_0_Idle_423520)
            {
                mCurrentMotion = eAbeMotions::Motion_19_CrouchIdle_4284C0;
            }
            else
            {
                mCurrentMotion = mNextMotion;
                mNextMotion = 0;
            }
        }
    }
    else
    {
        Environment_SFX_42A220(EnvironmentSfx::eGenericMovement_9, 0, 0x7FFF, this);
    }
}

void Abe::Motion_40_RunToRoll_427AE0()
{
    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        field_B4_velx = -(ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(4));
    }
    else
    {
        field_B4_velx = (ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(4));
    }

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(20), field_B4_velx))
    {
        ToKnockback_422D90(1, 1);
        mCurrentMotion = eAbeMotions::Motion_73_RollingKnockback_4291D0;
    }
    else
    {
        MoveForward_422FC0();

        if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            if (mCurrentMotion == eAbeMotions::Motion_40_RunToRoll_427AE0)
            {
                mCurrentMotion = eAbeMotions::Motion_25_RollLoop_427BB0;
            }
        }
    }
}

void Abe::Motion_41_StandingToRun_425530()
{
    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_35_RunLoop_425060;
    }

    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    field_10C_prev_held |= Input().Pressed();

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
    {
        ToIdle_422D50();
    }
    else
    {
        MoveForward_422FC0();
    }
}

void Abe::Motion_42_SneakLoop_424BB0()
{
    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
    {
        ToIdle_422D50();
        MapFollowMe_401D30(1);
        return;
    }

    MoveForward_422FC0();

    if (mCurrentMotion == eAbeMotions::Motion_42_SneakLoop_424BB0)
    {
        if (field_10_anim.field_92_current_frame == 3)
        {
            FP directedScale = {};
            if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
            {
                directedScale = -ScaleToGridSize(field_BC_sprite_scale);
            }
            else
            {
                directedScale = ScaleToGridSize(field_BC_sprite_scale);
            }

            if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), directedScale) || (field_B4_velx > FP_FromInteger(0) && Input().IsAnyPressed(sInputKey_Left_4C6594)) || (field_B4_velx < FP_FromInteger(0) && Input().IsAnyPressed(sInputKey_Right_4C6590)) || !Input().IsAnyPressed(sInputKey_Right_4C6590 | sInputKey_Left_4C6594))
            {
                mCurrentMotion = eAbeMotions::Motion_48_SneakToIdle_424F80;
            }
            return;
        }

        if (field_10_anim.field_92_current_frame == 6)
        {
            Environment_SFX_42A220(EnvironmentSfx::eSneakFootstep_3, 0, 0x7FFF, this);
            MapFollowMe_401D30(1);

            if (Input().IsAnyPressed(sInputKey_Right_4C6590 | sInputKey_Left_4C6594) && !Input().IsAnyPressed(sInputKey_Sneak_4C65AC))
            {
                mCurrentMotion = eAbeMotions::Motion_44_SneakToWalk_4249A0;
                field_10C_prev_held = 0;
                return;
            }

            field_10C_prev_held = 0;
            return;
        }

        if (field_10_anim.field_92_current_frame != 13)
        {
            if (field_10_anim.field_92_current_frame != 16)
            {
                return;
            }

            Environment_SFX_42A220(EnvironmentSfx::eSneakFootstep_3, 0, 0x7FFF, this);
            MapFollowMe_401D30(1);

            if (Input().IsAnyPressed(sInputKey_Right_4C6590 | sInputKey_Left_4C6594))
            {
                if (!Input().IsAnyPressed(sInputKey_Sneak_4C65AC))
                {
                    mCurrentMotion = eAbeMotions::Motion_46_MidSneakToWalk_424AA0;
                }
            }
            field_10C_prev_held = 0;
            return;
        }

        FP directedScale = {};
        if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
        {
            directedScale = -ScaleToGridSize(field_BC_sprite_scale);
        }
        else
        {
            directedScale = ScaleToGridSize(field_BC_sprite_scale);
        }

        if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), directedScale) || (field_B4_velx > FP_FromInteger(0) && Input().IsAnyPressed(sInputKey_Left_4C6594)) || (field_B4_velx < FP_FromInteger(0) && Input().IsAnyPressed(sInputKey_Right_4C6590)) || !Input().IsAnyPressed(sInputKey_Right_4C6590 | sInputKey_Left_4C6594))
        {
            mCurrentMotion = eAbeMotions::Motion_49_MidSneakToIdle_424FF0;
        }
    }
}

void Abe::Motion_43_WalkToSneak_424790()
{
    field_10C_prev_held |= Input().Pressed();

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        field_B4_velx = -(ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(10));
    }
    else
    {
        field_B4_velx = (ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(10));
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_42_SneakLoop_424BB0;
    }

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
    {
        ToIdle_422D50();
        MapFollowMe_401D30(1);
    }
    else
    {
        MoveForward_422FC0();
    }
}

void Abe::Motion_44_SneakToWalk_4249A0()
{
    field_10C_prev_held |= Input().Pressed();

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        field_B4_velx = -(ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(9));
    }
    else
    {
        field_B4_velx = (ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(9));
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_1_WalkLoop_423F90;
    }

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
    {
        ToIdle_422D50();
        MapFollowMe_401D30(1);
    }
    else
    {
        MoveForward_422FC0();
    }
}

void Abe::Motion_45_MidWalkToSneak_424890()
{
    field_10C_prev_held |= Input().Pressed();

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        field_B4_velx = -(ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(10));
    }
    else
    {
        field_B4_velx = (ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(10));
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_2A8_flags.Set(Flags_2A8::e2A8_Bit2_return_to_previous_motion);
        mPreviousMotion = 42;
        mBaseAliveGameObjectLastAnimFrame = 10;
    }

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
    {
        ToIdle_422D50();
        MapFollowMe_401D30(1);
    }
    else
    {
        MoveForward_422FC0();
    }
}

void Abe::Motion_46_MidSneakToWalk_424AA0()
{
    field_10C_prev_held |= Input().Pressed();

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        field_B4_velx = -(ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(9));
    }
    else
    {
        field_B4_velx = (ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(9));
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_2A8_flags.Set(Flags_2A8::e2A8_Bit2_return_to_previous_motion);
        mPreviousMotion = 1;
        mBaseAliveGameObjectLastAnimFrame = 9;
    }

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
    {
        ToIdle_422D50();
        MapFollowMe_401D30(1);
    }
    else
    {
        MoveForward_422FC0();
    }
}

void Abe::Motion_47_SneakBegin_424ED0()
{
    field_10C_prev_held |= Input().Pressed();

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_42_SneakLoop_424BB0;
    }

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
    {
        ToIdle_422D50();
        MapFollowMe_401D30(1);
    }
    else
    {
        MoveForward_422FC0();
    }
}

void Abe::Motion_48_SneakToIdle_424F80()
{
    if (field_10_anim.field_92_current_frame == 0)
    {
        Environment_SFX_42A220(EnvironmentSfx::eSneakFootstep_3, 0, 0x7FFF, this);
    }

    MoveForward_422FC0();

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        MapFollowMe_401D30(1);
        ToIdle_422D50();
    }
}

void Abe::Motion_49_MidSneakToIdle_424FF0()
{
    if (!field_10_anim.field_92_current_frame)
    {
        Environment_SFX_42A220(EnvironmentSfx::eSneakFootstep_3, 0, 0x7FFF, this);
    }

    MoveForward_422FC0();

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        MapFollowMe_401D30(1);

        ToIdle_422D50();
    }
}

void Abe::Motion_50_WalkToRun_424560()
{
    field_10C_prev_held |= Input().Pressed();

    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        field_B4_velx = -(ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(4));
    }
    else
    {
        field_B4_velx = (ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(4));
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_35_RunLoop_425060;
        field_10C_prev_held = 0;
    }

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
    {
        ToIdle_422D50();
        MapFollowMe_401D30(1);
    }
    else
    {
        MoveForward_422FC0();
    }
}

void Abe::Motion_51_MidWalkToRun_424670()
{
    field_10C_prev_held |= Input().Pressed();

    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        field_B4_velx = -(ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(4));
    }
    else
    {
        field_B4_velx = (ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(4));
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_2A8_flags.Set(Flags_2A8::e2A8_Bit2_return_to_previous_motion);
        mPreviousMotion = 35;
        mBaseAliveGameObjectLastAnimFrame = 8;
    }

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
    {
        ToIdle_422D50();
        MapFollowMe_401D30(1);
    }
    else
    {
        MoveForward_422FC0();
    }
}

void Abe::Motion_52_RunToWalk_4255E0()
{
    field_10C_prev_held |= Input().Pressed();

    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        field_B4_velx = -(ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(9));
    }
    else
    {
        field_B4_velx = (ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(9));
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_1_WalkLoop_423F90;
    }

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
    {
        ToIdle_422D50();
    }
    else
    {
        MoveForward_422FC0();
    }
}

void Abe::Motion_53_MidRunToWalk_4256E0()
{
    field_10C_prev_held |= Input().Pressed();

    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        field_B4_velx = -(ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(9));
    }
    else
    {
        field_B4_velx = (ScaleToGridSize(field_BC_sprite_scale) / FP_FromInteger(9));
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_2A8_flags.Set(Flags_2A8::e2A8_Bit2_return_to_previous_motion);
        mPreviousMotion = 1;
        mBaseAliveGameObjectLastAnimFrame = 9;
    }

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
    {
        ToIdle_422D50();
    }
    else
    {
        MoveForward_422FC0();
    }
}

void Abe::Motion_54_RunTurnToRun_425EA0()
{
    field_10C_prev_held |= Input().Pressed();

    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
    {
        ToIdle_422D50();
    }
    else
    {
        MoveForward_422FC0();

        if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            mCurrentMotion = eAbeMotions::Motion_35_RunLoop_425060;
            field_10_anim.mAnimFlags.Toggle(AnimFlags::eBit5_FlipX);
        }
    }
}

void Abe::Motion_55_RunTurnToWalk_425F70()
{
    field_10C_prev_held |= Input().Pressed();

    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);


    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
    {
        ToIdle_422D50();
    }
    else
    {
        MoveForward_422FC0();

        if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            mCurrentMotion = eAbeMotions::Motion_1_WalkLoop_423F90;
            field_10_anim.mAnimFlags.Toggle(AnimFlags::eBit5_FlipX);
        }
    }
}

void Abe::Motion_56_RunJumpLandRun_4278E0()
{
    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
    {
        ToIdle_422D50();
    }
    else
    {
        MoveForward_422FC0();

        if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            mCurrentMotion = eAbeMotions::Motion_35_RunLoop_425060;
        }
    }
}

void Abe::Motion_57_RunJumpLand_Walk_427980()
{
    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
    {
        ToIdle_422D50();
    }
    else
    {
        MoveForward_422FC0();

        if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            mCurrentMotion = eAbeMotions::Motion_1_WalkLoop_423F90;
        }
    }
}

void Abe::Motion_58_ToSpeak_42F8D0()
{
    FollowLift_42EE90();

    field_10C_prev_held |= Input().Held();

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = DoGameSpeak_42F5C0(field_10C_prev_held);
        if (mCurrentMotion == -1)
        {
            ToIdle_422D50();
        }
        else
        {
            Event_Broadcast(kEventSpeaking, this);
        }
        field_10C_prev_held = 0;
    }
}

void Abe::Motion_59_DeathDropFall_42CBE0()
{
    field_10_anim.mAnimFlags.Clear(AnimFlags::eBit2_Animate);

    FollowLift_42EE90();

    if (field_114_gnFrame == 0)
    {
        field_120_x_vel_slow_by = FP_FromInteger(0);
        field_124_unused = 0;
        field_B4_velx = FP_FromInteger(0);
        field_B8_vely = FP_FromInteger(0);
        field_118_timer = sGnFrame + 90;
        field_114_gnFrame = 1;
    }
    else if (field_114_gnFrame == 1)
    {
        if (static_cast<s32>(sGnFrame) == field_118_timer - 30)
        {
            SND_SEQ_Play_477760(SeqId::eHitBottomOfDeathPit_10, 1, 65, 65);
        }
        else if (static_cast<s32>(sGnFrame) == field_118_timer - 24)
        {
            Environment_SFX_42A220(EnvironmentSfx::eFallingDeathScreamHitGround_15, 0, 0x7FFF, this);

            ao_new<ScreenShake>(true);
        }
        else if (static_cast<s32>(sGnFrame) >= field_118_timer)
        {
            field_2A8_flags.Set(Flags_2A8::e2A8_Bit6_bShrivel);
            mCurrentMotion = eAbeMotions::Motion_60_Dead_42C4C0;
            field_114_gnFrame = 0;
            mHealth = FP_FromInteger(0);
            MusicController::static_PlayMusic(MusicController::MusicTypes::eDeathLong_14, this, 1, 0);
        }
    }
}

void Abe::Motion_60_Dead_42C4C0()
{
    field_10_anim.mAnimFlags.Clear(AnimFlags::eBit2_Animate);
    FollowLift_42EE90();

    switch (field_114_gnFrame)
    {
        case 0:
        {
            Event_Broadcast(kEventHeroDying, this);
            field_118_timer = sGnFrame + 30;
            field_120_x_vel_slow_by = FP_FromInteger(0);
            field_124_unused = 0;
            field_B4_velx = FP_FromInteger(0);
            field_B8_vely = FP_FromInteger(0);
            field_10C_prev_held = 0;
            field_114_gnFrame++;

            auto aux = 0;
            if (BaseAliveGameObjectPathTLV && BaseAliveGameObjectPathTLV->field_4_type == TlvTypes::DeathDrop_5)
            {
                aux = 60;
            }
            else
            {
                aux = 15;
            }
            const FP ypos = FP_FromInteger(Math_NextRandom() % 10) + mBaseAnimatedWithPhysicsGameObject_YPos + FP_FromInteger(15);
            const FP xpos = FP_FromInteger(((Math_NextRandom() % 64) - 32)) + mBaseAnimatedWithPhysicsGameObject_XPos;
            ao_new<DeathBirdParticle>(
                xpos,
                ypos,
                (Math_NextRandom() % 8) + field_118_timer + aux,
                1,
                field_BC_sprite_scale);

            return;
        }
        case 1:
        {
            Event_Broadcast(kEventHeroDying, this);
            if (!(sGnFrame % 4))
            {
                auto aux = 0;
                if (BaseAliveGameObjectPathTLV && BaseAliveGameObjectPathTLV->field_4_type == TlvTypes::DeathDrop_5)
                {
                    aux = 60;
                }
                else
                {
                    aux = 15;
                }
                const FP ypos = FP_FromInteger(Math_NextRandom() % 10) + mBaseAnimatedWithPhysicsGameObject_YPos + FP_FromInteger(15);
                const FP xpos = FP_FromInteger(((Math_NextRandom() % 64) - 32)) + mBaseAnimatedWithPhysicsGameObject_XPos;
                ao_new<DeathBirdParticle>(
                    xpos,
                    ypos,
                    (Math_NextRandom() % 8) + field_118_timer + aux,
                    0,
                    field_BC_sprite_scale);
            }
            field_BC_sprite_scale -= FP_FromDouble(0.008);

            field_C0_r -= 2;
            field_C2_g -= 2;
            field_C4_b -= 2;
            if (static_cast<s32>(sGnFrame) > field_118_timer)
            {
                field_118_timer = sGnFrame + 60;
                if (BaseAliveGameObjectPathTLV)
                {
                    if (BaseAliveGameObjectPathTLV->field_4_type == TlvTypes::DeathDrop_5)
                    {
                        field_118_timer = (sGnFrame + 60) + 45;
                    }
                }
                field_114_gnFrame++;
                MusicController::static_PlayMusic(MusicController::MusicTypes::eDeathLong_14, this, 1, 0);
            }
            return;
        }
        case 2:
        {
            Event_Broadcast(kEventHeroDying, this);
            if (static_cast<s32>(sGnFrame) > field_118_timer)
            {
                field_114_gnFrame++;
            }
            return;
        }
        case 3:
        {
            Event_Broadcast(kEventHeroDying, this);
            if (field_158_pDeathFadeout)
            {
                field_158_pDeathFadeout->mBaseGameObjectFlags.Set(Options::eDead);
                field_158_pDeathFadeout->mBaseGameObjectRefCount--;
            }
            field_158_pDeathFadeout = ao_new<DeathFadeOut>(Layer::eLayer_FadeFlash_40, 1, 0, 8, TPageAbr::eBlend_2);
            field_158_pDeathFadeout->mBaseGameObjectRefCount++;

            if (field_164_pCircularFade)
            {
                field_164_pCircularFade->mBaseGameObjectFlags.Set(Options::eDead);
                field_164_pCircularFade = nullptr;
            }
            field_114_gnFrame++;
            return;
        }
        case 4:
        {
            Event_Broadcast(kEventHeroDying, this);
            if (field_158_pDeathFadeout->field_6E_bDone)
            {
                if (!field_104_pending_resource_count)
                {
                    VOnTrapDoorOpen();
                    BaseAliveGameObjectCollisionLine = nullptr;
                    if (gElum_507680)
                    {
                        if (!gElum_507680->field_144_bRespawnOnDead)
                        {
                            gElum_507680->mBaseGameObjectFlags.Set(Options::eDead);
                        }
                    }
                    if (!field_1A4_resources.res[0])
                    {
                        field_1A4_resources.res[0] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbebasicAOResID, 1, 0);
                        field_1A4_resources.res[10] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbefallAOResID, 1, 0);
                        field_1A4_resources.res[38] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeommAOResID, 1, 0);
                        field_1A4_resources.res[9] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbesmashAOResID, 1, 0);
                        field_1A4_resources.res[61] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAneprmntAOResID, 1, 0);
                        if (gElum_507680)
                        {
                            if (gElum_507680->field_144_bRespawnOnDead)
                            {
                                gElum_507680->VLoadUnmountedResources_411260();
                            }
                            else
                            {
                                ResourceManager::FreeResource_455550(
                                    ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAneprmntAOResID, 0, 0));
                            }
                        }
                    }
                    field_118_timer = sGnFrame + 8;
                    field_114_gnFrame++;
                    //todo never used? dword_507720 = 0;
                }
            }
            return;
        }
        case 5:
        {
            Event_Broadcast(kEventDeathReset, this);
            if (static_cast<s32>(sGnFrame) > field_118_timer)
            {
                mCurrentMotion = eAbeMotions::Motion_61_Respawn_42CD20;
                field_118_timer = sGnFrame + 2;
                field_114_gnFrame = 0;
                MusicController::static_PlayMusic(MusicController::MusicTypes::eType0, this, 1, 0);
                if (field_168_ring_pulse_timer && field_16C_bHaveShrykull)
                {
                    Abe::Free_Shrykull_Resources_42F4C0();
                }
                else if (field_144_saved_level != EReliveLevelIds::eRuptureFarmsReturn || field_142_saved_path != 6)
                {
                    field_168_ring_pulse_timer = 0;
                }
                field_130_say = -1;
                field_D0_pShadow->field_14_flags.Clear(Shadow::Flags::eBit2_Enabled);
            }
            return;
        }
        default:
            return;
    }
}

void Abe::Motion_61_Respawn_42CD20()
{
    // This will crash the game if abe didnt touch a checkpoint yet

    if (gAttract_507698)
    {
        // Depending on the randomn seed value abe can die in a demo, if so the checkpoint save will load
        // depending on the saved camera number on returning the main menu this can crash. Hack fix it
        // by killing abe so the bad save cant get loaded before we return to the menu.
        LOG_WARNING("Destroying abe to prevent game crash, he isnt supposed to die in a demo!");
        mBaseGameObjectFlags.Set(BaseGameObject::eDead);
        sActiveHero_507678 = nullptr;
        sControlledCharacter_50767C = nullptr;
        return;
    }

    field_10_anim.mAnimFlags.Clear(AnimFlags::eBit2_Animate);
    FollowLift_42EE90();
    Event_Broadcast(kEventResetting, this);

    // TODO: states
    switch (field_114_gnFrame)
    {
        case 0:
        {
            mHealth = FP_FromInteger(1);
            if (field_19C_throwable_count != 0)
            {
                if (gpThrowableArray_50E26C)
                {
                    gpThrowableArray_50E26C->Remove(field_19C_throwable_count);
                }
            }
            field_19C_throwable_count = 0;

            if (static_cast<s32>(sGnFrame) > field_118_timer)
            {
                if (mLiftPoint)
                {
                    if (mLiftPoint->mBaseGameObjectFlags.Get(Options::eDrawable_Bit4))
                    {
                        mLiftPoint->VRemove(this);
                        mLiftPoint->mBaseGameObjectRefCount--;
                        mLiftPoint = nullptr;
                    }
                }
                if (field_140_saved_camera > 300u)
                {
                    field_140_saved_camera = gMap.mCurrentCamera;
                    field_142_saved_path = gMap.mCurrentPath;
                    field_144_saved_level = gMap.mCurrentLevel;

                    PSX_Point camPos = {};
                    gMap.GetCurrentCamCoords(&camPos);
                    field_138_zone_top_left.field_0_x = camPos.field_0_x + 512;
                    field_138_zone_top_left.field_2_y = camPos.field_2_y + 240;
                }
                SaveGame::LoadFromMemory(&gSaveBuffer_505668, 0);
                if (field_19C_throwable_count)
                {
                    LoadRockTypes(MapWrapper::FromAO(gSaveBuffer_505668.field_234_current_level), gSaveBuffer_505668.field_236_current_path);
                    if (!gpThrowableArray_50E26C)
                    {
                        gpThrowableArray_50E26C = ao_new<ThrowableArray>();
                    }
                    gpThrowableArray_50E26C->Add(field_19C_throwable_count);
                }
                field_114_gnFrame = 1;
                mCurrentMotion = eAbeMotions::Motion_61_Respawn_42CD20;
            }
            break;
        }
        case 1:
        {
            field_B2_lvl_number = field_144_saved_level;
            field_B0_path_number = field_142_saved_path;
            mBaseAnimatedWithPhysicsGameObject_XPos = FP_FromInteger(field_138_zone_top_left.field_0_x);
            mBaseAnimatedWithPhysicsGameObject_YPos = FP_FromInteger(field_138_zone_top_left.field_2_y) + field_BC_sprite_scale * FP_FromInteger(30);

            BaseAliveGameObjectLastLineYPos = mBaseAnimatedWithPhysicsGameObject_YPos;

            field_10_anim.mAnimFlags.Set(AnimFlags::eBit5_FlipX, field_2A8_flags.Get(Flags_2A8::e2A8_eBit16_AbeSpawnDir));
            MapFollowMe_401D30(TRUE);
            SetTint_418750(sAbeTints_4C6438, gMap.mCurrentLevel);
            if (gElum_507680)
            {
                gElum_507680->field_BC_sprite_scale = field_BC_sprite_scale;
            }
            if (field_BC_sprite_scale == FP_FromDouble(0.5))
            {
                field_10_anim.mRenderLayer = Layer::eLayer_AbeMenu_Half_13;
                field_C6_scale = 0;
                if (gElum_507680)
                {
                    gElum_507680->field_10_anim.mRenderLayer = Layer::eLayer_ZapLinesElum_Half_9;
                    gElum_507680->field_C6_scale = 0;
                }
            }
            else
            {
                field_10_anim.mRenderLayer = Layer::eLayer_AbeMenu_32;
                field_C6_scale = 1;
                if (gElum_507680)
                {
                    gElum_507680->field_10_anim.mRenderLayer = Layer::eLayer_ZapLinesElum_28;
                    gElum_507680->field_C6_scale = 1;
                }
            }
            field_10_anim.mAnimFlags.Clear(AnimFlags::eBit3_Render);
            Event_Broadcast(kEventDeathResetEnd, this);

            //TODO not used?
            //if (dword_507720)
            //{
            //    *(_BYTE *) (dword_507720 + 6) |= 4u;
            //}
            mBaseAliveGameObjectFlags.Clear(Flags_10A::e10A_Bit5_Electrocuted);

            field_158_pDeathFadeout->Init(Layer::eLayer_FadeFlash_40, 0, 1, 8);
            field_158_pDeathFadeout->mBaseGameObjectRefCount--;
            field_158_pDeathFadeout = nullptr;
            mNextMotion = eAbeMotions::Motion_0_Idle_423520;
            field_118_timer = sGnFrame + 60;
            field_114_gnFrame = 2;
            break;
        }
        case 2:
        {
            if (static_cast<s32>(sGnFrame) > field_118_timer)
            {
                auto xDiff = pScreenManager_4FF7C8->field_10_pCamPos->field_0_x - FP_FromInteger(pScreenManager_4FF7C8->field_14_xpos);
                auto yDiff = pScreenManager_4FF7C8->field_10_pCamPos->field_4_y - FP_FromInteger(pScreenManager_4FF7C8->field_16_ypos);

                for (s32 i = 0; i < 8; i++)
                {
                    const AnimRecord& doveRec = AO::AnimRec(AnimId::Dove_Flying);
                    auto pDove = ao_new<Dove>(
                        doveRec.mFrameTableOffset,
                        doveRec.mMaxW,
                        doveRec.mMaxH,
                        doveRec.mResourceId,
                        xDiff + FP_FromInteger(Math_NextRandom() * 2),
                        yDiff - FP_FromInteger(Math_NextRandom() % 32),
                        field_BC_sprite_scale);
                    if (pDove)
                    {
                        pDove->AsJoin(
                            mBaseAnimatedWithPhysicsGameObject_XPos + FP_FromInteger((Math_NextRandom() % 16) - 8),
                            mBaseAnimatedWithPhysicsGameObject_YPos + FP_FromInteger((Math_NextRandom() % 16) - 20));
                        pDove->field_BC_sprite_scale = field_BC_sprite_scale;
                    }
                }
                SFX_Play_Mono(SoundEffect::RespawnDove_17, 0, this);
                field_118_timer = sGnFrame + 45;
                field_114_gnFrame = 3;
            }
            break;
        }
        case 3:
        {
            if (field_118_timer - sGnFrame == 10)
            {
                SFX_Play_Mono(SoundEffect::Respawn_22, 90, 0);
            }
            if (static_cast<s32>(sGnFrame) > field_118_timer)
            {
                New_DestroyOrCreateObject_Particle_419D00(
                    mBaseAnimatedWithPhysicsGameObject_XPos,
                    field_BC_sprite_scale * FP_FromInteger(25) + mBaseAnimatedWithPhysicsGameObject_YPos,
                    field_BC_sprite_scale);
                field_114_gnFrame = 4;
                field_118_timer = sGnFrame + 2;
            }
            break;
        }
        case 4:
        {
            if (static_cast<s32>(sGnFrame) > field_118_timer)
            {
                field_D0_pShadow->field_14_flags.Set(Shadow::Flags::eBit2_Enabled);
                field_D0_pShadow->field_14_flags.Clear(Shadow::Flags::eBit1_ShadowAtBottom);
                MusicController::static_PlayMusic(MusicController::MusicTypes::eType0, this, 0, 0);
                field_2A8_flags.Set(Flags_2A8::e2A8_Bit8_bLandSoft);
                field_10_anim.mAnimFlags.Set(AnimFlags::eBit3_Render);
                mBaseGameObjectFlags.Set(Options::eDrawable_Bit4);
                mCurrentMotion = eAbeMotions::Motion_3_Fall_42E7F0;

                ao_new<Flash>(Layer::eLayer_Above_FG1_39, 255u, 0, 255u);
                field_106_shot = 0;
                field_2A8_flags.Clear(Flags_2A8::e2A8_Bit6_bShrivel);
                field_114_gnFrame = sGnFrame;
            }
            break;
        }
        default:
            return;
    }
}

using elumSpawn = decltype(&Elum::Spawn);
const elumSpawn dword_4CF550[] = {
    nullptr,
    nullptr,
    &Elum::Spawn,
    &Elum::Spawn,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    &Elum::Spawn,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr};

void Abe::Motion_62_LoadedSaveSpawn_45ADD0()
{
    Event_Broadcast(kEventResetting, this);

    if (field_114_gnFrame)
    {
        auto pSaveData = field_2AC_pSaveData;
        mBaseAnimatedWithPhysicsGameObject_YPos = FP_FromInteger(pSaveData->field_228_ypos);
        mBaseAnimatedWithPhysicsGameObject_XPos = FP_FromInteger(pSaveData->field_224_xpos);

        PathLine* pLine2 = nullptr;
        FP hitX2 = {};
        FP hitY2 = {};
        if (sCollisions->RayCast(
                sActiveHero_507678->mBaseAnimatedWithPhysicsGameObject_XPos,
                sActiveHero_507678->mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromInteger(60),
                sActiveHero_507678->mBaseAnimatedWithPhysicsGameObject_XPos,
                sActiveHero_507678->mBaseAnimatedWithPhysicsGameObject_YPos + FP_FromInteger(60),
                &pLine2,
                &hitX2,
                &hitY2,
                1 << pSaveData->field_23A_mode_mask))
        {
            sActiveHero_507678->BaseAliveGameObjectCollisionLine = pLine2;
            sActiveHero_507678->mBaseAnimatedWithPhysicsGameObject_YPos = hitY2;
            sActiveHero_507678->mCurrentMotion = eAbeMotions::Motion_0_Idle_423520;
        }
        else
        {
            sActiveHero_507678->mCurrentMotion = eAbeMotions::Motion_3_Fall_42E7F0;
        }
        sActiveHero_507678->field_2A8_flags.Clear(Flags_2A8::e2A8_Bit8_bLandSoft);
        sActiveHero_507678->BaseAliveGameObjectLastLineYPos = sActiveHero_507678->mBaseAnimatedWithPhysicsGameObject_YPos;
        sActiveHero_507678->field_110_state.raw = static_cast<s16>(pSaveData->field_244_stone_state);
        sActiveHero_507678->field_114_gnFrame = pSaveData->field_248_gnFrame;
        sActiveHero_507678->mBaseAliveGameObjectLastAnimFrame = pSaveData->field_240_last_anim_frame;
        sActiveHero_507678->field_10_anim.mAnimFlags.Set(AnimFlags::eBit5_FlipX, pSaveData->field_23C_ah_flipX & 1);
        sActiveHero_507678->MapFollowMe_401D30(TRUE);
        sActiveHero_507678->field_10_anim.mAnimFlags.Set(AnimFlags::eBit3_Render);
        if (sActiveHero_507678->field_19C_throwable_count)
        {
            if (!gpThrowableArray_50E26C)
            {
                LoadRockTypes(MapWrapper::FromAO(gSaveBuffer_505668.field_234_current_level), gSaveBuffer_505668.field_236_current_path);

                gpThrowableArray_50E26C = ao_new<ThrowableArray>();
            }
            gpThrowableArray_50E26C->Add(sActiveHero_507678->field_19C_throwable_count);
        }
        if (pSaveData->field_264_bInfiniteGrenades == -1)
        {
            LoadRockTypes(EReliveLevelIds::eRuptureFarmsReturn, 19);
            if (!gpThrowableArray_50E26C)
            {
                gpThrowableArray_50E26C = ao_new<ThrowableArray>();
            }
            gpThrowableArray_50E26C->Add(1);
            gInfiniteGrenades_5076EC = 1;
        }
        else
        {
            gInfiniteGrenades_5076EC = 0;
        }
        if (pSaveData->field_25A_bElumExists)
        {
            if (!gElum_507680)
            {
                TlvItemInfoUnion aux;
                aux.all = (u32) -1;
                dword_4CF550[static_cast<s32>(MapWrapper::ToAO(gMap.mCurrentLevel))](aux);
            }

            ResourceManager::LoadResourceFile_455270("ANEPRMNT.BAN", 0);
            ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAneprmntAOResID, 1, 0);
            gElum_507680->mBaseGameObjectFlags.Clear(Options::eUpdatable_Bit2);
            gElum_507680->field_10_anim.mAnimFlags.Clear(AnimFlags::eBit3_Render);
            gElum_507680->field_138_continue_rect = pSaveData->field_28C_elum_continue_rect;
            gElum_507680->field_140_continue_zone_number = pSaveData->field_294_continue_zone_number;
            gElum_507680->field_142_zone_number = pSaveData->field_296_elum_zone_number;
            gElum_507680->field_148_continue_path = pSaveData->field_298_elum_continue_path;
            gElum_507680->field_14A_continue_level = MapWrapper::FromAO(pSaveData->field_29A_continue_level);
            gElum_507680->field_150_continue_sprite_scale = pSaveData->field_29C_elum_sprite_scale;
            gElum_507680->field_144_bRespawnOnDead = pSaveData->field_25E_bElumRespawnOnDead;
            gElum_507680->field_B2_lvl_number = MapWrapper::FromAO(pSaveData->field_260_elum_lvl_number);
            gElum_507680->field_B0_path_number = pSaveData->field_262_elum_path_number;
            gElum_507680->mBaseAnimatedWithPhysicsGameObject_XPos = FP_FromInteger(pSaveData->field_268_elum_xpos);
            gElum_507680->mBaseAnimatedWithPhysicsGameObject_YPos = FP_FromInteger(pSaveData->field_26C_elum_ypos);
            gElum_507680->field_10_anim.mAnimFlags.Set(AnimFlags::eBit5_FlipX, pSaveData->field_272_elum_flipX & 1);
            gElum_507680->mBaseAliveGameObjectLastAnimFrame = 0;
            gElum_507680->field_120_bUnknown = 1;
            gElum_507680->field_122_bDontFollowAbe = pSaveData->field_276_bDontFollowAbe;
            gElum_507680->field_128_brain_idx = pSaveData->field_278_brain_idx;
            gElum_507680->field_12A_brain_sub_state = pSaveData->field_27A_elum_brain_state;
            gElum_507680->field_12C_honey_xpos = static_cast<s16>(pSaveData->field_27C_honey_xpos);
            gElum_507680->field_146_honey_ypos = pSaveData->field_280_honey_ypos;
            gElum_507680->field_130_unused = pSaveData->field_284_unused;

            gElum_507680->field_170_flags.Set(Elum::Flags_170::eFoundHoney_Bit4, pSaveData->field_28B_elum_FoundHoney & 1);
            gElum_507680->field_170_flags.Set(Elum::Flags_170::eFalling_Bit3, pSaveData->field_28A_elum_Falling & 1);
            gElum_507680->field_170_flags.Set(Elum::Flags_170::eStungByBees_Bit2, pSaveData->field_289_elum_StungByBees & 1);
            if (gElum_507680->field_B0_path_number == sActiveHero_507678->field_B0_path_number)
            {
                if (pSaveData->field_270_elum_line_type != -1)
                {
                    PathLine* pLine = nullptr;
                    FP hitX = {};
                    FP hitY = {};
                    if (sCollisions->RayCast(
                            gElum_507680->mBaseAnimatedWithPhysicsGameObject_XPos,
                            gElum_507680->mBaseAnimatedWithPhysicsGameObject_YPos - FP_FromInteger(60),
                            gElum_507680->mBaseAnimatedWithPhysicsGameObject_XPos,
                            gElum_507680->mBaseAnimatedWithPhysicsGameObject_YPos + FP_FromInteger(60),
                            &pLine,
                            &hitX,
                            &hitY,
                            1 << pSaveData->field_270_elum_line_type))
                    {
                        gElum_507680->BaseAliveGameObjectCollisionLine = pLine;
                        gElum_507680->mCurrentMotion = eElumMotions::Motion_1_Idle_412990;
                        gElum_507680->mPreviousMotion = eElumMotions::Motion_1_Idle_412990;
                    }
                    else
                    {
                        gElum_507680->mCurrentMotion = eElumMotions::Motion_21_Land_414A20;
                        gElum_507680->mPreviousMotion = eElumMotions::Motion_21_Land_414A20;
                    }
                }
            }
            else
            {
                //TODO fix this madness
                gElum_507680->BaseAliveGameObjectCollisionLine = reinterpret_cast<PathLine*>(-2);
            }
            if (gElum_507680->field_170_flags.Get(Elum::Flags_170::eFoundHoney_Bit4))
            {
                if (!ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kElmHoneyAOResID, 0, 0))
                {
                    ResourceManager::LoadResourceFile_455270("ELMHONEY.BAN", 0);
                }
                gElum_507680->mCurrentMotion = eElumMotions::Motion_25_LickingHoney_415B50;
                gElum_507680->mPreviousMotion = eElumMotions::Motion_25_LickingHoney_415B50;
            }
            gElum_507680->MapFollowMe_401D30(TRUE);
            gElum_507680->mBaseGameObjectFlags.Set(Options::eUpdatable_Bit2);
            gElum_507680->field_10_anim.mAnimFlags.Set(AnimFlags::eBit3_Render);
        }
    }
    else
    {
        field_114_gnFrame = 1;
    }
}

void Abe::Motion_63_TurnToRun_42A0A0()
{
    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
    {
        ToKnockback_422D90(1, 1);
    }
    else
    {
        MoveForward_422FC0();

        if (mCurrentMotion == eAbeMotions::Motion_63_TurnToRun_42A0A0)
        {
            if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                mCurrentMotion = eAbeMotions::Motion_35_RunLoop_425060;
            }
        }
    }
}

void Abe::Motion_64_LedgeAscend_428B60()
{
    FollowLift_42EE90();

    if (field_10_anim.field_92_current_frame == 0)
    {
        Environment_SFX_42A220(EnvironmentSfx::eExhaustingHoistNoise_10, 0, 0x7FFF, this);
    }
    if (field_10_anim.field_92_current_frame == 4)
    {
        Environment_SFX_42A220(EnvironmentSfx::eRunJumpOrLedgeHoist_11, 0, 0x7FFF, this);
        field_D0_pShadow->field_14_flags.Clear(Shadow::eBit1_ShadowAtBottom);
    }
    else if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        MapFollowMe_401D30(1);
        ToIdle_422D50();
    }
}

void Abe::Motion_65_LedgeDescend_428C00()
{
    FollowLift_42EE90();

    if (field_10_anim.field_92_current_frame == 2)
    {
        Environment_SFX_42A220(EnvironmentSfx::eRunJumpOrLedgeHoist_11, 0, 0x7FFF, this);
        field_D0_pShadow->field_14_flags.Toggle(Shadow::eBit1_ShadowAtBottom);
    }
    else if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_66_LedgeHang_428D90;
    }
}

void Abe::Motion_66_LedgeHang_428D90()
{
    FollowLift_42EE90();

    field_D0_pShadow->field_14_flags.Set(Shadow::eBit1_ShadowAtBottom);

    if (Input().IsAnyPressed(sInputKey_Up_4C6598))
    {
        mCurrentMotion = eAbeMotions::Motion_64_LedgeAscend_428B60;
    }
    else if (Input().IsAnyPressed(sInputKey_Down_4C659C))
    {
        VOnTrapDoorOpen();

        BaseAliveGameObjectCollisionLine = nullptr;
        mCurrentMotion = eAbeMotions::Motion_91_FallingFromGrab_429780;
        mBaseAnimatedWithPhysicsGameObject_YPos += (field_BC_sprite_scale * FP_FromInteger(80)) + FP_FromInteger(3);
        BaseAliveGameObjectLastLineYPos = mBaseAnimatedWithPhysicsGameObject_YPos;
        field_D0_pShadow->field_14_flags.Clear(Shadow::eBit1_ShadowAtBottom);
    }
}

void Abe::Motion_67_ToOffScreenHoist_428C50()
{
    mBaseAnimatedWithPhysicsGameObject_YPos -= (field_BC_sprite_scale * FP_FromInteger(80));

    field_D0_pShadow->field_14_flags.Toggle(Shadow::eBit1_ShadowAtBottom);

    PathLine* pLine = nullptr;
    FP hitX = {};
    FP hitY = {};
    if (sCollisions->RayCast(
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos - (field_BC_sprite_scale * FP_FromInteger(80)),
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos,
            &pLine,
            &hitX,
            &hitY,
            field_BC_sprite_scale != FP_FromDouble(0.5) ? 1 : 0x10))
    {
        mBaseAnimatedWithPhysicsGameObject_YPos = hitY;
        BaseAliveGameObjectCollisionLine = pLine;
        field_B8_vely = FP_FromInteger(0);
        if (!mLiftPoint)
        {
            if (BaseAliveGameObjectCollisionLine->field_8_type == eLineTypes ::eUnknown_32 ||
                BaseAliveGameObjectCollisionLine->field_8_type == eLineTypes::eUnknown_36)
            {
                PSX_RECT bRect = {};
                VGetBoundingRect(&bRect, 1);

                bRect.y += 5;
                bRect.h += 5;

                VOnCollisionWith(
                    {bRect.x, bRect.y},
                    {bRect.w, bRect.h},
                    ObjListPlatforms_50766C,
                    1,
                    (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection_401C10);
            }
        }
        mCurrentMotion = eAbeMotions::Motion_66_LedgeHang_428D90;
    }
    else
    {
        mCurrentMotion = eAbeMotions::Motion_17_HoistIdle_4269E0;
    }
}

void Abe::Motion_68_LedgeHangWobble_428E50()
{
    if (field_10_anim.field_92_current_frame == 0)
    {
        if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit2_bSfxPlaying))
        {
            field_2AA_flags.Set(Flags_2AA::e2AA_Bit2_bSfxPlaying);
            Environment_SFX_42A220(EnvironmentSfx::eWalkingFootstep_1, 0, 127, this);
        }
    }
    else if (field_10_anim.field_92_current_frame == 2)
    {
        if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit2_bSfxPlaying))
        {
            field_2AA_flags.Set(Flags_2AA::e2AA_Bit2_bSfxPlaying);
            Mudokon_SFX_42A4D0(MudSounds::eBeesStruggle_18, 45, -200, this);
        }
    }
    else
    {
        field_2AA_flags.Clear(Flags_2AA::e2AA_Bit2_bSfxPlaying);
    }

    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    FollowLift_42EE90();

    if (Input().IsAnyPressed(sInputKey_Up_4C6598))
    {
        field_2AA_flags.Clear(Flags_2AA::e2AA_Bit2_bSfxPlaying);
        mCurrentMotion = eAbeMotions::Motion_64_LedgeAscend_428B60;
    }
    else
    {
        if (Input().IsAnyPressed(sInputKey_Down_4C659C))
        {
            field_2AA_flags.Clear(Flags_2AA::e2AA_Bit2_bSfxPlaying);

            VOnTrapDoorOpen();
            BaseAliveGameObjectCollisionLine = nullptr;

            mCurrentMotion = eAbeMotions::Motion_91_FallingFromGrab_429780;
            mBaseAnimatedWithPhysicsGameObject_YPos += (field_BC_sprite_scale * FP_FromInteger(80)) + FP_FromInteger(3);
            field_D0_pShadow->field_14_flags.Clear(Shadow::eBit1_ShadowAtBottom);
            BaseAliveGameObjectLastLineYPos = mBaseAnimatedWithPhysicsGameObject_YPos;
        }
        else if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            field_2AA_flags.Clear(Flags_2AA::e2AA_Bit2_bSfxPlaying);
            mCurrentMotion = eAbeMotions::Motion_66_LedgeHang_428D90;
        }
    }
}

void Abe::Motion_69_RingRopePullHang_4299B0()
{
    if (field_160_pRope->vIsNotBeingPulled())
    {
        mCurrentMotion = eAbeMotions::Motion_91_FallingFromGrab_429780;
        field_160_pRope->mBaseGameObjectRefCount--;
        field_160_pRope = nullptr;
        field_B8_vely = FP_FromInteger(0);
    }
}

void Abe::Motion_70_Knockback_428FB0()
{
    ElumFree_4228F0();

    if (field_1A0_portal)
    {
        field_1A0_portal->VKillPortalClipper();
        field_1A0_portal = nullptr;
    }

    if (field_10_anim.field_92_current_frame == 12)
    {
        FallOnBombs_4231B0();
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit3_Render))
    {
        if (BaseAliveGameObjectCollisionLine)
        {
            if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
            {
                field_B4_velx = FP_FromInteger(0);
            }

            MoveWithVelocity_4257F0(FP_FromDouble(0.7));

            if ((gMap.mCurrentLevel == EReliveLevelIds::eRuptureFarms
                 || gMap.mCurrentLevel == EReliveLevelIds::eRuptureFarmsReturn
                 || gMap.mCurrentLevel == EReliveLevelIds::eBoardRoom)
                && field_10_anim.field_92_current_frame == 7)
            {
                Environment_SFX_42A220(EnvironmentSfx::eHitGroundSoft_6, 80, -200, this);
                Event_Broadcast(kEventNoise, this);
                Event_Broadcast(kEventSuspiciousNoise, this);
            }
        }
        else
        {
            Motion_3_Fall_42E7F0();

            if (mCurrentMotion == eAbeMotions::Motion_86_FallLandDie_42EDD0 || mCurrentMotion == eAbeMotions::Motion_98_LandSoft_42ED40)
            {
                field_114_gnFrame = sGnFrame + 10;
                mCurrentMotion = eAbeMotions::Motion_70_Knockback_428FB0;
                Environment_SFX_42A220(EnvironmentSfx::eHitGroundSoft_6, 80, -200, this);
            }
        }
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        if ((BaseAliveGameObjectCollisionLine || !field_10_anim.mAnimFlags.Get(AnimFlags::eBit3_Render)) && !field_104_pending_resource_count)
        {
            if (!field_1A4_resources.res[0])
            {
                field_1A4_resources.res[0] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbebasicAOResID, 1, 0);
                field_1A4_resources.res[10] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbefallAOResID, 1, 0);
                field_1A4_resources.res[38] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeommAOResID, 1, 0);
                field_1A4_resources.res[9] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbesmashAOResID, 1, 0);

                if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit3_ElumMountBegin))
                {
                    ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAneprmntAOResID, 1, 0);
                }
            }

            if (field_114_gnFrame <= static_cast<s32>(sGnFrame))
            {
                if (mHealth > FP_FromInteger(0) || gAbeInvulnerableCheat_5076E4)
                {
                    mCurrentMotion = eAbeMotions::Motion_71_KnockbackGetUp_429240;
                }
                else
                {
                    ToDieFinal_42C400();
                }
            }
        }
    }
}

void Abe::Motion_71_KnockbackGetUp_429240()
{
    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_72_PushWall_4292A0()
{
    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (field_10_anim.field_92_current_frame == 10)
    {
        if (Math_NextRandom() <= 127u)
        {
            Environment_SFX_42A220(EnvironmentSfx::eExhaustingHoistNoise_10, 0, 0x7FFF, this);
        }
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_73_RollingKnockback_4291D0()
{
    if (field_10_anim.field_92_current_frame == 12)
    {
        FallOnBombs_4231B0();
    }

    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (field_114_gnFrame <= static_cast<s32>(sGnFrame))
        {
            if (mHealth > FP_FromInteger(0) || gAbeInvulnerableCheat_5076E4)
            {
                mCurrentMotion = eAbeMotions::Motion_71_KnockbackGetUp_429240;
            }
            else
            {
                ToDieFinal_42C400();
            }
        }
    }
}

void Abe::Motion_74_JumpIntoWell_430EC0()
{
    field_D0_pShadow->field_14_flags.Clear(Shadow::Flags::eBit2_Enabled);

    if (field_BC_sprite_scale == FP_FromDouble(0.5))
    {
        field_10_anim.mRenderLayer = Layer::eLayer_BeforeWell_Half_3;
    }
    else
    {
        field_10_anim.mRenderLayer = Layer::eLayer_BeforeWell_22;
    }

    Motion_77_WellBegin_430F10();
}

void Abe::Motion_75_ToInsideOfAWellLocal_431090()
{
    Motion_78_InsideWellLocal_4310A0();
}

void Abe::Motion_76_ToWellShotOut_431720()
{
    Motion_79_WellShotOut_431730();
}

void Abe::Motion_77_WellBegin_430F10()
{
    Event_Broadcast(kEventNoise, this);
    if (field_10_anim.field_92_current_frame > 10)
    {
        field_D0_pShadow->field_14_flags.Clear(Shadow::Flags::eBit2_Enabled);

        BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446260(
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
            TlvTypes::WellLocal_11);
        if (!BaseAliveGameObjectPathTLV)
        {
            BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446260(
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                TlvTypes::WellExpress_45);
        }

        const s16 xpos = FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos);
        const auto tlv_mid_x = (BaseAliveGameObjectPathTLV->field_14_bottom_right.field_0_x + BaseAliveGameObjectPathTLV->field_10_top_left.field_0_x) / 2;
        if (xpos > tlv_mid_x)
        {
            mBaseAnimatedWithPhysicsGameObject_XPos -= field_BC_sprite_scale;
        }
        else if (xpos < tlv_mid_x)
        {
            mBaseAnimatedWithPhysicsGameObject_XPos += field_BC_sprite_scale;
        }
    }
    if (field_10_anim.field_92_current_frame == 11)
    {
        if (field_BC_sprite_scale == FP_FromDouble(0.5))
        {
            field_10_anim.mRenderLayer = Layer::eLayer_BeforeWell_Half_3;
        }
        else
        {
            field_10_anim.mRenderLayer = Layer::eLayer_BeforeWell_22;
        }
    }
    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        field_114_gnFrame = 15;
        SFX_Play_Mono(SoundEffect::WellEnter_25, 0, this);

        switch (mCurrentMotion)
        {
            case eAbeMotions::Motion_77_WellBegin_430F10:
            {
                mCurrentMotion = eAbeMotions::Motion_78_InsideWellLocal_4310A0;
                break;
            }
            case eAbeMotions::Motion_80_430EF0:
            {
                mCurrentMotion = eAbeMotions::Motion_81_InsideWellExpress_431320;
                break;
            }
            case eAbeMotions::Motion_83_430F00:
            {
                mCurrentMotion = eAbeMotions::Motion_84_ToInsideWellLocal_431080;
                break;
            }
            case eAbeMotions::Motion_74_JumpIntoWell_430EC0:
            {
                mCurrentMotion = eAbeMotions::Motion_75_ToInsideOfAWellLocal_431090;
                break;
            }
            default:
            {
                LOG_ERROR("Unrecognized state called: " << mCurrentMotion);
                ALIVE_FATAL("Unrecognized state in Abe::Motion_77_WellBegin_430F10 called!");
                break;
            }
        }
    }
}

ALIVE_VAR(1, 0x4C73CC, FP, gPointlessWellScale_4C73CC, FP_FromDouble(1.8));

void Abe::Motion_78_InsideWellLocal_4310A0()
{
    const s32 old_gnFrame = field_114_gnFrame;
    field_114_gnFrame--;

    if (old_gnFrame == 0)
    {
        BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446260(
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
            TlvTypes::WellLocal_11);

        if (!BaseAliveGameObjectPathTLV)
        {
            BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446260(
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                TlvTypes::WellExpress_45);
        }

        auto pWellBase = static_cast<Path_WellBase*>(BaseAliveGameObjectPathTLV);

        field_120_x_vel_slow_by = FP_FromInteger(0);

        if (field_2A8_flags.Get(Flags_2A8::e2A8_Bit4_snap_abe))
        {
            // Snap to exit point
            field_B4_velx = (field_BC_sprite_scale * (FP_FromInteger(pWellBase->field_20_exit_x) / FP_FromInteger(100)));
            field_B8_vely = (field_BC_sprite_scale * (FP_FromInteger(pWellBase->field_22_exit_y) / FP_FromInteger(100)));
            field_2A8_flags.Clear(Flags_2A8::e2A8_Bit4_snap_abe);
        }
        else
        {
            if (SwitchStates_Get(pWellBase->field_1A_switch_id))
            {
                auto pLocalWell = static_cast<Path_WellLocal*>(BaseAliveGameObjectPathTLV);
                field_B4_velx = (field_BC_sprite_scale * FP_FromInteger(pLocalWell->field_28_on_dx) / FP_FromInteger(100));
                field_B8_vely = (field_BC_sprite_scale * FP_FromInteger(pLocalWell->field_2A_on_dy) / FP_FromInteger(100));
            }
            else
            {
                field_B4_velx = (field_BC_sprite_scale * FP_FromInteger(pWellBase->field_24_off_level_or_dx.dx) / FP_FromInteger(100));
                field_B8_vely = (field_BC_sprite_scale * FP_FromInteger(pWellBase->field_26_off_path_or_dy) / FP_FromInteger(100));
            }
        }

        MapFollowMe_401D30(1);

        mBaseAnimatedWithPhysicsGameObject_YPos += field_B8_vely;
        gPointlessWellScale_4C73CC = FP_FromDouble(1.8);

        if (field_B4_velx >= FP_FromInteger(0))
        {
            field_10_anim.mAnimFlags.Clear(AnimFlags::eBit5_FlipX);
        }
        else
        {
            field_10_anim.mAnimFlags.Set(AnimFlags::eBit5_FlipX);
        }

        SFX_Play_Mono(SoundEffect::WellExit_24, 0, this);

        mCurrentMotion++; // can be motion 76 and 79 maybe more?

        if (field_BC_sprite_scale == FP_FromDouble(0.5))
        {
            field_10_anim.mRenderLayer = Layer::eLayer_BeforeWell_Half_3;
        }
        else
        {
            field_10_anim.mRenderLayer = Layer::eLayer_BeforeWell_22;
        }

        BaseAliveGameObjectCollisionLine = nullptr;
    }
}

void Abe::Motion_79_WellShotOut_431730()
{
    if (field_B8_vely >= FP_FromInteger(0))
    {
        Motion_3_Fall_42E7F0();
    }
    else
    {
        field_B8_vely += (field_BC_sprite_scale * gPointlessWellScale_4C73CC);

        mBaseAnimatedWithPhysicsGameObject_XPos += field_B4_velx;
        mBaseAnimatedWithPhysicsGameObject_YPos += field_B8_vely;

        SetActiveCameraDelayedFromDir_401C90();
        BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446060(
            nullptr,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos);
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted)
        || (mCurrentMotion != eAbeMotions::Motion_79_WellShotOut_431730
            && mCurrentMotion != eAbeMotions::Motion_85_ToWellShotOut_431710
            && mCurrentMotion != eAbeMotions::Motion_76_ToWellShotOut_431720))
    {
        if (field_BC_sprite_scale == FP_FromDouble(0.5))
        {
            field_10_anim.mRenderLayer = Layer::eLayer_AbeMenu_Half_13;
        }
        else
        {
            field_10_anim.mRenderLayer = Layer::eLayer_AbeMenu_32;
        }

        field_D0_pShadow->field_14_flags.Set(Shadow::eBit2_Enabled);
    }

    if (mCurrentMotion == eAbeMotions::Motion_86_FallLandDie_42EDD0)
    {
        mHealth = FP_FromInteger(1);
        mCurrentMotion = eAbeMotions::Motion_98_LandSoft_42ED40;
    }
}

void Abe::Motion_80_ToWellBegin_430EF0()
{
    Motion_77_WellBegin_430F10();
}

void Abe::Motion_81_InsideWellExpress_431320()
{
    BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446260(
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
        TlvTypes::WellLocal_11);

    if (!BaseAliveGameObjectPathTLV)
    {
        BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446260(
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
            TlvTypes::WellExpress_45);
    }


    if (field_2A8_flags.Get(Flags_2A8::e2A8_Bit4_snap_abe))
    {
        mCurrentMotion = eAbeMotions::Motion_78_InsideWellLocal_4310A0;
        return;
    }

    Path_WellExpress* pExpressWell = static_cast<Path_WellExpress*>(BaseAliveGameObjectPathTLV);
    if (SwitchStates_Get(pExpressWell->field_1A_switch_id))
    {
        field_190_level = MapWrapper::FromAO(pExpressWell->field_2C_on_level);
        field_192_path = pExpressWell->field_2E_on_path;
        field_194_camera = pExpressWell->field_30_on_camera;
        field_196_door_id = pExpressWell->field_32_on_well_id;
    }
    else
    {
        field_190_level = MapWrapper::FromAO(pExpressWell->field_24_off_level_or_dx.level);
        field_192_path = pExpressWell->field_26_off_path_or_dy;
        field_194_camera = pExpressWell->field_28_off_camera;
        field_196_door_id = pExpressWell->field_2A_off_well_id;
    }

    field_120_x_vel_slow_by = FP_FromInteger(0);

    if (gMap.mCurrentLevel == EReliveLevelIds::eLines)
    {
        if (field_190_level == EReliveLevelIds::eForest)
        {
            if (field_2A8_flags.Get(Flags_2A8::e2A8_Bit12_bParamoniaDone))
            {
                field_2A8_flags.Set(Flags_2A8::e2A8_Bit3_WalkToRun);
                field_114_gnFrame = 0;
                mCurrentMotion = eAbeMotions::Motion_78_InsideWellLocal_4310A0;
                Motion_78_InsideWellLocal_4310A0();
                return;
            }
            LOG_INFO("set bParamoniaDone");
            field_2A8_flags.Set(Flags_2A8::e2A8_Bit12_bParamoniaDone);
        }

        if (field_190_level == EReliveLevelIds::eDesert)
        {
            if (field_2A8_flags.Get(Flags_2A8::e2A8_eBit13_bScrabaniaDone))
            {
                field_2A8_flags.Set(Flags_2A8::e2A8_Bit3_WalkToRun);
                field_114_gnFrame = 0;
                mCurrentMotion = eAbeMotions::Motion_78_InsideWellLocal_4310A0;
                Motion_78_InsideWellLocal_4310A0();
                return;
            }
            LOG_INFO("set bScrabinaDone");
            field_2A8_flags.Set(Flags_2A8::e2A8_eBit13_bScrabaniaDone);
        }
    }
    if (field_190_level != gMap.mCurrentLevel
        || field_192_path != gMap.mCurrentPath
        || field_194_camera != gMap.mCurrentCamera)
    {
        field_114_gnFrame = 1;
        if (pExpressWell->field_3A_movie_id)
        {
            gMap.SetActiveCam(field_190_level, field_192_path, field_194_camera, CameraSwapEffects::ePlay1FMV_5, pExpressWell->field_3A_movie_id, 0);
        }
        else
        {
            gMap.SetActiveCam(field_190_level, field_192_path, field_194_camera, CameraSwapEffects::eInstantChange_0, 0, 0);
        }
        mCurrentMotion = eAbeMotions::Motion_82_WellExpressShotOut_4315A0;
    }
    else
    {
        Motion_82_WellExpressShotOut_4315A0();
        field_B4_velx = FP_FromInteger(0);
        field_B8_vely = FP_FromInteger(0);
        mBaseAnimatedWithPhysicsGameObject_YPos = mBaseAnimatedWithPhysicsGameObject_YPos - field_B8_vely;
        field_2A8_flags.Set(Flags_2A8::e2A8_Bit3_WalkToRun);
        mCurrentMotion = eAbeMotions::Motion_78_InsideWellLocal_4310A0;
    }
}

void Abe::Motion_82_WellExpressShotOut_4315A0()
{
    PSX_Point camCoords = {};
    gMap.GetCurrentCamCoords(&camCoords);
    Path_WellBase* pWell = nullptr;
    Path_TLV* pTlvIter = nullptr;
    do
    {
        pTlvIter = gMap.TLV_Get_At_446060(
            pTlvIter,
            FP_FromInteger(camCoords.field_0_x + 256),
            FP_FromInteger(camCoords.field_2_y + 120),
            FP_FromInteger(camCoords.field_0_x + 624),
            FP_FromInteger(camCoords.field_2_y + 360));
        if (!pTlvIter)
        {
            break;
        }

        if ((pTlvIter->field_4_type == TlvTypes::WellLocal_11 || pTlvIter->field_4_type == TlvTypes::WellExpress_45) && static_cast<Path_WellBase*>(pTlvIter)->field_1C_other_well_id == field_196_door_id)
        {
            pWell = static_cast<Path_WellBase*>(pTlvIter);
            break;
        }
    }
    while (pTlvIter);


    field_B2_lvl_number = gMap.mCurrentLevel;
    field_B0_path_number = gMap.mCurrentPath;

    if (pWell)
    {
        if (pWell->field_18_scale == Scale_short::eHalf_1)
        {
            field_BC_sprite_scale = FP_FromDouble(0.5);
            field_C6_scale = 0;
        }
        else
        {
            field_BC_sprite_scale = FP_FromInteger(1);
            field_C6_scale = 1;
        }

        mCurrentMotion = eAbeMotions::Motion_78_InsideWellLocal_4310A0;

        BaseAliveGameObjectPathTLV = pWell;
        mBaseAnimatedWithPhysicsGameObject_XPos = FP_FromInteger((pWell->field_10_top_left.field_0_x + pWell->field_14_bottom_right.field_0_x) / 2);
        mBaseAnimatedWithPhysicsGameObject_YPos = FP_FromInteger(pWell->field_14_bottom_right.field_2_y);
        field_2A8_flags.Set(Flags_2A8::e2A8_Bit4_snap_abe);
    }
    else
    {
        mBaseAnimatedWithPhysicsGameObject_XPos = FP_FromInteger(camCoords.field_0_x + 450);
        mBaseAnimatedWithPhysicsGameObject_YPos = FP_FromInteger(camCoords.field_2_y + 320);
        field_B4_velx = (field_BC_sprite_scale * -FP_FromDouble(2.7));
        field_B8_vely = (field_BC_sprite_scale * -FP_FromInteger(15));
    }
}

void Abe::Motion_83_ToWellBegin_430F00()
{
    Motion_77_WellBegin_430F10();
}

void Abe::Motion_84_ToInsideWellLocal_431080()
{
    Motion_78_InsideWellLocal_4310A0();
}

void Abe::Motion_85_ToWellShotOut_431710()
{
    Motion_79_WellShotOut_431730();
}

void Abe::Motion_86_FallLandDie_42EDD0()
{
    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (field_10_anim.field_92_current_frame == 0)
    {
        SFX_Play_Mono(SoundEffect::KillEffect_78, 85, 0);
        SND_SEQ_Play_477760(SeqId::eHitBottomOfDeathPit_10, 1, 95, 95);
        ao_new<ScreenShake>(true);
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (static_cast<s32>(sGnFrame) >= field_114_gnFrame)
        {
            ToDieFinal_42C400();
        }
    }
}

void Abe::Motion_87_ToFall_428FA0()
{
    Motion_3_Fall_42E7F0();
}

ALIVE_VAR(1, 0x507728, s32, gCounter_507728, 0);
ALIVE_VAR(1, 0x50772C, u8**, gpDemoPlaybackRes_50772C, nullptr);
ALIVE_VAR(1, 0x507730, s32, sAbeSound_507730, 0);
ALIVE_VAR(1, 0x507724, BellSong*, sBellSong_507724, nullptr);

void Abe::Motion_88_HandstoneBegin_430590()
{
    switch (field_110_state.stone)
    {
        case StoneStates::eHandstoneStart_0:
        {
            if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
            {
                ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kSpotliteAOResID, 1, 0);
                field_164_pCircularFade = Make_Circular_Fade(
                    mBaseAnimatedWithPhysicsGameObject_XPos,
                    mBaseAnimatedWithPhysicsGameObject_YPos,
                    field_BC_sprite_scale,
                    1,
                    0);

                field_164_pCircularFade->field_10_anim.mAnimFlags.Set(
                    AnimFlags::eBit5_FlipX,
                    field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX));

                field_110_state.stone = StoneStates::eGetHandstoneType_1;
                SFX_Play_Mono(SoundEffect::IngameTransition_107, 90, 0);
                BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446260(
                    FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
                    FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                    FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
                    FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                    TlvTypes::DemoPlaybackStone_96);
                if (!BaseAliveGameObjectPathTLV)
                    BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446260(
                        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
                        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
                        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                        TlvTypes::BellSongStone_54);
                if (!BaseAliveGameObjectPathTLV)
                {
                    BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446260(
                        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
                        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
                        FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                        TlvTypes::MovieStone_51);
                    sAbeSound_507730 = SFX_Play_Pitch(SoundEffect::HandstoneTransition_13, 127, -300, 0);
                    if (!BaseAliveGameObjectPathTLV)
                        BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446260(
                            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
                            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
                            FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                            TlvTypes::HandStone_100);
                }

                auto ptlv = static_cast<Path_Stone*>(BaseAliveGameObjectPathTLV);
                if (ptlv)
                {
                    field_170_hand_stone_type = BaseAliveGameObjectPathTLV->field_4_type;
                    switch (field_170_hand_stone_type.mType)
                    {
                        case TlvTypes::MovieStone_51:
                        {
                            field_174_pathStone.dataMovie = ptlv->field_18_data.dataMovie;
                            break;
                        }
                        case TlvTypes::BellSongStone_54:
                        {
                            field_174_pathStone.dataBellsong = ptlv->field_18_data.dataBellsong;
                            break;
                        }
                        case TlvTypes::DemoPlaybackStone_96:
                        {
                            field_174_pathStone.demoId = ptlv->field_18_data.demoId;
                            break;
                        }
                        case TlvTypes::HandStone_100:
                        {
                            field_174_pathStone.dataHandstone = ptlv->field_18_data.dataHandstone;
                            break;
                        }
                        default:
                            return;
                    }
                }
                else
                {
                    mCurrentMotion = eAbeMotions::Motion_89_HandstoneEnd_430E80;
                }
            }
            break;
        }
        case StoneStates::eGetHandstoneType_1:
        {
            if (field_164_pCircularFade->VDone())
            {
                switch (field_170_hand_stone_type.mType)
                {
                    case TlvTypes::MovieStone_51:
                    {
                        auto pFmvInfo = Path_Get_FMV_Record_434680(
                            gMap.mCurrentLevel,
                            field_174_pathStone.dataMovie.fmvId);
                        u32 aux = 0;
                        Get_fmvs_sectors_44FEB0(
                            pFmvInfo->field_0_pName, 0, 0, &aux, 0, 0);

                        ao_new<Movie>(
                            pFmvInfo->field_4_id,
                            aux,
                            static_cast<s8>(pFmvInfo->field_6),
                            pFmvInfo->field_A,
                            pFmvInfo->field_C_volume);

                        field_110_state.stone = StoneStates::eHandstoneMovieDone_2;
                        break;
                    }
                    case TlvTypes::BellSongStone_54:
                    {
                        sBellSong_507724 = ao_new<BellSong>(
                            field_174_pathStone.dataBellsong.type,
                            Code_Convert(field_174_pathStone.dataBellsong.code1, field_174_pathStone.dataBellsong.code2));

                        SwitchStates_Do_Operation(field_174_pathStone.dataBellsong.switch_id, SwitchOp::eSetTrue_0);
                        field_110_state.stone = StoneStates::eBellSongDone_4;
                        break;
                    }
                    case TlvTypes::DemoPlaybackStone_96:
                        field_164_pCircularFade->mBaseGameObjectFlags.Set(Options::eDead);
                        field_164_pCircularFade = nullptr;
                        field_110_state.stone = StoneStates::eFreeDemoPlaybackResources_3;
                        gCounter_507728 = 2;
                        gpDemoPlaybackRes_50772C = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Plbk, field_174_pathStone.demoId, 1, 0);
                        if (gpDemoPlaybackRes_50772C)
                        {
                            ao_new<DemoPlayback>(gpDemoPlaybackRes_50772C, 1);
                        }
                        break;
                    case TlvTypes::HandStone_100:
                    {
                        field_10_anim.mAnimFlags.Clear(AnimFlags::eBit3_Render);
                        field_110_state.stone = StoneStates::eWaitForInput_6;
                        field_16E_cameraIdx = 1;
                        field_164_pCircularFade->mBaseGameObjectFlags.Set(Options::eDead);
                        field_164_pCircularFade = 0;
                        field_158_pDeathFadeout = ao_new<DeathFadeOut>(Layer::eLayer_FadeFlash_40, 0, 0, 8, TPageAbr::eBlend_2);
                        field_190_level = gMap.mCurrentLevel;
                        field_192_path = gMap.mCurrentPath;
                        field_194_camera = gMap.mCurrentCamera;
                        gMap.SetActiveCam(
                            MapWrapper::FromAO(field_174_pathStone.dataHandstone.camera1.level),
                            field_174_pathStone.dataHandstone.camera1.path,
                            field_174_pathStone.dataHandstone.camera1.camera,
                            CameraSwapEffects::eInstantChange_0, 0, 0);
                        break;
                    }
                    default:
                        return;
                }
            }
            break;
        }
        case StoneStates::eHandstoneMovieDone_2:
        {
            if (sMovie_ref_count_9F309C == 0)
            {
                gPsxDisplay_504C78.PutCurrentDispEnv_40DE40();
                pScreenManager_4FF7C8->DecompressCameraToVRam(
                    reinterpret_cast<u16**>(gMap.field_34_camera_array[0]->field_C_ppBits));
                pScreenManager_4FF7C8->MoveImage();
                pScreenManager_4FF7C8->field_36_flags |= 1;
                field_164_pCircularFade->VFadeIn(0, 0);
                field_110_state.stone = StoneStates::eHandstoneEnd_5;
            }
            break;
        }
        case StoneStates::eFreeDemoPlaybackResources_3:
        {
            gCounter_507728--;
            if (gCounter_507728 == 0)
            {
                field_110_state.stone = StoneStates::eHandstoneEnd_5;
                ResourceManager::FreeResource_455550(gpDemoPlaybackRes_50772C);
                field_164_pCircularFade = Make_Circular_Fade(
                    mBaseAnimatedWithPhysicsGameObject_XPos,
                    mBaseAnimatedWithPhysicsGameObject_YPos,
                    field_BC_sprite_scale,
                    0,
                    0);

                field_164_pCircularFade->field_10_anim.mAnimFlags.Set(
                    AnimFlags::eBit5_FlipX,
                    field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX));
            }
            break;
        }
        case StoneStates::eBellSongDone_4:
        {
            if (sBellSong_507724->field_14_bDone)
            {
                sBellSong_507724->mBaseGameObjectFlags.Set(Options::eDead);
                field_164_pCircularFade->VFadeIn(0, 0);
                field_110_state.stone = StoneStates::eHandstoneEnd_5;
            }
            break;
        }
        case StoneStates::eHandstoneEnd_5:
        {
            if (field_164_pCircularFade->VDone())
            {
                field_164_pCircularFade->mBaseGameObjectFlags.Set(Options::eDead);
                mCurrentMotion = eAbeMotions::Motion_89_HandstoneEnd_430E80;
                field_164_pCircularFade = 0;
                if (sAbeSound_507730)
                {
                    SND_Stop_Channels_Mask_4774A0(sAbeSound_507730);
                    sAbeSound_507730 = 0;
                }
                ResourceManager::FreeResource_455550(
                    ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kSpotliteAOResID, 0, 0));
            }
            break;
        }
        case StoneStates::eWaitForInput_6:
        {
            if (field_158_pDeathFadeout->field_6E_bDone)
            {
                if (Input().IsAnyHeld(0xF0))
                {
                    field_158_pDeathFadeout->Init(Layer::eLayer_FadeFlash_40, 1, 0, 8);
                    field_110_state.stone = StoneStates::eSetActiveCamToAbeOrWaitForInput_7;
                    SFX_Play_Mono(SoundEffect::IngameTransition_107, 90, 0);
                }
            }
            break;
        }
        case StoneStates::eSetActiveCamToAbeOrWaitForInput_7:
        {
            if (field_158_pDeathFadeout->field_6E_bDone)
            {
                Path_Stone_camera camera = {};
                switch (field_16E_cameraIdx)
                {
                    case 0:
                        camera = field_174_pathStone.dataHandstone.camera1;
                        break;

                    case 1:
                        camera = field_174_pathStone.dataHandstone.camera2;
                        break;

                    case 2:
                        camera = field_174_pathStone.dataHandstone.camera3;
                        break;

                    default:
                        LOG_ERROR("CameraIdx out of bounds " << field_16E_cameraIdx);
                }
                if (field_16E_cameraIdx > 2 || (camera.level == LevelIds::eForestChase_14 || camera.level == LevelIds::eDesertEscape_15))
                {
                    field_110_state.stone = StoneStates::eSetActiveCamToAbe_12;
                }
                else
                {
                    field_158_pDeathFadeout->mBaseGameObjectFlags.Set(Options::eDead);
                    field_110_state.stone = StoneStates::eWaitForInput_6;
                    field_16E_cameraIdx++;
                    field_158_pDeathFadeout = ao_new<DeathFadeOut>(Layer::eLayer_FadeFlash_40, 0, 0, 8, TPageAbr::eBlend_2);
                    gMap.SetActiveCam(MapWrapper::FromAO(camera.level), camera.path, camera.camera, CameraSwapEffects::eInstantChange_0, 0, 0);
                }
            }
            break;
        }
        case StoneStates::eSetActiveCamToAbe_12:
            if (field_158_pDeathFadeout->field_6E_bDone)
            {
                field_10_anim.mAnimFlags.Set(AnimFlags::eBit3_Render);
                field_110_state.stone = StoneStates::eCircularFadeExit_13;
                gMap.SetActiveCam(field_190_level, field_192_path, field_194_camera, CameraSwapEffects::eInstantChange_0, 0, 0);
            }
            break;
        case StoneStates::eCircularFadeExit_13:
        {
            field_158_pDeathFadeout->mBaseGameObjectFlags.Set(Options::eDead);
            field_158_pDeathFadeout = 0;

            field_164_pCircularFade = Make_Circular_Fade(mBaseAnimatedWithPhysicsGameObject_XPos, mBaseAnimatedWithPhysicsGameObject_YPos, field_BC_sprite_scale, 0, 0);
            field_110_state.stone = StoneStates::eHandstoneEnd_5;
            field_164_pCircularFade->field_10_anim.mAnimFlags.Set(
                AnimFlags::eBit5_FlipX,
                field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX));

            if (sAbeSound_507730)
            {
                SND_Stop_Channels_Mask_4774A0(sAbeSound_507730);
                sAbeSound_507730 = 0;
            }
            break;
        }
        default:
            return;
    }
}

void Abe::Motion_89_HandstoneEnd_430E80()
{
    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        mCurrentMotion = eAbeMotions::Motion_0_Idle_423520;
    }
}

void Abe::Motion_90_GrenadeMachineUse_430EA0()
{
    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        mCurrentMotion = eAbeMotions::Motion_0_Idle_423520;
    }
}

void Abe::Motion_91_FallingFromGrab_429780()
{
    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_87_ToFall_428FA0;
    }

    Motion_3_Fall_42E7F0();

    if (mCurrentMotion == eAbeMotions::Motion_86_FallLandDie_42EDD0)
    {
        mCurrentMotion = eAbeMotions::Motion_98_LandSoft_42ED40;
    }

    mPreviousMotion = eAbeMotions::Motion_91_FallingFromGrab_429780;
}

void Abe::Motion_92_ForceDownFromHoist_4297C0()
{
    if (field_114_gnFrame == 0)
    {
        mBaseAnimatedWithPhysicsGameObject_YPos += (field_BC_sprite_scale * FP_FromInteger(80));
        field_D0_pShadow->field_14_flags.Clear(Shadow::eBit1_ShadowAtBottom);
        VOnTrapDoorOpen();
        BaseAliveGameObjectCollisionLine = nullptr;
        BaseAliveGameObjectLastLineYPos = mBaseAnimatedWithPhysicsGameObject_YPos;
        field_114_gnFrame++;
    }

    Motion_3_Fall_42E7F0();
}

void Abe::Motion_93_WalkOffEdge_429840()
{
    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_87_ToFall_428FA0;
    }
    Motion_3_Fall_42E7F0();
}

void Abe::Motion_94_RunOffEdge_429860()
{
    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_87_ToFall_428FA0;
    }
    Motion_3_Fall_42E7F0();
}

void Abe::Motion_95_SneakOffEdge_429880()
{
    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_87_ToFall_428FA0;
    }
    Motion_3_Fall_42E7F0();
}

void Abe::Motion_96_HopToFall_4298A0()
{
    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
    {
        mBaseAnimatedWithPhysicsGameObject_XPos += (field_BC_sprite_scale * FP_FromInteger(5));
    }
    else
    {
        mBaseAnimatedWithPhysicsGameObject_XPos -= (field_BC_sprite_scale * FP_FromInteger(5));
    }

    field_B8_vely += (field_BC_sprite_scale * FP_FromInteger(4));

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_87_ToFall_428FA0;
    }

    Motion_3_Fall_42E7F0();
}

void Abe::Motion_97_RunJumpToFall_429930()
{
    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_87_ToFall_428FA0;
    }
    Motion_3_Fall_42E7F0();
}

void Abe::Motion_98_LandSoft_42ED40()
{
    FollowLift_42EE90();

    if (field_10_anim.field_92_current_frame == 2)
    {
        if (!(field_2A8_flags.Get(Flags_2A8::e2A8_Bit8_bLandSoft)))
        {
            Event_Broadcast(kEventNoise, this);
            Event_Broadcast(kEventSuspiciousNoise, this);
        }

        field_2A8_flags.Clear(Flags_2A8::e2A8_Bit8_bLandSoft);

        if (mPreviousMotion == eAbeMotions::Motion_3_Fall_42E7F0)
        {
            Environment_SFX_42A220(EnvironmentSfx::eLandingSoft_5, 0, 0x7FFF, this);
        }
        else
        {
            Environment_SFX_42A220(EnvironmentSfx::eHitGroundSoft_6, 0, 0x7FFF, this);
        }

        if (Input().IsAnyPressed(0xA000u))
        {
            ToLeftRightMovement_422AA0();
        }
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_99_HoistBeginLong_426DC0()
{
    FollowLift_42EE90();

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        BaseAliveGameObjectLastLineYPos = mBaseAnimatedWithPhysicsGameObject_YPos;
        field_B8_vely = (field_BC_sprite_scale * FP_FromInteger(-8)) * FP_FromDouble(1.3);
        mBaseAnimatedWithPhysicsGameObject_YPos += field_B8_vely;
        VOnTrapDoorOpen();
        mCurrentMotion = eAbeMotions::Motion_17_HoistIdle_4269E0;
        BaseAliveGameObjectCollisionLine = nullptr;
    }
}

void Abe::Motion_100_RollOffLedge_429950()
{
    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_87_ToFall_428FA0;
    }
    Motion_3_Fall_42E7F0();
}

void Abe::Motion_101_LeverUse_429970()
{
    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_102_ElumWalkLoop_42DCA0()
{
    // Empty
}

void Abe::Motion_103_ElumIdle_42DCD0()
{
    if (!Input().IsAnyPressed(sInputKey_LeftGameSpeakEnabler_4C65B8 | sInputKey_RightGameSpeakEnabler_4C65DC) || !Input().IsAnyHeld(0xF0))
    {
        if (Input().Held() == sInputKey_Down_4C659C && !sDDCheat_FlyingEnabled_50771C)
        {
            ResourceManager::FreeResource_455550(field_1A4_resources.res[46]);
            field_104_pending_resource_count++;
            field_1A4_resources.res[46] = nullptr;
            ResourceManager::LoadResourceFile("ANEDSMNT.BND", BaseAliveGameObject::OnResourceLoaded_4019A0, this);
            mCurrentMotion = eAbeMotions::Motion_137_ElumUnmountBegin_42E2B0;
        }
    }
    else
    {
        mCurrentMotion = eAbeMotions::Motion_115_ElumSpeak_4299F0;
        if (Input().IsAnyPressed(sInputKey_LeftGameSpeakEnabler_4C65B8))
        {
            if (Input().IsAnyHeld(sInputKey_GameSpeak2_4C65BC))
            {
                pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eFollowMe_10);
                Mudokon_SFX_42A4D0(MudSounds::eFollowMe_4, 0, 0, this);
            }
            else if (Input().IsAnyHeld(sInputKey_GameSpeak4_4C65C4))
            {
                pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eWait_12);
                Mudokon_SFX_42A4D0(MudSounds::eWait_6, 0, 0, this);
            }
            else if (Input().IsAnyHeld(sInputKey_GameSpeak1_4C65C8))
            {
                pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eHello_9);
                Mudokon_SFX_42A4D0(MudSounds::eHello_3, 0, 0, this);
            }
            else if (Input().IsAnyHeld(sInputKey_GameSpeak3_4C65C0))
            {
                pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eAnger_11);
                Mudokon_SFX_42A4D0(MudSounds::eAngry_5, 0, 0, this);
            }
        }

        if (Input().IsAnyPressed(sInputKey_RightGameSpeakEnabler_4C65DC))
        {
            if (Input().IsAnyHeld(sInputKey_GameSpeak6_4C65E8))
            {
                pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eWhistleHigh_1);
                Mudokon_SFX_42A4D0(MudSounds::eWhistleHigh_1, 0, 0, this);
            }
            else if (Input().IsAnyHeld(sInputKey_GameSpeak5_4C65EC))
            {
                pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eWhistleLow_2);
                Mudokon_SFX_42A4D0(MudSounds::eWhistleLow_2, 0, 0, this);
            }
            else if (Input().IsAnyHeld(sInputKey_GameSpeak8_4C65E0))
            {
                pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eLaugh_4);
                Mudokon_SFX_42A4D0(MudSounds::eLaugh1_8, 0, 0, this);
            }
            else if (Input().IsAnyHeld(sInputKey_GameSpeak7_4C65E4))
            {
                pEventSystem_4FF954->VPushEvent(GameSpeakEvents::eFart_3);
                Mudokon_SFX_42A4D0(MudSounds::eFart_7, 0, 0, this);
            }
        }
    }
}

void Abe::Motion_104_ElumRunSlideStop_42DF00()
{
    // Empty
}

void Abe::Motion_105_ElumRunTurn_42DF10()
{
    // Empty
}

void Abe::Motion_106_Null_42DF20()
{
    // Empty
}

void Abe::Motion_107_ElumHopBegin_42DF30()
{
    // Empty
}

void Abe::Motion_108_ElumHopMid_42DF40()
{
    // Empty
}

void Abe::Motion_109_ElumHopLand_42DF50()
{
    // Empty
}

void Abe::Motion_110_ElumRunJumpBegin_42DF60()
{
    // Empty
}

void Abe::Motion_111_ElumRunJumpMid_42DF70()
{
    // Empty
}

void Abe::Motion_112_ElumRunJumpLand_42DF80()
{
    // Empty
}

void Abe::Motion_113_ElumTurn_42DF90()
{
    // Empty
}

void Abe::Motion_114_ElumRunLoop_42DFA0()
{
    // Empty
}

void Abe::Motion_115_ElumSpeak_4299F0()
{
    Event_Broadcast(kEventSpeaking, this);

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_103_ElumIdle_42DCD0;
    }
}

void Abe::Motion_116_Null_42DFB0()
{
    // Empty
}

void Abe::Motion_117_ElumWalkBegin_42DFC0()
{
    // Empty
}

void Abe::Motion_118_ElumRunBegin_42DFD0()
{
    // Empty
}

void Abe::Motion_119_Null_42DFE0()
{
    // Empty
}

void Abe::Motion_120_ElumRunToWalk_42DFF0()
{
    // Empty
}

void Abe::Motion_121_ElumMidRunToWalk_42E000()
{
    // Empty
}

void Abe::Motion_122_ElumRunTurnToRun_42E010()
{
    // Empty
}

void Abe::Motion_123_ElumRunTurnToWalk_42E020()
{
    // Empty
}

void Abe::Motion_124_ElumWalkEnd_42DCB0()
{
    // Empty
}

void Abe::Motion_125_ElumMidWalkEnd_42DCC0()
{
    // Empty
}

void Abe::Motion_126_ElumBeesStruggling_42E080()
{
    // Empty
}

void Abe::Motion_127_SlapBomb_429A20()
{
    if (sActiveHero_507678->field_10_anim.field_92_current_frame >= 6)
    {
        if (field_15C_pThrowable)
        {
            field_15C_pThrowable->mBaseGameObjectRefCount--;
            field_15C_pThrowable->VOnPickUpOrSlapped();
            field_15C_pThrowable = nullptr;
        }
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_19_CrouchIdle_4284C0;
    }
}

void Abe::Motion_128_KnockForward_429330()
{
    ElumFree_4228F0();

    if (field_10_anim.field_92_current_frame == 12)
    {
        FallOnBombs_4231B0();
    }

    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    FollowLift_42EE90();

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit3_Render))
    {
        if (BaseAliveGameObjectCollisionLine)
        {
            if (WallHit_401930(field_BC_sprite_scale * FP_FromInteger(50), field_B4_velx))
            {
                field_B4_velx = FP_FromInteger(0);
            }
            MoveWithVelocity_4257F0(FP_FromDouble(0.7));
        }
        else
        {
            Motion_3_Fall_42E7F0();

            if (mCurrentMotion == eAbeMotions::Motion_86_FallLandDie_42EDD0 || mCurrentMotion == eAbeMotions::Motion_98_LandSoft_42ED40)
            {
                mCurrentMotion = eAbeMotions::Motion_128_KnockForward_429330;
                field_114_gnFrame = sGnFrame + 10;
            }
        }
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        if ((BaseAliveGameObjectCollisionLine || !field_10_anim.mAnimFlags.Get(AnimFlags::eBit3_Render)) && !field_104_pending_resource_count)
        {
            if (!field_1A4_resources.res[0])
            {
                field_1A4_resources.res[0] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbebasicAOResID, 1, 0);
                field_1A4_resources.res[10] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbefallAOResID, 1, 0);
                field_1A4_resources.res[38] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeommAOResID, 1, 0);
                field_1A4_resources.res[9] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbesmashAOResID, 1, 0);

                if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit3_ElumMountBegin))
                {
                    ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAneprmntAOResID, 1, 0);
                }
            }

            if (field_114_gnFrame <= static_cast<s32>(sGnFrame))
            {
                if (mHealth > FP_FromInteger(0) || gAbeInvulnerableCheat_5076E4)
                {
                    mCurrentMotion = eAbeMotions::Motion_130_KnockForwardGetUp_429560;
                }
                else
                {
                    ToDieFinal_42C400();
                }
            }
        }
    }
}

void Abe::Motion_129_RollingKnockForward_4294F0()
{
    if (field_10_anim.field_92_current_frame == 12)
    {
        FallOnBombs_4231B0();
    }

    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        if (field_114_gnFrame <= static_cast<s32>(sGnFrame))
        {
            if (mHealth > FP_FromInteger(0) || gAbeInvulnerableCheat_5076E4)
            {
                mCurrentMotion = eAbeMotions::Motion_130_KnockForwardGetUp_429560;
            }
            else
            {
                ToDieFinal_42C400();
            }
        }
    }
}

void Abe::Motion_130_KnockForwardGetUp_429560()
{
    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_131_LiftUseUp_42F150()
{
    mCurrentMotion = MoveLiftUpOrDown_42F190(FP_FromInteger(-4));
}

void Abe::Motion_132_LiftUseDown_42F170()
{
    mCurrentMotion = MoveLiftUpOrDown_42F190(FP_FromInteger(4));
}

void Abe::Motion_133_LiftGrabBegin_42EF20()
{
    auto pLiftPoint = static_cast<LiftPoint*>(mLiftPoint);
    pLiftPoint->Move(FP_FromInteger(0), FP_FromInteger(0), 0);

    field_B8_vely = FP_FromInteger(0);
    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (Input().IsAnyPressed(sInputKey_Up_4C6598))
        {
            if (!pLiftPoint->OnTopFloor())
            {
                mCurrentMotion = eAbeMotions::Motion_131_LiftUseUp_42F150;
                return;
            }
        }
        else if (Input().IsAnyPressed(sInputKey_Down_4C659C))
        {
            if (!pLiftPoint->OnBottomFloor())
            {
                mCurrentMotion = eAbeMotions::Motion_132_LiftUseDown_42F170;
                return;
            }
        }
        mCurrentMotion = eAbeMotions::Motion_135_LiftGrabIdle_42F000;
    }
}

void Abe::Motion_134_LiftGrabEnd_42EFE0()
{
    field_B8_vely = FP_FromInteger(0);
    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_135_LiftGrabIdle_42F000()
{
    FollowLift_42EE90();

    auto pLiftPoint = static_cast<LiftPoint*>(mLiftPoint);
    pLiftPoint->Move(FP_FromInteger(0), FP_FromInteger(0), 0);

    field_B8_vely = FP_FromInteger(0);

    if (gBeeInstanceCount_5076B0 > 0 && gBeesNearAbe_5076AC)
    {
        mCurrentMotion = eAbeMotions::Motion_141_BeesStrugglingOnLift_42F390;
    }
    else
    {
        if (Input().IsAnyPressed(sInputKey_Up_4C6598))
        {
            if (!pLiftPoint->OnTopFloor())
            {
                mCurrentMotion = eAbeMotions::Motion_131_LiftUseUp_42F150;
            }
        }
        else if (Input().IsAnyPressed(sInputKey_Down_4C659C))
        {
            if (!pLiftPoint->OnBottomFloor())
            {
                mCurrentMotion = eAbeMotions::Motion_132_LiftUseDown_42F170;
            }
        }
        else
        {
            if (pLiftPoint->OnAnyFloor())
            {
                mCurrentMotion = eAbeMotions::Motion_134_LiftGrabEnd_42EFE0;
            }
        }
    }
}

void Abe::Motion_136_ElumMountEnd_42E110()
{
    switch (field_10_anim.field_92_current_frame)
    {
        case 0:
            if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit2_bSfxPlaying))
            {
                field_2AA_flags.Set(Flags_2AA::e2AA_Bit2_bSfxPlaying);
                SFX_Play_Mono(SoundEffect::AbeGenericMovement_37, 0, this);
            }
            break;

        case 5:
            if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit2_bSfxPlaying))
            {
                field_2AA_flags.Set(Flags_2AA::e2AA_Bit2_bSfxPlaying);
                Environment_SFX_42A220(EnvironmentSfx::eExhaustingElumMount_16, 0, 0x7FFF, this);
            }
            break;

        case 12:
            if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit2_bSfxPlaying))
            {
                field_2AA_flags.Set(Flags_2AA::e2AA_Bit2_bSfxPlaying);
                Environment_SFX_42A220(EnvironmentSfx::eMountElumSmackNoise_17, 0, 0x7FFF, this);
                SFX_Play_Mono(SoundEffect::MountingElum_38, 0, this);
            }
            break;

        case 15:
            if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit2_bSfxPlaying))
            {
                field_2AA_flags.Set(Flags_2AA::e2AA_Bit2_bSfxPlaying);
                Environment_SFX_42A220(EnvironmentSfx::eElumGetMountedNoise_18, 0, 0x7FFF, this);
            }
            break;

        default:
            field_2AA_flags.Clear(Flags_2AA::e2AA_Bit2_bSfxPlaying);
            break;
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (!field_104_pending_resource_count)
        {
            field_1A4_resources.res[46] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeWElmAOResID_100, 1, 0);
            field_1A4_resources.res[58] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kElumUnknownAOResID_112, 1, 0);
            mCurrentMotion = eAbeMotions::Motion_103_ElumIdle_42DCD0;
            sControlledCharacter_50767C = gElum_507680;
            MusicController::static_PlayMusic(MusicController::MusicTypes::eAbeOnElum_1, nullptr, 0, 0);
            sActiveHero_507678->field_D0_pShadow->field_14_flags.Clear(Shadow::Flags::eBit2_Enabled);
            Environment_SFX_42A220(EnvironmentSfx::eAbeMountedElumNoise_19, 0, 0x7FFF, this);
        }
    }
}

void Abe::Motion_137_ElumUnmountBegin_42E2B0()
{
    if (!field_104_pending_resource_count && field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        while (!ResourceManager::FreeResource_455550(field_1A4_resources.res[58]))
        {
            // Empty
        }

        field_1A4_resources.res[58] = nullptr;
        field_104_pending_resource_count = 3;

        ResourceManager::LoadResourceFile("ABEBSIC.BAN", BaseAliveGameObject::OnResourceLoaded_4019A0, this);
        ResourceManager::LoadResourceFile("ANEPRMNT.BAN", BaseAliveGameObject::OnResourceLoaded_4019A0, this);
        ResourceManager::LoadResourceFile("ABENOELM.BND", BaseAliveGameObject::OnResourceLoaded_4019A0, this);

        if (!ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeommAOResID, FALSE, FALSE))
        {
            field_104_pending_resource_count++;
            ResourceManager::LoadResourceFile("ABEOMM.BAN", BaseAliveGameObject::OnResourceLoaded_4019A0, this);
        }
        mCurrentMotion = eAbeMotions::Motion_138_ElumUnmountEnd_42E390;
    }
}

void Abe::Motion_138_ElumUnmountEnd_42E390()
{
    switch (field_10_anim.field_92_current_frame)
    {
        case 4:
            if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit2_bSfxPlaying))
            {
                field_2AA_flags.Set(Flags_2AA::e2AA_Bit2_bSfxPlaying);
                SFX_Play_Mono(SoundEffect::AbeGenericMovement_37, 17, this);
            }
            break;

        case 12:
            if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit2_bSfxPlaying))
            {
                field_2AA_flags.Set(Flags_2AA::e2AA_Bit2_bSfxPlaying);
                Environment_SFX_42A220(EnvironmentSfx::eExhaustingElumMount_16, 0, 0x7FFF, this);
            }
            break;

        case 19:
            if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit2_bSfxPlaying))
            {
                field_2AA_flags.Set(Flags_2AA::e2AA_Bit2_bSfxPlaying);
                Environment_SFX_42A220(EnvironmentSfx::eElumGetMountedNoise_18, 0, 0x7FFF, this);
            }
            break;

        case 20:
            if (!field_2AA_flags.Get(Flags_2AA::e2AA_Bit2_bSfxPlaying))
            {
                field_2AA_flags.Set(Flags_2AA::e2AA_Bit2_bSfxPlaying);
                SFX_Play_Mono(SoundEffect::MountingElum_38, 0, this);
            }
            break;

        default:
            field_2AA_flags.Clear(Flags_2AA::e2AA_Bit2_bSfxPlaying);
            break;
    }

    if (field_10_anim.field_92_current_frame >= 28 && field_104_pending_resource_count == 0)
    {
        field_1A4_resources.res[0] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbebasicAOResID, 1, 0);
        field_1A4_resources.res[61] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAneprmntAOResID, 1, 0);
        field_1A4_resources.res[10] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbefallAOResID, 1, 0);
        field_1A4_resources.res[38] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbeommAOResID, 1, 0);
        field_1A4_resources.res[9] = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbesmashAOResID, 1, 0);

        BaseAliveGameObjectCollisionLine = gElum_507680->BaseAliveGameObjectCollisionLine;

        if (mLiftPoint)
        {
            if (BaseAliveGameObjectCollisionLine->field_8_type != eLineTypes ::eUnknown_32 &&
                BaseAliveGameObjectCollisionLine->field_8_type != eLineTypes::eUnknown_36)
            {
                mPreviousMotion = mCurrentMotion;
                VOnTrapDoorOpen();
                mCurrentMotion = mPreviousMotion;
            }
        }
        else
        {
            if (BaseAliveGameObjectCollisionLine->field_8_type == eLineTypes::eUnknown_32 ||
                BaseAliveGameObjectCollisionLine->field_8_type == eLineTypes::eUnknown_36)
            {
                PSX_RECT bRect = {};
                VGetBoundingRect(&bRect, 1);
                bRect.y += 5;
                bRect.h += 5;
                VOnCollisionWith(
                    {bRect.x, bRect.y},
                    {bRect.w, bRect.h},
                    ObjListPlatforms_50766C,
                    1,
                    (TCollisionCallBack) &BaseAliveGameObject::OnTrapDoorIntersection_401C10);
            }
        }
        sControlledCharacter_50767C = sActiveHero_507678;
        MusicController::static_PlayMusic(MusicController::MusicTypes::eType0, this, 0, 0);
        sActiveHero_507678->field_D0_pShadow->field_14_flags.Clear(Shadow::Flags::eBit2_Enabled);
        ToIdle_422D50();
    }
}

void Abe::Motion_139_ElumMountBegin_42E090()
{
    if (!field_104_pending_resource_count && field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        while (!ResourceManager::FreeResource_455550(field_1A4_resources.res[61]))
        {
            // Empty
        }

        field_1A4_resources.res[61] = {};
        field_104_pending_resource_count = 1;

        ResourceManager::LoadResourceFile("ABEWELM.BND", BaseAliveGameObject::OnResourceLoaded_4019A0, this);
        VOnTrapDoorOpen();
        mCurrentMotion = eAbeMotions::Motion_136_ElumMountEnd_42E110;
    }
}

void Abe::Motion_140_BeesStruggling_423F30()
{
    Motion_0_Idle_423520();
    if ((!gBeeInstanceCount_5076B0 || !gBeesNearAbe_5076AC) && mCurrentMotion == eAbeMotions::Motion_140_BeesStruggling_423F30)
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_141_BeesStrugglingOnLift_42F390()
{
    LiftPoint* pLiftPoint = static_cast<LiftPoint*>(mLiftPoint);

    pLiftPoint->Move(FP_FromInteger(0), FP_FromInteger(12), 0);
    if (pLiftPoint)
    {
        field_B8_vely = pLiftPoint->field_B8_vely;
        if (pLiftPoint->mBaseGameObjectFlags.Get(Options::eDead))
        {
            VOnTrapDoorOpen();
            field_2A8_flags.Set(Flags_2A8::e2A8_Bit1);
        }
        SetActiveCameraDelayedFromDir_401C90();
    }

    field_B8_vely = pLiftPoint->field_B8_vely;

    if (pLiftPoint->OnBottomFloor())
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_142_RockThrowStandingHold_429CE0()
{
    if (field_10_anim.field_92_current_frame >= 4)
    {
        if (Input().IsAnyPressed(sInputKey_Right_4C6590 | sInputKey_Left_4C6594 | sInputKey_Up_4C6598 | sInputKey_Down_4C659C))
        {
            if (Input().IsAnyPressed(sInputKey_Right_4C6590))
            {
                if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    field_19D_throw_direction = 0;
                }
                else
                {
                    field_19D_throw_direction = 2;
                }
            }
            else if (Input().IsAnyPressed(sInputKey_Left_4C6594))
            {
                if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                {
                    field_19D_throw_direction = 2;
                }
                else
                {
                    field_19D_throw_direction = 0;
                }
            }
            else if (Input().IsAnyPressed(sInputKey_Up_4C6598))
            {
                field_19D_throw_direction = 1;
            }
            else
            {
                field_19D_throw_direction = 3;
            }
            mCurrentMotion = eAbeMotions::Motion_143_RockThrowStandingThrow_429FD0;
        }
    }

    if (Input().IsAnyReleased(sInputKey_ThrowItem_4C65B4))
    {
        field_198_pThrowable->VToDead();
        field_198_pThrowable = nullptr;
        mCurrentMotion = eAbeMotions::Motion_144_RockThrowStandingEnd_429DE0;
        if (!gInfiniteGrenades_5076EC)
        {
            field_19C_throwable_count++;
        }
    }
}

void Abe::Motion_143_RockThrowStandingThrow_429FD0()
{
    if (field_10_anim.field_92_current_frame == 0)
    {
        SFX_Play_Mono(SoundEffect::AirStream_28, 0, this);
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_144_RockThrowStandingEnd_429DE0()
{
    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_145_RockThrowCrouchingHold_428930()
{
    if (field_10_anim.field_92_current_frame >= 4)
    {
        if (Input().IsAnyPressed(sInputKey_Right_4C6590 | sInputKey_Left_4C6594 | sInputKey_Up_4C6598 | sInputKey_Down_4C659C))
        {
            field_19D_throw_direction = 4;
            mCurrentMotion = eAbeMotions::Motion_146_RockThrowCrouchingThrow_4289F0;
            if (field_198_pThrowable->mBaseGameObjectTypeId == ReliveTypes::eMeat)
            {
                field_19D_throw_direction = 5;
            }
        }
    }

    if (Input().IsAnyReleased(sInputKey_ThrowItem_4C65B4))
    {
        field_198_pThrowable->VToDead();
        field_198_pThrowable = nullptr;
        mCurrentMotion = eAbeMotions::Motion_19_CrouchIdle_4284C0;
        if (!gInfiniteGrenades_5076EC)
        {
            field_19C_throwable_count++;
        }
    }
}

void Abe::Motion_146_RockThrowCrouchingThrow_4289F0()
{
    FollowLift_42EE90();

    if (!field_10_anim.field_92_current_frame)
    {
        SFX_Play_Mono(SoundEffect::AirStream_28, 0, this);
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        mCurrentMotion = eAbeMotions::Motion_19_CrouchIdle_4284C0;
    }
}

void Abe::Motion_147_ShotRolling_4295C0()
{
    ElumFree_4228F0();

    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    Motion_3_Fall_42E7F0();

    if (mCurrentMotion != eAbeMotions::Motion_147_ShotRolling_4295C0 && !gAbeInvulnerableCheat_5076E4)
    {
        mCurrentMotion = eAbeMotions::Motion_147_ShotRolling_4295C0;
        BaseAliveGameObjectCollisionLine = nullptr;
        mBaseAnimatedWithPhysicsGameObject_YPos += (field_BC_sprite_scale * FP_FromInteger(4));
    }

    if (!gMap.Is_Point_In_Current_Camera_4449C0(
            field_B2_lvl_number,
            field_B0_path_number,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos,
            0))
    {
        if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
        {
            mBaseAnimatedWithPhysicsGameObject_YPos += FP_FromInteger(240);
            Mudokon_SFX_42A4D0(MudSounds::eDeathDropScream_17, 0, 0, this);
            ToDeathDropFall_42C3D0();
        }
    }
}

void Abe::Motion_148_Shot_4296A0()
{
    ElumFree_4228F0();

    Event_Broadcast(kEventNoise, this);
    Event_Broadcast(kEventSuspiciousNoise, this);

    Motion_3_Fall_42E7F0();

    if (mCurrentMotion != eAbeMotions::Motion_148_Shot_4296A0 && !gAbeInvulnerableCheat_5076E4)
    {
        mCurrentMotion = eAbeMotions::Motion_148_Shot_4296A0;
        BaseAliveGameObjectCollisionLine = nullptr;
        mBaseAnimatedWithPhysicsGameObject_YPos += (field_BC_sprite_scale * FP_FromInteger(4));
    }

    if (!gMap.Is_Point_In_Current_Camera_4449C0(
            field_B2_lvl_number,
            field_B0_path_number,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos,
            0))
    {
        if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
        {
            mBaseAnimatedWithPhysicsGameObject_YPos += FP_FromInteger(240);
            Mudokon_SFX_42A4D0(MudSounds::eDeathDropScream_17, 0, 0, this);
            ToDeathDropFall_42C3D0();
        }
    }
}

void Abe::Motion_149_PickupItem_42A030()
{
    if (field_10_anim.field_92_current_frame == 7)
    {
        SFX_Play_Mono(SoundEffect::PickupItem_33, 0, this);
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        mCurrentMotion = eAbeMotions::Motion_19_CrouchIdle_4284C0;
    }

    if (sActiveHero_507678->field_10_anim.field_92_current_frame >= 5)
    {
        if (field_15C_pThrowable)
        {
            field_15C_pThrowable->mBaseGameObjectRefCount--;
            field_15C_pThrowable->VOnPickUpOrSlapped();
            field_15C_pThrowable = nullptr;
        }
    }
}

void Abe::New_RandomizedChant_Particle()
{
    const auto xpos = mBaseAnimatedWithPhysicsGameObject_XPos + field_BC_sprite_scale * FP_FromInteger(40 * Math_NextRandom() / 256 - 20);
    const auto ypos = mBaseAnimatedWithPhysicsGameObject_YPos - (field_BC_sprite_scale * FP_FromInteger(30 * Math_NextRandom() / 256 + 30));
    New_Chant_Particle_4198E0(
        xpos,
        ypos,
        field_BC_sprite_scale,
        Layer::eLayer_0);
}

void Abe::Motion_150_Chant_42FD50()
{
    FollowLift_42EE90();
    if (field_110_state.chant != ChantStates::eWaitForUnpossessing_3 && field_110_state.chant != ChantStates::eUnpossessing_4)
    {
        SND_SEQ_PlaySeq_4775A0(SeqId::eMudokonChant1_11, 0, 0);
    }

    switch (field_110_state.chant)
    {
        case ChantStates::eIdleChanting_0:
        {
            Event_Broadcast(kEventSpeaking, this);
            Event_Broadcast(kEventAbeOhm, this);
            auto pObjToPossess = FindObjectToPossess_421410();
            if (field_168_ring_pulse_timer)
            {
                if (!field_16C_bHaveShrykull)
                {
                    PSX_RECT rect = {};
                    VGetBoundingRect(
                        &rect,
                        1);
                    AbilityRing::Factory(
                        FP_FromInteger((rect.w + rect.x) / 2),
                        FP_FromInteger((rect.h + rect.y) / 2),
                        RingTypes::eExplosive_Emit_1);
                    field_168_ring_pulse_timer = 0;
                }
            }

            if ((field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame)
                 || field_10_anim.field_92_current_frame == 3)
                && !Input_IsChanting())
            {
                mCurrentMotion = eAbeMotions::Motion_151_ChantEnd_430530;
                if (field_188_pOrbWhirlWind)
                {
                    field_188_pOrbWhirlWind->ToStop();
                    field_188_pOrbWhirlWind = nullptr;
                }
                return;
            }
            if (!(sGnFrame % 4))
            {
                New_RandomizedChant_Particle();
            }
            if (static_cast<s32>(sGnFrame) >= field_114_gnFrame - 70)
            {
                if (pObjToPossess)
                {
                    if (!field_188_pOrbWhirlWind)
                    {
                        FP xPos = {};
                        if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit5_FlipX))
                        {
                            xPos = mBaseAnimatedWithPhysicsGameObject_XPos + FP_FromInteger(-4);
                        }
                        else
                        {
                            xPos = mBaseAnimatedWithPhysicsGameObject_XPos + FP_FromInteger(4);
                        }
                        field_188_pOrbWhirlWind = ao_new<OrbWhirlWind>(
                            xPos,
                            mBaseAnimatedWithPhysicsGameObject_YPos - field_BC_sprite_scale * FP_FromInteger(38),
                            field_BC_sprite_scale);;
                    }
                }
                else
                {
                    field_114_gnFrame = sGnFrame + 70;
                    if (field_188_pOrbWhirlWind)
                    {
                        field_188_pOrbWhirlWind->ToStop();
                        field_188_pOrbWhirlWind = nullptr;
                    }
                }
            }

            if (static_cast<s32>(sGnFrame) > field_114_gnFrame)
            {
                field_18C_pObjToPossess = pObjToPossess;
                if (field_18C_pObjToPossess)
                {
                    field_18C_pObjToPossess->mBaseGameObjectRefCount++;
                    SFX_Play_Pitch(SoundEffect::PossessEffect_21, 0, -600, 0);
                    field_114_gnFrame = sGnFrame + 30;
                    field_110_state.chant = ChantStates::ePossessVictim_1;

                    PSX_RECT rect = {};
                    field_18C_pObjToPossess->VGetBoundingRect(
                        &rect,
                        1);
                    field_188_pOrbWhirlWind->ToSpin(
                        FP_FromInteger((rect.w + rect.x) / 2),
                        FP_FromInteger((rect.h + rect.y) / 2),
                        pObjToPossess);

                    ao_new<PossessionFlicker>(sActiveHero_507678, 30, 128, 255, 255);
                }
            }
            break;
        }
        case ChantStates::ePossessVictim_1:
        {
            if (static_cast<s32>(sGnFrame) > field_114_gnFrame)
            {
                field_110_state.chant = ChantStates::ePossessedVictim_2;
                return;
            }
            if (field_18C_pObjToPossess)
            {
                if (field_18C_pObjToPossess->mBaseGameObjectFlags.Get(Options::eDead))
                {
                    field_18C_pObjToPossess->mBaseGameObjectRefCount--;
                    field_18C_pObjToPossess = nullptr;
                }
            }
            if (field_18C_pObjToPossess)
            {
                if (field_18C_pObjToPossess->Is_In_Current_Camera_417CC0() == CameraPos::eCamCurrent_0)
                {
                    return;
                }
                mCurrentMotion = eAbeMotions::Motion_151_ChantEnd_430530;
                field_18C_pObjToPossess->mBaseGameObjectRefCount--;
                field_18C_pObjToPossess = nullptr;
            }
            else
            {
                mCurrentMotion = eAbeMotions::Motion_151_ChantEnd_430530;
            }
            if (field_188_pOrbWhirlWind)
            {
                field_188_pOrbWhirlWind->ToStop();
                field_188_pOrbWhirlWind = nullptr;
            }
            break;
        }
        case ChantStates::ePossessedVictim_2:
        {
            Event_Broadcast(kEventSpeaking, this);
            Event_Broadcast(kEventAbeOhm, this);
            field_188_pOrbWhirlWind = nullptr;
            if (field_18C_pObjToPossess)
            {
                if (field_18C_pObjToPossess->mBaseGameObjectFlags.Get(Options::eDead))
                {
                    field_18C_pObjToPossess->mBaseGameObjectRefCount--;
                    field_18C_pObjToPossess = nullptr;
                }
            }
            if (field_18C_pObjToPossess)
            {
                sControlledCharacter_50767C = field_18C_pObjToPossess;
                field_18C_pObjToPossess->VPossessed();
                field_18C_pObjToPossess->mBaseGameObjectRefCount--;
                field_18C_pObjToPossess = nullptr;
                if (sControlledCharacter_50767C->mBaseGameObjectTypeId == ReliveTypes::eSlig)
                {
                    field_2A8_flags.Set(Flags_2A8::e2A8_Bit11_bLaughAtChantEnd);
                }

                ao_new<PossessionFlicker>(sControlledCharacter_50767C, 60, 128, 255, 255);

                SND_Seq_Stop_477A60(SeqId::eMudokonChant1_11);
                SFX_Play_Pitch(SoundEffect::PossessEffect_21, 70, 400, 0);
                field_110_state.chant = ChantStates::eWaitForUnpossessing_3;
            }
            else if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                mCurrentMotion = eAbeMotions::Motion_151_ChantEnd_430530;
            }
            break;
        }
        case ChantStates::eWaitForUnpossessing_3:
        {
            if (sControlledCharacter_50767C == this)
            {
                ao_new<PossessionFlicker>(sControlledCharacter_50767C, 15, 128, 255, 255);

                field_110_state.chant = ChantStates::eUnpossessing_4;
                field_114_gnFrame = sGnFrame + 15;
            }
            break;
        }
        case ChantStates::eUnpossessing_4:
        {
            if (!(sGnFrame % 4))
            {
                New_RandomizedChant_Particle();
            }
            if (static_cast<s32>(sGnFrame) > field_114_gnFrame)
            {
                if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
                {
                    mCurrentMotion = eAbeMotions::Motion_151_ChantEnd_430530;
                }
            }
            break;
        }
        case ChantStates::eChantingForBirdPortal_6:
        {
            Event_Broadcast(kEventSpeaking, this);
            Event_Broadcast(kEventAbeOhm, this);
            if (!(sGnFrame % 4))
            {
                New_RandomizedChant_Particle();
            }

            break;
        }
        default:
            return;
    }
}

void Abe::Motion_151_ChantEnd_430530()
{
    SND_Seq_Stop_477A60(SeqId::eMudokonChant1_11);

    FollowLift_42EE90();

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        if (field_2A8_flags.Get(Flags_2A8::e2A8_Bit11_bLaughAtChantEnd))
        {
            mCurrentMotion = eAbeMotions::Motion_12_Speak_42FBD0;
            Mudokon_SFX_42A4D0(MudSounds::eLaugh1_8, 0, 0, this);
            field_2A8_flags.Clear(Flags_2A8::e2A8_Bit11_bLaughAtChantEnd);
        }
        else
        {
            ToIdle_422D50();
        }
    }
}

void Abe::Motion_152_ElumFallOffEdge_42E030()
{
    // Empty
}

void Abe::Motion_153_ElumFall_42E040()
{
    // Empty
}

void Abe::Motion_154_ElumLand_42E050()
{
    // Empty
}

void Abe::Motion_155_ElumJumpToFall_42E060()
{
    // Empty
}

void Abe::Motion_156_DoorEnter_42D370()
{
    switch (field_110_state.door)
    {
        case AbeDoorStates::eAbeComesIn_0:
        {
            if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
            {
                field_110_state.door = AbeDoorStates::eWaitABit_2;
                field_10_anim.mAnimFlags.Clear(AnimFlags::eBit3_Render);
                field_118_timer = sGnFrame + 3;
            }
            return;
        }
        case AbeDoorStates::eUnused_1:
        {
            if (field_158_pDeathFadeout->field_6E_bDone)
            {
                field_110_state.door = AbeDoorStates::eWaitABit_2;
                field_118_timer = sGnFrame + 5;
            }
            ALIVE_FATAL("never expected AbeDoorStates::eUnused_1 to be called");
            return;
        }
        case AbeDoorStates::eWaitABit_2:
        {
            if (field_118_timer <= static_cast<s32>(sGnFrame))
            {
                field_110_state.door = AbeDoorStates::eClearTlvIds_3;
                field_118_timer = sGnFrame + 3;
            }
            return;
        }
        case AbeDoorStates::eClearTlvIds_3:
        {
            if (field_118_timer <= static_cast<s32>(sGnFrame))
            {
                field_110_state.door = AbeDoorStates::eSetNewActiveCamera_4;
                auto pTlv = static_cast<Path_ResetPath*>(gMap.TLV_Get_At_446260(
                    FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
                    FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                    FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
                    FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                    TlvTypes::ResetPath_115));
                BaseAliveGameObjectPathTLV = pTlv;
                if (pTlv)
                {
                    if (pTlv->field_18_clearIds)
                    {
                        for (s16 i = pTlv->field_1A_from; i <= pTlv->field_1C_to; i++)
                        {
                            if (i != pTlv->field_1E_exclude && i > 1)
                            {
                                SwitchStates_Set(i, 0);
                            }
                        }
                    }
                    if (pTlv->field_20_clearObjects)
                    {
                        gMap.sub_447430(pTlv->field_22_path);
                    }
                }
            }
            return;
        }
        case AbeDoorStates::eSetNewActiveCamera_4:
        {
            auto pDoorTlv = static_cast<Path_Door*>(gMap.TLV_Get_At_446260(
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_XPos),
                FP_GetExponent(mBaseAnimatedWithPhysicsGameObject_YPos),
                TlvTypes::Door_6));
            BaseAliveGameObjectPathTLV = pDoorTlv;
            gMap.field_1E_door = 1;
            const auto changeEffect = kPathChangeEffectToInternalScreenChangeEffect_4CDC78[pDoorTlv->field_3A_wipe_effect];
            s16 flag = 0;
            if (changeEffect == CameraSwapEffects::ePlay1FMV_5 || changeEffect == CameraSwapEffects::eUnknown_11)
            {
                flag = 1;
            }
            gMap.SetActiveCam(
                MapWrapper::FromAO(pDoorTlv->field_18_level),
                pDoorTlv->field_1A_path,
                pDoorTlv->field_1C_camera,
                changeEffect,
                pDoorTlv->field_3C_movie_number,
                flag);
            field_110_state.door = AbeDoorStates::eSetNewAbePosition_5;
            field_196_door_id = pDoorTlv->field_24_target_door_number;
            return;
        }
        case AbeDoorStates::eSetNewAbePosition_5:
        {
            field_B2_lvl_number = gMap.mCurrentLevel;
            field_B0_path_number = gMap.mCurrentPath;
            gMap.field_1E_door = 0;
            auto pPathDoor = static_cast<Path_Door*>(gMap.TLV_First_Of_Type_In_Camera(TlvTypes::Door_6, 0));
            BaseAliveGameObjectPathTLV = pPathDoor;

            while (pPathDoor->field_20_door_number != field_196_door_id)
            {
                pPathDoor = static_cast<Path_Door*>(Path_TLV::TLV_Next_Of_Type_446500(BaseAliveGameObjectPathTLV, TlvTypes::Door_6));
                BaseAliveGameObjectPathTLV = pPathDoor;
                
                if (!BaseAliveGameObjectPathTLV)
                {
                    ALIVE_FATAL("Couldn't find target door. If this is a custom level, check if the level, path and camera is correct.");
                }
            }

            if (pPathDoor->field_26_start_state == DoorStates::eOpen_0)
            {
                if (pPathDoor->field_1E_scale == Scale_short::eHalf_1)
                {
                    field_BC_sprite_scale = FP_FromDouble(0.5);
                    field_10_anim.mRenderLayer = Layer::eLayer_AbeMenu_Half_13;
                    field_C6_scale = 0;
                }
                else
                {
                    field_BC_sprite_scale = FP_FromInteger(1);
                    field_10_anim.mRenderLayer = Layer::eLayer_AbeMenu_32;
                    field_C6_scale = 1;
                }
            }
            else if (pPathDoor->field_26_start_state == DoorStates::eClosed_1 || pPathDoor->field_26_start_state == DoorStates::eHubDoorClosed_2)
            {
                if (gMap.mCurrentLevel != EReliveLevelIds::eRuptureFarmsReturn)
                {
                    field_BC_sprite_scale = FP_FromDouble(0.5);
                    field_C6_scale = 0;
                }
                else
                {
                    field_BC_sprite_scale = FP_FromInteger(1);
                    field_C6_scale = 1;
                }
            }
            field_10_anim.mAnimFlags.Set(AnimFlags::eBit5_FlipX, pPathDoor->field_46_abe_direction == XDirection_short::eRight_1);
            mBaseAnimatedWithPhysicsGameObject_XPos = FP_FromInteger((BaseAliveGameObjectPathTLV->field_14_bottom_right.field_0_x - BaseAliveGameObjectPathTLV->field_10_top_left.field_0_x) / 2)
                          + FP_FromInteger(BaseAliveGameObjectPathTLV->field_10_top_left.field_0_x);
            MapFollowMe_401D30(TRUE);

            FP hitX = {};
            FP hitY = {};
            if (sCollisions->RayCast(
                    mBaseAnimatedWithPhysicsGameObject_XPos,
                    FP_FromInteger(BaseAliveGameObjectPathTLV->field_10_top_left.field_2_y),
                    mBaseAnimatedWithPhysicsGameObject_XPos,
                    FP_FromInteger(BaseAliveGameObjectPathTLV->field_14_bottom_right.field_2_y),
                    &BaseAliveGameObjectCollisionLine,
                    &hitX,
                    &hitY,
                    field_BC_sprite_scale != FP_FromDouble(0.5) ? 7 : 0x70))
            {
                mBaseAnimatedWithPhysicsGameObject_YPos = hitY;
            }

            field_110_state.door = AbeDoorStates::eAbeComesOut_6;
            field_118_timer = sGnFrame + 30;
            return;
        }
        case AbeDoorStates::eAbeComesOut_6:
        {
            if (field_118_timer <= static_cast<s32>(sGnFrame))
            {
                field_10_anim.mAnimFlags.Set(AnimFlags::eBit3_Render);
                field_110_state.door = AbeDoorStates::eAbeComesIn_0;
                mCurrentMotion = eAbeMotions::Motion_157_DoorExit_42D780;
            }
            return;
        }
        default:
            return;
    }
}

void Abe::Motion_157_DoorExit_42D780()
{
    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        BaseAliveGameObjectPathTLV = gMap.TLV_Get_At_446060(
            nullptr,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos,
            mBaseAnimatedWithPhysicsGameObject_XPos,
            mBaseAnimatedWithPhysicsGameObject_YPos);

        VOn_TLV_Collision(BaseAliveGameObjectPathTLV);

        ToIdle_422D50();
    }
}

void Abe::Motion_158_ElumKnockback_42E070()
{
    // Empty
}

void Abe::Motion_159_Idle_RubEyes_423360()
{
    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        ToIdle_422D50();
    }
}

void Abe::Motion_160_Idle_Stretch_Arms_4233A0()
{
    Motion_159_Idle_RubEyes_423360();
}

void Abe::Motion_161_Idle_Yawn_4233E0()
{
    Motion_159_Idle_RubEyes_423360();
}

void Abe::Motion_162_ToShrykull_42F410()
{
    if (field_110_state.raw == 0)
    {
        if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
        {
            field_10_anim.mAnimFlags.Clear(AnimFlags::eBit2_Animate);
            field_10_anim.mAnimFlags.Clear(AnimFlags::eBit3_Render);

            field_110_state.raw = 1;

            ao_new<Shrykull>();
        }
    }
}

void Abe::Motion_163_ShrykullEnd_42F520()
{
    if (field_114_gnFrame)
    {
        field_114_gnFrame = field_114_gnFrame - 1;
    }
    else if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit12_ForwardLoopCompleted))
    {
        if (!field_168_ring_pulse_timer)
        {
            ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kAbemorphAOResID, 0, 0));
            ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kShrmorphAOResID, 0, 0));
            ResourceManager::FreeResource_455550(ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Animation, AOResourceID::kSplineAOResID, 0, 0));
        }

        mCurrentMotion = eAbeMotions::Motion_9_Speak_42FA50;
        Mudokon_SFX_42A4D0(MudSounds::eLaugh1_8, 0, 0, this);
    }
}

void Abe::Motion_164_PoisonGasDeath_42A120()
{
    switch (field_10_anim.field_92_current_frame)
    {
        case 0:
            SFX_Play_Pitch(SoundEffect::Choke_98, 127, 128, 0);
            break;
        case 9:
            SFX_Play_Pitch(SoundEffect::Choke_98, 127, 384, 0);
            break;
        case 28:
            SFX_Play_Pitch(SoundEffect::Choke_98, 127, 640, 0);
            break;
        case 32:
            Environment_SFX_42A220(EnvironmentSfx::eHitGroundSoft_6, 80, 0, this);
            break;
        case 50:
            Environment_SFX_42A220(EnvironmentSfx::eHitGroundSoft_6, 100, -200, this);
            break;
        case 53:
            Environment_SFX_42A220(EnvironmentSfx::eHitGroundSoft_6, 50, -200, this);
            break;
        default:
            break;
    }

    if (field_10_anim.mAnimFlags.Get(AnimFlags::eBit18_IsLastFrame))
    {
        const s32 v2 = field_114_gnFrame;
        field_114_gnFrame--;
        if (v2 == 0)
        {
            ToDieFinal_42C400();
        }
    }
}

} // namespace AO
