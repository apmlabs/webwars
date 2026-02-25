#include "fpcrtl.h"

#include "uCollisions.h"
#include "uConsts.h"
#include "uLandGraphics.h"
#include "uVariables.h"
#include "SDLh.h"
#include "uLandTexture.h"
#include "uDebug.h"
#include "uLandUtils.h"
static const string255 __str2 = STRINIT("It should be 32 bpp sprite");
static const string255 __str1 = STRINIT("CheckGearsUnderSprite");
static const string255 __str0 = STRINIT("Assert SpritesData[Sprite].Surface failed");
typedef struct __TCollisionEntry {
            LongInt X;
            LongInt Y;
            LongInt Radius;
            PGear cGear;
        } TCollisionEntry;
enum{MAXRECTSINDEX = 1023};
static LongWord Count;
typedef TCollisionEntry cinfos_tt[(MAXRECTSINDEX + 1)];
static cinfos_tt cinfos;
static TGearArray ga;
static TGearHitOrder ordera;
static TGearHitOrder globalordera;
static TGearProximityCache proximitya;
void ucollisions_AddCI(PGear Gear)
{
    if(((Gear->CollisionIndex >= 0) || (Count > MAXRECTSINDEX)) || ((Count > (MAXRECTSINDEX - 200)) && (((Gear->Kind == gtMine) || (Gear->Kind == gtSMine)) || (Gear->Kind == gtKnife))))
    {
        return;
    }
    {
        cinfos[Count].X = ufloat_hwRound(Gear->X);
        cinfos[Count].Y = ufloat_hwRound(Gear->Y);
        cinfos[Count].Radius = Gear->Radius;
        ulandgraphics_ChangeRoundInLand(cinfos[Count].X, cinfos[Count].Y, cinfos[Count].Radius - 1, true, ((CurrentHedgehog != NULL) && (Gear == CurrentHedgehog->Gear)) || ((Gear->Kind == gtCase) && ((Gear->State & gstFrozen) == 0)), Gear->Kind == gtHedgehog);
        cinfos[Count].cGear = Gear;
    }
    Gear->CollisionIndex = Count;
    ++Count;
};
void ucollisions_DeleteCI(PGear Gear)
{
    if(Gear->CollisionIndex >= 0)
    {
        {
            ulandgraphics_ChangeRoundInLand(cinfos[Gear->CollisionIndex].X, cinfos[Gear->CollisionIndex].Y, cinfos[Gear->CollisionIndex].Radius - 1, false, ((CurrentHedgehog != NULL) && (Gear == CurrentHedgehog->Gear)) || ((Gear->Kind == gtCase) && ((Gear->State & gstFrozen) == 0)), Gear->Kind == gtHedgehog);
        }
        cinfos[Gear->CollisionIndex] = cinfos[((int)(Count) - 1)];
        (*cinfos[Gear->CollisionIndex].cGear).CollisionIndex = Gear->CollisionIndex;
        Gear->CollisionIndex = -1;
        --Count;
    }
};
boolean ucollisions_CheckCoordInWater(LongInt X,LongInt Y)
{
    boolean checkcoordinwater_result;
    checkcoordinwater_result = (Y > cWaterLine) || ((WorldEdge == weSea) && ((X < leftX) || (X > rightX)));
    return checkcoordinwater_result;
};
PGearArray ucollisions_CheckGearsCollision(PGear Gear)
{
    PGearArray checkgearscollision_result;
    LongInt mx;
    LongInt my;
    LongInt tr;
    LongWord i;
    checkgearscollision_result = &(ga);
    ga.Count = 0;
    if(Count == 0)
    {
        return checkgearscollision_result;
    }
    mx = ufloat_hwRound(Gear->X);
    my = ufloat_hwRound(Gear->Y);
    tr = Gear->Radius + 2;
    {i = 0;
     LongWord i__end__ = ((int)(Count) - 1);
     if (i <= i__end__) do {
                               {
                                   if((Gear != cinfos[i].cGear) && ((fpcrtl_sqr(mx - cinfos[i].X) + fpcrtl_sqr(my - cinfos[i].Y)) <= fpcrtl_sqr(cinfos[i].Radius + tr)))
                                   {
                                       ga.ar[ga.Count] = cinfos[i].cGear;
                                       ga.cX[ga.Count] = ufloat_hwRound(Gear->X);
                                       ga.cY[ga.Count] = ufloat_hwRound(Gear->Y);
                                       ++ga.Count;
                                   }
                               }
                           } while(i++ != i__end__);}
    return checkgearscollision_result;
};
PGearArray ucollisions_CheckAllGearsCollision(PGear SourceGear)
{
    PGearArray checkallgearscollision_result;
    LongInt mx;
    LongInt my;
    LongInt tr;
    PGear Gear;
    checkallgearscollision_result = &(ga);
    ga.Count = 0;
    mx = ufloat_hwRound(SourceGear->X);
    my = ufloat_hwRound(SourceGear->Y);
    tr = SourceGear->Radius + 2;
    Gear = GearsList;
    while(Gear != NULL)
    {
        if((Gear != SourceGear) && ((fpcrtl_sqr(mx - ufloat_hwRound(Gear->X)) + fpcrtl_sqr(my - ufloat_hwRound(Gear->Y))) <= fpcrtl_sqr(Gear->Radius + tr)))
        {
            ga.ar[ga.Count] = Gear;
            ga.cX[ga.Count] = mx;
            ga.cY[ga.Count] = my;
            ++ga.Count;
        }
        Gear = Gear->NextGear;
    }
    return checkallgearscollision_result;
};
TLineCollision ucollisions_LineCollisionTest(hwFloat oX,hwFloat oY,hwFloat dirX,hwFloat dirY,hwFloat dirNormSqr,hwFloat dirNormBound,LongInt width,PGear Gear)
{
    TLineCollision linecollisiontest_result;
    hwFloat toCenterX;
    hwFloat toCenterY;
    hwFloat r;
    hwFloat b;
    hwFloat bSqr;
    hwFloat c;
    hwFloat desc;
    hwFloat t;
    extended realT;
    linecollisiontest_result.hasCollision = false;
    toCenterX = ufloat_hwFloat_hwFloat_op_sub(oX, Gear->X);
    toCenterY = ufloat_hwFloat_hwFloat_op_sub(oY, Gear->Y);
    r = ufloat_int2hwFloat((Gear->Radius + width) + 2);
    if(ufloat_hwFloat_hwFloat_op_gt(ufloat_hwFloat_hwFloat_op_add(ufloat_hwAbs(toCenterX), ufloat_hwAbs(toCenterY)), ufloat_hwFloat_hwFloat_op_add(dirNormBound, r)))
    {
        return linecollisiontest_result;
    }
    b = ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_mul(dirX, toCenterX), ufloat_hwFloat_hwFloat_op_mul(dirY, toCenterY));
    c = ufloat_hwFloat_hwFloat_op_sub(ufloat_hwFloat_hwFloat_op_add(ufloat_hwSqr(toCenterX), ufloat_hwSqr(toCenterY)), ufloat_hwSqr(r));
    if((ufloat_hwFloat_hwFloat_op_gt(b, _0)) && (ufloat_hwFloat_hwFloat_op_gt(c, _0)))
    {
        return linecollisiontest_result;
    }
    bSqr = ufloat_hwSqr(b);
    desc = ufloat_hwFloat_hwFloat_op_sub(bSqr, ufloat_hwFloat_hwFloat_op_mul(dirNormSqr, c));
    if(desc.isNegative)
    {
        return linecollisiontest_result;
    }
    t = ufloat_hwFloat_hwFloat_op_sub(ufloat_hwFloat_op_sub(b), ufloat_hwSqrt(desc));
    if(t.isNegative)
    {
        t = _0;
    }
    if(ufloat_hwFloat_hwFloat_op_lt(t, dirNormSqr))
    {
        {
            linecollisiontest_result.hasCollision = true;
            realT = ufloat_hwFloat2Float(t) /(float) ufloat_hwFloat2Float(dirNormSqr);
            linecollisiontest_result.cX = fpcrtl_round(ufloat_hwFloat2Float(oX) + (realT * ufloat_hwFloat2Float(dirX)));
            linecollisiontest_result.cY = fpcrtl_round(ufloat_hwFloat2Float(oY) + (realT * ufloat_hwFloat2Float(dirY)));
        }
    }
    return linecollisiontest_result;
};
PGearArray ucollisions_CheckGearsLineCollision(PGear Gear,hwFloat oX,hwFloat oY,hwFloat tX,hwFloat tY)
{
    PGearArray checkgearslinecollision_result;
    hwFloat dirX;
    hwFloat dirY;
    hwFloat dirNormSqr;
    hwFloat dirNormBound;
    TLineCollision test;
    LongWord i;
    checkgearslinecollision_result = &(ga);
    ga.Count = 0;
    if(Count == 0)
    {
        return checkgearslinecollision_result;
    }
    dirX = ufloat_hwFloat_hwFloat_op_sub(tX, oX);
    dirY = ufloat_hwFloat_hwFloat_op_sub(tY, oY);
    dirNormBound = ufloat_hwFloat_hwFloat_op_mul(_1_5, ufloat_hwFloat_hwFloat_op_add(ufloat_hwAbs(dirX), ufloat_hwAbs(dirY)));
    dirNormSqr = ufloat_hwFloat_hwFloat_op_add(ufloat_hwSqr(dirX), ufloat_hwSqr(dirY));
    if(dirNormSqr.isNegative)
    {
        return checkgearslinecollision_result;
    }
    {i = 0;
     LongWord i__end__ = ((int)(Count) - 1);
     if (i <= i__end__) do {
                               {
                                   if(Gear != cinfos[i].cGear)
                                   {
                                       test = ucollisions_LineCollisionTest(oX, oY, dirX, dirY, dirNormSqr, dirNormBound, Gear->Radius, cinfos[i].cGear);
                                       if(test.hasCollision)
                                       {
                                           ga.ar[ga.Count] = cinfos[i].cGear;
                                           ga.cX[ga.Count] = test.cX;
                                           ga.cY[ga.Count] = test.cY;
                                           ++ga.Count;
                                       }
                                   }
                               }
                           } while(i++ != i__end__);}
    return checkgearslinecollision_result;
};
PGearArray ucollisions_CheckAllGearsLineCollision(PGear SourceGear,hwFloat oX,hwFloat oY,hwFloat tX,hwFloat tY)
{
    PGearArray checkallgearslinecollision_result;
    hwFloat dirX;
    hwFloat dirY;
    hwFloat dirNormSqr;
    hwFloat dirNormBound;
    TLineCollision test;
    PGear Gear;
    checkallgearslinecollision_result = &(ga);
    ga.Count = 0;
    dirX = ufloat_hwFloat_hwFloat_op_sub(tX, oX);
    dirY = ufloat_hwFloat_hwFloat_op_sub(tY, oY);
    dirNormBound = ufloat_hwFloat_hwFloat_op_mul(_1_5, ufloat_hwFloat_hwFloat_op_add(ufloat_hwAbs(dirX), ufloat_hwAbs(dirY)));
    dirNormSqr = ufloat_hwFloat_hwFloat_op_add(ufloat_hwSqr(dirX), ufloat_hwSqr(dirY));
    if(dirNormSqr.isNegative)
    {
        return checkallgearslinecollision_result;
    }
    Gear = GearsList;
    while(Gear != NULL)
    {
        if(SourceGear != Gear)
        {
            test = ucollisions_LineCollisionTest(oX, oY, dirX, dirY, dirNormSqr, dirNormBound, SourceGear->Radius, Gear);
            if(test.hasCollision)
            {
                ga.ar[ga.Count] = Gear;
                ga.cX[ga.Count] = test.cX;
                ga.cY[ga.Count] = test.cY;
                ++ga.Count;
            }
        }
        Gear = Gear->NextGear;
    }
    return checkallgearslinecollision_result;
};
PGearArray ucollisions_CheckCacheCollision(PGear SourceGear)
{
    PGearArray checkcachecollision_result;
    LongInt mx;
    LongInt my;
    LongInt tr;
    LongInt i;
    PGear Gear;
    checkcachecollision_result = &(ga);
    ga.Count = 0;
    mx = ufloat_hwRound(SourceGear->X);
    my = ufloat_hwRound(SourceGear->Y);
    tr = SourceGear->Radius + 2;
    {i = 0;
     LongInt i__end__ = proximitya.Count - 1;
     if (i <= i__end__) do {
                               Gear = proximitya.ar[i];
                               if((fpcrtl_sqr(mx - ufloat_hwRound(Gear->X)) + fpcrtl_sqr(my - ufloat_hwRound(Gear->Y))) <= fpcrtl_sqr(Gear->Radius + tr))
                               {
                                   ga.ar[ga.Count] = Gear;
                                   ga.cX[ga.Count] = mx;
                                   ga.cY[ga.Count] = my;
                                   ++ga.Count;
                               }
                           } while(i++ != i__end__);}
    return checkcachecollision_result;
};
boolean ucollisions_UpdateHitOrderImpl(PGearHitOrder HitOrder,PGear Gear,LongInt Order)
{
    boolean updatehitorderimpl_result;
    LongInt i;
    updatehitorderimpl_result = true;
    {i = 0;
     LongInt i__end__ = HitOrder->Count - 1;
     if (i <= i__end__) do {
                               if(HitOrder->ar[i] == Gear)
                               {
                                   if(Order <= HitOrder->order[i])
                                   {
                                       updatehitorderimpl_result = false;
                                   }
                                   HitOrder->order[i] = uutils_Max(HitOrder->order[i], Order);
                                   return updatehitorderimpl_result;
                               }
                           } while(i++ != i__end__);}
    if(HitOrder->Count > cMaxGearHitOrderInd)
    {
        updatehitorderimpl_result = false;
    }
    else
    {
        HitOrder->ar[HitOrder->Count] = Gear;
        HitOrder->order[HitOrder->Count] = Order;
        ++HitOrder->Count;
    }
    return updatehitorderimpl_result;
};
boolean ucollisions_UpdateHitOrder_2(PGear Gear,LongInt Order)
{
    boolean updatehitorder_result;
    updatehitorder_result = ucollisions_UpdateHitOrderImpl(&(ordera), Gear, Order);
    return updatehitorder_result;
};
boolean ucollisions_UpdateHitOrder_3(PGear Gear,LongInt Order,boolean Global)
{
    boolean updatehitorder_result;
    if(Global)
    {
        updatehitorder_result = ucollisions_UpdateHitOrderImpl(&(globalordera), Gear, Order);
    }
    else
    {
        updatehitorder_result = ucollisions_UpdateHitOrderImpl(&(ordera), Gear, Order);
    }
    return updatehitorder_result;
};
boolean ucollisions_UpdateGlobalHitOrder(PGear Gear,LongInt Order)
{
    boolean updateglobalhitorder_result;
    updateglobalhitorder_result = ucollisions_UpdateHitOrderImpl(&(globalordera), Gear, Order);
    return updateglobalhitorder_result;
};
void ucollisions_ClearHitOrderLeqImpl(PGearHitOrder HitOrder,LongInt MinOrder)
{
    LongInt i;
    LongInt freeIndex;
    ;
    freeIndex = 0;
    i = 0;
    while(i < HitOrder->Count)
    {
        if(HitOrder->order[i] <= MinOrder)
        {
            --HitOrder->Count;
        }
        else
        {
            if(freeIndex < i)
            {
                HitOrder->ar[freeIndex] = HitOrder->ar[i];
                HitOrder->order[freeIndex] = HitOrder->order[i];
            }
            ++freeIndex;
        }
        ++i;
    }
};
void ucollisions_ClearHitOrderLeq(LongInt MinOrder)
{
    ucollisions_ClearHitOrderLeqImpl(&(ordera), MinOrder);
};
void ucollisions_ClearGlobalHitOrderLeq(LongInt MinOrder)
{
    ucollisions_ClearHitOrderLeqImpl(&(globalordera), MinOrder);
};
void ucollisions_ClearHitOrder()
{
    ordera.Count = 0;
};
void ucollisions_RefillProximityCache(PGear SourceGear,LongInt radius)
{
    LongInt cx;
    LongInt cy;
    LongInt dx;
    LongInt dy;
    LongInt r;
    PGear Gear;
    proximitya.Count = 0;
    cx = ufloat_hwRound(SourceGear->X);
    cy = ufloat_hwRound(SourceGear->Y);
    Gear = GearsList;
    while((Gear != NULL) && (proximitya.Count <= cMaxGearProximityCacheInd))
    {
        dx = fpcrtl_abs(ufloat_hwRound(Gear->X) - cx);
        dy = fpcrtl_abs(ufloat_hwRound(Gear->Y) - cy);
        r = (radius + Gear->Radius) + 2;
        if(((Gear != SourceGear) && (uutils_Max(dx, dy) <= r)) && ((fpcrtl_sqr(dx) + fpcrtl_sqr(dy)) <= fpcrtl_sqr(r)))
        {
            proximitya.ar[proximitya.Count] = Gear;
            ++proximitya.Count;
        }
        Gear = Gear->NextGear;
    }
};
void ucollisions_RemoveFromProximityCache(PGear Gear)
{
    LongInt i;
    i = 0;
    while(i < proximitya.Count)
    {
        if(proximitya.ar[i] == Gear)
        {
            proximitya.ar[i] = proximitya.ar[proximitya.Count - 1];
            --proximitya.Count;
        }
        else
        {
            ++i;
        }
    }
};
void ucollisions_ClearProximityCache()
{
    proximitya.Count = 0;
};
Word ucollisions_TestCollisionXImpl(LongInt centerX,LongInt centerY,LongInt radius,LongInt direction,Word collisionMask)
{
    Word testcollisionximpl_result;
    LongInt x;
    LongInt y;
    LongInt minY;
    LongInt maxY;
    if(direction < 0)
    {
        x = centerX - radius;
    }
    else
    {
        x = centerX + radius;
    }
    if((x & LAND_WIDTH_MASK) == 0)
    {
        minY = uutils_Max((centerY - radius) + 1, 0);
        maxY = uutils_Min((centerY + radius) - 1, LAND_HEIGHT - 1);
        {y = minY;
         LongInt y__end__ = maxY;
         if (y <= y__end__) do {
                                   if((ulandutils_LandGet(y, x) & collisionMask) != 0)
                                   {
                                       return ulandutils_LandGet(y, x) & collisionMask;
                                   }
                               } while(y++ != y__end__);}
    }
    testcollisionximpl_result = 0;
    return testcollisionximpl_result;
};
Word ucollisions_TestCollisionYImpl(LongInt centerX,LongInt centerY,LongInt radius,LongInt direction,Word collisionMask)
{
    Word testcollisionyimpl_result;
    LongInt x;
    LongInt y;
    LongInt minX;
    LongInt maxX;
    if(direction < 0)
    {
        y = centerY - radius;
    }
    else
    {
        y = centerY + radius;
    }
    if((y & LAND_HEIGHT_MASK) == 0)
    {
        minX = uutils_Max((centerX - radius) + 1, 0);
        maxX = uutils_Min((centerX + radius) - 1, LAND_WIDTH - 1);
        {x = minX;
         LongInt x__end__ = maxX;
         if (x <= x__end__) do {
                                   if((ulandutils_LandGet(y, x) & collisionMask) != 0)
                                   {
                                       return ulandutils_LandGet(y, x) & collisionMask;
                                   }
                               } while(x++ != x__end__);}
    }
    testcollisionyimpl_result = 0;
    return testcollisionyimpl_result;
};
Word ucollisions_TestCollisionX(PGear Gear,LongInt Dir)
{
    Word testcollisionx_result;
    testcollisionx_result = ucollisions_TestCollisionXImpl(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Radius, Dir, Gear->CollisionMask & lfLandMask);
    return testcollisionx_result;
};
Word ucollisions_TestCollisionY(PGear Gear,LongInt Dir)
{
    Word testcollisiony_result;
    testcollisiony_result = ucollisions_TestCollisionYImpl(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Radius, Dir, Gear->CollisionMask & lfLandMask);
    return testcollisiony_result;
};
void ucollisions_LegacyFixupX(PGear Gear)
{
    if(((((Gear->CollisionMask == lfNotCurHogCrate) && (Gear->Kind != gtHedgehog)) && (Gear->Hedgehog != NULL)) && ((*Gear->Hedgehog).Gear != NULL)) && ((((ufloat_hwRound((*(*Gear->Hedgehog).Gear).X) + (*(*Gear->Hedgehog).Gear).Radius) + 16) < (ufloat_hwRound(Gear->X) - Gear->Radius)) || (((ufloat_hwRound((*(*Gear->Hedgehog).Gear).X) - (*(*Gear->Hedgehog).Gear).Radius) - 16) > (ufloat_hwRound(Gear->X) + Gear->Radius))))
    {
        Gear->CollisionMask = lfAll;
    }
};
void ucollisions_LegacyFixupY(PGear Gear)
{
    if(((((Gear->CollisionMask == lfNotCurHogCrate) && (Gear->Kind != gtHedgehog)) && (Gear->Hedgehog != NULL)) && ((*Gear->Hedgehog).Gear != NULL)) && ((((ufloat_hwRound((*(*Gear->Hedgehog).Gear).Y) + (*(*Gear->Hedgehog).Gear).Radius) + 16) < (ufloat_hwRound(Gear->Y) - Gear->Radius)) || (((ufloat_hwRound((*(*Gear->Hedgehog).Gear).Y) - (*(*Gear->Hedgehog).Gear).Radius) - 16) > (ufloat_hwRound(Gear->Y) + Gear->Radius))))
    {
        Gear->CollisionMask = lfAll;
    }
};
Word ucollisions_TestCollisionXwithGear(PGear Gear,LongInt Dir)
{
    Word testcollisionxwithgear_result;
    ucollisions_LegacyFixupX(Gear);
    testcollisionxwithgear_result = ucollisions_TestCollisionXImpl(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Radius, Dir, Gear->CollisionMask);
    return testcollisionxwithgear_result;
};
Word ucollisions_TestCollisionYwithGear(PGear Gear,LongInt Dir)
{
    Word testcollisionywithgear_result;
    ucollisions_LegacyFixupY(Gear);
    testcollisionywithgear_result = ucollisions_TestCollisionYImpl(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Radius, Dir, Gear->CollisionMask);
    return testcollisionywithgear_result;
};
Word ucollisions_TestCollisionXwithXYShift_5(PGear Gear,hwFloat ShiftX,LongInt ShiftY,LongInt Dir,boolean withGear)
{
    Word testcollisionxwithxyshift_result;
    Word collisionMask;
    if(withGear)
    {
        ucollisions_LegacyFixupX(Gear);
        collisionMask = Gear->CollisionMask;
    }
    else
    {
        collisionMask = Gear->CollisionMask & lfLandMask;
    }
    testcollisionxwithxyshift_result = ucollisions_TestCollisionXImpl(ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(Gear->X, ShiftX)), ufloat_hwRound(Gear->Y) + ShiftY, Gear->Radius, Dir, collisionMask);
    return testcollisionxwithxyshift_result;
};
Word ucollisions_TestCollisionYwithXYShift_5(PGear Gear,LongInt ShiftX,LongInt ShiftY,LongInt Dir,boolean withGear)
{
    Word testcollisionywithxyshift_result;
    Word collisionMask;
    if(withGear)
    {
        ucollisions_LegacyFixupY(Gear);
        collisionMask = Gear->CollisionMask;
    }
    else
    {
        collisionMask = Gear->CollisionMask & lfLandMask;
    }
    testcollisionywithxyshift_result = ucollisions_TestCollisionYImpl(ufloat_hwRound(Gear->X) + ShiftX, ufloat_hwRound(Gear->Y) + ShiftY, Gear->Radius, Dir, collisionMask);
    return testcollisionywithxyshift_result;
};
Word ucollisions_TestCollisionXwithXYShift_4(PGear Gear,hwFloat ShiftX,LongInt ShiftY,LongInt Dir)
{
    Word testcollisionxwithxyshift_result;
    testcollisionxwithxyshift_result = ucollisions_TestCollisionXwithXYShift_5(Gear, ShiftX, ShiftY, Dir, true);
    return testcollisionxwithxyshift_result;
};
Word ucollisions_TestCollisionYwithXYShift_4(PGear Gear,LongInt ShiftX,LongInt ShiftY,LongInt Dir)
{
    Word testcollisionywithxyshift_result;
    testcollisionywithxyshift_result = ucollisions_TestCollisionYwithXYShift_5(Gear, ShiftX, ShiftY, Dir, true);
    return testcollisionywithxyshift_result;
};
TKickTest ucollisions_TestCollisionXKickImpl(LongInt centerX,LongInt centerY,LongInt radius,LongInt direction,Word collisionMask,Word kickMask)
{
    TKickTest testcollisionxkickimpl_result;
    LongInt x;
    LongInt y;
    LongInt minY;
    LongInt maxY;
    testcollisionxkickimpl_result.kick = false;
    testcollisionxkickimpl_result.collisionMask = 0;
    if(direction < 0)
    {
        x = centerX - radius;
    }
    else
    {
        x = centerX + radius;
    }
    if((x & LAND_WIDTH_MASK) == 0)
    {
        minY = uutils_Max((centerY - radius) + 1, 0);
        maxY = uutils_Min((centerY + radius) - 1, LAND_HEIGHT - 1);
        {y = minY;
         LongInt y__end__ = maxY;
         if (y <= y__end__) do {
                                   if((ulandutils_LandGet(y, x) & collisionMask) != 0)
                                   {
                                       testcollisionxkickimpl_result.kick = false;
                                       testcollisionxkickimpl_result.collisionMask = ulandutils_LandGet(y, x) & collisionMask;
                                       return testcollisionxkickimpl_result;
                                   }
                                   else
                                   {
                                       if((ulandutils_LandGet(y, x) & kickMask) != 0)
                                       {
                                           testcollisionxkickimpl_result.kick = true;
                                           testcollisionxkickimpl_result.collisionMask = ulandutils_LandGet(y, x) & kickMask;
                                       }
                                   }
                               } while(y++ != y__end__);}
    }
    return testcollisionxkickimpl_result;
};
TKickTest ucollisions_TestCollisionYKickImpl(LongInt centerX,LongInt centerY,LongInt radius,LongInt direction,Word collisionMask,Word kickMask)
{
    TKickTest testcollisionykickimpl_result;
    LongInt x;
    LongInt y;
    LongInt minX;
    LongInt maxX;
    testcollisionykickimpl_result.kick = false;
    testcollisionykickimpl_result.collisionMask = 0;
    if(direction < 0)
    {
        y = centerY - radius;
    }
    else
    {
        y = centerY + radius;
    }
    if((y & LAND_HEIGHT_MASK) == 0)
    {
        minX = uutils_Max((centerX - radius) + 1, 0);
        maxX = uutils_Min((centerX + radius) - 1, LAND_WIDTH - 1);
        {x = minX;
         LongInt x__end__ = maxX;
         if (x <= x__end__) do {
                                   if((ulandutils_LandGet(y, x) & collisionMask) != 0)
                                   {
                                       testcollisionykickimpl_result.kick = false;
                                       testcollisionykickimpl_result.collisionMask = ulandutils_LandGet(y, x) & collisionMask;
                                       return testcollisionykickimpl_result;
                                   }
                                   else
                                   {
                                       if((ulandutils_LandGet(y, x) & kickMask) != 0)
                                       {
                                           testcollisionykickimpl_result.kick = true;
                                           testcollisionykickimpl_result.collisionMask = ulandutils_LandGet(y, x) & kickMask;
                                       }
                                   }
                               } while(x++ != x__end__);}
    }
    return testcollisionykickimpl_result;
};
Word ucollisions_TestCollisionXKick(PGear Gear,LongInt Dir)
{
    Word testcollisionxkick_result;
    LongInt centerX;
    LongInt centerY;
    LongInt i;
    TKickTest test;
    TCollisionEntry info;
    test = ucollisions_TestCollisionXKickImpl(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Radius, Dir, Gear->CollisionMask & lfLandMask, Gear->CollisionMask);
    testcollisionxkick_result = test.collisionMask;
    if(test.kick)
    {
        if(ufloat_hwFloat_hwFloat_op_lt(ufloat_hwAbs(Gear->dX), cHHKick))
        {
            return testcollisionxkick_result;
        }
        if(((Gear->State & gstHHJumping) != 0) && (ufloat_hwFloat_hwFloat_op_lt(ufloat_hwAbs(Gear->dX), _0_4)))
        {
            return testcollisionxkick_result;
        }
        centerX = ufloat_hwRound(Gear->X);
        centerY = ufloat_hwRound(Gear->Y);
        {i = 0;
         LongInt i__end__ = ((int)(Count) - 1);
         if (i <= i__end__) do {
                                   info = cinfos[i];
                                   if(((((Gear != info.cGear) && ((centerX > info.X) ^ (Dir > 0))) && (((*info.cGear).State & gstNotKickable) == 0)) && (((((*info.cGear).Kind == gtHedgehog) || ((*info.cGear).Kind == gtMine) || ((*info.cGear).Kind == gtKnife) || ((*info.cGear).Kind == gtSentry))) || (((*info.cGear).Kind == gtExplosives) && (((*info.cGear).State & gsttmpFlag) != 0)))) && ((fpcrtl_sqr(centerX - info.X) + fpcrtl_sqr(centerY - info.Y)) <= fpcrtl_sqr((info.Radius + Gear->Radius) + 2)))
                                   {
                                       {
                                           (*info.cGear).dX = Gear->dX;
                                           (*info.cGear).dY = ufloat_hwFloat_hwFloat_op_mul(Gear->dY, _0_5);
                                           (*info.cGear).State = (*info.cGear).State | gstMoving;
                                           if((*info.cGear).Kind == gtKnife)
                                           {
                                               (*info.cGear).State = (*info.cGear).State & ~gstCollision;
                                           }
                                           (*info.cGear).Active = true;
                                       }
                                       ucollisions_DeleteCI(info.cGear);
                                       return 0;
                                   }
                               } while(i++ != i__end__);}
    }
    return testcollisionxkick_result;
};
Word ucollisions_TestCollisionYKick(PGear Gear,LongInt Dir)
{
    Word testcollisionykick_result;
    LongInt centerX;
    LongInt centerY;
    LongInt i;
    TKickTest test;
    TCollisionEntry info;
    test = ucollisions_TestCollisionYKickImpl(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Radius, Dir, Gear->CollisionMask & lfLandMask, Gear->CollisionMask);
    testcollisionykick_result = test.collisionMask;
    if(test.kick)
    {
        if(ufloat_hwFloat_hwFloat_op_lt(ufloat_hwAbs(Gear->dY), cHHKick))
        {
            return testcollisionykick_result;
        }
        if((((Gear->State & gstHHJumping) != 0) && !Gear->dY.isNegative) && (ufloat_hwFloat_hwFloat_op_lt(Gear->dY, _0_4)))
        {
            return testcollisionykick_result;
        }
        centerX = ufloat_hwRound(Gear->X);
        centerY = ufloat_hwRound(Gear->Y);
        {i = 0;
         LongInt i__end__ = ((int)(Count) - 1);
         if (i <= i__end__) do {
                                   info = cinfos[i];
                                   if(((((Gear != info.cGear) && (((centerY + Gear->Radius) > info.Y) ^ (Dir > 0))) && (((*info.cGear).State & gstNotKickable) == 0)) && ((((*info.cGear).Kind == gtHedgehog) || ((*info.cGear).Kind == gtMine) || ((*info.cGear).Kind == gtKnife) || ((*info.cGear).Kind == gtExplosives) || ((*info.cGear).Kind == gtSentry)))) && ((fpcrtl_sqr(centerX - info.X) + fpcrtl_sqr(centerY - info.Y)) <= fpcrtl_sqr((info.Radius + Gear->Radius) + 2)))
                                   {
                                       {
                                           if(((*info.cGear).Kind != gtExplosives) || (((*info.cGear).State & gsttmpFlag) != 0))
                                           {
                                               (*info.cGear).dX = ufloat_hwFloat_hwFloat_op_mul(Gear->dX, _0_5);
                                           }
                                           (*info.cGear).dY = Gear->dY;
                                           (*info.cGear).State = (*info.cGear).State | gstMoving;
                                           if((*info.cGear).Kind == gtKnife)
                                           {
                                               (*info.cGear).State = (*info.cGear).State & ~gstCollision;
                                           }
                                           (*info.cGear).Active = true;
                                       }
                                       ucollisions_DeleteCI(info.cGear);
                                       return 0;
                                   }
                               } while(i++ != i__end__);}
    }
    return testcollisionykick_result;
};
boolean ucollisions_TestRectangleForObstacle(LongInt x1,LongInt y1,LongInt x2,LongInt y2,boolean landOnly)
{
    boolean testrectangleforobstacle_result;
    LongInt x;
    LongInt y;
    LongWord TestWord;
    testrectangleforobstacle_result = true;
    if(landOnly)
    {
        TestWord = 255;
    }
    else
    {
        TestWord = 0;
    }
    if(x1 > x2)
    {
        x = x1;
        x1 = x2;
        x2 = x;
    }
    if(y1 > y2)
    {
        y = y1;
        y1 = y2;
        y2 = y;
    }
    if(hasBorder && (((y1 < 0) || (x1 < 0)) || (x2 > LAND_WIDTH)))
    {
        return testrectangleforobstacle_result;
    }
    {y = y1;
     LongInt y__end__ = y2;
     if (y <= y__end__) do {
                               {x = x1;
                                LongInt x__end__ = x2;
                                if (x <= x__end__) do {
                                                          if((((y & LAND_HEIGHT_MASK) == 0) && ((x & LAND_WIDTH_MASK) == 0)) && (ulandutils_LandGet(y, x) > TestWord))
                                                          {
                                                              return testrectangleforobstacle_result;
                                                          }
                                                      } while(x++ != x__end__);}
                           } while(y++ != y__end__);}
    testrectangleforobstacle_result = false;
    return testrectangleforobstacle_result;
};
boolean ucollisions_CalcSlopeTangent(PGear Gear,LongInt collisionX,LongInt collisionY,LongInt (*outDeltaX),LongInt (*outDeltaY),LongWord TestWord)
{
    boolean calcslopetangent_result;
    LongInt ldx;
    LongInt ldy;
    LongInt rdx;
    LongInt rdy;
    ShortInt i;
    ShortInt j;
    ShortInt k;
    ShortInt mx;
    ShortInt my;
    ShortInt li;
    ShortInt ri;
    ShortInt jfr;
    ShortInt jto;
    ShortInt tmpo;
    LongWord tmpx;
    LongWord tmpy;
    hwFloat dx;
    hwFloat dy;
    hwFloat s;
    typedef ShortInt offset_tt[(7 + 1)][(1 + 1)];
    offset_tt offset;
    boolean isColl;
    calcslopetangent_result = false;
    dx = Gear->dX;
    dy = Gear->dY;
    if((dx.QWordValue > _0_995.QWordValue) || (dy.QWordValue > _0_995.QWordValue))
    {
        s = ufloat_hwFloat_hwFloat_op_div(_0_995, ufloat_Distance(dx, dy));
        dx = ufloat_hwFloat_hwFloat_op_mul(s, dx);
        dy = ufloat_hwFloat_hwFloat_op_mul(s, dy);
    }
    mx = ufloat_hwRound(ufloat_hwFloat_hwFloat_op_sub(Gear->X, dx)) - ufloat_hwRound(Gear->X);
    my = ufloat_hwRound(ufloat_hwFloat_hwFloat_op_sub(Gear->Y, dy)) - ufloat_hwRound(Gear->Y);
    li = -1;
    ri = -1;
    {i = 0;
     ShortInt i__end__ = 7;
     if (i <= i__end__) do {
                               offset[i][0] = mx;
                               offset[i][1] = my;
                               {k = 4;
                                ShortInt k__end__ = 1;
                                if (k >= k__end__) do {
                                                          tmpx = collisionX + (k * mx);
                                                          tmpy = collisionY + (k * my);
                                                          if(((tmpy & LAND_HEIGHT_MASK) == 0) && ((tmpx & LAND_WIDTH_MASK) == 0))
                                                          {
                                                              if(ulandutils_LandGet(tmpy, tmpx) > TestWord)
                                                              {
                                                                  if(i != 0)
                                                                  {
                                                                      if(ri == -1)
                                                                      {
                                                                          ri = i;
                                                                      }
                                                                      else
                                                                      {
                                                                          li = i;
                                                                      }
                                                                  }
                                                              }
                                                          }
                                                      } while(k-- != k__end__);}
                               if(i == 7)
                               {
                                   break;
                               }
                               if((mx == -1) && (my != -1))
                               {
                                   my = my - 1;
                               }
                               else
                               {
                                   if((my == -1) && (mx != 1))
                                   {
                                       mx = mx + 1;
                                   }
                                   else
                                   {
                                       if((mx == 1) && (my != 1))
                                       {
                                           my = my + 1;
                                       }
                                       else
                                       {
                                           mx = mx - 1;
                                       }
                                   }
                               }
                           } while(i++ != i__end__);}
    ldx = collisionX;
    ldy = collisionY;
    rdx = collisionX;
    rdy = collisionY;
    {i = 0;
     ShortInt i__end__ = 8;
     if (i <= i__end__) do {
                               jfr = (8 + li) + 1;
                               jto = (8 + li) - 1;
                               isColl = false;
                               {j = jfr;
                                ShortInt j__end__ = jto;
                                if (j >= j__end__) do {
                                                          tmpo = j % 8;
                                                          {k = 3;
                                                           ShortInt k__end__ = 1;
                                                           if (k >= k__end__) do {
                                                                                     tmpx = ldx + (k * offset[tmpo][0]);
                                                                                     tmpy = ldy + (k * offset[tmpo][1]);
                                                                                     if((((tmpy & LAND_HEIGHT_MASK) == 0) && ((tmpx & LAND_WIDTH_MASK) == 0)) && (ulandutils_LandGet(tmpy, tmpx) > TestWord))
                                                                                     {
                                                                                         ldx = tmpx;
                                                                                         ldy = tmpy;
                                                                                         isColl = true;
                                                                                         break;
                                                                                     }
                                                                                 } while(k-- != k__end__);}
                                                          if(isColl)
                                                          {
                                                              break;
                                                          }
                                                      } while(j-- != j__end__);}
                               jfr = (8 + ri) - 1;
                               jto = (8 + ri) + 1;
                               isColl = false;
                               {j = jfr;
                                ShortInt j__end__ = jto;
                                if (j <= j__end__) do {
                                                          tmpo = j % 8;
                                                          {k = 3;
                                                           ShortInt k__end__ = 1;
                                                           if (k >= k__end__) do {
                                                                                     tmpx = rdx + (k * offset[tmpo][0]);
                                                                                     tmpy = rdy + (k * offset[tmpo][1]);
                                                                                     if((((tmpy & LAND_HEIGHT_MASK) == 0) && ((tmpx & LAND_WIDTH_MASK) == 0)) && (ulandutils_LandGet(tmpy, tmpx) > TestWord))
                                                                                     {
                                                                                         rdx = tmpx;
                                                                                         rdy = tmpy;
                                                                                         isColl = true;
                                                                                         break;
                                                                                     }
                                                                                 } while(k-- != k__end__);}
                                                          if(isColl)
                                                          {
                                                              break;
                                                          }
                                                      } while(j++ != j__end__);}
                           } while(i++ != i__end__);}
    ldx = rdx - ldx;
    ldy = rdy - ldy;
    if((ldx == 0) && (ldy == 0))
    {
        return calcslopetangent_result;
    }
    (*outDeltaX) = ldx;
    (*outDeltaY) = ldy;
    calcslopetangent_result = true;
    return calcslopetangent_result;
};
hwFloat ucollisions_CalcSlopeNearGear(PGear Gear,LongInt dirX,LongInt dirY)
{
    hwFloat calcslopeneargear_result;
    hwFloat dx;
    hwFloat dy;
    LongInt collX;
    LongInt collY;
    LongInt i;
    LongInt y;
    LongInt x;
    LongInt gx;
    LongInt gy;
    LongInt sdx;
    LongInt sdy;
    boolean isColl;
    boolean bSucc;
    if(dirY != 0)
    {
        y = ufloat_hwRound(Gear->Y) + (Gear->Radius * dirY);
        gx = ufloat_hwRound(Gear->X);
        collX = gx;
        isColl = false;
        if((y & LAND_HEIGHT_MASK) == 0)
        {
            x = (ufloat_hwRound(Gear->X) - Gear->Radius) + 1;
            i = (x + (Gear->Radius * 2)) - 2;
            do {
                   if((x & LAND_WIDTH_MASK) == 0)
                   {
                       if(ulandutils_LandGet(y, x) != 0)
                       {
                           if(!isColl || (fpcrtl_abs(x - gx) < fpcrtl_abs(collX - gx)))
                           {
                               isColl = true;
                               collX = x;
                           }
                       }
                   }
                   ++x;
               } while(!(x > i));
        }
    }
    else
    {
        x = ufloat_hwRound(Gear->X) + (Gear->Radius * dirX);
        gy = ufloat_hwRound(Gear->Y);
        collY = gy;
        isColl = false;
        if((x & LAND_WIDTH_MASK) == 0)
        {
            y = (ufloat_hwRound(Gear->Y) - Gear->Radius) + 1;
            i = (y + (Gear->Radius * 2)) - 2;
            do {
                   if((y & LAND_HEIGHT_MASK) == 0)
                   {
                       if(ulandutils_LandGet(y, x) != 0)
                       {
                           if(!isColl || (fpcrtl_abs(y - gy) < fpcrtl_abs(collY - gy)))
                           {
                               isColl = true;
                               collY = y;
                           }
                       }
                   }
                   ++y;
               } while(!(y > i));
        }
    }
    if(isColl)
    {
        dx = Gear->dX;
        dy = Gear->dY;
        if(dirY != 0)
        {
            Gear->dX.QWordValue = 0;
            Gear->dX.isNegative = collX >= gx;
            Gear->dY = ufloat_hwFloat_LongInt_op_mul(_1, dirY);
        }
        else
        {
            Gear->dY.QWordValue = 0;
            Gear->dY.isNegative = collY >= gy;
            Gear->dX = ufloat_hwFloat_LongInt_op_mul(_1, dirX);
        }
        sdx = 0;
        sdy = 0;
        if(dirY != 0)
        {
            bSucc = ucollisions_CalcSlopeTangent(Gear, collX, y, &(sdx), &(sdy), 0);
        }
        else
        {
            bSucc = ucollisions_CalcSlopeTangent(Gear, x, collY, &(sdx), &(sdy), 0);
        }
        Gear->dX = dx;
        Gear->dY = dy;
        if(bSucc && ((sdx != 0) || (sdy != 0)))
        {
            dx = ufloat_hwFloat_LongInt_op_div(ufloat_int2hwFloat(sdy), fpcrtl_abs(sdx) + fpcrtl_abs(sdy));
            dx.isNegative = (sdx * sdy) < 0;
            return dx;
        }
    }
    calcslopeneargear_result = _0;
    return calcslopeneargear_result;
};
hwFloat ucollisions_CalcSlopeBelowGear(PGear Gear)
{
    hwFloat calcslopebelowgear_result;
    hwFloat dx;
    hwFloat dy;
    LongInt collX;
    LongInt i;
    LongInt y;
    LongInt x;
    LongInt gx;
    LongInt sdx;
    LongInt sdy;
    boolean isColl;
    boolean bSucc;
    y = ufloat_hwRound(Gear->Y) + Gear->Radius;
    gx = ufloat_hwRound(Gear->X);
    collX = gx;
    isColl = false;
    if((y & LAND_HEIGHT_MASK) == 0)
    {
        x = (ufloat_hwRound(Gear->X) - Gear->Radius) + 1;
        i = (x + (Gear->Radius * 2)) - 2;
        do {
               if((x & LAND_WIDTH_MASK) == 0)
               {
                   if((ulandutils_LandGet(y, x) & lfLandMask) != 0)
                   {
                       if(!isColl || (fpcrtl_abs(x - gx) < fpcrtl_abs(collX - gx)))
                       {
                           isColl = true;
                           collX = x;
                       }
                   }
               }
               ++x;
           } while(!(x > i));
    }
    if(isColl)
    {
        dx = Gear->dX;
        dy = Gear->dY;
        Gear->dX.QWordValue = 0;
        Gear->dX.isNegative = collX >= gx;
        Gear->dY = _1;
        sdx = 0;
        sdy = 0;
        bSucc = ucollisions_CalcSlopeTangent(Gear, collX, y, &(sdx), &(sdy), 255);
        Gear->dX = dx;
        Gear->dY = dy;
        if((bSucc && (sdx != 0)) && (sdy != 0))
        {
            dx = ufloat_hwFloat_LongInt_op_div(ufloat_int2hwFloat(sdy), fpcrtl_abs(sdx) + fpcrtl_abs(sdy));
            dx.isNegative = (sdx * sdy) < 0;
            return dx;
        }
    }
    calcslopebelowgear_result = _0;
    return calcslopebelowgear_result;
};
boolean ucollisions_CheckGearsUnderSprite(TSprite Sprite,LongInt sprX,LongInt sprY,LongInt Frame)
{
    boolean checkgearsundersprite_result;
    LongInt x;
    LongInt y;
    LongInt bpp;
    LongInt h;
    LongInt w;
    LongInt row;
    LongInt col;
    LongInt gx;
    LongInt gy;
    LongInt r;
    LongInt numFramesFirstCol;
    PByteArray p;
    PSDL_Surface Image;
    PGear Gear;
    checkgearsundersprite_result = false;
    if(udebug_checkFails(SpritesData[Sprite].Surface != NULL, __str0, true))
    {
        return checkgearsundersprite_result;
    }
    numFramesFirstCol = SpritesData[Sprite].imageHeight / SpritesData[Sprite].Height;
    Image = SpritesData[Sprite].Surface;
    if(sdlh_SDL_MustLock(Image))
    {
        if(udebug_SDLCheck(SDL_LockSurface(Image) >= 0, __str1, true))
        {
            return checkgearsundersprite_result;
        }
    }
    bpp = (*Image->format).BytesPerPixel;
    if(udebug_checkFails(bpp == 4, __str2, true))
    {
        if(sdlh_SDL_MustLock(Image))
        {
            SDL_UnlockSurface(Image);
        }
        return checkgearsundersprite_result;
    }
    w = SpritesData[Sprite].Width;
    h = SpritesData[Sprite].Height;
    row = Frame % numFramesFirstCol;
    col = Frame / numFramesFirstCol;
    p = ((PByteArray)&((*((PByteArray)Image->pixels))[((Image->pitch * row) * h) + ((col * w) * 4)]));
    Gear = GearsList;
    while(Gear != NULL)
    {
        if((Gear->Kind == gtAirMine) || ((((Gear->Kind == gtCase) || (Gear->Kind == gtExplosives) || (Gear->Kind == gtTarget) || (Gear->Kind == gtKnife) || (Gear->Kind == gtMine) || (Gear->Kind == gtHedgehog) || (Gear->Kind == gtSMine))) && (Gear->CollisionIndex == -1)))
        {
            gx = ufloat_hwRound(Gear->X);
            gy = ufloat_hwRound(Gear->Y);
            r = Gear->Radius + 1;
            if(((((gx + r) >= sprX) && ((gx - r) < (sprX + w))) && ((gy + r) >= sprY)) && ((gy - r) < (sprY + h)))
            {
                {y = gy - r;
                 LongInt y__end__ = gy + r;
                 if (y <= y__end__) do {
                                           {x = gx - r;
                                            LongInt x__end__ = gx + r;
                                            if (x <= x__end__) do {
                                                                      if((((((x >= sprX) && (x < (sprX + w))) && (y >= sprY)) && (y < (sprY + h))) && ((fpcrtl_sqr(x - gx) + fpcrtl_sqr(y - gy)) <= fpcrtl_sqr(r))) && (((*((PLongWord)&((*p)[(Image->pitch * (y - sprY)) + ((x - sprX) * 4)]))) & AMask) != 0))
                                                                      {
                                                                          checkgearsundersprite_result = true;
                                                                          if(sdlh_SDL_MustLock(Image))
                                                                          {
                                                                              SDL_UnlockSurface(Image);
                                                                          }
                                                                          return checkgearsundersprite_result;
                                                                      }
                                                                  } while(x++ != x__end__);}
                                       } while(y++ != y__end__);}
            }
        }
        Gear = Gear->NextGear;
    }
    return checkgearsundersprite_result;
};
void ucollisions_initModule()
{
    Count = 0;
};
void ucollisions_freeModule()
{
};
