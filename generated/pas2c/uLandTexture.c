#include "fpcrtl.h"

#include "uLandTexture.h"
#include "uConsts.h"
#include "GL.h"
#include "uTypes.h"
#include "uVariables.h"
#include "uTextures.h"
#include "uDebug.h"
#include "uRender.h"
#include "uUtils.h"
#include "uLandUtils.h"
static const string255 __str3 = STRINIT("UpdateLandTexture: wrong Height parameter");
static const string255 __str2 = STRINIT("UpdateLandTexture: wrong Y parameter");
static const string255 __str1 = STRINIT("UpdateLandTexture: wrong Width parameter");
static const string255 __str0 = STRINIT("UpdateLandTexture: wrong X parameter");
enum{TEXSIZE = 128};
static real BLURRYLANDOVERLAP = ((1 /(float) TEXSIZE) /(float) 2.0);
typedef struct __TLandRecord {
            boolean shouldUpdate;
            boolean landAdded;
            PTexture tex;
        } TLandRecord;
typedef struct __TLandRecord * (*LandTextures_tt);
static fpcrtl_dimension_t LandTextures_dimension_info ={.dim = 0, .a = {0, 0, 0, 0}};
static LandTextures_tt LandTextures = NULL;
typedef LongWord tmpPixels_tt[((TEXSIZE - 1) + 1)][((TEXSIZE - 1) + 1)];
static tmpPixels_tt tmpPixels;
static LongWord LANDTEXARW;
static LongWord LANDTEXARH;
pointer ulandtexture_Pixels(LongWord x,LongWord y)
{
    pointer pixels_result;
    LongWord ty;
    {ty = 0;
     LongWord ty__end__ = TEXSIZE - 1;
     if (ty <= ty__end__) do {
                                 fpcrtl_Move((*ulandutils_LandPixelRow((y * TEXSIZE) + ty))[x * TEXSIZE], tmpPixels[ty][0], sizeof(LongWord) * TEXSIZE);
                             } while(ty++ != ty__end__);}
    pixels_result = &(tmpPixels);
    return pixels_result;
};
pointer ulandtexture_Pixels2(LongWord x,LongWord y)
{
    pointer pixels2_result;
    LongWord tx;
    LongWord ty;
    {ty = 0;
     LongWord ty__end__ = TEXSIZE - 1;
     if (ty <= ty__end__) do {
                                 {tx = 0;
                                  LongWord tx__end__ = TEXSIZE - 1;
                                  if (tx <= tx__end__) do {
                                                              tmpPixels[ty][tx] = ulandutils_LandGet((y * TEXSIZE) + ty, (x * TEXSIZE) + tx) | AMask;
                                                          } while(tx++ != tx__end__);}
                             } while(ty++ != ty__end__);}
    pixels2_result = &(tmpPixels);
    return pixels2_result;
};
void ulandtexture_UpdateLandTexture(LongInt X,LongInt Width,LongInt Y,LongInt Height,boolean landAdded)
{
    LongWord tx;
    LongWord ty;
    LongInt tSize;
    if(cOnlyStats)
    {
        return;
    }
    if((Width <= 0) || (Height <= 0))
    {
        return;
    }
    udebug_checkFails((X >= 0) && (X < LAND_WIDTH), __str0, true);
    udebug_checkFails((X + Width) <= LAND_WIDTH, __str1, true);
    udebug_checkFails((Y >= 0) && (Y < LAND_HEIGHT), __str2, true);
    udebug_checkFails((Y + Height) <= LAND_HEIGHT, __str3, true);
    if(!allOK)
    {
        return;
    }
    tSize = TEXSIZE;
    if((cReducedQuality & rqBlurryLand) != 0)
    {
        tSize = tSize * 2;
    }
    {ty = Y / tSize;
     LongWord ty__end__ = ((Y + Height) - 1) / tSize;
     if (ty <= ty__end__) do {
                                 {tx = X / tSize;
                                  LongWord tx__end__ = ((X + Width) - 1) / tSize;
                                  if (tx <= tx__end__) do {
                                                              if(!LandTextures[tx][ty].shouldUpdate)
                                                              {
                                                                  LandTextures[tx][ty].shouldUpdate = true;
                                                                  ++dirtyLandTexCount;
                                                              }
                                                              LandTextures[tx][ty].landAdded = landAdded;
                                                          } while(tx++ != tx__end__);}
                             } while(ty++ != ty__end__);}
};
void ulandtexture_RealLandTexUpdate(LongInt x1,LongInt x2,LongInt y1,LongInt y2)
{
    LongWord x;
    LongWord y;
    LongWord ty;
    LongWord tx;
    LongWord lx;
    LongWord ly;
    boolean isEmpty;
    if(cOnlyStats)
    {
        return;
    }
    {x = x1;
     LongWord x__end__ = x2;
     if (x <= x__end__) do {
                               {y = y1;
                                LongWord y__end__ = y2;
                                if (y <= y__end__) do {
                                                          {
                                                              if(LandTextures[x][y].shouldUpdate)
                                                              {
                                                                  LandTextures[x][y].shouldUpdate = false;
                                                                  --dirtyLandTexCount;
                                                                  isEmpty = !LandTextures[x][y].landAdded;
                                                                  LandTextures[x][y].landAdded = false;
                                                                  ty = 0;
                                                                  tx = 1;
                                                                  ly = y * TEXSIZE;
                                                                  lx = x * TEXSIZE;
                                                                  while(isEmpty && (ty < TEXSIZE))
                                                                  {
                                                                      isEmpty = (ulandutils_LandPixelGet(ly + ty, lx) & AMask) == 0;
                                                                      if(isEmpty)
                                                                      {
                                                                          isEmpty = (ulandutils_LandPixelGet(ly + ty, ((int)(lx + TEXSIZE) - 1)) & AMask) == 0;
                                                                      }
                                                                      ++ty;
                                                                  }
                                                                  while(isEmpty && (tx < (TEXSIZE - 1)))
                                                                  {
                                                                      isEmpty = (ulandutils_LandPixelGet(ly, lx + tx) & AMask) == 0;
                                                                      if(isEmpty)
                                                                      {
                                                                          isEmpty = (ulandutils_LandPixelGet(((int)(ly + TEXSIZE) - 1), lx + tx) & AMask) == 0;
                                                                      }
                                                                      ++tx;
                                                                  }
                                                                  ty = 2;
                                                                  while(isEmpty && (ty < (TEXSIZE - 1)))
                                                                  {
                                                                      tx = 2;
                                                                      while(isEmpty && (tx < (TEXSIZE - 1)))
                                                                      {
                                                                          isEmpty = (ulandutils_LandPixelGet(ly + ty, lx + tx) & AMask) == 0;
                                                                          tx += 2;
                                                                      }
                                                                      ty += 2;
                                                                  }
                                                                  ty = 1;
                                                                  while(isEmpty && (ty < (TEXSIZE - 1)))
                                                                  {
                                                                      tx = 1;
                                                                      while(isEmpty && (tx < (TEXSIZE - 1)))
                                                                      {
                                                                          isEmpty = (ulandutils_LandPixelGet(ly + ty, lx + tx) & AMask) == 0;
                                                                          tx += 2;
                                                                      }
                                                                      ty += 2;
                                                                  }
                                                                  if(!isEmpty)
                                                                  {
                                                                      if(LandTextures[x][y].tex == NULL)
                                                                      {
                                                                          LandTextures[x][y].tex = utextures_NewTexture(TEXSIZE, TEXSIZE, ulandtexture_Pixels(x, y));
                                                                      }
                                                                      glBindTexture(GL_TEXTURE_2D, LandTextures[x][y].tex->id);
                                                                      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEXSIZE, TEXSIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, ulandtexture_Pixels(x, y));
                                                                  }
                                                                  else
                                                                  {
                                                                      if(LandTextures[x][y].tex != NULL)
                                                                      {
                                                                          utextures_FreeAndNilTexture(&(LandTextures[x][y].tex));
                                                                      }
                                                                  }
                                                                  if(dirtyLandTexCount < 1)
                                                                  {
                                                                      return;
                                                                  }
                                                              }
                                                          }
                                                      } while(y++ != y__end__);}
                           } while(x++ != x__end__);}
};
void ulandtexture_DrawLand(LongInt dX,LongInt dY)
{
    LongInt x;
    LongInt y;
    LongInt tX;
    LongInt ty;
    LongInt tSize;
    LongInt fx;
    LongInt lx;
    LongInt fy;
    LongInt ly;
    GLfloat tScale;
    boolean overlap;
    if((cReducedQuality & rqBlurryLand) != 0)
    {
        tSize = TEXSIZE * 2;
        tScale = 2.0;
        overlap = (cReducedQuality & rqClampLess) != 0;
    }
    else
    {
        tSize = TEXSIZE;
        tScale = 1.0;
        overlap = false;
    }
    tX = ViewLeftX - dX;
    fx = tX / tSize;
    if(tX < 0)
    {
        --fx;
    }
    fx = uutils_Max(0, fx);
    tX = ViewRightX - dX;
    lx = tX / tSize;
    if(tX < 0)
    {
        --lx;
    }
    lx = uutils_Min(LANDTEXARW - 1, lx);
    if(fx > lx)
    {
        return;
    }
    ty = ViewTopY - dY;
    fy = ty / tSize;
    if(ty < 0)
    {
        --fy;
    }
    fy = uutils_Max(0, fy);
    ty = ViewBottomY - dY;
    ly = ty / tSize;
    if(ty < 0)
    {
        --ly;
    }
    ly = uutils_Min(LANDTEXARH - 1, ly);
    if(fy > ly)
    {
        return;
    }
    if(dirtyLandTexCount > 0)
    {
        ulandtexture_RealLandTexUpdate(fx, lx, fy, ly);
    }
    tX = dX + (tSize * fx);
    {x = fx;
     LongInt x__end__ = lx;
     if (x <= x__end__) do {
                               {y = fy;
                                LongInt y__end__ = ly;
                                if (y <= y__end__) do {
                                                          {
                                                              if(LandTextures[x][y].tex != NULL)
                                                              {
                                                                  ty = dY + (y * tSize);
                                                                  if(overlap)
                                                                  {
                                                                      urender_DrawTexture2(tX, ty, LandTextures[x][y].tex, tScale, BLURRYLANDOVERLAP);
                                                                  }
                                                                  else
                                                                  {
                                                                      urender_DrawTexture_4(tX, ty, LandTextures[x][y].tex, tScale);
                                                                  }
                                                              }
                                                          }
                                                      } while(y++ != y__end__);}
                               tX += tSize;
                           } while(x++ != x__end__);}
};
void ulandtexture_SetLandTexture()
{
    if((cReducedQuality & rqBlurryLand) == 0)
    {
        LANDTEXARW = LAND_WIDTH / TEXSIZE;
        LANDTEXARH = LAND_HEIGHT / TEXSIZE;
    }
    else
    {
        LANDTEXARW = (LAND_WIDTH / TEXSIZE) / 2;
        LANDTEXARH = (LAND_HEIGHT / TEXSIZE) / 2;
    }
    fpcrtl_SetLength(LandTextures, LANDTEXARW, LANDTEXARH);
};
void ulandtexture_initModule()
{
};
void ulandtexture_ResetLand()
{
    LongInt x;
    LongInt y;
    {x = 0;
     LongInt x__end__ = LANDTEXARW - 1;
     if (x <= x__end__) do {
                               {y = 0;
                                LongInt y__end__ = LANDTEXARH - 1;
                                if (y <= y__end__) do {
                                                          {
                                                              utextures_FreeAndNilTexture(&(LandTextures[x][y].tex));
                                                          }
                                                      } while(y++ != y__end__);}
                           } while(x++ != x__end__);}
};
void ulandtexture_freeModule()
{
    ulandtexture_ResetLand();
    if(LandBackSurface != NULL)
    {
        SDL_FreeSurface(LandBackSurface);
    }
    LandBackSurface = NULL;
    fpcrtl_SetLength(LandTextures, 0, 0);
};
