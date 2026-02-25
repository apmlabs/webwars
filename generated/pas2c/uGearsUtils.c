#include "fpcrtl.h"

#include "uGearsUtils.h"
doStepHandlers_tt doStepHandlers;
#include "uSound.h"
#include "uCollisions.h"
#include "uUtils.h"
#include "uConsts.h"
#include "uVisualGears.h"
#include "uAIMisc.h"
#include "uVariables.h"
#include "uLandGraphics.h"
#include "uScript.h"
#include "uStats.h"
#include "uCaptions.h"
#include "uTeams.h"
#include "uStore.h"
#include "uLocale.h"
#include "uTextures.h"
#include "uRenderUtils.h"
#include "uRandom.h"
#include "SDLh.h"
#include "uDebug.h"
#include "uGearsList.h"
#include "Math.h"
#include "uVisualGearsList.h"
#include "uGearsHandlersMess.h"
#include "uGearsHedgehog.h"
#include "uLandUtils.h"
static const string255 __str9 = STRINIT("FindPlace: No place found, deleting Gear");
static const string255 __str8 = STRINIT("FindPlace: No place found, deleting hog");
static const string255 __str7 = STRINIT("FindPlace: Picked alternative spot for hog at coordinates (");
static const string255 __str6 = STRINIT("FindPlace: Can't find place for Gear");
static const string255 __str5 = STRINIT("FindPlace: Assigned Gear coordinates (");
static const string255 __str4 = STRINIT("onGearResurrect");
static const string255 __str3 = STRINIT("onGearWaterSkip");
static const string255 __str2 = STRINIT("onGearDamage");
static const string255 __str1 = STRINIT("fr_tomato");
static const string255 __str0 = STRINIT("Explosion: at (");
void ugearsutils_doMakeExplosion_5(LongInt X,LongInt Y,LongInt Radius,PHedgehog AttackingHog,LongWord Mask)
{
    ugearsutils_doMakeExplosion_6(X, Y, Radius, AttackingHog, Mask, 0xffffffff);
};
void ugearsutils_doMakeExplosion_6(LongInt X,LongInt Y,LongInt Radius,PHedgehog AttackingHog,LongWord Mask,LongWord Tint)
{
    PGear Gear;
    LongInt dmg;
    LongInt dmgBase;
    hwFloat fX;
    hwFloat fY;
    hwFloat tdX;
    hwFloat tdY;
    PVisualGear vg;
    LongInt i;
    LongInt cnt;
    boolean wrap;
    PVisualGear bubble;
    astring s;
    if(Radius > 4)
    {
        uutils_AddFileLog(_strappend(_strconcat(_strappend(_strconcat(__str0, uutils_IntToStr(X)), 0x2c), uutils_IntToStr(Y)), 0x29));
    }
    if(Radius > 25)
    {
        uvisualgears_KickFlakes(Radius, X, Y);
    }
    if((Mask & EXPLNoGfx) == 0)
    {
        vg = NULL;
        if(ucollisions_CheckCoordInWater(X, Y - Radius))
        {
            cnt = 2 * Radius;
            {i = (Radius * Radius) / 4;
             LongInt i__end__ = 0;
             if (i >= i__end__) do {
                                       bubble = uvisualgearslist_AddVisualGear_3((X - Radius) + fpcrtl_random(cnt), (Y - Radius) + fpcrtl_random(cnt), vgtBubble);
                                       if(bubble != NULL)
                                       {
                                           bubble->dY = 0.1 + (fpcrtl_random(20) /(float) 10);
                                       }
                                   } while(i-- != i__end__);}
        }
        else
        {
            if(Radius > 50)
            {
                vg = uvisualgearslist_AddVisualGear_3(X, Y, vgtBigExplosion);
            }
            else
            {
                if(Radius > 10)
                {
                    vg = uvisualgearslist_AddVisualGear_3(X, Y, vgtExplosion);
                }
            }
        }
        if(vg != NULL)
        {
            vg->Tint = Tint;
        }
    }
    if((Mask & EXPLAutoSound) != 0)
    {
        usound_PlaySound_1(sndExplosion);
    }
    dmgBase = (Radius << 1) + (cHHRadius / 2);
    wrap = false;
    do {
           fX = ufloat_int2hwFloat(X);
           fY = ufloat_int2hwFloat(Y);
           Gear = GearsList;
           while(Gear != NULL)
           {
               dmg = 0;
               if((Gear->State & gstNoDamage) == 0)
               {
                   switch(Gear->Kind)
                   {case gtHedgehog:
                    case gtMine:
                    case gtBall:
                    case gtMelonPiece:
                    case gtGrenade:
                    case gtClusterBomb:
                    case gtSMine:
                    case gtAirMine:
                    case gtCase:
                    case gtTarget:
                    case gtFlame:
                    case gtKnife:
                    case gtExplosives:
                    case gtSentry:{
                                      tdX = ufloat_hwFloat_hwFloat_op_sub(Gear->X, fX);
                                      tdY = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, fY);
                                      if(((LongInt)(tdX.Round + tdY.Round) + 2) < dmgBase)
                                      {
                                          dmg = dmgBase - ufloat_hwRound(ufloat_Distance(tdX, tdY));
                                      }
                                      if(dmg > 1)
                                      {
                                          dmg = ugearsutils_ModifyDamage(uutils_Min(dmg / 2, Radius), Gear);
                                          if((Mask & EXPLNoDamage) == 0)
                                          {
                                              if((Gear->Kind != gtHedgehog) || ((*Gear->Hedgehog).Effects[heInvulnerable] == 0))
                                              {
                                                  ugearsutils_ApplyDamage(Gear, AttackingHog, dmg, dsExplosion);
                                              }
                                              else
                                              {
                                                  Gear->State = Gear->State | gstWinner;
                                              }
                                          }
                                          if(((Mask & EXPLDoNotTouchAny) == 0) && (((Mask & EXPLDoNotTouchHH) == 0) || (Gear->Kind != gtHedgehog)))
                                          {
                                              ucollisions_DeleteCI(Gear);
                                              Gear->dX = ufloat_hwFloat_hwFloat_op_add(Gear->dX, ufloat_hwFloat_hwFloat_op_div(ufloat_SignAs(ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_LongInt_op_mul(_0_005, dmg), cHHKick), tdX), ufloat_hwFloat_hwFloat_op_div(Gear->Density, _3)));
                                              Gear->dY = ufloat_hwFloat_hwFloat_op_add(Gear->dY, ufloat_hwFloat_hwFloat_op_div(ufloat_SignAs(ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_LongInt_op_mul(_0_005, dmg), cHHKick), tdY), ufloat_hwFloat_hwFloat_op_div(Gear->Density, _3)));
                                              Gear->State = (Gear->State | gstMoving) & ~gstLoser;
                                              if(Gear->Kind == gtKnife)
                                              {
                                                  Gear->State = Gear->State & ~gstCollision;
                                              }
                                              if((Gear->Kind == gtHedgehog) && ((*Gear->Hedgehog).Effects[heInvulnerable] == 0))
                                              {
                                                  Gear->State = (Gear->State | gstMoving) & ~(gstHHJumping | gstHHHJump);
                                                  if(!GameOver)
                                                  {
                                                      Gear->State = Gear->State & ~gstWinner;
                                                  }
                                              }
                                              if(Gear->Kind == gtSentry)
                                              {
                                                  Gear->State = Gear->State & ~gstHHJumping;
                                              }
                                              Gear->Active = true;
                                              if(Gear->Kind != gtFlame)
                                              {
                                                  FollowGear = Gear;
                                              }
                                              if(Gear->Kind == gtAirMine)
                                              {
                                                  Gear->Tag = 1;
                                                  Gear->FlightTime = 5000;
                                              }
                                          }
                                          if((((((Mask & EXPLPoisoned) != 0) && (Gear->Kind == gtHedgehog)) && ((*Gear->Hedgehog).Effects[heInvulnerable] == 0)) && ((*Gear->Hedgehog).Effects[heFrozen] == 0)) && ((Gear->State & gstHHDeath) == 0))
                                          {
                                              if((*Gear->Hedgehog).Effects[hePoisoned] == 0)
                                              {
                                                  s = fpcrtl_str2astr((*Gear->Hedgehog).Name);
                                                  ucaptions_AddCaption(ulocale_FormatA_2(ulocale_GetEventString(eidPoisoned), s), capcolDefault, capgrpMessage);
                                                  ustats_HedgehogPoisoned(Gear, AttackingHog);
                                              }
                                              (*Gear->Hedgehog).Effects[hePoisoned] = 5;
                                          }
                                      }
                                  }
                                  break;
                    case gtGrave:if((Mask & EXPLDoNotTouchAny) == 0)
                                 {
                                     tdX = ufloat_hwFloat_hwFloat_op_sub(Gear->X, fX);
                                     tdY = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, fY);
                                     if(((LongInt)(tdX.Round + tdY.Round) + 2) < dmgBase)
                                     {
                                         dmg = dmgBase - ufloat_hwRound(ufloat_Distance(tdX, tdY));
                                     }
                                     if(dmg > 1)
                                     {
                                         dmg = ugearsutils_ModifyDamage(uutils_Min(dmg / 2, Radius), Gear);
                                         Gear->dY = ufloat_hwFloat_LongInt_op_mul(ufloat_hwFloat_op_sub(_0_004), dmg);
                                         Gear->Active = true;
                                     }
                                 }
                                 break;
                    default: break;}
               }
               Gear = Gear->NextGear;
           }
           if((Mask & EXPLDontDraw) == 0)
           {
               if(((GameFlags & gfSolidLand) == 0) || ((Mask & EXPLForceDraw) != 0))
               {
                   cnt = ulandgraphics_DrawExplosion(X, Y, Radius) / 1608;
                   if((cnt > 0) && (SpritesData[sprChunk].Texture != NULL))
                   {
                       {i = 0;
                        LongInt i__end__ = cnt;
                        if (i <= i__end__) do {
                                                  uvisualgearslist_AddVisualGear_3(X, Y, vgtChunk);
                                              } while(i++ != i__end__);}
                   }
               }
           }
           if(WorldEdge == weWrap)
           {
               if(wrap)
               {
                   break;
               }
               if((X + (Radius + 5)) > rightX)
               {
                   X -= playWidth;
                   wrap = true;
               }
               else
               {
                   if((X - (Radius + 5)) < leftX)
                   {
                       X += playWidth;
                       wrap = true;
                   }
               }
           }
       } while(!(!wrap));
    uaimisc_AwareOfExplosion(0, 0, 0);
};
LongWord ugearsutils_ModifyDamage(LongWord dmg,PGear Gear)
{
    LongWord modifydamage_result;
    hwFloat i;
    i = _1;
    if((CurrentHedgehog != NULL) && CurrentHedgehog->King)
    {
        i = _1_5;
    }
    if(((Gear->Kind == gtHedgehog) && (Gear->Hedgehog != NULL)) && ((*Gear->Hedgehog).King || ((*Gear->Hedgehog).Effects[heFrozen] > 0)))
    {
        modifydamage_result = ufloat_hwRound(ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_LongInt_op_mul(ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_LongInt_op_mul(cDamageModifier, dmg), i), cDamagePercent), _0_5), _0_01));
    }
    else
    {
        modifydamage_result = ufloat_hwRound(ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_LongInt_op_mul(ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_LongInt_op_mul(cDamageModifier, dmg), i), cDamagePercent), _0_01));
    }
    return modifydamage_result;
};
void ugearsutils_ApplyDamage(PGear Gear,PHedgehog AttackerHog,LongWord Damage,TDamageSource Source)
{
    LongWord vampDmg;
    LongWord tmpDmg;
    LongWord i;
    PVisualGear vg;
    if(Damage == 0)
    {
        return;
    }
    if(Gear->Kind == gtHedgehog)
    {
        Gear->LastDamage = AttackerHog;
        (*(*(*Gear->Hedgehog).Team).Clan).Flawless = false;
        if((Gear->State & gstHHDeath) == 0)
        {
            ugearsutils_HHHurt(Gear->Hedgehog, Source, Damage);
            uvisualgears_AddDamageTag(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Damage, (*(*(*Gear->Hedgehog).Team).Clan).Color);
        }
        tmpDmg = uutils_Min(Damage, uutils_Max(0, Gear->Health - Gear->Damage));
        if(((Gear != CurrentHedgehog->Gear) && (CurrentHedgehog->Gear != NULL)) && (tmpDmg >= 1))
        {
            if(cVampiric)
            {
                vampDmg = ufloat_hwRound(ufloat_hwFloat_hwFloat_op_mul(ufloat_int2hwFloat(tmpDmg), _0_8));
                if(vampDmg >= 1)
                {
                    vampDmg = ugearsutils_IncHogHealth(CurrentHedgehog, vampDmg);
                    ustore_RenderHealth(&((*CurrentHedgehog)));
                    uteams_RecountTeamHealth(CurrentHedgehog->Team);
                    ugearsutils_HHHeal_4(CurrentHedgehog, vampDmg, true, 0xff0000ff);
                }
            }
            if((((GameFlags & gfKarma) != 0) && ((GameFlags & gfInvulnerable) == 0)) && (CurrentHedgehog->Effects[heInvulnerable] == 0))
            {
                (*CurrentHedgehog->Gear).Karma += tmpDmg;
                (*CurrentHedgehog->Gear).LastDamage = CurrentHedgehog;
                ugearsutils_spawnHealthTagForHH(CurrentHedgehog->Gear, tmpDmg);
            }
        }
        ustats_HedgehogDamaged(Gear, AttackerHog, Damage, false);
        if((AprilOne && (_strcompare((*Gear->Hedgehog).Hat, __str1))) && (Damage > 2))
        {
            {i = 0;
             LongWord i__end__ = fpcrtl_random(uutils_Min(Damage, 20)) + 5;
             if (i <= i__end__) do {
                                       vg = uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtStraightShot);
                                       if(vg != NULL)
                                       {
                                           {
                                               (*vg).dX = 1.0e-3 * (fpcrtl_random(100) + 10);
                                               (*vg).dY = 1.0e-3 * (fpcrtl_random(100) + 10);
                                               (*vg).tdY = -cGravityf;
                                               if(fpcrtl_random(2) == 0)
                                               {
                                                   (*vg).dX = -(*vg).dX;
                                               }
                                               (*vg).FrameTicks = fpcrtl_random(500) + 1000;
                                               (*vg).State = (sprBubbles);
                                               (*vg).Tint = 0xff0000ff;
                                           }
                                       }
                                   } while(i++ != i__end__);}
        }
    }
    else
    {
        if(AttackerHog != NULL)
        {
            Gear->Hedgehog = AttackerHog;
        }
    }
    Gear->Damage += Damage;
    uscript_ScriptCall_3(__str2, Gear->uid, Damage);
};
void ugearsutils_spawnHealthTagForHH(PGear HHGear,LongWord dmg)
{
    PVisualGear tag;
    tag = uvisualgearslist_AddVisualGear_4(ufloat_hwRound(HHGear->X), ufloat_hwRound(HHGear->Y), vgtHealthTag, dmg);
    if(tag != NULL)
    {
        tag->Hedgehog = HHGear->Hedgehog;
    }
    AllInactive = false;
    HHGear->Active = true;
};
void ugearsutils_HHHurt(PHedgehog Hedgehog,TDamageSource Source,LongWord Damage)
{
    if(Hedgehog->Effects[heFrozen] != 0)
    {
        return;
    }
    if(((Damage >= ouchDmg) && (OuchTauntTimer == 0)) && ((((Source == dsFall) || (Source == dsBullet)) || (Source == dsShove)) || (Source == dsHammer)))
    {
        usound_PlaySoundV_2(sndOuch, (*Hedgehog->Team).voicepack);
        OuchTauntTimer = 1250;
    }
    else
    {
        if((Source == dsFall) || (Source == dsExplosion))
        {
            switch(fpcrtl_random(3))
            {case 0:usound_PlaySoundV_2(sndOoff1, (*Hedgehog->Team).voicepack);
                    break;
             case 1:usound_PlaySoundV_2(sndOoff2, (*Hedgehog->Team).voicepack);
                    break;
             case 2:usound_PlaySoundV_2(sndOoff3, (*Hedgehog->Team).voicepack);
                    break;
             default: break;}
        }
        else
        {
            if(Source == dsPoison)
            {
                switch(fpcrtl_random(2))
                {case 0:usound_PlaySoundV_2(sndPoisonCough, (*Hedgehog->Team).voicepack);
                        break;
                 case 1:usound_PlaySoundV_2(sndPoisonMoan, (*Hedgehog->Team).voicepack);
                        break;
                 default: break;}
            }
            else
            {
                switch(fpcrtl_random(4))
                {case 0:usound_PlaySoundV_2(sndOw1, (*Hedgehog->Team).voicepack);
                        break;
                 case 1:usound_PlaySoundV_2(sndOw2, (*Hedgehog->Team).voicepack);
                        break;
                 case 2:usound_PlaySoundV_2(sndOw3, (*Hedgehog->Team).voicepack);
                        break;
                 case 3:usound_PlaySoundV_2(sndOw4, (*Hedgehog->Team).voicepack);
                        break;
                 default: break;}
            }
        }
    }
};
void ugearsutils_HHHeal_4(PHedgehog Hedgehog,LongInt healthBoost,boolean showMessage,LongWord vgTint)
{
    LongInt i;
    PVisualGear vg;
    astring s;
    if(healthBoost < 1)
    {
        return;
    }
    if(showMessage)
    {
        s = fpcrtl_str2astr(uutils_IntToStr(healthBoost));
        ucaptions_AddCaption(ulocale_FormatA_2(trmsg[sidHealthGain], s), (*(*Hedgehog->Team).Clan).Color, capgrpAmmoinfo);
    }
    i = 0;
    if(vgTint != 0)
    {
        while((i < healthBoost) && (i < 1000))
        {
            vg = uvisualgearslist_AddVisualGear_3(ufloat_hwRound((*Hedgehog->Gear).X), ufloat_hwRound((*Hedgehog->Gear).Y), vgtStraightShot);
            if(vg != NULL)
            {
                {
                    (*vg).Tint = vgTint;
                    (*vg).State = (sprHealth);
                }
            }
            i += 5;
        }
    }
};
void ugearsutils_HHHeal_3(PHedgehog Hedgehog,LongInt healthBoost,boolean showMessage)
{
    ugearsutils_HHHeal_4(Hedgehog, healthBoost, showMessage, 0x00ff00ff);
};
LongInt ugearsutils_IncHogHealth(PHedgehog Hedgehog,LongInt healthBoost)
{
    LongInt inchoghealth_result;
    LongInt oldHealth;
    if(healthBoost < 1)
    {
        inchoghealth_result = 0;
        return inchoghealth_result;
    }
    oldHealth = (*Hedgehog->Gear).Health;
    (*Hedgehog->Gear).Health += healthBoost;
    if(((*Hedgehog->Gear).Health < 1) || ((*Hedgehog->Gear).Health > cMaxHogHealth))
    {
        (*Hedgehog->Gear).Health = cMaxHogHealth;
    }
    inchoghealth_result = (*Hedgehog->Gear).Health - oldHealth;
    return inchoghealth_result;
};
void ugearsutils_CheckHHDamage(PGear Gear)
{
    LongInt dmg;
    LongWord i;
    PVisualGear particle;
    if(ufloat_hwFloat_hwFloat_op_lt(_0_4, Gear->dY))
    {
        dmg = ugearsutils_ModifyDamage(1 + ufloat_hwRound(ufloat_hwFloat_LongInt_op_mul(ufloat_hwFloat_hwFloat_op_sub(Gear->dY, _0_4), 70)), Gear);
        if((*Gear->Hedgehog).Effects[heFrozen] == 0)
        {
            usound_PlaySound_1(sndBump);
        }
        else
        {
            usound_PlaySound_1(sndFrozenHogImpact);
        }
        if(dmg < 1)
        {
            return;
        }
        {i = uutils_Min(12, 3 + (dmg / 10));
         LongWord i__end__ = 0;
         if (i >= i__end__) do {
                                   particle = uvisualgearslist_AddVisualGear_3((ufloat_hwRound(Gear->X) - 5) + fpcrtl_random(10), ufloat_hwRound(Gear->Y) + 12, vgtDust);
                                   if(particle != NULL)
                                   {
                                       particle->dX = particle->dX + (Gear->dX.QWordValue /(float) 21474836480);
                                   }
                               } while(i-- != i__end__);}
        if((*Gear->Hedgehog).Effects[heInvulnerable] != 0)
        {
            return;
        }
        if(Gear->LastDamage != NULL)
        {
            ugearsutils_ApplyDamage(Gear, Gear->LastDamage, dmg, dsFall);
        }
        else
        {
            ugearsutils_ApplyDamage(Gear, CurrentHedgehog, dmg, dsFall);
        }
    }
};
void ugearsutils_CalcRotationDirAngle(PGear Gear)
{
    real dAngle;
    dAngle = ((Gear->dX.Round + Gear->dY.Round) /(float) 2) + ((Gear->dX.Frac /(float) 0x100000000) + (Gear->dY.Frac /(float) 0x100000000));
    if(!Gear->dX.isNegative)
    {
        Gear->DirAngle = Gear->DirAngle + dAngle;
    }
    else
    {
        Gear->DirAngle = Gear->DirAngle - dAngle;
    }
    if(Gear->DirAngle < 0)
    {
        Gear->DirAngle = Gear->DirAngle + 360;
    }
    else
    {
        if(360 < Gear->DirAngle)
        {
            Gear->DirAngle = Gear->DirAngle - 360;
        }
    }
};
void ugearsutils_AddSplashForGear(PGear Gear,boolean justSkipping)
{
    LongInt x;
    LongInt y;
    LongInt i;
    LongInt distL;
    LongInt distR;
    LongInt distB;
    LongInt minDist;
    LongInt maxDrops;
    PVisualGear splash;
    PVisualGear particle;
    hwFloat speed;
    hwFloat hwTmp;
    real vi;
    real vs;
    real tmp;
    boolean isImpactH;
    boolean isImpactRight;
    enum{dist2surf = 4};
    x = ufloat_hwRound(Gear->X);
    y = ufloat_hwRound(Gear->Y);
    distB = cWaterLine - y;
    if(WorldEdge != weSea)
    {
        minDist = distB;
    }
    else
    {
        distL = x - leftX;
        distR = rightX - x;
        minDist = uutils_Min(distB, uutils_Min(distL, distR));
    }
    isImpactH = minDist != distB;
    if(!isImpactH)
    {
        y = cWaterLine - dist2surf;
        speed = ufloat_hwAbs(Gear->dY);
    }
    else
    {
        isImpactRight = minDist == distR;
        if(isImpactRight)
        {
            x = rightX - dist2surf;
        }
        else
        {
            x = leftX + dist2surf;
        }
        speed = ufloat_hwAbs(Gear->dX);
    }
    if(justSkipping)
    {
        usound_PlaySound_1(sndSkip);
    }
    else
    {
        hwTmp = ufloat_hwAbs(ufloat_hwFloat_hwFloat_op_mul(Gear->Density, speed));
        if(ufloat_hwFloat_hwFloat_op_gt(hwTmp, _1))
        {
            usound_PlaySound_1(sndSplash);
        }
        else
        {
            if(ufloat_hwFloat_hwFloat_op_gt(hwTmp, _0_5))
            {
                usound_PlaySound_1(sndSkip);
            }
            else
            {
                if(ufloat_hwFloat_hwFloat_op_gt(hwTmp, _0_0002))
                {
                    usound_PlaySound_1(sndDroplet2);
                }
            }
        }
    }
    if((cReducedQuality & rqPlainSplash) != 0)
    {
        return;
    }
    splash = uvisualgearslist_AddVisualGear_3(x, y, vgtSplash);
    if(splash == NULL)
    {
        return;
    }
    if(!isImpactH)
    {
        vs = fpcrtl_abs(ufloat_hwFloat2Float(Gear->dX));
    }
    else
    {
        if(isImpactRight)
        {
            splash->Angle = -90;
        }
        else
        {
            splash->Angle = 90;
        }
        vs = fpcrtl_abs(ufloat_hwFloat2Float(Gear->dY));
    }
    vi = ufloat_hwFloat2Float(speed);
    {
        (*splash).scale = fpcrtl_abs(ufloat_hwFloat2Float(ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_div(Gear->Density, _3), speed)));
        if((*splash).scale > 1)
        {
            (*splash).scale = fpcrtl_power((*splash).scale, 0.3333);
        }
        else
        {
            (*splash).scale = (*splash).scale + ((1 - (*splash).scale) /(float) 2);
        }
        if((*splash).scale > 1)
        {
            (*splash).Timer = fpcrtl_round(uutils_Min(((*splash).scale * 5.0e-4) /(float) cGravityf, 4));
        }
        else
        {
            (*splash).Timer = 1;
        }
        if((*splash).scale > 1)
        {
            if(!isImpactH)
            {
                (*splash).Y = (*splash).Y + 10;
            }
            else
            {
                if(isImpactRight)
                {
                    (*splash).X = (*splash).X + 10;
                }
                else
                {
                    (*splash).X = (*splash).X - 10;
                }
            }
        }
        (*splash).FrameTicks = (*splash).FrameTicks * (*splash).Timer;
    }
    maxDrops = ((ufloat_hwRound(Gear->Density) * 3) / 2) + fpcrtl_round(((vi + vs) * ufloat_hwRound(Gear->Density)) * 6);
    {i = uutils_Max(maxDrops / 3, uutils_Min(32, fpcrtl_random(maxDrops)));
     LongInt i__end__ = 0;
     if (i >= i__end__) do {
                               if(isImpactH)
                               {
                                   particle = uvisualgearslist_AddVisualGear_3(x, (y - 3) + fpcrtl_random(7), vgtDroplet);
                               }
                               else
                               {
                                   particle = uvisualgearslist_AddVisualGear_3((x - 3) + fpcrtl_random(7), y, vgtDroplet);
                               }
                               if(particle != NULL)
                               {
                                   {
                                       if(isImpactH)
                                       {
                                           tmp = (*particle).dX;
                                           if(isImpactRight)
                                           {
                                               (*particle).dX = (*particle).dY - (vi /(float) 5);
                                           }
                                           else
                                           {
                                               (*particle).dX = -(*particle).dY + (vi /(float) 5);
                                           }
                                           (*particle).dY = tmp * (1 + (vs /(float) 10));
                                       }
                                       else
                                       {
                                           (*particle).dX = (*particle).dX * (1 + (vs /(float) 10));
                                           (*particle).dY = (*particle).dY - (vi /(float) 5);
                                       }
                                       if(splash != NULL)
                                       {
                                           if(splash->scale > 1)
                                           {
                                               (*particle).dX = (*particle).dX * fpcrtl_power(splash->scale, 0.3333);
                                               (*particle).dY = (*particle).dY * fpcrtl_power(splash->scale, 0.3333);
                                           }
                                           else
                                           {
                                               (*particle).dX = (*particle).dX * splash->scale;
                                               (*particle).dY = (*particle).dY * splash->scale;
                                           }
                                       }
                                   }
                               }
                           } while(i-- != i__end__);}
};
void ugearsutils_DrownGear(PGear Gear)
{
    Gear->doStep = &(ugearshandlersmess_doStepDrowningGear);
    Gear->Timer = 5000;
};
boolean ugearsutils_CheckGearDrowning(PGear (*Gear))
{
    boolean checkgeardrowning_result;
    hwFloat skipSpeed;
    hwFloat skipAngle;
    hwFloat skipDecay;
    LongInt tmp;
    LongInt X;
    LongInt Y;
    LongInt dist2Water;
    boolean isSubmersible;
    boolean isDirH;
    boolean isImpact;
    boolean isSkip;
    astring s;
    X = ufloat_hwRound((*Gear)->X);
    Y = ufloat_hwRound((*Gear)->Y);
    dist2Water = cWaterLine - (Y + (*Gear)->Radius);
    isDirH = false;
    if(WorldEdge == weSea)
    {
        tmp = dist2Water;
        dist2Water = uutils_Min(dist2Water, uutils_Min((X - (*Gear)->Radius) - leftX, rightX - (X + (*Gear)->Radius)));
        isDirH = tmp != dist2Water;
    }
    isImpact = false;
    if(dist2Water < 0)
    {
        if(((*Gear)->State & gstInvisible) != 0)
        {
            if((*Gear)->Kind == gtGenericFaller)
            {
                (*Gear)->X = ufloat_int2hwFloat(urandom_GetRandom(rightX - leftX) + leftX);
                (*Gear)->Y = ufloat_int2hwFloat(urandom_GetRandom(LAND_HEIGHT - topY) + topY);
                (*Gear)->dX = ufloat_hwFloat_hwFloat_op_sub(_90, ufloat_hwFloat_hwFloat_op_mul(urandom_GetRandomf(), _360));
                (*Gear)->dY = ufloat_hwFloat_hwFloat_op_sub(_90, ufloat_hwFloat_hwFloat_op_mul(urandom_GetRandomf(), _360));
            }
            else
            {
                ugearslist_DeleteGear((*Gear));
            }
            return true;
        }
        isSubmersible = ((((*Gear) == CurrentHedgehog->Gear) && (CurAmmoGear != NULL)) && ((CurAmmoGear->State & gstSubmersible) != 0)) || (((*Gear)->State & gstSubmersible) != 0);
        skipSpeed = _0_25;
        skipAngle = _1_9;
        skipDecay = _0_87;
        if((!isSubmersible && (ufloat_hwFloat_hwFloat_op_gt(ufloat_hwFloat_hwFloat_op_add(ufloat_hwSqr((*Gear)->dX), ufloat_hwSqr((*Gear)->dY)), skipSpeed))) && ((!isDirH && (ufloat_hwFloat_hwFloat_op_gt(ufloat_hwAbs((*Gear)->dX), ufloat_hwFloat_hwFloat_op_mul(skipAngle, ufloat_hwAbs((*Gear)->dY))))) || (isDirH && (ufloat_hwFloat_hwFloat_op_gt(ufloat_hwAbs((*Gear)->dY), ufloat_hwFloat_hwFloat_op_mul(skipAngle, ufloat_hwAbs((*Gear)->dX)))))))
        {
            isSkip = true;
            if(isDirH)
            {
                (*Gear)->dX.isNegative = !(*Gear)->dX.isNegative;
                (*Gear)->X = ufloat_hwFloat_hwFloat_op_add((*Gear)->X, (*Gear)->dX);
            }
            else
            {
                (*Gear)->dY.isNegative = !(*Gear)->dY.isNegative;
                (*Gear)->Y = ufloat_hwFloat_hwFloat_op_add((*Gear)->Y, (*Gear)->dY);
            }
            (*Gear)->dY = ufloat_hwFloat_hwFloat_op_mul((*Gear)->dY, skipDecay);
            (*Gear)->dX = ufloat_hwFloat_hwFloat_op_mul((*Gear)->dX, skipDecay);
            checkgeardrowning_result = false;
        }
        else
        {
            isImpact = true;
            isSkip = false;
            if(!isSubmersible)
            {
                checkgeardrowning_result = true;
                (*Gear)->State = gstDrowning;
                if((*Gear) == CurrentHedgehog->Gear)
                {
                    TurnTimeLeft = 0;
                }
                (*Gear)->RenderTimer = false;
                if((((((*Gear)->Kind != gtSniperRifleShot) && ((*Gear)->Kind != gtShotgunShot)) && ((*Gear)->Kind != gtDEagleShot)) && ((*Gear)->Kind != gtSineGunShot)) && ((*Gear)->Kind != gtMinigunBullet))
                {
                    if((*Gear)->Kind == gtHedgehog)
                    {
                        if((*(*Gear)->Hedgehog).Effects[heResurrectable] != 0)
                        {
                            ugearsutils_ResurrectHedgehog(&((*Gear)));
                            return true;
                        }
                        else
                        {
                            ugearsutils_DrownGear((*Gear));
                            (*Gear)->State = (*Gear)->State & ~gstHHDriven;
                            s = fpcrtl_str2astr((*(*Gear)->Hedgehog).Name);
                            if((*(*Gear)->Hedgehog).King)
                            {
                                ucaptions_AddCaption(ulocale_FormatA_2(ulocale_GetEventString(eidKingDied), s), capcolDefault, capgrpMessage);
                            }
                            else
                            {
                                ucaptions_AddCaption(ulocale_FormatA_2(ulocale_GetEventString(eidDrowned), s), capcolDefault, capgrpMessage);
                            }
                        }
                    }
                    else
                    {
                        ugearsutils_DrownGear((*Gear));
                    }
                }
                if((*Gear)->Kind == gtFlake)
                {
                    return true;
                }
            }
            else
            {
                if(Y > (cWaterLine + (cVisibleWater * 4)))
                {
                    ugearsutils_DrownGear((*Gear));
                    return true;
                }
                checkgeardrowning_result = false;
                if(((dist2Water + ((*Gear)->Radius / 2)) < 0) || (fpcrtl_abs(dist2Water + (*Gear)->Radius) >= (*Gear)->Radius))
                {
                    isImpact = false;
                }
                else
                {
                    if(isDirH)
                    {
                        tmp = ufloat_hwRound(ufloat_hwFloat_hwFloat_op_sub((*Gear)->X, (*Gear)->dX));
                        if(fpcrtl_abs(tmp - ((real)leftX)) < fpcrtl_abs(tmp - ((real)rightX)))
                        {
                            isImpact = (fpcrtl_abs(tmp - ((real)leftX)) >= (*Gear)->Radius) && (*Gear)->dX.isNegative;
                        }
                        else
                        {
                            isImpact = (fpcrtl_abs(tmp - ((real)rightX)) >= (*Gear)->Radius) && !(*Gear)->dX.isNegative;
                        }
                    }
                    else
                    {
                        tmp = ufloat_hwRound(ufloat_hwFloat_hwFloat_op_sub((*Gear)->Y, (*Gear)->dY));
                        tmp = fpcrtl_abs(cWaterLine - tmp);
                        isImpact = (tmp >= (*Gear)->Radius) && !(*Gear)->dY.isNegative;
                    }
                }
            }
        }
        if(isImpact || isSkip)
        {
            if(!(((dist2Water + ((*Gear)->Radius / 2)) < 0) || (fpcrtl_abs(dist2Water + (*Gear)->Radius) >= (*Gear)->Radius)))
            {
                ugearsutils_AddSplashForGear((*Gear), isSkip);
            }
        }
        if(isSkip)
        {
            uscript_ScriptCall_2(__str3, (*Gear)->uid);
        }
    }
    else
    {
        checkgeardrowning_result = false;
    }
    return checkgeardrowning_result;
};
void ugearsutils_ResurrectHedgehog(PGear (*gear))
{
    PTeam tempTeam;
    PVisualGear sparkles;
    PVisualGear expl;
    LongInt gX;
    LongInt gY;
    if((*gear)->LastDamage != NULL)
    {
        ustats_HedgehogDamaged((*gear), (*gear)->LastDamage, 0, true);
    }
    else
    {
        ustats_HedgehogDamaged((*gear), CurrentHedgehog, 0, true);
    }
    AttackBar = 0;
    (*gear)->dX = _0;
    (*gear)->dY = _0;
    (*gear)->Damage = 0;
    (*gear)->Health = (*(*gear)->Hedgehog).InitialHealth;
    (*(*gear)->Hedgehog).Effects[hePoisoned] = 0;
    if((CurrentHedgehog->Effects[heResurrectable] == 0) || ((CurrentHedgehog->Effects[heResurrectable] != 0) && ((*(*(*gear)->Hedgehog).Team).Clan != (*CurrentHedgehog->Team).Clan)))
    {
        {
            ++(*CurrentHedgehog).Team->stats.AIKills;
            utextures_FreeAndNilTexture(&((*CurrentHedgehog).Team->AIKillsTex));
            (*CurrentHedgehog).Team->AIKillsTex = urenderutils_RenderStringTex(fpcrtl_str2astr(uutils_IntToStr((*CurrentHedgehog).Team->stats.AIKills)), (*(*CurrentHedgehog).Team->Clan).Color, fnt16);
        }
    }
    tempTeam = (*(*gear)->Hedgehog).Team;
    ucollisions_DeleteCI((*gear));
    gX = ufloat_hwRound((*gear)->X);
    gY = ufloat_hwRound((*gear)->Y);
    sparkles = uvisualgearslist_AddVisualGear_4(gX, gY, vgtDust, 1);
    if(sparkles != NULL)
    {
        sparkles->Tint = ((*tempTeam->Clan).Color << 8) | 0xff;
    }
    ugearsutils_FindPlace_5(&((*gear)), false, 0, LAND_WIDTH, true);
    if((*gear) != NULL)
    {
        expl = uvisualgearslist_AddVisualGear_3(ufloat_hwRound((*gear)->X), ufloat_hwRound((*gear)->Y), vgtExplosion);
        usound_PlaySound_1(sndWarp);
        ustore_RenderHealth(&((*(*gear)->Hedgehog)));
        if(expl != NULL)
        {
            uscript_ScriptCall_3(__str4, (*gear)->uid, expl->uid);
        }
        else
        {
            uscript_ScriptCall_2(__str4, (*gear)->uid);
        }
        (*gear)->State = gstWait;
    }
    uteams_RecountTeamHealth(tempTeam);
};
LongInt ugearsutils_CountLand(LongInt x,LongInt y,LongInt r,LongInt c,LongWord mask,LongWord antimask)
{
    LongInt countland_result;
    LongInt i;
    LongInt count = 0;
    if((y & LAND_HEIGHT_MASK) == 0)
    {
        {i = uutils_Max(x - r, 0);
         LongInt i__end__ = uutils_Min(x + r, LAND_WIDTH - 1);
         if (i <= i__end__) do {
                                   if(((ulandutils_LandGet(y, i) & mask) != 0) && ((ulandutils_LandGet(y, i) & antimask) == 0))
                                   {
                                       ++count;
                                       if(count == c)
                                       {
                                           countland_result = count;
                                           return countland_result;
                                       }
                                   }
                               } while(i++ != i__end__);}
    }
    countland_result = count;
    return countland_result;
};
boolean ugearsutils_isSteadyPosition(LongInt x,LongInt y,LongInt r,LongInt c,LongWord mask)
{
    boolean issteadyposition_result;
    LongInt cnt;
    LongInt i;
    cnt = 0;
    issteadyposition_result = false;
    if((((y & LAND_HEIGHT_MASK) == 0) && ((x - r) >= 0)) && ((x + r) < LAND_WIDTH))
    {
        {i = (r - c) + 2;
         LongInt i__end__ = r;
         if (i <= i__end__) do {
                                   if((ulandutils_LandGet(y, x - i) & mask) != 0)
                                   {
                                       ++cnt;
                                   }
                                   if((ulandutils_LandGet(y, x + i) & mask) != 0)
                                   {
                                       ++cnt;
                                   }
                                   if(cnt >= c)
                                   {
                                       issteadyposition_result = true;
                                       return issteadyposition_result;
                                   }
                               } while(i++ != i__end__);}
    }
    return issteadyposition_result;
};
boolean ugearsutils_NoGearsToAvoid(LongInt mX,LongInt mY,LongInt rX,LongInt rY)
{
    boolean nogearstoavoid_result;
    PGear t;
    nogearstoavoid_result = false;
    t = GearsList;
    rX = fpcrtl_sqr(rX);
    rY = fpcrtl_sqr(rY);
    while(t != NULL)
    {
        if(t->Kind <= gtExplosives)
        {
            if(!(ufloat_hwFloat_hwFloat_op_gt(ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_LongInt_op_div(ufloat_hwSqr(ufloat_hwFloat_hwFloat_op_sub(ufloat_int2hwFloat(mX), t->X)), rX), ufloat_hwFloat_LongInt_op_div(ufloat_hwSqr(ufloat_hwFloat_hwFloat_op_sub(ufloat_int2hwFloat(mY), t->Y)), rY)), _1)))
            {
                return nogearstoavoid_result;
            }
        }
        t = t->NextGear;
    }
    nogearstoavoid_result = true;
    return nogearstoavoid_result;
};
void ugearsutils_FindPlace_4(PGear (*Gear),boolean withFall,LongInt Left,LongInt Right)
{
    ugearsutils_FindPlace_6(&((*Gear)), withFall, Left, Right, false, true);
};
void ugearsutils_FindPlace_5(PGear (*Gear),boolean withFall,LongInt Left,LongInt Right,boolean skipProximity)
{
    ugearsutils_FindPlace_6(&((*Gear)), withFall, Left, Right, skipProximity, true);
};
inline void ugearsutils_FindPlace_6(PGear (*Gear),boolean withFall,LongInt Left,LongInt Right,boolean skipProximity,boolean deleteOnFail)
{
    ugearsutils_FindPlace_7(&((*Gear)), withFall, Left, Right, cWaterLine, skipProximity, deleteOnFail);
};
void ugearsutils_FindPlace_7(PGear (*Gear),boolean withFall,LongInt Left,LongInt Right,LongInt Bottom,boolean skipProximity,boolean deleteOnFail)
{
    LongInt x;
    LongInt y;
    LongInt sy;
    LongInt dir;
    typedef TPoint ar_tt[(1023 + 1)];
    ar_tt ar;
    typedef TPoint ar2_tt[(2047 + 1)];
    ar2_tt ar2;
    TPoint temp;
    LongWord cnt;
    LongWord cnt2;
    LongInt delta;
    boolean ignoreNearObjects;
    boolean ignoreOverlap;
    boolean tryAgain;
    ignoreNearObjects = false;
    ignoreOverlap = false;
    tryAgain = true;
    if(WorldEdge != weNone)
    {
        Left = uutils_Max(Left, leftX + (*Gear)->Radius);
        Right = uutils_Min(Right, rightX - (*Gear)->Radius);
    }
    while(tryAgain)
    {
        delta = LAND_WIDTH / 16;
        cnt2 = 0;
        do {
               if(urandom_GetRandom(2) == 0)
               {
                   dir = -1;
               }
               else
               {
                   dir = 1;
               }
               x = uutils_Max(LAND_WIDTH / 2048, ((LongInt)urandom_GetRandom(delta)));
               if(dir == 1)
               {
                   x = Left + x;
               }
               else
               {
                   x = Right - x;
               }
               do {
                      cnt = 0;
                      y = uutils_Min(1024, topY) - ((*Gear)->Radius << 1);
                      while(y < Bottom)
                      {
                          do {
                                 y += 2;
                             } while(!(((y >= Bottom) || (ignoreOverlap && (ugearsutils_CountLand(x, y, (*Gear)->Radius - 1, 1, lfLandMask, 0) == 0))) || (!ignoreOverlap && (ugearsutils_CountLand(x, y, (*Gear)->Radius - 1, 1, lfAll, 0) == 0))));
                          sy = y;
                          do {
                                 ++y;
                             } while(!(((y >= Bottom) || (ignoreOverlap && (ugearsutils_CountLand(x, y, (*Gear)->Radius - 1, 1, lfAll, 0) != 0))) || (!ignoreOverlap && (ugearsutils_CountLand(x, y, (*Gear)->Radius - 1, 1, lfLandMask, 0) != 0))));
                          if((((y - sy) > ((*Gear)->Radius * 2)) && (y < Bottom)) && (((((*Gear)->Kind == gtExplosives) && (ignoreNearObjects || ugearsutils_NoGearsToAvoid(x, y - (*Gear)->Radius, 60, 60))) && (ugearsutils_isSteadyPosition(x, y + 1, (*Gear)->Radius - 1, 3, lfAll) || (ugearsutils_CountLand(x, y + 1, (*Gear)->Radius - 1, (*Gear)->Radius + 1, lfAll, 0) > (*Gear)->Radius))) || ((((*Gear)->Kind != gtExplosives) && (ignoreNearObjects || ugearsutils_NoGearsToAvoid(x, y - (*Gear)->Radius, 110, 110))) && (ugearsutils_isSteadyPosition(x, y + 1, (*Gear)->Radius - 1, 3, lfIce) || (ugearsutils_CountLand(x, y + 1, (*Gear)->Radius - 1, (*Gear)->Radius + 1, lfAll, lfIce) != 0)))))
                          {
                              ar[cnt].x = x;
                              if(withFall)
                              {
                                  ar[cnt].y = sy + (*Gear)->Radius;
                              }
                              else
                              {
                                  ar[cnt].y = y - (*Gear)->Radius;
                              }
                              ++cnt;
                          }
                          y += 10;
                      }
                      if(cnt > 0)
                      {
                          temp = ar[urandom_GetRandom(cnt)];
                          {
                              ar2[cnt2].x = temp.x;
                              ar2[cnt2].y = temp.y;
                              ++cnt2;
                          }
                      }
                      x += delta * dir;
                  } while(!(((dir == 1) && (x > Right)) || ((dir == -1) && (x < Left))));
               delta -= 60;
           } while(!((cnt2 > 0) || (delta < 70)));
        if(((cnt2 == 0) && skipProximity) && !ignoreOverlap)
        {
            tryAgain = true;
        }
        else
        {
            tryAgain = false;
        }
        if(ignoreNearObjects)
        {
            ignoreOverlap = true;
        }
        ignoreNearObjects = true;
    }
    if(cnt2 > 0)
    {
        temp = ar2[urandom_GetRandom(cnt2)];
        {
            (*Gear)->X = ufloat_int2hwFloat(temp.x);
            (*Gear)->Y = ufloat_int2hwFloat(temp.y);
            uutils_AddFileLog(_strappend(_strconcat(_strappend(_strconcat(__str5, uutils_IntToStr(temp.x)), 0x2c), uutils_IntToStr(temp.y)), 0x29));
        }
    }
    else
    {
        udebug_OutError(__str6, false);
        if((*Gear)->Kind == gtHedgehog)
        {
            cnt = 0;
            if(GameTicks == 0)
            {
                while(cnt < 1000)
                {
                    ++cnt;
                    x = (Left + urandom_GetRandom((Right - Left) - (2 * cHHRadius))) + cHHRadius;
                    y = (topY + urandom_GetRandom((LAND_HEIGHT - topY) - 64)) + 48;
                    if(ugearsutils_NoGearsToAvoid(x, y, 100 / uutils_Max(1, cnt / 100), 100 / uutils_Max(1, cnt / 100)))
                    {
                        (*Gear)->State = (*Gear)->State | gsttmpFlag;
                        (*Gear)->X = ufloat_int2hwFloat(x);
                        (*Gear)->Y = ufloat_int2hwFloat(y);
                        uutils_AddFileLog(_strappend(_strconcat(_strappend(_strconcat(__str7, uutils_IntToStr(ufloat_hwRound((*Gear)->X))), 0x2c), uutils_IntToStr(ufloat_hwRound((*Gear)->Y))), 0x29));
                        cnt = 2000;
                    }
                }
            }
            if(deleteOnFail && (cnt < 2000))
            {
                uutils_AddFileLog(__str8);
                (*(*Gear)->Hedgehog).Effects[heResurrectable] = 0;
                ugearslist_DeleteGear((*Gear));
                (*Gear) = NULL;
            }
        }
        else
        {
            if(deleteOnFail)
            {
                uutils_AddFileLog(__str9);
                ugearslist_DeleteGear((*Gear));
                (*Gear) = NULL;
            }
        }
    }
};
PGear ugearsutils_CheckGearNearImpl(TGearType Kind,hwFloat X,hwFloat Y,LongInt rX,LongInt rY,PGear exclude)
{
    PGear checkgearnearimpl_result;
    PGear t;
    hwFloat width;
    hwFloat dX;
    hwFloat dY;
    boolean isHit;
    LongWord i;
    LongWord j;
    LongWord bound;
    bound = (uutils_Max(rX, rY) * 3) / 2;
    rX = fpcrtl_sqr(rX);
    rY = fpcrtl_sqr(rY);
    width = ufloat_int2hwFloat(rightX - leftX);
    if(Kind == gtHedgehog)
    {
        {j = 0;
         LongWord j__end__ = ((int)(TeamsCount) - 1);
         if (j <= j__end__) do {
                                   if(TeamsArray[j]->TeamHealth > 0)
                                   {
                                       {
                                           {i = 0;
                                            LongWord i__end__ = cMaxHHIndex;
                                            if (i <= i__end__) do {
                                                                      {
                                                                          if((!(*TeamsArray[j]).Hedgehogs[i].Unplaced && ((*TeamsArray[j]).Hedgehogs[i].Gear != NULL)) && ((*TeamsArray[j]).Hedgehogs[i].Gear != exclude))
                                                                          {
                                                                              dX = ufloat_hwFloat_hwFloat_op_sub(X, (*TeamsArray[j]).Hedgehogs[i].Gear->X);
                                                                              dY = ufloat_hwFloat_hwFloat_op_sub(Y, (*TeamsArray[j]).Hedgehogs[i].Gear->Y);
                                                                              isHit = ((dX.Round + dY.Round) < bound) && !(ufloat_hwFloat_hwFloat_op_gt(ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_LongInt_op_div(ufloat_hwSqr(dX), rX), ufloat_hwFloat_LongInt_op_div(ufloat_hwSqr(dY), rY)), _1));
                                                                              if(!isHit && (WorldEdge == weWrap))
                                                                              {
                                                                                  if(((ufloat_hwFloat_hwFloat_op_sub(dX, width).Round + dY.Round) < bound) && !(ufloat_hwFloat_hwFloat_op_gt(ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_LongInt_op_div(ufloat_hwSqr(ufloat_hwFloat_hwFloat_op_sub(dX, width)), rX), ufloat_hwFloat_LongInt_op_div(ufloat_hwSqr(dY), rY)), _1)))
                                                                                  {
                                                                                      isHit = true;
                                                                                  }
                                                                                  else
                                                                                  {
                                                                                      if(((ufloat_hwFloat_hwFloat_op_add(dX, width).Round + dY.Round) < bound) && !(ufloat_hwFloat_hwFloat_op_gt(ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_LongInt_op_div(ufloat_hwSqr(ufloat_hwFloat_hwFloat_op_add(dX, width)), rX), ufloat_hwFloat_LongInt_op_div(ufloat_hwSqr(dY), rY)), _1)))
                                                                                      {
                                                                                          isHit = true;
                                                                                      }
                                                                                  }
                                                                              }
                                                                              if(isHit)
                                                                              {
                                                                                  checkgearnearimpl_result = (*TeamsArray[j]).Hedgehogs[i].Gear;
                                                                                  return checkgearnearimpl_result;
                                                                              }
                                                                          }
                                                                      }
                                                                  } while(i++ != i__end__);}
                                       }
                                   }
                               } while(j++ != j__end__);}
    }
    else
    {
        t = GearsList;
        while(t != NULL)
        {
            if((t != exclude) && (t->Kind == Kind))
            {
                dX = ufloat_hwFloat_hwFloat_op_sub(X, t->X);
                dY = ufloat_hwFloat_hwFloat_op_sub(Y, t->Y);
                isHit = ((dX.Round + dY.Round) < bound) && !(ufloat_hwFloat_hwFloat_op_gt(ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_LongInt_op_div(ufloat_hwSqr(dX), rX), ufloat_hwFloat_LongInt_op_div(ufloat_hwSqr(dY), rY)), _1));
                if(!isHit && (WorldEdge == weWrap))
                {
                    if(((ufloat_hwFloat_hwFloat_op_sub(dX, width).Round + dY.Round) < bound) && !(ufloat_hwFloat_hwFloat_op_gt(ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_LongInt_op_div(ufloat_hwSqr(ufloat_hwFloat_hwFloat_op_sub(dX, width)), rX), ufloat_hwFloat_LongInt_op_div(ufloat_hwSqr(dY), rY)), _1)))
                    {
                        isHit = true;
                    }
                    else
                    {
                        if(((ufloat_hwFloat_hwFloat_op_add(dX, width).Round + dY.Round) < bound) && !(ufloat_hwFloat_hwFloat_op_gt(ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_LongInt_op_div(ufloat_hwSqr(ufloat_hwFloat_hwFloat_op_add(dX, width)), rX), ufloat_hwFloat_LongInt_op_div(ufloat_hwSqr(dY), rY)), _1)))
                        {
                            isHit = true;
                        }
                    }
                }
                if(isHit)
                {
                    checkgearnearimpl_result = t;
                    return checkgearnearimpl_result;
                }
            }
            t = t->NextGear;
        }
    }
    checkgearnearimpl_result = NULL;
    return checkgearnearimpl_result;
};
PGear ugearsutils_CheckGearNear_5(TGearType Kind,hwFloat X,hwFloat Y,LongInt rX,LongInt rY)
{
    PGear checkgearnear_result;
    checkgearnear_result = ugearsutils_CheckGearNearImpl(Kind, X, Y, rX, rY, NULL);
    return checkgearnear_result;
};
PGear ugearsutils_CheckGearNear_4(PGear Gear,TGearType Kind,LongInt rX,LongInt rY)
{
    PGear checkgearnear_result;
    checkgearnear_result = ugearsutils_CheckGearNearImpl(Kind, Gear->X, Gear->Y, rX, rY, Gear);
    return checkgearnear_result;
};
void ugearsutils_CheckCollision(PGear Gear)
{
    if((ucollisions_TestCollisionXwithGear(Gear, ufloat_hwSign(Gear->dX)) != 0) || (ucollisions_TestCollisionYwithGear(Gear, ufloat_hwSign(Gear->dY)) != 0))
    {
        Gear->State = Gear->State | gstCollision;
    }
    else
    {
        Gear->State = Gear->State & ~gstCollision;
    }
};
void ugearsutils_CheckCollisionWithLand(PGear Gear)
{
    if((ucollisions_TestCollisionX(Gear, ufloat_hwSign(Gear->dX)) != 0) || (ucollisions_TestCollisionY(Gear, ufloat_hwSign(Gear->dY)) != 0))
    {
        Gear->State = Gear->State | gstCollision;
    }
    else
    {
        Gear->State = Gear->State & ~gstCollision;
    }
};
boolean ugearsutils_MakeHedgehogsStep(PGear Gear)
{
    boolean makehedgehogsstep_result;
    if(ucollisions_TestCollisionXwithGear(Gear, ufloat_hwSign(Gear->dX)) != 0)
    {
        if(ucollisions_TestCollisionYwithGear(Gear, -1) == 0)
        {
            Gear->Y = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, _1);
            if(ucollisions_TestCollisionXwithGear(Gear, ufloat_hwSign(Gear->dX)) != 0)
            {
                if(ucollisions_TestCollisionYwithGear(Gear, -1) == 0)
                {
                    Gear->Y = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, _1);
                    if(ucollisions_TestCollisionXwithGear(Gear, ufloat_hwSign(Gear->dX)) != 0)
                    {
                        if(ucollisions_TestCollisionYwithGear(Gear, -1) == 0)
                        {
                            Gear->Y = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, _1);
                            if(ucollisions_TestCollisionXwithGear(Gear, ufloat_hwSign(Gear->dX)) != 0)
                            {
                                if(ucollisions_TestCollisionYwithGear(Gear, -1) == 0)
                                {
                                    Gear->Y = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, _1);
                                    if(ucollisions_TestCollisionXwithGear(Gear, ufloat_hwSign(Gear->dX)) != 0)
                                    {
                                        if(ucollisions_TestCollisionYwithGear(Gear, -1) == 0)
                                        {
                                            Gear->Y = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, _1);
                                            if(ucollisions_TestCollisionXwithGear(Gear, ufloat_hwSign(Gear->dX)) != 0)
                                            {
                                                if(ucollisions_TestCollisionYwithGear(Gear, -1) == 0)
                                                {
                                                    Gear->Y = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, _1);
                                                    if(ucollisions_TestCollisionXwithGear(Gear, ufloat_hwSign(Gear->dX)) != 0)
                                                    {
                                                        Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _6);
                                                    }
                                                }
                                                else
                                                {
                                                    Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _5);
                                                }
                                            }
                                            else
                                            {
                                                ;
                                            }
                                        }
                                        else
                                        {
                                            Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _4);
                                        }
                                    }
                                    else
                                    {
                                        ;
                                    }
                                }
                                else
                                {
                                    Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _3);
                                }
                            }
                            else
                            {
                                ;
                            }
                        }
                        else
                        {
                            Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _2);
                        }
                    }
                    else
                    {
                        ;
                    }
                }
                else
                {
                    Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _1);
                }
            }
        }
    }
    if(ucollisions_TestCollisionXwithGear(Gear, ufloat_hwSign(Gear->dX)) == 0)
    {
        Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, ufloat_SignAs(_1, Gear->dX));
        makehedgehogsstep_result = true;
    }
    else
    {
        makehedgehogsstep_result = false;
    }
    if(ucollisions_TestCollisionYwithGear(Gear, 1) == 0)
    {
        Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _1);
        if(ucollisions_TestCollisionYwithGear(Gear, 1) == 0)
        {
            Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _1);
            if(ucollisions_TestCollisionYwithGear(Gear, 1) == 0)
            {
                Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _1);
                if(ucollisions_TestCollisionYwithGear(Gear, 1) == 0)
                {
                    Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _1);
                    if(ucollisions_TestCollisionYwithGear(Gear, 1) == 0)
                    {
                        Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _1);
                        if(ucollisions_TestCollisionYwithGear(Gear, 1) == 0)
                        {
                            Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _1);
                            if(ucollisions_TestCollisionYwithGear(Gear, 1) == 0)
                            {
                                Gear->Y = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, _6);
                                Gear->dY = _0;
                                Gear->State = Gear->State | gstMoving;
                                return makehedgehogsstep_result;
                            }
                        }
                    }
                }
            }
        }
    }
    return makehedgehogsstep_result;
};
void ugearsutils_ShotgunShot(PGear Gear)
{
    PGear t;
    LongInt dmg;
    LongInt r;
    LongInt dist;
    hwFloat dx;
    hwFloat dy;
    Gear->Radius = cShotgunRadius;
    t = GearsList;
    while(t != NULL)
    {
        switch(t->Kind)
        {case gtHedgehog:
         case gtMine:
         case gtSMine:
         case gtAirMine:
         case gtKnife:
         case gtCase:
         case gtTarget:
         case gtExplosives:
         case gtSentry:{
                           dmg = 0;
                           r = Gear->Radius + t->Radius;
                           dx = ufloat_hwFloat_hwFloat_op_sub(Gear->X, t->X);
                           dx.isNegative = false;
                           dy = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, t->Y);
                           dy.isNegative = false;
                           if((r - ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(dx, dy))) > 0)
                           {
                               dist = ufloat_hwRound(ufloat_Distance(dx, dy));
                               dmg = ugearsutils_ModifyDamage(uutils_Min(r - dist, Gear->Boom), t);
                           }
                           if(dmg > 0)
                           {
                               if((t->Kind != gtHedgehog) || ((*t->Hedgehog).Effects[heInvulnerable] == 0))
                               {
                                   ugearsutils_ApplyDamage(t, Gear->Hedgehog, dmg, dsBullet);
                               }
                               else
                               {
                                   Gear->State = Gear->State | gstWinner;
                               }
                               ucollisions_DeleteCI(t);
                               t->dX = ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_add(t->dX, ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_LongInt_op_mul(Gear->dX, dmg), _0_01)), ufloat_SignAs(cHHKick, Gear->dX));
                               t->dY = ufloat_hwFloat_hwFloat_op_add(t->dY, ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_LongInt_op_mul(Gear->dY, dmg), _0_01));
                               t->State = t->State | gstMoving;
                               if(t->Kind == gtKnife)
                               {
                                   t->State = t->State & ~gstCollision;
                               }
                               t->Active = true;
                               FollowGear = t;
                               if(t->Kind == gtAirMine)
                               {
                                   t->Tag = 1;
                                   t->FlightTime = 5000;
                               }
                           }
                       }
                       break;
         case gtGrave:{
                          dmg = 0;
                          r = Gear->Radius + t->Radius;
                          dx = ufloat_hwFloat_hwFloat_op_sub(Gear->X, t->X);
                          dx.isNegative = false;
                          dy = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, t->Y);
                          dy.isNegative = false;
                          if((r - ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(dx, dy))) > 0)
                          {
                              dist = ufloat_hwRound(ufloat_Distance(dx, dy));
                              dmg = ugearsutils_ModifyDamage(uutils_Min(r - dist, Gear->Boom), t);
                          }
                          if(dmg > 0)
                          {
                              t->dY = ufloat_hwFloat_op_sub(_0_1);
                              t->Active = true;
                          }
                      }
                      break;
         default: break;}
        t = t->NextGear;
    }
    if((GameFlags & gfSolidLand) == 0)
    {
        ulandgraphics_DrawExplosion(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), cShotgunRadius);
    }
};
LongInt ugearsutils_CountHogsInTeam(PGear HHGear,boolean countHidden)
{
    LongInt counthogsinteam_result;
    LongInt i;
    LongInt j;
    LongInt cnt;
    PHedgehog HH;
    if(HHGear == NULL)
    {
        return 0;
    }
    HH = HHGear->Hedgehog;
    cnt = 0;
    {j = 0;
     LongInt j__end__ = ((int)((*(*HH->Team).Clan).TeamsNumber) - 1);
     if (j <= j__end__) do {
                               {i = 0;
                                LongInt i__end__ = ((int)((*(*(*HH->Team).Clan).Teams[j]).HedgehogsNumber) - 1);
                                if (i <= i__end__) do {
                                                          if((((*(*(*HH->Team).Clan).Teams[j]).Hedgehogs[i].Gear != NULL) && (((*(*(*(*HH->Team).Clan).Teams[j]).Hedgehogs[i].Gear).State & gstDrowning) == 0)) && ((*(*(*(*HH->Team).Clan).Teams[j]).Hedgehogs[i].Gear).Health > (*(*(*(*HH->Team).Clan).Teams[j]).Hedgehogs[i].Gear).Damage))
                                                          {
                                                              ++cnt;
                                                          }
                                                          else
                                                          {
                                                              if(countHidden && ((*(*(*HH->Team).Clan).Teams[j]).Hedgehogs[i].GearHidden != NULL))
                                                              {
                                                                  ++cnt;
                                                              }
                                                          }
                                                      } while(i++ != i__end__);}
                           } while(j++ != j__end__);}
    counthogsinteam_result = cnt;
    return counthogsinteam_result;
};
boolean ugearsutils_CanUseTardis(PGear HHGear)
{
    boolean canusetardis_result;
    boolean usable;
    LongInt cnt;
    PHedgehog HH;
    usable = true;
    HH = HHGear->Hedgehog;
    if(HHGear != NULL)
    {
        if(((HHGear == NULL) || HH->King) || SuddenDeathActive)
        {
            usable = false;
        }
    }
    cnt = ugearsutils_CountHogsInTeam(HHGear, false);
    if(cnt < 2)
    {
        usable = false;
    }
    canusetardis_result = usable;
    return canusetardis_result;
};
void ugearsutils_AmmoShoveImpl(PGear Ammo,LongInt Damage,LongInt Power,PGearArray collisions)
{
    PGearArray t;
    PGear Gear;
    LongInt i;
    LongInt j;
    LongInt tmpDmg;
    PVisualGear VGear;
    t = collisions;
    if(((((CurAmmoGear != NULL) && (((CurAmmoGear->Kind == gtRope) || (CurAmmoGear->Kind == gtJetpack)) || (CurAmmoGear->Kind == gtBirdy))) && (CurrentHedgehog->Gear != NULL)) && ((*CurrentHedgehog->Gear).CollisionIndex == -1)) && ((fpcrtl_sqr(ufloat_hwRound(Ammo->X) - ufloat_hwRound((*CurrentHedgehog->Gear).X)) + fpcrtl_sqr(ufloat_hwRound(Ammo->Y) - ufloat_hwRound((*CurrentHedgehog->Gear).Y))) <= fpcrtl_sqr(cHHRadius + Ammo->Radius)))
    {
        t->ar[t->Count] = CurrentHedgehog->Gear;
        ++t->Count;
    }
    i = t->Count;
    if((Ammo->Kind == gtFlame) && (i > 0))
    {
        Ammo->Health = 0;
    }
    while(i > 0)
    {
        --i;
        Gear = t->ar[i];
        if((((Ammo->Kind == gtDEagleShot) || (Ammo->Kind == gtSniperRifleShot) || (Ammo->Kind == gtMinigunBullet) || (Ammo->Kind == gtFirePunch) || (Ammo->Kind == gtKamikaze) || (Ammo->Kind == gtWhip) || (Ammo->Kind == gtShover))) && (((Ammo->Data != NULL) && (((PGear)Ammo->Data) == Gear)) || !ucollisions_UpdateHitOrder_3(Gear, Ammo->WDTimer, (Ammo->Kind == gtMinigunBullet) && (Ammo->Pos != 0))))
        {
            continue;
        }
        if((((Ammo->Kind == gtFlame) || (Ammo->Kind == gtBlowTorch)) && (Gear->Kind == gtHedgehog)) && ((*Gear->Hedgehog).Effects[heFrozen] > 255))
        {
            (*Gear->Hedgehog).Effects[heFrozen] = uutils_Max(255, (*Gear->Hedgehog).Effects[heFrozen] - 10000);
        }
        tmpDmg = ugearsutils_ModifyDamage(Damage, Gear);
        if((Gear->State & gstNoDamage) == 0)
        {
            if(((Gear->Kind == gtHedgehog) && ((Ammo->State & gsttmpFlag) != 0)) && (Ammo->Kind == gtShover))
            {
                Gear->FlightTime = 1;
            }
            switch(Gear->Kind)
            {case gtHedgehog:
             case gtMine:
             case gtAirMine:
             case gtSMine:
             case gtKnife:
             case gtTarget:
             case gtCase:
             case gtExplosives:
             case gtSentry:{
                               if((((Ammo->Kind == gtFirePunch) || (Ammo->Kind == gtKamikaze))) && (Gear->Kind != gtSMine))
                               {
                                   usound_PlaySound_1(sndFirePunchHit);
                               }
                               if(((Ammo->Kind == gtDEagleShot) || (Ammo->Kind == gtSniperRifleShot) || (Ammo->Kind == gtMinigunBullet)))
                               {
                                   VGear = uvisualgearslist_AddVisualGear_3(t->cX[i], t->cY[i], vgtBulletHit);
                                   if(VGear != NULL)
                                   {
                                       VGear->Angle = uutils_DxDy2Angle(ufloat_hwFloat_op_sub(Ammo->dX), Ammo->dY);
                                   }
                               }
                               if(Ammo->Kind == gtDrill)
                               {
                                   Ammo->Timer = 0;
                                   return;
                               }
                               if((Gear->Kind != gtHedgehog) || ((*Gear->Hedgehog).Effects[heInvulnerable] == 0))
                               {
                                   if((Ammo->Kind == gtKnife) && (tmpDmg > 0))
                                   {
                                       {j = 1;
                                        LongInt j__end__ = uutils_Max(1, uutils_Min(3, tmpDmg / 5));
                                        if (j <= j__end__) do {
                                                                  VGear = uvisualgearslist_AddVisualGear_3(t->cX[i] - ((t->cX[i] - ufloat_hwRound(Gear->X)) / 2), t->cY[i] - ((t->cY[i] - ufloat_hwRound(Gear->Y)) / 2), vgtStraightShot);
                                                                  if(VGear != NULL)
                                                                  {
                                                                      {
                                                                          (*VGear).Tint = 0xffcc00ff;
                                                                          (*VGear).Angle = fpcrtl_random(360);
                                                                          (*VGear).dX = 5.0e-4 * fpcrtl_random(100);
                                                                          (*VGear).dY = 5.0e-4 * fpcrtl_random(100);
                                                                          if(fpcrtl_random(2) == 0)
                                                                          {
                                                                              (*VGear).dX = -(*VGear).dX;
                                                                          }
                                                                          if(fpcrtl_random(2) == 0)
                                                                          {
                                                                              (*VGear).dY = -(*VGear).dY;
                                                                          }
                                                                          (*VGear).FrameTicks = 600 + fpcrtl_random(200);
                                                                          (*VGear).State = (sprStar);
                                                                      }
                                                                  }
                                                              } while(j++ != j__end__);}
                                   }
                                   ugearsutils_ApplyDamage(Gear, Ammo->Hedgehog, tmpDmg, dsShove);
                                   if(Gear->Kind == gtAirMine)
                                   {
                                       Gear->Tag = 1;
                                       Gear->FlightTime = 5000;
                                   }
                               }
                               else
                               {
                                   Gear->State = Gear->State | gstWinner;
                               }
                               if((Gear->Kind == gtExplosives) && (Ammo->Kind == gtBlowTorch))
                               {
                                   if((*Ammo->Hedgehog).Gear != NULL)
                                   {
                                       (*(*Ammo->Hedgehog).Gear).State = (*(*Ammo->Hedgehog).Gear).State & ~gstNotKickable;
                                   }
                                   ugearsutils_ApplyDamage(Gear, Ammo->Hedgehog, tmpDmg * 100, dsExplosion);
                               }
                               if((Gear->Kind == gtHedgehog) && ((*Gear->Hedgehog).King || ((*Gear->Hedgehog).Effects[heFrozen] > 0)))
                               {
                                   Gear->dX = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_LongInt_op_mul(Ammo->dX, Power), _0_005);
                                   Gear->dY = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_LongInt_op_mul(Ammo->dY, Power), _0_005);
                               }
                               else
                               {
                                   if(((Ammo->Kind != gtFlame) || (Gear->Kind == gtHedgehog)) && (Power != 0))
                                   {
                                       if(((Ammo->Kind == gtMinigunBullet)))
                                       {
                                           Gear->dX = ufloat_hwFloat_hwFloat_op_add(Gear->dX, ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_LongInt_op_mul(Ammo->dX, Power), _0_01));
                                           Gear->dY = ufloat_hwFloat_hwFloat_op_add(Gear->dY, ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_LongInt_op_mul(Ammo->dY, Power), _0_01));
                                       }
                                       else
                                       {
                                           Gear->dX = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_LongInt_op_mul(Ammo->dX, Power), _0_01);
                                           Gear->dY = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_LongInt_op_mul(Ammo->dY, Power), _0_01);
                                       }
                                   }
                               }
                               if(!ufloat_isZero(Gear->dX) || !ufloat_isZero(Gear->dY))
                               {
                                   Gear->Active = true;
                                   ucollisions_DeleteCI(Gear);
                                   Gear->State = Gear->State | gstMoving;
                                   if(Gear->Kind == gtKnife)
                                   {
                                       Gear->State = Gear->State & ~gstCollision;
                                   }
                                   if(ucollisions_TestCollisionXwithGear(Gear, ufloat_hwSign(Gear->dX)) != 0)
                                   {
                                       if((ucollisions_TestCollisionXwithXYShift_4(Gear, _0, -3, ufloat_hwSign(Gear->dX)) == 0) && (ucollisions_TestCollisionYwithGear(Gear, -1) == 0))
                                       {
                                           Gear->Y = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, _1);
                                       }
                                       if((ucollisions_TestCollisionXwithXYShift_4(Gear, _0, -2, ufloat_hwSign(Gear->dX)) == 0) && (ucollisions_TestCollisionYwithGear(Gear, -1) == 0))
                                       {
                                           Gear->Y = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, _1);
                                       }
                                       if((ucollisions_TestCollisionXwithXYShift_4(Gear, _0, -1, ufloat_hwSign(Gear->dX)) == 0) && (ucollisions_TestCollisionYwithGear(Gear, -1) == 0))
                                       {
                                           Gear->Y = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, _1);
                                       }
                                   }
                               }
                               if((Ammo->Kind != gtFlame) || ((Ammo->State & gsttmpFlag) == 0))
                               {
                                   FollowGear = Gear;
                               }
                           }
                           break;
             default: break;}
        }
    }
    if(i != 0)
    {
        ugearsutils_SetAllToActive();
    }
};
void ugearsutils_AmmoShoveLine(PGear Ammo,LongInt Damage,LongInt Power,hwFloat oX,hwFloat oY,hwFloat tX,hwFloat tY)
{
    PGearArray t;
    t = ucollisions_CheckAllGearsLineCollision(Ammo, oX, oY, tX, tY);
    ugearsutils_AmmoShoveImpl(Ammo, Damage, Power, t);
};
void ugearsutils_AmmoShove(PGear Ammo,LongInt Damage,LongInt Power)
{
    ugearsutils_AmmoShoveImpl(Ammo, Damage, Power, ucollisions_CheckGearsCollision(Ammo));
};
void ugearsutils_AmmoShoveCache(PGear Ammo,LongInt Damage,LongInt Power)
{
    ugearsutils_AmmoShoveImpl(Ammo, Damage, Power, ucollisions_CheckCacheCollision(Ammo));
};
LongWord ugearsutils_CountGears(TGearType Kind)
{
    LongWord countgears_result;
    PGear t;
    LongWord count = 0;
    t = GearsList;
    while(t != NULL)
    {
        if(t->Kind == Kind)
        {
            ++count;
        }
        t = t->NextGear;
    }
    countgears_result = count;
    return countgears_result;
};
void ugearsutils_SetAllToActive()
{
    PGear t;
    AllInactive = false;
    t = GearsList;
    while(t != NULL)
    {
        t->Active = true;
        t = t->NextGear;
    }
};
void ugearsutils_SetAllHHToActive_0()
{
    ugearsutils_SetAllHHToActive_1(true);
};
void ugearsutils_SetAllHHToActive_1(boolean Ice)
{
    PGear t;
    AllInactive = false;
    t = GearsList;
    while(t != NULL)
    {
        if((t->Kind == gtHedgehog) || (t->Kind == gtExplosives))
        {
            if((t->Kind == gtHedgehog) && Ice)
            {
                ugearshedgehog_CheckIce(t);
            }
            t->Active = true;
        }
        t = t->NextGear;
    }
};
static fpcrtl_dimension_t GearsNearArray_dimension_info ={.dim = 0, .a = {0, 0, 0, 0}};
static TPGearArray GearsNearArray = NULL;
PGearArrayS ugearsutils_GearsNear(hwFloat X,hwFloat Y,TGearType Kind,LongInt r)
{
    PGearArrayS gearsnear_result;
    PGear t;
    LongWord s;
    hwFloat xc;
    hwFloat xc_left;
    hwFloat xc_right;
    hwFloat yc;
    r = r * r;
    s = 0;
    fpcrtl_SetLength(GearsNearArray, s);
    t = GearsList;
    while(t != NULL)
    {
        xc = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_sub(X, t->X), ufloat_hwFloat_hwFloat_op_sub(X, t->X));
        xc_left = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_sub(ufloat_hwFloat_hwFloat_op_sub(X, ufloat_int2hwFloat(rightX - leftX)), t->X), ufloat_hwFloat_hwFloat_op_sub(ufloat_hwFloat_hwFloat_op_sub(X, ufloat_int2hwFloat(rightX - leftX)), t->X));
        xc_right = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_sub(ufloat_hwFloat_hwFloat_op_add(X, ufloat_int2hwFloat(rightX - leftX)), t->X), ufloat_hwFloat_hwFloat_op_sub(ufloat_hwFloat_hwFloat_op_add(X, ufloat_int2hwFloat(rightX - leftX)), t->X));
        yc = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_sub(Y, t->Y), ufloat_hwFloat_hwFloat_op_sub(Y, t->Y));
        if((t->Kind == Kind) && ((ufloat_hwFloat_hwFloat_op_lt(ufloat_hwFloat_hwFloat_op_add(xc, yc), ufloat_int2hwFloat(r))) || ((WorldEdge == weWrap) && ((ufloat_hwFloat_hwFloat_op_lt(ufloat_hwFloat_hwFloat_op_add(xc_left, yc), ufloat_int2hwFloat(r))) || (ufloat_hwFloat_hwFloat_op_lt(ufloat_hwFloat_hwFloat_op_add(xc_right, yc), ufloat_int2hwFloat(r)))))))
        {
            ++s;
            fpcrtl_SetLength(GearsNearArray, s);
            GearsNearArray[s - 1] = t;
        }
        t = t->NextGear;
    }
    gearsnear_result.size = s;
    gearsnear_result.ar = &(GearsNearArray);
    return gearsnear_result;
};
PGear ugearsutils_SpawnBoxOfSmth()
{
    PGear spawnboxofsmth_result;
    LongInt t;
    LongInt aTot;
    LongInt uTot;
    LongInt a;
    LongInt h;
    TAmmoType i;
    spawnboxofsmth_result = NULL;
    if((((PlacingHogs || PlacingKings) || (cCaseFactor == 0)) || (ugearsutils_CountGears(gtCase) >= cMaxCaseDrops)) || (urandom_GetRandom(cCaseFactor) != 0))
    {
        return spawnboxofsmth_result;
    }
    FollowGear = NULL;
    aTot = 0;
    uTot = 0;
    {i = 0;
     TAmmoType i__end__ = 60;
     if (i <= i__end__) do {
                               if((Ammoz[i].Ammo.Propz & ammoprop_Utility) == 0)
                               {
                                   aTot += Ammoz[i].Probability;
                               }
                               else
                               {
                                   uTot += Ammoz[i].Probability;
                               }
                           } while(i++ != i__end__);}
    t = 0;
    a = aTot;
    h = 1;
    if((aTot + uTot) != 0)
    {
        if((GameFlags & gfInvulnerable) == 0)
        {
            h = cHealthCaseProb * 100;
            t = urandom_GetRandom(10000);
            a = ((10000 - h) * aTot) / (aTot + uTot);
        }
        else
        {
            t = urandom_GetRandom(aTot + uTot);
            h = 0;
        }
    }
    if(t < h)
    {
        FollowGear = ugearslist_AddGear_7(0, 0, gtCase, 0, _0, _0, 0);
        FollowGear->RenderHealth = true;
        FollowGear->Health = cHealthCaseAmount;
        FollowGear->Pos = posCaseHealth;
        FollowGear->Radius = cCaseHealthRadius;
        ucaptions_AddCaption(ulocale_GetEventString(eidNewHealthPack), capcolDefault, capgrpAmmoinfo);
    }
    else
    {
        if(t < (a + h))
        {
            t = aTot;
            if(t > 0)
            {
                FollowGear = ugearslist_AddGear_7(0, 0, gtCase, 0, _0, _0, 0);
                t = urandom_GetRandom(t);
                i = 0;
                FollowGear->Pos = posCaseAmmo;
                FollowGear->AmmoType = i;
                ucaptions_AddCaption(ulocale_GetEventString(eidNewAmmoPack), capcolDefault, capgrpAmmoinfo);
            }
        }
        else
        {
            t = uTot;
            if(t > 0)
            {
                FollowGear = ugearslist_AddGear_7(0, 0, gtCase, 0, _0, _0, 0);
                t = urandom_GetRandom(t);
                i = 0;
                FollowGear->Pos = posCaseUtility;
                FollowGear->AmmoType = i;
                ucaptions_AddCaption(ulocale_GetEventString(eidNewUtilityPack), capcolDefault, capgrpAmmoinfo);
            }
        }
    }
    if(FollowGear != NULL)
    {
        ugearsutils_FindPlace_4(&(FollowGear), true, 0, LAND_WIDTH);
        ugearsutils_PlayBoxSpawnTaunt(FollowGear);
        spawnboxofsmth_result = FollowGear;
    }
    return spawnboxofsmth_result;
};
void ugearsutils_PlayBoxSpawnTaunt(PGear Gear)
{
    LongInt ThisOneIsMineDistance = 130;
    LongInt d;
    LongInt minD;
    PGear gi;
    PGear closestHog;
    if(Gear != NULL)
    {
        gi = GearsList;
        minD = (LAND_WIDTH + ThisOneIsMineDistance) + 1;
        closestHog = NULL;
        while(gi != NULL)
        {
            if(gi->Kind == gtHedgehog)
            {
                d = ufloat_hwRound(ufloat_hwAbs(ufloat_hwFloat_hwFloat_op_sub(gi->X, Gear->X)));
                if(d < minD)
                {
                    minD = d;
                    closestHog = gi;
                }
            }
            gi = gi->NextGear;
        }
        if(((closestHog != NULL) && (closestHog->Hedgehog != NULL)) && (minD <= ThisOneIsMineDistance))
        {
            if(fpcrtl_random(3) > 0)
            {
                usound_AddVoice_2(sndThisOneIsMine, (*(*closestHog->Hedgehog).Team).voicepack);
            }
            else
            {
                usound_AddVoice_2(sndReinforce, CurrentTeam->voicepack);
            }
        }
        else
        {
            usound_AddVoice_2(sndReinforce, CurrentTeam->voicepack);
        }
    }
};
TAmmoType ugearsutils_GetAmmo(PHedgehog Hedgehog)
{
    TAmmoType getammo_result;
    LongInt t;
    LongInt aTot;
    TAmmoType i;
    UNUSED (Hedgehog);
    aTot = 0;
    {i = 0;
     TAmmoType i__end__ = 60;
     if (i <= i__end__) do {
                               if((Ammoz[i].Ammo.Propz & ammoprop_Utility) == 0)
                               {
                                   aTot += Ammoz[i].Probability;
                               }
                           } while(i++ != i__end__);}
    t = aTot;
    i = 0;
    if(t > 0)
    {
        t = urandom_GetRandom(t);
        while(t >= 0)
        {
            ++i;
            if((Ammoz[i].Ammo.Propz & ammoprop_Utility) == 0)
            {
                t -= Ammoz[i].Probability;
            }
        }
    }
    getammo_result = i;
    return getammo_result;
};
TAmmoType ugearsutils_GetUtility(PHedgehog Hedgehog)
{
    TAmmoType getutility_result;
    LongInt t;
    LongInt uTot;
    TAmmoType i;
    uTot = 0;
    {i = 0;
     TAmmoType i__end__ = 60;
     if (i <= i__end__) do {
                               if(((Ammoz[i].Ammo.Propz & ammoprop_Utility) != 0) && (((*Hedgehog->Team).HedgehogsNumber > 1) || (Ammoz[i].Ammo.AmmoType != amSwitch)))
                               {
                                   uTot += Ammoz[i].Probability;
                               }
                           } while(i++ != i__end__);}
    t = uTot;
    i = 0;
    if(t > 0)
    {
        t = urandom_GetRandom(t);
        while(t >= 0)
        {
            ++i;
            if(((Ammoz[i].Ammo.Propz & ammoprop_Utility) != 0) && (((*Hedgehog->Team).HedgehogsNumber > 1) || (Ammoz[i].Ammo.AmmoType != amSwitch)))
            {
                t -= Ammoz[i].Probability;
            }
        }
    }
    getutility_result = i;
    return getutility_result;
};
boolean ugearsutils_WorldWrap(PGear (*Gear))
{
    boolean worldwrap_result;
    boolean bounced;
    worldwrap_result = false;
    if(WorldEdge == weNone)
    {
        return false;
    }
    if((ufloat_hwRound((*Gear)->X) < leftX) || (ufloat_hwRound((*Gear)->X) > rightX))
    {
        if(WorldEdge == weWrap)
        {
            if(ufloat_hwRound((*Gear)->X) < leftX)
            {
                (*Gear)->X = ufloat_hwFloat_hwFloat_op_add((*Gear)->X, ufloat_int2hwFloat(rightX - leftX));
            }
            else
            {
                (*Gear)->X = ufloat_hwFloat_hwFloat_op_sub((*Gear)->X, ufloat_int2hwFloat(rightX - leftX));
            }
            LeftImpactTimer = 150;
            RightImpactTimer = 150;
            worldwrap_result = true;
        }
        else
        {
            if(WorldEdge == weBounce)
            {
                bounced = false;
                if(((ufloat_hwRound((*Gear)->X) - (*Gear)->Radius) < leftX) && (((ufloat_hwSign((*Gear)->dX) == -1) && !ufloat_isZero((*Gear)->dX)) || ((*Gear)->Kind == gtHedgehog)))
                {
                    LeftImpactTimer = 333;
                    if(((*Gear)->State & gstInBounceEdge) == 0)
                    {
                        (*Gear)->X = ufloat_int2hwFloat(leftX + (*Gear)->Radius);
                    }
                    (*Gear)->dX.isNegative = false;
                    bounced = true;
                }
                else
                {
                    if(((ufloat_hwRound((*Gear)->X) + (*Gear)->Radius) > rightX) && (((ufloat_hwSign((*Gear)->dX) == 1) && !ufloat_isZero((*Gear)->dX)) || ((*Gear)->Kind == gtHedgehog)))
                    {
                        RightImpactTimer = 333;
                        if(((*Gear)->State & gstInBounceEdge) == 0)
                        {
                            (*Gear)->X = ufloat_int2hwFloat(rightX - (*Gear)->Radius);
                        }
                        (*Gear)->dX.isNegative = true;
                        bounced = true;
                    }
                }
                if(((((*Gear)->State & gstInBounceEdge) != 0) && ((ufloat_hwRound((*Gear)->X) - (*Gear)->Radius) >= leftX)) && ((ufloat_hwRound((*Gear)->X) + (*Gear)->Radius) <= rightX))
                {
                    (*Gear)->State = (*Gear)->State & ~gstInBounceEdge;
                }
                if(bounced)
                {
                    worldwrap_result = true;
                    if((*Gear)->dX.QWordValue > _0_001.QWordValue)
                    {
                        ugearsutils_AddBounceEffectForGear_1((*Gear));
                    }
                }
            }
            else
            {
                worldwrap_result = true;
            }
        }
    }
    return worldwrap_result;
};
boolean ugearsutils_HomingWrap(PGear (*Gear))
{
    boolean homingwrap_result;
    hwFloat dist_center;
    hwFloat dist_right;
    hwFloat dist_left;
    homingwrap_result = false;
    if(WorldEdge == weWrap)
    {
        dist_center = ufloat_hwAbs(ufloat_hwFloat_hwFloat_op_sub((*Gear)->X, ufloat_int2hwFloat((*Gear)->Target.x)));
        dist_right = ufloat_hwAbs(ufloat_hwFloat_hwFloat_op_sub((*Gear)->X, ufloat_int2hwFloat((*Gear)->Target.x + (rightX - leftX))));
        dist_left = ufloat_hwAbs(ufloat_hwFloat_hwFloat_op_sub((*Gear)->X, ufloat_int2hwFloat((*Gear)->Target.x - (rightX - leftX))));
        if((ufloat_hwFloat_hwFloat_op_lt(dist_left, dist_right)) && (ufloat_hwFloat_hwFloat_op_lt(dist_left, dist_center)))
        {
            (*Gear)->Target.x -= rightX - leftX;
            homingwrap_result = true;
        }
        else
        {
            if((ufloat_hwFloat_hwFloat_op_lt(dist_right, dist_left)) && (ufloat_hwFloat_hwFloat_op_lt(dist_right, dist_center)))
            {
                (*Gear)->Target.x += rightX - leftX;
                homingwrap_result = true;
            }
        }
    }
    return homingwrap_result;
};
void ugearsutils_AddBounceEffectForGear_1(PGear Gear)
{
    ugearsutils_AddBounceEffectForGear_2(Gear, ufloat_hwFloat2Float(ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_mul(Gear->Density, ufloat_hwAbs(Gear->dY)), ufloat_hwAbs(Gear->dX))) /(float) 1.5);
};
void ugearsutils_AddBounceEffectForGear_2(PGear Gear,single imageScale)
{
    PVisualGear boing;
    if((ufloat_hwFloat_hwFloat_op_lt(Gear->Density, _0_01)) || (Gear->Radius < 2))
    {
        return;
    }
    boing = uvisualgearslist_AddVisualGear_6(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtStraightShot, 0, false, 1);
    if(boing != NULL)
    {
        {
            (*boing).Angle = fpcrtl_random(360);
            (*boing).dX = 0;
            (*boing).dY = 0;
            (*boing).FrameTicks = 200;
            (*boing).scale = imageScale;
            (*boing).State = (sprBoing);
        }
    }
    usound_PlaySound_2(sndMelonImpact, true);
};
boolean ugearsutils_IsHogFacingLeft(PGear Gear)
{
    boolean ishogfacingleft_result;
    LongInt sign;
    sign = ufloat_hwSign(Gear->dX);
    if((CurAmmoGear != NULL) && (CurAmmoGear->Kind == gtParachute))
    {
        ishogfacingleft_result = CurAmmoGear->Tag == -1;
    }
    else
    {
        if(((Gear->State & gstHHHJump) != 0) && ((*Gear->Hedgehog).Effects[heArtillery] == 0))
        {
            ishogfacingleft_result = sign > 0;
        }
        else
        {
            ishogfacingleft_result = sign < 0;
        }
    }
    return ishogfacingleft_result;
};
boolean ugearsutils_IsHogLocal(PHedgehog HH)
{
    boolean ishoglocal_result;
    ishoglocal_result = (!((*HH->Team).ExtDriven || (HH->BotLevel > 0)) || (*(*HH->Team).Clan).LocalOrAlly) || (GameType == gmtDemo);
    return ishoglocal_result;
};
