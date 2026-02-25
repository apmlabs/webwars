#include "fpcrtl.h"

#include "uLandObjects.h"
#include "uStore.h"
#include "uConsts.h"
#include "uConsole.h"
#include "uRandom.h"
#include "uSound.h"
#include "uTypes.h"
#include "uVariables.h"
#include "uDebug.h"
#include "uUtils.h"
#include "uPhysFSLayer.h"
#include "uRenderUtils.h"
#include "uLandUtils.h"
static const string255 __str55 = STRINIT("Adding spray objects...");
static const string255 __str54 = STRINIT("Adding theme objects...");
static const string255 __str53 = STRINIT("rq-sky");
static const string255 __str52 = STRINIT("sd-flakes");
static const string255 __str51 = STRINIT("sd-clouds");
static const string255 __str50 = STRINIT("sd-water-opacity");
static const string255 __str49 = STRINIT("sd-water-bottom");
static const string255 __str48 = STRINIT("sd-water-top");
static const string255 __str47 = STRINIT("rope-layers");
static const string255 __str46 = STRINIT("rope-step");
static const string255 __str45 = STRINIT("snow");
static const string255 __str44 = STRINIT("ice");
static const string255 __str43 = STRINIT("flatten-clouds");
static const string255 __str42 = STRINIT("flatten-flakes");
static const string255 __str41 = STRINIT("flakes");
static const string255 __str40 = STRINIT("sd-water-animation");
static const string255 __str39 = STRINIT("water-animation");
static const string255 __str38 = STRINIT("spray");
static const string255 __str37 = STRINIT("Broken theme. Object's overlay count should be no more than ");
static const string255 __str36 = STRINIT("Broken theme. Duplicate overlays declaration for object ");
static const string255 __str35 = STRINIT("overlays");
static const string255 __str34 = STRINIT("Broken theme. Object's anchor rectangle count should be no more than ");
static const string255 __str33 = STRINIT("Broken theme. Duplicate anchors declaration for object ");
static const string255 __str32 = STRINIT("anchors");
static const string255 __str31 = STRINIT("Broken theme. Object's outland rectangle count should be no more than ");
static const string255 __str30 = STRINIT("Broken theme. Object's inland rectangle count should be no more than ");
static const string255 __str29 = STRINIT(").");
static const string255 __str28 = STRINIT(" (it was ");
static const string255 __str27 = STRINIT("Broken theme. Object's max. count should be between 1 and ");
static const string255 __str26 = STRINIT("_mask");
static const string255 __str25 = STRINIT("object");
static const string255 __str24 = STRINIT("clouds");
static const string255 __str23 = STRINIT("fallback-sd-music");
static const string255 __str22 = STRINIT("fallback-music");
static const string255 __str21 = STRINIT("sd-music");
static const string255 __str20 = STRINIT("music");
static const string255 __str19 = STRINIT("water-opacity");
static const string255 __str18 = STRINIT("water-bottom");
static const string255 __str17 = STRINIT("water-top");
static const string255 __str16 = STRINIT("border");
static const string255 __str15 = STRINIT("sd-tint");
static const string255 __str14 = STRINIT("sky");
static const string255 __str13 = STRINIT("Error loading theme. File could not be opened: ");
static const string255 __str12 = STRINIT("Reading objects info...");
static const string255 __str11 = STRINIT(") > Height (");
static const string255 __str10 = STRINIT("Broken theme. Object's rectangle exceeds image: y + h (");
static const string255 __str9 = STRINIT(") > Width (");
static const string255 __str8 = STRINIT(" + ");
static const string255 __str7 = STRINIT("Broken theme. Object's rectangle exceeds image: x + w (");
static const string255 __str6 = STRINIT("Girder");
static const string255 __str5 = STRINIT("AddRect: overflow");
static const string255 __str4 = STRINIT("Land object overlay should be 32bit");
static const string255 __str3 = STRINIT("Generating overlay collision info... ");
static const string255 __str2 = STRINIT("Land object should be 32bit");
static const string255 __str1 = STRINIT("SDL_LockSurface");
static const string255 __str0 = STRINIT("Generating collision info... ");
enum{MaxRects = 512};
enum{MAXOBJECTRECTS = 16};
enum{MAXTHEMEOBJECTS = 32};
static const string255 cThemeCFGFilename = STRINIT("theme.cfg");
typedef LongWord * PLongWord;
typedef TSDL_Rect TRectsArray[(MaxRects + 1)];
typedef TRectsArray * PRectArray;
typedef struct __TThemeObjectOverlay {
            TPoint Position;
            PSDL_Surface Surf;
            LongWord Width;
            LongWord Height;
        } TThemeObjectOverlay;
typedef struct __TThemeObject {
            shortstring Name;
            PSDL_Surface Surf;
            PSDL_Surface Mask;
            TSDL_Rect inland[MAXOBJECTRECTS];
            TSDL_Rect outland[MAXOBJECTRECTS];
            TSDL_Rect anchors[MAXOBJECTRECTS];
            TThemeObjectOverlay overlays[MAXOBJECTRECTS];
            LongInt inrectcnt;
            LongInt outrectcnt;
            LongInt anchorcnt;
            LongInt overlaycnt;
            LongWord Width;
            LongWord Height;
            LongWord Maxcnt;
        } TThemeObject;
typedef struct __TThemeObjects {
            LongInt Count;
            TThemeObject objs[MAXTHEMEOBJECTS];
        } TThemeObjects;
typedef struct __TSprayObject {
            PSDL_Surface Surf;
            LongWord Width;
            LongWord Height;
            LongWord Maxcnt;
        } TSprayObject;
typedef struct __TSprayObjects {
            LongInt Count;
            TSprayObject objs[MAXTHEMEOBJECTS];
        } TSprayObjects;
