#include "fpcrtl.h"

#include "uGearsHandlers.h"
#include "SDLh.h"
#include "uFloat.h"
#include "uCollisions.h"
#include "uVariables.h"
#include "uGearsUtils.h"
typedef TPoint dirs_tt[(3 + 1)];
static dirs_tt dirs = {{
                           .x = 0,
                           .y = -1
                       },
                       {
                           .x = 1,
                           .y = 0
                       },
                       {
                           .x = 0,
                           .y = 1
                       },
                       {
                           .x = -1,
                           .y = 0
                       }};
void ugearshandlers_PrevAngle(PGear Gear,LongInt dA)
{
    ++Gear->WDTimer;
    Gear->Angle = (((LongInt)Gear->Angle) - dA) & 3;
};
void ugearshandlers_NextAngle(PGear Gear,LongInt dA)
{
    ++Gear->WDTimer;
    Gear->Angle = (((LongInt)Gear->Angle) + dA) & 3;
};
boolean ugearshandlers_cakeStep(PGear Gear)
{
    boolean cakestep_result;
    LongInt xx;
    LongInt yy;
    LongInt xxn;
    LongInt yyn;
    LongInt dA;
    dA = ufloat_hwSign(Gear->dX);
    xx = dirs[Gear->Angle].x;
    yy = dirs[Gear->Angle].y;
    xxn = dirs[(((LongInt)Gear->Angle) + dA) & 3].x;
    yyn = dirs[(((LongInt)Gear->Angle) + dA) & 3].y;
    if(xx == 0)
    {
        if(ucollisions_TestCollisionYwithGear(Gear, yy) != 0)
        {
            ugearshandlers_PrevAngle(Gear, dA);
        }
        else
        {
            Gear->Tag = 0;
            if(ucollisions_TestCollisionXwithGear(Gear, xxn) != 0)
            {
                Gear->WDTimer = 0;
            }
            Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, ufloat_int2hwFloat(yy));
            if(ucollisions_TestCollisionXwithGear(Gear, xxn) == 0)
            {
                Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, ufloat_int2hwFloat(xxn));
                ugearshandlers_NextAngle(Gear, dA);
            }
        }
    }
    if(yy == 0)
    {
        if(ucollisions_TestCollisionXwithGear(Gear, xx) != 0)
        {
            ugearshandlers_PrevAngle(Gear, dA);
        }
        else
        {
            Gear->Tag = 0;
            if(ucollisions_TestCollisionYwithGear(Gear, yyn) != 0)
            {
                Gear->WDTimer = 0;
            }
            Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, ufloat_int2hwFloat(xx));
            if(ucollisions_TestCollisionYwithGear(Gear, yyn) == 0)
            {
                Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, ufloat_int2hwFloat(yyn));
                ugearshandlers_NextAngle(Gear, dA);
            }
        }
    }
    if((WorldEdge == weWrap) && ((ufloat_hwRound(Gear->X) < leftX) || (ufloat_hwRound(Gear->X) > rightX)))
    {
        LeftImpactTimer = 150;
        RightImpactTimer = 150;
        Gear->WDTimer = 0;
        Gear->Karma = 1;
    }
    else
    {
        if((WorldEdge == weBounce) && (((ufloat_hwRound(Gear->X) - Gear->Radius) < leftX) || ((ufloat_hwRound(Gear->X) + Gear->Radius) > rightX)))
        {
            if((ufloat_hwRound(Gear->X) - Gear->Radius) < leftX)
            {
                LeftImpactTimer = 333;
            }
            else
            {
                RightImpactTimer = 333;
            }
            Gear->Karma = 2;
            Gear->WDTimer = 0;
            if((Gear->Radius > 2) && (Gear->dX.QWordValue > _0_001.QWordValue))
            {
                ugearsutils_AddBounceEffectForGear_1(Gear);
            }
        }
    }
    cakestep_result = Gear->WDTimer < 4;
    return cakestep_result;
};
