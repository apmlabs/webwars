#pragma once

#include "pas2c.h"

#include "uConsts.h"
#include "GL.h"
#include "uTypes.h"
void uvisualgears_initModule();
void uvisualgears_freeModule();
void uvisualgears_ProcessVisualGears(LongWord Steps);
void uvisualgears_DrawVisualGears(LongWord Layer,boolean worldIsShifted);
void uvisualgears_AddClouds();
void uvisualgears_AddFlakes();
void uvisualgears_AddDamageTag(LongWord X,LongWord Y,LongWord Damage,LongWord Color);
void uvisualgears_ChangeToSDClouds();
void uvisualgears_ChangeToSDFlakes();
void uvisualgears_KickFlakes(LongInt Radius,LongInt X,LongInt Y);

