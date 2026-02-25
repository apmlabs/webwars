#include "fpcrtl.h"

#include "uStats.h"
LongInt TotalRoundsPre;
LongInt TotalRoundsReal;
LongInt FinishedTurnsTotal;
boolean SendGameResultOn = true;
boolean SendRankingStatsOn = true;
boolean SendAchievementsStatsOn = true;
boolean SendHealthStatsOn = true;
PClanDeathLogEntry ClanDeathLog;
#include "uSound.h"
#include "uLocale.h"
#include "uVariables.h"
#include "uUtils.h"
#include "uIO.h"
#include "uCaptions.h"
#include "uMisc.h"
#include "uConsole.h"
#include "uScript.h"
static const string255 __str9 = STRINIT("GHOST_POINTS");
static const string255 __str8 = STRINIT("ACHIEVEMENT");
static const string255 __str7 = STRINIT("onAchievementsDeclaration");
static const string255 __str6 = STRINIT("DRAW");
static const string255 __str5 = STRINIT("WINNERS");
static const string255 __str4 = STRINIT("onGameResult");
static const string255 __str3 = STRINIT(" (");
static const string255 __str2 = STRINIT("1");
static const string255 __str1 = STRINIT("");
static const string255 __str0 = STRINIT("FLIGHT");
static LongWord DamageClan = 0;
static LongWord DamageTeam = 0;
static LongWord DamageTotal = 0;
static LongWord DamageTurn = 0;
static LongWord PoisonTurn = 0;
static LongWord PoisonClan = 0;
static LongWord PoisonTeam = 0;
static LongWord PoisonTotal = 0;
static LongWord KillsClan = 0;
static LongWord KillsTeam = 0;
static LongWord KillsSD = 0;
static LongWord Kills = 0;
static LongWord KillsTotal = 0;
static LongWord HitTargets = 0;
static LongWord AmmoUsedCount = 0;
static boolean AmmoDamagingUsed = false;
static boolean FirstBlood = false;
static boolean StepFirstBlood = false;
static boolean LeaveMeAlone = false;
static LongWord SkippedTurns = 0;
static boolean isTurnSkipped = false;
static PVoicepack vpHurtSameClan = NULL;
static PVoicepack vpHurtEnemy = NULL;
void ustats_HedgehogPoisoned(PGear Gear,PHedgehog Attacker)
{
    if((*Attacker->Team).Clan == (*(*Gear->Hedgehog).Team).Clan)
    {
        vpHurtSameClan = (*(*Gear->Hedgehog).Team).voicepack;
        ++PoisonClan;
        if(Attacker->Team == (*Gear->Hedgehog).Team)
        {
            ++PoisonTeam;
        }
    }
    else
    {
        if(!FirstBlood)
        {
            StepFirstBlood = true;
        }
        vpHurtEnemy = (*(*Gear->Hedgehog).Team).voicepack;
        ++PoisonTurn;
    }
    (*Gear->Hedgehog).stats.StepPoisoned = true;
    ++PoisonTotal;
};
void ustats_HedgehogSacrificed(PHedgehog Hedgehog)
{
    Hedgehog->stats.Sacrificed = true;
};
void ustats_HedgehogDamaged(PGear Gear,PHedgehog Attacker,LongWord Damage,boolean killed)
{
    boolean sameClan;
    sameClan = false;
    if(Attacker != NULL)
    {
        sameClan = (*Attacker->Team).Clan == (*(*Gear->Hedgehog).Team).Clan;
    }
    if(sameClan)
    {
        vpHurtSameClan = (*(*Gear->Hedgehog).Team).voicepack;
    }
    else
    {
        if(!FirstBlood)
        {
            StepFirstBlood = true;
        }
        vpHurtEnemy = (*(*Gear->Hedgehog).Team).voicepack;
        if(((Attacker != NULL) && !killed) && !bDuringWaterRise)
        {
            if((((*Gear->Hedgehog).RevengeHog != NULL) && ((*Gear->Hedgehog).RevengeHog == Attacker)) && ((*Gear->Hedgehog).stats.StepRevenge == false))
            {
                LeaveMeAlone = true;
            }
            if((Attacker->RevengeHog != NULL) && (Attacker->RevengeHog == Gear->Hedgehog))
            {
                Attacker->stats.GotRevenge = true;
                Attacker->stats.StepDamageRecvInRow = 0;
                Attacker->RevengeHog = NULL;
            }
            else
            {
                (*Gear->Hedgehog).RevengeHog = Attacker;
                (*Gear->Hedgehog).stats.StepRevenge = true;
            }
        }
    }
    if(!bDuringWaterRise)
    {
        if(Attacker != NULL)
        {
            Attacker->stats.StepDamageGiven += Damage;
        }
        (*Gear->Hedgehog).stats.StepDamageRecv += Damage;
    }
    if((*CurrentHedgehog->Team).Clan == (*(*Gear->Hedgehog).Team).Clan)
    {
        DamageClan += Damage;
    }
    if(CurrentHedgehog->Team == (*Gear->Hedgehog).Team)
    {
        DamageTeam += Damage;
    }
    if(killed)
    {
        (*Gear->Hedgehog).stats.StepDied = true;
        ++Kills;
        ++KillsTotal;
        if(bDuringWaterRise)
        {
            ++KillsSD;
        }
        else
        {
            if(Attacker != NULL)
            {
                ++Attacker->stats.StepKills;
                ++(*Attacker->Team).stats.Kills;
                if(_strcompare((*Attacker->Team).TeamName, (*(*Gear->Hedgehog).Team).TeamName))
                {
                    ++(*Attacker->Team).stats.TeamKills;
                    (*Attacker->Team).stats.TeamDamage += Gear->Damage;
                }
                if(Gear == Attacker->Gear)
                {
                    ++(*Attacker->Team).stats.Suicides;
                }
                if((*Attacker->Team).Clan == (*(*Gear->Hedgehog).Team).Clan)
                {
                    ++KillsClan;
                    if(Attacker->Team == (*Gear->Hedgehog).Team)
                    {
                        ++KillsTeam;
                    }
                }
            }
        }
    }
    DamageTotal += Damage;
    DamageTurn += Damage;
};
void ustats_TargetHit()
{
    ++HitTargets;
};
void ustats_Skipped()
{
    ++SkippedTurns;
    isTurnSkipped = true;
};
boolean ustats_getIsTurnSkipped()
{
    boolean getisturnskipped_result;
    getisturnskipped_result = isTurnSkipped;
    return getisturnskipped_result;
};
void ustats_TurnStats()
{
    LongInt i;
    LongInt t;
    LongWord c;
    PClanDeathLogEntry newEntry;
    ++FinishedTurnsTotal;
    {t = 0;
     LongInt t__end__ = ((int)(TeamsCount) - 1);
     if (t <= t__end__) do {
                               {
                                   {i = 0;
                                    LongInt i__end__ = cMaxHHIndex;
                                    if (i <= i__end__) do {
                                                              {
                                                                  (*TeamsArray[t]).Hedgehogs[i].stats.DamageRecv += (*TeamsArray[t]).Hedgehogs[i].stats.StepDamageRecv;
                                                                  (*TeamsArray[t]).Hedgehogs[i].stats.DamageGiven += (*TeamsArray[t]).Hedgehogs[i].stats.StepDamageGiven;
                                                                  if((*TeamsArray[t]).Hedgehogs[i].stats.StepDamageRecv > (*TeamsArray[t]).Hedgehogs[i].stats.MaxStepDamageRecv)
                                                                  {
                                                                      (*TeamsArray[t]).Hedgehogs[i].stats.MaxStepDamageRecv = (*TeamsArray[t]).Hedgehogs[i].stats.StepDamageRecv;
                                                                  }
                                                                  if((*TeamsArray[t]).Hedgehogs[i].stats.StepDamageGiven > (*TeamsArray[t]).Hedgehogs[i].stats.MaxStepDamageGiven)
                                                                  {
                                                                      (*TeamsArray[t]).Hedgehogs[i].stats.MaxStepDamageGiven = (*TeamsArray[t]).Hedgehogs[i].stats.StepDamageGiven;
                                                                  }
                                                                  if((*TeamsArray[t]).Hedgehogs[i].stats.StepKills > (*TeamsArray[t]).Hedgehogs[i].stats.MaxStepKills)
                                                                  {
                                                                      (*TeamsArray[t]).Hedgehogs[i].stats.MaxStepKills = (*TeamsArray[t]).Hedgehogs[i].stats.StepKills;
                                                                  }
                                                                  if(((*TeamsArray[t]).Hedgehogs[i].Team != NULL) && ((*(*(*TeamsArray[t]).Hedgehogs[i].Team).Clan).ClanIndex != (*(*CurrentHedgehog->Team).Clan).ClanIndex))
                                                                  {
                                                                      if((*TeamsArray[t]).Hedgehogs[i].stats.StepDamageRecv > 0)
                                                                      {
                                                                          ++(*TeamsArray[t]).Hedgehogs[i].stats.StepDamageRecvInRow;
                                                                      }
                                                                      else
                                                                      {
                                                                          (*TeamsArray[t]).Hedgehogs[i].stats.StepDamageRecvInRow = 0;
                                                                      }
                                                                      if((*TeamsArray[t]).Hedgehogs[i].stats.StepDamageRecvInRow >= 3)
                                                                      {
                                                                          LeaveMeAlone = true;
                                                                      }
                                                                  }
                                                              }
                                                          } while(i++ != i__end__);}
                               }
                           } while(t++ != t__end__);}
    c = 0;
    newEntry = NULL;
    {t = 0;
     LongInt t__end__ = ((int)(ClansCount) - 1);
     if (t <= t__end__) do {
                               {
                                   if(((*ClansArray[t]).ClanHealth == 0) && (ClansArray[t]->DeathLogged == false))
                                   {
                                       if(c == 0)
                                       {
                                           fpcrtl_new(newEntry);
                                           newEntry->Turn = FinishedTurnsTotal;
                                           newEntry->NextEntry = NULL;
                                       }
                                       newEntry->KilledClans[c] = ClansArray[t];
                                       ++c;
                                       newEntry->KilledClansCount = c;
                                       ClansArray[t]->DeathLogged = true;
                                   }
                                   if(SendHealthStatsOn)
                                   {
                                       uio_SendStat(siClanHealth, _strconcat(_strappend(uutils_IntToStr((*ClansArray[t]).Color), 0x20), uutils_IntToStr((*ClansArray[t]).ClanHealth)));
                                   }
                               }
                           } while(t++ != t__end__);}
    if(newEntry != NULL)
    {
        if(ClanDeathLog != NULL)
        {
            newEntry->NextEntry = ClanDeathLog;
        }
        ClanDeathLog = newEntry;
    }
};
void ustats_TurnReaction()
{
    LongInt killsCheck;
    astring s;
    if(FinishedTurnsTotal != 0)
    {
        s = fpcrtl_str2astr(CurrentHedgehog->Name);
        ++CurrentHedgehog->stats.FinishedTurns;
        killsCheck = KillsSD;
        if(CurrentHedgehog->stats.Sacrificed)
        {
            ++killsCheck;
        }
        if(((StepFirstBlood && !FirstBlood) && (ClansCount > 1)) && (((DamageTotal > 0) || (KillsTotal > 0)) || (PoisonTotal > 0)))
        {
            FirstBlood = true;
            usound_AddVoice_2(sndFirstBlood, CurrentTeam->voicepack);
        }
        else
        {
            if((CurrentHedgehog->stats.Sacrificed == false) && (((CurrentHedgehog->stats.StepDamageRecv > 0) || CurrentHedgehog->stats.StepPoisoned) || CurrentHedgehog->stats.StepDied))
            {
                if(((CurrentHedgehog->stats.StepDamageGiven == CurrentHedgehog->stats.StepDamageRecv) && (CurrentHedgehog->stats.StepDamageRecv >= 1)) && !CurrentHedgehog->stats.StepDied)
                {
                    ucaptions_AddCaption(ulocale_FormatA_2(ulocale_GetEventString(eidHurtSelf), s), capcolDefault, capgrpMessage);
                    if((CurrentHedgehog->stats.StepDamageGiven <= CurrentHedgehog->stats.StepDamageRecv) && (CurrentHedgehog->stats.StepDamageRecv >= 1))
                    {
                        switch(fpcrtl_random(3))
                        {case 0:usound_AddVoice_2(sndStupid, PreviousTeam->voicepack);
                                break;
                         case 1:usound_AddVoice_2(sndBugger, CurrentTeam->voicepack);
                                break;
                         case 2:usound_AddVoice_2(sndDrat, CurrentTeam->voicepack);
                                break;
                         default: break;}
                    }
                }
                else
                {
                    usound_AddVoice_2(sndStupid, PreviousTeam->voicepack);
                }
            }
            else
            {
                if(((DamageClan != 0) || (KillsClan > killsCheck)) || (PoisonClan != 0))
                {
                    if((DamageTurn > DamageClan) || ((((int64_t) (Kills)) - ((int64_t) (KillsSD))) > KillsClan))
                    {
                        if(fpcrtl_random(2) == 0)
                        {
                            usound_AddVoice_2(sndNutter, CurrentTeam->voicepack);
                        }
                        else
                        {
                            usound_AddVoice_2(sndWatchIt, vpHurtSameClan);
                        }
                    }
                    else
                    {
                        if((fpcrtl_random(2) == 0) && (((DamageTeam != 0) || (KillsTeam > killsCheck)) || (PoisonTeam != 0)))
                        {
                            usound_AddVoice_2(sndSameTeam, vpHurtSameClan);
                        }
                        else
                        {
                            usound_AddVoice_2(sndTraitor, vpHurtSameClan);
                        }
                    }
                }
                else
                {
                    if(((CurrentHedgehog->stats.StepDamageGiven != 0) || (CurrentHedgehog->stats.StepKills > killsCheck)) || (PoisonTurn != 0))
                    {
                        if(Kills > (killsCheck + 2))
                        {
                            usound_AddVoice_2(sndAmazing, CurrentTeam->voicepack);
                        }
                        else
                        {
                            if(Kills == (killsCheck + 2))
                            {
                                if(fpcrtl_random(2) == 0)
                                {
                                    usound_AddVoice_2(sndBrilliant, CurrentTeam->voicepack);
                                }
                                else
                                {
                                    usound_AddVoice_2(sndExcellent, CurrentTeam->voicepack);
                                }
                            }
                            else
                            {
                                if(Kills == (killsCheck + 1))
                                {
                                    usound_AddVoice_2(sndEnemyDown, CurrentTeam->voicepack);
                                }
                                else
                                {
                                    if(CurrentHedgehog->stats.GotRevenge)
                                    {
                                        usound_AddVoice_2(sndRevenge, (*CurrentHedgehog->Team).voicepack);
                                        switch(fpcrtl_random(4))
                                        {case 0:usound_AddVoice_4(sndRegret, vpHurtEnemy, false, true);
                                                break;
                                         case 1:usound_AddVoice_4(sndGonnaGetYou, vpHurtEnemy, false, true);
                                                break;
                                         case 2:usound_AddVoice_4(sndIllGetYou, vpHurtEnemy, false, true);
                                                break;
                                         case 3:usound_AddVoice_4(sndJustYouWait, vpHurtEnemy, false, true);
                                                break;
                                         default: break;}
                                    }
                                    else
                                    {
                                        if(LeaveMeAlone)
                                        {
                                            if(fpcrtl_random(2) == 0)
                                            {
                                                usound_AddVoice_2(sndCutItOut, vpHurtEnemy);
                                            }
                                            else
                                            {
                                                usound_AddVoice_2(sndLeaveMeAlone, vpHurtEnemy);
                                            }
                                        }
                                        else
                                        {
                                            switch(fpcrtl_random(4))
                                            {case 0:usound_AddVoice_2(sndRegret, vpHurtEnemy);
                                                    break;
                                             case 1:usound_AddVoice_2(sndGonnaGetYou, vpHurtEnemy);
                                                    break;
                                             case 2:usound_AddVoice_2(sndIllGetYou, vpHurtEnemy);
                                                    break;
                                             case 3:usound_AddVoice_2(sndJustYouWait, vpHurtEnemy);
                                                    break;
                                             default: break;}
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        if(((((AmmoDamagingUsed && (Kills <= killsCheck)) && (PoisonTurn == 0)) && (PoisonClan == 0)) && (DamageTurn == 0)) && (HitTargets == 0))
                        {
                            if(CurrentHedgehog->stats.Sacrificed)
                            {
                                switch(fpcrtl_random(3))
                                {case 0:usound_AddVoice_2(sndMissed, PreviousTeam->voicepack);
                                        break;
                                 case 1:usound_AddVoice_2(sndStupid, PreviousTeam->voicepack);
                                        break;
                                 case 2:usound_AddVoice_2(sndNutter, PreviousTeam->voicepack);
                                        break;
                                 default: break;}
                            }
                            else
                            {
                                usound_AddVoice_2(sndMissed, PreviousTeam->voicepack);
                            }
                        }
                        else
                        {
                            if((AmmoUsedCount > 0) && !isTurnSkipped)
                            {
                            }
                            else
                            {
                                if((isTurnSkipped && !PlacingHogs) && !PlacingKings)
                                {
                                    usound_AddVoice_2(sndCoward, PreviousTeam->voicepack);
                                    ucaptions_AddCaption(ulocale_FormatA_2(ulocale_GetEventString(eidTurnSkipped), s), capcolDefault, capgrpMessage);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
};
void ustats_TurnStatsReset()
{
    LongInt t;
    LongInt i;
    {t = 0;
     LongInt t__end__ = ((int)(TeamsCount) - 1);
     if (t <= t__end__) do {
                               {
                                   {i = 0;
                                    LongInt i__end__ = cMaxHHIndex;
                                    if (i <= i__end__) do {
                                                              {
                                                                  (*TeamsArray[t]).Hedgehogs[i].stats.StepKills = 0;
                                                                  (*TeamsArray[t]).Hedgehogs[i].stats.StepDamageRecv = 0;
                                                                  (*TeamsArray[t]).Hedgehogs[i].stats.StepDamageGiven = 0;
                                                                  (*TeamsArray[t]).Hedgehogs[i].stats.StepPoisoned = false;
                                                                  (*TeamsArray[t]).Hedgehogs[i].stats.StepDied = false;
                                                                  (*TeamsArray[t]).Hedgehogs[i].stats.GotRevenge = false;
                                                                  (*TeamsArray[t]).Hedgehogs[i].stats.StepRevenge = false;
                                                              }
                                                          } while(i++ != i__end__);}
                               }
                           } while(t++ != t__end__);}
    Kills = 0;
    KillsSD = 0;
    KillsClan = 0;
    KillsTeam = 0;
    DamageClan = 0;
    DamageTeam = 0;
    DamageTurn = 0;
    HitTargets = 0;
    PoisonClan = 0;
    PoisonTeam = 0;
    PoisonTurn = 0;
    AmmoUsedCount = 0;
    LeaveMeAlone = false;
    AmmoDamagingUsed = false;
    isTurnSkipped = false;
    StepFirstBlood = false;
};
void ustats_AmmoUsed(TAmmoType am)
{
    ++AmmoUsedCount;
    AmmoDamagingUsed = AmmoDamagingUsed || Ammoz[am].isDamaging;
};
void ustats_hedgehogFlight(PGear Gear,LongWord time)
{
    if(time > 4000)
    {
        uconsole_WriteLnToConsole(__str0);
        uconsole_WriteLnToConsole((*(*Gear->Hedgehog).Team).TeamName);
        uconsole_WriteLnToConsole(uutils_IntToStr(time));
        uconsole_WriteLnToConsole(__str1);
    }
};
void ustats_SendStats()
{
    LongInt i;
    LongInt t;
    LongInt c;
    LongWord msd;
    LongWord msk;
    PHedgehog msdhh;
    PHedgehog mskhh;
    LongWord mskcnt;
    LongWord maxTeamKills;
    string255 maxTeamKillsName;
    LongWord maxTurnSkips;
    string255 maxTurnSkipsName;
    LongWord maxTeamDamage;
    string255 maxTeamDamageName;
    PClan winnersClan;
    PClanDeathLogEntry deathEntry;
    LongWord currentRank;
    if(SendHealthStatsOn)
    {
        msd = 0;
    }
    msdhh = NULL;
    msk = 0;
    mskhh = NULL;
    mskcnt = 0;
    maxTeamKills = 0;
    maxTurnSkips = 0;
    maxTeamDamage = 0;
    winnersClan = NULL;
    currentRank = 0;
    {t = 0;
     LongInt t__end__ = ((int)(TeamsCount) - 1);
     if (t <= t__end__) do {
                               {
                                   if(!(*TeamsArray[t]).ExtDriven && SendRankingStatsOn)
                                   {
                                       uio_SendStat(siTeamStats, umisc_GetTeamStatString(TeamsArray[t]));
                                   }
                                   {i = 0;
                                    LongInt i__end__ = cMaxHHIndex;
                                    if (i <= i__end__) do {
                                                              if((*TeamsArray[t]).Hedgehogs[i].stats.MaxStepDamageGiven > msd)
                                                              {
                                                                  msdhh = &((*TeamsArray[t]).Hedgehogs[i]);
                                                                  msd = (*TeamsArray[t]).Hedgehogs[i].stats.MaxStepDamageGiven;
                                                              }
                                                              if((*TeamsArray[t]).Hedgehogs[i].stats.MaxStepKills >= msk)
                                                              {
                                                                  if((*TeamsArray[t]).Hedgehogs[i].stats.MaxStepKills == msk)
                                                                  {
                                                                      ++mskcnt;
                                                                  }
                                                                  else
                                                                  {
                                                                      mskcnt = 1;
                                                                      mskhh = &((*TeamsArray[t]).Hedgehogs[i]);
                                                                      msk = (*TeamsArray[t]).Hedgehogs[i].stats.MaxStepKills;
                                                                  }
                                                              }
                                                          } while(i++ != i__end__);}
                                   if((*TeamsArray[t]).Clan->ClanHealth > 0)
                                   {
                                       winnersClan = (*TeamsArray[t]).Clan;
                                       if(SendRankingStatsOn)
                                       {
                                           currentRank = 1;
                                           uio_SendStat(siTeamRank, __str2);
                                           uio_SendStat(siPlayerKills, _strconcat(_strappend(_strconcat(_strappend(uutils_IntToStr((*TeamsArray[t]).Clan->Color), 0x20), uutils_IntToStr((*TeamsArray[t]).stats.Kills)), 0x20), (*TeamsArray[t]).TeamName));
                                       }
                                   }
                                   if((*TeamsArray[t]).stats.TeamKills > maxTeamKills)
                                   {
                                       maxTeamKills = (*TeamsArray[t]).stats.TeamKills;
                                       maxTeamKillsName = (*TeamsArray[t]).TeamName;
                                   }
                                   if((*TeamsArray[t]).stats.TurnSkips > maxTurnSkips)
                                   {
                                       maxTurnSkips = (*TeamsArray[t]).stats.TurnSkips;
                                       maxTurnSkipsName = (*TeamsArray[t]).TeamName;
                                   }
                                   if((*TeamsArray[t]).stats.TeamDamage > maxTeamDamage)
                                   {
                                       maxTeamDamage = (*TeamsArray[t]).stats.TeamDamage;
                                       maxTeamDamageName = (*TeamsArray[t]).TeamName;
                                   }
                               }
                           } while(t++ != t__end__);}
    ++currentRank;
    deathEntry = ClanDeathLog;
    i = 0;
    if(SendRankingStatsOn)
    {
        while(deathEntry != NULL)
        {
            {c = 0;
             LongInt c__end__ = ((int)(deathEntry->KilledClansCount) - 1);
             if (c <= c__end__) do {
                                       if(((*deathEntry->KilledClans[c]).ClanHealth == 0) && !(*deathEntry->KilledClans[c]).StatsHandled)
                                       {
                                           {t = 0;
                                            LongInt t__end__ = ((int)(TeamsCount) - 1);
                                            if (t <= t__end__) do {
                                                                      if((*TeamsArray[t]->Clan).ClanIndex == (*deathEntry->KilledClans[c]).ClanIndex)
                                                                      {
                                                                          uio_SendStat(siTeamRank, uutils_IntToStr(currentRank));
                                                                          uio_SendStat(siPlayerKills, _strconcat(_strappend(_strconcat(_strappend(uutils_IntToStr((*deathEntry->KilledClans[c]).Color), 0x20), uutils_IntToStr(TeamsArray[t]->stats.Kills)), 0x20), TeamsArray[t]->TeamName));
                                                                      }
                                                                  } while(t++ != t__end__);}
                                           (*deathEntry->KilledClans[c]).StatsHandled = true;
                                           ++i;
                                       }
                                   } while(c++ != c__end__);}
            if(i > 0)
            {
                currentRank += i;
            }
            i = 0;
            deathEntry = deathEntry->NextEntry;
        }
    }
    if(SendAchievementsStatsOn)
    {
        if(msdhh != NULL)
        {
            uio_SendStat(siMaxStepDamage, _strappend(_strconcat(_strconcat(_strconcat(_strappend(uutils_IntToStr(msd), 0x20), msdhh->Name), __str3), (*msdhh->Team).TeamName), 0x29));
        }
        if(mskcnt == 1)
        {
            uio_SendStat(siMaxStepKills, _strappend(_strconcat(_strconcat(_strconcat(_strappend(uutils_IntToStr(msk), 0x20), mskhh->Name), __str3), (*mskhh->Team).TeamName), 0x29));
        }
        if(maxTeamKills > 1)
        {
            uio_SendStat(siMaxTeamKills, _strconcat(_strappend(uutils_IntToStr(maxTeamKills), 0x20), maxTeamKillsName));
        }
        if(maxTurnSkips > 2)
        {
            uio_SendStat(siMaxTurnSkips, _strconcat(_strappend(uutils_IntToStr(maxTurnSkips), 0x20), maxTurnSkipsName));
        }
        if(maxTeamDamage > 30)
        {
            uio_SendStat(siMaxTeamDamage, _strconcat(_strappend(uutils_IntToStr(maxTeamDamage), 0x20), maxTeamDamageName));
        }
        if(KilledHHs > 0)
        {
            uio_SendStat(siKilledHHs, uutils_IntToStr(KilledHHs));
        }
    }
    if(winnersClan != NULL)
    {
        uscript_ScriptCall_2(__str4, winnersClan->ClanIndex);
        uconsole_WriteLnToConsole(__str5);
        uconsole_WriteLnToConsole(uutils_IntToStr(winnersClan->TeamsNumber));
        {t = 0;
         LongInt t__end__ = winnersClan->TeamsNumber - 1;
         if (t <= t__end__) do {
                                   uconsole_WriteLnToConsole((*winnersClan->Teams[t]).TeamName);
                               } while(t++ != t__end__);}
    }
    else
    {
        uscript_ScriptCall_2(__str4, -1);
        uconsole_WriteLnToConsole(__str6);
    }
    uscript_ScriptCall_1(__str7);
};
void ustats_declareAchievement(string255 id,string255 teamname,string255 location,LongInt value)
{
    if(((fpcrtl_Length(id) == 0) || (fpcrtl_Length(teamname) == 0)) || (fpcrtl_Length(location) == 0))
    {
        return;
    }
    uconsole_WriteLnToConsole(__str8);
    uconsole_WriteLnToConsole(id);
    uconsole_WriteLnToConsole(teamname);
    uconsole_WriteLnToConsole(location);
    uconsole_WriteLnToConsole(uutils_IntToStr(value));
};
void ustats_startGhostPoints(LongInt n)
{
    uconsole_WriteLnToConsole(__str9);
    uconsole_WriteLnToConsole(uutils_IntToStr(n));
};
void ustats_dumpPoint(LongInt x,LongInt y)
{
    uconsole_WriteLnToConsole(uutils_IntToStr(x));
    uconsole_WriteLnToConsole(uutils_IntToStr(y));
};
void ustats_initModule()
{
    DamageClan = 0;
    DamageTeam = 0;
    DamageTotal = 0;
    DamageTurn = 0;
    PoisonClan = 0;
    PoisonTeam = 0;
    PoisonTurn = 0;
    KillsClan = 0;
    KillsTeam = 0;
    KillsSD = 0;
    Kills = 0;
    KillsTotal = 0;
    HitTargets = 0;
    AmmoUsedCount = 0;
    AmmoDamagingUsed = false;
    FirstBlood = false;
    StepFirstBlood = false;
    LeaveMeAlone = false;
    SkippedTurns = 0;
    isTurnSkipped = false;
    vpHurtSameClan = NULL;
    vpHurtEnemy = NULL;
    TotalRoundsPre = -1;
    TotalRoundsReal = -1;
    FinishedTurnsTotal = -1;
    ClanDeathLog = NULL;
};
void ustats_freeModule()
{
};
