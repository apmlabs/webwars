#include "fpcrtl.h"

#include "uGearsList.h"
PGear curHandledGear;
#include "uRandom.h"
#include "uUtils.h"
#include "uConsts.h"
#include "uVariables.h"
#include "uAmmos.h"
#include "uTeams.h"
#include "uStats.h"
#include "uTextures.h"
#include "uScript.h"
#include "uRenderUtils.h"
#include "uAI.h"
#include "uCollisions.h"
#include "uGearsRender.h"
#include "uGearsUtils.h"
#include "uDebug.h"
static const string255 __str9 = STRINIT("Delete: #");
static const string255 __str8 = STRINIT("onGearDelete");
static const string255 __str7 = STRINIT("onGearAdd");
static const string255 __str6 = STRINIT(") type = ");
static const string255 __str5 = STRINIT("), d(");
static const string255 __str4 = STRINIT(" (");
static const string255 __str3 = STRINIT("AddGear: #");
static const string255 __str2 = STRINIT("You're doing it wrong");
static const string255 __str1 = STRINIT(" from the list twice.");
static const string255 __str0 = STRINIT("Attempted to remove Gear #");
typedef TAmmoType GearKindAmmoTypeMap_tt[70];
static GearKindAmmoTypeMap_tt GearKindAmmoTypeMap = {amNothing,
                                                     amNothing,
                                                     amMine,
                                                     amNothing,
                                                     amAirMine,
                                                     amNothing,
                                                     amGrenade,
                                                     amBazooka,
                                                     amNothing,
                                                     amBee,
                                                     amShotgun,
                                                     amPickHammer,
                                                     amRope,
                                                     amDEagle,
                                                     amDynamite,
                                                     amClusterBomb,
                                                     amClusterBomb,
                                                     amBaseballBat,
                                                     amFirePunch,
                                                     amNothing,
                                                     amNothing,
                                                     amParachute,
                                                     amAirAttack,
                                                     amAirAttack,
                                                     amBlowTorch,
                                                     amGirder,
                                                     amTeleport,
                                                     amSwitch,
                                                     amNothing,
                                                     amMortar,
                                                     amWhip,
                                                     amKamikaze,
                                                     amCake,
                                                     amSeduction,
                                                     amWatermelon,
                                                     amWatermelon,
                                                     amHellishBomb,
                                                     amNothing,
                                                     amDrill,
                                                     amBallgun,
                                                     amBallgun,
                                                     amRCPlane,
                                                     amSniperRifle,
                                                     amJetpack,
                                                     amMolotov,
                                                     amBirdy,
                                                     amBirdy,
                                                     amPortalGun,
                                                     amPiano,
                                                     amGasBomb,
                                                     amSineGun,
                                                     amFlamethrower,
                                                     amSMine,
                                                     amNothing,
                                                     amHammer,
                                                     amHammer,
                                                     amResurrector,
                                                     amNothing,
                                                     amSnowball,
                                                     amNothing,
                                                     amLandGun,
                                                     amTardis,
                                                     amIceGun,
                                                     amNothing,
                                                     amNothing,
                                                     amKnife,
                                                     amCreeper,
                                                     amMinigun,
                                                     amMinigun,
                                                     amSentry};
