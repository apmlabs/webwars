#include "fpcrtl.h"

#include "uAI.h"
#include "uConsts.h"
#include "SDLh.h"
#include "uAIMisc.h"
#include "uAIAmmoTests.h"
#include "uAIActions.h"
#include "uAmmos.h"
#include "uTypes.h"
#include "uVariables.h"
#include "uCommands.h"
#include "uUtils.h"
#include "uDebug.h"
#include "uAILandMarks.h"
#include "uGearsUtils.h"
#include "uAI2.h"
static const string255 __str2 = STRINIT("Engine bug: AI may break demos playing");
static const string255 __str1 = STRINIT("think");
static const string255 __str0 = STRINIT("FreeActionsList called");
static TActions BestActions;
typedef boolean CanUseAmmo_tt[61];
static CanUseAmmo_tt CanUseAmmo;
static boolean StopThinking;
static LongWord StartTicks;
static PSDL_sem ThreadSem;
void uai_FreeActionsList()
{
    uutils_AddFileLog(__str0);
    StopThinking = true;
    SDL_SemWait(ThreadSem);
    SDL_SemPost(ThreadSem);
    if(CurrentHedgehog != NULL)
    {
        {
            if((*CurrentHedgehog).Gear != NULL)
            {
                if((*CurrentHedgehog).BotLevel != 0)
                {
                    ucommands_StopMessages((*CurrentHedgehog).Gear->Message);
                }
            }
        }
    }
    BestActions.Count = 0;
    BestActions.Pos = 0;
};
enum{cBranchStackSize = 12};
typedef struct __TStackEntry {
            TActions MadeActions;
            TGear Hedgehog;
        } TStackEntry;
typedef struct __Stack_tt {
            LongWord Count;
            TStackEntry States[cBranchStackSize];
        } Stack_tt;
