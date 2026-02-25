#pragma once

#include "pas2c.h"

#include "SDLh.h"
void ulandobjects_AddObjects();
void ulandobjects_FreeLandObjects();
void ulandobjects_LoadThemeConfig();
void ulandobjects_BlitImageAndGenerateCollisionInfo_4(LongWord cpX,LongWord cpY,LongWord Width,PSDL_Surface Image);
void ulandobjects_BlitImageAndGenerateCollisionInfo_5(LongWord cpX,LongWord cpY,LongWord Width,PSDL_Surface Image,Word LandFlags);
void ulandobjects_BlitImageAndGenerateCollisionInfo_6(LongWord cpX,LongWord cpY,LongWord Width,PSDL_Surface Image,Word LandFlags,boolean Flip);
void ulandobjects_BlitOverlayAndGenerateCollisionInfo(LongWord cpX,LongWord cpY,PSDL_Surface Image);
void ulandobjects_BlitImageUsingMask(LongWord cpX,LongWord cpY,PSDL_Surface Image,PSDL_Surface Mask);
void ulandobjects_AddOnLandObjects(PSDL_Surface Surface);
void ulandobjects_SetLand(LongInt y,LongInt x,LongWord Pixel);

