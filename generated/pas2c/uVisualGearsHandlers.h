#pragma once

#include "pas2c.h"

#include "uTypes.h"
#include "uGears.h"
typedef utypes_TVGearStepProcedure doStepVGHandlers_tt[34];
extern doStepVGHandlers_tt doStepVGHandlers;
void uvisualgearshandlers_doStepFlake(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepBeeTrace(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepCloud(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepExpl(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepNote(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepLineTrail(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepEgg(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepFire(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepShell(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepSmallDamageTag(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepBubble(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepSteam(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepAmmo(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepSmoke(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepDust(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepSplash(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepDroplet(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepSmokeRing(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepFeather(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepTeamHealthSorterWork(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepTeamHealthSorter(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepSpeechBubbleWork(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepSpeechBubble(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepHealthTagWork(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepHealthTagWorkUnderWater(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepHealthTag(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepSmokeTrace(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepExplosionWork(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepExplosion(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepBigExplosionWork(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepBigExplosion(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepChunk(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepBulletHit(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepCircle(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepSmoothWindBar(PVisualGear Gear,LongWord Steps);
void uvisualgearshandlers_doStepStraightShot(PVisualGear Gear,LongWord Steps);
boolean uvisualgearshandlers_isSorterActive();
void uvisualgearshandlers_initModule();

