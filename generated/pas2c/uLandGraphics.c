#include "fpcrtl.h"

#include "uLandGraphics.h"
#include "SDLh.h"
#include "uLandTexture.h"
#include "uTextures.h"
#include "uVariables.h"
#include "uUtils.h"
#include "uDebug.h"
#include "uScript.h"
#include "uLandUtils.h"
static const string255 __str10 = STRINIT("Land dump: ");
static const string255 __str9 = STRINIT("GetPlaceCollisionTex");
static const string255 __str8 = STRINIT("GetPlaceCollisionTex: fail to create surface");
static const string255 __str7 = STRINIT("SDL_LockSurface");
static const string255 __str6 = STRINIT("EraseLand");
static const string255 __str5 = STRINIT("onRubberPlacement");
static const string255 __str4 = STRINIT("onGirderPlacement");
static const string255 __str3 = STRINIT("onSpritePlacement");
static const string255 __str2 = STRINIT("It should be 32 bpp sprite");
static const string255 __str1 = STRINIT("TryPlaceOnLand");
static const string255 __str0 = STRINIT("Assert SpritesData[Obj].Surface failed");
void ulandgraphics_calculatePixelsCoordinates(LongInt landX,LongInt landY,LongInt (*pixelX),LongInt (*pixelY))
{
    if((cReducedQuality & rqBlurryLand) == 0)
    {
        (*pixelX) = landX;
        (*pixelY) = landY;
    }
    else
    {
        (*pixelX) = landX / 2;
        (*pixelY) = landY / 2;
    }
};
LongWord ulandgraphics_drawPixelBG(LongInt landX,LongInt landY,LongInt pixelX,LongInt pixelY)
{
    LongWord drawpixelbg_result;
    drawpixelbg_result = 0;
    if((ulandutils_LandGet(landY, landX) & lfIndestructible) == 0)
    {
        if((((ulandutils_LandGet(landY, landX) & lfBasic) != 0) && (((ulandutils_LandPixelGet(pixelY, pixelX) & AMask) >> AShift) == 255)) && !disableLandBack)
        {
            ulandutils_LandPixelSet(pixelY, pixelX, ulandgraphics_LandBackPixel(landX, landY));
            ++drawpixelbg_result;
        }
        else
        {
            if(((ulandutils_LandGet(landY, landX) & lfObject) != 0) || (((ulandutils_LandPixelGet(pixelY, pixelX) & AMask) >> AShift) < 255))
            {
                ulandutils_LandPixelSet(pixelY, pixelX, ExplosionBorderColorNoA);
            }
        }
    }
    return drawpixelbg_result;
};
void ulandgraphics_drawPixelEBC(LongInt landX,LongInt landY,LongInt pixelX,LongInt pixelY)
{
    if(((ulandutils_LandGet(landY, landX) & lfIndestructible) == 0) && (((ulandutils_LandGet(landY, landX) & lfBasic) != 0) || ((ulandutils_LandGet(landY, landX) & lfObject) != 0)))
    {
        ulandutils_LandPixelSet(pixelY, pixelX, ExplosionBorderColor);
        ulandutils_LandSet(landY, landX, (ulandutils_LandGet(landY, landX) | lfDamaged) & ~lfIce);
        LandDirty[landY / 32][landX / 32] = 1;
    }
};
boolean ulandgraphics_isLandscapeEdge(LongInt weight)
{
    boolean islandscapeedge_result;
    islandscapeedge_result = (weight < 8) && (weight >= 2);
    return islandscapeedge_result;
};
LongInt ulandgraphics_getPixelWeight(LongInt x,LongInt y)
{
    LongInt getpixelweight_result;
    LongInt i;
    LongInt j;
    LongInt r;
    r = 0;
    {i = x - 1;
     LongInt i__end__ = x + 1;
     if (i <= i__end__) do {
                               {j = y - 1;
                                LongInt j__end__ = y + 1;
                                if (j <= j__end__) do {
                                                          if((((i < 0) || (i > (LAND_WIDTH - 1))) || (j < 0)) || (j > (LAND_HEIGHT - 1)))
                                                          {
                                                              return 9;
                                                          }
                                                          if(((ulandutils_LandGet(j, i) & lfLandMask) & ~lfIce) == 0)
                                                          {
                                                              ++r;
                                                          }
                                                      } while(j++ != j__end__);}
                           } while(i++ != i__end__);}
    getpixelweight_result = r;
    return getpixelweight_result;
};
void ulandgraphics_fillPixelFromIceSprite(LongInt pixelX,LongInt pixelY)
{
    PSDL_Surface iceSurface;
    PLongWordArray icePixels;
    LongWord w;
    if(cOnlyStats)
    {
        return;
    }
    iceSurface = SpritesData[sprIceTexture].Surface;
    icePixels = iceSurface->pixels;
    w = ulandutils_LandPixelGet(pixelY, pixelX);
    if(w > 0)
    {
        w = fpcrtl_round(((((w >> RShift) & 0xff) * RGB_LUMINANCE_RED) + (((w >> BShift) & 0xff) * RGB_LUMINANCE_GREEN)) + (((w >> GShift) & 0xff) * RGB_LUMINANCE_BLUE));
        if(w < 128)
        {
            w = w + 128;
        }
        if(w > 255)
        {
            w = 255;
        }
        w = (((w << RShift) | (w << BShift)) | (w << GShift)) | (ulandutils_LandPixelGet(pixelY, pixelX) & AMask);
        ulandutils_LandPixelSet(pixelY, pixelX, ulandgraphics_addBgColor(w, IceColor));
        ulandutils_LandPixelSet(pixelY, pixelX, ulandgraphics_addBgColor(ulandutils_LandPixelGet(pixelY, pixelX), (*icePixels)[(iceSurface->w * (pixelY % iceSurface->h)) + (pixelX % iceSurface->w)]));
    }
    else
    {
        ulandutils_LandPixelSet(pixelY, pixelX, (IceColor & ~AMask) | (0xe8 << AShift));
        ulandutils_LandPixelSet(pixelY, pixelX, ulandgraphics_addBgColor(ulandutils_LandPixelGet(pixelY, pixelX), (*icePixels)[(iceSurface->w * (pixelY % iceSurface->h)) + (pixelX % iceSurface->w)]));
        if(((ulandutils_LandPixelGet(pixelY, pixelX) & AMask) >> AShift) == 255)
        {
            ulandutils_LandPixelSet(pixelY, pixelX, (ulandutils_LandPixelGet(pixelY, pixelX) & ~AMask) | (254 << AShift));
        }
    }
};
void ulandgraphics_DrawPixelIce(LongInt landX,LongInt landY,LongInt pixelX,LongInt pixelY)
{
    if((ulandutils_LandGet(landY, landX) & lfIce) != 0)
    {
        return;
    }
    if(((pixelX < leftX) || (pixelX > rightX)) || (pixelY < topY))
    {
        return;
    }
    if(ulandgraphics_isLandscapeEdge(ulandgraphics_getPixelWeight(landX, landY)))
    {
        if(((ulandutils_LandPixelGet(pixelY, pixelX) & AMask) < 255) && ((ulandutils_LandPixelGet(pixelY, pixelX) & AMask) > 0))
        {
            ulandutils_LandPixelSet(pixelY, pixelX, (IceEdgeColor & ~AMask) | (ulandutils_LandPixelGet(pixelY, pixelX) & AMask));
        }
        else
        {
            if(((ulandutils_LandPixelGet(pixelY, pixelX) & AMask) < 255) || (ulandutils_LandGet(landY, landX) > 255))
            {
                ulandutils_LandPixelSet(pixelY, pixelX, IceEdgeColor);
            }
        }
    }
    else
    {
        if(ulandutils_LandGet(landY, landX) > 255)
        {
            ulandgraphics_fillPixelFromIceSprite(pixelX, pixelY);
        }
    }
    if(ulandutils_LandGet(landY, landX) > 255)
    {
        ulandutils_LandSet(landY, landX, ulandutils_LandGet(landY, landX) | (lfIce & ~lfDamaged));
    }
};
LongWord ulandgraphics_FillLandCircleLineFT(LongInt y,LongInt fromPix,LongInt toPix,fillType fill)
{
    LongWord filllandcirclelineft_result;
    LongInt px;
    LongInt py;
    LongInt i;
    px = 0;
    py = 0;
    filllandcirclelineft_result = 0;
    switch(fill)
    {case backgroundPixel:{i = fromPix;
                           LongInt i__end__ = toPix;
                           if (i <= i__end__) do {
                                                     ulandgraphics_calculatePixelsCoordinates(i, y, &(px), &(py));
                                                     filllandcirclelineft_result += ulandgraphics_drawPixelBG(i, y, px, py);
                                                 } while(i++ != i__end__);}
                          break;
     case ebcPixel:{i = fromPix;
                    LongInt i__end__ = toPix;
                    if (i <= i__end__) do {
                                              ulandgraphics_calculatePixelsCoordinates(i, y, &(px), &(py));
                                              ulandgraphics_drawPixelEBC(i, y, px, py);
                                          } while(i++ != i__end__);}
                   break;
     case nullPixel:{i = fromPix;
                     LongInt i__end__ = toPix;
                     if (i <= i__end__) do {
                                               ulandgraphics_calculatePixelsCoordinates(i, y, &(px), &(py));
                                               if(((ulandutils_LandGet(y, i) & lfIndestructible) == 0) && (!disableLandBack || (ulandutils_LandGet(y, i) > 255)))
                                               {
                                                   ulandutils_LandPixelSet(py, px, ExplosionBorderColorNoA);
                                               }
                                           } while(i++ != i__end__);}
                    break;
     case icePixel:{i = fromPix;
                    LongInt i__end__ = toPix;
                    if (i <= i__end__) do {
                                              ulandgraphics_calculatePixelsCoordinates(i, y, &(px), &(py));
                                              ulandgraphics_DrawPixelIce(i, y, px, py);
                                          } while(i++ != i__end__);}
                   break;
     case addNotHHObj:{i = fromPix;
                       LongInt i__end__ = toPix;
                       if (i <= i__end__) do {
                                                 if(((ulandutils_LandGet(y, i) & lfNotHHObjMask) >> lfNotHHObjShift) < lfNotHHObjSize)
                                                 {
                                                     ulandutils_LandSet(y, i, (ulandutils_LandGet(y, i) & ~lfNotHHObjMask) | ((((ulandutils_LandGet(y, i) & lfNotHHObjMask) >> lfNotHHObjShift) + 1) << lfNotHHObjShift));
                                                 }
                                             } while(i++ != i__end__);}
                      break;
     case removeNotHHObj:{i = fromPix;
                          LongInt i__end__ = toPix;
                          if (i <= i__end__) do {
                                                    if((ulandutils_LandGet(y, i) & lfNotHHObjMask) != 0)
                                                    {
                                                        ulandutils_LandSet(y, i, (ulandutils_LandGet(y, i) & ~lfNotHHObjMask) | ((((ulandutils_LandGet(y, i) & lfNotHHObjMask) >> lfNotHHObjShift) - 1) << lfNotHHObjShift));
                                                    }
                                                } while(i++ != i__end__);}
                         break;
     case addHH:{i = fromPix;
                 LongInt i__end__ = toPix;
                 if (i <= i__end__) do {
                                           if((ulandutils_LandGet(y, i) & lfHHMask) < lfHHMask)
                                           {
                                               ulandutils_LandSet(y, i, ulandutils_LandGet(y, i) + 1);
                                           }
                                       } while(i++ != i__end__);}
                break;
     case removeHH:{i = fromPix;
                    LongInt i__end__ = toPix;
                    if (i <= i__end__) do {
                                              if((ulandutils_LandGet(y, i) & lfHHMask) > 0)
                                              {
                                                  ulandutils_LandSet(y, i, ulandutils_LandGet(y, i) - 1);
                                              }
                                          } while(i++ != i__end__);}
                   break;
     case setCurrentHog:{i = fromPix;
                         LongInt i__end__ = toPix;
                         if (i <= i__end__) do {
                                                   ulandutils_LandSet(y, i, ulandutils_LandGet(y, i) | lfCurHogCrate);
                                               } while(i++ != i__end__);}
                        break;
     case removeCurrentHog:{i = fromPix;
                            LongInt i__end__ = toPix;
                            if (i <= i__end__) do {
                                                      ulandutils_LandSet(y, i, ulandutils_LandGet(y, i) & lfNotCurHogCrate);
                                                  } while(i++ != i__end__);}
                           break;
     default: break;}
    return filllandcirclelineft_result;
};
LongWord ulandgraphics_FillLandCircleSegmentFT(LongInt x,LongInt y,LongInt dx,LongInt dy,fillType fill)
{
    LongWord filllandcirclesegmentft_result;
    filllandcirclesegmentft_result = 0;
    if(((y + dy) & LAND_HEIGHT_MASK) == 0)
    {
        filllandcirclesegmentft_result += ulandgraphics_FillLandCircleLineFT(y + dy, uutils_Max(x - dx, 0), uutils_Min(x + dx, LAND_WIDTH - 1), fill);
    }
    if(((y - dy) & LAND_HEIGHT_MASK) == 0)
    {
        filllandcirclesegmentft_result += ulandgraphics_FillLandCircleLineFT(y - dy, uutils_Max(x - dx, 0), uutils_Min(x + dx, LAND_WIDTH - 1), fill);
    }
    if(((y + dx) & LAND_HEIGHT_MASK) == 0)
    {
        filllandcirclesegmentft_result += ulandgraphics_FillLandCircleLineFT(y + dx, uutils_Max(x - dy, 0), uutils_Min(x + dy, LAND_WIDTH - 1), fill);
    }
    if(((y - dx) & LAND_HEIGHT_MASK) == 0)
    {
        filllandcirclesegmentft_result += ulandgraphics_FillLandCircleLineFT(y - dx, uutils_Max(x - dy, 0), uutils_Min(x + dy, LAND_WIDTH - 1), fill);
    }
    return filllandcirclesegmentft_result;
};
LongWord ulandgraphics_FillRoundInLandFT(LongInt X,LongInt Y,LongInt Radius,fillType fill)
{
    LongWord fillroundinlandft_result;
    LongInt dx;
    LongInt dy;
    LongInt d;
    dx = 0;
    dy = Radius;
    d = 3 - (2 * Radius);
    fillroundinlandft_result = 0;
    while(dx < dy)
    {
        fillroundinlandft_result += ulandgraphics_FillLandCircleSegmentFT(X, Y, dx, dy, fill);
        if(d < 0)
        {
            d = (d + (4 * dx)) + 6;
        }
        else
        {
            d = (d + (4 * (dx - dy))) + 10;
            --dy;
        }
        ++dx;
    }
    if(dx == dy)
    {
        fillroundinlandft_result += ulandgraphics_FillLandCircleSegmentFT(X, Y, dx, dy, fill);
    }
    return fillroundinlandft_result;
};
LongWord ulandgraphics_addBgColor(LongWord OldColor,LongWord NewColor)
{
    LongWord addbgcolor_result;
    Byte oRed;
    Byte oBlue;
    Byte oGreen;
    Byte oAlpha;
    Byte nRed;
    Byte nBlue;
    Byte nGreen;
    Byte nAlpha;
    oAlpha = OldColor >> AShift;
    nAlpha = NewColor >> AShift;
    if((oAlpha == 0) || (nAlpha == 0xff))
    {
        addbgcolor_result = NewColor;
        return addbgcolor_result;
    }
    oRed = OldColor >> RShift;
    oGreen = OldColor >> GShift;
    oBlue = OldColor >> BShift;
    nRed = NewColor >> RShift;
    nGreen = NewColor >> GShift;
    nBlue = NewColor >> BShift;
    nRed = uutils_Min(255, ((nRed * nAlpha) / 255) + (((oRed * oAlpha) * ((Byte)255 - nAlpha)) / 65025));
    nGreen = uutils_Min(255, ((nGreen * nAlpha) / 255) + (((oGreen * oAlpha) * ((Byte)255 - nAlpha)) / 65025));
    nBlue = uutils_Min(255, ((nBlue * nAlpha) / 255) + (((oBlue * oAlpha) * ((Byte)255 - nAlpha)) / 65025));
    nAlpha = uutils_Min(255, oAlpha + nAlpha);
    addbgcolor_result = (((nAlpha << AShift) | (nRed << RShift)) | (nGreen << GShift)) | (nBlue << BShift);
    return addbgcolor_result;
};
LongWord ulandgraphics_FillCircleLines(LongInt x,LongInt y,LongInt dx,LongInt dy,LongWord Value)
{
    LongWord fillcirclelines_result;
    LongInt i;
    fillcirclelines_result = 0;
    if(((y + dy) & LAND_HEIGHT_MASK) == 0)
    {
        {i = uutils_Max(x - dx, 0);
         LongInt i__end__ = uutils_Min(x + dx, LAND_WIDTH - 1);
         if (i <= i__end__) do {
                                   if((ulandutils_LandGet(y + dy, i) & lfIndestructible) == 0)
                                   {
                                       if(ulandutils_LandGet(y + dy, i) != Value)
                                       {
                                           ++fillcirclelines_result;
                                       }
                                       ulandutils_LandSet(y + dy, i, Value);
                                   }
                               } while(i++ != i__end__);}
    }
    if(((y - dy) & LAND_HEIGHT_MASK) == 0)
    {
        {i = uutils_Max(x - dx, 0);
         LongInt i__end__ = uutils_Min(x + dx, LAND_WIDTH - 1);
         if (i <= i__end__) do {
                                   if((ulandutils_LandGet(y - dy, i) & lfIndestructible) == 0)
                                   {
                                       if(ulandutils_LandGet(y - dy, i) != Value)
                                       {
                                           ++fillcirclelines_result;
                                       }
                                       ulandutils_LandSet(y - dy, i, Value);
                                   }
                               } while(i++ != i__end__);}
    }
    if(((y + dx) & LAND_HEIGHT_MASK) == 0)
    {
        {i = uutils_Max(x - dy, 0);
         LongInt i__end__ = uutils_Min(x + dy, LAND_WIDTH - 1);
         if (i <= i__end__) do {
                                   if((ulandutils_LandGet(y + dx, i) & lfIndestructible) == 0)
                                   {
                                       if(ulandutils_LandGet(y + dx, i) != Value)
                                       {
                                           ++fillcirclelines_result;
                                       }
                                       ulandutils_LandSet(y + dx, i, Value);
                                   }
                               } while(i++ != i__end__);}
    }
    if(((y - dx) & LAND_HEIGHT_MASK) == 0)
    {
        {i = uutils_Max(x - dy, 0);
         LongInt i__end__ = uutils_Min(x + dy, LAND_WIDTH - 1);
         if (i <= i__end__) do {
                                   if((ulandutils_LandGet(y - dx, i) & lfIndestructible) == 0)
                                   {
                                       if(ulandutils_LandGet(y - dx, i) != Value)
                                       {
                                           ++fillcirclelines_result;
                                       }
                                       ulandutils_LandSet(y - dx, i, Value);
                                   }
                               } while(i++ != i__end__);}
    }
    return fillcirclelines_result;
};
LongWord ulandgraphics_FillRoundInLand(LongInt X,LongInt Y,LongInt Radius,LongWord Value)
{
    LongWord fillroundinland_result;
    LongInt dx;
    LongInt dy;
    LongInt d;
    fillroundinland_result = 0;
    dx = 0;
    dy = Radius;
    d = 3 - (2 * Radius);
    while(dx < dy)
    {
        fillroundinland_result += ulandgraphics_FillCircleLines(X, Y, dx, dy, Value);
        if(d < 0)
        {
            d = (d + (4 * dx)) + 6;
        }
        else
        {
            d = (d + (4 * (dx - dy))) + 10;
            --dy;
        }
        ++dx;
    }
    if(dx == dy)
    {
        fillroundinland_result += ulandgraphics_FillCircleLines(X, Y, dx, dy, Value);
    }
    return fillroundinland_result;
};
void ulandgraphics_ChangeRoundInLand(LongInt X,LongInt Y,LongInt Radius,boolean doSet,boolean isCurrent,boolean isHH)
{
    if(!doSet && isCurrent)
    {
        ulandgraphics_FillRoundInLandFT(X, Y, Radius, removeCurrentHog);
    }
    else
    {
        if((!doSet && !isCurrent) && isHH)
        {
            ulandgraphics_FillRoundInLandFT(X, Y, Radius, removeHH);
        }
        else
        {
            if((!doSet && !isCurrent) && !isHH)
            {
                ulandgraphics_FillRoundInLandFT(X, Y, Radius, removeNotHHObj);
            }
            else
            {
                if(doSet && isCurrent)
                {
                    ulandgraphics_FillRoundInLandFT(X, Y, Radius, setCurrentHog);
                }
                else
                {
                    if((doSet && !isCurrent) && isHH)
                    {
                        ulandgraphics_FillRoundInLandFT(X, Y, Radius, addHH);
                    }
                    else
                    {
                        if((doSet && !isCurrent) && !isHH)
                        {
                            ulandgraphics_FillRoundInLandFT(X, Y, Radius, addNotHHObj);
                        }
                    }
                }
            }
        }
    }
};
void ulandgraphics_DrawIceBreak(LongInt x,LongInt y,LongInt iceRadius,LongInt iceHeight)
{
    LongInt i;
    LongInt j;
    LongInt iceL;
    LongInt iceR;
    LongInt IceT;
    LongInt iceB;
    TSDL_Rect landRect;
    IceT = 0;
    iceB = uutils_Min(cWaterLine, LAND_HEIGHT - 1);
    iceL = 0;
    iceR = LAND_WIDTH - 1;
    if(WorldEdge != weNone)
    {
        iceL = uutils_Max(leftX, iceL);
        iceR = uutils_Min(rightX, iceR);
    }
    if(y >= cWaterLine)
    {
        iceL = uutils_Max(x - iceRadius, iceL);
        iceR = uutils_Min(x + iceRadius, iceR);
        IceT = uutils_Max(cWaterLine - iceHeight, IceT);
    }
    else
    {
        IceT = uutils_Max(y - iceRadius, IceT);
        iceB = uutils_Min(y + iceRadius, iceB);
        if(x <= leftX)
        {
            iceR = uutils_Min(leftX + iceHeight, iceR);
        }
        else
        {
            iceL = uutils_Max(rightX - iceHeight, iceL);
        }
    }
    if((iceL > iceR) || (IceT > iceB))
    {
        return;
    }
    {i = iceL;
     LongInt i__end__ = iceR;
     if (i <= i__end__) do {
                               {j = IceT;
                                LongInt j__end__ = iceB;
                                if (j <= j__end__) do {
                                                          if(ulandutils_LandGet(j, i) == 0)
                                                          {
                                                              ulandutils_LandSet(j, i, lfIce);
                                                              if((cReducedQuality & rqBlurryLand) == 0)
                                                              {
                                                                  ulandgraphics_fillPixelFromIceSprite(i, j);
                                                              }
                                                              else
                                                              {
                                                                  ulandgraphics_fillPixelFromIceSprite(i / 2, j / 2);
                                                              }
                                                          }
                                                      } while(j++ != j__end__);}
                           } while(i++ != i__end__);}
    landRect.x = iceL;
    landRect.y = IceT;
    landRect.w = (iceR - iceL) + 1;
    landRect.h = (iceB - IceT) + 1;
    ulandtexture_UpdateLandTexture(landRect.x, landRect.w, landRect.y, landRect.h, true);
};
LongWord ulandgraphics_DrawExplosion(LongInt X,LongInt Y,LongInt Radius)
{
    LongWord drawexplosion_result;
    LongInt tx;
    LongInt ty;
    LongInt dx;
    LongInt dy;
    drawexplosion_result = ulandgraphics_FillRoundInLandFT(X, Y, Radius, backgroundPixel);
    if(Radius > 20)
    {
        ulandgraphics_FillRoundInLandFT(X, Y, Radius - 15, nullPixel);
    }
    ulandgraphics_FillRoundInLand(X, Y, Radius, 0);
    ulandgraphics_FillRoundInLandFT(X, Y, Radius + 4, ebcPixel);
    tx = uutils_Max((X - Radius) - 5, 0);
    dx = uutils_Min((X + Radius) + 5, LAND_WIDTH) - tx;
    ty = uutils_Max((Y - Radius) - 5, 0);
    dy = uutils_Min((Y + Radius) + 5, LAND_HEIGHT) - ty;
    ulandtexture_UpdateLandTexture(tx, dx, ty, dy, false);
    return drawexplosion_result;
};
void ulandgraphics_DrawHLinesExplosions(PRangeArray ar,LongInt Radius,LongInt y,LongInt dY,Byte Count)
{
    LongInt tx;
    LongInt ty;
    LongInt by;
    LongInt bx;
    LongInt i;
    {i = 0;
     LongInt i__end__ = ((int)(Count) - 1);
     if (i <= i__end__) do {
                               {ty = uutils_Max(y - Radius, 0);
                                LongInt ty__end__ = uutils_Min(y + Radius, topY);
                                if (ty <= ty__end__) do {
                                                            {tx = uutils_Max(leftX, (*ar)[i].Left - Radius);
                                                             LongInt tx__end__ = uutils_Min(rightX, (*ar)[i].Right + Radius);
                                                             if (tx <= tx__end__) do {
                                                                                         if((ulandutils_LandGet(ty, tx) & lfIndestructible) == 0)
                                                                                         {
                                                                                             if((cReducedQuality & rqBlurryLand) == 0)
                                                                                             {
                                                                                                 by = ty;
                                                                                                 bx = tx;
                                                                                             }
                                                                                             else
                                                                                             {
                                                                                                 by = ty / 2;
                                                                                                 bx = tx / 2;
                                                                                             }
                                                                                             if((((ulandutils_LandGet(ty, tx) & lfBasic) != 0) && (((ulandutils_LandPixelGet(by, bx) & AMask) >> AShift) == 255)) && !disableLandBack)
                                                                                             {
                                                                                                 ulandutils_LandPixelSet(by, bx, ulandgraphics_LandBackPixel(tx, ty));
                                                                                             }
                                                                                             else
                                                                                             {
                                                                                                 if(((ulandutils_LandGet(ty, tx) & lfObject) != 0) || (((ulandutils_LandPixelGet(by, bx) & AMask) >> AShift) < 255))
                                                                                                 {
                                                                                                     ulandutils_LandPixelSet(by, bx, ulandutils_LandPixelGet(by, bx) & ~AMask);
                                                                                                 }
                                                                                             }
                                                                                         }
                                                                                     } while(tx++ != tx__end__);}
                                                        } while(ty++ != ty__end__);}
                               y += dY;
                           } while(i++ != i__end__);}
    Radius += 4;
    y -= Count * dY;
    {i = 0;
     LongInt i__end__ = ((int)(Count) - 1);
     if (i <= i__end__) do {
                               {ty = uutils_Max(y - Radius, 0);
                                LongInt ty__end__ = uutils_Min(y + Radius, topY);
                                if (ty <= ty__end__) do {
                                                            {tx = uutils_Max(leftX, (*ar)[i].Left - Radius);
                                                             LongInt tx__end__ = uutils_Min(rightX, (*ar)[i].Right + Radius);
                                                             if (tx <= tx__end__) do {
                                                                                         if(((ulandutils_LandGet(ty, tx) & lfBasic) != 0) || ((ulandutils_LandGet(ty, tx) & lfObject) != 0))
                                                                                         {
                                                                                             if((cReducedQuality & rqBlurryLand) == 0)
                                                                                             {
                                                                                                 ulandutils_LandPixelSet(ty, tx, ExplosionBorderColor);
                                                                                             }
                                                                                             else
                                                                                             {
                                                                                                 ulandutils_LandPixelSet(ty / 2, tx / 2, ExplosionBorderColor);
                                                                                             }
                                                                                             ulandutils_LandSet(ty, tx, (ulandutils_LandGet(ty, tx) | lfDamaged) & ~lfIce);
                                                                                             LandDirty[ty / 32][tx / 32] = 1;
                                                                                         }
                                                                                     } while(tx++ != tx__end__);}
                                                        } while(ty++ != ty__end__);}
                               y += dY;
                           } while(i++ != i__end__);}
    ulandtexture_UpdateLandTexture(0, LAND_WIDTH, 0, LAND_HEIGHT, false);
};
void ulandgraphics_DrawExplosionBorder(hwFloat X,hwFloat Y,hwFloat dx,hwFloat dy,boolean despeckle)
{
    LongInt t;
    LongInt tx;
    LongInt ty;
    {t = 0;
     LongInt t__end__ = 7;
     if (t <= t__end__) do {
                               X = ufloat_hwFloat_hwFloat_op_add(X, dx);
                               Y = ufloat_hwFloat_hwFloat_op_add(Y, dy);
                               tx = ufloat_hwRound(X);
                               ty = ufloat_hwRound(Y);
                               if((((ty & LAND_HEIGHT_MASK) == 0) && ((tx & LAND_WIDTH_MASK) == 0)) && (((ulandutils_LandGet(ty, tx) & lfBasic) != 0) || ((ulandutils_LandGet(ty, tx) & lfObject) != 0)))
                               {
                                   ulandutils_LandSet(ty, tx, (ulandutils_LandGet(ty, tx) | lfDamaged) & ~lfIce);
                                   if(despeckle)
                                   {
                                       LandDirty[ty / 32][tx / 32] = 1;
                                   }
                                   if((cReducedQuality & rqBlurryLand) == 0)
                                   {
                                       ulandutils_LandPixelSet(ty, tx, ExplosionBorderColor);
                                   }
                                   else
                                   {
                                       ulandutils_LandPixelSet(ty / 2, tx / 2, ExplosionBorderColor);
                                   }
                               }
                           } while(t++ != t__end__);}
};
typedef enum {wnNone = 0x0,
              wnLeft = 0x1,
              wnRight = 0x2} TWrapNeeded;
