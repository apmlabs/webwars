#include "fpcrtl.h"

#include "uGearsHedgehog.h"
#include "uConsts.h"
#include "uVariables.h"
#include "uFloat.h"
#include "uAmmos.h"
#include "uSound.h"
#include "uCaptions.h"
#include "uCommands.h"
#include "uLocale.h"
#include "uUtils.h"
#include "uStats.h"
#include "uIO.h"
#include "uScript.h"
#include "uGearsList.h"
#include "uCollisions.h"
#include "uRandom.h"
#include "uStore.h"
#include "uTeams.h"
#include "uGearsUtils.h"
#include "uVisualGearsList.h"
#include "uChat.h"
static const string255 __str5 = STRINIT("onTaunt");
static const string255 __str4 = STRINIT(" (+");
static const string255 __str3 = STRINIT("onHogAttack");
static const string255 __str2 = STRINIT("a");
static const string255 __str1 = STRINIT("");
static const string255 __str0 = STRINIT("/skip");
static LongWord GHStepTicks = 0;
void ugearshedgehog_AFKSkip()
{
    Byte t;
    t = 0;
    while(TeamsArray[t] != CurrentTeam)
    {
        ++t;
    }
    uchat_AddChatString(_strprepend(0x2, ulocale_Format_2(fpcrtl_astr2str(trmsg[sidAutoSkip]), CurrentTeam->TeamName)));
    ucommands_ParseCommand_2(__str0, true);
};
boolean ugearshedgehog_ChangeAmmo(PGear HHGear)
{
    boolean changeammo_result;
    LongWord slot;
    LongWord i;
    LongInt ammoidx;
    TAmmoType prevAmmo;
    changeammo_result = false;
    slot = HHGear->MsgParam;
    {
        HHGear->Message = HHGear->Message & ~gmSlot;
        prevAmmo = (*HHGear->Hedgehog).CurAmmoType;
        ammoidx = 0;
        if((((HHGear->State & (gstAttacking | gstAttacked)) != 0) && ((GameFlags & gfInfAttack) == 0)) || ((HHGear->State & gstHHDriven) == 0))
        {
            return changeammo_result;
        }
        changeammo_result = true;
        while((ammoidx < cMaxSlotAmmoIndex) && ((*(*HHGear->Hedgehog).Ammo)[slot][ammoidx].AmmoType != (*HHGear->Hedgehog).CurAmmoType))
        {
            ++ammoidx;
        }
        if((*HHGear->Hedgehog).MultiShootAttacks > 0)
        {
            if((*HHGear->Hedgehog).Effects[heArtillery] == 2)
            {
                (*HHGear->Hedgehog).Effects[heArtillery] = 0;
            }
            if((Ammoz[(*HHGear->Hedgehog).CurAmmoType].Ammo.Propz & ammoprop_NoRoundEnd) == 0)
            {
                (*HHGear->Hedgehog).MultiShootAttacks = Ammoz[(*HHGear->Hedgehog).CurAmmoType].Ammo.NumPerTurn;
                ugearshedgehog_AfterAttack();
            }
            else
            {
                uammos_OnUsedAmmo(&((*HHGear->Hedgehog)));
            }
        }
        (*HHGear->Hedgehog).MultiShootAttacks = 0;
        HHGear->Message = HHGear->Message & ~(gmLJump | gmHJump);
        if((Ammoz[(*HHGear->Hedgehog).CurAmmoType].Slot) == (slot))
        {
            i = 0;
            do {
                   ++ammoidx;
                   if(ammoidx > cMaxSlotAmmoIndex)
                   {
                       ++i;
                       (*HHGear->Hedgehog).CurAmmoType = amNothing;
                       ammoidx = -1;
                   }
               } while(!((i == 1) || (((*(*HHGear->Hedgehog).Ammo)[slot][ammoidx].Count > 0) && ((*(*HHGear->Hedgehog).Team->Clan).TurnNumber > Ammoz[(*(*HHGear->Hedgehog).Ammo)[slot][ammoidx].AmmoType].SkipTurns))));
        }
        else
        {
            i = 0;
            while((i <= cMaxSlotAmmoIndex) && (((*(*HHGear->Hedgehog).Ammo)[slot][i].Count == 0) || ((*(*HHGear->Hedgehog).Team->Clan).TurnNumber <= Ammoz[(*(*HHGear->Hedgehog).Ammo)[slot][i].AmmoType].SkipTurns)))
            {
                ++i;
            }
            if(i <= cMaxSlotAmmoIndex)
            {
                ammoidx = i;
            }
            else
            {
                ammoidx = -1;
            }
        }
        if(ammoidx >= 0)
        {
            (*HHGear->Hedgehog).CurAmmoType = (*(*HHGear->Hedgehog).Ammo)[slot][ammoidx].AmmoType;
        }
        if(((*HHGear->Hedgehog).CurAmmoType == prevAmmo) && (slot < cMaxSlotIndex))
        {
            ++slot;
            HHGear->MsgParam = slot;
            ugearshedgehog_ChangeAmmo(HHGear);
        }
    }
    return changeammo_result;
};
void ugearshedgehog_HHSetWeapon(PGear HHGear)
{
    LongInt t;
    TAmmoType weap;
    PHedgehog Hedgehog;
    boolean s;
    LongWord prevState;
    LongWord newState;
    s = false;
    weap = ((TAmmoType)HHGear->MsgParam);
    Hedgehog = HHGear->Hedgehog;
    HHGear->Message = HHGear->Message & ~gmWeapon;
    if((*(*Hedgehog->Team).Clan).TurnNumber <= Ammoz[weap].SkipTurns)
    {
        return;
    }
    HHGear->MsgParam = Ammoz[weap].Slot;
    t = cMaxSlotAmmoIndex;
    prevState = HHGear->State;
    newState = prevState;
    {
        while(((*Hedgehog).CurAmmoType != weap) && (t >= 0))
        {
            s = ugearshedgehog_ChangeAmmo(HHGear);
            if(HHGear->State != prevState)
            {
                newState = HHGear->State;
            }
            HHGear->State = prevState;
            --t;
        }
    }
    HHGear->State = newState;
    if(s)
    {
        uammos_ApplyAmmoChanges(&((*HHGear->Hedgehog)));
    }
};
void ugearshedgehog_HHSetTimer(PGear Gear)
{
    PAmmo CurWeapon;
    LongWord color;
    Gear->Message = Gear->Message & ~gmTimer;
    CurWeapon = uammos_GetCurAmmoEntry(&((*Gear->Hedgehog)));
    {
        if(((((*Gear->Hedgehog).Gear->State & gstAttacked) != 0) && ((GameFlags & gfInfAttack) == 0)) || (((*Gear->Hedgehog).Gear->State & gstHHDriven) == 0))
        {
            return;
        }
    }
    if(((Gear->Message & gmPrecise) != 0) && ((CurWeapon->Propz & ammoprop_SetBounce) != 0))
    {
        color = (*(*(*Gear->Hedgehog).Team).Clan).Color;
        switch(Gear->MsgParam)
        {case 1:{
                    ucaptions_AddCaption(ulocale_FormatA_2(trmsg[sidBounce], trmsg[sidBounce1]), color, capgrpAmmostate);
                }
                break;
         case 2:{
                    ucaptions_AddCaption(ulocale_FormatA_2(trmsg[sidBounce], trmsg[sidBounce2]), color, capgrpAmmostate);
                }
                break;
         case 3:{
                    ucaptions_AddCaption(ulocale_FormatA_2(trmsg[sidBounce], trmsg[sidBounce3]), color, capgrpAmmostate);
                }
                break;
         case 4:{
                    ucaptions_AddCaption(ulocale_FormatA_2(trmsg[sidBounce], trmsg[sidBounce4]), color, capgrpAmmostate);
                }
                break;
         case 5:{
                    ucaptions_AddCaption(ulocale_FormatA_2(trmsg[sidBounce], trmsg[sidBounce5]), color, capgrpAmmostate);
                }
                break;
         default: break;}
        CurWeapon->Bounciness = bouncinessLevels[Gear->MsgParam - 1];
    }
    else
    {
        if((CurWeapon->Propz & ammoprop_Timerable) != 0)
        {
            CurWeapon->Timer = 1000 * Gear->MsgParam;
            {
                uammos_ApplyAmmoChanges(&((*CurrentTeam).Hedgehogs[(*CurrentTeam).CurrHedgehog]));
            }
        }
    }
};
LongWord ugearshedgehog_HHGetTimer(PGear Gear)
{
    LongWord hhgettimer_result;
    PAmmo CurWeapon;
    CurWeapon = uammos_GetCurAmmoEntry(&((*Gear->Hedgehog)));
    {
        if((CurWeapon->Propz & ammoprop_Timerable) != 0)
        {
            hhgettimer_result = CurWeapon->Timer;
        }
        else
        {
            hhgettimer_result = MSGPARAM_INVALID;
        }
    }
    return hhgettimer_result;
};
LongWord ugearshedgehog_HHGetTimerMsg(PGear Gear)
{
    LongWord hhgettimermsg_result;
    LongInt timer;
    timer = ugearshedgehog_HHGetTimer(Gear);
    if(timer > -1)
    {
        hhgettimermsg_result = timer / 1000;
    }
    else
    {
        hhgettimermsg_result = MSGPARAM_INVALID;
    }
    return hhgettimermsg_result;
};
LongWord ugearshedgehog_HHGetBounciness(PGear Gear)
{
    LongWord hhgetbounciness_result;
    PAmmo CurWeapon;
    CurWeapon = uammos_GetCurAmmoEntry(&((*Gear->Hedgehog)));
    {
        if((CurWeapon->Propz & ammoprop_SetBounce) != 0)
        {
            hhgetbounciness_result = CurWeapon->Bounciness;
        }
        else
        {
            hhgetbounciness_result = MSGPARAM_INVALID;
        }
    }
    return hhgetbounciness_result;
};
LongWord ugearshedgehog_HHGetBouncinessMsg(PGear Gear)
{
    LongWord hhgetbouncinessmsg_result;
    LongInt bounciness;
    LongInt i;
    bounciness = ugearshedgehog_HHGetBounciness(Gear);
    if(bounciness > -1)
    {
        {i = 0;
         LongInt i__end__ = 4;
         if (i <= i__end__) do {
                                   if(bounciness == bouncinessLevels[i])
                                   {
                                       hhgetbouncinessmsg_result = i + 1;
                                       return hhgetbouncinessmsg_result;
                                   }
                               } while(i++ != i__end__);}
    }
    hhgetbouncinessmsg_result = MSGPARAM_INVALID;
    return hhgetbouncinessmsg_result;
};
void ugearshedgehog_Attack(PGear Gear)
{
    hwFloat xx;
    hwFloat yy;
    hwFloat newDx;
    hwFloat newDy;
    hwFloat lx;
    hwFloat ly;
    PVisualGear speech;
    PGear newGear;
    PAmmo CurWeapon;
    TAmmoType usedAmmoType;
    boolean altUse;
    boolean faceLeft;
    hwFloat elastic;
    newGear = NULL;
    bShowFinger = false;
    CurWeapon = uammos_GetCurAmmoEntry(&((*Gear->Hedgehog)));
    {
        {
            usedAmmoType = (*Gear->Hedgehog).CurAmmoType;
            if((((((*Gear).State & gstHHDriven) != 0) && (((*Gear).State & (gstAttacked | gstChooseTarget)) == 0)) && (((((((*Gear).State & gstMoving) == 0) || ((*Gear).Power > 0)) || ((*Gear->Hedgehog).CurAmmoType == amTeleport)) || ((CurAmmoGear != NULL) && ((Ammoz[CurAmmoGear->AmmoType].Ammo.Propz & ammoprop_AltAttack) != 0))) || ((Ammoz[(*Gear->Hedgehog).CurAmmoType].Ammo.Propz & ammoprop_AttackInMove) != 0))) && ((TargetPoint.x != NoPointX) || ((Ammoz[(*Gear->Hedgehog).CurAmmoType].Ammo.Propz & ammoprop_NeedTarget) == 0)))
            {
                (*Gear).State = (*Gear).State | gstAttacking;
                if(((*Gear).Power == cMaxPower) || ((Ammoz[(*Gear->Hedgehog).CurAmmoType].Ammo.Propz & ammoprop_Power) == 0))
                {
                    (*Gear).Message = (*Gear).Message & ~gmAttack;
                }
                else
                {
                    if((*Gear).Power == 0)
                    {
                        AttackBar = CurrentTeam->AttackBar;
                        usound_PlaySound_1(sndThrowPowerUp);
                    }
                    ++(*Gear).Power;
                }
                if(((*Gear).Message & gmAttack) != 0)
                {
                    return;
                }
                if((Ammoz[(*Gear->Hedgehog).CurAmmoType].Ammo.Propz & ammoprop_Power) != 0)
                {
                    usound_StopSound_1(sndThrowPowerUp);
                    usound_PlaySound_1(sndThrowRelease);
                }
                xx = ufloat_SignAs(ufloat_AngleSin((*Gear).Angle), (*Gear).dX);
                yy = ufloat_hwFloat_op_sub(ufloat_AngleCos((*Gear).Angle));
                lx = ufloat_hwFloat_hwFloat_op_add((*Gear).X, ufloat_int2hwFloat(fpcrtl_round(uutils_GetLaunchX((*Gear->Hedgehog).CurAmmoType, ufloat_hwSign((*Gear).dX), (*Gear).Angle))));
                ly = ufloat_hwFloat_hwFloat_op_add((*Gear).Y, ufloat_int2hwFloat(fpcrtl_round(uutils_GetLaunchY((*Gear->Hedgehog).CurAmmoType, (*Gear).Angle))));
                if((((*Gear->Hedgehog).Gear->State & gstHHHJump) != 0) && ((*Gear->Hedgehog).Effects[heArtillery] == 0))
                {
                    xx = ufloat_hwFloat_op_sub(xx);
                }
                if(Ammoz[(*Gear->Hedgehog).CurAmmoType].Ammo.AttackVoice != sndNone)
                {
                    usound_AddVoice_2(Ammoz[(*Gear->Hedgehog).CurAmmoType].Ammo.AttackVoice, CurrentTeam->voicepack);
                }
                if((((CurAmmoGear != NULL) && ((Ammoz[CurAmmoGear->AmmoType].Ammo.Propz & ammoprop_AltAttack) != 0)) && (((*Gear->Hedgehog).Gear->Message & gmLJump) != 0)) && ((Ammoz[(*Gear->Hedgehog).CurAmmoType].Ammo.Propz & ammoprop_AltUse) != 0))
                {
                    if((CurAmmoGear->AmmoType == amJetpack) && (((*Gear->Hedgehog).Gear->Message & gmPrecise) != 0))
                    {
                        newDx = ufloat_hwFloat_LongInt_op_div(ufloat_hwFloat_LongInt_op_mul(xx, cMaxPower), cPowerDivisor);
                        newDy = ufloat_hwFloat_LongInt_op_div(ufloat_hwFloat_LongInt_op_mul(yy, cMaxPower), cPowerDivisor);
                    }
                    else
                    {
                        newDx = (*Gear).dX;
                        newDy = (*Gear).dY;
                    }
                    altUse = true;
                }
                else
                {
                    newDx = ufloat_hwFloat_LongInt_op_div(ufloat_hwFloat_LongInt_op_mul(xx, (*Gear).Power), cPowerDivisor);
                    newDy = ufloat_hwFloat_LongInt_op_div(ufloat_hwFloat_LongInt_op_mul(yy, (*Gear).Power), cPowerDivisor);
                    altUse = false;
                }
                switch((*Gear->Hedgehog).CurAmmoType)
                {case amGrenade:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtGrenade, 0, newDx, newDy, CurWeapon->Timer);
                                break;
                 case amAirMine:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtAirMine, 0, newDx, newDy, 0);
                                break;
                 case amMolotov:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtMolotov, 0, newDx, newDy, 0);
                                break;
                 case amClusterBomb:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtClusterBomb, 0, newDx, newDy, CurWeapon->Timer);
                                    break;
                 case amGasBomb:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtGasBomb, 0, newDx, newDy, CurWeapon->Timer);
                                break;
                 case amBazooka:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtShell, 0, newDx, newDy, 0);
                                break;
                 case amSnowball:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtSnowball, 0, newDx, newDy, 0);
                                 break;
                 case amBee:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtBee, 0, newDx, newDy, 0);
                            break;
                 case amShotgun:{
                                    usound_PlaySound_1(sndShotgunReload);
                                    newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtShotgunShot, 0, ufloat_hwFloat_hwFloat_op_mul(xx, _0_5), ufloat_hwFloat_hwFloat_op_mul(yy, _0_5), 0);
                                }
                                break;
                 case amPickHammer:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly) + cHHRadius, gtPickHammer, 0, _0, _0, 0);
                                   break;
                 case amSkip:ucommands_ParseCommand_2(__str0, true);
                             break;
                 case amRope:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtRope, 0, xx, yy, 0);
                             break;
                 case amMine:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx) + (ufloat_hwSign((*Gear).dX) * 7), ufloat_hwRound(ly), gtMine, gstWait, ufloat_SignAs(_0_02, (*Gear).dX), _0, 0);
                             break;
                 case amSMine:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtSMine, 0, ufloat_hwFloat_LongInt_op_div(ufloat_hwFloat_LongInt_op_mul(xx, (*Gear).Power), cPowerDivisor), ufloat_hwFloat_LongInt_op_div(ufloat_hwFloat_LongInt_op_mul(yy, (*Gear).Power), cPowerDivisor), 0);
                              break;
                 case amKnife:{
                                  newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtKnife, 0, ufloat_hwFloat_LongInt_op_div(ufloat_hwFloat_LongInt_op_mul(xx, (*Gear).Power), cPowerDivisor), ufloat_hwFloat_LongInt_op_div(ufloat_hwFloat_LongInt_op_mul(yy, (*Gear).Power), cPowerDivisor), 0);
                                  newGear->State = newGear->State | gstMoving;
                                  newGear->Radius = 4;
                              }
                              break;
                 case amDEagle:newGear = ugearslist_AddGear_7(ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(lx, ufloat_hwFloat_LongInt_op_mul(xx, cHHRadius))), ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ly, ufloat_hwFloat_LongInt_op_mul(yy, cHHRadius))), gtDEagleShot, 0, ufloat_hwFloat_hwFloat_op_mul(xx, _0_5), ufloat_hwFloat_hwFloat_op_mul(yy, _0_5), 0);
                               break;
                 case amMinigun:{
                                    usound_PlaySound_1(sndMinigun);
                                    newGear = ugearslist_AddGear_7(ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(lx, ufloat_hwFloat_LongInt_op_mul(xx, cHHRadius))), ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ly, ufloat_hwFloat_LongInt_op_mul(yy, cHHRadius))), gtMinigun, 0, ufloat_hwFloat_hwFloat_op_mul(xx, _0_5), ufloat_hwFloat_hwFloat_op_mul(yy, _0_5), 0);
                                }
                                break;
                 case amSineGun:newGear = ugearslist_AddGear_7(ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(lx, ufloat_hwFloat_LongInt_op_mul(xx, cHHRadius))), ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ly, ufloat_hwFloat_LongInt_op_mul(yy, cHHRadius))), gtSineGunShot, 0, ufloat_hwFloat_hwFloat_op_mul(xx, _0_5), ufloat_hwFloat_hwFloat_op_mul(yy, _0_5), 0);
                                break;
                 case amPortalGun:{
                                      newGear = ugearslist_AddGear_7(ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(lx, ufloat_hwFloat_LongInt_op_mul(xx, cHHRadius))), ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ly, ufloat_hwFloat_LongInt_op_mul(yy, cHHRadius))), gtPortal, 0, ufloat_hwFloat_hwFloat_op_mul(xx, _0_6), ufloat_hwFloat_hwFloat_op_mul(yy, _0_6), CurWeapon->Pos);
                                  }
                                  break;
                 case amSniperRifle:{
                                        usound_PlaySound_1(sndSniperReload);
                                        newGear = ugearslist_AddGear_7(ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(lx, ufloat_hwFloat_LongInt_op_mul(xx, cHHRadius))), ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ly, ufloat_hwFloat_LongInt_op_mul(yy, cHHRadius))), gtSniperRifleShot, 0, ufloat_hwFloat_hwFloat_op_mul(xx, _0_5), ufloat_hwFloat_hwFloat_op_mul(yy, _0_5), 0);
                                    }
                                    break;
                 case amDynamite:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx) + (ufloat_hwSign((*Gear).dX) * 7), ufloat_hwRound(ly), gtDynamite, 0, ufloat_SignAs(_0_03, (*Gear).dX), _0, 5000);
                                 break;
                 case amCreeper:{
                                    if(((leftX > (ufloat_hwRound((*Gear->Hedgehog).Gear->X) - (*Gear->Hedgehog).Gear->Karma)) || (rightX < (ufloat_hwRound((*Gear->Hedgehog).Gear->X) + (*Gear->Hedgehog).Gear->Karma))) || (cWaterLine < (ufloat_hwRound((*Gear->Hedgehog).Gear->Y) + (*Gear->Hedgehog).Gear->Karma)))
                                    {
                                        usound_PlaySound_1(sndDroplet2);
                                    }
                                    else
                                    {
                                        usound_PlaySound_1(sndCreeperDrop);
                                    }
                                    newGear = ugearslist_AddGear_7(ufloat_hwRound(lx) + (ufloat_hwSign((*Gear).dX) * 7), ufloat_hwRound(ly), gtCreeper, 0, ufloat_SignAs(_0_03, (*Gear).dX), _0, 0);
                                    if(!(!(*Gear).dX.isNegative ^ (((*Gear).State & gstHHHJump) != 0)))
                                    {
                                        newGear->Tag = -1;
                                    }
                                    else
                                    {
                                        newGear->Tag = 1;
                                    }
                                }
                                break;
                 case amSentry:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx) + (ufloat_hwSign((*Gear).dX) * 7), ufloat_hwRound(ly), gtSentry, 0, ufloat_SignAs(_0_03, (*Gear).dX), _0, 0);
                               break;
                 case amFirePunch:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx) + (ufloat_hwSign((*Gear).dX) * 10), ufloat_hwRound(ly), gtFirePunch, 0, xx, _0, 0);
                                  break;
                 case amWhip:{
                                 newGear = ugearslist_AddGear_7(ufloat_hwRound(lx) + (ufloat_hwSign((*Gear).dX) * 10), ufloat_hwRound(ly), gtWhip, 0, ufloat_SignAs(_1, (*Gear).dX), ufloat_hwFloat_op_sub(_0_8), 0);
                                 usound_PlaySound_1(sndWhipCrack);
                             }
                             break;
                 case amHammer:{
                                   newGear = ugearslist_AddGear_7(ufloat_hwRound(lx) + (ufloat_hwSign((*Gear).dX) * 10), ufloat_hwRound(ly), gtHammer, 0, ufloat_SignAs(_1, (*Gear).dX), ufloat_hwFloat_op_sub(_0_8), 0);
                                   usound_PlaySound_1(sndWhack);
                               }
                               break;
                 case amBaseballBat:{
                                        newGear = ugearslist_AddGear_7(ufloat_hwRound(lx) + (ufloat_hwSign((*Gear).dX) * 10), ufloat_hwRound(ly), gtShover, gsttmpFlag, ufloat_hwFloat_hwFloat_op_mul(xx, _0_5), ufloat_hwFloat_hwFloat_op_mul(yy, _0_5), 0);
                                        usound_PlaySound_1(sndBaseballBat);
                                    }
                                    break;
                 case amParachute:{
                                      faceLeft = ugearsutils_IsHogFacingLeft((*Gear->Hedgehog).Gear);
                                      newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtParachute, 0, _0, _0, 0);
                                      if(faceLeft)
                                      {
                                          newGear->Tag = -1;
                                      }
                                      usound_PlaySound_1(sndParachute);
                                  }
                                  break;
                 case amAirAttack:newGear = ugearslist_AddGear_7(CurWeapon->Pos, 0, gtAirAttack, 0, _0, _0, 0);
                                  break;
                 case amMineStrike:newGear = ugearslist_AddGear_7(CurWeapon->Pos, 0, gtAirAttack, 1, _0, _0, 0);
                                   break;
                 case amDrillStrike:newGear = ugearslist_AddGear_7(CurWeapon->Pos, 0, gtAirAttack, 3, _0, _0, CurWeapon->Timer);
                                    break;
                 case amNapalm:newGear = ugearslist_AddGear_7(CurWeapon->Pos, 0, gtAirAttack, 2, _0, _0, 0);
                               break;
                 case amBlowTorch:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtBlowTorch, 0, ufloat_SignAs(_0_5, (*Gear).dX), _0, 0);
                                  break;
                 case amGirder:newGear = ugearslist_AddGear_7(0, 0, gtGirder, CurWeapon->Pos, _0, _0, 0);
                               break;
                 case amRubber:{
                                   newGear = ugearslist_AddGear_7(0, 0, gtGirder, CurWeapon->Pos, _0, _0, 0);
                                   newGear->AmmoType = amRubber;
                               }
                               break;
                 case amTeleport:newGear = ugearslist_AddGear_7(CurWeapon->Pos, 0, gtTeleport, 0, _0, _0, 0);
                                 break;
                 case amSwitch:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtSwitcher, 0, _0, _0, 0);
                               break;
                 case amMortar:{
                                   usound_PlaySound_1(sndMortar);
                                   newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtMortar, 0, ufloat_hwFloat_LongInt_op_div(ufloat_hwFloat_LongInt_op_mul(xx, cMaxPower), cPowerDivisor), ufloat_hwFloat_LongInt_op_div(ufloat_hwFloat_LongInt_op_mul(yy, cMaxPower), cPowerDivisor), 0);
                               }
                               break;
                 case amRCPlane:{
                                    newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtRCPlane, 0, ufloat_hwFloat_LongInt_op_div(ufloat_hwFloat_LongInt_op_div(ufloat_hwFloat_LongInt_op_mul(xx, cMaxPower), cPowerDivisor), 4), ufloat_hwFloat_LongInt_op_div(ufloat_hwFloat_LongInt_op_div(ufloat_hwFloat_LongInt_op_mul(yy, cMaxPower), cPowerDivisor), 4), 0);
                                    newGear->SoundChannel = usound_LoopSound_1(sndRCPlane);
                                }
                                break;
                 case amKamikaze:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtKamikaze, 0, ufloat_hwFloat_hwFloat_op_mul(xx, _0_5), ufloat_hwFloat_hwFloat_op_mul(yy, _0_5), 0);
                                 break;
                 case amCake:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx) + (ufloat_hwSign((*Gear).dX) * 3), ufloat_hwRound(ly), gtCake, 0, ufloat_SignAs(cLittle, xx), _0, 0);
                             break;
                 case amSeduction:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtSeduction, 0, _0, _0, 0);
                                  break;
                 case amWatermelon:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtWatermelon, 0, newDx, newDy, CurWeapon->Timer);
                                   break;
                 case amHellishBomb:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtHellishBomb, 0, newDx, newDy, 0);
                                    break;
                 case amDrill:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtDrill, 0, newDx, newDy, 0);
                              break;
                 case amBallgun:newGear = ugearslist_AddGear_7(ufloat_hwRound((*Gear).X), ufloat_hwRound((*Gear).Y), gtBallGun, 0, ufloat_hwFloat_hwFloat_op_mul(xx, _0_5), ufloat_hwFloat_hwFloat_op_mul(yy, _0_5), 0);
                                break;
                 case amJetpack:newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtJetpack, 0, _0, _0, 0);
                                break;
                 case amBirdy:{
                                  usound_PlaySound_1(sndWhistle);
                                  newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly) - 32, gtBirdy, 0, _0, _0, 0);
                              }
                              break;
                 case amLowGravity:{
                                       usound_PlaySound_1(sndLowGravity);
                                       cGravity = cMaxWindSpeed;
                                       cGravityf = 2.5e-4;
                                       cLowGravity = true;
                                   }
                                   break;
                 case amExtraDamage:{
                                        usound_PlaySound_1(sndExtraDamage);
                                        cDamageModifier = _1_5;
                                    }
                                    break;
                 case amInvulnerable:{
                                         usound_PlaySound_1(sndInvulnerable);
                                         (*Gear->Hedgehog).Effects[heInvulnerable] = 1;
                                     }
                                     break;
                 case amExtraTime:{
                                      usound_PlaySound_1(sndExtraTime);
                                      if(TurnTimeLeft <= (cMaxTurnTime - ExtraTime))
                                      {
                                          TurnTimeLeft = TurnTimeLeft + ExtraTime;
                                      }
                                      else
                                      {
                                          TurnTimeLeft = cMaxTurnTime;
                                      }
                                  }
                                  break;
                 case amLaserSight:{
                                       usound_PlaySound_1(sndLaserSight);
                                       cLaserSighting = true;
                                   }
                                   break;
                 case amVampiric:{
                                     usound_PlaySoundV_2(sndOw1, (*Gear->Hedgehog).Team->voicepack);
                                     cVampiric = true;
                                 }
                                 break;
                 case amPiano:newGear = ugearslist_AddGear_7(TargetPoint.x, -1024, gtPiano, 0, _0, _0, 0);
                              break;
                 case amFlamethrower:newGear = ugearslist_AddGear_7(ufloat_hwRound((*Gear).X), ufloat_hwRound((*Gear).Y), gtFlamethrower, 0, ufloat_hwFloat_hwFloat_op_mul(xx, _0_5), ufloat_hwFloat_hwFloat_op_mul(yy, _0_5), 0);
                                     break;
                 case amLandGun:newGear = ugearslist_AddGear_7(ufloat_hwRound((*Gear).X), ufloat_hwRound((*Gear).Y), gtLandGun, 0, ufloat_hwFloat_hwFloat_op_mul(xx, _0_5), ufloat_hwFloat_hwFloat_op_mul(yy, _0_5), 0);
                                break;
                 case amResurrector:{
                                        newGear = ugearslist_AddGear_7(ufloat_hwRound(lx), ufloat_hwRound(ly), gtResurrector, 0, _0, _0, 0);
                                        newGear->SoundChannel = usound_LoopSound_1(sndResurrector);
                                    }
                                    break;
                 case amTardis:newGear = ugearslist_AddGear_7(ufloat_hwRound((*Gear).X), ufloat_hwRound((*Gear).Y), gtTardis, 0, _0, _0, 0);
                               break;
                 case amIceGun:newGear = ugearslist_AddGear_7(ufloat_hwRound((*Gear).X), ufloat_hwRound((*Gear).Y), gtIceGun, 0, _0, _0, 0);
                               break;
                 default: break;}
                if((altUse && (newGear != NULL)) && (((CurAmmoGear == NULL) || (CurAmmoGear->AmmoType != amJetpack)) || (((*Gear->Hedgehog).Gear->Message & gmPrecise) == 0)))
                {
                    newGear->dX = ufloat_hwFloat_hwFloat_op_div(newDx, newGear->Density);
                    newGear->dY = ufloat_hwFloat_hwFloat_op_div(newDy, newGear->Density);
                }
                if((((CurAmmoGear != NULL) && (CurAmmoGear->AmmoType == amJetpack)) && (((*Gear->Hedgehog).Gear->Message & gmPrecise) != 0)) && ucollisions_CheckCoordInWater(ufloat_hwRound((*Gear).X), ufloat_hwRound((*Gear).Y)))
                {
                    newGear->State = newGear->State | gstSubmersible;
                }
                switch((*Gear->Hedgehog).CurAmmoType)
                {case amGrenade:
                 case amMolotov:
                 case amClusterBomb:
                 case amGasBomb:
                 case amBazooka:
                 case amSnowball:
                 case amBee:
                 case amSMine:
                 case amMortar:
                 case amWatermelon:
                 case amHellishBomb:
                 case amDrill:
                 case amAirMine:FollowGear = newGear;
                                break;
                 case amShotgun:
                 case amPickHammer:
                 case amRope:
                 case amDEagle:
                 case amSineGun:
                 case amSniperRifle:
                 case amFirePunch:
                 case amWhip:
                 case amHammer:
                 case amBaseballBat:
                 case amParachute:
                 case amBlowTorch:
                 case amGirder:
                 case amTeleport:
                 case amSwitch:
                 case amRCPlane:
                 case amKamikaze:
                 case amCake:
                 case amSeduction:
                 case amBallgun:
                 case amJetpack:
                 case amBirdy:
                 case amFlamethrower:
                 case amLandGun:
                 case amResurrector:
                 case amTardis:
                 case amPiano:
                 case amIceGun:
                 case amAirAttack:
                 case amNapalm:
                 case amMineStrike:
                 case amDrillStrike:
                 case amRubber:
                 case amMinigun:CurAmmoGear = newGear;
                                break;
                 default: break;}
                if(((*Gear->Hedgehog).CurAmmoType == amCake) || ((*Gear->Hedgehog).CurAmmoType == amPiano))
                {
                    FollowGear = newGear;
                }
                if(((((*Gear->Hedgehog).CurAmmoType == amMine) || ((*Gear->Hedgehog).CurAmmoType == amSMine)) || ((*Gear->Hedgehog).CurAmmoType == amAirMine)) && ((GameFlags & gfInfAttack) != 0))
                {
                    newGear->FlightTime = GameTicks + uutils_Min(TurnTimeLeft, 1000);
                }
                else
                {
                    if((*Gear->Hedgehog).CurAmmoType == amDrill)
                    {
                        newGear->FlightTime = GameTicks + 250;
                    }
                }
                if((Ammoz[(*Gear->Hedgehog).CurAmmoType].Ammo.Propz & ammoprop_NeedTarget) != 0)
                {
                    newGear->Target.x = TargetPoint.x;
                    newGear->Target.y = TargetPoint.y;
                }
                if((newGear != NULL) && ((newGear->CollisionMask & lfCurHogCrate) != 0))
                {
                    newGear->CollisionMask = newGear->CollisionMask & ~lfCurHogCrate;
                }
                if(altUse)
                {
                    FollowGear = NULL;
                }
                if((newGear != NULL) && ((Ammoz[newGear->AmmoType].Ammo.Propz & ammoprop_SetBounce) != 0))
                {
                    elastic = ufloat_hwFloat_hwFloat_op_div(ufloat_int2hwFloat(CurWeapon->Bounciness), _1000);
                    if(ufloat_hwFloat_hwFloat_op_lt(elastic, _1))
                    {
                        newGear->Elasticity = ufloat_hwFloat_hwFloat_op_mul(newGear->Elasticity, elastic);
                    }
                    else
                    {
                        if(ufloat_hwFloat_hwFloat_op_gt(elastic, _1))
                        {
                            newGear->Elasticity = ufloat_hwFloat_hwFloat_op_sub(_1, ufloat_hwFloat_hwFloat_op_div(ufloat_hwFloat_hwFloat_op_sub(_1, newGear->Elasticity), elastic));
                        }
                    }
                }
                ustats_AmmoUsed((*Gear->Hedgehog).CurAmmoType);
                if(!(_strcompare(SpeechText, __str1)))
                {
                    speech = uvisualgearslist_AddVisualGear_3(0, 0, vgtSpeechBubble);
                    if(speech != NULL)
                    {
                        speech->Text = SpeechText;
                        speech->Hedgehog = (*Gear->Hedgehog).Gear->Hedgehog;
                        speech->FrameTicks = SpeechType;
                        uchat_AddChatString(_strprepend(0x9, ulocale_Format_3(fpcrtl_astr2str(trmsg[sidChatHog]), (*(*Gear->Hedgehog).Gear->Hedgehog).Name, SpeechText)));
                    }
                    SpeechText = __str1;
                }
                (*Gear).Power = 0;
                if((CurAmmoGear != NULL) && ((Ammoz[(*Gear->Hedgehog).CurAmmoType].Ammo.Propz & ammoprop_AltUse) == 0))
                {
                    if((((*Gear->Hedgehog).CurAmmoType == amRope) || ((*Gear->Hedgehog).CurAmmoType == amResurrector)))
                    {
                        (*Gear).Message = (*Gear).Message | gmAttack;
                    }
                    CurAmmoGear->Message = (*Gear).Message;
                }
                else
                {
                    if(!CurrentTeam->ExtDriven && ((Ammoz[(*Gear->Hedgehog).CurAmmoType].Ammo.Propz & ammoprop_Power) != 0))
                    {
                        uio_SendIPC(__str2);
                    }
                    ugearshedgehog_AfterAttack();
                }
                TargetPoint.x = NoPointX;
            }
            else
            {
                (*Gear).Message = (*Gear).Message & ~gmAttack;
            }
            uscript_ScriptCall_2(__str3, (usedAmmoType));
        }
    }
};
void ugearshedgehog_AfterAttack()
{
    astring s;
    TAmmoType a;
    PGear HHGear;
    {
        HHGear = (*CurrentHedgehog).Gear;
        a = (*CurrentHedgehog).CurAmmoType;
        if(HHGear != NULL)
        {
            HHGear->State = HHGear->State & ~gstAttacking;
        }
        if((Ammoz[a].Ammo.Propz & ammoprop_Effect) == 0)
        {
            ++(*CurrentHedgehog).MultiShootAttacks;
            if((Ammoz[a].Ammo.NumPerTurn > 0) && ((GameFlags & gfMultiWeapon) == 0))
            {
                s = fpcrtl_str2astr(uutils_IntToStr((((int64_t) (Ammoz[a].Ammo.NumPerTurn)) - ((int64_t) ((*CurrentHedgehog).MultiShootAttacks))) + 1));
                ucaptions_AddCaption(ulocale_FormatA_2(trmsg[sidRemaining], s), capcolDefault, capgrpAmmostate);
            }
            if((Ammoz[a].Ammo.NumPerTurn >= (*CurrentHedgehog).MultiShootAttacks) || ((GameFlags & gfMultiWeapon) != 0))
            {
                isInMultiShoot = true;
            }
            else
            {
                uammos_OnUsedAmmo(&((*CurrentHedgehog)));
                if(((Ammoz[a].Ammo.Propz & ammoprop_NoRoundEnd) == 0) && (((GameFlags & gfInfAttack) == 0) || PlacingHogs))
                {
                    if(TagTurnTimeLeft == 0)
                    {
                        TagTurnTimeLeft = TurnTimeLeft;
                    }
                    if((HHGear != NULL) && ((HHGear->State & gstHHDriven) != 0))
                    {
                        if(((CurAmmoGear != NULL) && ((CurAmmoGear->State & gstSubmersible) != 0)) && ucollisions_CheckCoordInWater(ufloat_hwRound(CurAmmoGear->X), ufloat_hwRound(CurAmmoGear->Y)))
                        {
                            TurnTimeLeft = (Ammoz[a].TimeAfterTurn * cGetAwayTime) / 25;
                        }
                        else
                        {
                            TurnTimeLeft = (Ammoz[a].TimeAfterTurn * cGetAwayTime) / 100;
                        }
                        IsGetAwayTime = true;
                    }
                }
                if(((Ammoz[a].Ammo.Propz & ammoprop_NoRoundEnd) == 0) && (HHGear != NULL))
                {
                    HHGear->State = HHGear->State | gstAttacked;
                }
                if(((a == amNothing) || ((Ammoz[a].Ammo.Propz & ammoprop_NoRoundEnd) != 0)) || (((GameFlags & gfInfAttack) != 0) && ((Ammoz[a].Ammo.Propz & ammoprop_ForceTurnEnd) == 0)))
                {
                    uammos_ApplyAmmoChanges(&((*CurrentHedgehog)));
                }
            }
        }
        else
        {
            uammos_OnUsedAmmo(&((*CurrentHedgehog)));
            uammos_ApplyAmmoChanges(&((*CurrentHedgehog)));
        }
        AttackBar = 0;
    }
};
void ugearshedgehog_doStepHedgehogDead(PGear Gear)
{
    enum{frametime = 200};
    enum{timertime = (frametime * 6)};
    PGear grave;
    if((*Gear->Hedgehog).Unplaced)
    {
        return;
    }
    if(Gear->Timer > 1)
    {
        AllInactive = false;
        --Gear->Timer;
        if((Gear->Timer % frametime) == 0)
        {
            ++Gear->Pos;
        }
    }
    else
    {
        if(Gear->Timer == 1)
        {
            (*Gear->Hedgehog).Effects[heFrozen] = 0;
            Gear->State = Gear->State | gstNoDamage;
            ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, CurrentHedgehog, EXPLAutoSound);
            grave = ugearslist_AddGear_7(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), gtGrave, 0, _0, _0, 0);
            grave->Hedgehog = Gear->Hedgehog;
            grave->Pos = Gear->uid;
            ugearslist_DeleteGear(Gear);
            ugearsutils_SetAllToActive();
        }
        else
        {
            AllInactive = false;
            Gear->Z = cCurrHHZ;
            ugearslist_RemoveGearFromList(Gear);
            ugearslist_InsertGearToList(Gear);
            switch(fpcrtl_random(3))
            {case 0:usound_PlaySoundV_2(sndByeBye, (*(*Gear->Hedgehog).Team).voicepack);
                    break;
             case 1:usound_PlaySoundV_2(sndSoLong, (*(*Gear->Hedgehog).Team).voicepack);
                    break;
             case 2:usound_PlaySoundV_2(sndOhDear, (*(*Gear->Hedgehog).Team).voicepack);
                    break;
             default: break;}
            Gear->Pos = 0;
            Gear->Timer = timertime;
        }
    }
};
void ugearshedgehog_doStepHedgehogGone(PGear Gear)
{
    enum{frametime = 65};
    enum{timertime = (frametime * 11)};
    LongInt i;
    if((*Gear->Hedgehog).Unplaced)
    {
        return;
    }
    if(Gear->Timer > 1)
    {
        AllInactive = false;
        --Gear->Timer;
        if((Gear->Timer % frametime) == 0)
        {
            ++Gear->Pos;
        }
    }
    else
    {
        if(Gear->Timer == 1)
        {
            ugearslist_DeleteGear(Gear);
            ugearsutils_SetAllToActive();
        }
        else
        {
            AllInactive = false;
            Gear->Z = cCurrHHZ;
            ugearslist_RemoveGearFromList(Gear);
            ugearslist_InsertGearToList(Gear);
            {
                {i = 0;
                 LongInt i__end__ = cMaxHHIndex;
                 if (i <= i__end__) do {
                                           if((*(*Gear->Hedgehog).Team).Hedgehogs[i].Gear != NULL)
                                           {
                                               if((*(*Gear->Hedgehog).Team).Hedgehogs[i].Gear == Gear)
                                               {
                                                   usound_PlaySoundV_2(sndByeBye, (*(*Gear->Hedgehog).Team).voicepack);
                                                   usound_PlaySound_1(sndWarp);
                                               }
                                               break;
                                           }
                                       } while(i++ != i__end__);}
            }
            Gear->Pos = 0;
            Gear->Timer = timertime;
        }
    }
};
void ugearshedgehog_AddPickup(THedgehog HH,TAmmoType ammo,LongWord cnt,LongWord X,LongWord Y)
{
    astring s;
    astring name;
    PVisualGear vga;
    if(cnt != 0)
    {
        uammos_AddAmmo_3(&(HH), ammo, cnt);
    }
    else
    {
        uammos_AddAmmo_2(&(HH), ammo);
    }
    if(ugearsutils_IsHogLocal(&(HH)))
    {
        if(fpcrtl_LengthA(trluaammo[Ammoz[ammo].NameId]) > 0)
        {
            name = trluaammo[Ammoz[ammo].NameId];
        }
        else
        {
            name = trammo[Ammoz[ammo].NameId];
        }
        if(cnt == 0)
        {
            cnt = Ammoz[ammo].NumberInCase;
        }
        if((ammo == amNothing) || (cnt == 0))
        {
            s = trmsg[sidEmptyCrate];
        }
        else
        {
            if(cnt >= AMMO_INFINITE)
            {
                s = _strconcatA(name, fpcrtl_str2astr(_strappend(_strappend(_strappend(_strappend(__str4, ((char)0xe2)), ((char)0x88)), ((char)0x9e)), 0x29)));
            }
            else
            {
                s = _strconcatA(name, fpcrtl_str2astr(_strappend(_strconcat(__str4, uutils_IntToStr(cnt)), 0x29)));
            }
        }
        ucaptions_AddCaption(s, (*(*HH.Team).Clan).Color, capgrpAmmoinfo);
        if((ammo != amNothing) && (cnt != 0))
        {
            vga = uvisualgearslist_AddVisualGear_3(X, Y, vgtAmmo);
            if(vga != NULL)
            {
                vga->Frame = ((LongWord)ammo);
            }
        }
    }
};
void ugearshedgehog_PickUp(PGear HH,PGear Gear)
{
    PGear ag;
    PGear gi;
    LongInt healthBoost;
    if((Gear->State & gstFrozen) != 0)
    {
        return;
    }
    if((Gear->Message & gmDestroy) != 0)
    {
        return;
    }
    Gear->Message = gmDestroy;
    if((Gear->Pos & posCaseExplode) != 0)
    {
        if((Gear->Pos & posCasePoison) != 0)
        {
            ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), 25, HH->Hedgehog, EXPLAutoSound + EXPLPoisoned);
        }
        else
        {
            ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), 25, HH->Hedgehog, EXPLAutoSound);
        }
    }
    else
    {
        if((Gear->Pos & posCasePoison) != 0)
        {
            ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), 25, HH->Hedgehog, (EXPLAutoSound + EXPLPoisoned) + EXPLNoDamage);
        }
        else
        {
            switch(Gear->Pos)
            {case posCaseUtility:
             case posCaseAmmo:{
                                  usound_PlaySound_1(sndShotgunReload);
                                  if(Gear->AmmoType != amNothing)
                                  {
                                      ugearshedgehog_AddPickup((*HH->Hedgehog), Gear->AmmoType, Gear->Power, ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y));
                                  }
                                  else
                                  {
                                      urandom_AddRandomness(GameTicks);
                                      gi = GearsList;
                                      while(gi != NULL)
                                      {
                                          if((gi->Kind == gtGenericFaller) && (gi->Tag == 1))
                                          {
                                              gi->Active = true;
                                              gi->State = gi->State | gsttmpFlag;
                                              gi->X = ufloat_int2hwFloat(urandom_GetRandom(rightX - leftX) + leftX);
                                              gi->Y = ufloat_int2hwFloat(urandom_GetRandom(LAND_HEIGHT - topY) + topY);
                                              gi->dX = ufloat_hwFloat_hwFloat_op_sub(_90, ufloat_hwFloat_hwFloat_op_mul(urandom_GetRandomf(), _360));
                                              gi->dY = ufloat_hwFloat_hwFloat_op_sub(_90, ufloat_hwFloat_hwFloat_op_mul(urandom_GetRandomf(), _360));
                                          }
                                          gi = gi->NextGear;
                                      }
                                      ag = ugearslist_AddGear_7(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), gtAddAmmo, gstInvisible, _0, _0, urandom_GetRandom(125) + 25);
                                      ag->Pos = Gear->Pos;
                                      ag->Power = Gear->Power;
                                  }
                              }
                              break;
             case posCaseHealth:{
                                    usound_PlaySound_1(sndShotgunReload);
                                    healthBoost = ugearsutils_IncHogHealth(HH->Hedgehog, Gear->Health);
                                    (*HH->Hedgehog).Effects[hePoisoned] = 0;
                                    ustore_RenderHealth(&((*HH->Hedgehog)));
                                    uteams_RecountTeamHealth((*HH->Hedgehog).Team);
                                    ugearsutils_HHHeal_3(HH->Hedgehog, healthBoost, true);
                                }
                                break;
             default: break;}
        }
    }
};
void ugearshedgehog_HedgehogStep(PGear Gear)
{
    LongInt PrevdX;
    PAmmo CurWeapon;
    CurWeapon = uammos_GetCurAmmoEntry(&((*Gear->Hedgehog)));
    if((Gear->State & (gstAttacking | gstMoving)) == 0)
    {
        if(isCursorVisible)
        {
            {
                {
                    if(Ammoz[(*CurWeapon).AmmoType].PosCount < 2)
                    {
                        return;
                    }
                    else
                    {
                        if(((*Gear->Hedgehog).Gear->Message & gmLeft) != 0)
                        {
                            (*CurWeapon).Pos = (((*CurWeapon).Pos - 1) + Ammoz[(*CurWeapon).AmmoType].PosCount) % Ammoz[(*CurWeapon).AmmoType].PosCount;
                        }
                        else
                        {
                            if(((*Gear->Hedgehog).Gear->Message & gmRight) != 0)
                            {
                                (*CurWeapon).Pos = ((*CurWeapon).Pos + 1) % Ammoz[(*CurWeapon).AmmoType].PosCount;
                            }
                            else
                            {
                                return;
                            }
                        }
                    }
                    GHStepTicks = 200;
                    return;
                }
            }
        }
        if((*Gear->Hedgehog).Unplaced)
        {
            return;
        }
        if((Gear->Message & gmAnimate) != 0)
        {
            Gear->Message = 0;
            Gear->State = Gear->State | gstAnimation;
            Gear->Tag = Gear->MsgParam;
            Gear->Timer = 0;
            Gear->Pos = 0;
        }
        if((Gear->Message & gmLJump) != 0)
        {
            Gear->Message = Gear->Message & ~gmLJump;
            ucollisions_DeleteCI(Gear);
            if(ucollisions_TestCollisionYwithGear(Gear, -1) == 0)
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
                if((*Gear->Hedgehog).Effects[heArtillery] == 0)
                {
                    Gear->dX = ufloat_SignAs(_0_15, Gear->dX);
                }
                Gear->State = (Gear->State | gstMoving) | gstHHJumping;
                usound_PlaySoundV_2(sndJump1, (*(*Gear->Hedgehog).Team).voicepack);
                return;
            }
        }
        if((Gear->Message & gmHJump) != 0)
        {
            ucollisions_DeleteCI(Gear);
            Gear->Message = Gear->Message & ~gmHJump;
            Gear->dY = ufloat_hwFloat_op_sub(_0_2);
            uutils_SetLittle(&(Gear->dX));
            Gear->State = (Gear->State | gstMoving) | gstHHJumping;
            usound_PlaySoundV_2(sndJump3, (*(*Gear->Hedgehog).Team).voicepack);
            return;
        }
        if((((Gear->Message & (gmLeft | gmRight)) != 0) && ((Gear->State & gstMoving) == 0)) && (ugearsutils_CheckGearNear_4(Gear, gtPortal, 26, 26) == NULL))
        {
            Gear->PortalCounter = 0;
        }
        PrevdX = ufloat_hwSign(Gear->dX);
        if((Gear->Message & gmLeft) != 0)
        {
            Gear->dX = ufloat_hwFloat_op_sub(_0);
        }
        else
        {
            if((Gear->Message & gmRight) != 0)
            {
                Gear->dX = _0;
            }
            else
            {
                return;
            }
        }
        StepSoundTimer = cHHStepTicks;
        GHStepTicks = cHHStepTicks;
        if(PrevdX != ufloat_hwSign(Gear->dX))
        {
            FollowGear = Gear;
            return;
        }
        ucollisions_DeleteCI(Gear);
        (*Gear->Hedgehog).visStepPos = ((*Gear->Hedgehog).visStepPos + 1) & 7;
        if((((*Gear->Hedgehog).Effects[heArtillery] == 0) || ((CurAmmoGear != NULL) && (CurAmmoGear->Kind == gtBlowTorch))) && ((Gear->Message & gmPrecise) == 0))
        {
            ugearsutils_MakeHedgehogsStep(Gear);
        }
        ugearsutils_SetAllHHToActive_1(false);
        ucollisions_AddCI(Gear);
    }
};
void ugearshedgehog_HedgehogChAngle(PGear HHGear)
{
    LongWord da;
    {
        if(((((*HHGear->Hedgehog).CurAmmoType == amRope) || ((CurAmmoGear != NULL) && (CurAmmoGear->AmmoType == amRope))) && ((HHGear->State & (gstMoving | gstHHJumping)) == gstMoving)) || (((*HHGear->Hedgehog).CurAmmoType == amPortalGun) && ((HHGear->State & gstMoving) != 0)))
        {
            da = 2;
        }
        else
        {
            da = 1;
        }
    }
    if((((HHGear->Message & gmPrecise) == 0) || ((CurAmmoGear != NULL) && (CurAmmoGear->AmmoType == amJetpack))) || ((GameTicks % 5) == 1))
    {
        if(((HHGear->Message & gmUp) != 0) && (HHGear->Angle >= (CurMinAngle + da)))
        {
            HHGear->Angle -= da;
        }
        else
        {
            if(((HHGear->Message & gmDown) != 0) && ((HHGear->Angle + da) <= CurMaxAngle))
            {
                HHGear->Angle += da;
            }
        }
    }
};
void ugearshedgehog_moveHedgehogOutOfWall(PGear Gear)
{
    hwFloat hx;
    boolean colly;
    boolean collxl;
    boolean collxr;
    colly = ucollisions_TestCollisionYwithGear(Gear, 1) != 0;
    while(colly)
    {
        hx = Gear->X;
        Gear->X = ufloat_hwFloat_hwFloat_op_add(hx, _1);
        collxl = ucollisions_TestCollisionX(Gear, -1) != 0;
        Gear->X = ufloat_hwFloat_hwFloat_op_sub(hx, _1);
        collxr = ucollisions_TestCollisionX(Gear, 1) != 0;
        Gear->X = hx;
        if(collxl == collxr)
        {
            break;
        }
        if(collxl)
        {
            if(ucollisions_TestCollisionX(Gear, 1) != 0)
            {
                break;
            }
            Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, _1);
        }
        else
        {
            if(ucollisions_TestCollisionX(Gear, -1) != 0)
            {
                break;
            }
            Gear->X = ufloat_hwFloat_hwFloat_op_sub(Gear->X, _1);
        }
        colly = ucollisions_TestCollisionYwithGear(Gear, 1) != 0;
    }
};
void ugearshedgehog_doStepHedgehogMoving(PGear Gear)
{
    boolean isFalling;
    boolean isUnderwater;
    Word land;
    LongWord cnt;
    astring s;
    if((*Gear->Hedgehog).Unplaced)
    {
        Gear->dY = _0;
        Gear->dX = _0;
        Gear->State = Gear->State & ~gstMoving;
        return;
    }
    land = 0;
    isUnderwater = ucollisions_CheckCoordInWater(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y) + Gear->Radius);
    if(Gear->dX.QWordValue > 8160437862)
    {
        Gear->dX.QWordValue = 8160437862;
    }
    if(Gear->dY.QWordValue > 8160437862)
    {
        Gear->dY.QWordValue = 8160437862;
    }
    isFalling = Gear->dY.isNegative;
    if(!isFalling)
    {
        ugearshedgehog_moveHedgehogOutOfWall(Gear);
        isFalling = ucollisions_TestCollisionYKick(Gear, 1) == 0;
    }
    if(isFalling)
    {
        land = ucollisions_TestCollisionYKick(Gear, -1);
        if(Gear->dY.isNegative && (land != 0))
        {
            if((land & lfBouncy) != 0)
            {
                ugearshandlersmess_doStepFallingGear(Gear);
                Gear->AdvBounce = 1;
                Gear->dX = ufloat_hwFloat_hwFloat_op_mul(Gear->dX, _0_8);
            }
            if(((land & lfBouncy) == 0) || ((Gear->State & gstCollision) != 0))
            {
                Gear->dY = _0;
            }
            Gear->State = Gear->State & ~gstCollision;
        }
        Gear->State = Gear->State | gstMoving;
        if(((((Gear->State & gstHHDriven) != 0) && (FollowGear != NULL)) && !CurrentTeam->ExtDriven) && (ufloat_hwFloat_hwFloat_op_gt(ufloat_hwFloat_hwFloat_op_add(ufloat_hwSqr(Gear->dX), ufloat_hwSqr(Gear->dY)), _0_003)))
        {
            FollowGear = Gear;
        }
        if(isUnderwater)
        {
            Gear->dY = ufloat_hwFloat_hwFloat_op_add(Gear->dY, ufloat_hwFloat_hwFloat_op_div(cGravity, _2));
        }
        else
        {
            Gear->dY = ufloat_hwFloat_hwFloat_op_add(Gear->dY, cGravity);
            if(((GameFlags & gfMoreWind) != 0) && (((Gear->Damage != 0) || ((CurAmmoGear != NULL) && ((CurAmmoGear->AmmoType == amJetpack) || (CurAmmoGear->AmmoType == amBirdy)))) || ((Gear->dY.QWordValue + Gear->dX.QWordValue) > _0_55.QWordValue)))
            {
                Gear->dX = ufloat_hwFloat_hwFloat_op_add(Gear->dX, ufloat_hwFloat_hwFloat_op_div(cWindSpeed, Gear->Density));
            }
        }
    }
    else
    {
        land = ucollisions_TestCollisionYwithGear(Gear, 1);
        if((((((Gear->dX.QWordValue + Gear->dY.QWordValue) < _0_55.QWordValue) && ((land & lfIce) == 0)) && (((land & lfBouncy) == 0) || ((Gear->State & gstCollision) != 0))) && (Gear->Damage == 0)) && ((Gear->State & gstHHJumping) != 0))
        {
            uutils_SetLittle(&(Gear->dX));
        }
        if(!Gear->dY.isNegative)
        {
            if((land & lfBouncy) != 0)
            {
                ugearshandlersmess_doStepFallingGear(Gear);
                Gear->AdvBounce = 1;
                Gear->dX = ufloat_hwFloat_hwFloat_op_mul(Gear->dX, _0_8);
            }
            ugearsutils_CheckHHDamage(Gear);
            if(((land & lfBouncy) == 0) || ((Gear->State & gstCollision) != 0))
            {
                if((((Gear->State & gstHHHJump) != 0) && ((*Gear->Hedgehog).Effects[heArtillery] == 0)) && (Gear->dX.QWordValue < _0_02.QWordValue))
                {
                    if((land & lfBouncy) != 0)
                    {
                        Gear->dY = _0;
                    }
                    Gear->dX.isNegative = !Gear->dX.isNegative;
                }
                Gear->State = Gear->State & ~(gstHHJumping | gstHHHJump);
                if(((land & lfBouncy) == 0) || (Gear->dX.QWordValue < _0_02.QWordValue))
                {
                    Gear->dY = _0;
                }
            }
            Gear->State = Gear->State & ~gstCollision;
        }
        else
        {
            Gear->dY = ufloat_hwFloat_hwFloat_op_add(Gear->dY, cGravity);
        }
        if((Gear->State & gstMoving) != 0)
        {
            if((land & lfIce) != 0)
            {
                Gear->dX = ufloat_hwFloat_hwFloat_op_mul(Gear->dX, ufloat_hwFloat_hwFloat_op_sub(_1, ufloat_hwFloat_hwFloat_op_div(ufloat_hwFloat_hwFloat_op_sub(_1, Gear->Friction), _2)));
            }
            else
            {
                Gear->dX = ufloat_hwFloat_hwFloat_op_mul(Gear->dX, Gear->Friction);
            }
        }
    }
    if((Gear->State & ((gstMoving | gstHHJumping) | gstHHHJump)) != 0)
    {
        ucollisions_DeleteCI(Gear);
    }
    if(isUnderwater)
    {
        Gear->dY = ufloat_hwFloat_hwFloat_op_mul(Gear->dY, _0_999);
        Gear->dX = ufloat_hwFloat_hwFloat_op_mul(Gear->dX, _0_999);
    }
    if((Gear->State & gstMoving) != 0)
    {
        if(ucollisions_TestCollisionXKick(Gear, ufloat_hwSign(Gear->dX)) != 0)
        {
            if(!isFalling)
            {
                if(ufloat_hwFloat_hwFloat_op_gt(ufloat_hwAbs(Gear->dX), _0_01))
                {
                    if((ucollisions_TestCollisionXwithXYShift_4(Gear, ufloat_hwFloat_hwFloat_op_sub(ufloat_int2hwFloat(ufloat_hwSign(Gear->dX)), Gear->dX), -1, ufloat_hwSign(Gear->dX)) == 0) && (ucollisions_TestCollisionYwithXYShift_4(Gear, ufloat_hwSign(Gear->dX) - ufloat_hwRound(Gear->dX), -1, -1) == 0))
                    {
                        Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, Gear->dX);
                        Gear->dX = ufloat_hwFloat_hwFloat_op_mul(Gear->dX, _0_96);
                        Gear->Y = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, _1);
                    }
                    else
                    {
                        if((ucollisions_TestCollisionXwithXYShift_4(Gear, ufloat_hwFloat_hwFloat_op_sub(ufloat_int2hwFloat(ufloat_hwSign(Gear->dX)), Gear->dX), -2, ufloat_hwSign(Gear->dX)) == 0) && (ucollisions_TestCollisionYwithXYShift_4(Gear, ufloat_hwSign(Gear->dX) - ufloat_hwRound(Gear->dX), -1, -1) == 0))
                        {
                            Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, Gear->dX);
                            Gear->dX = ufloat_hwFloat_hwFloat_op_mul(Gear->dX, _0_93);
                            Gear->Y = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, _2);
                        }
                        else
                        {
                            if((ucollisions_TestCollisionXwithXYShift_4(Gear, ufloat_hwFloat_hwFloat_op_sub(ufloat_int2hwFloat(ufloat_hwSign(Gear->dX)), Gear->dX), -3, ufloat_hwSign(Gear->dX)) == 0) && (ucollisions_TestCollisionYwithXYShift_4(Gear, ufloat_hwSign(Gear->dX) - ufloat_hwRound(Gear->dX), -1, -1) == 0))
                            {
                                Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, Gear->dX);
                                Gear->dX = ufloat_hwFloat_hwFloat_op_mul(Gear->dX, _0_9);
                                Gear->Y = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, _3);
                            }
                            else
                            {
                                if((ucollisions_TestCollisionXwithXYShift_4(Gear, ufloat_hwFloat_hwFloat_op_sub(ufloat_int2hwFloat(ufloat_hwSign(Gear->dX)), Gear->dX), -4, ufloat_hwSign(Gear->dX)) == 0) && (ucollisions_TestCollisionYwithXYShift_4(Gear, ufloat_hwSign(Gear->dX) - ufloat_hwRound(Gear->dX), -1, -1) == 0))
                                {
                                    Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, Gear->dX);
                                    Gear->dX = ufloat_hwFloat_hwFloat_op_mul(Gear->dX, _0_87);
                                    Gear->Y = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, _4);
                                }
                                else
                                {
                                    if((ucollisions_TestCollisionXwithXYShift_4(Gear, ufloat_hwFloat_hwFloat_op_sub(ufloat_int2hwFloat(ufloat_hwSign(Gear->dX)), Gear->dX), -5, ufloat_hwSign(Gear->dX)) == 0) && (ucollisions_TestCollisionYwithXYShift_4(Gear, ufloat_hwSign(Gear->dX) - ufloat_hwRound(Gear->dX), -1, -1) == 0))
                                    {
                                        Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, Gear->dX);
                                        Gear->dX = ufloat_hwFloat_hwFloat_op_mul(Gear->dX, _0_84);
                                        Gear->Y = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, _5);
                                    }
                                    else
                                    {
                                        if(ufloat_hwFloat_hwFloat_op_gt(ufloat_hwAbs(Gear->dX), _0_02))
                                        {
                                            Gear->dX = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_op_sub(Gear->Elasticity), Gear->dX);
                                        }
                                        else
                                        {
                                            Gear->State = Gear->State & ~gstMoving;
                                            cnt = 0;
                                            while((((cnt < 6) && !ugearsutils_CheckGearDrowning(&(Gear))) && (Gear != NULL)) && (ucollisions_TestCollisionYwithGear(Gear, 1) == 0))
                                            {
                                                Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _1);
                                                ++cnt;
                                            }
                                            uutils_SetLittle(&(Gear->dX));
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    Gear->State = Gear->State & ~gstMoving;
                    cnt = 0;
                    while((((cnt < 6) && !ugearsutils_CheckGearDrowning(&(Gear))) && (Gear != NULL)) && (ucollisions_TestCollisionYwithGear(Gear, 1) == 0))
                    {
                        Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _1);
                        ++cnt;
                    }
                    uutils_SetLittle(&(Gear->dX));
                }
            }
            else
            {
                if((ufloat_hwFloat_hwFloat_op_gt(ufloat_hwAbs(Gear->dX), cLittle)) && ((Gear->State & gstHHJumping) == 0))
                {
                    Gear->dX = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_op_sub(Gear->Elasticity), Gear->dX);
                }
                else
                {
                    uutils_SetLittle(&(Gear->dX));
                }
            }
        }
    }
    if(!isFalling && (ufloat_hwFloat_hwFloat_op_lt(ufloat_hwFloat_hwFloat_op_add(ufloat_hwAbs(Gear->dX), ufloat_hwAbs(Gear->dY)), _0_03)))
    {
        if(!GameOver)
        {
            Gear->State = Gear->State & ~gstWinner;
        }
        Gear->State = Gear->State & ~gstMoving;
        cnt = 0;
        while((((cnt < 6) && !ugearsutils_CheckGearDrowning(&(Gear))) && (Gear != NULL)) && (ucollisions_TestCollisionYwithGear(Gear, 1) == 0))
        {
            Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _1);
            ++cnt;
        }
        if(Gear == NULL)
        {
            return;
        }
        uutils_SetLittle(&(Gear->dX));
        Gear->dY = _0;
    }
    else
    {
        Gear->State = Gear->State | gstMoving;
    }
    if((Gear->State & gstMoving) != 0)
    {
        Gear->State = Gear->State & ~gstAnimation;
        Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, Gear->dX);
        Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, Gear->dY);
        if(!Gear->dY.isNegative && (ucollisions_TestCollisionYKick(Gear, 1) == 0))
        {
            land = ucollisions_TestCollisionYwithXYShift_4(Gear, 0, 1, 1);
            if((land & lfBouncy) != 0)
            {
                ugearshandlersmess_doStepFallingGear(Gear);
            }
            Gear->AdvBounce = 1;
            if((land != 0) && (((land & lfBouncy) == 0) || ((Gear->State & gstCollision) != 0)))
            {
                ugearsutils_CheckHHDamage(Gear);
                Gear->dY = _0;
                Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _1);
            }
            Gear->State = Gear->State & ~gstCollision;
        }
        if(Gear == NULL)
        {
            return;
        }
        if((Gear->State & gstDrowning) != 0)
        {
            if(CurrentHedgehog->Gear == Gear)
            {
                isCursorVisible = false;
            }
        }
    }
    if((!ufloat_isZero(Gear->dY) && (Gear->FlightTime > 0)) && ((GameFlags & gfLowGravity) == 0))
    {
        ++Gear->FlightTime;
        if((Gear->FlightTime > 1500) && ((ufloat_hwRound(Gear->X) < (leftX - 250)) || (ufloat_hwRound(Gear->X) > (rightX + 250))))
        {
            Gear->FlightTime = 0;
            s = fpcrtl_str2astr(CurrentHedgehog->Name);
            ucaptions_AddCaption(ulocale_FormatA_2(ulocale_GetEventString(eidHomerun), s), capcolDefault, capgrpMessage2);
            usound_PlaySound_1(sndHomerun);
        }
    }
    else
    {
        ustats_hedgehogFlight(Gear, Gear->FlightTime);
        Gear->FlightTime = 0;
    }
    if((((((((WorldEdge == weNone) && !hasBorder) && !(*Gear->Hedgehog).FlownOffMap) && !ufloat_isZero(Gear->dX)) && !isUnderwater) && ((Gear->State & gstHHDriven) == 0)) && (ufloat_hwRound(Gear->Y) < (cWaterLine - 300))) && ((ufloat_hwRound(Gear->X) < -cCamLimitX) || (ufloat_hwRound(Gear->X) > (LAND_WIDTH + cCamLimitX))))
    {
        usound_PlaySoundV_2(sndFlyAway, (*(*Gear->Hedgehog).Team).voicepack);
        (*Gear->Hedgehog).FlownOffMap = true;
    }
};
void ugearshedgehog_doStepHedgehogDriven(PGear HHGear)
{
    PGear t;
    boolean wasJumping;
    PHedgehog Hedgehog;
    astring s;
    Hedgehog = HHGear->Hedgehog;
    if(!isInMultiShoot)
    {
        AllInactive = false;
    }
    else
    {
        if(((Hedgehog->CurAmmoType == amShotgun) || (Hedgehog->CurAmmoType == amDEagle) || (Hedgehog->CurAmmoType == amSniperRifle)))
        {
            HHGear->Message = HHGear->Message & gmPrecise;
        }
    }
    if(((Ammoz[CurrentHedgehog->CurAmmoType].Ammo.Propz & ammoprop_Utility) != 0) && isInMultiShoot)
    {
        AllInactive = true;
    }
    else
    {
        if(!isInMultiShoot)
        {
            AllInactive = false;
        }
    }
    if(((((TurnTimeLeft == 0) || (HHGear->Damage > 0)) || (HHGear->Health == 0)) || (((GameFlags & gfKing) != 0) && !(*Hedgehog->Team).hasKing)) || (LuaEndTurnRequested == true))
    {
        if(Hedgehog->CurAmmoType == amKnife)
        {
            ustore_LoadHedgehogHat(&((*Hedgehog)), Hedgehog->Hat);
        }
        if(TagTurnTimeLeft == 0)
        {
            TagTurnTimeLeft = TurnTimeLeft;
        }
        TurnTimeLeft = 0;
        if(((((((GameOver == false) && ((GameFlags & gfInfAttack) == 0)) && ((HHGear->State & gstAttacked) == 0)) && (HHGear->Damage == 0)) && (HHGear->Health > 0)) && (LuaNoEndTurnTaunts == false)) && (ustats_getIsTurnSkipped() == false))
        {
            usound_AddVoice_2(sndBoring, (*Hedgehog->Team).voicepack);
            if((GameFlags & gfInfAttack) == 0)
            {
                s = fpcrtl_str2astr(Hedgehog->Name);
                ucaptions_AddCaption(ulocale_FormatA_2(ulocale_GetEventString(eidTimeout), s), capcolDefault, capgrpMessage);
            }
        }
        isCursorVisible = false;
        HHGear->State = HHGear->State & ~((gstHHDriven | gstAnimation) | gstAttacking);
        AttackBar = 0;
        usound_StopSound_1(sndThrowPowerUp);
        LuaEndTurnRequested = false;
        LuaNoEndTurnTaunts = false;
        if((HHGear->Damage > 0) || (HHGear->Health == 0))
        {
            HHGear->State = HHGear->State & ~(gstHHJumping | gstHHHJump);
        }
        return;
    }
    if((isAFK && !CurrentTeam->ExtDriven) && (CurrentHedgehog->BotLevel == 0))
    {
        ugearshedgehog_AFKSkip();
        return;
    }
    if((HHGear->State & gstAnimation) != 0)
    {
        HHGear->Message = 0;
        if((HHGear->Pos == Wavez[((TWave)HHGear->Tag)].VoiceDelay) && (HHGear->Timer == 0))
        {
            usound_PlaySoundV_2(Wavez[((TWave)HHGear->Tag)].Voice, (*Hedgehog->Team).voicepack);
        }
        ++HHGear->Timer;
        if(HHGear->Timer == Wavez[((TWave)HHGear->Tag)].Interval)
        {
            HHGear->Timer = 0;
            ++HHGear->Pos;
            if(HHGear->Pos == Wavez[((TWave)HHGear->Tag)].FramesCount)
            {
                HHGear->State = HHGear->State & ~gstAnimation;
            }
        }
        return;
    }
    if((((HHGear->State & gstMoving) != 0) || (GHStepTicks == cHHStepTicks)) || (CurAmmoGear != NULL))
    {
        {
            if(((CurAmmoGear == NULL) && (ufloat_hwFloat_hwFloat_op_gt(HHGear->dY, _0_39))) && ((*Hedgehog).CurAmmoType == amParachute))
            {
                HHGear->Message = HHGear->Message | gmAttack;
            }
        }
        t = ugearsutils_CheckGearNear_4(HHGear, gtCase, 36, 36);
        if(t != NULL)
        {
            ugearshedgehog_PickUp(HHGear, t);
        }
    }
    if(CurAmmoGear == NULL)
    {
        if(((HHGear->Message & gmAttack) != 0) || ((HHGear->State & gstAttacking) != 0))
        {
            ugearshedgehog_Attack(HHGear);
        }
        else
        {
            ;
        }
    }
    else
    {
        {
            if((((Ammoz[CurAmmoGear->AmmoType].Ammo.Propz & ammoprop_AltAttack) != 0) && ((HHGear->Message & gmLJump) != 0)) && ((Ammoz[(*Hedgehog).CurAmmoType].Ammo.Propz & ammoprop_AltUse) != 0))
            {
                ugearshedgehog_Attack(HHGear);
                HHGear->Message = HHGear->Message & ~gmLJump;
            }
        }
    }
    if((CurAmmoGear == NULL) || ((Ammoz[CurAmmoGear->AmmoType].Ammo.Propz & ammoprop_AltAttack) != 0))
    {
        if((HHGear->Message & gmSlot) != 0)
        {
            if(ugearshedgehog_ChangeAmmo(HHGear))
            {
                uammos_ApplyAmmoChanges(&((*Hedgehog)));
            }
        }
        if((HHGear->Message & gmWeapon) != 0)
        {
            ugearshedgehog_HHSetWeapon(HHGear);
        }
        if((HHGear->Message & gmTimer) != 0)
        {
            ugearshedgehog_HHSetTimer(HHGear);
        }
    }
    if(CurAmmoGear != NULL)
    {
        CurAmmoGear->Message = HHGear->Message;
        return;
    }
    ugearshedgehog_HedgehogChAngle(HHGear);
    if((HHGear->State & gstMoving) != 0)
    {
        wasJumping = (HHGear->State & gstHHJumping) != 0;
        if((((HHGear->Message & gmHJump) != 0) && wasJumping) && ((HHGear->State & gstHHHJump) == 0))
        {
            if(!(ufloat_hwFloat_hwFloat_op_gt(ufloat_hwAbs(HHGear->dX), cLittle)) && (ufloat_hwFloat_hwFloat_op_lt(HHGear->dY, _0_05)))
            {
                HHGear->State = HHGear->State | gstHHHJump;
                HHGear->dY = ufloat_hwFloat_op_sub(_0_25);
                if(Hedgehog->Effects[heArtillery] == 0)
                {
                    HHGear->dX = ufloat_hwFloat_op_sub(ufloat_SignAs(_0_02, HHGear->dX));
                }
                usound_PlaySoundV_2(sndJump2, (*Hedgehog->Team).voicepack);
            }
        }
        HHGear->Message = HHGear->Message & ~(gmLJump | gmHJump);
        if(((Hedgehog->Effects[heArtillery] == 0) && wasJumping) && (ucollisions_TestCollisionXwithGear(HHGear, ufloat_hwSign(HHGear->dX)) != 0))
        {
            uutils_SetLittle(&(HHGear->dX));
        }
        if(Hedgehog->Gear != NULL)
        {
            ugearshedgehog_doStepHedgehogMoving(HHGear);
        }
        if((HHGear->State & (gstMoving | gstDrowning)) == 0)
        {
            ucollisions_AddCI(HHGear);
            if(wasJumping)
            {
                GHStepTicks = 410;
            }
            else
            {
                GHStepTicks = 95;
            }
        }
        return;
    }
    if(!(isInMultiShoot && (((Hedgehog->CurAmmoType == amShotgun) || (Hedgehog->CurAmmoType == amDEagle) || (Hedgehog->CurAmmoType == amSniperRifle)))) && (Hedgehog->Gear != NULL))
    {
        if(GHStepTicks > 0)
        {
            --GHStepTicks;
        }
        if(GHStepTicks == 0)
        {
            ugearshedgehog_HedgehogStep(HHGear);
        }
    }
};
void ugearshedgehog_doStepHedgehogFree(PGear Gear)
{
    LongWord prevState;
    astring s;
    prevState = Gear->State;
    ugearshedgehog_doStepHedgehogMoving(Gear);
    if((Gear->State & (gstMoving | gstDrowning)) != 0)
    {
        if(Gear->Damage > 0)
        {
            ugearsutils_CalcRotationDirAngle(Gear);
        }
        AllInactive = false;
        return;
    }
    if(Gear->Health == 0)
    {
        if(PrvInactive || ((GameFlags & gfInfAttack) != 0))
        {
            Gear->Timer = 0;
            FollowGear = Gear;
            PrvInactive = false;
            AllInactive = false;
            if((Gear->State & gstHHGone) == 0)
            {
                (*Gear->Hedgehog).Effects[hePoisoned] = 0;
                if((*Gear->Hedgehog).Effects[heResurrectable] != 0)
                {
                    ugearsutils_ResurrectHedgehog(&(Gear));
                }
                else
                {
                    Gear->State = (Gear->State | gstHHDeath) & ~gstAnimation;
                    Gear->doStep = &(ugearshedgehog_doStepHedgehogDead);
                    s = fpcrtl_str2astr((*Gear->Hedgehog).Name);
                    if((*Gear->Hedgehog).King)
                    {
                        ucaptions_AddCaption(ulocale_FormatA_2(ulocale_GetEventString(eidKingDied), s), capcolDefault, capgrpMessage);
                    }
                    else
                    {
                        ucaptions_AddCaption(ulocale_FormatA_2(ulocale_GetEventString(eidDied), s), capcolDefault, capgrpMessage);
                    }
                }
            }
            else
            {
                Gear->State = Gear->State & ~gstAnimation;
                Gear->doStep = &(ugearshedgehog_doStepHedgehogGone);
                s = fpcrtl_str2astr((*Gear->Hedgehog).Name);
                ucaptions_AddCaption(ulocale_FormatA_2(ulocale_GetEventString(eidGone), s), capcolDefault, capgrpMessage);
            }
        }
        return;
    }
    if(((Gear->State & gstWait) == 0) && (prevState != Gear->State))
    {
        Gear->State = Gear->State | gstWait;
        Gear->Timer = 150;
    }
    else
    {
        if(Gear->Timer == 0)
        {
            Gear->State = Gear->State & ~((((gstWait | gstLoser) | gstAttacked) | gstNotKickable) | gstChooseTarget);
            if(!GameOver)
            {
                Gear->State = Gear->State & ~gstWinner;
            }
            if((*Gear->Hedgehog).Effects[heFrozen] == 0)
            {
                Gear->Active = false;
            }
            ucollisions_AddCI(Gear);
            return;
        }
        else
        {
            --Gear->Timer;
        }
    }
    AllInactive = false;
};
void ugearshedgehog_CheckIce(PGear Gear)
{
    hwFloat slope;
    if(((((((Gear->Message & ((gmAllStoppable | gmLJump) | gmHJump)) == 0) && ((Gear->State & (((gstHHJumping | gstHHHJump) | gstAttacking) | gstAnimation)) == 0)) && ((Gear->Hedgehog == NULL) || (((*Gear->Hedgehog).Effects[heFrozen] == 0) || ((*Gear->Hedgehog).Effects[heFrozen] > 255)))) && !Gear->dY.isNegative) && TurnClockActive) && ((ucollisions_TestCollisionYwithGear(Gear, 1) & lfIce) != 0))
    {
        slope = ucollisions_CalcSlopeBelowGear(Gear);
        if(slope.QWordValue > 730144440)
        {
            Gear->dX = ufloat_hwFloat_hwFloat_op_add(Gear->dX, ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_mul(slope, cGravity), _256));
            Gear->State = Gear->State | gstMoving;
        }
    }
};
void ugearshedgehog_doStepHedgehog(PGear Gear)
{
    hwFloat tX;
    if(!(*Gear->Hedgehog).Unplaced)
    {
        ugearsutils_CheckGearDrowning(&(Gear));
    }
    if(Gear == NULL)
    {
        return;
    }
    tX = Gear->X;
    if(ugearsutils_WorldWrap(&(Gear)))
    {
        if(((((WorldEdge != weBounce) && (Gear == CurrentHedgehog->Gear)) && (CurAmmoGear != NULL)) && (CurAmmoGear->Kind == gtRope)) && (ufloat_hwFloat_hwFloat_op_neq(CurAmmoGear->Elasticity, _0)))
        {
            CurAmmoGear->PortalCounter = 1;
        }
        if((WorldEdge == weWrap) && ((ucollisions_TestCollisionXwithGear(Gear, 1) != 0) || (ucollisions_TestCollisionXwithGear(Gear, -1) != 0)))
        {
            if((Gear->State & gstNotKickable) == 0)
            {
                if(ufloat_hwRound(tX) > (leftX + (Gear->Radius * 2)))
                {
                    Gear->X = ufloat_int2hwFloat(rightX);
                }
                else
                {
                    Gear->X = ufloat_int2hwFloat(leftX);
                }
                Gear->dX.QWordValue = 0;
                Gear->State = Gear->State | gstCollision;
            }
        }
    }
    CheckSum = CheckSum ^ (*Gear->Hedgehog).BotLevel;
    if((Gear->Message & gmDestroy) != 0)
    {
        ugearslist_DeleteGear(Gear);
        return;
    }
    if((GameTicks % 128) == 0)
    {
        ugearshedgehog_CheckIce(Gear);
    }
    if((((GameTicks % 10) == 0) && ((*Gear->Hedgehog).Effects[heFrozen] > 0)) && ((*Gear->Hedgehog).Effects[heFrozen] < 256))
    {
        --(*Gear->Hedgehog).Effects[heFrozen];
    }
    if((Gear->State & gstHHDriven) == 0)
    {
        ugearshedgehog_doStepHedgehogFree(Gear);
    }
    else
    {
        {
            if((*Gear->Hedgehog).Team->hasGone)
            {
                uteams_TeamGoneEffect(&((*(*Gear->Hedgehog).Team)));
            }
            else
            {
                ugearshedgehog_doStepHedgehogDriven((*Gear->Hedgehog).Gear);
            }
        }
    }
};
void ugearshedgehog_PlayTaunt(LongWord taunt)
{
    if(CurrentHedgehog->Gear != NULL)
    {
        {
            (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message | (gmAnimate & InputMask);
            (*CurrentHedgehog->Gear).MsgParam = taunt;
            uscript_ScriptCall_2(__str5, (*CurrentHedgehog->Gear).MsgParam);
        }
    }
};
