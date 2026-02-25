#pragma once

#include "pas2c.h"

#include "SDLh.h"
#include "uTypes.h"
#include "GL.h"
void urender_initModule();
void urender_freeModule();
void urender_DrawSprite_4(TSprite Sprite,LongInt X,LongInt Y,LongInt Frame);
void urender_DrawSprite_5(TSprite Sprite,LongInt X,LongInt Y,LongInt FrameX,LongInt FrameY);
void urender_DrawSpriteFromRect(TSprite Sprite,TSDL_Rect r,LongInt X,LongInt Y,LongInt Height,LongInt Position);
void urender_DrawSpriteClipped(TSprite Sprite,LongInt X,LongInt Y,LongInt TopY,LongInt RightX,LongInt BottomY,LongInt LeftX);
void urender_DrawSpriteRotated(TSprite Sprite,LongInt X,LongInt Y,LongInt Dir,real Angle);
void urender_DrawSpriteRotatedF(TSprite Sprite,LongInt X,LongInt Y,LongInt Frame,LongInt Dir,real Angle);
void urender_DrawSpriteRotatedFReal(TSprite Sprite,real X,real Y,LongInt Frame,LongInt Dir,real Angle);
void urender_DrawSpritePivotedF(TSprite Sprite,LongInt X,LongInt Y,LongInt Frame,LongInt Dir,LongInt PivotX,LongInt PivotY,real Angle);
void urender_DrawTexture_3(LongInt X,LongInt Y,PTexture Texture);
void urender_DrawTexture_4(LongInt X,LongInt Y,PTexture Texture,GLfloat Scale);
void urender_DrawTexture2(LongInt X,LongInt Y,PTexture Texture,GLfloat Scale,GLfloat Overlap);
void urender_DrawTextureFromRect_4(LongInt X,LongInt Y,PSDL_Rect r,PTexture SourceTexture);
void urender_DrawTextureFromRect_6(LongInt X,LongInt Y,LongInt W,LongInt H,PSDL_Rect r,PTexture SourceTexture);
void urender_DrawTextureFromRectDir(LongInt X,LongInt Y,LongInt W,LongInt H,PSDL_Rect r,PTexture SourceTexture,LongInt Dir);
void urender_DrawTextureCentered(LongInt X,LongInt Top,PTexture Source);
void urender_DrawTextureF(PTexture Texture,GLfloat Scale,LongInt X,LongInt Y,LongInt Frame,LongInt Dir,LongInt w,LongInt h);
void urender_DrawTextureRotated(PTexture Texture,LongInt hw,LongInt hh,LongInt X,LongInt Y,LongInt Dir,real Angle);
void urender_DrawTextureRotatedF(PTexture Texture,GLfloat Scale,GLfloat OffsetX,GLfloat OffsetY,LongInt X,LongInt Y,LongInt Frame,LongInt Dir,LongInt w,LongInt h,real Angle);
void urender_DrawCircle_4(LongInt X,LongInt Y,LongInt Radius,LongInt Width);
void urender_DrawCircle_8(LongInt X,LongInt Y,LongInt Radius,LongInt Width,Byte r,Byte g,Byte b,Byte a);
void urender_DrawCircle_5(LongInt X,LongInt Y,LongInt Radius,LongInt Width,LongWord color);
void urender_DrawCircleFilled(LongInt X,LongInt Y,LongInt Radius,Byte r,Byte g,Byte b,Byte a);
void urender_DrawLine_6(single X0,single Y0,single X1,single Y1,single Width,LongWord color);
void urender_DrawLine_9(single X0,single Y0,single X1,single Y1,single Width,Byte r,Byte g,Byte b,Byte a);
void urender_DrawLineWrapped_8(single X0,single Y0,single X1,single Y1,single Width,boolean goesLeft,LongWord Wraps,LongWord color);
void urender_DrawLineWrapped_11(single X0,single Y0,single X1,single Y1,single Width,boolean goesLeft,LongWord Wraps,Byte r,Byte g,Byte b,Byte a);
void urender_DrawLineOnScreen(single X0,single Y0,single X1,single Y1,single Width,Byte r,Byte g,Byte b,Byte a);
void urender_DrawRect(TSDL_Rect rect,Byte r,Byte g,Byte b,Byte a,boolean Fill);
void urender_DrawHedgehog(LongInt X,LongInt Y,LongInt Dir,LongWord Pos,LongWord Step,real Angle);
void urender_DrawScreenWidget(POnScreenWidget widget);
void urender_DrawWater(Byte Alpha,LongInt OffsetY,LongInt OffsetX);
void urender_DrawWaves(LongInt Dir,LongInt dX,LongInt dY,LongInt oX,Byte tnt);
void urender_RenderClear();
void urender_RenderSetClearColor(real r,real g,real b,real a);
void urender_Tint_4(Byte r,Byte g,Byte b,Byte a);
void urender_Tint_1(LongWord c);
void urender_untint();
void urender_setTintAdd(boolean enable);
void urender_FinishRender();
void urender_FlushBatch();
boolean urender_isAreaOffscreen(LongInt X,LongInt Y,LongInt Width,LongInt Height);
boolean urender_isCircleOffscreen(LongInt X,LongInt Y,LongInt RadiusSquared);
LongInt urender_isDxAreaOffscreen(LongInt X,LongInt Width);
LongInt urender_isDyAreaOffscreen(LongInt Y,LongInt Height);
void urender_SetScale(GLfloat f);
void urender_UpdateViewLimits();
void urender_RendererSetup();
void urender_RendererCleanup();
void urender_ChangeDepth(TRenderMode rm,GLfloat d);
void urender_ResetDepth(TRenderMode rm);
void urender_EnableTexture(boolean enable);
void urender_SetTexCoordPointer(pointer p,Integer n);
void urender_SetVertexPointer(pointer p,Integer n);
void urender_SetColorPointer(pointer p,Integer n);
void urender_UpdateModelviewProjection();
void urender_openglPushMatrix();
void urender_openglPopMatrix();
void urender_openglTranslatef(GLfloat X,GLfloat Y,GLfloat Z);

