#include "fpcrtl.h"

#include "uAIAmmoTests.h"
real aiWindSpeed;
hwFloat aiGravity;
real aiGravityf;
boolean aiLaserSighting;
LongInt aiHogsInTeam;
AmmoTests_tt AmmoTests = {{
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = &uaiammotests_TestGrenade,
                              .flags = 0
                          },
                          {
                              .proc = &uaiammotests_TestClusterBomb,
                              .flags = 0
                          },
                          {
                              .proc = &uaiammotests_TestBazooka,
                              .flags = 0
                          },
                          {
                              .proc = &uaiammotests_TestBee,
                              .flags = amtest_Rare
                          },
                          {
                              .proc = &uaiammotests_TestShotgun,
                              .flags = amtest_LaserSight
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = &uaiammotests_TestMine,
                              .flags = amtest_NoTarget
                          },
                          {
                              .proc = &uaiammotests_TestDesertEagle,
                              .flags = (amtest_MultipleAttacks | amtest_LaserSight)
                          },
                          {
                              .proc = &uaiammotests_TestDynamite,
                              .flags = amtest_NoTarget
                          },
                          {
                              .proc = &uaiammotests_TestFirePunch,
                              .flags = amtest_NoTarget
                          },
                          {
                              .proc = &uaiammotests_TestWhip,
                              .flags = (amtest_NoTarget | amtest_NoInvulnerable)
                          },
                          {
                              .proc = &uaiammotests_TestBaseballBat,
                              .flags = (amtest_NoTarget | amtest_NoInvulnerable)
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = &uaiammotests_TestAirAttack,
                              .flags = amtest_Rare
                          },
                          {
                              .proc = &uaiammotests_TestMineStrike,
                              .flags = amtest_Rare
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = &uaiammotests_TestMortar,
                              .flags = 0
                          },
                          {
                              .proc = &uaiammotests_TestKamikaze,
                              .flags = ((amtest_LaserSight | amtest_NoInvulnerable) | amtest_NoVampiric)
                          },
                          {
                              .proc = &uaiammotests_TestCake,
                              .flags = (amtest_Rare | amtest_NoTarget)
                          },
                          {
                              .proc = &uaiammotests_TestSeduction,
                              .flags = amtest_NoTarget
                          },
                          {
                              .proc = &uaiammotests_TestWatermelon,
                              .flags = 0
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = &uaiammotests_TestDrillRocket,
                              .flags = 0
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = &uaiammotests_TestRCPlane,
                              .flags = amtest_LaserSight
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = &uaiammotests_TestSniperRifle,
                              .flags = 0
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = &uaiammotests_TestMolotov,
                              .flags = 0
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = &uaiammotests_TestPiano,
                              .flags = ((amtest_Rare | amtest_NoInvulnerable) | amtest_NoVampiric)
                          },
                          {
                              .proc = &uaiammotests_TestGrenade,
                              .flags = amtest_NoTrackFall
                          },
                          {
                              .proc = &uaiammotests_TestSineGun,
                              .flags = amtest_NoVampiric
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = &uaiammotests_TestSMine,
                              .flags = 0
                          },
                          {
                              .proc = &uaiammotests_TestHammer,
                              .flags = (amtest_NoTarget | amtest_NoInvulnerable)
                          },
                          {
                              .proc = &uaiammotests_TestResurrector,
                              .flags = (((amtest_NoTarget | amtest_NoInvulnerable) | amtest_NoVampiric) | amtest_NoLowGravity)
                          },
                          {
                              .proc = &uaiammotests_TestDrillStrike,
                              .flags = amtest_Rare
                          },
                          {
                              .proc = &uaiammotests_TestSnowball,
                              .flags = (amtest_NoInvulnerable | amtest_NoVampiric)
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = &uaiammotests_TestKnife,
                              .flags = 0
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = &uaiammotests_TestAirMine,
                              .flags = amtest_LaserSight
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          },
                          {
                              .proc = &uaiammotests_TestMinigun,
                              .flags = amtest_LaserSight
                          },
                          {
                              .proc = NULL,
                              .flags = 0
                          }};
