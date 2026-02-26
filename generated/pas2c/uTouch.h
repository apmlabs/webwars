#pragma once

#include "pas2c.h"

#include "SysUtils.h"
#include "uUtils.h"
#include "uConsole.h"
#include "uVariables.h"
#include "SDLh.h"
#include "uFloat.h"
#include "uConsts.h"
#include "uCommands.h"
#include "GLUnit.h"
#include "uTypes.h"
#include "uCaptions.h"
#include "uWorld.h"
#include "uGearsHedgehog.h"
void utouch_initModule();
void utouch_freeModule();
void utouch_ProcessTouch();
void utouch_NewTurnBeginning();
void utouch_onTouchDown(single x,single y,Int64 pointerId);
void utouch_onTouchMotion(single x,single y,single dx,single dy,Int64 pointerId);
void utouch_onTouchUp(single x,single y,Int64 pointerId);
LongInt utouch_convertToCursorX(LongInt x);
LongInt utouch_convertToCursorY(LongInt y);
PTouch_Data utouch_addFinger(LongWord x,LongWord y,Int64 id);
PTouch_Data utouch_updateFinger(LongWord x,LongWord y,LongWord dx,LongWord dy,Int64 id);
void utouch_deleteFinger(Int64 id);
void utouch_onTouchClick(TTouch_Data finger);
void utouch_onTouchDoubleClick(TTouch_Data finger);
void utouch_onTouchLongClick(TTouch_Data finger);
PTouch_Data utouch_findFinger(Int64 id);
void utouch_aim(TTouch_Data finger);
boolean utouch_isOnCrosshair(TTouch_Data finger);
boolean utouch_isOnCurrentHog(TTouch_Data finger);
void utouch_convertToWorldCoord(LongInt (*x),LongInt (*y),TTouch_Data finger);
void utouch_convertToFingerCoord(LongInt (*x),LongInt (*y),LongInt oldX,LongInt oldY);
boolean utouch_fingerHasMoved(TTouch_Data finger);
LongInt utouch_calculateDelta(TTouch_Data finger1,TTouch_Data finger2);
PTouch_Data utouch_getSecondFinger(TTouch_Data finger);
boolean utouch_isOnRect_2(TSDL_Rect rect,TTouch_Data finger);
boolean utouch_isOnRect_5(LongInt x,LongInt y,LongInt w,LongInt h,TTouch_Data finger);
boolean utouch_isOnWidget(TOnScreenWidget widget,TTouch_Data finger);
void utouch_printFinger(TTouch_Data finger);

