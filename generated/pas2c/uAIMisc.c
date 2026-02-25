#include "fpcrtl.h"

#include "uAIMisc.h"
PGear ThinkingHH;
TTargets Targets;
TBonuses bonuses;
Twalkbonuses walkbonuses;
LongInt friendlyfactor = 300;
real dmgMod = 1.0;
#include "uCollisions.h"
#include "uVariables.h"
#include "uUtils.h"
#include "uGearsUtils.h"
#include "uAIAmmoTests.h"
#include "uLandUtils.h"
typedef struct __KnownExplosion_tt {
            LongInt X;
            LongInt Y;
            LongInt Radius;
        } KnownExplosion_tt;
static KnownExplosion_tt KnownExplosion = {
                                              .X = 0,
                                              .Y = 0,
                                              .Radius = 0
                                          };
void uaimisc_ResetTargets()
{
    LongWord i;
    if(Targets.reset)
    {
        {i = 0;
         LongWord i__end__ = Targets.Count;
         if (i <= i__end__) do {
                                   Targets.ar[i].dead = false;
                               } while(i++ != i__end__);}
    }
    Targets.reset = false;
};
void uaimisc_FillTargets()
{
    LongInt f;
    LongInt e;
    PGear Gear;
    Targets.Count = 0;
    Targets.reset = false;
    f = 0;
    e = 0;
    Gear = GearsList;
    while(Gear != NULL)
    {
        if((((((((Gear->Kind == gtHedgehog) && (Gear != ThinkingHH)) && (Gear->Health > Gear->Damage)) && !(*(*Gear->Hedgehog).Team).hasGone) || ((Gear->Kind == gtGrave) && (Gear->Health == 0))) || ((Gear->Kind == gtExplosives) && (Gear->Health > Gear->Damage))) || (((Gear->Kind == gtMine) && (Gear->Health == 0)) && (Gear->Damage < 35))) && (Targets.Count < 255))
        {
            {
                Targets.ar[Targets.Count].skip = false;
                Targets.ar[Targets.Count].dead = false;
                Targets.ar[Targets.Count].Kind = Gear->Kind;
                Targets.ar[Targets.Count].Radius = Gear->Radius;
                Targets.ar[Targets.Count].Density = ufloat_hwFloat2Float(Gear->Density) /(float) 3;
                Targets.ar[Targets.Count].State = Gear->State;
                Targets.ar[Targets.Count].matters = (Gear->AIHints & aihDoesntMatter) == 0;
                Targets.ar[Targets.Count].Point.x = ufloat_hwRound(Gear->X);
                Targets.ar[Targets.Count].Point.y = ufloat_hwRound(Gear->Y);
                if(Gear->Kind == gtHedgehog)
                {
                    if((*(*Gear->Hedgehog).Team).Clan == CurrentTeam->Clan)
                    {
                        Targets.ar[Targets.Count].Score = Gear->Damage - Gear->Health;
                        ++f;
                    }
                    else
                    {
                        Targets.ar[Targets.Count].Score = Gear->Health - Gear->Damage;
                        ++e;
                    }
                }
                else
                {
                    if(Gear->Kind == gtGrave)
                    {
                        if((*(*Gear->Hedgehog).Team).Clan == CurrentTeam->Clan)
                        {
                            Targets.ar[Targets.Count].Score = ResurrectScore;
                            ++f;
                        }
                        else
                        {
                            Targets.ar[Targets.Count].Score = -ResurrectScore;
                            ++e;
                        }
                    }
                    else
                    {
                        if(Gear->Kind == gtExplosives)
                        {
                            Targets.ar[Targets.Count].Score = Gear->Health - Gear->Damage;
                        }
                        else
                        {
                            if(Gear->Kind == gtMine)
                            {
                                Targets.ar[Targets.Count].Score = uutils_Max(0, 35 - Gear->Damage);
                            }
                        }
                    }
                }
            }
            ++Targets.Count;
        }
        Gear = Gear->NextGear;
    }
    if(e > f)
    {
        friendlyfactor = 300 + ((e - f) * 30);
    }
    else
    {
        friendlyfactor = uutils_Max(30, 300 - ((f * 80) / uutils_Max(1, e)));
    }
};
void uaimisc_AddBonus(LongInt x,LongInt y,LongWord r,LongInt s)
{
    if(bonuses.Count < MAXBONUS)
    {
        bonuses.ar[bonuses.Count].X = x;
        bonuses.ar[bonuses.Count].Y = y;
        bonuses.ar[bonuses.Count].Radius = r;
        bonuses.ar[bonuses.Count].Score = s;
        ++bonuses.Count;
    }
};
void uaimisc_AddWalkBonus(LongInt x,LongInt y,LongWord r,LongInt s)
{
    if(walkbonuses.Count < (MAXBONUS / 8))
    {
        walkbonuses.ar[walkbonuses.Count].X = x;
        walkbonuses.ar[walkbonuses.Count].Y = y;
        walkbonuses.ar[walkbonuses.Count].Radius = r;
        walkbonuses.ar[walkbonuses.Count].Score = s;
        ++walkbonuses.Count;
    }
};
void uaimisc_FillBonuses(boolean isAfterAttack)
{
    PGear Gear;
    PClan MyClan;
    LongInt i;
    bonuses.Count = 0;
    bonuses.activity = false;
    MyClan = (*(*ThinkingHH->Hedgehog).Team).Clan;
    Gear = GearsList;
    while(Gear != NULL)
    {
        switch(Gear->Kind)
        {case gtAirAttack:
         case gtAirBomb:
         case gtBall:
         case gtBee:
         case gtBirdy:
         case gtClusterBomb:
         case gtCake:
         case gtCluster:
         case gtDrill:
         case gtEgg:
         case gtGasBomb:
         case gtGrenade:
         case gtHellishBomb:
         case gtPiano:
         case gtPoisonCloud:
         case gtRCPlane:
         case gtMelonPiece:
         case gtMolotov:
         case gtMortar:
         case gtNapalmBomb:
         case gtShell:
         case gtSnowball:
         case gtWatermelon:bonuses.activity = true;
                           break;
         case gtCase:if((Gear->AIHints & aihDoesntMatter) == 0)
                     {
                         uaimisc_AddBonus(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y) + 3, 37, 25);
                     }
                     break;
         case gtFlame:if((Gear->State & gsttmpFlag) != 0)
                      {
                          uaimisc_AddBonus(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), 20, -50);
                      }
                      break;
         case gtMine:{
                         if((Gear->State & gstMoving) != 0)
                         {
                             bonuses.activity = true;
                         }
                         if(((Gear->State & gstAttacking) == 0) && (((cMineDudPercent < 90) || (((Gear->State & gstWait) != 0) && (Gear->Health != 0))) || ((isAfterAttack && (Gear->Health == 0)) && (Gear->Damage > 30))))
                         {
                             uaimisc_AddBonus(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), 50, -50);
                         }
                         else
                         {
                             if((Gear->State & gstAttacking) != 0)
                             {
                                 uaimisc_AddBonus(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), 100, -50);
                             }
                         }
                     }
                     break;
         case gtAirMine:if((Gear->State & gstFrozen) == 0)
                        {
                            uaimisc_AddBonus(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Angle + 5, -30);
                            if((Gear->dX.QWordValue + Gear->dY.QWordValue) > _0_02.QWordValue)
                            {
                                bonuses.activity = true;
                            }
                        }
                        break;
         case gtExplosives:{
                               if(isAfterAttack)
                               {
                                   uaimisc_AddBonus(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), 75, -60 + Gear->Health);
                               }
                           }
                           break;
         case gtSMine:{
                          if((Gear->State & (gstMoving | gstAttacking)) != 0)
                          {
                              bonuses.activity = true;
                          }
                          uaimisc_AddBonus(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), 50, -30);
                      }
                      break;
         case gtDynamite:{
                             bonuses.activity = true;
                             uaimisc_AddBonus(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), 150, -75);
                         }
                         break;
         case gtHedgehog:{
                             if((ThinkingHH != Gear) && ((((Gear->State & ((gstMoving | gstDrowning) | gstHHDeath)) != 0) || (Gear->Health == 0)) || (Gear->Damage >= Gear->Health)))
                             {
                                 bonuses.activity = true;
                             }
                             if(Gear->Damage >= Gear->Health)
                             {
                                 uaimisc_AddBonus(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), 60, -25);
                             }
                             else
                             {
                                 if((isAfterAttack && (ThinkingHH->Hedgehog != Gear->Hedgehog)) && (ufloat_hwFloat_hwFloat_op_lt(ufloat_hwFloat_hwFloat_op_add(ufloat_hwAbs(Gear->dX), ufloat_hwAbs(Gear->dY)), _0_1)))
                                 {
                                     if((ClansCount > 2) || (MyClan == (*(*Gear->Hedgehog).Team).Clan))
                                     {
                                         uaimisc_AddBonus(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), 150, -3);
                                     }
                                     else
                                     {
                                         uaimisc_AddBonus(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), 100, 3);
                                     }
                                 }
                             }
                         }
                         break;
         default: break;}
        Gear = Gear->NextGear;
    }
    if(isAfterAttack && (KnownExplosion.Radius > 0))
    {
        {
            uaimisc_AddBonus(KnownExplosion.X, KnownExplosion.Y, KnownExplosion.Radius + 10, -KnownExplosion.Radius);
        }
    }
    if(isAfterAttack)
    {
        {i = 0;
         LongInt i__end__ = ((int)(walkbonuses.Count) - 1);
         if (i <= i__end__) do {
                                   {
                                       uaimisc_AddBonus(walkbonuses.ar[i].X, walkbonuses.ar[i].Y, walkbonuses.ar[i].Radius, walkbonuses.ar[i].Score);
                                   }
                               } while(i++ != i__end__);}
        walkbonuses.Count = 0;
    }
};
void uaimisc_AwareOfExplosion(LongInt x,LongInt y,LongInt r)
{
    KnownExplosion.X = x;
    KnownExplosion.Y = y;
    KnownExplosion.Radius = r;
};
LongInt uaimisc_RatePlace(PGear Gear)
{
    LongInt rateplace_result;
    LongInt i;
    LongInt r;
    LongInt rate;
    real gX;
    real gY;
    gX = ufloat_hwFloat2Float(Gear->X);
    gY = ufloat_hwFloat2Float(Gear->Y);
    rate = 0;
    {i = 0;
     LongInt i__end__ = ((int)(bonuses.Count) - 1);
     if (i <= i__end__) do {
                               {
                                   r = bonuses.ar[i].Radius;
                                   if((fpcrtl_abs(gX - bonuses.ar[i].X) + fpcrtl_abs(gY - bonuses.ar[i].Y)) < bonuses.ar[i].Radius)
                                   {
                                       r = fpcrtl_trunc(sqrt(fpcrtl_sqr(gX - bonuses.ar[i].X) + fpcrtl_sqr(gY - bonuses.ar[i].Y)));
                                   }
                                   if(r < 20)
                                   {
                                       rate += bonuses.ar[i].Score * bonuses.ar[i].Radius;
                                   }
                                   else
                                   {
                                       if(r < bonuses.ar[i].Radius)
                                       {
                                           rate += bonuses.ar[i].Score * (bonuses.ar[i].Radius - r);
                                       }
                                   }
                               }
                           } while(i++ != i__end__);}
    rateplace_result = rate;
    return rateplace_result;
};
real uaimisc_CheckWrap(real x)
{
    real checkwrap_result;
    if(WorldEdge == weWrap)
    {
        if(x < leftX)
        {
            x = x + (rightX - leftX);
        }
        else
        {
            if(x > rightX)
            {
                x = x - (rightX - leftX);
            }
        }
    }
    checkwrap_result = x;
    return checkwrap_result;
};
boolean uaimisc_CheckBounds(LongInt x,LongInt y,LongInt r)
{
    boolean checkbounds_result;
    checkbounds_result = (((((x - r) & LAND_WIDTH_MASK) == 0) && (((x + r) & LAND_WIDTH_MASK) == 0)) && (((y - r) & LAND_HEIGHT_MASK) == 0)) && (((y + r) & LAND_HEIGHT_MASK) == 0);
    return checkbounds_result;
};
boolean uaimisc_TestCollWithEverything(LongInt x,LongInt y,LongInt r)
{
    boolean testcollwitheverything_result;
    if(!uaimisc_CheckBounds(x, y, r))
    {
        return false;
    }
    if((((ulandutils_LandGet(y - r, x - r) != 0) || (ulandutils_LandGet(y + r, x - r) != 0)) || (ulandutils_LandGet(y - r, x + r) != 0)) || (ulandutils_LandGet(y + r, x + r) != 0))
    {
        return true;
    }
    testcollwitheverything_result = false;
    return testcollwitheverything_result;
};
boolean uaimisc_TestCollExcludingObjects(LongInt x,LongInt y,LongInt r)
{
    boolean testcollexcludingobjects_result;
    if(!uaimisc_CheckBounds(x, y, r))
    {
        return false;
    }
    if((((ulandutils_LandGet(y - r, x - r) > lfAllObjMask) || (ulandutils_LandGet(y + r, x - r) > lfAllObjMask)) || (ulandutils_LandGet(y - r, x + r) > lfAllObjMask)) || (ulandutils_LandGet(y + r, x + r) > lfAllObjMask))
    {
        return true;
    }
    testcollexcludingobjects_result = false;
    return testcollexcludingobjects_result;
};
boolean uaimisc_TestColl(LongInt x,LongInt y,LongInt r)
{
    boolean testcoll_result;
    if(!uaimisc_CheckBounds(x, y, r))
    {
        return false;
    }
    if(((((ulandutils_LandGet(y - r, x - r) & lfNotCurHogCrate) != 0) || ((ulandutils_LandGet(y + r, x - r) & lfNotCurHogCrate) != 0)) || ((ulandutils_LandGet(y - r, x + r) & lfNotCurHogCrate) != 0)) || ((ulandutils_LandGet(y + r, x + r) & lfNotCurHogCrate) != 0))
    {
        return true;
    }
    testcoll_result = false;
    return testcoll_result;
};
boolean uaimisc_TestCollHogsOrObjects(LongInt x,LongInt y,LongInt r)
{
    boolean testcollhogsorobjects_result;
    if(!uaimisc_CheckBounds(x, y, r))
    {
        return false;
    }
    if(((((ulandutils_LandGet(y - r, x - r) & lfAllObjMask) != 0) || ((ulandutils_LandGet(y + r, x - r) & lfAllObjMask) != 0)) || ((ulandutils_LandGet(y - r, x + r) & lfAllObjMask) != 0)) || ((ulandutils_LandGet(y + r, x + r) & lfAllObjMask) != 0))
    {
        return true;
    }
    testcollhogsorobjects_result = false;
    return testcollhogsorobjects_result;
};
boolean uaimisc_TestCollExcludingMe(PGear Me,LongInt x,LongInt y,LongInt r)
{
    boolean testcollexcludingme_result;
    LongInt MeX;
    LongInt MeY;
    if(((x & LAND_WIDTH_MASK) == 0) && ((y & LAND_HEIGHT_MASK) == 0))
    {
        MeX = ufloat_hwRound(Me->X);
        MeY = ufloat_hwRound(Me->Y);
        if(((fpcrtl_sqr(x - MeX) + fpcrtl_sqr(y - MeY)) < 256) && ((ulandutils_LandGet(y, x) & lfObjMask) == 0))
        {
            return false;
        }
    }
    testcollexcludingme_result = uaimisc_TestCollWithEverything(x, y, r);
    return testcollexcludingme_result;
};
LongInt uaimisc_TraceFall(LongInt eX,LongInt eY,real (*x),real (*y),real dX,real dY,LongWord r,TTarget Target)
{
    LongInt tracefall_result;
    boolean skipLandCheck;
    real rCorner;
    real dxdy;
    real odX;
    real odY;
    LongInt dmg;
    odX = dX;
    odY = dY;
    skipLandCheck = true;
    rCorner = r * 0.75;
    while(true)
    {
        (*x) = uaimisc_CheckWrap((*x));
        (*x) = (*x) + dX;
        (*y) = (*y) + dY;
        dY = dY + aiGravityf;
        skipLandCheck = ((skipLandCheck && (r != 0)) && ((fpcrtl_abs(eX - (*x)) + fpcrtl_abs(eY - (*y))) < r)) && ((fpcrtl_abs(eX - (*x)) < rCorner) || (fpcrtl_abs(eY - (*y)) < rCorner));
        if(!skipLandCheck && uaimisc_TestCollExcludingObjects(fpcrtl_trunc((*x)), fpcrtl_trunc((*y)), Target.Radius))
        {
            {
                if((Target.Kind == gtHedgehog) && (0.4 < dY))
                {
                    dmg = 1 + fpcrtl_trunc((dY - 0.4) * 70);
                    return dmg;
                }
                else
                {
                    dxdy = fpcrtl_abs(dX) + fpcrtl_abs(dY);
                    if(((Target.Kind == gtMine) && (dxdy > 0.35)) || ((Target.Kind == gtExplosives) && ((((Target.State & gsttmpFlag) != 0) && (dxdy > 0.35)) || ((((Target.State & gsttmpFlag) == 0) && ((fpcrtl_abs(odX) > 0.15) || ((fpcrtl_abs(odY) > 0.15) && (fpcrtl_abs(odX) > 2.0e-2)))) && (dxdy > 0.35)))))
                    {
                        dmg = fpcrtl_trunc(dxdy * 25);
                        return dmg;
                    }
                    else
                    {
                        if(((Target.Kind == gtExplosives) && (!(fpcrtl_abs(odX) > 0.15) || ((fpcrtl_abs(odY) > 0.15) && (fpcrtl_abs(odX) > 2.0e-2)))) && (dY > 0.2))
                        {
                            dmg = fpcrtl_trunc(dY * 70);
                            return dmg;
                        }
                    }
                }
                return 0;
            }
        }
        if(ucollisions_CheckCoordInWater(fpcrtl_round((*x)), fpcrtl_round((*y))))
        {
            return -1;
        }
    }
    return tracefall_result;
};
LongInt uaimisc_TraceShoveFall(real (*x),real (*y),real dX,real dY,TTarget Target)
{
    LongInt traceshovefall_result;
    LongInt dmg;
    real dxdy;
    real odX;
    real odY;
    odX = dX;
    odY = dY;
    while(true)
    {
        (*x) = uaimisc_CheckWrap((*x));
        (*x) = (*x) + dX;
        (*y) = (*y) + dY;
        dY = dY + aiGravityf;
        if(uaimisc_TestCollExcludingObjects(fpcrtl_trunc((*x)), fpcrtl_trunc((*y)), Target.Radius))
        {
            {
                if((Target.Kind == gtHedgehog) && (0.4 < dY))
                {
                    dmg = fpcrtl_trunc((dY - 0.4) * 70);
                    return dmg;
                }
                else
                {
                    dxdy = fpcrtl_abs(dX) + fpcrtl_abs(dY);
                    if(((Target.Kind == gtMine) && (dxdy > 0.4)) || ((Target.Kind == gtExplosives) && ((((Target.State & gsttmpFlag) != 0) && (dxdy > 0.4)) || ((((Target.State & gsttmpFlag) == 0) && ((fpcrtl_abs(odX) > 0.15) || ((fpcrtl_abs(odY) > 0.15) && (fpcrtl_abs(odX) > 2.0e-2)))) && (dxdy > 0.35)))))
                    {
                        dmg = fpcrtl_trunc(dxdy * 50);
                        return dmg;
                    }
                    else
                    {
                        if(((Target.Kind == gtExplosives) && (!(fpcrtl_abs(odX) > 0.15) || ((fpcrtl_abs(odY) > 0.15) && (fpcrtl_abs(odX) > 2.0e-2)))) && (dY > 0.2))
                        {
                            dmg = fpcrtl_trunc(dY * 70);
                            return dmg;
                        }
                    }
                }
                return 0;
            }
        }
        if(ucollisions_CheckCoordInWater(fpcrtl_round((*x)), fpcrtl_round((*y))))
        {
            return -1;
        }
    }
    return traceshovefall_result;
};
LongInt uaimisc_RateExplosion_4(PGear Me,LongInt x,LongInt y,LongInt r)
{
    LongInt rateexplosion_result;
    rateexplosion_result = uaimisc_RealRateExplosion(Me, x, y, r, 0);
    uaimisc_ResetTargets();
    return rateexplosion_result;
};
LongInt uaimisc_RateExplosion_5(PGear Me,LongInt x,LongInt y,LongInt r,LongWord Flags)
{
    LongInt rateexplosion_result;
    rateexplosion_result = uaimisc_RealRateExplosion(Me, x, y, r, Flags);
    uaimisc_ResetTargets();
    return rateexplosion_result;
};
LongInt uaimisc_RealRateExplosion(PGear Me,LongInt x,LongInt y,LongInt r,LongWord Flags)
{
    LongInt realrateexplosion_result;
    LongInt i;
    LongInt fallDmg;
    LongInt dmg;
    LongInt dmgBase;
    LongInt rate;
    LongInt subrate;
    LongInt erasure;
    real pX;
    real pY;
    real dX;
    real dY;
    boolean hadSkips;
    x = fpcrtl_round(uaimisc_CheckWrap(((real)x)));
    fallDmg = 0;
    rate = 0;
    if((Flags & afIgnoreMe) == 0)
    {
        {
            Targets.ar[Targets.Count].Point.x = ufloat_hwRound(Me->X);
            Targets.ar[Targets.Count].Point.y = ufloat_hwRound(Me->Y);
            Targets.ar[Targets.Count].skip = false;
            Targets.ar[Targets.Count].matters = true;
            Targets.ar[Targets.Count].Kind = gtHedgehog;
            Targets.ar[Targets.Count].Density = 1;
            Targets.ar[Targets.Count].Radius = cHHRadius;
            Targets.ar[Targets.Count].Score = -ThinkingHH->Health;
        }
    }
    if(((Flags & afErasesLand) != 0) && ((GameFlags & gfSolidLand) == 0))
    {
        erasure = r;
    }
    else
    {
        erasure = 0;
    }
    hadSkips = false;
    {i = 0;
     LongInt i__end__ = Targets.Count;
     if (i <= i__end__) do {
                               if(!Targets.ar[i].dead)
                               {
                                   {
                                       if(!Targets.ar[i].matters)
                                       {
                                           hadSkips = true;
                                       }
                                       else
                                       {
                                           dmg = 0;
                                           dmgBase = r + (Targets.ar[i].Radius / 2);
                                           if((fpcrtl_abs(Targets.ar[i].Point.x - x) + fpcrtl_abs(Targets.ar[i].Point.y - y)) < dmgBase)
                                           {
                                               dmg = fpcrtl_trunc(dmgMod * uutils_Min((dmgBase - fpcrtl_trunc(sqrt(fpcrtl_sqr(Targets.ar[i].Point.x - x) + fpcrtl_sqr(Targets.ar[i].Point.y - y)))) / 2, r));
                                           }
                                           if(dmg > 0)
                                           {
                                               pX = Targets.ar[i].Point.x;
                                               pY = Targets.ar[i].Point.y;
                                               fallDmg = 0;
                                               dX = 0;
                                               if((((Flags & afTrackFall) != 0) && (Targets.ar[i].Score > 0)) && (dmg < Targets.ar[i].Score))
                                               {
                                                   dX = ((5.0e-3 * dmg) + 1.0e-2) /(float) Targets.ar[i].Density;
                                                   dY = dX;
                                                   if(((Targets.ar[i].Kind == gtExplosives) && ((Targets.ar[i].State & gsttmpFlag) == 0)) && (((fpcrtl_abs(dY) >= 0.15) && (fpcrtl_abs(dX) < 2.0e-2)) || ((fpcrtl_abs(dY) < 0.15) && (fpcrtl_abs(dX) < 0.15))))
                                                   {
                                                       dX = 0;
                                                   }
                                                   if((pX - x) < 0)
                                                   {
                                                       dX = -dX;
                                                   }
                                                   if((pY - y) < 0)
                                                   {
                                                       dY = -dY;
                                                   }
                                                   if((((x & LAND_WIDTH_MASK) == 0) && ((((y + cHHRadius) + 2) & LAND_HEIGHT_MASK) == 0)) && ((ulandutils_LandGet((y + cHHRadius) + 2, x) & lfIndestructible) != 0))
                                                   {
                                                       fallDmg = fpcrtl_trunc(uaimisc_TraceFall(x, y, &(pX), &(pY), dX, dY, 0, Targets.ar[i]) * dmgMod);
                                                   }
                                                   else
                                                   {
                                                       fallDmg = fpcrtl_trunc(uaimisc_TraceFall(x, y, &(pX), &(pY), dX, dY, erasure, Targets.ar[i]) * dmgMod);
                                                   }
                                               }
                                               if(Targets.ar[i].Kind == gtHedgehog)
                                               {
                                                   if(fallDmg < 0)
                                                   {
                                                       if(Targets.ar[i].Score > 0)
                                                       {
                                                           rate += (KillScore + (Targets.ar[i].Score / 10)) * 1024;
                                                       }
                                                       else
                                                       {
                                                           rate -= (((KillScore * friendlyfactor) / 100) - (Targets.ar[i].Score / 10)) * 1024;
                                                       }
                                                   }
                                                   else
                                                   {
                                                       if((dmg + fallDmg) >= fpcrtl_abs(Targets.ar[i].Score))
                                                       {
                                                           Targets.ar[i].dead = true;
                                                           Targets.reset = true;
                                                           if(dX < 3.5e-2)
                                                           {
                                                               subrate = uaimisc_RealRateExplosion(Me, fpcrtl_round(pX), fpcrtl_round(pY), 61, afErasesLand | (Flags & afTrackFall));
                                                               if(fpcrtl_abs(subrate) > 2000)
                                                               {
                                                                   rate += subrate;
                                                               }
                                                           }
                                                           if(Targets.ar[i].Score > 0)
                                                           {
                                                               rate += (KillScore * 1024) + (dmg + fallDmg);
                                                           }
                                                           else
                                                           {
                                                               rate -= ((KillScore * friendlyfactor) / 100) * 1024;
                                                           }
                                                       }
                                                       else
                                                       {
                                                           if(Targets.ar[i].Score > 0)
                                                           {
                                                               rate += (dmg + fallDmg) * 1024;
                                                           }
                                                           else
                                                           {
                                                               rate -= (((dmg + fallDmg) * friendlyfactor) / 100) * 1024;
                                                           }
                                                       }
                                                   }
                                               }
                                               else
                                               {
                                                   if((fallDmg >= 0) && ((dmg + fallDmg) >= Targets.ar[i].Score))
                                                   {
                                                       Targets.ar[i].dead = true;
                                                       Targets.reset = true;
                                                       if(Targets.ar[i].Kind == gtExplosives)
                                                       {
                                                           subrate = uaimisc_RealRateExplosion(Me, fpcrtl_round(pX), fpcrtl_round(pY), 151, afErasesLand | (Flags & afTrackFall));
                                                       }
                                                       else
                                                       {
                                                           subrate = uaimisc_RealRateExplosion(Me, fpcrtl_round(pX), fpcrtl_round(pY), 101, afErasesLand | (Flags & afTrackFall));
                                                       }
                                                       if(fpcrtl_abs(subrate) > 2000)
                                                       {
                                                           rate += subrate;
                                                       }
                                                   }
                                               }
                                           }
                                       }
                                   }
                               }
                           } while(i++ != i__end__);}
    if(hadSkips && (rate <= 0))
    {
        realrateexplosion_result = BadTurn;
    }
    else
    {
        realrateexplosion_result = rate;
    }
    return realrateexplosion_result;
};
LongInt uaimisc_RateShove(PGear Me,LongInt x,LongInt y,LongInt r,LongInt power,LongInt kick,real gdX,real gdY,LongWord Flags)
{
    LongInt rateshove_result;
    LongInt i;
    LongInt fallDmg;
    LongInt dmg;
    LongInt rate;
    LongInt subrate;
    real dX;
    real dY;
    real pX;
    real pY;
    boolean hadSkips;
    fallDmg = 0;
    dX = (gdX * 1.0e-2) * kick;
    dY = (gdY * 1.0e-2) * kick;
    rate = 0;
    hadSkips = false;
    {i = 0;
     LongInt i__end__ = ((int)(Targets.Count) - 1);
     if (i <= i__end__) do {
                               {
                                   if(Targets.ar[i].skip)
                                   {
                                       if((Flags & afSetSkip) == 0)
                                       {
                                           Targets.ar[i].skip = false;
                                       }
                                   }
                                   else
                                   {
                                       if(Targets.ar[i].matters)
                                       {
                                           dmg = 0;
                                           if((fpcrtl_abs(Targets.ar[i].Point.x - x) + fpcrtl_abs(Targets.ar[i].Point.y - y)) < r)
                                           {
                                               dmg = r - fpcrtl_trunc(sqrt(fpcrtl_sqr(Targets.ar[i].Point.x - x) + fpcrtl_sqr(Targets.ar[i].Point.y - y)));
                                           }
                                           if(dmg > 0)
                                           {
                                               pX = Targets.ar[i].Point.x;
                                               pY = Targets.ar[i].Point.y - 2;
                                               fallDmg = 0;
                                               if((Flags & afSetSkip) != 0)
                                               {
                                                   Targets.ar[i].skip = true;
                                               }
                                               if(((!Targets.ar[i].dead && ((Flags & afTrackFall) != 0)) && (Targets.ar[i].Score > 0)) && (power < Targets.ar[i].Score))
                                               {
                                                   if(((Targets.ar[i].Kind == gtExplosives) && ((Targets.ar[i].State & gsttmpFlag) == 0)) && (((fpcrtl_abs(dY) > 0.15) && (fpcrtl_abs(dX) < 2.0e-2)) || ((fpcrtl_abs(dY) < 0.15) && (fpcrtl_abs(dX) < 0.15))))
                                                   {
                                                       fallDmg = fpcrtl_trunc(uaimisc_TraceShoveFall(&(pX), &(pY), 0, dY, Targets.ar[i]) * dmgMod);
                                                   }
                                                   else
                                                   {
                                                       fallDmg = fpcrtl_trunc(uaimisc_TraceShoveFall(&(pX), &(pY), dX, dY, Targets.ar[i]) * dmgMod);
                                                   }
                                               }
                                               if(Targets.ar[i].Kind == gtHedgehog)
                                               {
                                                   if(fallDmg < 0)
                                                   {
                                                       if(Targets.ar[i].Score > 0)
                                                       {
                                                           rate += KillScore + (Targets.ar[i].Score / 10);
                                                       }
                                                       else
                                                       {
                                                           rate -= ((KillScore * friendlyfactor) / 100) - (Targets.ar[i].Score / 10);
                                                       }
                                                   }
                                                   else
                                                   {
                                                       if((power + fallDmg) >= fpcrtl_abs(Targets.ar[i].Score))
                                                       {
                                                           Targets.ar[i].dead = true;
                                                           Targets.reset = true;
                                                           if(dX < 3.5e-2)
                                                           {
                                                               subrate = uaimisc_RealRateExplosion(Me, fpcrtl_round(pX), fpcrtl_round(pY), 61, afErasesLand | afTrackFall);
                                                               if(fpcrtl_abs(subrate) > 2000)
                                                               {
                                                                   rate += subrate / 1024;
                                                               }
                                                           }
                                                           if(Targets.ar[i].Score > 0)
                                                           {
                                                               rate += KillScore;
                                                           }
                                                           else
                                                           {
                                                               rate -= (KillScore * friendlyfactor) / 100;
                                                           }
                                                       }
                                                       else
                                                       {
                                                           if(Targets.ar[i].Score > 0)
                                                           {
                                                               rate += power + fallDmg;
                                                           }
                                                           else
                                                           {
                                                               rate -= ((power + fallDmg) * friendlyfactor) / 100;
                                                           }
                                                       }
                                                   }
                                               }
                                               else
                                               {
                                                   if((fallDmg >= 0) && ((dmg + fallDmg) >= Targets.ar[i].Score))
                                                   {
                                                       Targets.ar[i].dead = true;
                                                       Targets.reset = true;
                                                       if(Targets.ar[i].Kind == gtExplosives)
                                                       {
                                                           subrate = uaimisc_RealRateExplosion(Me, fpcrtl_round(pX), fpcrtl_round(pY), 151, afErasesLand | (Flags & afTrackFall));
                                                       }
                                                       else
                                                       {
                                                           subrate = uaimisc_RealRateExplosion(Me, fpcrtl_round(pX), fpcrtl_round(pY), 101, afErasesLand | (Flags & afTrackFall));
                                                       }
                                                       if(fpcrtl_abs(subrate) > 2000)
                                                       {
                                                           rate += subrate / 1024;
                                                       }
                                                   }
                                               }
                                           }
                                       }
                                       else
                                       {
                                           hadSkips = true;
                                       }
                                   }
                               }
                           } while(i++ != i__end__);}
    if(hadSkips && (rate <= 0))
    {
        rateshove_result = BadTurn;
    }
    else
    {
        rateshove_result = rate * 1024;
    }
    uaimisc_ResetTargets();
    return rateshove_result;
};
LongInt uaimisc_RateShotgun(PGear Me,real gdX,real gdY,LongInt x,LongInt y)
{
    LongInt rateshotgun_result;
    LongInt i;
    LongInt dmg;
    LongInt fallDmg;
    LongInt baseDmg;
    LongInt rate;
    LongInt subrate;
    LongInt erasure;
    real pX;
    real pY;
    real dX;
    real dY;
    boolean hadSkips;
    rate = 0;
    gdX = gdX * 1.0e-2;
    gdY = gdX * 1.0e-2;
    {
        Targets.ar[Targets.Count].Point.x = ufloat_hwRound(Me->X);
        Targets.ar[Targets.Count].Point.y = ufloat_hwRound(Me->Y);
        Targets.ar[Targets.Count].skip = false;
        Targets.ar[Targets.Count].matters = true;
        Targets.ar[Targets.Count].Kind = gtHedgehog;
        Targets.ar[Targets.Count].Density = 1;
        Targets.ar[Targets.Count].Radius = cHHRadius;
        Targets.ar[Targets.Count].Score = -ThinkingHH->Health;
    }
    baseDmg = (cHHRadius + cShotgunRadius) + 4;
    if((GameFlags & gfSolidLand) == 0)
    {
        erasure = cShotgunRadius;
    }
    else
    {
        erasure = 0;
    }
    hadSkips = false;
    {i = 0;
     LongInt i__end__ = Targets.Count;
     if (i <= i__end__) do {
                               if(!Targets.ar[i].dead)
                               {
                                   {
                                       if(!Targets.ar[i].matters)
                                       {
                                           hadSkips = true;
                                       }
                                       else
                                       {
                                           dmg = 0;
                                           if((fpcrtl_abs(Targets.ar[i].Point.x - x) + fpcrtl_abs(Targets.ar[i].Point.y - y)) < baseDmg)
                                           {
                                               dmg = uutils_Min(baseDmg - fpcrtl_trunc(sqrt(fpcrtl_sqr(Targets.ar[i].Point.x - x) + fpcrtl_sqr(Targets.ar[i].Point.y - y))), 25);
                                               dmg = fpcrtl_trunc(dmg * dmgMod);
                                           }
                                           if(dmg > 0)
                                           {
                                               fallDmg = 0;
                                               pX = Targets.ar[i].Point.x;
                                               pY = Targets.ar[i].Point.y;
                                               if((!Targets.ar[i].dead && (Targets.ar[i].Score > 0)) && (dmg < Targets.ar[i].Score))
                                               {
                                                   dX = (gdX * dmg) /(float) Targets.ar[i].Density;
                                                   dY = (gdY * dmg) /(float) Targets.ar[i].Density;
                                                   if(dX < 0)
                                                   {
                                                       dX = dX - 1.0e-2;
                                                   }
                                                   else
                                                   {
                                                       dX = dX + 1.0e-2;
                                                   }
                                                   if(((Targets.ar[i].Kind == gtExplosives) && ((Targets.ar[i].State & gsttmpFlag) == 0)) && (((fpcrtl_abs(dY) > 0.15) && (fpcrtl_abs(dX) < 2.0e-2)) || ((fpcrtl_abs(dY) < 0.15) && (fpcrtl_abs(dX) < 0.15))))
                                                   {
                                                       dX = 0;
                                                   }
                                                   if((((x & LAND_WIDTH_MASK) == 0) && ((((y + cHHRadius) + 2) & LAND_HEIGHT_MASK) == 0)) && ((ulandutils_LandGet((y + cHHRadius) + 2, x) & lfIndestructible) != 0))
                                                   {
                                                       fallDmg = fpcrtl_trunc(uaimisc_TraceFall(x, y, &(pX), &(pY), dX, dY, 0, Targets.ar[i]) * dmgMod);
                                                   }
                                                   else
                                                   {
                                                       fallDmg = fpcrtl_trunc(uaimisc_TraceFall(x, y, &(pX), &(pY), dX, dY, erasure, Targets.ar[i]) * dmgMod);
                                                   }
                                               }
                                               if(Targets.ar[i].Kind == gtHedgehog)
                                               {
                                                   if(fallDmg < 0)
                                                   {
                                                       if(Targets.ar[i].Score > 0)
                                                       {
                                                           rate += KillScore + (Targets.ar[i].Score / 10);
                                                       }
                                                       else
                                                       {
                                                           rate -= ((KillScore * friendlyfactor) / 100) - (Targets.ar[i].Score / 10);
                                                       }
                                                   }
                                                   else
                                                   {
                                                       if((dmg + fallDmg) >= fpcrtl_abs(Targets.ar[i].Score))
                                                       {
                                                           Targets.ar[i].dead = true;
                                                           Targets.reset = true;
                                                           if(fpcrtl_abs(gdX) < 3.5e-2)
                                                           {
                                                               subrate = uaimisc_RealRateExplosion(Me, fpcrtl_round(pX), fpcrtl_round(pY), 61, afErasesLand | afTrackFall);
                                                               if(fpcrtl_abs(subrate) > 2000)
                                                               {
                                                                   rate += subrate / 1024;
                                                               }
                                                           }
                                                           if(Targets.ar[i].Score > 0)
                                                           {
                                                               rate += KillScore;
                                                           }
                                                           else
                                                           {
                                                               rate -= (KillScore * friendlyfactor) / 100;
                                                           }
                                                       }
                                                       else
                                                       {
                                                           if(Targets.ar[i].Score > 0)
                                                           {
                                                               rate += dmg + fallDmg;
                                                           }
                                                           else
                                                           {
                                                               rate -= ((dmg + fallDmg) * friendlyfactor) / 100;
                                                           }
                                                       }
                                                   }
                                               }
                                               else
                                               {
                                                   if((fallDmg >= 0) && ((dmg + fallDmg) >= Targets.ar[i].Score))
                                                   {
                                                       Targets.ar[i].dead = true;
                                                       Targets.reset = true;
                                                       if(Targets.ar[i].Kind == gtExplosives)
                                                       {
                                                           subrate = uaimisc_RealRateExplosion(Me, fpcrtl_round(pX), fpcrtl_round(pY), 151, afErasesLand | afTrackFall);
                                                       }
                                                       else
                                                       {
                                                           subrate = uaimisc_RealRateExplosion(Me, fpcrtl_round(pX), fpcrtl_round(pY), 101, afErasesLand | afTrackFall);
                                                       }
                                                       if(fpcrtl_abs(subrate) > 2000)
                                                       {
                                                           rate += subrate / 1024;
                                                       }
                                                   }
                                               }
                                           }
                                       }
                                   }
                               }
                           } while(i++ != i__end__);}
    if(hadSkips && (rate <= 0))
    {
        rateshotgun_result = BadTurn;
    }
    else
    {
        rateshotgun_result = rate * 1024;
    }
    uaimisc_ResetTargets();
    return rateshotgun_result;
};
LongInt uaimisc_RateSeduction(PGear Me)
{
    LongInt rateseduction_result;
    LongInt pX;
    LongInt pY;
    LongInt i;
    LongInt r;
    LongInt rate;
    LongInt subrate;
    LongInt fallDmg;
    LongInt diffX;
    LongInt diffY;
    hwFloat meX;
    hwFloat meY;
    hwFloat dX;
    hwFloat dY;
    real pXr;
    real pYr;
    boolean hadSkips;
    meX = Me->X;
    meY = Me->Y;
    rate = 0;
    hadSkips = false;
    {i = 0;
     LongInt i__end__ = Targets.Count;
     if (i <= i__end__) do {
                               if(!Targets.ar[i].dead)
                               {
                                   {
                                       pX = Targets.ar[i].Point.x;
                                       pY = Targets.ar[i].Point.y;
                                       diffX = pX - ufloat_hwRound(meX);
                                       diffY = pY - ufloat_hwRound(meY);
                                       if(((((*Me->Hedgehog).BotLevel < 4) && (fpcrtl_abs(diffX) <= (cHHRadius * 2))) && (diffY >= 0)) && (diffY <= (cHHRadius * 2)))
                                       {
                                           return BadTurn;
                                       }
                                       if(!Targets.ar[i].matters)
                                       {
                                           hadSkips = true;
                                       }
                                       else
                                       {
                                           if((Targets.ar[i].matters && (Targets.ar[i].Kind == gtHedgehog)) && ((fpcrtl_abs(pX - ufloat_hwRound(meX)) + fpcrtl_abs(pY - ufloat_hwRound(meY))) < cSeductionDist))
                                           {
                                               r = fpcrtl_trunc(sqrt(fpcrtl_sqr(fpcrtl_abs(pX - ufloat_hwRound(meX))) + fpcrtl_sqr(fpcrtl_abs(pY - ufloat_hwRound(meY)))));
                                               if(r < cSeductionDist)
                                               {
                                                   if((WorldEdge != weWrap) || !(ufloat_hwFloat_hwFloat_op_gt(ufloat_hwAbs(ufloat_hwFloat_hwFloat_op_sub(meX, ufloat_int2hwFloat(pX))), ufloat_int2hwFloat(cSeductionDist))))
                                                   {
                                                       dX = ufloat_hwFloat_LongInt_op_div(ufloat_hwFloat_hwFloat_op_mul(aiGravity, ufloat_hwFloat_hwFloat_op_sub(meX, ufloat_int2hwFloat(pX))), 2);
                                                   }
                                                   else
                                                   {
                                                       if(!(ufloat_hwFloat_hwFloat_op_gt(ufloat_hwAbs(ufloat_hwFloat_hwFloat_op_add(meX, ufloat_int2hwFloat((rightX - leftX) - pX))), ufloat_int2hwFloat(cSeductionDist))))
                                                       {
                                                           dX = ufloat_hwFloat_LongInt_op_div(ufloat_hwFloat_hwFloat_op_mul(aiGravity, ufloat_hwFloat_hwFloat_op_add(meX, ufloat_int2hwFloat((rightX - leftX) - pX))), 2);
                                                       }
                                                       else
                                                       {
                                                           dX = ufloat_hwFloat_LongInt_op_div(ufloat_hwFloat_hwFloat_op_mul(aiGravity, ufloat_hwFloat_hwFloat_op_sub(meX, ufloat_int2hwFloat((rightX - leftX) - pX))), 2);
                                                       }
                                                   }
                                                   dY = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_op_sub(_900), cMaxWindSpeed);
                                                   pXr = pX;
                                                   pYr = pY;
                                                   fallDmg = fpcrtl_trunc(uaimisc_TraceShoveFall(&(pXr), &(pYr), ufloat_hwFloat2Float(dX), ufloat_hwFloat2Float(dY), Targets.ar[i]) * dmgMod);
                                                   if(fallDmg < 0)
                                                   {
                                                       if(Targets.ar[i].Score > 0)
                                                       {
                                                           rate += (KillScore + (Targets.ar[i].Score / 10)) * 1024;
                                                       }
                                                       else
                                                       {
                                                           rate -= (((KillScore * friendlyfactor) / 100) - (Targets.ar[i].Score / 10)) * 1024;
                                                       }
                                                   }
                                                   else
                                                   {
                                                       if(fallDmg >= fpcrtl_abs(Targets.ar[i].Score))
                                                       {
                                                           Targets.ar[i].dead = true;
                                                           Targets.reset = true;
                                                           if(ufloat_hwFloat2Float(dX) < 3.5e-2)
                                                           {
                                                               subrate = uaimisc_RealRateExplosion(Me, fpcrtl_round(pX), fpcrtl_round(pY), 61, afErasesLand | afTrackFall);
                                                               if(fpcrtl_abs(subrate) > 2000)
                                                               {
                                                                   rate += subrate;
                                                               }
                                                           }
                                                           if(Targets.ar[i].Score > 0)
                                                           {
                                                               rate += (KillScore * 1024) + fallDmg;
                                                           }
                                                           else
                                                           {
                                                               rate -= ((KillScore * friendlyfactor) / 100) * 1024;
                                                           }
                                                       }
                                                       else
                                                       {
                                                           if(fallDmg != 0)
                                                           {
                                                               if(Targets.ar[i].Score > 0)
                                                               {
                                                                   rate += fallDmg * 1024;
                                                               }
                                                               else
                                                               {
                                                                   rate -= ((fallDmg * friendlyfactor) / 100) * 1024;
                                                               }
                                                           }
                                                           else
                                                           {
                                                               if(Targets.ar[i].Score < 0)
                                                               {
                                                                   rate -= 100;
                                                               }
                                                           }
                                                       }
                                                   }
                                               }
                                           }
                                       }
                                   }
                               }
                           } while(i++ != i__end__);}
    if(hadSkips && (rate <= 0))
    {
        rateseduction_result = BadTurn;
    }
    else
    {
        rateseduction_result = rate * 1024;
    }
    return rateseduction_result;
};
LongInt uaimisc_RateResurrector(PGear Me)
{
    LongInt rateresurrector_result;
    LongInt i;
    LongInt r;
    LongInt rate;
    LongInt pX;
    LongInt pY;
    hwFloat meX;
    hwFloat meY;
    boolean hadSkips;
    meX = Me->X;
    meY = Me->Y;
    rate = 0;
    hadSkips = false;
    {i = 0;
     LongInt i__end__ = Targets.Count;
     if (i <= i__end__) do {
                               if((Targets.ar[i].Kind == gtGrave) && !Targets.ar[i].dead)
                               {
                                   {
                                       pX = Targets.ar[i].Point.x;
                                       pY = Targets.ar[i].Point.y;
                                       if(!Targets.ar[i].matters)
                                       {
                                           hadSkips = true;
                                       }
                                       else
                                       {
                                           if(Targets.ar[i].matters && ((fpcrtl_abs(pX - ufloat_hwRound(meX)) + fpcrtl_abs(pY - ufloat_hwRound(meY))) < cResurrectorDist))
                                           {
                                               r = fpcrtl_trunc(sqrt(fpcrtl_sqr(fpcrtl_abs(pX - ufloat_hwRound(meX))) + fpcrtl_sqr(fpcrtl_abs(pY - ufloat_hwRound(meY)))));
                                               if(r < cResurrectorDist)
                                               {
                                                   if(Targets.ar[i].Score > 0)
                                                   {
                                                       rate += Targets.ar[i].Score * 1024;
                                                   }
                                                   else
                                                   {
                                                       rate += ((Targets.ar[i].Score * friendlyfactor) / 100) * 1024;
                                                   }
                                                   Targets.ar[i].dead = true;
                                                   Targets.reset = true;
                                               }
                                           }
                                       }
                                   }
                               }
                           } while(i++ != i__end__);}
    if(hadSkips && (rate <= 0))
    {
        rateresurrector_result = BadTurn;
    }
    else
    {
        rateresurrector_result = rate * 1024;
    }
    return rateresurrector_result;
};
LongInt uaimisc_RateHammer(PGear Me)
{
    LongInt ratehammer_result;
    LongInt x;
    LongInt y;
    LongInt i;
    LongInt r;
    LongInt rate;
    boolean hadSkips;
    x = ufloat_hwRound(Me->X) + (ufloat_hwSign(Me->dX) * 10);
    y = ufloat_hwRound(Me->Y);
    rate = 0;
    hadSkips = false;
    {i = 0;
     LongInt i__end__ = ((int)(Targets.Count) - 1);
     if (i <= i__end__) do {
                               {
                                   if(!Targets.ar[i].matters)
                                   {
                                       hadSkips = true;
                                   }
                                   else
                                   {
                                       if((Targets.ar[i].matters && (Targets.ar[i].Kind == gtHedgehog)) && ((fpcrtl_abs(Targets.ar[i].Point.x - x) + fpcrtl_abs(Targets.ar[i].Point.y - y)) < 18))
                                       {
                                           r = fpcrtl_trunc(sqrt(fpcrtl_sqr(Targets.ar[i].Point.x - x) + fpcrtl_sqr(Targets.ar[i].Point.y - y)));
                                           if(r <= 18)
                                           {
                                               if(Targets.ar[i].Score > 0)
                                               {
                                                   rate += Targets.ar[i].Score / 3;
                                               }
                                               else
                                               {
                                                   rate += ((Targets.ar[i].Score / 3) * friendlyfactor) / 100;
                                               }
                                           }
                                       }
                                   }
                               }
                           } while(i++ != i__end__);}
    if(hadSkips && (rate <= 0))
    {
        ratehammer_result = BadTurn;
    }
    else
    {
        ratehammer_result = rate * 1024;
    }
    return ratehammer_result;
};
boolean uaimisc_HHJump(PGear Gear,TJumpType JumpType,TGoInfo (*GoInfo))
{
    boolean hhjump_result;
    LongInt bX;
    LongInt bY;
    hhjump_result = false;
    (*GoInfo).Ticks = 0;
    (*GoInfo).JumpType = jmpNone;
    bX = ufloat_hwRound(Gear->X);
    bY = ufloat_hwRound(Gear->Y);
    switch(JumpType)
    {case jmpNone:return false;
                  break;
     case jmpHJump:if(ucollisions_TestCollisionYwithGear(Gear, -1) == 0)
                   {
                       Gear->dY = ufloat_hwFloat_op_sub(_0_2);
                       uutils_SetLittle(&(Gear->dX));
                       Gear->State = (Gear->State | gstMoving) | gstHHJumping;
                   }
                   else
                   {
                       return false;
                   }
                   break;
     case jmpLJump:{
                       if(ucollisions_TestCollisionYwithGear(Gear, -1) != 0)
                       {
                           if(ucollisions_TestCollisionXwithXYShift_4(Gear, _0, -2, ufloat_hwSign(Gear->dX)) == 0)
                           {
                               Gear->Y = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, _2);
                           }
                           else
                           {
                               if(ucollisions_TestCollisionXwithXYShift_4(Gear, _0, -1, ufloat_hwSign(Gear->dX)) == 0)
                               {
                                   Gear->Y = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, _1);
                               }
                           }
                       }
                       if((ucollisions_TestCollisionXwithGear(Gear, ufloat_hwSign(Gear->dX)) == 0) && (ucollisions_TestCollisionYwithGear(Gear, -1) == 0))
                       {
                           Gear->dY = ufloat_hwFloat_op_sub(_0_15);
                           Gear->dX = ufloat_SignAs(_0_15, Gear->dX);
                           Gear->State = (Gear->State | gstMoving) | gstHHJumping;
                       }
                       else
                       {
                           return false;
                       }
                   }
                   break;
     default: break;}
    do {
           if(ucollisions_CheckCoordInWater(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y) + cHHRadius))
           {
               return false;
           }
           if((Gear->State & gstMoving) != 0)
           {
               if((*GoInfo).Ticks == 350)
               {
                   if(!(ufloat_hwFloat_hwFloat_op_gt(ufloat_hwAbs(Gear->dX), cLittle)) && (ufloat_hwFloat_hwFloat_op_lt(Gear->dY, ufloat_hwFloat_op_sub(_0_02))))
                   {
                       Gear->dY = ufloat_hwFloat_op_sub(_0_25);
                       Gear->dX = ufloat_SignAs(_0_02, Gear->dX);
                   }
               }
               if(ucollisions_TestCollisionXwithGear(Gear, ufloat_hwSign(Gear->dX)) != 0)
               {
                   uutils_SetLittle(&(Gear->dX));
               }
               Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, Gear->dX);
               ++(*GoInfo).Ticks;
               Gear->dY = ufloat_hwFloat_hwFloat_op_add(Gear->dY, aiGravity);
               if(ufloat_hwFloat_hwFloat_op_gt(Gear->dY, _0_4))
               {
                   return false;
               }
               if(Gear->dY.isNegative && (ucollisions_TestCollisionYwithGear(Gear, -1) != 0))
               {
                   Gear->dY = _0;
               }
               Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, Gear->dY);
               if(!Gear->dY.isNegative && (ucollisions_TestCollisionYwithGear(Gear, 1) != 0))
               {
                   Gear->State = Gear->State & ~(gstMoving | gstHHJumping);
                   Gear->dY = _0;
                   switch(JumpType)
                   {case jmpHJump:if((bY - ufloat_hwRound(Gear->Y)) > 5)
                                  {
                                      (*GoInfo).JumpType = jmpHJump;
                                      (*GoInfo).Ticks += 300 + 300;
                                      return true;
                                  }
                                  break;
                    case jmpLJump:if(fpcrtl_abs(bX - ufloat_hwRound(Gear->X)) > 30)
                                  {
                                      (*GoInfo).JumpType = jmpLJump;
                                      (*GoInfo).Ticks += 300 + 300;
                                      return true;
                                  }
                                  break;
                    default: break;}
                   return false;
               }
           }
       } while(!(false));
    return hhjump_result;
};
boolean uaimisc_HHGo(PGear Gear,PGear AltGear,TGoInfo (*GoInfo))
{
    boolean hhgo_result;
    LongInt pX;
    LongInt pY;
    LongInt tY;
    hhgo_result = false;
    Gear->CollisionMask = lfNotCurHogCrate;
    Gear->dX.isNegative = (Gear->Message & gmLeft) != 0;
    (*AltGear) = (*Gear);
    (*GoInfo).Ticks = 0;
    (*GoInfo).FallPix = 0;
    (*GoInfo).JumpType = jmpNone;
    tY = ufloat_hwRound(Gear->Y);
    do {
           pX = ufloat_hwRound(Gear->X);
           pY = ufloat_hwRound(Gear->Y);
           if(ucollisions_CheckCoordInWater(pX, pY + cHHRadius))
           {
               if((*AltGear->Hedgehog).BotLevel < 4)
               {
                   uaimisc_AddWalkBonus(pX, tY, 250, -40);
               }
               return false;
           }
           if((Gear->State & gstMoving) != 0)
           {
               ++(*GoInfo).Ticks;
               Gear->dY = ufloat_hwFloat_hwFloat_op_add(Gear->dY, aiGravity);
               if((ufloat_hwFloat_hwFloat_op_gt(Gear->dY, _0_4)) && ((*Gear->Hedgehog).Effects[heInvulnerable] == 0))
               {
                   (*GoInfo).FallPix = 0;
                   uaimisc_HHJump(AltGear, jmpLJump, &((*GoInfo)));
                   if((*AltGear->Hedgehog).BotLevel < 4)
                   {
                       uaimisc_AddWalkBonus(pX, tY, 175, -20);
                   }
                   return false;
               }
               Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, Gear->dY);
               if(ufloat_hwRound(Gear->Y) > pY)
               {
                   ++(*GoInfo).FallPix;
               }
               if(ucollisions_TestCollisionYwithGear(Gear, 1) != 0)
               {
                   (*GoInfo).Ticks += 410;
                   Gear->State = Gear->State & ~(gstMoving | gstHHJumping);
                   Gear->dY = _0;
                   uaimisc_HHJump(AltGear, jmpLJump, &((*GoInfo)));
                   return true;
               }
               continue;
           }
           Gear->dX = ufloat_SignAs(cLittle, Gear->dX);
           if(ugearsutils_MakeHedgehogsStep(Gear))
           {
               (*GoInfo).Ticks += cHHStepTicks;
           }
           if((pX != ufloat_hwRound(Gear->X)) && ((Gear->State & gstMoving) == 0))
           {
               return true;
           }
       } while(!(((pX == ufloat_hwRound(Gear->X)) && (pY == ufloat_hwRound(Gear->Y))) && ((Gear->State & gstMoving) == 0)));
    uaimisc_HHJump(AltGear, jmpHJump, &((*GoInfo)));
    return hhgo_result;
};
LongInt uaimisc_AIrndSign(LongInt num)
{
    LongInt airndsign_result;
    if(fpcrtl_random(2) == 0)
    {
        airndsign_result = num;
    }
    else
    {
        airndsign_result = -num;
    }
    return airndsign_result;
};
LongInt uaimisc_AIrndOffset(TTarget targ,LongWord Level)
{
    LongInt airndoffset_result;
    if(Level != 1)
    {
        return 0;
    }
    airndoffset_result = (targ.Radius * (fpcrtl_random(7) - 3)) * 2;
    return airndoffset_result;
};
void uaimisc_initModule()
{
    friendlyfactor = 300;
    KnownExplosion.X = 0;
    KnownExplosion.Y = 0;
    KnownExplosion.Radius = 0;
};
void uaimisc_freeModule()
{
};
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TJumpType enumvar)
{
    switch(enumvar){
    case jmpNone:
        return fpcrtl_make_string("jmpNone");
        break;
    case jmpHJump:
        return fpcrtl_make_string("jmpHJump");
        break;
    case jmpLJump:
        return fpcrtl_make_string("jmpLJump");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}