#include "uVariables.h"
#include "uUtils.h"
#include "uGearsHandlers.h"
#include "uLandUtils.h"
LongInt uaiammotests_Metric(LongInt x1,LongInt y1,LongInt x2,LongInt y2)
{
    LongInt metric_result;
    metric_result = fpcrtl_abs(x1 - x2) + fpcrtl_abs(y1 - y2);
    return metric_result;
};
LongInt uaiammotests_TestBazooka(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testbazooka_result;
    enum{cExtraTime = 300};
    real Vx;
    real Vy;
    real r;
    real mX;
    real mY;
    LongInt rTime;
    LongInt EX;
    LongInt EY;
    LongInt valueResult;
    real targXWrap;
    real x;
    real y;
    real dX;
    real dY;
    LongInt t;
    LongInt value;
    UNUSED (Flags);
    mX = ufloat_hwFloat2Float(Me->X);
    mY = ufloat_hwFloat2Float(Me->Y);
    (*ap).Time = 0;
    rTime = 350;
    (*ap).ExplR = 0;
    if(WorldEdge == weWrap)
    {
        if(Targ.Point.x < mX)
        {
            targXWrap = Targ.Point.x + (rightX - leftX);
        }
        else
        {
            targXWrap = Targ.Point.x - (rightX - leftX);
        }
    }
    valueResult = BadTurn;
    do {
           rTime = ((rTime + 300) + (Level * 50)) + fpcrtl_random(300);
           if((WorldEdge == weWrap) && (fpcrtl_random(2) == 0))
           {
               Vx = ((-aiWindSpeed * rTime) * 0.5) + ((((targXWrap + uaimisc_AIrndSign(2)) + uaimisc_AIrndOffset(Targ, Level)) - mX) /(float) rTime);
           }
           else
           {
               Vx = ((-aiWindSpeed * rTime) * 0.5) + ((((Targ.Point.x + uaimisc_AIrndSign(2)) + uaimisc_AIrndOffset(Targ, Level)) - mX) /(float) rTime);
           }
           Vy = ((aiGravityf * rTime) * 0.5) - (((Targ.Point.y + 1) - mY) /(float) rTime);
           r = fpcrtl_sqr(Vx) + fpcrtl_sqr(Vy);
           if(!(r > 1))
           {
               x = mX;
               y = mY;
               dX = Vx;
               dY = -Vy;
               t = rTime;
               do {
                      x = uaimisc_CheckWrap(x);
                      x = x + dX;
                      y = y + dY;
                      dX = dX + aiWindSpeed;
                      dY = dY + aiGravityf;
                      --t;
                  } while(!((((Me == CurrentHedgehog->Gear) && uaimisc_TestColl(fpcrtl_trunc(x), fpcrtl_trunc(y), 5)) || ((Me != CurrentHedgehog->Gear) && uaimisc_TestCollExcludingMe((*Me->Hedgehog).Gear, fpcrtl_trunc(x), fpcrtl_trunc(y), 5))) || (t < -cExtraTime)));
               EX = fpcrtl_trunc(x);
               EY = fpcrtl_trunc(y);
               if(t >= -cExtraTime)
               {
                   if(Level == 1)
                   {
                       value = uaimisc_RateExplosion_5(Me, EX, EY, 101, afTrackFall | afErasesLand);
                   }
                   else
                   {
                       value = uaimisc_RateExplosion_4(Me, EX, EY, 101);
                   }
               }
               else
               {
                   value = BadTurn;
               }
               if(((value == 0) && (Targ.Kind == gtHedgehog)) && (Targ.Score > 0))
               {
                   if((GameFlags & gfSolidLand) == 0)
                   {
                       value = 1024 - (uaiammotests_Metric(Targ.Point.x, Targ.Point.y, EX, EY) / 64);
                   }
                   else
                   {
                       value = BadTurn;
                   }
               }
               if((valueResult < value) || ((valueResult == value) && (Level < 3)))
               {
                   (*ap).Angle = uutils_DxDy2AttackAnglef(Vx, Vy) + uaimisc_AIrndSign(fpcrtl_random((Level - 1) * 9));
                   (*ap).Power = fpcrtl_trunc(sqrt(r) * cMaxPower) - fpcrtl_random(((Level - 1) * 17) + 1);
                   (*ap).ExplR = 100;
                   (*ap).ExplX = EX;
                   (*ap).ExplY = EY;
                   valueResult = value;
               }
           }
       } while(!(rTime > (5050 - (Level * 800))));
    testbazooka_result = valueResult;
    return testbazooka_result;
};
LongInt uaiammotests_calcBeeFlight(PGear Me,real x,real y,real dx,real dy,real tX,real tY,LongInt (*eX),LongInt (*eY))
{
    LongInt calcbeeflight_result;
    LongWord t;
    boolean f;
    real speed;
    real d;
    t = 500;
    do {
           x = x + dx;
           y = y + dy;
           dy = dy + aiGravityf;
           f = ((Me == CurrentHedgehog->Gear) && uaimisc_TestColl(fpcrtl_trunc(x), fpcrtl_trunc(y), 5)) || ((Me != CurrentHedgehog->Gear) && uaimisc_TestCollExcludingMe((*Me->Hedgehog).Gear, fpcrtl_trunc(x), fpcrtl_trunc(y), 5));
           --t;
       } while(!(((t == 0) || (y >= cWaterLine)) || f));
    if(f)
    {
        (*eX) = fpcrtl_trunc(x);
        (*eY) = fpcrtl_trunc(y);
        return uaimisc_RateExplosion_5(Me, (*eX), (*eY), 101, afTrackFall | afErasesLand);
    }
    t = 5000;
    speed = sqrt(fpcrtl_sqr(dx) + fpcrtl_sqr(dy));
    do {
           if((t & 0xf) == 0)
           {
               dx = dx + (6.4e-5 * (tX - x));
               dy = dy + (6.4e-5 * (tY - y));
               d = speed /(float) sqrt(fpcrtl_sqr(dx) + fpcrtl_sqr(dy));
               dx = dx * d;
               dy = dy * d;
           }
           x = x + dx;
           y = y + dy;
           f = ((Me == CurrentHedgehog->Gear) && uaimisc_TestColl(fpcrtl_trunc(x), fpcrtl_trunc(y), 5)) || ((Me != CurrentHedgehog->Gear) && uaimisc_TestCollExcludingMe((*Me->Hedgehog).Gear, fpcrtl_trunc(x), fpcrtl_trunc(y), 5));
           --t;
       } while(!((t == 0) || f));
    if(f)
    {
        (*eX) = fpcrtl_trunc(x);
        (*eY) = fpcrtl_trunc(y);
        return uaimisc_RateExplosion_5(Me, (*eX), (*eY), 101, afTrackFall | afErasesLand);
    }
    else
    {
        calcbeeflight_result = BadTurn;
    }
    return calcbeeflight_result;
};
LongInt uaiammotests_TestBee(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testbee_result;
    LongInt i;
    LongInt j;
    LongInt valueResult;
    LongInt v;
    LongInt a;
    LongInt p;
    real mX;
    real mY;
    LongInt eX;
    LongInt eY;
    UNUSED (Flags);
    if(Level > 1)
    {
        return BadTurn;
    }
    eX = 0;
    eY = 0;
    mX = ufloat_hwFloat2Float(Me->X);
    mY = ufloat_hwFloat2Float(Me->Y);
    valueResult = BadTurn;
    {i = 0;
     LongInt i__end__ = 8;
     if (i <= i__end__) do {
                               {j = 0;
                                LongInt j__end__ = 1;
                                if (j <= j__end__) do {
                                                          a = i * 120;
                                                          p = fpcrtl_random(cMaxPower - 200) + 180;
                                                          if(j == 0)
                                                          {
                                                              a = -a;
                                                          }
                                                          v = uaiammotests_calcBeeFlight(Me, mX, mY, (sin((a * pi) /(float) 2048) * p) /(float) cPowerDivisor, (-cos((a * pi) /(float) 2048) * p) /(float) cPowerDivisor, Targ.Point.x, Targ.Point.y, &(eX), &(eY));
                                                          if(v > valueResult)
                                                          {
                                                              (*ap).ExplR = 100;
                                                              (*ap).ExplX = eX;
                                                              (*ap).ExplY = eY;
                                                              (*ap).Angle = a;
                                                              (*ap).Power = p;
                                                              valueResult = v;
                                                          }
                                                      } while(j++ != j__end__);}
                           } while(i++ != i__end__);}
    (*ap).AttackPutX = Targ.Point.x;
    (*ap).AttackPutY = Targ.Point.y;
    if(valueResult > 0)
    {
        testbee_result = valueResult - 5000;
    }
    else
    {
        testbee_result = BadTurn;
    }
    return testbee_result;
};
LongInt uaiammotests_TestDrillRocket(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testdrillrocket_result;
    real Vx;
    real Vy;
    real r;
    real mX;
    real mY;
    LongInt rTime;
    LongInt EX;
    LongInt EY;
    LongInt valueResult;
    real targXWrap;
    real x;
    real y;
    real dX;
    real dY;
    LongInt t;
    LongInt value;
    real t2;
    LongInt timer;
    UNUSED (Flags);
    if(Level > 3)
    {
        return BadTurn;
    }
    mX = ufloat_hwFloat2Float(Me->X);
    mY = ufloat_hwFloat2Float(Me->Y);
    (*ap).Time = 0;
    rTime = 350;
    (*ap).ExplR = 0;
    valueResult = BadTurn;
    if(WorldEdge == weWrap)
    {
        if(Targ.Point.x < mX)
        {
            targXWrap = Targ.Point.x + (rightX - leftX);
        }
        else
        {
            targXWrap = Targ.Point.x - (rightX - leftX);
        }
    }
    timer = 0;
    do {
           rTime = ((rTime + 300) + (Level * 50)) + fpcrtl_random(300);
           if((WorldEdge == weWrap) && (fpcrtl_random(2) == 0))
           {
               Vx = ((-aiWindSpeed * rTime) * 0.5) + (((targXWrap + uaimisc_AIrndSign(2)) - mX) /(float) rTime);
           }
           else
           {
               Vx = ((-aiWindSpeed * rTime) * 0.5) + (((Targ.Point.x + uaimisc_AIrndSign(2)) - mX) /(float) rTime);
           }
           Vy = ((aiGravityf * rTime) * 0.5) - (((Targ.Point.y - 35) - mY) /(float) rTime);
           r = fpcrtl_sqr(Vx) + fpcrtl_sqr(Vy);
           if(!(r > 1))
           {
               x = mX;
               y = mY;
               dX = Vx;
               dY = -Vy;
               t = rTime;
               do {
                      x = uaimisc_CheckWrap(x);
                      x = x + dX;
                      y = y + dY;
                      dX = dX + aiWindSpeed;
                      dY = dY + aiGravityf;
                      --t;
                  } while(!((((Me == CurrentHedgehog->Gear) && uaimisc_TestColl(fpcrtl_trunc(x), fpcrtl_trunc(y), 5)) || ((Me != CurrentHedgehog->Gear) && uaimisc_TestCollExcludingMe((*Me->Hedgehog).Gear, fpcrtl_trunc(x), fpcrtl_trunc(y), 5))) || (y > cWaterLine)));
               if(uaimisc_TestCollExcludingObjects(fpcrtl_trunc(x), fpcrtl_trunc(y), 5) && ((fpcrtl_abs(Targ.Point.x - fpcrtl_trunc(x)) + fpcrtl_abs(Targ.Point.y - fpcrtl_trunc(y))) > 21))
               {
                   timer = 500;
                   t2 = 0.5 /(float) sqrt(fpcrtl_sqr(dX) + fpcrtl_sqr(dY));
                   dX = dX * t2;
                   dY = dY * t2;
                   do {
                          x = x + dX;
                          y = y + dY;
                          --timer;
                      } while(!((((((((fpcrtl_abs(Targ.Point.x - fpcrtl_trunc(x)) + fpcrtl_abs(Targ.Point.y - fpcrtl_trunc(y))) < 22) || (x < 0)) || (y < 0)) || (fpcrtl_trunc(x) > LAND_WIDTH)) || (fpcrtl_trunc(y) > LAND_HEIGHT)) || !uaimisc_TestCollExcludingObjects(fpcrtl_trunc(x), fpcrtl_trunc(y), 5)) || (timer == 0)));
               }
               EX = fpcrtl_trunc(x);
               EY = fpcrtl_trunc(y);
               if(((EY < (cWaterLine - 5)) && (timer > 0)) && ((fpcrtl_abs(Targ.Point.x - fpcrtl_trunc(x)) + fpcrtl_abs(Targ.Point.y - fpcrtl_trunc(y))) > 21))
               {
                   value = BadTurn;
               }
               else
               {
                   if(Level == 1)
                   {
                       value = uaimisc_RateExplosion_5(Me, EX, EY, 101, afTrackFall | afErasesLand);
                   }
                   else
                   {
                       value = uaimisc_RateExplosion_4(Me, EX, EY, 101);
                   }
               }
               if(valueResult <= value)
               {
                   (*ap).Angle = uutils_DxDy2AttackAnglef(Vx, Vy) + uaimisc_AIrndSign(fpcrtl_random((Level - 1) * 9));
                   (*ap).Power = fpcrtl_trunc(sqrt(r) * cMaxPower) - fpcrtl_random(((Level - 1) * 17) + 1);
                   (*ap).ExplR = 100;
                   (*ap).ExplX = EX;
                   (*ap).ExplY = EY;
                   valueResult = value - 2500;
               }
           }
       } while(!(rTime > (5050 - (Level * 800))));
    testdrillrocket_result = valueResult;
    return testdrillrocket_result;
};
LongInt uaiammotests_TestRCPlane(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testrcplane_result;
    enum{MIN_RANGE = 200};
    real Vx;
    real Vy;
    real meX;
    real meY;
    real x;
    real y;
    LongInt rx;
    LongInt ry;
    LongInt valueResult;
    Integer range;
    Integer maxRange;
    UNUSED (Flags);
    if(Level == 5)
    {
        return BadTurn;
    }
    else
    {
        if(Level == 4)
        {
            maxRange = 2200;
        }
        else
        {
            if(Level == 3)
            {
                maxRange = 2900;
            }
            else
            {
                if(Level == 2)
                {
                    maxRange = 3500;
                }
                else
                {
                    maxRange = 3900;
                }
            }
        }
    }
    testrcplane_result = BadTurn;
    (*ap).ExplR = 0;
    (*ap).Time = 0;
    (*ap).Power = 1;
    meX = ufloat_hwFloat2Float(Me->X);
    meY = ufloat_hwFloat2Float(Me->Y);
    x = meX;
    y = meY;
    range = uaiammotests_Metric(fpcrtl_trunc(x), fpcrtl_trunc(y), Targ.Point.x, Targ.Point.y);
    if((range < MIN_RANGE) || (range > maxRange))
    {
        return BadTurn;
    }
    Vx = ((Targ.Point.x - x) * 1) /(float) 1024;
    Vy = ((Targ.Point.y - y) * 1) /(float) 1024;
    (*ap).Angle = uutils_DxDy2AttackAnglef(Vx, -Vy);
    do {
           x = x + Vx;
           y = y + Vy;
           rx = fpcrtl_trunc(x);
           ry = fpcrtl_trunc(y);
           if(((Me == CurrentHedgehog->Gear) && uaimisc_TestColl(rx, ry, 8)) || ((Me != CurrentHedgehog->Gear) && uaimisc_TestCollExcludingMe((*Me->Hedgehog).Gear, rx, ry, 8)))
           {
               x = x + (Vx * 8);
               y = y + (Vy * 8);
               if(Level == 1)
               {
                   valueResult = uaimisc_RateExplosion_5(Me, rx, ry, 26, afTrackFall | afErasesLand);
               }
               else
               {
                   valueResult = uaimisc_RateExplosion_4(Me, rx, ry, 26);
               }
               range = uaiammotests_Metric(fpcrtl_trunc(meX), fpcrtl_trunc(meY), rx, ry);
               if((range < MIN_RANGE) || (range > maxRange))
               {
                   return BadTurn;
               }
               if((((Level < 3) && (range <= 600)) && (meY >= ry)) && ((((*ap).Angle < 0) && (aiWindSpeed > 0)) || (((*ap).Angle > 0) && (aiWindSpeed < 0))))
               {
                   return BadTurn;
               }
               if(!aiLaserSighting)
               {
                   (*ap).Angle += uaimisc_AIrndSign(fpcrtl_random((Level - 1) * 9));
               }
               if(valueResult <= 0)
               {
                   valueResult = BadTurn;
               }
               return valueResult;
           }
       } while(!((((((fpcrtl_abs(Targ.Point.x - fpcrtl_trunc(x)) + fpcrtl_abs(Targ.Point.y - fpcrtl_trunc(y))) < 4) || (x < 0)) || (y < 0)) || (fpcrtl_trunc(x) > LAND_WIDTH)) || (fpcrtl_trunc(y) > LAND_HEIGHT)));
    testrcplane_result = BadTurn;
    return testrcplane_result;
};
LongInt uaiammotests_TestSnowball(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testsnowball_result;
    enum{timeLimit = 5000};
    real Density = 0.5;
    real Vx;
    real Vy;
    real r;
    LongInt rTime;
    LongInt EX;
    LongInt EY;
    LongInt valueResult;
    real targXWrap;
    real x;
    real y;
    real dX;
    real dY;
    real meX;
    real meY;
    LongInt t;
    LongInt value;
    UNUSED (Flags);
    meX = ufloat_hwFloat2Float(Me->X);
    meY = ufloat_hwFloat2Float(Me->Y);
    (*ap).Time = 0;
    rTime = 350;
    (*ap).ExplR = 0;
    valueResult = BadTurn;
    if(WorldEdge == weWrap)
    {
        if(Targ.Point.x < meX)
        {
            targXWrap = Targ.Point.x + (rightX - leftX);
        }
        else
        {
            targXWrap = Targ.Point.x - (rightX - leftX);
        }
    }
    do {
           rTime = ((rTime + 300) + (Level * 50)) + fpcrtl_random(300);
           if((WorldEdge == weWrap) && (fpcrtl_random(2) == 0))
           {
               Vx = (targXWrap - meX) /(float) rTime;
           }
           else
           {
               Vx = (Targ.Point.x - meX) /(float) rTime;
           }
           if((GameFlags & gfMoreWind) != 0)
           {
               Vx = ((-(aiWindSpeed /(float) Density) * rTime) * 0.5) + Vx;
           }
           else
           {
               Vx = ((-aiWindSpeed * rTime) * 0.5) + Vx;
           }
           Vy = ((aiGravityf * rTime) * 0.5) - ((Targ.Point.y - meY) /(float) rTime);
           r = fpcrtl_sqr(Vx) + fpcrtl_sqr(Vy);
           if(!(r > 1))
           {
               x = meX;
               y = meY;
               dX = Vx;
               dY = -Vy;
               t = rTime;
               do {
                      x = uaimisc_CheckWrap(x);
                      x = x + dX;
                      if((GameFlags & gfMoreWind) != 0)
                      {
                          dX = dX + (aiWindSpeed /(float) Density);
                      }
                      else
                      {
                          dX = dX + aiWindSpeed;
                      }
                      y = y + dY;
                      dY = dY + aiGravityf;
                      --t;
                  } while(!(((((Me == CurrentHedgehog->Gear) && uaimisc_TestColl(fpcrtl_trunc(x), fpcrtl_trunc(y), 4)) || ((Me != CurrentHedgehog->Gear) && uaimisc_TestCollExcludingMe((*Me->Hedgehog).Gear, fpcrtl_trunc(x), fpcrtl_trunc(y), 4))) || (fpcrtl_trunc(y) > cWaterLine)) || (t < -timeLimit)));
               EX = fpcrtl_trunc(x);
               EY = fpcrtl_trunc(y);
               if(uaiammotests_Metric(fpcrtl_trunc(meX), fpcrtl_trunc(meY), EX, EY) <= 40)
               {
                   value = BadTurn;
               }
               else
               {
                   if((t >= -timeLimit) && (EY <= cWaterLine))
                   {
                       value = uaimisc_RateShove(Me, EX, EY, 16, 0, fpcrtl_trunc((fpcrtl_abs(dX) + fpcrtl_abs(dY)) * 20), dX, dY, afTrackFall);
                   }
                   else
                   {
                       value = BadTurn;
                   }
               }
               if(((value == 0) && (Targ.Kind == gtHedgehog)) && (Targ.Score > 0))
               {
                   value = BadTurn;
               }
               if((valueResult < value) || ((valueResult == value) && (Level == 1)))
               {
                   (*ap).Angle = uutils_DxDy2AttackAnglef(Vx, Vy) + uaimisc_AIrndSign(fpcrtl_random((Level - 1) * 12));
                   (*ap).Power = fpcrtl_trunc(sqrt(r) * cMaxPower) - fpcrtl_random(((Level - 1) * 22) + 1);
                   (*ap).ExplX = EX;
                   (*ap).ExplY = EY;
                   valueResult = value;
               }
           }
       } while(!(rTime > (5050 - (Level * 800))));
    testsnowball_result = valueResult;
    return testsnowball_result;
};
LongInt uaiammotests_TestMolotov(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testmolotov_result;
    enum{timeLimit = 50};
    real Density = 2.0;
    real Vx;
    real Vy;
    real r;
    real meX;
    real meY;
    LongInt rTime;
    LongInt EX;
    LongInt EY;
    LongInt valueResult;
    real targXWrap;
    real x;
    real y;
    real dX;
    real dY;
    LongInt t;
    LongInt value;
    LongInt range;
    UNUSED (Flags);
    meX = ufloat_hwFloat2Float(Me->X);
    meY = ufloat_hwFloat2Float(Me->Y);
    (*ap).Time = 0;
    rTime = 350;
    (*ap).ExplR = 0;
    if(WorldEdge == weWrap)
    {
        if(Targ.Point.x < meX)
        {
            targXWrap = Targ.Point.x + (rightX - leftX);
        }
        else
        {
            targXWrap = Targ.Point.x - (rightX - leftX);
        }
    }
    valueResult = BadTurn;
    do {
           rTime = ((rTime + 300) + (Level * 50)) + fpcrtl_random(300);
           if((WorldEdge == weWrap) && (fpcrtl_random(2) == 0))
           {
               Vx = (((targXWrap + uaimisc_AIrndSign(2)) + uaimisc_AIrndOffset(Targ, Level)) - meX) /(float) rTime;
           }
           else
           {
               Vx = (((Targ.Point.x + uaimisc_AIrndSign(2)) + uaimisc_AIrndOffset(Targ, Level)) - meX) /(float) rTime;
           }
           if((GameFlags & gfMoreWind) != 0)
           {
               Vx = ((-(aiWindSpeed /(float) Density) * rTime) * 0.5) + Vx;
           }
           Vy = ((aiGravityf * rTime) * 0.5) - (((Targ.Point.y + 1) - meY) /(float) rTime);
           r = fpcrtl_sqr(Vx) + fpcrtl_sqr(Vy);
           if(!(r > 1))
           {
               x = meX;
               y = meY;
               dX = Vx;
               dY = -Vy;
               t = rTime;
               do {
                      x = uaimisc_CheckWrap(x);
                      x = x + dX;
                      if((GameFlags & gfMoreWind) != 0)
                      {
                          dX = dX + (aiWindSpeed /(float) Density);
                      }
                      y = y + dY;
                      dY = dY + aiGravityf;
                      --t;
                  } while(!((((Me == CurrentHedgehog->Gear) && uaimisc_TestColl(fpcrtl_trunc(x), fpcrtl_trunc(y), 5)) || ((Me != CurrentHedgehog->Gear) && uaimisc_TestCollExcludingMe((*Me->Hedgehog).Gear, fpcrtl_trunc(x), fpcrtl_trunc(y), 5))) || (t < -timeLimit)));
               EX = fpcrtl_trunc(x);
               EY = fpcrtl_trunc(y);
               range = uaiammotests_Metric(fpcrtl_trunc(meX), fpcrtl_trunc(meY), EX, EY);
               if(!uaimisc_TestCollHogsOrObjects(EX, EY, 5))
               {
                   value = BadTurn;
               }
               else
               {
                   if((range < 150) && (Level < 5))
                   {
                       value = BadTurn;
                   }
                   else
                   {
                       if((((Level < 3) && (range <= 1000)) && (fpcrtl_trunc(meY) >= EY)) && (((*ap).Angle < 0) != (aiWindSpeed < 0)))
                       {
                           value = BadTurn;
                       }
                       else
                       {
                           if(t < -timeLimit)
                           {
                               value = BadTurn;
                           }
                           else
                           {
                               value = uaimisc_RateExplosion_4(Me, EX, EY, 97);
                           }
                       }
                   }
               }
               if(((value == 0) && (Targ.Kind == gtHedgehog)) && (Targ.Score > 0))
               {
                   value = BadTurn;
               }
               if((valueResult < value) || ((valueResult == value) && (Level < 3)))
               {
                   (*ap).Angle = uutils_DxDy2AttackAnglef(Vx, Vy) + uaimisc_AIrndSign(fpcrtl_random((Level - 1) * 9));
                   (*ap).Power = fpcrtl_trunc(sqrt(r) * cMaxPower) - fpcrtl_random(((Level - 1) * 17) + 1);
                   (*ap).ExplR = 100;
                   (*ap).ExplX = EX;
                   (*ap).ExplY = EY;
                   valueResult = value;
               }
           }
       } while(!(rTime > (5050 - (Level * 800))));
    testmolotov_result = valueResult;
    return testmolotov_result;
};
LongInt uaiammotests_TestGrenade(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testgrenade_result;
    enum{tDelta = 24};
    real Density = 1.5;
    real Vx;
    real Vy;
    real r;
    LongInt Score;
    LongInt EX;
    LongInt EY;
    LongInt valueResult;
    LongInt TestTime;
    real targXWrap;
    real x;
    real y;
    real meX;
    real meY;
    real dX;
    real dY;
    LongInt t;
    valueResult = BadTurn;
    TestTime = 0;
    (*ap).Bounce = 0;
    (*ap).ExplR = 0;
    meX = ufloat_hwFloat2Float(Me->X);
    meY = ufloat_hwFloat2Float(Me->Y);
    if(WorldEdge == weWrap)
    {
        if(Targ.Point.x < meX)
        {
            targXWrap = Targ.Point.x + (rightX - leftX);
        }
        else
        {
            targXWrap = Targ.Point.x - (rightX - leftX);
        }
    }
    do {
           TestTime += 1000;
           if((WorldEdge == weWrap) && (fpcrtl_random(2) == 0))
           {
               Vx = ((targXWrap + uaimisc_AIrndOffset(Targ, Level)) - meX) /(float) (TestTime + tDelta);
           }
           else
           {
               Vx = ((Targ.Point.x + uaimisc_AIrndOffset(Targ, Level)) - meX) /(float) (TestTime + tDelta);
           }
           if((GameFlags & gfMoreWind) != 0)
           {
               Vx = ((-(aiWindSpeed /(float) Density) * (TestTime + tDelta)) * 0.5) + Vx;
           }
           Vy = (aiGravityf * ((TestTime + tDelta) / 2)) - ((Targ.Point.y - meY) /(float) (TestTime + tDelta));
           r = fpcrtl_sqr(Vx) + fpcrtl_sqr(Vy);
           if(!(r > 1))
           {
               x = meX;
               y = meY;
               dX = Vx;
               dY = -Vy;
               t = TestTime;
               do {
                      x = uaimisc_CheckWrap(x);
                      x = x + dX;
                      if((GameFlags & gfMoreWind) != 0)
                      {
                          dX = dX + (aiWindSpeed /(float) Density);
                      }
                      y = y + dY;
                      dY = dY + aiGravityf;
                      --t;
                  } while(!((((Me == CurrentHedgehog->Gear) && uaimisc_TestColl(fpcrtl_trunc(x), fpcrtl_trunc(y), 5)) || ((Me != CurrentHedgehog->Gear) && uaimisc_TestCollExcludingMe((*Me->Hedgehog).Gear, fpcrtl_trunc(x), fpcrtl_trunc(y), 5))) || (t == 0)));
               EX = fpcrtl_trunc(x);
               EY = fpcrtl_trunc(y);
               if(t < 50)
               {
                   if((Level == 1) && ((Flags & amtest_NoTrackFall) == 0))
                   {
                       Score = uaimisc_RateExplosion_5(Me, EX, EY, 101, afTrackFall | afErasesLand);
                   }
                   else
                   {
                       Score = uaimisc_RateExplosion_4(Me, EX, EY, 101);
                   }
               }
               else
               {
                   Score = BadTurn;
               }
               if((valueResult < Score) && (Score > 0))
               {
                   (*ap).Angle = uutils_DxDy2AttackAnglef(Vx, Vy) + uaimisc_AIrndSign(fpcrtl_random(Level * 3));
                   (*ap).Power = fpcrtl_trunc(sqrt(r) * cMaxPower) + uaimisc_AIrndSign(fpcrtl_random(Level) * 20);
                   (*ap).Time = TestTime;
                   (*ap).ExplR = 100;
                   (*ap).ExplX = EX;
                   (*ap).ExplY = EY;
                   valueResult = Score;
               }
           }
       } while(!(TestTime > (4500 - (Level * 512))));
    testgrenade_result = valueResult;
    return testgrenade_result;
};
LongInt uaiammotests_TestClusterBomb(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testclusterbomb_result;
    enum{tDelta = 24};
    real Density = 1.5;
    real Vx;
    real Vy;
    real r;
    LongInt Score;
    LongInt EX;
    LongInt EY;
    LongInt valueResult;
    LongWord TestTime;
    real x;
    real y;
    real dX;
    real dY;
    real meX;
    real meY;
    LongInt t;
    UNUSED (Flags);
    valueResult = BadTurn;
    TestTime = 500;
    (*ap).Bounce = 0;
    (*ap).ExplR = 0;
    meX = ufloat_hwFloat2Float(Me->X);
    meY = ufloat_hwFloat2Float(Me->Y);
    do {
           TestTime += 900;
           if((GameFlags & gfMoreWind) != 0)
           {
               Vx = ((-(aiWindSpeed /(float) Density) * (TestTime + tDelta)) * 0.5) + ((Targ.Point.x - meX) /(float) (TestTime + tDelta));
           }
           else
           {
               if(meX < Targ.Point.x)
               {
                   Vx = ((Targ.Point.x + 10) - meX) /(float) (TestTime + tDelta);
               }
               else
               {
                   Vx = ((Targ.Point.x - 10) - meX) /(float) (TestTime + tDelta);
               }
           }
           Vy = (aiGravityf * ((TestTime + tDelta) / 2)) - (((Targ.Point.y - 50) - meY) /(float) (TestTime + tDelta));
           r = fpcrtl_sqr(Vx) + fpcrtl_sqr(Vy);
           if(!(r > 1))
           {
               x = meX;
               dX = Vx;
               y = meY;
               dY = -Vy;
               t = TestTime;
               do {
                      x = x + dX;
                      if((GameFlags & gfMoreWind) != 0)
                      {
                          dX = dX + (aiWindSpeed /(float) Density);
                      }
                      y = y + dY;
                      dY = dY + aiGravityf;
                      --t;
                  } while(!((((Me == CurrentHedgehog->Gear) && uaimisc_TestColl(fpcrtl_trunc(x), fpcrtl_trunc(y), 5)) || ((Me != CurrentHedgehog->Gear) && uaimisc_TestCollExcludingMe((*Me->Hedgehog).Gear, fpcrtl_trunc(x), fpcrtl_trunc(y), 5))) || (t == 0)));
               EX = fpcrtl_trunc(x);
               EY = fpcrtl_trunc(y);
               if(t < 50)
               {
                   Score = uaimisc_RateExplosion_4(Me, EX, EY, 41);
               }
               else
               {
                   Score = BadTurn;
               }
               if(Score > 0)
               {
                   (*ap).Angle = uutils_DxDy2AttackAnglef(Vx, Vy) + uaimisc_AIrndSign(fpcrtl_random(Level * 2));
                   (*ap).Power = fpcrtl_trunc(sqrt(r) * cMaxPower) + uaimisc_AIrndSign(fpcrtl_random(Level) * 15);
                   (*ap).Time = (TestTime / 1000) * 1000;
                   (*ap).ExplR = 90;
                   (*ap).ExplX = EX;
                   (*ap).ExplY = EY;
                   valueResult = Score;
               }
           }
       } while(!(TestTime == 4100));
    testclusterbomb_result = valueResult;
    return testclusterbomb_result;
};
LongInt uaiammotests_TestWatermelon(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testwatermelon_result;
    enum{tDelta = 24};
    real Density = 2.0;
    real Vx;
    real Vy;
    real r;
    LongInt Score;
    LongInt EX;
    LongInt EY;
    LongInt valueResult;
    LongWord TestTime;
    real targXWrap;
    real x;
    real y;
    real dX;
    real dY;
    real meX;
    real meY;
    LongInt t;
    UNUSED (Flags);
    valueResult = BadTurn;
    TestTime = 500;
    (*ap).ExplR = 0;
    meX = ufloat_hwFloat2Float(Me->X);
    meY = ufloat_hwFloat2Float(Me->Y);
    if(WorldEdge == weWrap)
    {
        if(Targ.Point.x < meX)
        {
            targXWrap = Targ.Point.x + (rightX - leftX);
        }
        else
        {
            targXWrap = Targ.Point.x - (rightX - leftX);
        }
    }
    do {
           TestTime += 900;
           if((WorldEdge == weWrap) && (fpcrtl_random(2) == 0))
           {
               Vx = (targXWrap - meX) /(float) (TestTime + tDelta);
           }
           else
           {
               Vx = (Targ.Point.x - meX) /(float) (TestTime + tDelta);
           }
           if((GameFlags & gfMoreWind) != 0)
           {
               Vx = ((-(aiWindSpeed /(float) Density) * (TestTime + tDelta)) * 0.5) + Vx;
           }
           Vy = (aiGravityf * ((TestTime + tDelta) / 2)) - (((Targ.Point.y - 50) - meY) /(float) (TestTime + tDelta));
           r = fpcrtl_sqr(Vx) + fpcrtl_sqr(Vy);
           if(!(r > 1))
           {
               x = meX;
               dX = Vx;
               y = meY;
               dY = -Vy;
               t = TestTime;
               do {
                      x = uaimisc_CheckWrap(x);
                      x = x + dX;
                      if((GameFlags & gfMoreWind) != 0)
                      {
                          dX = dX + (aiWindSpeed /(float) Density);
                      }
                      y = y + dY;
                      dY = dY + aiGravityf;
                      --t;
                  } while(!((((Me == CurrentHedgehog->Gear) && uaimisc_TestColl(fpcrtl_trunc(x), fpcrtl_trunc(y), 6)) || ((Me != CurrentHedgehog->Gear) && uaimisc_TestCollExcludingMe((*Me->Hedgehog).Gear, fpcrtl_trunc(x), fpcrtl_trunc(y), 6))) || (t == 0)));
               EX = fpcrtl_trunc(x);
               EY = fpcrtl_trunc(y);
               if(t < 50)
               {
                   Score = uaimisc_RateExplosion_4(Me, EX, EY, 200) + uaimisc_RateExplosion_4(Me, EX, EY + 120, 200);
               }
               else
               {
                   Score = BadTurn;
               }
               if(valueResult < Score)
               {
                   (*ap).Angle = uutils_DxDy2AttackAnglef(Vx, Vy) + uaimisc_AIrndSign(fpcrtl_random(Level));
                   (*ap).Power = fpcrtl_trunc(sqrt(r) * cMaxPower) + uaimisc_AIrndSign(fpcrtl_random(Level) * 15);
                   (*ap).Time = (TestTime / 1000) * 1000;
                   (*ap).ExplR = 300;
                   (*ap).ExplX = EX;
                   (*ap).ExplY = EY;
                   valueResult = Score;
               }
           }
       } while(!(TestTime == 4100));
    testwatermelon_result = valueResult;
    return testwatermelon_result;
};
LongWord uaiammotests_Solve(LongInt TX,LongInt TY,LongInt MX,LongInt MY)
{
    LongWord solve_result;
    real A;
    real B;
    real D;
    real T;
    LongInt C;
    A = fpcrtl_sqr(aiGravityf);
    B = (-aiGravityf * (TY - MY)) - 1;
    C = fpcrtl_sqr(TY - MY) + fpcrtl_sqr(TX - MX);
    D = fpcrtl_sqr(B) - (A * C);
    if(D >= 0)
    {
        D = sqrt(D) - B;
        if(D >= 0)
        {
            T = sqrt((D * 2) /(float) A);
        }
        else
        {
            T = 0;
        }
        solve_result = fpcrtl_trunc(T);
    }
    else
    {
        solve_result = 0;
    }
    return solve_result;
};
LongInt uaiammotests_TestMortar(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testmortar_result;
    real Density = 1.0;
    real Vx;
    real Vy;
    LongInt Score;
    LongInt EX;
    LongInt EY;
    LongWord TestTime;
    real x;
    real y;
    real dX;
    real dY;
    real meX;
    real meY;
    UNUSED (Flags);
    testmortar_result = BadTurn;
    (*ap).ExplR = 0;
    meX = ufloat_hwFloat2Float(Me->X);
    meY = ufloat_hwFloat2Float(Me->Y);
    if(Level > 2)
    {
        return BadTurn;
    }
    TestTime = uaiammotests_Solve(Targ.Point.x, Targ.Point.y, fpcrtl_trunc(meX), fpcrtl_trunc(meY));
    if(TestTime == 0)
    {
        return BadTurn;
    }
    Vx = (Targ.Point.x - meX) /(float) TestTime;
    if((GameFlags & gfMoreWind) != 0)
    {
        Vx = ((-(aiWindSpeed /(float) Density) * TestTime) * 0.5) + Vx;
    }
    Vy = (aiGravityf * (TestTime / 2)) - ((Targ.Point.y - meY) /(float) TestTime);
    x = meX;
    dX = Vx;
    y = meY;
    dY = -Vy;
    do {
           x = x + dX;
           if((GameFlags & gfMoreWind) != 0)
           {
               dX = dX + (aiWindSpeed /(float) Density);
           }
           y = y + dY;
           dY = dY + aiGravityf;
           EX = fpcrtl_trunc(x);
           EY = fpcrtl_trunc(y);
       } while(!((((Me == CurrentHedgehog->Gear) && uaimisc_TestColl(EX, EY, 4)) || ((Me != CurrentHedgehog->Gear) && uaimisc_TestCollExcludingMe((*Me->Hedgehog).Gear, EX, EY, 4))) || (EY > cWaterLine)));
    if((EY < cWaterLine) && (dY >= 0))
    {
        Score = uaimisc_RateExplosion_4(Me, EX, EY, 91);
        if(Score == 0)
        {
            if(((dY > 0.15) && (Targ.Kind == gtHedgehog)) && (Targ.Score > 0))
            {
                Score = -fpcrtl_abs(Targ.Point.y - EY) / 32;
            }
            else
            {
                Score = BadTurn;
            }
        }
        else
        {
            if(Score < 0)
            {
                Score = BadTurn;
            }
        }
    }
    else
    {
        Score = BadTurn;
    }
    if(Score > 0)
    {
        (*ap).Angle = uutils_DxDy2AttackAnglef(Vx, Vy) + uaimisc_AIrndSign(fpcrtl_random(Level));
        (*ap).Power = 1;
        (*ap).ExplR = 100;
        (*ap).ExplX = EX;
        (*ap).ExplY = EY;
        testmortar_result = Score;
    }
    return testmortar_result;
};
LongInt uaiammotests_TestShotgun(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testshotgun_result;
    enum{MIN_RANGE = 80};
    enum{MAX_RANGE = 400};
    real Vx;
    real Vy;
    real x;
    real y;
    LongInt rx;
    LongInt ry;
    LongInt valueResult;
    Integer range;
    UNUSED (Flags);
    testshotgun_result = BadTurn;
    (*ap).ExplR = 0;
    (*ap).Time = 0;
    (*ap).Power = 1;
    x = ufloat_hwFloat2Float(Me->X);
    y = ufloat_hwFloat2Float(Me->Y);
    range = uaiammotests_Metric(fpcrtl_trunc(x), fpcrtl_trunc(y), Targ.Point.x, Targ.Point.y);
    if((range < MIN_RANGE) || (((range > MAX_RANGE) && !aiLaserSighting) && (Level >= 4)))
    {
        return BadTurn;
    }
    Vx = ((Targ.Point.x - x) * 1) /(float) 1024;
    Vy = ((Targ.Point.y - y) * 1) /(float) 1024;
    (*ap).Angle = uutils_DxDy2AttackAnglef(Vx, -Vy);
    if(!aiLaserSighting)
    {
        (*ap).Angle += uaimisc_AIrndSign(fpcrtl_random((Level - 1) * 10));
    }
    do {
           x = x + Vx;
           y = y + Vy;
           rx = fpcrtl_trunc(x);
           ry = fpcrtl_trunc(y);
           if(((Me == CurrentHedgehog->Gear) && uaimisc_TestColl(rx, ry, 2)) || ((Me != CurrentHedgehog->Gear) && uaimisc_TestCollExcludingMe((*Me->Hedgehog).Gear, rx, ry, 2)))
           {
               x = x + (Vx * 8);
               y = y + (Vy * 8);
               valueResult = uaimisc_RateShotgun(Me, Vx, Vy, rx, ry);
               if(((valueResult == 0) && (Targ.Kind == gtHedgehog)) && (Targ.Score > 0))
               {
                   if((GameFlags & gfSolidLand) == 0)
                   {
                       valueResult = 1024 - (uaiammotests_Metric(Targ.Point.x, Targ.Point.y, rx, ry) / 64);
                   }
                   else
                   {
                       valueResult = BadTurn;
                   }
               }
               else
               {
                   valueResult -= Level * 4000;
               }
               return (valueResult * 27) / 20;
           }
       } while(!((((((fpcrtl_abs(Targ.Point.x - fpcrtl_trunc(x)) + fpcrtl_abs(Targ.Point.y - fpcrtl_trunc(y))) < 4) || (x < 0)) || (y < 0)) || (fpcrtl_trunc(x) > LAND_WIDTH)) || (fpcrtl_trunc(y) > LAND_HEIGHT)));
    testshotgun_result = BadTurn;
    return testshotgun_result;
};
LongInt uaiammotests_TestDesertEagle(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testdeserteagle_result;
    real Vx;
    real Vy;
    real x;
    real y;
    real t;
    LongWord d;
    LongInt ix;
    LongInt iy;
    LongInt valueResult;
    UNUSED (Flags);
    if(((Level > 4) || (Targ.Score < 0)) || (Targ.Kind != gtHedgehog))
    {
        return BadTurn;
    }
    UNUSED (Level);
    (*ap).ExplR = 1;
    (*ap).Time = 0;
    (*ap).Power = 1;
    x = ufloat_hwFloat2Float(Me->X);
    y = ufloat_hwFloat2Float(Me->Y);
    if((fpcrtl_abs(fpcrtl_trunc(x) - Targ.Point.x) + fpcrtl_abs(fpcrtl_trunc(y) - Targ.Point.y)) < 20)
    {
        return BadTurn;
    }
    t = 2 /(float) sqrt(fpcrtl_sqr(Targ.Point.x - x) + fpcrtl_sqr(Targ.Point.y - y));
    Vx = (Targ.Point.x - x) * t;
    Vy = (Targ.Point.y - y) * t;
    (*ap).Angle = uutils_DxDy2AttackAnglef(Vx, -Vy);
    if(!aiLaserSighting)
    {
        (*ap).Angle += uaimisc_AIrndSign(fpcrtl_random((Level - 1) * 10));
    }
    d = 0;
    ix = fpcrtl_trunc(x);
    iy = fpcrtl_trunc(y);
    if(((ix & LAND_WIDTH_MASK) == 0) && ((iy & LAND_HEIGHT_MASK) == 0))
    {
        do {
               if(ulandutils_LandGet(iy, ix) != 0)
               {
                   ++d;
               }
               x = x + Vx;
               y = y + Vy;
               ix = fpcrtl_trunc(x);
               iy = fpcrtl_trunc(y);
           } while(!(((((((fpcrtl_abs(Targ.Point.x - ix) + fpcrtl_abs(Targ.Point.y - iy)) < 5) || (x < 0)) || (y < 0)) || (ix >= LAND_WIDTH)) || (iy >= LAND_HEIGHT)) || (d > 48)));
    }
    if((fpcrtl_abs(Targ.Point.x - ix) + fpcrtl_abs(Targ.Point.y - iy)) < 5)
    {
        (*ap).AttacksNum = 1 + ((d + 8) / 12);
        valueResult = uaimisc_RateShove(Me, Targ.Point.x, Targ.Point.y, 1, 7, 20, Vx * 0.125, Vy * 0.125, afTrackFall) - (*ap).AttacksNum;
    }
    else
    {
        valueResult = BadTurn;
    }
    testdeserteagle_result = valueResult;
    return testdeserteagle_result;
};
LongInt uaiammotests_TestSniperRifle(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testsniperrifle_result;
    real Vx;
    real Vy;
    real x;
    real y;
    real t;
    real dmg;
    LongWord d;
    UNUSED (Flags);
    if(((Level > 3) || (Targ.Score < 0)) || (Targ.Kind != gtHedgehog))
    {
        return BadTurn;
    }
    UNUSED (Level);
    (*ap).ExplR = 0;
    (*ap).Time = 0;
    (*ap).Power = 1;
    x = ufloat_hwFloat2Float(Me->X);
    y = ufloat_hwFloat2Float(Me->Y);
    if((fpcrtl_abs(fpcrtl_trunc(x) - Targ.Point.x) + fpcrtl_abs(fpcrtl_trunc(y) - Targ.Point.y)) < 40)
    {
        return BadTurn;
    }
    dmg = sqrt(fpcrtl_sqr(Targ.Point.x - x) + fpcrtl_sqr(Targ.Point.y - y));
    t = 1.5 /(float) dmg;
    dmg = dmg * 2.5e-2;
    Vx = (Targ.Point.x - x) * t;
    Vy = (Targ.Point.y - y) * t;
    (*ap).Angle = uutils_DxDy2AttackAnglef(Vx, -Vy);
    (*ap).Angle += uaimisc_AIrndSign(fpcrtl_random((Level - 1) * 5));
    d = 0;
    do {
           x = x + Vx;
           y = y + Vy;
           if((((fpcrtl_trunc(x) & LAND_WIDTH_MASK) == 0) && ((fpcrtl_trunc(y) & LAND_HEIGHT_MASK) == 0)) && (ulandutils_LandGet(fpcrtl_trunc(y), fpcrtl_trunc(x)) != 0))
           {
               ++d;
           }
       } while(!(((((((fpcrtl_abs(Targ.Point.x - fpcrtl_trunc(x)) + fpcrtl_abs(Targ.Point.y - fpcrtl_trunc(y))) < 4) || (x < 0)) || (y < 0)) || (fpcrtl_trunc(x) > LAND_WIDTH)) || (fpcrtl_trunc(y) > LAND_HEIGHT)) || (d > 22)));
    if((fpcrtl_abs(Targ.Point.x - fpcrtl_trunc(x)) + fpcrtl_abs(Targ.Point.y - fpcrtl_trunc(y))) < 4)
    {
        testsniperrifle_result = uaimisc_RateShove(Me, Targ.Point.x, Targ.Point.y, 1, fpcrtl_trunc(dmg), 20, Vx * 0.166, Vy * 0.166, afTrackFall);
    }
    else
    {
        testsniperrifle_result = BadTurn;
    }
    return testsniperrifle_result;
};
LongInt uaiammotests_TestBaseballBat(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testbaseballbat_result;
    LongInt valueResult;
    LongInt a;
    LongInt v1;
    LongInt v2;
    LongInt x;
    LongInt y;
    LongInt trackFall;
    real dx;
    real dy;
    UNUSED (Flags);
    UNUSED (Targ);
    if(Level < 3)
    {
        trackFall = afTrackFall;
    }
    else
    {
        trackFall = 0;
    }
    (*ap).ExplR = 0;
    (*ap).Time = 0;
    (*ap).Power = 1;
    x = ufloat_hwRound(Me->X);
    y = ufloat_hwRound(Me->Y);
    a = cMaxAngle / 2;
    valueResult = 0;
    while(a >= 0)
    {
        dx = sin((a /(float) cMaxAngle) * pi) * 0.5;
        dy = cos((a /(float) cMaxAngle) * pi) * 0.5;
        v1 = uaimisc_RateShove(Me, x - 10, y + 2, 32, 30, 115, -dx, -dy, trackFall);
        v2 = uaimisc_RateShove(Me, x + 10, y + 2, 32, 30, 115, dx, -dy, trackFall);
        if((v1 > valueResult) || (v2 > valueResult))
        {
            if((v2 > v1) || ((v2 == v1) && !Me->dX.isNegative))
            {
                (*ap).Angle = a;
                valueResult = v2;
            }
            else
            {
                (*ap).Angle = -a;
                valueResult = v1;
            }
        }
        a = (a - 15) - fpcrtl_random(cMaxAngle / 16);
    }
    if(valueResult <= 0)
    {
        valueResult = BadTurn;
    }
    testbaseballbat_result = valueResult;
    return testbaseballbat_result;
};
LongInt uaiammotests_TestFirePunch(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testfirepunch_result;
    LongInt valueResult;
    LongInt v1;
    LongInt v2;
    LongInt i;
    LongInt x;
    LongInt y;
    LongInt trackFall;
    UNUSED (Flags);
    UNUSED (Targ);
    if(Level == 1)
    {
        trackFall = afTrackFall;
    }
    else
    {
        trackFall = 0;
    }
    (*ap).ExplR = 0;
    (*ap).Time = 0;
    (*ap).Power = 1;
    x = ufloat_hwRound(Me->X);
    y = ufloat_hwRound(Me->Y) + 4;
    v1 = 0;
    {i = 0;
     LongInt i__end__ = 8;
     if (i <= i__end__) do {
                               v1 = v1 + uaimisc_RateShove(Me, x - 5, y - (10 * i), 19, 30, 40, -0.45, -0.9, trackFall | afSetSkip);
                           } while(i++ != i__end__);}
    v1 = v1 + uaimisc_RateShove(Me, x - 5, y - 90, 19, 30, 40, -0.45, -0.9, trackFall);
    v2 = 0;
    {i = 0;
     LongInt i__end__ = 8;
     if (i <= i__end__) do {
                               v2 = v2 + uaimisc_RateShove(Me, x + 5, y - (10 * i), 19, 30, 40, 0.45, -0.9, trackFall | afSetSkip);
                           } while(i++ != i__end__);}
    v2 = v2 + uaimisc_RateShove(Me, x + 5, y - 90, 19, 30, 40, 0.45, -0.9, trackFall);
    if((v2 > v1) || ((v2 == v1) && !Me->dX.isNegative))
    {
        (*ap).Angle = 1;
        valueResult = v2;
    }
    else
    {
        (*ap).Angle = -1;
        valueResult = v1;
    }
    if(valueResult <= 0)
    {
        valueResult = BadTurn;
    }
    testfirepunch_result = valueResult;
    return testfirepunch_result;
};
LongInt uaiammotests_TestWhip(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testwhip_result;
    LongInt valueResult;
    LongInt v1;
    LongInt v2;
    LongInt x;
    LongInt y;
    LongInt trackFall;
    UNUSED (Flags);
    UNUSED (Targ);
    if(Level == 1)
    {
        trackFall = afTrackFall;
    }
    else
    {
        trackFall = 0;
    }
    (*ap).ExplR = 0;
    (*ap).Time = 0;
    (*ap).Power = 1;
    x = ufloat_hwRound(Me->X);
    y = ufloat_hwRound(Me->Y);
    v1 = uaimisc_RateShove(Me, x - 13, y, 30, 30, 25, -1, -0.8, trackFall | afSetSkip);
    v1 = v1 + uaimisc_RateShove(Me, x - 2, y, 30, 30, 25, -1, -0.8, trackFall);
    v2 = uaimisc_RateShove(Me, x + 13, y, 30, 30, 25, 1, -0.8, trackFall | afSetSkip);
    v2 = v2 + uaimisc_RateShove(Me, x + 2, y, 30, 30, 25, 1, -0.8, trackFall);
    if((v2 > v1) || ((v2 == v1) && !Me->dX.isNegative))
    {
        (*ap).Angle = 1;
        valueResult = v2;
    }
    else
    {
        (*ap).Angle = -1;
        valueResult = v1;
    }
    if(valueResult <= 0)
    {
        valueResult = BadTurn;
    }
    else
    {
        ++valueResult;
    }
    testwhip_result = valueResult;
    return testwhip_result;
};
LongInt uaiammotests_TestKamikaze(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testkamikaze_result;
    enum{step = 8};
    LongInt valueResult;
    LongInt i;
    LongInt v;
    LongInt tx;
    LongInt trackFall;
    real t;
    real d;
    real x;
    real y;
    real dx;
    real dy;
    real cx;
    UNUSED (Flags);
    (*ap).ExplR = 0;
    (*ap).Time = 0;
    (*ap).Power = 1;
    if(Level == 1)
    {
        trackFall = afTrackFall;
    }
    else
    {
        if(Level == 2)
        {
            trackFall = 0;
        }
        else
        {
            return BadTurn;
        }
    }
    if(aiHogsInTeam <= 1)
    {
        return BadTurn;
    }
    valueResult = 0;
    v = 0;
    x = ufloat_hwFloat2Float(Me->X);
    y = ufloat_hwFloat2Float(Me->Y);
    d = sqrt(fpcrtl_sqr(Targ.Point.x - x) + fpcrtl_sqr(Targ.Point.y - y));
    if(d < 10)
    {
        dx = 0;
        dy = step;
        (*ap).Angle = 2048;
    }
    else
    {
        t = step /(float) d;
        dx = (Targ.Point.x - x) * t;
        dy = (Targ.Point.y - y) * t;
        (*ap).Angle = uutils_DxDy2AttackAnglef(dx, -dy);
        if(!aiLaserSighting)
        {
            (*ap).Angle += uaimisc_AIrndSign(fpcrtl_random((Level - 1) * 10));
        }
    }
    if(dx >= 0)
    {
        cx = 0.45;
    }
    else
    {
        cx = -0.45;
    }
    {i = 1;
     LongInt i__end__ = (512 / step) - 2;
     if (i <= i__end__) do {
                               x = x + dx;
                               y = y + dy;
                               valueResult = valueResult + uaimisc_RateShove(Me, fpcrtl_trunc(x), fpcrtl_trunc(y), 30, 30, 25, cx, -0.9, (trackFall | afSetSkip) | afIgnoreMe);
                           } while(i++ != i__end__);}
    if((d < 10) && (dx == 0))
    {
        x = ufloat_hwFloat2Float(Me->X);
        y = ufloat_hwFloat2Float(Me->Y);
        tx = fpcrtl_trunc(x);
        v = uaimisc_RateShove(Me, tx, fpcrtl_trunc(y), 30, 30, 25, -cx, -0.9, trackFall | afIgnoreMe);
        {i = 1;
         LongInt i__end__ = (512 / step) - 2;
         if (i <= i__end__) do {
                                   y = y + dy;
                                   v = v + uaimisc_RateShove(Me, tx, fpcrtl_trunc(y), 30, 30, 25, -cx, -0.9, (trackFall | afSetSkip) | afIgnoreMe);
                               } while(i++ != i__end__);}
    }
    if(v > valueResult)
    {
        cx = -cx;
        (*ap).Angle = -2048;
        valueResult = v;
    }
    v = uaimisc_RateShove(Me, fpcrtl_trunc(x), fpcrtl_trunc(y), 30, 30, 25, cx, -0.9, trackFall | afIgnoreMe);
    valueResult = (valueResult + v) - (((KillScore * friendlyfactor) / 100) * 1024);
    if(v < 65536)
    {
        valueResult += uaimisc_RateExplosion_5(Me, fpcrtl_trunc(x), fpcrtl_trunc(y), 30, afIgnoreMe);
    }
    testkamikaze_result = valueResult;
    return testkamikaze_result;
};
LongInt uaiammotests_TestHammer(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testhammer_result;
    LongInt rate;
    UNUSED (Flags);
    UNUSED (Level);
    UNUSED (Targ);
    (*ap).ExplR = 0;
    (*ap).Time = 0;
    (*ap).Power = 1;
    (*ap).Angle = 0;
    rate = uaimisc_RateHammer(Me);
    if(rate == 0)
    {
        rate = BadTurn;
    }
    testhammer_result = rate;
    return testhammer_result;
};
LongInt uaiammotests_TestAirAttack(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testairattack_result;
    enum{cShift = 4};
    real Density = 2.0;
    real bombsSpeed;
    real X;
    real Y;
    real dX;
    real dY;
    typedef boolean b_tt[(9 + 1)];
    b_tt b;
    typedef LongInt dmg_tt[(9 + 1)];
    dmg_tt dmg;
    boolean fexit;
    boolean firstHit;
    LongInt i;
    LongInt t;
    LongInt valueResult;
    LongInt targetY;
    UNUSED (Flags);
    (*ap).ExplR = 0;
    (*ap).Time = 0;
    if((Level > 3) || (aiGravityf <= 0))
    {
        return BadTurn;
    }
    (*ap).Angle = 0;
    (*ap).AttackPutX = Targ.Point.x;
    (*ap).AttackPutY = Targ.Point.y;
    bombsSpeed = ufloat_hwFloat2Float(cBombsSpeed);
    X = (Targ.Point.x - 135) - cShift;
    X = X - (bombsSpeed * sqrt(((Targ.Point.y + 128) * 2) /(float) aiGravityf));
    Y = topY - 300;
    dX = bombsSpeed;
    dY = 0;
    {i = 0;
     LongInt i__end__ = 9;
     if (i <= i__end__) do {
                               b[i] = true;
                               dmg[i] = 0;
                           } while(i++ != i__end__);}
    valueResult = 0;
    firstHit = false;
    do {
           X = X + dX;
           if((GameFlags & gfMoreWind) != 0)
           {
               dX = dX + (aiWindSpeed /(float) Density);
           }
           Y = Y + dY;
           dY = dY + aiGravityf;
           fexit = true;
           {i = 0;
            LongInt i__end__ = 9;
            if (i <= i__end__) do {
                                      if(b[i])
                                      {
                                          fexit = false;
                                          if(uaimisc_TestColl(fpcrtl_trunc(X) + ((LongWord)i * 30), fpcrtl_trunc(Y), 4))
                                          {
                                              b[i] = false;
                                              if(Level == 1)
                                              {
                                                  dmg[i] = uaimisc_RateExplosion_5(Me, fpcrtl_trunc(X) + ((LongWord)i * 30), fpcrtl_trunc(Y), 58, afTrackFall | afErasesLand);
                                              }
                                              else
                                              {
                                                  dmg[i] = uaimisc_RateExplosion_4(Me, fpcrtl_trunc(X) + ((LongWord)i * 30), fpcrtl_trunc(Y), 58);
                                              }
                                              if(!firstHit)
                                              {
                                                  firstHit = true;
                                                  targetY = fpcrtl_trunc(Y);
                                              }
                                          }
                                      }
                                  } while(i++ != i__end__);}
       } while(!(fexit || (Y > cWaterLine)));
    {i = 0;
     LongInt i__end__ = 5;
     if (i <= i__end__) do {
                               if(dmg[i] != BadTurn)
                               {
                                   valueResult += dmg[i];
                               }
                           } while(i++ != i__end__);}
    t = valueResult;
    (*ap).AttackPutX = Targ.Point.x - 60;
    if(firstHit)
    {
        (*ap).AttackPutY = targetY;
    }
    {i = 0;
     LongInt i__end__ = 3;
     if (i <= i__end__) do {
                               if(dmg[i] != BadTurn)
                               {
                                   t -= dmg[i];
                                   t += dmg[i + 6];
                                   if(t > valueResult)
                                   {
                                       valueResult = t;
                                       (*ap).AttackPutX = ((Targ.Point.x - 30) - cShift) + (i * 30);
                                   }
                               }
                           } while(i++ != i__end__);}
    if(valueResult <= 0)
    {
        valueResult = BadTurn;
    }
    testairattack_result = valueResult;
    return testairattack_result;
};
LongInt uaiammotests_TestResurrector(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testresurrector_result;
    LongInt rate;
    LongInt heal;
    UNUSED (Flags);
    UNUSED (Targ);
    if(Level == 5)
    {
        return BadTurn;
    }
    if(Me->Health <= 1)
    {
        return BadTurn;
    }
    if((Level <= 2) && ((*Me->Hedgehog).Effects[hePoisoned] > 0))
    {
        heal = Me->Health - 1;
    }
    else
    {
        heal = Me->Health / 10;
    }
    (*ap).ExplR = 0;
    (*ap).Time = 0;
    if(Level >= 4)
    {
        (*ap).Power = uutils_Max((512 * heal) - 512, 10);
    }
    else
    {
        (*ap).Power = uutils_Max((16 * heal) - 16, 10);
    }
    (*ap).Power = uutils_Min((*ap).Power, 5000);
    (*ap).Angle = 0;
    rate = uaimisc_RateResurrector(Me);
    if(rate <= 0)
    {
        rate = BadTurn;
    }
    testresurrector_result = rate;
    return testresurrector_result;
};
LongInt uaiammotests_TestDrillStrike(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testdrillstrike_result;
    enum{cShift = 4};
    real Density = 1.0;
    real bombsSpeed;
    real X;
    real Y;
    real dX;
    real dY;
    real drillX;
    real drillY;
    real t2;
    typedef LongInt dmg_tt[(9 + 1)];
    dmg_tt dmg;
    boolean collided;
    boolean drilling;
    boolean timerRuns;
    boolean firstHit;
    LongInt i;
    LongInt t;
    LongInt value;
    LongInt valueResult;
    LongInt attackTime;
    LongInt drillTimer;
    LongInt targetX;
    LongInt targetY;
    UNUSED (Flags);
    (*ap).ExplR = 0;
    if((Level > 3) || (aiGravityf <= 0))
    {
        return BadTurn;
    }
    (*ap).Angle = 0;
    targetX = Targ.Point.x;
    (*ap).AttackPutY = Targ.Point.y;
    bombsSpeed = ufloat_hwFloat2Float(cBombsSpeed);
    X = (Targ.Point.x - 135) - cShift;
    X = X - (bombsSpeed * sqrt(((Targ.Point.y + 128) * 2) /(float) aiGravityf));
    Y = topY - 300;
    valueResult = 0;
    attackTime = 6000;
    while(attackTime >= 0)
    {
        attackTime -= 1000;
        value = 0;
        firstHit = false;
        {i = 0;
         LongInt i__end__ = 9;
         if (i <= i__end__) do {
                                   dmg[i] = 0;
                                   drillX = fpcrtl_trunc(X) + ((LongWord)i * 30);
                                   drillY = fpcrtl_trunc(Y);
                                   dX = bombsSpeed;
                                   dY = 0;
                                   collided = false;
                                   drilling = false;
                                   timerRuns = false;
                                   drillTimer = attackTime;
                                   do {
                                          drillX = drillX + dX;
                                          drillY = drillY + dY;
                                          if((GameFlags & gfMoreWind) != 0)
                                          {
                                              dX = dX + (aiWindSpeed /(float) Density);
                                          }
                                          dY = dY + aiGravityf;
                                          if(timerRuns)
                                          {
                                              --drillTimer;
                                          }
                                          if(((drillTimer > 0) && uaimisc_TestCollExcludingObjects(fpcrtl_trunc(drillX), fpcrtl_trunc(drillY), 4)) && ((fpcrtl_abs(Targ.Point.x - fpcrtl_trunc(drillX)) + fpcrtl_abs(Targ.Point.y - fpcrtl_trunc(drillY))) > 21))
                                          {
                                              drilling = true;
                                              timerRuns = true;
                                              t2 = 0.5 /(float) sqrt(fpcrtl_sqr(dX) + fpcrtl_sqr(dY));
                                              dX = dX * t2;
                                              dY = dY * t2;
                                              do {
                                                     drillX = drillX + dX;
                                                     drillY = drillY + dY;
                                                     drillTimer -= 10;
                                                     if(((((((fpcrtl_abs(Targ.Point.x - drillX) + fpcrtl_abs(Targ.Point.y - drillY)) < 22) || (drillX < -32)) || (drillY < -32)) || (fpcrtl_trunc(drillX) > (LAND_WIDTH + 32))) || (fpcrtl_trunc(drillY) > cWaterLine)) || (drillTimer <= 0))
                                                     {
                                                         collided = true;
                                                     }
                                                     else
                                                     {
                                                         if(!uaimisc_TestCollExcludingObjects(fpcrtl_trunc(drillX), fpcrtl_trunc(drillY), 4))
                                                         {
                                                             drilling = false;
                                                         }
                                                     }
                                                 } while(!(collided || !drilling));
                                          }
                                          else
                                          {
                                              if((drillTimer <= 0) || uaimisc_TestColl(fpcrtl_trunc(drillX), fpcrtl_trunc(drillY), 4))
                                              {
                                                  collided = true;
                                              }
                                          }
                                          if(collided)
                                          {
                                              if(Level == 1)
                                              {
                                                  dmg[i] = uaimisc_RateExplosion_5(Me, fpcrtl_trunc(drillX), fpcrtl_trunc(drillY), 58, afTrackFall | afErasesLand);
                                              }
                                              else
                                              {
                                                  dmg[i] = uaimisc_RateExplosion_4(Me, fpcrtl_trunc(drillX), fpcrtl_trunc(drillY), 58);
                                              }
                                              if(!firstHit)
                                              {
                                                  targetY = fpcrtl_trunc(drillY);
                                                  firstHit = true;
                                              }
                                          }
                                      } while(!(collided || (drillY > cWaterLine)));
                               } while(i++ != i__end__);}
        {i = 0;
         LongInt i__end__ = 5;
         if (i <= i__end__) do {
                                   if(dmg[i] != BadTurn)
                                   {
                                       value += dmg[i];
                                   }
                               } while(i++ != i__end__);}
        t = value;
        targetX = (Targ.Point.x - 60) - cShift;
        {i = 0;
         LongInt i__end__ = 3;
         if (i <= i__end__) do {
                                   if(dmg[i] != BadTurn)
                                   {
                                       t -= dmg[i];
                                       t += dmg[i + 6];
                                       if(t >= value)
                                       {
                                           value = t;
                                           targetX = ((Targ.Point.x - 30) - cShift) + (i * 30);
                                       }
                                   }
                               } while(i++ != i__end__);}
        if(value > valueResult)
        {
            valueResult = value;
            (*ap).AttackPutX = targetX;
            if(firstHit)
            {
                (*ap).AttackPutY = targetY;
            }
            (*ap).Time = attackTime;
        }
    }
    if(valueResult <= 0)
    {
        valueResult = BadTurn;
    }
    else
    {
        if(Level == 5)
        {
            (*ap).Time = (*ap).Time + ((3 - fpcrtl_random(7)) * 1000);
        }
        else
        {
            if(Level == 4)
            {
                (*ap).Time = (*ap).Time + ((2 - fpcrtl_random(5)) * 1000);
            }
            else
            {
                if(Level == 3)
                {
                    if(fpcrtl_random(2) == 0)
                    {
                        (*ap).Time = (*ap).Time + ((1 - fpcrtl_random(3)) * 1000);
                    }
                    else
                    {
                        if(Level == 2)
                        {
                            if(fpcrtl_random(2) == 0)
                            {
                                (*ap).Time = (*ap).Time + ((1 - fpcrtl_random(3)) * 1000);
                            }
                        }
                    }
                }
            }
        }
        (*ap).Time = uutils_Min(5000, uutils_Max(1000, (*ap).Time));
    }
    testdrillstrike_result = valueResult;
    return testdrillstrike_result;
};
LongInt uaiammotests_TestMineStrike(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testminestrike_result;
    enum{cShift = 4};
    real Density = 1.0;
    real minesSpeed;
    real X;
    real Y;
    real dX;
    real dY;
    typedef boolean b_tt[(9 + 1)];
    b_tt b;
    typedef LongInt dmg_tt[(9 + 1)];
    dmg_tt dmg;
    boolean fexit;
    boolean firstHit;
    LongInt i;
    LongInt t;
    LongInt valueResult;
    LongInt targetY;
    UNUSED (Flags);
    (*ap).ExplR = 0;
    (*ap).Time = 0;
    if(((Level > 3) || (aiGravityf <= 0)) || (cMinesTime != 0))
    {
        return BadTurn;
    }
    (*ap).Angle = 0;
    (*ap).AttackPutX = Targ.Point.x;
    (*ap).AttackPutY = Targ.Point.y;
    minesSpeed = ufloat_hwFloat2Float(cBombsSpeed);
    X = (Targ.Point.x - 135) - cShift;
    X = X - (minesSpeed * sqrt(((Targ.Point.y + 128) * 2) /(float) aiGravityf));
    Y = topY - 300;
    dX = minesSpeed;
    dY = 0;
    {i = 0;
     LongInt i__end__ = 9;
     if (i <= i__end__) do {
                               b[i] = true;
                               dmg[i] = 0;
                           } while(i++ != i__end__);}
    valueResult = 0;
    firstHit = false;
    do {
           X = X + dX;
           if((GameFlags & (gfMoreWind | gfInfAttack)) != 0)
           {
               dX = dX + (aiWindSpeed /(float) Density);
           }
           Y = Y + dY;
           dY = dY + aiGravityf;
           fexit = true;
           {i = 0;
            LongInt i__end__ = 9;
            if (i <= i__end__) do {
                                      if(b[i])
                                      {
                                          fexit = false;
                                          if(uaimisc_TestColl(fpcrtl_trunc(X) + ((LongWord)i * 30), fpcrtl_trunc(Y), 4))
                                          {
                                              b[i] = false;
                                              if(Level == 1)
                                              {
                                                  dmg[i] = uaimisc_RateExplosion_5(Me, fpcrtl_trunc(X) + ((LongWord)i * 30), fpcrtl_trunc(Y), 96, afTrackFall | afErasesLand);
                                              }
                                              else
                                              {
                                                  dmg[i] = uaimisc_RateExplosion_4(Me, fpcrtl_trunc(X) + ((LongWord)i * 30), fpcrtl_trunc(Y), 96);
                                              }
                                              if(!firstHit)
                                              {
                                                  targetY = fpcrtl_trunc(Y);
                                                  firstHit = true;
                                              }
                                          }
                                      }
                                  } while(i++ != i__end__);}
       } while(!(fexit || (Y > cWaterLine)));
    {i = 0;
     LongInt i__end__ = 5;
     if (i <= i__end__) do {
                               if(dmg[i] != BadTurn)
                               {
                                   valueResult += dmg[i];
                               }
                           } while(i++ != i__end__);}
    t = valueResult;
    (*ap).AttackPutX = Targ.Point.x - 60;
    if(firstHit)
    {
        (*ap).AttackPutY = targetY;
    }
    {i = 0;
     LongInt i__end__ = 3;
     if (i <= i__end__) do {
                               if(dmg[i] != BadTurn)
                               {
                                   t -= dmg[i];
                                   t += dmg[i + 6];
                                   if(t > valueResult)
                                   {
                                       valueResult = t;
                                       (*ap).AttackPutX = ((Targ.Point.x - 30) - cShift) + (i * 30);
                                   }
                               }
                           } while(i++ != i__end__);}
    if(valueResult <= 0)
    {
        valueResult = BadTurn;
    }
    testminestrike_result = valueResult;
    return testminestrike_result;
};
LongInt uaiammotests_TestSineGun(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testsinegun_result;
    enum{MIN_RANGE = 40};
    enum{MAX_RANGE = 400};
    real Vx;
    real Vy;
    real x;
    real y;
    LongInt rx;
    LongInt ry;
    LongInt value;
    LongInt valueResult;
    Integer range;
    boolean landStop;
    UNUSED (Flags);
    testsinegun_result = BadTurn;
    valueResult = 0;
    (*ap).ExplR = 0;
    (*ap).Time = 0;
    (*ap).Power = 1;
    x = ufloat_hwFloat2Float(Me->X);
    y = ufloat_hwFloat2Float(Me->Y);
    range = uaiammotests_Metric(fpcrtl_trunc(x), fpcrtl_trunc(y), Targ.Point.x, Targ.Point.y);
    if((range < MIN_RANGE) || ((range > MAX_RANGE) && (Level >= 4)))
    {
        return BadTurn;
    }
    Vx = ((Targ.Point.x - x) * 1) /(float) 1024;
    Vy = ((Targ.Point.y - y) * 1) /(float) 1024;
    if(Vy >= 0)
    {
        return BadTurn;
    }
    landStop = false;
    (*ap).Angle = uutils_DxDy2AttackAnglef(Vx, -Vy);
    if(!aiLaserSighting)
    {
        (*ap).Angle += uaimisc_AIrndSign(fpcrtl_random((Level - 1) * 10));
    }
    do {
           x = x + Vx;
           y = y + Vy;
           rx = fpcrtl_trunc(x);
           ry = fpcrtl_trunc(y);
           if((GameFlags & gfSolidLand) != 0)
           {
               landStop = (Me == CurrentHedgehog->Gear) && uaimisc_TestColl(rx, ry, 5);
           }
           if((landStop || ((Me == CurrentHedgehog->Gear) && uaimisc_TestCollHogsOrObjects(rx, ry, 5))) || ((Me != CurrentHedgehog->Gear) && uaimisc_TestCollExcludingMe((*Me->Hedgehog).Gear, rx, ry, 5)))
           {
               x = x + (Vx * 8);
               y = y + (Vy * 8);
               value = uaimisc_RateShove(Me, rx, ry, 5, 35, 50, Vx, Vy, afTrackFall);
               if(value > 0)
               {
                   valueResult += value;
               }
           }
       } while(!((((((((fpcrtl_abs(Targ.Point.x - fpcrtl_trunc(x)) + fpcrtl_abs(Targ.Point.y - fpcrtl_trunc(y))) < 5) || landStop) || (uaiammotests_Metric(fpcrtl_trunc(x), fpcrtl_trunc(y), ufloat_hwRound(Me->X), ufloat_hwRound(Me->Y)) > MAX_RANGE)) || (x < 0)) || (y < 0)) || (fpcrtl_trunc(x) > LAND_WIDTH)) || (fpcrtl_trunc(y) > LAND_HEIGHT)));
    if(valueResult <= 0)
    {
        valueResult = BadTurn;
    }
    testsinegun_result = valueResult;
    return testsinegun_result;
};
LongInt uaiammotests_TestSMine(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testsmine_result;
    enum{timeLimit = 50};
    real Density = 1.6;
    real Vx;
    real Vy;
    real r;
    real meX;
    real meY;
    LongInt rTime;
    LongInt EX;
    LongInt EY;
    LongInt valueResult;
    real targXWrap;
    real x;
    real y;
    real dX;
    real dY;
    LongInt t;
    LongInt value;
    UNUSED (Flags);
    meX = ufloat_hwFloat2Float(Me->X);
    meY = ufloat_hwFloat2Float(Me->Y);
    (*ap).Time = 0;
    rTime = 350;
    (*ap).ExplR = 0;
    if(WorldEdge == weWrap)
    {
        if(Targ.Point.x < meX)
        {
            targXWrap = Targ.Point.x + (rightX - leftX);
        }
        else
        {
            targXWrap = Targ.Point.x - (rightX - leftX);
        }
    }
    valueResult = BadTurn;
    do {
           rTime = ((rTime + 300) + (Level * 50)) + fpcrtl_random(300);
           if((WorldEdge == weWrap) && (fpcrtl_random(2) == 0))
           {
               Vx = (((targXWrap + uaimisc_AIrndSign(2)) + uaimisc_AIrndOffset(Targ, Level)) - meX) /(float) rTime;
           }
           else
           {
               Vx = (((Targ.Point.x + uaimisc_AIrndSign(2)) + uaimisc_AIrndOffset(Targ, Level)) - meX) /(float) rTime;
           }
           if((GameFlags & gfMoreWind) != 0)
           {
               Vx = ((-(aiWindSpeed /(float) Density) * rTime) * 0.5) + Vx;
           }
           Vy = ((aiGravityf * rTime) * 0.5) - (((Targ.Point.y + 1) - meY) /(float) rTime);
           r = fpcrtl_sqr(Vx) + fpcrtl_sqr(Vy);
           if(!(r > 1))
           {
               x = meX;
               y = meY;
               dX = Vx;
               dY = -Vy;
               t = rTime;
               do {
                      x = uaimisc_CheckWrap(x);
                      x = x + dX;
                      if((GameFlags & gfMoreWind) != 0)
                      {
                          dX = dX + (aiWindSpeed /(float) Density);
                      }
                      y = y + dY;
                      dY = dY + aiGravityf;
                      --t;
                  } while(!((((Me == CurrentHedgehog->Gear) && uaimisc_TestColl(fpcrtl_trunc(x), fpcrtl_trunc(y), 2)) || ((Me != CurrentHedgehog->Gear) && uaimisc_TestCollExcludingMe((*Me->Hedgehog).Gear, fpcrtl_trunc(x), fpcrtl_trunc(y), 2))) || (t < -timeLimit)));
               EX = fpcrtl_trunc(x);
               EY = fpcrtl_trunc(y);
               if(t >= -timeLimit)
               {
                   if((Level == 1) && ((Flags & amtest_NoTrackFall) == 0))
                   {
                       value = uaimisc_RateExplosion_5(Me, EX, EY, 61, afTrackFall);
                   }
                   else
                   {
                       value = uaimisc_RateExplosion_4(Me, EX, EY, 61);
                   }
               }
               else
               {
                   value = BadTurn;
               }
               if(((value == 0) && (Targ.Kind == gtHedgehog)) && (Targ.Score > 0))
               {
                   value = BadTurn;
               }
               if((valueResult < value) || ((valueResult == value) && (Level < 3)))
               {
                   (*ap).Angle = uutils_DxDy2AttackAnglef(Vx, Vy) + uaimisc_AIrndSign(fpcrtl_random((Level - 1) * 9));
                   (*ap).Power = fpcrtl_trunc(sqrt(r) * cMaxPower) - fpcrtl_random(((Level - 1) * 17) + 1);
                   (*ap).ExplR = 60;
                   (*ap).ExplX = EX;
                   (*ap).ExplY = EY;
                   valueResult = value;
               }
           }
       } while(!(rTime > (5050 - (Level * 800))));
    if(valueResult != BadTurn)
    {
        valueResult = (valueResult * 27) / 20;
    }
    testsmine_result = valueResult;
    return testsmine_result;
};
LongInt uaiammotests_TestPiano(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testpiano_result;
    enum{BOUNCES = 1};
    real X;
    real Y;
    typedef LongInt dmg_tt[((BOUNCES - 1) + 1)];
    dmg_tt dmg;
    LongInt i;
    LongInt e;
    LongInt rate;
    LongInt valueResult;
    LongInt targetY;
    boolean firstHit;
    boolean solidBounce;
    UNUSED (Flags);
    (*ap).ExplR = 0;
    (*ap).Time = 0;
    if(aiGravityf <= 0)
    {
        return BadTurn;
    }
    if(Level > 2)
    {
        return BadTurn;
    }
    if(aiHogsInTeam <= 1)
    {
        return BadTurn;
    }
    (*ap).Angle = 0;
    (*ap).AttackPutX = Targ.Point.x;
    (*ap).AttackPutY = Targ.Point.y;
    X = Targ.Point.x;
    Y = -1024;
    {i = 0;
     LongInt i__end__ = BOUNCES - 1;
     if (i <= i__end__) do {
                               dmg[i] = 0;
                           } while(i++ != i__end__);}
    i = 1;
    firstHit = false;
    solidBounce = false;
    do {
           if(!solidBounce)
           {
               Y = Y + 11;
           }
           if(solidBounce || uaimisc_TestCollExcludingMe((*Me->Hedgehog).Gear, fpcrtl_trunc(X), fpcrtl_trunc(Y), 32))
           {
               if(!firstHit)
               {
                   targetY = fpcrtl_trunc(Y);
               }
               firstHit = true;
               if((GameFlags & gfSolidLand) != 0)
               {
                   solidBounce = true;
               }
               {e = -1;
                LongInt e__end__ = 1;
                if (e <= e__end__) do {
                                          rate = uaimisc_RateExplosion_5(Me, fpcrtl_trunc(X) + (30 * e), fpcrtl_trunc(Y) + 40, 161, afIgnoreMe);
                                          if(rate != BadTurn)
                                          {
                                              dmg[i] = dmg[i] + rate;
                                          }
                                      } while(e++ != e__end__);}
               if((i > 1) && (dmg[i] > 0))
               {
                   dmg[i] = dmg[i] / 2;
               }
               ++i;
               if(!solidBounce)
               {
                   Y = Y + 41;
               }
           }
       } while(!((i > BOUNCES) || (Y > cWaterLine)));
    if((i == 0) && (Y > cWaterLine))
    {
        return BadTurn;
    }
    valueResult = 0;
    {i = 0;
     LongInt i__end__ = BOUNCES;
     if (i <= i__end__) do {
                               if(dmg[i] <= BadTurn)
                               {
                                   valueResult = BadTurn;
                                   break;
                               }
                               else
                               {
                                   valueResult += dmg[i];
                               }
                           } while(i++ != i__end__);}
    (*ap).AttackPutX = Targ.Point.x;
    if(firstHit)
    {
        (*ap).AttackPutY = targetY;
    }
    valueResult = valueResult - (((KillScore * friendlyfactor) / 100) * 1024);
    if(valueResult <= 0)
    {
        valueResult = BadTurn;
    }
    testpiano_result = valueResult;
    return testpiano_result;
};
LongInt uaiammotests_TestTeleport(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testteleport_result;
    LongWord i;
    LongWord failNum;
    LongWord maxTop;
    UNUSED (Flags);
    testteleport_result = BadTurn;
    return BadTurn;
    UNUSED (Level);
    if(bonuses.Count == 0)
    {
        if(Me->Health <= 100)
        {
            maxTop = Targ.Point.y - (cHHRadius * 2);
            while(!uaimisc_TestColl(Targ.Point.x, maxTop, cHHRadius) && (maxTop > ((topY + (cHHRadius * 2)) + 1)))
            {
                maxTop -= cHHRadius * 2;
            }
            if(!uaimisc_TestColl(Targ.Point.x, maxTop + cHHRadius, cHHRadius))
            {
                (*ap).AttackPutX = Targ.Point.x;
                (*ap).AttackPutY = maxTop + cHHRadius;
                testteleport_result = Targ.Point.y - maxTop;
            }
        }
    }
    else
    {
        failNum = 0;
        do {
               i = fpcrtl_random(bonuses.Count);
               ++failNum;
           } while(!(!uaimisc_TestColl(bonuses.ar[i].X, (bonuses.ar[i].Y - cHHRadius) - bonuses.ar[i].Radius, cHHRadius) || (failNum == (bonuses.Count * 2))));
        if(failNum < (bonuses.Count * 2))
        {
            (*ap).AttackPutX = bonuses.ar[i].X;
            (*ap).AttackPutY = (bonuses.ar[i].Y - cHHRadius) - bonuses.ar[i].Radius;
            testteleport_result = 0;
        }
    }
    return testteleport_result;
};
void uaiammotests_checkCakeWalk(PGear Me,PGear Gear,TAttackParams (*ap))
{
    LongWord i;
    LongInt v;
    while(!uaimisc_TestColl(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), 6) && (Gear->Y.Round < ((LongWord)LAND_HEIGHT)))
    {
        Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _1);
    }
    {i = 0;
     LongWord i__end__ = 2040;
     if (i <= i__end__) do {
                               ugearshandlers_cakeStep(Gear);
                               v = uaimisc_RateExplosion_5(Me, ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), cakeDmg * 2, afTrackFall);
                               if(v > (*ap).Power)
                               {
                                   (*ap).ExplX = ufloat_hwRound(Gear->X);
                                   (*ap).ExplY = ufloat_hwRound(Gear->Y);
                                   (*ap).Power = v;
                               }
                           } while(i++ != i__end__);}
};
LongInt uaiammotests_TestCake(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testcake_result;
    LongInt valueResult;
    LongInt v1;
    LongInt v2;
    TGear cake;
    UNUSED (Flags);
    UNUSED (Targ);
    if(Level > 2)
    {
        return BadTurn;
    }
    (*ap).ExplR = 0;
    (*ap).Time = 0;
    (*ap).Power = BadTurn;
    cake.Radius = 7;
    cake.CollisionMask = lfNotCurHogCrate;
    cake.Hedgehog = Me->Hedgehog;
    cake.Kind = gtCake;
    cake.Angle = 3;
    cake.dX.isNegative = true;
    cake.dX.QWordValue = 0;
    cake.dY = _0;
    cake.X = ufloat_hwFloat_hwFloat_op_sub(Me->X, _3);
    cake.Y = Me->Y;
    uaiammotests_checkCakeWalk(Me, &(cake), &((*ap)));
    v1 = (*ap).Power;
    cake.Angle = 1;
    cake.dX.isNegative = false;
    cake.X = ufloat_hwFloat_hwFloat_op_add(Me->X, _3);
    cake.Y = Me->Y;
    uaiammotests_checkCakeWalk(Me, &(cake), &((*ap)));
    v2 = (*ap).Power;
    (*ap).Power = 1;
    if(v2 > v1)
    {
        (*ap).Angle = 1;
        valueResult = v2;
    }
    else
    {
        (*ap).Angle = -1;
        valueResult = v1;
    }
    if(valueResult <= 0)
    {
        valueResult = BadTurn;
    }
    testcake_result = valueResult;
    return testcake_result;
};
LongInt uaiammotests_TestSeduction(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testseduction_result;
    LongInt rate;
    UNUSED (Flags);
    UNUSED (Level);
    UNUSED (Targ);
    if(Level == 5)
    {
        return BadTurn;
    }
    (*ap).ExplR = 0;
    (*ap).Time = 0;
    (*ap).Power = 1;
    (*ap).Angle = 0;
    rate = uaimisc_RateSeduction(Me);
    if(rate <= 0)
    {
        rate = BadTurn;
    }
    testseduction_result = rate;
    return testseduction_result;
};
LongInt uaiammotests_TestDynamite(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testdynamite_result;
    real Density = 2.0;
    LongInt valueResult;
    real x;
    real y;
    real dx;
    real dy;
    LongInt EX;
    LongInt EY;
    LongInt t;
    UNUSED (Flags);
    UNUSED (Targ);
    x = ufloat_hwFloat2Float(Me->X) + (ufloat_hwSign(Me->dX) * 7);
    y = ufloat_hwFloat2Float(Me->Y);
    dx = ufloat_hwSign(Me->dX) * 3.0e-2;
    if((GameFlags & gfMoreWind) != 0)
    {
        dx = -(aiWindSpeed /(float) Density) + dx;
    }
    dy = 0;
    t = 5000;
    do {
           --t;
           if((GameFlags & gfMoreWind) != 0)
           {
               dx = dx + (aiWindSpeed /(float) Density);
           }
           x = x + dx;
           dy = dy + aiGravityf;
           y = y + dy;
           if(uaimisc_TestColl(fpcrtl_trunc(x), fpcrtl_trunc(y), 3))
           {
               t = 0;
           }
       } while(!(t == 0));
    EX = fpcrtl_trunc(x);
    EY = fpcrtl_trunc(y);
    if(Level == 1)
    {
        valueResult = uaimisc_RateExplosion_5(Me, EX, EY, 76, afTrackFall | afErasesLand);
    }
    else
    {
        valueResult = uaimisc_RateExplosion_4(Me, EX, EY, 76);
    }
    if(valueResult > 0)
    {
        (*ap).Angle = 0;
        (*ap).Power = 1;
        (*ap).Time = 0;
        (*ap).ExplR = 150;
        (*ap).ExplX = EX;
        (*ap).ExplY = EY;
    }
    else
    {
        valueResult = BadTurn;
    }
    testdynamite_result = valueResult;
    return testdynamite_result;
};
LongInt uaiammotests_TestMine(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testmine_result;
    real Density = 1.0;
    LongInt valueResult;
    real x;
    real y;
    real dx;
    real dy;
    LongInt EX;
    LongInt EY;
    LongInt t;
    UNUSED (Flags);
    UNUSED (Targ);
    x = ufloat_hwFloat2Float(Me->X) + (ufloat_hwSign(Me->dX) * 7);
    y = ufloat_hwFloat2Float(Me->Y);
    dx = ufloat_hwSign(Me->dX) * 2.0e-2;
    if((GameFlags & gfMoreWind) != 0)
    {
        dx = -(aiWindSpeed /(float) Density) + dx;
    }
    dy = 0;
    t = 10000;
    do {
           --t;
           if((GameFlags & gfMoreWind) != 0)
           {
               dx = dx + (aiWindSpeed /(float) Density);
           }
           x = x + dx;
           dy = dy + aiGravityf;
           y = y + dy;
           if(((Me == CurrentHedgehog->Gear) && uaimisc_TestColl(fpcrtl_trunc(x), fpcrtl_trunc(y), 2)) || ((Me != CurrentHedgehog->Gear) && uaimisc_TestCollExcludingMe((*Me->Hedgehog).Gear, fpcrtl_trunc(x), fpcrtl_trunc(y), 2)))
           {
               t = 0;
           }
       } while(!(t == 0));
    EX = fpcrtl_trunc(x);
    EY = fpcrtl_trunc(y);
    if(Level == 1)
    {
        valueResult = uaimisc_RateExplosion_5(Me, EX, EY, 51, afTrackFall | afErasesLand);
    }
    else
    {
        valueResult = uaimisc_RateExplosion_4(Me, EX, EY, 51);
    }
    if(valueResult > 0)
    {
        (*ap).Angle = 0;
        (*ap).Power = 1;
        (*ap).Time = 0;
        if(Level < 5)
        {
            (*ap).Bounce = 1;
        }
        else
        {
            (*ap).Bounce = 0;
        }
        (*ap).ExplR = 100;
        (*ap).ExplX = EX;
        (*ap).ExplY = EY;
    }
    else
    {
        valueResult = BadTurn;
    }
    testmine_result = valueResult;
    return testmine_result;
};
LongInt uaiammotests_TestKnife(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testknife_result;
    enum{timeLimit = 300};
    real Density = 4.0;
    real Vx;
    real Vy;
    real r;
    real meX;
    real meY;
    LongInt rTime;
    LongInt EX;
    LongInt EY;
    LongInt valueResult;
    real targXWrap;
    real x;
    real y;
    real dX;
    real dY;
    LongInt t;
    LongInt value;
    LongInt range;
    UNUSED (Flags);
    meX = ufloat_hwFloat2Float(Me->X);
    meY = ufloat_hwFloat2Float(Me->Y);
    (*ap).Time = 0;
    rTime = 350;
    (*ap).ExplR = 0;
    if(WorldEdge == weWrap)
    {
        if(Targ.Point.x < meX)
        {
            targXWrap = Targ.Point.x + (rightX - leftX);
        }
        else
        {
            targXWrap = Targ.Point.x - (rightX - leftX);
        }
    }
    valueResult = BadTurn;
    do {
           rTime = ((rTime + 300) + (Level * 50)) + fpcrtl_random(300);
           if((WorldEdge == weWrap) && (fpcrtl_random(2) == 0))
           {
               Vx = (targXWrap - meX) /(float) rTime;
           }
           else
           {
               Vx = (Targ.Point.x - meX) /(float) rTime;
           }
           if((GameFlags & gfMoreWind) != 0)
           {
               Vx = ((-(aiWindSpeed /(float) Density) * rTime) * 0.5) + Vx;
           }
           Vy = ((aiGravityf * rTime) * 0.5) - (((Targ.Point.y + 1) - meY) /(float) rTime);
           r = fpcrtl_sqr(Vx) + fpcrtl_sqr(Vy);
           if(!(r > 1))
           {
               x = meX;
               y = meY;
               dX = Vx;
               dY = -Vy;
               t = rTime;
               do {
                      x = uaimisc_CheckWrap(x);
                      x = x + dX;
                      if((GameFlags & gfMoreWind) != 0)
                      {
                          dX = dX + (aiWindSpeed /(float) Density);
                      }
                      y = y + dY;
                      dY = dY + aiGravityf;
                      --t;
                  } while(!((((Me == CurrentHedgehog->Gear) && uaimisc_TestColl(fpcrtl_trunc(x), fpcrtl_trunc(y), 7)) || ((Me != CurrentHedgehog->Gear) && uaimisc_TestCollExcludingMe((*Me->Hedgehog).Gear, fpcrtl_trunc(x), fpcrtl_trunc(y), 7))) || (t < -timeLimit)));
               EX = fpcrtl_trunc(x);
               EY = fpcrtl_trunc(y);
               range = uaiammotests_Metric(fpcrtl_trunc(meX), fpcrtl_trunc(meY), EX, EY);
               if(range <= 40)
               {
                   value = BadTurn;
               }
               else
               {
                   if(t < -timeLimit)
                   {
                       value = BadTurn;
                   }
                   else
                   {
                       value = uaimisc_RateShove(Me, EX, EY, 16, fpcrtl_trunc(fpcrtl_sqr(((fpcrtl_abs(dY) + fpcrtl_abs(dX)) * 40000) /(float) 10000)), 0, dX, dY, 0);
                   }
               }
               if(((value == 0) && (Targ.Kind == gtHedgehog)) && (Targ.Score > 0))
               {
                   value = BadTurn;
               }
               if((valueResult < value) || ((valueResult == value) && (Level == 1)))
               {
                   (*ap).Angle = uutils_DxDy2AttackAnglef(Vx, Vy) + uaimisc_AIrndSign(fpcrtl_random((Level - 1) * 12));
                   (*ap).Power = fpcrtl_trunc(sqrt(r) * cMaxPower) - fpcrtl_random(((Level - 1) * 22) + 1);
                   valueResult = value;
               }
           }
       } while(!(rTime > (5050 - (Level * 800))));
    testknife_result = valueResult;
    return testknife_result;
};
LongInt uaiammotests_TestAirMine(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testairmine_result;
    enum{MIN_RANGE = 160};
    enum{MAX_RANGE = 2612};
    real Vx;
    real Vy;
    real meX;
    real meY;
    real x;
    real y;
    real r;
    LongInt rx;
    LongInt ry;
    LongInt valueResult;
    Integer range;
    Integer maxRange;
    UNUSED (Flags);
    maxRange = MAX_RANGE - ((Level - 1) * 300);
    testairmine_result = BadTurn;
    (*ap).ExplR = 60;
    (*ap).Time = 0;
    meX = ufloat_hwFloat2Float(Me->X);
    meY = ufloat_hwFloat2Float(Me->Y);
    x = meX;
    y = meY;
    range = uaiammotests_Metric(fpcrtl_trunc(x), fpcrtl_trunc(y), Targ.Point.x, Targ.Point.y);
    if((range < MIN_RANGE) || (range > maxRange))
    {
        return BadTurn;
    }
    Vx = ((Targ.Point.x - x) * 1) /(float) 1024;
    Vy = ((Targ.Point.y - y) * 1) /(float) 1024;
    (*ap).Angle = uutils_DxDy2AttackAnglef(Vx, -Vy);
    do {
           x = x + Vx;
           y = y + Vy;
           rx = fpcrtl_trunc(x);
           ry = fpcrtl_trunc(y);
           if(((Me == CurrentHedgehog->Gear) && uaimisc_TestColl(rx, ry, 8)) || ((Me != CurrentHedgehog->Gear) && uaimisc_TestCollExcludingMe((*Me->Hedgehog).Gear, rx, ry, 8)))
           {
               x = x + (Vx * 8);
               y = y + (Vy * 8);
               if(Level == 1)
               {
                   valueResult = uaimisc_RateExplosion_5(Me, rx, ry, 61, afTrackFall);
               }
               else
               {
                   valueResult = uaimisc_RateExplosion_4(Me, rx, ry, 61);
               }
               r = fpcrtl_sqr(meX - rx) + fpcrtl_sqr(meY - ry);
               range = fpcrtl_trunc(sqrt(r));
               if((range < MIN_RANGE) || (range > maxRange))
               {
                   return BadTurn;
               }
               (*ap).Power = ((range + (cHHRadius * 2)) * cMaxPower) / MAX_RANGE;
               (*ap).Power += fpcrtl_random(93 * (Level - 1)) - (31 * (Level - 1));
               if(!aiLaserSighting)
               {
                   (*ap).Angle += uaimisc_AIrndSign(fpcrtl_random((Level - 1) * 10));
               }
               if(valueResult <= 0)
               {
                   valueResult = BadTurn;
               }
               return valueResult;
           }
       } while(!((((((fpcrtl_abs(Targ.Point.x - fpcrtl_trunc(x)) + fpcrtl_abs(Targ.Point.y - fpcrtl_trunc(y))) < 4) || (x < 0)) || (y < 0)) || (fpcrtl_trunc(x) > LAND_WIDTH)) || (fpcrtl_trunc(y) > LAND_HEIGHT)));
    testairmine_result = BadTurn;
    return testairmine_result;
};
LongInt uaiammotests_TestMinigun(PGear Me,TTarget Targ,LongInt Level,TAttackParams (*ap),LongWord Flags)
{
    LongInt testminigun_result;
    enum{MAX_RANGE = 400};
    real Vx;
    real Vy;
    real x;
    real y;
    LongInt rx;
    LongInt ry;
    LongInt valueResult;
    Integer range;
    UNUSED (Flags);
    testminigun_result = BadTurn;
    (*ap).ExplR = 0;
    (*ap).Time = 0;
    (*ap).Power = 1;
    x = ufloat_hwFloat2Float(Me->X);
    y = ufloat_hwFloat2Float(Me->Y);
    range = uaiammotests_Metric(fpcrtl_trunc(x), fpcrtl_trunc(y), Targ.Point.x, Targ.Point.y);
    if(range > MAX_RANGE)
    {
        return BadTurn;
    }
    Vx = ((Targ.Point.x - x) * 1) /(float) 1024;
    Vy = ((Targ.Point.y - y) * 1) /(float) 1024;
    (*ap).Angle = uutils_DxDy2AttackAnglef(Vx, -Vy);
    if((fpcrtl_abs((*ap).Angle) < Ammoz[amMinigun].minAngle) || (fpcrtl_abs((*ap).Angle) > Ammoz[amMinigun].maxAngle))
    {
        return BadTurn;
    }
    if(!aiLaserSighting)
    {
        (*ap).Angle += uaimisc_AIrndSign(fpcrtl_random((Level - 1) * 10));
    }
    do {
           x = x + Vx;
           y = y + Vy;
           rx = fpcrtl_trunc(x);
           ry = fpcrtl_trunc(y);
           if(((Me == CurrentHedgehog->Gear) && uaimisc_TestColl(rx, ry, 1)) || ((Me != CurrentHedgehog->Gear) && uaimisc_TestCollExcludingMe((*Me->Hedgehog).Gear, rx, ry, 1)))
           {
               x = x + (Vx * 8);
               y = y + (Vy * 8);
               valueResult = uaimisc_RateShotgun(Me, Vx, Vy, rx, ry);
               if(((valueResult == 0) && (Targ.Kind == gtHedgehog)) && (Targ.Score > 0))
               {
                   if((GameFlags & gfSolidLand) == 0)
                   {
                       valueResult = 1024 - (uaiammotests_Metric(Targ.Point.x, Targ.Point.y, rx, ry) / 64);
                   }
                   else
                   {
                       valueResult = BadTurn;
                   }
               }
               else
               {
                   valueResult -= Level * 4000;
               }
               return valueResult;
           }
       } while(!((((((fpcrtl_abs(Targ.Point.x - fpcrtl_trunc(x)) + fpcrtl_abs(Targ.Point.y - fpcrtl_trunc(y))) < 4) || (x < 0)) || (y < 0)) || (fpcrtl_trunc(x) > LAND_WIDTH)) || (fpcrtl_trunc(y) > LAND_HEIGHT)));
    testminigun_result = BadTurn;
    return testminigun_result;
};
