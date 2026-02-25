#pragma once

#include "pas2c.h"

#include "uFloat.h"
#include "uTypes.h"
#include "SDLh.h"
void ugearslist_initializeGear(PGear gear,LongInt X,LongInt Y,TGearType Kind,LongWord State,hwFloat dX,hwFloat dY,LongWord Timer,LongWord newUid);
PGear ugearslist_AddGear_7(LongInt X,LongInt Y,TGearType Kind,LongWord State,hwFloat dX,hwFloat dY,LongWord Timer);
PGear ugearslist_AddGear_8(LongInt X,LongInt Y,TGearType Kind,LongWord State,hwFloat dX,hwFloat dY,LongWord Timer,LongWord newUid);
void ugearslist_DeleteGear(PGear Gear);
void ugearslist_InsertGearToList(PGear Gear);
void ugearslist_RemoveGearFromList(PGear Gear);
extern PGear curHandledGear;

