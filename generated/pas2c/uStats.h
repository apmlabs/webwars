#pragma once

#include "pas2c.h"

#include "uConsts.h"
#include "uTypes.h"
extern LongInt TotalRoundsPre;
extern LongInt TotalRoundsReal;
extern LongInt FinishedTurnsTotal;
extern boolean SendGameResultOn;
extern boolean SendRankingStatsOn;
extern boolean SendAchievementsStatsOn;
extern boolean SendHealthStatsOn;
extern PClanDeathLogEntry ClanDeathLog;
void ustats_initModule();
void ustats_freeModule();
void ustats_AmmoUsed(TAmmoType am);
void ustats_HedgehogPoisoned(PGear Gear,PHedgehog Attacker);
void ustats_HedgehogSacrificed(PHedgehog Hedgehog);
void ustats_HedgehogDamaged(PGear Gear,PHedgehog Attacker,LongWord Damage,boolean killed);
void ustats_TargetHit();
void ustats_Skipped();
boolean ustats_getIsTurnSkipped();
void ustats_TurnStats();
void ustats_TurnReaction();
void ustats_TurnStatsReset();
void ustats_SendStats();
void ustats_hedgehogFlight(PGear Gear,LongWord time);
void ustats_declareAchievement(string255 id,string255 teamname,string255 location,LongInt value);
void ustats_startGhostPoints(LongInt n);
void ustats_dumpPoint(LongInt x,LongInt y);

