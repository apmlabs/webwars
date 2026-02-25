#pragma once

#include "pas2c.h"

#include "SDLh.h"
void ulandtexture_initModule();
void ulandtexture_freeModule();
void ulandtexture_UpdateLandTexture(LongInt X,LongInt Width,LongInt Y,LongInt Height,boolean landAdded);
void ulandtexture_DrawLand(LongInt dX,LongInt dY);
void ulandtexture_ResetLand();
void ulandtexture_SetLandTexture();

