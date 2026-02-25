#include "fpcrtl.h"

#include "uLandPainted.h"
#include "uLandGraphics.h"
#include "uConsts.h"
#include "uVariables.h"
#include "uUtils.h"
#include "SDLh.h"
#include "uCommands.h"
#include "uScript.h"
#include "uIO.h"
static const string255 __str1 = STRINIT("draw");
static const string255 __str0 = STRINIT("onSpecialPoint");
typedef struct __PointRec {
            SmallInt X;
            SmallInt Y;
            Byte flags;
        } PointRec;
typedef struct __PointRec * PPointRec;
typedef struct __PointEntry * PPointEntry;
typedef struct __PointEntry {
            PointRec point;
            PPointEntry next;
        } PointEntry;
static PPointEntry pointsListHead;
static PPointEntry pointsListLast;
void ulandpainted_chDraw(string255 (*s))
{
    PointRec rec;
    PPointRec prec;
    PPointEntry pe;
    Byte i;
    Byte l;
    i = 1;
    l = fpcrtl_Length((*s));
    while(i < l)
    {
        prec = ((PPointRec)&((*s).s[i]));
        rec = (*prec);
        rec.X = sdlh_SDLNet_Read16(&(rec.X));
        rec.Y = sdlh_SDLNet_Read16(&(rec.Y));
        if(rec.X < -318)
        {
            rec.X = -318;
        }
        if(rec.X > (4096 + 318))
        {
            rec.X = 4096 + 318;
        }
        if(rec.Y < -318)
        {
            rec.Y = -318;
        }
        if(rec.Y > (2048 + 318))
        {
            rec.Y = 2048 + 318;
        }
        fpcrtl_new(pe);
        if(pointsListLast == NULL)
        {
            pointsListHead = pe;
        }
        else
        {
            pointsListLast->next = pe;
        }
        pointsListLast = pe;
        pe->point = rec;
        pe->next = NULL;
        i += 5;
    }
};
void ulandpainted_Draw()
{
    PPointEntry pe;
    PointRec prevPoint;
    LongInt radius;
    LongWord color;
    LongWord Xoffset;
    LongWord Yoffset;
    LongWord lineNumber;
    LongWord linePoints;
    prevPoint.X = 0;
    prevPoint.Y = 0;
    radius = 0;
    linePoints = 0;
    Xoffset = (LAND_WIDTH - playWidth) / 2;
    Yoffset = LAND_HEIGHT - playHeight;
    pe = pointsListHead;
    while((pe != NULL) && ((pe->point.flags & 0x80) == 0))
    {
        uscript_ScriptCall_4(__str0, pe->point.X, pe->point.Y, pe->point.flags);
        pe = pe->next;
    }
    lineNumber = 0;
    while(pe != NULL)
    {
        pe->point.X = ((((LongInt)pe->point.X) * playWidth) / 4096) + Xoffset;
        pe->point.Y = ((((LongInt)pe->point.Y) * playHeight) / 2048) + Yoffset;
        if((pe->point.flags & 0x80) != 0)
        {
            if(((lineNumber > 0) && (linePoints == 0)) && cAdvancedMapGenMode)
            {
                uio_SendIPC(_strprepend(0x7c, uutils_IntToStr(lineNumber - 1)));
            }
            ++lineNumber;
            if((pe->point.flags & 0x40) != 0)
            {
                color = 0;
            }
            else
            {
                color = lfBasic;
            }
            radius = ((pe->point.flags & 0x3f) * 5) + 3;
            radius = (radius * playWidth) / 4096;
            linePoints = ulandgraphics_FillRoundInLand(pe->point.X, pe->point.Y, radius, color);
        }
        else
        {
            linePoints += ulandgraphics_DrawThickLine(prevPoint.X, prevPoint.Y, pe->point.X, pe->point.Y, radius, color);
        }
        prevPoint = pe->point;
        pe = pe->next;
    }
    if(topY > 0)
    {
        ulandgraphics_EraseLandRectRaw(0, 0, LAND_WIDTH, topY);
    }
    if(leftX > 0)
    {
        ulandgraphics_EraseLandRectRaw(0, topY, leftX, LAND_HEIGHT - topY);
    }
    if(rightX < (LAND_WIDTH - 1))
    {
        ulandgraphics_EraseLandRectRaw(rightX + 1, topY, LAND_WIDTH - (rightX + 1), LAND_HEIGHT - topY);
    }
};
void ulandpainted_initModule()
{
    pointsListHead = NULL;
    pointsListLast = NULL;
    ucommands_RegisterVariable_3(__str1, &(ulandpainted_chDraw), false);
};
void ulandpainted_freeModule()
{
    PPointEntry pe;
    PPointEntry pp;
    pe = pointsListHead;
    while(pe != NULL)
    {
        pp = pe;
        pe = pe->next;
        fpcrtl_dispose(pp);
    }
};
