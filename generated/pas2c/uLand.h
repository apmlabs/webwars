#pragma once

#include "pas2c.h"

#include "SDLh.h"
#include "uConsts.h"
#include "uTypes.h"
#include "uAILandMarks.h"
void uland_initModule();
void uland_freeModule();
void uland_DrawBottomBorder();
void uland_GenMap();
void uland_GenPreview(TPreview (*Preview));
void uland_GenPreviewAlpha(TPreviewAlpha (*Preview));

