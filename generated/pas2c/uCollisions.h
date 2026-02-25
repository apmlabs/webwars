#pragma once

#include "pas2c.h"

#include "uFloat.h"
#include "uTypes.h"
#include "uUtils.h"
enum{cMaxGearArrayInd = 1023};
enum{cMaxGearHitOrderInd = 1023};
enum{cMaxGearProximityCacheInd = 1023};
typedef struct __TGearArray * PGearArray;
typedef struct __TGearArray {
            PGear ar[(cMaxGearArrayInd + 1)];
            LongInt cX[(cMaxGearArrayInd + 1)];
            LongInt cY[(cMaxGearArrayInd + 1)];
            LongWord Count;
        } TGearArray;
typedef struct __TGearHitOrder * PGearHitOrder;
typedef struct __TGearHitOrder {
            PGear ar[(cMaxGearHitOrderInd + 1)];
            LongInt order[(cMaxGearHitOrderInd + 1)];
            LongWord Count;
        } TGearHitOrder;
typedef struct __TGearProximityCache * PGearProximityCache;
typedef struct __TGearProximityCache {
            PGear ar[(cMaxGearProximityCacheInd + 1)];
            LongWord Count;
        } TGearProximityCache;
typedef struct __TLineCollision {
            boolean hasCollision;
            LongInt cX;
            LongInt cY;
        } TLineCollision;
typedef struct __TKickTest {
            boolean kick;
            Word collisionMask;
        } TKickTest;
void ucollisions_initModule();
void ucollisions_freeModule();
void ucollisions_AddCI(PGear Gear);
void ucollisions_DeleteCI(PGear Gear);
PGearArray ucollisions_CheckGearsCollision(PGear Gear);
PGearArray ucollisions_CheckAllGearsCollision(PGear SourceGear);
PGearArray ucollisions_CheckCacheCollision(PGear SourceGear);
PGearArray ucollisions_CheckGearsLineCollision(PGear Gear,hwFloat oX,hwFloat oY,hwFloat tX,hwFloat tY);
PGearArray ucollisions_CheckAllGearsLineCollision(PGear SourceGear,hwFloat oX,hwFloat oY,hwFloat tX,hwFloat tY);
boolean ucollisions_UpdateHitOrder_2(PGear Gear,LongInt Order);
boolean ucollisions_UpdateHitOrder_3(PGear Gear,LongInt Order,boolean Global);
boolean ucollisions_UpdateGlobalHitOrder(PGear Gear,LongInt Order);
void ucollisions_ClearHitOrderLeq(LongInt MinOrder);
void ucollisions_ClearGlobalHitOrderLeq(LongInt MinOrder);
void ucollisions_ClearHitOrder();
void ucollisions_RefillProximityCache(PGear SourceGear,LongInt radius);
void ucollisions_RemoveFromProximityCache(PGear Gear);
void ucollisions_ClearProximityCache();
Word ucollisions_TestCollisionXImpl(LongInt centerX,LongInt centerY,LongInt radius,LongInt direction,Word collisionMask);
Word ucollisions_TestCollisionYImpl(LongInt centerX,LongInt centerY,LongInt radius,LongInt direction,Word collisionMask);
Word ucollisions_TestCollisionXwithGear(PGear Gear,LongInt Dir);
Word ucollisions_TestCollisionYwithGear(PGear Gear,LongInt Dir);
Word ucollisions_TestCollisionX(PGear Gear,LongInt Dir);
Word ucollisions_TestCollisionY(PGear Gear,LongInt Dir);
Word ucollisions_TestCollisionXwithXYShift_4(PGear Gear,hwFloat ShiftX,LongInt ShiftY,LongInt Dir);
Word ucollisions_TestCollisionXwithXYShift_5(PGear Gear,hwFloat ShiftX,LongInt ShiftY,LongInt Dir,boolean withGear);
Word ucollisions_TestCollisionYwithXYShift_4(PGear Gear,LongInt ShiftX,LongInt ShiftY,LongInt Dir);
Word ucollisions_TestCollisionYwithXYShift_5(PGear Gear,LongInt ShiftX,LongInt ShiftY,LongInt Dir,boolean withGear);
TKickTest ucollisions_TestCollisionXKickImpl(LongInt centerX,LongInt centerY,LongInt radius,LongInt direction,Word collisionMask,Word kickMask);
TKickTest ucollisions_TestCollisionYKickImpl(LongInt centerX,LongInt centerY,LongInt radius,LongInt direction,Word collisionMask,Word kickMask);
Word ucollisions_TestCollisionXKick(PGear Gear,LongInt Dir);
Word ucollisions_TestCollisionYKick(PGear Gear,LongInt Dir);
boolean ucollisions_TestRectangleForObstacle(LongInt x1,LongInt y1,LongInt x2,LongInt y2,boolean landOnly);
boolean ucollisions_CheckCoordInWater(LongInt X,LongInt Y);
hwFloat ucollisions_CalcSlopeBelowGear(PGear Gear);
hwFloat ucollisions_CalcSlopeNearGear(PGear Gear,LongInt dirX,LongInt dirY);
boolean ucollisions_CalcSlopeTangent(PGear Gear,LongInt collisionX,LongInt collisionY,LongInt (*outDeltaX),LongInt (*outDeltaY),LongWord TestWord);
boolean ucollisions_CheckGearsUnderSprite(TSprite Sprite,LongInt sprX,LongInt sprY,LongInt Frame);

