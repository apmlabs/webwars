#pragma once

#include "pas2c.h"

#include "SDLh.h"
#include "uTypes.h"
PTexture utextures_NewTexture(LongWord width,LongWord height,pointer buf);
void utextures_Surface2GrayScale(PSDL_Surface surf);
PTexture utextures_Surface2Tex(PSDL_Surface surf,boolean enableClamp);
void utextures_PrettifySurfaceAlpha(PSDL_Surface surf,PLongWordArray pixels);
void utextures_PrettifyAlpha2D(LongWord height,LongWord width);
void utextures_FreeAndNilTexture(PTexture (*tex));
void utextures_initModule();
void utextures_freeModule();

