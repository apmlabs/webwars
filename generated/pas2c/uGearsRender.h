#pragma once

#include "pas2c.h"

#include "uTypes.h"
#include "uConsts.h"
#include "GL.h"
#include "uFloat.h"
#include "SDLh.h"
typedef struct __Tar {
            hwFloat X;
            hwFloat Y;
            hwFloat dLen;
            boolean b;
        } Tar;
typedef struct __TRopePoints {
            LongWord Count;
            GLfloat HookAngle;
            Tar ar[(MAXROPEPOINTS + 1)];
            TVertex2f rounded[((MAXROPEPOINTS + 2) + 1)];
        } TRopePoints;
void ugearsrender_RenderGear(PGear Gear,LongInt x,LongInt y);
void ugearsrender_RenderGearTimer(PGear Gear,LongInt x,LongInt y);
void ugearsrender_RenderGearHealth(PGear Gear,LongInt x,LongInt y);
void ugearsrender_RenderFinger(PGear Gear,LongInt ox,LongInt oy);
void ugearsrender_RenderHHGuiExtras(PGear Gear,LongInt ox,LongInt oy);
void ugearsrender_RenderAirMineGuiExtras(PGear Gear,LongInt ox,LongInt oy);
void ugearsrender_DrawHHOrder();
typedef struct __RopePoints_tt {
            LongWord Count;
            GLfloat HookAngle;
            struct __ar {
                hwFloat X;
                hwFloat Y;
                hwFloat dLen;
                boolean b;
                boolean sx;
                boolean sy;
                boolean sb;
            } ar[(MAXROPEPOINTS + 1)];
            TVertex2f rounded[((MAXROPEPOINTS + 2) + 1)];
        } RopePoints_tt;
extern RopePoints_tt RopePoints;

