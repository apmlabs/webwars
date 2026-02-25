#pragma once

#include "pas2c.h"

#include "SysUtils.h"
#include "uConsts.h"
#include "SDLh.h"
#include "GL.h"
#include "uTypes.h"
#include "uLandTexture.h"
#include "uCaptions.h"
#include "uChat.h"
void ustore_initModule();
void ustore_freeModule();
void ustore_LoadFonts();
void ustore_StoreLoad(boolean reload);
void ustore_StoreRelease(boolean reload);
void ustore_RenderHealth(THedgehog (*Hedgehog));
PTexture ustore_makeHealthBarTexture(LongWord w,LongWord h,LongWord Color);
void ustore_AddProgress();
void ustore_FinishProgress();
void ustore_LoadFont(THWFont font);
PSDL_Surface ustore_LoadImage(string255 filename,LongInt imageFlags);
PSDL_Surface ustore_LoadDataImage(TPathType path,string255 filename,LongInt imageFlags);
PSDL_Surface ustore_LoadDataImageAltPath(TPathType path,TPathType altPath,string255 filename,LongInt imageFlags);
PSDL_Surface ustore_LoadDataImageAltFile(TPathType path,string255 filename,string255 altFile,LongInt imageFlags);
void ustore_LoadHedgehogHat(THedgehog (*HH),string255 newHat);
void ustore_LoadHedgehogHat2(THedgehog (*HH),string255 newHat,boolean allowSurfReuse);
void ustore_LoadDefaultClanColors(string255 s);
void ustore_InitZoom(real zoom);
void ustore_SetupOpenGL();
PTexture ustore_RenderHelpWindow(astring caption,astring subcaption,astring description,astring extra,LongInt extracolor,PSDL_Surface iconsurf,PSDL_Rect iconrect);
void ustore_RenderWeaponTooltip(TAmmoType atype);
void ustore_ShowWeaponTooltip(LongInt x,LongInt y);
void ustore_MakeCrossHairs();
void ustore_WarpMouse(Word x,Word y);
void ustore_SwapBuffers();
void ustore_SetSkyColor(real r,real g,real b);

