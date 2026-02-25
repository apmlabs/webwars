#include "fpcrtl.h"

#include "uStore.h"
#include "uMisc.h"
#include "uConsole.h"
#include "uVariables.h"
#include "uUtils.h"
#include "uTextures.h"
#include "uRender.h"
#include "uRenderUtils.h"
#include "uCommands.h"
#include "uPhysFSLayer.h"
#include "uDebug.h"
#include "uLocale.h"
#include "uInputHandler.h"
#include "adler32.h"
static const string255 __str56 = STRINIT("fullscr");
static const string255 __str55 = STRINIT("hwengine");
static const string255 __str54 = STRINIT("SDL_CreateWindow");
static const string255 __str53 = STRINIT("Hedgewars");
static const string255 __str52 = STRINIT("Freeing old primary surface...");
static const string255 __str51 = STRINIT("IMG_Init");
static const string255 __str50 = STRINIT("Init SDL_image... ");
static const string255 __str49 = STRINIT("Preparing to change video parameters...");
static const string255 __str48 = STRINIT("RenderHelpWindow: fail to create surface");
static const string255 __str47 = STRINIT(" ");
static const string255 __str46 = STRINIT("???");
static const string255 __str45 = STRINIT("Freeing progress textures... ");
static const string255 __str44 = STRINIT("Error - Progress or Loading texture is nil!");
static const string255 __str43 = STRINIT("Progress");
static const string255 __str42 = STRINIT("progress sprite: ");
static const string255 __str41 = STRINIT("SDLGLcontext");
static const string255 __str40 = STRINIT("Setting up OpenGL (using driver: ");
static const string255 __str39 = STRINIT("Settings file not found");
static const string255 __str38 = STRINIT("color");
static const string255 __str37 = STRINIT("[colors]");
static const string255 __str36 = STRINIT("Loading default clan colors from: ");
static const string255 __str35 = STRINIT("Got Hat");
static const string255 __str34 = STRINIT("Hat => ");
static const string255 __str33 = STRINIT(" [AD: ");
static const string255 __str32 = STRINIT(" [CD: ");
static const string255 __str31 = STRINIT("LoadImage: ");
static const string255 __str30 = STRINIT(".png");
static const string255 __str29 = STRINIT(".png [flags: ");
static const string255 __str28 = STRINIT("Number texture creation for ammo type #");
static const string255 __str27 = STRINIT(" failed!");
static const string255 __str26 = STRINIT("Name-texture creation for ammo type #");
static const string255 __str25 = STRINIT("No default text/translation found for ammo type #");
static const string255 __str24 = STRINIT("quit");
static const string255 __str23 = STRINIT("confirm");
static const string255 __str22 = STRINIT("Ammos_bw_ExtraDamage_comma");
static const string255 __str21 = STRINIT("Ammos_ExtraDamage_comma");
static const string255 __str20 = STRINIT("Reserved/chef");
static const string255 __str19 = STRINIT("StoreLoad()");
static const string255 __str18 = STRINIT("LoadFonts();");
static const string255 __str17 = STRINIT("TTF_OpenFontRW");
static const string255 __str16 = STRINIT("pt)... ");
static const string255 __str15 = STRINIT(" (");
static const string255 __str14 = STRINIT("Statue");
static const string255 __str13 = STRINIT("");
static const string255 __str12 = STRINIT("missions");
static const string255 __str11 = STRINIT("Reserved/");
static const string255 __str10 = STRINIT("Reserved");
static const string255 __str9 = STRINIT("fr_tomato");
static const string255 __str8 = STRINIT("fr_pumpkin");
static const string255 __str7 = STRINIT("Santa");
static const string255 __str6 = STRINIT("eastertop");
static const string255 __str5 = STRINIT("\" as well as the default flag");
static const string255 __str4 = STRINIT("Failed to load flag \"");
static const string255 __str3 = STRINIT("hedgewars");
static const string255 __str2 = STRINIT("cpu_plain");
static const string255 __str1 = STRINIT("cpu");
static const string255 __str0 = STRINIT("NoHat");
static LongInt squaresize;
static LongInt numsquares;
static PTexture ProgrTex;
static PTexture LoadingText;
static string255 prevHat;
static PSDL_Surface tmpHatSurf;
static const string255 cHHFileName = STRINIT("Hedgehog");
static const string255 cCHFileName = STRINIT("Crosshair");
void ustore_freeTmpHatSurf()
{
    if(tmpHatSurf == NULL)
    {
        return;
    }
    SDL_FreeSurface(tmpHatSurf);
    tmpHatSurf = NULL;
    prevHat = __str0;
};
void ustore_InitZoom(real zoom)
{
    urender_SetScale(zoom);
    urender_UpdateViewLimits();
};
TSDL_Rect ustore_WriteInRect(PSDL_Surface Surface,LongInt X,LongInt Y,LongWord Color,THWFont Font,PChar s)
{
    TSDL_Rect writeinrect_result;
    LongInt w;
    LongInt h;
    PSDL_Surface tmpsurf;
    TSDL_Color clr;
    TSDL_Rect finalRect;
    w = 0;
    h = 0;
    TTF_SizeUTF8(Fontz[Font].Handle, s, &(w), &(h));
    finalRect.x = (X + cFontBorder) + 2;
    finalRect.y = Y + cFontBorder;
    finalRect.w = (w + (cFontBorder * 2)) + 4;
    finalRect.h = h + (cFontBorder * 2);
    clr.r = Color >> 16;
    clr.g = (Color >> 8) & 0xff;
    clr.b = Color & 0xff;
    clr.a = 0xff;
    tmpsurf = TTF_RenderUTF8_Blended(Fontz[Font].Handle, s, clr);
    if(tmpsurf == NULL)
    {
        return finalRect;
    }
    tmpsurf = umisc_doSurfaceConversion(tmpsurf);
    if(tmpsurf != NULL)
    {
        SDL_UpperBlit(tmpsurf, NULL, Surface, &(finalRect));
        SDL_FreeSurface(tmpsurf);
        finalRect.x = X;
        finalRect.y = Y;
        finalRect.w = (w + (cFontBorder * 2)) + 4;
        finalRect.h = h + (cFontBorder * 2);
    }
    writeinrect_result = finalRect;
    return writeinrect_result;
};
void ustore_MakeCrossHairs()
{
    PSDL_Surface tmpsurf;
    tmpsurf = ustore_LoadDataImage(ptGraphics, cCHFileName, ifAlpha | ifCritical);
    CrosshairTexture = utextures_Surface2Tex(tmpsurf, false);
    SDL_FreeSurface(tmpsurf);
};
PTexture ustore_makeHealthBarTexture(LongWord w,LongWord h,LongWord Color)
{
    PTexture makehealthbartexture_result;
    TSDL_Rect rr;
    PSDL_Surface texsurf;
    rr.x = 0;
    rr.y = 0;
    rr.w = w;
    rr.h = h;
    texsurf = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, RMask, GMask, BMask, AMask);
    if(!udebug_checkFails(texsurf != NULL, errmsgCreateSurface, true))
    {
        udebug_checkFails(SDL_SetColorKey(texsurf, SDL_TRUE, 0) == 0, errmsgTransparentSet, true);
    }
    if(!allOK)
    {
        return NULL;
    }
    urenderutils_DrawRoundRect(&(rr), cWhiteColor, cNearBlackColor, texsurf, true);
    rr.x = 2;
    rr.y = 2;
    rr.w = w - 4;
    rr.h = h - 4;
    urenderutils_DrawRoundRect(&(rr), Color, Color, texsurf, false);
    makehealthbartexture_result = utextures_Surface2Tex(texsurf, false);
    SDL_FreeSurface(texsurf);
    return makehealthbartexture_result;
};
void ustore_WriteNames(THWFont Font)
{
    LongInt t;
    LongInt i;
    LongInt maxLevel;
    TSDL_Rect r;
    LongInt drY;
    PSDL_Surface texsurf;
    PSDL_Surface flagsurf;
    PSDL_Surface iconsurf;
    boolean foundBot;
    Word year;
    Word month;
    Word md;
    if(cOnlyStats)
    {
        return;
    }
    r.x = 0;
    r.y = 0;
    drY = -4;
    year = 0;
    month = 0;
    md = 0;
    {t = 0;
     LongInt t__end__ = ((int)(TeamsCount) - 1);
     if (t <= t__end__) do {
                               {
                                   if((*TeamsArray[t]).ExtDriven)
                                   {
                                       (*TeamsArray[t]).NameTagTex = urenderutils_RenderStringTexLim(fpcrtl_str2astr((*TeamsArray[t]).TeamName), (*TeamsArray[t]).Clan->Color, Font, cTeamHealthWidth);
                                   }
                                   else
                                   {
                                       (*TeamsArray[t]).NameTagTex = urenderutils_RenderStringTex(fpcrtl_str2astr((*TeamsArray[t]).TeamName), (*TeamsArray[t]).Clan->Color, Font);
                                   }
                                   if(fpcrtl_Length((*TeamsArray[t]).Owner) > 0)
                                   {
                                       if((*TeamsArray[t]).ExtDriven)
                                       {
                                           (*TeamsArray[t]).OwnerTex = urenderutils_RenderStringTexLim(fpcrtl_str2astr((*TeamsArray[t]).Owner), (*TeamsArray[t]).Clan->Color, Font, cTeamHealthWidth);
                                       }
                                       else
                                       {
                                           (*TeamsArray[t]).OwnerTex = urenderutils_RenderStringTex(fpcrtl_str2astr((*TeamsArray[t]).Owner), (*TeamsArray[t]).Clan->Color, Font);
                                       }
                                   }
                                   r.x = 0;
                                   r.y = 0;
                                   r.w = 32;
                                   r.h = 32;
                                   texsurf = SDL_CreateRGBSurface(SDL_SWSURFACE, r.w, r.h, 32, RMask, GMask, BMask, AMask);
                                   if(!udebug_checkFails(texsurf != NULL, errmsgCreateSurface, true))
                                   {
                                       udebug_checkFails(SDL_SetColorKey(texsurf, SDL_TRUE, 0) == 0, errmsgTransparentSet, true);
                                   }
                                   if(!allOK)
                                   {
                                       return;
                                   }
                                   r.w = 26;
                                   r.h = 19;
                                   urenderutils_DrawRoundRect(&(r), cWhiteColor, cNearBlackColor, texsurf, true);
                                   foundBot = false;
                                   maxLevel = -1;
                                   {i = 0;
                                    LongInt i__end__ = cMaxHHIndex;
                                    if (i <= i__end__) do {
                                                              {
                                                                  if(((*TeamsArray[t]).Hedgehogs[i].Gear != NULL) && ((*TeamsArray[t]).Hedgehogs[i].BotLevel > 0))
                                                                  {
                                                                      foundBot = true;
                                                                      if(maxLevel == -1)
                                                                      {
                                                                          maxLevel = (*TeamsArray[t]).Hedgehogs[i].BotLevel;
                                                                      }
                                                                      else
                                                                      {
                                                                          if((maxLevel > 0) && (maxLevel != (*TeamsArray[t]).Hedgehogs[i].BotLevel))
                                                                          {
                                                                              maxLevel = 0;
                                                                          }
                                                                      }
                                                                  }
                                                                  else
                                                                  {
                                                                      if((*TeamsArray[t]).Hedgehogs[i].Gear != NULL)
                                                                      {
                                                                          maxLevel = 0;
                                                                      }
                                                                  }
                                                              }
                                                          } while(i++ != i__end__);}
                                   if(foundBot)
                                   {
                                       (*TeamsArray[t]).Flag = __str1;
                                   }
                                   else
                                   {
                                       if((_strcompare((*TeamsArray[t]).Flag, __str1)) || (_strcompare((*TeamsArray[t]).Flag, __str2)))
                                       {
                                           (*TeamsArray[t]).Flag = __str3;
                                       }
                                   }
                                   flagsurf = ustore_LoadDataImageAltFile(ptFlags, (*TeamsArray[t]).Flag, __str3, ifNone);
                                   if(!udebug_checkFails(flagsurf != NULL, _strconcat(_strconcat(__str4, (*TeamsArray[t]).Flag), __str5), true))
                                   {
                                       switch(maxLevel)
                                       {case 1:urenderutils_copyToXY(SpritesData[sprBotlevels].Surface, flagsurf, 0, 0);
                                               break;
                                        case 2:urenderutils_copyToXYFromRect(SpritesData[sprBotlevels].Surface, flagsurf, 5, 2, 17, 13, 5, 2);
                                               break;
                                        case 3:urenderutils_copyToXYFromRect(SpritesData[sprBotlevels].Surface, flagsurf, 9, 5, 13, 10, 9, 5);
                                               break;
                                        case 4:urenderutils_copyToXYFromRect(SpritesData[sprBotlevels].Surface, flagsurf, 13, 9, 9, 6, 13, 9);
                                               break;
                                        case 5:urenderutils_copyToXYFromRect(SpritesData[sprBotlevels].Surface, flagsurf, 17, 11, 5, 4, 17, 11);
                                               break;
                                        default: break;}
                                       urenderutils_copyToXY(flagsurf, texsurf, 2, 2);
                                       SDL_FreeSurface(flagsurf);
                                       flagsurf = NULL;
                                   }
                                   (*((PLongWordArray)texsurf->pixels))[(32 * 2) + 2] = cNearBlackColor;
                                   (*((PLongWordArray)texsurf->pixels))[(32 * 2) + 23] = cNearBlackColor;
                                   (*((PLongWordArray)texsurf->pixels))[(32 * 16) + 2] = cNearBlackColor;
                                   (*((PLongWordArray)texsurf->pixels))[(32 * 16) + 23] = cNearBlackColor;
                                   (*TeamsArray[t]).FlagTex = utextures_Surface2Tex(texsurf, false);
                                   SDL_FreeSurface(texsurf);
                                   texsurf = NULL;
                                   if(!allOK)
                                   {
                                       return;
                                   }
                                   (*TeamsArray[t]).AIKillsTex = urenderutils_RenderStringTex(fpcrtl_str2astr(uutils_IntToStr((*TeamsArray[t]).stats.AIKills)), (*TeamsArray[t]).Clan->Color, fnt16);
                                   (*TeamsArray[t]).LuaTeamValueTex = urenderutils_RenderStringTex((*TeamsArray[t]).luaTeamValue, (*TeamsArray[t]).Clan->Color, fnt16);
                                   drY -= r.h + 2;
                                   (*TeamsArray[t]).DrawHealthY = drY;
                                   {i = 0;
                                    LongInt i__end__ = cMaxHHIndex;
                                    if (i <= i__end__) do {
                                                              {
                                                                  if((*TeamsArray[t]).Hedgehogs[i].Gear != NULL)
                                                                  {
                                                                      if((*TeamsArray[t]).ExtDriven)
                                                                      {
                                                                          (*TeamsArray[t]).Hedgehogs[i].NameTagTex = urenderutils_RenderStringTexLim(fpcrtl_str2astr((*TeamsArray[t]).Hedgehogs[i].Name), (*TeamsArray[t]).Clan->Color, fnt16, cTeamHealthWidth);
                                                                      }
                                                                      else
                                                                      {
                                                                          (*TeamsArray[t]).Hedgehogs[i].NameTagTex = urenderutils_RenderStringTex(fpcrtl_str2astr((*TeamsArray[t]).Hedgehogs[i].Name), (*TeamsArray[t]).Clan->Color, fnt16);
                                                                      }
                                                                      if(cHolidaySilliness)
                                                                      {
                                                                          if(_strcompare((*TeamsArray[t]).Hedgehogs[i].Hat, __str0))
                                                                          {
                                                                              if((month == 4) && (md == 20))
                                                                              {
                                                                                  (*TeamsArray[t]).Hedgehogs[i].Hat = __str6;
                                                                              }
                                                                              else
                                                                              {
                                                                                  if((month == 12) && (((md == 24) || (md == 25)) || (md == 26)))
                                                                                  {
                                                                                      (*TeamsArray[t]).Hedgehogs[i].Hat = __str7;
                                                                                  }
                                                                                  else
                                                                                  {
                                                                                      if((month == 10) && (md == 31))
                                                                                      {
                                                                                          (*TeamsArray[t]).Hedgehogs[i].Hat = __str8;
                                                                                      }
                                                                                  }
                                                                              }
                                                                          }
                                                                          if((month == 4) && (md == 1))
                                                                          {
                                                                              AprilOne = true;
                                                                              (*TeamsArray[t]).Hedgehogs[i].Hat = __str9;
                                                                          }
                                                                      }
                                                                      if(_strncompare((*TeamsArray[t]).Hedgehogs[i].Hat, __str0))
                                                                      {
                                                                          if(((fpcrtl_Length((*TeamsArray[t]).Hedgehogs[i].Hat) > 39) && (_strcompare(fpcrtl_copy((*TeamsArray[t]).Hedgehogs[i].Hat, 1, 8), __str10))) && (_strcompare(fpcrtl_copy((*TeamsArray[t]).Hedgehogs[i].Hat, 9, 32), (*TeamsArray[t]).PlayerHash)))
                                                                          {
                                                                              ustore_LoadHedgehogHat2(&((*TeamsArray[t]).Hedgehogs[i]), _strconcat(__str11, fpcrtl_copy((*TeamsArray[t]).Hedgehogs[i].Hat, 9, fpcrtl_Length((*TeamsArray[t]).Hedgehogs[i].Hat) - 8)), true);
                                                                          }
                                                                          else
                                                                          {
                                                                              ustore_LoadHedgehogHat2(&((*TeamsArray[t]).Hedgehogs[i]), (*TeamsArray[t]).Hedgehogs[i].Hat, true);
                                                                          }
                                                                      }
                                                                  }
                                                              }
                                                          } while(i++ != i__end__);}
                               }
                           } while(t++ != t__end__);}
    ustore_freeTmpHatSurf();
    MissionIcons = ustore_LoadDataImage(ptGraphics, __str12, ifCritical);
    iconsurf = SDL_CreateRGBSurface(SDL_SWSURFACE, 28, 28, 32, RMask, GMask, BMask, AMask);
    if(iconsurf != NULL)
    {
        r.x = 0;
        r.y = 0;
        r.w = 28;
        r.h = 28;
        urenderutils_DrawRoundRect(&(r), cWhiteColor, cNearBlackColor, iconsurf, true);
        ropeIconTex = utextures_Surface2Tex(iconsurf, false);
        SDL_FreeSurface(iconsurf);
        iconsurf = NULL;
    }
    {t = 0;
     LongInt t__end__ = ((int)(ClansCount) - 1);
     if (t <= t__end__) do {
                               {
                                   (*ClansArray[t]).HealthTex = ustore_makeHealthBarTexture(cTeamHealthWidth + 5, cTeamHealthHeight, (*ClansArray[t]).Color);
                               }
                           } while(t++ != t__end__);}
    GenericHealthTexture = ustore_makeHealthBarTexture(cTeamHealthWidth + 5, cTeamHealthHeight, cWhiteColor);
};
void ustore_InitHealth()
{
    LongInt i;
    LongInt t;
    {t = 0;
     LongInt t__end__ = ((int)(TeamsCount) - 1);
     if (t <= t__end__) do {
                               if(TeamsArray[t] != NULL)
                               {
                                   {
                                       {i = 0;
                                        LongInt i__end__ = cMaxHHIndex;
                                        if (i <= i__end__) do {
                                                                  if((*TeamsArray[t]).Hedgehogs[i].Gear != NULL)
                                                                  {
                                                                      ustore_RenderHealth(&((*TeamsArray[t]).Hedgehogs[i]));
                                                                  }
                                                              } while(i++ != i__end__);}
                                   }
                               }
                           } while(t++ != t__end__);}
};
void ustore_LoadGraves()
{
    LongInt t;
    PSDL_Surface texsurf;
    {t = 0;
     LongInt t__end__ = ((int)(TeamsCount) - 1);
     if (t <= t__end__) do {
                               if(TeamsArray[t] != NULL)
                               {
                                   {
                                       if(_strcompare((*TeamsArray[t]).GraveName, __str13))
                                       {
                                           (*TeamsArray[t]).GraveName = __str14;
                                       }
                                       texsurf = ustore_LoadDataImageAltFile(ptGraves, (*TeamsArray[t]).GraveName, __str14, ifCritical | ifColorKey);
                                       (*TeamsArray[t]).GraveTex = utextures_Surface2Tex(texsurf, false);
                                       SDL_FreeSurface(texsurf);
                                   }
                               }
                           } while(t++ != t__end__);}
};
void ustore_LoadFont(THWFont font)
{
    string255 s;
    {
        if(Fontz[font].Handle != NULL)
        {
            TTF_CloseFont(Fontz[font].Handle);
            Fontz[font].Handle = NULL;
        }
        s = _strconcat(_strappend(cPathz[ptFonts], 0x2f), Fontz[font].Name);
        uconsole_WriteToConsole(_strconcat(_strconcat(_strconcat(_strconcat(msgLoading, s), __str15), uutils_IntToStr(Fontz[font].Height)), __str16));
        Fontz[font].Handle = TTF_OpenFontRW(uphysfslayer_rwopsOpenRead(s), true, Fontz[font].Height);
        if(udebug_SDLCheck(Fontz[font].Handle != NULL, __str17, true))
        {
            return;
        }
        TTF_SetFontStyle(Fontz[font].Handle, Fontz[font].style);
        uconsole_WriteLnToConsole(msgOK);
    }
};
void ustore_LoadFonts()
{
    THWFont fi;
    uutils_AddFileLog(__str18);
    if(!cOnlyStats)
    {
        {fi = 0;
         THWFont fi__end__ = 7;
         if (fi <= fi__end__) do {
                                     ustore_LoadFont(fi);
                                 } while(fi++ != fi__end__);}
    }
};
void ustore_StoreLoad(boolean reload)
{
    TSprite ii;
    TAmmoType ai;
    PSDL_Surface tmpsurf;
    PSDL_Surface tmpoverlay;
    LongInt i;
    LongInt imflags;
    string255 keyConfirm;
    string255 keyQuit;
    uutils_AddFileLog(__str19);
    if(!cOnlyStats)
    {
        ustore_MakeCrossHairs();
        ustore_LoadGraves();
        tmpHatSurf = ustore_LoadDataImage(ptHats, __str20, ifNone);
        ChefHatTexture = utextures_Surface2Tex(tmpHatSurf, true);
        ustore_freeTmpHatSurf();
    }
    if(!reload)
    {
        ustore_AddProgress();
    }
    {ii = 0;
     TSprite ii__end__ = 219;
     if (ii <= ii__end__) do {
                                 {
                                     if(((((((((cReducedQuality & (rqNoBackground | rqLowRes)) == 0) || !(((ii == sprSky) || (ii == sprSkyL) || (ii == sprSkyR) || (ii == sprHorizont) || (ii == sprHorizontL) || (ii == sprHorizontR)))) && (((cReducedQuality & rqPlainSplash) == 0) || !(((ii == sprSplash) || (ii == sprDroplet) || (ii == sprSDSplash) || (ii == sprSDDroplet))))) && ((((cReducedQuality & rqKillFlakes) == 0) || cSnow) || !(((ii == sprFlake) || (ii == sprSDFlake))))) && ((cCloudsNumber > 0) || (ii != sprCloud))) && ((vobCount > 0) || (ii != sprFlake))) && (SpritesData[ii].saveSurf || !cOnlyStats)) && allOK)
                                     {
                                         if(reload)
                                         {
                                             tmpsurf = SpritesData[ii].Surface;
                                         }
                                         else
                                         {
                                             imflags = ifAlpha | ifColorKey;
                                             if(SpritesData[ii].critical)
                                             {
                                                 imflags = imflags | ifCritical;
                                             }
                                             if(SpritesData[ii].checkSum)
                                             {
                                                 tmpsurf = ustore_LoadDataImageAltPath(SpritesData[ii].Path, SpritesData[ii].AltPath, SpritesData[ii].FileName, imflags | ifDigestAlpha);
                                             }
                                             else
                                             {
                                                 tmpsurf = ustore_LoadDataImageAltPath(SpritesData[ii].Path, SpritesData[ii].AltPath, SpritesData[ii].FileName, imflags);
                                             }
                                         }
                                         if(tmpsurf != NULL)
                                         {
                                             if(SpritesData[ii].getImageDimensions)
                                             {
                                                 SpritesData[ii].imageWidth = tmpsurf->w;
                                                 SpritesData[ii].imageHeight = tmpsurf->h;
                                             }
                                             if(SpritesData[ii].getDimensions)
                                             {
                                                 if(SpritesData[ii].Height == -1)
                                                 {
                                                     SpritesData[ii].Width = tmpsurf->w;
                                                     SpritesData[ii].Height = tmpsurf->h / watFrames;
                                                 }
                                                 else
                                                 {
                                                     if(SpritesData[ii].Height == -2)
                                                     {
                                                         SpritesData[ii].Width = tmpsurf->w;
                                                         SpritesData[ii].Height = tmpsurf->h / watSDFrames;
                                                     }
                                                     else
                                                     {
                                                         SpritesData[ii].Width = tmpsurf->w;
                                                         SpritesData[ii].Height = tmpsurf->h;
                                                     }
                                                 }
                                             }
                                             if(((ii == sprAMAmmos) || (ii == sprAMAmmosBW)))
                                             {
                                                 tmpoverlay = ustore_LoadDataImage(SpritesData[ii].Path, fpcrtl_copy(SpritesData[ii].FileName, 1, fpcrtl_Length(SpritesData[ii].FileName) - 5), imflags & ~ifCritical);
                                                 if(tmpoverlay != NULL)
                                                 {
                                                     urenderutils_copyToXY(tmpoverlay, tmpsurf, 0, 0);
                                                     SDL_FreeSurface(tmpoverlay);
                                                 }
                                                 if(lDecimalSeparator == 0x2c)
                                                 {
                                                     if(ii == sprAMAmmos)
                                                     {
                                                         tmpoverlay = ustore_LoadDataImage(ptAmmoMenu, __str21, ifNone);
                                                     }
                                                     else
                                                     {
                                                         tmpoverlay = ustore_LoadDataImage(ptAmmoMenu, __str22, ifNone);
                                                     }
                                                     if(tmpoverlay != NULL)
                                                     {
                                                         urenderutils_copyToXY(tmpoverlay, tmpsurf, urenderutils_GetSurfaceFrameCoordinateX(tmpsurf, (amExtraDamage) - 1, SpritesData[ii].Width, SpritesData[ii].Height), urenderutils_GetSurfaceFrameCoordinateY(tmpsurf, (amExtraDamage) - 1, SpritesData[ii].Height));
                                                         SDL_FreeSurface(tmpoverlay);
                                                     }
                                                 }
                                             }
                                             if(((ii == sprSky) || (ii == sprSkyL) || (ii == sprSkyR) || (ii == sprHorizont) || (ii == sprHorizontL) || (ii == sprHorizontR)))
                                             {
                                                 SpritesData[ii].Texture = utextures_Surface2Tex(tmpsurf, true);
                                                 SpritesData[ii].Texture->scale = 2;
                                             }
                                             else
                                             {
                                                 SpritesData[ii].Texture = utextures_Surface2Tex(tmpsurf, false);
                                                 if(((ii == sprWater) || (ii == sprSDWater)) && ((cReducedQuality & (rq2DWater | rqClampLess)) == 0))
                                                 {
                                                     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                                                 }
                                             }
                                             if(!reload)
                                             {
                                                 if(SpritesData[ii].saveSurf)
                                                 {
                                                     SpritesData[ii].Surface = tmpsurf;
                                                 }
                                                 else
                                                 {
                                                     SDL_FreeSurface(tmpsurf);
                                                 }
                                             }
                                         }
                                         else
                                         {
                                             SpritesData[ii].Surface = NULL;
                                         }
                                     }
                                 }
                             } while(ii++ != ii__end__);}
    if(!cOnlyStats && allOK)
    {
        ustore_WriteNames(fnt16);
        if(!reload)
        {
            ustore_AddProgress();
        }
        tmpsurf = ustore_LoadDataImage(ptGraphics, cHHFileName, (ifAlpha | ifCritical) | ifColorKey);
        HHTexture = utextures_Surface2Tex(tmpsurf, false);
        SDL_FreeSurface(tmpsurf);
        ustore_InitHealth();
        PauseTexture = urenderutils_RenderStringTex(trmsg[sidPaused], cCentralMessageColor, fntBig);
        AFKTexture = urenderutils_RenderStringTex(trmsg[sidAFK], cCentralMessageColor, fntBig);
        keyConfirm = uinputhandler_KeyBindToName(__str23);
        keyQuit = uinputhandler_KeyBindToName(__str24);
        ConfirmTexture = urenderutils_RenderStringTex(ulocale_FormatA_3(trmsg[sidConfirm], fpcrtl_str2astr(keyConfirm), fpcrtl_str2astr(keyQuit)), cCentralMessageColor, fntBig);
        SyncTexture = urenderutils_RenderStringTex(trmsg[sidSync], cCentralMessageColor, fntBig);
        if(!reload)
        {
            ustore_AddProgress();
        }
        {ai = 0;
         TAmmoType ai__end__ = 60;
         if (ai <= ai__end__) do {
                                     {
                                         if(udebug_checkFails(fpcrtl_LengthA(trammo[Ammoz[ai].NameId]) > 0, _strappend(_strconcat(__str25, uutils_IntToStr((ai))), 0x21), true))
                                         {
                                             return;
                                         }
                                         tmpsurf = TTF_RenderUTF8_Blended(Fontz[uutils_CheckCJKFont(trammo[Ammoz[ai].NameId], fnt16)].Handle, fpcrtl__pcharA(trammo[Ammoz[ai].NameId]), cWhiteColorChannels);
                                         if(udebug_checkFails(tmpsurf != NULL, _strconcat(_strconcat(__str26, uutils_IntToStr((ai))), __str27), true))
                                         {
                                             return;
                                         }
                                         tmpsurf = umisc_doSurfaceConversion(tmpsurf);
                                         utextures_FreeAndNilTexture(&(Ammoz[ai].NameTex));
                                         Ammoz[ai].NameTex = utextures_Surface2Tex(tmpsurf, false);
                                         SDL_FreeSurface(tmpsurf);
                                     }
                                 } while(ai++ != ai__end__);}
        {i = 0;
         LongInt i__end__ = (AMMO_INFINITE - 1);
         if (i <= i__end__) do {
                                   tmpsurf = TTF_RenderUTF8_Blended(Fontz[uutils_CheckCJKFont(trmsg[sidAmmoCount], fnt16)].Handle, uutils_Str2PChar(ulocale_Format_2(fpcrtl_astr2str(trmsg[sidAmmoCount]), uutils_IntToStr(i))), cWhiteColorChannels);
                                   if(udebug_checkFails(tmpsurf != NULL, _strconcat(_strconcat(__str28, uutils_IntToStr((ai))), __str27), true))
                                   {
                                       return;
                                   }
                                   tmpsurf = umisc_doSurfaceConversion(tmpsurf);
                                   utextures_FreeAndNilTexture(&(CountTexz[i]));
                                   CountTexz[i] = utextures_Surface2Tex(tmpsurf, false);
                                   SDL_FreeSurface(tmpsurf);
                               } while(i++ != i__end__);}
        if(!reload)
        {
            ustore_AddProgress();
        }
    }
    IMG_Quit();
};
void ustore_StoreRelease(boolean reload)
{
    TSprite ii;
    TAmmoType ai;
    LongInt i;
    LongInt t;
    {ii = 0;
     TSprite ii__end__ = 219;
     if (ii <= ii__end__) do {
                                 utextures_FreeAndNilTexture(&(SpritesData[ii].Texture));
                                 if((SpritesData[ii].Surface != NULL) && !reload)
                                 {
                                     SDL_FreeSurface(SpritesData[ii].Surface);
                                     SpritesData[ii].Surface = NULL;
                                 }
                             } while(ii++ != ii__end__);}
    SDL_FreeSurface(MissionIcons);
    utextures_FreeAndNilTexture(&(ChefHatTexture));
    utextures_FreeAndNilTexture(&(CrosshairTexture));
    utextures_FreeAndNilTexture(&(WeaponTooltipTex));
    utextures_FreeAndNilTexture(&(PauseTexture));
    utextures_FreeAndNilTexture(&(AFKTexture));
    utextures_FreeAndNilTexture(&(SyncTexture));
    utextures_FreeAndNilTexture(&(ConfirmTexture));
    utextures_FreeAndNilTexture(&(ropeIconTex));
    utextures_FreeAndNilTexture(&(HHTexture));
    utextures_FreeAndNilTexture(&(GenericHealthTexture));
    {ai = 0;
     TAmmoType ai__end__ = 60;
     if (ai <= ai__end__) do {
                                 utextures_FreeAndNilTexture(&(Ammoz[ai].NameTex));
                             } while(ai++ != ai__end__);}
    {i = 0;
     LongInt i__end__ = (AMMO_INFINITE - 1);
     if (i <= i__end__) do {
                               utextures_FreeAndNilTexture(&(CountTexz[i]));
                               CountTexz[i] = NULL;
                           } while(i++ != i__end__);}
    {t = 0;
     LongInt t__end__ = ((int)(ClansCount) - 1);
     if (t <= t__end__) do {
                               if(ClansArray[t] != NULL)
                               {
                                   utextures_FreeAndNilTexture(&(ClansArray[t]->HealthTex));
                               }
                           } while(t++ != t__end__);}
    {t = 0;
     LongInt t__end__ = ((int)(TeamsCount) - 1);
     if (t <= t__end__) do {
                               if(TeamsArray[t] != NULL)
                               {
                                   utextures_FreeAndNilTexture(&(TeamsArray[t]->NameTagTex));
                                   utextures_FreeAndNilTexture(&(TeamsArray[t]->GraveTex));
                                   utextures_FreeAndNilTexture(&(TeamsArray[t]->AIKillsTex));
                                   utextures_FreeAndNilTexture(&(TeamsArray[t]->FlagTex));
                                   {i = 0;
                                    LongInt i__end__ = cMaxHHIndex;
                                    if (i <= i__end__) do {
                                                              utextures_FreeAndNilTexture(&(TeamsArray[t]->Hedgehogs[i].NameTagTex));
                                                              utextures_FreeAndNilTexture(&(TeamsArray[t]->Hedgehogs[i].HealthTagTex));
                                                              utextures_FreeAndNilTexture(&(TeamsArray[t]->Hedgehogs[i].HatTex));
                                                          } while(i++ != i__end__);}
                               }
                           } while(t++ != t__end__);}
    urender_RendererCleanup();
};
void ustore_RenderHealth(THedgehog (*Hedgehog))
{
    string255 s;
    utextures_FreeAndNilTexture(&((*Hedgehog).HealthTagTex));
    if((*Hedgehog).Gear != NULL)
    {
        s = uutils_IntToStr((*(*Hedgehog).Gear).Health);
    }
    else
    {
        if((*Hedgehog).GearHidden != NULL)
        {
            s = uutils_IntToStr((*(*Hedgehog).GearHidden).Health);
        }
        else
        {
            return;
        }
    }
    (*Hedgehog).HealthTagTex = urenderutils_RenderStringTex(fpcrtl_str2astr(s), (*(*(*Hedgehog).Team).Clan).Color, fnt16);
};
PSDL_Surface ustore_LoadImage(string255 filename,LongInt imageFlags)
{
    PSDL_Surface loadimage_result;
    PSDL_Surface tmpsurf;
    string255 s;
    string255 logMsg;
    string255 digestMsg;
    PSDL_RWops rwops;
    LongInt y;
    LongInt x;
    PByteArray rowData;
    loadimage_result = NULL;
    digestMsg = __str13;
    logMsg = _strappend(_strconcat(_strconcat(_strconcat(msgLoading, filename), __str29), uutils_IntToStr(imageFlags)), 0x5d);
    s = _strconcat(filename, __str30);
    rwops = NULL;
    tmpsurf = NULL;
    if(uphysfslayer_pfsExists(s))
    {
        rwops = uphysfslayer_rwopsOpenRead(s);
        if(rwops != NULL)
        {
            tmpsurf = IMG_Load_RW(rwops, true);
        }
    }
    if(tmpsurf == NULL)
    {
        if(rwops != NULL)
        {
            if((imageFlags & ifCritical) != 0)
            {
                udebug_OutError(_strconcat(_strappend(logMsg, 0x20), msgFailed), false);
            }
            if(udebug_SDLCheck(false, _strconcat(_strappend(_strconcat(__str31, logMsg), 0x20), msgFailed), (imageFlags & ifCritical) != 0))
            {
                return loadimage_result;
            }
            rwops = NULL;
        }
        else
        {
            if((imageFlags & ifCritical) != 0)
            {
                udebug_OutError(_strconcat(_strappend(logMsg, 0x20), msgFailed), (imageFlags & ifCritical) != 0);
            }
        }
        return loadimage_result;
    }
    if(((imageFlags & ifIgnoreCaps) == 0) && ((tmpsurf->w > MaxTextureSize) || (tmpsurf->h > MaxTextureSize)))
    {
        SDL_FreeSurface(tmpsurf);
        udebug_OutError(_strconcat(_strappend(logMsg, 0x20), msgFailedSize), !cOnlyStats && ((imageFlags & ifCritical) != 0));
        loadimage_result = SDL_CreateRGBSurface(SDL_SWSURFACE, 2, 2, 32, RMask, GMask, BMask, AMask);
        return loadimage_result;
    }
    tmpsurf = umisc_doSurfaceConversion(tmpsurf);
    if((imageFlags & ifColorKey) != 0)
    {
        if(udebug_checkFails(SDL_SetColorKey(tmpsurf, SDL_TRUE, 0) == 0, errmsgTransparentSet, true))
        {
            return loadimage_result;
        }
    }
    if(((imageFlags & (ifDigestAll | ifDigestAlpha)) != 0) && ((*tmpsurf->format).BytesPerPixel == 4))
    {
        if(sdlh_SDL_MustLock(tmpsurf))
        {
            SDL_LockSurface(tmpsurf);
        }
        if((imageFlags & ifDigestAll) != 0)
        {
            {y = 0;
             LongInt y__end__ = tmpsurf->h - 1;
             if (y <= y__end__) do {
                                       syncedPixelDigest = adler32_Adler32Update(syncedPixelDigest, &((*((PByteArray)tmpsurf->pixels))[y * tmpsurf->pitch]), tmpsurf->w * 4);
                                   } while(y++ != y__end__);}
            digestMsg = _strappend(_strconcat(__str32, uutils_IntToStr(syncedPixelDigest)), 0x5d);
        }
        else
        {
            if((imageFlags & ifDigestAlpha) != 0)
            {
                rowData = fpcrtl_GetMem(tmpsurf->w);
                {y = 0;
                 LongInt y__end__ = tmpsurf->h - 1;
                 if (y <= y__end__) do {
                                           {x = 0;
                                            LongInt x__end__ = tmpsurf->w - 1;
                                            if (x <= x__end__) do {
                                                                      (*rowData)[x] = (*((PByteArray)tmpsurf->pixels))[((y * tmpsurf->pitch) + (x * 4)) + AByteIndex];
                                                                  } while(x++ != x__end__);}
                                           syncedPixelDigest = adler32_Adler32Update(syncedPixelDigest, rowData, tmpsurf->w);
                                       } while(y++ != y__end__);}
                fpcrtl_FreeMem(rowData, tmpsurf->w);
                digestMsg = _strappend(_strconcat(__str33, uutils_IntToStr(syncedPixelDigest)), 0x5d);
            }
        }
        if(sdlh_SDL_MustLock(tmpsurf))
        {
            SDL_UnlockSurface(tmpsurf);
        }
    }
    loadimage_result = tmpsurf;
    return loadimage_result;
};
PSDL_Surface ustore_LoadDataImage(TPathType path,string255 filename,LongInt imageFlags)
{
    PSDL_Surface loaddataimage_result;
    PSDL_Surface tmpsurf;
    tmpsurf = ustore_LoadImage(_strconcat(_strappend(cPathz[path], 0x2f), filename), imageFlags);
    loaddataimage_result = tmpsurf;
    return loaddataimage_result;
};
PSDL_Surface ustore_LoadDataImageAltPath(TPathType path,TPathType altPath,string255 filename,LongInt imageFlags)
{
    PSDL_Surface loaddataimagealtpath_result;
    PSDL_Surface tmpsurf;
    if(altPath == ptNone)
    {
        return ustore_LoadDataImage(path, filename, imageFlags);
    }
    tmpsurf = ustore_LoadDataImage(path, filename, imageFlags & ~ifCritical);
    if(tmpsurf == NULL)
    {
        tmpsurf = ustore_LoadDataImage(altPath, filename, imageFlags);
    }
    loaddataimagealtpath_result = tmpsurf;
    return loaddataimagealtpath_result;
};
PSDL_Surface ustore_LoadDataImageAltFile(TPathType path,string255 filename,string255 altFile,LongInt imageFlags)
{
    PSDL_Surface loaddataimagealtfile_result;
    PSDL_Surface tmpsurf;
    if(_strcompare(altFile, __str13))
    {
        return ustore_LoadDataImage(path, filename, imageFlags);
    }
    tmpsurf = ustore_LoadDataImage(path, filename, imageFlags & ~ifCritical);
    if(tmpsurf == NULL)
    {
        tmpsurf = ustore_LoadDataImage(path, altFile, imageFlags);
    }
    loaddataimagealtfile_result = tmpsurf;
    return loaddataimagealtfile_result;
};
void ustore_LoadHedgehogHat(THedgehog (*HH),string255 newHat)
{
    ustore_LoadHedgehogHat2(&((*HH)), newHat, false);
};
void ustore_LoadHedgehogHat2(THedgehog (*HH),string255 newHat,boolean allowSurfReuse)
{
    if((*HH).HatTex != NULL)
    {
        utextures_FreeAndNilTexture(&((*HH).HatTex));
    }
    if(_strncompare(newHat, prevHat))
    {
        ustore_freeTmpHatSurf();
        tmpHatSurf = ustore_LoadDataImage(ptHats, newHat, ifNone);
    }
    uutils_AddFileLog(_strconcat(__str34, newHat));
    if(tmpHatSurf != NULL)
    {
        uutils_AddFileLog(__str35);
        (*HH).HatTex = utextures_Surface2Tex(tmpHatSurf, true);
        if(allowSurfReuse)
        {
            prevHat = newHat;
        }
        else
        {
            ustore_freeTmpHatSurf();
        }
    }
};
void ustore_LoadDefaultClanColors(string255 s)
{
    LongInt i;
    PFSFile f;
    string255 key;
    string255 value;
    string255 l;
    string255 temp;
    LongWord color;
    LongWord tempColor;
    Byte clanID;
    Byte tempClanID;
    if(cOnlyStats)
    {
        return;
    }
    uconsole_WriteLnToConsole(_strconcat(__str36, s));
    l = __str13;
    if(uphysfslayer_pfsExists(s))
    {
        f = uphysfslayer_pfsOpenRead(s);
        while(!uphysfslayer_pfsEOF(f) && (_strncompare(l, __str37)))
        {
            uphysfslayer_pfsReadLn(f, &(l));
        }
        while(!uphysfslayer_pfsEOF(f) && (_strncompare(l, __str13)))
        {
            uphysfslayer_pfsReadLn(f, &(l));
            key = __str13;
            i = 1;
            while((i <= fpcrtl_Length(l)) && (l.s[i] != 0x3d))
            {
                key = _strappend(key, l.s[i]);
                ++i;
            }
            temp = fpcrtl_copy(key, 1, 5);
            if(_strcompare(temp, __str38))
            {
                temp = fpcrtl_copy(key, 6, fpcrtl_Length(key) - 5);
                tempClanID = uutils_StrToInt(temp);
                clanID = tempClanID;
            }
            else
            {
                continue;
            }
            if(i < fpcrtl_Length(l))
            {
                value = fpcrtl_copy(l, i + 1, fpcrtl_Length(l) - i);
                if((fpcrtl_Length(value) == 2) && (value.s[1] == 0x5c))
                {
                    value = _strprepend(value.s[1], __str13);
                }
                else
                {
                    if((value.s[1] == 0x22) && (value.s[fpcrtl_Length(value)] == 0x22))
                    {
                        value = fpcrtl_copy(value, 2, fpcrtl_Length(value) - 2);
                    }
                }
                if(value.s[1] != 0x23)
                {
                    continue;
                }
                temp = fpcrtl_copy(value, 2, fpcrtl_Length(value) - 1);
                tempColor = uutils_StrToInt(_strprepend(0x24, temp));
                color = tempColor;
            }
            if(clanID <= cClanColors)
            {
                ClanColorArray[clanID] = color;
            }
        }
        uphysfslayer_pfsClose(f);
    }
    else
    {
        uconsole_WriteLnToConsole(__str39);
    }
};
void ustore_SetupOpenGLAttributes()
{
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
};
void ustore_SetupOpenGL()
{
    uutils_AddFileLog(_strappend(_strconcat(__str40, fpcrtl_pchar2str(SDL_GetCurrentVideoDriver())), 0x29));
    if(SDLGLcontext == NULL)
    {
        SDLGLcontext = SDL_GL_CreateContext(SDLwindow);
    }
    if(udebug_SDLCheck(SDLGLcontext != NULL, __str41, true))
    {
        return;
    }
    SDL_GL_SetSwapInterval(1);
    urender_RendererSetup();
};
void ustore_AddProgress()
{
    TSDL_Rect r;
    PSDL_Surface texsurf;
    if(cOnlyStats)
    {
        return;
    }
    if(Step == 0)
    {
        uconsole_WriteToConsole(_strconcat(msgLoading, __str42));
        texsurf = ustore_LoadDataImage(ptGraphics, __str43, ifCritical | ifColorKey);
        ProgrTex = utextures_Surface2Tex(texsurf, false);
        LoadingText = urenderutils_RenderStringTex(trmsg[sidLoading], 0xfff39ee8, fntBig);
        squaresize = texsurf->w >> 1;
        numsquares = texsurf->h / squaresize;
        SDL_FreeSurface(texsurf);
    }
    if(udebug_checkFails((ProgrTex != NULL) && (LoadingText != NULL), __str44, true))
    {
        return;
    }
    urender_RenderClear();
    if(Step < numsquares)
    {
        r.x = 0;
    }
    else
    {
        r.x = squaresize;
    }
    r.y = (Step % numsquares) * squaresize;
    r.w = squaresize;
    r.h = squaresize;
    urender_DrawTextureFromRect_4(-squaresize / 2, (cScreenHeight - squaresize) >> 1, &(r), ProgrTex);
    urender_DrawTexture_3(-LoadingText->w / 2, ((((cScreenHeight - LoadingText->h) >> 1) - (squaresize / 2)) - (LoadingText->h / 2)) - 8, LoadingText);
    ustore_SwapBuffers();
    ++Step;
};
void ustore_FinishProgress()
{
    uconsole_WriteLnToConsole(__str45);
    utextures_FreeAndNilTexture(&(ProgrTex));
    utextures_FreeAndNilTexture(&(LoadingText));
    Step = 0;
};
PTexture ustore_RenderHelpWindow(astring caption,astring subcaption,astring description,astring extra,LongInt extracolor,PSDL_Surface iconsurf,PSDL_Rect iconrect)
{
    PTexture renderhelpwindow_result;
    PSDL_Surface tmpsurf;
    LongInt w;
    LongInt h;
    LongInt i;
    LongInt j;
    THWFont font;
    TSDL_Rect r;
    TSDL_Rect r2;
    LongInt wa;
    LongInt ha;
    astring tmpline;
    astring tmpline2;
    astring tmpline3;
    astring tmpdesc;
    if(fpcrtl_LengthA(caption) == 0)
    {
        caption = fpcrtl_str2astr(__str46);
    }
    if(fpcrtl_LengthA(subcaption) == 0)
    {
        subcaption = fpcrtl_str2astr(__str47);
    }
    font = uutils_CheckCJKFont(caption, fnt16);
    font = uutils_CheckCJKFont(subcaption, font);
    font = uutils_CheckCJKFont(description, font);
    font = uutils_CheckCJKFont(extra, font);
    w = 0;
    h = 0;
    wa = (cFontBorder * 2) + 4;
    ha = cFontBorder * 2;
    i = 0;
    j = 0;
    TTF_SizeUTF8(Fontz[font].Handle, fpcrtl__pcharA(caption), &(i), &(j));
    w = (i + 36) + wa;
    h = j + ha;
    TTF_SizeUTF8(Fontz[font].Handle, fpcrtl__pcharA(subcaption), &(i), &(j));
    if(w < ((i + 36) + wa))
    {
        w = (i + 36) + wa;
    }
    h += j + ha;
    tmpdesc = description;
    while(fpcrtl_LengthA(tmpdesc) > 0)
    {
        tmpline = tmpdesc;
        uutils_EscapeCharA(&(tmpline), 0x7c);
        uutils_SplitByCharA(&(tmpline), &(tmpdesc), 0x7c);
        uutils_UnEscapeCharA(&(tmpline), 0x7c);
        if(fpcrtl_LengthA(tmpline) > 0)
        {
            TTF_SizeUTF8(Fontz[font].Handle, fpcrtl__pcharA(tmpline), &(i), &(j));
            if(w < (i + wa))
            {
                w = i + wa;
            }
            h += j + ha;
        }
    }
    if(fpcrtl_LengthA(extra) > 0)
    {
        TTF_SizeUTF8(Fontz[font].Handle, fpcrtl__pcharA(extra), &(i), &(j));
        if(w < (i + wa))
        {
            w = i + wa;
        }
        h += j + ha;
    }
    w += wa;
    h += ha + 8;
    tmpsurf = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, RMask, GMask, BMask, AMask);
    if(udebug_checkFails(tmpsurf != NULL, __str48, true))
    {
        return NULL;
    }
    r.x = 0;
    r.y = 0;
    r.w = w;
    r.h = h;
    urenderutils_DrawRoundRect(&(r), cWhiteColor, cNearBlackColor, tmpsurf, true);
    r = ustore_WriteInRect(tmpsurf, (36 + cFontBorder) + 2, ha, 0xffffffff, font, fpcrtl__pcharA(caption));
    r = ustore_WriteInRect(tmpsurf, (36 + cFontBorder) + 2, r.y + r.h, 0xffc7c7c7, font, fpcrtl__pcharA(subcaption));
    tmpdesc = description;
    while(fpcrtl_LengthA(tmpdesc) > 0)
    {
        tmpline = tmpdesc;
        uutils_EscapeCharA(&(tmpline), 0x7c);
        uutils_SplitByCharA(&(tmpline), &(tmpdesc), 0x7c);
        uutils_UnEscapeCharA(&(tmpline), 0x7c);
        r2 = r;
        if(fpcrtl_LengthA(tmpline) > 0)
        {
            uutils_EscapeCharA(&(tmpline), 0x3a);
            tmpline2 = fpcrtl_str2astr(__str13);
            uutils_SplitByCharA(&(tmpline), &(tmpline2), 0x3a);
            if(fpcrtl_LengthA(tmpline2) > 0)
            {
                if(tmpline2.s[1] != 0x3a)
                {
                    tmpline = _strappendA(tmpline, 0x3a);
                    tmpline3 = _strconcatA(tmpline, tmpline2);
                }
                else
                {
                    tmpline3 = _strconcatA(tmpline, fpcrtl_copyA(tmpline2, 2, fpcrtl_LengthA(tmpline2) - 1));
                }
                uutils_UnEscapeCharA(&(tmpline3), 0x3a);
                r = ustore_WriteInRect(tmpsurf, cFontBorder + 2, r.y + r.h, 0xff707070, font, fpcrtl__pcharA(tmpline3));
                ustore_WriteInRect(tmpsurf, cFontBorder + 2, r2.y + r2.h, 0xffc7c7c7, font, fpcrtl__pcharA(tmpline));
            }
            else
            {
                uutils_UnEscapeCharA(&(tmpline), 0x3a);
                r = ustore_WriteInRect(tmpsurf, cFontBorder + 2, r.y + r.h, 0xff707070, font, fpcrtl__pcharA(tmpline));
            }
        }
    }
    if(fpcrtl_LengthA(extra) > 0)
    {
        r = ustore_WriteInRect(tmpsurf, cFontBorder + 2, r.y + r.h, extracolor, font, fpcrtl__pcharA(extra));
    }
    r.x = cFontBorder + 6;
    r.y = cFontBorder + 4;
    r.w = 32;
    r.h = 32;
    SDL_FillRect(tmpsurf, &(r), SDL_MapRGB(tmpsurf->format, 0, 0, 0));
    SDL_UpperBlit(iconsurf, iconrect, tmpsurf, &(r));
    renderhelpwindow_result = utextures_Surface2Tex(tmpsurf, true);
    SDL_FreeSurface(tmpsurf);
    return renderhelpwindow_result;
};
void ustore_RenderWeaponTooltip(TAmmoType atype)
{
    TSDL_Rect r;
    LongInt i;
    astring ammoname;
    astring ammocap;
    astring ammodesc;
    astring extra;
    LongInt extracolor;
    if((cReducedQuality & rqTooltipsOff) != 0)
    {
        WeaponTooltipTex = NULL;
        return;
    }
    utextures_FreeAndNilTexture(&(WeaponTooltipTex));
    i = ((LongInt)atype) - 1;
    r.x = (i >> 4) * 32;
    r.y = (i % 16) * 32;
    r.w = 32;
    r.h = 32;
    extra = fpcrtl_str2astr(__str13);
    extracolor = 0;
    if(trluaammoe[Ammoz[atype].NameId] == true)
    {
        if((CurrentTeam != NULL) && (Ammoz[atype].SkipTurns >= (*CurrentTeam->Clan).TurnNumber))
        {
            if((atype == amTardis) && SuddenDeathActive)
            {
                extra = trmsg[sidNotAvailableInSD];
            }
            else
            {
                extra = trmsg[sidNotYetAvailable];
            }
            extracolor = ((LongInt)0xffc77070);
        }
        else
        {
            if(((((GameFlags & gfInfAttack) != 0) && ((Ammoz[atype].Ammo.Propz & ammoprop_ForceTurnEnd) == 0)) || ((Ammoz[atype].Ammo.Propz & ammoprop_NoRoundEnd) != 0)) && !(PlacingHogs && (atype == amTeleport)))
            {
                extra = trmsg[sidNoEndTurn];
                extracolor = ((LongInt)0xff70c770);
            }
        }
    }
    if(fpcrtl_LengthA(trluaammo[Ammoz[atype].NameId]) > 0)
    {
        ammoname = trluaammo[Ammoz[atype].NameId];
    }
    else
    {
        ammoname = trammo[Ammoz[atype].NameId];
    }
    if(fpcrtl_LengthA(trluaammoc[Ammoz[atype].NameId]) > 0)
    {
        ammocap = trluaammoc[Ammoz[atype].NameId];
    }
    else
    {
        ammocap = trammoc[Ammoz[atype].NameId];
    }
    if(fpcrtl_LengthA(trluaammod[Ammoz[atype].NameId]) > 0)
    {
        ammodesc = trluaammod[Ammoz[atype].NameId];
    }
    else
    {
        ammodesc = trammod[Ammoz[atype].NameId];
    }
    if(fpcrtl_LengthA(trluaammoa[Ammoz[atype].NameId]) > 0)
    {
        ammodesc = _strconcatA(_strappendA(ammodesc, 0x7c), trluaammoa[Ammoz[atype].NameId]);
    }
    WeaponTooltipTex = ustore_RenderHelpWindow(ammoname, ammocap, ammodesc, extra, extracolor, SpritesData[sprAMAmmos].Surface, &(r));
};
void ustore_ShowWeaponTooltip(LongInt x,LongInt y)
{
    if(WeaponTooltipTex != NULL)
    {
        urender_DrawTexture_3(x, y, WeaponTooltipTex);
    }
};
void ustore_chFullScr(string255 (*s))
{
    LongWord flags = 0;
    boolean reinit = false;
    PSDL_Surface ico;
    LongInt x;
    LongInt y;
    if(cOnlyStats)
    {
        MaxTextureSize = 1024;
        return;
    }
    if(fpcrtl_Length((*s)) == 0)
    {
        cFullScreen = !cFullScreen;
    }
    else
    {
        cFullScreen = _strcomparec((*s), 0x31);
    }
    if(cFullScreen)
    {
        cScreenWidth = cFullscreenWidth;
        cScreenHeight = cFullscreenHeight;
    }
    else
    {
        cScreenWidth = cWindowedWidth;
        cScreenHeight = cWindowedHeight;
    }
    uutils_AddFileLog(__str49);
    if(SDLwindow == NULL)
    {
        uconsole_WriteToConsole(__str50);
        if(udebug_SDLCheck(IMG_Init(IMG_INIT_PNG) != 0, __str51, true))
        {
            return;
        }
        uconsole_WriteLnToConsole(msgOK);
    }
    else
    {
        AmmoMenuInvalidated = true;
        urender_SetScale(cDefaultZoomLevel);
        uutils_AddFileLog(__str52);
    }
    ustore_SetupOpenGLAttributes();
    x = SDL_WINDOWPOS_CENTERED_MASK;
    y = SDL_WINDOWPOS_CENTERED_MASK;
    if(SDLwindow == NULL)
    {
        flags = (SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN) | SDL_WINDOW_RESIZABLE;
        if(cFullScreen)
        {
            flags = flags | SDL_WINDOW_FULLSCREEN;
        }
        SDLwindow = SDL_CreateWindow(fpcrtl__pchar(__str53), x, y, cScreenWidth, cScreenHeight, flags);
    }
    else
    {
        if(fpcrtl_Length((*s)) == 0)
        {
            if(cFullScreen)
            {
                SDL_SetWindowSize(SDLwindow, cScreenWidth, cScreenHeight);
                SDL_SetWindowFullscreen(SDLwindow, SDL_WINDOW_FULLSCREEN);
            }
            else
            {
                SDL_SetWindowFullscreen(SDLwindow, 0);
                SDL_SetWindowSize(SDLwindow, cScreenWidth, cScreenHeight);
                SDL_SetWindowPosition(SDLwindow, x, y);
            }
            urender_UpdateViewLimits();
        }
    }
    if(udebug_SDLCheck(SDLwindow != NULL, __str54, true))
    {
        return;
    }
    ico = ustore_LoadDataImage(ptGraphics, __str55, ifIgnoreCaps);
    if(ico != NULL)
    {
        SDL_SetWindowIcon(SDLwindow, ico);
        SDL_FreeSurface(ico);
    }
    ustore_SetupOpenGL();
    if(reinit)
    {
        urender_RenderClear();
        if(SuddenDeathDmg)
        {
            ustore_SetSkyColor((SDSkyColor.r * (SDTint.r /(float) 255)) /(float) 255, (SDSkyColor.g * (SDTint.g /(float) 255)) /(float) 255, (SDSkyColor.b * (SDTint.b /(float) 255)) /(float) 255);
        }
        else
        {
            if((cReducedQuality & rqNoBackground) == 0)
            {
                ustore_SetSkyColor(SkyColor.r /(float) 255, SkyColor.g /(float) 255, SkyColor.b /(float) 255);
            }
            else
            {
                ustore_SetSkyColor(RQSkyColor.r /(float) 255, RQSkyColor.g /(float) 255, RQSkyColor.b /(float) 255);
            }
        }
        ucaptions_ReloadCaptions(false);
        uchat_ReloadLines();
        ustore_StoreLoad(true);
        ulandtexture_UpdateLandTexture(0, LAND_WIDTH, 0, LAND_HEIGHT, false);
    }
};
void ustore_WarpMouse(Word x,Word y)
{
    SDL_WarpMouseInWindow(SDLwindow, x, y);
};
inline void ustore_SwapBuffers()
{
    if(GameType == gmtRecord)
    {
        return;
    }
    SDL_GL_SwapWindow(SDLwindow);
};
void ustore_SetSkyColor(real r,real g,real b)
{
    urender_RenderSetClearColor(r, g, b, 0.99);
};
void ustore_initModule()
{
    TAmmoType ai;
    LongInt i;
    ucommands_RegisterVariable_3(__str56, &(ustore_chFullScr), true);
    cScaleFactor = 2.0;
    urender_UpdateViewLimits();
    Step = 0;
    ProgrTex = NULL;
    SupportNPOTT = false;
    {ai = 0;
     TAmmoType ai__end__ = 60;
     if (ai <= ai__end__) do {
                                 Ammoz[ai].NameTex = NULL;
                             } while(ai++ != ai__end__);}
    {i = 0;
     LongInt i__end__ = (AMMO_INFINITE - 1);
     if (i <= i__end__) do {
                               CountTexz[i] = NULL;
                           } while(i++ != i__end__);}
    SDLwindow = NULL;
    SDLGLcontext = NULL;
    prevHat = __str0;
    tmpHatSurf = NULL;
};
void ustore_freeModule()
{
    THWFont fi;
    ustore_StoreRelease(false);
    {fi = 0;
     THWFont fi__end__ = 7;
     if (fi <= fi__end__) do {
                                 {
                                     if(Fontz[fi].Handle != NULL)
                                     {
                                         TTF_CloseFont(Fontz[fi].Handle);
                                         Fontz[fi].Handle = NULL;
                                     }
                                 }
                             } while(fi++ != fi__end__);}
    TTF_Quit();
    SDL_GL_DeleteContext(SDLGLcontext);
    SDL_DestroyWindow(SDLwindow);
    SDL_Quit();
};
