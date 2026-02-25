#include "fpcrtl.h"

#include "uGears.h"
#include "uStore.h"
#include "uSound.h"
#include "uTeams.h"
#include "uRandom.h"
#include "uIO.h"
#include "uLandGraphics.h"
#include "uLocale.h"
#include "uAmmos.h"
#include "uStats.h"
#include "uVisualGears.h"
#include "uScript.h"
#include "uVariables.h"
#include "uCommands.h"
#include "uUtils.h"
#include "uTextures.h"
#include "uRenderUtils.h"
#include "uGearsRender.h"
#include "uCaptions.h"
#include "uGearsHedgehog.h"
#include "uGearsUtils.h"
#include "uGearsList.h"
#include "uGearsHandlersRope.h"
#include "uVisualGearsList.h"
#include "uGearsHandlersMess.h"
#include "uAI.h"
#include "SDLh.h"
static const string255 __str19 = STRINIT("hogsay");
static const string255 __str18 = STRINIT("skip");
static const string255 __str17 = STRINIT("...");
static const string255 __str16 = STRINIT("onSkipTurn");
static const string255 __str15 = STRINIT(",");
static const string255 __str14 = STRINIT("onSuddenDeath");
static const string255 __str13 = STRINIT("Placed flower for hog at coordinates (");
static const string255 __str12 = STRINIT("Carved a hole for hog at coordinates (");
static const string255 __str11 = STRINIT("Placed Air Mine @ (");
static const string255 __str10 = STRINIT("");
static const string255 __str9 = STRINIT("sff");
static const string255 __str8 = STRINIT("hiTicks increment (current team is local or gone)");
static const string255 __str7 = STRINIT("hiTicks increment message sent");
static const string255 __str6 = STRINIT("#");
static const string255 __str5 = STRINIT("/nextturn");
static const string255 __str4 = STRINIT("onCaseDrop");
static const string255 __str3 = STRINIT("onEndTurn");
static const string255 __str2 = STRINIT("onNewTurn");
static const string255 __str1 = STRINIT("onGameTick20");
static const string255 __str0 = STRINIT("onGameTick");
static boolean skipFlag;
static LongWord delay;
static LongWord delay2;
static enum {stInit = 0x0,
             stDelay1 = 0x1,
             stChDmg = 0x2,
             stSweep = 0x3,
             stTurnStats = 0x4,
             stChWin1 = 0x5,
             stTurnReact = 0x6,
             stDelay2 = 0x7,
             stChWin2 = 0x8,
             stWater = 0x9,
             stChWin3 = 0xa,
             stChKing = 0xb,
             stSuddenDeath = 0xc,
             stDelay3 = 0xd,
             stHealth = 0xe,
             stSpawn = 0xf,
             stDelay4 = 0x10,
             stNTurn = 0x11} step;
