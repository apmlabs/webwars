#include "fpcrtl.h"

#include "uAmmos.h"
LongInt StoreCnt;
#include "uVariables.h"
#include "uCommands.h"
#include "uUtils.h"
#include "uCaptions.h"
#include "uDebug.h"
#include "uScript.h"
#include "uConsole.h"
static const string255 __str20 = STRINIT("ammstore");
static const string255 __str19 = STRINIT("ammreinf");
static const string255 __str18 = STRINIT("ammprob");
static const string255 __str17 = STRINIT("ammdelay");
static const string255 __str16 = STRINIT("ammloadt");
static const string255 __str15 = STRINIT("");
static const string255 __str14 = STRINIT("/setweap ");
static const string255 __str13 = STRINIT(", ");
static const string255 __str12 = STRINIT(" (");
static const string255 __str11 = STRINIT("Ammo slot index overflow");
static const string255 __str10 = STRINIT("onUsedAmmo");
static const string255 __str9 = STRINIT("Invalid ammo store number");
static const string255 __str8 = STRINIT("Ammo stores overflow");
static const string255 __str7 = STRINIT("Incomplete or missing ammo scheme set (incompatible frontend or demo/save?)");
static const string255 __str6 = STRINIT("Reinf: ");
static const string255 __str5 = STRINIT("Delay: ");
static const string255 __str4 = STRINIT("Prob: ");
static const string255 __str3 = STRINIT("Loadout: ");
static const string255 __str2 = STRINIT("Expected: ");
static const string255 __str1 = STRINIT("=== AMMO DEBUG ===");
static const string255 __str0 = STRINIT("Ammo slot overflow");
typedef TAmmo TAmmoArray[61];
typedef PHHAmmo StoresList_tt[cMaxHHs];
static StoresList_tt StoresList;
static string255 ammoLoadout;
static string255 ammoProbability;
static string255 ammoDelay;
static string255 ammoReinforcement;
typedef TAmmoCounts InitialCountsLocal_tt[cMaxHHs];
static InitialCountsLocal_tt InitialCountsLocal;
void uammos_FillAmmoStore(PHHAmmo Ammo,TAmmoArray (*newAmmo))
{
    typedef Byte mi_tt[(cMaxSlotIndex + 1)];
    mi_tt mi;
    TAmmoType a;
    fpcrtl_FillChar(mi, sizeof(mi), 0);
    fpcrtl_FillChar((*Ammo), sizeof((*Ammo)), 0);
    {a = 0;
     TAmmoType a__end__ = 60;
     if (a <= a__end__) do {
                               if((*newAmmo)[a].Count > 0)
                               {
                                   if(udebug_checkFails(mi[Ammoz[a].Slot] <= cMaxSlotAmmoIndex, __str0, true))
                                   {
                                       return;
                                   }
                                   (*Ammo)[Ammoz[a].Slot][mi[Ammoz[a].Slot]] = (*newAmmo)[a];
                                   ++mi[Ammoz[a].Slot];
                               }
                           } while(a++ != a__end__);}
    AmmoMenuInvalidated = true;
};
void uammos_AddAmmoStore()
{
    LongWord cnt;
    TAmmoType a;
    TAmmoCounts ammos;
    TAmmoArray newAmmos;
    LongWord expectedLen;
    expectedLen = (60);
    uconsole_WriteLnToConsole(__str1);
    uconsole_WriteToConsole(__str2);
    uconsole_WriteLnToConsole(uutils_IntToStr(expectedLen));
    uconsole_WriteToConsole(__str3);
    uconsole_WriteLnToConsole(uutils_IntToStr(((Byte)ammoLoadout.s[0])));
    uconsole_WriteToConsole(__str4);
    uconsole_WriteLnToConsole(uutils_IntToStr(((Byte)ammoProbability.s[0])));
    uconsole_WriteToConsole(__str5);
    uconsole_WriteLnToConsole(uutils_IntToStr(((Byte)ammoDelay.s[0])));
    uconsole_WriteToConsole(__str6);
    uconsole_WriteLnToConsole(uutils_IntToStr(((Byte)ammoReinforcement.s[0])));
    if(udebug_checkFails((((((Byte)ammoLoadout.s[0]) == ((Byte)(60))) && (((Byte)ammoProbability.s[0]) == ((Byte)(60)))) && (((Byte)ammoDelay.s[0]) == ((Byte)(60)))) && (((Byte)ammoReinforcement.s[0]) == ((Byte)(60))), __str7, true))
    {
        return;
    }
    if(udebug_checkFails(StoreCnt < cMaxHHs, __str8, true))
    {
        return;
    }
    ++StoreCnt;
    fpcrtl_new(StoresList[((int)(StoreCnt) - 1)]);
    {a = 0;
     TAmmoType a__end__ = 60;
     if (a <= a__end__) do {
                               if(a != amNothing)
                               {
                                   Ammoz[a].Probability = probabilityLevels[((Byte)ammoProbability.s[(a)]) - ((Byte)0x30)];
                                   Ammoz[a].SkipTurns = ((Byte)ammoDelay.s[(a)]) - ((Byte)0x30);
                                   Ammoz[a].NumberInCase = ((Byte)ammoReinforcement.s[(a)]) - ((Byte)0x30);
                                   cnt = ((Byte)ammoLoadout.s[(a)]) - ((Byte)0x30);
                                   if(cnt == 9)
                                   {
                                       cnt = AMMO_INFINITE;
                                       Ammoz[a].Probability = 0;
                                   }
                                   if(Ammoz[a].NumberInCase == 0)
                                   {
                                       Ammoz[a].Probability = 0;
                                   }
                                   if(((((((a == amLowGravity) && ((GameFlags & gfLowGravity) != 0)) || ((((a == amInvulnerable) || (a == amResurrector) || (a == amVampiric))) && ((GameFlags & gfInvulnerable) != 0))) || ((a == amLaserSight) && ((GameFlags & gfLaserSight) != 0))) || ((a == amVampiric) && ((GameFlags & gfVampiric) != 0))) || ((a == amExtraTime) && (cHedgehogTurnTime >= 1000000))) || (a == amCreeper))
                                   {
                                       cnt = 0;
                                       Ammoz[a].Probability = 0;
                                   }
                                   ammos[a] = cnt;
                                   if((((((GameFlags & gfPlaceHog) != 0) || (((GameFlags & gfKing) != 0) && ((GameFlags & gfPlaceHog) == 0))) && (a != amTeleport)) && (a != amSkip)) && (Ammoz[a].SkipTurns < 10000))
                                   {
                                       Ammoz[a].SkipTurns += 10000;
                                   }
                                   if((((GameFlags & gfPlaceHog) != 0) || (((GameFlags & gfKing) != 0) && ((GameFlags & gfPlaceHog) == 0))) && (a == amTeleport))
                                   {
                                       ammos[a] = AMMO_INFINITE;
                                   }
                               }
                               else
                               {
                                   ammos[a] = AMMO_INFINITE;
                               }
                               if((((GameFlags & gfPlaceHog) != 0) || (((GameFlags & gfKing) != 0) && ((GameFlags & gfPlaceHog) == 0))) && (a == amTeleport))
                               {
                                   InitialCountsLocal[((int)(StoreCnt) - 1)][a] = cnt;
                                   InitialAmmoCounts[a] = cnt;
                               }
                               else
                               {
                                   InitialCountsLocal[((int)(StoreCnt) - 1)][a] = ammos[a];
                                   InitialAmmoCounts[a] = ammos[a];
                               }
                           } while(a++ != a__end__);}
    {a = 0;
     TAmmoType a__end__ = 60;
     if (a <= a__end__) do {
                               newAmmos[a] = Ammoz[a].Ammo;
                               newAmmos[a].Count = ammos[a];
                           } while(a++ != a__end__);}
    uammos_FillAmmoStore(StoresList[((int)(StoreCnt) - 1)], &(newAmmos));
};
PHHAmmo uammos_GetAmmoByNum(LongInt num)
{
    PHHAmmo getammobynum_result;
    if(udebug_checkFails(num < StoreCnt, __str9, true))
    {
        getammobynum_result = NULL;
    }
    else
    {
        getammobynum_result = StoresList[num];
    }
    return getammobynum_result;
};
PAmmo uammos_GetCurAmmoEntry(THedgehog (*Hedgehog))
{
    PAmmo getcurammoentry_result;
    getcurammoentry_result = uammos_GetAmmoEntry(&((*Hedgehog)), (*Hedgehog).CurAmmoType);
    return getcurammoentry_result;
};
PAmmo uammos_GetAmmoEntry(THedgehog (*Hedgehog),TAmmoType am)
{
    PAmmo getammoentry_result;
    LongWord ammoidx;
    LongWord slot;
    {
        slot = Ammoz[am].Slot;
        ammoidx = 0;
        while((ammoidx < cMaxSlotAmmoIndex) && ((*(*Hedgehog).Ammo)[slot][ammoidx].AmmoType != am))
        {
            ++ammoidx;
        }
        getammoentry_result = &((*(*Hedgehog).Ammo)[slot][ammoidx]);
        if((*(*Hedgehog).Ammo)[slot][ammoidx].AmmoType != am)
        {
            getammoentry_result = uammos_GetAmmoEntry(&((*Hedgehog)), amNothing);
        }
    }
    return getammoentry_result;
};
void uammos_AssignStores()
{
    LongInt t;
    LongWord i;
    {t = 0;
     LongInt t__end__ = ((int)(TeamsCount) - 1);
     if (t <= t__end__) do {
                               {
                                   {i = 0;
                                    LongWord i__end__ = cMaxHHIndex;
                                    if (i <= i__end__) do {
                                                              if((*TeamsArray[t]).Hedgehogs[i].Gear != NULL)
                                                              {
                                                                  (*TeamsArray[t]).Hedgehogs[i].Ammo = uammos_GetAmmoByNum((*TeamsArray[t]).Hedgehogs[i].AmmoStore);
                                                                  if(((GameFlags & gfPlaceHog) != 0) || (((GameFlags & gfKing) != 0) && ((*TeamsArray[t]).Hedgehogs[i].King == true)))
                                                                  {
                                                                      (*TeamsArray[t]).Hedgehogs[i].CurAmmoType = amTeleport;
                                                                  }
                                                                  else
                                                                  {
                                                                      (*TeamsArray[t]).Hedgehogs[i].CurAmmoType = amNothing;
                                                                  }
                                                              }
                                                          } while(i++ != i__end__);}
                               }
                           } while(t++ != t__end__);}
};
void uammos_AddAmmo_3(THedgehog (*Hedgehog),TAmmoType ammo,LongWord amt)
{
    LongWord cnt;
    PAmmo a;
    a = uammos_GetAmmoEntry(&((*Hedgehog)), ammo);
    if(a->AmmoType != amNothing)
    {
        cnt = a->Count;
    }
    else
    {
        cnt = 0;
    }
    if((cnt >= AMMO_INFINITE) || (amt >= AMMO_INFINITE))
    {
        cnt = AMMO_INFINITE;
    }
    else
    {
        cnt = uutils_Min(AMMO_FINITE_MAX, cnt + amt);
    }
    uammos_SetAmmo(&((*Hedgehog)), ammo, cnt);
};
void uammos_AddAmmo_2(THedgehog (*Hedgehog),TAmmoType ammo)
{
    uammos_AddAmmo_3(&((*Hedgehog)), ammo, Ammoz[ammo].NumberInCase);
};
void uammos_SetAmmo(THedgehog (*Hedgehog),TAmmoType ammo,LongWord cnt)
{
    TAmmoArray ammos;
    LongInt slot;
    LongInt ami;
    PHHAmmo hhammo;
    PAmmo CurWeapon;
    TAmmoType a;
    if(ammo == amNothing)
    {
        return;
    }
    fpcrtl_FillChar(ammos, sizeof(ammos), 0);
    hhammo = (*Hedgehog).Ammo;
    {a = 0;
     TAmmoType a__end__ = 60;
     if (a <= a__end__) do {
                               ammos[a] = Ammoz[a].Ammo;
                               ammos[a].Count = 0;
                           } while(a++ != a__end__);}
    {slot = 0;
     LongInt slot__end__ = cMaxSlotIndex;
     if (slot <= slot__end__) do {
                                     {ami = 0;
                                      LongInt ami__end__ = cMaxSlotAmmoIndex;
                                      if (ami <= ami__end__) do {
                                                                    if((*hhammo)[slot][ami].Count > 0)
                                                                    {
                                                                        ammos[(*hhammo)[slot][ami].AmmoType] = (*hhammo)[slot][ami];
                                                                    }
                                                                } while(ami++ != ami__end__);}
                                 } while(slot++ != slot__end__);}
    ammos[ammo].Count = cnt;
    if(ammos[ammo].Count > AMMO_INFINITE)
    {
        ammos[ammo].Count = AMMO_INFINITE;
    }
    uammos_FillAmmoStore(hhammo, &(ammos));
    CurWeapon = uammos_GetCurAmmoEntry(&((*Hedgehog)));
    {
        {
            if(((*CurWeapon).Count == 0) || ((*CurWeapon).AmmoType == amNothing))
            {
                uammos_PackAmmo((*Hedgehog).Ammo, Ammoz[(*CurWeapon).AmmoType].Slot);
                (*Hedgehog).CurAmmoType = amNothing;
            }
        }
    }
    if((*Hedgehog).BotLevel != 0)
    {
        (*(*Hedgehog).Gear).AIHints = (*(*Hedgehog).Gear).AIHints | aihAmmosChanged;
    }
};
void uammos_PackAmmo(PHHAmmo Ammo,LongInt Slot)
{
    LongInt ami;
    boolean b;
    do {
           b = false;
           ami = 0;
           while(!b && (ami < cMaxSlotAmmoIndex))
           {
               if(((*Ammo)[Slot][ami].Count == 0) && ((*Ammo)[Slot][ami + 1].Count > 0))
               {
                   b = true;
               }
               else
               {
                   ++ami;
               }
           }
           if(b)
           {
               (*Ammo)[Slot][ami] = (*Ammo)[Slot][ami + 1];
               (*Ammo)[Slot][ami + 1].Count = 0;
           }
       } while(!(!b));
    AmmoMenuInvalidated = true;
};
void uammos_OnUsedAmmo(THedgehog (*Hedgehog))
{
    PAmmo CurWeapon;
    CurWeapon = uammos_GetCurAmmoEntry(&((*Hedgehog)));
    {
        if((*Hedgehog).CurAmmoType != amNothing)
        {
            uscript_ScriptCall_2(__str10, ((*Hedgehog).CurAmmoType));
        }
        (*Hedgehog).MultiShootAttacks = 0;
        {
            if((*CurWeapon).Count != AMMO_INFINITE)
            {
                --(*CurWeapon).Count;
                if((*CurWeapon).Count == 0)
                {
                    uammos_PackAmmo((*Hedgehog).Ammo, Ammoz[(*CurWeapon).AmmoType].Slot);
                    if((*Hedgehog).CurAmmoType == amKnife)
                    {
                        ustore_LoadHedgehogHat(&((*Hedgehog)), (*Hedgehog).Hat);
                    }
                    (*Hedgehog).CurAmmoType = amNothing;
                }
            }
        }
    }
};
LongWord uammos_HHHasAmmo(THedgehog (*Hedgehog),TAmmoType Ammo)
{
    LongWord hhhasammo_result;
    LongInt slot;
    LongInt ami;
    hhhasammo_result = 0;
    slot = Ammoz[Ammo].Slot;
    ami = 0;
    while(ami <= cMaxSlotAmmoIndex)
    {
        {
            if((*(*Hedgehog).Ammo)[slot][ami].AmmoType == Ammo)
            {
                if((*(*(*Hedgehog).Team).Clan).TurnNumber > Ammoz[(*(*Hedgehog).Ammo)[slot][ami].AmmoType].SkipTurns)
                {
                    return (*(*Hedgehog).Ammo)[slot][ami].Count;
                }
                else
                {
                    return 0;
                }
            }
        }
        ++ami;
    }
    return hhhasammo_result;
};
void uammos_ApplyAngleBounds(THedgehog (*Hedgehog),TAmmoType AmmoType)
{
    if((*Hedgehog).Gear != NULL)
    {
        {
            if(AmmoType != amNothing)
            {
                if((CurAmmoGear != NULL) && (CurAmmoGear->AmmoType == amRope))
                {
                    CurMaxAngle = Ammoz[amRope].maxAngle;
                    CurMinAngle = Ammoz[amRope].minAngle;
                }
                else
                {
                    CurMinAngle = Ammoz[AmmoType].minAngle;
                    if(Ammoz[AmmoType].maxAngle != 0)
                    {
                        CurMaxAngle = Ammoz[AmmoType].maxAngle;
                    }
                    else
                    {
                        CurMaxAngle = cMaxAngle;
                    }
                }
                {
                    if((*(*Hedgehog).Gear).Angle < CurMinAngle)
                    {
                        (*(*Hedgehog).Gear).Angle = CurMinAngle;
                    }
                    if((*(*Hedgehog).Gear).Angle > CurMaxAngle)
                    {
                        (*(*Hedgehog).Gear).Angle = CurMaxAngle;
                    }
                }
            }
        }
    }
};
void uammos_SwitchToFirstLegalAmmo(THedgehog (*Hedgehog))
{
    LongWord slot;
    LongWord ammoidx;
    {
        (*Hedgehog).CurAmmoType = amNothing;
        slot = 0;
        ammoidx = 0;
        while((slot <= cMaxSlotIndex) && (((*(*Hedgehog).Ammo)[slot][ammoidx].Count == 0) || ((((int64_t) (Ammoz[(*(*Hedgehog).Ammo)[slot][ammoidx].AmmoType].SkipTurns)) - ((int64_t) ((*CurrentTeam->Clan).TurnNumber))) >= 0)))
        {
            while((ammoidx <= cMaxSlotAmmoIndex) && (((*(*Hedgehog).Ammo)[slot][ammoidx].Count == 0) || ((((int64_t) (Ammoz[(*(*Hedgehog).Ammo)[slot][ammoidx].AmmoType].SkipTurns)) - ((int64_t) ((*CurrentTeam->Clan).TurnNumber))) >= 0)))
            {
                ++ammoidx;
            }
            if(ammoidx > cMaxSlotAmmoIndex)
            {
                ammoidx = 0;
                ++slot;
            }
        }
        if(udebug_checkFails(slot <= cMaxSlotIndex, __str11, true))
        {
            return;
        }
        (*Hedgehog).CurAmmoType = (*(*Hedgehog).Ammo)[slot][ammoidx].AmmoType;
    }
};
void uammos_ApplyAmmoChanges(THedgehog (*Hedgehog))
{
    astring s;
    PAmmo OldWeapon;
    PAmmo CurWeapon;
    TargetPoint.x = NoPointX;
    {
        CurWeapon = uammos_GetCurAmmoEntry(&((*Hedgehog)));
        OldWeapon = uammos_GetCurAmmoEntry(&((*Hedgehog)));
        if(((*Hedgehog).Gear != NULL) && (((*(*Hedgehog).Gear).State & gstHHDriven) == 0))
        {
            (*Hedgehog).CurAmmoType = amNothing;
        }
        else
        {
            if(CurWeapon->Count == 0)
            {
                uammos_SwitchToFirstLegalAmmo(&((*Hedgehog)));
            }
            else
            {
                if(CurWeapon->AmmoType == amNothing)
                {
                    (*Hedgehog).CurAmmoType = amNothing;
                }
            }
        }
        CurWeapon = uammos_GetCurAmmoEntry(&((*Hedgehog)));
        if(CurWeapon->AmmoType != OldWeapon->AmmoType)
        {
            (*Hedgehog).Timer = 10;
        }
        uammos_ApplyAngleBounds(&((*Hedgehog)), CurWeapon->AmmoType);
        {
            if(fpcrtl_LengthA(trluaammo[Ammoz[(*CurWeapon).AmmoType].NameId]) > 0)
            {
                s = trluaammo[Ammoz[(*CurWeapon).AmmoType].NameId];
            }
            else
            {
                s = trammo[Ammoz[(*CurWeapon).AmmoType].NameId];
            }
            if(((*CurWeapon).Count != AMMO_INFINITE) && !((*(*Hedgehog).Team).ExtDriven || ((*Hedgehog).BotLevel > 0)))
            {
                s = _strconcatA(s, fpcrtl_str2astr(_strappend(_strconcat(__str12, uutils_IntToStr((*CurWeapon).Count)), 0x29)));
            }
            if(((*CurWeapon).Propz & ammoprop_Timerable) != 0)
            {
                s = _strconcatA(_strconcatA(s, fpcrtl_str2astr(_strappend(_strconcat(__str13, uutils_IntToStr((*CurWeapon).Timer / 1000)), 0x20))), trammo[sidSeconds]);
            }
            if(((*Hedgehog).Gear != NULL) && (((*(*Hedgehog).Gear).State & gstHHDriven) != 0))
            {
                ucaptions_AddCaption(s, (*(*Hedgehog).Team->Clan).Color, capgrpAmmoinfo);
            }
            if(((*CurWeapon).Propz & ammoprop_NeedTarget) != 0)
            {
                if((*Hedgehog).Gear != NULL)
                {
                    (*Hedgehog).Gear->State = (*Hedgehog).Gear->State | gstChooseTarget;
                }
                isCursorVisible = true;
            }
            else
            {
                if((*Hedgehog).Gear != NULL)
                {
                    (*Hedgehog).Gear->State = (*Hedgehog).Gear->State & ~gstChooseTarget;
                }
                isCursorVisible = false;
            }
        }
    }
};
void uammos_SwitchNotHeldAmmo(THedgehog (*Hedgehog))
{
    {
        if(((Ammoz[(*Hedgehog).CurAmmoType].Ammo.Propz & ammoprop_DontHold) != 0) || ((((int64_t) (Ammoz[(*Hedgehog).CurAmmoType].SkipTurns)) - ((int64_t) ((*CurrentTeam->Clan).TurnNumber))) >= 0))
        {
            uammos_SwitchToFirstLegalAmmo(&((*Hedgehog)));
        }
    }
};
void uammos_SetWeapon(TAmmoType weap)
{
    ucommands_ParseCommand_2(_strappend(__str14, ((char)weap)), true);
};
void uammos_DisableSomeWeapons()
{
    LongWord i;
    LongWord slot;
    LongWord a;
    TAmmoType t;
    {i = 0;
     LongWord i__end__ = ((int)(StoreCnt) - 1);
     if (i <= i__end__) do {
                               {slot = 0;
                                LongWord slot__end__ = cMaxSlotIndex;
                                if (slot <= slot__end__) do {
                                                                {a = 0;
                                                                 LongWord a__end__ = cMaxSlotAmmoIndex;
                                                                 if (a <= a__end__) do {
                                                                                           {
                                                                                               if(((*StoresList[i])[slot][a].Propz & ammoprop_NotBorder) != 0)
                                                                                               {
                                                                                                   (*StoresList[i])[slot][a].Count = 0;
                                                                                                   InitialCountsLocal[i][(*StoresList[i])[slot][a].AmmoType] = 0;
                                                                                               }
                                                                                           }
                                                                                       } while(a++ != a__end__);}
                                                                uammos_PackAmmo(StoresList[i], slot);
                                                            } while(slot++ != slot__end__);}
                           } while(i++ != i__end__);}
    {t = 0;
     TAmmoType t__end__ = 60;
     if (t <= t__end__) do {
                               if((Ammoz[t].Ammo.Propz & ammoprop_NotBorder) != 0)
                               {
                                   Ammoz[t].Probability = 0;
                               }
                           } while(t++ != t__end__);}
};
void uammos_SetAmmoLoadout(string255 (*s))
{
    ammoLoadout = (*s);
};
void uammos_SetAmmoProbability(string255 (*s))
{
    ammoProbability = (*s);
};
void uammos_SetAmmoDelay(string255 (*s))
{
    ammoDelay = (*s);
};
void uammos_SetAmmoReinforcement(string255 (*s))
{
    ammoReinforcement = (*s);
};
void uammos_ResetWeapons()
{
    LongWord i;
    LongWord t;
    TAmmoType a;
    TAmmoArray newAmmos;
    {t = 0;
     LongWord t__end__ = ((int)(TeamsCount) - 1);
     if (t <= t__end__) do {
                               {
                                   {i = 0;
                                    LongWord i__end__ = cMaxHHIndex;
                                    if (i <= i__end__) do {
                                                              (*TeamsArray[t]).Hedgehogs[i].CurAmmoType = amNothing;
                                                          } while(i++ != i__end__);}
                               }
                           } while(t++ != t__end__);}
    {a = 0;
     TAmmoType a__end__ = 60;
     if (a <= a__end__) do {
                               newAmmos[a] = Ammoz[a].Ammo;
                           } while(a++ != a__end__);}
    {i = 0;
     LongWord i__end__ = ((int)(StoreCnt) - 1);
     if (i <= i__end__) do {
                               {a = 0;
                                TAmmoType a__end__ = 60;
                                if (a <= a__end__) do {
                                                          newAmmos[a].Count = InitialCountsLocal[i][a];
                                                      } while(a++ != a__end__);}
                               uammos_FillAmmoStore(StoresList[i], &(newAmmos));
                           } while(i++ != i__end__);}
    {a = 0;
     TAmmoType a__end__ = 60;
     if (a <= a__end__) do {
                               if(Ammoz[a].SkipTurns >= 10000)
                               {
                                   Ammoz[a].SkipTurns -= 10000;
                               }
                           } while(a++ != a__end__);}
};
void uammos_chAddAmmoStore(string255 (*descr))
{
    (*descr) = __str15;
    uammos_AddAmmoStore();
};
void uammos_initModule()
{
    LongWord i;
    ucommands_RegisterVariable_3(__str16, &(uammos_SetAmmoLoadout), false);
    ucommands_RegisterVariable_3(__str17, &(uammos_SetAmmoDelay), false);
    ucommands_RegisterVariable_3(__str18, &(uammos_SetAmmoProbability), false);
    ucommands_RegisterVariable_3(__str19, &(uammos_SetAmmoReinforcement), false);
    ucommands_RegisterVariable_3(__str20, &(uammos_chAddAmmoStore), false);
    CurMinAngle = 0;
    CurMaxAngle = cMaxAngle;
    StoreCnt = 0;
    ammoLoadout = __str15;
    ammoProbability = __str15;
    ammoDelay = __str15;
    ammoReinforcement = __str15;
    {i = 1;
     LongWord i__end__ = (60);
     if (i <= i__end__) do {
                               ammoLoadout = _strappend(ammoLoadout, 0x30);
                               ammoProbability = _strappend(ammoProbability, 0x30);
                               ammoDelay = _strappend(ammoDelay, 0x30);
                               ammoReinforcement = _strappend(ammoReinforcement, 0x30);
                           } while(i++ != i__end__);}
    fpcrtl_FillChar(InitialCountsLocal, sizeof(InitialCountsLocal), 0);
};
void uammos_freeModule()
{
    LongWord i;
    if(StoreCnt > 0)
    {
        {i = 0;
         LongWord i__end__ = ((int)(StoreCnt) - 1);
         if (i <= i__end__) do {
                                   fpcrtl_dispose(StoresList[i]);
                               } while(i++ != i__end__);}
    }
};
