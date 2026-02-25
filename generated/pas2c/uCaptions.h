#pragma once

#include "pas2c.h"

#include "uTypes.h"
void ucaptions_AddCaption(astring s,LongWord Color,TCapGroup Group);
void ucaptions_DrawCaptions();
void ucaptions_ReloadCaptions(boolean unload);
void ucaptions_initModule();
void ucaptions_freeModule();

