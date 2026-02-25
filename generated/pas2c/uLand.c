#include "fpcrtl.h"

#include "uLand.h"
#include "uConsole.h"
#include "uStore.h"
#include "uRandom.h"
#include "uLandObjects.h"
#include "uIO.h"
#include "uLandTexture.h"
#include "uVariables.h"
#include "uUtils.h"
#include "uCommands.h"
#include "adler32.h"
#include "uDebug.h"
#include "uLandPainted.h"
#include "uTextures.h"
#include "uPhysFSLayer.h"
#include "uScript.h"
#include "uLandGenPerlin.h"
#include "uLandUtils.h"
#include "uRenderUtils.h"
static const string255 __str43 = STRINIT("sendlanddigest");
static const string255 __str42 = STRINIT("landcheck");
static const string255 __str41 = STRINIT("LandDigest");
static const string255 __str40 = STRINIT("Loaded map or other critical resource does not match across all players");
static const string255 __str39 = STRINIT(" digest : ");
static const string255 __str38 = STRINIT("CheckLandDigest: ");
static const string255 __str37 = STRINIT("Generating preview...");
static const string255 __str36 = STRINIT("Unknown mapgen");
static const string255 __str35 = STRINIT("Generating land...");
static const string255 __str34 = STRINIT("/mask.png");
static const string255 __str33 = STRINIT("/map.png");
static const string255 __str32 = STRINIT("Map should be 32bit");
static const string255 __str31 = STRINIT("Map dimensions too big!");
static const string255 __str30 = STRINIT("/map");
static const string255 __str29 = STRINIT("map");
static const string255 __str28 = STRINIT("Loading land from file...");
static const string255 __str27 = STRINIT("/mask");
static const string255 __str26 = STRINIT("mask");
static const string255 __str25 = STRINIT("Fetching map HH limit");
static const string255 __str24 = STRINIT("/map.cfg");
static const string255 __str23 = STRINIT("Generating forts land...");
static const string255 __str22 = STRINIT("Error creating pre-land surface");
static const string255 __str21 = STRINIT("SDL_LockSurface");
static const string255 __str20 = STRINIT("Assert (LandSurface <> nil) failed");
static const string255 __str19 = STRINIT("Using template filter ");
static const string255 __str18 = STRINIT("wacky");
static const string255 __str17 = STRINIT("cavern");
static const string255 __str16 = STRINIT("large");
static const string255 __str15 = STRINIT("medium");
static const string255 __str14 = STRINIT("Error selecting TemplateFilter");
static const string255 __str13 = STRINIT("large_islands");
static const string255 __str12 = STRINIT("medium_islands");
static const string255 __str11 = STRINIT("small_islands");
static const string255 __str10 = STRINIT("large_tunnels");
static const string255 __str9 = STRINIT("medium_tunnels");
static const string255 __str8 = STRINIT("small_tunnels");
static const string255 __str7 = STRINIT("small");
static const string255 __str6 = STRINIT("");
static const string255 __str5 = STRINIT(" playHeight=");
static const string255 __str4 = STRINIT(" playWidth=");
static const string255 __str3 = STRINIT("Drawn map size: cFeatureSize=");
static const string255 __str2 = STRINIT("LandBackTex");
static const string255 __str1 = STRINIT("LandTex");
static const string255 __str0 = STRINIT("Border");
static string255 digest;
static boolean maskOnly;
void uland_PrettifyLandAlpha()
{
    if((cReducedQuality & rqBlurryLand) != 0)
    {
        utextures_PrettifyAlpha2D(LAND_HEIGHT / 2, LAND_WIDTH / 2);
    }
    else
    {
        utextures_PrettifyAlpha2D(LAND_HEIGHT, LAND_WIDTH);
    }
};
void uland_DrawBorderFromImage(PSDL_Surface Surface)
{
    PSDL_Surface tmpsurf;
    LongInt x;
    LongInt yd;
    LongInt yu;
    Word targetMask;
    tmpsurf = ustore_LoadDataImage(ptCurrTheme, __str0, (ifCritical | ifIgnoreCaps) | ifColorKey);
    if(maskOnly)
    {
        targetMask = lfLandMask;
    }
    else
    {
        targetMask = lfBasic;
    }
    {x = 0;
     LongInt x__end__ = LAND_WIDTH - 1;
     if (x <= x__end__) do {
                               yd = LAND_HEIGHT - 1;
                               do {
                                      while((yd > 0) && ((ulandutils_LandGet(yd, x) & targetMask) == 0))
                                      {
                                          --yd;
                                      }
                                      if(yd < 0)
                                      {
                                          yd = 0;
                                      }
                                      while((yd < LAND_HEIGHT) && ((ulandutils_LandGet(yd, x) & targetMask) != 0))
                                      {
                                          ++yd;
                                      }
                                      --yd;
                                      yu = yd;
                                      while((yu > 0) && ((ulandutils_LandGet(yu, x) & targetMask) != 0))
                                      {
                                          --yu;
                                      }
                                      while((yu < yd) && ((ulandutils_LandGet(yu, x) & targetMask) == 0))
                                      {
                                          ++yu;
                                      }
                                      if((yd < (LAND_HEIGHT - 1)) && ((yd - yu) >= 16))
                                      {
                                          urenderutils_copyToXYFromRect(tmpsurf, Surface, x % tmpsurf->w, 16, 1, 16, x, yd - 15);
                                      }
                                      if(yu > 0)
                                      {
                                          urenderutils_copyToXYFromRect(tmpsurf, Surface, x % tmpsurf->w, 0, 1, uutils_Min(16, (yd - yu) + 1), x, yu);
                                      }
                                      yd = yu - 1;
                                  } while(!(yd < 0));
                           } while(x++ != x__end__);}
    SDL_FreeSurface(tmpsurf);
};
void uland_DrawShoppaBorder()
{
    LongWord x;
    LongWord y;
    LongWord s;
    LongWord i;
    LongWord c1;
    LongWord c2;
    LongWord c;
    c1 = AMask;
    c2 = (AMask | RMask) | GMask;
    s = LAND_HEIGHT;
    {x = 0;
     LongWord x__end__ = LAND_WIDTH - 1;
     if (x <= x__end__) do {
                               {y = 0;
                                LongWord y__end__ = LAND_HEIGHT - 1;
                                if (y <= y__end__) do {
                                                          if(ulandutils_LandGet(y, x) == 0)
                                                          {
                                                              if(s < y)
                                                              {
                                                                  {i = uutils_Max(s, y - 8);
                                                                   LongWord i__end__ = y - 1;
                                                                   if (i <= i__end__) do {
                                                                                             if(((x + i) & 16) == 0)
                                                                                             {
                                                                                                 c = c1;
                                                                                             }
                                                                                             else
                                                                                             {
                                                                                                 c = c2;
                                                                                             }
                                                                                             if((cReducedQuality & rqBlurryLand) == 0)
                                                                                             {
                                                                                                 ulandutils_LandPixelSet(i, x, c);
                                                                                             }
                                                                                             else
                                                                                             {
                                                                                                 ulandutils_LandPixelSet(i / 2, x / 2, c);
                                                                                             }
                                                                                         } while(i++ != i__end__);}
                                                                  s = LAND_HEIGHT;
                                                              }
                                                              else
                                                              {
                                                                  ;
                                                              }
                                                          }
                                                          else
                                                          {
                                                              if(s > y)
                                                              {
                                                                  s = y;
                                                              }
                                                              if((s + 8) > y)
                                                              {
                                                                  if(((x + y) & 16) == 0)
                                                                  {
                                                                      c = c1;
                                                                  }
                                                                  else
                                                                  {
                                                                      c = c2;
                                                                  }
                                                                  if((cReducedQuality & rqBlurryLand) == 0)
                                                                  {
                                                                      ulandutils_LandPixelSet(y, x, c);
                                                                  }
                                                                  else
                                                                  {
                                                                      ulandutils_LandPixelSet(y / 2, x / 2, c);
                                                                  }
                                                              }
                                                          }
                                                      } while(y++ != y__end__);}
                           } while(x++ != x__end__);}
    s = LAND_WIDTH;
    {y = 0;
     LongWord y__end__ = LAND_HEIGHT - 1;
     if (y <= y__end__) do {
                               {x = 0;
                                LongWord x__end__ = LAND_WIDTH - 1;
                                if (x <= x__end__) do {
                                                          if(ulandutils_LandGet(y, x) == 0)
                                                          {
                                                              if(s < x)
                                                              {
                                                                  {i = uutils_Max(s, x - 8);
                                                                   LongWord i__end__ = x - 1;
                                                                   if (i <= i__end__) do {
                                                                                             if(((y + i) & 16) == 0)
                                                                                             {
                                                                                                 c = c1;
                                                                                             }
                                                                                             else
                                                                                             {
                                                                                                 c = c2;
                                                                                             }
                                                                                             if((cReducedQuality & rqBlurryLand) == 0)
                                                                                             {
                                                                                                 ulandutils_LandPixelSet(y, i, c);
                                                                                             }
                                                                                             else
                                                                                             {
                                                                                                 ulandutils_LandPixelSet(y / 2, i / 2, c);
                                                                                             }
                                                                                         } while(i++ != i__end__);}
                                                                  s = LAND_WIDTH;
                                                              }
                                                              else
                                                              {
                                                                  ;
                                                              }
                                                          }
                                                          else
                                                          {
                                                              if(s > x)
                                                              {
                                                                  s = x;
                                                              }
                                                              if((s + 8) > x)
                                                              {
                                                                  if(((x + y) & 16) == 0)
                                                                  {
                                                                      c = c1;
                                                                  }
                                                                  else
                                                                  {
                                                                      c = c2;
                                                                  }
                                                                  if((cReducedQuality & rqBlurryLand) == 0)
                                                                  {
                                                                      ulandutils_LandPixelSet(y, x, c);
                                                                  }
                                                                  else
                                                                  {
                                                                      ulandutils_LandPixelSet(y / 2, x / 2, c);
                                                                  }
                                                              }
                                                          }
                                                      } while(x++ != x__end__);}
                           } while(y++ != y__end__);}
};
void uland_ColorizeLandFast(PSDL_Surface mapsurf)
{
    PSDL_Surface ltexsurf;
    LongInt i;
    pointer ltlnp;
    pointer srcp;
    pointer dstp;
    pointer stopp;
    SizeInt c;
    ltexsurf = ustore_LoadDataImage(ptCurrTheme, __str1, ifCritical | ifIgnoreCaps);
    ltlnp = ltexsurf->pixels;
    dstp = mapsurf->pixels;
    SDL_LockSurface(mapsurf);
    SDL_LockSurface(ltexsurf);
    {i = 1;
     LongInt i__end__ = uutils_Min(ltexsurf->h, mapsurf->h);
     if (i <= i__end__) do {
                               c = ltexsurf->pitch;
                               if(c > mapsurf->pitch)
                               {
                                   c = mapsurf->pitch;
                               }
                               fpcrtl_Move((*ltlnp), (*dstp), c);
                               srcp = dstp;
                               stopp = dstp + mapsurf->pitch;
                               dstp += c;
                               while(dstp < stopp)
                               {
                                   c = uutils_Min(dstp - srcp, stopp - dstp);
                                   fpcrtl_Move((*srcp), (*dstp), c);
                                   dstp += c;
                               }
                               ltlnp += ltexsurf->pitch;
                           } while(i++ != i__end__);}
    ltlnp = NULL;
    SDL_UnlockSurface(ltexsurf);
    SDL_FreeSurface(ltexsurf);
    ltexsurf = NULL;
    srcp = mapsurf->pixels;
    stopp = srcp + (mapsurf->pitch * mapsurf->h);
    while(dstp < stopp)
    {
        c = uutils_Min(dstp - srcp, stopp - dstp);
        fpcrtl_Move((*srcp), (*dstp), c);
        dstp += c;
    }
    srcp = NULL;
    dstp = NULL;
    stopp = NULL;
    SDL_UnlockSurface(mapsurf);
    LandBackSurface = ustore_LoadDataImage(ptCurrTheme, __str2, ifIgnoreCaps | ifColorKey);
    if((LandBackSurface != NULL) && GrayScale)
    {
        utextures_Surface2GrayScale(LandBackSurface);
    }
};
void uland_ColorizeLand(PSDL_Surface Surface)
{
    PSDL_Surface tmpsurf;
    TSDL_Rect r;
    LongInt y;
    tmpsurf = ustore_LoadDataImage(ptCurrTheme, __str1, ifCritical | ifIgnoreCaps);
    r.y = 0;
    y = 0;
    while(y < LAND_HEIGHT)
    {
        r.x = 0;
        while(r.x < LAND_WIDTH)
        {
            urenderutils_copyToXY(tmpsurf, Surface, r.x, r.y);
            r.x += tmpsurf->w;
        }
        y += tmpsurf->h;
        r.y = y;
    }
    SDL_FreeSurface(tmpsurf);
    LandBackSurface = ustore_LoadDataImage(ptCurrTheme, __str2, ifIgnoreCaps | ifColorKey);
    if((LandBackSurface != NULL) && GrayScale)
    {
        utextures_Surface2GrayScale(LandBackSurface);
    }
};
void uland_GenDrawnMap()
{
    LongInt lowerX;
    LongInt upperX;
    LongInt lowerY;
    LongInt upperY;
    LongInt lowerFS;
    LongInt upperFS;
    if(cFeatureSize <= 6)
    {
        MaxHedgehogs = 6 + ((cFeatureSize - 1) * 2);
    }
    else
    {
        if(cFeatureSize < 11)
        {
            MaxHedgehogs = 16 + ((cFeatureSize - 6) * 4);
        }
        else
        {
            if(cFeatureSize == 11)
            {
                MaxHedgehogs = 48;
            }
            else
            {
                if(cFeatureSize == 12)
                {
                    MaxHedgehogs = 64;
                }
                else
                {
                    MaxHedgehogs = cMaxHHs;
                }
            }
        }
    }
    if(GameType == gmtLandPreview)
    {
        cFeatureSize = 1;
    }
    if(cFeatureSize < 6)
    {
        lowerFS = 1;
        lowerX = 1024;
        lowerY = 512;
        upperFS = 6;
    }
    else
    {
        if(cFeatureSize < 12)
        {
            lowerFS = 6;
            lowerX = 2048;
            lowerY = 1024;
            upperFS = 12;
        }
        else
        {
            lowerFS = 12;
            lowerX = 4096;
            lowerY = 2048;
            upperFS = 25;
        }
    }
    upperX = lowerX * 2;
    upperY = lowerY * 2;
    if(cFeatureSize == 25)
    {
        playWidth = 8192;
        playHeight = 4096;
    }
    else
    {
        playWidth = lowerX + (((upperX - lowerX) / (upperFS - lowerFS)) * (cFeatureSize - lowerFS));
        playHeight = lowerY + (((upperY - lowerY) / (upperFS - lowerFS)) * (cFeatureSize - lowerFS));
    }
    if(GameType != gmtLandPreview)
    {
        uconsole_WriteLnToConsole(_strconcat(_strconcat(_strconcat(_strconcat(_strconcat(__str3, uutils_IntToStr(cFeatureSize)), __str4), uutils_IntToStr(playWidth)), __str5), uutils_IntToStr(playHeight)));
    }
    ulandutils_ResizeLand(playWidth, playHeight);
    hasGirders = true;
    leftX = (LAND_WIDTH - playWidth) / 2;
    rightX = (playWidth + ((LAND_WIDTH - playWidth) / 2)) - 1;
    topY = LAND_HEIGHT - playHeight;
    ulandpainted_Draw();
};
string255 uland_SelectTemplate()
{
    string255 selecttemplate_result;
    selecttemplate_result = __str6;
    if((cReducedQuality & rqLowRes) != 0)
    {
        selecttemplate_result = __str7;
    }
    else
    {
        if((cTemplateFilter == 0) && (cMapGen != mgMaze))
        {
            cTemplateFilter = urandom_GetRandom(5) + 1;
        }
        else
        {
            urandom_GetRandom(1);
        }
        switch(cMapGen)
        {case mgMaze:switch(cTemplateFilter)
                     {case 0:selecttemplate_result = __str8;
                             break;
                      case 1:selecttemplate_result = __str9;
                             break;
                      case 2:selecttemplate_result = __str10;
                             break;
                      case 3:selecttemplate_result = __str11;
                             break;
                      case 4:selecttemplate_result = __str12;
                             break;
                      case 5:selecttemplate_result = __str13;
                             break;
                      default: udebug_OutError(__str14, true);}
                     break;
         default: switch(cTemplateFilter)
                  {case 1:selecttemplate_result = __str7;
                          break;
                   case 2:selecttemplate_result = __str15;
                          break;
                   case 3:selecttemplate_result = __str16;
                          break;
                   case 4:selecttemplate_result = __str17;
                          break;
                   case 5:selecttemplate_result = __str18;
                          break;
                   case 6:{
                              selecttemplate_result = __str7;
                              urandom_GetRandom(2);
                          }
                          break;
                   default: udebug_OutError(__str14, true);}}
    }
    uconsole_WriteLnToConsole(_strconcat(__str19, selecttemplate_result));
    return selecttemplate_result;
};
void uland_LandSurface2LandPixels(PSDL_Surface Surface)
{
    LongInt x;
    LongInt y;
    PLongWordArray p;
    if(udebug_checkFails(Surface != NULL, __str20, true))
    {
        return;
    }
    if(sdlh_SDL_MustLock(Surface))
    {
        if(udebug_SDLCheck(SDL_LockSurface(Surface) >= 0, __str21, true))
        {
            return;
        }
    }
    p = Surface->pixels;
    {y = 0;
     LongInt y__end__ = LAND_HEIGHT - 1;
     if (y <= y__end__) do {
                               {x = 0;
                                LongInt x__end__ = LAND_WIDTH - 1;
                                if (x <= x__end__) do {
                                                          if(ulandutils_LandGet(y, x) != 0)
                                                          {
                                                              if((cReducedQuality & rqBlurryLand) == 0)
                                                              {
                                                                  ulandutils_LandPixelSet(y, x, (*p)[x]);
                                                              }
                                                              else
                                                              {
                                                                  ulandutils_LandPixelSet(y / 2, x / 2, (*p)[x]);
                                                              }
                                                          }
                                                      } while(x++ != x__end__);}
                               p = ((PLongWordArray)&((*p)[Surface->pitch / 4]));
                           } while(y++ != y__end__);}
    if(sdlh_SDL_MustLock(Surface))
    {
        SDL_UnlockSurface(Surface);
    }
};
void uland_GenLandSurface()
{
    PSDL_Surface tmpsurf;
    LongWord x;
    LongWord y;
    ustore_AddProgress();
    tmpsurf = SDL_CreateRGBSurface(SDL_SWSURFACE, LAND_WIDTH, LAND_HEIGHT, 32, RMask, GMask, BMask, AMask);
    if(udebug_checkFails(tmpsurf != NULL, __str22, true))
    {
        return;
    }
    uland_ColorizeLandFast(tmpsurf);
    if((GameFlags & gfShoppaBorder) == 0)
    {
        uland_DrawBorderFromImage(tmpsurf);
    }
    ulandobjects_AddOnLandObjects(tmpsurf);
    uland_LandSurface2LandPixels(tmpsurf);
    SDL_FreeSurface(tmpsurf);
    if((GameFlags & gfShoppaBorder) != 0)
    {
        uland_DrawShoppaBorder();
    }
    {x = ((LongWord)leftX + 2);
     LongWord x__end__ = ((LongWord)rightX - 2);
     if (x <= x__end__) do {
                               {y = ((LongWord)topY + 2);
                                LongWord y__end__ = LAND_HEIGHT - 3;
                                if (y <= y__end__) do {
                                                          if((ulandutils_LandGet(y, x) == 0) && ((((ulandutils_LandGet(y, x - 1) == lfBasic) && (ulandutils_LandGet(y + 1, x) == lfBasic)) || (ulandutils_LandGet(y - 1, x) == lfBasic)) || ((ulandutils_LandGet(y, x + 1) == lfBasic) && ((ulandutils_LandGet(y - 1, x) == lfBasic) || (ulandutils_LandGet(y + 1, x) == lfBasic)))))
                                                          {
                                                              if((cReducedQuality & rqBlurryLand) == 0)
                                                              {
                                                                  if((ulandutils_LandGet(y, x - 1) == lfBasic) && ((ulandutils_LandPixelGet(y, x - 1) & AMask) != 0))
                                                                  {
                                                                      ulandutils_LandPixelSet(y, x, ulandutils_LandPixelGet(y, x - 1));
                                                                  }
                                                                  else
                                                                  {
                                                                      if((ulandutils_LandGet(y, x + 1) == lfBasic) && ((ulandutils_LandPixelGet(y, x + 1) & AMask) != 0))
                                                                      {
                                                                          ulandutils_LandPixelSet(y, x, ulandutils_LandPixelGet(y, x + 1));
                                                                      }
                                                                      else
                                                                      {
                                                                          if((ulandutils_LandGet(y - 1, x) == lfBasic) && ((ulandutils_LandPixelGet(y - 1, x) & AMask) != 0))
                                                                          {
                                                                              ulandutils_LandPixelSet(y, x, ulandutils_LandPixelGet(y - 1, x));
                                                                          }
                                                                          else
                                                                          {
                                                                              if((ulandutils_LandGet(y + 1, x) == lfBasic) && ((ulandutils_LandPixelGet(y + 1, x) & AMask) != 0))
                                                                              {
                                                                                  ulandutils_LandPixelSet(y, x, ulandutils_LandPixelGet(y + 1, x));
                                                                              }
                                                                          }
                                                                      }
                                                                  }
                                                                  if(((ulandutils_LandPixelGet(y, x) & AMask) >> AShift) > 10)
                                                                  {
                                                                      ulandutils_LandPixelSet(y, x, (ulandutils_LandPixelGet(y, x) & ~AMask) | (128 << AShift));
                                                                  }
                                                              }
                                                              ulandutils_LandSet(y, x, lfObject);
                                                          }
                                                          else
                                                          {
                                                              if((ulandutils_LandGet(y, x) == 0) && ((((((((((ulandutils_LandGet(y, x - 1) == lfBasic) && (ulandutils_LandGet(y + 1, x - 1) == lfBasic)) && (ulandutils_LandGet(y + 2, x) == lfBasic)) || (((ulandutils_LandGet(y, x - 1) == lfBasic) && (ulandutils_LandGet(y - 1, x - 1) == lfBasic)) && (ulandutils_LandGet(y - 2, x) == lfBasic))) || (((ulandutils_LandGet(y, x + 1) == lfBasic) && (ulandutils_LandGet(y + 1, x + 1) == lfBasic)) && (ulandutils_LandGet(y + 2, x) == lfBasic))) || (((ulandutils_LandGet(y, x + 1) == lfBasic) && (ulandutils_LandGet(y - 1, x + 1) == lfBasic)) && (ulandutils_LandGet(y - 2, x) == lfBasic))) || (((ulandutils_LandGet(y + 1, x) == lfBasic) && (ulandutils_LandGet(y + 1, x + 1) == lfBasic)) && (ulandutils_LandGet(y, x + 2) == lfBasic))) || (((ulandutils_LandGet(y - 1, x) == lfBasic) && (ulandutils_LandGet(y - 1, x + 1) == lfBasic)) && (ulandutils_LandGet(y, x + 2) == lfBasic))) || (((ulandutils_LandGet(y + 1, x) == lfBasic) && (ulandutils_LandGet(y + 1, x - 1) == lfBasic)) && (ulandutils_LandGet(y, x - 2) == lfBasic))) || (((ulandutils_LandGet(y - 1, x) == lfBasic) && (ulandutils_LandGet(y - 1, x - 1) == lfBasic)) && (ulandutils_LandGet(y, x - 2) == lfBasic))))
                                                              {
                                                                  if((cReducedQuality & rqBlurryLand) == 0)
                                                                  {
                                                                      if((ulandutils_LandGet(y, x - 1) == lfBasic) && ((ulandutils_LandPixelGet(y, x - 1) & AMask) != 0))
                                                                      {
                                                                          ulandutils_LandPixelSet(y, x, ulandutils_LandPixelGet(y, x - 1));
                                                                      }
                                                                      else
                                                                      {
                                                                          if((ulandutils_LandGet(y, x + 1) == lfBasic) && ((ulandutils_LandPixelGet(y, x + 1) & AMask) != 0))
                                                                          {
                                                                              ulandutils_LandPixelSet(y, x, ulandutils_LandPixelGet(y, x + 1));
                                                                          }
                                                                          else
                                                                          {
                                                                              if((ulandutils_LandGet(y + 1, x) == lfBasic) && ((ulandutils_LandPixelGet(y + 1, x) & AMask) != 0))
                                                                              {
                                                                                  ulandutils_LandPixelSet(y, x, ulandutils_LandPixelGet(y + 1, x));
                                                                              }
                                                                              else
                                                                              {
                                                                                  if((ulandutils_LandGet(y - 1, x) == lfBasic) && ((ulandutils_LandPixelGet(y - 1, x) & AMask) != 0))
                                                                                  {
                                                                                      ulandutils_LandPixelSet(y, x, ulandutils_LandPixelGet(y - 1, x));
                                                                                  }
                                                                              }
                                                                          }
                                                                      }
                                                                      if(((ulandutils_LandPixelGet(y, x) & AMask) >> AShift) > 10)
                                                                      {
                                                                          ulandutils_LandPixelSet(y, x, (ulandutils_LandPixelGet(y, x) & ~AMask) | (64 << AShift));
                                                                      }
                                                                  }
                                                                  ulandutils_LandSet(y, x, lfObject);
                                                              }
                                                          }
                                                      } while(y++ != y__end__);}
                           } while(x++ != x__end__);}
    ustore_AddProgress();
};
void uland_MakeFortsPreview()
{
    LongInt gap;
    LongWord h1;
    LongWord h2;
    LongWord w1;
    LongWord w2;
    LongWord x;
    LongWord y;
    LongWord lastX;
    LongWord wbm;
    LongWord bmref;
    enum{fortHeight = 960};
    enum{fortWidth = 704};
    enum{bmHeight = 53};
    enum{bmWidth = 64};
    ulandutils_ResizeLand(4096, 2048);
    lastX = LAND_WIDTH - 1;
    gap = ((1024 - fortWidth) + 60) + (20 * cFeatureSize);
    h2 = LAND_HEIGHT - 1;
    h1 = h2 - fortHeight;
    w2 = (LAND_WIDTH - gap) / 2;
    w1 = w2 - fortWidth;
    wbm = h1 + bmHeight;
    {y = h1;
     LongWord y__end__ = h2;
     if (y <= y__end__) do {
                               {x = w1;
                                LongWord x__end__ = w2;
                                if (x <= x__end__) do {
                                                          if((x % 4) != 0)
                                                          {
                                                              if((y <= wbm) && (((((int64_t) (x)) - ((int64_t) (w1))) % (bmWidth * 2)) >= bmWidth))
                                                              {
                                                                  continue;
                                                              }
                                                              ulandutils_LandSet(y, x, lfBasic);
                                                              ulandutils_LandSet(y, ((int64_t) (lastX)) - ((int64_t) (x)), lfBasic);
                                                          }
                                                      } while(x++ != x__end__);}
                           } while(y++ != y__end__);}
    w2 = w1 - gap;
    w1 = uutils_Max(0, w2 - fortWidth);
    wbm = h1 + bmHeight;
    bmref = w2 + bmWidth;
    {y = h1;
     LongWord y__end__ = h2;
     if (y <= y__end__) do {
                               {x = w1;
                                LongWord x__end__ = w2;
                                if (x <= x__end__) do {
                                                          if(((((int64_t) (y)) - ((int64_t) (x))) % 2) == 0)
                                                          {
                                                              if((y <= wbm) && (((((int64_t) ((LAND_WIDTH + x))) - ((int64_t) (bmref))) % (bmWidth * 2)) >= bmWidth))
                                                              {
                                                                  continue;
                                                              }
                                                              ulandutils_LandSet(y, x, lfBasic);
                                                              ulandutils_LandSet(y, ((int64_t) (lastX)) - ((int64_t) (x)), lfBasic);
                                                          }
                                                      } while(x++ != x__end__);}
                           } while(y++ != y__end__);}
};
void uland_MakeFortsMap()
{
    PSDL_Surface tmpsurf;
    Integer sectionWidth;
    Integer i;
    Integer t;
    Integer p;
    boolean mirror;
    PClan pc;
    if(cMapGen == mgForts)
    {
        sectionWidth = (1024 + 60) + (20 * cFeatureSize);
    }
    else
    {
        sectionWidth = 1024 * 300;
    }
    {i = 0;
     Integer i__end__ = ClansCount - 1;
     if (i <= i__end__) do {
                               t = urandom_GetRandom(ClansCount);
                               p = urandom_GetRandom(ClansCount);
                               if(t != p)
                               {
                                   pc = SpawnClansArray[t];
                                   SpawnClansArray[t] = SpawnClansArray[p];
                                   SpawnClansArray[p] = pc;
                               }
                           } while(i++ != i__end__);}
    playWidth = sectionWidth * ClansCount;
    ulandutils_ResizeLand(playWidth, 2048);
    playHeight = 1200;
    leftX = (LAND_WIDTH - playWidth) / 2;
    rightX = (playWidth + ((LAND_WIDTH - playWidth) / 2)) - 1;
    topY = LAND_HEIGHT - playHeight;
    uconsole_WriteLnToConsole(__str23);
    {i = 0;
     Integer i__end__ = ClansCount - 1;
     if (i <= i__end__) do {
                               mirror = urandom_GetRandom(2) == 0;
                               if((WorldEdge != weWrap) || (ClansCount == 2))
                               {
                                   mirror = (i != 0) && (mirror || (i == (ClansCount - 1)));
                               }
                               if(mirror)
                               {
                                   tmpsurf = ustore_LoadDataImage(ptForts, _strappend((*SpawnClansArray[i]->Teams[0]).FortName, 0x52), (ifAlpha | ifColorKey) | ifIgnoreCaps);
                                   if(tmpsurf == NULL)
                                   {
                                       tmpsurf = ustore_LoadDataImage(ptForts, _strappend((*SpawnClansArray[i]->Teams[0]).FortName, 0x4c), ((ifAlpha | ifCritical) | ifColorKey) | ifIgnoreCaps);
                                       ulandobjects_BlitImageAndGenerateCollisionInfo_6((leftX + (sectionWidth * i)) + ((sectionWidth - tmpsurf->w) / 2), LAND_HEIGHT - tmpsurf->h, tmpsurf->w, tmpsurf, 0, true);
                                   }
                                   else
                                   {
                                       ulandobjects_BlitImageAndGenerateCollisionInfo_4((leftX + (sectionWidth * i)) + ((sectionWidth - tmpsurf->w) / 2), LAND_HEIGHT - tmpsurf->h, tmpsurf->w, tmpsurf);
                                   }
                                   SDL_FreeSurface(tmpsurf);
                               }
                               else
                               {
                                   tmpsurf = ustore_LoadDataImage(ptForts, _strappend((*SpawnClansArray[i]->Teams[0]).FortName, 0x4c), ((ifAlpha | ifCritical) | ifColorKey) | ifIgnoreCaps);
                                   ulandobjects_BlitImageAndGenerateCollisionInfo_4((leftX + (sectionWidth * i)) + ((sectionWidth - tmpsurf->w) / 2), LAND_HEIGHT - tmpsurf->h, tmpsurf->w, tmpsurf);
                                   SDL_FreeSurface(tmpsurf);
                               }
                           } while(i++ != i__end__);}
};
void uland_LoadMapConfig()
{
    PFSFile f;
    string255 s;
    s = _strconcat(cPathz[ptMapCurrent], __str24);
    uconsole_WriteLnToConsole(__str25);
    f = uphysfslayer_pfsOpenRead(s);
    if(f != NULL)
    {
        uphysfslayer_pfsReadLn(f, &(s));
        if(!uphysfslayer_pfsEOF(f))
        {
            uphysfslayer_pfsReadLn(f, &(s));
            fpcrtl_val(s, MaxHedgehogs);
        }
        uphysfslayer_pfsClose(f);
    }
    if(MaxHedgehogs == 0)
    {
        MaxHedgehogs = 18;
    }
};
void uland_LoadMask()
{
    PSDL_Surface tmpsurf;
    PLongWordArray p;
    LongWord x;
    LongWord y;
    LongWord cpX;
    LongWord cpY;
    string255 mapName;
    tmpsurf = ustore_LoadDataImage(ptMapCurrent, __str26, (ifAlpha | ifColorKey) | ifIgnoreCaps);
    if(tmpsurf == NULL)
    {
        mapName = uutils_ExtractFileName(cPathz[ptMapCurrent]);
        tmpsurf = ustore_LoadDataImage(ptMissionMaps, _strconcat(mapName, __str27), (ifAlpha | ifColorKey) | ifIgnoreCaps);
    }
    if((tmpsurf != NULL) && ((*tmpsurf->format).BytesPerPixel == 4))
    {
        if(LAND_WIDTH == 0)
        {
            uland_LoadMapConfig();
            ulandutils_ResizeLand(tmpsurf->w, tmpsurf->h);
            playHeight = tmpsurf->h;
            playWidth = tmpsurf->w;
            leftX = (LAND_WIDTH - playWidth) / 2;
            rightX = (playWidth + ((LAND_WIDTH - playWidth) / 2)) - 1;
            topY = LAND_HEIGHT - playHeight;
        }
        disableLandBack = true;
        cpX = (LAND_WIDTH - tmpsurf->w) / 2;
        cpY = LAND_HEIGHT - tmpsurf->h;
        if(sdlh_SDL_MustLock(tmpsurf))
        {
            udebug_SDLCheck(SDL_LockSurface(tmpsurf) >= 0, __str21, true);
        }
        if(allOK)
        {
            p = tmpsurf->pixels;
            {y = 0;
             LongWord y__end__ = ((int)(tmpsurf->h) - 1);
             if (y <= y__end__) do {
                                       {x = 0;
                                        LongWord x__end__ = ((int)(tmpsurf->w) - 1);
                                        if (x <= x__end__) do {
                                                                  ulandobjects_SetLand(cpY + y, cpX + x, (*p)[x]);
                                                              } while(x++ != x__end__);}
                                       p = ((PLongWordArray)&((*p)[tmpsurf->pitch / 4]));
                                   } while(y++ != y__end__);}
            if(sdlh_SDL_MustLock(tmpsurf))
            {
                SDL_UnlockSurface(tmpsurf);
            }
            if(!disableLandBack)
            {
                LandBackSurface = ustore_LoadDataImage(ptCurrTheme, __str2, ifIgnoreCaps | ifColorKey);
                if((LandBackSurface != NULL) && GrayScale)
                {
                    utextures_Surface2GrayScale(LandBackSurface);
                }
            }
        }
    }
    if(tmpsurf != NULL)
    {
        SDL_FreeSurface(tmpsurf);
    }
    tmpsurf = NULL;
};
void uland_LoadMap()
{
    PSDL_Surface tmpsurf;
    string255 mapName = STRINIT("");
    uconsole_WriteLnToConsole(__str28);
    ustore_AddProgress();
    tmpsurf = ustore_LoadDataImage(ptMapCurrent, __str29, (ifAlpha | ifColorKey) | ifIgnoreCaps);
    if(tmpsurf == NULL)
    {
        mapName = uutils_ExtractFileName(cPathz[ptMapCurrent]);
        tmpsurf = ustore_LoadDataImage(ptMissionMaps, _strconcat(mapName, __str30), ((ifAlpha | ifCritical) | ifColorKey) | ifIgnoreCaps);
        if(!allOK)
        {
            return;
        }
    }
    if(udebug_checkFails(((tmpsurf->w < 0x40000000) && (tmpsurf->h < 0x40000000)) && ((((QWord)tmpsurf->w) * tmpsurf->h) < (((6 * 1024) * 1024) * 1024)), __str31, true))
    {
        return;
    }
    ulandutils_ResizeLand(tmpsurf->w, tmpsurf->h);
    uland_LoadMapConfig();
    playHeight = tmpsurf->h;
    playWidth = tmpsurf->w;
    leftX = (LAND_WIDTH - playWidth) / 2;
    rightX = (playWidth + ((LAND_WIDTH - playWidth) / 2)) - 1;
    topY = LAND_HEIGHT - playHeight;
    if(!udebug_checkFails((*tmpsurf->format).BytesPerPixel == 4, __str32, true))
    {
        ulandobjects_BlitImageAndGenerateCollisionInfo_4((LAND_WIDTH - tmpsurf->w) / 2, LAND_HEIGHT - tmpsurf->h, tmpsurf->w, tmpsurf);
    }
    SDL_FreeSurface(tmpsurf);
    if(allOK)
    {
        uland_LoadMask();
    }
};
void uland_DrawBottomBorder()
{
    LongWord x;
    LongWord w;
    LongWord c;
    LongWord y;
    {w = 0;
     LongWord w__end__ = 23;
     if (w <= w__end__) do {
                               {x = ((LongWord)leftX);
                                LongWord x__end__ = ((LongWord)rightX);
                                if (x <= x__end__) do {
                                                          y = (((LongWord)cWaterLine) - 1) - w;
                                                          ulandutils_LandSet(y, x, lfIndestructible);
                                                          if(((x + y) % 32) < 16)
                                                          {
                                                              c = AMask;
                                                          }
                                                          else
                                                          {
                                                              c = (AMask | RMask) | GMask;
                                                          }
                                                          if((cReducedQuality & rqBlurryLand) == 0)
                                                          {
                                                              ulandutils_LandPixelSet(y, x, c);
                                                          }
                                                          else
                                                          {
                                                              ulandutils_LandPixelSet(y / 2, x / 2, c);
                                                          }
                                                      } while(x++ != x__end__);}
                           } while(w++ != w__end__);}
};
void uland_GenMap()
{
    LongWord x;
    LongWord y;
    LongWord w;
    LongWord c;
    LongWord c2;
    string255 map;
    string255 mask;
    hasBorder = false;
    maskOnly = false;
    ulandobjects_LoadThemeConfig();
    if(_strncompare(cPathz[ptMapCurrent], __str6))
    {
        map = _strconcat(cPathz[ptMapCurrent], __str33);
        mask = _strconcat(cPathz[ptMapCurrent], __str34);
        if(!uphysfslayer_pfsExists(map) && uphysfslayer_pfsExists(mask))
        {
            maskOnly = true;
            uland_LoadMask();
            uland_GenLandSurface();
        }
        else
        {
            uland_LoadMap();
        }
    }
    else
    {
        uconsole_WriteLnToConsole(__str35);
        switch(cMapGen)
        {case mgRandom:ulandutils_GenerateOutlineTemplatedLand(cFeatureSize, cSeed, uland_SelectTemplate(), PathPrefix);
                       break;
         case mgMaze:ulandutils_GenerateMazeLand(cFeatureSize, cSeed, uland_SelectTemplate(), PathPrefix);
                     break;
         case mgPerlin:{
                           ulandutils_ResizeLand(4096, 2048);
                           ulandgenperlin_GenPerlin();
                       }
                       break;
         case mgDrawn:uland_GenDrawnMap();
                      break;
         case mgForts:{
                          GameFlags = GameFlags | gfDivideTeams;
                          uland_MakeFortsMap();
                      }
                      break;
         case mgWFC:ulandutils_GenerateWfcTemplatedLand(cFeatureSize, cSeed, uland_SelectTemplate(), PathPrefix);
                    break;
         default: udebug_OutError(__str36, true);}
        if(cMapGen != mgForts)
        {
            uland_GenLandSurface();
        }
    }
    ustore_AddProgress();
    c = 0;
    if((GameFlags & gfBorder) != 0)
    {
        hasBorder = true;
    }
    else
    {
        {y = ((LongWord)topY);
         LongWord y__end__ = ((LongWord)topY + 5);
         if (y <= y__end__) do {
                                   {x = ((LongWord)leftX);
                                    LongWord x__end__ = ((LongWord)rightX);
                                    if (x <= x__end__) do {
                                                              if(ulandutils_LandGet(y, x) != 0)
                                                              {
                                                                  ++c;
                                                                  if(c > ((LongWord)LAND_WIDTH / 2))
                                                                  {
                                                                      hasBorder = true;
                                                                      break;
                                                                  }
                                                              }
                                                          } while(x++ != x__end__);}
                               } while(y++ != y__end__);}
    }
    if(hasBorder)
    {
        if(WorldEdge == weNone)
        {
            {y = 0;
             LongWord y__end__ = LAND_HEIGHT - 1;
             if (y <= y__end__) do {
                                       {x = 0;
                                        LongWord x__end__ = LAND_WIDTH - 1;
                                        if (x <= x__end__) do {
                                                                  if(((y < ((LongWord)topY)) || (x < ((LongWord)leftX))) || (x > ((LongWord)rightX)))
                                                                  {
                                                                      ulandutils_LandSet(y, x, lfIndestructible);
                                                                  }
                                                              } while(x++ != x__end__);}
                                   } while(y++ != y__end__);}
        }
        else
        {
            if(topY > 0)
            {
                {y = 0;
                 LongWord y__end__ = ((LongWord)topY - 1);
                 if (y <= y__end__) do {
                                           {x = 0;
                                            LongWord x__end__ = LAND_WIDTH - 1;
                                            if (x <= x__end__) do {
                                                                      ulandutils_LandSet(y, x, lfIndestructible);
                                                                  } while(x++ != x__end__);}
                                       } while(y++ != y__end__);}
            }
        }
        {w = 0;
         LongWord w__end__ = cBorderWidth - 1;
         if (w <= w__end__) do {
                                   if((WorldEdge != weBounce) && (WorldEdge != weWrap))
                                   {
                                       {y = ((LongWord)topY);
                                        LongWord y__end__ = LAND_HEIGHT - 1;
                                        if (y <= y__end__) do {
                                                                  ulandutils_LandSet(y, leftX + w, lfIndestructible);
                                                                  ulandutils_LandSet(y, rightX - w, lfIndestructible);
                                                                  if((((y + leftX) + w) % 32) < 16)
                                                                  {
                                                                      c = AMask;
                                                                  }
                                                                  else
                                                                  {
                                                                      c = (AMask | RMask) | GMask;
                                                                  }
                                                                  if((((y + rightX) - w) % 32) < 16)
                                                                  {
                                                                      c2 = AMask;
                                                                  }
                                                                  else
                                                                  {
                                                                      c2 = (AMask | RMask) | GMask;
                                                                  }
                                                                  if((cReducedQuality & rqBlurryLand) == 0)
                                                                  {
                                                                      ulandutils_LandPixelSet(y, leftX + w, c);
                                                                      ulandutils_LandPixelSet(y, rightX - w, c2);
                                                                  }
                                                                  else
                                                                  {
                                                                      ulandutils_LandPixelSet(y / 2, (leftX + w) / 2, c);
                                                                      ulandutils_LandPixelSet(y / 2, (rightX - w) / 2, c2);
                                                                  }
                                                              } while(y++ != y__end__);}
                                   }
                                   {x = ((LongWord)leftX);
                                    LongWord x__end__ = ((LongWord)rightX);
                                    if (x <= x__end__) do {
                                                              ulandutils_LandSet(topY + w, x, lfIndestructible);
                                                              if((((topY + x) + w) % 32) < 16)
                                                              {
                                                                  c = AMask;
                                                              }
                                                              else
                                                              {
                                                                  c = (AMask | RMask) | GMask;
                                                              }
                                                              if((cReducedQuality & rqBlurryLand) == 0)
                                                              {
                                                                  ulandutils_LandPixelSet(topY + w, x, c);
                                                              }
                                                              else
                                                              {
                                                                  ulandutils_LandPixelSet((topY + w) / 2, x / 2, c);
                                                              }
                                                          } while(x++ != x__end__);}
                               } while(w++ != w__end__);}
    }
    if((GameFlags & gfBottomBorder) != 0)
    {
        uland_DrawBottomBorder();
    }
    if((GameFlags & gfDisableGirders) != 0)
    {
        hasGirders = false;
    }
    if((cMapGen != mgForts) && (maskOnly || (_strcompare(cPathz[ptMapCurrent], __str6))))
    {
        ulandobjects_AddObjects();
    }
    else
    {
        ustore_AddProgress();
    }
    ulandobjects_FreeLandObjects();
    if(!allOK)
    {
        return;
    }
    if(GrayScale)
    {
        if((cReducedQuality & rqBlurryLand) == 0)
        {
            {x = ((LongWord)leftX);
             LongWord x__end__ = ((LongWord)rightX);
             if (x <= x__end__) do {
                                       {y = ((LongWord)topY);
                                        LongWord y__end__ = LAND_HEIGHT - 1;
                                        if (y <= y__end__) do {
                                                                  w = ulandutils_LandPixelGet(y, x);
                                                                  w = fpcrtl_round(((((w >> RShift) & 0xff) * RGB_LUMINANCE_RED) + (((w >> BShift) & 0xff) * RGB_LUMINANCE_GREEN)) + (((w >> GShift) & 0xff) * RGB_LUMINANCE_BLUE));
                                                                  if(w > 255)
                                                                  {
                                                                      w = 255;
                                                                  }
                                                                  w = ((((w & 0xff) << RShift) | ((w & 0xff) << BShift)) | ((w & 0xff) << GShift)) | (ulandutils_LandPixelGet(y, x) & AMask);
                                                                  ulandutils_LandPixelSet(y, x, w | (ulandutils_LandPixelGet(y, x) & AMask));
                                                              } while(y++ != y__end__);}
                                   } while(x++ != x__end__);}
        }
        else
        {
            {x = ((LongWord)leftX / 2);
             LongWord x__end__ = ((LongWord)rightX / 2);
             if (x <= x__end__) do {
                                       {y = ((LongWord)topY / 2);
                                        LongWord y__end__ = LAND_HEIGHT - (1 / 2);
                                        if (y <= y__end__) do {
                                                                  w = ulandutils_LandPixelGet(y / 2, x / 2);
                                                                  w = ((((w >> RShift) & 0xff) + ((w >> BShift) & 0xff)) + ((w >> GShift) & 0xff)) / 3;
                                                                  w = ((((w & 0xff) << RShift) | ((w & 0xff) << BShift)) | ((w & 0xff) << GShift)) | (ulandutils_LandPixelGet(y / 2, x / 2) & AMask);
                                                                  ulandutils_LandPixelSet(y, x, w | (ulandutils_LandPixelGet(y / 2, x / 2) & AMask));
                                                              } while(y++ != y__end__);}
                                   } while(x++ != x__end__);}
        }
    }
    uland_PrettifyLandAlpha();
    if((WorldEdge != weNone) && !hasBorder)
    {
        ulandutils_InitWorldEdges();
    }
    uscript_ScriptSetMapGlobals();
};
void uland_GenPreview(TPreview (*Preview))
{
    LongInt rh;
    LongInt rw;
    LongInt ox;
    LongInt oy;
    LongInt x;
    LongInt y;
    LongInt xx;
    LongInt yy;
    LongInt t;
    LongInt bit;
    LongInt cbit;
    LongInt lh;
    LongInt lw;
    uconsole_WriteLnToConsole(__str37);
    switch(cMapGen)
    {case mgRandom:ulandutils_GenerateOutlineTemplatedLand(cFeatureSize, cSeed, uland_SelectTemplate(), PathPrefix);
                   break;
     case mgMaze:ulandutils_GenerateMazeLand(cFeatureSize, cSeed, uland_SelectTemplate(), PathPrefix);
                 break;
     case mgPerlin:{
                       ulandutils_ResizeLand(4096, 2048);
                       ulandgenperlin_GenPerlin();
                   }
                   break;
     case mgDrawn:{
                      uland_GenDrawnMap();
                  }
                  break;
     case mgForts:uland_MakeFortsPreview();
                  break;
     case mgWFC:ulandutils_GenerateWfcTemplatedLand(cFeatureSize, cSeed, uland_SelectTemplate(), PathPrefix);
                break;
     default: udebug_OutError(__str36, true);}
    uscript_ScriptSetMapGlobals();
    if(cMapGen != mgDrawn)
    {
        rh = uutils_Max(LAND_HEIGHT, 2048);
        rw = uutils_Max(LAND_WIDTH, 4096);
    }
    else
    {
        rh = LAND_HEIGHT;
        rw = LAND_WIDTH;
    }
    ox = 0;
    if(rw < (rh * 2))
    {
        rw = rh * 2;
    }
    if(rh < (rw / 2))
    {
        rh = rw * 2;
    }
    ox = (rw - LAND_WIDTH) / 2;
    oy = rh - LAND_HEIGHT;
    lh = rh / 128;
    lw = rw / 32;
    {y = 0;
     LongInt y__end__ = 127;
     if (y <= y__end__) do {
                               {x = 0;
                                LongInt x__end__ = 31;
                                if (x <= x__end__) do {
                                                          (*Preview)[y][x] = 0;
                                                          {bit = 0;
                                                           LongInt bit__end__ = 7;
                                                           if (bit <= bit__end__) do {
                                                                                         t = 0;
                                                                                         cbit = bit * 8;
                                                                                         {yy = y * lh;
                                                                                          LongInt yy__end__ = (y * lh) + 7;
                                                                                          if (yy <= yy__end__) do {
                                                                                                                      {xx = (x * lw) + cbit;
                                                                                                                       LongInt xx__end__ = ((x * lw) + cbit) + 7;
                                                                                                                       if (xx <= xx__end__) do {
                                                                                                                                                   if(((((yy - oy) & LAND_HEIGHT_MASK) == 0) && (((xx - ox) & LAND_WIDTH_MASK) == 0)) && (ulandutils_LandGet(yy - oy, xx - ox) != 0))
                                                                                                                                                   {
                                                                                                                                                       ++t;
                                                                                                                                                   }
                                                                                                                                               } while(xx++ != xx__end__);}
                                                                                                                  } while(yy++ != yy__end__);}
                                                                                         if(t > 8)
                                                                                         {
                                                                                             (*Preview)[y][x] = (*Preview)[y][x] | (0x80 >> bit);
                                                                                         }
                                                                                     } while(bit++ != bit__end__);}
                                                      } while(x++ != x__end__);}
                           } while(y++ != y__end__);}
};
void uland_GenPreviewAlpha(TPreviewAlpha (*Preview))
{
    LongInt rh;
    LongInt rw;
    LongInt ox;
    LongInt oy;
    LongInt x;
    LongInt y;
    LongInt xx;
    LongInt yy;
    LongInt t;
    LongInt lh;
    LongInt lw;
    uconsole_WriteLnToConsole(__str37);
    switch(cMapGen)
    {case mgRandom:ulandutils_GenerateOutlineTemplatedLand(cFeatureSize, cSeed, uland_SelectTemplate(), PathPrefix);
                   break;
     case mgMaze:ulandutils_GenerateMazeLand(cFeatureSize, cSeed, uland_SelectTemplate(), PathPrefix);
                 break;
     case mgPerlin:{
                       ulandutils_ResizeLand(4096, 2048);
                       ulandgenperlin_GenPerlin();
                   }
                   break;
     case mgDrawn:{
                      uland_GenDrawnMap();
                  }
                  break;
     case mgForts:uland_MakeFortsPreview();
                  break;
     case mgWFC:ulandutils_GenerateWfcTemplatedLand(cFeatureSize, cSeed, uland_SelectTemplate(), PathPrefix);
                break;
     default: udebug_OutError(__str36, true);}
    uscript_ScriptSetMapGlobals();
    if(cMapGen != mgDrawn)
    {
        rh = uutils_Max(LAND_HEIGHT, 2048);
        rw = uutils_Max(LAND_WIDTH, 4096);
    }
    else
    {
        rh = LAND_HEIGHT;
        rw = LAND_WIDTH;
    }
    ox = 0;
    if(rw < (rh * 2))
    {
        rw = rh * 2;
    }
    if(rh < (rw / 2))
    {
        rh = rw * 2;
    }
    ox = (rw - LAND_WIDTH) / 2;
    oy = rh - LAND_HEIGHT;
    lh = rh / 128;
    lw = rw / 256;
    {y = 0;
     LongInt y__end__ = 127;
     if (y <= y__end__) do {
                               {x = 0;
                                LongInt x__end__ = 255;
                                if (x <= x__end__) do {
                                                          t = 0;
                                                          {yy = (y * lh) - oy;
                                                           LongInt yy__end__ = (((y * lh) + lh) - 1) - oy;
                                                           if (yy <= yy__end__) do {
                                                                                       {xx = (x * lw) - ox;
                                                                                        LongInt xx__end__ = (((x * lw) + lw) - 1) - ox;
                                                                                        if (xx <= xx__end__) do {
                                                                                                                    if((((yy & LAND_HEIGHT_MASK) == 0) && ((xx & LAND_WIDTH_MASK) == 0)) && (ulandutils_LandGet(yy, xx) != 0))
                                                                                                                    {
                                                                                                                        ++t;
                                                                                                                    }
                                                                                                                } while(xx++ != xx__end__);}
                                                                                   } while(yy++ != yy__end__);}
                                                          (*Preview)[y][x] = (t * 255) / (lh * lw);
                                                      } while(x++ != x__end__);}
                           } while(y++ != y__end__);}
};
void uland_chLandCheck(string255 (*s))
{
    uutils_AddFileLog(_strconcat(_strconcat(_strconcat(__str38, (*s)), __str39), digest));
    if(_strcompare(digest, __str6))
    {
        digest = (*s);
    }
    else
    {
        udebug_checkFails(_strcompare((*s), digest), __str40, true);
    }
};
void uland_chSendLandDigest(string255 (*s))
{
    LongInt i;
    LongInt landPixelDigest;
    landPixelDigest = 1;
    {i = 0;
     LongInt i__end__ = LAND_HEIGHT - 1;
     if (i <= i__end__) do {
                               landPixelDigest = adler32_Adler32Update(landPixelDigest, ulandutils_LandRow(i), LAND_WIDTH * 2);
                           } while(i++ != i__end__);}
    (*s) = _strconcat(_strappend(_strprepend(0x4d, uutils_IntToStr(syncedPixelDigest)), 0x7c), uutils_IntToStr(landPixelDigest));
    uscript_ScriptSetString(__str41, uutils_IntToStr(landPixelDigest));
    uland_chLandCheck(&((*s)));
    if(allOK)
    {
        uio_SendIPCRaw(&((*s).s[0]), fpcrtl_Length((*s)) + 1);
    }
};
void uland_initModule()
{
    ucommands_RegisterVariable_3(__str42, &(uland_chLandCheck), false);
    ucommands_RegisterVariable_3(__str43, &(uland_chSendLandDigest), false);
    LandBackSurface = NULL;
    digest = __str6;
    maskOnly = false;
    LAND_WIDTH = 0;
    LAND_HEIGHT = 0;
};
void uland_freeModule()
{
    ulandutils_DisposeLand();
    fpcrtl_SetLength(LandDirty, 0, 0);
};
