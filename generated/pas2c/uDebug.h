#pragma once

#include "pas2c.h"

void udebug_OutError(string255 Msg,boolean isFatalError);
boolean udebug_checkFails(boolean Assert,string255 Msg,boolean isFatal);
boolean udebug_SDLCheck(boolean Assert,string255 Msg,boolean isFatal);
extern boolean allOK;

