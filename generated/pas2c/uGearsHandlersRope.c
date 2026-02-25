#include "fpcrtl.h"

#include "uGearsHandlersRope.h"
#include "uConsts.h"
#include "uFloat.h"
#include "uCollisions.h"
#include "uVariables.h"
#include "uGearsList.h"
#include "uSound.h"
#include "uGearsUtils.h"
#include "uAmmos.h"
#include "uDebug.h"
#include "uUtils.h"
#include "uGearsHedgehog.h"
#include "uGearsRender.h"
#include "uLandUtils.h"
static const string255 __str3 = STRINIT("ERROR: doStepRopeAttach called while HHGear = nil");
static const string255 __str2 = STRINIT("Rope points overflow");
static const string255 __str1 = STRINIT("ERROR: doStepRopeWork called while HHGear = nil");
static const string255 __str0 = STRINIT("ERROR: doStepRopeAfterAttack called while HHGear = nil");
static const bool IsNilHHFatal = false;
void ugearshandlersrope_doStepRopeAfterAttack(PGear Gear)
{
    PGear HHGear;
    hwFloat tX;
    HHGear = (*Gear->Hedgehog).Gear;
    if(HHGear == NULL)
    {
        udebug_OutError(__str0, IsNilHHFatal);
        ugearslist_DeleteGear(Gear);
        return;
    }
    else
    {
        if(!CurrentTeam->ExtDriven && (FollowGear != NULL))
        {
            FollowGear = HHGear;
        }
    }
    tX = HHGear->X;
    if((ugearsutils_WorldWrap(&(HHGear)) && (WorldEdge == weWrap)) && ((ucollisions_TestCollisionXwithGear(HHGear, 1) != 0) || (ucollisions_TestCollisionXwithGear(HHGear, -1) != 0)))
    {
        HHGear->X = tX;
        HHGear->dX.isNegative = ufloat_hwRound(tX) > (leftX + (HHGear->Radius * 2));
    }
    if(((*HHGear->Hedgehog).CurAmmoType == amParachute) && (ufloat_hwFloat_hwFloat_op_gt(HHGear->dY, _0_39)))
    {
        ugearslist_DeleteGear(Gear);
        uammos_ApplyAmmoChanges(&((*HHGear->Hedgehog)));
        HHGear->Message = HHGear->Message | gmLJump;
        return;
    }
    if((((HHGear->State & gstHHDriven) == 0) || ugearsutils_CheckGearDrowning(&(HHGear))) || (ucollisions_TestCollisionYwithGear(HHGear, 1) != 0))
    {
        ugearslist_DeleteGear(Gear);
        if((((ucollisions_TestCollisionYwithGear(HHGear, 1) != 0) && (uammos_GetAmmoEntry(&((*HHGear->Hedgehog)), amRope)->Count >= 1)) && ((Ammoz[(*HHGear->Hedgehog).CurAmmoType].Ammo.Propz & ammoprop_AltUse) != 0)) && ((*HHGear->Hedgehog).MultiShootAttacks == 0))
        {
            (*HHGear->Hedgehog).CurAmmoType = amRope;
        }
        isCursorVisible = false;
        uammos_ApplyAmmoChanges(&((*HHGear->Hedgehog)));
        return;
    }
    ugearshedgehog_HedgehogChAngle(HHGear);
    if(ucollisions_TestCollisionXwithGear(HHGear, ufloat_hwSign(HHGear->dX)) != 0)
    {
        uutils_SetLittle(&(HHGear->dX));
    }
    if(HHGear->dY.isNegative && (ucollisions_TestCollisionYwithGear(HHGear, -1) != 0))
    {
        HHGear->dY = _0;
    }
    HHGear->X = ufloat_hwFloat_hwFloat_op_add(HHGear->X, HHGear->dX);
    HHGear->Y = ufloat_hwFloat_hwFloat_op_add(HHGear->Y, HHGear->dY);
    HHGear->dY = ufloat_hwFloat_hwFloat_op_add(HHGear->dY, cGravity);
    if((GameFlags & gfMoreWind) != 0)
    {
        HHGear->dX = ufloat_hwFloat_hwFloat_op_add(HHGear->dX, ufloat_hwFloat_hwFloat_op_div(cWindSpeed, HHGear->Density));
    }
    if((Gear->Message & gmAttack) != 0)
    {
        Gear->X = HHGear->X;
        Gear->Y = HHGear->Y;
        uammos_ApplyAngleBounds(&((*Gear->Hedgehog)), amRope);
        Gear->dX = ufloat_SignAs(ufloat_AngleSin(HHGear->Angle), HHGear->dX);
        Gear->dY = ufloat_hwFloat_op_sub(ufloat_AngleCos(HHGear->Angle));
        Gear->Friction = ufloat_hwFloat_LongInt_op_mul(_4_5, cRopePercent);
        Gear->Elasticity = _0;
        Gear->State = Gear->State & ~gsttmpFlag;
        Gear->doStep = &(ugearshandlersrope_doStepRope);
    }
};
void ugearshandlersrope_RopeDeleteMe(PGear Gear,PGear HHGear)
{
    {
        (*HHGear).Message = (*HHGear).Message & ~gmAttack;
        (*HHGear).State = ((*HHGear).State | gstMoving) & ~gstWinner;
    }
    ugearslist_DeleteGear(Gear);
};
void ugearshandlersrope_RopeWaitCollision(PGear Gear,PGear HHGear)
{
    {
        (*HHGear).Message = (*HHGear).Message & ~gmAttack;
        (*HHGear).State = (*HHGear).State | gstMoving;
    }
    RopePoints.Count = 0;
    Gear->Elasticity = _0;
    Gear->doStep = &(ugearshandlersrope_doStepRopeAfterAttack);
};
void ugearshandlersrope_doStepRopeWork(PGear Gear)
{
    PGear HHGear;
    hwFloat len;
    hwFloat tx;
    hwFloat ty;
    hwFloat nx;
    hwFloat ny;
    hwFloat ropeDx;
    hwFloat ropeDy;
    hwFloat mdX;
    hwFloat mdY;
    LongInt lx;
    LongInt ly;
    LongInt cd;
    boolean haveCollision;
    boolean haveDivided;
    boolean wrongSide;
    HHGear = (*Gear->Hedgehog).Gear;
    if(HHGear == NULL)
    {
        udebug_OutError(__str1, IsNilHHFatal);
        ugearslist_DeleteGear(Gear);
        return;
    }
    else
    {
        if(!CurrentTeam->ExtDriven && (FollowGear != NULL))
        {
            FollowGear = HHGear;
        }
    }
    if((((HHGear->State & gstHHDriven) == 0) || ugearsutils_CheckGearDrowning(&(HHGear))) || (Gear->PortalCounter != 0))
    {
        usound_PlaySound_1(sndRopeRelease);
        ugearshandlersrope_RopeDeleteMe(Gear, HHGear);
        return;
    }
    if((GameTicks % 4) != 0)
    {
        return;
    }
    tx = HHGear->X;
    if((ugearsutils_WorldWrap(&(HHGear)) && (WorldEdge == weWrap)) && ((ucollisions_TestCollisionXwithGear(HHGear, 1) != 0) || (ucollisions_TestCollisionXwithGear(HHGear, -1) != 0)))
    {
        usound_PlaySound_1(sndRopeRelease);
        ugearshandlersrope_RopeDeleteMe(Gear, HHGear);
        HHGear->X = tx;
        HHGear->dX.isNegative = ufloat_hwRound(tx) > (leftX + (HHGear->Radius * 2));
        return;
    }
    tx = HHGear->X;
    HHGear->dX.QWordValue = HHGear->dX.QWordValue << 2;
    HHGear->dY.QWordValue = HHGear->dY.QWordValue << 2;
    if(((Gear->Message & gmLeft) != 0) && (ucollisions_TestCollisionXwithGear(HHGear, -1) == 0))
    {
        HHGear->dX = ufloat_hwFloat_hwFloat_op_sub(HHGear->dX, _0_0032);
    }
    if(((Gear->Message & gmRight) != 0) && (ucollisions_TestCollisionXwithGear(HHGear, 1) == 0))
    {
        HHGear->dX = ufloat_hwFloat_hwFloat_op_add(HHGear->dX, _0_0032);
    }
    ropeDx = ufloat_hwFloat_hwFloat_op_sub(HHGear->X, Gear->X);
    ropeDy = ufloat_hwFloat_hwFloat_op_sub(HHGear->Y, Gear->Y);
    if(ucollisions_TestCollisionYwithXYShift_4(HHGear, 0, 1, 1) == 0)
    {
        if(ropeDx.isNegative == ropeDy.isNegative)
        {
            cd = -1;
        }
        else
        {
            cd = 1;
        }
        if(ucollisions_TestCollisionXwithXYShift_5(HHGear, ufloat_hwFloat_LongInt_op_mul(_2, cd), 0, cd, true) == 0)
        {
            HHGear->dY = ufloat_hwFloat_hwFloat_op_add(HHGear->dY, ufloat_hwFloat_LongInt_op_mul(cGravity, 16));
        }
        if((GameFlags & gfMoreWind) != 0)
        {
            if(ucollisions_TestCollisionXwithGear(HHGear, ufloat_hwSign(cWindSpeed)) == 0)
            {
                HHGear->dX = ufloat_hwFloat_hwFloat_op_add(HHGear->dX, ufloat_hwFloat_hwFloat_op_div(ufloat_hwFloat_LongInt_op_mul(cWindSpeed, 16), HHGear->Density));
            }
        }
    }
    mdX = ufloat_hwFloat_hwFloat_op_add(ropeDx, HHGear->dX);
    mdY = ufloat_hwFloat_hwFloat_op_add(ropeDy, HHGear->dY);
    len = ufloat_hwFloat_hwFloat_op_div(_1, ufloat_Distance(mdX, mdY));
    mdX = ufloat_hwFloat_hwFloat_op_mul(mdX, len);
    mdY = ufloat_hwFloat_hwFloat_op_mul(mdY, len);
    Gear->dX = mdX;
    Gear->dY = mdY;
    tx = HHGear->X;
    ty = HHGear->Y;
    if(((Gear->Message & gmDown) != 0) && (ufloat_hwFloat_hwFloat_op_lt(Gear->Elasticity, Gear->Friction)))
    {
        if(!((ucollisions_TestCollisionXwithXYShift_5(HHGear, ufloat_hwFloat_LongInt_op_mul(_2, ufloat_hwSign(ropeDx)), 0, ufloat_hwSign(ropeDx), true) != 0) || ((ropeDy.QWordValue != 0) && (ucollisions_TestCollisionYwithXYShift_4(HHGear, 0, ufloat_hwSign(ropeDy), ufloat_hwSign(ropeDy)) != 0))))
        {
            Gear->Elasticity = ufloat_hwFloat_hwFloat_op_add(Gear->Elasticity, _1_2);
        }
    }
    if(((Gear->Message & gmUp) != 0) && (ufloat_hwFloat_hwFloat_op_gt(Gear->Elasticity, _30)))
    {
        if(!((ucollisions_TestCollisionXwithXYShift_5(HHGear, ufloat_hwFloat_LongInt_op_mul(ufloat_hwFloat_op_sub(_2), ufloat_hwSign(ropeDx)), 0, -ufloat_hwSign(ropeDx), true) != 0) || ((ropeDy.QWordValue != 0) && (ucollisions_TestCollisionYwithXYShift_4(HHGear, 0, -ufloat_hwSign(ropeDy), -ufloat_hwSign(ropeDy)) != 0))))
        {
            Gear->Elasticity = ufloat_hwFloat_hwFloat_op_sub(Gear->Elasticity, _1_2);
        }
    }
    HHGear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, ufloat_hwFloat_hwFloat_op_mul(mdX, Gear->Elasticity));
    HHGear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, ufloat_hwFloat_hwFloat_op_mul(mdY, Gear->Elasticity));
    HHGear->dX = ufloat_hwFloat_hwFloat_op_sub(HHGear->X, tx);
    HHGear->dY = ufloat_hwFloat_hwFloat_op_sub(HHGear->Y, ty);
    haveDivided = false;
    len = ufloat_hwFloat_hwFloat_op_sub(Gear->Elasticity, _5);
    nx = ufloat_hwFloat_hwFloat_op_add(Gear->X, ufloat_hwFloat_hwFloat_op_mul(mdX, len));
    ny = ufloat_hwFloat_hwFloat_op_add(Gear->Y, ufloat_hwFloat_hwFloat_op_mul(mdY, len));
    tx = ufloat_hwFloat_hwFloat_op_mul(mdX, _1_2);
    ty = ufloat_hwFloat_hwFloat_op_mul(mdY, _1_2);
    while(ufloat_hwFloat_hwFloat_op_gt(len, _3))
    {
        lx = ufloat_hwRound(nx);
        ly = ufloat_hwRound(ny);
        if((((ly & LAND_HEIGHT_MASK) == 0) && ((lx & LAND_WIDTH_MASK) == 0)) && (ulandutils_LandGet(ly, lx) > lfAllObjMask))
        {
            tx = ufloat_hwFloat_hwFloat_op_div(_1, ufloat_Distance(ropeDx, ropeDy));
            nx = ufloat_hwFloat_hwFloat_op_mul(ropeDx, tx);
            ny = ufloat_hwFloat_hwFloat_op_mul(ropeDy, tx);
            {
                RopePoints.ar[RopePoints.Count].X = Gear->X;
                RopePoints.ar[RopePoints.Count].Y = Gear->Y;
                if(RopePoints.Count == 0)
                {
                    RopePoints.HookAngle = uutils_DxDy2Angle(Gear->dY, Gear->dX);
                }
                RopePoints.ar[RopePoints.Count].b = ufloat_hwFloat_hwFloat_op_gt(ufloat_hwFloat_hwFloat_op_mul(nx, HHGear->dY), ufloat_hwFloat_hwFloat_op_mul(ny, HHGear->dX));
                RopePoints.ar[RopePoints.Count].sx = Gear->dX.isNegative;
                RopePoints.ar[RopePoints.Count].sy = Gear->dY.isNegative;
                RopePoints.ar[RopePoints.Count].sb = Gear->dX.QWordValue < Gear->dY.QWordValue;
                RopePoints.ar[RopePoints.Count].dLen = len;
            }
            {
                RopePoints.rounded[RopePoints.Count].X = ufloat_hwRound(Gear->X);
                RopePoints.rounded[RopePoints.Count].Y = ufloat_hwRound(Gear->Y);
            }
            Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, ufloat_hwFloat_hwFloat_op_mul(nx, len));
            Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, ufloat_hwFloat_hwFloat_op_mul(ny, len));
            ++RopePoints.Count;
            if(udebug_checkFails(RopePoints.Count <= MAXROPEPOINTS, __str2, true))
            {
                return;
            }
            Gear->Elasticity = ufloat_hwFloat_hwFloat_op_sub(Gear->Elasticity, len);
            Gear->Friction = ufloat_hwFloat_hwFloat_op_sub(Gear->Friction, len);
            haveDivided = true;
            break;
        }
        nx = ufloat_hwFloat_hwFloat_op_sub(nx, tx);
        ny = ufloat_hwFloat_hwFloat_op_sub(ny, ty);
        len.QWordValue = ((int64_t) (len.QWordValue)) - ((int64_t) (_1_2.QWordValue));
    }
    if(!haveDivided)
    {
        if(RopePoints.Count > 0)
        {
            tx = RopePoints.ar[((int)(RopePoints.Count) - 1)].X;
            ty = RopePoints.ar[((int)(RopePoints.Count) - 1)].Y;
            mdX = ufloat_hwFloat_hwFloat_op_sub(tx, Gear->X);
            mdY = ufloat_hwFloat_hwFloat_op_sub(ty, Gear->Y);
            ropeDx = ufloat_hwFloat_hwFloat_op_sub(tx, HHGear->X);
            ropeDy = ufloat_hwFloat_hwFloat_op_sub(ty, HHGear->Y);
            if(RopePoints.ar[((int)(RopePoints.Count) - 1)].b ^ (ufloat_hwFloat_hwFloat_op_gt(ufloat_hwFloat_hwFloat_op_mul(mdX, ropeDy), ufloat_hwFloat_hwFloat_op_mul(ropeDx, mdY))))
            {
                --RopePoints.Count;
                Gear->X = tx;
                Gear->Y = ty;
                wrongSide = (ropeDx.isNegative == RopePoints.ar[RopePoints.Count].sx) && (ropeDy.isNegative == RopePoints.ar[RopePoints.Count].sy);
                if(!wrongSide && ((ropeDx.isNegative == RopePoints.ar[RopePoints.Count].sx) != (ropeDy.isNegative == RopePoints.ar[RopePoints.Count].sy)))
                {
                    if(RopePoints.ar[RopePoints.Count].sb)
                    {
                        wrongSide = ropeDy.isNegative == RopePoints.ar[RopePoints.Count].sy;
                    }
                    else
                    {
                        wrongSide = ropeDx.isNegative == RopePoints.ar[RopePoints.Count].sx;
                    }
                }
                if(wrongSide)
                {
                    Gear->Elasticity = ufloat_hwFloat_hwFloat_op_sub(Gear->Elasticity, RopePoints.ar[RopePoints.Count].dLen);
                    Gear->Friction = ufloat_hwFloat_hwFloat_op_sub(Gear->Friction, RopePoints.ar[RopePoints.Count].dLen);
                }
                else
                {
                    Gear->Elasticity = ufloat_hwFloat_hwFloat_op_add(Gear->Elasticity, RopePoints.ar[RopePoints.Count].dLen);
                    Gear->Friction = ufloat_hwFloat_hwFloat_op_add(Gear->Friction, RopePoints.ar[RopePoints.Count].dLen);
                    len = ufloat_hwFloat_hwFloat_op_div(_1, ufloat_Distance(mdX, mdY));
                    mdX = ufloat_hwFloat_hwFloat_op_mul(mdX, len);
                    mdY = ufloat_hwFloat_hwFloat_op_mul(mdY, len);
                    HHGear->X = ufloat_hwFloat_hwFloat_op_sub(Gear->X, ufloat_hwFloat_hwFloat_op_mul(mdX, Gear->Elasticity));
                    HHGear->Y = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, ufloat_hwFloat_hwFloat_op_mul(mdY, Gear->Elasticity));
                }
            }
        }
    }
    haveCollision = false;
    if(ucollisions_TestCollisionXwithXYShift_5(HHGear, ufloat_hwFloat_LongInt_op_mul(_2, ufloat_hwSign(HHGear->dX)), 0, ufloat_hwSign(HHGear->dX), true) != 0)
    {
        HHGear->dX = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_op_sub(_0_6), HHGear->dX);
        haveCollision = true;
    }
    if(ucollisions_TestCollisionYwithXYShift_4(HHGear, 0, 1 * ufloat_hwSign(HHGear->dY), ufloat_hwSign(HHGear->dY)) != 0)
    {
        HHGear->dY = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_op_sub(_0_6), HHGear->dY);
        haveCollision = true;
    }
    if((haveCollision && ((Gear->Message & (gmLeft | gmRight)) != 0)) && ((Gear->Message & (gmUp | gmDown)) != 0))
    {
        HHGear->dX = ufloat_SignAs(ufloat_hwFloat_hwFloat_op_add(ufloat_hwAbs(HHGear->dX), _0_8), HHGear->dX);
        HHGear->dY = ufloat_SignAs(ufloat_hwFloat_hwFloat_op_add(ufloat_hwAbs(HHGear->dY), _0_8), HHGear->dY);
    }
    len = ufloat_hwFloat_hwFloat_op_add(ufloat_hwSqr(HHGear->dX), ufloat_hwSqr(HHGear->dY));
    if(ufloat_hwFloat_hwFloat_op_gt(len, _10))
    {
        len = ufloat_hwFloat_hwFloat_op_div(_3_2, ufloat_hwSqrt(len));
        HHGear->dX = ufloat_hwFloat_hwFloat_op_mul(HHGear->dX, len);
        HHGear->dY = ufloat_hwFloat_hwFloat_op_mul(HHGear->dY, len);
    }
    haveCollision = (((ufloat_hwRound(Gear->Y) & LAND_HEIGHT_MASK) == 0) && ((ufloat_hwRound(Gear->X) & LAND_WIDTH_MASK) == 0)) && (ulandutils_LandGet(ufloat_hwRound(Gear->Y), ufloat_hwRound(Gear->X)) != 0);
    if(!haveCollision)
    {
        tx = Gear->X;
        ty = Gear->Y;
        if(RopePoints.Count > 0)
        {
            Gear->X = RopePoints.ar[0].X;
            Gear->Y = RopePoints.ar[0].Y;
        }
        ugearsutils_CheckCollision(Gear);
        if((Gear->State & gstCollision) == 0)
        {
            Gear->dX.isNegative = !Gear->dX.isNegative;
            Gear->dY.isNegative = !Gear->dY.isNegative;
            ugearsutils_CheckCollision(Gear);
            Gear->dX.isNegative = !Gear->dX.isNegative;
            Gear->dY.isNegative = !Gear->dY.isNegative;
        }
        haveCollision = (Gear->State & gstCollision) != 0;
        Gear->X = tx;
        Gear->Y = ty;
    }
    if((Gear->Message & gmAttack) != 0)
    {
        haveCollision = false;
    }
    HHGear->dX.QWordValue = HHGear->dX.QWordValue >> 2;
    HHGear->dY.QWordValue = HHGear->dY.QWordValue >> 2;
    if(!haveCollision && ((Gear->State & gsttmpFlag) != 0))
    {
        {
            usound_PlaySound_1(sndRopeRelease);
            if((*Gear->Hedgehog).CurAmmoType != amParachute)
            {
                ugearshandlersrope_RopeWaitCollision(Gear, HHGear);
            }
            else
            {
                ugearshandlersrope_RopeDeleteMe(Gear, HHGear);
            }
        }
    }
    else
    {
        if((Gear->State & gsttmpFlag) == 0)
        {
            Gear->State = Gear->State | gsttmpFlag;
        }
    }
};
void ugearshandlersrope_RopeRemoveFromAmmo(PGear Gear,PGear HHGear)
{
    if((Gear->State & gstAttacked) == 0)
    {
        uammos_OnUsedAmmo(&((*HHGear->Hedgehog)));
        Gear->State = Gear->State | gstAttacked;
        uammos_ApplyAmmoChanges(&((*HHGear->Hedgehog)));
    }
};
void ugearshandlersrope_doStepRopeAttach(PGear Gear)
{
    PGear HHGear;
    hwFloat tx;
    hwFloat ty;
    hwFloat tt;
    Gear->X = ufloat_hwFloat_hwFloat_op_sub(Gear->X, Gear->dX);
    Gear->Y = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, Gear->dY);
    Gear->Elasticity = ufloat_hwFloat_hwFloat_op_add(Gear->Elasticity, _1);
    HHGear = (*Gear->Hedgehog).Gear;
    if(HHGear == NULL)
    {
        udebug_OutError(__str3, IsNilHHFatal);
        ugearslist_DeleteGear(Gear);
        return;
    }
    else
    {
        if(!CurrentTeam->ExtDriven && (FollowGear != NULL))
        {
            FollowGear = HHGear;
        }
    }
    if((ugearsutils_WorldWrap(&(Gear)) && (WorldEdge == weWrap)) || ((WorldEdge == weBounce) && ((ufloat_hwRound(Gear->X) <= leftX) || (ufloat_hwRound(Gear->X) >= rightX))))
    {
        HHGear->State = HHGear->State & ~((gstAttacking | gstHHJumping) | gstHHHJump);
        HHGear->Message = HHGear->Message & ~gmAttack;
        ugearslist_DeleteGear(Gear);
        if(((uammos_GetAmmoEntry(&((*HHGear->Hedgehog)), amRope)->Count >= 1) && ((Ammoz[(*HHGear->Hedgehog).CurAmmoType].Ammo.Propz & ammoprop_AltUse) != 0)) && ((*HHGear->Hedgehog).MultiShootAttacks == 0))
        {
            (*HHGear->Hedgehog).CurAmmoType = amRope;
        }
        isCursorVisible = false;
        uammos_ApplyAmmoChanges(&((*HHGear->Hedgehog)));
        return;
    }
    ucollisions_DeleteCI(HHGear);
    if((HHGear->State & gstMoving) != 0)
    {
        ugearshedgehog_doStepHedgehogMoving(HHGear);
        Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, HHGear->dX);
        Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, HHGear->dY);
        Gear->Elasticity = ufloat_int2hwFloat(ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ufloat_Distance(ufloat_hwFloat_hwFloat_op_sub(Gear->X, HHGear->X), ufloat_hwFloat_hwFloat_op_sub(Gear->Y, HHGear->Y)), _0_001)));
        tt = Gear->Elasticity;
        tx = _0;
        ty = _0;
        while(ufloat_hwFloat_hwFloat_op_gt(tt, _20))
        {
            if((((ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(Gear->Y, ty)) & LAND_HEIGHT_MASK) == 0) && ((ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(Gear->X, tx)) & LAND_WIDTH_MASK) == 0)) && (ulandutils_LandGet(ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(Gear->Y, ty)), ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(Gear->X, tx))) > lfAllObjMask))
            {
                Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, tx);
                Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, ty);
                Gear->Elasticity = tt;
                Gear->doStep = &(ugearshandlersrope_doStepRopeWork);
                usound_PlaySound_1(sndRopeAttach);
                {
                    (*HHGear).State = (*HHGear).State & ~((gstAttacking | gstHHJumping) | gstHHHJump);
                    (*HHGear).Message = (*HHGear).Message & ~gmAttack;
                }
                ugearshandlersrope_RopeRemoveFromAmmo(Gear, HHGear);
                return;
            }
            tx = ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_add(tx, Gear->dX), Gear->dX);
            ty = ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_add(ty, Gear->dY), Gear->dY);
            tt = ufloat_hwFloat_hwFloat_op_sub(tt, _2);
        }
    }
    if(ufloat_hwFloat_hwFloat_op_lt(Gear->Elasticity, _20))
    {
        Gear->CollisionMask = lfLandMask;
    }
    else
    {
        Gear->CollisionMask = lfNotCurHogCrate;
    }
    ugearsutils_CheckCollision(Gear);
    if((Gear->State & gstCollision) != 0)
    {
        if(ufloat_hwFloat_hwFloat_op_lt(Gear->Elasticity, _10))
        {
            Gear->Elasticity = _10000;
        }
        else
        {
            Gear->doStep = &(ugearshandlersrope_doStepRopeWork);
            usound_PlaySound_1(sndRopeAttach);
            {
                (*HHGear).State = (*HHGear).State & ~((gstAttacking | gstHHJumping) | gstHHHJump);
                (*HHGear).Message = (*HHGear).Message & ~gmAttack;
            }
            ugearshandlersrope_RopeRemoveFromAmmo(Gear, HHGear);
            return;
        }
    }
    if((((ufloat_hwFloat_hwFloat_op_gt(Gear->Elasticity, Gear->Friction)) || ((Gear->Message & gmAttack) == 0)) || ((HHGear->State & gstHHDriven) == 0)) || (HHGear->Damage > 0))
    {
        {
            (*(*Gear->Hedgehog).Gear).State = (*(*Gear->Hedgehog).Gear).State & ~gstAttacking;
            (*(*Gear->Hedgehog).Gear).Message = (*(*Gear->Hedgehog).Gear).Message & ~gmAttack;
        }
        ugearslist_DeleteGear(Gear);
        if(((uammos_GetAmmoEntry(&((*HHGear->Hedgehog)), amRope)->Count >= 1) && ((Ammoz[(*HHGear->Hedgehog).CurAmmoType].Ammo.Propz & ammoprop_AltUse) != 0)) && ((*HHGear->Hedgehog).MultiShootAttacks == 0))
        {
            (*HHGear->Hedgehog).CurAmmoType = amRope;
        }
        isCursorVisible = false;
        uammos_ApplyAmmoChanges(&((*HHGear->Hedgehog)));
        return;
    }
    if(ugearsutils_CheckGearDrowning(&(HHGear)))
    {
        ugearslist_DeleteGear(Gear);
    }
};
void ugearshandlersrope_doStepRope(PGear Gear)
{
    Gear->dX = ufloat_hwFloat_op_sub(Gear->dX);
    Gear->dY = ufloat_hwFloat_op_sub(Gear->dY);
    Gear->doStep = &(ugearshandlersrope_doStepRopeAttach);
    usound_PlaySound_1(sndRopeShot);
};
