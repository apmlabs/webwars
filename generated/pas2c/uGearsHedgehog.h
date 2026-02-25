#pragma once

#include "pas2c.h"

#include "uTypes.h"
#include "uGearsHandlersMess.h"
void ugearshedgehog_doStepHedgehog(PGear Gear);
void ugearshedgehog_AfterAttack();
void ugearshedgehog_HedgehogStep(PGear Gear);
void ugearshedgehog_doStepHedgehogMoving(PGear Gear);
void ugearshedgehog_HedgehogChAngle(PGear HHGear);
void ugearshedgehog_PickUp(PGear HH,PGear Gear);
void ugearshedgehog_AddPickup(THedgehog HH,TAmmoType ammo,LongWord cnt,LongWord X,LongWord Y);
void ugearshedgehog_CheckIce(PGear Gear);
void ugearshedgehog_PlayTaunt(LongWord taunt);
LongWord ugearshedgehog_HHGetTimer(PGear Gear);
LongWord ugearshedgehog_HHGetTimerMsg(PGear Gear);
LongWord ugearshedgehog_HHGetBounciness(PGear Gear);
LongWord ugearshedgehog_HHGetBouncinessMsg(PGear Gear);

