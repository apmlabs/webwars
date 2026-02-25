#include "fpcrtl.h"

#include "uWorld.h"
#include "uStore.h"
#include "uMisc.h"
#include "uIO.h"
#include "uLocale.h"
#include "uSound.h"
#include "uAmmos.h"
#include "uVisualGears.h"
#include "uChat.h"
#include "uLandTexture.h"
#include "uVariables.h"
#include "uUtils.h"
#include "uTextures.h"
#include "uRender.h"
#include "uCaptions.h"
#include "uCursor.h"
#include "uCommands.h"
#include "uTeams.h"
#include "uDebug.h"
#include "uInputHandler.h"
static const string255 __str4 = STRINIT("quit");
static const string255 __str3 = STRINIT(" failed!");
static const string255 __str2 = STRINIT("Name-texture creation for ammo type #");
static const string255 __str1 = STRINIT("No default text/translation found for ammo type #");
static const string255 __str0 = STRINIT("");
static LongInt AMShiftTargetX;
static LongInt AMShiftTargetY;
static LongInt AMShiftX;
static LongInt AMShiftY;
static LongInt SlotsNum;
static LongInt AMAnimStartTime;
static LongInt AMState;
static single AMAnimState;
static PSDL_Surface tmpSurface;
static PTexture fpsTexture;
static PTexture timeTexture;
static LongWord FPS;
static LongWord CountTicks;
static TPoint prevPoint;
static TAmmoType amSel = amNothing;
static PTexture missionTex;
static LongInt missionTimer;
static boolean isFirstFrame;
static LongInt AMAnimType;
static PTexture recTexture;
static PTexture AmmoMenuTex;
static LongInt HorizontOffset;
static LongInt cOffsetY;
typedef HwColor4f WorldEnd_tt[(3 + 1)];
static WorldEnd_tt WorldEnd;
static WorldEnd_tt WorldFade;
#define cStereo_Sky (5.0e-2)
;
#define cStereo_Horizon (2.5e-2)
;
#define cStereo_MidDistance (1.75e-2)
;
#define cStereo_Water_distant (1.25e-2)
;
#define cStereo_Land (7.5e-3)
;
#define cStereo_Water_near (2.5e-3)
;
#define cStereo_Outside (-4.0e-2)
;
enum{AMAnimDuration = 200};
enum{AMHidden = 0};
enum{AMShowingUp = 1};
enum{AMShowing = 2};
enum{AMHiding = 3};
enum{AMTypeMaskX = 0x00000001};
enum{AMTypeMaskY = 0x00000002};
enum{AMTypeMaskAlpha = 0x00000004};
enum{AMSlotSize = 32};
enum{AMSlotPadding = ((AMSlotSize - 32) >> 1)};
enum{amNumOffsetY = 0};
enum{amNumOffsetX = AMSlotSize};
enum{cSendCursorPosTime = 50};
enum{cCursorEdgesDist = 100};
astring uworld_AddGoal_4(astring s,LongWord gf,TGoalStrId si,LongInt i)
{
    astring addgoal_result;
    astring t;
    if((GameFlags & gf) != 0)
    {
        t = fpcrtl_str2astr(uutils_IntToStr(i));
        s = _strappendA(_strconcatA(s, ulocale_FormatA_2(trgoal[si], t)), 0x7c);
    }
    addgoal_result = s;
    return addgoal_result;
};
astring uworld_AddGoal_3(astring s,LongWord gf,TGoalStrId si)
{
    astring addgoal_result;
    if((GameFlags & gf) != 0)
    {
        s = _strappendA(_strconcatA(s, trgoal[si]), 0x7c);
    }
    addgoal_result = s;
    return addgoal_result;
};
void uworld_InitWorld()
{
    LongInt i;
    LongInt t;
    PClan cp;
    astring g;
    missionTimer = 0;
    if((GameFlags & gfRandomOrder) != 0)
    {
        {i = 0;
         LongInt i__end__ = ClansCount * 4;
         if (i <= i__end__) do {
                                   t = urandom_GetRandom(ClansCount);
                                   if(t != 0)
                                   {
                                       cp = ClansArray[0];
                                       ClansArray[0] = ClansArray[t];
                                       ClansArray[t] = cp;
                                       ClansArray[t]->ClanIndex = t;
                                       ClansArray[0]->ClanIndex = 0;
                                   }
                               } while(i++ != i__end__);}
        CurrentTeam = ClansArray[0]->Teams[0];
    }
    if((GameFlags & gfInvulnerable) != 0)
    {
        cTagsMask = cTagsMask & ~htHealth;
    }
    g = fpcrtl_str2astr(__str0);
    if(_strncompareA(LuaGoals, fpcrtl_str2astr(__str0)))
    {
        g = _strappendA(LuaGoals, 0x7c);
    }
    g = uworld_AddGoal_3(g, gfKing, gidKing);
    if(((GameFlags & gfKing) != 0) && ((GameFlags & gfPlaceHog) == 0))
    {
        g = uworld_AddGoal_3(g, gfAny, gidPlaceKing);
    }
    g = uworld_AddGoal_3(g, gfPlaceHog, gidPlaceHog);
    g = uworld_AddGoal_3(g, gfTagTeam, gidTagTeam);
    g = uworld_AddGoal_3(g, gfSharedAmmo, gidSharedAmmo);
    g = uworld_AddGoal_3(g, gfPerHogAmmo, gidPerHogAmmo);
    g = uworld_AddGoal_3(g, gfMoreWind, gidMoreWind);
    g = uworld_AddGoal_3(g, gfLowGravity, gidLowGravity);
    g = uworld_AddGoal_3(g, gfSolidLand, gidSolidLand);
    g = uworld_AddGoal_3(g, gfArtillery, gidArtillery);
    g = uworld_AddGoal_3(g, gfInfAttack, gidInfAttack);
    g = uworld_AddGoal_3(g, gfResetWeps, gidResetWeps);
    g = uworld_AddGoal_3(g, gfResetHealth, gidResetHealth);
    g = uworld_AddGoal_3(g, gfKarma, gidKarma);
    g = uworld_AddGoal_3(g, gfVampiric, gidVampiric);
    g = uworld_AddGoal_3(g, gfInvulnerable, gidInvulnerable);
    g = uworld_AddGoal_3(g, gfAISurvival, gidAISurvival);
    if(cDamagePercent != 100)
    {
        g = uworld_AddGoal_4(g, gfAny, gidDamageModifier, cDamagePercent);
    }
    ScreenFade = sfFromBlack;
    ScreenFadeValue = sfMax;
    ScreenFadeSpeed = 1;
    if(cMinesTime != 3000)
    {
        if(cMinesTime == 0)
        {
            g = uworld_AddGoal_3(g, gfAny, gidNoMineTimer);
        }
        else
        {
            if(cMinesTime < 0)
            {
                g = uworld_AddGoal_3(g, gfAny, gidRandomMineTimer);
            }
            else
            {
                g = uworld_AddGoal_4(g, gfAny, gidMineTimer, cMinesTime / 1000);
            }
        }
    }
    if(fpcrtl_LengthA(g) > 0)
    {
        if((GameFlags & gfKing) != 0)
        {
            uworld_ShowMission_5(trgoal[gidCaption], trgoal[gidSubCaption], g, 0, 0);
        }
        else
        {
            uworld_ShowMission_5(trgoal[gidCaption], trgoal[gidSubCaption], g, 1, 0);
        }
    }
    cWaveHeight = 32;
    uworld_InitCameraBorders();
    ucursor_init();
    prevPoint.x = 0;
    prevPoint.y = cScreenHeight / 2;
    WorldDx = -((LongInt)leftX + (playWidth / 2));
    WorldDy = -(LAND_HEIGHT - (playHeight / 2)) + (cScreenHeight / 2);
    SkyOffset = 0;
    HorizontOffset = 0;
    uworld_InitTouchInterface();
    AMAnimType = AMTypeMaskX | AMTypeMaskAlpha;
};
void uworld_InitCameraBorders()
{
    cGearScrEdgesDist = uutils_Min((2 * cScreenHeight) / 5, (2 * cScreenWidth) / 5);
};
void uworld_InitTouchInterface()
{
};
void uworld_ResetWorldTex()
{
    utextures_FreeAndNilTexture(&(fpsTexture));
    utextures_FreeAndNilTexture(&(timeTexture));
    utextures_FreeAndNilTexture(&(missionTex));
    utextures_FreeAndNilTexture(&(recTexture));
    utextures_FreeAndNilTexture(&(AmmoMenuTex));
    AmmoMenuInvalidated = true;
};
PTexture uworld_GetAmmoMenuTexture(PHHAmmo Ammo)
{
    PTexture getammomenutexture_result;
    enum{BORDERSIZE = 2};
    LongInt x;
    LongInt y;
    LongInt i;
    LongInt t;
    LongInt SlotsNumY;
    LongInt SlotsNumX;
    LongInt AMFrame;
    LongInt STurns;
    PSDL_Surface amSurface;
    TSDL_Rect AMRect;
    PSDL_Surface tmpsurf;
    boolean usesDefaultSlotKeys;
    if(cOnlyStats)
    {
        return NULL;
    }
    SlotsNum = 0;
    {i = 0;
     LongInt i__end__ = cMaxSlotIndex;
     if (i <= i__end__) do {
                               if((i != cHiddenSlotIndex) && ((*Ammo)[i][0].Count > 0))
                               {
                                   ++SlotsNum;
                               }
                           } while(i++ != i__end__);}
    SlotsNumX = cMaxSlotAmmoIndex + 1;
    SlotsNumY = SlotsNum + 1;
    ++SlotsNumX;
    AmmoRect.w = ((BORDERSIZE * 2) + (SlotsNumX * AMSlotSize)) + (SlotsNumX - 1);
    AmmoRect.h = ((BORDERSIZE * 2) + (SlotsNumY * AMSlotSize)) + (SlotsNumY - 1);
    amSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, AmmoRect.w, AmmoRect.h, 32, RMask, GMask, BMask, AMask);
    AMRect.x = BORDERSIZE;
    AMRect.y = BORDERSIZE;
    AMRect.w = AmmoRect.w - (BORDERSIZE * 2);
    AMRect.h = AmmoRect.h - (BORDERSIZE * 2);
    SDL_FillRect(amSurface, &(AMRect), SDL_MapRGB(amSurface->format, 0, 0, 0));
    x = AMRect.x;
    y = AMRect.y;
    usesDefaultSlotKeys = uinputhandler_CheckDefaultSlotKeys();
    {i = 0;
     LongInt i__end__ = cMaxSlotIndex;
     if (i <= i__end__) do {
                               if((i != cHiddenSlotIndex) && ((*Ammo)[i][0].Count > 0))
                               {
                                   x = AMRect.x;
                                   if(usesDefaultSlotKeys)
                                   {
                                       tmpsurf = TTF_RenderUTF8_Blended(Fontz[fnt16].Handle, uutils_Str2PChar(_strprepend(0x46, uutils_IntToStr(i + 1))), cWhiteColorChannels);
                                   }
                                   else
                                   {
                                       tmpsurf = TTF_RenderUTF8_Blended(Fontz[fnt16].Handle, uutils_Str2PChar(uutils_IntToStr(i + 1)), cWhiteColorChannels);
                                   }
                                   urenderutils_copyToXY(tmpsurf, amSurface, ((x + AMSlotPadding) + (AMSlotSize >> 1)) - (tmpsurf->w >> 1), ((y + AMSlotPadding) + (AMSlotSize >> 1)) - (tmpsurf->h >> 1));
                                   SDL_FreeSurface(tmpsurf);
                                   x = (AMRect.x + AMSlotSize) + 1;
                                   {t = 0;
                                    LongInt t__end__ = cMaxSlotAmmoIndex;
                                    if (t <= t__end__) do {
                                                              if(((*Ammo)[i][t].Count > 0) && ((*Ammo)[i][t].AmmoType != amNothing))
                                                              {
                                                                  STurns = ((int64_t) (Ammoz[(*Ammo)[i][t].AmmoType].SkipTurns)) - ((int64_t) ((*CurrentTeam->Clan).TurnNumber));
                                                                  AMFrame = ((LongInt)(*Ammo)[i][t].AmmoType) - 1;
                                                                  if(STurns >= 0)
                                                                  {
                                                                      urenderutils_DrawSpriteFrame2Surf(sprAMAmmosBW, amSurface, x + AMSlotPadding, y + AMSlotPadding, AMFrame);
                                                                      if(STurns < 100)
                                                                      {
                                                                          urenderutils_DrawSpriteFrame2Surf(sprTurnsLeft, amSurface, (x + AMSlotSize) - 16, ((y + AMSlotSize) + 1) - 16, STurns);
                                                                      }
                                                                  }
                                                                  else
                                                                  {
                                                                      urenderutils_DrawSpriteFrame2Surf(sprAMAmmos, amSurface, x + AMSlotPadding, y + AMSlotPadding, AMFrame);
                                                                  }
                                                                  x += AMSlotSize + 1;
                                                              }
                                                          } while(t++ != t__end__);}
                                   y += AMSlotSize + 1;
                               }
                           } while(i++ != i__end__);}
    {i = 1;
     LongInt i__end__ = SlotsNumX - 1;
     if (i <= i__end__) do {
                               urenderutils_DrawLine2Surf(amSurface, (i * (AMSlotSize + 1)) + 1, BORDERSIZE, (i * (AMSlotSize + 1)) + 1, ((AMRect.h + BORDERSIZE) - AMSlotSize) - 2, 160, 160, 160);
                           } while(i++ != i__end__);}
    {i = 1;
     LongInt i__end__ = SlotsNumY - 1;
     if (i <= i__end__) do {
                               urenderutils_DrawLine2Surf(amSurface, BORDERSIZE, (i * (AMSlotSize + 1)) + 1, AMRect.w + BORDERSIZE, (i * (AMSlotSize + 1)) + 1, 160, 160, 160);
                           } while(i++ != i__end__);}
    urenderutils_DrawSpriteFrame2Surf(sprAMCorners, amSurface, 0, 0, 0);
    urenderutils_DrawSpriteFrame2Surf(sprAMCorners, amSurface, AMRect.w + BORDERSIZE, AMRect.y, 1);
    urenderutils_DrawSpriteFrame2Surf(sprAMCorners, amSurface, AMRect.x, AMRect.h + BORDERSIZE, 2);
    urenderutils_DrawSpriteFrame2Surf(sprAMCorners, amSurface, AMRect.w + BORDERSIZE, AMRect.h + BORDERSIZE, 3);
    {i = 0;
     LongInt i__end__ = BORDERSIZE - 1;
     if (i <= i__end__) do {
                               urenderutils_DrawLine2Surf(amSurface, BORDERSIZE, i, AMRect.w + BORDERSIZE, i, 160, 160, 160);
                               urenderutils_DrawLine2Surf(amSurface, BORDERSIZE, (AMRect.h + BORDERSIZE) + i, AMRect.w + BORDERSIZE, (AMRect.h + BORDERSIZE) + i, 160, 160, 160);
                               urenderutils_DrawLine2Surf(amSurface, i, BORDERSIZE, i, AMRect.h + BORDERSIZE, 160, 160, 160);
                               urenderutils_DrawLine2Surf(amSurface, (AMRect.w + BORDERSIZE) + i, BORDERSIZE, (AMRect.w + BORDERSIZE) + i, AMRect.h + BORDERSIZE, 160, 160, 160);
                           } while(i++ != i__end__);}
    getammomenutexture_result = utextures_Surface2Tex(amSurface, false);
    if(amSurface != NULL)
    {
        SDL_FreeSurface(amSurface);
    }
    return getammomenutexture_result;
};
void uworld_ShowAmmoMenu()
{
    enum{BORDERSIZE = 2};
    LongInt Slot;
    LongInt Pos;
    PHHAmmo Ammo;
    LongInt c;
    LongInt i;
    LongInt g;
    LongInt t;
    LongInt STurns;
    if(TurnTimeLeft == 0)
    {
        bShowAmmoMenu = false;
    }
    Ammo = NULL;
    if((((CurrentTeam != NULL) && (CurrentHedgehog != NULL)) && !CurrentTeam->ExtDriven) && (CurrentHedgehog->BotLevel == 0))
    {
        Ammo = CurrentHedgehog->Ammo;
    }
    else
    {
        if(LocalAmmo != -1)
        {
            Ammo = uammos_GetAmmoByNum(LocalAmmo);
        }
    }
    Pos = -1;
    if(Ammo == NULL)
    {
        bShowAmmoMenu = false;
        AMState = AMHidden;
        return;
    }
    if(AmmoMenuInvalidated)
    {
        AmmoMenuInvalidated = false;
        utextures_FreeAndNilTexture(&(AmmoMenuTex));
        AmmoMenuTex = uworld_GetAmmoMenuTexture(Ammo);
        AmmoRect.x = ((cScreenWidth >> 1) - AmmoRect.w) - AMSlotSize;
        AmmoRect.y = cScreenHeight - (AmmoRect.h + AMSlotSize);
        if(AMState != AMShowing)
        {
            AMShiftTargetX = (cScreenWidth >> 1) - AmmoRect.x;
            AMShiftTargetY = cScreenHeight - AmmoRect.y;
            if((AMAnimType & AMTypeMaskX) != 0)
            {
                AMShiftTargetX = (cScreenWidth >> 1) - AmmoRect.x;
            }
            else
            {
                AMShiftTargetX = 0;
            }
            if((AMAnimType & AMTypeMaskY) != 0)
            {
                AMShiftTargetY = cScreenHeight - AmmoRect.y;
            }
            else
            {
                AMShiftTargetY = 0;
            }
            AMShiftX = AMShiftTargetX;
            AMShiftY = AMShiftTargetY;
        }
    }
    AMAnimState = (RealTicks - AMAnimStartTime) /(float) AMAnimDuration;
    if(AMState == AMShowing)
    {
        FollowGear = NULL;
    }
    if(AMState == AMShowingUp)
    {
        if(((cReducedQuality & rqSlowMenu) != 0) || (cHedgehogTurnTime <= 10000))
        {
            AMShiftX = 0;
            AMShiftY = 0;
            CursorPoint.x = (AmmoRect.x + AmmoRect.w) - 3;
            CursorPoint.y = ((cScreenHeight - AmmoRect.y) - amNumOffsetY) - 1;
            AMState = AMShowing;
        }
        else
        {
            if(AMAnimState < 1)
            {
                AMShiftX = fpcrtl_round(AMShiftTargetX * (1 - AMAnimState));
                AMShiftY = fpcrtl_round(AMShiftTargetY * (1 - AMAnimState));
                if((AMAnimType & AMTypeMaskAlpha) != 0)
                {
                    urender_Tint_4(0xff, 0xff, 0xff, fpcrtl_round(0xff * AMAnimState));
                }
            }
            else
            {
                AMShiftX = 0;
                AMShiftY = 0;
                CursorPoint.x = (AmmoRect.x + AmmoRect.w) - 3;
                CursorPoint.y = ((cScreenHeight - AmmoRect.y) - amNumOffsetY) - 1;
                AMState = AMShowing;
            }
        }
    }
    if(AMState == AMHiding)
    {
        if(((cReducedQuality & rqSlowMenu) != 0) || (cHedgehogTurnTime <= 10000))
        {
            AMShiftX = AMShiftTargetX;
            AMShiftY = AMShiftTargetY;
            prevPoint = CursorPoint;
            AMState = AMHidden;
        }
        else
        {
            if(AMAnimState < 1)
            {
                AMShiftX = fpcrtl_round(AMShiftTargetX * AMAnimState);
                AMShiftY = fpcrtl_round(AMShiftTargetY * AMAnimState);
                if((AMAnimType & AMTypeMaskAlpha) != 0)
                {
                    urender_Tint_4(0xff, 0xff, 0xff, fpcrtl_round(0xff * (1 - AMAnimState)));
                }
            }
            else
            {
                AMShiftX = AMShiftTargetX;
                AMShiftY = AMShiftTargetY;
                prevPoint = CursorPoint;
                AMState = AMHidden;
            }
        }
    }
    urender_DrawTexture_3(AmmoRect.x + AMShiftX, AmmoRect.y + AMShiftY, AmmoMenuTex);
    if(((AMState == AMHiding) || (AMState == AMShowingUp)) && ((AMAnimType & AMTypeMaskAlpha) != 0))
    {
        urender_untint();
    }
    Pos = -1;
    Slot = -1;
    c = -1;
    {i = 0;
     LongInt i__end__ = cMaxSlotIndex;
     if (i <= i__end__) do {
                               if((i != cHiddenSlotIndex) && ((*Ammo)[i][0].Count > 0))
                               {
                                   ++c;
                                   g = 1;
                                   {t = 0;
                                    LongInt t__end__ = cMaxSlotAmmoIndex;
                                    if (t <= t__end__) do {
                                                              if(((*Ammo)[i][t].Count > 0) && ((*Ammo)[i][t].AmmoType != amNothing))
                                                              {
                                                                  if((((CursorPoint.y <= ((cScreenHeight - AmmoRect.y) - (c * (AMSlotSize + 1)))) && (CursorPoint.y > ((cScreenHeight - AmmoRect.y) - ((c + 1) * (AMSlotSize + 1))))) && (CursorPoint.x > (AmmoRect.x + (g * (AMSlotSize + 1))))) && (CursorPoint.x <= (AmmoRect.x + ((g + 1) * (AMSlotSize + 1)))))
                                                                  {
                                                                      Slot = i;
                                                                      Pos = t;
                                                                      STurns = ((int64_t) (Ammoz[(*Ammo)[i][t].AmmoType].SkipTurns)) - ((int64_t) ((*CurrentTeam->Clan).TurnNumber));
                                                                      if(((STurns < 0) && (AMShiftX == 0)) && (AMShiftY == 0))
                                                                      {
                                                                          urender_DrawSprite_4(sprAMSlot, ((AmmoRect.x + BORDERSIZE) + (g * (AMSlotSize + 1))) + AMSlotPadding, (((AmmoRect.y + BORDERSIZE) + (c * (AMSlotSize + 1))) + AMSlotPadding) - 1, 0);
                                                                      }
                                                                  }
                                                                  ++g;
                                                              }
                                                          } while(t++ != t__end__);}
                               }
                           } while(i++ != i__end__);}
    if(((((Pos >= 0) && (Pos <= cMaxSlotAmmoIndex)) && (Slot >= 0)) && (Slot <= cMaxSlotIndex)) && (Slot != cHiddenSlotIndex))
    {
        if((AMShiftX == 0) && (AMShiftY == 0))
        {
            if(((*Ammo)[Slot][Pos].Count > 0) && ((*Ammo)[Slot][Pos].AmmoType != amNothing))
            {
                if((amSel != (*Ammo)[Slot][Pos].AmmoType) || (WeaponTooltipTex == NULL))
                {
                    amSel = (*Ammo)[Slot][Pos].AmmoType;
                    ustore_RenderWeaponTooltip(amSel);
                }
                urender_DrawTexture_3(AmmoRect.x + (AMSlotSize >> 1), (((AmmoRect.y + AmmoRect.h) - BORDERSIZE) - (AMSlotSize >> 1)) - ((*Ammoz[(*Ammo)[Slot][Pos].AmmoType].NameTex).h >> 1), Ammoz[(*Ammo)[Slot][Pos].AmmoType].NameTex);
                if((*Ammo)[Slot][Pos].Count < AMMO_INFINITE)
                {
                    urender_DrawTexture_3(((AmmoRect.x + AmmoRect.w) - 20) - CountTexz[(*Ammo)[Slot][Pos].Count]->w, (((AmmoRect.y + AmmoRect.h) - BORDERSIZE) - (AMSlotSize >> 1)) - (CountTexz[(*Ammo)[Slot][Pos].Count]->h >> 1), CountTexz[(*Ammo)[Slot][Pos].Count]);
                }
                if(bSelected && ((((int64_t) (Ammoz[(*Ammo)[Slot][Pos].AmmoType].SkipTurns)) - ((int64_t) ((*CurrentTeam->Clan).TurnNumber))) < 0))
                {
                    bShowAmmoMenu = false;
                    uammos_SetWeapon((*Ammo)[Slot][Pos].AmmoType);
                    bSelected = false;
                    utextures_FreeAndNilTexture(&(WeaponTooltipTex));
                    uworld_updateTouchWidgets((*Ammo)[Slot][Pos].AmmoType);
                    return;
                }
            }
        }
    }
    else
    {
        utextures_FreeAndNilTexture(&(WeaponTooltipTex));
    }
    if(((WeaponTooltipTex != NULL) && (AMShiftX == 0)) && (AMShiftY == 0))
    {
        ustore_ShowWeaponTooltip((AmmoRect.x - WeaponTooltipTex->w) - 3, uutils_Min(AmmoRect.y + 1, (cScreenHeight - WeaponTooltipTex->h) - 40));
    }
    bSelected = false;
    if((AMShiftX == 0) && (AMShiftY == 0))
    {
        urender_DrawSprite_4(sprArrow, CursorPoint.x, cScreenHeight - CursorPoint.y, (RealTicks >> 6) % 8);
    }
};
void uworld_DrawRepeated(TSprite spr,TSprite sprL,TSprite sprR,LongInt Shift,LongInt OffsetY)
{
    LongInt i;
    LongInt w;
    LongInt h;
    LongInt lw;
    LongInt lh;
    LongInt rw;
    LongInt rh;
    LongInt sw;
    sw = fpcrtl_round(cScreenWidth /(float) cScaleFactor);
    if((SpritesData[sprL].Texture == NULL) && (SpritesData[spr].Texture != NULL))
    {
        w = SpritesData[spr].Width * (*SpritesData[spr].Texture).scale;
        h = SpritesData[spr].Height * (*SpritesData[spr].Texture).scale;
        i = Shift % w;
        if(i > 0)
        {
            i -= w;
        }
        i -= w * ((sw / w) + 1);
        do {
               urender_DrawTexture_4(i, ((WorldDy + LAND_HEIGHT) + OffsetY) - h, SpritesData[spr].Texture, (*SpritesData[spr].Texture).scale);
               i += w;
           } while(!(i > sw));
    }
    else
    {
        if(SpritesData[spr].Texture != NULL)
        {
            w = SpritesData[spr].Width * (*SpritesData[spr].Texture).scale;
            h = SpritesData[spr].Height * (*SpritesData[spr].Texture).scale;
            lw = SpritesData[sprL].Width * (*SpritesData[spr].Texture).scale;
            lh = SpritesData[sprL].Height * (*SpritesData[spr].Texture).scale;
            if(SpritesData[sprR].Texture != NULL)
            {
                rw = SpritesData[sprR].Width * (*SpritesData[spr].Texture).scale;
                rh = SpritesData[sprR].Height * (*SpritesData[spr].Texture).scale;
            }
            Shift -= w / 2;
            urender_DrawTexture_4(Shift, ((WorldDy + LAND_HEIGHT) + OffsetY) - h, SpritesData[spr].Texture, (*SpritesData[spr].Texture).scale);
            i = Shift - lw;
            while(i >= (-sw - lw))
            {
                urender_DrawTexture_4(i, ((WorldDy + LAND_HEIGHT) + OffsetY) - lh, SpritesData[sprL].Texture, (*SpritesData[sprL].Texture).scale);
                i -= lw;
            }
            i = Shift + w;
            if(SpritesData[sprR].Texture != NULL)
            {
                while(i <= sw)
                {
                    urender_DrawTexture_4(i, ((WorldDy + LAND_HEIGHT) + OffsetY) - rh, SpritesData[sprR].Texture, (*SpritesData[sprR].Texture).scale);
                    i += rw;
                }
            }
            else
            {
                while(i <= sw)
                {
                    urender_DrawTexture_4(i, ((WorldDy + LAND_HEIGHT) + OffsetY) - lh, SpritesData[sprL].Texture, (*SpritesData[sprL].Texture).scale);
                    i += lw;
                }
            }
        }
    }
};
void uworld_CameraBounds()
{
    LongInt lowBound;
    if(!hasBorder)
    {
        if(WorldDy > (((-(cScreenHeight /(float) cScaleFactor) + (cScreenHeight / 2)) - topY) + cCamLimitY))
        {
            WorldDy = ((-fpcrtl_trunc(cScreenHeight /(float) cScaleFactor) + (cScreenHeight / 2)) - topY) + cCamLimitY;
        }
        if((((rightX - leftX) + (cCamLimitX * 2)) / 2) < (cScreenWidth /(float) cScaleFactor))
        {
            WorldDx = -((leftX + rightX) / 2);
        }
        else
        {
            if(WorldDx < ((-LAND_WIDTH - cCamLimitX) + (cScreenWidth /(float) cScaleFactor)))
            {
                WorldDx = (-LAND_WIDTH - cCamLimitX) + fpcrtl_trunc(cScreenWidth /(float) cScaleFactor);
            }
            if(WorldDx > (cCamLimitX - (cScreenWidth /(float) cScaleFactor)))
            {
                WorldDx = cCamLimitX - fpcrtl_trunc(cScreenWidth /(float) cScaleFactor);
            }
        }
    }
    else
    {
        if(WorldDy > (((-(cScreenHeight /(float) cScaleFactor) + (cScreenHeight / 2)) - topY) + cCamLimitBorderY))
        {
            WorldDy = ((-fpcrtl_trunc(cScreenHeight /(float) cScaleFactor) + (cScreenHeight / 2)) - topY) + cCamLimitBorderY;
        }
        if((((rightX - leftX) + (cCamLimitBorderX * 2)) / 2) < (cScreenWidth /(float) cScaleFactor))
        {
            WorldDx = -((leftX + rightX) / 2);
        }
        else
        {
            if(WorldDx > ((-leftX + cCamLimitBorderX) - (cScreenWidth /(float) cScaleFactor)))
            {
                WorldDx = (-leftX + cCamLimitBorderX) - fpcrtl_trunc(cScreenWidth /(float) cScaleFactor);
            }
            if(WorldDx < ((-rightX - cCamLimitBorderX) + (cScreenWidth /(float) cScaleFactor)))
            {
                WorldDx = (-rightX - cCamLimitBorderX) + fpcrtl_trunc(cScreenWidth /(float) cScaleFactor);
            }
        }
    }
    lowBound = ((fpcrtl_trunc(cScreenHeight /(float) cScaleFactor) + (cScreenHeight / 2)) - cWaterLine) - (cVisibleWater + fpcrtl_trunc(CinematicBarH /(float) (cScaleFactor /(float) 2.0)));
    if(WorldDy < lowBound)
    {
        WorldDy = lowBound;
    }
};
void uworld_DrawWorld(LongInt Lag)
{
    if(ZoomValue < zoom)
    {
        zoom = zoom - (2.0e-3 * Lag);
        if(ZoomValue > zoom)
        {
            zoom = ZoomValue;
        }
    }
    else
    {
        if(ZoomValue > zoom)
        {
            zoom = zoom + (2.0e-3 * Lag);
            if(ZoomValue < zoom)
            {
                zoom = ZoomValue;
            }
        }
        else
        {
            ZoomValue = zoom;
        }
    }
    if((!isPaused && !isAFK) && (GameType != gmtRecord))
    {
        uworld_MoveCamera();
    }
    else
    {
        if(isPaused)
        {
            uworld_CameraBounds();
        }
    }
    if(cStereoMode == smNone)
    {
        urender_RenderClear();
        uworld_DrawWorldStereo(Lag, rmDefault);
    }
    urender_FinishRender();
};
void uworld_RenderWorldEdge()
{
    LongInt tmp;
    LongInt w;
    TSDL_Rect rect;
    if((WorldEdge != weNone) && (WorldEdge != weSea))
    {
        rect.y = ViewTopY;
        rect.h = ViewHeight;
        tmp = leftX + WorldDx;
        w = tmp - ViewLeftX;
        if(w > 0)
        {
            rect.w = w;
            rect.x = ViewLeftX;
            urender_DrawRect(rect, 0x10, 0x10, 0x10, 0x80, true);
            if(WorldEdge == weBounce)
            {
                urender_DrawLineOnScreen(tmp - 1, ViewTopY, tmp - 1, ViewBottomY, 2, 0x54, 0x54, 0xff, 0xff);
            }
        }
        tmp = rightX + WorldDx;
        w = ViewRightX - tmp;
        if(w > 0)
        {
            rect.w = w;
            rect.x = tmp;
            urender_DrawRect(rect, 0x10, 0x10, 0x10, 0x80, true);
            if(WorldEdge == weBounce)
            {
                urender_DrawLineOnScreen(tmp - 1, ViewTopY, tmp - 1, ViewBottomY, 2, 0x54, 0x54, 0xff, 0xff);
            }
        }
    }
};
void uworld_RenderTeamsHealth()
{
    LongInt t;
    LongInt i;
    LongInt h;
    LongInt v;
    LongInt smallScreenOffset;
    LongInt TeamHealthBarWidth;
    TSDL_Rect r;
    boolean highlight;
    boolean hasVisibleHog;
    PTexture htex;
    if((VisibleTeamsCount * 20) > (((LongWord)cScreenHeight) / 7))
    {
        urender_SetScale(1.5);
        smallScreenOffset = cScreenHeight / 6;
        if((VisibleTeamsCount * 100) > ((LongWord)cScreenHeight))
        {
            urender_Tint_4(0xff, 0xff, 0xff, 0x80);
        }
    }
    else
    {
        smallScreenOffset = 0;
    }
    v = 0;
    {t = 0;
     LongInt t__end__ = ((int)(TeamsCount) - 1);
     if (t <= t__end__) do {
                               {
                                   hasVisibleHog = false;
                                   {i = 0;
                                    LongInt i__end__ = cMaxHHIndex;
                                    if (i <= i__end__) do {
                                                              if((*TeamsArray[t]).Hedgehogs[i].Gear != NULL)
                                                              {
                                                                  hasVisibleHog = true;
                                                              }
                                                          } while(i++ != i__end__);}
                                   if(((*TeamsArray[t]).TeamHealth > 0) && hasVisibleHog)
                                   {
                                       ++v;
                                       highlight = (bShowFinger && (CurrentTeam == TeamsArray[t])) && ((RealTicks % 1000) < 500);
                                       if(highlight)
                                       {
                                           urender_Tint_1(((*TeamsArray[t]).Clan->Color << 8) | 0xff);
                                           htex = GenericHealthTexture;
                                       }
                                       else
                                       {
                                           htex = (*TeamsArray[t]).Clan->HealthTex;
                                       }
                                       if((*TeamsArray[t]).OwnerTex != NULL)
                                       {
                                           urender_DrawTexture_3((-(*TeamsArray[t]).OwnerTex->w - (*TeamsArray[t]).NameTagTex->w) - 18, (cScreenHeight + (*TeamsArray[t]).DrawHealthY) + smallScreenOffset, (*TeamsArray[t]).OwnerTex);
                                       }
                                       urender_DrawTexture_3(-(*TeamsArray[t]).NameTagTex->w - 16, (cScreenHeight + (*TeamsArray[t]).DrawHealthY) + smallScreenOffset, (*TeamsArray[t]).NameTagTex);
                                       urender_DrawTexture_3(-14, (cScreenHeight + (*TeamsArray[t]).DrawHealthY) + smallScreenOffset, (*TeamsArray[t]).FlagTex);
                                       TeamHealthBarWidth = (cTeamHealthWidth * (*TeamsArray[t]).TeamHealthBarHealth) / MaxTeamHealth;
                                       r.x = 0;
                                       r.y = 0;
                                       r.w = 2 + TeamHealthBarWidth;
                                       r.h = htex->h;
                                       urender_DrawTextureFromRect_4(14, (cScreenHeight + (*TeamsArray[t]).DrawHealthY) + smallScreenOffset, &(r), htex);
                                       r.x += cTeamHealthWidth + 2;
                                       r.w = 3;
                                       urender_DrawTextureFromRect_4(TeamHealthBarWidth + 15, (cScreenHeight + (*TeamsArray[t]).DrawHealthY) + smallScreenOffset, &(r), htex);
                                       h = 0;
                                       if(!(*TeamsArray[t]).hasGone)
                                       {
                                           {i = 0;
                                            LongInt i__end__ = cMaxHHIndex;
                                            if (i <= i__end__) do {
                                                                      h += (*TeamsArray[t]).Hedgehogs[i].HealthBarHealth;
                                                                      if((h < (*TeamsArray[t]).TeamHealthBarHealth) && ((*TeamsArray[t]).Hedgehogs[i].HealthBarHealth > 0))
                                                                      {
                                                                          if(urenderutils_IsTooDarkToRead((*TeamsArray[t]).Clan->Color))
                                                                          {
                                                                              urender_DrawTexture_3(15 + ((h * TeamHealthBarWidth) / (*TeamsArray[t]).TeamHealthBarHealth), ((cScreenHeight + (*TeamsArray[t]).DrawHealthY) + smallScreenOffset) + 1, SpritesData[sprSlider].Texture);
                                                                          }
                                                                          else
                                                                          {
                                                                              urender_DrawTexture_3(15 + ((h * TeamHealthBarWidth) / (*TeamsArray[t]).TeamHealthBarHealth), ((cScreenHeight + (*TeamsArray[t]).DrawHealthY) + smallScreenOffset) + 1, SpritesData[sprSliderInverted].Texture);
                                                                          }
                                                                      }
                                                                  } while(i++ != i__end__);}
                                       }
                                       if((*TeamsArray[t]).hasLuaTeamValue)
                                       {
                                           urender_DrawTexture_3(TeamHealthBarWidth + 22, (cScreenHeight + (*TeamsArray[t]).DrawHealthY) + smallScreenOffset, (*TeamsArray[t]).LuaTeamValueTex);
                                       }
                                       else
                                       {
                                           if((GameFlags & gfAISurvival) != 0)
                                           {
                                               urender_DrawTexture_3(TeamHealthBarWidth + 22, (cScreenHeight + (*TeamsArray[t]).DrawHealthY) + smallScreenOffset, (*TeamsArray[t]).AIKillsTex);
                                           }
                                       }
                                       if(highlight)
                                       {
                                           if((VisibleTeamsCount * 100) > ((LongWord)cScreenHeight))
                                           {
                                               urender_Tint_4(0xff, 0xff, 0xff, 0x80);
                                           }
                                           else
                                           {
                                               urender_untint();
                                           }
                                           r.x = 2;
                                           r.y = 2;
                                           r.w = (*TeamsArray[t]).NameTagTex->w - 4;
                                           r.h = (*TeamsArray[t]).NameTagTex->h - 4;
                                           urender_DrawTextureFromRect_4(-(*TeamsArray[t]).NameTagTex->w - 14, ((cScreenHeight + (*TeamsArray[t]).DrawHealthY) + smallScreenOffset) + 2, &(r), (*TeamsArray[t]).NameTagTex);
                                           if((*TeamsArray[t]).OwnerTex != NULL)
                                           {
                                               r.w = (*TeamsArray[t]).OwnerTex->w - 4;
                                               r.h = (*TeamsArray[t]).OwnerTex->h - 4;
                                               urender_DrawTextureFromRect_4((-(*TeamsArray[t]).OwnerTex->w - (*TeamsArray[t]).NameTagTex->w) - 16, ((cScreenHeight + (*TeamsArray[t]).DrawHealthY) + smallScreenOffset) + 2, &(r), (*TeamsArray[t]).OwnerTex);
                                           }
                                           if((*TeamsArray[t]).hasLuaTeamValue)
                                           {
                                               r.w = (*TeamsArray[t]).LuaTeamValueTex->w - 4;
                                               r.h = (*TeamsArray[t]).LuaTeamValueTex->h - 4;
                                               urender_DrawTextureFromRect_4(TeamHealthBarWidth + 24, ((cScreenHeight + (*TeamsArray[t]).DrawHealthY) + smallScreenOffset) + 2, &(r), (*TeamsArray[t]).LuaTeamValueTex);
                                           }
                                           else
                                           {
                                               if((GameFlags & gfAISurvival) != 0)
                                               {
                                                   r.w = (*TeamsArray[t]).AIKillsTex->w - 4;
                                                   r.h = (*TeamsArray[t]).AIKillsTex->h - 4;
                                                   urender_DrawTextureFromRect_4(TeamHealthBarWidth + 24, ((cScreenHeight + (*TeamsArray[t]).DrawHealthY) + smallScreenOffset) + 2, &(r), (*TeamsArray[t]).AIKillsTex);
                                               }
                                           }
                                           r.w = 22;
                                           r.h = 15;
                                           urender_DrawTextureFromRect_4(-12, ((cScreenHeight + (*TeamsArray[t]).DrawHealthY) + smallScreenOffset) + 2, &(r), (*TeamsArray[t]).FlagTex);
                                       }
                                       else
                                       {
                                           if((CurrentTeam == TeamsArray[t]) && (TurnTimeLeft > 0))
                                           {
                                               h = -(*TeamsArray[t]).NameTagTex->w - 24;
                                               if((*TeamsArray[t]).OwnerTex != NULL)
                                               {
                                                   h = (h - (*TeamsArray[t]).OwnerTex->w) - 4;
                                               }
                                               if(urenderutils_IsTooDarkToRead((*TeamsArray[t]->Clan).Color))
                                               {
                                                   urender_DrawSpriteRotatedF(sprFingerBackInv, h, (((cScreenHeight + (*TeamsArray[t]).DrawHealthY) + smallScreenOffset) + 2) + (SpritesData[sprFingerBackInv].Width / 4), 0, 1, -90);
                                               }
                                               else
                                               {
                                                   urender_DrawSpriteRotatedF(sprFingerBack, h, (((cScreenHeight + (*TeamsArray[t]).DrawHealthY) + smallScreenOffset) + 2) + (SpritesData[sprFingerBack].Width / 4), 0, 1, -90);
                                               }
                                               urender_Tint_1(((*TeamsArray[t]->Clan).Color << 8) | 0xff);
                                               urender_DrawSpriteRotatedF(sprFinger, h, (((cScreenHeight + (*TeamsArray[t]).DrawHealthY) + smallScreenOffset) + 2) + (SpritesData[sprFinger].Width / 4), 0, 1, -90);
                                               urender_untint();
                                           }
                                       }
                                   }
                               }
                           } while(t++ != t__end__);}
    if(smallScreenOffset != 0)
    {
        urender_SetScale(cDefaultZoomLevel);
        if((VisibleTeamsCount * 20) > (((LongWord)cScreenHeight) / 5))
        {
            urender_untint();
        }
    }
    VisibleTeamsCount = v;
};
void uworld_RenderAttackBar()
{
    LongInt i;
    double tdx;
    double tdy;
    if(CurrentTeam != NULL)
    {
        switch(AttackBar)
        {case 2:{
                    tdx = ufloat_hwSign((*CurrentHedgehog).Gear->dX) * sin(((*CurrentHedgehog).Gear->Angle * pi) /(float) cMaxAngle);
                    tdy = -cos(((*CurrentHedgehog).Gear->Angle * pi) /(float) cMaxAngle);
                    {i = ((*CurrentHedgehog).Gear->Power * 24) / cPowerDivisor;
                     LongInt i__end__ = 0;
                     if (i >= i__end__) do {
                                               urender_DrawSprite_4(sprPower, ((ufloat_hwRound((*CurrentHedgehog).Gear->X) + uutils_GetLaunchX((*CurrentHedgehog).CurAmmoType, ufloat_hwSign((*CurrentHedgehog).Gear->dX), (*CurrentHedgehog).Gear->Angle)) + ((LongInt)fpcrtl_round(WorldDx + (tdx * (24 + (i * 2)))))) - 16, ((ufloat_hwRound((*CurrentHedgehog).Gear->Y) + uutils_GetLaunchY((*CurrentHedgehog).CurAmmoType, (*CurrentHedgehog).Gear->Angle)) + ((LongInt)fpcrtl_round(WorldDy + (tdy * (24 + (i * 2)))))) - 16, i);
                                           } while(i-- != i__end__);}
                }
                break;
         default: break;}
    }
};
static LongInt preShiftWorldDx;
void uworld_ShiftWorld(LongInt Dir)
{
    preShiftWorldDx = WorldDx;
    Dir = Dir * ((LongInt)playWidth);
    WorldDx = WorldDx + Dir;
};
void uworld_UnshiftWorld()
{
    WorldDx = preShiftWorldDx;
};
void uworld_DrawWorldStereo(LongInt Lag,TRenderMode RM)
{
    LongInt i;
    LongInt t;
    TSprite spr;
    TSDL_Rect r;
    string255 s;
    LongInt offsetX;
    LongInt offsetY;
    LongInt screenBottom;
    boolean replicateToLeft;
    boolean replicateToRight;
    boolean isNotHiddenByCinematic;
    if(WorldEdge != weWrap)
    {
        replicateToLeft = false;
        replicateToRight = false;
    }
    else
    {
        replicateToLeft = (leftX + WorldDx) > ViewLeftX;
        replicateToRight = (rightX + WorldDx) < ViewRightX;
    }
    screenBottom = ((WorldDy - fpcrtl_trunc(cScreenHeight /(float) cScaleFactor)) - (cScreenHeight / 2)) + cWaterLine;
    offsetY = 10 * uutils_Min(0, -145 - screenBottom);
    if((cReducedQuality & rqNoBackground) == 0)
    {
        SkyOffset = (offsetY / 35) + cWaveHeight;
        HorizontOffset = SkyOffset;
        if(screenBottom > SkyOffset)
        {
            HorizontOffset = HorizontOffset + ((screenBottom - SkyOffset) / 20);
        }
        urender_ChangeDepth(RM, cStereo_Sky);
        if(SuddenDeathDmg)
        {
            urender_Tint_4(SDTint.r, SDTint.g, SDTint.b, SDTint.a);
        }
        uworld_DrawRepeated(sprSky, sprSkyL, sprSkyR, ((WorldDx + (LAND_WIDTH / 2)) * 3) / 8, SkyOffset);
        urender_ChangeDepth(RM, -cStereo_Horizon);
        uworld_DrawRepeated(sprHorizont, sprHorizontL, sprHorizontR, ((WorldDx + (LAND_WIDTH / 2)) * 3) / 5, HorizontOffset);
        if(SuddenDeathDmg)
        {
            urender_untint();
        }
    }
    uvisualgears_DrawVisualGears(0, false);
    urender_ChangeDepth(RM, -cStereo_MidDistance);
    uvisualgears_DrawVisualGears(4, false);
    if((cReducedQuality & rq2DWater) == 0)
    {
        urender_DrawWater(255, SkyOffset, 0);
        urender_ChangeDepth(RM, -cStereo_Water_distant);
        urender_DrawWaves(1, 0 - (WorldDx / 32), offsetY / 35, -49, 64);
        urender_ChangeDepth(RM, -cStereo_Water_distant);
        urender_DrawWaves(-1, 25 + (WorldDx / 25), offsetY / 38, -37, 48);
        urender_ChangeDepth(RM, -cStereo_Water_distant);
        urender_DrawWaves(1, 75 - (WorldDx / 19), offsetY / 45, -23, 32);
        urender_ChangeDepth(RM, -cStereo_Water_distant);
        urender_DrawWaves(-1, 100 + (WorldDx / 14), offsetY / 70, -7, 24);
    }
    else
    {
        urender_DrawWaves(-1, 100, -cWaveHeight / 2, -cWaveHeight / 2, 0);
    }
    urender_ChangeDepth(RM, cStereo_Land);
    uvisualgears_DrawVisualGears(5, false);
    ulandtexture_DrawLand(WorldDx, WorldDy);
    if(replicateToLeft)
    {
        uworld_ShiftWorld(-1);
        ulandtexture_DrawLand(WorldDx, WorldDy);
        uworld_UnshiftWorld();
    }
    if(replicateToRight)
    {
        uworld_ShiftWorld(1);
        ulandtexture_DrawLand(WorldDx, WorldDy);
        uworld_UnshiftWorld();
    }
    urender_DrawWater(255, 0, 0);
    if(replicateToLeft)
    {
        uworld_ShiftWorld(-1);
        uvisualgears_DrawVisualGears(1, true);
        ugears_DrawGears();
        uvisualgears_DrawVisualGears(6, true);
        uworld_UnshiftWorld();
    }
    if(replicateToRight)
    {
        uworld_ShiftWorld(1);
        uvisualgears_DrawVisualGears(1, true);
        ugears_DrawGears();
        uvisualgears_DrawVisualGears(6, true);
        uworld_UnshiftWorld();
    }
    uvisualgears_DrawVisualGears(1, false);
    ugears_DrawGears();
    uvisualgears_DrawVisualGears(6, false);
    if(SuddenDeathDmg)
    {
        urender_DrawWater(SDWaterOpacity, 0, 0);
    }
    else
    {
        urender_DrawWater(WaterOpacity, 0, 0);
    }
    urender_ChangeDepth(RM, cStereo_Water_near);
    urender_DrawWaves(1, 25 - (WorldDx / 9), 0, 0, 12);
    if((cReducedQuality & rq2DWater) == 0)
    {
        urender_ChangeDepth(RM, cStereo_Water_near);
        urender_DrawWaves(-1, 50 + (WorldDx / 6), -offsetY / 40, 23, 8);
        if(SuddenDeathDmg)
        {
            urender_DrawWater(SDWaterOpacity, -offsetY / 20, 23);
        }
        else
        {
            urender_DrawWater(WaterOpacity, -offsetY / 20, 23);
        }
        urender_ChangeDepth(RM, cStereo_Water_near);
        urender_DrawWaves(1, 75 - (WorldDx / 4), -offsetY / 20, 37, 2);
        if(SuddenDeathDmg)
        {
            urender_DrawWater(SDWaterOpacity, -offsetY / 10, 47);
        }
        else
        {
            urender_DrawWater(WaterOpacity, -offsetY / 10, 47);
        }
        urender_ChangeDepth(RM, cStereo_Water_near);
        urender_DrawWaves(-1, 25 + (WorldDx / 3), -offsetY / 10, 59, 0);
    }
    else
    {
        urender_DrawWaves(-1, 50, cWaveHeight / 2, cWaveHeight / 2, 0);
    }
    {
        if(isCursorVisible && ((((*CurrentHedgehog).CurAmmoType == amNapalm) || ((*CurrentHedgehog).CurAmmoType == amMineStrike)) || (((GameFlags & gfMoreWind) != 0) && (((*CurrentHedgehog).CurAmmoType == amDrillStrike) || ((*CurrentHedgehog).CurAmmoType == amAirAttack)))))
        {
            urender_DrawLine_9(-cCamLimitX, topY - 300, LAND_WIDTH + cCamLimitX, topY - 300, 3.0, (*(*CurrentHedgehog).Team->Clan).Color >> 16, ((*(*CurrentHedgehog).Team->Clan).Color >> 8) & 0xff, (*(*CurrentHedgehog).Team->Clan).Color & 0xff, 0xff);
        }
    }
    if(replicateToLeft)
    {
        uworld_ShiftWorld(-1);
        ugears_DrawGearsGui();
        uworld_UnshiftWorld();
    }
    if(replicateToRight)
    {
        uworld_ShiftWorld(1);
        ugears_DrawGearsGui();
        uworld_UnshiftWorld();
    }
    ugears_DrawGearsGui();
    ugears_DrawFinger();
    urender_ChangeDepth(RM, cStereo_Outside);
    if(replicateToLeft)
    {
        uworld_ShiftWorld(-1);
        uvisualgears_DrawVisualGears(2, true);
        uworld_UnshiftWorld();
    }
    if(replicateToRight)
    {
        uworld_ShiftWorld(1);
        uvisualgears_DrawVisualGears(2, true);
        uworld_UnshiftWorld();
    }
    uvisualgears_DrawVisualGears(2, false);
    urender_ResetDepth(RM);
    if(replicateToLeft)
    {
        uworld_ShiftWorld(-1);
        uvisualgears_DrawVisualGears(3, true);
        uworld_UnshiftWorld();
    }
    if(replicateToRight)
    {
        uworld_ShiftWorld(1);
        uvisualgears_DrawVisualGears(3, true);
        uworld_UnshiftWorld();
    }
    uvisualgears_DrawVisualGears(3, false);
    if(((TargetPoint.x != NoPointX) && (CurrentTeam != NULL)) && (CurrentHedgehog != NULL))
    {
        {
            if((*((PHedgehog)CurrentHedgehog)).CurAmmoType == amBee)
            {
                spr = sprTargetBee;
            }
            else
            {
                spr = sprTargetP;
            }
            if(replicateToLeft)
            {
                uworld_ShiftWorld(-1);
                if(spr == sprTargetP)
                {
                    if(urenderutils_IsTooDarkToRead((*(*((PHedgehog)CurrentHedgehog)).Team->Clan).Color))
                    {
                        urender_DrawSpriteRotatedF(sprTargetPBackInv, TargetPoint.x + WorldDx, TargetPoint.y + WorldDy, 0, 0, (RealTicks >> 3) % 360);
                    }
                    else
                    {
                        urender_DrawSpriteRotatedF(sprTargetPBack, TargetPoint.x + WorldDx, TargetPoint.y + WorldDy, 0, 0, (RealTicks >> 3) % 360);
                    }
                    urender_Tint_1(((*(*((PHedgehog)CurrentHedgehog)).Team->Clan).Color << 8) | 0xff);
                }
                urender_DrawSpriteRotatedF(spr, TargetPoint.x + WorldDx, TargetPoint.y + WorldDy, 0, 0, (RealTicks >> 3) % 360);
                if(spr == sprTargetP)
                {
                    urender_untint();
                }
                uworld_UnshiftWorld();
            }
            if(replicateToRight)
            {
                uworld_ShiftWorld(1);
                if(spr == sprTargetP)
                {
                    if(urenderutils_IsTooDarkToRead((*(*((PHedgehog)CurrentHedgehog)).Team->Clan).Color))
                    {
                        urender_DrawSpriteRotatedF(sprTargetPBackInv, TargetPoint.x + WorldDx, TargetPoint.y + WorldDy, 0, 0, (RealTicks >> 3) % 360);
                    }
                    else
                    {
                        urender_DrawSpriteRotatedF(sprTargetPBack, TargetPoint.x + WorldDx, TargetPoint.y + WorldDy, 0, 0, (RealTicks >> 3) % 360);
                    }
                    urender_Tint_1(((*(*((PHedgehog)CurrentHedgehog)).Team->Clan).Color << 8) | 0xff);
                }
                urender_DrawSpriteRotatedF(spr, TargetPoint.x + WorldDx, TargetPoint.y + WorldDy, 0, 0, (RealTicks >> 3) % 360);
                if(spr == sprTargetP)
                {
                    urender_untint();
                }
                uworld_UnshiftWorld();
            }
            if(spr == sprTargetP)
            {
                if(urenderutils_IsTooDarkToRead((*(*((PHedgehog)CurrentHedgehog)).Team->Clan).Color))
                {
                    urender_DrawSpriteRotatedF(sprTargetPBackInv, TargetPoint.x + WorldDx, TargetPoint.y + WorldDy, 0, 0, (RealTicks >> 3) % 360);
                }
                else
                {
                    urender_DrawSpriteRotatedF(sprTargetPBack, TargetPoint.x + WorldDx, TargetPoint.y + WorldDy, 0, 0, (RealTicks >> 3) % 360);
                }
                urender_Tint_1(((*(*((PHedgehog)CurrentHedgehog)).Team->Clan).Color << 8) | 0xff);
            }
            urender_DrawSpriteRotatedF(spr, TargetPoint.x + WorldDx, TargetPoint.y + WorldDy, 0, 0, (RealTicks >> 3) % 360);
            if(spr == sprTargetP)
            {
                urender_untint();
            }
        }
    }
    if(replicateToLeft)
    {
        uworld_ShiftWorld(-1);
        uworld_RenderAttackBar();
        uworld_UnshiftWorld();
    }
    if(replicateToRight)
    {
        uworld_ShiftWorld(1);
        uworld_RenderAttackBar();
        uworld_UnshiftWorld();
    }
    uworld_RenderAttackBar();
    uworld_RenderWorldEdge();
    urender_SetScale(cDefaultZoomLevel);
    isNotHiddenByCinematic = true;
    if(CinematicScript || ((InCinematicMode && autoCameraOn) && ((((CurrentHedgehog == NULL) || (*CurrentHedgehog->Team).ExtDriven) || (CurrentHedgehog->BotLevel != 0)) || (GameType == gmtDemo))))
    {
        if(CinematicSteps < 300)
        {
            CinematicSteps += Lag;
            if(CinematicSteps > 300)
            {
                CinematicSteps = 300;
                isNotHiddenByCinematic = false;
            }
        }
    }
    else
    {
        if(CinematicSteps > 0)
        {
            CinematicSteps -= Lag;
            if(CinematicSteps < 0)
            {
                CinematicSteps = 0;
            }
        }
    }
    if((UIDisplay != uiNone) && isNotHiddenByCinematic)
    {
        offsetX = 48;
        offsetY = cOffsetY;
        if(((TurnTimeLeft != 0) && (TurnTimeLeft < 999000)) || (ReadyTimeLeft != 0))
        {
            if(ReadyTimeLeft != 0)
            {
                i = (((int)(ReadyTimeLeft) - 1) / 1000 + 1);
            }
            else
            {
                i = (((int)(TurnTimeLeft) - 1) / 1000 + 1);
            }
            if(i > 99)
            {
                t = 112;
            }
            else
            {
                if(i > 9)
                {
                    t = 96;
                }
                else
                {
                    t = 80;
                }
            }
            urender_DrawSprite_4(sprFrame, (-(cScreenWidth >> 1) + t) + offsetY, cScreenHeight - offsetX, 1);
            while(i > 0)
            {
                t -= 32;
                if(isPaused || !ugears_IsClockRunning())
                {
                    spr = sprBigDigitGray;
                }
                else
                {
                    if(ReadyTimeLeft != 0)
                    {
                        spr = sprBigDigitGreen;
                    }
                    else
                    {
                        if(IsGetAwayTime)
                        {
                            spr = sprBigDigitRed;
                        }
                        else
                        {
                            spr = sprBigDigit;
                        }
                    }
                }
                urender_DrawSprite_4(spr, (-(cScreenWidth >> 1) + t) + offsetY, cScreenHeight - offsetX, i % 10);
                i = i / 10;
            }
            urender_DrawSprite_4(sprFrame, ((-(cScreenWidth >> 1) + t) - 4) + offsetY, cScreenHeight - offsetX, 0);
        }
    }
    if((UIDisplay == uiAll) && isNotHiddenByCinematic)
    {
        uworld_RenderTeamsHealth();
    }
    if(((((((UIDisplay == uiAll) || (UIDisplay == uiNoTeams)) && isNotHiddenByCinematic) && (CurrentHedgehog != NULL)) && (CurrentHedgehog->Gear != NULL)) && (CurrentHedgehog->HealthTagTex != NULL)) && (((*CurrentHedgehog->Gear).State & gstHHDriven) != 0))
    {
        t = 11;
        i = t;
        t += (*CurrentHedgehog->HealthTagTex).h;
        cDemoClockFPSOffsetY = t;
        if((GameFlags & gfInvulnerable) == 0)
        {
            urender_DrawTexture_3(((cScreenWidth / 2) - (*CurrentHedgehog->HealthTagTex).w) - 16, i, CurrentHedgehog->HealthTagTex);
            t = SpritesData[sprHealthHud].Width + 18;
            if((GameFlags & gfResetHealth) == 0)
            {
                if(CurrentHedgehog->Effects[hePoisoned] != 0)
                {
                    urender_DrawSprite_4(sprHealthPoisonHud, ((cScreenWidth / 2) - (*CurrentHedgehog->HealthTagTex).w) - t, i, 0);
                }
                else
                {
                    urender_DrawSprite_4(sprHealthHud, ((cScreenWidth / 2) - (*CurrentHedgehog->HealthTagTex).w) - t, i, 0);
                }
            }
            else
            {
                if(CurrentHedgehog->Effects[hePoisoned] != 0)
                {
                    urender_DrawSprite_4(sprMedicPoisonHud, ((cScreenWidth / 2) - (*CurrentHedgehog->HealthTagTex).w) - t, i, 0);
                }
                else
                {
                    urender_DrawSprite_4(sprMedicHud, ((cScreenWidth / 2) - (*CurrentHedgehog->HealthTagTex).w) - t, i, 0);
                }
            }
            if(CurrentHedgehog->Effects[heResurrectable] != 0)
            {
                urender_DrawSprite_4(sprHaloHud, (((cScreenWidth / 2) - (*CurrentHedgehog->HealthTagTex).w) - t) - 2, (i - SpritesData[sprHaloHud].Height) + 1, 0);
            }
            t += 2;
            if(CurrentHedgehog->Effects[heInvulnerable] != 0)
            {
                t += SpritesData[sprInvulnHUD].Width + 2;
                urender_DrawSprite_4(sprInvulnHUD, ((cScreenWidth / 2) - (*CurrentHedgehog->HealthTagTex).w) - t, i, 0);
            }
            else
            {
                if((GameFlags & gfKarma) != 0)
                {
                    t += SpritesData[sprKarmaHud].Width + 2;
                    urender_DrawSprite_4(sprKarmaHud, ((cScreenWidth / 2) - (*CurrentHedgehog->HealthTagTex).w) - t, i, 0);
                }
            }
            if(cVampiric)
            {
                t += SpritesData[sprVampHud].Width + 2;
                urender_DrawSprite_4(sprVampHud, ((cScreenWidth / 2) - (*CurrentHedgehog->HealthTagTex).w) - t, i, 0);
            }
        }
        else
        {
            t += 8;
            urender_DrawSprite_4(sprInvulnHUD, (cScreenWidth / 2) - t, i, 0);
            if(CurrentHedgehog->Effects[heResurrectable] != 0)
            {
                urender_DrawSprite_4(sprHaloHud, ((cScreenWidth / 2) - t) - 2, (i - SpritesData[sprHaloHud].Height) + 1, 0);
            }
            if(cVampiric)
            {
                t += SpritesData[sprVampHud].Width + 2;
                urender_DrawSprite_4(sprVampHud, (cScreenWidth / 2) - t, i, 0);
            }
        }
    }
    else
    {
        cDemoClockFPSOffsetY = 0;
    }
    if((UIDisplay != uiNone) && isNotHiddenByCinematic)
    {
        offsetX = 30;
        offsetY = 180;
        urender_DrawSprite_4(sprWindBar, (cScreenWidth >> 1) - offsetY, cScreenHeight - offsetX, 0);
        if(WindBarWidth > 0)
        {
            r.x = 8 - ((RealTicks >> 6) % 9);
            r.y = 0;
            r.w = WindBarWidth;
            r.h = 13;
            urender_DrawSpriteFromRect(sprWindR, r, ((cScreenWidth >> 1) - offsetY) + 77, (cScreenHeight - offsetX) + 2, 13, 0);
        }
        else
        {
            if(WindBarWidth < 0)
            {
                r.x = (((LongWord)WindBarWidth) + (RealTicks >> 6)) % 9;
                r.y = 0;
                r.w = -WindBarWidth;
                r.h = 13;
                urender_DrawSpriteFromRect(sprWindL, r, (((cScreenWidth >> 1) - offsetY) + 74) + WindBarWidth, (cScreenHeight - offsetX) + 2, 13, 0);
            }
        }
    }
    if((UIDisplay != uiNone) && isNotHiddenByCinematic)
    {
        offsetX = 45;
        offsetY = 51;
        if(ufloat_hwFloat_hwFloat_op_eq(cDamageModifier, _1_5))
        {
            urender_DrawTextureF(ropeIconTex, 1, (cScreenWidth >> 1) - offsetX, cScreenHeight - offsetY, 0, 1, 32, 32);
            urender_DrawTextureF(SpritesData[sprAMAmmos].Texture, 0.9, (cScreenWidth >> 1) - offsetX, cScreenHeight - offsetY, (amExtraDamage) - 1, 1, 32, 32);
            offsetX = offsetX + 33;
        }
        if(cLowGravity || ((GameFlags & gfLowGravity) != 0))
        {
            urender_DrawTextureF(ropeIconTex, 1, (cScreenWidth >> 1) - offsetX, cScreenHeight - offsetY, 0, 1, 32, 32);
            urender_DrawTextureF(SpritesData[sprAMAmmos].Texture, 0.9, (cScreenWidth >> 1) - offsetX, cScreenHeight - offsetY, (amLowGravity) - 1, 1, 32, 32);
            offsetX = offsetX + 33;
        }
        if(cLaserSighting)
        {
            urender_DrawTextureF(ropeIconTex, 1, (cScreenWidth >> 1) - offsetX, cScreenHeight - offsetY, 0, 1, 32, 32);
            urender_DrawTextureF(SpritesData[sprAMAmmos].Texture, 0.9, (cScreenWidth >> 1) - offsetX, cScreenHeight - offsetY, (amLaserSight) - 1, 1, 32, 32);
        }
    }
    if(CinematicSteps > 0)
    {
        r.x = ViewLeftX;
        r.w = ViewWidth;
        r.y = ViewTopY;
        CinematicBarH = (ViewHeight * CinematicSteps) / 2048;
        r.h = CinematicBarH;
        urender_DrawRect(r, 0, 0, 0, 0xff, true);
        r.y = ViewBottomY - r.h;
        urender_DrawRect(r, 0, 0, 0, 0xff, true);
    }
    if(UIDisplay != uiNone)
    {
        ucaptions_DrawCaptions();
    }
    if(isInLag)
    {
        urender_DrawSprite_4(sprLag, 32 - (cScreenWidth >> 1), 32, (RealTicks >> 7) % 12);
    }
    uchat_DrawChat();
    if(((((!isFirstFrame && (missionTimer != 0)) || isShowMission) || isPaused) || fastUntilLag) || (GameState == gsConfirm))
    {
        if((ReadyTimeLeft == 0) && (missionTimer > 0))
        {
            missionTimer -= Lag;
        }
        if(missionTimer < 0)
        {
            missionTimer = 0;
        }
        if(missionTex != NULL)
        {
            urender_DrawTextureCentered(0, uutils_Min((cScreenHeight >> 1) + 100, (cScreenHeight - 48) - missionTex->h), missionTex);
        }
    }
    if(missionTimer == 0)
    {
        isForceMission = false;
    }
    if(bShowAmmoMenu && ((AMState == AMHidden) || (AMState == AMHiding)))
    {
        if(AMState == AMHidden)
        {
            AMAnimStartTime = RealTicks;
        }
        else
        {
            AMAnimStartTime = RealTicks - (AMAnimDuration - (RealTicks - AMAnimStartTime));
        }
        AMState = AMShowingUp;
    }
    if(!bShowAmmoMenu && ((AMState == AMShowing) || (AMState == AMShowingUp)))
    {
        if(AMState == AMShowing)
        {
            AMAnimStartTime = RealTicks;
        }
        else
        {
            AMAnimStartTime = RealTicks - (AMAnimDuration - (RealTicks - AMAnimStartTime));
        }
        AMState = AMHiding;
    }
    if(bShowAmmoMenu || (AMState == AMHiding))
    {
        uworld_ShowAmmoMenu();
    }
    if(fastUntilLag)
    {
        urender_DrawTextureCentered(0, cScreenHeight >> 1, SyncTexture);
    }
    else
    {
        if(isAFK)
        {
            urender_DrawTextureCentered(0, cScreenHeight >> 1, AFKTexture);
        }
        else
        {
            if(isPaused)
            {
                urender_DrawTextureCentered(0, cScreenHeight >> 1, PauseTexture);
            }
        }
    }
    if(isCursorVisible && bShowAmmoMenu)
    {
        urender_DrawSprite_4(sprArrow, CursorPoint.x, cScreenHeight - CursorPoint.y, (RealTicks >> 6) % 8);
    }
    offsetY = cDemoClockFPSOffsetY + 10;
    offsetX = cOffsetY;
    if((RM == rmDefault) || (RM == rmRightEye))
    {
        ++Frames;
        if(cShowFPS || (GameType == gmtDemo))
        {
            CountTicks += Lag;
        }
        if((GameType == gmtDemo) && (CountTicks >= 1000))
        {
            i = GameTicks / 1000;
            t = i % 60;
            s = uutils_IntToStr(t);
            if(t < 10)
            {
                s = _strprepend(0x30, s);
            }
            i = i / 60;
            t = i % 60;
            s = _strconcat(_strappend(uutils_IntToStr(t), 0x3a), s);
            if(t < 10)
            {
                s = _strprepend(0x30, s);
            }
            s = _strconcat(_strappend(uutils_IntToStr(i / 60), 0x3a), s);
            tmpSurface = TTF_RenderUTF8_Blended(Fontz[fnt16].Handle, uutils_Str2PChar(s), cWhiteColorChannels);
            tmpSurface = umisc_doSurfaceConversion(tmpSurface);
            utextures_FreeAndNilTexture(&(timeTexture));
            timeTexture = utextures_Surface2Tex(tmpSurface, false);
            SDL_FreeSurface(tmpSurface);
        }
        if((timeTexture != NULL) && (UIDisplay != uiNone))
        {
            urender_DrawTexture_3((((cScreenWidth >> 1) - 20) - timeTexture->w) - offsetX, offsetY, timeTexture);
        }
        if(cShowFPS && (UIDisplay != uiNone))
        {
            if(CountTicks >= 1000)
            {
                FPS = Frames;
                Frames = 0;
                CountTicks = 0;
                s = ulocale_Format_2(fpcrtl_astr2str(trmsg[sidFPS]), uutils_IntToStr(FPS));
                tmpSurface = TTF_RenderUTF8_Blended(Fontz[uutils_CheckCJKFont(trmsg[sidFPS], fnt16)].Handle, uutils_Str2PChar(s), cWhiteColorChannels);
                tmpSurface = umisc_doSurfaceConversion(tmpSurface);
                utextures_FreeAndNilTexture(&(fpsTexture));
                fpsTexture = utextures_Surface2Tex(tmpSurface, false);
                SDL_FreeSurface(tmpSurface);
            }
            if(fpsTexture != NULL)
            {
                if(timeTexture != NULL)
                {
                    i = fpsTexture->h + 5;
                }
                else
                {
                    i = 0;
                }
                urender_DrawTexture_3((((cScreenWidth >> 1) - 20) - fpsTexture->w) - offsetX, offsetY + i, fpsTexture);
            }
        }
    }
    if(GameState == gsConfirm)
    {
        urender_DrawTextureCentered(0, (cScreenHeight >> 1) - 40, ConfirmTexture);
    }
    if(ScreenFade != sfNone)
    {
        if(!isFirstFrame)
        {
            switch(ScreenFade)
            {case sfToBlack:
             case sfToWhite:if((ScreenFadeValue + (Lag * ScreenFadeSpeed)) < sfMax)
                            {
                                ScreenFadeValue += Lag * ScreenFadeSpeed;
                            }
                            else
                            {
                                ScreenFadeValue = sfMax;
                            }
                            break;
             case sfFromBlack:
             case sfFromWhite:if((ScreenFadeValue - (Lag * ScreenFadeSpeed)) > 0)
                              {
                                  ScreenFadeValue -= Lag * ScreenFadeSpeed;
                              }
                              else
                              {
                                  ScreenFadeValue = 0;
                              }
                              break;
             default: break;}
        }
        if(ScreenFade != sfNone)
        {
            r.x = ViewLeftX;
            r.y = ViewTopY;
            r.w = ViewWidth;
            r.h = ViewHeight;
            switch(ScreenFade)
            {case sfToBlack:
             case sfFromBlack:urender_DrawRect(r, 0, 0, 0, (ScreenFadeValue * 255) / 1000, true);
                              break;
             case sfToWhite:
             case sfFromWhite:urender_DrawRect(r, 0xff, 0xff, 0xff, (ScreenFadeValue * 255) / 1000, true);
                              break;
             default: break;}
            if(!isFirstFrame && ((ScreenFadeValue == 0) || (ScreenFadeValue == sfMax)))
            {
                ScreenFade = sfNone;
            }
        }
    }
    urender_SetScale(zoom);
    if(isCursorVisible && !bShowAmmoMenu)
    {
        if(!CurrentTeam->ExtDriven)
        {
            TargetCursorPoint = CursorPoint;
        }
        {
            if(((*CurrentHedgehog).Gear != NULL) && (((*CurrentHedgehog).Gear->State & gstChooseTarget) != 0))
            {
                i = uammos_GetCurAmmoEntry(&((*CurrentHedgehog)))->Pos;
                {
                    if(Ammoz[(*CurrentHedgehog).CurAmmoType].PosCount > 0)
                    {
                        if(((*CurrentHedgehog).CurAmmoType == amGirder) || ((*CurrentHedgehog).CurAmmoType == amTeleport))
                        {
                            if(((GameTicks / 16) % 0x80) >= 0x40)
                            {
                                urender_Tint_4(0xff, 0xff, 0xff, 0xc0 - ((GameTicks / 16) % 0x40));
                            }
                            else
                            {
                                urender_Tint_4(0xff, 0xff, 0xff, 0x80 + ((GameTicks / 16) % 0x40));
                            }
                        }
                        urender_DrawSprite_4(Ammoz[(*CurrentHedgehog).CurAmmoType].PosSprite, TargetCursorPoint.x - (SpritesData[Ammoz[(*CurrentHedgehog).CurAmmoType].PosSprite].Width >> 1), (cScreenHeight - TargetCursorPoint.y) - (SpritesData[Ammoz[(*CurrentHedgehog).CurAmmoType].PosSprite].Height >> 1), i);
                        urender_untint();
                        if((WorldEdge == weWrap) && ((*CurrentHedgehog).CurAmmoType == amBee))
                        {
                            if((TargetCursorPoint.x - WorldDx) > rightX)
                            {
                                urender_DrawSprite_4(sprThroughWrap, TargetCursorPoint.x - (SpritesData[sprThroughWrap].Width >> 1), (((cScreenHeight - TargetCursorPoint.y) - (SpritesData[Ammoz[(*CurrentHedgehog).CurAmmoType].PosSprite].Height >> 1)) - SpritesData[sprThroughWrap].Height) - 2, 0);
                            }
                            else
                            {
                                if((TargetCursorPoint.x - WorldDx) < leftX)
                                {
                                    urender_DrawSprite_4(sprThroughWrap, TargetCursorPoint.x - (SpritesData[sprThroughWrap].Width >> 1), (((cScreenHeight - TargetCursorPoint.y) - (SpritesData[Ammoz[(*CurrentHedgehog).CurAmmoType].PosSprite].Height >> 1)) - SpritesData[sprThroughWrap].Height) - 2, 1);
                                }
                            }
                        }
                    }
                }
            }
        }
        urender_DrawTextureF(SpritesData[sprArrow].Texture, cDefaultZoomLevel /(float) cScaleFactor, TargetCursorPoint.x + fpcrtl_round(SpritesData[sprArrow].Width /(float) cScaleFactor), (cScreenHeight + fpcrtl_round(SpritesData[sprArrow].Height /(float) cScaleFactor)) - TargetCursorPoint.y, (RealTicks >> 6) % 8, 1, SpritesData[sprArrow].Width, SpritesData[sprArrow].Height);
    }
    if(cViewLimitsDebug)
    {
        r.x = ViewLeftX;
        r.y = ViewTopY;
        r.w = ViewWidth;
        r.h = ViewHeight;
        urender_DrawRect(r, 255, 0, 0, 128, false);
    }
    isFirstFrame = false;
};
static LongWord PrevSentPointTime = 0;
void uworld_MoveCamera()
{
    LongInt EdgesDist;
    LongInt shs;
    LongInt z;
    LongInt dstX;
    boolean inbtwnTrgtAttks;
    if((!(((CurrentTeam->ExtDriven && isCursorVisible) && !bShowAmmoMenu) && autoCameraOn) && cHasFocus) && (GameState != gsConfirm))
    {
        ucursor_updatePosition();
    }
    z = fpcrtl_round(200 /(float) zoom);
    inbtwnTrgtAttks = ((((GameFlags & gfInfAttack) != 0) && (CurrentHedgehog != NULL)) && ((CurrentHedgehog->Gear == NULL) || (CurrentHedgehog->Gear != FollowGear))) && ((Ammoz[CurrentHedgehog->CurAmmoType].Ammo.Propz & ammoprop_NeedTarget) != 0);
    if((((((autoCameraOn && !PlacingHogs) && (FollowGear != NULL)) && !isCursorVisible) && !bShowAmmoMenu) && !fastUntilLag) && !inbtwnTrgtAttks)
    {
        if((fpcrtl_abs(CursorPoint.x - prevPoint.x) + fpcrtl_abs(CursorPoint.y - prevPoint.y)) > 4)
        {
            FollowGear = NULL;
            prevPoint = CursorPoint;
            return;
        }
        else
        {
            dstX = (ufloat_hwRound(FollowGear->X) + (ufloat_hwSign(FollowGear->dX) * z)) + WorldDx;
            if(WorldEdge == weWrap)
            {
                if((dstX - prevPoint.x) < ((leftX - rightX) / 2))
                {
                    CursorPoint.x = (((prevPoint.x * 7) + dstX) - (leftX - rightX)) / 8;
                }
                else
                {
                    if((dstX - prevPoint.x) > ((rightX - leftX) / 2))
                    {
                        CursorPoint.x = (((prevPoint.x * 7) + dstX) - (rightX - leftX)) / 8;
                    }
                    else
                    {
                        CursorPoint.x = ((prevPoint.x * 7) + dstX) / 8;
                    }
                }
            }
            else
            {
                CursorPoint.x = ((prevPoint.x * 7) + dstX) / 8;
            }
            if((uutils_isPhone() || (cScreenHeight < 600)) || (((hwFloat)ufloat_hwFloat_LongInt_op_mul(FollowGear->dY, z)).Round < 10))
            {
                CursorPoint.y = (((prevPoint.y * 7) + cScreenHeight) - (ufloat_hwRound(FollowGear->Y) + WorldDy)) / 8;
            }
            else
            {
                CursorPoint.y = (((prevPoint.y * 7) + cScreenHeight) - ((ufloat_hwRound(FollowGear->Y) + (ufloat_hwSign(FollowGear->dY) * z)) + WorldDy)) / 8;
            }
        }
    }
    if(WorldEdge == weWrap)
    {
        if(-WorldDx < leftX)
        {
            WorldDx = (WorldDx - rightX) + leftX;
        }
        else
        {
            if(-WorldDx > rightX)
            {
                WorldDx = (WorldDx + rightX) - leftX;
            }
        }
    }
    if((CursorPoint.x == prevPoint.x) && (CursorPoint.y == prevPoint.y))
    {
        uworld_CameraBounds();
        return;
    }
    if((AMState == AMShowingUp) || (AMState == AMShowing))
    {
        if(CursorPoint.x < ((AmmoRect.x + amNumOffsetX) + 3))
        {
            CursorPoint.x = (AmmoRect.x + amNumOffsetX) + 3;
        }
        if(CursorPoint.x > ((AmmoRect.x + AmmoRect.w) - 3))
        {
            CursorPoint.x = (AmmoRect.x + AmmoRect.w) - 3;
        }
        if(CursorPoint.y > (((cScreenHeight - AmmoRect.y) - amNumOffsetY) - 1))
        {
            CursorPoint.y = ((cScreenHeight - AmmoRect.y) - amNumOffsetY) - 1;
        }
        if(CursorPoint.y < (cScreenHeight - (((AmmoRect.y + AmmoRect.h) - AMSlotSize) - 5)))
        {
            CursorPoint.y = cScreenHeight - (((AmmoRect.y + AmmoRect.h) - AMSlotSize) - 5);
        }
        prevPoint = CursorPoint;
        uworld_CameraBounds();
        return;
    }
    if(isCursorVisible)
    {
        if(!CurrentTeam->ExtDriven && (GameTicks >= (PrevSentPointTime + cSendCursorPosTime)))
        {
            uio_SendIPCXY(0x50, CursorPoint.x - WorldDx, (cScreenHeight - CursorPoint.y) - WorldDy);
            PrevSentPointTime = GameTicks;
        }
        EdgesDist = cCursorEdgesDist;
    }
    else
    {
        EdgesDist = cGearScrEdgesDist;
    }
    if((((CurrentTeam->ExtDriven && isCursorVisible) && autoCameraOn) || (!CurrentTeam->ExtDriven && isCursorVisible)) || ((FollowGear != NULL) && autoCameraOn))
    {
        if(CursorPoint.x < (-fpcrtl_trunc(cScreenWidth /(float) cScaleFactor) + EdgesDist))
        {
            WorldDx = ((WorldDx - CursorPoint.x) - fpcrtl_trunc(cScreenWidth /(float) cScaleFactor)) + EdgesDist;
            CursorPoint.x = -fpcrtl_trunc(cScreenWidth /(float) cScaleFactor) + EdgesDist;
        }
        else
        {
            if(CursorPoint.x > (fpcrtl_trunc(cScreenWidth /(float) cScaleFactor) - EdgesDist))
            {
                WorldDx = ((WorldDx - CursorPoint.x) + fpcrtl_trunc(cScreenWidth /(float) cScaleFactor)) - EdgesDist;
                CursorPoint.x = fpcrtl_trunc(cScreenWidth /(float) cScaleFactor) - EdgesDist;
            }
        }
        shs = uutils_Min(((cScreenHeight / 2) - fpcrtl_trunc(cScreenHeight /(float) cScaleFactor)) + EdgesDist, cScreenHeight - EdgesDist);
        if(CursorPoint.y < shs)
        {
            WorldDy = (WorldDy + CursorPoint.y) - shs;
            CursorPoint.y = shs;
        }
        else
        {
            if(CursorPoint.y > (cScreenHeight - EdgesDist))
            {
                WorldDy = ((WorldDy + CursorPoint.y) - cScreenHeight) + EdgesDist;
                CursorPoint.y = cScreenHeight - EdgesDist;
            }
        }
    }
    else
    {
        if(cHasFocus)
        {
            WorldDx = (WorldDx - CursorPoint.x) + prevPoint.x;
            WorldDy = (WorldDy + CursorPoint.y) - prevPoint.y;
            CursorPoint.x = 0;
            CursorPoint.y = cScreenHeight / 2;
        }
    }
    prevPoint = CursorPoint;
    uworld_CameraBounds();
};
void uworld_ShowMission_5(astring caption,astring subcaption,astring text,LongInt icon,LongInt time)
{
    uworld_ShowMission_6(caption, subcaption, text, icon, time, false);
};
void uworld_ShowMission_6(astring caption,astring subcaption,astring text,LongInt icon,LongInt time,boolean forceDisplay)
{
    TSDL_Rect r;
    if(cOnlyStats)
    {
        return;
    }
    r.w = 32;
    r.h = 32;
    isForceMission = forceDisplay;
    if(time == 0)
    {
        time = 5000;
    }
    missionTimer = time;
    utextures_FreeAndNilTexture(&(missionTex));
    if(icon > -1)
    {
        r.x = 0;
        r.y = icon * 32;
        missionTex = ustore_RenderHelpWindow(caption, subcaption, text, fpcrtl_str2astr(__str0), 0, MissionIcons, &(r));
    }
    else
    {
        r.x = ((-icon - 1) >> 4) * 32;
        r.y = ((-icon - 1) % 16) * 32;
        missionTex = ustore_RenderHelpWindow(caption, subcaption, text, fpcrtl_str2astr(__str0), 0, SpritesData[sprAMAmmos].Surface, &(r));
    }
};
void uworld_HideMission()
{
    missionTimer = 0;
    isForceMission = false;
};
void uworld_SetAmmoTexts(TAmmoType ammoType,astring name,astring caption,astring description,boolean autoLabels)
{
    TAmmoStrId ammoStrId;
    astring ammoStr;
    PSDL_Surface tmpsurf;
    if(cOnlyStats)
    {
        return;
    }
    ammoStrId = Ammoz[ammoType].NameId;
    trluaammo[ammoStrId] = name;
    if(fpcrtl_LengthA(trluaammo[ammoStrId]) > 0)
    {
        ammoStr = trluaammo[ammoStrId];
    }
    else
    {
        ammoStr = trammo[ammoStrId];
    }
    if(udebug_checkFails(fpcrtl_LengthA(ammoStr) > 0, _strappend(_strconcat(__str1, uutils_IntToStr((ammoType))), 0x21), true))
    {
        return;
    }
    tmpsurf = TTF_RenderUTF8_Blended(Fontz[uutils_CheckCJKFont(ammoStr, fnt16)].Handle, fpcrtl__pcharA(ammoStr), cWhiteColorChannels);
    if(udebug_checkFails(tmpsurf != NULL, _strconcat(_strconcat(__str2, uutils_IntToStr((ammoType))), __str3), true))
    {
        return;
    }
    tmpsurf = umisc_doSurfaceConversion(tmpsurf);
    utextures_FreeAndNilTexture(&(Ammoz[ammoType].NameTex));
    Ammoz[ammoType].NameTex = utextures_Surface2Tex(tmpsurf, false);
    SDL_FreeSurface(tmpsurf);
    trluaammoc[ammoStrId] = caption;
    trluaammod[ammoStrId] = description;
    trluaammoe[ammoStrId] = autoLabels;
};
void uworld_ShakeCamera(LongInt amount)
{
    if(isCursorVisible)
    {
        return;
    }
    amount = uutils_Max(1, fpcrtl_round((amount * zoom) /(float) 2));
    WorldDx = (WorldDx - amount) + ((LongInt)fpcrtl_random(1 + (amount * 2)));
    WorldDy = (WorldDy - amount) + ((LongInt)fpcrtl_random(1 + (amount * 2)));
};
void uworld_onFocusStateChanged()
{
    if(!cHasFocus && (GameState != gsConfirm))
    {
        ucommands_ParseCommand_2(__str4, true);
    }
    {
        if(!cHasFocus)
        {
            usound_DampenAudio();
        }
        else
        {
            usound_UndampenAudio();
        }
    }
};
void uworld_updateCursorVisibility()
{
    if((isPaused || isAFK) || (GameState == gsConfirm))
    {
        SDL_SetRelativeMouseMode(SDL_FALSE);
        if(SDL_ShowCursor(SDL_QUERY) == SDL_DISABLE)
        {
            ucursor_resetPosition();
            SDL_ShowCursor(SDL_ENABLE);
        }
    }
    else
    {
        ucursor_resetPositionDelta();
        SDL_ShowCursor(SDL_DISABLE);
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }
};
void uworld_updateTouchWidgets(TAmmoType ammoType)
{
    UNUSED (ammoType);
};
void uworld_SetUtilityWidgetState(TAmmoType ammoType)
{
    UNUSED (ammoType);
};
void uworld_animateWidget(POnScreenWidget widget,boolean fade,boolean showWidget)
{
    {
        (*widget).show = showWidget;
        if(fade)
        {
            (*widget).fadeAnimStart = RealTicks;
        }
        {
            (*widget).moveAnim.animate = true;
            (*widget).moveAnim.startTime = RealTicks;
            (*widget).moveAnim.source.x = (*widget).moveAnim.source.x ^ (*widget).moveAnim.target.x;
            (*widget).moveAnim.target.x = (*widget).moveAnim.source.x ^ (*widget).moveAnim.target.x;
            (*widget).moveAnim.source.x = (*widget).moveAnim.source.x ^ (*widget).moveAnim.target.x;
            (*widget).moveAnim.source.y = (*widget).moveAnim.source.y ^ (*widget).moveAnim.target.y;
            (*widget).moveAnim.target.y = (*widget).moveAnim.source.y ^ (*widget).moveAnim.target.y;
            (*widget).moveAnim.source.y = (*widget).moveAnim.source.y ^ (*widget).moveAnim.target.y;
        }
    }
};
void uworld_initModule()
{
    fpsTexture = NULL;
    recTexture = NULL;
    FollowGear = NULL;
    WindBarWidth = 0;
    bShowAmmoMenu = false;
    bSelected = false;
    bShowFinger = false;
    Frames = 0;
    WorldDx = -512;
    WorldDy = -256;
    PrevSentPointTime = 0;
    FPS = 0;
    CountTicks = 0;
    SoundTimerTicks = 0;
    prevPoint.x = 0;
    prevPoint.y = 0;
    missionTimer = 0;
    missionTex = NULL;
    cOffsetY = 0;
    AMState = AMHidden;
    isFirstFrame = true;
    fpcrtl_FillChar(WorldFade, sizeof(WorldFade), 0);
    WorldFade[0].a = 255;
    WorldFade[1].a = 255;
    fpcrtl_FillChar(WorldEnd, sizeof(WorldEnd), 0);
    WorldEnd[0].a = 255;
    WorldEnd[1].a = 255;
    WorldEnd[2].a = 255;
    WorldEnd[3].a = 255;
    AmmoMenuTex = NULL;
    AmmoMenuInvalidated = true;
};
void uworld_freeModule()
{
    uworld_ResetWorldTex();
};
