#pragma once

#include "pas2c.h"

#include "SDLh.h"
#include "uConsts.h"
#include "GL.h"
#include "uTypes.h"
void umisc_initModule();
void umisc_freeModule();
PSDL_Surface umisc_doSurfaceConversion(PSDL_Surface tmpsurf);
boolean umisc_MakeScreenshot(string255 filename,LongInt k,LongWord dump);
string255 umisc_GetTeamStatString(PTeam p);
TSDL_Rect umisc_SDL_RectMake(LongInt x,LongInt y,LongInt width,LongInt height);