TWrapNeeded ulandgraphics_DrawTunnel_real(hwFloat X,hwFloat Y,hwFloat dX,hwFloat dY,LongInt ticks,LongInt HalfWidth)
{
    TWrapNeeded drawtunnel_real_result;
    hwFloat nx;
    hwFloat ny;
    hwFloat dX8;
    hwFloat dY8;
    LongInt i;
    LongInt t;
    LongInt tx;
    LongInt ty;
    LongInt by;
    LongInt bx;
    LongInt stX;
    LongInt stY;
    LongInt ddy;
    LongInt ddx;
    boolean despeckle;
    drawtunnel_real_result = wnNone;
    stY = ufloat_hwRound(Y);
    stX = ufloat_hwRound(X);
    despeckle = HalfWidth > 1;
    nx = ufloat_hwFloat_hwFloat_op_add(X, ufloat_hwFloat_LongInt_op_mul(dY, HalfWidth + 8));
    ny = ufloat_hwFloat_hwFloat_op_sub(Y, ufloat_hwFloat_LongInt_op_mul(dX, HalfWidth + 8));
    dX8 = ufloat_hwFloat_LongInt_op_mul(dX, 8);
    dY8 = ufloat_hwFloat_LongInt_op_mul(dY, 8);
    {i = 0;
     LongInt i__end__ = 7;
     if (i <= i__end__) do {
                               X = ufloat_hwFloat_hwFloat_op_sub(nx, dX8);
                               Y = ufloat_hwFloat_hwFloat_op_sub(ny, dY8);
                               {t = -8;
                                LongInt t__end__ = ticks + 8;
                                if (t <= t__end__) do {
                                                          X = ufloat_hwFloat_hwFloat_op_add(X, dX);
                                                          Y = ufloat_hwFloat_hwFloat_op_add(Y, dY);
                                                          tx = ufloat_hwRound(X);
                                                          ty = ufloat_hwRound(Y);
                                                          if((((ty & LAND_HEIGHT_MASK) == 0) && ((tx & LAND_WIDTH_MASK) == 0)) && (((ulandutils_LandGet(ty, tx) & lfBasic) != 0) || ((ulandutils_LandGet(ty, tx) & lfObject) != 0)))
                                                          {
                                                              ulandutils_LandSet(ty, tx, ulandutils_LandGet(ty, tx) & ~lfIce);
                                                              if(despeckle)
                                                              {
                                                                  ulandutils_LandSet(ty, tx, ulandutils_LandGet(ty, tx) | lfDamaged);
                                                                  LandDirty[ty / 32][tx / 32] = 1;
                                                              }
                                                              if((cReducedQuality & rqBlurryLand) == 0)
                                                              {
                                                                  ulandutils_LandPixelSet(ty, tx, ExplosionBorderColor);
                                                              }
                                                              else
                                                              {
                                                                  ulandutils_LandPixelSet(ty / 2, tx / 2, ExplosionBorderColor);
                                                              }
                                                          }
                                                      } while(t++ != t__end__);}
                               nx = ufloat_hwFloat_hwFloat_op_sub(nx, dY);
                               ny = ufloat_hwFloat_hwFloat_op_add(ny, dX);
                           } while(i++ != i__end__);}
    {i = -HalfWidth;
     LongInt i__end__ = HalfWidth;
     if (i <= i__end__) do {
                               X = ufloat_hwFloat_hwFloat_op_sub(nx, dX8);
                               Y = ufloat_hwFloat_hwFloat_op_sub(ny, dY8);
                               ulandgraphics_DrawExplosionBorder(X, Y, dX, dY, despeckle);
                               X = nx;
                               Y = ny;
                               {t = 0;
                                LongInt t__end__ = ticks;
                                if (t <= t__end__) do {
                                                          X = ufloat_hwFloat_hwFloat_op_add(X, dX);
                                                          Y = ufloat_hwFloat_hwFloat_op_add(Y, dY);
                                                          tx = ufloat_hwRound(X);
                                                          ty = ufloat_hwRound(Y);
                                                          if((((ty & LAND_HEIGHT_MASK) == 0) && ((tx & LAND_WIDTH_MASK) == 0)) && ((ulandutils_LandGet(ty, tx) & lfIndestructible) == 0))
                                                          {
                                                              if((cReducedQuality & rqBlurryLand) == 0)
                                                              {
                                                                  by = ty;
                                                                  bx = tx;
                                                              }
                                                              else
                                                              {
                                                                  by = ty / 2;
                                                                  bx = tx / 2;
                                                              }
                                                              if((((ulandutils_LandGet(ty, tx) & lfBasic) != 0) && (((ulandutils_LandPixelGet(by, bx) & AMask) >> AShift) == 255)) && !disableLandBack)
                                                              {
                                                                  ulandutils_LandPixelSet(by, bx, ulandgraphics_LandBackPixel(tx, ty));
                                                              }
                                                              else
                                                              {
                                                                  if(((ulandutils_LandGet(ty, tx) & lfObject) != 0) || (((ulandutils_LandPixelGet(by, bx) & AMask) >> AShift) < 255))
                                                                  {
                                                                      ulandutils_LandPixelSet(by, bx, ulandutils_LandPixelGet(by, bx) & ~AMask);
                                                                  }
                                                              }
                                                              ulandutils_LandSet(ty, tx, 0);
                                                          }
                                                      } while(t++ != t__end__);}
                               ulandgraphics_DrawExplosionBorder(X, Y, dX, dY, despeckle);
                               nx = ufloat_hwFloat_hwFloat_op_sub(nx, dY);
                               ny = ufloat_hwFloat_hwFloat_op_add(ny, dX);
                           } while(i++ != i__end__);}
    {i = 0;
     LongInt i__end__ = 7;
     if (i <= i__end__) do {
                               X = ufloat_hwFloat_hwFloat_op_sub(nx, dX8);
                               Y = ufloat_hwFloat_hwFloat_op_sub(ny, dY8);
                               {t = -8;
                                LongInt t__end__ = ticks + 8;
                                if (t <= t__end__) do {
                                                          X = ufloat_hwFloat_hwFloat_op_add(X, dX);
                                                          Y = ufloat_hwFloat_hwFloat_op_add(Y, dY);
                                                          tx = ufloat_hwRound(X);
                                                          ty = ufloat_hwRound(Y);
                                                          if((((ty & LAND_HEIGHT_MASK) == 0) && ((tx & LAND_WIDTH_MASK) == 0)) && (((ulandutils_LandGet(ty, tx) & lfBasic) != 0) || ((ulandutils_LandGet(ty, tx) & lfObject) != 0)))
                                                          {
                                                              ulandutils_LandSet(ty, tx, (ulandutils_LandGet(ty, tx) | lfDamaged) & ~lfIce);
                                                              if(despeckle)
                                                              {
                                                                  LandDirty[ty / 32][tx / 32] = 1;
                                                              }
                                                              if((cReducedQuality & rqBlurryLand) == 0)
                                                              {
                                                                  ulandutils_LandPixelSet(ty, tx, ExplosionBorderColor);
                                                              }
                                                              else
                                                              {
                                                                  ulandutils_LandPixelSet(ty / 2, tx / 2, ExplosionBorderColor);
                                                              }
                                                          }
                                                      } while(t++ != t__end__);}
                               nx = ufloat_hwFloat_hwFloat_op_sub(nx, dY);
                               ny = ufloat_hwFloat_hwFloat_op_add(ny, dX);
                           } while(i++ != i__end__);}
    tx = ((stX - (HalfWidth * 2)) - 4) - fpcrtl_abs(ufloat_hwRound(ufloat_hwFloat_LongInt_op_mul(dX, ticks)));
    ddx = ((stX + (HalfWidth * 2)) + 4) + fpcrtl_abs(ufloat_hwRound(ufloat_hwFloat_LongInt_op_mul(dX, ticks)));
    if(WorldEdge == weWrap)
    {
        if((tx < leftX) || (ddx < leftX))
        {
            drawtunnel_real_result = wnLeft;
        }
        else
        {
            if((tx > rightX) || (ddx > rightX))
            {
                drawtunnel_real_result = wnRight;
            }
        }
    }
    tx = uutils_Max(tx, 0);
    ty = uutils_Max(((stY - (HalfWidth * 2)) - 4) - fpcrtl_abs(ufloat_hwRound(ufloat_hwFloat_LongInt_op_mul(dY, ticks))), 0);
    ddx = uutils_Min(ddx, LAND_WIDTH) - tx;
    ddy = uutils_Min(((stY + (HalfWidth * 2)) + 4) + fpcrtl_abs(ufloat_hwRound(ufloat_hwFloat_LongInt_op_mul(dY, ticks))), LAND_HEIGHT) - ty;
    ulandtexture_UpdateLandTexture(tx, ddx, ty, ddy, false);
    return drawtunnel_real_result;
};
void ulandgraphics_DrawTunnel(hwFloat X,hwFloat Y,hwFloat dX,hwFloat dY,LongInt ticks,LongInt HalfWidth)
{
    TWrapNeeded wn;
    wn = ulandgraphics_DrawTunnel_real(X, Y, dX, dY, ticks, HalfWidth);
    if(wn != wnNone)
    {
        if(wn == wnLeft)
        {
            ulandgraphics_DrawTunnel_real(ufloat_hwFloat_hwFloat_op_add(X, ufloat_int2hwFloat(playWidth)), Y, dX, dY, ticks, HalfWidth);
        }
        else
        {
            ulandgraphics_DrawTunnel_real(ufloat_hwFloat_hwFloat_op_sub(X, ufloat_int2hwFloat(playWidth)), Y, dX, dY, ticks, HalfWidth);
        }
    }
};
boolean ulandgraphics_TryPlaceOnLandSimple(LongInt cpX,LongInt cpY,TSprite Obj,LongInt Frame,boolean doPlace,boolean indestructible)
{
    boolean tryplaceonlandsimple_result;
    Word lf;
    if(indestructible)
    {
        lf = lfIndestructible;
    }
    else
    {
        lf = 0;
    }
    tryplaceonlandsimple_result = ulandgraphics_TryPlaceOnLand_12(cpX, cpY, Obj, Frame, doPlace, false, false, false, false, false, lf, 0xffffffff);
    return tryplaceonlandsimple_result;
};
boolean ulandgraphics_TryPlaceOnLand_6(LongInt cpX,LongInt cpY,TSprite Obj,LongInt Frame,boolean doPlace,Word LandFlags)
{
    boolean tryplaceonland_result;
    tryplaceonland_result = ulandgraphics_TryPlaceOnLand_12(cpX, cpY, Obj, Frame, doPlace, false, false, false, false, false, LandFlags, 0xffffffff);
    return tryplaceonland_result;
};
boolean ulandgraphics_ForcePlaceOnLand(LongInt cpX,LongInt cpY,TSprite Obj,LongInt Frame,Word LandFlags,LongWord Tint,boolean Behind,boolean flipHoriz,boolean flipVert)
{
    boolean forceplaceonland_result;
    forceplaceonland_result = ulandgraphics_TryPlaceOnLand_12(cpX, cpY, Obj, Frame, true, false, true, Behind, flipHoriz, flipVert, LandFlags, Tint);
    return forceplaceonland_result;
};
boolean ulandgraphics_TryPlaceOnLand_12(LongInt cpX,LongInt cpY,TSprite Obj,LongInt Frame,boolean doPlace,boolean outOfMap,boolean force,boolean behind,boolean flipHoriz,boolean flipVert,Word LandFlags,LongWord Tint)
{
    boolean tryplaceonland_result;
    LongInt X;
    LongInt Y;
    LongInt bpp;
    LongInt h;
    LongInt w;
    LongInt row;
    LongInt col;
    LongInt gx;
    LongInt gy;
    LongInt numFramesFirstCol;
    PByteArray p;
    PSDL_Surface Image;
    LongWord pixel;
    tryplaceonland_result = false;
    numFramesFirstCol = SpritesData[Obj].imageHeight / SpritesData[Obj].Height;
    if(outOfMap)
    {
        doPlace = false;
    }
    if(udebug_checkFails(SpritesData[Obj].Surface != NULL, __str0, true))
    {
        return tryplaceonland_result;
    }
    Image = SpritesData[Obj].Surface;
    w = SpritesData[Obj].Width;
    h = SpritesData[Obj].Height;
    if(flipVert)
    {
        urenderutils_flipSurface(Image, true);
    }
    if(flipHoriz)
    {
        urenderutils_flipSurface(Image, false);
    }
    row = Frame % numFramesFirstCol;
    col = Frame / numFramesFirstCol;
    if(sdlh_SDL_MustLock(Image))
    {
        if(udebug_SDLCheck(SDL_LockSurface(Image) >= 0, __str1, true))
        {
            return tryplaceonland_result;
        }
    }
    bpp = (*Image->format).BytesPerPixel;
    if(udebug_checkFails(bpp == 4, __str2, true))
    {
        if(sdlh_SDL_MustLock(Image))
        {
            SDL_UnlockSurface(Image);
        }
        return tryplaceonland_result;
    }
    p = ((PByteArray)&((*((PByteArray)Image->pixels))[((Image->pitch * row) * h) + ((col * w) * 4)]));
    switch(bpp)
    {case 4:{Y = 0;
             LongInt Y__end__ = ((int)(h) - 1);
             if (Y <= Y__end__) do {
                                       {X = 0;
                                        LongInt X__end__ = ((int)(w) - 1);
                                        if (X <= X__end__) do {
                                                                  if(((*((PLongWord)&((*p)[X * 4]))) & AMask) != 0)
                                                                  {
                                                                      if((((((outOfMap && ((cpY + Y) < LAND_HEIGHT)) && ((cpY + Y) >= 0)) && ((cpX + X) < LAND_WIDTH)) && ((cpX + X) >= 0)) && (!force && (ulandutils_LandGet(cpY + Y, cpX + X) != 0))) || (!outOfMap && ((((((cpY + Y) <= topY) || ((cpY + Y) >= LAND_HEIGHT)) || ((cpX + X) <= leftX)) || ((cpX + X) >= rightX)) || (!force && (ulandutils_LandGet(cpY + Y, cpX + X) != 0)))))
                                                                      {
                                                                          if(sdlh_SDL_MustLock(Image))
                                                                          {
                                                                              SDL_UnlockSurface(Image);
                                                                          }
                                                                          return tryplaceonland_result;
                                                                      }
                                                                  }
                                                              } while(X++ != X__end__);}
                                       p = ((PByteArray)&((*p)[Image->pitch]));
                                   } while(Y++ != Y__end__);}
            break;
     default: break;}
    tryplaceonland_result = true;
    if(!doPlace)
    {
        if(sdlh_SDL_MustLock(Image))
        {
            SDL_UnlockSurface(Image);
        }
        return tryplaceonland_result;
    }
    p = ((PByteArray)&((*((PByteArray)Image->pixels))[((Image->pitch * row) * h) + ((col * w) * 4)]));
    switch(bpp)
    {case 4:{Y = 0;
             LongInt Y__end__ = ((int)(h) - 1);
             if (Y <= Y__end__) do {
                                       {X = 0;
                                        LongInt X__end__ = ((int)(w) - 1);
                                        if (X <= X__end__) do {
                                                                  if(((*((PLongWord)&((*p)[X * 4]))) & AMask) != 0)
                                                                  {
                                                                      if((cReducedQuality & rqBlurryLand) == 0)
                                                                      {
                                                                          gx = cpX + X;
                                                                          gy = cpY + Y;
                                                                      }
                                                                      else
                                                                      {
                                                                          gx = (cpX + X) / 2;
                                                                          gy = (cpY + Y) / 2;
                                                                      }
                                                                      if(!behind || ((ulandutils_LandGet(cpY + Y, cpX + X) & lfLandMask) == 0))
                                                                      {
                                                                          if(((LandFlags & lfBasic) != 0) || ((((ulandutils_LandPixelGet(gy, gx) & AMask) >> AShift) > 128) && ((LandFlags & (lfObject | lfIce)) == 0)))
                                                                          {
                                                                              ulandutils_LandSet(cpY + Y, cpX + X, lfBasic | LandFlags);
                                                                          }
                                                                          else
                                                                          {
                                                                              if((LandFlags & lfIce) == 0)
                                                                              {
                                                                                  ulandutils_LandSet(cpY + Y, cpX + X, lfObject | LandFlags);
                                                                              }
                                                                              else
                                                                              {
                                                                                  ulandutils_LandSet(cpY + Y, cpX + X, LandFlags);
                                                                              }
                                                                          }
                                                                      }
                                                                      if(!behind || (ulandutils_LandPixelGet(gy, gx) == 0))
                                                                      {
                                                                          if(Tint == 0xffffffff)
                                                                          {
                                                                              ulandutils_LandPixelSet(gy, gx, (*((PLongWord)&((*p)[X * 4]))));
                                                                          }
                                                                          else
                                                                          {
                                                                              pixel = (*((PLongWord)&((*p)[X * 4])));
                                                                              ulandutils_LandPixelSet(gy, gx, (((fpcrtl_ceil(((pixel >> RShift) & 0xff) * ((Tint >> 24) /(float) 255)) << RShift) | (fpcrtl_ceil(((pixel >> GShift) & 0xff) * (((Tint >> 16) & 0xff) /(float) 255)) << GShift)) | (fpcrtl_ceil(((pixel >> BShift) & 0xff) * (((Tint >> 8) & 0xff) /(float) 255)) << BShift)) | (fpcrtl_ceil(((pixel >> AShift) & 0xff) * ((Tint & 0xff) /(float) 255)) << AShift));
                                                                          }
                                                                      }
                                                                  }
                                                              } while(X++ != X__end__);}
                                       p = ((PByteArray)&((*p)[Image->pitch]));
                                   } while(Y++ != Y__end__);}
            break;
     default: break;}
    if(sdlh_SDL_MustLock(Image))
    {
        SDL_UnlockSurface(Image);
    }
    if(flipVert)
    {
        urenderutils_flipSurface(Image, true);
    }
    if(flipHoriz)
    {
        urenderutils_flipSurface(Image, false);
    }
    X = uutils_Max(cpX, leftX);
    w = uutils_Min(cpX + Image->w, LAND_WIDTH) - X;
    Y = uutils_Max(cpY, topY);
    h = uutils_Min(cpY + Image->h, LAND_HEIGHT) - Y;
    ulandtexture_UpdateLandTexture(X, w, Y, h, true);
    uscript_ScriptCall_4(__str3, (Obj), cpX + (w / 2), cpY + (h / 2));
    if(Obj == sprAmGirder)
    {
        uscript_ScriptCall_4(__str4, Frame, cpX + (w / 2), cpY + (h / 2));
    }
    else
    {
        if(Obj == sprAmRubber)
        {
            uscript_ScriptCall_4(__str5, Frame, cpX + (w / 2), cpY + (h / 2));
        }
    }
    return tryplaceonland_result;
};
void ulandgraphics_EraseLandRectRaw(LongWord X,LongWord Y,LongWord width,LongWord height)
{
    LongWord tx;
    LongWord ty;
    {ty = 0;
     LongWord ty__end__ = height - 1;
     if (ty <= ty__end__) do {
                                 {tx = 0;
                                  LongWord tx__end__ = width - 1;
                                  if (tx <= tx__end__) do {
                                                              ulandutils_LandPixelSet(ty, tx, 0);
                                                              ulandutils_LandSet(Y + ty, X + tx, 0);
                                                          } while(tx++ != tx__end__);}
                             } while(ty++ != ty__end__);}
};
void ulandgraphics_EraseLand(LongInt cpX,LongInt cpY,TSprite Obj,LongInt Frame,Word LandFlags,boolean eraseOnLFMatch,boolean onlyEraseLF,boolean flipHoriz,boolean flipVert)
{
    LongInt X;
    LongInt Y;
    LongInt bpp;
    LongInt h;
    LongInt w;
    LongInt row;
    LongInt col;
    LongInt gx;
    LongInt gy;
    LongInt numFramesFirstCol;
    PByteArray p;
    PSDL_Surface Image;
    numFramesFirstCol = SpritesData[Obj].imageHeight / SpritesData[Obj].Height;
    if(udebug_checkFails(SpritesData[Obj].Surface != NULL, __str0, true))
    {
        return;
    }
    Image = SpritesData[Obj].Surface;
    w = SpritesData[Obj].Width;
    h = SpritesData[Obj].Height;
    if(flipVert)
    {
        urenderutils_flipSurface(Image, true);
    }
    if(flipHoriz)
    {
        urenderutils_flipSurface(Image, false);
    }
    row = Frame % numFramesFirstCol;
    col = Frame / numFramesFirstCol;
    if(sdlh_SDL_MustLock(Image))
    {
        if(udebug_SDLCheck(SDL_LockSurface(Image) >= 0, __str6, true))
        {
            return;
        }
    }
    bpp = (*Image->format).BytesPerPixel;
    if(udebug_checkFails(bpp == 4, __str2, true))
    {
        if(sdlh_SDL_MustLock(Image))
        {
            SDL_UnlockSurface(Image);
        }
        return;
    }
    p = ((PByteArray)&((*((PByteArray)Image->pixels))[((Image->pitch * row) * h) + ((col * w) * 4)]));
    {Y = 0;
     LongInt Y__end__ = ((int)(h) - 1);
     if (Y <= Y__end__) do {
                               {X = 0;
                                LongInt X__end__ = ((int)(w) - 1);
                                if (X <= X__end__) do {
                                                          if(((*((PLongWord)&((*p)[X * 4]))) & AMask) != 0)
                                                          {
                                                              if(((((cpY + Y) <= topY) || ((cpY + Y) >= LAND_HEIGHT)) || ((cpX + X) <= leftX)) || ((cpX + X) >= rightX))
                                                              {
                                                                  if(sdlh_SDL_MustLock(Image))
                                                                  {
                                                                      SDL_UnlockSurface(Image);
                                                                  }
                                                                  return;
                                                              }
                                                          }
                                                      } while(X++ != X__end__);}
                               p = ((PByteArray)&((*p)[Image->pitch]));
                           } while(Y++ != Y__end__);}
    p = ((PByteArray)&((*((PByteArray)Image->pixels))[((Image->pitch * row) * h) + ((col * w) * 4)]));
    {Y = 0;
     LongInt Y__end__ = ((int)(h) - 1);
     if (Y <= Y__end__) do {
                               {X = 0;
                                LongInt X__end__ = ((int)(w) - 1);
                                if (X <= X__end__) do {
                                                          if(((*((PLongWord)&((*p)[X * 4]))) & AMask) != 0)
                                                          {
                                                              if((cReducedQuality & rqBlurryLand) == 0)
                                                              {
                                                                  gx = cpX + X;
                                                                  gy = cpY + Y;
                                                              }
                                                              else
                                                              {
                                                                  gx = (cpX + X) / 2;
                                                                  gy = (cpY + Y) / 2;
                                                              }
                                                              if((!eraseOnLFMatch || ((ulandutils_LandGet(cpY + Y, cpX + X) & LandFlags) != 0)) && (((*((PLongWord)&((*p)[X * 4]))) & AMask) != 0))
                                                              {
                                                                  if(!onlyEraseLF)
                                                                  {
                                                                      ulandutils_LandPixelSet(gy, gx, 0);
                                                                      ulandutils_LandSet(cpY + Y, cpX + X, 0);
                                                                  }
                                                                  else
                                                                  {
                                                                      ulandutils_LandSet(cpY + Y, cpX + X, ulandutils_LandGet(cpY + Y, cpX + X) & ~LandFlags);
                                                                  }
                                                              }
                                                          }
                                                      } while(X++ != X__end__);}
                               p = ((PByteArray)&((*p)[Image->pitch]));
                           } while(Y++ != Y__end__);}
    if(sdlh_SDL_MustLock(Image))
    {
        SDL_UnlockSurface(Image);
    }
    if(flipVert)
    {
        urenderutils_flipSurface(Image, true);
    }
    if(flipHoriz)
    {
        urenderutils_flipSurface(Image, false);
    }
    X = uutils_Max(cpX, leftX);
    w = uutils_Min(cpX + Image->w, LAND_WIDTH) - X;
    Y = uutils_Max(cpY, topY);
    h = uutils_Min(cpY + Image->h, LAND_HEIGHT) - Y;
    ulandtexture_UpdateLandTexture(X, w, Y, h, true);
};
PTexture ulandgraphics_GetPlaceCollisionTex(LongInt cpX,LongInt cpY,TSprite Obj,LongInt Frame)
{
    PTexture getplacecollisiontex_result;
    LongInt X;
    LongInt Y;
    LongInt bpp;
    LongInt h;
    LongInt w;
    LongInt row;
    LongInt col;
    LongInt numFramesFirstCol;
    PLongWordArray p;
    PLongWordArray pt;
    PSDL_Surface Image;
    PSDL_Surface finalSurface;
    getplacecollisiontex_result = NULL;
    numFramesFirstCol = SpritesData[Obj].imageHeight / SpritesData[Obj].Height;
    udebug_checkFails(SpritesData[Obj].Surface != NULL, __str0, true);
    Image = SpritesData[Obj].Surface;
    w = SpritesData[Obj].Width;
    h = SpritesData[Obj].Height;
    row = Frame % numFramesFirstCol;
    col = Frame / numFramesFirstCol;
    if(sdlh_SDL_MustLock(Image))
    {
        if(udebug_SDLCheck(SDL_LockSurface(Image) >= 0, __str7, true))
        {
            return getplacecollisiontex_result;
        }
    }
    bpp = (*Image->format).BytesPerPixel;
    udebug_checkFails(bpp == 4, __str2, true);
    finalSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, RMask, GMask, BMask, AMask);
    udebug_checkFails(finalSurface != NULL, __str8, true);
    if(sdlh_SDL_MustLock(finalSurface))
    {
        udebug_SDLCheck(SDL_LockSurface(finalSurface) >= 0, __str9, true);
    }
    if(!allOK)
    {
        if(sdlh_SDL_MustLock(Image))
        {
            SDL_UnlockSurface(Image);
        }
        if(sdlh_SDL_MustLock(finalSurface))
        {
            SDL_UnlockSurface(finalSurface);
        }
        if(finalSurface != NULL)
        {
            SDL_FreeSurface(finalSurface);
        }
    }
    p = ((PLongWordArray)&((*((PLongWordArray)Image->pixels))[(((Image->pitch / 4) * row) * h) + (col * w)]));
    pt = ((PLongWordArray)finalSurface->pixels);
    {Y = 0;
     LongInt Y__end__ = ((int)(h) - 1);
     if (Y <= Y__end__) do {
                               {X = 0;
                                LongInt X__end__ = ((int)(w) - 1);
                                if (X <= X__end__) do {
                                                          if((((*p)[X] & AMask) != 0) && ((((((cpY + Y) < topY) || ((cpY + Y) >= LAND_HEIGHT)) || ((cpX + X) < leftX)) || ((cpX + X) > rightX)) || (ulandutils_LandGet(cpY + Y, cpX + X) != 0)))
                                                          {
                                                              (*pt)[X] = cWhiteColor;
                                                          }
                                                          else
                                                          {
                                                              (*pt)[X] = cWhiteColor & ~AMask;
                                                          }
                                                      } while(X++ != X__end__);}
                               p = ((PLongWordArray)&((*p)[Image->pitch / 4]));
                               pt = ((PLongWordArray)&((*pt)[finalSurface->pitch / 4]));
                           } while(Y++ != Y__end__);}
    if(sdlh_SDL_MustLock(Image))
    {
        SDL_UnlockSurface(Image);
    }
    if(sdlh_SDL_MustLock(finalSurface))
    {
        SDL_UnlockSurface(finalSurface);
    }
    getplacecollisiontex_result = utextures_Surface2Tex(finalSurface, true);
    SDL_FreeSurface(finalSurface);
    return getplacecollisiontex_result;
};
boolean ulandgraphics_Despeckle(LongInt X,LongInt Y)
{
    boolean despeckle_result;
    LongInt nx;
    LongInt ny;
    LongInt i;
    LongInt j;
    LongInt c;
    LongInt xx;
    LongInt yy;
    boolean pixelsweep;
    despeckle_result = true;
    if((cReducedQuality & rqBlurryLand) == 0)
    {
        xx = X;
        yy = Y;
    }
    else
    {
        xx = X / 2;
        yy = Y / 2;
    }
    pixelsweep = (ulandutils_LandGet(Y, X) <= lfAllObjMask) && ((ulandutils_LandPixelGet(yy, xx) & AMask) != 0);
    if((((ulandutils_LandGet(Y, X) & lfDamaged) != 0) && ((ulandutils_LandGet(Y, X) & lfIndestructible) == 0)) || pixelsweep)
    {
        c = 0;
        {i = -1;
         LongInt i__end__ = 1;
         if (i <= i__end__) do {
                                   {j = -1;
                                    LongInt j__end__ = 1;
                                    if (j <= j__end__) do {
                                                              if((i != 0) || (j != 0))
                                                              {
                                                                  ny = Y + i;
                                                                  nx = X + j;
                                                                  if(((ny & LAND_HEIGHT_MASK) == 0) && ((nx & LAND_WIDTH_MASK) == 0))
                                                                  {
                                                                      if(pixelsweep)
                                                                      {
                                                                          if((cReducedQuality & rqBlurryLand) != 0)
                                                                          {
                                                                              ny = (Y / 2) + i;
                                                                              nx = (X / 2) + j;
                                                                              if(((ny & (LAND_HEIGHT_MASK / 2)) == 0) && ((nx & (LAND_WIDTH_MASK / 2)) == 0))
                                                                              {
                                                                                  if((ulandutils_LandPixelGet(ny, nx) & AMask) != 0)
                                                                                  {
                                                                                      ++c;
                                                                                  }
                                                                              }
                                                                          }
                                                                          else
                                                                          {
                                                                              if((ulandutils_LandPixelGet(ny, nx) & AMask) != 0)
                                                                              {
                                                                                  ++c;
                                                                              }
                                                                          }
                                                                      }
                                                                      else
                                                                      {
                                                                          if(ulandutils_LandGet(ny, nx) > 255)
                                                                          {
                                                                              ++c;
                                                                          }
                                                                      }
                                                                  }
                                                              }
                                                          } while(j++ != j__end__);}
                               } while(i++ != i__end__);}
        if(c < 4)
        {
            if(((ulandutils_LandGet(Y, X) & lfBasic) != 0) && !disableLandBack)
            {
                ulandutils_LandPixelSet(yy, xx, ulandgraphics_LandBackPixel(X, Y));
            }
            else
            {
                ulandutils_LandPixelSet(yy, xx, ulandutils_LandPixelGet(yy, xx) & ~AMask);
            }
            if(!pixelsweep)
            {
                ulandutils_LandSet(Y, X, 0);
                return despeckle_result;
            }
        }
    }
    despeckle_result = false;
    return despeckle_result;
};
void ulandgraphics_Smooth(LongInt X,LongInt Y)
{
    Integer c;
    Integer r;
    Integer g;
    Integer b;
    Integer a;
    Integer i;
    LongInt nx;
    LongInt ny;
    LongWord pixel;
    if((ulandutils_LandGet(Y, X) & lfDamaged) == 0)
    {
        return;
    }
    if((((Y <= (topY + 1)) || (Y >= (LAND_HEIGHT - 2))) || (X <= (leftX + 1))) || (X >= (rightX - 1)))
    {
        return;
    }
    c = 8;
    r = 0;
    g = 0;
    b = 0;
    a = 0;
    {nx = X - 1;
     LongInt nx__end__ = X + 1;
     if (nx <= nx__end__) do {
                                 {ny = Y - 1;
                                  LongInt ny__end__ = Y + 1;
                                  if (ny <= ny__end__) do {
                                                              if((ulandutils_LandGet(ny, nx) & lfDamaged) == 0)
                                                              {
                                                                  pixel = ulandutils_LandPixelGet(ny, nx);
                                                                  r += (pixel & RMask) >> RShift;
                                                                  g += (pixel & GMask) >> GShift;
                                                                  b += (pixel & BMask) >> BShift;
                                                                  a += (pixel & AMask) >> AShift;
                                                                  --c;
                                                              }
                                                          } while(ny++ != ny__end__);}
                             } while(nx++ != nx__end__);}
    if(c < 1)
    {
        return;
    }
    {i = 1;
     Integer i__end__ = c;
     if (i <= i__end__) do {
                               r += ExplosionBorderColorR;
                               g += ExplosionBorderColorG;
                               b += ExplosionBorderColorB;
                               a += 255;
                           } while(i++ != i__end__);}
    r = r / 8;
    g = g / 8;
    b = b / 8;
    a = a / 8;
    ulandutils_LandPixelSet(Y, X, (((r << RShift) | (g << GShift)) | (b << BShift)) | (a << AShift));
};
void ulandgraphics_Smooth_oldImpl(LongInt X,LongInt Y)
{
    if(((((ulandutils_LandGet(Y, X) == 0) && (Y > (topY + 1))) && (Y < (LAND_HEIGHT - 2))) && (X > (leftX + 1))) && (X < (rightX - 1)))
    {
        if(((((ulandutils_LandGet(Y, X - 1) & lfDamaged) != 0) && ((ulandutils_LandGet(Y + 1, X) & lfDamaged) != 0)) || ((ulandutils_LandGet(Y - 1, X) & lfDamaged) != 0)) || (((ulandutils_LandGet(Y, X + 1) & lfDamaged) != 0) && (((ulandutils_LandGet(Y - 1, X) & lfDamaged) != 0) || ((ulandutils_LandGet(Y + 1, X) & lfDamaged) != 0))))
        {
            if((cReducedQuality & rqBlurryLand) == 0)
            {
                if(((ulandutils_LandPixelGet(Y, X) & AMask) >> AShift) < 10)
                {
                    ulandutils_LandPixelSet(Y, X, (ExplosionBorderColor & ~AMask) | (128 << AShift));
                }
                else
                {
                    ulandutils_LandPixelSet(Y, X, ((((((((ulandutils_LandPixelGet(Y, X) & RMask) >> RShift) / 2) + (((ExplosionBorderColor & RMask) >> RShift) / 2)) & 0xff) << RShift) | ((((((ulandutils_LandPixelGet(Y, X) & GMask) >> GShift) / 2) + (((ExplosionBorderColor & GMask) >> GShift) / 2)) & 0xff) << GShift)) | ((((((ulandutils_LandPixelGet(Y, X) & BMask) >> BShift) / 2) + (((ExplosionBorderColor & BMask) >> BShift) / 2)) & 0xff) << BShift)) | (0xff << AShift));
                }
            }
        }
        else
        {
            if(((((((((((ulandutils_LandGet(Y, X - 1) & lfDamaged) != 0) && ((ulandutils_LandGet(Y + 1, X - 1) & lfDamaged) != 0)) && ((ulandutils_LandGet(Y + 2, X) & lfDamaged) != 0)) || ((((ulandutils_LandGet(Y, X - 1) & lfDamaged) != 0) && ((ulandutils_LandGet(Y - 1, X - 1) & lfDamaged) != 0)) && ((ulandutils_LandGet(Y - 2, X) & lfDamaged) != 0))) || ((((ulandutils_LandGet(Y, X + 1) & lfDamaged) != 0) && ((ulandutils_LandGet(Y + 1, X + 1) & lfDamaged) != 0)) && ((ulandutils_LandGet(Y + 2, X) & lfDamaged) != 0))) || ((((ulandutils_LandGet(Y, X + 1) & lfDamaged) != 0) && ((ulandutils_LandGet(Y - 1, X + 1) & lfDamaged) != 0)) && ((ulandutils_LandGet(Y - 2, X) & lfDamaged) != 0))) || ((((ulandutils_LandGet(Y + 1, X) & lfDamaged) != 0) && ((ulandutils_LandGet(Y + 1, X + 1) & lfDamaged) != 0)) && ((ulandutils_LandGet(Y, X + 2) & lfDamaged) != 0))) || ((((ulandutils_LandGet(Y - 1, X) & lfDamaged) != 0) && ((ulandutils_LandGet(Y - 1, X + 1) & lfDamaged) != 0)) && ((ulandutils_LandGet(Y, X + 2) & lfDamaged) != 0))) || ((((ulandutils_LandGet(Y + 1, X) & lfDamaged) != 0) && ((ulandutils_LandGet(Y + 1, X - 1) & lfDamaged) != 0)) && ((ulandutils_LandGet(Y, X - 2) & lfDamaged) != 0))) || ((((ulandutils_LandGet(Y - 1, X) & lfDamaged) != 0) && ((ulandutils_LandGet(Y - 1, X - 1) & lfDamaged) != 0)) && ((ulandutils_LandGet(Y, X - 2) & lfDamaged) != 0)))
            {
                if((cReducedQuality & rqBlurryLand) == 0)
                {
                    if(((ulandutils_LandPixelGet(Y, X) & AMask) >> AShift) < 10)
                    {
                        ulandutils_LandPixelSet(Y, X, (ExplosionBorderColor & ~AMask) | (64 << AShift));
                    }
                    else
                    {
                        ulandutils_LandPixelSet(Y, X, (((((((((ulandutils_LandPixelGet(Y, X) & RMask) >> RShift) * 3) / 4) + (((ExplosionBorderColor & RMask) >> RShift) / 4)) & 0xff) << RShift) | (((((((ulandutils_LandPixelGet(Y, X) & GMask) >> GShift) * 3) / 4) + (((ExplosionBorderColor & GMask) >> GShift) / 4)) & 0xff) << GShift)) | (((((((ulandutils_LandPixelGet(Y, X) & BMask) >> BShift) * 3) / 4) + (((ExplosionBorderColor & BMask) >> BShift) / 4)) & 0xff) << BShift)) | (0xff << AShift));
                    }
                }
            }
        }
    }
    else
    {
        if((((((((cReducedQuality & rqBlurryLand) == 0) && ((ulandutils_LandPixelGet(Y, X) & AMask) == AMask)) && ((ulandutils_LandGet(Y, X) & (lfDamaged | lfBasic)) == lfBasic)) && (Y > (topY + 1))) && (Y < (LAND_HEIGHT - 2))) && (X > (leftX + 1))) && (X < (rightX - 1)))
        {
            if(((((ulandutils_LandGet(Y, X - 1) & lfDamaged) != 0) && ((ulandutils_LandGet(Y + 1, X) & lfDamaged) != 0)) || ((ulandutils_LandGet(Y - 1, X) & lfDamaged) != 0)) || (((ulandutils_LandGet(Y, X + 1) & lfDamaged) != 0) && (((ulandutils_LandGet(Y - 1, X) & lfDamaged) != 0) || ((ulandutils_LandGet(Y + 1, X) & lfDamaged) != 0))))
            {
                ulandutils_LandPixelSet(Y, X, ((((((((ulandutils_LandPixelGet(Y, X) & RMask) >> RShift) / 2) + (((ExplosionBorderColor & RMask) >> RShift) / 2)) & 0xff) << RShift) | ((((((ulandutils_LandPixelGet(Y, X) & GMask) >> GShift) / 2) + (((ExplosionBorderColor & GMask) >> GShift) / 2)) & 0xff) << GShift)) | ((((((ulandutils_LandPixelGet(Y, X) & BMask) >> BShift) / 2) + (((ExplosionBorderColor & BMask) >> BShift) / 2)) & 0xff) << BShift)) | (0xff << AShift));
            }
            else
            {
                if(((((((((((ulandutils_LandGet(Y, X - 1) & lfDamaged) != 0) && ((ulandutils_LandGet(Y + 1, X - 1) & lfDamaged) != 0)) && ((ulandutils_LandGet(Y + 2, X) & lfDamaged) != 0)) || ((((ulandutils_LandGet(Y, X - 1) & lfDamaged) != 0) && ((ulandutils_LandGet(Y - 1, X - 1) & lfDamaged) != 0)) && ((ulandutils_LandGet(Y - 2, X) & lfDamaged) != 0))) || ((((ulandutils_LandGet(Y, X + 1) & lfDamaged) != 0) && ((ulandutils_LandGet(Y + 1, X + 1) & lfDamaged) != 0)) && ((ulandutils_LandGet(Y + 2, X) & lfDamaged) != 0))) || ((((ulandutils_LandGet(Y, X + 1) & lfDamaged) != 0) && ((ulandutils_LandGet(Y - 1, X + 1) & lfDamaged) != 0)) && ((ulandutils_LandGet(Y - 2, X) & lfDamaged) != 0))) || ((((ulandutils_LandGet(Y + 1, X) & lfDamaged) != 0) && ((ulandutils_LandGet(Y + 1, X + 1) & lfDamaged) != 0)) && ((ulandutils_LandGet(Y, X + 2) & lfDamaged) != 0))) || ((((ulandutils_LandGet(Y - 1, X) & lfDamaged) != 0) && ((ulandutils_LandGet(Y - 1, X + 1) & lfDamaged) != 0)) && ((ulandutils_LandGet(Y, X + 2) & lfDamaged) != 0))) || ((((ulandutils_LandGet(Y + 1, X) & lfDamaged) != 0) && ((ulandutils_LandGet(Y + 1, X - 1) & lfDamaged) != 0)) && ((ulandutils_LandGet(Y, X - 2) & lfDamaged) != 0))) || ((((ulandutils_LandGet(Y - 1, X) & lfDamaged) != 0) && ((ulandutils_LandGet(Y - 1, X - 1) & lfDamaged) != 0)) && ((ulandutils_LandGet(Y, X - 2) & lfDamaged) != 0)))
                {
                    ulandutils_LandPixelSet(Y, X, (((((((((ulandutils_LandPixelGet(Y, X) & RMask) >> RShift) * 3) / 4) + (((ExplosionBorderColor & RMask) >> RShift) / 4)) & 0xff) << RShift) | (((((((ulandutils_LandPixelGet(Y, X) & GMask) >> GShift) * 3) / 4) + (((ExplosionBorderColor & GMask) >> GShift) / 4)) & 0xff) << GShift)) | (((((((ulandutils_LandPixelGet(Y, X) & BMask) >> BShift) * 3) / 4) + (((ExplosionBorderColor & BMask) >> BShift) / 4)) & 0xff) << BShift)) | (0xff << AShift));
                }
            }
        }
    }
};
boolean ulandgraphics_SweepDirty()
{
    boolean sweepdirty_result;
    LongInt x;
    LongInt y;
    LongInt xx;
    LongInt yy;
    LongInt ty;
    LongInt tx;
    boolean bRes;
    boolean resweep;
    boolean recheck;
    bRes = false;
    recheck = true;
    while(recheck)
    {
        recheck = false;
        {y = 0;
         LongInt y__end__ = (LAND_HEIGHT / 32) - 1;
         if (y <= y__end__) do {
                                   {x = 0;
                                    LongInt x__end__ = (LAND_WIDTH / 32) - 1;
                                    if (x <= x__end__) do {
                                                              if(LandDirty[y][x] == 1)
                                                              {
                                                                  resweep = true;
                                                                  ty = y * 32;
                                                                  tx = x * 32;
                                                                  while(resweep)
                                                                  {
                                                                      resweep = false;
                                                                      {yy = ty;
                                                                       LongInt yy__end__ = ty + 31;
                                                                       if (yy <= yy__end__) do {
                                                                                                   {xx = tx;
                                                                                                    LongInt xx__end__ = tx + 31;
                                                                                                    if (xx <= xx__end__) do {
                                                                                                                                if(ulandgraphics_Despeckle(xx, yy))
                                                                                                                                {
                                                                                                                                    bRes = true;
                                                                                                                                    resweep = true;
                                                                                                                                    if((yy == ty) && (y > 0))
                                                                                                                                    {
                                                                                                                                        LandDirty[y - 1][x] = 1;
                                                                                                                                        recheck = true;
                                                                                                                                    }
                                                                                                                                    else
                                                                                                                                    {
                                                                                                                                        if((yy == (ty + 31)) && (y < ((LAND_HEIGHT / 32) - 1)))
                                                                                                                                        {
                                                                                                                                            LandDirty[y + 1][x] = 1;
                                                                                                                                            recheck = true;
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                    if((xx == tx) && (x > 0))
                                                                                                                                    {
                                                                                                                                        LandDirty[y][x - 1] = 1;
                                                                                                                                        recheck = true;
                                                                                                                                    }
                                                                                                                                    else
                                                                                                                                    {
                                                                                                                                        if((xx == (tx + 31)) && (x < ((LAND_WIDTH / 32) - 1)))
                                                                                                                                        {
                                                                                                                                            LandDirty[y][x + 1] = 1;
                                                                                                                                            recheck = true;
                                                                                                                                        }
                                                                                                                                    }
                                                                                                                                }
                                                                                                                            } while(xx++ != xx__end__);}
                                                                                               } while(yy++ != yy__end__);}
                                                                  }
                                                              }
                                                          } while(x++ != x__end__);}
                               } while(y++ != y__end__);}
    }
    if((cReducedQuality & rqBlurryLand) == 0)
    {
        {y = 0;
         LongInt y__end__ = (LAND_HEIGHT / 32) - 1;
         if (y <= y__end__) do {
                                   {x = 0;
                                    LongInt x__end__ = (LAND_WIDTH / 32) - 1;
                                    if (x <= x__end__) do {
                                                              if(LandDirty[y][x] != 0)
                                                              {
                                                                  ty = y * 32;
                                                                  tx = x * 32;
                                                                  {yy = ty;
                                                                   LongInt yy__end__ = ty + 31;
                                                                   if (yy <= yy__end__) do {
                                                                                               {xx = tx;
                                                                                                LongInt xx__end__ = tx + 31;
                                                                                                if (xx <= xx__end__) do {
                                                                                                                            ulandgraphics_Smooth(xx, yy);
                                                                                                                        } while(xx++ != xx__end__);}
                                                                                           } while(yy++ != yy__end__);}
                                                              }
                                                          } while(x++ != x__end__);}
                               } while(y++ != y__end__);}
    }
    {y = 0;
     LongInt y__end__ = (LAND_HEIGHT / 32) - 1;
     if (y <= y__end__) do {
                               {x = 0;
                                LongInt x__end__ = (LAND_WIDTH / 32) - 1;
                                if (x <= x__end__) do {
                                                          if(LandDirty[y][x] != 0)
                                                          {
                                                              LandDirty[y][x] = 0;
                                                              ty = y * 32;
                                                              tx = x * 32;
                                                              ulandtexture_UpdateLandTexture(tx, 32, ty, 32, false);
                                                          }
                                                      } while(x++ != x__end__);}
                           } while(y++ != y__end__);}
    sweepdirty_result = bRes;
    return sweepdirty_result;
};
boolean ulandgraphics_CheckLandValue(LongInt X,LongInt Y,Word LandFlag)
{
    boolean checklandvalue_result;
    checklandvalue_result = (((X & LAND_WIDTH_MASK) != 0) || ((Y & LAND_HEIGHT_MASK) != 0)) || ((ulandutils_LandGet(Y, X) & LandFlag) == 0);
    return checklandvalue_result;
};
LongWord ulandgraphics_LandBackPixel(LongInt x,LongInt y)
{
    LongWord landbackpixel_result;
    PLongWordArray p;
    if(LandBackSurface == NULL)
    {
        landbackpixel_result = 0;
    }
    else
    {
        p = LandBackSurface->pixels;
        landbackpixel_result = (*p)[(LandBackSurface->w * (y % LandBackSurface->h)) + (x % LandBackSurface->w)];
    }
    return landbackpixel_result;
};
void ulandgraphics_DrawLine(LongInt X1,LongInt Y1,LongInt X2,LongInt Y2,LongWord Color)
{
    LongInt eX;
    LongInt eY;
    LongInt dX;
    LongInt dY;
    LongInt i;
    LongInt sX;
    LongInt sY;
    LongInt x;
    LongInt y;
    LongInt d;
    eX = 0;
    eY = 0;
    dX = X2 - X1;
    dY = Y2 - Y1;
    if(dX > 0)
    {
        sX = 1;
    }
    else
    {
        if(dX < 0)
        {
            sX = -1;
            dX = -dX;
        }
        else
        {
            sX = dX;
        }
    }
    if(dY > 0)
    {
        sY = 1;
    }
    else
    {
        if(dY < 0)
        {
            sY = -1;
            dY = -dY;
        }
        else
        {
            sY = dY;
        }
    }
    if(dX > dY)
    {
        d = dX;
    }
    else
    {
        d = dY;
    }
    x = X1;
    y = Y1;
    {i = 0;
     LongInt i__end__ = d;
     if (i <= i__end__) do {
                               eX += dX;
                               eY += dY;
                               if(eX > d)
                               {
                                   eX -= d;
                                   x += sX;
                               }
                               if(eY > d)
                               {
                                   eY -= d;
                                   y += sY;
                               }
                               if(((x & LAND_WIDTH_MASK) == 0) && ((y & LAND_HEIGHT_MASK) == 0))
                               {
                                   ulandutils_LandSet(y, x, Color);
                               }
                           } while(i++ != i__end__);}
};
LongWord ulandgraphics_DrawDots(LongInt x,LongInt y,LongInt xx,LongInt yy,LongWord Color)
{
    LongWord drawdots_result;
    drawdots_result = 0;
    if(((((x + xx) & LAND_WIDTH_MASK) == 0) && (((y + yy) & LAND_HEIGHT_MASK) == 0)) && (ulandutils_LandGet(y + yy, x + xx) != Color))
    {
        ++drawdots_result;
        ulandutils_LandSet(y + yy, x + xx, Color);
    }
    if(((((x + xx) & LAND_WIDTH_MASK) == 0) && (((y - yy) & LAND_HEIGHT_MASK) == 0)) && (ulandutils_LandGet(y - yy, x + xx) != Color))
    {
        ++drawdots_result;
        ulandutils_LandSet(y - yy, x + xx, Color);
    }
    if(((((x - xx) & LAND_WIDTH_MASK) == 0) && (((y + yy) & LAND_HEIGHT_MASK) == 0)) && (ulandutils_LandGet(y + yy, x - xx) != Color))
    {
        ++drawdots_result;
        ulandutils_LandSet(y + yy, x - xx, Color);
    }
    if(((((x - xx) & LAND_WIDTH_MASK) == 0) && (((y - yy) & LAND_HEIGHT_MASK) == 0)) && (ulandutils_LandGet(y - yy, x - xx) != Color))
    {
        ++drawdots_result;
        ulandutils_LandSet(y - yy, x - xx, Color);
    }
    if(((((x + yy) & LAND_WIDTH_MASK) == 0) && (((y + xx) & LAND_HEIGHT_MASK) == 0)) && (ulandutils_LandGet(y + xx, x + yy) != Color))
    {
        ++drawdots_result;
        ulandutils_LandSet(y + xx, x + yy, Color);
    }
    if(((((x + yy) & LAND_WIDTH_MASK) == 0) && (((y - xx) & LAND_HEIGHT_MASK) == 0)) && (ulandutils_LandGet(y - xx, x + yy) != Color))
    {
        ++drawdots_result;
        ulandutils_LandSet(y - xx, x + yy, Color);
    }
    if(((((x - yy) & LAND_WIDTH_MASK) == 0) && (((y + xx) & LAND_HEIGHT_MASK) == 0)) && (ulandutils_LandGet(y + xx, x - yy) != Color))
    {
        ++drawdots_result;
        ulandutils_LandSet(y + xx, x - yy, Color);
    }
    if(((((x - yy) & LAND_WIDTH_MASK) == 0) && (((y - xx) & LAND_HEIGHT_MASK) == 0)) && (ulandutils_LandGet(y - xx, x - yy) != Color))
    {
        ++drawdots_result;
        ulandutils_LandSet(y - xx, x - yy, Color);
    }
    return drawdots_result;
};
LongWord ulandgraphics_DrawLines(LongInt X1,LongInt Y1,LongInt X2,LongInt Y2,LongInt XX,LongInt YY,LongWord color)
{
    LongWord drawlines_result;
    LongInt eX;
    LongInt eY;
    LongInt dX;
    LongInt dY;
    LongInt i;
    LongInt sX;
    LongInt sY;
    LongInt x;
    LongInt y;
    LongInt d;
    boolean f;
    eX = 0;
    eY = 0;
    dX = X2 - X1;
    dY = Y2 - Y1;
    drawlines_result = 0;
    if(dX > 0)
    {
        sX = 1;
    }
    else
    {
        if(dX < 0)
        {
            sX = -1;
            dX = -dX;
        }
        else
        {
            sX = dX;
        }
    }
    if(dY > 0)
    {
        sY = 1;
    }
    else
    {
        if(dY < 0)
        {
            sY = -1;
            dY = -dY;
        }
        else
        {
            sY = dY;
        }
    }
    if(dX > dY)
    {
        d = dX;
    }
    else
    {
        d = dY;
    }
    x = X1;
    y = Y1;
    {i = 0;
     LongInt i__end__ = d;
     if (i <= i__end__) do {
                               eX += dX;
                               eY += dY;
                               f = eX > d;
                               if(f)
                               {
                                   eX -= d;
                                   x += sX;
                                   drawlines_result += ulandgraphics_DrawDots(x, y, XX, YY, color);
                               }
                               if(eY > d)
                               {
                                   eY -= d;
                                   y += sY;
                                   f = true;
                                   drawlines_result += ulandgraphics_DrawDots(x, y, XX, YY, color);
                               }
                               if(!f)
                               {
                                   drawlines_result += ulandgraphics_DrawDots(x, y, XX, YY, color);
                               }
                           } while(i++ != i__end__);}
    return drawlines_result;
};
LongWord ulandgraphics_DrawThickLine(LongInt X1,LongInt Y1,LongInt X2,LongInt Y2,LongInt radius,LongWord color)
{
    LongWord drawthickline_result;
    LongInt dx;
    LongInt dy;
    LongInt d;
    drawthickline_result = 0;
    dx = 0;
    dy = radius;
    d = 3 - (2 * radius);
    while(dx < dy)
    {
        drawthickline_result += ulandgraphics_DrawLines(X1, Y1, X2, Y2, dx, dy, color);
        if(d < 0)
        {
            d = (d + (4 * dx)) + 6;
        }
        else
        {
            d = (d + (4 * (dx - dy))) + 10;
            --dy;
        }
        ++dx;
    }
    if(dx == dy)
    {
        drawthickline_result += ulandgraphics_DrawLines(X1, Y1, X2, Y2, dx, dy, color);
    }
    return drawthickline_result;
};
void ulandgraphics_DumpLandToLog(LongInt x,LongInt y,LongInt r)
{
    LongInt xx;
    LongInt yy;
    LongInt dx;
    string255 s;
    s.s[0] = ((char)(r * 2) + 1);
    {yy = y - r;
     LongInt yy__end__ = y + r;
     if (yy <= yy__end__) do {
                                 {dx = 0;
                                  LongInt dx__end__ = r * 2;
                                  if (dx <= dx__end__) do {
                                                              xx = (dx - r) + x;
                                                              if((xx == x) && (yy == y))
                                                              {
                                                                  s.s[dx + 1] = 0x58;
                                                              }
                                                              else
                                                              {
                                                                  if(ulandutils_LandGet(yy, xx) > 255)
                                                                  {
                                                                      s.s[dx + 1] = 0x4f;
                                                                  }
                                                                  else
                                                                  {
                                                                      if(ulandutils_LandGet(yy, xx) > 0)
                                                                      {
                                                                          s.s[dx + 1] = 0x2a;
                                                                      }
                                                                      else
                                                                      {
                                                                          s.s[dx + 1] = 0x2e;
                                                                      }
                                                                  }
                                                              }
                                                          } while(dx++ != dx__end__);}
                                 uutils_AddFileLog(_strconcat(__str10, s));
                             } while(yy++ != yy__end__);}
};
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const fillType enumvar)
{
    switch(enumvar){
    case nullPixel:
        return fpcrtl_make_string("nullPixel");
        break;
    case backgroundPixel:
        return fpcrtl_make_string("backgroundPixel");
        break;
    case ebcPixel:
        return fpcrtl_make_string("ebcPixel");
        break;
    case icePixel:
        return fpcrtl_make_string("icePixel");
        break;
    case addNotHHObj:
        return fpcrtl_make_string("addNotHHObj");
        break;
    case removeNotHHObj:
        return fpcrtl_make_string("removeNotHHObj");
        break;
    case addHH:
        return fpcrtl_make_string("addHH");
        break;
    case removeHH:
        return fpcrtl_make_string("removeHH");
        break;
    case setCurrentHog:
        return fpcrtl_make_string("setCurrentHog");
        break;
    case removeCurrentHog:
        return fpcrtl_make_string("removeCurrentHog");
        break;
    default: assert(0);
        return fpcrtl_make_string("nonsense");
    }
}