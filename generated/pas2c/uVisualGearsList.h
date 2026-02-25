#pragma once

#include "pas2c.h"

#include "uTypes.h"
PVisualGear uvisualgearslist_AddVisualGear_3(LongInt X,LongInt Y,TVisualGearType Kind);
PVisualGear uvisualgearslist_AddVisualGear_4(LongInt X,LongInt Y,TVisualGearType Kind,LongWord State);
PVisualGear uvisualgearslist_AddVisualGear_5(LongInt X,LongInt Y,TVisualGearType Kind,LongWord State,boolean Critical);
PVisualGear uvisualgearslist_AddVisualGear_6(LongInt X,LongInt Y,TVisualGearType Kind,LongWord State,boolean Critical,LongInt Layer);
void uvisualgearslist_DeleteVisualGear(PVisualGear Gear);
PVisualGear uvisualgearslist_VisualGearByUID(LongWord uid);
enum{cExplFrameTicks = 110};
extern LongWord VGCounter;
typedef PVisualGear VisualGearLayersStart_tt[(6 + 1)];
extern VisualGearLayersStart_tt VisualGearLayersStart;
typedef PVisualGear VisualGearLayersEnd_tt[(6 + 1)];
extern VisualGearLayersEnd_tt VisualGearLayersEnd;

