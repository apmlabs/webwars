#include "fpcrtl.h"

#include "uTeams.h"
LongInt MaxTeamHealth;
#include "uLocale.h"
#include "uAmmos.h"
#include "uChat.h"
#include "uVariables.h"
#include "uUtils.h"
#include "uIO.h"
#include "uCaptions.h"
#include "uCommands.h"
#include "uDebug.h"
#include "uGearsUtils.h"
#include "uGearsList.h"
#include "uVisualGearsList.h"
#include "uTextures.h"
static const string255 __str40 = STRINIT("owner");
static const string255 __str39 = STRINIT("flag");
static const string255 __str38 = STRINIT("hat");
static const string255 __str37 = STRINIT("grave");
static const string255 __str36 = STRINIT("fort");
static const string255 __str35 = STRINIT("teamback");
static const string255 __str34 = STRINIT("teamgone");
static const string255 __str33 = STRINIT("hhcoords");
static const string255 __str32 = STRINIT("setmissteam");
static const string255 __str31 = STRINIT("addteam");
static const string255 __str30 = STRINIT("addmisshh");
static const string255 __str29 = STRINIT("addhh");
static const string255 __str28 = STRINIT(" \"/owner\"");
static const string255 __str27 = STRINIT(" \"/flag\"");
static const string255 __str26 = STRINIT(" \"/fort\"");
static const string255 __str25 = STRINIT(" \"/grave\"");
static const string255 __str24 = STRINIT("NoHat");
static const string255 __str23 = STRINIT("Reserved");
static const string255 __str22 = STRINIT("g");
static const string255 __str21 = STRINIT("/teamgone s");
static const string255 __str20 = STRINIT("/teamback s");
static const string255 __str19 = STRINIT("f");
static const string255 __str18 = STRINIT("* ");
static const string255 __str17 = STRINIT("Default_qau");
static const string255 __str16 = STRINIT(" 2");
static const string255 __str15 = STRINIT("bind");
static const string255 __str14 = STRINIT(".hwt");
static const string255 __str13 = STRINIT("Invalid hedgehog health (must be between 1 and ");
static const string255 __str12 = STRINIT(" hogs)");
static const string255 __str11 = STRINIT("\"! (already ");
static const string255 __str10 = STRINIT("Can't add hedgehog to \"");
static const string255 __str9 = STRINIT("Can't add hedgehogs yet, add a team first!");
static const string255 __str8 = STRINIT("/skip");
static const string255 __str7 = STRINIT("onHogRestore");
static const string255 __str6 = STRINIT("crown");
static const string255 __str5 = STRINIT("hedgewars");
static const string255 __str4 = STRINIT("Too many teams");
static const string255 __str3 = STRINIT("AddTeam: team = nil");
static const string255 __str2 = STRINIT("Wind = ");
static const string255 __str1 = STRINIT("Team is nil!");
static const string255 __str0 = STRINIT("");
static boolean TeamsGameOver;
static boolean NextClan;
static LongInt SwapClanPre;
static LongInt SwapClanReal;
boolean uteams_CheckForWin()
{
    boolean checkforwin_result;
    PClan AliveClan;
    astring s;
    astring cap;
    typedef astring ts_tt[((cMaxTeams - 1) + 1)];
    ts_tt ts;
    LongInt t;
    LongInt ActiveAliveCount;
    LongInt i;
    LongInt j;
    boolean allWin;
    boolean winCamera;
    checkforwin_result = false;
    ActiveAliveCount = 0;
    {t = 0;
     LongInt t__end__ = ((int)(ClansCount) - 1);
     if (t <= t__end__) do {
                               if((ClansArray[t]->ClanHealth > 0) && !ClansArray[t]->Passive)
                               {
                                   ++ActiveAliveCount;
                                   AliveClan = ClansArray[t];
                               }
                           } while(t++ != t__end__);}
    if((ActiveAliveCount > 1) || ((ActiveAliveCount == 1) && ((GameFlags & gfOneClanMode) != 0)))
    {
        return checkforwin_result;
    }
    checkforwin_result = true;
    TurnTimeLeft = 0;
    ReadyTimeLeft = 0;
    if((!bBetweenTurns && isInMultiShoot) || bDuringWaterRise)
    {
        ustats_TurnStats();
        if(!bDuringWaterRise)
        {
            ustats_TurnReaction();
        }
        ustats_TurnStatsReset();
    }
    if(!TeamsGameOver)
    {
        if(ActiveAliveCount == 0)
        {
            ucaptions_AddCaption(ulocale_GetEventString(eidRoundDraw), capcolDefault, capgrpGameState);
            if(SendGameResultOn)
            {
                uio_SendStat(siGameResult, fpcrtl_astr2str(trmsg[sidDraw]));
            }
            if(PreviousTeam != NULL)
            {
                usound_AddVoice_2(sndStupid, PreviousTeam->voicepack);
            }
            else
            {
                usound_AddVoice_2(sndStupid, TeamsArray[0]->voicepack);
            }
            ugearslist_AddGear_7(0, 0, gtATFinishGame, 0, _0, _0, 3000);
        }
        else
        {
            allWin = false;
            {
                if((*AliveClan).TeamsNumber == 1)
                {
                    s = fpcrtl_str2astr((*AliveClan).Teams[0]->TeamName);
                    cap = ulocale_FormatA_2(ulocale_GetEventString(eidRoundWin), s);
                    ucaptions_AddCaption(cap, capcolDefault, capgrpGameState);
                    s = ulocale_FormatA_2(trmsg[sidWinner], s);
                }
                else
                {
                    s = fpcrtl_str2astr(__str0);
                    {j = 0;
                     LongInt j__end__ = ((int)((*AliveClan).TeamsNumber) - 1);
                     if (j <= j__end__) do {
                                               ts[j] = fpcrtl_str2astr((*AliveClan).Teams[j]->TeamName);
                                           } while(j++ != j__end__);}
                    if(((*AliveClan).TeamsNumber == cMaxTeams) || (TeamsCount == (*AliveClan).TeamsNumber))
                    {
                        s = trmsg[sidWinnerAll];
                        allWin = true;
                    }
                    else
                    {
                        if(((*AliveClan).TeamsNumber >= 2) && ((*AliveClan).TeamsNumber < cMaxTeams))
                        {
                            if((*AliveClan).TeamsNumber == 2)
                            {
                                s = ulocale_FormatA_3(trmsg[((TMsgStrId)sidWinner2)], ts[0], ts[1]);
                            }
                            else
                            {
                                if((*AliveClan).TeamsNumber == 3)
                                {
                                    s = ulocale_FormatA_4(trmsg[((TMsgStrId)sidWinner3)], ts[0], ts[1], ts[2]);
                                }
                                else
                                {
                                    if((*AliveClan).TeamsNumber == 4)
                                    {
                                        s = ulocale_FormatA_5(trmsg[((TMsgStrId)sidWinner4)], ts[0], ts[1], ts[2], ts[3]);
                                    }
                                    else
                                    {
                                        if((*AliveClan).TeamsNumber == 5)
                                        {
                                            s = ulocale_FormatA_6(trmsg[((TMsgStrId)sidWinner5)], ts[0], ts[1], ts[2], ts[3], ts[4]);
                                        }
                                        else
                                        {
                                            if((*AliveClan).TeamsNumber == 6)
                                            {
                                                s = ulocale_FormatA_7(trmsg[((TMsgStrId)sidWinner6)], ts[0], ts[1], ts[2], ts[3], ts[4], ts[5]);
                                            }
                                            else
                                            {
                                                if((*AliveClan).TeamsNumber == 7)
                                                {
                                                    s = ulocale_FormatA_8(trmsg[((TMsgStrId)sidWinner7)], ts[0], ts[1], ts[2], ts[3], ts[4], ts[5], ts[6]);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    cap = s;
                    ucaptions_AddCaption(cap, capcolDefault, capgrpGameState);
                }
                winCamera = false;
                {j = 0;
                 LongInt j__end__ = ((int)((*AliveClan).TeamsNumber) - 1);
                 if (j <= j__end__) do {
                                           {
                                               {i = 0;
                                                LongInt i__end__ = cMaxHHIndex;
                                                if (i <= i__end__) do {
                                                                          {
                                                                              if((*(*AliveClan).Teams[j]).Hedgehogs[i].Gear != NULL)
                                                                              {
                                                                                  if(!winCamera)
                                                                                  {
                                                                                      FollowGear = (*(*AliveClan).Teams[j]).Hedgehogs[i].Gear;
                                                                                      winCamera = true;
                                                                                  }
                                                                                  (*(*AliveClan).Teams[j]).Hedgehogs[i].Gear->State = gstWinner;
                                                                              }
                                                                          }
                                                                      } while(i++ != i__end__);}
                                           }
                                       } while(j++ != j__end__);}
                if((*AliveClan).Flawless)
                {
                    usound_AddVoice_2(sndFlawless, (*AliveClan).Teams[0]->voicepack);
                }
                else
                {
                    usound_AddVoice_2(sndVictory, (*AliveClan).Teams[0]->voicepack);
                }
            }
            if(SendGameResultOn)
            {
                uio_SendStat(siGameResult, fpcrtl_astr2str(s));
            }
            if(allWin && SendAchievementsStatsOn)
            {
                uio_SendStat(siEverAfter, __str0);
            }
            ugearslist_AddGear_7(0, 0, gtATFinishGame, 0, _0, _0, 3000);
        }
        ustats_SendStats();
    }
    TeamsGameOver = true;
    GameOver = true;
    return checkforwin_result;
};
void uteams_SwitchHedgehog()
{
    LongWord c;
    LongWord i;
    LongWord t;
    LongWord PrevHH;
    LongWord PrevTeam;
    TargetPoint.x = NoPointX;
    if(udebug_checkFails(CurrentTeam != NULL, __str1, true))
    {
        return;
    }
    {
        if(((PreviousTeam != NULL) && PlacingHogs) && (*CurrentHedgehog).Unplaced)
        {
            (*CurrentHedgehog).Unplaced = false;
            if((*CurrentHedgehog).Gear != NULL)
            {
                ucollisions_DeleteCI((*CurrentHedgehog).Gear);
                ugearsutils_FindPlace_5(&((*CurrentHedgehog).Gear), false, 0, LAND_WIDTH, true);
                if((*CurrentHedgehog).Gear != NULL)
                {
                    ucollisions_AddCI((*CurrentHedgehog).Gear);
                }
            }
        }
        else
        {
            if(((PreviousTeam != NULL) && PlacingKings) && (*CurrentHedgehog).UnplacedKing)
            {
                (*CurrentHedgehog).UnplacedKing = false;
            }
        }
    }
    PreviousTeam = CurrentTeam;
    {
        if((*CurrentHedgehog).Gear != NULL)
        {
            (*CurrentHedgehog).MultiShootAttacks = 0;
            (*CurrentHedgehog).Gear->Message = 0;
            (*CurrentHedgehog).Gear->Z = cHHZ;
            ugearslist_RemoveGearFromList((*CurrentHedgehog).Gear);
            ugearslist_InsertGearToList((*CurrentHedgehog).Gear);
        }
    }
    {
        if((((GameFlags & gfPerHogAmmo) != 0) && !(*CurrentTeam).ExtDriven) && (CurrentHedgehog->BotLevel == 0))
        {
            c = (*CurrentTeam).CurrHedgehog;
            do {
                   {
                       ++c;
                       if(c > cMaxHHIndex)
                       {
                           c = 0;
                       }
                   }
               } while(!((c == (*CurrentTeam).CurrHedgehog) || (((*CurrentTeam).Hedgehogs[c].Gear != NULL) && ((*CurrentTeam).Hedgehogs[c].Effects[heFrozen] < 50255))));
            LocalAmmo = (*CurrentTeam).Hedgehogs[c].AmmoStore;
        }
    }
    c = (*CurrentTeam->Clan).ClanIndex;
    do {
           if((GameFlags & gfTagTeam) != 0)
           {
               {
                   if((*ClansArray[c]).CurrTeam == (*ClansArray[c]).TagTeamIndex)
                   {
                       (*ClansArray[c]).TagTeamIndex = ((int)((*ClansArray[c]).TagTeamIndex) - 1) % (*ClansArray[c]).TeamsNumber;
                       (*ClansArray[c]).CurrTeam = ((int)((*ClansArray[c]).CurrTeam) - 1) % (*ClansArray[c]).TeamsNumber;
                       ++c;
                       if(c == ClansCount)
                       {
                           c = 0;
                       }
                       if(c == SwapClanReal)
                       {
                           ++TotalRoundsReal;
                       }
                       NextClan = true;
                   }
               }
               {
                   if((!PlacingHogs && !PlacingKings) && ((((*ClansArray[c]).CurrTeam + 1) % (*ClansArray[c]).TeamsNumber) == (*ClansArray[c]).TagTeamIndex))
                   {
                       if(c == SwapClanPre)
                       {
                           ++TotalRoundsPre;
                       }
                   }
               }
           }
           else
           {
               ++c;
               if(c == ClansCount)
               {
                   c = 0;
               }
               if(!PlacingHogs && !PlacingKings)
               {
                   if(c == SwapClanPre)
                   {
                       ++TotalRoundsPre;
                   }
                   if(c == SwapClanReal)
                   {
                       ++TotalRoundsReal;
                   }
               }
           }
           {
               PrevTeam = (*ClansArray[c]).CurrTeam;
               do {
                      (*ClansArray[c]).CurrTeam = ((*ClansArray[c]).CurrTeam + 1) % (*ClansArray[c]).TeamsNumber;
                      CurrentTeam = (*ClansArray[c]).Teams[(*ClansArray[c]).CurrTeam];
                      {
                          if(!(*CurrentTeam).Passive)
                          {
                              PrevHH = (*CurrentTeam).CurrHedgehog % (*CurrentTeam).HedgehogsNumber;
                              do {
                                     (*CurrentTeam).CurrHedgehog = ((*CurrentTeam).CurrHedgehog + 1) % (*CurrentTeam).HedgehogsNumber;
                                 } while(!((((*CurrentTeam).Hedgehogs[(*CurrentTeam).CurrHedgehog].Gear != NULL) && ((*CurrentTeam).Hedgehogs[(*CurrentTeam).CurrHedgehog].Effects[heFrozen] < 256)) || ((*CurrentTeam).CurrHedgehog == PrevHH)));
                          }
                      }
                  } while(!((((!CurrentTeam->Passive && (CurrentTeam->Hedgehogs[CurrentTeam->CurrHedgehog].Gear != NULL)) && (CurrentTeam->Hedgehogs[CurrentTeam->CurrHedgehog].Effects[heFrozen] < 256)) || (PrevTeam == (*ClansArray[c]).CurrTeam)) || (((*ClansArray[c]).CurrTeam == (*ClansArray[c]).TagTeamIndex) && ((GameFlags & gfTagTeam) != 0))));
           }
           if((CurrentTeam->Passive || (CurrentTeam->Hedgehogs[CurrentTeam->CurrHedgehog].Gear == NULL)) || (CurrentTeam->Hedgehogs[CurrentTeam->CurrHedgehog].Effects[heFrozen] > 255))
           {
               {
                   {t = 0;
                    LongWord t__end__ = ((int)((*CurrentTeam->Clan).TeamsNumber) - 1);
                    if (t <= t__end__) do {
                                              {
                                                  {i = 0;
                                                   LongWord i__end__ = ((int)((*(*CurrentTeam->Clan).Teams[t]).HedgehogsNumber) - 1);
                                                   if (i <= i__end__) do {
                                                                             {
                                                                                 if((*(*CurrentTeam->Clan).Teams[t]).Hedgehogs[i].Effects[heFrozen] > 255)
                                                                                 {
                                                                                     (*(*CurrentTeam->Clan).Teams[t]).Hedgehogs[i].Effects[heFrozen] = uutils_Max(255, (*(*CurrentTeam->Clan).Teams[t]).Hedgehogs[i].Effects[heFrozen] - 50000);
                                                                                 }
                                                                                 if((((*(*CurrentTeam->Clan).Teams[t]).Hedgehogs[i].Gear != NULL) && ((*(*CurrentTeam->Clan).Teams[t]).Hedgehogs[i].Effects[heFrozen] < 256)) && (CurrentTeam->Hedgehogs[CurrentTeam->CurrHedgehog].Effects[heFrozen] > 255))
                                                                                 {
                                                                                     (*(*CurrentTeam->Clan).Teams[t]).CurrHedgehog = i;
                                                                                 }
                                                                             }
                                                                         } while(i++ != i__end__);}
                                              }
                                          } while(t++ != t__end__);}
               }
               if(!CurrentTeam->Passive && ((CurrentTeam->Hedgehogs[CurrentTeam->CurrHedgehog].Gear == NULL) || (CurrentTeam->Hedgehogs[CurrentTeam->CurrHedgehog].Effects[heFrozen] > 255)))
               {
                   ++(*CurrentTeam->Clan).TurnNumber;
               }
           }
       } while(!((!CurrentTeam->Passive && (CurrentTeam->Hedgehogs[CurrentTeam->CurrHedgehog].Gear != NULL)) && (CurrentTeam->Hedgehogs[CurrentTeam->CurrHedgehog].Effects[heFrozen] < 256)));
    uteams_SwitchCurrentHedgehog(&(CurrentTeam->Hedgehogs[CurrentTeam->CurrHedgehog]));
    AmmoMenuInvalidated = true;
};
void uteams_AfterSwitchHedgehog()
{
    LongInt i;
    LongInt t;
    PAmmo CurWeapon;
    real w;
    PVisualGear vg;
    PGear g;
    astring s;
    if(PlacingHogs || PlacingKings)
    {
        PlacingHogs = false;
        PlacingKings = false;
        {t = 0;
         LongInt t__end__ = ((int)(TeamsCount) - 1);
         if (t <= t__end__) do {
                                   {i = 0;
                                    LongInt i__end__ = cMaxHHIndex;
                                    if (i <= i__end__) do {
                                                              if((((GameFlags & gfPlaceHog) != 0) && (TeamsArray[t]->Hedgehogs[i].Gear != NULL)) && TeamsArray[t]->Hedgehogs[i].Unplaced)
                                                              {
                                                                  PlacingHogs = true;
                                                              }
                                                              else
                                                              {
                                                                  if(((((GameFlags & gfPlaceHog) == 0) && ((GameFlags & gfKing) != 0)) && (TeamsArray[t]->Hedgehogs[i].Gear != NULL)) && TeamsArray[t]->Hedgehogs[i].UnplacedKing)
                                                                  {
                                                                      PlacingKings = true;
                                                                  }
                                                              }
                                                          } while(i++ != i__end__);}
                               } while(t++ != t__end__);}
        if(!PlacingHogs && !PlacingKings)
        {
            {i = 0;
             LongInt i__end__ = ClansCount;
             if (i <= i__end__) do {
                                       if(ClansArray[i] != NULL)
                                       {
                                           ClansArray[i]->TurnNumber = 0;
                                       }
                                   } while(i++ != i__end__);}
            uammos_ResetWeapons();
        }
    }
    if(!PlacingHogs && !PlacingKings)
    {
        if(TotalRoundsReal == -1)
        {
            TotalRoundsReal = 0;
        }
        if((TotalRoundsPre == -1) && (ClansCount == 1))
        {
            TotalRoundsPre = 0;
        }
    }
    if(!PlacingHogs && !PlacingKings)
    {
        if(SwapClanPre == -1)
        {
            if((GameFlags & gfRandomOrder) != 0)
            {
                SwapClanPre = 0;
            }
            else
            {
                SwapClanPre = ClansCount - 1;
            }
        }
        if(SwapClanReal == -1)
        {
            SwapClanReal = (*CurrentTeam->Clan).ClanIndex;
        }
    }
    ++(*CurrentTeam->Clan).TurnNumber;
    {
        {t = 0;
         LongInt t__end__ = ((int)((*CurrentTeam->Clan).TeamsNumber) - 1);
         if (t <= t__end__) do {
                                   {
                                       {i = 0;
                                        LongInt i__end__ = ((int)((*(*CurrentTeam->Clan).Teams[t]).HedgehogsNumber) - 1);
                                        if (i <= i__end__) do {
                                                                  {
                                                                      if((*(*CurrentTeam->Clan).Teams[t]).Hedgehogs[i].Effects[heFrozen] > 255)
                                                                      {
                                                                          (*(*CurrentTeam->Clan).Teams[t]).Hedgehogs[i].Effects[heFrozen] = uutils_Max(255, (*(*CurrentTeam->Clan).Teams[t]).Hedgehogs[i].Effects[heFrozen] - 50000);
                                                                      }
                                                                  }
                                                              } while(i++ != i__end__);}
                                   }
                               } while(t++ != t__end__);}
    }
    CurWeapon = uammos_GetCurAmmoEntry(&((*CurrentHedgehog)));
    if(CurWeapon->Count == 0)
    {
        CurrentHedgehog->CurAmmoType = amNothing;
    }
    if(CurrentHedgehog->BotLevel != 0)
    {
        (*CurrentHedgehog->Gear).AIHints = (*CurrentHedgehog->Gear).AIHints & ~aihAmmosChanged;
    }
    {
        {
            (*(*CurrentHedgehog).Gear).Z = cCurrHHZ;
            (*(*CurrentHedgehog).Gear).State = gstHHDriven;
            (*(*CurrentHedgehog).Gear).Active = true;
            (*(*CurrentHedgehog).Gear).Power = 0;
            (*(*CurrentHedgehog).Gear).LastDamage = NULL;
        }
        ugearslist_RemoveGearFromList((*CurrentHedgehog).Gear);
        ugearslist_InsertGearToList((*CurrentHedgehog).Gear);
        FollowGear = (*CurrentHedgehog).Gear;
    }
    if((GameFlags & gfDisableWind) == 0)
    {
        cWindSpeed = urandom_rndSign(ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_LongInt_op_mul(urandom_GetRandomf(), 2), cMaxWindSpeed));
        w = ufloat_hwFloat2Float(cWindSpeed);
        vg = uvisualgearslist_AddVisualGear_3(0, 0, vgtSmoothWindBar);
        if(vg != NULL)
        {
            vg->dAngle = w;
        }
        uutils_AddFileLog(_strconcat(__str2, uutils_FloatToStr(cWindSpeed)));
    }
    uammos_ApplyAmmoChanges(&((*CurrentHedgehog)));
    if(!CurrentTeam->ExtDriven && (CurrentHedgehog->BotLevel == 0))
    {
        uinputhandler_SetBinds(&(CurrentTeam->Binds));
    }
    if(PlacingHogs)
    {
        if(CurrentHedgehog->Unplaced)
        {
            TurnTimeLeft = 15000;
        }
        else
        {
            TurnTimeLeft = 0;
        }
    }
    else
    {
        if(PlacingKings)
        {
            if(CurrentHedgehog->King && CurrentHedgehog->UnplacedKing)
            {
                TurnTimeLeft = cHedgehogTurnTime;
            }
            else
            {
                TurnTimeLeft = 0;
            }
        }
        else
        {
            if(((GameFlags & gfTagTeam) != 0) && !NextClan)
            {
                if(TagTurnTimeLeft != 0)
                {
                    TurnTimeLeft = TagTurnTimeLeft;
                }
                TagTurnTimeLeft = 0;
            }
            else
            {
                TurnTimeLeft = cHedgehogTurnTime;
                TagTurnTimeLeft = 0;
                NextClan = false;
            }
            if((((GameFlags & gfSwitchHog) != 0) && !CurrentTeam->hasGone) && !((((GameFlags & gfKing) != 0) && ((GameFlags & gfPlaceHog) == 0)) && (TotalRoundsReal == -1)))
            {
                g = ugearslist_AddGear_7(ufloat_hwRound((*CurrentHedgehog->Gear).X), ufloat_hwRound((*CurrentHedgehog->Gear).Y), gtSwitcher, 0, _0, _0, 0);
                CurAmmoGear = g;
                lastGearByUID = g;
            }
            else
            {
                bShowFinger = true;
            }
        }
    }
    IsGetAwayTime = false;
    if((TurnTimeLeft > 0) && (CurrentHedgehog->BotLevel == 0))
    {
        if(!CinematicScript)
        {
            if(CurrentTeam->ExtDriven)
            {
                usound_AddVoice_2(sndHmm, CurrentTeam->voicepack);
            }
            else
            {
                usound_AddVoice_2(sndYesSir, CurrentTeam->voicepack);
            }
        }
        if(cHedgehogTurnTime < 1000000)
        {
            ReadyTimeLeft = cReadyDelay;
        }
        s = fpcrtl_str2astr(CurrentTeam->TeamName);
        ucaptions_AddCaption(ulocale_FormatA_2(trmsg[sidReady], s), capcolDefault, capgrpGameState);
    }
    else
    {
        if((TurnTimeLeft > 0) && !CinematicScript)
        {
            usound_AddVoice_2(sndHmm, CurrentTeam->voicepack);
        }
        ReadyTimeLeft = 0;
    }
};
PTeam uteams_SetMissionTeam()
{
    PTeam setmissionteam_result;
    PTeam team;
    fpcrtl_new(team);
    if(udebug_checkFails(team != NULL, __str3, true))
    {
        return NULL;
    }
    fpcrtl_FillChar((*team), sizeof(TTeam), 0);
    team->HedgehogsNumber = 0;
    team->Binds = DefaultBinds;
    CurrentTeam = team;
    MissionTeam = team;
    setmissionteam_result = team;
    return setmissionteam_result;
};
PTeam uteams_AddTeam(LongWord TeamColor)
{
    PTeam addteam_result;
    PTeam team;
    LongInt c;
    if(udebug_checkFails(TeamsCount < cMaxTeams, __str4, true))
    {
        return NULL;
    }
    fpcrtl_new(team);
    if(udebug_checkFails(team != NULL, __str3, true))
    {
        return NULL;
    }
    fpcrtl_FillChar((*team), sizeof(TTeam), 0);
    team->AttackBar = 2;
    team->CurrHedgehog = 0;
    team->Flag = __str5;
    TeamsArray[TeamsCount] = team;
    ++TeamsCount;
    ++VisibleTeamsCount;
    team->Binds = DefaultBinds;
    team->Passive = false;
    c = ((int)(ClansCount) - 1);
    while((c >= 0) && (ClansArray[c]->Color != TeamColor))
    {
        --c;
    }
    if(c < 0)
    {
        fpcrtl_new(team->Clan);
        fpcrtl_FillChar((*team->Clan), sizeof(TClan), 0);
        ClansArray[ClansCount] = team->Clan;
        ++ClansCount;
        {
            (*team->Clan).ClanIndex = ((int)(ClansCount) - 1);
            (*team->Clan).Color = TeamColor;
            (*team->Clan).TagTeamIndex = 0;
            (*team->Clan).Flawless = true;
            (*team->Clan).LocalOrAlly = false;
            (*team->Clan).DeathLogged = false;
            (*team->Clan).StatsHandled = false;
        }
    }
    else
    {
        team->Clan = ClansArray[c];
    }
    {
        (*team->Clan).Teams[(*team->Clan).TeamsNumber] = team;
        (*team->Clan).Passive = false;
        ++(*team->Clan).TeamsNumber;
    }
    fpcrtl_memcpy(SpawnClansArray, ClansArray, sizeof(ClansArray));
    CurrentTeam = team;
    addteam_result = team;
    return addteam_result;
};
void uteams_RecountAllTeamsHealth()
{
    LongInt t;
    {t = 0;
     LongInt t__end__ = ((int)(TeamsCount) - 1);
     if (t <= t__end__) do {
                               uteams_RecountTeamHealth(TeamsArray[t]);
                           } while(t++ != t__end__);}
};
void uteams_InitTeams()
{
    LongInt i;
    LongInt t;
    LongInt th;
    LongInt h;
    {t = 0;
     LongInt t__end__ = ((int)(TeamsCount) - 1);
     if (t <= t__end__) do {
                               {
                                   if(!(*TeamsArray[t]).ExtDriven && ((*TeamsArray[t]).Hedgehogs[0].BotLevel == 0))
                                   {
                                       if((MissionTeam == NULL) || (_strcompare(MissionTeam->TeamName, (*TeamsArray[t]).TeamName)))
                                       {
                                           (*TeamsArray[t]).Clan->LocalOrAlly = true;
                                       }
                                       LocalTeam = t;
                                       LocalAmmo = (*TeamsArray[t]).Hedgehogs[0].AmmoStore;
                                   }
                                   th = 0;
                                   {i = 0;
                                    LongInt i__end__ = cMaxHHIndex;
                                    if (i <= i__end__) do {
                                                              if((*TeamsArray[t]).Hedgehogs[i].Gear != NULL)
                                                              {
                                                                  th += (*(*TeamsArray[t]).Hedgehogs[i].Gear).Health;
                                                              }
                                                          } while(i++ != i__end__);}
                                   if(th > MaxTeamHealth)
                                   {
                                       MaxTeamHealth = th;
                                   }
                                   if((GameFlags & gfKing) != 0)
                                   {
                                       (*TeamsArray[t]).hasKing = true;
                                       (*TeamsArray[t]).Hedgehogs[0].King = true;
                                       (*TeamsArray[t]).Hedgehogs[0].Hat = __str6;
                                       (*TeamsArray[t]).Hedgehogs[0].Effects[hePoisoned] = 0;
                                       h = (*(*TeamsArray[t]).Hedgehogs[0].Gear).Health;
                                       (*(*TeamsArray[t]).Hedgehogs[0].Gear).Health = ufloat_hwRound(ufloat_hwFloat_hwFloat_op_mul(ufloat_int2hwFloat(th), _0_375));
                                       if((*(*TeamsArray[t]).Hedgehogs[0].Gear).Health > h)
                                       {
                                           th -= h;
                                           th += (*(*TeamsArray[t]).Hedgehogs[0].Gear).Health;
                                           if(th > MaxTeamHealth)
                                           {
                                               MaxTeamHealth = th;
                                           }
                                       }
                                       else
                                       {
                                           (*(*TeamsArray[t]).Hedgehogs[0].Gear).Health = h;
                                       }
                                       if(((*(*TeamsArray[t]).Hedgehogs[0].Gear).Health < 0) || ((*(*TeamsArray[t]).Hedgehogs[0].Gear).Health > cMaxHogHealth))
                                       {
                                           (*(*TeamsArray[t]).Hedgehogs[0].Gear).Health = cMaxHogHealth;
                                       }
                                       (*TeamsArray[t]).Hedgehogs[0].InitialHealth = (*(*TeamsArray[t]).Hedgehogs[0].Gear).Health;
                                   }
                               }
                           } while(t++ != t__end__);}
    uteams_RecountAllTeamsHealth();
};
LongWord uteams_TeamSize(PTeam p)
{
    LongWord teamsize_result;
    LongWord i;
    LongWord value;
    value = 0;
    {i = 0;
     LongWord i__end__ = cMaxHHIndex;
     if (i <= i__end__) do {
                               if(p->Hedgehogs[i].Gear != NULL)
                               {
                                   ++value;
                               }
                           } while(i++ != i__end__);}
    teamsize_result = value;
    return teamsize_result;
};
void uteams_RecountClanHealth(PClan clan)
{
    LongInt i;
    {
        (*clan).ClanHealth = 0;
        {i = 0;
         LongInt i__end__ = ((int)((*clan).TeamsNumber) - 1);
         if (i <= i__end__) do {
                                   (*clan).ClanHealth += (*clan).Teams[i]->TeamHealth;
                               } while(i++ != i__end__);}
    }
};
void uteams_RecountTeamHealth(PTeam team)
{
    LongInt i;
    {
        (*team).TeamHealth = 0;
        {i = 0;
         LongInt i__end__ = cMaxHHIndex;
         if (i <= i__end__) do {
                                   if((*team).Hedgehogs[i].Gear != NULL)
                                   {
                                       (*team).TeamHealth += (*(*team).Hedgehogs[i].Gear).Health;
                                   }
                                   else
                                   {
                                       if((*team).Hedgehogs[i].GearHidden != NULL)
                                       {
                                           (*team).TeamHealth += (*(*team).Hedgehogs[i].GearHidden).Health;
                                       }
                                   }
                               } while(i++ != i__end__);}
        if((*team).TeamHealth > MaxTeamHealth)
        {
            MaxTeamHealth = (*team).TeamHealth;
            uteams_RecountAllTeamsHealth();
        }
    }
    uteams_RecountClanHealth(team->Clan);
    uvisualgearslist_AddVisualGear_3(0, 0, vgtTeamHealthSorter);
};
void uteams_RestoreHog(PHedgehog HH)
{
    HH->Gear = HH->GearHidden;
    HH->GearHidden = NULL;
    ugearslist_InsertGearToList(HH->Gear);
    (*HH->Gear).State = ((*HH->Gear).State & ~((gstHHDriven | gstInvisible) | gstAttacking)) | gstAttacked;
    ucollisions_AddCI(HH->Gear);
    (*HH->Gear).Active = true;
    uscript_ScriptCall_2(__str7, (*HH->Gear).uid);
    uvisualgearslist_AddVisualGear_3(0, 0, vgtTeamHealthSorter);
};
void uteams_RestoreTeamsFromSave()
{
    LongInt t;
    {t = 0;
     LongInt t__end__ = ((int)(TeamsCount) - 1);
     if (t <= t__end__) do {
                               TeamsArray[t]->ExtDriven = false;
                           } while(t++ != t__end__);}
};
void uteams_TeamGoneEffect(TTeam (*Team))
{
    LongInt i;
    {
        if((*Team).skippedTurns < 3)
        {
            ++(*Team).skippedTurns;
            {i = 0;
             LongInt i__end__ = cMaxHHIndex;
             if (i <= i__end__) do {
                                       {
                                           if((*Team).Hedgehogs[i].Gear != NULL)
                                           {
                                               (*Team).Hedgehogs[i].Gear->State = (*Team).Hedgehogs[i].Gear->State & ~gstHHDriven;
                                           }
                                       }
                                   } while(i++ != i__end__);}
            ucommands_ParseCommand_2(__str8, true);
        }
        else
        {
            {i = 0;
             LongInt i__end__ = cMaxHHIndex;
             if (i <= i__end__) do {
                                       {
                                           if((*Team).Hedgehogs[i].GearHidden != NULL)
                                           {
                                               uteams_RestoreHog(&((*Team).Hedgehogs[i]));
                                           }
                                           if((*Team).Hedgehogs[i].Gear != NULL)
                                           {
                                               (*(*Team).Hedgehogs[i].Gear->Hedgehog).Effects[heInvulnerable] = 0;
                                               (*Team).Hedgehogs[i].Gear->Damage = (*Team).Hedgehogs[i].Gear->Health;
                                               (*Team).Hedgehogs[i].Gear->State = ((*Team).Hedgehogs[i].Gear->State | gstHHGone) & ~gstHHDriven;
                                           }
                                       }
                                   } while(i++ != i__end__);}
        }
    }
};
void uteams_chAddMissionHH(string255 (*id))
{
    string255 s;
    LongInt Health;
    s = __str0;
    if(!isDeveloperMode)
    {
        return;
    }
    if(udebug_checkFails(CurrentTeam != NULL, __str9, true))
    {
        return;
    }
    {
        if(udebug_checkFails((*CurrentTeam).HedgehogsNumber <= cMaxHHIndex, _strconcat(_strconcat(_strconcat(_strconcat(__str10, (*CurrentTeam).TeamName), __str11), uutils_IntToStr((*CurrentTeam).HedgehogsNumber)), __str12), true))
        {
            return;
        }
        uutils_SplitBySpace(&((*id)), &(s));
        CurrentHedgehog = &((*CurrentTeam).Hedgehogs[(*CurrentTeam).HedgehogsNumber]);
        CurrentHedgehog->BotLevel = uutils_StrToInt((*id));
        CurrentHedgehog->Team = CurrentTeam;
        uutils_SplitBySpace(&(s), &((*id)));
        Health = uutils_StrToInt(s);
        if(udebug_checkFails((Health > 0) && (Health <= cMaxHogHealth), _strappend(_strconcat(__str13, uutils_IntToStr(cMaxHogHealth)), 0x29), true))
        {
            return;
        }
        CurrentHedgehog->Name = (*id);
        CurrentHedgehog->InitialHealth = Health;
        CurrentHedgehog->RevengeHog = NULL;
        ++(*CurrentTeam).HedgehogsNumber;
    }
};
void uteams_chAddHH(string255 (*id))
{
    string255 s;
    PGear Gear;
    s = __str0;
    if(!isDeveloperMode)
    {
        return;
    }
    if(udebug_checkFails(CurrentTeam != NULL, __str9, true))
    {
        return;
    }
    {
        if(udebug_checkFails((*CurrentTeam).HedgehogsNumber <= cMaxHHIndex, _strconcat(_strconcat(_strconcat(_strconcat(__str10, (*CurrentTeam).TeamName), __str11), uutils_IntToStr((*CurrentTeam).HedgehogsNumber)), __str12), true))
        {
            return;
        }
        uutils_SplitBySpace(&((*id)), &(s));
        uteams_SwitchCurrentHedgehog(&((*CurrentTeam).Hedgehogs[(*CurrentTeam).HedgehogsNumber]));
        CurrentHedgehog->BotLevel = uutils_StrToInt((*id));
        CurrentHedgehog->Team = CurrentTeam;
        Gear = ugearslist_AddGear_7(0, 0, gtHedgehog, 0, _0, _0, 0);
        uutils_SplitBySpace(&(s), &((*id)));
        Gear->Health = uutils_StrToInt(s);
        if(udebug_checkFails((Gear->Health > 0) && (Gear->Health <= cMaxHogHealth), _strappend(_strconcat(__str13, uutils_IntToStr(cMaxHogHealth)), 0x29), true))
        {
            return;
        }
        if((GameFlags & gfSharedAmmo) != 0)
        {
            CurrentHedgehog->AmmoStore = (*CurrentTeam).Clan->ClanIndex;
        }
        else
        {
            if((GameFlags & gfPerHogAmmo) != 0)
            {
                uammos_AddAmmoStore();
                CurrentHedgehog->AmmoStore = StoreCnt - 1;
            }
            else
            {
                CurrentHedgehog->AmmoStore = TeamsCount - 1;
            }
        }
        CurrentHedgehog->Gear = Gear;
        CurrentHedgehog->Name = (*id);
        CurrentHedgehog->InitialHealth = Gear->Health;
        CurrentHedgehog->RevengeHog = NULL;
        CurrentHedgehog->FlownOffMap = false;
        (*CurrentTeam).CurrHedgehog = (*CurrentTeam).HedgehogsNumber;
        ++(*CurrentTeam).HedgehogsNumber;
    }
};
void uteams_loadTeamBinds(string255 s)
{
    LongInt i;
    {i = 1;
     LongInt i__end__ = fpcrtl_Length(s);
     if (i <= i__end__) do {
                               if(((s.s[i] == 0x5c) || (s.s[i] == 0x2f)) || (s.s[i] == 0x3a))
                               {
                                   s.s[i] = 0x5f;
                               }
                           } while(i++ != i__end__);}
    s = _strconcat(_strconcat(_strappend(cPathz[ptTeams], 0x2f), s), __str14);
    uinputhandler_loadBinds(__str15, s);
};
void uteams_makeTeamNameUnique(PTeam chTeam)
{
    string255 tail;
    LongInt t;
    LongInt numLen;
    LongInt numTail;
    boolean nameDupeCheck;
    char chChar;
    nameDupeCheck = false;
    while(nameDupeCheck == false)
    {
        nameDupeCheck = true;
        {t = 0;
         LongInt t__end__ = TeamsCount - 1;
         if (t <= t__end__) do {
                                   if((chTeam != TeamsArray[t]) && (_strcompare(TeamsArray[t]->TeamName, chTeam->TeamName)))
                                   {
                                       numLen = 0;
                                       chChar = chTeam->TeamName.s[fpcrtl_Length(chTeam->TeamName) - numLen];
                                       while(((chChar >= 0x30) && (chChar <= 0x39)) && (numLen < fpcrtl_Length(chTeam->TeamName)))
                                       {
                                           ++numLen;
                                           chChar = chTeam->TeamName.s[fpcrtl_Length(chTeam->TeamName) - numLen];
                                       }
                                       if(numLen > 0)
                                       {
                                           tail = fpcrtl_copy(chTeam->TeamName, (fpcrtl_Length(chTeam->TeamName) - numLen) + 1, numLen);
                                           fpcrtl_val(tail, numTail);
                                           ++numTail;
                                           tail = uutils_IntToStr(numTail);
                                           chTeam->TeamName = _strconcat(fpcrtl_copy(chTeam->TeamName, 0, fpcrtl_Length(chTeam->TeamName) - numLen), tail);
                                       }
                                       else
                                       {
                                           chTeam->TeamName = _strconcat(chTeam->TeamName, __str16);
                                       }
                                       nameDupeCheck = false;
                                       break;
                                   }
                               } while(t++ != t__end__);}
    }
};
void uteams_chAddTeam(string255 (*s))
{
    LongWord Color;
    string255 ts;
    string255 cs;
    cs = __str0;
    ts = __str0;
    if(isDeveloperMode)
    {
        uutils_SplitBySpace(&((*s)), &(cs));
        uutils_SplitBySpace(&(cs), &(ts));
        Color = uutils_StrToInt(cs);
        Color = Color | 0xff000000;
        uteams_AddTeam(Color);
        if(CurrentTeam != NULL)
        {
            CurrentTeam->TeamName = ts;
            uteams_makeTeamNameUnique(CurrentTeam);
            CurrentTeam->PlayerHash = (*s);
            uteams_loadTeamBinds(ts);
            if(((GameType == gmtDemo) || (GameType == gmtSave) || (GameType == gmtRecord)))
            {
                CurrentTeam->ExtDriven = true;
            }
            CurrentTeam->voicepack = usound_AskForVoicepack(__str17);
        }
    }
};
void uteams_chSetMissionTeam(string255 (*s))
{
    string255 ts;
    string255 cs;
    cs = __str0;
    ts = __str0;
    if(isDeveloperMode)
    {
        uutils_SplitBySpace(&((*s)), &(cs));
        uutils_SplitBySpace(&(cs), &(ts));
        uteams_SetMissionTeam();
        if(CurrentTeam != NULL)
        {
            CurrentTeam->TeamName = ts;
            CurrentTeam->PlayerHash = (*s);
            uteams_loadTeamBinds(ts);
            CurrentTeam->voicepack = usound_AskForVoicepack(__str17);
        }
    }
};
void uteams_chSetHHCoords(string255 (*x))
{
    string255 y;
    LongInt t;
    y = __str0;
    if((!isDeveloperMode || (CurrentHedgehog == NULL)) || (CurrentHedgehog->Gear == NULL))
    {
        return;
    }
    uutils_SplitBySpace(&((*x)), &(y));
    t = uutils_StrToInt((*x));
    (*CurrentHedgehog->Gear).X = ufloat_int2hwFloat(t);
    t = uutils_StrToInt(y);
    (*CurrentHedgehog->Gear).Y = ufloat_int2hwFloat(t);
};
void uteams_chBind(string255 (*id))
{
    if(CurrentTeam == NULL)
    {
        return;
    }
    uinputhandler_addBind(&(CurrentTeam->Binds), &((*id)));
};
void uteams_chTeamGone(string255 (*s))
{
    LongInt t;
    LongInt i;
    boolean isSynced;
    isSynced = (*s).s[1] == 0x73;
    fpcrtl_Delete((*s), 1, 1);
    t = 0;
    while((t < TeamsCount) && (_strncompare(TeamsArray[t]->TeamName, (*s))))
    {
        ++t;
    }
    if(t == TeamsCount)
    {
        return;
    }
    TeamsArray[t]->isGoneFlagPendingToBeSet = true;
    if(isSynced)
    {
        {i = 0;
         LongInt i__end__ = ((int)(TeamsCount) - 1);
         if (i <= i__end__) do {
                                   {
                                       if(!(*TeamsArray[i]).hasGone && (*TeamsArray[i]).isGoneFlagPendingToBeSet)
                                       {
                                           if(!TeamsGameOver)
                                           {
                                               uchat_AddChatString(_strprepend(0x7, ulocale_Format_2(_strconcat(__str18, fpcrtl_astr2str(trmsg[sidTeamGone])), (*TeamsArray[i]).TeamName)));
                                           }
                                           if(!CurrentTeam->ExtDriven)
                                           {
                                               uio_SendIPC(_strconcat(__str19, (*s)));
                                           }
                                           (*TeamsArray[i]).hasGone = true;
                                           (*TeamsArray[i]).skippedTurns = 0;
                                           (*TeamsArray[i]).isGoneFlagPendingToBeSet = false;
                                           uteams_RecountTeamHealth(TeamsArray[i]);
                                       }
                                       if((*TeamsArray[i]).hasGone && (*TeamsArray[i]).isGoneFlagPendingToBeUnset)
                                       {
                                           ucommands_ParseCommand_2(_strconcat(__str20, (*s)), true);
                                       }
                                   }
                               } while(i++ != i__end__);}
    }
    else
    {
        if((!CurrentTeam->ExtDriven || (_strcompare(CurrentTeam->TeamName, (*s)))) || CurrentTeam->hasGone)
        {
            ucommands_ParseCommand_2(_strconcat(__str21, (*s)), true);
        }
    }
};
void uteams_chTeamBack(string255 (*s))
{
    LongInt t;
    boolean isSynced;
    isSynced = (*s).s[1] == 0x73;
    fpcrtl_Delete((*s), 1, 1);
    t = 0;
    while((t < TeamsCount) && (_strncompare(TeamsArray[t]->TeamName, (*s))))
    {
        ++t;
    }
    if(t == TeamsCount)
    {
        return;
    }
    if(isSynced)
    {
        {
            if((*TeamsArray[t]).hasGone)
            {
                uchat_AddChatString(_strprepend(0x8, ulocale_Format_2(_strconcat(__str18, fpcrtl_astr2str(trmsg[sidTeamBack])), (*TeamsArray[t]).TeamName)));
                if(!CurrentTeam->ExtDriven)
                {
                    uio_SendIPC(_strconcat(__str22, (*s)));
                }
                (*TeamsArray[t]).hasGone = false;
                uteams_RecountTeamHealth(TeamsArray[t]);
                if((*TeamsArray[t]).isGoneFlagPendingToBeUnset && (_strcompare((*TeamsArray[t]).Owner, UserNick)))
                {
                    (*TeamsArray[t]).ExtDriven = false;
                }
                (*TeamsArray[t]).isGoneFlagPendingToBeUnset = false;
            }
        }
    }
    else
    {
        TeamsArray[t]->isGoneFlagPendingToBeUnset = true;
        if(!CurrentTeam->ExtDriven)
        {
            ucommands_ParseCommand_2(_strconcat(__str20, (*s)), true);
        }
    }
};
void uteams_SwitchCurrentHedgehog(PHedgehog newHog)
{
    boolean oldCI;
    boolean newCI;
    PHedgehog oldHH;
    if((CurrentHedgehog != NULL) && (CurrentHedgehog->CurAmmoType == amKnife))
    {
        ustore_LoadHedgehogHat(&((*CurrentHedgehog)), CurrentHedgehog->Hat);
    }
    oldCI = ((CurrentHedgehog != NULL) && (CurrentHedgehog->Gear != NULL)) && ((*CurrentHedgehog->Gear).CollisionIndex >= 0);
    newCI = (newHog->Gear != NULL) && ((*newHog->Gear).CollisionIndex >= 0);
    if(oldCI)
    {
        ucollisions_DeleteCI(CurrentHedgehog->Gear);
    }
    if(newCI)
    {
        ucollisions_DeleteCI(newHog->Gear);
    }
    oldHH = CurrentHedgehog;
    CurrentHedgehog = newHog;
    if(oldCI)
    {
        ucollisions_AddCI(oldHH->Gear);
    }
    if(newCI)
    {
        ucollisions_AddCI(newHog->Gear);
    }
};
void uteams_chSetHat(string255 (*s))
{
    if(!isDeveloperMode || (CurrentTeam == NULL))
    {
        return;
    }
    {
        if(!CurrentHedgehog->King)
        {
            if(((_strcompare((*s), __str0)) || (((GameFlags & gfKing) != 0) && (_strcompare((*s), __str6)))) || (((fpcrtl_Length((*s)) > 39) && (_strcompare(fpcrtl_copy((*s), 1, 8), __str23))) && (_strncompare(fpcrtl_copy((*s), 9, 32), (*CurrentTeam).PlayerHash))))
            {
                CurrentHedgehog->Hat = __str24;
            }
            else
            {
                CurrentHedgehog->Hat = (*s);
            }
        }
    }
};
void uteams_chGrave(string255 (*s))
{
    if(CurrentTeam == NULL)
    {
        udebug_OutError(_strconcat(errmsgIncorrectUse, __str25), true);
    }
    if((*s).s[1] == 0x22)
    {
        fpcrtl_Delete((*s), 1, 1);
    }
    if((*s).s[((Byte)(*s).s[0])] == 0x22)
    {
        fpcrtl_Delete((*s), ((Byte)(*s).s[0]), 1);
    }
    CurrentTeam->GraveName = (*s);
};
void uteams_chFort(string255 (*s))
{
    if(CurrentTeam == NULL)
    {
        udebug_OutError(_strconcat(errmsgIncorrectUse, __str26), true);
    }
    if((*s).s[1] == 0x22)
    {
        fpcrtl_Delete((*s), 1, 1);
    }
    if((*s).s[((Byte)(*s).s[0])] == 0x22)
    {
        fpcrtl_Delete((*s), ((Byte)(*s).s[0]), 1);
    }
    CurrentTeam->FortName = (*s);
};
void uteams_chFlag(string255 (*s))
{
    if(CurrentTeam == NULL)
    {
        udebug_OutError(_strconcat(errmsgIncorrectUse, __str27), true);
    }
    if((*s).s[1] == 0x22)
    {
        fpcrtl_Delete((*s), 1, 1);
    }
    if((*s).s[((Byte)(*s).s[0])] == 0x22)
    {
        fpcrtl_Delete((*s), ((Byte)(*s).s[0]), 1);
    }
    CurrentTeam->Flag = (*s);
};
void uteams_chOwner(string255 (*s))
{
    if(CurrentTeam == NULL)
    {
        udebug_OutError(_strconcat(errmsgIncorrectUse, __str28), true);
    }
    CurrentTeam->Owner = (*s);
};
void uteams_initModule()
{
    ucommands_RegisterVariable_3(__str29, &(uteams_chAddHH), false);
    ucommands_RegisterVariable_3(__str30, &(uteams_chAddMissionHH), false);
    ucommands_RegisterVariable_3(__str31, &(uteams_chAddTeam), false);
    ucommands_RegisterVariable_3(__str32, &(uteams_chSetMissionTeam), false);
    ucommands_RegisterVariable_3(__str33, &(uteams_chSetHHCoords), false);
    ucommands_RegisterVariable_3(__str15, &(uteams_chBind), true);
    ucommands_RegisterVariable_3(__str34, &(uteams_chTeamGone), true);
    ucommands_RegisterVariable_3(__str35, &(uteams_chTeamBack), true);
    ucommands_RegisterVariable_3(__str36, &(uteams_chFort), false);
    ucommands_RegisterVariable_3(__str37, &(uteams_chGrave), false);
    ucommands_RegisterVariable_3(__str38, &(uteams_chSetHat), false);
    ucommands_RegisterVariable_3(__str39, &(uteams_chFlag), false);
    ucommands_RegisterVariable_3(__str40, &(uteams_chOwner), false);
    CurrentTeam = NULL;
    PreviousTeam = NULL;
    CurrentHedgehog = NULL;
    TeamsCount = 0;
    ClansCount = 0;
    LocalTeam = -1;
    LocalAmmo = -1;
    TeamsGameOver = false;
    NextClan = true;
    SwapClanPre = -1;
    SwapClanReal = -1;
    MaxTeamHealth = 0;
};
void uteams_freeModule()
{
    LongWord i;
    LongWord h;
    CurrentHedgehog = NULL;
    if(TeamsCount > 0)
    {
        {i = 0;
         LongWord i__end__ = ((int)(TeamsCount) - 1);
         if (i <= i__end__) do {
                                   {h = 0;
                                    LongWord h__end__ = cMaxHHIndex;
                                    if (h <= h__end__) do {
                                                              {
                                                                  if(TeamsArray[i]->Hedgehogs[h].GearHidden != NULL)
                                                                  {
                                                                      fpcrtl_dispose(TeamsArray[i]->Hedgehogs[h].GearHidden);
                                                                  }
                                                                  utextures_FreeAndNilTexture(&(TeamsArray[i]->Hedgehogs[h].NameTagTex));
                                                                  utextures_FreeAndNilTexture(&(TeamsArray[i]->Hedgehogs[h].HealthTagTex));
                                                                  utextures_FreeAndNilTexture(&(TeamsArray[i]->Hedgehogs[h].HatTex));
                                                              }
                                                          } while(h++ != h__end__);}
                                   {
                                       utextures_FreeAndNilTexture(&((*TeamsArray[i]).NameTagTex));
                                       utextures_FreeAndNilTexture(&((*TeamsArray[i]).OwnerTex));
                                       utextures_FreeAndNilTexture(&((*TeamsArray[i]).GraveTex));
                                       utextures_FreeAndNilTexture(&((*TeamsArray[i]).AIKillsTex));
                                       utextures_FreeAndNilTexture(&((*TeamsArray[i]).LuaTeamValueTex));
                                       utextures_FreeAndNilTexture(&((*TeamsArray[i]).FlagTex));
                                   }
                                   fpcrtl_dispose(TeamsArray[i]);
                               } while(i++ != i__end__);}
        {i = 0;
         LongWord i__end__ = ((int)(ClansCount) - 1);
         if (i <= i__end__) do {
                                   utextures_FreeAndNilTexture(&(ClansArray[i]->HealthTex));
                                   fpcrtl_dispose(ClansArray[i]);
                               } while(i++ != i__end__);}
    }
    TeamsCount = 0;
    ClansCount = 0;
    SwapClanPre = -1;
    SwapClanReal = -1;
};
