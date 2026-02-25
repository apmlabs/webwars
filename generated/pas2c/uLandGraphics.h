#pragma once

#include "pas2c.h"

#include "uFloat.h"
#include "uConsts.h"
#include "uTypes.h"
#include "Math.h"
#include "uRenderUtils.h"
typedef enum {nullPixel = 0x0,
              backgroundPixel = 0x1,
              ebcPixel = 0x2,
              icePixel = 0x3,
              addNotHHObj = 0x4,
              removeNotHHObj = 0x5,
              addHH = 0x6,
              removeHH = 0x7,
              setCurrentHog = 0x8,
              removeCurrentHog = 0x9} fillType;
typedef struct __TRangeArray {
            LongInt Left;
            LongInt Right;
        } TRangeArray[(31 + 1)];
typedef TRangeArray * PRangeArray;
typedef void(*ulandgraphics_TLandCircleProcedure)(LongInt landX,LongInt landY,LongInt pixelX,LongInt pixelY);
LongWord ulandgraphics_addBgColor(LongWord OldColor,LongWord NewColor);
boolean ulandgraphics_SweepDirty();
boolean ulandgraphics_Despeckle(LongInt X,LongInt Y);
void ulandgraphics_Smooth(LongInt X,LongInt Y);
boolean ulandgraphics_CheckLandValue(LongInt X,LongInt Y,Word LandFlag);
LongWord ulandgraphics_DrawExplosion(LongInt X,LongInt Y,LongInt Radius);
void ulandgraphics_DrawHLinesExplosions(PRangeArray ar,LongInt Radius,LongInt y,LongInt dY,Byte Count);
void ulandgraphics_DrawTunnel(hwFloat X,hwFloat Y,hwFloat dX,hwFloat dY,LongInt ticks,LongInt HalfWidth);
LongWord ulandgraphics_FillRoundInLand(LongInt X,LongInt Y,LongInt Radius,LongWord Value);
LongWord ulandgraphics_FillRoundInLandFT(LongInt X,LongInt Y,LongInt Radius,fillType fill);
void ulandgraphics_ChangeRoundInLand(LongInt X,LongInt Y,LongInt Radius,boolean doSet,boolean isCurrent,boolean isHH);
LongWord ulandgraphics_LandBackPixel(LongInt x,LongInt y);
void ulandgraphics_DrawLine(LongInt X1,LongInt Y1,LongInt X2,LongInt Y2,LongWord Color);
LongWord ulandgraphics_DrawThickLine(LongInt X1,LongInt Y1,LongInt X2,LongInt Y2,LongInt radius,LongWord color);
void ulandgraphics_DumpLandToLog(LongInt x,LongInt y,LongInt r);
void ulandgraphics_DrawIceBreak(LongInt x,LongInt y,LongInt iceRadius,LongInt iceHeight);
boolean ulandgraphics_TryPlaceOnLandSimple(LongInt cpX,LongInt cpY,TSprite Obj,LongInt Frame,boolean doPlace,boolean indestructible);
boolean ulandgraphics_TryPlaceOnLand_6(LongInt cpX,LongInt cpY,TSprite Obj,LongInt Frame,boolean doPlace,Word LandFlags);
boolean ulandgraphics_ForcePlaceOnLand(LongInt cpX,LongInt cpY,TSprite Obj,LongInt Frame,Word LandFlags,LongWord Tint,boolean Behind,boolean flipHoriz,boolean flipVert);
boolean ulandgraphics_TryPlaceOnLand_12(LongInt cpX,LongInt cpY,TSprite Obj,LongInt Frame,boolean doPlace,boolean outOfMap,boolean force,boolean behind,boolean flipHoriz,boolean flipVert,Word LandFlags,LongWord Tint);
void ulandgraphics_EraseLandRectRaw(LongWord X,LongWord Y,LongWord width,LongWord height);
void ulandgraphics_EraseLand(LongInt cpX,LongInt cpY,TSprite Obj,LongInt Frame,Word LandFlags,boolean eraseOnLFMatch,boolean onlyEraseLF,boolean flipHoriz,boolean flipVert);
PTexture ulandgraphics_GetPlaceCollisionTex(LongInt cpX,LongInt cpY,TSprite Obj,LongInt Frame);

string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const fillType enumvar);