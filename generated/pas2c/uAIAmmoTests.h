#pragma once

#include "pas2c.h"

#include "uConsts.h"
#include "uFloat.h"
#include "uTypes.h"
#include "uAIMisc.h"
enum{amtest_Rare = 0x00000001};
enum{amtest_NoTarget = 0x00000002};
enum{amtest_MultipleAttacks = 0x00000004};
enum{amtest_NoTrackFall = 0x00000008};
enum{amtest_LaserSight = 0x00000010};
enum{amtest_NoVampiric = 0x00000020};
enum{amtest_NoInvulnerable = 0x00000040};
enum{amtest_NoLowGravity = 0x00000080};
extern real aiWindSpeed;
extern hwFloat aiGravity;
extern real aiGravityf;
extern boolean aiLaserSighting;
extern LongInt aiHogsInTeam;
typedef struct __TAttackParams {
            LongWord Time;
            LongWord Bounce;
            LongWord AttacksNum;
            LongInt Angle;
            LongInt Power;
            LongInt ExplX;
            LongInt ExplY;
            LongInt ExplR;
            LongInt AttackPutX;
            LongInt AttackPutY;
        } TAttackParams;
LongInt uaiammotests_TestBazooka(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestBee(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestSnowball(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestGrenade(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestMolotov(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestClusterBomb(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestWatermelon(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestDrillRocket(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestRCPlane(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestMortar(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestShotgun(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestDesertEagle(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestSniperRifle(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestBaseballBat(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestFirePunch(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestWhip(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestKamikaze(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestAirAttack(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestDrillStrike(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestMineStrike(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestSineGun(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestSMine(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestPiano(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestTeleport(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestHammer(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestResurrector(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestCake(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestSeduction(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestDynamite(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestMine(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestKnife(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestAirMine(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
LongInt uaiammotests_TestMinigun(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
typedef LongInt(*uaiammotests_TAmmoTestProc)(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags);
typedef struct __TAmmoTest {
            uaiammotests_TAmmoTestProc proc;
            LongWord flags;
        } TAmmoTest;
typedef TAmmoTest AmmoTests_tt[61];
extern AmmoTests_tt AmmoTests;