static LongWord NewTurnTick;
enum{delayInit = 50};
enum{delaySDStart = 1600};
enum{delaySDWarning = 1000};
enum{delayDamageTagFull = 1500};
enum{delayDamageTagShort = 500};
enum{delayTurnReact = 800};
enum{delayFinal = 100};
boolean ugears_CheckNoDamage()
{
    boolean checknodamage_result;
    PGear Gear;
    LongInt dmg;
    checknodamage_result = true;
    Gear = GearsList;
    while(Gear != NULL)
    {
        if((Gear->Kind == gtHedgehog) && (((GameFlags & gfInfAttack) == 0) || ((Gear->dX.QWordValue < _0_000004.QWordValue) && (Gear->dY.QWordValue < _0_000004.QWordValue))))
        {
            if(!isInMultiShoot)
            {
                Gear->Damage += Gear->Karma;
            }
            if((Gear->Damage != 0) && ((*Gear->Hedgehog).Effects[heInvulnerable] == 0))
            {
                checknodamage_result = false;
                dmg = Gear->Damage;
                if(Gear->Health < dmg)
                {
                    Gear->Active = true;
                    Gear->Health = 0;
                }
                else
                {
                    Gear->Health -= dmg;
                }
                ugearsutils_spawnHealthTagForHH(Gear, dmg);
                ustore_RenderHealth(&((*Gear->Hedgehog)));
                uteams_RecountTeamHealth((*Gear->Hedgehog).Team);
            }
            else
            {
                if(((GameFlags & gfKing) != 0) && !(*(*Gear->Hedgehog).Team).hasKing)
                {
                    Gear->Active = true;
                    Gear->Health = 0;
                    ustore_RenderHealth(&((*Gear->Hedgehog)));
                    uteams_RecountTeamHealth((*Gear->Hedgehog).Team);
                }
            }
            if(!isInMultiShoot)
            {
                Gear->Karma = 0;
            }
            Gear->Damage = 0;
        }
        Gear = Gear->NextGear;
    }
    return checknodamage_result;
};
boolean ugears_DoDelay()
{
    boolean dodelay_result;
    if(delay <= 0)
    {
        delay = 1;
    }
    else
    {
        --delay;
    }
    dodelay_result = delay == 0;
    return dodelay_result;
};
boolean ugears_CheckMinionsDie()
{
    boolean checkminionsdie_result;
    PGear Gear;
    checkminionsdie_result = false;
    if((GameFlags & gfKing) == 0)
    {
        return checkminionsdie_result;
    }
    Gear = GearsList;
    while(Gear != NULL)
    {
        if(((Gear->Kind == gtHedgehog) && !(*Gear->Hedgehog).King) && !(*(*Gear->Hedgehog).Team).hasKing)
        {
            checkminionsdie_result = true;
            return checkminionsdie_result;
        }
        Gear = Gear->NextGear;
    }
    return checkminionsdie_result;
};
void ugears_HealthMachine()
{
    PGear Gear;
    PTeam team;
    LongWord i;
    boolean flag;
    LongWord tmp;
    Gear = GearsList;
    while(Gear != NULL)
    {
        if(Gear->Kind == gtHedgehog)
        {
            tmp = 0;
            if(((*Gear->Hedgehog).Effects[hePoisoned] != 0) && ((*Gear->Hedgehog).Effects[heFrozen] == 0))
            {
                tmp += ugearsutils_ModifyDamage((*Gear->Hedgehog).Effects[hePoisoned], Gear);
                if((GameFlags & gfResetHealth) != 0)
                {
                    --(*Gear->Hedgehog).InitialHealth;
                }
            }
            if(TotalRoundsPre > (cSuddenDTurns - 1))
            {
                tmp += cHealthDecrease;
                if((GameFlags & gfResetHealth) != 0)
                {
                    (*Gear->Hedgehog).InitialHealth -= cHealthDecrease;
                }
            }
            if((*Gear->Hedgehog).King)
            {
                flag = false;
                team = (*Gear->Hedgehog).Team;
                {i = 0;
                 LongWord i__end__ = ((int)(team->HedgehogsNumber) - 1);
                 if (i <= i__end__) do {
                                           if(((team->Hedgehogs[i].Gear != NULL) && !team->Hedgehogs[i].King) && ((*team->Hedgehogs[i].Gear).Health > (*team->Hedgehogs[i].Gear).Damage))
                                           {
                                               flag = true;
                                           }
                                       } while(i++ != i__end__);}
                if(!flag)
                {
                    tmp += 5;
                    if((GameFlags & gfResetHealth) != 0)
                    {
                        (*Gear->Hedgehog).InitialHealth -= 5;
                    }
                }
            }
            if((*Gear->Hedgehog).InitialHealth < 1)
            {
                (*Gear->Hedgehog).InitialHealth = 1;
            }
            if(tmp > 0)
            {
                tmp = uutils_Min(tmp, uutils_Max(0, (Gear->Health - 1) - Gear->Damage));
                Gear->Damage += tmp;
                if(tmp > 0)
                {
                    ugearsutils_HHHurt(Gear->Hedgehog, dsPoison, tmp);
                }
            }
        }
        Gear = Gear->NextGear;
    }
};
void ugears_processFlakes()
{
    LongWord i;
    if((GameTicks & 0x7) == 0)
    {
        {i = 1;
         LongWord i__end__ = FlakesCount;
         if (i <= i__end__) do {
                                   ugearshandlersmess_doStepSnowflake(&(Flakes[i - 1]));
                               } while(i++ != i__end__);}
    }
};
void ugears_ProcessGears()
{
    PGear t;
    PGear tmpGear;
    LongInt i;
    LongInt j;
    LongInt AliveCount;
    astring s;
    LongWord prevtime;
    boolean stirFallers;
    stirFallers = false;
    prevtime = TurnTimeLeft;
    uscript_ScriptCall_1(__str0);
    if((GameTicks % 20) == 0)
    {
        uscript_ScriptCall_1(__str1);
    }
    if(GameTicks == NewTurnTick)
    {
        uscript_ScriptCall_1(__str2);
    }
    PrvInactive = AllInactive;
    AllInactive = true;
    if((StepSoundTimer > 0) && (StepSoundChannel < 0))
    {
        StepSoundChannel = usound_LoopSound_1(sndSteps);
    }
    else
    {
        if((StepSoundTimer == 0) && (StepSoundChannel > -1))
        {
            usound_StopSoundChan_1(StepSoundChannel);
            StepSoundChannel = -1;
        }
    }
    if(StepSoundTimer > 0)
    {
        StepSoundTimer -= 1;
    }
    ugears_processFlakes();
    t = GearsList;
    while(t != NULL)
    {
        curHandledGear = t;
        t = curHandledGear->NextGear;
        if((((GameTicks & 0x1fff) == 0) && (curHandledGear->Kind == gtCase)) && (curHandledGear->Pos != posCaseHealth))
        {
            stirFallers = true;
        }
        if((curHandledGear->Message & gmDelete) != 0)
        {
            ugearslist_DeleteGear(curHandledGear);
        }
        else
        {
            if((curHandledGear->Message & gmRemoveFromList) != 0)
            {
                ugearslist_RemoveGearFromList(curHandledGear);
                if((curHandledGear->Message & gmAddToList) != 0)
                {
                    ugearslist_InsertGearToList(curHandledGear);
                }
                curHandledGear->Message = curHandledGear->Message & ~(gmRemoveFromList | gmAddToList);
            }
            if(curHandledGear->Active)
            {
                if(!cOnlyStats && curHandledGear->RenderTimer)
                {
                    if(((curHandledGear->Kind == gtMine) || (curHandledGear->Kind == gtSMine) || (curHandledGear->Kind == gtAirMine)))
                    {
                        if(curHandledGear->Tex == NULL)
                        {
                            if((curHandledGear->Karma == 1) && !(((GameType == gmtDemo) || (GameType == gmtRecord))))
                            {
                                curHandledGear->Tex = urenderutils_RenderStringTex(trmsg[sidUnknownGearValue], 0xff808080, fntSmall);
                            }
                            else
                            {
                                utextures_FreeAndNilTexture(&(curHandledGear->Tex));
                                i = curHandledGear->Timer / 1000;
                                j = (curHandledGear->Timer % 1000) / 100;
                                if(j == 0)
                                {
                                    curHandledGear->Tex = urenderutils_RenderStringTex(fpcrtl_str2astr(uutils_IntToStr(i)), 0xff808080, fntSmall);
                                }
                                else
                                {
                                    curHandledGear->Tex = urenderutils_RenderStringTex(fpcrtl_str2astr(_strconcat(_strappend(uutils_IntToStr(i), lDecimalSeparator), uutils_IntToStr(j))), 0xff808080, fntSmall);
                                }
                            }
                        }
                    }
                    else
                    {
                        if((curHandledGear->Timer > 500) && ((curHandledGear->Timer % 1000) == 0))
                        {
                            utextures_FreeAndNilTexture(&(curHandledGear->Tex));
                            curHandledGear->Tex = urenderutils_RenderStringTex(fpcrtl_str2astr(uutils_IntToStr(curHandledGear->Timer / 1000)), cWhiteColor, fntSmall);
                        }
                    }
                }
                curHandledGear->doStep(curHandledGear);
            }
        }
    }
    if(stirFallers)
    {
        t = GearsList;
        while(t != NULL)
        {
            if((t->Kind == gtGenericFaller) && (t->Tag == 1))
            {
                t->Active = true;
                t->X = ufloat_int2hwFloat(urandom_GetRandom(rightX - leftX) + leftX);
                t->Y = ufloat_int2hwFloat(urandom_GetRandom(LAND_HEIGHT - topY) + topY);
                t->dX = ufloat_hwFloat_hwFloat_op_sub(_90, ufloat_hwFloat_hwFloat_op_mul(urandom_GetRandomf(), _360));
                t->dY = ufloat_hwFloat_hwFloat_op_sub(_90, ufloat_hwFloat_hwFloat_op_mul(urandom_GetRandomf(), _360));
            }
            t = t->NextGear;
        }
    }
    curHandledGear = NULL;
    if(AllInactive)
    {
        switch(step)
        {case stInit:{
                         if(!bBetweenTurns && !isInMultiShoot)
                         {
                             uscript_ScriptCall_1(__str3);
                         }
                         delay = delayInit;
                         ++step;
                     }
                     break;
         case stDelay1:{
                           if(ugears_DoDelay())
                           {
                               ++step;
                           }
                       }
                       break;
         case stChDmg:if(ugears_CheckNoDamage())
                      {
                          ++step;
                      }
                      else
                      {
                          if(!bBetweenTurns && !isInMultiShoot)
                          {
                              delay = delayDamageTagShort;
                          }
                          else
                          {
                              delay = delayDamageTagFull;
                          }
                          step = stDelay1;
                      }
                      break;
         case stSweep:if(ulandgraphics_SweepDirty())
                      {
                          ugearsutils_SetAllToActive();
                          step = stChDmg;
                      }
                      else
                      {
                          ++step;
                      }
                      break;
         case stTurnStats:{
                              if(!bBetweenTurns && !isInMultiShoot)
                              {
                                  ustats_TurnStats();
                              }
                              ++step;
                          }
                          break;
         case stChWin1:{
                           uteams_CheckForWin();
                           ++step;
                       }
                       break;
         case stTurnReact:{
                              if(!bBetweenTurns && !isInMultiShoot)
                              {
                                  ustats_TurnReaction();
                                  ustats_TurnStatsReset();
                                  delay = delayTurnReact;
                                  ++step;
                              }
                              else
                              {
                                  step += 2;
                              }
                          }
                          break;
         case stDelay2:if(ugears_DoDelay())
                       {
                           ++step;
                       }
                       break;
         case stChWin2:{
                           uteams_CheckForWin();
                           ++step;
                       }
                       break;
         case stWater:if(!bBetweenTurns && !isInMultiShoot)
                      {
                          if(TotalRoundsPre == (cSuddenDTurns + 1))
                          {
                              bWaterRising = true;
                          }
                          if(bWaterRising && (cWaterRise > 0))
                          {
                              bDuringWaterRise = true;
                              ugearslist_AddGear_7(0, 0, gtWaterUp, 0, _0, _0, 0)->Tag = cWaterRise;
                          }
                          ++step;
                      }
                      else
                      {
                          step += 2;
                      }
                      break;
         case stChWin3:{
                           uteams_CheckForWin();
                           bDuringWaterRise = false;
                           ++step;
                       }
                       break;
         case stChKing:{
                           if(!isInMultiShoot && ugears_CheckMinionsDie())
                           {
                               step = stChDmg;
                           }
                           else
                           {
                               ++step;
                           }
                       }
                       break;
         case stSuddenDeath:{
                                if(((cWaterRise != 0) || (cHealthDecrease != 0)) && !(isInMultiShoot || bBetweenTurns))
                                {
                                    if((TotalRoundsPre == cSuddenDTurns) && !SuddenDeath)
                                    {
                                        ugears_StartSuddenDeath();
                                        delay = delaySDStart;
                                        ++step;
                                    }
                                    else
                                    {
                                        if((TotalRoundsPre < cSuddenDTurns) && ((LastSuddenDWarn == -2) || (LastSuddenDWarn != TotalRoundsPre)))
                                        {
                                            i = cSuddenDTurns - TotalRoundsPre;
                                            s = fpcrtl_str2astr(uutils_IntToStr(i));
                                            if((i > 0) && (((i <= 3) || (i == 7)) || (((i % 50) == 0) || ((i <= 25) && ((i % 5) == 0)))))
                                            {
                                                if(i == 1)
                                                {
                                                    ucaptions_AddCaption(trmsg[sidRoundSD], capcolDefault, capgrpGameState);
                                                }
                                                else
                                                {
                                                    ucaptions_AddCaption(ulocale_FormatA_2(trmsg[sidRoundsSD], s), capcolDefault, capgrpGameState);
                                                }
                                                delay = delaySDWarning;
                                                ++step;
                                                LastSuddenDWarn = TotalRoundsPre;
                                            }
                                            else
                                            {
                                                step += 2;
                                            }
                                        }
                                        else
                                        {
                                            step += 2;
                                        }
                                    }
                                }
                                else
                                {
                                    step += 2;
                                }
                            }
                            break;
         case stDelay3:if(ugears_DoDelay())
                       {
                           ++step;
                       }
                       break;
         case stHealth:{
                           if((bBetweenTurns || isInMultiShoot) || (TotalRoundsReal == -1))
                           {
                               ++step;
                           }
                           else
                           {
                               bBetweenTurns = true;
                               ugears_HealthMachine();
                               step = stChDmg;
                           }
                       }
                       break;
         case stSpawn:{
                          if(!isInMultiShoot)
                          {
                              tmpGear = ugearsutils_SpawnBoxOfSmth();
                              if(tmpGear != NULL)
                              {
                                  uscript_ScriptCall_2(__str4, tmpGear->uid);
                              }
                              else
                              {
                                  uscript_ScriptCall_1(__str4);
                              }
                              delay = delayFinal;
                              ++step;
                          }
                          else
                          {
                              step += 2;
                          }
                      }
                      break;
         case stDelay4:if(ugears_DoDelay())
                       {
                           ++step;
                       }
                       break;
         case stNTurn:{
                          if(isInMultiShoot)
                          {
                              isInMultiShoot = false;
                          }
                          else
                          {
                              {
                                  if((((*CurrentHedgehog).Gear != NULL) && (((*CurrentHedgehog).Gear->State & gstAttacked) == 0)) && ((*CurrentHedgehog).MultiShootAttacks > 0))
                                  {
                                      uammos_OnUsedAmmo(&((*CurrentHedgehog)));
                                  }
                              }
                              ugears_EndTurnCleanup();
                              uai_FreeActionsList();
                              ucommands_ParseCommand_2(__str5, true);
                              uteams_SwitchHedgehog();
                              uteams_AfterSwitchHedgehog();
                              bBetweenTurns = false;
                              NewTurnTick = GameTicks + 1;
                          }
                          step = 0;
                      }
                      break;
         default: break;}
    }
    else
    {
        if((GameFlags & gfInfAttack) != 0)
        {
            if(delay2 == 0)
            {
                delay2 = cInactDelay * 50;
            }
            else
            {
                --delay2;
                if((((((delay2 % cInactDelay) == 0) && (CurrentHedgehog != NULL)) && (CurrentHedgehog->Gear != NULL)) && !CurrentHedgehog->Unplaced) && !PlacingHogs)
                {
                    if((((*CurrentHedgehog->Gear).State & gstAttacked) != 0) && ((Ammoz[CurrentHedgehog->CurAmmoType].Ammo.Propz & ammoprop_NeedTarget) != 0))
                    {
                        (*CurrentHedgehog->Gear).State = (*CurrentHedgehog->Gear).State | gstChooseTarget;
                        isCursorVisible = true;
                    }
                    (*CurrentHedgehog->Gear).State = (*CurrentHedgehog->Gear).State & ~gstAttacked;
                }
                if(delay2 == 0)
                {
                    if(((CurrentHedgehog->Gear != NULL) && (((*CurrentHedgehog->Gear).State & gstAttacked) == 0)) && (CurAmmoGear == NULL))
                    {
                        ulandgraphics_SweepDirty();
                    }
                    if(((CurrentHedgehog->Gear == NULL) || (((*CurrentHedgehog->Gear).State & gstHHDriven) == 0)) || ((*CurrentHedgehog->Gear).Damage == 0))
                    {
                        ugears_CheckNoDamage();
                    }
                    AliveCount = 0;
                    {i = 0;
                     LongInt i__end__ = ((int)(ClansCount) - 1);
                     if (i <= i__end__) do {
                                               if(ClansArray[i]->ClanHealth > 0)
                                               {
                                                   ++AliveCount;
                                               }
                                           } while(i++ != i__end__);}
                    if((AliveCount <= 1) && ((GameFlags & gfOneClanMode) == 0))
                    {
                        step = stChDmg;
                        if(TagTurnTimeLeft == 0)
                        {
                            TagTurnTimeLeft = TurnTimeLeft;
                        }
                        GameOver = true;
                        TurnTimeLeft = 0;
                    }
                }
            }
        }
    }
    if(TurnTimeLeft > 0)
    {
        if(ugears_IsClockRunning())
        {
            if(((((cHedgehogTurnTime > TurnTimeLeft) && (CurrentHedgehog->Gear != NULL)) && (((*CurrentHedgehog->Gear).State & gstAttacked) == 0)) && !IsGetAwayTime) && (ReadyTimeLeft == 0))
            {
                if((TurnTimeLeft == 5000) && (cHedgehogTurnTime >= 10000))
                {
                    usound_PlaySoundV_2(sndHurry, CurrentTeam->voicepack);
                }
                else
                {
                    if(TurnTimeLeft == 4000)
                    {
                        usound_PlaySound_1(sndCountdown4);
                    }
                    else
                    {
                        if(TurnTimeLeft == 3000)
                        {
                            usound_PlaySound_1(sndCountdown3);
                        }
                        else
                        {
                            if(TurnTimeLeft == 2000)
                            {
                                usound_PlaySound_1(sndCountdown2);
                            }
                            else
                            {
                                if(TurnTimeLeft == 1000)
                                {
                                    usound_PlaySound_1(sndCountdown1);
                                }
                            }
                        }
                    }
                }
            }
            if(ReadyTimeLeft > 0)
            {
                if((((ReadyTimeLeft == 2000) && (LastVoice.snd == sndNone)) && !PlacingHogs) && !CinematicScript)
                {
                    usound_AddVoice_2(sndComeonthen, CurrentTeam->voicepack);
                }
                --ReadyTimeLeft;
            }
            else
            {
                --TurnTimeLeft;
            }
        }
    }
    if((TurnTimeLeft == 0) && (ReadyTimeLeft == 0))
    {
        ++TimeNotInTurn;
    }
    else
    {
        TimeNotInTurn = 0;
    }
    if(skipFlag)
    {
        if(TagTurnTimeLeft == 0)
        {
            TagTurnTimeLeft = TurnTimeLeft;
        }
        TurnTimeLeft = 0;
        skipFlag = false;
        ++(*CurrentHedgehog->Team).stats.TurnSkips;
    }
    if((GameTicks & 0xffff) == 0xffff)
    {
        if(!CurrentTeam->ExtDriven)
        {
            uio_SendIPC(__str6);
            uutils_AddFileLog(__str7);
        }
        if(!CurrentTeam->ExtDriven || CurrentTeam->hasGone)
        {
            uutils_AddFileLog(__str8);
            ++hiTicks;
        }
    }
    urandom_AddRandomness(CheckSum);
    TurnClockActive = prevtime != TurnTimeLeft;
    ++GameTicks;
    if(OuchTauntTimer > 0)
    {
        --OuchTauntTimer;
    }
    if(fastForward && (GameTicks == FFGameTick))
    {
        ucommands_ParseCommand_2(__str9, true);
    }
};
void ugears_EndTurnCleanup()
{
    LongInt i;
    PGear t;
    SpeechText = __str10;
    if((GameFlags & gfLowGravity) == 0)
    {
        cGravity = ufloat_hwFloat_LongInt_op_mul(cMaxWindSpeed, 2);
        cGravityf = 2.5e-4 * 2;
        cLowGravity = false;
    }
    if((GameFlags & gfVampiric) == 0)
    {
        cVampiric = false;
    }
    cDamageModifier = _1;
    if((GameFlags & gfLaserSight) == 0)
    {
        cLaserSighting = false;
        cLaserSightingSniper = false;
    }
    if(CurrentTeam != NULL)
    {
        {
            {i = 0;
             LongInt i__end__ = cMaxHHIndex;
             if (i <= i__end__) do {
                                       {
                                           if((*CurrentTeam).Hedgehogs[i].Gear != NULL)
                                           {
                                               if((GameFlags & gfInvulnerable) == 0)
                                               {
                                                   (*(*CurrentTeam).Hedgehogs[i].Gear->Hedgehog).Effects[heInvulnerable] = 0;
                                               }
                                               if((*(*CurrentTeam).Hedgehogs[i].Gear->Hedgehog).Effects[heArtillery] == 2)
                                               {
                                                   (*(*CurrentTeam).Hedgehogs[i].Gear->Hedgehog).Effects[heArtillery] = 0;
                                               }
                                           }
                                       }
                                   } while(i++ != i__end__);}
        }
    }
    t = GearsList;
    while(t != NULL)
    {
        t->PortalCounter = 0;
        if((((GameFlags & gfResetHealth) != 0) && (t->Kind == gtHedgehog)) && (t->Health < (*t->Hedgehog).InitialHealth))
        {
            i = (*t->Hedgehog).InitialHealth - t->Health;
            t->Health = (*t->Hedgehog).InitialHealth;
            if(i > 0)
            {
                ugearsutils_HHHeal_4(t->Hedgehog, i, false, 0x00ff0040);
            }
            ustore_RenderHealth(&((*t->Hedgehog)));
        }
        t = t->NextGear;
    }
    if((((GameFlags & gfResetWeps) != 0) && !PlacingHogs) && !PlacingKings)
    {
        uammos_ResetWeapons();
    }
    if((GameFlags & gfResetHealth) != 0)
    {
        {i = 0;
         LongInt i__end__ = ((int)(TeamsCount) - 1);
         if (i <= i__end__) do {
                                   uteams_RecountTeamHealth(TeamsArray[i]);
                               } while(i++ != i__end__);}
    }
};
void ugears_DrawGears()
{
    PGear Gear;
    LongInt x;
    LongInt y;
    LongWord i;
    Gear = GearsList;
    while(Gear != NULL)
    {
        if(((Gear->State & gstInvisible) == 0) && ((Gear->Message & gmRemoveFromList) == 0))
        {
            x = ufloat_hwRound(Gear->X) + WorldDx;
            y = ufloat_hwRound(Gear->Y) + WorldDy;
            ugearsrender_RenderGear(Gear, x, y);
        }
        Gear = Gear->NextGear;
    }
    {i = 1;
     LongWord i__end__ = FlakesCount;
     if (i <= i__end__) do {
                               Gear = &(Flakes[i - 1]);
                               if(((Gear->State & gstInvisible) == 0) && ((Gear->Message & gmRemoveFromList) == 0))
                               {
                                   x = ufloat_hwRound(Gear->X) + WorldDx;
                                   y = ufloat_hwRound(Gear->Y) + WorldDy;
                                   ugearsrender_RenderGear(Gear, x, y);
                               }
                           } while(i++ != i__end__);}
    if(SpeechHogNumber > 0)
    {
        ugearsrender_DrawHHOrder();
    }
};
void ugears_DrawGearsGui()
{
    PGear Gear;
    LongInt x;
    LongInt y;
    Gear = GearsList;
    while(Gear != NULL)
    {
        x = ufloat_hwRound(Gear->X) + WorldDx;
        y = ufloat_hwRound(Gear->Y) + WorldDy;
        if(Gear->Kind == gtAirMine)
        {
            ugearsrender_RenderAirMineGuiExtras(Gear, x, y);
        }
        ugearsrender_RenderGearHealth(Gear, x, y);
        ugearsrender_RenderGearTimer(Gear, x, y);
        if(Gear->Kind == gtHedgehog)
        {
            ugearsrender_RenderHHGuiExtras(Gear, x, y);
        }
        Gear = Gear->NextGear;
    }
};
void ugears_DrawFinger()
{
    PGear Gear;
    LongInt x;
    LongInt y;
    if((CurrentHedgehog != NULL) && (CurrentHedgehog->Gear != NULL))
    {
        Gear = CurrentHedgehog->Gear;
        x = ufloat_hwRound(Gear->X) + WorldDx;
        y = ufloat_hwRound(Gear->Y) + WorldDy;
        ugearsrender_RenderFinger(Gear, x, y);
    }
};
void ugears_FreeGearsList()
{
    PGear t;
    PGear tt;
    tt = GearsList;
    GearsList = NULL;
    while(tt != NULL)
    {
        utextures_FreeAndNilTexture(&(tt->Tex));
        t = tt;
        tt = tt->NextGear;
        fpcrtl_dispose(t);
    }
};
void ugears_AddLandSentries(LongWord count)
{
    LongInt i;
    LongInt x;
    LongInt y;
    LongInt swapIndex;
    typedef TPoint positions_tt[(1023 + 1)];
    positions_tt positions;
    LongInt positionsCount;
    LongInt tries;
    positionsCount = 0;
    tries = 2048;
    while((positionsCount < 1024) && (tries > 0))
    {
        x = (leftX + cHHRadius) + urandom_GetRandom((rightX - leftX) - (2 * cHHRadius));
        y = cHHRadius;
        while(y < cWaterLine)
        {
            do {
                   y += cHHRadius;
               } while(!((y >= cWaterLine) || (ugearsutils_CountLand(x, y, cHHRadius - 1, 1, lfAll, 0) == 0)));
            if(y < cWaterLine)
            {
                do {
                       ++y;
                   } while(!((y >= cWaterLine) || (ugearsutils_CountLand(x, y, cHHRadius - 1, 1, lfAll, 0) != 0)));
                if(y < cWaterLine)
                {
                    swapIndex = urandom_GetRandom(positionsCount + 1);
                    if(swapIndex == positionsCount)
                    {
                        positions[positionsCount].x = x;
                        positions[positionsCount].y = y;
                    }
                    else
                    {
                        positions[positionsCount].x = positions[swapIndex].x;
                        positions[positionsCount].y = positions[swapIndex].y;
                        positions[swapIndex].x = x;
                        positions[swapIndex].y = y;
                    }
                    ++positionsCount;
                    if(positionsCount >= 1024)
                    {
                        break;
                    }
                    y += cHHRadius * 2;
                }
                else
                {
                    --tries;
                }
            }
            else
            {
                --tries;
            }
        }
    }
    {i = 0;
     LongInt i__end__ = uutils_Min(count, positionsCount) - 1;
     if (i <= i__end__) do {
                               ugearslist_AddGear_7(positions[i].x, positions[i].y - cHHRadius, gtSentry, 0, _0, _0, 0)->Hedgehog = NULL;
                           } while(i++ != i__end__);}
};
LongWord ugears_AddWaterSentries(LongWord count)
{
    LongWord addwatersentries_result;
    LongInt i;
    LongInt x;
    LongInt y;
    typedef TPoint positions_tt[(255 + 1)];
    positions_tt positions;
    LongInt positionsCount;
    LongInt tries;
    addwatersentries_result = 0;
    positionsCount = 0;
    tries = 512;
    while((positionsCount < 256) && (tries > 0))
    {
        x = (leftX + cHHRadius) + urandom_GetRandom((rightX - leftX) - (2 * cHHRadius));
        y = cWaterLine - (3 * cHHRadius);
        if(ugearsutils_CountLand(x, y, cHHRadius - 1, 1, lfAll, 0) == 0)
        {
            positions[positionsCount].x = x;
            positions[positionsCount].y = y;
            ++positionsCount;
            if(positionsCount >= 256)
            {
                break;
            }
        }
    }
    {i = 0;
     LongInt i__end__ = uutils_Min(count, positionsCount) - 1;
     if (i <= i__end__) do {
                               ugearslist_AddGear_7(positions[i].x, positions[i].y - cHHRadius, gtSentry, 0, _0, _0, 0)->Hedgehog = NULL;
                               ++addwatersentries_result;
                           } while(i++ != i__end__);}
    return addwatersentries_result;
};
void ugears_AddMiscGears()
{
    LongWord p;
    LongWord i;
    LongWord j;
    LongWord t;
    LongWord h;
    LongWord unplaced;
    LongInt rx;
    LongInt ry;
    hwFloat rdx;
    hwFloat rdy;
    PGear Gear;
    ugearslist_AddGear_7(0, 0, gtATStartGame, 0, _0, _0, 2000);
    i = 0;
    unplaced = 0;
    while((i < cLandMines) && (unplaced < 4))
    {
        Gear = ugearslist_AddGear_7(0, 0, gtMine, 0, _0, _0, 0);
        Gear->Hedgehog = NULL;
        ugearsutils_FindPlace_4(&(Gear), false, 0, LAND_WIDTH);
        if(Gear == NULL)
        {
            ++unplaced;
        }
        else
        {
            unplaced = 0;
        }
        ++i;
    }
    i = 0;
    unplaced = 0;
    while((i < cExplosives) && (unplaced < 4))
    {
        Gear = ugearslist_AddGear_7(0, 0, gtExplosives, 0, _0, _0, 0);
        Gear->Hedgehog = NULL;
        ugearsutils_FindPlace_4(&(Gear), false, 0, LAND_WIDTH);
        if(Gear == NULL)
        {
            ++unplaced;
        }
        else
        {
            unplaced = 0;
            ucollisions_AddCI(Gear);
        }
        ++i;
    }
    i = 0;
    j = 0;
    p = 0;
    unplaced = 0;
    if(cAirMines > 0)
    {
        Gear = ugearslist_AddGear_7(0, 0, gtAirMine, 0, _0, _0, 0);
    }
    while((i < cAirMines) && (j < (1000 * cAirMines)))
    {
        p = 0;
        if(hasBorder || (WorldEdge == weBounce))
        {
            rx = (leftX + urandom_GetRandom((rightX - leftX) - 16)) + 8;
        }
        else
        {
            rx = (leftX + urandom_GetRandom((rightX - leftX) + 400)) - 200;
        }
        if(hasBorder)
        {
            ry = (topY + urandom_GetRandom((LAND_HEIGHT - topY) - 16)) + 8;
        }
        else
        {
            ry = (topY + urandom_GetRandom((LAND_HEIGHT - topY) + 400)) - 200;
        }
        Gear->X = ufloat_int2hwFloat(uutils_CalcWorldWrap(rx, Gear->Radius));
        Gear->Y = ufloat_int2hwFloat(ry);
        if((((ulandgraphics_CheckLandValue(rx, ry, 0xffff) && (ucollisions_TestCollisionYwithGear(Gear, -1) == 0)) && (ucollisions_TestCollisionXwithGear(Gear, 1) == 0)) && (ucollisions_TestCollisionXwithGear(Gear, -1) == 0)) && (ucollisions_TestCollisionYwithGear(Gear, 1) == 0))
        {
            t = 0;
            while((t < TeamsCount) && (p == 0))
            {
                h = 0;
                {
                    while((h <= cMaxHHIndex) && (p == 0))
                    {
                        if((*TeamsArray[t]).Hedgehogs[h].Gear != NULL)
                        {
                            rdx = ufloat_hwFloat_hwFloat_op_sub(Gear->X, (*(*TeamsArray[t]).Hedgehogs[h].Gear).X);
                            rdy = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, (*(*TeamsArray[t]).Hedgehogs[h].Gear).Y);
                            if((Gear->Angle < 0xffffffff) && (((rdx.Round + rdy.Round) < Gear->Angle) && (ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ufloat_hwSqr(rdx), ufloat_hwSqr(rdy))) < fpcrtl_sqr(Gear->Angle))))
                            {
                                p = 1;
                            }
                        }
                        ++h;
                    }
                }
                ++t;
            }
            if(p == 0)
            {
                ++i;
                uutils_AddFileLog(_strappend(_strconcat(_strappend(_strconcat(__str11, uutils_IntToStr(rx)), 0x2c), uutils_IntToStr(ry)), 0x29));
                if(i < cAirMines)
                {
                    Gear = ugearslist_AddGear_7(0, 0, gtAirMine, 0, _0, _0, 0);
                }
                Gear->Hedgehog = NULL;
            }
        }
        else
        {
            p = 1;
        }
        ++j;
    }
    if(p != 0)
    {
        ugearslist_DeleteGear(Gear);
    }
    if(cSentries > 10)
    {
        ugears_AddLandSentries(((int64_t) (cSentries)) - ((int64_t) (ugears_AddWaterSentries(cSentries / 10))));
    }
    else
    {
        ugears_AddLandSentries(cSentries);
    }
    if((GameFlags & gfLowGravity) != 0)
    {
        cGravity = cMaxWindSpeed;
        cGravityf = 2.5e-4;
        cLowGravity = true;
    }
    if((GameFlags & gfVampiric) != 0)
    {
        cVampiric = true;
    }
    Gear = GearsList;
    if((GameFlags & gfInvulnerable) != 0)
    {
        {p = 0;
         LongWord p__end__ = ((int)(ClansCount) - 1);
         if (p <= p__end__) do {
                                   {
                                       {j = 0;
                                        LongWord j__end__ = ((int)((*ClansArray[p]).TeamsNumber) - 1);
                                        if (j <= j__end__) do {
                                                                  {
                                                                      {i = 0;
                                                                       LongWord i__end__ = cMaxHHIndex;
                                                                       if (i <= i__end__) do {
                                                                                                 {
                                                                                                     (*(*ClansArray[p]).Teams[j]).Hedgehogs[i].Effects[heInvulnerable] = 1;
                                                                                                 }
                                                                                             } while(i++ != i__end__);}
                                                                  }
                                                              } while(j++ != j__end__);}
                                   }
                               } while(p++ != p__end__);}
    }
    if((GameFlags & gfLaserSight) != 0)
    {
        cLaserSighting = true;
    }
    {i = ((LAND_WIDTH * LAND_HEIGHT) / 524288) + 2;
     LongWord i__end__ = 0;
     if (i >= i__end__) do {
                               rx = urandom_GetRandom(rightX - leftX) + leftX;
                               ry = urandom_GetRandom(LAND_HEIGHT - topY) + topY;
                               rdx = ufloat_hwFloat_hwFloat_op_sub(_90, ufloat_hwFloat_hwFloat_op_mul(urandom_GetRandomf(), _360));
                               rdy = ufloat_hwFloat_hwFloat_op_sub(_90, ufloat_hwFloat_hwFloat_op_mul(urandom_GetRandomf(), _360));
                               Gear = ugearslist_AddGear_7(rx, ry, gtGenericFaller, gstInvisible, rdx, rdy, 0xffffffff);
                               Gear->Tag = 1;
                           } while(i-- != i__end__);}
    snowRight = uutils_Max(LAND_WIDTH, 4096) + 512;
    snowLeft = -(snowRight - LAND_WIDTH);
    FlakesCount = 0;
    if(!hasBorder && cSnow)
    {
        FlakesCount = (vobCount * ((LongWord)uutils_Max(LAND_WIDTH, 4096))) / 2048;
        fpcrtl_SetLength(Flakes, FlakesCount);
        {i = 0;
         LongWord i__end__ = FlakesCount - 1;
         if (i <= i__end__) do {
                                   rx = urandom_GetRandom(snowRight - snowLeft);
                                   ry = urandom_GetRandom(750);
                                   ugearslist_initializeGear(&(Flakes[i]), rx + snowLeft, (((LongInt)LAND_HEIGHT) + ry) - 1300, gtFlake, 0, _0, _0, 0, 0);
                               } while(i++ != i__end__);}
    }
};
void ugears_SortHHsByClan()
{
    LongInt n;
    LongInt newn;
    LongInt i;
    LongInt j;
    LongInt k;
    LongInt p;
    typedef PHedgehog ar_tt[cMaxHHs];
    ar_tt ar;
    ar_tt clar;
    LongWord Count;
    LongWord clCount;
    hwFloat tmpX;
    hwFloat tmpY;
    PHedgehog hh1;
    PHedgehog hh2;
    Count = 0;
    {p = 0;
     LongInt p__end__ = ClansCount - 1;
     if (p <= p__end__) do {
                               {
                                   clCount = 0;
                                   {j = 0;
                                    LongInt j__end__ = ((int)((*SpawnClansArray[p]).TeamsNumber) - 1);
                                    if (j <= j__end__) do {
                                                              {
                                                                  {i = 0;
                                                                   LongInt i__end__ = cMaxHHIndex;
                                                                   if (i <= i__end__) do {
                                                                                             if((*(*SpawnClansArray[p]).Teams[j]).Hedgehogs[i].Gear != NULL)
                                                                                             {
                                                                                                 clar[clCount] = &((*(*SpawnClansArray[p]).Teams[j]).Hedgehogs[i]);
                                                                                                 ++clCount;
                                                                                             }
                                                                                         } while(i++ != i__end__);}
                                                              }
                                                          } while(j++ != j__end__);}
                                   {i = 0;
                                    LongInt i__end__ = clCount - 1;
                                    if (i <= i__end__) do {
                                                              j = urandom_GetRandom(clCount);
                                                              k = urandom_GetRandom(clCount);
                                                              if(clar[j] != clar[k])
                                                              {
                                                                  hh1 = clar[j];
                                                                  clar[j] = clar[k];
                                                                  clar[k] = hh1;
                                                              }
                                                          } while(i++ != i__end__);}
                                   {i = 0;
                                    LongInt i__end__ = clCount - 1;
                                    if (i <= i__end__) do {
                                                              ar[Count] = clar[i];
                                                              ++Count;
                                                          } while(i++ != i__end__);}
                               }
                           } while(p++ != p__end__);}
    n = Count - 1;
    do {
           newn = 0;
           {i = 1;
            LongInt i__end__ = n;
            if (i <= i__end__) do {
                                      hh1 = ar[i - 1];
                                      hh2 = ar[i];
                                      if(ufloat_hwRound((*hh1->Gear).X) > ufloat_hwRound((*hh2->Gear).X))
                                      {
                                          tmpX = (*hh1->Gear).X;
                                          tmpY = (*hh1->Gear).Y;
                                          (*hh1->Gear).X = (*hh2->Gear).X;
                                          (*hh1->Gear).Y = (*hh2->Gear).Y;
                                          (*hh2->Gear).X = tmpX;
                                          (*hh2->Gear).Y = tmpY;
                                          newn = i;
                                      }
                                  } while(i++ != i__end__);}
           n = newn;
       } while(!(n == 0));
};
void ugears_AssignHHCoords()
{
    LongInt i;
    LongInt t;
    LongInt p;
    LongInt j;
    LongInt x;
    LongInt y;
    typedef PHedgehog ar_tt[cMaxHHs];
    ar_tt ar;
    LongWord Count;
    boolean divide;
    boolean sectionDivide;
    if((GameFlags & gfPlaceHog) != 0)
    {
        PlacingHogs = true;
    }
    else
    {
        if((GameFlags & gfKing) != 0)
        {
            PlacingKings = true;
        }
    }
    divide = (GameFlags & gfDivideTeams) != 0;
    sectionDivide = divide && ((cMapGen == mgForts) || (ClansCount == 2));
    if(sectionDivide)
    {
        t = leftX;
        {p = 0;
         LongInt p__end__ = ClansCount - 1;
         if (p <= p__end__) do {
                                   {
                                       {j = 0;
                                        LongInt j__end__ = ((int)((*SpawnClansArray[p]).TeamsNumber) - 1);
                                        if (j <= j__end__) do {
                                                                  {
                                                                      {i = 0;
                                                                       LongInt i__end__ = cMaxHHIndex;
                                                                       if (i <= i__end__) do {
                                                                                                 {
                                                                                                     if(((*(*SpawnClansArray[p]).Teams[j]).Hedgehogs[i].Gear != NULL) && ((*(*SpawnClansArray[p]).Teams[j]).Hedgehogs[i].Gear->X.QWordValue == 0))
                                                                                                     {
                                                                                                         if(PlacingHogs)
                                                                                                         {
                                                                                                             (*(*SpawnClansArray[p]).Teams[j]).Hedgehogs[i].Unplaced = true;
                                                                                                         }
                                                                                                         else
                                                                                                         {
                                                                                                             ugearsutils_FindPlace_5(&((*(*SpawnClansArray[p]).Teams[j]).Hedgehogs[i].Gear), false, t, t + (playWidth / ClansCount), true);
                                                                                                         }
                                                                                                         if(PlacingKings && (*(*SpawnClansArray[p]).Teams[j]).Hedgehogs[i].King)
                                                                                                         {
                                                                                                             (*(*SpawnClansArray[p]).Teams[j]).Hedgehogs[i].UnplacedKing = true;
                                                                                                         }
                                                                                                         if((*(*SpawnClansArray[p]).Teams[j]).Hedgehogs[i].Gear != NULL)
                                                                                                         {
                                                                                                             (*(*SpawnClansArray[p]).Teams[j]).Hedgehogs[i].Gear->Pos = urandom_GetRandom(49);
                                                                                                             if((WorldEdge != weWrap) && ((p == 0) || (p == (ClansCount - 1))))
                                                                                                             {
                                                                                                                 (*(*SpawnClansArray[p]).Teams[j]).Hedgehogs[i].Gear->dX.isNegative = p != 0;
                                                                                                             }
                                                                                                             else
                                                                                                             {
                                                                                                                 (*(*SpawnClansArray[p]).Teams[j]).Hedgehogs[i].Gear->dX.isNegative = urandom_GetRandom(2) == 1;
                                                                                                             }
                                                                                                         }
                                                                                                     }
                                                                                                 }
                                                                                             } while(i++ != i__end__);}
                                                                  }
                                                              } while(j++ != j__end__);}
                                   }
                                   t += playWidth / ClansCount;
                               } while(p++ != p__end__);}
    }
    else
    {
        Count = 0;
        {p = 0;
         LongInt p__end__ = ((int)(TeamsCount) - 1);
         if (p <= p__end__) do {
                                   {
                                       {i = 0;
                                        LongInt i__end__ = cMaxHHIndex;
                                        if (i <= i__end__) do {
                                                                  {
                                                                      if(((*TeamsArray[p]).Hedgehogs[i].Gear != NULL) && ((*TeamsArray[p]).Hedgehogs[i].Gear->X.QWordValue == 0))
                                                                      {
                                                                          ar[Count] = &((*TeamsArray[p]).Hedgehogs[i]);
                                                                          ++Count;
                                                                      }
                                                                  }
                                                              } while(i++ != i__end__);}
                                   }
                               } while(p++ != p__end__);}
        while(Count > 0)
        {
            i = urandom_GetRandom(Count);
            if(PlacingHogs)
            {
                ar[i]->Unplaced = true;
            }
            else
            {
                ugearsutils_FindPlace_5(&(ar[i]->Gear), false, leftX, rightX, true);
            }
            if(PlacingKings && ar[i]->King)
            {
                ar[i]->UnplacedKing = true;
            }
            if(ar[i]->Gear != NULL)
            {
                (*ar[i]->Gear).dX.isNegative = ufloat_hwRound((*ar[i]->Gear).X) > (leftX + (playWidth / 2));
            }
            ar[i] = ar[Count - 1];
            --Count;
        }
    }
    {p = 0;
     LongInt p__end__ = ((int)(TeamsCount) - 1);
     if (p <= p__end__) do {
                               {
                                   {i = 0;
                                    LongInt i__end__ = cMaxHHIndex;
                                    if (i <= i__end__) do {
                                                              {
                                                                  if(((*TeamsArray[p]).Hedgehogs[i].Gear != NULL) && (((*TeamsArray[p]).Hedgehogs[i].Gear->State & gsttmpFlag) != 0))
                                                                  {
                                                                      ulandgraphics_DrawExplosion(ufloat_hwRound((*TeamsArray[p]).Hedgehogs[i].Gear->X), ufloat_hwRound((*TeamsArray[p]).Hedgehogs[i].Gear->Y), 50);
                                                                      uutils_AddFileLog(_strappend(_strconcat(_strappend(_strconcat(__str12, uutils_IntToStr(ufloat_hwRound((*TeamsArray[p]).Hedgehogs[i].Gear->X))), 0x2c), uutils_IntToStr(ufloat_hwRound((*TeamsArray[p]).Hedgehogs[i].Gear->Y))), 0x29));
                                                                  }
                                                              }
                                                          } while(i++ != i__end__);}
                               }
                           } while(p++ != p__end__);}
    {p = 0;
     LongInt p__end__ = ((int)(TeamsCount) - 1);
     if (p <= p__end__) do {
                               {
                                   {i = 0;
                                    LongInt i__end__ = cMaxHHIndex;
                                    if (i <= i__end__) do {
                                                              {
                                                                  if(((*TeamsArray[p]).Hedgehogs[i].Gear != NULL) && (((*TeamsArray[p]).Hedgehogs[i].Gear->State & gsttmpFlag) != 0))
                                                                  {
                                                                      x = ufloat_hwRound((*TeamsArray[p]).Hedgehogs[i].Gear->X) - (SpritesData[sprTargetBee].Width / 2);
                                                                      y = ufloat_hwRound((*TeamsArray[p]).Hedgehogs[i].Gear->Y) - (SpritesData[sprTargetBee].Height / 2);
                                                                      if(hasBorder)
                                                                      {
                                                                          x = uutils_Max(uutils_Min(x, (rightX - SpritesData[sprTargetBee].Width) - cBorderWidth), leftX + cBorderWidth);
                                                                      }
                                                                      else
                                                                      {
                                                                          x = uutils_Max(uutils_Min(x, rightX - SpritesData[sprTargetBee].Width), leftX);
                                                                      }
                                                                      y = uutils_Max(y, topY);
                                                                      ulandgraphics_ForcePlaceOnLand(x, y, sprTargetBee, 0, lfBasic, 0xffffffff, false, false, false);
                                                                      (*TeamsArray[p]).Hedgehogs[i].Gear->Y = ufloat_int2hwFloat((ufloat_hwRound((*TeamsArray[p]).Hedgehogs[i].Gear->Y) - (SpritesData[sprTargetBee].Height / 2)) - (*TeamsArray[p]).Hedgehogs[i].Gear->Radius);
                                                                      ucollisions_AddCI((*TeamsArray[p]).Hedgehogs[i].Gear);
                                                                      (*TeamsArray[p]).Hedgehogs[i].Gear->State = (*TeamsArray[p]).Hedgehogs[i].Gear->State & ~gsttmpFlag;
                                                                      uutils_AddFileLog(_strappend(_strconcat(_strappend(_strconcat(__str13, uutils_IntToStr(x)), 0x2c), uutils_IntToStr(y)), 0x29));
                                                                  }
                                                              }
                                                          } while(i++ != i__end__);}
                               }
                           } while(p++ != p__end__);}
    if(divide && !sectionDivide)
    {
        ugears_SortHHsByClan();
    }
};
void ugears_RandomizeHHAnim()
{
    LongInt i;
    LongInt j;
    LongInt p;
    {p = 0;
     LongInt p__end__ = ClansCount - 1;
     if (p <= p__end__) do {
                               {
                                   {j = 0;
                                    LongInt j__end__ = ((int)((*SpawnClansArray[p]).TeamsNumber) - 1);
                                    if (j <= j__end__) do {
                                                              {
                                                                  {i = 0;
                                                                   LongInt i__end__ = cMaxHHIndex;
                                                                   if (i <= i__end__) do {
                                                                                             if((*(*SpawnClansArray[p]).Teams[j]).Hedgehogs[i].Gear != NULL)
                                                                                             {
                                                                                                 (*(*(*SpawnClansArray[p]).Teams[j]).Hedgehogs[i].Gear).Pos = urandom_GetRandom(19);
                                                                                             }
                                                                                         } while(i++ != i__end__);}
                                                              }
                                                          } while(j++ != j__end__);}
                               }
                           } while(p++ != p__end__);}
};
PGear ugears_SpawnCustomCrateAt(LongInt x,LongInt y,TCrateType crate,LongWord content,LongWord cnt)
{
    PGear spawncustomcrateat_result;
    PGear gear;
    gear = ugearslist_AddGear_7(x, y, gtCase, 0, _0, _0, 0);
    if(FinishedTurnsTotal > -1)
    {
        FollowGear = gear;
    }
    cCaseFactor = 0;
    if((crate != HealthCrate) && (content > (60)))
    {
        content = (60);
    }
    gear->Power = cnt;
    switch(crate)
    {case HealthCrate:{
                          gear->Pos = posCaseHealth;
                          gear->RenderHealth = true;
                          gear->Radius = cCaseHealthRadius;
                          gear->Health = content;
                          if(FinishedTurnsTotal > -1)
                          {
                              ucaptions_AddCaption(ulocale_GetEventString(eidNewHealthPack), capcolDefault, capgrpAmmoinfo);
                          }
                      }
                      break;
     case AmmoCrate:{
                        gear->Pos = posCaseAmmo;
                        gear->AmmoType = ((TAmmoType)content);
                        if(FinishedTurnsTotal > -1)
                        {
                            ucaptions_AddCaption(ulocale_GetEventString(eidNewAmmoPack), capcolDefault, capgrpAmmoinfo);
                        }
                    }
                    break;
     case UtilityCrate:{
                           gear->Pos = posCaseUtility;
                           gear->AmmoType = ((TAmmoType)content);
                           if(FinishedTurnsTotal > -1)
                           {
                               ucaptions_AddCaption(ulocale_GetEventString(eidNewUtilityPack), capcolDefault, capgrpAmmoinfo);
                           }
                       }
                       break;
     default: break;}
    if((x == 0) && (y == 0))
    {
        ugearsutils_FindPlace_4(&(gear), true, 0, LAND_WIDTH);
    }
    spawncustomcrateat_result = gear;
    return spawncustomcrateat_result;
};
PGear ugears_SpawnFakeCrateAt(LongInt x,LongInt y,TCrateType crate,boolean explode,boolean poison)
{
    PGear spawnfakecrateat_result;
    PGear gear;
    gear = ugearslist_AddGear_7(x, y, gtCase, 0, _0, _0, 0);
    if(FinishedTurnsTotal > -1)
    {
        FollowGear = gear;
    }
    cCaseFactor = 0;
    gear->Pos = posCaseDummy;
    if(explode)
    {
        gear->Pos = gear->Pos + posCaseExplode;
    }
    if(poison)
    {
        gear->Pos = gear->Pos + posCasePoison;
    }
    switch(crate)
    {case HealthCrate:{
                          gear->Pos = gear->Pos + posCaseHealth;
                          gear->RenderHealth = true;
                          gear->Karma = 2;
                          gear->Radius = cCaseHealthRadius;
                          if(FinishedTurnsTotal > -1)
                          {
                              ucaptions_AddCaption(ulocale_GetEventString(eidNewHealthPack), capcolDefault, capgrpAmmoinfo);
                          }
                      }
                      break;
     case AmmoCrate:{
                        gear->Pos = gear->Pos + posCaseAmmo;
                        if(FinishedTurnsTotal > -1)
                        {
                            ucaptions_AddCaption(ulocale_GetEventString(eidNewAmmoPack), capcolDefault, capgrpAmmoinfo);
                        }
                    }
                    break;
     case UtilityCrate:{
                           gear->Pos = gear->Pos + posCaseUtility;
                           if(FinishedTurnsTotal > -1)
                           {
                               ucaptions_AddCaption(ulocale_GetEventString(eidNewUtilityPack), capcolDefault, capgrpAmmoinfo);
                           }
                       }
                       break;
     default: break;}
    if((x == 0) && (y == 0))
    {
        ugearsutils_FindPlace_4(&(gear), true, 0, LAND_WIDTH);
    }
    spawnfakecrateat_result = gear;
    return spawnfakecrateat_result;
};
void ugears_StartSuddenDeath()
{
    if(SuddenDeath)
    {
        return;
    }
    SuddenDeath = true;
    SuddenDeathActive = true;
    if(cHealthDecrease != 0)
    {
        SuddenDeathDmg = true;
        ScreenFade = sfFromWhite;
        ScreenFadeValue = sfMax;
        ScreenFadeSpeed = 1;
        uvisualgears_ChangeToSDClouds();
        uvisualgears_ChangeToSDFlakes();
        ustore_SetSkyColor((SDSkyColor.r * (SDTint.r /(float) 255)) /(float) 255, (SDSkyColor.g * (SDTint.g /(float) 255)) /(float) 255, (SDSkyColor.b * (SDTint.b /(float) 255)) /(float) 255);
    }
    Ammoz[amTardis].SkipTurns = 9999;
    Ammoz[amTardis].Probability = 0;
    ucaptions_AddCaption(trmsg[sidSuddenDeath], capcolDefault, capgrpGameState);
    uscript_ScriptCall_1(__str14);
    usound_PlaySound_1(sndSuddenDeath);
    usound_StopMusic();
    if(_strncompare(SDMusicFN, __str10))
    {
        usound_PlayMusic();
    }
};
PGear ugears_GearByUID(LongWord uid)
{
    PGear gearbyuid_result;
    PGear gear;
    gearbyuid_result = NULL;
    if(uid == 0)
    {
        return gearbyuid_result;
    }
    if((lastGearByUID != NULL) && (lastGearByUID->uid == uid))
    {
        gearbyuid_result = lastGearByUID;
        return gearbyuid_result;
    }
    gear = GearsList;
    while(gear != NULL)
    {
        if(gear->uid == uid)
        {
            lastGearByUID = gear;
            gearbyuid_result = gear;
            return gearbyuid_result;
        }
        gear = gear->NextGear;
    }
    return gearbyuid_result;
};
boolean ugears_IsClockRunning()
{
    boolean isclockrunning_result;
    isclockrunning_result = (((CurrentHedgehog->Gear != NULL) && ((((((*CurrentHedgehog->Gear).State & gstAttacking) == 0) || ((Ammoz[CurrentHedgehog->CurAmmoType].Ammo.Propz & ammoprop_DoesntStopTimerWhileAttacking) != 0)) || (((GameFlags & gfInfAttack) != 0) && ((Ammoz[CurrentHedgehog->CurAmmoType].Ammo.Propz & ammoprop_DoesntStopTimerWhileAttackingInInfAttackMode) != 0))) || (CurrentHedgehog->CurAmmoType == amSniperRifle))) && !(isInMultiShoot && ((Ammoz[CurrentHedgehog->CurAmmoType].Ammo.Propz & ammoprop_DoesntStopTimerInMultiShoot) != 0))) && !LuaClockPaused;
    return isclockrunning_result;
};
void ugears_chSkip(string255 (*s))
{
    UNUSED ((*s));
    if(!isExternalSource)
    {
        uio_SendIPC(__str15);
    }
    ustats_Skipped();
    skipFlag = true;
    uscript_ScriptCall_1(__str16);
};
void ugears_chHogSay(string255 (*s))
{
    PVisualGear Gear;
    string255 text;
    PHedgehog hh;
    Byte i;
    Byte x;
    Byte t;
    Byte h;
    LongInt c;
    LongInt j;
    hh = NULL;
    i = 0;
    t = 0;
    x = ((Byte)(*s).s[1]);
    if(x < 4)
    {
        t = ((Byte)(*s).s[2]);
        if(fpcrtl_Length((*s)) > 2)
        {
            h = ((Byte)(*s).s[3]);
        }
        else
        {
            h = 0;
        }
    }
    if(((x < 4) && (h > ((Byte)0x30))) && (h < ((Byte)0x39)))
    {
        i = h - 48;
    }
    if(i != 0)
    {
        text = fpcrtl_copy((*s), 4, fpcrtl_Length((*s)) - 1);
    }
    else
    {
        if(x < 4)
        {
            text = fpcrtl_copy((*s), 3, fpcrtl_Length((*s)) - 1);
        }
        else
        {
            text = fpcrtl_copy((*s), 2, fpcrtl_Length((*s)) - 1);
        }
    }
    if(_strcompare(text, __str10))
    {
        text = __str17;
    }
    if((x < 4) && (TeamsArray[t] != NULL))
    {
        if((((i == 0) && (CurrentHedgehog != NULL)) && (CurrentHedgehog->Team == TeamsArray[t])) && !CurrentHedgehog->Unplaced)
        {
            hh = CurrentHedgehog;
        }
        else
        {
            j = 0;
            c = 0;
            while((j <= cMaxHHIndex) && (hh == NULL))
            {
                if((TeamsArray[t]->Hedgehogs[j].Gear != NULL) && !TeamsArray[t]->Hedgehogs[j].Unplaced)
                {
                    ++c;
                    if((i == 0) || (i == c))
                    {
                        hh = &(TeamsArray[t]->Hedgehogs[j]);
                    }
                }
                ++j;
            }
        }
        if(hh != NULL)
        {
            Gear = uvisualgearslist_AddVisualGear_3(0, 0, vgtSpeechBubble);
            if(Gear != NULL)
            {
                Gear->Hedgehog = hh;
                Gear->Text = text;
                Gear->FrameTicks = x;
            }
            uchat_AddChatString(_strprepend(0x9, ulocale_Format_3(fpcrtl_astr2str(trmsg[sidChatHog]), hh->Name, text)));
        }
    }
    else
    {
        if(x >= 4)
        {
            SpeechType = x - 3;
            SpeechText = text;
        }
    }
};
void ugears_initModule()
{
    typedef utypes_TGearStepProcedure handlers_tt[70];
    handlers_tt handlers = {&ugearshandlersmess_doStepFlame,
                            &ugearshedgehog_doStepHedgehog,
                            &ugearshandlersmess_doStepMine,
                            &ugearshandlersmess_doStepCase,
                            &ugearshandlersmess_doStepAirMine,
                            &ugearshandlersmess_doStepCase,
                            &ugearshandlersmess_doStepBomb,
                            &ugearshandlersmess_doStepShell,
                            &ugearshandlersmess_doStepGrave,
                            &ugearshandlersmess_doStepBee,
                            &ugearshandlersmess_doStepShotgunShot,
                            &ugearshandlersmess_doStepPickHammer,
                            &ugearshandlersrope_doStepRope,
                            &ugearshandlersmess_doStepDEagleShot,
                            &ugearshandlersmess_doStepDynamite,
                            &ugearshandlersmess_doStepBomb,
                            &ugearshandlersmess_doStepCluster,
                            &ugearshandlersmess_doStepShover,
                            &ugearshandlersmess_doStepFirePunch,
                            &ugearshandlersmess_doStepActionTimer,
                            &ugearshandlersmess_doStepActionTimer,
                            &ugearshandlersmess_doStepParachute,
                            &ugearshandlersmess_doStepAirAttack,
                            &ugearshandlersmess_doStepAirBomb,
                            &ugearshandlersmess_doStepBlowTorch,
                            &ugearshandlersmess_doStepGirder,
                            &ugearshandlersmess_doStepTeleport,
                            &ugearshandlersmess_doStepSwitcher,
                            &ugearshandlersmess_doStepTarget,
                            &ugearshandlersmess_doStepMortar,
                            &ugearshandlersmess_doStepWhip,
                            &ugearshandlersmess_doStepKamikaze,
                            &ugearshandlersmess_doStepCake,
                            &ugearshandlersmess_doStepSeduction,
                            &ugearshandlersmess_doStepBomb,
                            &ugearshandlersmess_doStepCluster,
                            &ugearshandlersmess_doStepBomb,
                            &ugearshandlersmess_doStepWaterUp,
                            &ugearshandlersmess_doStepDrill,
                            &ugearshandlersmess_doStepBallgun,
                            &ugearshandlersmess_doStepBomb,
                            &ugearshandlersmess_doStepRCPlane,
                            &ugearshandlersmess_doStepSniperRifleShot,
                            &ugearshandlersmess_doStepJetpack,
                            &ugearshandlersmess_doStepMolotov,
                            &ugearshandlersmess_doStepBirdy,
                            &ugearshandlersmess_doStepEggWork,
                            &ugearshandlersmess_doStepPortalShot,
                            &ugearshandlersmess_doStepPiano,
                            &ugearshandlersmess_doStepBomb,
                            &ugearshandlersmess_doStepSineGunShot,
                            &ugearshandlersmess_doStepFlamethrower,
                            &ugearshandlersmess_doStepSMine,
                            &ugearshandlersmess_doStepPoisonCloud,
                            &ugearshandlersmess_doStepHammer,
                            &ugearshandlersmess_doStepHammerHit,
                            &ugearshandlersmess_doStepResurrector,
                            &ugearshandlersmess_doStepNapalmBomb,
                            &ugearshandlersmess_doStepSnowball,
                            &ugearshandlersmess_doStepSnowflake,
                            &ugearshandlersmess_doStepLandGun,
                            &ugearshandlersmess_doStepTardis,
                            &ugearshandlersmess_doStepIceGun,
                            &ugearshandlersmess_doStepAddAmmo,
                            &ugearshandlersmess_doStepGenericFaller,
                            &ugearshandlersmess_doStepKnife,
                            &ugearshandlersmess_doStepCreeper,
                            &ugearshandlersmess_doStepMinigun,
                            &ugearshandlersmess_doStepMinigunBullet,
                            &ugearshandlersmess_doStepSentryDeploy};
    fpcrtl_memcpy(doStepHandlers, handlers, sizeof(handlers));
    ucommands_RegisterVariable_3(__str18, &(ugears_chSkip), false);
    ucommands_RegisterVariable_3(__str19, &(ugears_chHogSay), true);
    CurAmmoGear = NULL;
    GearsList = NULL;
    curHandledGear = NULL;
    KilledHHs = 0;
    SuddenDeath = false;
    SuddenDeathDmg = false;
    SpeechType = 1;
    skipFlag = false;
    AllInactive = false;
    PrvInactive = false;
    delay = 0;
    delay2 = 0;
    step = stDelay1;
    upd = 0;
    NewTurnTick = 0xffffffff;
};
void ugears_freeModule()
{
    ugears_FreeGearsList();
};
