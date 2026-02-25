#pragma once

#include "pas2c.h"

#include "SDLh.h"
#include "uConsts.h"
#include "uFloat.h"
#include "uTypes.h"
enum{MAXBONUS = 1024};
enum{afTrackFall = 0x00000001};
enum{afErasesLand = 0x00000002};
enum{afSetSkip = 0x00000004};
enum{afIgnoreMe = 0x00000008};
enum{BadTurn = (-2147483648 / 4)};
typedef struct __TTarget {
            TPoint Point;
            LongInt Score;
            LongInt Radius;
            LongWord State;
            real Density;
            boolean skip;
            boolean matters;
            boolean dead;
            TGearType Kind;
        } TTarget;
typedef struct __TTargets {
            LongWord Count;
            TTarget ar[256];
            boolean reset;
        } TTargets;
typedef enum {jmpNone = 0x0,
              jmpHJump = 0x1,
              jmpLJump = 0x2} TJumpType;
typedef struct __TGoInfo {
            LongWord Ticks;
            LongWord FallPix;
            TJumpType JumpType;
        } TGoInfo;
typedef struct __TBonus {
            LongInt X;
            LongInt Y;
            LongInt Radius;
            LongInt Score;
        } TBonus;
typedef struct __TBonuses {
            boolean activity;
            LongInt Count;
            TBonus ar[MAXBONUS];
        } TBonuses;
typedef struct __Twalkbonuses {
            LongWord Count;
            TBonus ar[(MAXBONUS / 8)];
        } Twalkbonuses;
void uaimisc_initModule();
void uaimisc_freeModule();
void uaimisc_FillTargets();
void uaimisc_ResetTargets();
void uaimisc_AddBonus(LongInt x,LongInt y,LongWord r,LongInt s);
void uaimisc_FillBonuses(boolean isAfterAttack);
void uaimisc_AwareOfExplosion(LongInt x,LongInt y,LongInt r);
LongInt uaimisc_RatePlace(PGear Gear);
real uaimisc_CheckWrap(real x);
boolean uaimisc_TestColl(LongInt x,LongInt y,LongInt r);
boolean uaimisc_TestCollHogsOrObjects(LongInt x,LongInt y,LongInt r);
boolean uaimisc_TestCollExcludingObjects(LongInt x,LongInt y,LongInt r);
boolean uaimisc_TestCollExcludingMe(PGear Me,LongInt x,LongInt y,LongInt r);
LongInt uaimisc_RateExplosion_4(PGear Me,LongInt x,LongInt y,LongInt r);
LongInt uaimisc_RateExplosion_5(PGear Me,LongInt x,LongInt y,LongInt r,LongWord Flags);
LongInt uaimisc_RealRateExplosion(PGear Me,LongInt x,LongInt y,LongInt r,LongWord Flags);
LongInt uaimisc_RateShove(PGear Me,LongInt x,LongInt y,LongInt r,LongInt power,LongInt kick,real gdX,real gdY,LongWord Flags);
LongInt uaimisc_RateShotgun(PGear Me,real gdX,real gdY,LongInt x,LongInt y);
LongInt uaimisc_RateSeduction(PGear Me);
LongInt uaimisc_RateResurrector(PGear Me);
LongInt uaimisc_RateHammer(PGear Me);
boolean uaimisc_HHGo(PGear Gear,PGear AltGear,TGoInfo (*GoInfo));
LongInt uaimisc_AIrndSign(LongInt num);
LongInt uaimisc_AIrndOffset(TTarget targ,LongWord Level);
extern PGear ThinkingHH;
extern TTargets Targets;
extern TBonuses bonuses;
extern Twalkbonuses walkbonuses;
enum{KillScore = 200};
enum{ResurrectScore = 100};
extern LongInt friendlyfactor;
extern real dmgMod;

string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TJumpType enumvar);