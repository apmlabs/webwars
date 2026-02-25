#pragma once

#include "pas2c.h"

#include "uConsts.h"
#include "uInputHandler.h"
#include "uRandom.h"
#include "uFloat.h"
#include "uStats.h"
#include "uCollisions.h"
#include "uSound.h"
#include "uStore.h"
#include "uTypes.h"
#include "uScript.h"
void uteams_initModule();
void uteams_freeModule();
PTeam uteams_AddTeam(LongWord TeamColor);
PTeam uteams_SetMissionTeam();
void uteams_SwitchHedgehog();
void uteams_AfterSwitchHedgehog();
void uteams_InitTeams();
LongWord uteams_TeamSize(PTeam p);
void uteams_RecountTeamHealth(PTeam team);
void uteams_RecountAllTeamsHealth();
void uteams_RestoreHog(PHedgehog HH);
void uteams_RestoreTeamsFromSave();
boolean uteams_CheckForWin();
void uteams_TeamGoneEffect(TTeam (*Team));
void uteams_SwitchCurrentHedgehog(PHedgehog newHog);
extern LongInt MaxTeamHealth;

