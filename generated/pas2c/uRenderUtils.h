#pragma once

#include "pas2c.h"

#include "SDLh.h"
#include "uTypes.h"
void urenderutils_flipSurface(PSDL_Surface Surface,boolean Vertical);
void urenderutils_copyRotatedSurface(PSDL_Surface src,PSDL_Surface dest);
void urenderutils_copyToXY(PSDL_Surface src,PSDL_Surface dest,LongInt destX,LongInt destY);
void urenderutils_copyToXYFromRect(PSDL_Surface src,PSDL_Surface dest,LongInt srcX,LongInt srcY,LongInt srcW,LongInt srcH,LongInt destX,LongInt destY);
LongInt urenderutils_GetSurfaceFrameCoordinateX(PSDL_Surface Surface,LongInt Frame,LongInt frameWidth,LongInt frameHeight);
LongInt urenderutils_GetSurfaceFrameCoordinateY(PSDL_Surface Surface,LongInt Frame,LongInt frameHeight);
void urenderutils_DrawSprite2Surf(TSprite sprite,PSDL_Surface dest,LongInt x,LongInt y);
void urenderutils_DrawSpriteFrame2Surf(TSprite sprite,PSDL_Surface dest,LongInt x,LongInt y,LongInt frame);
void urenderutils_DrawLine2Surf(PSDL_Surface dest,LongInt x0,LongInt y0,LongInt x1,LongInt y1,Byte r,Byte g,Byte b);
void urenderutils_DrawRoundRect(PSDL_Rect rect,LongWord BorderColor,LongWord FillColor,PSDL_Surface Surface,boolean Clear);
PTexture urenderutils_RenderStringTex(astring s,LongWord Color,THWFont font);
PTexture urenderutils_RenderStringTexLim(astring s,LongWord Color,THWFont font,LongWord maxLength);
PTexture urenderutils_RenderSpeechBubbleTex(astring s,LongWord SpeechType,THWFont font);
boolean urenderutils_IsTooDarkToRead(LongWord TextColor);

