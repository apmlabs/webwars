#pragma once

#include "pas2c.h"

#include "SDLh.h"
#include "uGears.h"
#include "uConsts.h"
#include "uFloat.h"
#include "uRandom.h"
#include "uTypes.h"
#include "uRenderUtils.h"
void uworld_initModule();
void uworld_freeModule();
void uworld_InitWorld();
void uworld_ResetWorldTex();
void uworld_DrawWorld(LongInt Lag);
void uworld_DrawWorldStereo(LongInt Lag,TRenderMode RM);
void uworld_ShowMission_5(astring caption,astring subcaption,astring text,LongInt icon,LongInt time);
void uworld_ShowMission_6(astring caption,astring subcaption,astring text,LongInt icon,LongInt time,boolean forceDisplay);
void uworld_HideMission();
void uworld_SetAmmoTexts(TAmmoType ammoType,astring name,astring caption,astring description,boolean autoLabels);
void uworld_ShakeCamera(LongInt amount);
void uworld_InitCameraBorders();
void uworld_InitTouchInterface();
void uworld_SetUtilityWidgetState(TAmmoType ammoType);
void uworld_animateWidget(POnScreenWidget widget,boolean fade,boolean showWidget);
void uworld_MoveCamera();
void uworld_onFocusStateChanged();
void uworld_updateCursorVisibility();
void uworld_updateTouchWidgets(TAmmoType ammoType);