static PRectArray Rects;
static LongWord RectCount;
static TThemeObjects ThemeObjects;
static TSprayObjects SprayObjects;
void ulandobjects_SetLand(LongInt y,LongInt x,LongWord Pixel)
{
    if((AMask & Pixel) == 0)
    {
        ulandutils_LandSet(y, x, 0);
    }
    else
    {
        if(((((Pixel & AMask) > 0) && ((Pixel & RMask) > 0)) && ((Pixel & GMask) > 0)) && ((Pixel & BMask) > 0))
        {
            ulandutils_LandSet(y, x, lfObject);
        }
        else
        {
            if(((((Pixel & AMask) > 0) && ((Pixel & RMask) == 0)) && ((Pixel & GMask) == 0)) && ((Pixel & BMask) == 0))
            {
                ulandutils_LandSet(y, x, lfBasic);
                disableLandBack = false;
            }
            else
            {
                if(((((Pixel & AMask) > 0) && ((Pixel & RMask) > 0)) && ((Pixel & GMask) == 0)) && ((Pixel & BMask) == 0))
                {
                    ulandutils_LandSet(y, x, lfIndestructible);
                }
                else
                {
                    if(((((Pixel & AMask) > 0) && ((Pixel & RMask) == 0)) && ((Pixel & GMask) == 0)) && ((Pixel & BMask) > 0))
                    {
                        ulandutils_LandSet(y, x, lfObject | lfIce);
                    }
                    else
                    {
                        if(((((Pixel & AMask) > 0) && ((Pixel & RMask) == 0)) && ((Pixel & GMask) > 0)) && ((Pixel & BMask) == 0))
                        {
                            ulandutils_LandSet(y, x, lfObject | lfBouncy);
                        }
                    }
                }
            }
        }
    }
};
void ulandobjects_BlitImageAndGenerateCollisionInfo_4(LongWord cpX,LongWord cpY,LongWord Width,PSDL_Surface Image)
{
    ulandobjects_BlitImageAndGenerateCollisionInfo_6(cpX, cpY, Width, Image, 0, false);
};
void ulandobjects_BlitImageAndGenerateCollisionInfo_5(LongWord cpX,LongWord cpY,LongWord Width,PSDL_Surface Image,Word LandFlags)
{
    ulandobjects_BlitImageAndGenerateCollisionInfo_6(cpX, cpY, Width, Image, LandFlags, false);
};
LongWord ulandobjects_LerpByte(Byte src,Byte dst,LongWord l)
{
    LongWord lerpbyte_result;
    lerpbyte_result = (((255 - l) * src) + (l * dst)) / 255;
    return lerpbyte_result;
};
void ulandobjects_BlitImageAndGenerateCollisionInfo_6(LongWord cpX,LongWord cpY,LongWord Width,PSDL_Surface Image,Word LandFlags,boolean Flip)
{
    PLongWordArray p;
    PLongWord pLandColor;
    LongWord alpha;
    LongWord color;
    LongWord landColor;
    LongWord x;
    LongWord y;
    LongInt bpp;
    uconsole_WriteToConsole(__str0);
    if(sdlh_SDL_MustLock(Image))
    {
        if(udebug_SDLCheck(SDL_LockSurface(Image) >= 0, __str1, true))
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
    }
    if(Width == 0)
    {
        Width = Image->w;
    }
    p = Image->pixels;
    {y = 0;
     LongWord y__end__ = ((int)(Image->h) - 1);
     if (y <= y__end__) do {
                               {x = 0;
                                LongWord x__end__ = ((int)(Width) - 1);
                                if (x <= x__end__) do {
                                                          if(Flip)
                                                          {
                                                              color = (*p)[((int)(Image->w) - 1) - x];
                                                          }
                                                          else
                                                          {
                                                              color = (*p)[x];
                                                          }
                                                          if((cReducedQuality & rqBlurryLand) == 0)
                                                          {
                                                              pLandColor = &((*ulandutils_LandPixelRow(cpY + y))[cpX + x]);
                                                          }
                                                          else
                                                          {
                                                              pLandColor = &((*ulandutils_LandPixelRow((cpY + y) / 2))[(cpX + x) / 2]);
                                                          }
                                                          landColor = (*pLandColor);
                                                          alpha = (landColor & AMask) >> AShift;
                                                          if(((color & AMask) != 0) && (alpha != 255))
                                                          {
                                                              if(alpha == 0)
                                                              {
                                                                  (*pLandColor) = color;
                                                              }
                                                              else
                                                              {
                                                                  (*pLandColor) = (((ulandobjects_LerpByte((color & RMask) >> RShift, (landColor & RMask) >> RShift, alpha) << RShift) | (ulandobjects_LerpByte((color & GMask) >> GShift, (landColor & GMask) >> GShift, alpha) << GShift)) | (ulandobjects_LerpByte((color & BMask) >> BShift, (landColor & BMask) >> BShift, alpha) << BShift)) | (ulandobjects_LerpByte(alpha, 255, (color & AMask) >> AShift) << AShift);
                                                              }
                                                          }
                                                          if(((color & AMask) != 0) && (ulandutils_LandGet(cpY + y, cpX + x) <= lfAllObjMask))
                                                          {
                                                              ulandutils_LandSet(cpY + y, cpX + x, lfObject | LandFlags);
                                                          }
                                                      } while(x++ != x__end__);}
                               p = ((PLongWordArray)&((*p)[Image->pitch >> 2]));
                           } while(y++ != y__end__);}
    if(sdlh_SDL_MustLock(Image))
    {
        SDL_UnlockSurface(Image);
    }
    uconsole_WriteLnToConsole(msgOK);
};
void ulandobjects_BlitOverlayAndGenerateCollisionInfo(LongWord cpX,LongWord cpY,PSDL_Surface Image)
{
    PLongWordArray p;
    PLongWord pLandColor;
    LongWord x;
    LongWord y;
    LongWord alpha;
    LongWord color;
    LongWord landColor;
    uconsole_WriteToConsole(__str3);
    if(sdlh_SDL_MustLock(Image))
    {
        if(udebug_SDLCheck(SDL_LockSurface(Image) >= 0, __str1, true))
        {
            return;
        }
    }
    if(udebug_checkFails((*Image->format).BytesPerPixel == 4, __str4, true) && sdlh_SDL_MustLock(Image))
    {
        SDL_UnlockSurface(Image);
    }
    p = Image->pixels;
    {y = 0;
     LongWord y__end__ = ((int)(Image->h) - 1);
     if (y <= y__end__) do {
                               {x = 0;
                                LongWord x__end__ = ((int)(Image->w) - 1);
                                if (x <= x__end__) do {
                                                          color = (*p)[x];
                                                          if((color & AMask) != 0)
                                                          {
                                                              if((cReducedQuality & rqBlurryLand) == 0)
                                                              {
                                                                  pLandColor = &((*ulandutils_LandPixelRow(cpY + y))[cpX + x]);
                                                              }
                                                              else
                                                              {
                                                                  pLandColor = &((*ulandutils_LandPixelRow((cpY + y) / 2))[(cpX + x) / 2]);
                                                              }
                                                              alpha = (color & AMask) >> AShift;
                                                              if((alpha != 0xff) && ((*pLandColor) != 0))
                                                              {
                                                                  landColor = (*pLandColor);
                                                                  color = (((ulandobjects_LerpByte((landColor & RMask) >> RShift, (color & RMask) >> RShift, alpha) << RShift) | (ulandobjects_LerpByte((landColor & GMask) >> GShift, (color & GMask) >> GShift, alpha) << GShift)) | (ulandobjects_LerpByte((landColor & BMask) >> BShift, (color & BMask) >> BShift, alpha) << BShift)) | (ulandobjects_LerpByte(alpha, 255, (landColor & AMask) >> AShift) << AShift);
                                                              }
                                                              (*pLandColor) = color;
                                                              if(ulandutils_LandGet(cpY + y, cpX + x) <= lfAllObjMask)
                                                              {
                                                                  ulandutils_LandSet(cpY + y, cpX + x, lfObject);
                                                              }
                                                          }
                                                      } while(x++ != x__end__);}
                               p = ((PLongWordArray)&((*p)[Image->pitch >> 2]));
                           } while(y++ != y__end__);}
    if(sdlh_SDL_MustLock(Image))
    {
        SDL_UnlockSurface(Image);
    }
    uconsole_WriteLnToConsole(msgOK);
};
void ulandobjects_BlitImageUsingMask(LongWord cpX,LongWord cpY,PSDL_Surface Image,PSDL_Surface Mask)
{
    PLongWordArray p;
    PLongWordArray mp;
    PLongWord pLandColor;
    LongWord alpha;
    LongWord color;
    LongWord landColor;
    LongWord x;
    LongWord y;
    LongInt bpp;
    uconsole_WriteToConsole(__str0);
    if(sdlh_SDL_MustLock(Image))
    {
        if(udebug_SDLCheck(SDL_LockSurface(Image) >= 0, __str1, true))
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
    }
    p = Image->pixels;
    mp = Mask->pixels;
    {y = 0;
     LongWord y__end__ = ((int)(Image->h) - 1);
     if (y <= y__end__) do {
                               {x = 0;
                                LongWord x__end__ = ((int)(Image->w) - 1);
                                if (x <= x__end__) do {
                                                          color = (*p)[x];
                                                          if((cReducedQuality & rqBlurryLand) == 0)
                                                          {
                                                              pLandColor = &((*ulandutils_LandPixelRow(cpY + y))[cpX + x]);
                                                          }
                                                          else
                                                          {
                                                              pLandColor = &((*ulandutils_LandPixelRow((cpY + y) / 2))[(cpX + x) / 2]);
                                                          }
                                                          landColor = (*pLandColor);
                                                          alpha = (landColor & AMask) >> AShift;
                                                          if(((color & AMask) != 0) && (alpha != 255))
                                                          {
                                                              if(alpha == 0)
                                                              {
                                                                  (*pLandColor) = color;
                                                              }
                                                              else
                                                              {
                                                                  (*pLandColor) = (((ulandobjects_LerpByte((color & RMask) >> RShift, (landColor & RMask) >> RShift, alpha) << RShift) | (ulandobjects_LerpByte((color & GMask) >> GShift, (landColor & GMask) >> GShift, alpha) << GShift)) | (ulandobjects_LerpByte((color & BMask) >> BShift, (landColor & BMask) >> BShift, alpha) << BShift)) | (ulandobjects_LerpByte(alpha, 255, (color & AMask) >> AShift) << AShift);
                                                              }
                                                          }
                                                          if((ulandutils_LandGet(cpY + y, cpX + x) <= lfAllObjMask) || ((ulandutils_LandGet(cpY + y, cpX + x) & lfObject) != 0))
                                                          {
                                                              ulandobjects_SetLand(cpY + y, cpX + x, (*mp)[x]);
                                                          }
                                                      } while(x++ != x__end__);}
                               p = ((PLongWordArray)&((*p)[Image->pitch >> 2]));
                               mp = ((PLongWordArray)&((*mp)[Mask->pitch >> 2]));
                           } while(y++ != y__end__);}
    if(sdlh_SDL_MustLock(Image))
    {
        SDL_UnlockSurface(Image);
    }
    uconsole_WriteLnToConsole(msgOK);
};
void ulandobjects_AddRect(LongInt x1,LongInt y1,LongInt w1,LongInt h1)
{
    {
        (*Rects)[RectCount].x = x1;
        (*Rects)[RectCount].y = y1;
        (*Rects)[RectCount].w = w1;
        (*Rects)[RectCount].h = h1;
    }
    ++RectCount;
    udebug_checkFails(RectCount < MaxRects, __str5, true);
};
void ulandobjects_InitRects()
{
    RectCount = 0;
    fpcrtl_new(Rects);
};
void ulandobjects_FreeRects()
{
    fpcrtl_dispose(Rects);
};
boolean ulandobjects_CheckIntersect(LongInt x1,LongInt y1,LongInt w1,LongInt h1)
{
    boolean checkintersect_result;
    LongWord i;
    boolean res = false;
    i = 0;
    if(RectCount > 0)
    {
        do {
               {
                   res = ((((*Rects)[i].x < (x1 + w1)) && (x1 < ((*Rects)[i].x + (*Rects)[i].w))) && ((*Rects)[i].y < (y1 + h1))) && (y1 < ((*Rects)[i].y + (*Rects)[i].h));
               }
               ++i;
           } while(!((i == RectCount) || res));
    }
    checkintersect_result = res;
    return checkintersect_result;
};
LongWord ulandobjects_CountNonZeroz(LongInt x,LongInt y,LongInt h)
{
    LongWord countnonzeroz_result;
    LongInt i;
    LongWord lRes;
    lRes = 0;
    {i = y;
     LongInt i__end__ = ((int)(y + h) - 1);
     if (i <= i__end__) do {
                               if(ulandutils_LandGet(i, x) != 0)
                               {
                                   ++lRes;
                               }
                           } while(i++ != i__end__);}
    countnonzeroz_result = lRes;
    return countnonzeroz_result;
};
boolean ulandobjects_AddGirder(LongInt gX,PSDL_Surface (*girSurf))
{
    boolean addgirder_result;
    LongInt x1;
    LongInt x2;
    LongInt y;
    LongInt k;
    LongInt i;
    LongInt girderHeight;
    TSDL_Rect rr;
    boolean bRes;
    if((*girSurf) == NULL)
    {
        (*girSurf) = ustore_LoadDataImageAltPath(ptCurrTheme, ptGraphics, __str6, ((ifCritical | ifColorKey) | ifIgnoreCaps) | ifDigestAlpha);
    }
    girderHeight = (*girSurf)->h;
    y = topY + 150;
    do {
           y += 24;
           x1 = gX;
           x2 = gX;
           while((x1 > (leftX + 150)) && (ulandobjects_CountNonZeroz(x1, y, girderHeight) == 0))
           {
               x1 -= 2;
           }
           i = x1 - 12;
           do {
                  k = ulandobjects_CountNonZeroz(x1, y, girderHeight);
                  x1 -= 2;
              } while(!((((x1 < (leftX + 100)) || (k == 0)) || (k == girderHeight)) || (x1 < i)));
           x1 += 2;
           if(k == girderHeight)
           {
               while((x2 < (rightX - 100)) && (ulandobjects_CountNonZeroz(x2, y, girderHeight) == 0))
               {
                   x2 += 2;
               }
               i = x2 + 12;
               do {
                      x2 += 2;
                      k = ulandobjects_CountNonZeroz(x2, y, girderHeight);
                  } while(!(((((x2 >= (rightX - 150)) || (k == 0)) || (k == girderHeight)) || (x2 > i)) || ((x2 - x1) >= 900)));
               if(((((x2 < (rightX - 100)) && (k == girderHeight)) && ((x2 - x1) > 200)) && ((x2 - x1) < 900)) && !ulandobjects_CheckIntersect(x1 - 32, y - 64, (x2 - x1) + 64, 144))
               {
                   break;
               }
           }
           x1 = 0;
       } while(!(y > (LAND_HEIGHT - 125)));
    if(x1 > 0)
    {
        bRes = true;
        rr.x = x1;
        while(rr.x < x2)
        {
            if(cIce)
            {
                ulandobjects_BlitImageAndGenerateCollisionInfo_5(rr.x, y, uutils_Min(x2 - rr.x, (*girSurf)->w), (*girSurf), lfIce);
            }
            else
            {
                ulandobjects_BlitImageAndGenerateCollisionInfo_4(rr.x, y, uutils_Min(x2 - rr.x, (*girSurf)->w), (*girSurf));
            }
            rr.x += (*girSurf)->w;
        }
        ulandobjects_AddRect(x1 - 8, y - 32, (x2 - x1) + 16, 80);
    }
    else
    {
        bRes = false;
    }
    addgirder_result = bRes;
    return addgirder_result;
};
boolean ulandobjects_CheckLand(TSDL_Rect rect,LongWord dX,LongWord dY,LongWord Color)
{
    boolean checkland_result;
    LongInt tmpx;
    LongInt tmpx2;
    LongInt tmpy;
    LongInt tmpy2;
    LongInt bx;
    LongInt by;
    boolean bRes = true;
    rect.x += dX;
    rect.y += dY;
    bx = rect.x + rect.w;
    by = rect.y + rect.h;
    tmpx = rect.x;
    tmpx2 = bx;
    while((tmpx <= ((bx - (rect.w / 2)) - 1)) && bRes)
    {
        bRes = ((((((((rect.y & LAND_HEIGHT_MASK) == 0) && ((by & LAND_HEIGHT_MASK) == 0)) && ((tmpx & LAND_WIDTH_MASK) == 0)) && ((tmpx2 & LAND_WIDTH_MASK) == 0)) && (ulandutils_LandGet(rect.y, tmpx) == Color)) && (ulandutils_LandGet(by, tmpx) == Color)) && (ulandutils_LandGet(rect.y, tmpx2) == Color)) && (ulandutils_LandGet(by, tmpx2) == Color);
        ++tmpx;
        --tmpx2;
    }
    tmpy = rect.y + 1;
    tmpy2 = by - 1;
    while((tmpy <= ((by - (rect.h / 2)) - 1)) && bRes)
    {
        bRes = ((((((((tmpy & LAND_HEIGHT_MASK) == 0) && ((tmpy2 & LAND_HEIGHT_MASK) == 0)) && ((rect.x & LAND_WIDTH_MASK) == 0)) && ((bx & LAND_WIDTH_MASK) == 0)) && (ulandutils_LandGet(tmpy, rect.x) == Color)) && (ulandutils_LandGet(tmpy, bx) == Color)) && (ulandutils_LandGet(tmpy2, rect.x) == Color)) && (ulandutils_LandGet(tmpy2, bx) == Color);
        ++tmpy;
        --tmpy2;
    }
    checkland_result = bRes;
    return checkland_result;
};
boolean ulandobjects_CheckLandAny(TSDL_Rect rect,LongWord dX,LongWord dY,LongWord LandType)
{
    boolean checklandany_result;
    LongInt tmpx;
    LongInt tmpy;
    LongInt bx;
    LongInt by;
    rect.x += dX;
    rect.y += dY;
    bx = (rect.x + rect.w) - 1;
    by = (rect.y + rect.h) - 1;
    checklandany_result = false;
    if(((((rect.x & LAND_WIDTH_MASK) | (bx & LAND_WIDTH_MASK)) | (rect.y & LAND_HEIGHT_MASK)) | (by & LAND_HEIGHT_MASK)) == 0)
    {
        {tmpx = rect.x;
         LongInt tmpx__end__ = bx;
         if (tmpx <= tmpx__end__) do {
                                         if(((ulandutils_LandGet(rect.y, tmpx) & LandType) | (ulandutils_LandGet(by, tmpx) & LandType)) != 0)
                                         {
                                             checklandany_result = true;
                                             return checklandany_result;
                                         }
                                     } while(tmpx++ != tmpx__end__);}
        {tmpy = rect.y;
         LongInt tmpy__end__ = by;
         if (tmpy <= tmpy__end__) do {
                                         if(((ulandutils_LandGet(tmpy, rect.x) & LandType) | (ulandutils_LandGet(tmpy, bx) & LandType)) != 0)
                                         {
                                             checklandany_result = true;
                                             return checklandany_result;
                                         }
                                     } while(tmpy++ != tmpy__end__);}
    }
    return checklandany_result;
};
boolean ulandobjects_CheckCanPlace(LongWord x,LongWord y,TThemeObject (*Obj))
{
    boolean checkcanplace_result;
    LongWord i;
    boolean bRes;
    boolean anchored;
    TPoint overlayP1;
    TPoint overlayP2;
    {
        bRes = true;
        i = 0;
        while(bRes && (i < (*Obj).overlaycnt))
        {
            overlayP1.x = (*Obj).overlays[i].Position.x + x;
            overlayP1.y = (*Obj).overlays[i].Position.y + y;
            overlayP2.x = (overlayP1.x + (*Obj).overlays[i].Width) - 1;
            overlayP2.y = (overlayP1.y + (*Obj).overlays[i].Height) - 1;
            bRes = (((((LAND_WIDTH_MASK & overlayP1.x) | (LAND_HEIGHT_MASK & overlayP1.y)) | (LAND_WIDTH_MASK & overlayP2.x)) | (LAND_HEIGHT_MASK & overlayP2.y)) == 0) && !ulandobjects_CheckIntersect(overlayP1.x, overlayP1.y, (*Obj).overlays[i].Width, (*Obj).overlays[i].Height);
            ++i;
        }
        i = 0;
        while(bRes && (i < (*Obj).inrectcnt))
        {
            bRes = ulandobjects_CheckLand((*Obj).inland[i], x, y, lfBasic);
            ++i;
        }
        i = 0;
        while(bRes && (i < (*Obj).outrectcnt))
        {
            bRes = ulandobjects_CheckLand((*Obj).outland[i], x, y, 0);
            ++i;
        }
        if(bRes)
        {
            anchored = (*Obj).anchorcnt == 0;
            i = 0;
            while(i < (*Obj).anchorcnt)
            {
                anchored = ulandobjects_CheckLandAny((*Obj).anchors[i], x, y, lfLandMask);
                if(anchored)
                {
                    break;
                }
                ++i;
            }
            bRes = anchored;
        }
        if(bRes)
        {
            bRes = !ulandobjects_CheckIntersect(x, y, (*Obj).Width, (*Obj).Height);
        }
        checkcanplace_result = bRes;
    }
    return checkcanplace_result;
};
boolean ulandobjects_TryPut(TThemeObject (*Obj))
{
    boolean tryput_result;
    enum{MaxPointsIndex = 2047};
    LongWord x;
    LongWord y;
    typedef TPoint ar_tt[(MaxPointsIndex + 1)];
    ar_tt ar;
    LongWord cnt;
    LongWord i;
    LongWord ii;
    boolean bRes;
    tryput_result = false;
    cnt = 0;
    {
        if((*Obj).Maxcnt == 0)
        {
            return tryput_result;
        }
        x = leftX;
        do {
               y = topY + 32;
               do {
                      if((((((*Obj).inrectcnt > 0) && ((*Obj).inland[0].x == 0)) && ((*Obj).inland[0].y == 0)) && ((*Obj).inland[0].w == 0)) && ((*Obj).inland[0].h == 0))
                      {
                          y = LAND_HEIGHT - (*Obj).Height;
                      }
                      if(ulandobjects_CheckCanPlace(x, y, &((*Obj))))
                      {
                          ar[cnt].x = x;
                          ar[cnt].y = y;
                          if(cnt >= MaxPointsIndex)
                          {
                              y = LAND_HEIGHT;
                              x = LAND_WIDTH;
                          }
                          else
                          {
                              ++cnt;
                          }
                      }
                      y += 3;
                  } while(!(y >= (LAND_HEIGHT - (*Obj).Height)));
               x += urandom_GetRandom(6) + 3;
           } while(!(x >= (rightX - (*Obj).Width)));
        bRes = cnt != 0;
        if(bRes)
        {
            i = urandom_GetRandom(cnt);
            if((*Obj).Mask != NULL)
            {
                ulandobjects_BlitImageUsingMask(ar[i].x, ar[i].y, (*Obj).Surf, (*Obj).Mask);
            }
            else
            {
                ulandobjects_BlitImageAndGenerateCollisionInfo_4(ar[i].x, ar[i].y, 0, (*Obj).Surf);
            }
            ulandobjects_AddRect(ar[i].x, ar[i].y, (*Obj).Width, (*Obj).Height);
            ii = 0;
            while(ii < (*Obj).overlaycnt)
            {
                ulandobjects_BlitOverlayAndGenerateCollisionInfo(ar[i].x + (*Obj).overlays[ii].Position.x, ar[i].y + (*Obj).overlays[ii].Position.y, (*Obj).overlays[ii].Surf);
                ulandobjects_AddRect(ar[i].x + (*Obj).overlays[ii].Position.x, ar[i].y + (*Obj).overlays[ii].Position.y, (*Obj).Width, (*Obj).Height);
                ++ii;
            }
            --(*Obj).Maxcnt;
        }
        else
        {
            (*Obj).Maxcnt = 0;
        }
    }
    tryput_result = bRes;
    return tryput_result;
};
boolean ulandobjects_TryPut2(TSprayObject (*Obj),PSDL_Surface Surface)
{
    boolean tryput2_result;
    enum{MaxPointsIndex = 8095};
    LongWord x;
    LongWord y;
    LongWord xStart;
    LongWord yStart;
    Byte xWraps;
    Byte yWraps;
    typedef TPoint ar_tt[(MaxPointsIndex + 1)];
    ar_tt ar;
    LongWord cnt;
    LongWord i;
    TSDL_Rect r;
    boolean bRes;
    tryput2_result = false;
    cnt = 0;
    {
        if((*Obj).Maxcnt == 0)
        {
            return tryput2_result;
        }
        xWraps = 0;
        yWraps = 0;
        xStart = urandom_GetRandom(LAND_WIDTH - (*Obj).Width);
        yStart = 8 + urandom_GetRandom((LAND_HEIGHT - (*Obj).Height) - 16);
        x = xStart;
        y = yStart;
        r.x = 0;
        r.y = 0;
        r.w = (*Obj).Width;
        r.h = (*Obj).Height + 16;
        do {
               yWraps = 0;
               do {
                      if(ulandobjects_CheckLand(r, x, y - 8, lfBasic) && !ulandobjects_CheckIntersect(x, y, (*Obj).Width, (*Obj).Height))
                      {
                          ar[cnt].x = x;
                          ar[cnt].y = y;
                          if(cnt >= MaxPointsIndex)
                          {
                              y = 0xff000000;
                              x = 0xff000000;
                          }
                          else
                          {
                              ++cnt;
                          }
                      }
                      y += 12;
                      if((y >= ((LAND_HEIGHT - (*Obj).Height) - 8)) || ((yWraps > 0) && (y >= yStart)))
                      {
                          ++yWraps;
                          y = 8;
                      }
                  } while(!(yWraps > 1));
               x += urandom_GetRandom(12) + 12;
               if((x >= (LAND_WIDTH - (*Obj).Width)) || ((xWraps > 0) && (x >= xStart)))
               {
                   ++xWraps;
                   x = 0;
               }
           } while(!(xWraps > 1));
        bRes = cnt != 0;
        if(bRes)
        {
            i = urandom_GetRandom(cnt);
            urenderutils_copyToXY((*Obj).Surf, Surface, ar[i].x, ar[i].y);
            ulandobjects_AddRect(ar[i].x - 32, ar[i].y - 32, (*Obj).Width + 64, (*Obj).Height + 64);
            --(*Obj).Maxcnt;
        }
        else
        {
            (*Obj).Maxcnt = 0;
        }
    }
    tryput2_result = bRes;
    return tryput2_result;
};
void ulandobjects_CheckRect(LongWord Width,LongWord Height,LongWord x,LongWord y,LongWord w,LongWord h)
{
    if((x + w) > Width)
    {
        udebug_OutError(_strappend(_strconcat(_strconcat(_strconcat(_strconcat(_strconcat(__str7, uutils_IntToStr(x)), __str8), uutils_IntToStr(w)), __str9), uutils_IntToStr(Width)), 0x29), true);
    }
    if((y + h) > Height)
    {
        udebug_OutError(_strappend(_strconcat(_strconcat(_strconcat(_strconcat(_strconcat(__str10, uutils_IntToStr(y)), __str8), uutils_IntToStr(h)), __str11), uutils_IntToStr(Height)), 0x29), true);
    }
};
void ulandobjects_ReadRect(TSDL_Rect (*rect),shortstring (*s))
{
    LongInt i;
    {
        i = fpcrtl_pos(0x2c, (*s));
        (*rect).x = uutils_StrToInt(uutils_Trim(fpcrtl_copy((*s), 1, ((int)(i) - 1))));
        fpcrtl_Delete((*s), 1, i);
        i = fpcrtl_pos(0x2c, (*s));
        (*rect).y = uutils_StrToInt(uutils_Trim(fpcrtl_copy((*s), 1, ((int)(i) - 1))));
        fpcrtl_Delete((*s), 1, i);
        i = fpcrtl_pos(0x2c, (*s));
        (*rect).w = uutils_StrToInt(uutils_Trim(fpcrtl_copy((*s), 1, ((int)(i) - 1))));
        fpcrtl_Delete((*s), 1, i);
        i = fpcrtl_pos(0x2c, (*s));
        if(i == 0)
        {
            i = (fpcrtl_Length((*s)) + 1);
        }
        (*rect).h = uutils_StrToInt(uutils_Trim(fpcrtl_copy((*s), 1, ((int)(i) - 1))));
        fpcrtl_Delete((*s), 1, i);
    }
};
void ulandobjects_ReadOverlay(TThemeObjectOverlay (*overlay),shortstring (*s))
{
    LongInt i;
    {
        i = fpcrtl_pos(0x2c, (*s));
        (*overlay).Position.x = uutils_StrToInt(uutils_Trim(fpcrtl_copy((*s), 1, ((int)(i) - 1))));
        fpcrtl_Delete((*s), 1, i);
        i = fpcrtl_pos(0x2c, (*s));
        (*overlay).Position.y = uutils_StrToInt(uutils_Trim(fpcrtl_copy((*s), 1, ((int)(i) - 1))));
        fpcrtl_Delete((*s), 1, i);
        i = fpcrtl_pos(0x2c, (*s));
        if(i == 0)
        {
            i = (fpcrtl_Length((*s)) + 1);
        }
        (*overlay).Surf = ustore_LoadDataImage(ptCurrTheme, uutils_Trim(fpcrtl_copy((*s), 1, ((int)(i) - 1))), ((ifColorKey | ifIgnoreCaps) | ifCritical) | ifDigestAlpha);
        (*overlay).Width = (*overlay).Surf->w;
        (*overlay).Height = (*overlay).Surf->h;
        fpcrtl_Delete((*s), 1, i);
    }
};
void ulandobjects_ReadThemeInfo(TThemeObjects (*ThemeObjects),TSprayObjects (*SprayObjects))
{
    string255 s;
    string255 key;
    string255 nameRef;
    PFSFile f;
    LongInt i;
    LongWord ii;
    LongWord t;
    TSDL_Color c2;
    ustore_AddProgress();
    if(GrayScale)
    {
        {i = 0;
         LongInt i__end__ = 7;
         if (i <= i__end__) do {
                                   t = fpcrtl_round(((SDWaterColorArray[i].r * RGB_LUMINANCE_RED) + (SDWaterColorArray[i].g * RGB_LUMINANCE_GREEN)) + (SDWaterColorArray[i].b * RGB_LUMINANCE_BLUE));
                                   if(t > 255)
                                   {
                                       t = 255;
                                   }
                                   SDWaterColorArray[i].r = t;
                                   SDWaterColorArray[i].g = t;
                                   SDWaterColorArray[i].b = t;
                               } while(i++ != i__end__);}
        {i = 0;
         LongInt i__end__ = 7;
         if (i <= i__end__) do {
                                   t = fpcrtl_round(((WaterColorArray[i].r * RGB_LUMINANCE_RED) + (WaterColorArray[i].g * RGB_LUMINANCE_GREEN)) + (WaterColorArray[i].b * RGB_LUMINANCE_BLUE));
                                   if(t > 255)
                                   {
                                       t = 255;
                                   }
                                   WaterColorArray[i].r = t;
                                   WaterColorArray[i].g = t;
                                   WaterColorArray[i].b = t;
                               } while(i++ != i__end__);}
    }
    s = _strconcat(_strappend(cPathz[ptCurrTheme], 0x2f), cThemeCFGFilename);
    uconsole_WriteLnToConsole(__str12);
    f = uphysfslayer_pfsOpenRead(s);
    if(f == NULL)
    {
        udebug_OutError(_strconcat(__str13, s), true);
    }
    (*ThemeObjects).Count = 0;
    (*SprayObjects).Count = 0;
    while(!uphysfslayer_pfsEOF(f) && allOK)
    {
        uphysfslayer_pfsReadLn(f, &(s));
        if(fpcrtl_Length(s) == 0)
        {
            continue;
        }
        if(s.s[1] == 0x3b)
        {
            continue;
        }
        i = fpcrtl_pos(0x3d, s);
        key = uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1)));
        fpcrtl_Delete(s, 1, i);
        if(_strcompare(key, __str14))
        {
            i = fpcrtl_pos(0x2c, s);
            SkyColor.r = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
            fpcrtl_Delete(s, 1, i);
            i = fpcrtl_pos(0x2c, s);
            SkyColor.g = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
            fpcrtl_Delete(s, 1, i);
            SkyColor.b = uutils_StrToInt(uutils_Trim(s));
            if(GrayScale)
            {
                t = fpcrtl_round(((SkyColor.r * RGB_LUMINANCE_RED) + (SkyColor.g * RGB_LUMINANCE_GREEN)) + (SkyColor.b * RGB_LUMINANCE_BLUE));
                if(t > 255)
                {
                    t = 255;
                }
                SkyColor.r = t;
                SkyColor.g = t;
                SkyColor.b = t;
            }
            ustore_SetSkyColor(SkyColor.r /(float) 255, SkyColor.g /(float) 255, SkyColor.b /(float) 255);
            SDSkyColor.r = SkyColor.r;
            SDSkyColor.g = SkyColor.g;
            SDSkyColor.b = SkyColor.b;
        }
        else
        {
            if(_strcompare(key, __str15))
            {
                i = fpcrtl_pos(0x2c, s);
                SDTint.r = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                fpcrtl_Delete(s, 1, i);
                i = fpcrtl_pos(0x2c, s);
                SDTint.g = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                fpcrtl_Delete(s, 1, i);
                i = fpcrtl_pos(0x2c, s);
                SDTint.b = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                fpcrtl_Delete(s, 1, i);
                SDTint.a = uutils_StrToInt(uutils_Trim(s));
                if(GrayScale)
                {
                    t = fpcrtl_round(((SDTint.r * RGB_LUMINANCE_RED) + (SDTint.g * RGB_LUMINANCE_GREEN)) + (SDTint.b * RGB_LUMINANCE_BLUE));
                    if(t > 255)
                    {
                        t = 255;
                    }
                    SDTint.r = t;
                    SDTint.g = t;
                    SDTint.b = t;
                }
            }
            else
            {
                if(_strcompare(key, __str16))
                {
                    i = fpcrtl_pos(0x2c, s);
                    c2.r = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                    fpcrtl_Delete(s, 1, i);
                    i = fpcrtl_pos(0x2c, s);
                    c2.g = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                    fpcrtl_Delete(s, 1, i);
                    c2.b = uutils_StrToInt(uutils_Trim(s));
                    if(GrayScale)
                    {
                        t = fpcrtl_round(((SkyColor.r * RGB_LUMINANCE_RED) + (SkyColor.g * RGB_LUMINANCE_GREEN)) + (SkyColor.b * RGB_LUMINANCE_BLUE));
                        if(t > 255)
                        {
                            t = 255;
                        }
                        c2.r = t;
                        c2.g = t;
                        c2.b = t;
                    }
                    ExplosionBorderColorR = c2.r;
                    ExplosionBorderColorG = c2.g;
                    ExplosionBorderColorB = c2.b;
                    ExplosionBorderColorNoA = ((c2.r << RShift) | (c2.g << GShift)) | (c2.b << BShift);
                    ExplosionBorderColor = ExplosionBorderColorNoA | AMask;
                }
                else
                {
                    if(_strcompare(key, __str17))
                    {
                        i = fpcrtl_pos(0x2c, s);
                        WaterColorArray[1].r = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                        fpcrtl_Delete(s, 1, i);
                        i = fpcrtl_pos(0x2c, s);
                        WaterColorArray[1].g = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                        fpcrtl_Delete(s, 1, i);
                        WaterColorArray[1].b = uutils_StrToInt(uutils_Trim(s));
                        WaterColorArray[1].a = 255;
                        if(GrayScale)
                        {
                            t = fpcrtl_round(((WaterColorArray[0].r * RGB_LUMINANCE_RED) + (WaterColorArray[0].g * RGB_LUMINANCE_GREEN)) + (WaterColorArray[0].b * RGB_LUMINANCE_BLUE));
                            if(t > 255)
                            {
                                t = 255;
                            }
                            WaterColorArray[1].r = t;
                            WaterColorArray[1].g = t;
                            WaterColorArray[1].b = t;
                        }
                        WaterColorArray[3] = WaterColorArray[1];
                        WaterColorArray[5] = WaterColorArray[1];
                        WaterColorArray[7] = WaterColorArray[1];
                    }
                    else
                    {
                        if(_strcompare(key, __str18))
                        {
                            i = fpcrtl_pos(0x2c, s);
                            WaterColorArray[0].r = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                            fpcrtl_Delete(s, 1, i);
                            i = fpcrtl_pos(0x2c, s);
                            WaterColorArray[0].g = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                            fpcrtl_Delete(s, 1, i);
                            WaterColorArray[0].b = uutils_StrToInt(uutils_Trim(s));
                            WaterColorArray[0].a = 255;
                            if(GrayScale)
                            {
                                t = fpcrtl_round(((WaterColorArray[2].r * RGB_LUMINANCE_RED) + (WaterColorArray[2].g * RGB_LUMINANCE_GREEN)) + (WaterColorArray[2].b * RGB_LUMINANCE_BLUE));
                                if(t > 255)
                                {
                                    t = 255;
                                }
                                WaterColorArray[0].r = t;
                                WaterColorArray[0].g = t;
                                WaterColorArray[0].b = t;
                            }
                            WaterColorArray[2] = WaterColorArray[0];
                            WaterColorArray[4] = WaterColorArray[0];
                            WaterColorArray[6] = WaterColorArray[0];
                        }
                        else
                        {
                            if(_strcompare(key, __str19))
                            {
                                WaterOpacity = uutils_StrToInt(uutils_Trim(s));
                                SDWaterOpacity = WaterOpacity;
                            }
                            else
                            {
                                if(_strcompare(key, __str20))
                                {
                                    MusicFN = uutils_Trim(s);
                                }
                                else
                                {
                                    if(_strcompare(key, __str21))
                                    {
                                        SDMusicFN = uutils_Trim(s);
                                    }
                                    else
                                    {
                                        if(_strcompare(key, __str22))
                                        {
                                            FallbackMusicFN = uutils_Trim(s);
                                        }
                                        else
                                        {
                                            if(_strcompare(key, __str23))
                                            {
                                                FallbackSDMusicFN = uutils_Trim(s);
                                            }
                                            else
                                            {
                                                if(_strcompare(key, __str24))
                                                {
                                                    cCloudsNumber = (((Word)uutils_StrToInt(uutils_Trim(s))) * cScreenSpace) / 4096;
                                                    cSDCloudsNumber = cCloudsNumber;
                                                }
                                                else
                                                {
                                                    if(_strcompare(key, __str25))
                                                    {
                                                        ++(*ThemeObjects).Count;
                                                        {
                                                            i = fpcrtl_pos(0x2c, s);
                                                            (*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].Name = uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1)));
                                                            (*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].Mask = ustore_LoadDataImage(ptCurrTheme, _strconcat(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))), __str26), (ifColorKey | ifIgnoreCaps) | ifDigestAll);
                                                            if((*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].Mask == NULL)
                                                            {
                                                                (*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].Surf = ustore_LoadDataImage(ptCurrTheme, (*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].Name, ((ifColorKey | ifIgnoreCaps) | ifCritical) | ifDigestAlpha);
                                                            }
                                                            else
                                                            {
                                                                (*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].Surf = ustore_LoadDataImage(ptCurrTheme, (*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].Name, (ifColorKey | ifIgnoreCaps) | ifCritical);
                                                            }
                                                            (*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].Width = (*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].Surf->w;
                                                            (*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].Height = (*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].Surf->h;
                                                            fpcrtl_Delete(s, 1, i);
                                                            i = fpcrtl_pos(0x2c, s);
                                                            (*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].Maxcnt = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                            fpcrtl_Delete(s, 1, i);
                                                            if(((*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].Maxcnt < 1) || ((*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].Maxcnt > MAXTHEMEOBJECTS))
                                                            {
                                                                udebug_OutError(_strconcat(_strconcat(_strconcat(_strconcat(__str27, uutils_IntToStr(MAXTHEMEOBJECTS)), __str28), uutils_IntToStr((*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].Maxcnt)), __str29), true);
                                                            }
                                                            (*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].inrectcnt = 0;
                                                            {ii = 1;
                                                             LongWord ii__end__ = fpcrtl_Length(s);
                                                             if (ii <= ii__end__) do {
                                                                                         if(s.s[ii] == 0x2c)
                                                                                         {
                                                                                             ++(*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].inrectcnt;
                                                                                         }
                                                                                     } while(ii++ != ii__end__);}
                                                            if(((*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].inrectcnt % 2) == 0)
                                                            {
                                                                (*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].inrectcnt = 1;
                                                            }
                                                            else
                                                            {
                                                                i = fpcrtl_pos(0x2c, s);
                                                                (*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].inrectcnt = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                                fpcrtl_Delete(s, 1, i);
                                                            }
                                                            if((*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].inrectcnt > MAXOBJECTRECTS)
                                                            {
                                                                udebug_OutError(_strconcat(_strconcat(_strconcat(_strconcat(__str30, uutils_IntToStr(MAXOBJECTRECTS)), __str28), uutils_IntToStr((*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].inrectcnt)), __str29), true);
                                                            }
                                                            {ii = 0;
                                                             LongWord ii__end__ = ((int)((*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].inrectcnt) - 1);
                                                             if (ii <= ii__end__) do {
                                                                                         ulandobjects_ReadRect(&((*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].inland[ii]), &(s));
                                                                                     } while(ii++ != ii__end__);}
                                                            i = fpcrtl_pos(0x2c, s);
                                                            (*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].outrectcnt = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                            fpcrtl_Delete(s, 1, i);
                                                            if((*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].outrectcnt > MAXOBJECTRECTS)
                                                            {
                                                                udebug_OutError(_strconcat(_strconcat(_strconcat(_strconcat(__str31, uutils_IntToStr(MAXOBJECTRECTS)), __str28), uutils_IntToStr((*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].outrectcnt)), __str29), true);
                                                            }
                                                            {ii = 0;
                                                             LongWord ii__end__ = ((int)((*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].outrectcnt) - 1);
                                                             if (ii <= ii__end__) do {
                                                                                         ulandobjects_ReadRect(&((*ThemeObjects).objs[((int)((*ThemeObjects).Count) - 1)].outland[ii]), &(s));
                                                                                     } while(ii++ != ii__end__);}
                                                        }
                                                    }
                                                    else
                                                    {
                                                        if(_strcompare(key, __str32))
                                                        {
                                                            i = fpcrtl_pos(0x2c, s);
                                                            nameRef = uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1)));
                                                            {ii = 0;
                                                             LongWord ii__end__ = ((int)((*ThemeObjects).Count) - 1);
                                                             if (ii <= ii__end__) do {
                                                                                         if(_strcompare((*ThemeObjects).objs[ii].Name, nameRef))
                                                                                         {
                                                                                             {
                                                                                                 if((*ThemeObjects).objs[ii].anchorcnt != 0)
                                                                                                 {
                                                                                                     udebug_OutError(_strconcat(__str33, nameRef), true);
                                                                                                 }
                                                                                                 fpcrtl_Delete(s, 1, i);
                                                                                                 i = fpcrtl_pos(0x2c, s);
                                                                                                 (*ThemeObjects).objs[ii].anchorcnt = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                                                                 fpcrtl_Delete(s, 1, i);
                                                                                                 if((*ThemeObjects).objs[ii].anchorcnt > MAXOBJECTRECTS)
                                                                                                 {
                                                                                                     udebug_OutError(_strconcat(_strconcat(_strconcat(_strconcat(__str34, uutils_IntToStr(MAXOBJECTRECTS)), __str28), uutils_IntToStr((*ThemeObjects).objs[ii].anchorcnt)), __str29), true);
                                                                                                 }
                                                                                                 {t = 0;
                                                                                                  LongWord t__end__ = ((int)((*ThemeObjects).objs[ii].anchorcnt) - 1);
                                                                                                  if (t <= t__end__) do {
                                                                                                                            ulandobjects_ReadRect(&((*ThemeObjects).objs[ii].anchors[t]), &(s));
                                                                                                                        } while(t++ != t__end__);}
                                                                                                 break;
                                                                                             }
                                                                                         }
                                                                                     } while(ii++ != ii__end__);}
                                                        }
                                                        else
                                                        {
                                                            if(_strcompare(key, __str35))
                                                            {
                                                                i = fpcrtl_pos(0x2c, s);
                                                                nameRef = uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1)));
                                                                {ii = 0;
                                                                 LongWord ii__end__ = ((int)((*ThemeObjects).Count) - 1);
                                                                 if (ii <= ii__end__) do {
                                                                                             if(_strcompare((*ThemeObjects).objs[ii].Name, nameRef))
                                                                                             {
                                                                                                 {
                                                                                                     if((*ThemeObjects).objs[ii].overlaycnt != 0)
                                                                                                     {
                                                                                                         udebug_OutError(_strconcat(__str36, nameRef), true);
                                                                                                     }
                                                                                                     fpcrtl_Delete(s, 1, i);
                                                                                                     i = fpcrtl_pos(0x2c, s);
                                                                                                     (*ThemeObjects).objs[ii].overlaycnt = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                                                                     fpcrtl_Delete(s, 1, i);
                                                                                                     if((*ThemeObjects).objs[ii].overlaycnt > MAXOBJECTRECTS)
                                                                                                     {
                                                                                                         udebug_OutError(_strconcat(_strconcat(_strconcat(_strconcat(__str37, uutils_IntToStr(MAXOBJECTRECTS)), __str28), uutils_IntToStr((*ThemeObjects).objs[ii].overlaycnt)), __str29), true);
                                                                                                     }
                                                                                                     {t = 0;
                                                                                                      LongWord t__end__ = ((int)((*ThemeObjects).objs[ii].overlaycnt) - 1);
                                                                                                      if (t <= t__end__) do {
                                                                                                                                ulandobjects_ReadOverlay(&((*ThemeObjects).objs[ii].overlays[t]), &(s));
                                                                                                                            } while(t++ != t__end__);}
                                                                                                     break;
                                                                                                 }
                                                                                             }
                                                                                         } while(ii++ != ii__end__);}
                                                            }
                                                            else
                                                            {
                                                                if(_strcompare(key, __str38))
                                                                {
                                                                    ++(*SprayObjects).Count;
                                                                    {
                                                                        i = fpcrtl_pos(0x2c, s);
                                                                        (*SprayObjects).objs[((int)((*SprayObjects).Count) - 1)].Surf = ustore_LoadDataImage(ptCurrTheme, uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))), ifAlpha | ifIgnoreCaps);
                                                                        (*SprayObjects).objs[((int)((*SprayObjects).Count) - 1)].Width = (*SprayObjects).objs[((int)((*SprayObjects).Count) - 1)].Surf->w;
                                                                        (*SprayObjects).objs[((int)((*SprayObjects).Count) - 1)].Height = (*SprayObjects).objs[((int)((*SprayObjects).Count) - 1)].Surf->h;
                                                                        fpcrtl_Delete(s, 1, i);
                                                                        (*SprayObjects).objs[((int)((*SprayObjects).Count) - 1)].Maxcnt = uutils_StrToInt(uutils_Trim(s));
                                                                    }
                                                                }
                                                                else
                                                                {
                                                                    if(_strcompare(key, __str39))
                                                                    {
                                                                        i = fpcrtl_pos(0x2c, s);
                                                                        watFrames = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                                        fpcrtl_Delete(s, 1, i);
                                                                        i = fpcrtl_pos(0x2c, s);
                                                                        watFrameTicks = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                                        fpcrtl_Delete(s, 1, i);
                                                                        watMove = uutils_StrToInt(uutils_Trim(s));
                                                                    }
                                                                    else
                                                                    {
                                                                        if(_strcompare(key, __str40))
                                                                        {
                                                                            i = fpcrtl_pos(0x2c, s);
                                                                            watSDFrames = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                                            fpcrtl_Delete(s, 1, i);
                                                                            i = fpcrtl_pos(0x2c, s);
                                                                            watSDFrameTicks = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                                            fpcrtl_Delete(s, 1, i);
                                                                            watSDMove = uutils_StrToInt(uutils_Trim(s));
                                                                        }
                                                                        else
                                                                        {
                                                                            if(_strcompare(key, __str41))
                                                                            {
                                                                                i = fpcrtl_pos(0x2c, s);
                                                                                vobCount = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                                                fpcrtl_Delete(s, 1, i);
                                                                                if(vobCount > 0)
                                                                                {
                                                                                    i = fpcrtl_pos(0x2c, s);
                                                                                    vobFramesCount = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                                                    fpcrtl_Delete(s, 1, i);
                                                                                    i = fpcrtl_pos(0x2c, s);
                                                                                    vobFrameTicks = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                                                    fpcrtl_Delete(s, 1, i);
                                                                                    i = fpcrtl_pos(0x2c, s);
                                                                                    vobVelocity = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                                                    fpcrtl_Delete(s, 1, i);
                                                                                    vobFallSpeed = uutils_StrToInt(uutils_Trim(s));
                                                                                }
                                                                            }
                                                                            else
                                                                            {
                                                                                if(_strcompare(key, __str42))
                                                                                {
                                                                                    cFlattenFlakes = true;
                                                                                }
                                                                                else
                                                                                {
                                                                                    if(_strcompare(key, __str43))
                                                                                    {
                                                                                        cFlattenClouds = true;
                                                                                    }
                                                                                    else
                                                                                    {
                                                                                        if(_strcompare(key, __str44))
                                                                                        {
                                                                                            cIce = true;
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            if(_strcompare(key, __str45))
                                                                                            {
                                                                                                cSnow = true;
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                if(_strcompare(key, __str46))
                                                                                                {
                                                                                                    cRopeNodeStep = uutils_Max(1, uutils_StrToInt(s));
                                                                                                }
                                                                                                else
                                                                                                {
                                                                                                    if(_strcompare(key, __str47))
                                                                                                    {
                                                                                                        cRopeLayers = uutils_Max(1, uutils_Min(MAXROPELAYERS, uutils_StrToInt(s)));
                                                                                                    }
                                                                                                    else
                                                                                                    {
                                                                                                        if(_strcompare(key, __str48))
                                                                                                        {
                                                                                                            i = fpcrtl_pos(0x2c, s);
                                                                                                            SDWaterColorArray[1].r = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                                                                            fpcrtl_Delete(s, 1, i);
                                                                                                            i = fpcrtl_pos(0x2c, s);
                                                                                                            SDWaterColorArray[1].g = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                                                                            fpcrtl_Delete(s, 1, i);
                                                                                                            SDWaterColorArray[1].b = uutils_StrToInt(uutils_Trim(s));
                                                                                                            SDWaterColorArray[1].a = 255;
                                                                                                            if(GrayScale)
                                                                                                            {
                                                                                                                t = fpcrtl_round(((SDWaterColorArray[0].r * RGB_LUMINANCE_RED) + (SDWaterColorArray[0].g * RGB_LUMINANCE_GREEN)) + (SDWaterColorArray[0].b * RGB_LUMINANCE_BLUE));
                                                                                                                if(t > 255)
                                                                                                                {
                                                                                                                    t = 255;
                                                                                                                }
                                                                                                                SDWaterColorArray[1].r = t;
                                                                                                                SDWaterColorArray[1].g = t;
                                                                                                                SDWaterColorArray[1].b = t;
                                                                                                            }
                                                                                                            SDWaterColorArray[3] = SDWaterColorArray[1];
                                                                                                            SDWaterColorArray[5] = SDWaterColorArray[1];
                                                                                                            SDWaterColorArray[7] = SDWaterColorArray[1];
                                                                                                        }
                                                                                                        else
                                                                                                        {
                                                                                                            if(_strcompare(key, __str49))
                                                                                                            {
                                                                                                                i = fpcrtl_pos(0x2c, s);
                                                                                                                SDWaterColorArray[0].r = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                                                                                fpcrtl_Delete(s, 1, i);
                                                                                                                i = fpcrtl_pos(0x2c, s);
                                                                                                                SDWaterColorArray[0].g = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                                                                                fpcrtl_Delete(s, 1, i);
                                                                                                                SDWaterColorArray[0].b = uutils_StrToInt(uutils_Trim(s));
                                                                                                                SDWaterColorArray[0].a = 255;
                                                                                                                if(GrayScale)
                                                                                                                {
                                                                                                                    t = fpcrtl_round(((SDWaterColorArray[2].r * RGB_LUMINANCE_RED) + (SDWaterColorArray[2].g * RGB_LUMINANCE_GREEN)) + (SDWaterColorArray[2].b * RGB_LUMINANCE_BLUE));
                                                                                                                    if(t > 255)
                                                                                                                    {
                                                                                                                        t = 255;
                                                                                                                    }
                                                                                                                    SDWaterColorArray[0].r = t;
                                                                                                                    SDWaterColorArray[0].g = t;
                                                                                                                    SDWaterColorArray[0].b = t;
                                                                                                                }
                                                                                                                SDWaterColorArray[2] = SDWaterColorArray[0];
                                                                                                                SDWaterColorArray[4] = SDWaterColorArray[0];
                                                                                                                SDWaterColorArray[6] = SDWaterColorArray[0];
                                                                                                            }
                                                                                                            else
                                                                                                            {
                                                                                                                if(_strcompare(key, __str50))
                                                                                                                {
                                                                                                                    SDWaterOpacity = uutils_StrToInt(uutils_Trim(s));
                                                                                                                }
                                                                                                                else
                                                                                                                {
                                                                                                                    if(_strcompare(key, __str51))
                                                                                                                    {
                                                                                                                        cSDCloudsNumber = (((Word)uutils_StrToInt(uutils_Trim(s))) * cScreenSpace) / 4096;
                                                                                                                    }
                                                                                                                    else
                                                                                                                    {
                                                                                                                        if(_strcompare(key, __str52))
                                                                                                                        {
                                                                                                                            i = fpcrtl_pos(0x2c, s);
                                                                                                                            vobSDCount = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                                                                                            fpcrtl_Delete(s, 1, i);
                                                                                                                            if(vobSDCount > 0)
                                                                                                                            {
                                                                                                                                i = fpcrtl_pos(0x2c, s);
                                                                                                                                vobSDFramesCount = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                                                                                                fpcrtl_Delete(s, 1, i);
                                                                                                                                i = fpcrtl_pos(0x2c, s);
                                                                                                                                vobSDFrameTicks = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                                                                                                fpcrtl_Delete(s, 1, i);
                                                                                                                                i = fpcrtl_pos(0x2c, s);
                                                                                                                                vobSDVelocity = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                                                                                                fpcrtl_Delete(s, 1, i);
                                                                                                                                vobSDFallSpeed = uutils_StrToInt(uutils_Trim(s));
                                                                                                                            }
                                                                                                                        }
                                                                                                                        else
                                                                                                                        {
                                                                                                                            if(_strcompare(key, __str53))
                                                                                                                            {
                                                                                                                                if((cReducedQuality & rqNoBackground) != 0)
                                                                                                                                {
                                                                                                                                    i = fpcrtl_pos(0x2c, s);
                                                                                                                                    RQSkyColor.r = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                                                                                                    fpcrtl_Delete(s, 1, i);
                                                                                                                                    i = fpcrtl_pos(0x2c, s);
                                                                                                                                    RQSkyColor.g = uutils_StrToInt(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))));
                                                                                                                                    fpcrtl_Delete(s, 1, i);
                                                                                                                                    RQSkyColor.b = uutils_StrToInt(uutils_Trim(s));
                                                                                                                                    if(GrayScale)
                                                                                                                                    {
                                                                                                                                        t = fpcrtl_round(((RQSkyColor.r * RGB_LUMINANCE_RED) + (RQSkyColor.g * RGB_LUMINANCE_GREEN)) + (RQSkyColor.b * RGB_LUMINANCE_BLUE));
                                                                                                                                        if(t > 255)
                                                                                                                                        {
                                                                                                                                            t = 255;
                                                                                                                                        }
                                                                                                                                        RQSkyColor.r = t;
                                                                                                                                        RQSkyColor.g = t;
                                                                                                                                        RQSkyColor.b = t;
                                                                                                                                    }
                                                                                                                                    ustore_SetSkyColor(RQSkyColor.r /(float) 255, RQSkyColor.g /(float) 255, RQSkyColor.b /(float) 255);
                                                                                                                                    SDSkyColor.r = RQSkyColor.r;
                                                                                                                                    SDSkyColor.g = RQSkyColor.g;
                                                                                                                                    SDSkyColor.b = RQSkyColor.b;
                                                                                                                                }
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    uphysfslayer_pfsClose(f);
    ustore_AddProgress();
};
void ulandobjects_AddThemeObjects(TThemeObjects (*ThemeObjects))
{
    LongInt i;
    LongInt ii;
    LongInt t;
    boolean b;
    if((*ThemeObjects).Count == 0)
    {
        return;
    }
    uconsole_WriteLnToConsole(__str54);
    {i = 0;
     LongInt i__end__ = ((int)((*ThemeObjects).Count) - 1);
     if (i <= i__end__) do {
                               (*ThemeObjects).objs[i].Maxcnt = uutils_Max(1, ((*ThemeObjects).objs[i].Maxcnt * MaxHedgehogs) / 18);
                           } while(i++ != i__end__);}
    do {
           t = urandom_GetRandom((*ThemeObjects).Count);
           b = false;
           {i = 0;
            LongInt i__end__ = ((int)((*ThemeObjects).Count) - 1);
            if (i <= i__end__) do {
                                      ii = (i + t) % (*ThemeObjects).Count;
                                      if((*ThemeObjects).objs[ii].Maxcnt != 0)
                                      {
                                          b = b || ulandobjects_TryPut(&((*ThemeObjects).objs[ii]));
                                      }
                                  } while(i++ != i__end__);}
       } while(!(!b));
};
void ulandobjects_AddSprayObjects(PSDL_Surface Surface,TSprayObjects (*SprayObjects))
{
    LongInt i;
    LongInt ii;
    LongInt t;
    boolean b;
    if((*SprayObjects).Count == 0)
    {
        return;
    }
    uconsole_WriteLnToConsole(__str55);
    {i = 0;
     LongInt i__end__ = ((int)((*SprayObjects).Count) - 1);
     if (i <= i__end__) do {
                               (*SprayObjects).objs[i].Maxcnt = uutils_Max(1, ((*SprayObjects).objs[i].Maxcnt * MaxHedgehogs) / 18);
                           } while(i++ != i__end__);}
    do {
           t = urandom_GetRandom((*SprayObjects).Count);
           b = false;
           {i = 0;
            LongInt i__end__ = ((int)((*SprayObjects).Count) - 1);
            if (i <= i__end__) do {
                                      ii = (i + t) % (*SprayObjects).Count;
                                      if((*SprayObjects).objs[ii].Maxcnt != 0)
                                      {
                                          b = b || ulandobjects_TryPut2(&((*SprayObjects).objs[ii]), Surface);
                                      }
                                  } while(i++ != i__end__);}
       } while(!(!b));
};
void ulandobjects_AddObjects()
{
    PSDL_Surface girSurf;
    LongWord i;
    LongWord g;
    ulandobjects_InitRects();
    if(hasGirders)
    {
        g = uutils_Max(playWidth / 8, 256);
        i = leftX + g;
        girSurf = NULL;
        do {
               ulandobjects_AddGirder(i, &(girSurf));
               i = i + g;
           } while(!(i > (rightX - g)));
        if(girSurf != NULL)
        {
            SDL_FreeSurface(girSurf);
            girSurf = NULL;
        }
    }
    if((GameFlags & gfDisableLandObjects) == 0)
    {
        ulandobjects_AddThemeObjects(&(ThemeObjects));
    }
    ustore_AddProgress();
    ulandobjects_FreeRects();
};
void ulandobjects_AddOnLandObjects(PSDL_Surface Surface)
{
    ulandobjects_InitRects();
    ulandobjects_AddSprayObjects(Surface, &(SprayObjects));
    ulandobjects_FreeRects();
};
void ulandobjects_LoadThemeConfig()
{
    ulandobjects_ReadThemeInfo(&(ThemeObjects), &(SprayObjects));
};
void ulandobjects_FreeLandObjects()
{
    LongWord i;
    LongWord ii;
    {i = 0;
     LongWord i__end__ = ((int)(MAXTHEMEOBJECTS) - 1);
     if (i <= i__end__) do {
                               if(ThemeObjects.objs[i].Surf != NULL)
                               {
                                   SDL_FreeSurface(ThemeObjects.objs[i].Surf);
                               }
                               if(SprayObjects.objs[i].Surf != NULL)
                               {
                                   SDL_FreeSurface(SprayObjects.objs[i].Surf);
                               }
                               ThemeObjects.objs[i].Surf = NULL;
                               SprayObjects.objs[i].Surf = NULL;
                               ii = 0;
                               while(ii < ThemeObjects.objs[i].overlaycnt)
                               {
                                   if(ThemeObjects.objs[i].overlays[ii].Surf != NULL)
                                   {
                                       SDL_FreeSurface(ThemeObjects.objs[i].overlays[ii].Surf);
                                       ThemeObjects.objs[i].overlays[ii].Surf = NULL;
                                   }
                                   ++ii;
                               }
                           } while(i++ != i__end__);}
};
