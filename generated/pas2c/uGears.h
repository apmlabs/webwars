#pragma once

#include "pas2c.h"

#include "uConsts.h"
#include "uFloat.h"
#include "uTypes.h"
#include "uChat.h"
#include "uCollisions.h"
void ugears_initModule();
void ugears_freeModule();
PGear ugears_SpawnCustomCrateAt(LongInt x,LongInt y,TCrateType crate,LongWord content,LongWord cnt);
PGear ugears_SpawnFakeCrateAt(LongInt x,LongInt y,TCrateType crate,boolean explode,boolean poison);
void ugears_ProcessGears();
void ugears_EndTurnCleanup();
void ugears_DrawGears();
void ugears_DrawGearsGui();
void ugears_DrawFinger();
void ugears_FreeGearsList();
void ugears_AddMiscGears();
void ugears_AssignHHCoords();
void ugears_RandomizeHHAnim();
void ugears_StartSuddenDeath();
PGear ugears_GearByUID(LongWord uid);
boolean ugears_IsClockRunning();