static Stack_tt Stack;
boolean uai_Push(TActions Actions,TGear Me,Integer Dir)
{
    boolean push_result;
    boolean bRes;
    bRes = (Stack.Count < cBranchStackSize) && (Actions.Count < (MAXACTIONS - 5));
    if(bRes)
    {
        {
            Stack.States[Stack.Count].MadeActions = Actions;
            Stack.States[Stack.Count].Hedgehog = Me;
            Stack.States[Stack.Count].Hedgehog.Message = Dir;
            ++Stack.Count;
        }
    }
    push_result = bRes;
    return push_result;
};
void uai_Pop(TActions (*Actions),TGear (*Me))
{
    --Stack.Count;
    {
        (*Actions) = Stack.States[Stack.Count].MadeActions;
        (*Me) = Stack.States[Stack.Count].Hedgehog;
    }
};
void uai_TestAmmos(TActions (*Actions),PGear Me,boolean rareChecks)
{
    Byte BotLevel;
    TAttackParams ap;
    LongInt Score;
    LongInt i;
    LongInt l;
    LongInt t;
    LongInt n;
    LongInt dAngle;
    TAmmoType a;
    TAmmoType aa;
    boolean useThisActions;
    boolean hasLowGrav;
    BotLevel = (*Me->Hedgehog).BotLevel;
    aiWindSpeed = ufloat_hwFloat2Float(cWindSpeed);
    aiLaserSighting = cLaserSighting || (uammos_HHHasAmmo(&((*Me->Hedgehog)), amLaserSight) > 0);
    aiGravity = cGravity;
    aiGravityf = cGravityf;
    aiHogsInTeam = ugearsutils_CountHogsInTeam(Me, true);
    hasLowGrav = uammos_HHHasAmmo(&((*Me->Hedgehog)), amLowGravity) > 0;
    useThisActions = false;
    Me->AIHints = Me->AIHints & ~aihAmmosChanged;
    {l = 0;
     LongInt l__end__ = 1;
     if (l <= l__end__) do {
                               if((l == 0) || (hasLowGrav && !cLowGravity))
                               {
                                   if(l == 0)
                                   {
                                       aiGravity = cGravity;
                                       aiGravityf = cGravityf;
                                   }
                                   else
                                   {
                                       if(l == 1)
                                       {
                                           aiGravity = ufloat_hwFloat_hwFloat_op_div(cGravity, _2);
                                           aiGravityf = cGravityf /(float) 2;
                                       }
                                   }
                                   {i = 0;
                                    LongInt i__end__ = ((int)(Targets.Count) - 1);
                                    if (i <= i__end__) do {
                                                              if((Targets.ar[i].Score >= 0) && !StopThinking)
                                                              {
                                                                  {
                                                                      a = (*Me->Hedgehog).CurAmmoType;
                                                                  }
                                                                  aa = a;
                                                                  SDL_Delay(0);
                                                                  do {
                                                                         if(((CanUseAmmo[a] && (!rareChecks || ((AmmoTests[a].flags & amtest_Rare) == 0))) && ((i == 0) || ((AmmoTests[a].flags & amtest_NoTarget) == 0))) && ((l == 0) || ((AmmoTests[a].flags & amtest_NoLowGravity) == 0)))
                                                                         {
                                                                             Score = AmmoTests[a].proc(Me, Targets.ar[i], BotLevel, &(ap), AmmoTests[a].flags);
                                                                             if((Score > BadTurn) && (((*Actions).Score + Score) > BestActions.Score))
                                                                             {
                                                                                 if((BestActions.Score < 0) || (((*Actions).Score + Score) > (BestActions.Score + (((Byte)BotLevel - 1) * 2048))))
                                                                                 {
                                                                                     if(useThisActions)
                                                                                     {
                                                                                         BestActions.Count = (*Actions).Count;
                                                                                     }
                                                                                     else
                                                                                     {
                                                                                         BestActions = (*Actions);
                                                                                         BestActions.isWalkingToABetterPlace = false;
                                                                                         useThisActions = true;
                                                                                     }
                                                                                     BestActions.Score = (*Actions).Score + Score;
                                                                                     if(CurrentHedgehog->MultiShootAttacks == 0)
                                                                                     {
                                                                                         if((!cLaserSighting && (uammos_HHHasAmmo(&((*Me->Hedgehog)), amLaserSight) > 0)) && ((AmmoTests[a].flags & amtest_LaserSight) != 0))
                                                                                         {
                                                                                             uaiactions_AddAction(&(BestActions), aia_Weapon, ((LongWord)amLaserSight), 80, 0, 0);
                                                                                             uaiactions_AddAction(&(BestActions), aia_attack, aim_push, 10, 0, 0);
                                                                                             uaiactions_AddAction(&(BestActions), aia_attack, aim_release, 10, 0, 0);
                                                                                         }
                                                                                         if((((AmmoTests[a].flags & amtest_NoInvulnerable) == 0) && (uammos_HHHasAmmo(&((*Me->Hedgehog)), amInvulnerable) > 0)) && ((*Me->Hedgehog).Effects[heInvulnerable] == 0))
                                                                                         {
                                                                                             uaiactions_AddAction(&(BestActions), aia_Weapon, ((LongWord)amInvulnerable), 80, 0, 0);
                                                                                             uaiactions_AddAction(&(BestActions), aia_attack, aim_push, 10, 0, 0);
                                                                                             uaiactions_AddAction(&(BestActions), aia_attack, aim_release, 10, 0, 0);
                                                                                         }
                                                                                         if((l == 1) && hasLowGrav)
                                                                                         {
                                                                                             uaiactions_AddAction(&(BestActions), aia_Weapon, ((LongWord)amLowGravity), 80, 0, 0);
                                                                                             uaiactions_AddAction(&(BestActions), aia_attack, aim_push, 10, 0, 0);
                                                                                             uaiactions_AddAction(&(BestActions), aia_attack, aim_release, 10, 0, 0);
                                                                                         }
                                                                                         if((uammos_HHHasAmmo(&((*Me->Hedgehog)), amExtraDamage) > 0) && (ufloat_hwFloat_hwFloat_op_neq(cDamageModifier, _1_5)))
                                                                                         {
                                                                                             uaiactions_AddAction(&(BestActions), aia_Weapon, ((LongWord)amExtraDamage), 80, 0, 0);
                                                                                             uaiactions_AddAction(&(BestActions), aia_attack, aim_push, 10, 0, 0);
                                                                                             uaiactions_AddAction(&(BestActions), aia_attack, aim_release, 10, 0, 0);
                                                                                         }
                                                                                         if((!cVampiric && ((AmmoTests[a].flags & amtest_NoVampiric) == 0)) && (uammos_HHHasAmmo(&((*Me->Hedgehog)), amVampiric) > 0))
                                                                                         {
                                                                                             uaiactions_AddAction(&(BestActions), aia_Weapon, ((LongWord)amVampiric), 80, 0, 0);
                                                                                             uaiactions_AddAction(&(BestActions), aia_attack, aim_push, 10, 0, 0);
                                                                                             uaiactions_AddAction(&(BestActions), aia_attack, aim_release, 10, 0, 0);
                                                                                         }
                                                                                     }
                                                                                     if(ap.Angle > 0)
                                                                                     {
                                                                                         uaiactions_AddAction(&(BestActions), aia_LookRight, 0, 200, 0, 0);
                                                                                     }
                                                                                     else
                                                                                     {
                                                                                         if(ap.Angle < 0)
                                                                                         {
                                                                                             uaiactions_AddAction(&(BestActions), aia_LookLeft, 0, 200, 0, 0);
                                                                                         }
                                                                                     }
                                                                                     uaiactions_AddAction(&(BestActions), aia_Weapon, ((LongWord)a), 300 + fpcrtl_random(400), 0, 0);
                                                                                     if((Ammoz[a].Ammo.Propz & ammoprop_Timerable) != 0)
                                                                                     {
                                                                                         uaiactions_AddAction(&(BestActions), aia_Timer, ap.Time / 1000, 400, 0, 0);
                                                                                     }
                                                                                     if(((Ammoz[a].Ammo.Propz & ammoprop_SetBounce) > 0) && (ap.Bounce > 0))
                                                                                     {
                                                                                         uaiactions_AddAction(&(BestActions), aia_Precise, aim_push, 10, 0, 0);
                                                                                         uaiactions_AddAction(&(BestActions), aia_Timer, ap.Bounce, 200, 0, 0);
                                                                                         uaiactions_AddAction(&(BestActions), aia_Precise, aim_release, 10, 0, 0);
                                                                                     }
                                                                                     if((Ammoz[a].Ammo.Propz & ammoprop_NeedTarget) != 0)
                                                                                     {
                                                                                         uaiactions_AddAction(&(BestActions), aia_Put, 0, 8, ap.AttackPutX, ap.AttackPutY);
                                                                                     }
                                                                                     if((Ammoz[a].Ammo.Propz & ammoprop_NoCrosshair) == 0)
                                                                                     {
                                                                                         dAngle = ((LongInt)Me->Angle) - fpcrtl_abs(ap.Angle);
                                                                                         if(dAngle > 0)
                                                                                         {
                                                                                             uaiactions_AddAction(&(BestActions), aia_Up, aim_push, 300 + fpcrtl_random(250), 0, 0);
                                                                                             uaiactions_AddAction(&(BestActions), aia_waitAngle, ap.Angle, 1, 0, 0);
                                                                                             uaiactions_AddAction(&(BestActions), aia_Up, aim_release, 1, 0, 0);
                                                                                         }
                                                                                         else
                                                                                         {
                                                                                             if(dAngle < 0)
                                                                                             {
                                                                                                 uaiactions_AddAction(&(BestActions), aia_Down, aim_push, 300 + fpcrtl_random(250), 0, 0);
                                                                                                 uaiactions_AddAction(&(BestActions), aia_waitAngle, ap.Angle, 1, 0, 0);
                                                                                                 uaiactions_AddAction(&(BestActions), aia_Down, aim_release, 1, 0, 0);
                                                                                             }
                                                                                         }
                                                                                     }
                                                                                     if((Ammoz[a].Ammo.Propz & ammoprop_OscAim) != 0)
                                                                                     {
                                                                                         uaiactions_AddAction(&(BestActions), aia_attack, aim_push, 350 + fpcrtl_random(200), 0, 0);
                                                                                         uaiactions_AddAction(&(BestActions), aia_attack, aim_release, 1, 0, 0);
                                                                                         if(fpcrtl_abs(ap.Angle) > 32)
                                                                                         {
                                                                                             uaiactions_AddAction(&(BestActions), aia_Down, aim_push, 100 + fpcrtl_random(150), 0, 0);
                                                                                             uaiactions_AddAction(&(BestActions), aia_Down, aim_release, 32, 0, 0);
                                                                                         }
                                                                                         uaiactions_AddAction(&(BestActions), aia_waitAngle, ap.Angle, 250, 0, 0);
                                                                                         uaiactions_AddAction(&(BestActions), aia_attack, aim_push, 1, 0, 0);
                                                                                         uaiactions_AddAction(&(BestActions), aia_attack, aim_release, 1, 0, 0);
                                                                                     }
                                                                                     else
                                                                                     {
                                                                                         if((Ammoz[a].Ammo.Propz & ammoprop_AttackingPut) == 0)
                                                                                         {
                                                                                             if((AmmoTests[a].flags & amtest_MultipleAttacks) == 0)
                                                                                             {
                                                                                                 n = 1;
                                                                                             }
                                                                                             else
                                                                                             {
                                                                                                 n = ap.AttacksNum;
                                                                                             }
                                                                                             uaiactions_AddAction(&(BestActions), aia_attack, aim_push, 650 + fpcrtl_random(300), 0, 0);
                                                                                             if((a == amResurrector) && (BotLevel < 4))
                                                                                             {
                                                                                                 uaiactions_AddAction(&(BestActions), aia_Up, aim_push, 1, 0, 0);
                                                                                             }
                                                                                             {t = 2;
                                                                                              LongInt t__end__ = n;
                                                                                              if (t <= t__end__) do {
                                                                                                                        uaiactions_AddAction(&(BestActions), aia_attack, aim_push, 150, 0, 0);
                                                                                                                        uaiactions_AddAction(&(BestActions), aia_attack, aim_release, ap.Power, 0, 0);
                                                                                                                    } while(t++ != t__end__);}
                                                                                             if((a == amResurrector) && (BotLevel < 4))
                                                                                             {
                                                                                                 uaiactions_AddAction(&(BestActions), aia_Up, aim_release, ap.Power, 0, 0);
                                                                                                 uaiactions_AddAction(&(BestActions), aia_attack, aim_release, 0, 0, 0);
                                                                                             }
                                                                                             else
                                                                                             {
                                                                                                 uaiactions_AddAction(&(BestActions), aia_attack, aim_release, ap.Power, 0, 0);
                                                                                             }
                                                                                             if((a == amKamikaze) && (fpcrtl_random(10000) == 0))
                                                                                             {
                                                                                                 uaiactions_AddAction(&(BestActions), aia_Switch, 0, 1, 0, 0);
                                                                                                 uaiactions_AddAction(&(BestActions), aia_Precise, aim_push, 1, 0, 0);
                                                                                                 uaiactions_AddAction(&(BestActions), aia_Precise, aim_release, 5000, 0, 0);
                                                                                             }
                                                                                         }
                                                                                     }
                                                                                     if((Ammoz[a].Ammo.Propz & ammoprop_Track) != 0)
                                                                                     {
                                                                                         uaiactions_AddAction(&(BestActions), aia_waitAmmoXY, 0, 12, ap.ExplX, ap.ExplY);
                                                                                         uaiactions_AddAction(&(BestActions), aia_attack, aim_push, 1, 0, 0);
                                                                                         uaiactions_AddAction(&(BestActions), aia_attack, aim_release, 7, 0, 0);
                                                                                     }
                                                                                     if(ap.ExplR > 0)
                                                                                     {
                                                                                         uaiactions_AddAction(&(BestActions), aia_AwareExpl, ap.ExplR, 10, ap.ExplX, ap.ExplY);
                                                                                     }
                                                                                 }
                                                                             }
                                                                         }
                                                                         if(a == 60)
                                                                         {
                                                                             a = 0;
                                                                         }
                                                                         else
                                                                         {
                                                                             ++a;
                                                                         }
                                                                     } while(!(((a == aa) || (CurrentHedgehog->MultiShootAttacks > 0)) || StopThinking));
                                                              }
                                                          } while(i++ != i__end__);}
                               }
                           } while(l++ != l__end__);}
    aiGravity = cGravity;
    aiGravityf = cGravityf;
};
void uai_Walk(PGear Me,TActions (*Actions))
{
    enum{FallPixForBranching = cHHRadius};
    LongWord maxticks;
    LongWord oldticks;
    LongWord steps;
    LongWord tmp;
    LongInt BaseRate;
    LongInt BestRate;
    LongInt Rate;
    LongInt i;
    TGoInfo GoInfo;
    boolean CanGo;
    TGear AltMe;
    Byte BotLevel;
    TAmmoType a;
    boolean isAfterAttack;
    (*Actions).ticks = 0;
    oldticks = 0;
    Stack.Count = 0;
    uailandmarks_clearAllMarks();
    {a = 0;
     TAmmoType a__end__ = 60;
     if (a <= a__end__) do {
                               CanUseAmmo[a] = fpcrtl_Assigned(AmmoTests[a].proc) && (uammos_HHHasAmmo(&((*Me->Hedgehog)), a) > 0);
                           } while(a++ != a__end__);}
    BotLevel = (*Me->Hedgehog).BotLevel;
    isAfterAttack = ((Me->State & gstAttacked) != 0) && ((GameFlags & gfInfAttack) == 0);
    if(isAfterAttack)
    {
        maxticks = uutils_Max(0, TurnTimeLeft - 500);
    }
    else
    {
        maxticks = uutils_Max(0, (TurnTimeLeft - 5000) - ((LongWord)4000 * BotLevel));
    }
    if(!isAfterAttack)
    {
        uai_TestAmmos(&((*Actions)), Me, false);
    }
    BestRate = uaimisc_RatePlace(Me);
    BaseRate = uutils_Max(BestRate, 0);
    if((Ammoz[(*Me->Hedgehog).CurAmmoType].Ammo.Propz & ammoprop_NeedTarget) != 0)
    {
        uaiactions_AddAction(&((*Actions)), aia_Weapon, ((LongWord)amNothing), 100 + fpcrtl_random(200), 0, 0);
    }
    if((((CurrentHedgehog->MultiShootAttacks == 0) || ((Ammoz[(*Me->Hedgehog).CurAmmoType].Ammo.Propz & ammoprop_NoMoveAfter) == 0)) && (CurrentHedgehog->Effects[heArtillery] == 0)) && (aiGravityf != 0))
    {
        tmp = fpcrtl_random(2) + 1;
        uai_Push((*Actions), (*Me), tmp);
        uai_Push((*Actions), (*Me), tmp ^ 3);
        while((Stack.Count > 0) && !StopThinking)
        {
            uai_Pop(&((*Actions)), &((*Me)));
            uaiactions_AddAction(&((*Actions)), Me->Message, aim_push, 250, 0, 0);
            if((Me->Message & gmLeft) != 0)
            {
                uaiactions_AddAction(&((*Actions)), aia_WaitXL, ufloat_hwRound(Me->X), 0, 0, 0);
            }
            else
            {
                uaiactions_AddAction(&((*Actions)), aia_WaitXR, ufloat_hwRound(Me->X), 0, 0, 0);
            }
            steps = 0;
            while(!StopThinking)
            {
                CanGo = uaimisc_HHGo(Me, &(AltMe), &(GoInfo));
                oldticks = (*Actions).ticks;
                (*Actions).ticks += GoInfo.Ticks;
                if(((*Actions).ticks > maxticks) || (TurnTimeLeft < (BestActions.ticks + 5000)))
                {
                    if(((((BotLevel < 5) && !isAfterAttack) && (BestActions.Score > 0)) && (TurnTimeLeft < (BestActions.ticks + 5000))) && (uammos_HHHasAmmo(&((*Me->Hedgehog)), amExtraTime) > 0))
                    {
                        BestActions.Count = 0;
                        uaiactions_AddAction(&(BestActions), aia_Weapon, ((LongWord)amExtraTime), 80, 0, 0);
                        uaiactions_AddAction(&(BestActions), aia_attack, aim_push, 10, 0, 0);
                        uaiactions_AddAction(&(BestActions), aia_attack, aim_release, 10, 0, 0);
                        if((BotLevel < 3) && (uammos_HHHasAmmo(&((*Me->Hedgehog)), amExtraTime) == AMMO_INFINITE))
                        {
                            {i = 1;
                             LongInt i__end__ = 3;
                             if (i <= i__end__) do {
                                                       uaiactions_AddAction(&(BestActions), aia_attack, aim_push, 100, 0, 0);
                                                       uaiactions_AddAction(&(BestActions), aia_attack, aim_release, 100, 0, 0);
                                                   } while(i++ != i__end__);}
                        }
                    }
                    break;
                }
                if(((BotLevel < 5) && (GoInfo.JumpType == jmpHJump)) && !uailandmarks_checkMark(ufloat_hwRound(Me->X), ufloat_hwRound(Me->Y), markHJumped))
                {
                    uailandmarks_addMark(ufloat_hwRound(Me->X), ufloat_hwRound(Me->Y), markHJumped);
                    if(uai_Push((*Actions), AltMe, Me->Message ^ 3))
                    {
                        {
                            if((Me->Message & gmLeft) != 0)
                            {
                                uaiactions_AddAction(&(Stack.States[((int)(Stack.Count) - 1)].MadeActions), aia_LookRight, 0, 200, 0, 0);
                            }
                            else
                            {
                                uaiactions_AddAction(&(Stack.States[((int)(Stack.Count) - 1)].MadeActions), aia_LookLeft, 0, 200, 0, 0);
                            }
                            uaiactions_AddAction(&(Stack.States[((int)(Stack.Count) - 1)].MadeActions), aia_HJump, 0, 305 + fpcrtl_random(50), 0, 0);
                            uaiactions_AddAction(&(Stack.States[((int)(Stack.Count) - 1)].MadeActions), aia_HJump, 0, 350, 0, 0);
                        }
                        uai_Push(Stack.States[((int)(Stack.Count) - 1)].MadeActions, AltMe, Me->Message);
                    }
                }
                if(((BotLevel < 3) && (GoInfo.JumpType == jmpLJump)) && !uailandmarks_checkMark(ufloat_hwRound(Me->X), ufloat_hwRound(Me->Y), markLJumped))
                {
                    uailandmarks_addMark(ufloat_hwRound(Me->X), ufloat_hwRound(Me->Y), markLJumped);
                    if(uai_Push((*Actions), AltMe, Me->Message ^ 3))
                    {
                        {
                            if((Me->Message & gmLeft) != 0)
                            {
                                uaiactions_AddAction(&(Stack.States[((int)(Stack.Count) - 1)].MadeActions), aia_LookLeft, 0, 200, 0, 0);
                            }
                            else
                            {
                                uaiactions_AddAction(&(Stack.States[((int)(Stack.Count) - 1)].MadeActions), aia_LookRight, 0, 200, 0, 0);
                            }
                            uaiactions_AddAction(&(Stack.States[((int)(Stack.Count) - 1)].MadeActions), aia_LJump, 0, 305 + fpcrtl_random(50), 0, 0);
                        }
                    }
                    if(CanGo)
                    {
                        uai_Push((*Actions), (*Me), Me->Message);
                    }
                    if(uai_Push((*Actions), AltMe, Me->Message))
                    {
                        {
                            uaiactions_AddAction(&(Stack.States[((int)(Stack.Count) - 1)].MadeActions), aia_LJump, 0, 305 + fpcrtl_random(50), 0, 0);
                        }
                    }
                    break;
                }
                if(!CanGo)
                {
                    break;
                }
                ++steps;
                (*Actions).actions[((int)((*Actions).Count) - 1)].Param = ufloat_hwRound(Me->X);
                Rate = uaimisc_RatePlace(Me);
                if(Rate > BestRate)
                {
                    BestActions = (*Actions);
                    BestActions.isWalkingToABetterPlace = true;
                    BestRate = Rate;
                    isAfterAttack = true;
                }
                else
                {
                    if(Rate < BestRate)
                    {
                        break;
                    }
                }
                if(!isAfterAttack && ((steps % 4) == 0))
                {
                    if((steps > 4) && uailandmarks_checkMark(ufloat_hwRound(Me->X), ufloat_hwRound(Me->Y), markWalkedHere))
                    {
                        break;
                    }
                    uailandmarks_addMark(ufloat_hwRound(Me->X), ufloat_hwRound(Me->Y), markWalkedHere);
                    uai_TestAmmos(&((*Actions)), Me, ((*Actions).ticks >> 12) == (oldticks >> 12));
                }
                if(GoInfo.FallPix >= FallPixForBranching)
                {
                    uai_Push((*Actions), (*Me), Me->Message ^ 3);
                }
            }
            if(BestRate > BaseRate)
            {
                return;
            }
        }
    }
};
LongInt uai_Think(PGear Me)
{
    LongInt think_result;
    TGear BackMe;
    TGear WalkMe;
    LongInt switchCount;
    LongWord currHedgehogIndex;
    LongWord itHedgehog;
    LongWord switchesNum;
    LongWord i;
    boolean switchImmediatelyAvailable;
    TActions Actions;
    dmgMod = (1.0e-2 * ufloat_hwFloat2Float(cDamageModifier)) * cDamagePercent;
    aiGravity = cGravity;
    aiGravityf = cGravityf;
    StartTicks = GameTicks;
    currHedgehogIndex = CurrentTeam->CurrHedgehog;
    itHedgehog = currHedgehogIndex;
    switchesNum = 0;
    switchImmediatelyAvailable = (CurAmmoGear != NULL) && (CurAmmoGear->Kind == gtSwitcher);
    if((*Me->Hedgehog).BotLevel != 5)
    {
        switchCount = uammos_HHHasAmmo(&((*((PGear)Me)->Hedgehog)), amSwitch);
    }
    else
    {
        switchCount = 0;
    }
    if(((((Me->State & gstAttacked) == 0) || isInMultiShoot) || bonuses.activity) || ((Me->AIHints & aihAmmosChanged) != 0))
    {
        if(Targets.Count > 0)
        {
            do {
                   WalkMe = (*CurrentTeam->Hedgehogs[itHedgehog].Gear);
                   Actions.Count = 0;
                   Actions.Pos = 0;
                   Actions.Score = 0;
                   if(switchesNum > 0)
                   {
                       if(!switchImmediatelyAvailable)
                       {
                           if(switchCount < 10)
                           {
                               Actions.Score = (-27 + (switchCount * 3)) * 4000;
                           }
                           uaiactions_AddAction(&(Actions), aia_Weapon, ((LongWord)amSwitch), 300 + fpcrtl_random(200), 0, 0);
                           uaiactions_AddAction(&(Actions), aia_attack, aim_push, 300 + fpcrtl_random(300), 0, 0);
                           uaiactions_AddAction(&(Actions), aia_attack, aim_release, 1, 0, 0);
                       }
                       {i = 1;
                        LongWord i__end__ = switchesNum;
                        if (i <= i__end__) do {
                                                  uaiactions_AddAction(&(Actions), aia_Switch, 0, 300 + fpcrtl_random(200), 0, 0);
                                              } while(i++ != i__end__);}
                   }
                   uai_Walk(&(WalkMe), &(Actions));
                   do {
                          itHedgehog = (itHedgehog + 1) % CurrentTeam->HedgehogsNumber;
                      } while(!((itHedgehog == currHedgehogIndex) || ((CurrentTeam->Hedgehogs[itHedgehog].Gear != NULL) && (CurrentTeam->Hedgehogs[itHedgehog].Effects[heFrozen] == 0))));
                   ++switchesNum;
               } while(!(((!(switchImmediatelyAvailable || (switchCount > 0)) || StopThinking) || (itHedgehog == currHedgehogIndex)) || BestActions.isWalkingToABetterPlace));
            if((StartTicks > (GameTicks - 1500)) && !StopThinking)
            {
                SDL_Delay(700);
            }
            if((BestActions.Score < -1023) && !BestActions.isWalkingToABetterPlace)
            {
                BestActions.Count = 0;
                uaimisc_FillBonuses(false);
                if(!bonuses.activity && ((Me->AIHints & aihAmmosChanged) == 0))
                {
                    if((((((GameFlags & gfInfAttack) != 0) || (CurrentHedgehog->MultiShootAttacks == 0)) && (uammos_HHHasAmmo(&((*Me->Hedgehog)), amTardis) > 0)) && ugearsutils_CanUseTardis((*Me->Hedgehog).Gear)) && (fpcrtl_random(4) < 3))
                    {
                        uaiactions_AddAction(&(BestActions), aia_Weapon, ((LongWord)amTardis), 80, 0, 0);
                        uaiactions_AddAction(&(BestActions), aia_attack, aim_push, 10, 0, 0);
                        uaiactions_AddAction(&(BestActions), aia_attack, aim_release, 10, 0, 0);
                    }
                    else
                    {
                        uaiactions_AddAction(&(BestActions), aia_Skip, 0, 250, 0, 0);
                    }
                }
                Me->AIHints = Me->AIHints & ~aihAmmosChanged;
            }
        }
        else
        {
            BestActions.Count = 0;
            uaiactions_AddAction(&(BestActions), aia_Skip, 0, 250, 0, 0);
            Me->AIHints = Me->AIHints & ~aihAmmosChanged;
        }
    }
    else
    {
        BackMe = (*Me);
        i = 4;
        while((!StopThinking && (BestActions.Count == 0)) && (i > 0))
        {
            uaimisc_FillBonuses(true);
            WalkMe = BackMe;
            Actions.Count = 0;
            Actions.Pos = 0;
            Actions.Score = 0;
            uai_Walk(&(WalkMe), &(Actions));
            if(!bonuses.activity)
            {
                --i;
            }
            if(!StopThinking)
            {
                SDL_Delay(100);
            }
        }
    }
    Me->State = Me->State & ~gstHHThinking;
    think_result = 0;
    SDL_SemPost(ThreadSem);
    return think_result;
};
void uai_StartThink(PGear Me)
{
    PSDL_Thread ThinkThread;
    if(((Me->State & ((gstAttacking | gstHHJumping) | gstMoving)) != 0) || isInMultiShoot)
    {
        return;
    }
    SDL_SemWait(ThreadSem);
    Me->State = Me->State | gstHHThinking;
    Me->Message = 0;
    BestActions.Count = 0;
    BestActions.Pos = 0;
    BestActions.Score = -2147483648;
    BestActions.isWalkingToABetterPlace = false;
    StopThinking = false;
    ThinkingHH = Me;
    uaimisc_FillTargets();
    uaimisc_FillBonuses((((Me->State & gstAttacked) != 0) && !isInMultiShoot) && ((GameFlags & gfInfAttack) == 0));
    ThinkThread = SDL_CreateThread(&(uai_Think), fpcrtl__pchar(__str1), Me);
    SDL_DetachThread(ThinkThread);
};
void uai_ProcessBot_old()
{
    enum{cStopThinkTime = 40};
    {
        if((((*CurrentHedgehog).Gear != NULL) && (((*CurrentHedgehog).Gear->State & gstHHDriven) != 0)) && ((TurnTimeLeft < (cHedgehogTurnTime - 50)) || (TurnTimeLeft > cHedgehogTurnTime)))
        {
            if(((*CurrentHedgehog).Gear->State & gstHHThinking) == 0)
            {
                if((BestActions.Pos >= BestActions.Count) && (TurnTimeLeft > cStopThinkTime))
                {
                    if((*CurrentHedgehog).Gear->Message != 0)
                    {
                        ucommands_StopMessages((*CurrentHedgehog).Gear->Message);
                        if(udebug_checkFails(((*CurrentHedgehog).Gear->Message & gmAllStoppable) == 0, __str2, true))
                        {
                            return;
                        }
                    }
                    if((*CurrentHedgehog).Gear->Message != 0)
                    {
                        return;
                    }
                    uai_StartThink((*CurrentHedgehog).Gear);
                    StartTicks = GameTicks;
                }
                else
                {
                    uaiactions_ProcessAction(&(BestActions), (*CurrentHedgehog).Gear);
                }
            }
            else
            {
                if(((((int64_t) (GameTicks)) - ((int64_t) (StartTicks))) > cMaxAIThinkTime) || (TurnTimeLeft <= cStopThinkTime))
                {
                    StopThinking = true;
                }
            }
        }
    }
};
void uai_ProcessBot()
{
    if(true)
    {
        uai_ProcessBot_old();
    }
    else
    {
        uai2_ProcessBot();
    }
};
void uai_initModule()
{
    StartTicks = 0;
    ThreadSem = SDL_CreateSemaphore(1);
};
void uai_freeModule()
{
    uai_FreeActionsList();
    SDL_DestroySemaphore(ThreadSem);
};