static LongWord GCounter = 0;
enum{cUsualZ = 500};
enum{cOnHHZ = 2000};
void ugearslist_InsertGearToList(PGear Gear)
{
    PGear tmp;
    PGear ptmp;
    tmp = GearsList;
    ptmp = GearsList;
    while((tmp != NULL) && (tmp->Z < Gear->Z))
    {
        ptmp = tmp;
        tmp = tmp->NextGear;
    }
    if(ptmp != tmp)
    {
        Gear->NextGear = ptmp->NextGear;
        Gear->PrevGear = ptmp;
        if(ptmp->NextGear != NULL)
        {
            (*ptmp->NextGear).PrevGear = Gear;
        }
        ptmp->NextGear = Gear;
    }
    else
    {
        Gear->NextGear = GearsList;
        if(Gear->NextGear != NULL)
        {
            (*Gear->NextGear).PrevGear = Gear;
        }
        GearsList = Gear;
    }
};
void ugearslist_RemoveGearFromList(PGear Gear)
{
    if((((Gear != GearsList) && (Gear != NULL)) && (Gear->NextGear == NULL)) && (Gear->PrevGear == NULL))
    {
        uutils_AddFileLog(_strconcat(_strconcat(__str0, uutils_IntToStr(Gear->uid)), __str1));
        return;
    }
    udebug_checkFails(((Gear == NULL) || (curHandledGear == NULL)) || (Gear == curHandledGear), __str2, true);
    if(Gear->NextGear != NULL)
    {
        (*Gear->NextGear).PrevGear = Gear->PrevGear;
    }
    if(Gear->PrevGear != NULL)
    {
        (*Gear->PrevGear).NextGear = Gear->NextGear;
    }
    else
    {
        GearsList = Gear->NextGear;
    }
    Gear->NextGear = NULL;
    Gear->PrevGear = NULL;
};
void ugearslist_initializeGear(PGear gear,LongInt X,LongInt Y,TGearType Kind,LongWord State,hwFloat dX,hwFloat dY,LongWord Timer,LongWord newUid)
{
    PCakeData cakeData;
    fpcrtl_FillChar((*gear), sizeof(TGear), 0);
    gear->X = ufloat_int2hwFloat(X);
    gear->Y = ufloat_int2hwFloat(Y);
    gear->Target.x = NoPointX;
    gear->Kind = Kind;
    gear->State = State;
    gear->Active = true;
    gear->dX = dX;
    gear->dY = dY;
    gear->doStep = doStepHandlers[Kind];
    gear->CollisionIndex = -1;
    gear->Timer = Timer;
    if(newUid == 0)
    {
        gear->uid = GCounter;
    }
    else
    {
        gear->uid = newUid;
    }
    gear->SoundChannel = -1;
    gear->ImpactSound = sndNone;
    gear->Density = _1;
    gear->AmmoType = GearKindAmmoTypeMap[Kind];
    gear->CollisionMask = lfAll;
    gear->Tint = 0xffffffff;
    gear->Data = NULL;
    gear->Sticky = false;
    if(CurrentHedgehog != NULL)
    {
        gear->Hedgehog = CurrentHedgehog;
        if(((CurrentHedgehog->Gear != NULL) && (ufloat_hwRound((*CurrentHedgehog->Gear).X) == X)) && (ufloat_hwRound((*CurrentHedgehog->Gear).Y) == Y))
        {
            gear->CollisionMask = lfNotCurHogCrate;
        }
    }
    if((Ammoz[gear->AmmoType].Ammo.Propz & ammoprop_NeedTarget) != 0)
    {
        gear->Z = cHHZ + 1;
    }
    else
    {
        gear->Z = cUsualZ;
    }
    if(WorldEdge == weBounce)
    {
        if(((ufloat_hwRound(gear->X) - gear->Radius) < leftX) || ((ufloat_hwRound(gear->X) + gear->Radius) > rightX))
        {
            switch(gear->Kind)
            {case gtHedgehog:
             case gtFlame:
             case gtMine:
             case gtAirBomb:
             case gtDrill:
             case gtNapalmBomb:
             case gtCase:
             case gtAirMine:
             case gtExplosives:
             case gtGrenade:
             case gtShell:
             case gtBee:
             case gtDynamite:
             case gtClusterBomb:
             case gtMelonPiece:
             case gtCluster:
             case gtMortar:
             case gtKamikaze:
             case gtCake:
             case gtWatermelon:
             case gtGasBomb:
             case gtHellishBomb:
             case gtBall:
             case gtRCPlane:
             case gtSniperRifleShot:
             case gtShotgunShot:
             case gtDEagleShot:
             case gtSineGunShot:
             case gtMinigunBullet:
             case gtEgg:
             case gtPiano:
             case gtSMine:
             case gtSnowball:
             case gtKnife:
             case gtCreeper:
             case gtSentry:
             case gtMolotov:
             case gtFlake:
             case gtGrave:
             case gtPortal:
             case gtTarget:gear->State = gear->State | gstInBounceEdge;
                           break;
             default: break;}
        }
    }
    switch(Kind)
    {case gtFlame:gear->Boom = 2;
                  break;
     case gtHedgehog:gear->Boom = 30;
                     break;
     case gtMine:gear->Boom = 50;
                 break;
     case gtCase:gear->Boom = 25;
                 break;
     case gtAirMine:gear->Boom = 30;
                    break;
     case gtExplosives:gear->Boom = 75;
                       break;
     case gtGrenade:gear->Boom = 50;
                    break;
     case gtShell:gear->Boom = 50;
                  break;
     case gtBee:gear->Boom = 50;
                break;
     case gtShotgunShot:gear->Boom = 25;
                        break;
     case gtPickHammer:gear->Boom = 6;
                       break;
     case gtDEagleShot:gear->Boom = 7;
                       break;
     case gtDynamite:gear->Boom = 75;
                     break;
     case gtClusterBomb:gear->Boom = 20;
                        break;
     case gtMelonPiece:
     case gtCluster:gear->Boom = Timer;
                    break;
     case gtShover:gear->Boom = 30;
                   break;
     case gtFirePunch:gear->Boom = 30;
                      break;
     case gtAirBomb:gear->Boom = 30;
                    break;
     case gtBlowTorch:gear->Boom = 2;
                      break;
     case gtMortar:gear->Boom = 20;
                   break;
     case gtWhip:gear->Boom = 30;
                 break;
     case gtKamikaze:gear->Boom = 30;
                     break;
     case gtCake:gear->Boom = cakeDmg;
                 break;
     case gtWatermelon:gear->Boom = 75;
                       break;
     case gtHellishBomb:gear->Boom = 90;
                        break;
     case gtDrill:if((gear->State & gsttmpFlag) == 0)
                  {
                      gear->Boom = 50;
                  }
                  else
                  {
                      gear->Boom = 30;
                  }
                  break;
     case gtBall:gear->Boom = 40;
                 break;
     case gtRCPlane:gear->Boom = 25;
                    break;
     case gtSniperRifleShot:gear->Boom = 100000;
                            break;
     case gtEgg:gear->Boom = 10;
                break;
     case gtPiano:gear->Boom = 80;
                  break;
     case gtGasBomb:gear->Boom = 20;
                    break;
     case gtSineGunShot:gear->Boom = 35;
                        break;
     case gtSMine:gear->Boom = 30;
                  break;
     case gtSnowball:gear->Boom = 200000;
                     break;
     case gtHammer:if(ufloat_hwFloat_hwFloat_op_gt(cDamageModifier, _1))
                   {
                       gear->Boom = 2;
                   }
                   else
                   {
                       gear->Boom = 3;
                   }
                   break;
     case gtPoisonCloud:gear->Boom = 20;
                        break;
     case gtKnife:gear->Boom = 40000;
                  break;
     case gtCreeper:gear->Boom = 100;
                    break;
     case gtMinigunBullet:gear->Boom = 2;
                          break;
     case gtSentry:gear->Boom = 40;
                   break;
     default: break;}
    switch(Kind)
    {case gtGrenade:
     case gtClusterBomb:
     case gtGasBomb:{
                        gear->ImpactSound = sndGrenadeImpact;
                        gear->nImpactSounds = 1;
                        gear->AdvBounce = 1;
                        gear->Radius = 5;
                        gear->Elasticity = _0_8;
                        gear->Friction = _0_8;
                        gear->Density = _1_5;
                        gear->RenderTimer = true;
                        if(gear->Timer == 0)
                        {
                            gear->Timer = 3000;
                        }
                    }
                    break;
     case gtWatermelon:{
                           gear->ImpactSound = sndMelonImpact;
                           gear->nImpactSounds = 1;
                           gear->AdvBounce = 1;
                           gear->Radius = 6;
                           gear->Elasticity = _0_8;
                           gear->Friction = _0_995;
                           gear->Density = _2;
                           gear->RenderTimer = true;
                           if(gear->Timer == 0)
                           {
                               gear->Timer = 3000;
                           }
                       }
                       break;
     case gtMelonPiece:{
                           gear->AdvBounce = 1;
                           gear->Density = _2;
                           gear->Elasticity = _0_8;
                           gear->Friction = _0_995;
                           gear->Radius = 4;
                       }
                       break;
     case gtHedgehog:{
                         gear->AdvBounce = 1;
                         gear->Radius = cHHRadius;
                         gear->Elasticity = _0_35;
                         gear->Friction = _0_999;
                         gear->Angle = cMaxAngle / 2;
                         gear->Density = _3;
                         gear->Z = cHHZ;
                         if((GameFlags & gfAISurvival) != 0)
                         {
                             if((*gear->Hedgehog).BotLevel > 0)
                             {
                                 (*gear->Hedgehog).Effects[heResurrectable] = 1;
                             }
                         }
                         if((GameFlags & gfArtillery) != 0)
                         {
                             (*gear->Hedgehog).Effects[heArtillery] = 1;
                         }
                     }
                     break;
     case gtParachute:{
                          gear->Tag = 1;
                          gear->Z = cCurrHHZ;
                      }
                      break;
     case gtShell:{
                      gear->Elasticity = _0_8;
                      gear->Friction = _0_8;
                      gear->Radius = 4;
                      gear->Density = _1;
                      gear->AdvBounce = 1;
                  }
                  break;
     case gtSnowball:{
                         gear->ImpactSound = sndMudballImpact;
                         gear->nImpactSounds = 1;
                         gear->Radius = 4;
                         gear->Density = _0_5;
                         gear->AdvBounce = 1;
                         gear->Elasticity = _0_8;
                         gear->Friction = _0_8;
                     }
                     break;
     case gtFlake:{
                      {
                          (*gear).Pos = 0;
                          (*gear).Radius = 1;
                          (*gear).DirAngle = fpcrtl_random(360);
                          (*gear).Sticky = true;
                          if(((*gear).State & gsttmpFlag) == 0)
                          {
                              (*gear).dX.isNegative = urandom_GetRandom(2) == 0;
                              (*gear).dX.QWordValue = (((QWord)0x40da) * urandom_GetRandom(10000)) * 8;
                              (*gear).dY.isNegative = false;
                              (*gear).dY.QWordValue = (((QWord)0x3ad3) * urandom_GetRandom(7000)) * 8;
                              if(urandom_GetRandom(2) == 0)
                              {
                                  (*gear).dX = ufloat_hwFloat_op_sub((*gear).dX);
                              }
                              (*gear).Tint = 0xffffffff;
                          }
                          else
                          {
                              (*gear).Tint = (((((ExplosionBorderColor >> RShift) & 0xff) << 24) | (((ExplosionBorderColor >> GShift) & 0xff) << 16)) | (((ExplosionBorderColor >> BShift) & 0xff) << 8)) | 0xff;
                          }
                          (*gear).State = (*gear).State | gstInvisible;
                          if(vobFrameTicks > 0)
                          {
                              (*gear).Health = fpcrtl_random(vobFrameTicks);
                          }
                          else
                          {
                              (*gear).Health = 0;
                          }
                          if(gear->Timer == 0)
                          {
                              (*gear).Timer = fpcrtl_random(vobFramesCount);
                          }
                          (*gear).Damage = (((fpcrtl_random(2) * 2) - 1) * (vobVelocity + fpcrtl_random(vobVelocity))) * 8;
                      }
                  }
                  break;
     case gtGrave:{
                      gear->ImpactSound = sndGraveImpact;
                      gear->nImpactSounds = 1;
                      gear->Radius = 10;
                      gear->Elasticity = _0_6;
                      gear->Z = 1;
                  }
                  break;
     case gtBee:{
                    gear->Radius = 5;
                    if(gear->Timer == 0)
                    {
                        gear->Timer = 500;
                    }
                    gear->RenderTimer = true;
                    gear->Elasticity = _0_9;
                    gear->Tag = 0;
                    gear->State = gear->State | gstSubmersible;
                }
                break;
     case gtSeduction:{
                          gear->Radius = cSeductionDist;
                      }
                      break;
     case gtShotgunShot:{
                            if(gear->Timer == 0)
                            {
                                gear->Timer = 900;
                            }
                            gear->Radius = 2;
                        }
                        break;
     case gtPickHammer:{
                           gear->Radius = 10;
                           if(gear->Timer == 0)
                           {
                               gear->Timer = 4000;
                           }
                       }
                       break;
     case gtHammerHit:{
                          gear->Radius = 8;
                          if(gear->Timer == 0)
                          {
                              gear->Timer = 125;
                          }
                      }
                      break;
     case gtRope:{
                     gear->Radius = 3;
                     gear->Friction = ufloat_hwFloat_LongInt_op_mul(ufloat_hwFloat_hwFloat_op_mul(_450, _0_01), cRopePercent);
                     RopePoints.Count = 0;
                     gear->Tint = 0xd8d8d8ff;
                     gear->Tag = 0;
                     gear->CollisionMask = lfNotCurHogCrate;
                 }
                 break;
     case gtMine:{
                     gear->ImpactSound = sndMineImpact;
                     gear->nImpactSounds = 1;
                     gear->Health = 10;
                     gear->State = gear->State | gstMoving;
                     gear->Radius = 2;
                     gear->Elasticity = _0_55;
                     gear->Friction = _0_995;
                     gear->Density = _1;
                     if(gear->Timer == 0)
                     {
                         if(cMinesTime < 0)
                         {
                             gear->Timer = urandom_GetRandom(51) * 100;
                             gear->Karma = 1;
                         }
                         else
                         {
                             gear->Timer = cMinesTime;
                         }
                     }
                     gear->RenderTimer = true;
                 }
                 break;
     case gtAirMine:{
                        gear->AdvBounce = 1;
                        gear->ImpactSound = sndAirMineImpact;
                        gear->nImpactSounds = 1;
                        gear->Health = 30;
                        gear->State = ((gear->State | gstMoving) | gstNoGravity) | gstSubmersible;
                        gear->Radius = 8;
                        gear->Elasticity = _0_55;
                        gear->Friction = _0_995;
                        gear->Density = _1;
                        gear->Angle = 175;
                        gear->Power = cMaxWindSpeed.QWordValue / 2;
                        gear->Pos = (cMaxWindSpeed.QWordValue * 3) / 2;
                        gear->Tag = 0;
                        if(gear->Timer == 0)
                        {
                            if(cMinesTime < 0)
                            {
                                gear->Timer = urandom_GetRandom(13) * 100;
                                gear->Karma = 1;
                            }
                            else
                            {
                                gear->Timer = cMinesTime / 4;
                            }
                        }
                        gear->RenderTimer = true;
                        gear->WDTimer = gear->Timer;
                    }
                    break;
     case gtSMine:{
                      gear->Health = 10;
                      gear->State = gear->State | gstMoving;
                      gear->Radius = 2;
                      gear->Elasticity = _0_55;
                      gear->Friction = _0_995;
                      gear->Density = _1_6;
                      gear->AdvBounce = 1;
                      gear->Sticky = true;
                      if(gear->Timer == 0)
                      {
                          gear->Timer = 500;
                      }
                      gear->RenderTimer = true;
                  }
                  break;
     case gtKnife:{
                      gear->ImpactSound = sndKnifeImpact;
                      gear->AdvBounce = 1;
                      gear->Elasticity = _0_8;
                      gear->Friction = _0_8;
                      gear->Density = _4;
                      gear->Radius = 7;
                      gear->Sticky = true;
                  }
                  break;
     case gtCase:{
                     gear->ImpactSound = sndCaseImpact;
                     gear->nImpactSounds = 1;
                     gear->Radius = 16;
                     gear->Elasticity = _0_3;
                     if(gear->Timer == 0)
                     {
                         gear->Timer = 500;
                     }
                 }
                 break;
     case gtExplosives:{
                           gear->AdvBounce = 1;
                           if(((GameType == gmtDemo) || (GameType == gmtRecord)))
                           {
                               gear->RenderHealth = true;
                           }
                           gear->ImpactSound = sndGrenadeImpact;
                           gear->nImpactSounds = 1;
                           gear->Radius = 16;
                           gear->Elasticity = _0_4;
                           gear->Friction = _0_995;
                           gear->Density = _6;
                           gear->Health = cBarrelHealth;
                           gear->Z = cHHZ - 1;
                       }
                       break;
     case gtDEagleShot:{
                           gear->Radius = 1;
                           gear->Health = 50;
                           gear->Data = NULL;
                       }
                       break;
     case gtSniperRifleShot:{
                                gear->Radius = 1;
                                gear->Health = 50;
                            }
                            break;
     case gtDynamite:{
                         gear->ImpactSound = sndDynamiteImpact;
                         gear->nImpactSounds = 1;
                         gear->Radius = 3;
                         gear->Elasticity = _0_55;
                         gear->Friction = _0_03;
                         gear->Density = _2;
                         if(gear->Timer == 0)
                         {
                             gear->Timer = 5000;
                         }
                     }
                     break;
     case gtCluster:{
                        gear->AdvBounce = 1;
                        gear->Elasticity = _0_8;
                        gear->Friction = _0_8;
                        gear->Radius = 2;
                        gear->Density = _1_5;
                        gear->RenderTimer = true;
                    }
                    break;
     case gtShover:{
                       gear->Radius = 20;
                       gear->Tag = 0;
                       gear->Timer = 50;
                   }
                   break;
     case gtFlame:{
                      gear->Tag = urandom_GetRandom(32);
                      gear->Radius = 1;
                      gear->Health = 5;
                      gear->Density = _1;
                      gear->FlightTime = 9999999;
                      if((gear->dY.QWordValue == 0) && (gear->dX.QWordValue == 0))
                      {
                          gear->dY = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_sub(urandom_GetRandomf(), _0_8), _0_03);
                          gear->dX = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_sub(urandom_GetRandomf(), _0_5), _0_4);
                      }
                  }
                  break;
     case gtFirePunch:{
                          if(gear->Timer == 0)
                          {
                              gear->Timer = 3000;
                          }
                          gear->Radius = 15;
                          gear->Tag = Y;
                      }
                      break;
     case gtAirAttack:{
                          gear->Health = 6;
                          gear->Damage = 30;
                          gear->Z = cHHZ + 2;
                          gear->Karma = 0;
                          gear->Radius = 150;
                          gear->FlightTime = 0;
                          gear->Power = 0;
                          gear->WDTimer = 0;
                          gear->Density = _19;
                          gear->Tint = ((*(*(*gear->Hedgehog).Team).Clan).Color << 8) | 0xff;
                      }
                      break;
     case gtAirBomb:{
                        gear->AdvBounce = 1;
                        gear->Radius = 5;
                        gear->Density = _2;
                        gear->Elasticity = _0_55;
                        gear->Friction = _0_995;
                    }
                    break;
     case gtBlowTorch:{
                          gear->Radius = (cHHRadius + cBlowTorchC) - 1;
                          if(gear->Timer == 0)
                          {
                              gear->Timer = 7500;
                          }
                      }
                      break;
     case gtSwitcher:{
                         gear->Z = cCurrHHZ;
                     }
                     break;
     case gtTarget:{
                       gear->ImpactSound = sndGrenadeImpact;
                       gear->nImpactSounds = 1;
                       gear->Radius = 10;
                       gear->Elasticity = _0_3;
                   }
                   break;
     case gtTardis:{
                       gear->Pos = 1;
                       gear->Tag = 0;
                       gear->Z = cCurrHHZ + 1;
                   }
                   break;
     case gtMortar:{
                       gear->AdvBounce = 1;
                       gear->Radius = 4;
                       gear->Elasticity = _0_2;
                       gear->Friction = _0_08;
                       gear->Density = _1;
                   }
                   break;
     case gtWhip:gear->Radius = 20;
                 break;
     case gtHammer:gear->Radius = 20;
                   break;
     case gtKamikaze:{
                         gear->Health = 2048;
                         gear->Radius = 20;
                     }
                     break;
     case gtCake:{
                     gear->Health = 2048;
                     gear->Radius = 7;
                     gear->Z = cOnHHZ;
                     gear->RenderTimer = false;
                     gear->DirAngle = -90 * ufloat_hwSign(gear->dX);
                     gear->FlightTime = 100;
                     if(!dX.isNegative)
                     {
                         gear->Angle = 1;
                     }
                     else
                     {
                         gear->Angle = 3;
                     }
                     fpcrtl_new(cakeData);
                     gear->Data = ((pointer)cakeData);
                 }
                 break;
     case gtHellishBomb:{
                            gear->ImpactSound = sndHellishImpact1;
                            gear->nImpactSounds = 4;
                            gear->AdvBounce = 1;
                            gear->Radius = 4;
                            gear->Elasticity = _0_5;
                            gear->Friction = _0_96;
                            gear->Density = _1_5;
                            gear->RenderTimer = true;
                            if(gear->Timer == 0)
                            {
                                gear->Timer = 5000;
                            }
                        }
                        break;
     case gtDrill:{
                      gear->AdvBounce = 1;
                      gear->Elasticity = _0_8;
                      gear->Friction = _0_8;
                      if(gear->Timer == 0)
                      {
                          gear->Timer = 5000;
                      }
                      gear->Tag = 0;
                      gear->Pos = 0;
                      gear->Radius = 4;
                      gear->Density = _1;
                  }
                  break;
     case gtBall:{
                     gear->ImpactSound = sndGrenadeImpact;
                     gear->nImpactSounds = 1;
                     gear->AdvBounce = 1;
                     gear->Radius = 5;
                     gear->Tag = fpcrtl_random(8);
                     if(gear->Timer == 0)
                     {
                         gear->Timer = 5000;
                     }
                     gear->Elasticity = _0_7;
                     gear->Friction = _0_995;
                     gear->Density = _1_5;
                 }
                 break;
     case gtBallGun:{
                        if(gear->Timer == 0)
                        {
                            gear->Timer = 5001;
                        }
                    }
                    break;
     case gtRCPlane:{
                        if(gear->Timer == 0)
                        {
                            gear->Timer = 15000;
                        }
                        gear->Health = 3;
                        gear->Radius = 8;
                        gear->Tint = ((*(*(*gear->Hedgehog).Team).Clan).Color << 8) | 0xff;
                    }
                    break;
     case gtJetpack:{
                        gear->Health = 2000;
                        gear->Damage = 100;
                        gear->State = gear->State | gstSubmersible;
                    }
                    break;
     case gtMolotov:{
                        gear->AdvBounce = 1;
                        gear->Radius = 6;
                        gear->Elasticity = _0_8;
                        gear->Friction = _0_8;
                        gear->Density = _2;
                    }
                    break;
     case gtBirdy:{
                      gear->Radius = 16;
                      gear->Health = 2000;
                      gear->FlightTime = 2;
                      gear->Z = cCurrHHZ;
                  }
                  break;
     case gtEgg:{
                    gear->AdvBounce = 1;
                    gear->Radius = 4;
                    gear->Elasticity = _0_6;
                    gear->Friction = _0_96;
                    gear->Density = _1;
                    if(gear->Timer == 0)
                    {
                        gear->Timer = 3000;
                    }
                }
                break;
     case gtPortal:{
                       gear->ImpactSound = sndMelonImpact;
                       gear->nImpactSounds = 1;
                       gear->Radius = 17;
                       gear->Tag = 2 * gear->Timer;
                       gear->Timer = 15000;
                       gear->RenderTimer = false;
                       gear->Health = 100;
                       gear->Sticky = true;
                   }
                   break;
     case gtPiano:{
                      gear->Radius = 32;
                      gear->Density = _50;
                  }
                  break;
     case gtSineGunShot:{
                            gear->Radius = 5;
                            gear->Health = 6000;
                        }
                        break;
     case gtFlamethrower:{
                             gear->Tag = 10;
                             if(gear->Timer == 0)
                             {
                                 gear->Timer = 10;
                             }
                             gear->Health = 500;
                             gear->Damage = 100;
                         }
                         break;
     case gtLandGun:{
                        gear->Tag = 10;
                        if(gear->Timer == 0)
                        {
                            gear->Timer = 10;
                        }
                        gear->Health = 1000;
                        gear->Damage = 100;
                    }
                    break;
     case gtPoisonCloud:{
                            if(gear->Timer == 0)
                            {
                                gear->Timer = 5000;
                            }
                            gear->WDTimer = gear->Timer;
                            gear->dY = ufloat_hwFloat_LongInt_op_div(ufloat_int2hwFloat(-4 + ((LongInt)urandom_GetRandom(8))), 1000);
                            gear->Tint = 0xc0c000c0;
                        }
                        break;
     case gtResurrector:{
                            gear->Radius = cResurrectorDist;
                            gear->Tag = 0;
                            gear->Tint = 0xf5db35ff;
                        }
                        break;
     case gtWaterUp:{
                        gear->Tag = 47;
                    }
                    break;
     case gtNapalmBomb:{
                           gear->Elasticity = _0_8;
                           gear->Friction = _0_8;
                           if(gear->Timer == 0)
                           {
                               gear->Timer = 1000;
                           }
                           gear->Radius = 5;
                           gear->Density = _1_5;
                       }
                       break;
     case gtIceGun:{
                       gear->Health = 1000;
                       gear->Radius = 8;
                       gear->Density = _0;
                       gear->Tag = 0;
                   }
                   break;
     case gtCreeper:{
                        gear->Radius = cHHRadius;
                        gear->Elasticity = _0_35;
                        gear->Friction = _0_93;
                        gear->Density = _5;
                        gear->AdvBounce = 1;
                        gear->ImpactSound = sndAirMineImpact;
                        gear->nImpactSounds = 1;
                        gear->Health = 30;
                        gear->Radius = 8;
                        gear->Angle = 175;
                        gear->Power = cMaxWindSpeed.QWordValue / 2;
                        gear->Pos = (cMaxWindSpeed.QWordValue * 3) / 2;
                        if(gear->Timer == 0)
                        {
                            gear->Timer = 5000;
                        }
                        gear->WDTimer = gear->Timer;
                    }
                    break;
     case gtMinigun:{
                        if(gear->Timer == 0)
                        {
                            gear->Timer = 601;
                        }
                        gear->Karma = 3451;
                    }
                    break;
     case gtMinigunBullet:{
                              gear->Radius = 1;
                              gear->Health = 2;
                              gear->Karma = 5;
                              gear->Pos = 0;
                              gear->Data = NULL;
                          }
                          break;
     case gtSentry:{
                       gear->Radius = cHHRadius;
                       gear->Health = cSentryHealth;
                       gear->Friction = _0_999;
                       gear->Elasticity = _0_35;
                       gear->Density = _3;
                       gear->Tag = 0;
                       gear->Timer = 1000;
                       gear->WDTimer = 0;
                   }
                   break;
     case gtGenericFaller:{
                              gear->AdvBounce = 1;
                              gear->Radius = 1;
                              gear->Elasticity = _0_9;
                              gear->Friction = _0_995;
                              gear->Density = _1;
                          }
                          break;
     default: break;}
};
PGear ugearslist_AddGear_7(LongInt X,LongInt Y,TGearType Kind,LongWord State,hwFloat dX,hwFloat dY,LongWord Timer)
{
    PGear addgear_result;
    addgear_result = ugearslist_AddGear_8(X, Y, Kind, State, dX, dY, Timer, 0);
    return addgear_result;
};
PGear ugearslist_AddGear_8(LongInt X,LongInt Y,TGearType Kind,LongWord State,hwFloat dX,hwFloat dY,LongWord Timer,LongWord newUid)
{
    PGear addgear_result;
    PGear gear;
    if(newUid == 0)
    {
        ++GCounter;
    }
    uutils_AddFileLog(_strconcat(_strconcat(_strconcat(_strappend(_strconcat(_strconcat(_strconcat(_strappend(_strconcat(_strconcat(_strconcat(__str3, uutils_IntToStr(GCounter)), __str4), uutils_IntToStr(X)), 0x2c), uutils_IntToStr(Y)), __str5), uutils_FloatToStr(dX)), 0x2c), uutils_FloatToStr(dY)), __str6), uutils_EnumToStr_1(Kind)));
    fpcrtl_new(gear);
    ugearslist_initializeGear(gear, X, Y, Kind, State, dX, dY, Timer, newUid);
    ugearslist_InsertGearToList(gear);
    addgear_result = gear;
    uscript_ScriptCall_2(__str7, gear->uid);
    return addgear_result;
};
void ugearslist_DeleteGear(PGear Gear)
{
    PTeam team;
    LongWord t;
    LongWord i;
    PCakeData cakeData;
    PGear iterator;
    uscript_ScriptCall_2(__str8, Gear->uid);
    ucollisions_DeleteCI(Gear);
    ucollisions_RemoveFromProximityCache(Gear);
    utextures_FreeAndNilTexture(&(Gear->Tex));
    if(((Gear->Kind == gtHedgehog) || (Gear->Kind == gtMine)) || (Gear->Kind == gtExplosives))
    {
        iterator = NULL;
        while(true)
        {
            if(iterator == NULL)
            {
                iterator = GearsList;
            }
            else
            {
                iterator = iterator->NextGear;
            }
            if(iterator == NULL)
            {
                break;
            }
            if(iterator->LinkedGear == Gear)
            {
                iterator->LinkedGear = NULL;
            }
        }
    }
    if(Gear->Kind == gtPortal)
    {
        if(Gear->LinkedGear != NULL)
        {
            if((*Gear->LinkedGear).LinkedGear == Gear)
            {
                (*Gear->LinkedGear).LinkedGear = NULL;
            }
        }
    }
    else
    {
        if(Gear->Kind == gtCake)
        {
            cakeData = ((PCakeData)Gear->Data);
            fpcrtl_dispose(cakeData);
            cakeData = NULL;
        }
        else
        {
            if(Gear->Kind == gtHedgehog)
            {
                if((((CurrentHedgehog == NULL) || (Gear != CurrentHedgehog->Gear)) || (CurAmmoGear == NULL)) || (CurAmmoGear->Kind != gtKamikaze))
                {
                    (*(*(*Gear->Hedgehog).Team).Clan).Flawless = false;
                }
                if(ucollisions_CheckCoordInWater(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y)))
                {
                    t = uutils_Max(Gear->Damage, Gear->Health);
                    Gear->Damage = t;
                    ugearsutils_spawnHealthTagForHH(Gear, t);
                }
                team = (*Gear->Hedgehog).Team;
                if((CurrentHedgehog != NULL) && (CurrentHedgehog->Gear == Gear))
                {
                    AttackBar = 0;
                    uai_FreeActionsList();
                    if(((Ammoz[CurrentHedgehog->CurAmmoType].Ammo.Propz & ammoprop_NoRoundEnd) != 0) && (CurrentHedgehog->MultiShootAttacks > 0))
                    {
                        uammos_OnUsedAmmo(&((*CurrentHedgehog)));
                    }
                }
                (*Gear->Hedgehog).Gear = NULL;
                if((*Gear->Hedgehog).King)
                {
                    {
                        (*(*Gear->Hedgehog).Team).hasKing = false;
                        {t = 0;
                         LongWord t__end__ = cMaxHHIndex;
                         if (t <= t__end__) do {
                                                   if((*(*Gear->Hedgehog).Team).Hedgehogs[t].Gear != NULL)
                                                   {
                                                       (*(*(*Gear->Hedgehog).Team).Hedgehogs[t].Gear).Health = 0;
                                                   }
                                                   else
                                                   {
                                                       if((*(*Gear->Hedgehog).Team).Hedgehogs[t].GearHidden != NULL)
                                                       {
                                                           (*(*(*Gear->Hedgehog).Team).Hedgehogs[t].GearHidden).Health = 0;
                                                       }
                                                   }
                                               } while(t++ != t__end__);}
                    }
                }
                if(!(*(*(*Gear->Hedgehog).Team).Clan).Passive)
                {
                    (*(*(*Gear->Hedgehog).Team).Clan).Passive = true;
                    {i = 0;
                     LongWord i__end__ = ((int)((*team->Clan).TeamsNumber) - 1);
                     if (i <= i__end__) do {
                                               {
                                                   if(!(*(*team->Clan).Teams[i]).Passive)
                                                   {
                                                       {t = 0;
                                                        LongWord t__end__ = cMaxHHIndex;
                                                        if (t <= t__end__) do {
                                                                                  if(((*(*team->Clan).Teams[i]).Hedgehogs[t].Gear != NULL) || ((*(*team->Clan).Teams[i]).Hedgehogs[t].GearHidden != NULL))
                                                                                  {
                                                                                      (*(*(*Gear->Hedgehog).Team).Clan).Passive = false;
                                                                                      break;
                                                                                  }
                                                                              } while(t++ != t__end__);}
                                                   }
                                               }
                                               if(!(*(*(*Gear->Hedgehog).Team).Clan).Passive)
                                               {
                                                   break;
                                               }
                                           } while(i++ != i__end__);}
                }
                if((Gear->LastDamage != NULL) && (CurrentHedgehog != NULL))
                {
                    ustats_HedgehogDamaged(Gear, Gear->LastDamage, 0, true);
                }
                else
                {
                    if(CurrentHedgehog != NULL)
                    {
                        ustats_HedgehogDamaged(Gear, CurrentHedgehog, 0, true);
                    }
                }
                ++KilledHHs;
                uteams_RecountTeamHealth(team);
                if(((CurrentHedgehog != NULL) && (CurrentHedgehog->Effects[heResurrectable] != 0)) && ((*(*Gear->Hedgehog).Team).Clan != (*CurrentHedgehog->Team).Clan))
                {
                    {
                        ++(*CurrentHedgehog).Team->stats.AIKills;
                        utextures_FreeAndNilTexture(&((*CurrentHedgehog).Team->AIKillsTex));
                        (*CurrentHedgehog).Team->AIKillsTex = urenderutils_RenderStringTex(fpcrtl_str2astr(uutils_IntToStr((*CurrentHedgehog).Team->stats.AIKills)), (*(*CurrentHedgehog).Team->Clan).Color, fnt16);
                    }
                }
            }
        }
    }
    {
        uutils_AddFileLog(_strconcat(_strconcat(_strconcat(_strappend(_strconcat(_strconcat(_strconcat(_strappend(_strconcat(_strconcat(_strconcat(__str9, uutils_IntToStr((*Gear).uid)), __str4), uutils_IntToStr(ufloat_hwRound((*Gear).X))), 0x2c), uutils_IntToStr(ufloat_hwRound((*Gear).Y))), __str5), uutils_FloatToStr((*Gear).dX)), 0x2c), uutils_FloatToStr((*Gear).dY)), __str6), uutils_EnumToStr_1((*Gear).Kind)));
        urandom_AddRandomness((((((((*Gear).X.Round ^ (*Gear).X.Frac) ^ (*Gear).dX.Round) ^ (*Gear).dX.Frac) ^ (*Gear).Y.Round) ^ (*Gear).Y.Frac) ^ (*Gear).dY.Round) ^ (*Gear).dY.Frac);
    }
    if(CurAmmoGear == Gear)
    {
        CurAmmoGear = NULL;
    }
    if(FollowGear == Gear)
    {
        FollowGear = NULL;
    }
    if(lastGearByUID == Gear)
    {
        lastGearByUID = NULL;
    }
    if((Gear->Hedgehog == NULL) || ((*Gear->Hedgehog).GearHidden != Gear))
    {
        ugearslist_RemoveGearFromList(Gear);
    }
    else
    {
        (*Gear->Hedgehog).GearHidden = NULL;
    }
    fpcrtl_dispose(Gear);
};
