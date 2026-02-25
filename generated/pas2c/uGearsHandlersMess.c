#include "fpcrtl.h"

#include "uGearsHandlersMess.h"
LongWord upd;
LongInt snowLeft;
LongInt snowRight;
#include "uConsts.h"
#include "uVariables.h"
#include "uVisualGearsList.h"
#include "uRandom.h"
#include "uCollisions.h"
#include "uGearsList.h"
#include "uUtils.h"
#include "uSound.h"
#include "SDLh.h"
#include "uScript.h"
#include "uGearsHedgehog.h"
#include "uGearsUtils.h"
#include "uIO.h"
#include "uCaptions.h"
#include "uLandGraphics.h"
#include "uGearsHandlers.h"
#include "uTextures.h"
#include "uRenderUtils.h"
#include "uAmmos.h"
#include "uTeams.h"
#include "uLandTexture.h"
#include "uStore.h"
#include "uAI.h"
#include "uStats.h"
#include "uLocale.h"
#include "uLandUtils.h"
static const string255 __str7 = STRINIT("Reserved/Zombie");
static const string255 __str6 = STRINIT("NoHat");
static const string255 __str5 = STRINIT("onHogSwitch");
static const string255 __str4 = STRINIT("onGearDamage");
static const string255 __str3 = STRINIT("q");
static const string255 __str2 = STRINIT("m");
static const string255 __str1 = STRINIT("N");
static const string255 __str0 = STRINIT("onHogHide");
void ugearshandlersmess_doStepPerPixel(PGear Gear,utypes_TGearStepProcedure ugearshandlersmess_step,boolean onlyCheckIfChanged)
{
    hwFloat dX;
    hwFloat dY;
    hwFloat sX;
    hwFloat sY;
    LongWord i;
    LongWord steps;
    utypes_TGearStepProcedure ugearshandlersmess_caller;
    dX = Gear->dX;
    dY = Gear->dY;
    steps = uutils_Max(fpcrtl_abs(ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(Gear->X, dX)) - ufloat_hwRound(Gear->X)), fpcrtl_abs(ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(Gear->Y, dY)) - ufloat_hwRound(Gear->Y)));
    if(steps < 1)
    {
        if(onlyCheckIfChanged)
        {
            Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, dX);
            Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, dY);
            return;
        }
        else
        {
            steps = 1;
        }
    }
    if(steps > 1)
    {
        sX = ufloat_hwFloat_LongInt_op_div(dX, steps);
        sY = ufloat_hwFloat_LongInt_op_div(dY, steps);
    }
    else
    {
        sX = dX;
        sY = dY;
    }
    ugearshandlersmess_caller = Gear->doStep;
    {i = 1;
     LongWord i__end__ = steps;
     if (i <= i__end__) do {
                               Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, sX);
                               Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, sY);
                               ugearshandlersmess_step(Gear);
                               if((((Gear->doStep) != (ugearshandlersmess_caller)) | ((Gear->State & gstCollision) != 0)) || ((Gear->State & gstMoving) == 0))
                               {
                                   break;
                               }
                           } while(i++ != i__end__);}
};
void ugearshandlersmess_makeHogsWorry(hwFloat x,hwFloat y,LongInt r,TGearType gearType)
{
    PGear gi;
    LongInt d;
    boolean grenadeTaunt;
    gi = GearsList;
    while(gi != NULL)
    {
        if(gi->Kind == gtHedgehog)
        {
            d = r - ufloat_hwRound(ufloat_Distance(ufloat_hwFloat_hwFloat_op_sub(gi->X, x), ufloat_hwFloat_hwFloat_op_sub(gi->Y, y)));
            if(((d > 1) && ((*gi->Hedgehog).Effects[heInvulnerable] == 0)) && (urandom_GetRandom(2) == 0))
            {
                if(CurrentHedgehog->Gear == gi)
                {
                    if((*CurrentHedgehog->Gear).FlightTime == 0)
                    {
                        switch(fpcrtl_random(4))
                        {case 0:usound_PlaySoundV_2(sndWhatThe, (*(*gi->Hedgehog).Team).voicepack);
                                break;
                         case 1:usound_PlaySoundV_2(sndOops, (*(*gi->Hedgehog).Team).voicepack);
                                break;
                         case 2:usound_PlaySoundV_2(sndRunAway, (*(*gi->Hedgehog).Team).voicepack);
                                break;
                         case 3:usound_PlaySoundV_2(sndRunAway, (*(*gi->Hedgehog).Team).voicepack);
                                break;
                         default: break;}
                    }
                    else
                    {
                        if(fpcrtl_random(4) == 0)
                        {
                            usound_PlaySoundV_2(sndWhatThe, (*(*gi->Hedgehog).Team).voicepack);
                        }
                        else
                        {
                            usound_PlaySoundV_2(sndOops, (*(*gi->Hedgehog).Team).voicepack);
                        }
                    }
                }
                else
                {
                    if(((gi->State & gstMoving) == 0) && ((*gi->Hedgehog).Effects[heFrozen] == 0))
                    {
                        gi->dX.isNegative = ufloat_hwFloat_hwFloat_op_lt(x, gi->X);
                        gi->State = gi->State | gstLoser;
                    }
                    grenadeTaunt = false;
                    if(gearType == gtGrenade)
                    {
                        grenadeTaunt = fpcrtl_random(2) == 0;
                    }
                    if(grenadeTaunt)
                    {
                        usound_PlaySoundV_2(sndGrenade, (*(*gi->Hedgehog).Team).voicepack);
                    }
                    else
                    {
                        if(d > (r / 2))
                        {
                            if(fpcrtl_random(3) == 0)
                            {
                                usound_PlaySoundV_2(sndWhatThe, (*(*gi->Hedgehog).Team).voicepack);
                            }
                            else
                            {
                                usound_PlaySoundV_2(sndNooo, (*(*gi->Hedgehog).Team).voicepack);
                            }
                        }
                        else
                        {
                            usound_PlaySoundV_2(sndUhOh, (*(*gi->Hedgehog).Team).voicepack);
                        }
                    }
                }
            }
        }
        gi = gi->NextGear;
    }
};
void ugearshandlersmess_HideHog(PHedgehog HH)
{
    if(HH->Gear == NULL)
    {
        return;
    }
    uscript_ScriptCall_2(__str0, (*HH->Gear).uid);
    ucollisions_DeleteCI(HH->Gear);
    if(FollowGear == HH->Gear)
    {
        FollowGear = NULL;
    }
    if(lastGearByUID == HH->Gear)
    {
        lastGearByUID = NULL;
    }
    (*HH->Gear).Message = (*HH->Gear).Message | gmRemoveFromList;
    {
        (*HH->Gear).Z = cHHZ;
        (*HH->Gear).Active = false;
        (*HH->Gear).State = (*HH->Gear).State & ~((gstHHDriven | gstAttacking) | gstAttacked);
        (*HH->Gear).Message = (*HH->Gear).Message & ~gmAttack;
    }
    HH->GearHidden = HH->Gear;
    HH->Gear = NULL;
    uvisualgearslist_AddVisualGear_3(0, 0, vgtTeamHealthSorter);
};
void ugearshandlersmess_doStepDrowningGear(PGear Gear)
{
    LongInt i;
    LongInt d;
    LongInt bubbleX;
    LongInt bubbleY;
    PVisualGear bubble;
    if(Gear->Timer == 0)
    {
        d = 2 * Gear->Radius;
        {i = (Gear->Radius * Gear->Radius) / 4;
         LongInt i__end__ = 0;
         if (i >= i__end__) do {
                                   bubble = uvisualgearslist_AddVisualGear_3((ufloat_hwRound(Gear->X) - Gear->Radius) + fpcrtl_random(d), (ufloat_hwRound(Gear->Y) - Gear->Radius) + fpcrtl_random(d), vgtBubble);
                                   if(bubble != NULL)
                                   {
                                       bubble->dY = 0.1 + (fpcrtl_random(20) /(float) 10);
                                   }
                               } while(i-- != i__end__);}
        ugearslist_DeleteGear(Gear);
        return;
    }
    AllInactive = false;
    --Gear->Timer;
    Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, cDrownSpeed);
    if(cWaterLine > (ufloat_hwRound(Gear->Y) + Gear->Radius))
    {
        if((leftX + Gear->Radius) > ufloat_hwRound(Gear->X))
        {
            Gear->X = ufloat_hwFloat_hwFloat_op_sub(Gear->X, cDrownSpeed);
        }
        else
        {
            Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, cDrownSpeed);
        }
    }
    else
    {
        Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, ufloat_hwFloat_hwFloat_op_mul(Gear->dX, cDrownSpeed));
    }
    if((Gear->Kind == gtHedgehog) && Gear->dX.isNegative)
    {
        bubbleX = ufloat_hwRound(Gear->X) - Gear->Radius;
    }
    else
    {
        bubbleX = ufloat_hwRound(Gear->X) + Gear->Radius;
    }
    bubbleY = ufloat_hwRound(Gear->Y) - Gear->Radius;
    if(((!SuddenDeathDmg && (WaterOpacity < 0xff)) || (SuddenDeathDmg && (SDWaterOpacity < 0xff))) && ((GameTicks & 0x1f) == 0))
    {
        if((Gear->Kind == gtHedgehog) && (fpcrtl_random(4) == 0))
        {
            uvisualgearslist_AddVisualGear_3(bubbleX, bubbleY, vgtBubble);
        }
        else
        {
            if(fpcrtl_random(12) == 0)
            {
                uvisualgearslist_AddVisualGear_3(bubbleX, bubbleY, vgtBubble);
            }
        }
    }
    if((!SuddenDeathDmg && (WaterOpacity > 0xfe)) || (SuddenDeathDmg && (SDWaterOpacity > 0xfe)))
    {
        if((WorldEdge == weSea) && ((ufloat_hwRound(Gear->X) - Gear->Radius) < leftX))
        {
            if((ufloat_hwRound(Gear->X) - Gear->Radius) > (leftX - 90))
            {
                Gear->X = ufloat_hwFloat_hwFloat_op_sub(Gear->X, _90);
            }
        }
        else
        {
            if((WorldEdge == weSea) && ((ufloat_hwRound(Gear->X) + Gear->Radius) > rightX))
            {
                if((ufloat_hwRound(Gear->X) - Gear->Radius) < (rightX + 90))
                {
                    Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, _90);
                }
            }
            else
            {
                Gear->Y = ufloat_int2hwFloat((Gear->Radius + cWaterLine) + cVisibleWater);
            }
        }
        ugearslist_DeleteGear(Gear);
        return;
    }
    if(Gear->Kind == gtPiano)
    {
        d = SpritesData[sprPiano].Height;
    }
    else
    {
        if(Gear->Kind == gtRCPlane)
        {
            d = SpritesData[sprPlane].Width;
        }
        else
        {
            if(Gear->Kind == gtKnife)
            {
                d = SpritesData[sprKnife].Height;
            }
            else
            {
                if(Gear->Kind == gtDynamite)
                {
                    d = SpritesData[sprDynamite].Height;
                }
                else
                {
                    if(Gear->Kind == gtSnowball)
                    {
                        d = SpritesData[sprSnowball].Height;
                    }
                    else
                    {
                        d = Gear->Radius * 2;
                    }
                }
            }
        }
    }
    if(ufloat_hwRound(Gear->Y) > ((d + cWaterLine) + cVisibleWater))
    {
        ugearslist_DeleteGear(Gear);
    }
};
void ugearshandlersmess_doStepFallingGear(PGear Gear)
{
    boolean isFalling;
    hwFloat tX;
    hwFloat tdX;
    hwFloat tdY;
    LongInt collV;
    LongInt collH;
    LongInt gX;
    LongInt gY;
    Word land;
    Word xland;
    tX = Gear->X;
    gX = ufloat_hwRound(Gear->X);
    gY = ufloat_hwRound(Gear->Y);
    Gear->State = Gear->State & ~gstCollision;
    if((((Gear->Kind != gtGenericFaller) && ugearsutils_WorldWrap(&(Gear))) && (WorldEdge == weWrap)) && ((ucollisions_TestCollisionXwithGear(Gear, 1) != 0) || (ucollisions_TestCollisionXwithGear(Gear, -1) != 0)))
    {
        if(!Gear->Sticky)
        {
            Gear->X = tX;
            Gear->dX.isNegative = gX > (leftX + (Gear->Radius * 2));
            Gear->dX = ufloat_hwFloat_hwFloat_op_mul(Gear->dX, Gear->Friction);
        }
        Gear->State = Gear->State | gstCollision;
    }
    if(Gear->dX.QWordValue > 8160437862)
    {
        Gear->dX.QWordValue = 8160437862;
    }
    if(Gear->dY.QWordValue > 8160437862)
    {
        Gear->dY.QWordValue = 8160437862;
    }
    if(((Gear->State & gstSubmersible) != 0) && ucollisions_CheckCoordInWater(gX, gY))
    {
        Gear->dX = ufloat_hwFloat_hwFloat_op_mul(Gear->dX, _0_999);
        Gear->dY = ufloat_hwFloat_hwFloat_op_mul(Gear->dY, _0_999);
    }
    collV = 0;
    collH = 0;
    tdX = Gear->dX;
    tdY = Gear->dY;
    if((gX < uutils_Min(LAND_WIDTH / -2, -2048)) || (gX > uutils_Max((LAND_WIDTH * 3) / 2, 6144)))
    {
        Gear->Message = Gear->Message | gmDestroy;
    }
    if(Gear->dY.isNegative)
    {
        land = ucollisions_TestCollisionYwithGear(Gear, -1);
        isFalling = land == 0;
        if(land != 0)
        {
            collV = -1;
            if((land & lfIce) != 0)
            {
                Gear->dX = ufloat_hwFloat_hwFloat_op_mul(Gear->dX, ufloat_hwFloat_hwFloat_op_add(_0_9, ufloat_hwFloat_hwFloat_op_mul(Gear->Friction, _0_1)));
            }
            else
            {
                Gear->dX = ufloat_hwFloat_hwFloat_op_mul(Gear->dX, Gear->Friction);
            }
            if((Gear->AdvBounce == 0) || ((land & lfBouncy) == 0))
            {
                Gear->dY = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_op_sub(Gear->dY), Gear->Elasticity);
                Gear->State = Gear->State | gstCollision;
            }
            else
            {
                Gear->dY = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_op_sub(Gear->dY), cElastic);
            }
        }
        else
        {
            if(Gear->AdvBounce == 1)
            {
                land = ucollisions_TestCollisionYwithGear(Gear, 1);
                if(land != 0)
                {
                    collV = 1;
                }
            }
        }
    }
    else
    {
        land = ucollisions_TestCollisionYwithGear(Gear, 1);
        if(land != 0)
        {
            collV = 1;
            isFalling = false;
            if((land & lfIce) != 0)
            {
                Gear->dX = ufloat_hwFloat_hwFloat_op_mul(Gear->dX, ufloat_hwFloat_hwFloat_op_add(_0_9, ufloat_hwFloat_hwFloat_op_mul(Gear->Friction, _0_1)));
            }
            else
            {
                Gear->dX = ufloat_hwFloat_hwFloat_op_mul(Gear->dX, Gear->Friction);
            }
            if((Gear->AdvBounce == 0) || ((land & lfBouncy) == 0))
            {
                Gear->dY = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_op_sub(Gear->dY), Gear->Elasticity);
                Gear->State = Gear->State | gstCollision;
            }
            else
            {
                Gear->dY = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_op_sub(Gear->dY), cElastic);
            }
        }
        else
        {
            isFalling = true;
            if(Gear->AdvBounce == 1)
            {
                land = ucollisions_TestCollisionYwithGear(Gear, -1);
                if(land != 0)
                {
                    collV = -1;
                }
            }
        }
    }
    xland = ucollisions_TestCollisionXwithGear(Gear, ufloat_hwSign(Gear->dX));
    if(xland != 0)
    {
        collH = ufloat_hwSign(Gear->dX);
        if((Gear->AdvBounce == 0) || ((xland & lfBouncy) == 0))
        {
            Gear->dX = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_op_sub(Gear->dX), Gear->Elasticity);
            Gear->dY = ufloat_hwFloat_hwFloat_op_mul(Gear->dY, Gear->Elasticity);
            Gear->State = Gear->State | gstCollision;
        }
        else
        {
            Gear->dX = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_op_sub(Gear->dX), cElastic);
            Gear->dY = ufloat_hwFloat_hwFloat_op_mul(Gear->dY, cElastic);
        }
    }
    else
    {
        if(Gear->AdvBounce == 1)
        {
            xland = ucollisions_TestCollisionXwithGear(Gear, -ufloat_hwSign(Gear->dX));
            if(xland != 0)
            {
                collH = -ufloat_hwSign(Gear->dX);
            }
        }
    }
    if(((collV != 0) && (collH != 0)) && ((Gear->AdvBounce == 1) && ((collV == -1) || ((tdX.QWordValue + tdY.QWordValue) > _0_2.QWordValue))))
    {
        if(((xland | land) & lfBouncy) == 0)
        {
            Gear->dX = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_mul(tdY, Gear->Elasticity), Gear->Friction);
            Gear->dY = ufloat_hwFloat_hwFloat_op_mul(tdX, Gear->Elasticity);
            Gear->State = Gear->State | gstCollision;
        }
        else
        {
            Gear->dX = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_mul(tdY, cElastic), Gear->Friction);
            Gear->dY = ufloat_hwFloat_hwFloat_op_mul(tdX, cElastic);
        }
        Gear->dX.isNegative = tdX.isNegative;
        Gear->dY.isNegative = tdY.isNegative;
        if((((collV > 0) && (collH > 0)) && !tdX.isNegative) && !tdY.isNegative)
        {
            Gear->dX.isNegative = true;
            Gear->dY.isNegative = true;
        }
        else
        {
            if(((collV > 0) && (collH < 0)) && (tdX.isNegative || tdY.isNegative))
            {
                Gear->dY.isNegative = !tdY.isNegative;
                if(!tdY.isNegative)
                {
                    Gear->dX.isNegative = false;
                }
            }
            else
            {
                if(((collV < 0) && (collH > 0)) && !tdX.isNegative)
                {
                    Gear->dX.isNegative = true;
                    Gear->dY.isNegative = false;
                }
                else
                {
                    if((((collV < 0) && (collH < 0)) && tdX.isNegative) && tdY.isNegative)
                    {
                        Gear->dX.isNegative = false;
                    }
                }
            }
        }
        isFalling = false;
        Gear->AdvBounce = 10;
    }
    if(Gear->AdvBounce > 1)
    {
        --Gear->AdvBounce;
    }
    if(isFalling && ((Gear->State & gstNoGravity) == 0))
    {
        Gear->dY = ufloat_hwFloat_hwFloat_op_add(Gear->dY, cGravity);
        if(((GameFlags & gfMoreWind) != 0) && (!(((Gear->Kind == gtMine) || (Gear->Kind == gtAirMine) || (Gear->Kind == gtSMine) || (Gear->Kind == gtKnife) || (Gear->Kind == gtExplosives) || (Gear->Kind == gtSentry))) || (TimeNotInTurn < MaxMoreWindTime)))
        {
            Gear->dX = ufloat_hwFloat_hwFloat_op_add(Gear->dX, ufloat_hwFloat_hwFloat_op_div(cWindSpeed, Gear->Density));
        }
    }
    Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, Gear->dX);
    Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, Gear->dY);
    ugearsutils_CheckGearDrowning(&(Gear));
    if(!isFalling && ((Gear->dX.QWordValue + Gear->dY.QWordValue) < _0_02.QWordValue))
    {
        Gear->State = Gear->State & ~gstMoving;
    }
    else
    {
        Gear->State = Gear->State | gstMoving;
    }
    if(((((xland | land) & lfBouncy) != 0) && (Gear->dX.QWordValue < _0_15.QWordValue)) && (Gear->dY.QWordValue < _0_15.QWordValue))
    {
        Gear->State = Gear->State | gstCollision;
    }
    if((((xland | land) & lfBouncy) != 0) && ((Gear->dX.QWordValue > _0_15.QWordValue) || (Gear->dY.QWordValue > _0_15.QWordValue)))
    {
        ugearsutils_AddBounceEffectForGear_1(Gear);
    }
    else
    {
        if((((Gear->nImpactSounds > 0) && ((Gear->State & gstCollision) != 0)) && (((Gear->Kind != gtMine) && (Gear->Damage != 0)) || ((Gear->State & gstMoving) != 0))) && (((Gear->Radius < 3) && (ufloat_hwFloat_hwFloat_op_lt(Gear->dY, ufloat_hwFloat_op_sub(_0_1)))) || ((Gear->Radius >= 3) && ((Gear->dX.QWordValue > _0_1.QWordValue) || (Gear->dY.QWordValue > _0_1.QWordValue)))))
        {
            usound_PlaySound_2(((TSound)(Gear->ImpactSound) + ((LongInt)urandom_GetRandom(Gear->nImpactSounds))), Gear->Kind != gtDynamite);
        }
    }
};
void ugearshandlersmess_doStepBomb(PGear Gear)
{
    LongInt i;
    LongInt x;
    LongInt y;
    hwFloat dX;
    hwFloat dY;
    hwFloat gdX;
    PVisualGear vg;
    AllInactive = false;
    ugearshandlersmess_doStepFallingGear(Gear);
    --Gear->Timer;
    if(Gear->Timer == 1000)
    {
        switch(Gear->Kind)
        {case gtGrenade:
         case gtClusterBomb:
         case gtWatermelon:
         case gtHellishBomb:ugearshandlersmess_makeHogsWorry(Gear->X, Gear->Y, Gear->Boom, Gear->Kind);
                            break;
         case gtGasBomb:ugearshandlersmess_makeHogsWorry(Gear->X, Gear->Y, 50, Gear->Kind);
                        break;
         default: break;}
    }
    if((Gear->Kind == gtBall) && ((Gear->State & gsttmpFlag) != 0))
    {
        ugearsutils_CheckCollision(Gear);
        if((Gear->State & gstCollision) != 0)
        {
            ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLDontDraw | EXPLNoGfx);
        }
    }
    if((Gear->Kind == gtGasBomb) && ((GameTicks % 200) == 0))
    {
        vg = uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtSmokeWhite);
        if(vg != NULL)
        {
            vg->Tint = 0xffc0c000;
        }
    }
    if(Gear->Timer == 0)
    {
        switch(Gear->Kind)
        {case gtGrenade:ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
                        break;
         case gtBall:ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
                     break;
         case gtClusterBomb:{
                                x = ufloat_hwRound(Gear->X);
                                y = ufloat_hwRound(Gear->Y);
                                gdX = Gear->dX;
                                ugearsutils_doMakeExplosion_5(x, y, Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
                                {i = 0;
                                 LongInt i__end__ = 4;
                                 if (i <= i__end__) do {
                                                           dX = ufloat_hwFloat_hwFloat_op_add(urandom_rndSign(ufloat_hwFloat_hwFloat_op_mul(urandom_GetRandomf(), _0_1)), ufloat_hwFloat_LongInt_op_div(gdX, 5));
                                                           dY = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_sub(urandom_GetRandomf(), _3), _0_08);
                                                           FollowGear = ugearslist_AddGear_7(x, y, gtCluster, 0, dX, dY, 25);
                                                       } while(i++ != i__end__);}
                            }
                            break;
         case gtWatermelon:{
                               x = ufloat_hwRound(Gear->X);
                               y = ufloat_hwRound(Gear->Y);
                               gdX = Gear->dX;
                               ugearsutils_doMakeExplosion_5(x, y, Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
                               {i = 0;
                                LongInt i__end__ = 5;
                                if (i <= i__end__) do {
                                                          dX = ufloat_hwFloat_hwFloat_op_add(urandom_rndSign(ufloat_hwFloat_hwFloat_op_mul(urandom_GetRandomf(), _0_1)), ufloat_hwFloat_LongInt_op_div(gdX, 5));
                                                          dY = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_sub(urandom_GetRandomf(), _1_5), _0_3);
                                                          FollowGear = ugearslist_AddGear_7(x, y, gtMelonPiece, 0, dX, dY, 75);
                                                          FollowGear->DirAngle = i * 60;
                                                      } while(i++ != i__end__);}
                           }
                           break;
         case gtHellishBomb:{
                                x = ufloat_hwRound(Gear->X);
                                y = ufloat_hwRound(Gear->Y);
                                ugearsutils_doMakeExplosion_5(x, y, Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
                                {i = 0;
                                 LongInt i__end__ = 127;
                                 if (i <= i__end__) do {
                                                           dX = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleCos(i * 16), _0_5), ufloat_hwFloat_hwFloat_op_add(urandom_GetRandomf(), _1));
                                                           dY = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleSin(i * 16), _0_5), ufloat_hwFloat_hwFloat_op_add(urandom_GetRandomf(), _1));
                                                           if((i % 2) == 0)
                                                           {
                                                               ugearslist_AddGear_7(x, y, gtFlame, gsttmpFlag, dX, dY, 0);
                                                               ugearslist_AddGear_7(x, y, gtFlame, 0, dX, ufloat_hwFloat_op_sub(dY), 0);
                                                           }
                                                           else
                                                           {
                                                               ugearslist_AddGear_7(x, y, gtFlame, 0, dX, dY, 0);
                                                               ugearslist_AddGear_7(x, y, gtFlame, gsttmpFlag, dX, ufloat_hwFloat_op_sub(dY), 0);
                                                           }
                                                       } while(i++ != i__end__);}
                            }
                            break;
         case gtGasBomb:{
                            ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
                            {i = 0;
                             LongInt i__end__ = 2;
                             if (i <= i__end__) do {
                                                       x = urandom_GetRandom(60);
                                                       y = urandom_GetRandom(40);
                                                       FollowGear = ugearslist_AddGear_7((ufloat_hwRound(Gear->X) - 30) + x, (ufloat_hwRound(Gear->Y) - 20) + y, gtPoisonCloud, 0, _0, _0, 0);
                                                   } while(i++ != i__end__);}
                        }
                        break;
         default: break;}
        ugearslist_DeleteGear(Gear);
        return;
    }
    ugearsutils_CalcRotationDirAngle(Gear);
    if(Gear->Kind == gtHellishBomb)
    {
        if(Gear->Timer == 3000)
        {
            Gear->nImpactSounds = 0;
            usound_PlaySound_1(sndHellish);
        }
        if((GameTicks & 0x3f) == 0)
        {
            if((Gear->State & gstCollision) == 0)
            {
                uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtEvilTrace);
            }
        }
    }
};
void ugearshandlersmess_doStepMolotov(PGear Gear)
{
    LongWord s;
    LongInt i;
    LongInt gX;
    LongInt gY;
    hwFloat dX;
    hwFloat dY;
    PVisualGear smoke;
    PVisualGear glass;
    AllInactive = false;
    ugearshandlersmess_doStepFallingGear(Gear);
    ugearsutils_CalcRotationDirAngle(Gear);
    s = uutils_Max(32, 152 - fpcrtl_round((fpcrtl_abs(ufloat_hwFloat2Float(Gear->dX)) + fpcrtl_abs(ufloat_hwFloat2Float(Gear->dY))) * 120)) + fpcrtl_random(10);
    if((GameTicks % s) == 0)
    {
        if(Gear->dX.isNegative)
        {
            i = 130;
        }
        else
        {
            i = 50;
        }
        smoke = uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X) - fpcrtl_round(cos(((Gear->DirAngle + i) * pi) /(float) 180) * 20), ufloat_hwRound(Gear->Y) - fpcrtl_round(sin(((Gear->DirAngle + i) * pi) /(float) 180) * 20), vgtSmoke);
        if(smoke != NULL)
        {
            smoke->scale = 0.75;
        }
    }
    if((Gear->State & gstCollision) != 0)
    {
        usound_PlaySound_1(sndMolotov);
        gX = ufloat_hwRound(Gear->X);
        gY = ufloat_hwRound(Gear->Y);
        {i = 0;
         LongInt i__end__ = 4;
         if (i <= i__end__) do {
                                   glass = uvisualgearslist_AddVisualGear_3((gX + fpcrtl_random(7)) - 3, (gY + fpcrtl_random(7)) - 3, vgtEgg);
                                   if(glass != NULL)
                                   {
                                       {
                                           (*glass).Frame = 2;
                                           (*glass).Tint = 0x41b83ed0 - (i * 0x10081000);
                                           (*glass).dX = (*glass).dX + (ufloat_hwFloat2Float(Gear->dX) /(float) 2);
                                           (*glass).Angle = fpcrtl_random(360);
                                           (*glass).FrameTicks = 750;
                                           (*glass).State = (sprEgg);
                                       }
                                   }
                               } while(i++ != i__end__);}
        {i = 0;
         LongInt i__end__ = 24;
         if (i <= i__end__) do {
                                   dX = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleCos(i * 2), ufloat_hwFloat_LongInt_op_mul(_0_15, i / 5)), ufloat_hwFloat_hwFloat_op_add(urandom_GetRandomf(), _1));
                                   dY = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleSin(i * 8), _0_5), ufloat_hwFloat_hwFloat_op_add(urandom_GetRandomf(), _1));
                                   ugearslist_AddGear_7(gX, gY, gtFlame, gsttmpFlag, dX, dY, 0);
                                   ugearslist_AddGear_7(gX, gY, gtFlame, gsttmpFlag, dX, ufloat_hwFloat_op_sub(dY), 0);
                                   ugearslist_AddGear_7(gX, gY, gtFlame, gsttmpFlag, ufloat_hwFloat_op_sub(dX), dY, 0);
                                   ugearslist_AddGear_7(gX, gY, gtFlame, gsttmpFlag, ufloat_hwFloat_op_sub(dX), ufloat_hwFloat_op_sub(dY), 0);
                               } while(i++ != i__end__);}
        ugearslist_DeleteGear(Gear);
        return;
    }
};
void ugearshandlersmess_doStepCluster(PGear Gear)
{
    AllInactive = false;
    ugearshandlersmess_doStepFallingGear(Gear);
    if((Gear->State & gstCollision) != 0)
    {
        ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
        ugearslist_DeleteGear(Gear);
        return;
    }
    if(Gear->Kind == gtMelonPiece)
    {
        ugearsutils_CalcRotationDirAngle(Gear);
    }
    else
    {
        if((GameTicks & 0x1f) == 0)
        {
            uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtSmokeTrace);
        }
    }
};
void ugearshandlersmess_doStepShell(PGear Gear)
{
    AllInactive = false;
    if((GameFlags & gfMoreWind) == 0)
    {
        Gear->dX = ufloat_hwFloat_hwFloat_op_add(Gear->dX, cWindSpeed);
    }
    ugearshandlersmess_doStepFallingGear(Gear);
    if((Gear->State & gstCollision) != 0)
    {
        ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
        ugearslist_DeleteGear(Gear);
        return;
    }
    if((GameTicks & 0x3f) == 0)
    {
        uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtSmokeTrace);
    }
};
void ugearshandlersmess_doStepSnowball(PGear Gear)
{
    LongInt kick;
    LongInt i;
    PVisualGear particle;
    hwFloat gdX;
    hwFloat gdY;
    AllInactive = false;
    if((GameFlags & gfMoreWind) == 0)
    {
        Gear->dX = ufloat_hwFloat_hwFloat_op_add(Gear->dX, cWindSpeed);
    }
    gdX = Gear->dX;
    gdY = Gear->dY;
    ugearshandlersmess_doStepFallingGear(Gear);
    ugearsutils_CalcRotationDirAngle(Gear);
    if((Gear->State & gstCollision) != 0)
    {
        kick = ufloat_hwRound(ufloat_hwFloat_LongInt_op_div(ufloat_hwFloat_LongInt_op_mul(ufloat_hwFloat_hwFloat_op_add(ufloat_hwAbs(gdX), ufloat_hwAbs(gdY)), Gear->Boom), 10000));
        Gear->dX = gdX;
        Gear->dY = gdY;
        ugearsutils_AmmoShove(Gear, 0, kick);
        {i = 15 + (kick / 10);
         LongInt i__end__ = 0;
         if (i >= i__end__) do {
                                   particle = uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X) + fpcrtl_random(25), ufloat_hwRound(Gear->Y) + fpcrtl_random(25), vgtDust);
                                   if(particle != NULL)
                                   {
                                       particle->dX = particle->dX + (Gear->dX.QWordValue /(float) 21474836480);
                                   }
                               } while(i-- != i__end__);}
        ugearslist_DeleteGear(Gear);
        return;
    }
    if(((GameTicks & 0x1f) == 0) && (fpcrtl_random(3) == 0))
    {
        particle = uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtDust);
        if(particle != NULL)
        {
            particle->dX = particle->dX + (Gear->dX.QWordValue /(float) 21474836480);
        }
    }
};
void ugearshandlersmess_doStepSnowflake(PGear Gear)
{
    LongInt xx;
    LongInt yy;
    LongInt px;
    LongInt py;
    LongInt rx;
    LongInt ry;
    LongInt lx;
    LongInt ly;
    boolean move;
    boolean draw;
    boolean allpx;
    boolean gun;
    PSDL_Surface s;
    PLongWordArray p;
    LongWord lf;
    hwFloat oldY;
    gun = (Gear->State & gsttmpFlag) != 0;
    move = false;
    draw = false;
    if(gun)
    {
        ++Gear->Pos;
        Gear->State = Gear->State & ~gstInvisible;
        ugearshandlersmess_doStepFallingGear(Gear);
        ugearsutils_CheckCollision(Gear);
        if(((Gear->State & gstCollision) != 0) || ((Gear->State & gstMoving) == 0))
        {
            draw = true;
        }
        xx = ufloat_hwRound(Gear->X);
        yy = ufloat_hwRound(Gear->Y);
        if((draw && (WorldEdge == weWrap)) && ((xx < (leftX + 3)) || (xx > (rightX - 3))))
        {
            if(xx < (leftX + 3))
            {
                xx = rightX - 3;
            }
            else
            {
                xx = leftX + 3;
            }
            Gear->X = ufloat_int2hwFloat(xx);
        }
    }
    else
    {
        if((GameTicks & 0x7) == 0)
        {
            {
                (*Gear).Pos += 8;
                (*Gear).State = (*Gear).State & ~gstInvisible;
                oldY = (*Gear).Y;
                (*Gear).X = ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_add((*Gear).X, ufloat_hwFloat_LongInt_op_mul(cWindSpeed, 3200)), (*Gear).dX);
                (*Gear).Y = ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_add((*Gear).Y, (*Gear).dY), ufloat_hwFloat_LongInt_op_mul(cGravity, vobFallSpeed * 8));
                xx = ufloat_hwRound((*Gear).X);
                yy = ufloat_hwRound((*Gear).Y);
                if(vobVelocity != 0)
                {
                    (*Gear).DirAngle = (*Gear).DirAngle + ((*Gear).Damage /(float) 1000);
                    if((*Gear).DirAngle < 0)
                    {
                        (*Gear).DirAngle = (*Gear).DirAngle + 360;
                    }
                    else
                    {
                        if(360 < (*Gear).DirAngle)
                        {
                            (*Gear).DirAngle = (*Gear).DirAngle - 360;
                        }
                    }
                }
                if(ucollisions_CheckCoordInWater(xx, yy))
                {
                    move = true;
                }
                else
                {
                    if((xx > snowRight) || (xx < snowLeft))
                    {
                        move = true;
                    }
                    else
                    {
                        if(cGravity.isNegative && (yy < (LAND_HEIGHT - 1200)))
                        {
                            move = true;
                        }
                        else
                        {
                            if((((yy & LAND_HEIGHT_MASK) == 0) && ((xx & LAND_WIDTH_MASK) == 0)) && (ulandutils_LandGet(yy, xx) != 0))
                            {
                                lf = ulandutils_LandGet(yy, xx) & ((lfObject | lfBasic) | lfIndestructible);
                                if(lf == 0)
                                {
                                    lf = lfObject;
                                }
                                if((((yy - 1) & LAND_HEIGHT_MASK) == 0) && (ulandutils_LandGet(yy - 1, xx) == 0))
                                {
                                    (*Gear).X = ufloat_hwFloat_hwFloat_op_sub(ufloat_hwFloat_hwFloat_op_sub((*Gear).X, ufloat_hwFloat_LongInt_op_mul(cWindSpeed, 1600)), (*Gear).dX);
                                }
                                else
                                {
                                    if(((yy - 1) & LAND_HEIGHT_MASK) == 0)
                                    {
                                        if((((xx - 1) & LAND_WIDTH_MASK) == 0) && (ulandutils_LandGet(yy - 1, xx - 1) == 0))
                                        {
                                            (*Gear).X = ufloat_hwFloat_hwFloat_op_sub((*Gear).X, _0_8);
                                            (*Gear).Y = oldY;
                                        }
                                        else
                                        {
                                            if((((xx - 2) & LAND_WIDTH_MASK) == 0) && (ulandutils_LandGet(yy - 1, xx - 2) == 0))
                                            {
                                                (*Gear).X = ufloat_hwFloat_hwFloat_op_sub((*Gear).X, _1_6);
                                                (*Gear).Y = oldY;
                                            }
                                            else
                                            {
                                                if((((xx + 1) & LAND_WIDTH_MASK) == 0) && (ulandutils_LandGet(yy - 1, xx + 1) == 0))
                                                {
                                                    (*Gear).X = ufloat_hwFloat_hwFloat_op_add((*Gear).X, _0_8);
                                                    (*Gear).Y = oldY;
                                                }
                                                else
                                                {
                                                    if((((xx + 2) & LAND_WIDTH_MASK) == 0) && (ulandutils_LandGet(yy - 1, xx + 2) == 0))
                                                    {
                                                        (*Gear).X = ufloat_hwFloat_hwFloat_op_add((*Gear).X, _1_6);
                                                        (*Gear).Y = oldY;
                                                    }
                                                    else
                                                    {
                                                        if((((yy + 1) & LAND_HEIGHT_MASK) == 0) && ((ulandutils_LandGet(yy + 1, xx) & 0xff) != 0))
                                                        {
                                                            move = true;
                                                        }
                                                        else
                                                        {
                                                            draw = true;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if((((yy + 1) & LAND_HEIGHT_MASK) == 0) && ((ulandutils_LandGet(yy + 1, xx) & 0xff) != 0))
                                        {
                                            move = true;
                                        }
                                        else
                                        {
                                            draw = true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(draw)
    {
        {
            move = true;
            if(((*Gear).Pos > 20) && ((CurAmmoGear == NULL) || (CurAmmoGear->Kind != gtRope)))
            {
                if(!gun)
                {
                    yy -= 3;
                    xx -= 1;
                }
                s = SpritesData[sprSnow].Surface;
                p = s->pixels;
                allpx = true;
                {py = 0;
                 LongInt py__end__ = ((int)(s->h) - 1);
                 if (py <= py__end__) do {
                                             {px = 0;
                                              LongInt px__end__ = ((int)(s->w) - 1);
                                              if (px <= px__end__) do {
                                                                          lx = xx + px;
                                                                          ly = yy + py;
                                                                          if((((ly & LAND_HEIGHT_MASK) == 0) && ((lx & LAND_WIDTH_MASK) == 0)) && ((ulandutils_LandGet(ly, lx) & 0xff) == 0))
                                                                          {
                                                                              rx = lx;
                                                                              ry = ly;
                                                                              if((cReducedQuality & rqBlurryLand) != 0)
                                                                              {
                                                                                  rx = rx / 2;
                                                                                  ry = ry / 2;
                                                                              }
                                                                              if(ulandutils_LandGet(yy + py, xx + px) <= lfAllObjMask)
                                                                              {
                                                                                  if(gun)
                                                                                  {
                                                                                      LandDirty[yy / 32][xx / 32] = 1;
                                                                                      if(ulandutils_LandPixelGet(ry, rx) == 0)
                                                                                      {
                                                                                          ulandutils_LandSet(ly, lx, lfDamaged | lfObject);
                                                                                      }
                                                                                      else
                                                                                      {
                                                                                          ulandutils_LandSet(ly, lx, lfDamaged | lfBasic);
                                                                                      }
                                                                                  }
                                                                                  else
                                                                                  {
                                                                                      ulandutils_LandSet(ly, lx, lf);
                                                                                  }
                                                                              }
                                                                              if(gun)
                                                                              {
                                                                                  ulandutils_LandPixelSet(ry, rx, ((((Gear->Tint >> 24) << RShift) | (((Gear->Tint >> 16) & 0xff) << GShift)) | (((Gear->Tint >> 8) & 0xff) << BShift)) | ((*p)[px] & AMask));
                                                                              }
                                                                              else
                                                                              {
                                                                                  ulandutils_LandPixelSet(ry, rx, ulandgraphics_addBgColor(ulandutils_LandPixelGet(ry, rx), (*p)[px]));
                                                                              }
                                                                          }
                                                                          else
                                                                          {
                                                                              allpx = false;
                                                                          }
                                                                      } while(px++ != px__end__);}
                                             p = ((PLongWordArray)&((*p)[s->pitch >> 2]));
                                         } while(py++ != py__end__);}
                if(allpx)
                {
                    ulandtexture_UpdateLandTexture(xx, ((int)(s->h) - 1), yy, ((int)(s->w) - 1), true);
                }
                else
                {
                    ulandtexture_UpdateLandTexture(uutils_Max(0, uutils_Min(LAND_WIDTH, xx)), uutils_Min(LAND_WIDTH - xx, ((int)(s->w) - 1)), uutils_Max(0, uutils_Min(LAND_WIDTH, yy)), uutils_Min(LAND_HEIGHT - yy, ((int)(s->h) - 1)), false);
                }
            }
        }
    }
    if(move)
    {
        if(gun)
        {
            ugearslist_DeleteGear(Gear);
            return;
        }
        Gear->Pos = 0;
        Gear->X = ufloat_int2hwFloat(((LongInt)urandom_GetRandom(snowRight - snowLeft)) + snowLeft);
        if(cGravity.isNegative && (yy < (LAND_HEIGHT - 1200)))
        {
            Gear->Y = ufloat_int2hwFloat((LAND_HEIGHT - 50) - ((LongInt)urandom_GetRandom(50)));
        }
        else
        {
            Gear->Y = ufloat_int2hwFloat((LAND_HEIGHT + ((LongInt)urandom_GetRandom(50))) - 1250);
        }
        Gear->State = Gear->State | gstInvisible;
    }
};
void ugearshandlersmess_doStepGrave(PGear Gear)
{
    if((Gear->Message & gmDestroy) != 0)
    {
        ugearslist_DeleteGear(Gear);
        return;
    }
    AllInactive = false;
    if(Gear->dY.isNegative)
    {
        if(ucollisions_TestCollisionY(Gear, -1) != 0)
        {
            Gear->dY = _0;
        }
    }
    if(!Gear->dY.isNegative)
    {
        if(ucollisions_TestCollisionY(Gear, 1) != 0)
        {
            Gear->dY = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_op_sub(Gear->dY), Gear->Elasticity);
            if(ufloat_hwFloat_hwFloat_op_gt(Gear->dY, ufloat_hwFloat_op_sub(_1div1024)))
            {
                Gear->Active = false;
                return;
            }
            else
            {
                if(ufloat_hwFloat_hwFloat_op_lt(Gear->dY, ufloat_hwFloat_op_sub(_0_03)))
                {
                    usound_PlaySound_1(Gear->ImpactSound);
                }
            }
        }
    }
    Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, Gear->dY);
    ugearsutils_CheckGearDrowning(&(Gear));
    Gear->dY = ufloat_hwFloat_hwFloat_op_add(Gear->dY, cGravity);
};
void ugearshandlersmess_doStepBeeWork(PGear Gear)
{
    hwFloat t;
    LongInt gX;
    LongInt gY;
    LongInt i;
    boolean uw;
    boolean nuw;
    boolean wrapped;
    PVisualGear flower;
    wrapped = ugearsutils_WorldWrap(&(Gear));
    if(wrapped)
    {
        ugearsutils_HomingWrap(&(Gear));
    }
    AllInactive = false;
    gX = ufloat_hwRound(Gear->X);
    gY = ufloat_hwRound(Gear->Y);
    uw = Gear->Tag != 0;
    nuw = ucollisions_CheckCoordInWater(gX, gY + Gear->Radius);
    if(nuw != uw)
    {
        if(Gear->Timer != 5000)
        {
            ugearsutils_AddSplashForGear(Gear, false);
        }
        usound_StopSoundChan_1(Gear->SoundChannel);
        if(nuw)
        {
            Gear->SoundChannel = usound_LoopSound_1(sndBeeWater);
            Gear->Tag = 1;
        }
        else
        {
            Gear->SoundChannel = usound_LoopSound_1(sndBee);
            Gear->Tag = 0;
        }
    }
    if(Gear->Timer == 0)
    {
        ugearshandlersmess_doStepFallingGear(Gear);
        if((Gear->State & gstDrowning) != 0)
        {
            usound_StopSoundChan_1(Gear->SoundChannel);
        }
    }
    else
    {
        if((Gear->Timer & 0xf) == 0)
        {
            if((Gear->Timer & 0x3f) == 0)
            {
                uvisualgearslist_AddVisualGear_3(gX, gY, vgtBeeTrace);
            }
            Gear->dX = ufloat_hwFloat_hwFloat_op_add(Gear->dX, ufloat_hwFloat_LongInt_op_mul(_0_000064, Gear->Target.x - gX));
            Gear->dY = ufloat_hwFloat_hwFloat_op_add(Gear->dY, ufloat_hwFloat_LongInt_op_mul(_0_000064, Gear->Target.y - gY));
            t = ufloat_hwFloat_hwFloat_op_div(Gear->Friction, ufloat_Distance(Gear->dX, Gear->dY));
            Gear->dX = ufloat_hwFloat_hwFloat_op_mul(Gear->dX, t);
            Gear->dY = ufloat_hwFloat_hwFloat_op_mul(Gear->dY, t);
        }
        Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, Gear->dX);
        Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, Gear->dY);
    }
    ugearsutils_CheckCollision(Gear);
    if((Gear->State & gstCollision) != 0)
    {
        usound_StopSoundChan_1(Gear->SoundChannel);
        ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
        {i = 0;
         LongInt i__end__ = 31;
         if (i <= i__end__) do {
                                   flower = uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtStraightShot);
                                   if(flower != NULL)
                                   {
                                       {
                                           (*flower).scale = 0.75;
                                           (*flower).dX = 1.0e-3 * fpcrtl_random(200);
                                           (*flower).dY = 1.0e-3 * fpcrtl_random(200);
                                           if(fpcrtl_random(2) == 0)
                                           {
                                               (*flower).dX = -(*flower).dX;
                                           }
                                           if(fpcrtl_random(2) == 0)
                                           {
                                               (*flower).dY = -(*flower).dY;
                                           }
                                           (*flower).FrameTicks = fpcrtl_random(250) + 250;
                                           (*flower).State = (sprTargetBee);
                                       }
                                   }
                               } while(i++ != i__end__);}
        ugearslist_DeleteGear(Gear);
        return;
    }
    if(Gear->Timer > 0)
    {
        --Gear->Timer;
        if(Gear->Timer == 0)
        {
            Gear->RenderTimer = false;
            Gear->State = Gear->State & ~gstSubmersible;
        }
    }
};
void ugearshandlersmess_doStepBee(PGear Gear)
{
    boolean wrapped;
    AllInactive = false;
    Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, Gear->dX);
    Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, Gear->dY);
    wrapped = ugearsutils_WorldWrap(&(Gear));
    if(wrapped)
    {
        ugearsutils_HomingWrap(&(Gear));
    }
    Gear->dY = ufloat_hwFloat_hwFloat_op_add(Gear->dY, cGravity);
    ugearsutils_CheckGearDrowning(&(Gear));
    ugearsutils_CheckCollision(Gear);
    if((Gear->State & gstCollision) != 0)
    {
        ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
        ugearslist_DeleteGear(Gear);
        return;
    }
    --Gear->Timer;
    if(Gear->Timer == 0)
    {
        (*(*Gear->Hedgehog).Gear).Message = (*(*Gear->Hedgehog).Gear).Message & ~gmAttack;
        (*(*Gear->Hedgehog).Gear).State = (*(*Gear->Hedgehog).Gear).State & ~gstAttacking;
        AttackBar = 0;
        Gear->SoundChannel = usound_LoopSound_1(sndBee);
        Gear->Timer = 5000;
        Gear->Friction = ufloat_Distance(Gear->dX, Gear->dY);
        Gear->doStep = &(ugearshandlersmess_doStepBeeWork);
    }
};
void ugearshandlersmess_doStepShotIdle(PGear Gear)
{
    AllInactive = false;
    if(Gear->Kind != gtMinigunBullet)
    {
        ++Gear->Timer;
        if(Gear->Timer > 75)
        {
            ugearslist_DeleteGear(Gear);
            ugearshedgehog_AfterAttack();
        }
    }
    else
    {
        ugearslist_DeleteGear(Gear);
    }
};
void ugearshandlersmess_CreateShellForGear(PGear Gear,LongWord startFrame)
{
    PVisualGear shell;
    shell = uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtShell);
    if(shell != NULL)
    {
        shell->dX = Gear->dX.QWordValue /(float) -17179869184;
        if(Gear->dX.isNegative)
        {
            shell->dX = -shell->dX;
        }
        shell->dY = Gear->dY.QWordValue /(float) -17179869184;
        shell->Frame = startFrame;
    }
};
boolean ugearshandlersmess_ShotgunLineHitHelp(PGear Gear,hwFloat oX,hwFloat oY,hwFloat tX,hwFloat tY)
{
    boolean shotgunlinehithelp_result;
    LongInt i;
    PGearArray Collisions;
    shotgunlinehithelp_result = false;
    Collisions = ucollisions_CheckAllGearsLineCollision(Gear, oX, oY, tX, tY);
    i = Collisions->Count;
    while(i > 0)
    {
        --i;
        if((((*Collisions->ar[i]).Kind == gtMine) || ((*Collisions->ar[i]).Kind == gtSMine) || ((*Collisions->ar[i]).Kind == gtAirMine) || ((*Collisions->ar[i]).Kind == gtKnife) || ((*Collisions->ar[i]).Kind == gtCase) || ((*Collisions->ar[i]).Kind == gtTarget) || ((*Collisions->ar[i]).Kind == gtExplosives) || ((*Collisions->ar[i]).Kind == gtSentry)))
        {
            Gear->X = (*Collisions->ar[i]).X;
            Gear->Y = (*Collisions->ar[i]).Y;
            ugearsutils_ShotgunShot(Gear);
            Gear->doStep = &(ugearshandlersmess_doStepShotIdle);
            shotgunlinehithelp_result = true;
            return shotgunlinehithelp_result;
        }
    }
    return shotgunlinehithelp_result;
};
void ugearshandlersmess_doStepShotgunShot(PGear Gear)
{
    LongWord i;
    hwFloat oX;
    hwFloat oY;
    hwFloat tmpX;
    hwFloat tmpY;
    AllInactive = false;
    if((Gear->State & gstAnimation) == 0)
    {
        --Gear->Timer;
        if(Gear->Timer == 0)
        {
            usound_PlaySound_1(sndShotgunFire);
            ugearshandlersmess_CreateShellForGear(Gear, 0);
            Gear->State = Gear->State | gstAnimation;
        }
        else
        {
            if(((*Gear->Hedgehog).Gear == NULL) || (((*(*Gear->Hedgehog).Gear).State & (gstMoving | gstHHDriven)) == gstMoving))
            {
                ugearslist_DeleteGear(Gear);
                ugearshedgehog_AfterAttack();
            }
        }
        return;
    }
    else
    {
        ++Gear->Timer;
    }
    i = 100;
    oX = Gear->X;
    oY = Gear->Y;
    do {
           if(Gear->Tag == 0)
           {
               Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, Gear->dX);
               Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, Gear->dY);
           }
           tmpX = Gear->X;
           tmpY = Gear->Y;
           if((Gear->PortalCounter < 30) && ugearsutils_WorldWrap(&(Gear)))
           {
               ++Gear->PortalCounter;
               if(ugearshandlersmess_ShotgunLineHitHelp(Gear, oX, oY, tmpX, tmpY))
               {
                   return;
               }
               oX = Gear->X;
               oY = Gear->Y;
           }
           ugearsutils_CheckCollision(Gear);
           if((Gear->State & gstCollision) != 0)
           {
               if(Gear->Tag == 0)
               {
                   Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, ufloat_hwFloat_LongInt_op_mul(Gear->dX, 2));
                   Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, ufloat_hwFloat_LongInt_op_mul(Gear->dY, 2));
                   Gear->Tag = 1;
               }
               else
               {
                   Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, ufloat_hwFloat_LongInt_op_mul(Gear->dX, 6));
                   Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, ufloat_hwFloat_LongInt_op_mul(Gear->dY, 6));
                   ugearsutils_ShotgunShot(Gear);
                   Gear->doStep = &(ugearshandlersmess_doStepShotIdle);
               }
               return;
           }
           else
           {
               Gear->Tag = 0;
           }
           ugearsutils_CheckGearDrowning(&(Gear));
           if((Gear->State & gstDrowning) != 0)
           {
               Gear->doStep = &(ugearshandlersmess_doStepShotIdle);
               break;
           }
           --i;
       } while(!(i == 0));
    ugearshandlersmess_ShotgunLineHitHelp(Gear, oX, oY, Gear->X, Gear->Y);
    if(((ufloat_hwRound(Gear->X) & LAND_WIDTH_MASK) != 0) || ((ufloat_hwRound(Gear->Y) & LAND_HEIGHT_MASK) != 0))
    {
        Gear->doStep = &(ugearshandlersmess_doStepShotIdle);
    }
};
void ugearshandlersmess_spawnBulletTrail(PGear Bullet,hwFloat bulletX,hwFloat bulletY,boolean fadeIn)
{
    hwFloat oX;
    hwFloat oY;
    real fromX;
    real fromY;
    real toX;
    real toY;
    real dX;
    real dY;
    real bLength;
    real stepLength;
    PVisualGear VGear;
    LongWord i;
    LongWord steps;
    if(CurrentHedgehog->Gear == NULL)
    {
        ugearslist_DeleteGear(Bullet);
        return;
    }
    if(Bullet->PortalCounter == 0)
    {
        oX = ufloat_hwFloat_hwFloat_op_add((*CurrentHedgehog->Gear).X, ufloat_int2hwFloat(uutils_GetLaunchX(CurrentHedgehog->CurAmmoType, ufloat_hwSign((*CurrentHedgehog->Gear).dX), (*CurrentHedgehog->Gear).Angle)));
        oY = ufloat_hwFloat_hwFloat_op_add((*CurrentHedgehog->Gear).Y, ufloat_int2hwFloat(uutils_GetLaunchY(CurrentHedgehog->CurAmmoType, (*CurrentHedgehog->Gear).Angle)));
    }
    else
    {
        oX = Bullet->Elasticity;
        oY = Bullet->Friction;
    }
    fromX = ufloat_hwFloat2Float(oX);
    fromY = ufloat_hwFloat2Float(oY);
    toX = ufloat_hwFloat2Float(bulletX);
    toY = ufloat_hwFloat2Float(bulletY);
    dX = toX - fromX;
    dY = toY - fromY;
    bLength = sqrt((dX * dX) + (dY * dY));
    dX = dX /(float) bLength;
    dY = dY /(float) bLength;
    if(fadeIn)
    {
        steps = 10;
        stepLength = 12;
        fromX = fromX + (dX * 45);
        fromY = fromY + (dY * 45);
        bLength = bLength - 45;
    }
    else
    {
        steps = 1;
    }
    {i = 0;
     LongWord i__end__ = steps - 1;
     if (i <= i__end__) do {
                               if(i < (steps - 1))
                               {
                                   toX = fromX + (dX * uutils_MinD(stepLength, bLength));
                                   toY = fromY + (dY * uutils_MinD(stepLength, bLength));
                               }
                               else
                               {
                                   if(steps > 1)
                                   {
                                       toX = fromX + (dX * bLength);
                                       toY = fromY + (dY * bLength);
                                   }
                               }
                               if(bLength > 0)
                               {
                                   VGear = uvisualgearslist_AddVisualGear_3(fpcrtl_round(fromX), fpcrtl_round(fromY), vgtLineTrail);
                                   if(VGear != NULL)
                                   {
                                       VGear->X = fromX;
                                       VGear->Y = fromY;
                                       VGear->dX = toX;
                                       VGear->dY = toY;
                                       VGear->Tint = 0xffffff00 | ((0xff * (i + 1)) / steps);
                                       if((((fpcrtl_round(toX) & LAND_WIDTH_MASK) != 0) && !(((WorldEdge == weBounce) || (WorldEdge == weWrap)))) || ((fpcrtl_round(toY) & LAND_HEIGHT_MASK) != 0))
                                       {
                                           if(!ucollisions_CheckCoordInWater(fpcrtl_round(toX), fpcrtl_round(toY)))
                                           {
                                               VGear->dX = VGear->dX + (uutils_Max(LAND_WIDTH, 4096) * (VGear->dX - VGear->X));
                                               VGear->dY = VGear->dY + (uutils_Max(LAND_WIDTH, 4096) * (VGear->dY - VGear->Y));
                                           }
                                       }
                                       VGear->Timer = 200;
                                   }
                               }
                               if(i < (steps - 1))
                               {
                                   fromX = toX;
                                   fromY = toY;
                                   bLength = bLength - stepLength;
                               }
                           } while(i++ != i__end__);}
};
void ugearshandlersmess_LineShoveHelp(PGear Gear,hwFloat oX,hwFloat oY,hwFloat tX,hwFloat tY,hwFloat dX,hwFloat dY,LongWord count)
{
    LongInt dmg;
    LongInt power;
    if(ufloat_hwFloat_hwFloat_op_gt(ufloat_hwFloat_hwFloat_op_add(ufloat_hwSqr(ufloat_hwFloat_hwFloat_op_sub(tX, oX)), ufloat_hwSqr(ufloat_hwFloat_hwFloat_op_sub(tY, oY))), _0_25))
    {
        if((Gear->AmmoType == amDEagle) || (Gear->AmmoType == amMinigun))
        {
            dmg = Gear->Boom;
        }
        else
        {
            dmg = (Gear->Timer * Gear->Boom) / 100000;
        }
        if(Gear->AmmoType == amMinigun)
        {
            power = 10;
        }
        else
        {
            power = 20;
        }
        ugearsutils_AmmoShoveLine(Gear, dmg, power, oX, oY, tX, tY);
    }
    if(Gear->Damage > 0)
    {
        ulandgraphics_DrawTunnel(oX, oY, dX, dY, count, 1);
        Gear->Health -= Gear->Damage;
        Gear->Damage = 0;
    }
};
void ugearshandlersmess_CheckBulletDrowningHelp(PGear Bullet)
{
    hwFloat dX;
    hwFloat dY;
    dX = Bullet->dX;
    dY = Bullet->dY;
    ugearsutils_CheckGearDrowning(&(Bullet));
    if((ufloat_hwFloat_hwFloat_op_neq(dX, Bullet->dX)) || (ufloat_hwFloat_hwFloat_op_neq(dY, Bullet->dY)))
    {
        ugearshandlersmess_spawnBulletTrail(Bullet, Bullet->X, Bullet->Y, Bullet->FlightTime == 0);
        Bullet->Elasticity = Bullet->X;
        Bullet->Friction = Bullet->Y;
        ++Bullet->PortalCounter;
        Bullet->FlightTime = 1;
    }
};
void ugearshandlersmess_CreateBubblesForBullet(PGear Gear)
{
    LongWord i;
    LongWord iInit;
    iInit = 0;
    if(((Gear->State & gstDrowning) != 0) && (Gear->Health > 0))
    {
        if((!SuddenDeathDmg && (WaterOpacity < 0xff)) || (SuddenDeathDmg && (SDWaterOpacity < 0xff)))
        {
            switch(Gear->Kind)
            {case gtMinigunBullet:iInit = Gear->Health * 100;
                                  break;
             case gtDEagleShot:
             case gtSniperRifleShot:iInit = Gear->Health * 4;
                                    break;
             default: break;}
            {i = iInit;
             LongWord i__end__ = 0;
             if (i >= i__end__) do {
                                       if(fpcrtl_random(6) == 0)
                                       {
                                           uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtBubble);
                                       }
                                       Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, Gear->dX);
                                       Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, Gear->dY);
                                   } while(i-- != i__end__);}
        }
        Gear->Health = 0;
    }
};
void ugearshandlersmess_doStepBulletWork(PGear Gear)
{
    LongWord i;
    LongWord x;
    LongWord y;
    LongWord iInit;
    hwFloat oX;
    hwFloat oY;
    hwFloat tX;
    hwFloat tY;
    hwFloat tDx;
    hwFloat tDy;
    PVisualGear VGear;
    Word LandFlags;
    boolean isDigging;
    boolean isDead;
    AllInactive = false;
    ++Gear->Timer;
    iInit = 100;
    i = iInit;
    isDigging = false;
    isDead = false;
    oX = Gear->X;
    oY = Gear->Y;
    do {
           Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, Gear->dX);
           Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, Gear->dY);
           tX = Gear->X;
           tY = Gear->Y;
           tDx = Gear->dX;
           tDy = Gear->dY;
           if((Gear->PortalCounter < 30) && ugearsutils_WorldWrap(&(Gear)))
           {
               ugearshandlersmess_LineShoveHelp(Gear, oX, oY, tX, tY, tDx, tDy, (iInit + 2) - i);
               ugearshandlersmess_spawnBulletTrail(Gear, tX, tY, Gear->FlightTime == 0);
               Gear->FlightTime = 1;
               iInit = i;
               oX = Gear->X;
               oY = Gear->Y;
               ++Gear->PortalCounter;
               Gear->Elasticity = Gear->X;
               Gear->Friction = Gear->Y;
               ugearshandlersmess_spawnBulletTrail(Gear, Gear->X, Gear->Y, false);
               if(WorldEdge != weSea)
               {
                   Gear->Data = NULL;
               }
           }
           x = ufloat_hwRound(Gear->X);
           y = ufloat_hwRound(Gear->Y);
           if(((y & LAND_HEIGHT_MASK) == 0) && ((x & LAND_WIDTH_MASK) == 0))
           {
               LandFlags = ulandutils_LandGet(y, x);
               if(LandFlags != 0)
               {
                   ++Gear->Damage;
               }
               isDigging = (LandFlags & lfLandMask) != 0;
           }
           if(isDigging && (Gear->Tag == 0))
           {
               Gear->Tag = 1;
               --Gear->Damage;
               Gear->X = ufloat_hwFloat_hwFloat_op_sub(Gear->X, Gear->dX);
               Gear->Y = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, Gear->dY);
               ugearshandlersmess_CheckBulletDrowningHelp(Gear);
               break;
           }
           else
           {
               if(!isDigging)
               {
                   Gear->Tag = 0;
               }
           }
           if((!isDigging && (Gear->Damage > 5)) && (Gear->Kind != gtMinigunBullet))
           {
               ugearshandlersmess_LineShoveHelp(Gear, oX, oY, tX, tY, tDx, tDy, (iInit + 2) - i);
               ugearshandlersmess_spawnBulletTrail(Gear, tX, tY, Gear->FlightTime == 0);
               Gear->FlightTime = 1;
               iInit = i;
               oX = Gear->X;
               oY = Gear->Y;
           }
           ugearshandlersmess_CheckBulletDrowningHelp(Gear);
           switch(Gear->Kind)
           {case gtMinigunBullet:isDead = isDigging || ((Gear->State & gstDrowning) != 0);
                                 break;
            case gtDEagleShot:
            case gtSniperRifleShot:isDead = (Gear->Damage >= Gear->Health) || ((Gear->State & gstDrowning) != 0);
                                   break;
            default: break;}
           --i;
       } while(!((i == 0) || isDead));
    ugearshandlersmess_LineShoveHelp(Gear, oX, oY, Gear->X, Gear->Y, Gear->dX, Gear->dY, (iInit + 2) - i);
    ugearshandlersmess_CreateBubblesForBullet(Gear);
    x = ufloat_hwRound(Gear->X);
    y = ufloat_hwRound(Gear->Y);
    if((isDead || ((x & LAND_WIDTH_MASK) != 0)) || ((y & LAND_HEIGHT_MASK) != 0))
    {
        if(Gear->Kind == gtSniperRifleShot)
        {
            cLaserSightingSniper = false;
        }
        if((Ammoz[Gear->AmmoType].Ammo.NumPerTurn <= CurrentHedgehog->MultiShootAttacks) && (CurrentHedgehog->Effects[heArtillery] == 2))
        {
            CurrentHedgehog->Effects[heArtillery] = 0;
        }
        if((((Gear->State & gstDrowning) == 0) && ((x & LAND_WIDTH_MASK) == 0)) && ((y & LAND_HEIGHT_MASK) == 0))
        {
            if(Gear->Kind == gtMinigunBullet)
            {
                ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Karma, Gear->Hedgehog, EXPLNoDamage | EXPLDoNotTouchHH);
                VGear = uvisualgearslist_AddVisualGear_3(ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(Gear->X, ufloat_hwFloat_LongInt_op_mul(Gear->dX, 5))), ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(Gear->Y, ufloat_hwFloat_LongInt_op_mul(Gear->dY, 5))), vgtBulletHit);
            }
            else
            {
                VGear = uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtBulletHit);
            }
            if(VGear != NULL)
            {
                VGear->Angle = uutils_DxDy2Angle(ufloat_hwFloat_op_sub(Gear->dX), Gear->dY);
            }
        }
        ugearshandlersmess_spawnBulletTrail(Gear, Gear->X, Gear->Y, Gear->FlightTime == 0);
        Gear->FlightTime = 1;
        if(Gear->Kind == gtMinigunBullet)
        {
            ucollisions_ClearHitOrderLeq(Gear->Tag);
        }
        if((((((WorldEdge == weSea) && (Gear->Kind == gtMinigunBullet)) && Gear->Y.isNegative) && Gear->dY.isNegative) && (Gear->Health > 0)) && !ufloat_isZero(Gear->dX))
        {
            if(Gear->dX.isNegative)
            {
                Gear->X = ufloat_int2hwFloat(-1);
                iInit = x - leftX;
            }
            else
            {
                Gear->X = ufloat_int2hwFloat(LAND_WIDTH);
                iInit = (rightX - x) - 1;
            }
            Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, ufloat_hwFloat_hwFloat_op_mul(Gear->dY, ufloat_hwAbs(ufloat_hwFloat_hwFloat_op_div(ufloat_int2hwFloat(iInit), Gear->dX))));
            ugearsutils_CheckGearDrowning(&(Gear));
            ugearshandlersmess_CreateBubblesForBullet(Gear);
        }
        Gear->doStep = &(ugearshandlersmess_doStepShotIdle);
    }
};
void ugearshandlersmess_doStepDEagleShot(PGear Gear)
{
    if(Gear->Data == NULL)
    {
        if((Gear->Hedgehog != NULL) && ((*Gear->Hedgehog).Gear != NULL))
        {
            Gear->Data = ((pointer)(*Gear->Hedgehog).Gear);
        }
    }
    usound_PlaySound_1(sndGun);
    ucollisions_ClearHitOrder();
    Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, ufloat_hwFloat_LongInt_op_mul(Gear->dX, 2));
    Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, ufloat_hwFloat_LongInt_op_mul(Gear->dY, 2));
    Gear->FlightTime = 0;
    Gear->doStep = &(ugearshandlersmess_doStepBulletWork);
};
void ugearshandlersmess_doStepSniperRifleShot(PGear Gear)
{
    PGear HHGear;
    HHGear = (*Gear->Hedgehog).Gear;
    if((*Gear->Hedgehog).Effects[heArtillery] != 1)
    {
        (*Gear->Hedgehog).Effects[heArtillery] = 2;
    }
    if(HHGear == NULL)
    {
        ugearslist_DeleteGear(Gear);
        return;
    }
    Gear->Data = ((pointer)(*Gear->Hedgehog).Gear);
    HHGear->State = HHGear->State | gstNotKickable;
    ugearshedgehog_HedgehogChAngle(HHGear);
    if(cLaserSightingSniper == false)
    {
        cLaserSightingSniper = true;
        HHGear->Message = 0;
        if(HHGear->Angle >= 32)
        {
            HHGear->Angle -= 32;
        }
    }
    if((HHGear->Message & gmAttack) != 0)
    {
        ugearshandlersmess_CreateShellForGear(Gear, 1);
        Gear->State = Gear->State | gstAnimation;
        Gear->dX = ufloat_hwFloat_hwFloat_op_mul(ufloat_SignAs(ufloat_AngleSin(HHGear->Angle), HHGear->dX), _0_5);
        Gear->dY = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_op_sub(ufloat_AngleCos(HHGear->Angle)), _0_5);
        usound_PlaySound_1(sndGun);
        ucollisions_ClearHitOrder();
        Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, ufloat_hwFloat_LongInt_op_mul(Gear->dX, 2));
        Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, ufloat_hwFloat_LongInt_op_mul(Gear->dY, 2));
        Gear->FlightTime = 0;
        Gear->doStep = &(ugearshandlersmess_doStepBulletWork);
    }
    else
    {
        if((GameTicks % 32) == 0)
        {
            if((GameTicks % 4096) < 2048)
            {
                if((HHGear->Angle + 1) <= cMaxAngle)
                {
                    ++HHGear->Angle;
                }
            }
            else
            {
                if(HHGear->Angle >= 1)
                {
                    --HHGear->Angle;
                }
            }
        }
    }
    if(TurnTimeLeft == 0)
    {
        HHGear->State = HHGear->State & ~gstNotKickable;
        ugearslist_DeleteGear(Gear);
        ugearshedgehog_AfterAttack();
    }
};
void ugearshandlersmess_doStepActionTimer(PGear Gear)
{
    --Gear->Timer;
    switch(Gear->Kind)
    {case gtATStartGame:{
                            AllInactive = false;
                            if(Gear->Timer == 0)
                            {
                                ucaptions_AddCaption(ulocale_GetEventString(eidRoundStart), capcolDefault, capgrpGameState);
                            }
                        }
                        break;
     case gtATFinishGame:{
                             AllInactive = false;
                             if(Gear->Timer == 1000)
                             {
                                 ScreenFade = sfToBlack;
                                 ScreenFadeValue = 0;
                                 ScreenFadeSpeed = 1;
                             }
                             if(Gear->Timer == 0)
                             {
                                 uio_SendIPC(__str1);
                                 if(LuaCmdUsed)
                                 {
                                     uio_SendIPC(__str2);
                                 }
                                 uio_SendIPC(__str3);
                                 GameState = gsExit;
                             }
                         }
                         break;
     default: break;}
    if(Gear->Timer == 0)
    {
        ugearslist_DeleteGear(Gear);
    }
};
void ugearshandlersmess_doStepPickHammerWork(PGear Gear)
{
    LongInt i;
    LongInt ei;
    LongInt x;
    LongInt y;
    PGear HHGear;
    AllInactive = false;
    ugearsutils_WorldWrap(&(Gear));
    HHGear = (*Gear->Hedgehog).Gear;
    --Gear->Timer;
    if((((TurnTimeLeft == 0) || (Gear->Timer == 0)) || ((Gear->Message & gmDestroy) != 0)) || ((HHGear->State & gstHHDriven) == 0))
    {
        usound_StopSoundChan_1(Gear->SoundChannel);
        ugearslist_DeleteGear(Gear);
        ugearshedgehog_AfterAttack();
        ugearshedgehog_doStepHedgehogMoving(HHGear);
        return;
    }
    x = ufloat_hwRound(Gear->X);
    y = ufloat_hwRound(Gear->Y);
    if((Gear->Timer % 33) == 0)
    {
        HHGear->State = HHGear->State | gstNoDamage;
        ugearsutils_doMakeExplosion_5(x, y + 7, Gear->Boom, Gear->Hedgehog, EXPLDontDraw);
        HHGear->State = HHGear->State & ~gstNoDamage;
    }
    if((Gear->Timer % 47) == 0)
    {
        if(((((y + 12) & LAND_HEIGHT_MASK) == 0) && ((x & LAND_WIDTH_MASK) == 0)) && (ulandutils_LandGet(y + 12, x) > 255))
        {
            {i = 0;
             LongInt i__end__ = 1;
             if (i <= i__end__) do {
                                       uvisualgearslist_AddVisualGear_3((x - 5) + fpcrtl_random(10), y + 12, vgtDust);
                                   } while(i++ != i__end__);}
        }
        i = (x - Gear->Radius) - ((LongInt)urandom_GetRandom(2));
        ei = (x + Gear->Radius) + ((LongInt)urandom_GetRandom(2));
        while(i <= ei)
        {
            ugearsutils_doMakeExplosion_5(i, y + 3, 3, Gear->Hedgehog, ((EXPLNoDamage | EXPLDoNotTouchAny) | EXPLNoGfx) | EXPLForceDraw);
            i += 1;
        }
        if(ulandgraphics_CheckLandValue(ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_add(Gear->X, Gear->dX), ufloat_SignAs(_6, Gear->dX))), ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(Gear->Y, _1_9)), lfIndestructible))
        {
            Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, Gear->dX);
            Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _1_9);
        }
        ugearsutils_SetAllHHToActive_0();
    }
    if(ucollisions_TestCollisionYwithGear(Gear, 1) != 0)
    {
        Gear->dY = _0;
        uutils_SetLittle(&(HHGear->dX));
        HHGear->dY = _0;
    }
    else
    {
        if(Gear->dY.isNegative && (ucollisions_TestCollisionYwithGear(HHGear, -1) != 0))
        {
            Gear->dY = cGravity;
            HHGear->dY = cGravity;
        }
        else
        {
            if(ulandgraphics_CheckLandValue(ufloat_hwRound(Gear->X), ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_add(Gear->Y, Gear->dY), cGravity)), lfLandMask))
            {
                Gear->dY = ufloat_hwFloat_hwFloat_op_add(Gear->dY, cGravity);
                Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, Gear->dY);
            }
            if(ufloat_hwRound(Gear->Y) > cWaterLine)
            {
                Gear->Timer = 1;
            }
        }
    }
    Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, HHGear->dX);
    if(ulandgraphics_CheckLandValue(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y) - cHHRadius, lfLandMask))
    {
        HHGear->X = Gear->X;
        HHGear->Y = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, ufloat_int2hwFloat(cHHRadius));
    }
    if((Gear->Message & gmAttack) != 0)
    {
        if((Gear->State & gsttmpFlag) != 0)
        {
            Gear->Timer = 1;
        }
        else
        {
            ;
        }
    }
    else
    {
        if((Gear->State & gsttmpFlag) == 0)
        {
            Gear->State = Gear->State | gsttmpFlag;
        }
    }
    if((Gear->Message & gmLeft) != 0)
    {
        Gear->dX = ufloat_hwFloat_op_sub(_0_3);
    }
    else
    {
        if((Gear->Message & gmRight) != 0)
        {
            Gear->dX = _0_3;
        }
        else
        {
            Gear->dX = _0;
        }
    }
};
void ugearshandlersmess_doStepPickHammer(PGear Gear)
{
    LongInt i;
    LongInt y;
    TRangeArray ar;
    PGear HHGear;
    i = 0;
    HHGear = (*Gear->Hedgehog).Gear;
    y = ufloat_hwRound(Gear->Y) - (cHHRadius * 2);
    while(y < ufloat_hwRound(Gear->Y))
    {
        ar[i].Left = (ufloat_hwRound(Gear->X) - Gear->Radius) - ((LongInt)urandom_GetRandom(2));
        ar[i].Right = (ufloat_hwRound(Gear->X) + Gear->Radius) + ((LongInt)urandom_GetRandom(2));
        y += 2;
        ++i;
    }
    ulandgraphics_DrawHLinesExplosions(&(ar), 3, ufloat_hwRound(Gear->Y) - (cHHRadius * 2), 2, ((int)(i) - 1));
    Gear->dY = HHGear->dY;
    ucollisions_DeleteCI(HHGear);
    Gear->SoundChannel = usound_LoopSound_1(sndPickhammer);
    ugearshandlersmess_doStepPickHammerWork(Gear);
    Gear->doStep = &(ugearshandlersmess_doStepPickHammerWork);
};
static LongInt BTPrevAngle;
static LongInt BTSteps;
void ugearshandlersmess_doStepBlowTorchWork(PGear Gear)
{
    PGear HHGear;
    boolean dig;
    boolean hit;
    hwFloat newX;
    hwFloat newY;
    AllInactive = false;
    ugearsutils_WorldWrap(&(Gear));
    --Gear->Timer;
    if((*Gear->Hedgehog).Gear == NULL)
    {
        ucollisions_ClearProximityCache();
        usound_StopSoundChan_1(Gear->SoundChannel);
        ugearslist_DeleteGear(Gear);
        ugearshedgehog_AfterAttack();
        return;
    }
    HHGear = (*Gear->Hedgehog).Gear;
    ugearshedgehog_HedgehogChAngle(HHGear);
    dig = false;
    hit = false;
    if(fpcrtl_abs(((LongInt)HHGear->Angle) - BTPrevAngle) > 7)
    {
        Gear->dX = ufloat_SignAs(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleSin(HHGear->Angle), _0_5), Gear->dX);
        Gear->dY = ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleCos(HHGear->Angle), ufloat_hwFloat_op_sub(_0_5));
        BTPrevAngle = HHGear->Angle;
        dig = true;
    }
    if((HHGear->State & gstMoving) != 0)
    {
        ugearshedgehog_doStepHedgehogMoving(HHGear);
        if((HHGear->State & gstHHDriven) == 0)
        {
            Gear->Timer = 0;
        }
    }
    if((Gear->Timer % 1500) == 0)
    {
        ucollisions_RefillProximityCache(Gear, 200);
    }
    if((Gear->Timer % cHHStepTicks) == 0)
    {
        dig = true;
        if(Gear->dX.isNegative)
        {
            HHGear->Message = (HHGear->Message & ((gmAttack | gmUp) | gmDown)) | gmLeft;
        }
        else
        {
            HHGear->Message = (HHGear->Message & ((gmAttack | gmUp) | gmDown)) | gmRight;
        }
        if((HHGear->State & gstMoving) == 0)
        {
            HHGear->State = HHGear->State & ~gstAttacking;
            if(ulandgraphics_CheckLandValue(ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(HHGear->X, ufloat_SignAs(_6, HHGear->dX))), ufloat_hwRound(HHGear->Y), lfIndestructible))
            {
                ugearshedgehog_HedgehogStep(HHGear);
            }
            HHGear->State = HHGear->State | gstAttacking;
        }
        newX = ufloat_hwFloat_hwFloat_op_add(HHGear->X, ufloat_hwFloat_LongInt_op_mul(Gear->dX, cHHRadius + cBlowTorchC));
        newY = ufloat_hwFloat_hwFloat_op_add(HHGear->Y, ufloat_hwFloat_LongInt_op_mul(Gear->dY, cHHRadius + cBlowTorchC));
        if(ulandgraphics_CheckLandValue(ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(newX, ufloat_SignAs(_6, Gear->dX))), ufloat_hwRound(newY), lfIndestructible))
        {
            Gear->X = newX;
            Gear->Y = newY;
        }
        ++BTSteps;
        if(BTSteps == 11)
        {
            BTSteps = 0;
            hit = true;
        }
    }
    if(dig)
    {
        ulandgraphics_DrawTunnel(ufloat_hwFloat_hwFloat_op_add(HHGear->X, ufloat_hwFloat_LongInt_op_mul(Gear->dX, cHHRadius)), ufloat_hwFloat_hwFloat_op_sub(ufloat_hwFloat_hwFloat_op_sub(ufloat_hwFloat_hwFloat_op_add(HHGear->Y, ufloat_hwFloat_LongInt_op_mul(Gear->dY, cHHRadius)), _1), ufloat_hwFloat_LongInt_op_mul(ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_div(ufloat_hwAbs(Gear->dX), ufloat_hwFloat_hwFloat_op_add(ufloat_hwAbs(Gear->dX), ufloat_hwAbs(Gear->dY))), _0_5), 7)), Gear->dX, Gear->dY, cHHStepTicks, (cHHRadius * 2) + 7);
        HHGear->State = HHGear->State | gstNoDamage;
        if(hit)
        {
            ugearsutils_AmmoShoveCache(Gear, Gear->Boom, 15);
        }
        else
        {
            ugearsutils_AmmoShoveCache(Gear, 0, 15);
        }
        HHGear->State = HHGear->State & ~gstNoDamage;
    }
    if(((TurnTimeLeft == 0) || (Gear->Timer == 0)) || ((HHGear->Message & gmAttack) != 0))
    {
        ucollisions_ClearProximityCache();
        usound_StopSoundChan_1(Gear->SoundChannel);
        HHGear->Message = 0;
        HHGear->State = HHGear->State & ~gstNotKickable;
        ugearslist_DeleteGear(Gear);
        ugearshedgehog_AfterAttack();
    }
};
void ugearshandlersmess_doStepBlowTorch(PGear Gear)
{
    PGear HHGear;
    BTPrevAngle = 2147483647;
    BTSteps = 0;
    HHGear = (*Gear->Hedgehog).Gear;
    ugearshedgehog_HedgehogChAngle(HHGear);
    Gear->dX = ufloat_SignAs(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleSin(HHGear->Angle), _0_5), Gear->dX);
    Gear->dY = ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleCos(HHGear->Angle), ufloat_hwFloat_op_sub(_0_5));
    ulandgraphics_DrawTunnel(HHGear->X, ufloat_hwFloat_hwFloat_op_sub(ufloat_hwFloat_hwFloat_op_sub(ufloat_hwFloat_hwFloat_op_add(HHGear->Y, ufloat_hwFloat_LongInt_op_mul(Gear->dY, cHHRadius)), _1), ufloat_hwFloat_LongInt_op_mul(ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_div(ufloat_hwAbs(Gear->dX), ufloat_hwFloat_hwFloat_op_add(ufloat_hwAbs(Gear->dX), ufloat_hwAbs(Gear->dY))), _0_5), 7)), Gear->dX, Gear->dY, cHHStepTicks, (cHHRadius * 2) + 7);
    HHGear->Message = 0;
    HHGear->State = HHGear->State | gstNotKickable;
    ucollisions_RefillProximityCache(Gear, 200);
    Gear->SoundChannel = usound_LoopSound_1(sndBlowTorch);
    Gear->doStep = &(ugearshandlersmess_doStepBlowTorchWork);
};
void ugearshandlersmess_doStepMine(PGear Gear)
{
    PVisualGear vg;
    hwFloat dxdy;
    LongWord dmg;
    if(Gear->Health == 0)
    {
        dxdy = ufloat_hwFloat_hwFloat_op_add(ufloat_hwAbs(Gear->dX), ufloat_hwAbs(Gear->dY));
    }
    Gear->RenderTimer = (((Gear->State & gstFrozen) == 0) && ((Gear->State & gstAttacking) == 0)) && (Gear->Health != 0);
    if((Gear->State & gstMoving) != 0)
    {
        ucollisions_DeleteCI(Gear);
        ugearshandlersmess_doStepFallingGear(Gear);
        if((Gear->State & gstMoving) == 0)
        {
            ucollisions_AddCI(Gear);
            Gear->dX = _0;
            Gear->dY = _0;
        }
        ugearsutils_CalcRotationDirAngle(Gear);
        AllInactive = false;
    }
    else
    {
        if((GameTicks & 0x3f) == 25)
        {
            ugearshandlersmess_doStepFallingGear(Gear);
        }
    }
    if(Gear->Health == 0)
    {
        if((ufloat_hwFloat_hwFloat_op_gt(dxdy, _0_4)) && ((Gear->State & gstCollision) != 0))
        {
            dmg = ufloat_hwRound(ufloat_hwFloat_hwFloat_op_mul(dxdy, _50));
            Gear->Damage += dmg;
            uscript_ScriptCall_3(__str4, Gear->uid, dmg);
        }
        if(((GameTicks & 0xff) == 0) && (Gear->Damage > fpcrtl_random(30)))
        {
            vg = uvisualgearslist_AddVisualGear_3((ufloat_hwRound(Gear->X) - 4) + fpcrtl_random(8), (ufloat_hwRound(Gear->Y) - 4) - fpcrtl_random(4), vgtSmoke);
            if(vg != NULL)
            {
                vg->scale = 0.5;
            }
        }
        if(Gear->Damage > 35)
        {
            ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
            ugearslist_DeleteGear(Gear);
            return;
        }
    }
    if(((Gear->State & gsttmpFlag) != 0) && (Gear->Health != 0))
    {
        if((Gear->State & gstAttacking) == 0)
        {
            if((GameTicks & 0x1f) == 0)
            {
                if(ugearsutils_CheckGearNear_4(Gear, gtHedgehog, 46, 32) != NULL)
                {
                    Gear->State = Gear->State | gstAttacking;
                }
            }
        }
        else
        {
            AllInactive = false;
            if((Gear->Tag == 1) && (Gear->Timer == 0))
            {
                if((GameTicks % 2) == 0)
                {
                    urandom_GetRandom(2);
                }
                if((GameTicks % 3) == 0)
                {
                    urandom_GetRandom(2);
                }
                Gear->Timer = urandom_GetRandom(51) * 100;
                Gear->Tag = 0;
            }
            if((Gear->Timer & 0xff) == 0)
            {
                usound_PlaySound_1(sndMineTick);
            }
            if(Gear->Timer == 0)
            {
                if((((Gear->State & gstWait) != 0) || (cMineDudPercent == 0)) || (urandom_GetRandom(100) > cMineDudPercent))
                {
                    ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
                    ugearslist_DeleteGear(Gear);
                    return;
                }
                else
                {
                    vg = uvisualgearslist_AddVisualGear_3((ufloat_hwRound(Gear->X) - 4) + fpcrtl_random(8), (ufloat_hwRound(Gear->Y) - 4) - fpcrtl_random(4), vgtSmoke);
                    if(vg != NULL)
                    {
                        vg->scale = 0.5;
                    }
                    usound_PlaySound_1(sndVaporize);
                    Gear->Health = 0;
                    Gear->Damage = 0;
                    Gear->State = Gear->State & ~gstAttacking;
                }
                return;
            }
            --Gear->Timer;
        }
    }
    else
    {
        if(((TurnTimeLeft == 0) || (((GameFlags & gfInfAttack) != 0) && (GameTicks > Gear->FlightTime))) || ((*Gear->Hedgehog).Gear == NULL))
        {
            Gear->State = Gear->State | gsttmpFlag;
        }
    }
};
void ugearshandlersmess_doStepAirMine(PGear Gear)
{
    LongWord i;
    LongWord t;
    LongWord targDist;
    LongWord tmpDist;
    PGear targ;
    PGear tmpG;
    hwFloat trackSpeed;
    hwFloat airFriction;
    hwFloat tX;
    hwFloat tY;
    boolean isUnderwater;
    PVisualGear sparkle;
    targ = NULL;
    Gear->RenderTimer = ((Gear->State & gstFrozen) == 0) && ((Gear->State & gstAttacking) == 0);
    if((Gear->State & gstFrozen) != 0)
    {
        if(Gear->Damage > 0)
        {
            ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
            if((Gear->State & gstNoGravity) != 0)
            {
                ulandgraphics_EraseLand(ufloat_hwRound(Gear->X) - (SpritesData[sprFrozenAirMine].Width / 2), ufloat_hwRound(Gear->Y) - (SpritesData[sprFrozenAirMine].Height / 2), sprFrozenAirMine, 0, 0, false, false, false, false);
            }
            ugearslist_DeleteGear(Gear);
            return;
        }
        if(((Gear->dX.QWordValue + Gear->dY.QWordValue) > _0_02.QWordValue) || ((GameTicks & 0x3f) == 15))
        {
            ugearshandlersmess_doStepFallingGear(Gear);
        }
        return;
    }
    isUnderwater = ucollisions_CheckCoordInWater(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y) + Gear->Radius);
    if(Gear->Pos > 0)
    {
        airFriction = _1;
        if(isUnderwater)
        {
            airFriction.QWordValue -= Gear->Pos * 2;
        }
        else
        {
            airFriction.QWordValue -= Gear->Pos;
        }
        Gear->dX = ufloat_hwFloat_hwFloat_op_mul(Gear->dX, airFriction);
        Gear->dY = ufloat_hwFloat_hwFloat_op_mul(Gear->dY, airFriction);
    }
    if(((Gear->dX.QWordValue + Gear->dY.QWordValue) > _0_02.QWordValue) || ((GameTicks & 0x3f) == 15))
    {
        ugearshandlersmess_doStepFallingGear(Gear);
    }
    if((TurnTimeLeft == 0) && ((Gear->dX.QWordValue + Gear->dY.QWordValue) > _0_02.QWordValue))
    {
        AllInactive = false;
    }
    if((Gear->State & gsttmpFlag) == 0)
    {
        if(((TurnTimeLeft == 0) || (((GameFlags & gfInfAttack) != 0) && (GameTicks > Gear->FlightTime))) || (CurrentHedgehog->Gear == NULL))
        {
            Gear->FlightTime = GameTicks;
            Gear->State = Gear->State | gsttmpFlag;
            Gear->Hedgehog = NULL;
        }
        return;
    }
    if(Gear->Tag != 0)
    {
        if((Gear->FlightTime & 0xff) == 0)
        {
            if(ucollisions_CheckCoordInWater(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y)) == false)
            {
                sparkle = uvisualgearslist_AddVisualGear_4(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtDust, 1);
                if(sparkle != NULL)
                {
                    sparkle->dX = 4.0e-3 * (fpcrtl_random(100) - 50);
                    sparkle->dY = -5.0e-2 + (4.0e-3 * (fpcrtl_random(100) - 50));
                    sparkle->Tint = 0xd5cd8cff;
                    sparkle->Angle = fpcrtl_random(360);
                }
            }
            else
            {
                uvisualgearslist_AddVisualGear_3((ufloat_hwRound(Gear->X) - 8) + fpcrtl_random(16), (ufloat_hwRound(Gear->Y) + 16) + fpcrtl_random(8), vgtBubble);
            }
        }
        --Gear->FlightTime;
        if(Gear->FlightTime == 0)
        {
            Gear->Tag = 0;
            Gear->Hedgehog = NULL;
            Gear->State = Gear->State & ~gstAttacking;
            Gear->Timer = Gear->WDTimer;
        }
        return;
    }
    if((((TurnTimeLeft == 0) || (Gear->Angle == 0)) || (Gear->Hedgehog == NULL)) || ((*Gear->Hedgehog).Gear == NULL))
    {
        Gear->Hedgehog = NULL;
        targ = NULL;
    }
    else
    {
        if(Gear->Hedgehog != NULL)
        {
            targ = (*Gear->Hedgehog).Gear;
        }
    }
    if(targ != NULL)
    {
        tX = ufloat_hwFloat_hwFloat_op_sub(Gear->X, targ->X);
        tY = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, targ->Y);
        if((GameTicks > (Gear->FlightTime + 10000)) || !(((tX.Round + tY.Round) < (Gear->Angle * 9)) && (ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ufloat_hwSqr(tX), ufloat_hwSqr(tY))) < fpcrtl_sqr(Gear->Angle * 6))))
        {
            targ = NULL;
        }
    }
    if((((ReadyTimeLeft > 0) || (TurnTimeLeft == 0)) || ((TurnTimeLeft < cHedgehogTurnTime) && ((((int64_t) (cHedgehogTurnTime)) - ((int64_t) (TurnTimeLeft))) < 5000))) || (Gear->Angle == 0))
    {
        Gear->State = Gear->State & ~gstChooseTarget;
    }
    else
    {
        if((((Gear->State & gstAttacking) == 0) && ((GameTicks & 0xff) == 17)) && (GameTicks > Gear->FlightTime))
        {
            Gear->State = Gear->State | gstChooseTarget;
            if(targ != NULL)
            {
                targDist = ufloat_Distance(ufloat_hwFloat_hwFloat_op_sub(Gear->X, targ->X), ufloat_hwFloat_hwFloat_op_sub(Gear->Y, targ->Y)).Round;
            }
            else
            {
                targDist = 0;
            }
            {t = 0;
             LongWord t__end__ = ((int)(TeamsCount) - 1);
             if (t <= t__end__) do {
                                       {
                                           {i = 0;
                                            LongWord i__end__ = cMaxHHIndex;
                                            if (i <= i__end__) do {
                                                                      if(((!(*TeamsArray[t]).Hedgehogs[i].Unplaced && ((*TeamsArray[t]).Hedgehogs[i].Gear != NULL)) && ((*TeamsArray[t]).Hedgehogs[i].Effects[heFrozen] == 0)) && (((*(*TeamsArray[t]).Hedgehogs[i].Gear).State & gstInvisible) == 0))
                                                                      {
                                                                          tmpG = (*TeamsArray[t]).Hedgehogs[i].Gear;
                                                                          tX = ufloat_hwFloat_hwFloat_op_sub(Gear->X, tmpG->X);
                                                                          tY = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, tmpG->Y);
                                                                          if((Gear->Angle == 0xffffffff) || (((tX.Round + tY.Round) < Gear->Angle) && (ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ufloat_hwSqr(tX), ufloat_hwSqr(tY))) < fpcrtl_sqr(Gear->Angle))))
                                                                          {
                                                                              if(targ != NULL)
                                                                              {
                                                                                  tmpDist = ufloat_Distance(tX, tY).Round;
                                                                              }
                                                                              if((targ == NULL) || (tmpDist < targDist))
                                                                              {
                                                                                  if(targ == NULL)
                                                                                  {
                                                                                      targDist = ufloat_Distance(tX, tY).Round;
                                                                                  }
                                                                                  else
                                                                                  {
                                                                                      targDist = tmpDist;
                                                                                  }
                                                                                  Gear->Hedgehog = &((*TeamsArray[t]).Hedgehogs[i]);
                                                                                  targ = tmpG;
                                                                              }
                                                                          }
                                                                      }
                                                                  } while(i++ != i__end__);}
                                       }
                                   } while(t++ != t__end__);}
            if(targ != NULL)
            {
                Gear->FlightTime = GameTicks + 5000;
            }
        }
    }
    if(targ != NULL)
    {
        trackSpeed = _0;
        if(isUnderwater)
        {
            trackSpeed.QWordValue = Gear->Power / 2;
        }
        else
        {
            trackSpeed.QWordValue = Gear->Power;
        }
        if((ufloat_hwFloat_hwFloat_op_lt(Gear->X, targ->X)) && (ufloat_hwFloat_hwFloat_op_lt(Gear->dX, _0_1)))
        {
            if((WorldEdge == weWrap) && (ufloat_hwFloat_hwFloat_op_gt(ufloat_hwFloat_hwFloat_op_sub(targ->X, Gear->X), ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_sub(Gear->X, ufloat_int2hwFloat(leftX)), ufloat_hwFloat_hwFloat_op_sub(ufloat_int2hwFloat(rightX), targ->X)))))
            {
                Gear->dX = ufloat_hwFloat_hwFloat_op_sub(Gear->dX, trackSpeed);
            }
            else
            {
                Gear->dX = ufloat_hwFloat_hwFloat_op_add(Gear->dX, trackSpeed);
            }
        }
        else
        {
            if((ufloat_hwFloat_hwFloat_op_gt(Gear->X, targ->X)) && (ufloat_hwFloat_hwFloat_op_gt(Gear->dX, ufloat_hwFloat_op_sub(_0_1))))
            {
                if((WorldEdge == weWrap) && (ufloat_hwFloat_hwFloat_op_gt(ufloat_hwFloat_hwFloat_op_sub(Gear->X, targ->X), ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_sub(targ->X, ufloat_int2hwFloat(leftX)), ufloat_hwFloat_hwFloat_op_sub(ufloat_int2hwFloat(rightX), Gear->X)))))
                {
                    Gear->dX = ufloat_hwFloat_hwFloat_op_add(Gear->dX, trackSpeed);
                }
                else
                {
                    Gear->dX = ufloat_hwFloat_hwFloat_op_sub(Gear->dX, trackSpeed);
                }
            }
        }
        if((ufloat_hwFloat_hwFloat_op_lt(Gear->Y, targ->Y)) && (ufloat_hwFloat_hwFloat_op_lt(Gear->dY, _0_1)))
        {
            Gear->dY = ufloat_hwFloat_hwFloat_op_add(Gear->dY, trackSpeed);
        }
        else
        {
            if((ufloat_hwFloat_hwFloat_op_gt(Gear->Y, targ->Y)) && (ufloat_hwFloat_hwFloat_op_gt(Gear->dY, ufloat_hwFloat_op_sub(_0_1))))
            {
                Gear->dY = ufloat_hwFloat_hwFloat_op_sub(Gear->dY, trackSpeed);
            }
        }
    }
    else
    {
        Gear->Hedgehog = NULL;
    }
    if((Gear->State & gstAttacking) == 0)
    {
        if(((GameTicks + Gear->uid) & 0x1f) == 0)
        {
            if(targ != NULL)
            {
                tX = ufloat_hwFloat_hwFloat_op_sub(Gear->X, targ->X);
                tY = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, targ->Y);
                if(((tX.Round + tY.Round) < Gear->Boom) && (ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ufloat_hwSqr(tX), ufloat_hwSqr(tY))) < fpcrtl_sqr(Gear->Boom)))
                {
                    Gear->State = Gear->State | gstAttacking;
                }
            }
            else
            {
                if((Gear->Angle > 0) && (ugearsutils_CheckGearNear_4(Gear, gtHedgehog, Gear->Boom, Gear->Boom) != NULL))
                {
                    Gear->State = Gear->State | gstAttacking;
                }
            }
        }
    }
    else
    {
        AllInactive = false;
        if((Gear->Timer & 0xff) == 0)
        {
            usound_PlaySound_1(sndMineTick);
        }
        if(Gear->Timer == 0)
        {
            if(targ != NULL)
            {
                tX = ufloat_hwFloat_hwFloat_op_sub(Gear->X, targ->X);
                tY = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, targ->Y);
                if(((tX.Round + tY.Round) < Gear->Boom) && (ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ufloat_hwSqr(tX), ufloat_hwSqr(tY))) < fpcrtl_sqr(Gear->Boom)))
                {
                    Gear->Hedgehog = CurrentHedgehog;
                    tmpG = FollowGear;
                    ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
                    FollowGear = tmpG;
                    ugearslist_DeleteGear(Gear);
                    return;
                }
            }
            else
            {
                if((Gear->Angle > 0) && (ugearsutils_CheckGearNear_4(Gear, gtHedgehog, Gear->Boom, Gear->Boom) != NULL))
                {
                    Gear->Hedgehog = CurrentHedgehog;
                    ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
                    ugearslist_DeleteGear(Gear);
                    return;
                }
            }
            Gear->State = Gear->State & ~gstAttacking;
            Gear->Timer = Gear->WDTimer;
        }
        if(Gear->Timer > 0)
        {
            --Gear->Timer;
        }
    }
};
void ugearshandlersmess_doStepSMine(PGear Gear)
{
    Word land;
    land = ucollisions_TestCollisionXwithGear(Gear, 2);
    if(land == 0)
    {
        land = ucollisions_TestCollisionYwithGear(Gear, -2);
    }
    if(land == 0)
    {
        land = ucollisions_TestCollisionXwithGear(Gear, -2);
    }
    if(land == 0)
    {
        land = ucollisions_TestCollisionYwithGear(Gear, 2);
    }
    if((land != 0) && (((land & lfBouncy) == 0) || ((Gear->State & gstMoving) == 0)))
    {
        if((((Gear->State & gstMoving) != 0) || !ufloat_isZero(Gear->dX)) || !ufloat_isZero(Gear->dY))
        {
            usound_PlaySound_1(sndRopeAttach);
            Gear->dX = _0;
            Gear->dY = _0;
            Gear->State = Gear->State & ~gstMoving;
            ucollisions_AddCI(Gear);
        }
    }
    else
    {
        Gear->State = Gear->State | gstMoving;
        ucollisions_DeleteCI(Gear);
        ugearshandlersmess_doStepFallingGear(Gear);
        AllInactive = false;
        ugearsutils_CalcRotationDirAngle(Gear);
    }
    Gear->RenderTimer = (Gear->State & ((gstFrozen | gstAttacking) | gstDrowning)) == 0;
    if(((Gear->State & gsttmpFlag) != 0) && (Gear->Health != 0))
    {
        if(((Gear->State & gstAttacking) == 0) && ((Gear->State & gstFrozen) == 0))
        {
            if((GameTicks & 0x1f) == 0)
            {
                if(ugearsutils_CheckGearNear_4(Gear, gtHedgehog, 46, 32) != NULL)
                {
                    Gear->State = Gear->State | gstAttacking;
                }
            }
        }
        else
        {
            if((Gear->State & gstFrozen) == 0)
            {
                AllInactive = false;
                if(Gear->Timer == 0)
                {
                    ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
                    ugearslist_DeleteGear(Gear);
                    return;
                }
                else
                {
                    if((Gear->Timer & 0xff) == 0)
                    {
                        usound_PlaySound_1(sndMineTick);
                    }
                }
                --Gear->Timer;
            }
        }
    }
    else
    {
        if((((GameFlags & gfInfAttack) == 0) && ((TurnTimeLeft == 0) || ((*Gear->Hedgehog).Gear == NULL))) || (((GameFlags & gfInfAttack) != 0) && (GameTicks > Gear->FlightTime)))
        {
            Gear->State = Gear->State | gsttmpFlag;
        }
    }
};
void ugearshandlersmess_doStepDynamite(PGear Gear)
{
    ugearshandlersmess_doStepFallingGear(Gear);
    AllInactive = false;
    if((Gear->SoundChannel != -1) && ((Gear->State & gstDrowning) != 0))
    {
        usound_StopSoundChan_1(Gear->SoundChannel);
        Gear->SoundChannel = -1;
    }
    else
    {
        if(Gear->SoundChannel == -1)
        {
            Gear->SoundChannel = usound_LoopSound_1(sndDynamiteFuse);
        }
    }
    if((Gear->State & gstDrowning) != 0)
    {
        return;
    }
    if((Gear->Timer % 166) == 0)
    {
        ++Gear->Tag;
    }
    if(Gear->Timer == 1000)
    {
        ugearshandlersmess_makeHogsWorry(Gear->X, Gear->Y, 75, Gear->Kind);
    }
    if(Gear->Timer == 0)
    {
        usound_StopSoundChan_1(Gear->SoundChannel);
        ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
        ugearslist_DeleteGear(Gear);
        return;
    }
    --Gear->Timer;
};
void ugearshandlersmess_doStepRollingBarrel(PGear Gear)
{
    LongInt i;
    LongInt dmg;
    PVisualGear particle;
    hwFloat dxdy;
    if(((Gear->dX.QWordValue == 0) && (Gear->dY.QWordValue == 0)) && (ucollisions_TestCollisionYwithGear(Gear, 1) == 0))
    {
        uutils_SetLittle(&(Gear->dY));
    }
    Gear->State = Gear->State | gstAnimation;
    if(Gear->Health < cBarrelHealth)
    {
        Gear->State = Gear->State & ~gstFrozen;
    }
    if((Gear->dX.QWordValue != 0) || (Gear->dY.QWordValue != 0))
    {
        ucollisions_DeleteCI(Gear);
        AllInactive = false;
        dxdy = ufloat_hwFloat_hwFloat_op_add(ufloat_hwAbs(Gear->dX), ufloat_hwAbs(Gear->dY));
        ugearshandlersmess_doStepFallingGear(Gear);
        if(((Gear->State & gstCollision) != 0) && (ufloat_hwFloat_hwFloat_op_gt(dxdy, _0_4)))
        {
            if(ucollisions_TestCollisionYwithGear(Gear, 1) != 0)
            {
                Gear->State = Gear->State | gsttmpFlag;
                {i = uutils_Min(12, ufloat_hwRound(ufloat_hwFloat_hwFloat_op_mul(dxdy, _10)));
                 LongInt i__end__ = 0;
                 if (i >= i__end__) do {
                                           particle = uvisualgearslist_AddVisualGear_3((ufloat_hwRound(Gear->X) - 5) + fpcrtl_random(10), ufloat_hwRound(Gear->Y) + 12, vgtDust);
                                           if(particle != NULL)
                                           {
                                               particle->dX = particle->dX + (Gear->dX.QWordValue /(float) 21474836480);
                                           }
                                       } while(i-- != i__end__);}
            }
            dmg = ufloat_hwRound(ufloat_hwFloat_hwFloat_op_mul(dxdy, _50));
            Gear->Damage += dmg;
            uscript_ScriptCall_3(__str4, Gear->uid, dmg);
        }
        ugearsutils_CalcRotationDirAngle(Gear);
    }
    else
    {
        Gear->State = Gear->State | gsttmpFlag;
        ucollisions_AddCI(Gear);
    }
    if((!Gear->dY.isNegative && (ufloat_hwFloat_hwFloat_op_lt(Gear->dY, _0_001))) && (ucollisions_TestCollisionYwithGear(Gear, 1) != 0))
    {
        Gear->dY = _0;
    }
    if(ufloat_hwFloat_hwFloat_op_lt(ufloat_hwAbs(Gear->dX), _0_001))
    {
        Gear->dX = _0;
    }
    if(((Gear->Health > 0) && (((Gear->Health * 100) / cBarrelHealth) < fpcrtl_random(90))) && ((GameTicks & 0xff) == 0))
    {
        if((cBarrelHealth / Gear->Health) > 2)
        {
            uvisualgearslist_AddVisualGear_3((ufloat_hwRound(Gear->X) - 16) + fpcrtl_random(32), ufloat_hwRound(Gear->Y) - 2, vgtSmoke);
        }
        else
        {
            uvisualgearslist_AddVisualGear_3((ufloat_hwRound(Gear->X) - 16) + fpcrtl_random(32), ufloat_hwRound(Gear->Y) - 2, vgtSmokeWhite);
        }
    }
    Gear->Health -= Gear->Damage;
    Gear->Damage = 0;
    if(Gear->Health <= 0)
    {
        ugearshandlersmess_doStepCase(Gear);
    }
    else
    {
        if(!cOnlyStats && ((Gear->Health != Gear->FlightTime) || (Gear->Tex == NULL)))
        {
            Gear->FlightTime = Gear->Health;
            utextures_FreeAndNilTexture(&(Gear->Tex));
            Gear->Tex = urenderutils_RenderStringTex(fpcrtl_str2astr(uutils_IntToStr(Gear->Health)), 0xff808080, fnt16);
        }
    }
};
void ugearshandlersmess_doStepCase(PGear Gear)
{
    LongInt i;
    LongInt x;
    LongInt y;
    TGearType k;
    hwFloat dX;
    hwFloat dY;
    PHedgehog hog;
    PVisualGear sparkles;
    k = Gear->Kind;
    if((Gear->Message & gmDestroy) > 0)
    {
        ugearslist_DeleteGear(Gear);
        uai_FreeActionsList();
        ugearsutils_SetAllToActive();
        {
            if((*CurrentHedgehog).Gear != NULL)
            {
                (*CurrentHedgehog).Gear->Message = (*CurrentHedgehog).Gear->Message & ~(gmLJump | gmHJump);
            }
        }
        return;
    }
    if((k == gtExplosives) && (Gear->Health < cBarrelHealth))
    {
        Gear->State = Gear->State & ~gstFrozen;
    }
    if(((k != gtExplosives) && (Gear->Damage > 0)) || ((k == gtExplosives) && (Gear->Health <= 0)))
    {
        x = ufloat_hwRound(Gear->X);
        y = ufloat_hwRound(Gear->Y);
        hog = Gear->Hedgehog;
        if(k == gtCase)
        {
            ugearsutils_doMakeExplosion_5(x, y, Gear->Boom, hog, EXPLAutoSound);
            {i = 0;
             LongInt i__end__ = 63;
             if (i <= i__end__) do {
                                       ugearslist_AddGear_7(x, y, gtFlame, 0, _0, _0, 0);
                                   } while(i++ != i__end__);}
        }
        else
        {
            if(k == gtTarget)
            {
                ustats_TargetHit();
            }
            else
            {
                if(k == gtExplosives)
                {
                    ugearsutils_doMakeExplosion_5(x, y, Gear->Boom, hog, EXPLAutoSound);
                    {i = 0;
                     LongInt i__end__ = 31;
                     if (i <= i__end__) do {
                                               dX = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleCos(i * 64), _0_5), ufloat_hwFloat_hwFloat_op_add(urandom_GetRandomf(), _1));
                                               dY = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleSin(i * 64), _0_5), ufloat_hwFloat_hwFloat_op_add(urandom_GetRandomf(), _1));
                                               ugearslist_AddGear_7(x, y, gtFlame, 0, dX, dY, 0);
                                               ugearslist_AddGear_7(x, y, gtFlame, gsttmpFlag, ufloat_hwFloat_op_sub(dX), ufloat_hwFloat_op_sub(dY), 0);
                                           } while(i++ != i__end__);}
                }
            }
        }
        ugearslist_DeleteGear(Gear);
        return;
    }
    if(k == gtExplosives)
    {
        if((ufloat_hwFloat_hwFloat_op_gt(ufloat_hwAbs(Gear->dX), _0_15)) || ((ufloat_hwFloat_hwFloat_op_gt(ufloat_hwAbs(Gear->dY), _0_15)) && (ufloat_hwFloat_hwFloat_op_gt(ufloat_hwAbs(Gear->dX), _0_02))))
        {
            Gear->doStep = &(ugearshandlersmess_doStepRollingBarrel);
            return;
        }
        else
        {
            Gear->dX = _0;
        }
        if((((Gear->Health * 100) / cBarrelHealth) < fpcrtl_random(90)) && ((GameTicks & 0xff) == 0))
        {
            if((cBarrelHealth / Gear->Health) > 2)
            {
                uvisualgearslist_AddVisualGear_3((ufloat_hwRound(Gear->X) - 16) + fpcrtl_random(32), ufloat_hwRound(Gear->Y) - 2, vgtSmoke);
            }
            else
            {
                uvisualgearslist_AddVisualGear_3((ufloat_hwRound(Gear->X) - 16) + fpcrtl_random(32), ufloat_hwRound(Gear->Y) - 2, vgtSmokeWhite);
            }
        }
        Gear->Health -= Gear->Damage;
        Gear->Damage = 0;
        if(!cOnlyStats && ((Gear->Health != Gear->FlightTime) || (Gear->Tex == NULL)))
        {
            Gear->FlightTime = Gear->Health;
            utextures_FreeAndNilTexture(&(Gear->Tex));
            Gear->Tex = urenderutils_RenderStringTex(fpcrtl_str2astr(uutils_IntToStr(Gear->Health)), 0xff808080, fnt16);
        }
    }
    else
    {
        if((k == gtCase) && ((Gear->Pos & posCaseHealth) != 0))
        {
            if((Gear->State & gstFrozen) == 0)
            {
                if(Gear->Karma == 2)
                {
                    i = 0;
                }
                else
                {
                    if(Gear->Karma == 1)
                    {
                        if(((GameType == gmtDemo) || (GameType == gmtRecord)))
                        {
                            i = 1;
                        }
                        else
                        {
                            i = 0;
                        }
                    }
                    else
                    {
                        if(cOnlyStats)
                        {
                            i = 0;
                        }
                        else
                        {
                            i = 1;
                        }
                    }
                }
                if(i == 1)
                {
                    if(!cOnlyStats && ((Gear->Health != Gear->FlightTime) || (Gear->Tex == NULL)))
                    {
                        Gear->FlightTime = Gear->Health;
                        utextures_FreeAndNilTexture(&(Gear->Tex));
                        Gear->Tex = urenderutils_RenderStringTex(fpcrtl_str2astr(uutils_IntToStr(Gear->Health)), 0xff80ff80, fnt16);
                    }
                }
                else
                {
                    if(!cOnlyStats && ((Gear->FlightTime != 0xffffffff) || (Gear->Tex == NULL)))
                    {
                        Gear->FlightTime = 0xffffffff;
                        utextures_FreeAndNilTexture(&(Gear->Tex));
                        Gear->Tex = urenderutils_RenderStringTex(trmsg[sidUnknownGearValue], 0xff80ff80, fnt16);
                    }
                }
            }
        }
        if(Gear->Timer == 500)
        {
            Gear->Angle = ufloat_hwRound(Gear->Y);
            Gear->Tag = fpcrtl_random(2);
            ++Gear->Timer;
        }
        if(Gear->Timer < 1833)
        {
            ++Gear->Timer;
        }
        if(Gear->Timer == 1000)
        {
            sparkles = uvisualgearslist_AddVisualGear_4(ufloat_hwRound(Gear->X), Gear->Angle, vgtDust, 1);
            if(sparkles != NULL)
            {
                sparkles->dX = 0;
                sparkles->dY = 0;
                sparkles->Angle = 270;
                if(Gear->Tag == 1)
                {
                    sparkles->Tint = 0x3744d7ff;
                }
                else
                {
                    sparkles->Tint = 0xfab22cff;
                }
            }
        }
        if(Gear->Timer < 1000)
        {
            AllInactive = false;
            return;
        }
    }
    if((Gear->dY.QWordValue != 0) || (ucollisions_TestCollisionYwithGear(Gear, 1) == 0))
    {
        AllInactive = false;
        Gear->dY = ufloat_hwFloat_hwFloat_op_add(Gear->dY, cGravity);
        if((!Gear->dY.isNegative && (ucollisions_TestCollisionYwithGear(Gear, 1) != 0)) || (Gear->dY.isNegative && (ucollisions_TestCollisionYwithGear(Gear, -1) != 0)))
        {
            Gear->dY = _0;
        }
        else
        {
            Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, Gear->dY);
        }
        if(!Gear->dY.isNegative && (ufloat_hwFloat_hwFloat_op_gt(Gear->dY, _0_001)))
        {
            ugearsutils_SetAllHHToActive_1(false);
        }
        if(!Gear->dY.isNegative && (ucollisions_TestCollisionYwithGear(Gear, 1) != 0))
        {
            if((ufloat_hwFloat_hwFloat_op_gt(Gear->dY, _0_2)) && (k == gtExplosives))
            {
                Gear->Damage += ufloat_hwRound(ufloat_hwFloat_hwFloat_op_mul(Gear->dY, _70));
            }
            if(ufloat_hwFloat_hwFloat_op_gt(Gear->dY, _0_2))
            {
                {i = uutils_Min(12, ufloat_hwRound(ufloat_hwFloat_hwFloat_op_mul(Gear->dY, _10)));
                 LongInt i__end__ = 0;
                 if (i >= i__end__) do {
                                           uvisualgearslist_AddVisualGear_3((ufloat_hwRound(Gear->X) - 5) + fpcrtl_random(10), ufloat_hwRound(Gear->Y) + 12, vgtDust);
                                       } while(i-- != i__end__);}
            }
            Gear->dY = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_op_sub(Gear->dY), Gear->Elasticity);
            if(ufloat_hwFloat_hwFloat_op_gt(Gear->dY, ufloat_hwFloat_op_sub(_0_001)))
            {
                Gear->dY = _0;
            }
            else
            {
                if(ufloat_hwFloat_hwFloat_op_lt(Gear->dY, ufloat_hwFloat_op_sub(_0_03)))
                {
                    usound_PlaySound_1(Gear->ImpactSound);
                }
            }
        }
        ugearsutils_CheckGearDrowning(&(Gear));
        if((Gear->State & gstDrowning) != 0)
        {
            Gear->RenderHealth = false;
        }
    }
    if(Gear->dY.QWordValue == 0)
    {
        ucollisions_AddCI(Gear);
    }
    else
    {
        if(Gear->dY.QWordValue != 0)
        {
            ucollisions_DeleteCI(Gear);
        }
    }
};
void ugearshandlersmess_doStepTarget(PGear Gear)
{
    if((Gear->Timer == 0) && (Gear->Tag == 0))
    {
        usound_PlaySound_1(sndWarp);
        Gear->Angle = ufloat_hwRound(Gear->Y);
    }
    if((Gear->Tag == 0) && (Gear->Timer < 1000))
    {
        ++Gear->Timer;
    }
    else
    {
        if(Gear->Tag == 1)
        {
            Gear->Tag = 2;
        }
        else
        {
            if(Gear->Tag == 2)
            {
                if(Gear->Timer > 0)
                {
                    --Gear->Timer;
                }
                else
                {
                    ugearslist_DeleteGear(Gear);
                    return;
                }
            }
        }
    }
    ugearshandlersmess_doStepCase(Gear);
};
void ugearshandlersmess_doStepIdle(PGear Gear)
{
    AllInactive = false;
    --Gear->Timer;
    if(Gear->Timer == 0)
    {
        ugearslist_DeleteGear(Gear);
        ugearshedgehog_AfterAttack();
    }
};
void ugearshandlersmess_doStepShover(PGear Gear)
{
    PGear HHGear;
    --Gear->Timer;
    if(Gear->Timer == 0)
    {
        ++Gear->Tag;
        Gear->Timer = 50;
        if(Gear->Tag == 3)
        {
            ucollisions_ClearHitOrder();
            ucollisions_RefillProximityCache(Gear, 100);
        }
    }
    if(Gear->Tag == 3)
    {
        HHGear = (*Gear->Hedgehog).Gear;
        HHGear->State = HHGear->State | gstNoDamage;
        ucollisions_DeleteCI(HHGear);
        ugearsutils_AmmoShoveCache(Gear, Gear->Boom, 115);
        HHGear->State = (HHGear->State & ~gstNoDamage) | gstMoving;
    }
    else
    {
        if(Gear->Tag == 4)
        {
            ucollisions_ClearHitOrder();
            ucollisions_ClearProximityCache();
            Gear->Timer = 250;
            Gear->doStep = &(ugearshandlersmess_doStepIdle);
        }
    }
};
void ugearshandlersmess_doStepWhip(PGear Gear)
{
    PGear HHGear;
    LongInt i;
    HHGear = (*Gear->Hedgehog).Gear;
    HHGear->State = HHGear->State | gstNoDamage;
    ucollisions_DeleteCI(HHGear);
    ucollisions_ClearHitOrder();
    ucollisions_RefillProximityCache(Gear, 100);
    {i = 0;
     LongInt i__end__ = 3;
     if (i <= i__end__) do {
                               uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X) + (ufloat_hwSign(Gear->dX) * (10 + (6 * i))), (ufloat_hwRound(Gear->Y) + 12) + fpcrtl_random(6), vgtDust);
                               ugearsutils_AmmoShoveCache(Gear, Gear->Boom, 25);
                               Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, ufloat_hwFloat_LongInt_op_mul(Gear->dX, 5));
                           } while(i++ != i__end__);}
    ucollisions_ClearHitOrder();
    ucollisions_ClearProximityCache();
    HHGear->State = (HHGear->State & ~gstNoDamage) | gstMoving;
    Gear->Timer = 250;
    Gear->doStep = &(ugearshandlersmess_doStepIdle);
};
void ugearshandlersmess_doStepFlame(PGear Gear)
{
    LongInt gX;
    LongInt gY;
    LongInt i;
    boolean sticky;
    PVisualGear vgt;
    hwFloat tdX;
    hwFloat tdY;
    hwFloat f;
    Word landPixel;
    ugearsutils_WorldWrap(&(Gear));
    if(Gear->FlightTime > 0)
    {
        --Gear->FlightTime;
    }
    sticky = (Gear->State & gsttmpFlag) != 0;
    if(!sticky)
    {
        AllInactive = false;
    }
    landPixel = ucollisions_TestCollisionYwithGear(Gear, 1);
    if(landPixel == 0)
    {
        AllInactive = false;
        if(((GameTicks & 0xf) == 0) && (Gear->FlightTime == 0))
        {
            Gear->Radius = 7;
            tdX = Gear->dX;
            tdY = Gear->dY;
            Gear->dX.QWordValue = 120000000;
            Gear->dY.QWordValue = 429496730;
            Gear->dX.isNegative = urandom_GetRandom(2) != 1;
            Gear->dY.isNegative = true;
            ugearsutils_AmmoShove(Gear, Gear->Boom, 125);
            Gear->dX = tdX;
            Gear->dY = tdY;
            Gear->Radius = 1;
        }
        if((GameTicks % 100) == 0)
        {
            vgt = uvisualgearslist_AddVisualGear_4(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtFire, gsttmpFlag);
            if(vgt != NULL)
            {
                vgt->dX = 0;
                vgt->dY = 0;
                vgt->FrameTicks = 1800 / ((Gear->Tag % 3) + 2);
            }
        }
        if((Gear->dX.QWordValue > _2.QWordValue) || (Gear->dY.QWordValue > _2.QWordValue))
        {
            f = ufloat_hwFloat_hwFloat_op_div(_1_9, ufloat_Distance(Gear->dX, Gear->dY));
            Gear->dX = ufloat_hwFloat_hwFloat_op_mul(Gear->dX, f);
            Gear->dY = ufloat_hwFloat_hwFloat_op_mul(Gear->dY, f);
        }
        else
        {
            if(Gear->dX.QWordValue > _0_01.QWordValue)
            {
                Gear->dX = ufloat_hwFloat_hwFloat_op_mul(Gear->dX, _0_995);
            }
            Gear->dY = ufloat_hwFloat_hwFloat_op_add(Gear->dY, cGravity);
            if(Gear->dY.QWordValue > _0_2.QWordValue)
            {
                Gear->dY = ufloat_hwFloat_hwFloat_op_mul(Gear->dY, _0_995);
            }
            tdX = ufloat_hwFloat_hwFloat_op_add(Gear->dX, ufloat_hwFloat_LongInt_op_mul(cWindSpeed, 640));
            if((WorldEdge == weBounce) && ((((ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(Gear->X, tdX)) - Gear->Radius) < leftX) && (ufloat_hwSign(tdX) == -1)) || (((ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(Gear->X, tdX)) + Gear->Radius) > rightX) && (ufloat_hwSign(tdX) == 1))))
            {
                Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, Gear->dX);
            }
            else
            {
                Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, tdX);
            }
            Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, Gear->dY);
        }
        gX = ufloat_hwRound(Gear->X);
        gY = ufloat_hwRound(Gear->Y);
        if(ucollisions_CheckCoordInWater(gX, gY))
        {
            {i = 0;
             LongInt i__end__ = 3;
             if (i <= i__end__) do {
                                       uvisualgearslist_AddVisualGear_3((gX - 8) + fpcrtl_random(16), (gY - 8) + fpcrtl_random(16), vgtSteam);
                                   } while(i++ != i__end__);}
            usound_PlaySound_1(sndVaporize);
            ugearslist_DeleteGear(Gear);
            return;
        }
    }
    else
    {
        if((Gear->Timer == 1) && ((GameTicks & 0x3) == 0))
        {
            Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _6);
            if(((landPixel & lfIce) != 0) || ((ucollisions_TestCollisionYwithGear(Gear, 1) & lfIce) != 0))
            {
                gX = ufloat_hwRound(Gear->X);
                gY = ufloat_hwRound(Gear->Y) - 6;
                ugearsutils_doMakeExplosion_5(gX, gY, 4, Gear->Hedgehog, (EXPLNoDamage | EXPLDoNotTouchAny) | EXPLNoGfx);
                usound_PlaySound_1(sndVaporize);
                uvisualgearslist_AddVisualGear_3((gX - 3) + fpcrtl_random(6), gY - 2, vgtSteam);
                ugearslist_DeleteGear(Gear);
                return;
            }
            Gear->Y = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, _6);
        }
        if(sticky && ((GameTicks & 0xf) == 0))
        {
            Gear->Radius = 7;
            tdX = Gear->dX;
            tdY = Gear->dY;
            Gear->dX.QWordValue = 120000000;
            Gear->dY.QWordValue = 429496730;
            Gear->dX.isNegative = urandom_GetRandom(2) != 1;
            Gear->dY.isNegative = true;
            ugearsutils_AmmoShove(Gear, Gear->Boom, 125);
            Gear->dX = tdX;
            Gear->dY = tdY;
            Gear->Radius = 1;
        }
        if(Gear->Timer > 0)
        {
            --Gear->Timer;
            ++Gear->Damage;
        }
        else
        {
            gX = ufloat_hwRound(Gear->X);
            gY = ufloat_hwRound(Gear->Y);
            if(!sticky)
            {
                if((GameTicks & 0x1) == 0)
                {
                    Gear->Radius = 7;
                    tdX = Gear->dX;
                    tdY = Gear->dY;
                    Gear->dX.QWordValue = 214748365;
                    Gear->dY.QWordValue = 429496730;
                    Gear->dX.isNegative = urandom_GetRandom(2) != 1;
                    Gear->dY.isNegative = true;
                    ugearsutils_AmmoShove(Gear, Gear->Boom * 3, 100);
                    Gear->dX = tdX;
                    Gear->dY = tdY;
                    Gear->Radius = 1;
                }
                else
                {
                    if((GameTicks & 0x3) == 3)
                    {
                        ugearsutils_doMakeExplosion_5(gX, gY, Gear->Boom * 4, Gear->Hedgehog, 0);
                    }
                }
                if(((GameTicks & 0x7) == 0) && (fpcrtl_random(2) == 0))
                {
                    {i = fpcrtl_random(2);
                     LongInt i__end__ = 0;
                     if (i >= i__end__) do {
                                               uvisualgearslist_AddVisualGear_3((gX - 3) + fpcrtl_random(6), gY - 2, vgtSmoke);
                                           } while(i-- != i__end__);}
                }
                if(Gear->Health > 0)
                {
                    --Gear->Health;
                }
                Gear->Timer = (450 - (Gear->Tag * 8)) + ((LongInt)urandom_GetRandom(2));
            }
            else
            {
                if(((GameTicks & 0x7ff) == 0) && ((GameFlags & gfSolidLand) == 0))
                {
                    ugearsutils_doMakeExplosion_5(gX, gY, 4, Gear->Hedgehog, (EXPLNoDamage | EXPLDoNotTouchAny) | EXPLNoGfx);
                    {i = fpcrtl_random(3);
                     LongInt i__end__ = 0;
                     if (i >= i__end__) do {
                                               uvisualgearslist_AddVisualGear_3((gX - 3) + fpcrtl_random(6), gY - 2, vgtSmoke);
                                           } while(i-- != i__end__);}
                }
                Gear->Timer = (100 - (Gear->Tag * 3)) + ((LongInt)urandom_GetRandom(2));
                if(Gear->Damage > (3000 + (Gear->Tag * 1500)))
                {
                    Gear->Health = 0;
                }
            }
        }
    }
    if(Gear->Health == 0)
    {
        gX = ufloat_hwRound(Gear->X);
        gY = ufloat_hwRound(Gear->Y);
        if(!sticky)
        {
            if(((GameTicks & 0x3) == 0) && (fpcrtl_random(1) == 0))
            {
                {i = fpcrtl_random(2);
                 LongInt i__end__ = 0;
                 if (i >= i__end__) do {
                                           uvisualgearslist_AddVisualGear_3((gX - 3) + fpcrtl_random(6), gY - 2, vgtSmoke);
                                       } while(i-- != i__end__);}
            }
        }
        else
        {
            {i = fpcrtl_random(3);
             LongInt i__end__ = 0;
             if (i >= i__end__) do {
                                       uvisualgearslist_AddVisualGear_3((gX - 3) + fpcrtl_random(6), gY - 2, vgtSmoke);
                                   } while(i-- != i__end__);}
        }
        ugearslist_DeleteGear(Gear);
    }
};
void ugearshandlersmess_doStepFirePunchWork(PGear Gear)
{
    PGear HHGear;
    AllInactive = false;
    if((Gear->Message & gmDestroy) != 0)
    {
        ugearslist_DeleteGear(Gear);
        ugearshedgehog_AfterAttack();
        return;
    }
    HHGear = (*Gear->Hedgehog).Gear;
    if(ufloat_hwRound(HHGear->Y) <= (Gear->Tag - 2))
    {
        Gear->Tag = ufloat_hwRound(HHGear->Y);
        ulandgraphics_DrawTunnel(ufloat_hwFloat_hwFloat_op_sub(HHGear->X, ufloat_int2hwFloat(cHHRadius)), ufloat_hwFloat_hwFloat_op_sub(HHGear->Y, _1), _0_5, _0, (cHHRadius * 4) + 2, 2);
        HHGear->State = HHGear->State | gstNoDamage;
        Gear->Y = HHGear->Y;
        ugearsutils_AmmoShoveCache(Gear, Gear->Boom, 40);
        HHGear->State = HHGear->State & ~gstNoDamage;
    }
    HHGear->dY = ufloat_hwFloat_hwFloat_op_add(HHGear->dY, cGravity);
    if(Gear->Timer > 0)
    {
        --Gear->Timer;
    }
    if(!HHGear->dY.isNegative || (Gear->Timer == 0))
    {
        HHGear->State = HHGear->State | gstMoving;
        ucollisions_ClearHitOrder();
        ucollisions_ClearProximityCache();
        ugearslist_DeleteGear(Gear);
        ugearshedgehog_AfterAttack();
        return;
    }
    if(ulandgraphics_CheckLandValue(ufloat_hwRound(HHGear->X), ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_add(HHGear->Y, HHGear->dY), ufloat_SignAs(_6, Gear->dY))), lfIndestructible))
    {
        HHGear->Y = ufloat_hwFloat_hwFloat_op_add(HHGear->Y, HHGear->dY);
    }
    if((Gear->Timer % 200) == 0)
    {
        ucollisions_RefillProximityCache(Gear, 300);
    }
};
void ugearshandlersmess_doStepFirePunch(PGear Gear)
{
    PGear HHGear;
    AllInactive = false;
    HHGear = (*Gear->Hedgehog).Gear;
    ucollisions_DeleteCI(HHGear);
    HHGear->dX = ufloat_SignAs(cLittle, Gear->dX);
    HHGear->dY = ufloat_hwFloat_op_sub(_0_3);
    ucollisions_ClearHitOrder();
    ucollisions_RefillProximityCache(Gear, 300);
    Gear->X = HHGear->X;
    Gear->dX = ufloat_SignAs(_0_45, Gear->dX);
    Gear->dY = ufloat_hwFloat_op_sub(_0_9);
    Gear->doStep = &(ugearshandlersmess_doStepFirePunchWork);
    ulandgraphics_DrawTunnel(ufloat_hwFloat_hwFloat_op_sub(HHGear->X, ufloat_int2hwFloat(cHHRadius)), ufloat_hwFloat_hwFloat_op_add(HHGear->Y, _1), _0_5, _0, cHHRadius * 4, 5);
    usound_PlaySoundV_2(((TSound)(sndFirePunch1) + urandom_GetRandom(6)), (*(*HHGear->Hedgehog).Team).voicepack);
};
void ugearshandlersmess_doStepParachuteWork(PGear Gear)
{
    PGear HHGear;
    hwFloat deltaX;
    hwFloat deltaY;
    HHGear = (*Gear->Hedgehog).Gear;
    ++Gear->Timer;
    if((((ucollisions_TestCollisionYwithGear(HHGear, 1) != 0) || ((HHGear->State & gstHHDriven) == 0)) || ugearsutils_CheckGearDrowning(&(HHGear))) || ((Gear->Message & gmAttack) != 0))
    {
        {
            (*HHGear).Message = 0;
            if(Gear->Tag == 1)
            {
                (*HHGear).dX = _1;
            }
            else
            {
                (*HHGear).dX = ufloat_hwFloat_op_sub(_1);
            }
            uutils_SetLittle(&((*HHGear).dX));
            (*HHGear).dY = _0;
            (*HHGear).State = (*HHGear).State | gstMoving;
        }
        if(((uammos_GetAmmoEntry(&((*HHGear->Hedgehog)), amParachute)->Count >= 1) && ((Ammoz[(*HHGear->Hedgehog).CurAmmoType].Ammo.Propz & ammoprop_AltUse) != 0)) && ((*HHGear->Hedgehog).MultiShootAttacks == 0))
        {
            (*HHGear->Hedgehog).CurAmmoType = amParachute;
        }
        isCursorVisible = false;
        uammos_ApplyAmmoChanges(&((*HHGear->Hedgehog)));
        ugearslist_DeleteGear(Gear);
        return;
    }
    deltaX = _0;
    deltaX = ufloat_hwFloat_hwFloat_op_add(deltaX, ufloat_hwFloat_LongInt_op_mul(cWindSpeed, 200));
    deltaY = _0;
    if((Gear->Message & gmLeft) != 0)
    {
        deltaX = ufloat_hwFloat_hwFloat_op_sub(deltaX, ufloat_hwFloat_LongInt_op_mul(cMaxWindSpeed, 80));
    }
    else
    {
        if((Gear->Message & gmRight) != 0)
        {
            deltaX = ufloat_hwFloat_hwFloat_op_add(deltaX, ufloat_hwFloat_LongInt_op_mul(cMaxWindSpeed, 80));
        }
    }
    if((Gear->Message & gmUp) != 0)
    {
        deltaY = ufloat_hwFloat_hwFloat_op_sub(deltaY, ufloat_hwFloat_LongInt_op_mul(cGravity, 40));
    }
    else
    {
        if((Gear->Message & gmDown) != 0)
        {
            deltaY = ufloat_hwFloat_hwFloat_op_add(deltaY, ufloat_hwFloat_LongInt_op_mul(cGravity, 40));
        }
    }
    HHGear->X = ufloat_hwFloat_hwFloat_op_add(HHGear->X, deltaX);
    if(ucollisions_TestCollisionXwithGear(HHGear, ufloat_hwSign(deltaX)) != 0)
    {
        HHGear->X = ufloat_hwFloat_hwFloat_op_sub(HHGear->X, ufloat_int2hwFloat(ufloat_hwSign(deltaX)));
        deltaX = _0;
    }
    deltaY = ufloat_hwFloat_hwFloat_op_add(deltaY, ufloat_hwFloat_LongInt_op_mul(cGravity, 100));
    HHGear->Y = ufloat_hwFloat_hwFloat_op_add(HHGear->Y, deltaY);
    HHGear->dX = deltaX;
    HHGear->dY = deltaY;
    Gear->X = HHGear->X;
    Gear->Y = HHGear->Y;
};
void ugearshandlersmess_doStepParachute(PGear Gear)
{
    PGear HHGear;
    HHGear = (*Gear->Hedgehog).Gear;
    ucollisions_DeleteCI(HHGear);
    ugearshedgehog_AfterAttack();
    if((ucollisions_TestCollisionXwithGear(HHGear, -1) != 0) && (ucollisions_TestCollisionXwithGear(HHGear, 1) != 0))
    {
        HHGear->dY = ufloat_hwFloat_LongInt_op_mul(cGravity, 100);
        isCursorVisible = false;
        uammos_ApplyAmmoChanges(&((*HHGear->Hedgehog)));
        ugearslist_DeleteGear(Gear);
        return;
    }
    if((HHGear->State & gstHHHJump) != 0)
    {
        HHGear->dX.isNegative = !HHGear->dX.isNegative;
    }
    HHGear->State = HHGear->State & ~((((gstAttacking | gstAttacked) | gstMoving) | gstHHJumping) | gstHHHJump);
    HHGear->Message = HHGear->Message & ~gmAttack;
    Gear->doStep = &(ugearshandlersmess_doStepParachuteWork);
    Gear->Message = HHGear->Message;
    ugearshandlersmess_doStepParachuteWork(Gear);
};
void ugearshandlersmess_doStepAirAttackWork(PGear Gear)
{
    boolean uw;
    boolean nuw;
    hwFloat tmpFloat;
    LongInt i;
    AllInactive = false;
    if(WorldEdge == weWrap)
    {
        if(ugearsutils_WorldWrap(&(Gear)))
        {
            ++Gear->Power;
        }
    }
    Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, ufloat_hwFloat_LongInt_op_mul(cAirPlaneSpeed, Gear->Tag));
    if(((Gear->Health > 0) && (Gear->Power >= Gear->WDTimer)) && (((Gear->Tag == 1) && !(ufloat_hwFloat_hwFloat_op_lt(Gear->X, Gear->dX))) || ((Gear->Tag == -1) && !(ufloat_hwFloat_hwFloat_op_gt(Gear->X, Gear->dX)))))
    {
        --Gear->Health;
        Gear->FlightTime = 0;
        switch(Gear->State)
        {case 0:FollowGear = ugearslist_AddGear_7(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), gtAirBomb, 0, ufloat_hwFloat_LongInt_op_mul(cBombsSpeed, Gear->Tag), _0, 0);
                break;
         case 1:FollowGear = ugearslist_AddGear_7(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), gtMine, 0, ufloat_hwFloat_LongInt_op_mul(cBombsSpeed, Gear->Tag), _0, 0);
                break;
         case 2:FollowGear = ugearslist_AddGear_7(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), gtNapalmBomb, 0, ufloat_hwFloat_LongInt_op_mul(cBombsSpeed, Gear->Tag), _0, 0);
                break;
         case 3:FollowGear = ugearslist_AddGear_7(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), gtDrill, gsttmpFlag, ufloat_hwFloat_LongInt_op_mul(cBombsSpeed, Gear->Tag), _0, Gear->Timer + 1);
                break;
         default: break;}
        Gear->dX = ufloat_hwFloat_hwFloat_op_add(Gear->X, ufloat_int2hwFloat(Gear->Damage * Gear->Tag));
        if(WorldEdge == weWrap)
        {
            Gear->dX = ufloat_int2hwFloat(uutils_CalcWorldWrap(ufloat_hwRound(Gear->dX), 0));
            if(((Gear->Tag == 1) && !(ufloat_hwFloat_hwFloat_op_lt(Gear->X, Gear->dX))) || ((Gear->Tag == -1) && !(ufloat_hwFloat_hwFloat_op_gt(Gear->X, Gear->dX))))
            {
                ++Gear->WDTimer;
            }
        }
        if(ucollisions_CheckCoordInWater(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y)))
        {
            FollowGear->State = FollowGear->State | gstSubmersible;
        }
    }
    if(Gear->Health == 0)
    {
        ++Gear->FlightTime;
    }
    if(((Gear->SoundChannel != -1) && (WorldEdge != weSea)) && (Gear->FlightTime > 20))
    {
        usound_StopSoundChan_2(Gear->SoundChannel, 4000);
        Gear->SoundChannel = -1;
    }
    if((GameTicks & 0x3f) == 0)
    {
        if(ucollisions_CheckCoordInWater(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y)))
        {
            {i = 1;
             LongInt i__end__ = 3;
             if (i <= i__end__) do {
                                       uvisualgearslist_AddVisualGear_3((ufloat_hwRound(Gear->X) - 8) + fpcrtl_random(16), (ufloat_hwRound(Gear->Y) - 8) + fpcrtl_random(16), vgtBubble);
                                   } while(i++ != i__end__);}
            if(fpcrtl_random(2) == 0)
            {
                uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X) + 10, ufloat_hwRound(Gear->Y) - 50, vgtBubble);
            }
        }
        else
        {
            uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtSmokeTrace);
        }
    }
    if(((WorldEdge == weWrap) && (Gear->FlightTime >= 4000)) || ((WorldEdge != weWrap) && ((((ufloat_hwRound(Gear->X) - Gear->Radius) > (LAND_WIDTH + 2048)) || ((ufloat_hwRound(Gear->X) + Gear->Radius) < -2048)) || ((Gear->Message & gmDestroy) > 0))))
    {
        if(Gear->SoundChannel != -1)
        {
            usound_StopSoundChan_1(Gear->SoundChannel);
            Gear->SoundChannel = -1;
        }
        if(WorldEdge == weWrap)
        {
            uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtBigExplosion);
        }
        ugearslist_DeleteGear(Gear);
        return;
    }
    uw = Gear->Karma != 0;
    nuw = ucollisions_CheckCoordInWater(ufloat_hwRound(Gear->X) + (Gear->Radius * Gear->Tag), ufloat_hwRound(Gear->Y));
    if(nuw != uw)
    {
        tmpFloat = Gear->dX;
        Gear->dX = ufloat_hwFloat_LongInt_op_mul(cAirPlaneSpeed, Gear->Tag);
        ugearsutils_AddSplashForGear(Gear, false);
        Gear->dX = tmpFloat;
        usound_StopSoundChan_1(Gear->SoundChannel);
        if(nuw)
        {
            Gear->SoundChannel = usound_LoopSound_1(sndPlaneWater);
            usound_StopSoundChan_2(Gear->SoundChannel, 4000);
            Gear->SoundChannel = -1;
            Gear->Karma = 1;
        }
        else
        {
            Gear->SoundChannel = usound_LoopSound_1(sndPlane);
            Gear->Karma = 0;
        }
    }
};
void ugearshandlersmess_doStepAirAttack(PGear Gear)
{
    PGear HHGear;
    AllInactive = false;
    HHGear = NULL;
    if((Gear->Hedgehog != NULL) && ((*Gear->Hedgehog).Gear != NULL))
    {
        HHGear = (*Gear->Hedgehog).Gear;
    }
    if(HHGear != NULL)
    {
        usound_PlaySoundV_2(sndIncoming, (*(*Gear->Hedgehog).Team).voicepack);
    }
    ugearshedgehog_AfterAttack();
    CurAmmoGear = NULL;
    if(Gear->X.QWordValue == 0)
    {
        Gear->Tag = 1;
        if(WorldEdge == weWrap)
        {
            Gear->X = ufloat_int2hwFloat(uutils_CalcWorldWrap(Gear->Target.x + uutils_Max(384, LAND_WIDTH >> 2), 0));
        }
        else
        {
            Gear->X = ufloat_hwFloat_op_sub(_2048);
        }
    }
    else
    {
        Gear->Tag = -1;
        if(WorldEdge == weWrap)
        {
            Gear->X = ufloat_int2hwFloat(uutils_CalcWorldWrap(Gear->Target.x - uutils_Max(384, LAND_WIDTH >> 2), 0));
        }
        else
        {
            Gear->X = ufloat_int2hwFloat(LAND_WIDTH + 2048);
        }
    }
    Gear->Y = ufloat_int2hwFloat(topY - 300);
    if(WorldEdge == weWrap)
    {
        uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtBigExplosion);
    }
    Gear->dX = ufloat_hwFloat_hwFloat_op_sub(ufloat_int2hwFloat(Gear->Target.x), ufloat_hwFloat_LongInt_op_div(ufloat_int2hwFloat((Gear->Tag * (Gear->Health - 1)) * Gear->Damage), 2));
    if(Gear->State == 2)
    {
        Gear->dX = ufloat_hwFloat_hwFloat_op_sub(Gear->dX, ufloat_hwFloat_LongInt_op_mul(ufloat_hwFloat_LongInt_op_mul(cBombsSpeed, Gear->Tag), 900));
    }
    else
    {
        if(ufloat_hwFloat_hwFloat_op_gt(ufloat_hwFloat_hwFloat_op_sub(ufloat_int2hwFloat(Gear->Target.y), Gear->Y), _0))
        {
            Gear->dX = ufloat_hwFloat_hwFloat_op_sub(Gear->dX, ufloat_hwFloat_LongInt_op_mul(ufloat_hwFloat_hwFloat_op_mul(cBombsSpeed, ufloat_hwSqrt(ufloat_hwFloat_hwFloat_op_div(ufloat_hwFloat_LongInt_op_mul(ufloat_hwFloat_hwFloat_op_sub(ufloat_int2hwFloat(Gear->Target.y), Gear->Y), 2), cGravity))), Gear->Tag));
        }
    }
    if(WorldEdge == weWrap)
    {
        Gear->dX = ufloat_int2hwFloat(uutils_CalcWorldWrap(ufloat_hwRound(Gear->dX), 0));
        if(((Gear->Tag == 1) && !(ufloat_hwFloat_hwFloat_op_lt(Gear->X, Gear->dX))) || ((Gear->Tag == -1) && !(ufloat_hwFloat_hwFloat_op_gt(Gear->X, Gear->dX))))
        {
            Gear->WDTimer = 1;
        }
    }
    Gear->doStep = &(ugearshandlersmess_doStepAirAttackWork);
    if(WorldEdge == weSea)
    {
        Gear->SoundChannel = usound_LoopSound_2(sndPlaneWater, 4000);
        Gear->Karma = 1;
    }
    else
    {
        if(WorldEdge == weWrap)
        {
            Gear->SoundChannel = usound_LoopSound_2(sndPlane, 500);
            Gear->Karma = 0;
        }
        else
        {
            Gear->SoundChannel = usound_LoopSound_2(sndPlane, 4000);
            Gear->Karma = 0;
        }
    }
    if((GameFlags & gfInfAttack) == 0)
    {
        FollowGear = Gear;
    }
};
void ugearshandlersmess_doStepAirBomb(PGear Gear)
{
    AllInactive = false;
    ugearshandlersmess_doStepFallingGear(Gear);
    if((Gear->State & gstCollision) != 0)
    {
        ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
        ugearslist_DeleteGear(Gear);
        return;
    }
    if((GameTicks & 0x3f) == 0)
    {
        uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtSmokeTrace);
    }
};
void ugearshandlersmess_doStepGirder(PGear Gear)
{
    PGear HHGear;
    hwFloat x;
    hwFloat y;
    hwFloat tx;
    hwFloat ty;
    LongInt rx;
    Word LandFlags;
    PVisualGear warn;
    boolean distFail;
    AllInactive = false;
    HHGear = (*Gear->Hedgehog).Gear;
    tx = ufloat_int2hwFloat(Gear->Target.x);
    ty = ufloat_int2hwFloat(Gear->Target.y);
    x = HHGear->X;
    y = HHGear->Y;
    rx = ufloat_hwRound(x);
    LandFlags = 0;
    if(Gear->AmmoType == amRubber)
    {
        LandFlags = lfBouncy;
    }
    else
    {
        if(cIce)
        {
            LandFlags = lfIce;
        }
    }
    distFail = (cBuildMaxDist > 0) && ((ufloat_hwRound(ufloat_Distance(ufloat_hwFloat_hwFloat_op_sub(tx, x), ufloat_hwFloat_hwFloat_op_sub(ty, y))) > cBuildMaxDist) && ((WorldEdge != weWrap) || ((ufloat_hwRound(ufloat_Distance(ufloat_hwFloat_hwFloat_op_sub(tx, ufloat_int2hwFloat(rightX + (rx - leftX))), ufloat_hwFloat_hwFloat_op_sub(ty, y))) > cBuildMaxDist) && (ufloat_hwRound(ufloat_Distance(ufloat_hwFloat_hwFloat_op_sub(tx, ufloat_int2hwFloat(leftX - (rightX - rx))), ufloat_hwFloat_hwFloat_op_sub(ty, y))) > cBuildMaxDist))));
    if((distFail || ucollisions_CheckGearsUnderSprite(Ammoz[Gear->AmmoType].PosSprite, Gear->Target.x - (SpritesData[Ammoz[Gear->AmmoType].PosSprite].Width / 2), Gear->Target.y - (SpritesData[Ammoz[Gear->AmmoType].PosSprite].Height / 2), Gear->State)) || !ulandgraphics_TryPlaceOnLand_6(Gear->Target.x - (SpritesData[Ammoz[Gear->AmmoType].PosSprite].Width / 2), Gear->Target.y - (SpritesData[Ammoz[Gear->AmmoType].PosSprite].Height / 2), Ammoz[Gear->AmmoType].PosSprite, Gear->State, true, LandFlags))
    {
        usound_PlaySound_1(sndDenied);
        if(!distFail)
        {
            warn = uvisualgearslist_AddVisualGear_5(Gear->Target.x, Gear->Target.y, vgtNoPlaceWarn, 0, true);
            if(warn != NULL)
            {
                warn->Tex = ulandgraphics_GetPlaceCollisionTex(Gear->Target.x - (SpritesData[Ammoz[Gear->AmmoType].PosSprite].Width / 2), Gear->Target.y - (SpritesData[Ammoz[Gear->AmmoType].PosSprite].Height / 2), Ammoz[Gear->AmmoType].PosSprite, Gear->State);
            }
        }
        HHGear->Message = HHGear->Message & ~gmAttack;
        HHGear->State = HHGear->State & ~gstAttacking;
        HHGear->State = HHGear->State | gstChooseTarget;
        isCursorVisible = true;
        ugearslist_DeleteGear(Gear);
    }
    else
    {
        usound_PlaySound_1(sndPlaced);
        ugearslist_DeleteGear(Gear);
        ugearshedgehog_AfterAttack();
    }
    HHGear->State = HHGear->State & ~(gstAttacking | gstAttacked);
    HHGear->Message = HHGear->Message & ~gmAttack;
};
void ugearshandlersmess_doStepTeleportAfter(PGear Gear)
{
    PGear HHGear;
    HHGear = (*Gear->Hedgehog).Gear;
    if(HHGear != NULL)
    {
        ugearshedgehog_doStepHedgehogMoving(HHGear);
    }
    if((((((GameFlags & gfInfAttack) != 0) || (HHGear == NULL)) || ((HHGear->State & gstMoving) == 0)) || (HHGear->Damage > 0)) || ((HHGear->State & gstDrowning) != 0))
    {
        ugearslist_DeleteGear(Gear);
        ugearshedgehog_AfterAttack();
    }
};
void ugearshandlersmess_doStepTeleportAnim(PGear Gear)
{
    if(((*Gear->Hedgehog).Gear == NULL) || ((*(*Gear->Hedgehog).Gear).Damage > 0))
    {
        ugearslist_DeleteGear(Gear);
        ugearshedgehog_AfterAttack();
        return;
    }
    ++Gear->Timer;
    if(Gear->Timer == 65)
    {
        Gear->Timer = 0;
        ++Gear->Pos;
        if(Gear->Pos == 11)
        {
            Gear->doStep = &(ugearshandlersmess_doStepTeleportAfter);
        }
    }
};
void ugearshandlersmess_doStepTeleport(PGear Gear)
{
    LongInt lx;
    LongInt ty;
    LongInt y;
    LongInt oy;
    PGear HHGear;
    boolean valid;
    PVisualGear warn;
    enum{ytol = cHHRadius};
    AllInactive = false;
    HHGear = (*Gear->Hedgehog).Gear;
    if(HHGear == NULL)
    {
        ugearslist_DeleteGear(Gear);
        return;
    }
    valid = false;
    lx = Gear->Target.x - (SpritesData[sprHHTelepMask].Width / 2);
    if(WorldEdge != weBounce)
    {
        lx = uutils_CalcWorldWrap(lx, SpritesData[sprHHTelepMask].Width / 2);
    }
    ty = Gear->Target.y - (SpritesData[sprHHTelepMask].Height / 2);
    oy = Gear->Target.y;
    {y = ty;
     LongInt y__end__ = ty - ytol;
     if (y >= y__end__) do {
                               if(ulandgraphics_TryPlaceOnLand_12(lx, y, sprHHTelepMask, 0, false, !hasBorder, false, false, false, false, 0, 0xffffffff))
                               {
                                   valid = true;
                                   break;
                               }
                               --Gear->Target.y;
                           } while(y-- != y__end__);}
    if((WorldEdge == weBounce) && ((Gear->Target.x < leftX) || (Gear->Target.x > rightX)))
    {
        valid = false;
    }
    if(!valid)
    {
        HHGear->Message = HHGear->Message & ~gmAttack;
        HHGear->State = HHGear->State & ~gstAttacking;
        HHGear->State = HHGear->State | gstChooseTarget;
        isCursorVisible = true;
        warn = uvisualgearslist_AddVisualGear_5(Gear->Target.x, oy, vgtNoPlaceWarn, 0, true);
        if(warn != NULL)
        {
            warn->Tex = ulandgraphics_GetPlaceCollisionTex(lx, ty, sprHHTelepMask, 0);
        }
        ugearslist_DeleteGear(Gear);
        usound_PlaySound_1(sndDenied);
        return;
    }
    else
    {
        ucollisions_DeleteCI(HHGear);
        ugearsutils_SetAllHHToActive_0();
        Gear->doStep = &(ugearshandlersmess_doStepTeleportAnim);
        Gear->dX = HHGear->dX;
        HHGear->dX.isNegative = Gear->X.QWordValue != 0;
        Gear->X = HHGear->X;
        Gear->Y = HHGear->Y;
        HHGear->X = ufloat_int2hwFloat(Gear->Target.x);
        HHGear->Y = ufloat_int2hwFloat(Gear->Target.y);
        HHGear->State = HHGear->State | gstMoving;
        if(!(*Gear->Hedgehog).Unplaced)
        {
            Gear->State = Gear->State | gstAnimation;
        }
        (*Gear->Hedgehog).Unplaced = false;
        isCursorVisible = false;
        usound_PlaySound_1(sndWarp);
    }
    Gear->Target.x = NoPointX;
};
void ugearshandlersmess_doStepSwitcherWork(PGear Gear)
{
    PGear HHGear;
    PHedgehog hedgehog;
    LongWord State;
    LongWord switchDir;
    LongWord oldUid;
    if(CurrentHedgehog->Gear == NULL)
    {
        ugearslist_DeleteGear(Gear);
        return;
    }
    AllInactive = false;
    if(((Gear->Message & ~(gmSwitch | gmPrecise)) != 0) || (TurnTimeLeft == 0))
    {
        hedgehog = Gear->Hedgehog;
        uammos_ApplyAmmoChanges(&((*hedgehog)));
        HHGear = CurrentHedgehog->Gear;
        uammos_ApplyAmmoChanges(&((*HHGear->Hedgehog)));
        ugearslist_DeleteGear(Gear);
        bShowSwitcher = false;
        return;
    }
    HHGear = CurrentHedgehog->Gear;
    if((Gear->Message & gmSwitch) != 0)
    {
        oldUid = HHGear->uid;
        HHGear->Message = HHGear->Message & ~gmSwitch;
        Gear->Message = Gear->Message & ~gmSwitch;
        if((Gear->Message & gmPrecise) != 0)
        {
            HHGear->Message = HHGear->Message & ~gmPrecise;
            switchDir = CurrentTeam->HedgehogsNumber - 1;
        }
        else
        {
            switchDir = 1;
        }
        State = HHGear->State;
        if((HHGear->State & gstMoving) == 0)
        {
            HHGear->Active = false;
        }
        HHGear->State = HHGear->State & gstMoving;
        HHGear->Z = cHHZ;
        HHGear->Message = (HHGear->Message | gmRemoveFromList) | gmAddToList;
        usound_PlaySound_1(sndSwitchHog);
        do {
               CurrentTeam->CurrHedgehog = (CurrentTeam->CurrHedgehog + switchDir) % CurrentTeam->HedgehogsNumber;
           } while(!(((((CurrentTeam->Hedgehogs[CurrentTeam->CurrHedgehog].Gear != NULL) && ((*CurrentTeam->Hedgehogs[CurrentTeam->CurrHedgehog].Gear).Damage == 0)) && ((*CurrentTeam->Hedgehogs[CurrentTeam->CurrHedgehog].Gear).Health > 0)) && (((*CurrentTeam->Hedgehogs[CurrentTeam->CurrHedgehog].Gear).State & gstHHDeath) == 0)) && (CurrentTeam->Hedgehogs[CurrentTeam->CurrHedgehog].Effects[heFrozen] == 0)));
        uteams_SwitchCurrentHedgehog(&(CurrentTeam->Hedgehogs[CurrentTeam->CurrHedgehog]));
        AmmoMenuInvalidated = true;
        HHGear = CurrentHedgehog->Gear;
        uscript_ScriptCall_2(__str5, oldUid);
        HHGear->State = State;
        HHGear->Active = true;
        FollowGear = HHGear;
        HHGear->Z = cCurrHHZ;
        if(switchDir != 1)
        {
            HHGear->Message = HHGear->Message | gmPrecise;
        }
        HHGear->Message = (HHGear->Message | gmRemoveFromList) | gmAddToList;
    }
    ugearshedgehog_doStepHedgehogMoving(HHGear);
    Gear->X = HHGear->X;
    Gear->Y = HHGear->Y;
};
void ugearshandlersmess_doStepSwitcher(PGear Gear)
{
    PGear HHGear;
    Gear->doStep = &(ugearshandlersmess_doStepSwitcherWork);
    bShowSwitcher = true;
    HHGear = (*Gear->Hedgehog).Gear;
    uammos_OnUsedAmmo(&((*HHGear->Hedgehog)));
    {
        (*HHGear).State = (*HHGear).State & ~gstAttacking;
        (*HHGear).Message = (*HHGear).Message & ~(gmAttack | gmSwitch);
    }
};
void ugearshandlersmess_doStepMortar(PGear Gear)
{
    hwFloat dX;
    hwFloat dY;
    hwFloat gdX;
    hwFloat gdY;
    LongInt i;
    AllInactive = false;
    gdX = Gear->dX;
    gdY = Gear->dY;
    ugearshandlersmess_doStepFallingGear(Gear);
    if((Gear->State & gstCollision) != 0)
    {
        ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
        gdX.isNegative = !gdX.isNegative;
        gdY.isNegative = !gdY.isNegative;
        gdX = ufloat_hwFloat_hwFloat_op_mul(gdX, _0_2);
        gdY = ufloat_hwFloat_hwFloat_op_mul(gdY, _0_2);
        {i = 0;
         LongInt i__end__ = 4;
         if (i <= i__end__) do {
                                   dX = ufloat_hwFloat_hwFloat_op_add(gdX, ufloat_hwFloat_hwFloat_op_mul(urandom_rndSign(urandom_GetRandomf()), _0_03));
                                   dY = ufloat_hwFloat_hwFloat_op_add(gdY, ufloat_hwFloat_hwFloat_op_mul(urandom_rndSign(urandom_GetRandomf()), _0_03));
                                   ugearslist_AddGear_7(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), gtCluster, 0, dX, dY, 25);
                               } while(i++ != i__end__);}
        ugearslist_DeleteGear(Gear);
        return;
    }
    if((GameTicks & 0x3f) == 0)
    {
        uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtSmokeTrace);
    }
};
void ugearshandlersmess_doStepKamikazeWork(PGear Gear)
{
    LongWord i;
    PGear HHGear;
    PVisualGear sparkles;
    boolean hasWishes;
    astring s;
    AllInactive = false;
    hasWishes = (Gear->Message & (gmPrecise | gmSwitch)) == (gmPrecise | gmSwitch);
    if(hasWishes)
    {
        Gear->AdvBounce = 1;
    }
    HHGear = (*Gear->Hedgehog).Gear;
    if(HHGear == NULL)
    {
        ucollisions_ClearHitOrder();
        ucollisions_ClearProximityCache();
        ugearslist_DeleteGear(Gear);
        return;
    }
    HHGear->State = HHGear->State | gstNoDamage;
    ucollisions_DeleteCI(HHGear);
    Gear->X = HHGear->X;
    Gear->Y = HHGear->Y;
    if(((GameTicks % 2) == 0) && hasWishes)
    {
        sparkles = uvisualgearslist_AddVisualGear_4(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtDust, 1);
        if(sparkles != NULL)
        {
            sparkles->Tint = ((((fpcrtl_random(210) + 45) << 24) | ((fpcrtl_random(210) + 45) << 16)) | ((fpcrtl_random(210) + 45) << 8)) | 0xff;
            sparkles->Angle = fpcrtl_random(360);
        }
    }
    i = 2;
    do {
           Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, HHGear->dX);
           Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, HHGear->dY);
           HHGear->X = Gear->X;
           HHGear->Y = Gear->Y;
           if(ugearsutils_CheckGearDrowning(&(HHGear)))
           {
               ugearshedgehog_AfterAttack();
               ucollisions_ClearHitOrder();
               ucollisions_ClearProximityCache();
               ugearslist_DeleteGear(Gear);
               return;
           }
           Gear->Damage += 2;
           --i;
       } while(!((i == 0) || (Gear->Damage > Gear->Health)));
    ++upd;
    if(upd > 3)
    {
        if(Gear->Health < 1500)
        {
            if(Gear->AdvBounce != 0)
            {
                Gear->Pos = 3;
            }
            else
            {
                Gear->Pos = 2;
            }
        }
        ugearsutils_AmmoShoveCache(Gear, Gear->Boom, 40);
        ulandgraphics_DrawTunnel(ufloat_hwFloat_hwFloat_op_sub(HHGear->X, ufloat_hwFloat_LongInt_op_mul(HHGear->dX, 10)), ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_sub(ufloat_hwFloat_hwFloat_op_sub(HHGear->Y, _2), ufloat_hwFloat_LongInt_op_mul(HHGear->dY, 10)), ufloat_hwFloat_LongInt_op_mul(ufloat_hwAbs(HHGear->dY), 2)), HHGear->dX, HHGear->dY, 20 + (cHHRadius * 2), (cHHRadius * 2) + 7);
        upd = 0;
    }
    ++Gear->Timer;
    if((Gear->Timer % 100) == 0)
    {
        ucollisions_RefillProximityCache(Gear, 300);
    }
    if(Gear->Health < Gear->Damage)
    {
        ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
        if(hasWishes)
        {
            {i = 0;
             LongWord i__end__ = 31;
             if (i <= i__end__) do {
                                       sparkles = uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtStraightShot);
                                       if(sparkles != NULL)
                                       {
                                           {
                                               (*sparkles).Tint = ((((fpcrtl_random(210) + 45) << 24) | ((fpcrtl_random(210) + 45) << 16)) | ((fpcrtl_random(210) + 45) << 8)) | 0xff;
                                               (*sparkles).Angle = fpcrtl_random(360);
                                               (*sparkles).dX = 1.0e-3 * fpcrtl_random(200);
                                               (*sparkles).dY = 1.0e-3 * fpcrtl_random(200);
                                               if(fpcrtl_random(2) == 0)
                                               {
                                                   (*sparkles).dX = -(*sparkles).dX;
                                               }
                                               if(fpcrtl_random(2) == 0)
                                               {
                                                   (*sparkles).dY = -(*sparkles).dY;
                                               }
                                               (*sparkles).FrameTicks = fpcrtl_random(400) + 250;
                                           }
                                       }
                                   } while(i++ != i__end__);}
        }
        s = fpcrtl_str2astr((*Gear->Hedgehog).Name);
        ucaptions_AddCaption(ulocale_FormatA_2(ulocale_GetEventString(eidKamikaze), s), capcolDefault, capgrpMessage);
        ustats_HedgehogSacrificed(Gear->Hedgehog);
        ugearshedgehog_AfterAttack();
        HHGear->Message = HHGear->Message | gmDestroy;
        ucollisions_ClearHitOrder();
        ucollisions_ClearProximityCache();
        ugearslist_DeleteGear(Gear);
    }
    else
    {
        Gear->Health -= Gear->Damage;
        Gear->Damage = 0;
    }
};
void ugearshandlersmess_doStepKamikazeIdle(PGear Gear)
{
    PGear HHGear;
    AllInactive = false;
    --Gear->Timer;
    HHGear = (*Gear->Hedgehog).Gear;
    if((HHGear == NULL) || (HHGear->Damage != 0))
    {
        if(HHGear != NULL)
        {
            ugearshedgehog_AfterAttack();
        }
        ucollisions_ClearHitOrder();
        ucollisions_ClearProximityCache();
        ugearslist_DeleteGear(Gear);
        return;
    }
    if(Gear->Timer == 0)
    {
        Gear->Pos = 1;
        usound_PlaySoundV_2(sndKamikaze, (*(*Gear->Hedgehog).Team).voicepack);
        ucollisions_ClearHitOrder();
        ucollisions_RefillProximityCache(Gear, 300);
        Gear->doStep = &(ugearshandlersmess_doStepKamikazeWork);
    }
};
void ugearshandlersmess_doStepKamikaze(PGear Gear)
{
    PGear HHGear;
    AllInactive = false;
    HHGear = (*Gear->Hedgehog).Gear;
    HHGear->dX = Gear->dX;
    HHGear->dY = Gear->dY;
    Gear->dX = ufloat_SignAs(_0_45, Gear->dX);
    Gear->dY = ufloat_hwFloat_op_sub(_0_9);
    Gear->Timer = 550;
    Gear->doStep = &(ugearshandlersmess_doStepKamikazeIdle);
};
void ugearshandlersmess_doStepCakeExpl(PGear Gear)
{
    PGear gi;
    AllInactive = false;
    ++Gear->Tag;
    if(Gear->Tag < 2250)
    {
        return;
    }
    InCinematicMode = false;
    gi = GearsList;
    while(gi != NULL)
    {
        if(gi->Kind == gtHedgehog)
        {
            gi->State = gi->State & ~gstLoser;
        }
        gi = gi->NextGear;
    }
    ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
    ugearshedgehog_AfterAttack();
    ugearslist_DeleteGear(Gear);
};
void ugearshandlersmess_doStepCakeDown(PGear Gear)
{
    PGear gi;
    LongInt dmg;
    LongInt dmgBase;
    LongInt partyEpicness;
    LongInt i;
    hwFloat fX;
    hwFloat fY;
    hwFloat tdX;
    hwFloat tdY;
    PVisualGear sparkles;
    AllInactive = false;
    ++Gear->Tag;
    if(Gear->Tag < 100)
    {
        return;
    }
    Gear->Tag = 0;
    if(Gear->Pos == 0)
    {
        fX = ufloat_int2hwFloat(ufloat_hwRound(Gear->X));
        fY = ufloat_int2hwFloat(ufloat_hwRound(Gear->Y));
        dmgBase = (Gear->Boom << 1) + (cHHRadius / 2);
        partyEpicness = 0;
        gi = GearsList;
        while(gi != NULL)
        {
            if(gi->Kind == gtHedgehog)
            {
                dmg = 0;
                tdX = ufloat_hwFloat_hwFloat_op_sub(gi->X, fX);
                tdY = ufloat_hwFloat_hwFloat_op_sub(gi->Y, fY);
                if(ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ufloat_hwAbs(tdX), ufloat_hwAbs(tdY))) < dmgBase)
                {
                    dmg = dmgBase - uutils_Max(ufloat_hwRound(ufloat_Distance(tdX, tdY)), gi->Radius);
                }
                if(dmg > 1)
                {
                    dmg = ugearsutils_ModifyDamage(uutils_Min(dmg / 2, Gear->Boom), gi);
                }
                if(dmg > 1)
                {
                    if((CurrentHedgehog->Gear == gi) && ((*gi->Hedgehog).Effects[heInvulnerable] == 0))
                    {
                        gi->State = gi->State | gstLoser;
                        partyEpicness -= 45;
                    }
                    else
                    {
                        gi->State = gi->State | gstWinner;
                        if(CurrentHedgehog->Gear == gi)
                        {
                            partyEpicness -= 45;
                        }
                        else
                        {
                            ++partyEpicness;
                        }
                    }
                }
            }
            gi = gi->NextGear;
        }
        Gear->doStep = &(ugearshandlersmess_doStepCakeExpl);
        if((partyEpicness > 6) && (fpcrtl_abs(90 - fpcrtl_abs(fpcrtl_trunc(Gear->DirAngle))) < 20))
        {
            {i = 0;
             LongInt i__end__ = 2 * partyEpicness;
             if (i <= i__end__) do {
                                       sparkles = uvisualgearslist_AddVisualGear_4(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtEgg, 1);
                                       if(sparkles != NULL)
                                       {
                                           sparkles->dX = 8.0e-3 * (fpcrtl_random(100) - 50);
                                           sparkles->dY = -0.3 + (2.0e-3 * (fpcrtl_random(100) - 50));
                                           sparkles->Tint = ((((fpcrtl_random(210) + 45) << 24) | ((fpcrtl_random(210) + 45) << 16)) | ((fpcrtl_random(210) + 45) << 8)) | 0xff;
                                           sparkles->Angle = fpcrtl_random(360);
                                       }
                                   } while(i++ != i__end__);}
            InCinematicMode = true;
        }
        usound_PlaySound_1(sndCake);
    }
    else
    {
        --Gear->Pos;
    }
};
void ugearshandlersmess_doStepCakeWalk(PGear Gear)
{
    hwFloat tdx;
    hwFloat tdy;
    PCakeData cakeData;
    LongWord i;
    AllInactive = false;
    ++Gear->Tag;
    if(Gear->Tag < 7)
    {
        return;
    }
    --Gear->Health;
    Gear->Timer = Gear->Health * 10;
    if((Gear->Health % 100) == 0)
    {
        Gear->PortalCounter = 0;
    }
    if((Gear->Health <= 0) || ((Gear->Message & gmAttack) != 0))
    {
        FollowGear = Gear;
        Gear->RenderTimer = false;
        Gear->doStep = &(ugearshandlersmess_doStepCakeDown);
        return;
    }
    else
    {
        if(Gear->Timer < 6000)
        {
            Gear->RenderTimer = true;
        }
    }
    if(!ugearshandlers_cakeStep(Gear))
    {
        Gear->doStep = &(ugearshandlersmess_doStepCakeFall);
    }
    if(Gear->Karma == 1)
    {
        tdx = Gear->X;
        if(ufloat_hwRound(Gear->X) < leftX)
        {
            Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, ufloat_int2hwFloat(rightX - leftX));
        }
        else
        {
            Gear->X = ufloat_hwFloat_hwFloat_op_sub(Gear->X, ufloat_int2hwFloat(rightX - leftX));
        }
        Gear->Tag = 0;
        if((ucollisions_TestCollisionXwithGear(Gear, 1) != 0) || (ucollisions_TestCollisionXwithGear(Gear, -1) != 0))
        {
            Gear->X = tdx;
            Gear->Karma = 3;
        }
        else
        {
            if((ucollisions_TestCollisionYwithGear(Gear, 1) == 0) && (ucollisions_TestCollisionYwithGear(Gear, -1) == 0))
            {
                Gear->doStep = &(ugearshandlersmess_doStepCakeFall);
            }
            Gear->Karma = 4;
        }
    }
    if((Gear->Karma == 2) || (Gear->Karma == 3))
    {
        Gear->dX.isNegative = !Gear->dX.isNegative;
        Gear->WDTimer = 0;
        Gear->Angle = (((LongInt)Gear->Angle) + 2) & 3;
        if(Gear->Karma == 2)
        {
            ugearsutils_AddBounceEffectForGear_2(Gear, 0.55);
        }
        Gear->Tag = 0;
        Gear->Karma = 4;
    }
    if(Gear->Karma == 4)
    {
        cakeData = ((PCakeData)Gear->Data);
        {
            {i = 0;
             LongWord i__end__ = ((int)(cakeh) - 1);
             if (i <= i__end__) do {
                                       (*cakeData).CakePoints[i].x = Gear->X;
                                       (*cakeData).CakePoints[i].y = Gear->Y;
                                   } while(i++ != i__end__);}
            (*cakeData).CakeI = 0;
        }
        Gear->Karma = 0;
    }
    if(Gear->Tag == 0)
    {
        cakeData = ((PCakeData)Gear->Data);
        {
            (*cakeData).CakeI = ((*cakeData).CakeI + 1) % cakeh;
            tdx = ufloat_hwFloat_hwFloat_op_sub((*cakeData).CakePoints[(*cakeData).CakeI].x, Gear->X);
            tdy = ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_op_sub((*cakeData).CakePoints[(*cakeData).CakeI].y), Gear->Y);
            (*cakeData).CakePoints[(*cakeData).CakeI].x = Gear->X;
            (*cakeData).CakePoints[(*cakeData).CakeI].y = Gear->Y;
            Gear->DirAngle = uutils_DxDy2Angle(tdx, tdy);
        }
    }
};
void ugearshandlersmess_doStepCakeUp(PGear Gear)
{
    LongWord i;
    PCakeData cakeData;
    AllInactive = false;
    ++Gear->Tag;
    if((Gear->Tag < 100) && (Gear->FlightTime > 1))
    {
        return;
    }
    Gear->Tag = 0;
    if((Gear->Pos == 6) || (Gear->FlightTime <= 1))
    {
        Gear->Pos = 6;
        cakeData = ((PCakeData)Gear->Data);
        {
            {i = 0;
             LongWord i__end__ = ((int)(cakeh) - 1);
             if (i <= i__end__) do {
                                       (*cakeData).CakePoints[i].x = Gear->X;
                                       (*cakeData).CakePoints[i].y = Gear->Y;
                                   } while(i++ != i__end__);}
            (*cakeData).CakeI = 0;
        }
        if((Gear->FlightTime <= 1) && (Gear->Health > 2))
        {
            --Gear->Health;
        }
        Gear->FlightTime = 0;
        Gear->doStep = &(ugearshandlersmess_doStepCakeWalk);
    }
    else
    {
        ++Gear->Pos;
    }
};
void ugearshandlersmess_doStepCakeFall(PGear Gear)
{
    AllInactive = false;
    Gear->dY = ufloat_hwFloat_hwFloat_op_add(Gear->dY, cGravity);
    ++Gear->FlightTime;
    if(ucollisions_TestCollisionYwithGear(Gear, 1) != 0)
    {
        Gear->doStep = &(ugearshandlersmess_doStepCakeUp);
    }
    else
    {
        Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, Gear->dY);
        if(ugearsutils_CheckGearDrowning(&(Gear)))
        {
            ugearshedgehog_AfterAttack();
        }
    }
};
void ugearshandlersmess_doStepCake(PGear Gear)
{
    AllInactive = false;
    Gear->CollisionMask = lfNotCurHogCrate;
    Gear->dY = ufloat_hwFloat_LongInt_op_mul(cMaxWindSpeed, 100);
    Gear->doStep = &(ugearshandlersmess_doStepCakeFall);
};
void ugearshandlersmess_doStepSeductionWork(PGear Gear)
{
    LongInt i;
    PGearArrayS hits;
    PGear HHGear;
    AllInactive = false;
    HHGear = (*Gear->Hedgehog).Gear;
    if((HHGear != NULL) && ((HHGear->State & gstHHDriven) == 0))
    {
        usound_StopSound_1(sndYoohoo);
        ugearshedgehog_AfterAttack();
        ugearslist_DeleteGear(Gear);
        return;
    }
    hits = ugearsutils_GearsNear(Gear->X, Gear->Y, gtHedgehog, Gear->Radius);
    if(hits.size > 0)
    {
        {i = 0;
         LongInt i__end__ = hits.size - 1;
         if (i <= i__end__) do {
                                   {
                                       if(((*hits.ar)[i] != CurrentHedgehog->Gear) && ((*(*hits.ar)[i]).Hedgehog->Effects[heFrozen] == 0))
                                       {
                                           if((WorldEdge != weWrap) || !(ufloat_hwFloat_hwFloat_op_gt(ufloat_hwAbs(ufloat_hwFloat_hwFloat_op_sub(Gear->X, (*(*hits.ar)[i]).X)), ufloat_int2hwFloat(Gear->Radius))))
                                           {
                                               (*(*hits.ar)[i]).dX = ufloat_hwFloat_hwFloat_op_div(ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_mul(_50, cGravity), ufloat_hwFloat_hwFloat_op_sub(Gear->X, (*(*hits.ar)[i]).X)), _25);
                                           }
                                           else
                                           {
                                               if(!(ufloat_hwFloat_hwFloat_op_gt(ufloat_hwAbs(ufloat_hwFloat_hwFloat_op_sub(ufloat_hwFloat_hwFloat_op_add(Gear->X, ufloat_int2hwFloat(rightX - leftX)), (*(*hits.ar)[i]).X)), ufloat_int2hwFloat(Gear->Radius))))
                                               {
                                                   (*(*hits.ar)[i]).dX = ufloat_hwFloat_hwFloat_op_div(ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_mul(_50, cGravity), ufloat_hwFloat_hwFloat_op_sub(ufloat_hwFloat_hwFloat_op_add(Gear->X, ufloat_int2hwFloat(rightX - leftX)), (*(*hits.ar)[i]).X)), _25);
                                               }
                                               else
                                               {
                                                   (*(*hits.ar)[i]).dX = ufloat_hwFloat_hwFloat_op_div(ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_mul(_50, cGravity), ufloat_hwFloat_hwFloat_op_sub(ufloat_hwFloat_hwFloat_op_sub(Gear->X, ufloat_int2hwFloat(rightX - leftX)), (*(*hits.ar)[i]).X)), _25);
                                               }
                                           }
                                           (*(*hits.ar)[i]).dY = ufloat_hwFloat_LongInt_op_mul(ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_op_sub(_450), cMaxWindSpeed), 2);
                                           (*(*hits.ar)[i]).Active = true;
                                       }
                                       else
                                       {
                                           if((*(*hits.ar)[i]).Hedgehog->Effects[heFrozen] > 255)
                                           {
                                               (*(*hits.ar)[i]).Hedgehog->Effects[heFrozen] = 255;
                                           }
                                       }
                                   }
                               } while(i++ != i__end__);}
    }
    hits = ugearsutils_GearsNear(Gear->X, Gear->Y, gtSentry, Gear->Radius);
    if(hits.size > 0)
    {
        {i = 0;
         LongInt i__end__ = hits.size - 1;
         if (i <= i__end__) do {
                                   {
                                       if((Gear->Hedgehog != NULL) && ((*(*hits.ar)[i]).Hedgehog != Gear->Hedgehog))
                                       {
                                           (*(*hits.ar)[i]).dX = ufloat_SignAs(_0, (*(*hits.ar)[i]).dX);
                                           (*(*hits.ar)[i]).dY = ufloat_hwFloat_op_sub(_0_15);
                                           (*(*hits.ar)[i]).Hedgehog = Gear->Hedgehog;
                                           ugearshandlersmess_ResetSentryState((*hits.ar)[i], 0, 10000);
                                       }
                                   }
                               } while(i++ != i__end__);}
    }
    ugearshedgehog_AfterAttack();
    ugearslist_DeleteGear(Gear);
};
void ugearshandlersmess_doStepSeductionWear(PGear Gear)
{
    PVisualGear heart;
    PGear HHGear;
    AllInactive = false;
    HHGear = (*Gear->Hedgehog).Gear;
    if((HHGear != NULL) && ((HHGear->State & gstHHDriven) == 0))
    {
        usound_StopSound_1(sndYoohoo);
        ugearshedgehog_AfterAttack();
        ugearslist_DeleteGear(Gear);
        return;
    }
    ++Gear->Timer;
    if(Gear->Timer > 250)
    {
        Gear->Timer = 0;
        ++Gear->Pos;
        if(Gear->Pos == 5)
        {
            usound_PlaySound_1(sndYoohoo);
        }
        if(Gear->Pos == 14)
        {
            usound_PlaySound_1(sndKiss);
        }
    }
    if((Gear->Pos == 14) && ((GameTicks & 0x1) == 0))
    {
        heart = uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtStraightShot);
        if(heart != NULL)
        {
            {
                (*heart).dX = 1.0e-3 * fpcrtl_random(201);
                (*heart).dY = 1.0e-3 * fpcrtl_random(201);
                if(fpcrtl_random(2) == 0)
                {
                    if(0.2 < ((*heart).dX + (*heart).dY))
                    {
                        (*heart).dY = 0.2 - (*heart).dY;
                        (*heart).dX = 0.2 - (*heart).dX;
                    }
                    (*heart).dX = (*heart).dX + (((*heart).dX /(float) 0.2) * ((0.2 * sin(pi * ((0.2 - (*heart).dY) /(float) 0.4))) - (0.2 - (*heart).dY)));
                    (*heart).dY = -(*heart).dY;
                }
                else
                {
                    (*heart).dY = (*heart).dY * (0.3 + (0.7 * sin((pi * (*heart).dX) /(float) 0.2)));
                }
                if(fpcrtl_random(2) == 0)
                {
                    (*heart).dX = -(*heart).dX;
                }
                (*heart).FrameTicks = fpcrtl_random(750) + 1000;
                (*heart).State = (sprSeduction);
            }
        }
    }
    if(Gear->Pos == 15)
    {
        Gear->doStep = &(ugearshandlersmess_doStepSeductionWork);
    }
};
void ugearshandlersmess_doStepSeduction(PGear Gear)
{
    AllInactive = false;
    Gear->doStep = &(ugearshandlersmess_doStepSeductionWear);
};
void ugearshandlersmess_doStepWaterUp(PGear Gear)
{
    LongWord i;
    if((Gear->Tag == 0) || (cWaterLine == 0))
    {
        ugearslist_DeleteGear(Gear);
        return;
    }
    AllInactive = false;
    ++Gear->Timer;
    if(Gear->Timer == 17)
    {
        Gear->Timer = 0;
    }
    else
    {
        return;
    }
    if((WorldEdge == weSea) && (playWidth > cMinPlayWidth))
    {
        ++leftX;
        --rightX;
        playWidth -= 2;
        {i = 0;
         LongWord i__end__ = LAND_HEIGHT - 1;
         if (i <= i__end__) do {
                                   ulandutils_LandSet(i, leftX, 0);
                                   ulandutils_LandSet(i, rightX, 0);
                               } while(i++ != i__end__);}
    }
    if(cWaterLine > 0)
    {
        --cWaterLine;
        {i = 0;
         LongWord i__end__ = LAND_WIDTH - 1;
         if (i <= i__end__) do {
                                   ulandutils_LandSet(cWaterLine, i, 0);
                               } while(i++ != i__end__);}
        ugearsutils_SetAllToActive();
    }
    --Gear->Tag;
};
void ugearshandlersmess_doStepDrillDrilling(PGear Gear)
{
    PGearArray t;
    Word tempColl;
    ugearsutils_WorldWrap(&(Gear));
    AllInactive = false;
    if((Gear->Timer > 0) && ((Gear->Timer % 10) != 0))
    {
        --Gear->Timer;
        return;
    }
    ulandgraphics_DrawTunnel(Gear->X, Gear->Y, Gear->dX, Gear->dY, 2, 6);
    Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, Gear->dX);
    Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, Gear->dY);
    if((Gear->Timer % 30) == 0)
    {
        uvisualgearslist_AddVisualGear_3(ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(Gear->X, ufloat_hwFloat_hwFloat_op_mul(_20, Gear->dX))), ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(Gear->Y, ufloat_hwFloat_hwFloat_op_mul(_20, Gear->dY))), vgtDust);
    }
    if(ugearsutils_CheckGearDrowning(&(Gear)))
    {
        usound_StopSoundChan_1(Gear->SoundChannel);
        return;
    }
    tempColl = Gear->CollisionMask;
    Gear->CollisionMask = lfObjMask;
    if(((ucollisions_TestCollisionYwithGear(Gear, ufloat_hwSign(Gear->dY)) != 0) || (ucollisions_TestCollisionXwithGear(Gear, ufloat_hwSign(Gear->dX)) != 0)) || (GameTicks > Gear->FlightTime))
    {
        t = ucollisions_CheckGearsCollision(Gear);
    }
    else
    {
        t = NULL;
    }
    Gear->CollisionMask = tempColl;
    if((((Gear->Timer == 0) || ((t != NULL) && (t->Count != 0))) || ((((Gear->State & gsttmpFlag) == 0) && (ucollisions_TestCollisionYwithGear(Gear, ufloat_hwSign(Gear->dY)) == 0)) && (ucollisions_TestCollisionXwithGear(Gear, ufloat_hwSign(Gear->dX)) == 0))) || !ulandgraphics_CheckLandValue(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), lfIndestructible))
    {
        usound_StopSoundChan_1(Gear->SoundChannel);
        ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
        ugearslist_DeleteGear(Gear);
        return;
    }
    else
    {
        if((ucollisions_TestCollisionYwithGear(Gear, ufloat_hwSign(Gear->dY)) == 0) && (ucollisions_TestCollisionXwithGear(Gear, ufloat_hwSign(Gear->dX)) == 0))
        {
            usound_StopSoundChan_1(Gear->SoundChannel);
            Gear->Tag = 1;
            Gear->AdvBounce = 50;
            Gear->doStep = &(ugearshandlersmess_doStepDrill);
        }
    }
    --Gear->Timer;
};
void ugearshandlersmess_doStepDrill(PGear Gear)
{
    PGearArray t;
    hwFloat oldX;
    hwFloat oldY;
    hwFloat oldDx;
    hwFloat oldDy;
    hwFloat t2;
    AllInactive = false;
    if(((Gear->State & gsttmpFlag) == 0) && ((GameFlags & gfMoreWind) == 0))
    {
        Gear->dX = ufloat_hwFloat_hwFloat_op_add(Gear->dX, cWindSpeed);
    }
    oldDx = Gear->dX;
    oldDy = Gear->dY;
    oldX = Gear->X;
    oldY = Gear->Y;
    ugearshandlersmess_doStepFallingGear(Gear);
    if((GameTicks & 0x3f) == 0)
    {
        uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtSmokeTrace);
    }
    if((Gear->State & gstCollision) != 0)
    {
        Gear->dX = oldDx;
        Gear->dY = oldDy;
        Gear->X = oldX;
        Gear->Y = oldY;
        if(GameTicks > Gear->FlightTime)
        {
            t = ucollisions_CheckGearsCollision(Gear);
        }
        else
        {
            t = NULL;
        }
        if((t == NULL) || (t->Count == 0))
        {
            t2 = ufloat_hwFloat_hwFloat_op_div(_0_5, ufloat_Distance(Gear->dX, Gear->dY));
            Gear->dX = ufloat_hwFloat_hwFloat_op_mul(Gear->dX, t2);
            Gear->dY = ufloat_hwFloat_hwFloat_op_mul(Gear->dY, t2);
        }
        else
        {
            if(t != NULL)
            {
                ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
                ugearslist_DeleteGear(Gear);
                return;
            }
        }
        Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, ufloat_hwFloat_LongInt_op_mul(Gear->dX, 4));
        Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, ufloat_hwFloat_LongInt_op_mul(Gear->dY, 4));
        Gear->SoundChannel = usound_LoopSound_1(sndDrillRocket);
        Gear->Pos = 1;
        Gear->doStep = &(ugearshandlersmess_doStepDrillDrilling);
        if((Gear->State & gsttmpFlag) != 0)
        {
            Gear->RenderTimer = true;
        }
        if(Gear->Timer > 0)
        {
            --Gear->Timer;
        }
    }
    else
    {
        if(((Gear->State & gsttmpFlag) != 0) && (Gear->Tag != 0))
        {
            if(Gear->Timer > 0)
            {
                --Gear->Timer;
            }
            else
            {
                ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
                ugearslist_DeleteGear(Gear);
            }
        }
    }
};
void ugearshandlersmess_doStepBallgunWork(PGear Gear)
{
    PGear HHGear;
    PGear ball;
    hwFloat rx;
    hwFloat ry;
    LongInt gX;
    LongInt gY;
    AllInactive = false;
    --Gear->Timer;
    HHGear = (*Gear->Hedgehog).Gear;
    if(HHGear == NULL)
    {
        ugearslist_DeleteGear(Gear);
        return;
    }
    ugearshedgehog_HedgehogChAngle(HHGear);
    gX = ufloat_hwRound(Gear->X) + uutils_GetLaunchX(amBallgun, ufloat_hwSign(HHGear->dX), HHGear->Angle);
    gY = ufloat_hwRound(Gear->Y) + uutils_GetLaunchY(amBallgun, HHGear->Angle);
    if((Gear->Timer % 100) == 0)
    {
        rx = urandom_rndSign(ufloat_hwFloat_hwFloat_op_mul(urandom_GetRandomf(), _0_1));
        ry = urandom_rndSign(ufloat_hwFloat_hwFloat_op_mul(urandom_GetRandomf(), _0_1));
        ball = ugearslist_AddGear_7(gX, gY, gtBall, 0, ufloat_hwFloat_hwFloat_op_add(ufloat_SignAs(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleSin(HHGear->Angle), _0_8), HHGear->dX), rx), ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleCos(HHGear->Angle), ufloat_hwFloat_op_sub(_0_8)), ry), 0);
        ball->CollisionMask = lfNotCurHogCrate;
        usound_PlaySound_1(sndGun);
    }
    if((Gear->Timer == 0) || ((HHGear->State & gstHHDriven) == 0))
    {
        HHGear->State = HHGear->State & ~gstNotKickable;
        ugearslist_DeleteGear(Gear);
        ugearshedgehog_AfterAttack();
    }
};
void ugearshandlersmess_doStepBallgun(PGear Gear)
{
    PGear HHGear;
    HHGear = (*Gear->Hedgehog).Gear;
    HHGear->Message = HHGear->Message & ~(gmUp | gmDown);
    HHGear->State = HHGear->State | gstNotKickable;
    Gear->doStep = &(ugearshandlersmess_doStepBallgunWork);
};
void ugearshandlersmess_doStepRCPlaneWork(PGear Gear)
{
    enum{cAngleSpeed = 3};
    PGear HHGear;
    LongInt i;
    astring s;
    hwFloat dX;
    hwFloat dY;
    boolean fChanged;
    LongWord trueAngle;
    PGear t;
    if(ugearsutils_WorldWrap(&(Gear)))
    {
        if(WorldEdge == weBounce)
        {
            Gear->Angle = 4096 - Gear->Angle;
        }
        else
        {
            if(WorldEdge == weSea)
            {
                if(Gear->Angle < 2048)
                {
                    Gear->Angle = 4096 - Gear->Angle;
                }
                Gear->Angle = (Gear->Angle + 1024) % 4096;
            }
        }
    }
    AllInactive = false;
    HHGear = (*Gear->Hedgehog).Gear;
    FollowGear = Gear;
    if(Gear->Timer > 0)
    {
        if(Gear->Timer == 1)
        {
            usound_StopSoundChan_1(Gear->SoundChannel);
            Gear->SoundChannel = -1;
        }
        --Gear->Timer;
    }
    fChanged = false;
    if(((HHGear == NULL) || ((HHGear->State & gstHHDriven) == 0)) || (Gear->Timer == 0))
    {
        fChanged = true;
        if(Gear->Angle > 2048)
        {
            --Gear->Angle;
        }
        else
        {
            if(Gear->Angle < 2048)
            {
                ++Gear->Angle;
            }
            else
            {
                fChanged = false;
            }
        }
    }
    else
    {
        if((Gear->Message & gmLeft) != 0)
        {
            fChanged = true;
            Gear->Angle = (Gear->Angle + (4096 - cAngleSpeed)) % 4096;
        }
        if((Gear->Message & gmRight) != 0)
        {
            fChanged = true;
            Gear->Angle = (Gear->Angle + cAngleSpeed) % 4096;
        }
    }
    if(fChanged)
    {
        Gear->dX.isNegative = Gear->Angle > 2048;
        if(Gear->dX.isNegative)
        {
            trueAngle = 4096 - Gear->Angle;
        }
        else
        {
            trueAngle = Gear->Angle;
        }
        Gear->dX = ufloat_hwFloat_hwFloat_op_mul(ufloat_SignAs(ufloat_AngleSin(trueAngle), Gear->dX), _0_25);
        Gear->dY = ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleCos(trueAngle), ufloat_hwFloat_op_sub(_0_25));
    }
    Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, Gear->dX);
    Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, Gear->dY);
    if((GameTicks & 0xff) == 0)
    {
        if(Gear->Timer < 3500)
        {
            uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtEvilTrace);
        }
        else
        {
            uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtSmokeTrace);
        }
    }
    if((HHGear != NULL) && ((HHGear->Message & gmAttack) != 0))
    {
        if(Gear->Health != 0)
        {
            HHGear->Message = HHGear->Message & ~gmAttack;
            ugearslist_AddGear_7(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), gtAirBomb, 0, ufloat_hwFloat_hwFloat_op_mul(Gear->dX, _0_5), ufloat_hwFloat_hwFloat_op_mul(Gear->dY, _0_5), 0);
            --Gear->Health;
        }
        s = fpcrtl_str2astr(uutils_IntToStr(Gear->Health));
        ucaptions_AddCaption(ulocale_FormatA_2(trmsg[sidRemaining], s), capcolDefault, capgrpAmmostate);
    }
    if(((HHGear != NULL) && ((HHGear->Message & gmLJump) != 0)) && ((Gear->State & gsttmpFlag) == 0))
    {
        Gear->State = Gear->State | gsttmpFlag;
        usound_PlayMusicSound(sndRideOfTheValkyries);
        InCinematicMode = true;
    }
    t = ugearsutils_CheckGearNear_4(Gear, gtCase, 36, 36);
    if((t != NULL) && (HHGear != NULL))
    {
        ugearshedgehog_PickUp(HHGear, t);
    }
    ugearsutils_CheckCollision(Gear);
    if(((Gear->State & gstCollision) != 0) || ugearsutils_CheckGearDrowning(&(Gear)))
    {
        InCinematicMode = false;
        usound_StopSoundChan_1(Gear->SoundChannel);
        usound_StopMusicSound(sndRideOfTheValkyries);
        if((Gear->State & gstCollision) != 0)
        {
            ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
            {i = 0;
             LongInt i__end__ = 15;
             if (i <= i__end__) do {
                                       dX = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleCos(i * 64), _0_5), ufloat_hwFloat_hwFloat_op_add(urandom_GetRandomf(), _1));
                                       dY = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleSin(i * 64), _0_5), ufloat_hwFloat_hwFloat_op_add(urandom_GetRandomf(), _1));
                                       ugearslist_AddGear_7(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), gtFlame, 0, dX, dY, 0);
                                       ugearslist_AddGear_7(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), gtFlame, 0, dX, ufloat_hwFloat_op_sub(dY), 0);
                                   } while(i++ != i__end__);}
            if(HHGear != NULL)
            {
                HHGear->State = HHGear->State & ~gstNotKickable;
            }
            ugearslist_DeleteGear(Gear);
        }
        ugearshedgehog_AfterAttack();
        CurAmmoGear = NULL;
        if((GameFlags & gfInfAttack) == 0)
        {
            if(TagTurnTimeLeft == 0)
            {
                TagTurnTimeLeft = TurnTimeLeft;
            }
            TurnTimeLeft = 14 * 125;
        }
        if(HHGear != NULL)
        {
            HHGear->Message = 0;
            ugearshedgehog_PlayTaunt(1);
        }
    }
};
void ugearshandlersmess_doStepRCPlane(PGear Gear)
{
    PGear HHGear;
    HHGear = (*Gear->Hedgehog).Gear;
    HHGear->Message = 0;
    HHGear->State = HHGear->State | gstNotKickable;
    Gear->Angle = HHGear->Angle;
    Gear->Tag = ufloat_hwSign(HHGear->dX);
    if(HHGear->dX.isNegative)
    {
        Gear->Angle = 4096 - Gear->Angle;
    }
    Gear->doStep = &(ugearshandlersmess_doStepRCPlaneWork);
};
void ugearshandlersmess_doStepJetpackWork(PGear Gear)
{
    PGear HHGear;
    LongInt fuel;
    LongInt i;
    hwFloat move;
    boolean isUnderwater;
    PVisualGear bubble;
    isUnderwater = ucollisions_CheckCoordInWater(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y) + Gear->Radius);
    if(Gear->Pos > 0)
    {
        --Gear->Pos;
    }
    AllInactive = false;
    HHGear = (*Gear->Hedgehog).Gear;
    move = _0_2;
    fuel = 50;
    if((HHGear->Message & gmPrecise) != 0)
    {
        ugearshedgehog_HedgehogChAngle(HHGear);
    }
    else
    {
        if((Gear->Health > 0) || (Gear->Health == JETPACK_FUEL_INFINITE))
        {
            if((HHGear->Message & gmUp) != 0)
            {
                if(!HHGear->dY.isNegative || (ufloat_hwFloat_hwFloat_op_gt(HHGear->Y, ufloat_hwFloat_op_sub(_256))))
                {
                    if(isUnderwater)
                    {
                        HHGear->dY = ufloat_hwFloat_hwFloat_op_sub(HHGear->dY, ufloat_hwFloat_hwFloat_op_mul(move, _0_7));
                        {i = fpcrtl_random(10) + 10;
                         LongInt i__end__ = 0;
                         if (i >= i__end__) do {
                                                   bubble = uvisualgearslist_AddVisualGear_3((ufloat_hwRound(HHGear->X) - 8) + fpcrtl_random(16), (ufloat_hwRound(HHGear->Y) + 16) + fpcrtl_random(8), vgtBubble);
                                                   if(bubble != NULL)
                                                   {
                                                       bubble->dY = (fpcrtl_random(20) /(float) 10) + 0.1;
                                                   }
                                               } while(i-- != i__end__);}
                    }
                    else
                    {
                        usound_PlaySound_1(sndJetpackBoost);
                        HHGear->dY = ufloat_hwFloat_hwFloat_op_sub(HHGear->dY, move);
                    }
                }
                if(Gear->Health != JETPACK_FUEL_INFINITE)
                {
                    Gear->Health -= fuel;
                }
                Gear->MsgParam = Gear->MsgParam | gmUp;
                Gear->Timer = GameTicks;
            }
            move.isNegative = (HHGear->Message & gmLeft) != 0;
            if((HHGear->Message & (gmLeft | gmRight)) != 0)
            {
                HHGear->dX = ufloat_hwFloat_hwFloat_op_add(HHGear->dX, ufloat_hwFloat_hwFloat_op_mul(move, _0_1));
                if(isUnderwater)
                {
                    {i = fpcrtl_random(5) + 5;
                     LongInt i__end__ = 0;
                     if (i >= i__end__) do {
                                               bubble = uvisualgearslist_AddVisualGear_3(ufloat_hwRound(HHGear->X) + fpcrtl_random(8), (ufloat_hwRound(HHGear->Y) - 8) + fpcrtl_random(16), vgtBubble);
                                               if(bubble != NULL)
                                               {
                                                   bubble->dX = ((fpcrtl_random(10) /(float) 10) + 2.0e-2) * -1;
                                                   if(move.isNegative)
                                                   {
                                                       bubble->X = bubble->X + 28;
                                                       bubble->dX = bubble->dX * -1;
                                                   }
                                                   else
                                                   {
                                                       bubble->X = bubble->X - 28;
                                                   }
                                               }
                                           } while(i-- != i__end__);}
                }
                else
                {
                    usound_PlaySound_1(sndJetpackBoost);
                }
                if(Gear->Health != JETPACK_FUEL_INFINITE)
                {
                    Gear->Health -= fuel / 5;
                }
                Gear->MsgParam = Gear->MsgParam | (HHGear->Message & (gmLeft | gmRight));
                Gear->Timer = GameTicks;
            }
        }
    }
    if((Gear->Timer != 0) && ((((int64_t) (GameTicks)) - ((int64_t) (Gear->Timer))) > 250))
    {
        Gear->Timer = 0;
        Gear->MsgParam = 0;
    }
    if((Gear->Health < 0) && (Gear->Health != JETPACK_FUEL_INFINITE))
    {
        Gear->Health = 0;
    }
    i = Gear->Health / 20;
    if((!cOnlyStats && (i != Gear->Damage)) && ((GameTicks & 0x3f) == 0))
    {
        Gear->Damage = i;
        utextures_FreeAndNilTexture(&(Gear->Tex));
        if(Gear->Health != JETPACK_FUEL_INFINITE)
        {
            Gear->Tex = urenderutils_RenderStringTex(ulocale_FormatA_2(trmsg[sidFuel], fpcrtl_str2astr(uutils_IntToStr(i))), cWhiteColor, fntSmall);
        }
    }
    if((((HHGear->Message & (((gmAttack | gmUp) | gmLeft) | gmRight)) != 0) && ((HHGear->Message & gmPrecise) == 0)) && ((Gear->State & gsttmpFlag) != 0))
    {
        Gear->State = Gear->State & ~gsttmpFlag;
        HHGear->dX = Gear->dX;
    }
    if((HHGear->Message & gmPrecise) == 0)
    {
        HHGear->Message = HHGear->Message & ~((gmUp | gmLeft) | gmRight);
    }
    HHGear->State = HHGear->State | gstMoving;
    Gear->X = HHGear->X;
    Gear->Y = HHGear->Y;
    if((!isUnderwater && hasBorder) && ((ufloat_hwFloat_hwFloat_op_lt(HHGear->X, _0)) || (ufloat_hwRound(HHGear->X) > LAND_WIDTH)))
    {
        HHGear->dY.isNegative = false;
    }
    if(((Gear->State & gsttmpFlag) == 0) || (ufloat_hwFloat_hwFloat_op_lt(HHGear->dY, _0)))
    {
        ugearshedgehog_doStepHedgehogMoving(HHGear);
    }
    else
    {
        HHGear->dX = ufloat_SignAs(_0, HHGear->dX);
    }
    if(((((HHGear->Damage != 0) || ((cWaterLine + (cVisibleWater * 4)) < ufloat_hwRound(HHGear->Y))) || (TurnTimeLeft == 0)) || ((((GameTicks & 0x1ff) == 0) && !HHGear->dY.isNegative) && (ucollisions_TestCollisionYwithGear(HHGear, 1) != 0))) || ((Gear->Message & gmAttack) != 0))
    {
        {
            (*HHGear).Message = 0;
            (*HHGear).Active = true;
            (*HHGear).State = (*HHGear).State | gstMoving;
        }
        if(((uammos_GetAmmoEntry(&((*HHGear->Hedgehog)), amJetpack)->Count >= 1) && ((Ammoz[(*HHGear->Hedgehog).CurAmmoType].Ammo.Propz & ammoprop_AltUse) != 0)) && ((*HHGear->Hedgehog).MultiShootAttacks == 0))
        {
            (*HHGear->Hedgehog).CurAmmoType = amJetpack;
        }
        isCursorVisible = false;
        uammos_ApplyAmmoChanges(&((*HHGear->Hedgehog)));
        ugearslist_DeleteGear(Gear);
    }
};
void ugearshandlersmess_doStepJetpack(PGear Gear)
{
    PGear HHGear;
    Gear->Pos = 0;
    Gear->doStep = &(ugearshandlersmess_doStepJetpackWork);
    HHGear = (*Gear->Hedgehog).Gear;
    usound_PlaySound_1(sndJetpackLaunch);
    FollowGear = HHGear;
    ugearshedgehog_AfterAttack();
    {
        (*HHGear).State = (*HHGear).State & ~gstAttacking;
        (*HHGear).Message = (*HHGear).Message & ~((((gmAttack | gmUp) | gmPrecise) | gmLeft) | gmRight);
        if((ufloat_hwFloat_hwFloat_op_lt((*HHGear).dY, _0_1)) && (ufloat_hwFloat_hwFloat_op_gt((*HHGear).dY, ufloat_hwFloat_op_sub(_0_1))))
        {
            Gear->State = Gear->State | gsttmpFlag;
            (*HHGear).dY = ufloat_hwFloat_hwFloat_op_sub((*HHGear).dY, _0_2);
            Gear->dX = (*HHGear).dX;
        }
    }
};
void ugearshandlersmess_doStepBirdyDisappear(PGear Gear)
{
    AllInactive = false;
    Gear->Pos = 0;
    if(Gear->Timer < 2000)
    {
        Gear->Timer += 1;
    }
    else
    {
        ugearslist_DeleteGear(Gear);
    }
};
void ugearshandlersmess_doStepBirdyFly(PGear Gear)
{
    PGear HHGear;
    LongInt energy;
    LongInt i;
    hwFloat move;
    astring s;
    HHGear = (*Gear->Hedgehog).Gear;
    if(HHGear == NULL)
    {
        Gear->Timer = 0;
        Gear->State = (Gear->State | gstAnimation) | gsttmpFlag;
        Gear->Timer = 0;
        Gear->doStep = &(ugearshandlersmess_doStepBirdyDisappear);
        CurAmmoGear = NULL;
        isCursorVisible = false;
        ugearshedgehog_AfterAttack();
        return;
    }
    move = _0_2;
    energy = 50;
    if(Gear->Pos > 0)
    {
        Gear->Pos -= 1;
    }
    else
    {
        if((HHGear->Message & ((gmLeft | gmRight) | gmUp)) != 0)
        {
            Gear->Pos = 500;
        }
    }
    if(HHGear->dX.isNegative)
    {
        Gear->Tag = -1;
    }
    else
    {
        Gear->Tag = 1;
    }
    if((HHGear->Message & gmUp) != 0)
    {
        if(!HHGear->dY.isNegative || (ufloat_hwFloat_hwFloat_op_gt(HHGear->Y, ufloat_hwFloat_op_sub(_256))))
        {
            HHGear->dY = ufloat_hwFloat_hwFloat_op_sub(HHGear->dY, move);
        }
        if(Gear->Health != BIRDY_ENERGY_INFINITE)
        {
            Gear->Health -= energy;
        }
        Gear->MsgParam = Gear->MsgParam | gmUp;
    }
    if((HHGear->Message & gmLeft) != 0)
    {
        move.isNegative = true;
    }
    if((HHGear->Message & (gmLeft | gmRight)) != 0)
    {
        HHGear->dX = ufloat_hwFloat_hwFloat_op_add(HHGear->dX, ufloat_hwFloat_hwFloat_op_mul(move, _0_1));
        if(Gear->Health != BIRDY_ENERGY_INFINITE)
        {
            Gear->Health -= energy / 5;
        }
        Gear->MsgParam = Gear->MsgParam | (HHGear->Message & (gmLeft | gmRight));
    }
    if((Gear->Health < 0) && (Gear->Health != BIRDY_ENERGY_INFINITE))
    {
        Gear->Health = 0;
    }
    if((((GameTicks & 0xff) == 0) && (Gear->Health < 500)) && (Gear->Health != BIRDY_ENERGY_INFINITE))
    {
        {i = (500 - Gear->Health) / 250;
         LongInt i__end__ = 0;
         if (i >= i__end__) do {
                                   uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtFeather);
                               } while(i-- != i__end__);}
    }
    if((HHGear->Message & gmAttack) != 0)
    {
        HHGear->Message = HHGear->Message & ~gmAttack;
        if(Gear->FlightTime > 0)
        {
            ugearslist_AddGear_7(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y) + 32, gtEgg, 0, ufloat_hwFloat_hwFloat_op_mul(Gear->dX, _0_5), Gear->dY, 0);
            usound_PlaySound_1(sndBirdyLay);
            --Gear->FlightTime;
        }
        s = fpcrtl_str2astr(uutils_IntToStr(Gear->FlightTime));
        ucaptions_AddCaption(ulocale_FormatA_2(trmsg[sidRemaining], s), capcolDefault, capgrpAmmostate);
    }
    if((HHGear->Message & (((gmUp | gmPrecise) | gmLeft) | gmRight)) != 0)
    {
        Gear->State = Gear->State & ~gsttmpFlag;
    }
    HHGear->Message = HHGear->Message & ~(((gmUp | gmPrecise) | gmLeft) | gmRight);
    HHGear->State = HHGear->State | gstMoving;
    Gear->X = HHGear->X;
    Gear->Y = ufloat_hwFloat_hwFloat_op_sub(HHGear->Y, ufloat_int2hwFloat(32));
    if(!CurrentTeam->ExtDriven)
    {
        FollowGear = HHGear;
    }
    if(((Gear->State & gsttmpFlag) == 0) || (ufloat_hwFloat_hwFloat_op_lt(HHGear->dY, _0)))
    {
        ugearshedgehog_doStepHedgehogMoving(HHGear);
    }
    if((((((Gear->Health == 0) || (HHGear->Damage != 0)) || ugearsutils_CheckGearDrowning(&(HHGear))) || (TurnTimeLeft == 0)) || ((((GameTicks & 0x1ff) == 0) && !HHGear->dY.isNegative) && (ucollisions_TestCollisionYwithGear(HHGear, 1) != 0))) || ((Gear->Message & gmAttack) != 0))
    {
        {
            (*HHGear).Message = 0;
            (*HHGear).Active = true;
            (*HHGear).State = (*HHGear).State | gstMoving;
        }
        Gear->State = (Gear->State | gstAnimation) | gsttmpFlag;
        if(ufloat_hwFloat_hwFloat_op_lt(HHGear->dY, _0))
        {
            Gear->dX = HHGear->dX;
            Gear->dY = HHGear->dY;
        }
        Gear->Timer = 0;
        Gear->doStep = &(ugearshandlersmess_doStepBirdyDisappear);
        CurAmmoGear = NULL;
        isCursorVisible = false;
        ugearshedgehog_AfterAttack();
    }
};
void ugearshandlersmess_doStepBirdyDescend(PGear Gear)
{
    PGear HHGear;
    if(Gear->Timer > 0)
    {
        Gear->Timer -= 1;
    }
    HHGear = (*Gear->Hedgehog).Gear;
    if((HHGear == NULL) || ((HHGear->State & gstHHDriven) == 0))
    {
        Gear->Hedgehog = NULL;
        Gear->Timer = 0;
        Gear->State = (Gear->State | gstAnimation) | gsttmpFlag;
        Gear->doStep = &(ugearshandlersmess_doStepBirdyDisappear);
        CurAmmoGear = NULL;
        isCursorVisible = false;
        ugearshedgehog_AfterAttack();
        return;
    }
    HHGear->Message = HHGear->Message & ~(((gmUp | gmPrecise) | gmLeft) | gmRight);
    if(fpcrtl_abs(ufloat_hwRound(ufloat_hwFloat_hwFloat_op_sub(HHGear->Y, Gear->Y))) > 32)
    {
        if(Gear->Timer == 0)
        {
            Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _0_1);
        }
    }
    else
    {
        if(Gear->Timer == 0)
        {
            Gear->doStep = &(ugearshandlersmess_doStepBirdyFly);
            HHGear->dY = ufloat_hwFloat_op_sub(_0_2);
        }
    }
};
void ugearshandlersmess_doStepBirdyAppear(PGear Gear)
{
    Gear->Pos = 0;
    if(Gear->Timer < 2000)
    {
        Gear->Timer += 1;
    }
    else
    {
        Gear->Timer = 500;
        Gear->dX = _0;
        Gear->dY = _0;
        Gear->State = Gear->State & ~gstAnimation;
        Gear->doStep = &(ugearshandlersmess_doStepBirdyDescend);
    }
};
void ugearshandlersmess_doStepBirdy(PGear Gear)
{
    PGear HHGear;
    Gear->State = Gear->State | (gstAnimation & ~gsttmpFlag);
    Gear->doStep = &(ugearshandlersmess_doStepBirdyAppear);
    if(CurrentHedgehog->Gear == NULL)
    {
        ugearslist_DeleteGear(Gear);
        return;
    }
    HHGear = CurrentHedgehog->Gear;
    if(HHGear->dX.isNegative)
    {
        Gear->Tag = -1;
    }
    else
    {
        Gear->Tag = 1;
    }
    Gear->Pos = 0;
    AllInactive = false;
    FollowGear = HHGear;
    {
        (*HHGear).State = (*HHGear).State & ~gstAttacking;
        (*HHGear).Message = (*HHGear).Message & ~((((gmAttack | gmUp) | gmPrecise) | gmLeft) | gmRight);
    }
};
void ugearshandlersmess_doStepEggWork(PGear Gear)
{
    PVisualGear vg;
    LongInt i;
    AllInactive = false;
    UNUSED (Gear->dX);
    ugearshandlersmess_doStepFallingGear(Gear);
    ugearsutils_CalcRotationDirAngle(Gear);
    if((Gear->State & gstCollision) != 0)
    {
        ugearsutils_doMakeExplosion_6(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLPoisoned, 0xc0e0ffe0);
        usound_PlaySound_1(sndEggBreak);
        uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtEgg);
        vg = uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtEgg);
        if(vg != NULL)
        {
            vg->Frame = 2;
        }
        {i = 10;
         LongInt i__end__ = 0;
         if (i >= i__end__) do {
                                   vg = uvisualgearslist_AddVisualGear_3((ufloat_hwRound(Gear->X) - 3) + fpcrtl_random(6), (ufloat_hwRound(Gear->Y) - 3) + fpcrtl_random(6), vgtDust);
                                   if(vg != NULL)
                                   {
                                       vg->dX = vg->dX + (Gear->dX.QWordValue /(float) 21474836480);
                                   }
                               } while(i-- != i__end__);}
        ugearslist_DeleteGear(Gear);
        return;
    }
};
void ugearshandlersmess_doPortalColorSwitch()
{
    PAmmo CurWeapon;
    if(((CurrentHedgehog->Gear != NULL) && (((*CurrentHedgehog->Gear).State & gstHHDriven) != 0)) && (((*CurrentHedgehog->Gear).Message & gmSwitch) != 0))
    {
        {
            if((*CurrentHedgehog).CurAmmoType == amPortalGun)
            {
                usound_PlaySound_1(sndPortalSwitch);
                (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message & ~gmSwitch;
                CurWeapon = uammos_GetCurAmmoEntry(&((*CurrentHedgehog)));
                if(CurWeapon->Pos != 0)
                {
                    CurWeapon->Pos = 0;
                }
                else
                {
                    CurWeapon->Pos = 1;
                }
            }
        }
    }
};
void ugearshandlersmess_doStepPortal(PGear Gear)
{
    PGear iterator;
    PGear conPortal;
    hwFloat s;
    hwFloat r;
    hwFloat nx;
    hwFloat ny;
    hwFloat ox;
    hwFloat oy;
    hwFloat poffs;
    hwFloat noffs;
    hwFloat pspeed;
    hwFloat nspeed;
    hwFloat resetx;
    hwFloat resety;
    hwFloat resetdx;
    hwFloat resetdy;
    LongInt sx;
    LongInt sy;
    LongInt rh;
    LongInt resetr;
    boolean hasdxy;
    boolean isbullet;
    boolean iscake;
    boolean isCollision;
    ugearshandlersmess_doPortalColorSwitch();
    if(((((ulandutils_LandGet(ufloat_hwRound(Gear->Y), ufloat_hwRound(Gear->X)) <= lfAllObjMask) || ((ulandutils_LandGet(ufloat_hwRound(Gear->Y), ufloat_hwRound(Gear->X)) & lfBouncy) != 0)) || (Gear->Timer < 1)) || ((*Gear->Hedgehog).Team != CurrentHedgehog->Team)) || ucollisions_CheckCoordInWater(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y)))
    {
        ugearslist_DeleteGear(Gear);
        return;
    }
    if((TurnTimeLeft < 1) || (Gear->Health < 1))
    {
        --Gear->Timer;
    }
    if(Gear->Timer < 10000)
    {
        Gear->RenderTimer = true;
    }
    if(Gear->LinkedGear == NULL)
    {
        return;
    }
    if(((*Gear->LinkedGear).Tag & 1) == 0)
    {
        return;
    }
    conPortal = Gear->LinkedGear;
    iterator = NULL;
    while(true)
    {
        if(iterator == NULL)
        {
            iterator = GearsList;
        }
        else
        {
            iterator = iterator->NextGear;
        }
        if(iterator == NULL)
        {
            break;
        }
        if((((iterator->Kind == gtPortal) || (iterator->Kind == gtRope) || (iterator->Kind == gtAirAttack) || (iterator->Kind == gtIceGun))) || (iterator->PortalCounter > 32))
        {
            continue;
        }
        if(iterator->Radius > Gear->Radius)
        {
            continue;
        }
        r = ufloat_int2hwFloat(iterator->Radius + Gear->Radius);
        if((((ufloat_hwFloat_hwFloat_op_lt(iterator->X, ufloat_hwFloat_hwFloat_op_sub(Gear->X, r))) || (ufloat_hwFloat_hwFloat_op_gt(iterator->X, ufloat_hwFloat_hwFloat_op_add(Gear->X, r)))) || (ufloat_hwFloat_hwFloat_op_lt(iterator->Y, ufloat_hwFloat_hwFloat_op_sub(Gear->Y, r)))) || (ufloat_hwFloat_hwFloat_op_gt(iterator->Y, ufloat_hwFloat_hwFloat_op_add(Gear->Y, r))))
        {
            continue;
        }
        hasdxy = ((iterator->dX.QWordValue != 0) || (iterator->dY.QWordValue != 0)) || ((iterator->State & gstMoving) == 0);
        if(!hasdxy)
        {
            if(ufloat_hwFloat_hwFloat_op_lt(Gear->Y, iterator->Y))
            {
                continue;
            }
            ox = ufloat_hwFloat_hwFloat_op_sub(Gear->X, iterator->X);
            oy = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, iterator->Y);
        }
        else
        {
            ox = iterator->dX;
            oy = iterator->dY;
        }
        iscake = iterator->Kind == gtCake;
        if(iscake)
        {
            if(!ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_sub(iterator->X, Gear->X), ox), ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_sub(iterator->Y, Gear->Y), oy)).isNegative)
            {
                continue;
            }
        }
        else
        {
            if(!ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_mul(Gear->dX, ox), ufloat_hwFloat_hwFloat_op_mul(Gear->dY, oy)).isNegative)
            {
                continue;
            }
        }
        isbullet = ((iterator->Kind == gtShotgunShot) || (iterator->Kind == gtDEagleShot) || (iterator->Kind == gtSniperRifleShot) || (iterator->Kind == gtSineGunShot) || (iterator->Kind == gtMinigunBullet));
        r = ufloat_int2hwFloat(iterator->Radius);
        if(!(isbullet || iscake))
        {
            if(hasdxy)
            {
                s = ufloat_Distance(iterator->dX, iterator->dY);
                if(s.QWordValue == 0)
                {
                    continue;
                }
                s = ufloat_hwFloat_hwFloat_op_div(r, s);
                ox = ufloat_hwFloat_hwFloat_op_add(iterator->X, ufloat_hwFloat_hwFloat_op_mul(s, iterator->dX));
                oy = ufloat_hwFloat_hwFloat_op_add(iterator->Y, ufloat_hwFloat_hwFloat_op_mul(s, iterator->dY));
            }
            else
            {
                ox = iterator->X;
                oy = ufloat_hwFloat_hwFloat_op_add(iterator->Y, r);
            }
            if(ufloat_hwRound(ufloat_Distance(ufloat_hwFloat_hwFloat_op_sub(Gear->X, ox), ufloat_hwFloat_hwFloat_op_sub(Gear->Y, oy))) > (Gear->Radius + 1))
            {
                continue;
            }
        }
        if(((iterator->Kind == gtDEagleShot) || (iterator->Kind == gtSniperRifleShot) || (iterator->Kind == gtMinigunBullet)))
        {
            ugearshandlersmess_spawnBulletTrail(iterator, iterator->X, iterator->Y, iterator->FlightTime == 0);
            iterator->FlightTime = 1;
            iterator->Data = NULL;
        }
        ox = ufloat_hwFloat_hwFloat_op_sub(iterator->X, Gear->X);
        oy = ufloat_hwFloat_hwFloat_op_sub(iterator->Y, Gear->Y);
        poffs = ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_mul(Gear->dX, ox), ufloat_hwFloat_hwFloat_op_mul(Gear->dY, oy));
        if(!isbullet && poffs.isNegative)
        {
            continue;
        }
        if(isbullet && !(ufloat_hwFloat_hwFloat_op_lt(ufloat_hwAbs(poffs), _3)))
        {
            continue;
        }
        resetr = iterator->Radius;
        resetx = iterator->X;
        resety = iterator->Y;
        resetdx = iterator->dX;
        resetdy = iterator->dY;
        nx = Gear->dY;
        ny = Gear->dX;
        if(Gear->Elasticity.isNegative)
        {
            nx.isNegative = !nx.isNegative;
        }
        else
        {
            ny.isNegative = !ny.isNegative;
        }
        noffs = ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_mul(nx, ox), ufloat_hwFloat_hwFloat_op_mul(ny, oy));
        if(isbullet && (noffs.Round >= ((LongWord)Gear->Radius)))
        {
            continue;
        }
        if((((!(iscake || isbullet) && Gear->dY.isNegative) && conPortal->dY.isNegative) && ((iterator->dX.QWordValue + iterator->dY.QWordValue) < _0_08.QWordValue)) && (iterator->PortalCounter > 0))
        {
            continue;
        }
        if(hasdxy)
        {
            pspeed = ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_mul(Gear->dX, iterator->dX), ufloat_hwFloat_hwFloat_op_mul(Gear->dY, iterator->dY));
            nspeed = ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_mul(nx, iterator->dX), ufloat_hwFloat_hwFloat_op_mul(ny, iterator->dY));
        }
        else
        {
            pspeed = ufloat_hwAbs(ufloat_hwFloat_hwFloat_op_mul(cGravity, oy));
            nspeed = _0;
        }
        nx = conPortal->dY;
        ny = conPortal->dX;
        if(conPortal->Elasticity.isNegative)
        {
            nx.isNegative = !nx.isNegative;
        }
        else
        {
            ny.isNegative = !ny.isNegative;
        }
        iterator->dX = ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_op_sub(pspeed), conPortal->dX), ufloat_hwFloat_hwFloat_op_mul(nspeed, nx));
        iterator->dY = ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_op_sub(pspeed), conPortal->dY), ufloat_hwFloat_hwFloat_op_mul(nspeed, ny));
        if(iscake)
        {
            ox = ufloat_hwFloat_hwFloat_op_sub(r, _0_7);
        }
        else
        {
            ox = ufloat_hwFloat_hwFloat_op_mul(r, _1_5);
        }
        s = ufloat_hwFloat_hwFloat_op_div(ox, poffs);
        poffs = ox;
        if((nspeed.QWordValue != 0) && (ufloat_hwFloat_hwFloat_op_gt(pspeed, _0)))
        {
            noffs = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_mul(noffs, s), ufloat_hwFloat_hwFloat_op_div(nspeed, pspeed));
        }
        if(!isbullet)
        {
            s = ufloat_hwFloat_hwFloat_op_sub(ufloat_hwFloat_hwFloat_op_add(ufloat_hwAbs(noffs), r), ufloat_int2hwFloat(Gear->Radius));
            if(ufloat_hwFloat_hwFloat_op_gt(s, _0))
            {
                noffs = ufloat_hwFloat_hwFloat_op_sub(noffs, ufloat_SignAs(s, noffs));
            }
        }
        iterator->X = ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_add(conPortal->X, ufloat_hwFloat_hwFloat_op_mul(poffs, conPortal->dX)), ufloat_hwFloat_hwFloat_op_mul(noffs, nx));
        iterator->Y = ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_add(conPortal->Y, ufloat_hwFloat_hwFloat_op_mul(poffs, conPortal->dY)), ufloat_hwFloat_hwFloat_op_mul(noffs, ny));
        if(!hasdxy && !conPortal->dY.isNegative)
        {
            iterator->dY = ufloat_hwFloat_hwFloat_op_add(iterator->dY, ufloat_hwAbs(ufloat_hwFloat_hwFloat_op_mul(cGravity, ufloat_hwFloat_hwFloat_op_sub(iterator->Y, conPortal->Y))));
        }
        if(!(isbullet || iscake))
        {
            ox.QWordValue = _1.QWordValue;
            ox.isNegative = !iterator->dX.isNegative;
            sx = ufloat_hwSign(iterator->dX);
            sy = ufloat_hwSign(iterator->dY);
            if(iterator->Radius > 1)
            {
                iterator->Radius = iterator->Radius - 1;
            }
            isCollision = (ucollisions_TestCollisionY(iterator, sy) != 0) || (ucollisions_TestCollisionX(iterator, sx) != 0);
            if(!isCollision)
            {
                iterator->Radius = 1 + (resetr / 2);
                rh = resetr / 4;
                isCollision = (ucollisions_TestCollisionYwithXYShift_5(iterator, 0, -sy * rh, sy, false) != 0) || (ucollisions_TestCollisionXwithXYShift_5(iterator, ufloat_hwFloat_LongInt_op_mul(ox, rh), 0, sx, false) != 0);
            }
            iterator->Radius = resetr;
            if(isCollision)
            {
                iterator->X = resetx;
                iterator->Y = resety;
                iterator->dX = resetdx;
                iterator->dY = resetdy;
                continue;
            }
        }
        if(iterator->Kind == gtKamikaze)
        {
            ucollisions_RefillProximityCache(iterator, 300);
        }
        if(iscake)
        {
            iterator->PortalCounter = 33;
        }
        else
        {
            ++iterator->PortalCounter;
            iterator->Active = true;
            iterator->State = (iterator->State & ~gstHHHJump) | gstMoving;
        }
        if(iterator->Kind == gtRCPlane)
        {
            iterator->Angle = 1024 + (ufloat_vector2Angle(iterator->dX, iterator->dY) % 4096);
        }
        else
        {
            if(((CurAmmoGear != NULL) && (CurAmmoGear->Kind == gtKamikaze)) && (CurAmmoGear->Hedgehog == iterator->Hedgehog))
            {
                iterator->Angle = uutils_DxDy2AttackAngle(iterator->dX, iterator->dY);
                iterator->Angle = 2048 - iterator->Angle;
                if(iterator->dX.isNegative)
                {
                    iterator->Angle = 4096 - iterator->Angle;
                }
            }
        }
        if(((((CurrentHedgehog->Gear != NULL) && (iterator == CurrentHedgehog->Gear)) && (CurAmmoGear != NULL)) && (CurAmmoGear->Kind == gtRope)) && (ufloat_hwFloat_hwFloat_op_neq(CurAmmoGear->Elasticity, _0)))
        {
            CurAmmoGear->PortalCounter = 1;
        }
        if((!isbullet && ((iterator->State & gstInvisible) == 0)) && (iterator->Kind != gtFlake))
        {
            FollowGear = iterator;
        }
        if(isbullet)
        {
            iterator->Elasticity = iterator->X;
            iterator->Friction = iterator->Y;
        }
        if(Gear->Health > 1)
        {
            --Gear->Health;
        }
    }
};
void ugearshandlersmess_loadNewPortalBall(PGear oldPortal,boolean destroyGear)
{
    PAmmo CurWeapon;
    if(CurrentHedgehog != NULL)
    {
        {
            CurWeapon = uammos_GetCurAmmoEntry(&((*CurrentHedgehog)));
            if((*CurrentHedgehog).CurAmmoType == amPortalGun)
            {
                if(!destroyGear)
                {
                    if((oldPortal->Tag & 2) == 0)
                    {
                        CurWeapon->Pos = 1;
                    }
                    else
                    {
                        CurWeapon->Pos = 0;
                    }
                }
                CurWeapon->Timer = 0;
            }
        }
    }
    if(destroyGear)
    {
        oldPortal->Timer = 0;
    }
};
void ugearshandlersmess_doStepMovingPortal_real(PGear Gear)
{
    LongInt x;
    LongInt y;
    LongInt tx;
    LongInt ty;
    hwFloat s;
    ugearsutils_WorldWrap(&(Gear));
    x = ufloat_hwRound(Gear->X);
    y = ufloat_hwRound(Gear->Y);
    tx = 0;
    ty = 0;
    if((((y & LAND_HEIGHT_MASK) == 0) && ((x & LAND_WIDTH_MASK) == 0)) && (ulandutils_LandGet(y, x) > 255))
    {
        Gear->State = Gear->State | gstCollision;
        Gear->State = Gear->State & ~gstMoving;
        if((((ulandutils_LandGet(y, x) & lfBouncy) != 0) || !ucollisions_CalcSlopeTangent(Gear, x, y, &(tx), &(ty), 255)) || (ufloat_hwFloat_hwFloat_op_lt(ufloat_DistanceI(tx, ty), _12)))
        {
            ugearshandlersmess_loadNewPortalBall(Gear, true);
            return;
        }
        s = ufloat_hwFloat_hwFloat_op_div(_1, ufloat_DistanceI(tx, ty));
        Gear->dX = ufloat_hwFloat_LongInt_op_mul(s, ty);
        Gear->dY = ufloat_hwFloat_LongInt_op_mul(ufloat_hwFloat_op_sub(s), tx);
        Gear->DirAngle = uutils_DxDy2Angle(ufloat_hwFloat_op_sub(Gear->dY), Gear->dX);
        if(!Gear->dX.isNegative)
        {
            Gear->DirAngle = 180 - Gear->DirAngle;
        }
        if((Gear->LinkedGear == NULL) || (ufloat_hwRound(ufloat_Distance(ufloat_hwFloat_hwFloat_op_sub(Gear->X, (*Gear->LinkedGear).X), ufloat_hwFloat_hwFloat_op_sub(Gear->Y, (*Gear->LinkedGear).Y))) >= (Gear->Radius * 2)))
        {
            usound_PlaySound_1(sndPortalOpen);
            ugearshandlersmess_loadNewPortalBall(Gear, false);
            ++Gear->Tag;
            Gear->doStep = &(ugearshandlersmess_doStepPortal);
        }
        else
        {
            ugearshandlersmess_loadNewPortalBall(Gear, true);
        }
    }
    else
    {
        if(((ucollisions_CheckCoordInWater(x, y) || (y < -uutils_Max(LAND_WIDTH, 4096))) || (x > (2 * uutils_Max(LAND_WIDTH, 4096)))) || (x < -uutils_Max(LAND_WIDTH, 4096)))
        {
            ugearshandlersmess_loadNewPortalBall(Gear, true);
        }
    }
};
void ugearshandlersmess_doStepMovingPortal(PGear Gear)
{
    ugearshandlersmess_doPortalColorSwitch();
    ugearshandlersmess_doStepPerPixel(Gear, &(ugearshandlersmess_doStepMovingPortal_real), true);
    if((Gear->Timer < 1) || ((*Gear->Hedgehog).Team != CurrentHedgehog->Team))
    {
        ugearslist_DeleteGear(Gear);
    }
};
void ugearshandlersmess_doStepPortalShot(PGear newPortal)
{
    PGear iterator;
    hwFloat s;
    PAmmo CurWeapon;
    if(CurrentHedgehog->Gear == NULL)
    {
        ugearslist_DeleteGear(newPortal);
        return;
    }
    s = ufloat_Distance(newPortal->dX, newPortal->dY);
    s = ufloat_hwFloat_hwFloat_op_div(ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_mul(_2, s), ufloat_hwFloat_hwFloat_op_div(ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_mul(newPortal->dX, (*CurrentHedgehog->Gear).dX), ufloat_hwFloat_hwFloat_op_mul(newPortal->dY, (*CurrentHedgehog->Gear).dY)), s)), s);
    newPortal->dX = ufloat_hwFloat_hwFloat_op_mul(newPortal->dX, s);
    newPortal->dY = ufloat_hwFloat_hwFloat_op_mul(newPortal->dY, s);
    newPortal->LinkedGear = NULL;
    usound_PlaySound_1(sndPortalShot);
    {
        CurWeapon = uammos_GetCurAmmoEntry(&((*CurrentHedgehog)));
        newPortal->Elasticity.isNegative = (*CurrentHedgehog->Gear).dX.isNegative;
        if((((*CurrentHedgehog).Gear->State & gstHHHJump) != 0) && ((*CurrentHedgehog).Effects[heArtillery] == 0))
        {
            newPortal->Elasticity.isNegative = !newPortal->Elasticity.isNegative;
        }
        if((CurWeapon != NULL) && ((*CurrentHedgehog).CurAmmoType == amPortalGun))
        {
            CurWeapon->Timer = CurWeapon->Timer | 2;
        }
        iterator = GearsList;
        while(iterator != NULL)
        {
            if(iterator->Kind == gtPortal)
            {
                if(((iterator != newPortal) && (iterator->Timer > 0)) && (iterator->Hedgehog == CurrentHedgehog))
                {
                    if((iterator->Tag & 2) == (newPortal->Tag & 2))
                    {
                        iterator->Timer = 0;
                    }
                    else
                    {
                        newPortal->LinkedGear = iterator;
                        iterator->LinkedGear = newPortal;
                        iterator->Health = newPortal->Health;
                    }
                }
            }
            iterator->PortalCounter = 0;
            iterator = iterator->NextGear;
        }
        if(newPortal->LinkedGear != NULL)
        {
            iterator = GearsList;
            while(iterator != NULL)
            {
                if(!(((iterator->Kind == gtPortal) || (iterator->Kind == gtAirAttack) || (iterator->Kind == gtKnife) || (iterator->Kind == gtSMine))) && ((iterator->Hedgehog != CurrentHedgehog) || ((iterator->Message & gmAllStoppable) == 0)))
                {
                    iterator->Active = true;
                    if(iterator->dY.QWordValue == 0)
                    {
                        iterator->dY.isNegative = false;
                    }
                    iterator->State = iterator->State | gstMoving;
                    ucollisions_DeleteCI(iterator);
                }
                iterator = iterator->NextGear;
            }
        }
    }
    newPortal->State = newPortal->State & ~gstCollision;
    newPortal->State = newPortal->State | gstMoving;
    newPortal->doStep = &(ugearshandlersmess_doStepMovingPortal);
};
void ugearshandlersmess_doStepPiano(PGear Gear)
{
    boolean valid;
    PGear HHGear;
    AllInactive = false;
    valid = true;
    if((Gear->Hedgehog != NULL) && ((*Gear->Hedgehog).Gear != NULL))
    {
        HHGear = (*Gear->Hedgehog).Gear;
    }
    if(WorldEdge == weBounce)
    {
        if((ufloat_hwRound(Gear->X) - Gear->Radius) < leftX)
        {
            valid = false;
        }
        else
        {
            if((ufloat_hwRound(Gear->X) + Gear->Radius) > rightX)
            {
                valid = false;
            }
        }
    }
    if(!valid)
    {
        if(HHGear != NULL)
        {
            HHGear->Message = HHGear->Message & ~gmAttack;
            HHGear->State = HHGear->State & ~gstAttacking;
            HHGear->State = HHGear->State | gstChooseTarget;
            isCursorVisible = true;
        }
        ugearslist_DeleteGear(Gear);
        usound_PlaySound_1(sndDenied);
        return;
    }
    isCursorVisible = false;
    if(HHGear != NULL)
    {
        usound_PlaySoundV_2(sndIncoming, (*(*Gear->Hedgehog).Team).voicepack);
        (*Gear->Hedgehog).Unplaced = true;
        HHGear->X = _0;
        HHGear->Y = _0;
    }
    usound_PauseMusic();
    Gear->doStep = &(ugearshandlersmess_doStepPianoWork);
};
void ugearshandlersmess_doStepPianoWork(PGear Gear)
{
    LongInt r0;
    LongInt r1;
    hwFloat odY;
    AllInactive = false;
    if(((CurrentHedgehog != NULL) && (CurrentHedgehog->Gear != NULL)) && (((*CurrentHedgehog->Gear).Message & gmSlot) != 0))
    {
        switch((*CurrentHedgehog->Gear).MsgParam)
        {case 0:usound_PlaySound_4(sndPiano0, false, false, true);
                break;
         case 1:usound_PlaySound_4(sndPiano1, false, false, true);
                break;
         case 2:usound_PlaySound_4(sndPiano2, false, false, true);
                break;
         case 3:usound_PlaySound_4(sndPiano3, false, false, true);
                break;
         case 4:usound_PlaySound_4(sndPiano4, false, false, true);
                break;
         case 5:usound_PlaySound_4(sndPiano5, false, false, true);
                break;
         case 6:usound_PlaySound_4(sndPiano6, false, false, true);
                break;
         case 7:usound_PlaySound_4(sndPiano7, false, false, true);
                break;
         case 8:usound_PlaySound_4(sndPiano8, false, false, true);
                break;
         default: break;}
        if((*CurrentHedgehog->Gear).MsgParam <= 8)
        {
            uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtNote);
        }
        (*CurrentHedgehog->Gear).MsgParam = 0;
        (*CurrentHedgehog->Gear).Message = (*CurrentHedgehog->Gear).Message & ~gmSlot;
    }
    if(Gear->Pos == 5)
    {
        Gear->dY = ufloat_hwFloat_hwFloat_op_add(Gear->dY, ufloat_hwFloat_LongInt_op_mul(cGravity, 2));
        Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, Gear->dY);
        if(ugearsutils_CheckGearDrowning(&(Gear)))
        {
            Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _50);
            uammos_OnUsedAmmo(&((*CurrentHedgehog)));
            ustats_HedgehogSacrificed(CurrentHedgehog);
            if(CurrentHedgehog->Gear != NULL)
            {
                (*CurrentHedgehog->Gear).Active = true;
                (*CurrentHedgehog->Gear).X = Gear->X;
                (*CurrentHedgehog->Gear).Y = ufloat_hwFloat_hwFloat_op_add(ufloat_int2hwFloat(cWaterLine + cVisibleWater), _128);
                CurrentHedgehog->Unplaced = false;
                if(TagTurnTimeLeft == 0)
                {
                    TagTurnTimeLeft = TurnTimeLeft;
                }
                TurnTimeLeft = 0;
            }
            usound_ResumeMusic();
        }
        return;
    }
    odY = Gear->dY;
    ugearshandlersmess_doStepFallingGear(Gear);
    if((Gear->State & gstDrowning) != 0)
    {
        Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _50);
        uammos_OnUsedAmmo(&((*CurrentHedgehog)));
        ustats_HedgehogSacrificed(CurrentHedgehog);
        if(CurrentHedgehog->Gear != NULL)
        {
            (*CurrentHedgehog->Gear).Active = true;
            (*CurrentHedgehog->Gear).X = Gear->X;
            (*CurrentHedgehog->Gear).Y = ufloat_hwFloat_hwFloat_op_add(ufloat_int2hwFloat(cWaterLine + cVisibleWater), _128);
            CurrentHedgehog->Unplaced = false;
            if(TagTurnTimeLeft == 0)
            {
                TagTurnTimeLeft = TurnTimeLeft;
            }
            TurnTimeLeft = 0;
        }
        usound_ResumeMusic();
    }
    else
    {
        if((Gear->State & gstCollision) != 0)
        {
            r0 = urandom_GetRandom((Gear->Boom / 4) + 1);
            r1 = urandom_GetRandom((Gear->Boom / 4) + 1);
            ugearsutils_doMakeExplosion_5((ufloat_hwRound(Gear->X) - 30) - r0, ufloat_hwRound(Gear->Y) + 40, (Gear->Boom / 2) + r1, Gear->Hedgehog, 0);
            ugearsutils_doMakeExplosion_5((ufloat_hwRound(Gear->X) + 30) + r1, ufloat_hwRound(Gear->Y) + 40, (Gear->Boom / 2) + r0, Gear->Hedgehog, 0);
            ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom + r0, Gear->Hedgehog, EXPLAutoSound);
            {r0 = 0;
             LongInt r0__end__ = 4;
             if (r0 <= r0__end__) do {
                                         uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtNote);
                                     } while(r0++ != r0__end__);}
            Gear->dY = ufloat_hwFloat_hwFloat_op_sub(ufloat_hwFloat_LongInt_op_mul(cGravity, 2), odY);
            Gear->Pos = Gear->Pos + 1;
        }
        else
        {
            Gear->dY = ufloat_hwFloat_hwFloat_op_add(Gear->dY, ufloat_hwFloat_LongInt_op_mul(cGravity, 2));
        }
    }
};
void ugearshandlersmess_doStepSineGunShotWork(PGear Gear)
{
    LongInt x;
    LongInt y;
    LongInt rX;
    LongInt rY;
    LongInt t;
    LongInt tmp;
    LongInt initHealth;
    hwFloat oX;
    hwFloat oY;
    hwFloat ldX;
    hwFloat ldY;
    hwFloat sdX;
    hwFloat sdY;
    hwFloat sine;
    hwFloat lx;
    hwFloat ly;
    hwFloat amp;
    boolean justCollided;
    boolean justBounced;
    AllInactive = false;
    initHealth = Gear->Health;
    lx = Gear->X;
    ly = Gear->Y;
    ldX = Gear->dX;
    ldY = Gear->dY;
    sdY = ufloat_hwFloat_hwFloat_op_div(_0_5, ufloat_Distance(Gear->dX, Gear->dY));
    ldX = ufloat_hwFloat_hwFloat_op_mul(ldX, sdY);
    ldY = ufloat_hwFloat_hwFloat_op_mul(ldY, sdY);
    sdY = ufloat_hwFloat_hwFloat_op_add(ufloat_hwAbs(ldX), ufloat_hwAbs(ldY));
    sdX = ufloat_hwFloat_hwFloat_op_sub(_1, ufloat_hwAbs(ufloat_hwFloat_hwFloat_op_div(ldX, sdY)));
    sdY = ufloat_hwFloat_hwFloat_op_sub(_1, ufloat_hwAbs(ufloat_hwFloat_hwFloat_op_div(ldY, sdY)));
    if(ldX.isNegative == ldY.isNegative)
    {
        sdY = ufloat_hwFloat_op_sub(sdY);
    }
    t = urandom_GetRandom(4096);
    justCollided = false;
    justBounced = false;
    do {
           lx = ufloat_hwFloat_hwFloat_op_add(lx, ldX);
           ly = ufloat_hwFloat_hwFloat_op_add(ly, ldY);
           oX = Gear->X;
           oY = Gear->Y;
           rX = ufloat_hwRound(oX);
           rY = ufloat_hwRound(oY);
           tmp = t % 4096;
           amp = ufloat_hwFloat_hwFloat_op_mul(_128, ufloat_hwFloat_hwFloat_op_sub(_1, ufloat_hwSqr(ufloat_hwFloat_LongInt_op_div(ufloat_int2hwFloat(Gear->Health), initHealth))));
           sine = ufloat_hwFloat_hwFloat_op_mul(amp, ufloat_AngleSin(tmp % 2048));
           sine.isNegative = tmp < 2048;
           Gear->X = ufloat_hwFloat_hwFloat_op_add(lx, ufloat_hwFloat_hwFloat_op_mul(sine, sdX));
           Gear->Y = ufloat_hwFloat_hwFloat_op_add(ly, ufloat_hwFloat_hwFloat_op_mul(sine, sdY));
           Gear->dX = ufloat_hwFloat_hwFloat_op_sub(Gear->X, oX);
           Gear->dY = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, oY);
           x = ufloat_hwRound(Gear->X);
           y = ufloat_hwRound(Gear->Y);
           if(WorldEdge == weWrap)
           {
               if(x > rightX)
               {
                   do {
                          x -= playWidth;
                          rX -= playWidth;
                      } while(!(x <= rightX));
               }
               else
               {
                   if(x < leftX)
                   {
                       do {
                              x += playWidth;
                              rX += playWidth;
                          } while(!(x >= leftX));
                   }
               }
           }
           else
           {
               if(WorldEdge == weBounce)
               {
                   if(!justBounced && ((x > rightX) || (x < leftX)))
                   {
                       lx = ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_sub(lx, ldX), ufloat_hwFloat_LongInt_op_mul(ufloat_hwFloat_hwFloat_op_sub(oX, lx), 2));
                       ly = ufloat_hwFloat_hwFloat_op_sub(ly, ldY);
                       Gear->X = oX;
                       Gear->Y = oY;
                       ldX.isNegative = !ldX.isNegative;
                       sdX.isNegative = !sdX.isNegative;
                       justBounced = true;
                       continue;
                   }
                   else
                   {
                       justBounced = false;
                   }
               }
           }
           t += Gear->Health / 313;
           if(hasBorder && (((x & LAND_WIDTH_MASK) != 0) || ((y & LAND_HEIGHT_MASK) != 0)))
           {
               Gear->Damage = 0;
               Gear->Health = 0;
           }
           else
           {
               if(!ucollisions_CheckCoordInWater(rX, rY) || !ucollisions_CheckCoordInWater(x, y))
               {
                   if((((y & LAND_HEIGHT_MASK) == 0) && ((x & LAND_WIDTH_MASK) == 0)) && (ulandutils_LandGet(y, x) != 0))
                   {
                       if(((GameFlags & gfSolidLand) != 0) && (ulandutils_LandGet(y, x) > 255))
                       {
                           Gear->Damage = initHealth;
                       }
                       else
                       {
                           if(justCollided)
                           {
                               Gear->Damage = initHealth;
                           }
                           else
                           {
                               Gear->Damage += 3;
                               justCollided = true;
                           }
                       }
                   }
                   else
                   {
                       justCollided = false;
                   }
                   if(Gear->Damage > 0)
                   {
                       if((GameFlags & gfSolidLand) == 0)
                       {
                           ugearsutils_doMakeExplosion_5(rX, rY, Gear->Radius, Gear->Hedgehog, (EXPLNoDamage | EXPLDoNotTouchAny) | EXPLNoGfx);
                       }
                       ugearsutils_AmmoShove(Gear, Gear->Boom, 50);
                       Gear->Health -= Gear->Damage;
                       if(Gear->Damage >= initHealth)
                       {
                           tmp = urandom_GetRandom(256);
                           {t = 0;
                            LongInt t__end__ = 3;
                            if (t <= t__end__) do {
                                                      if(!ufloat_isZero(Gear->dX))
                                                      {
                                                          rX = rX - ufloat_hwSign(Gear->dX);
                                                      }
                                                      if(!ufloat_isZero(Gear->dY))
                                                      {
                                                          rY = rY - ufloat_hwSign(Gear->dY);
                                                      }
                                                      lx = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleCos(tmp + (t * 512)), _0_25), ufloat_hwFloat_hwFloat_op_add(urandom_GetRandomf(), _1));
                                                      ly = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleSin(tmp + (t * 512)), _0_25), ufloat_hwFloat_hwFloat_op_add(urandom_GetRandomf(), _1));
                                                      ugearslist_AddGear_7(rX, rY, gtFlame, 0, lx, ly, 0);
                                                      ugearslist_AddGear_7(rX, rY, gtFlame, 0, lx, ufloat_hwFloat_op_sub(ly), 0);
                                                  } while(t++ != t__end__);}
                       }
                       else
                       {
                           if(urandom_GetRandom(6) == 0)
                           {
                               tmp = urandom_GetRandom(2 * Gear->Radius);
                               ugearslist_AddGear_7((x - Gear->Radius) + tmp, y - urandom_GetRandom(Gear->Radius + 1), gtFlame, gsttmpFlag, _0, _0, 0);
                           }
                       }
                   }
                   Gear->Damage = 0;
                   if(fpcrtl_random(100) == 0)
                   {
                       uvisualgearslist_AddVisualGear_3(x, y, vgtSmokeTrace);
                   }
               }
               else
               {
                   Gear->Health -= 5;
               }
           }
           --Gear->Health;
           if(Gear->Radius > 4)
           {
               if(Gear->Health <= (initHealth / 3))
               {
                   --Gear->Radius;
               }
           }
           else
           {
               if(Gear->Radius > 3)
               {
                   if(Gear->Health <= (initHealth / 4))
                   {
                       --Gear->Radius;
                   }
               }
               else
               {
                   if(Gear->Radius > 2)
                   {
                       if(Gear->Health <= (initHealth / 5))
                       {
                           --Gear->Radius;
                       }
                   }
                   else
                   {
                       if(Gear->Radius > 1)
                       {
                           if(Gear->Health <= (initHealth / 6))
                           {
                               --Gear->Radius;
                           }
                       }
                   }
               }
           }
       } while(!(Gear->Health <= 0));
    ugearslist_DeleteGear(Gear);
    ugearshedgehog_AfterAttack();
};
void ugearshandlersmess_doStepSineGunShot(PGear Gear)
{
    PGear HHGear;
    usound_PlaySound_1(sndSineGun);
    if((Gear->Hedgehog != NULL) && ((*Gear->Hedgehog).Gear != NULL))
    {
        HHGear = (*Gear->Hedgehog).Gear;
        Gear->dX.isNegative = !Gear->dX.isNegative;
        Gear->dY.isNegative = !Gear->dY.isNegative;
        HHGear->dX = Gear->dX;
        HHGear->dY = Gear->dY;
        ugearsutils_AmmoShove(Gear, 0, 79);
        Gear->dX.isNegative = !Gear->dX.isNegative;
        Gear->dY.isNegative = !Gear->dY.isNegative;
    }
    Gear->doStep = &(ugearshandlersmess_doStepSineGunShotWork);
};
void ugearshandlersmess_doStepFlamethrowerWork(PGear Gear)
{
    PGear HHGear;
    PGear flame;
    hwFloat rx;
    hwFloat ry;
    hwFloat speed;
    LongInt i;
    LongInt gX;
    LongInt gY;
    AllInactive = false;
    HHGear = (*Gear->Hedgehog).Gear;
    if(HHGear == NULL)
    {
        usound_StopSoundChan_2(Gear->SoundChannel, 300);
        ugearslist_DeleteGear(Gear);
        return;
    }
    ugearshedgehog_HedgehogChAngle(HHGear);
    gX = ufloat_hwRound(Gear->X) + uutils_GetLaunchX(amBallgun, ufloat_hwSign(HHGear->dX), HHGear->Angle);
    gY = ufloat_hwRound(Gear->Y) + uutils_GetLaunchY(amBallgun, HHGear->Angle);
    if((GameTicks & 0xff) == 0)
    {
        if((HHGear->Message & gmRight) != 0)
        {
            if(HHGear->dX.isNegative && (Gear->Tag < 20))
            {
                ++Gear->Tag;
            }
            else
            {
                if(Gear->Tag > 5)
                {
                    --Gear->Tag;
                }
            }
        }
        else
        {
            if((HHGear->Message & gmLeft) != 0)
            {
                if(HHGear->dX.isNegative && (Gear->Tag > 5))
                {
                    --Gear->Tag;
                }
                else
                {
                    if(Gear->Tag < 20)
                    {
                        ++Gear->Tag;
                    }
                }
            }
        }
    }
    --Gear->Timer;
    if(Gear->Timer == 0)
    {
        --Gear->Health;
        if((Gear->Health % 5) == 0)
        {
            rx = urandom_rndSign(ufloat_hwFloat_hwFloat_op_mul(urandom_GetRandomf(), _0_1));
            ry = urandom_rndSign(ufloat_hwFloat_hwFloat_op_mul(urandom_GetRandomf(), _0_1));
            speed = ufloat_hwFloat_hwFloat_op_mul(_0_5, ufloat_hwFloat_LongInt_op_div(_10, Gear->Tag));
            flame = ugearslist_AddGear_7(gX, gY, gtFlame, gsttmpFlag, ufloat_hwFloat_hwFloat_op_add(ufloat_SignAs(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleSin(HHGear->Angle), speed), HHGear->dX), rx), ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleCos(HHGear->Angle), ufloat_hwFloat_op_sub(speed)), ry), 0);
            flame->CollisionMask = lfNotCurHogCrate;
            if((Gear->Health % 30) == 0)
            {
                flame = ugearslist_AddGear_7(gX, gY, gtFlame, 0, ufloat_hwFloat_hwFloat_op_add(ufloat_SignAs(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleSin(HHGear->Angle), speed), HHGear->dX), rx), ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleCos(HHGear->Angle), ufloat_hwFloat_op_sub(speed)), ry), 0);
                flame->CollisionMask = lfNotCurHogCrate;
            }
        }
        Gear->Timer = Gear->Tag;
    }
    if((Gear->Health == 0) || ((HHGear->State & gstHHDriven) == 0))
    {
        HHGear->Message = HHGear->Message & ~((gmAttack | gmLeft) | gmRight);
        HHGear->State = HHGear->State & ~gstNotKickable;
        usound_StopSoundChan_2(Gear->SoundChannel, 300);
        ugearslist_DeleteGear(Gear);
        ugearshedgehog_AfterAttack();
    }
    else
    {
        i = Gear->Health / 5;
        if((!cOnlyStats && (i != Gear->Damage)) && ((GameTicks & 0x3f) == 0))
        {
            Gear->Damage = i;
            utextures_FreeAndNilTexture(&(Gear->Tex));
            Gear->Tex = urenderutils_RenderStringTex(ulocale_FormatA_2(trmsg[sidFuel], fpcrtl_str2astr(uutils_IntToStr(i))), cWhiteColor, fntSmall);
        }
    }
};
void ugearshandlersmess_doStepFlamethrower(PGear Gear)
{
    PGear HHGear;
    HHGear = (*Gear->Hedgehog).Gear;
    HHGear->Message = HHGear->Message & ~(((gmUp | gmDown) | gmLeft) | gmRight);
    HHGear->State = HHGear->State | gstNotKickable;
    Gear->SoundChannel = usound_LoopSound_2(sndFlamethrower, 20);
    Gear->doStep = &(ugearshandlersmess_doStepFlamethrowerWork);
};
void ugearshandlersmess_doStepLandGunWork(PGear Gear)
{
    PGear HHGear;
    PGear land;
    hwFloat rx;
    hwFloat ry;
    hwFloat speed;
    LongInt i;
    LongInt gX;
    LongInt gY;
    AllInactive = false;
    HHGear = (*Gear->Hedgehog).Gear;
    if(HHGear == NULL)
    {
        usound_StopSoundChan_1(Gear->SoundChannel);
        ugearslist_DeleteGear(Gear);
        return;
    }
    ugearshedgehog_HedgehogChAngle(HHGear);
    gX = ufloat_hwRound(Gear->X) + uutils_GetLaunchX(amBallgun, ufloat_hwSign(HHGear->dX), HHGear->Angle);
    gY = ufloat_hwRound(Gear->Y) + uutils_GetLaunchY(amBallgun, HHGear->Angle);
    if((GameTicks & 0xff) == 0)
    {
        if((HHGear->Message & gmRight) != 0)
        {
            if(HHGear->dX.isNegative && (Gear->Tag < 20))
            {
                ++Gear->Tag;
            }
            else
            {
                if(Gear->Tag > 5)
                {
                    --Gear->Tag;
                }
            }
        }
        else
        {
            if((HHGear->Message & gmLeft) != 0)
            {
                if(HHGear->dX.isNegative && (Gear->Tag > 5))
                {
                    --Gear->Tag;
                }
                else
                {
                    if(Gear->Tag < 20)
                    {
                        ++Gear->Tag;
                    }
                }
            }
        }
    }
    --Gear->Timer;
    if(Gear->Timer == 0)
    {
        --Gear->Health;
        rx = urandom_rndSign(ufloat_hwFloat_hwFloat_op_mul(urandom_GetRandomf(), _0_1));
        ry = urandom_rndSign(ufloat_hwFloat_hwFloat_op_mul(urandom_GetRandomf(), _0_1));
        speed = ufloat_hwFloat_LongInt_op_div(_3, Gear->Tag);
        land = ugearslist_AddGear_7(gX, gY, gtFlake, gsttmpFlag, ufloat_hwFloat_hwFloat_op_add(ufloat_SignAs(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleSin(HHGear->Angle), speed), HHGear->dX), rx), ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleCos(HHGear->Angle), ufloat_hwFloat_op_sub(speed)), ry), 0);
        land->CollisionMask = lfNotCurHogCrate;
        Gear->Timer = Gear->Tag;
    }
    if(((Gear->Health == 0) || ((HHGear->State & gstHHDriven) == 0)) || ((HHGear->Message & gmAttack) != 0))
    {
        HHGear->Message = HHGear->Message & ~((gmAttack | gmLeft) | gmRight);
        HHGear->State = HHGear->State & ~gstNotKickable;
        usound_StopSoundChan_1(Gear->SoundChannel);
        ugearslist_DeleteGear(Gear);
        ugearshedgehog_AfterAttack();
    }
    else
    {
        i = Gear->Health / 10;
        if((!cOnlyStats && (i != Gear->Damage)) && ((GameTicks & 0x3f) == 0))
        {
            Gear->Damage = i;
            utextures_FreeAndNilTexture(&(Gear->Tex));
            Gear->Tex = urenderutils_RenderStringTex(ulocale_FormatA_2(trmsg[sidFuel], fpcrtl_str2astr(uutils_IntToStr(i))), cWhiteColor, fntSmall);
        }
    }
};
void ugearshandlersmess_doStepLandGun(PGear Gear)
{
    PGear HHGear;
    HHGear = (*Gear->Hedgehog).Gear;
    HHGear->Message = HHGear->Message & ~((((gmUp | gmDown) | gmLeft) | gmRight) | gmAttack);
    HHGear->State = HHGear->State | gstNotKickable;
    Gear->SoundChannel = usound_LoopSound_1(sndLandGun);
    Gear->doStep = &(ugearshandlersmess_doStepLandGunWork);
};
void ugearshandlersmess_doStepPoisonCloud(PGear Gear)
{
    if(WorldEdge != weBounce)
    {
        ugearsutils_WorldWrap(&(Gear));
    }
    if(Gear->Timer == 0)
    {
        ugearslist_DeleteGear(Gear);
        return;
    }
    --Gear->Timer;
    Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, Gear->dX);
    Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, Gear->dY);
    Gear->dX = ufloat_hwFloat_hwFloat_op_add(Gear->dX, ufloat_hwFloat_LongInt_op_div(cWindSpeed, 4));
    Gear->dY = ufloat_hwFloat_hwFloat_op_add(Gear->dY, ufloat_hwFloat_LongInt_op_div(cGravity, 100));
    if((GameTicks & 0xff) == 0)
    {
        ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, (((EXPLDontDraw | EXPLNoGfx) | EXPLNoDamage) | EXPLDoNotTouchAny) | EXPLPoisoned);
    }
    if((Gear->State & gsttmpFlag) == 0)
    {
        AllInactive = false;
    }
};
void ugearshandlersmess_doStepHammer(PGear Gear)
{
    PGear HHGear;
    PGear tmp;
    PGear tmp2;
    PGearArray t;
    LongInt i;
    LongInt dmg;
    HHGear = (*Gear->Hedgehog).Gear;
    HHGear->State = HHGear->State | gstNoDamage;
    ucollisions_DeleteCI(HHGear);
    uutils_SetLittle(&(HHGear->dY));
    HHGear->dY.isNegative = true;
    HHGear->State = HHGear->State | gstMoving;
    t = ucollisions_CheckGearsCollision(Gear);
    {i = 5;
     LongInt i__end__ = 0;
     if (i >= i__end__) do {
                               uvisualgearslist_AddVisualGear_3((ufloat_hwRound(Gear->X) - 5) + fpcrtl_random(10), ufloat_hwRound(Gear->Y) + 12, vgtDust);
                           } while(i-- != i__end__);}
    i = t->Count;
    while(i > 0)
    {
        --i;
        tmp = t->ar[i];
        if((tmp->State & gstNoDamage) == 0)
        {
            if(((tmp->Kind == gtHedgehog) || (tmp->Kind == gtMine)) || (tmp->Kind == gtExplosives))
            {
                dmg = 0;
                if((tmp->Kind != gtHedgehog) || (((*tmp->Hedgehog).Effects[heInvulnerable] == 0) && ((tmp->State & gstHHDeath) == 0)))
                {
                    dmg = tmp->Health - tmp->Damage;
                    dmg = dmg / Gear->Boom;
                    if(dmg > 0)
                    {
                        ugearsutils_ApplyDamage(tmp, CurrentHedgehog, dmg, dsHammer);
                    }
                    tmp->dY = ufloat_hwFloat_LongInt_op_mul(_0_03, Gear->Boom);
                }
                if(((tmp->Kind == gtHedgehog) && ((tmp->State & gstHHDeath) == 0)) || (tmp->Health > tmp->Damage))
                {
                    tmp2 = ugearslist_AddGear_7(ufloat_hwRound(tmp->X), ufloat_hwRound(tmp->Y), gtHammerHit, 0, _0, _0, 0);
                    tmp2->LinkedGear = tmp;
                    ugearsutils_SetAllToActive();
                }
            }
        }
    }
    HHGear->State = HHGear->State & ~gstNoDamage;
    Gear->Timer = 250;
    Gear->doStep = &(ugearshandlersmess_doStepIdle);
};
void ugearshandlersmess_doStepHammerHitWork(PGear Gear)
{
    LongInt i;
    LongInt j;
    LongInt ei;
    PGear HitGear;
    AllInactive = false;
    HitGear = Gear->LinkedGear;
    --Gear->Timer;
    if(((HitGear == NULL) || (Gear->Timer == 0)) || ((Gear->Message & gmDestroy) != 0))
    {
        ugearslist_DeleteGear(Gear);
        return;
    }
    if((Gear->Timer % 5) == 0)
    {
        uvisualgearslist_AddVisualGear_3((ufloat_hwRound(Gear->X) - 5) + fpcrtl_random(10), ufloat_hwRound(Gear->Y) + 12, vgtDust);
        i = (ufloat_hwRound(Gear->X) - HitGear->Radius) + 2;
        ei = (ufloat_hwRound(Gear->X) + HitGear->Radius) - 2;
        {j = 1;
         LongInt j__end__ = 4;
         if (j <= j__end__) do {
                                   ugearsutils_doMakeExplosion_5(i - urandom_GetRandom(5), ufloat_hwRound(Gear->Y) + (6 * j), 3, Gear->Hedgehog, ((EXPLNoDamage | EXPLDoNotTouchAny) | EXPLNoGfx) | EXPLForceDraw);
                               } while(j++ != j__end__);}
        {j = 1;
         LongInt j__end__ = 4;
         if (j <= j__end__) do {
                                   ugearsutils_doMakeExplosion_5(ei + ((LongInt)urandom_GetRandom(5)), ufloat_hwRound(Gear->Y) + (6 * j), 3, Gear->Hedgehog, ((EXPLNoDamage | EXPLDoNotTouchAny) | EXPLNoGfx) | EXPLForceDraw);
                               } while(j++ != j__end__);}
        while(i <= ei)
        {
            {j = 1;
             LongInt j__end__ = 11;
             if (j <= j__end__) do {
                                       ugearsutils_doMakeExplosion_5(i, ufloat_hwRound(Gear->Y) + (3 * j), 3, Gear->Hedgehog, ((EXPLNoDamage | EXPLDoNotTouchAny) | EXPLNoGfx) | EXPLForceDraw);
                                   } while(j++ != j__end__);}
            i += 1;
        }
        if(ulandgraphics_CheckLandValue(ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_add(Gear->X, Gear->dX), ufloat_SignAs(_6, Gear->dX))), ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(Gear->Y, _1_9)), lfIndestructible))
        {
            Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, _1_9);
        }
    }
    if(ucollisions_TestCollisionYwithGear(Gear, 1) != 0)
    {
        Gear->dY = _0;
        uutils_SetLittle(&(HitGear->dX));
        HitGear->dY = _0;
    }
    else
    {
        if(ucollisions_CheckCoordInWater(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y)))
        {
            Gear->Timer = 1;
        }
    }
    HitGear->X = Gear->X;
    HitGear->Y = Gear->Y;
    uutils_SetLittle(&(HitGear->dY));
    HitGear->Active = true;
};
void ugearshandlersmess_doStepHammerHit(PGear Gear)
{
    LongInt i;
    LongInt y;
    TRangeArray ar;
    PGear HHGear;
    i = 0;
    HHGear = (*Gear->Hedgehog).Gear;
    y = ufloat_hwRound(Gear->Y) - (cHHRadius * 2);
    while(y < ufloat_hwRound(Gear->Y))
    {
        ar[i].Left = (ufloat_hwRound(Gear->X) - Gear->Radius) - ((LongInt)urandom_GetRandom(2));
        ar[i].Right = (ufloat_hwRound(Gear->X) + Gear->Radius) + ((LongInt)urandom_GetRandom(2));
        y += 2;
        ++i;
    }
    ulandgraphics_DrawHLinesExplosions(&(ar), 3, ufloat_hwRound(Gear->Y) - (cHHRadius * 2), 2, ((int)(i) - 1));
    Gear->dY = HHGear->dY;
    ucollisions_DeleteCI(HHGear);
    ugearshandlersmess_doStepHammerHitWork(Gear);
    Gear->doStep = &(ugearshandlersmess_doStepHammerHitWork);
};
void ugearshandlersmess_doStepResurrectorWork(PGear Gear)
{
    PGearArrayS graves;
    PGear resgear;
    PHedgehog hh;
    LongInt i;
    astring s;
    AllInactive = false;
    hh = Gear->Hedgehog;
    if((Gear->Message & gmUp) != 0)
    {
        if((GameTicks & 0xf) != 0)
        {
            return;
        }
    }
    else
    {
        if((GameTicks & 0x1ff) != 0)
        {
            return;
        }
    }
    if(Gear->Power < 45)
    {
        ++Gear->Power;
        if(ucollisions_TestCollisionYwithGear(hh->Gear, -1) == 0)
        {
            (*hh->Gear).Y = ufloat_hwFloat_hwFloat_op_sub((*hh->Gear).Y, _1);
        }
    }
    graves = ugearsutils_GearsNear(Gear->X, Gear->Y, gtGrave, Gear->Radius);
    if(graves.size == 0)
    {
        usound_StopSoundChan_1(Gear->SoundChannel);
        Gear->Timer = 250;
        Gear->doStep = &(ugearshandlersmess_doStepIdle);
        return;
    }
    if((((Gear->Message & gmAttack) != 0) && ((*hh->Gear).Health > 0)) && (TurnTimeLeft > 0))
    {
        if(((LongInt)graves.size) <= Gear->Tag)
        {
            Gear->Tag = 0;
        }
        --(*hh->Gear).Health;
        if(((*hh->Gear).Health == 0) && ((*hh->Gear).Damage == 0))
        {
            (*hh->Gear).Damage = 1;
        }
        ustore_RenderHealth(&((*hh)));
        uteams_RecountTeamHealth(hh->Team);
        ++(*(*graves.ar)[Gear->Tag]).Health;
        ++Gear->Tag;
    }
    else
    {
        {i = 0;
         LongInt i__end__ = graves.size - 1;
         if (i <= i__end__) do {
                                   if((*(*graves.ar)[i]).Health > 0)
                                   {
                                       resgear = ugearslist_AddGear_8(ufloat_hwRound((*(*graves.ar)[i]).X), ufloat_hwRound((*(*graves.ar)[i]).Y), gtHedgehog, gstWait, _0, _0, 0, (*(*graves.ar)[i]).Pos);
                                       resgear->Hedgehog = (*(*graves.ar)[i]).Hedgehog;
                                       resgear->Health = (*(*graves.ar)[i]).Health;
                                       ((PHedgehog)(*(*graves.ar)[i]).Hedgehog)->Gear = resgear;
                                       (*(*graves.ar)[i]).Message = (*(*graves.ar)[i]).Message | gmDestroy;
                                       (*(*graves.ar)[i]).Active = true;
                                       ustore_RenderHealth(&((*resgear->Hedgehog)));
                                       uteams_RecountTeamHealth((*resgear->Hedgehog).Team);
                                       (*resgear->Hedgehog).Effects[heResurrected] = 1;
                                       if((*resgear->Hedgehog).King)
                                       {
                                           (*(*resgear->Hedgehog).Team).hasKing = true;
                                       }
                                       (*(*(*resgear->Hedgehog).Team).Clan).DeathLogged = false;
                                       if(!(*(*resgear->Hedgehog).Team).Passive)
                                       {
                                           (*(*(*resgear->Hedgehog).Team).Clan).Passive = false;
                                       }
                                       s = fpcrtl_str2astr((*resgear->Hedgehog).Name);
                                       ucaptions_AddCaption(ulocale_FormatA_2(ulocale_GetEventString(eidResurrected), s), capcolDefault, capgrpMessage);
                                       if(_strcompare((*resgear->Hedgehog).Hat, __str6))
                                       {
                                           ustore_LoadHedgehogHat(&((*resgear->Hedgehog)), __str7);
                                       }
                                   }
                               } while(i++ != i__end__);}
        (*hh->Gear).dY = ufloat_hwFloat_op_sub(cLittle);
        (*hh->Gear).dX = _0;
        ugearshedgehog_doStepHedgehogMoving(hh->Gear);
        usound_StopSoundChan_1(Gear->SoundChannel);
        Gear->Timer = 250;
        Gear->doStep = &(ugearshandlersmess_doStepIdle);
    }
};
void ugearshandlersmess_doStepResurrector(PGear Gear)
{
    PGearArrayS graves;
    PHedgehog hh;
    LongInt i;
    AllInactive = false;
    graves = ugearsutils_GearsNear(Gear->X, Gear->Y, gtGrave, Gear->Radius);
    if(graves.size > 0)
    {
        hh = Gear->Hedgehog;
        {i = 0;
         LongInt i__end__ = graves.size - 1;
         if (i <= i__end__) do {
                                   ((PHedgehog)(*(*graves.ar)[i]).Hedgehog)->Gear = NULL;
                                   (*(*graves.ar)[i]).Health = 0;
                               } while(i++ != i__end__);}
        Gear->doStep = &(ugearshandlersmess_doStepResurrectorWork);
        if((((Gear->Message & gmAttack) != 0) && ((*hh->Gear).Health > 0)) && (TurnTimeLeft > 0))
        {
            if(((LongInt)graves.size) <= Gear->Tag)
            {
                Gear->Tag = 0;
            }
            --(*hh->Gear).Health;
            if(((*hh->Gear).Health == 0) && ((*hh->Gear).Damage == 0))
            {
                (*hh->Gear).Damage = 1;
            }
            ustore_RenderHealth(&((*hh)));
            uteams_RecountTeamHealth(hh->Team);
            ++(*(*graves.ar)[Gear->Tag]).Health;
            ++Gear->Tag;
        }
    }
    else
    {
        usound_StopSoundChan_1(Gear->SoundChannel);
        Gear->Timer = 250;
        Gear->doStep = &(ugearshandlersmess_doStepIdle);
    }
};
void ugearshandlersmess_doStepNapalmBomb(PGear Gear)
{
    LongInt i;
    LongInt gX;
    LongInt gY;
    hwFloat dX;
    hwFloat dY;
    AllInactive = false;
    ugearshandlersmess_doStepFallingGear(Gear);
    if((Gear->Timer > 0) && ((Gear->State & gstCollision) != 0))
    {
        ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), 10, Gear->Hedgehog, EXPLAutoSound);
        gX = ufloat_hwRound(Gear->X);
        gY = ufloat_hwRound(Gear->Y);
        {i = 0;
         LongInt i__end__ = 10;
         if (i <= i__end__) do {
                                   dX = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleCos(i * 2), ufloat_hwFloat_LongInt_op_mul(_0_1, i / 5)), ufloat_hwFloat_hwFloat_op_add(urandom_GetRandomf(), _1));
                                   dY = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleSin(i * 8), _0_5), ufloat_hwFloat_hwFloat_op_add(urandom_GetRandomf(), _1));
                                   ugearslist_AddGear_7(gX, gY, gtFlame, 0, dX, dY, 0);
                                   ugearslist_AddGear_7(gX, gY, gtFlame, 0, dX, ufloat_hwFloat_op_sub(dY), 0);
                                   ugearslist_AddGear_7(gX, gY, gtFlame, 0, ufloat_hwFloat_op_sub(dX), dY, 0);
                                   ugearslist_AddGear_7(gX, gY, gtFlame, 0, ufloat_hwFloat_op_sub(dX), ufloat_hwFloat_op_sub(dY), 0);
                               } while(i++ != i__end__);}
        ugearslist_DeleteGear(Gear);
        return;
    }
    if(Gear->Timer == 0)
    {
        ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), 10, Gear->Hedgehog, EXPLAutoSound);
        {i = -19;
         LongInt i__end__ = 19;
         if (i <= i__end__) do {
                                   FollowGear = ugearslist_AddGear_7(ufloat_hwRound(Gear->X) + (i / 3), ufloat_hwRound(Gear->Y), gtFlame, 0, ufloat_hwFloat_LongInt_op_mul(_0_001, i), _0, 0);
                               } while(i++ != i__end__);}
        ugearslist_DeleteGear(Gear);
        return;
    }
    if((GameTicks & 0x3f) == 0)
    {
        uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtSmokeTrace);
    }
    --Gear->Timer;
};
void ugearshandlersmess_doStepTardisWarp(PGear Gear)
{
    PHedgehog HH;
    LongWord i;
    LongWord j;
    LongWord cnt;
    LongInt restoreBottomY;
    astring s;
    HH = Gear->Hedgehog;
    if(Gear->Tag == 0)
    {
        if(HH->Gear != NULL)
        {
            if((((*HH->Gear).Damage != 0) || ((*HH->Gear).Health == 0)) || (((*HH->Gear).State & (((gstMoving | gstHHDeath) | gstHHGone) | gstDrowning)) != 0))
            {
                Gear->Tag = 1;
                (*HH->Gear).State = (*HH->Gear).State & ~gstAttacking;
                (*HH->Gear).Message = (*HH->Gear).Message & ~gmAttack;
                ugearshedgehog_AfterAttack();
            }
        }
        else
        {
            if(HH->GearHidden == NULL)
            {
                Gear->Tag = 1;
            }
        }
        if((Gear->Tag == 1) && (Gear == CurAmmoGear))
        {
            CurAmmoGear = NULL;
        }
    }
    if(Gear->Pos == 2)
    {
        usound_StopSoundChan_1(Gear->SoundChannel);
        Gear->SoundChannel = -1;
        if(Gear->Timer == 0)
        {
            if((HH->Gear != NULL) && (((*HH->Gear).State & gstInvisible) == 0))
            {
                if(Gear->Tag == 0)
                {
                    ugearshedgehog_AfterAttack();
                }
                if(Gear == CurAmmoGear)
                {
                    CurAmmoGear = NULL;
                }
                if(Gear->Tag == 0)
                {
                    ugearshandlersmess_HideHog(HH);
                }
            }
            else
            {
                if(HH->GearHidden != NULL)
                {
                    uteams_RestoreHog(HH);
                    s = fpcrtl_str2astr(HH->Name);
                    ucaptions_AddCaption(ulocale_FormatA_2(ulocale_GetEventString(eidTimeTravelEnd), s), capcolDefault, capgrpMessage);
                }
            }
        }
        ++Gear->Timer;
        if((Gear->Timer > 2000) && ((GameTicks % 2000) == 1000))
        {
            Gear->SoundChannel = usound_LoopSound_1(sndTardis);
            Gear->Pos = 3;
        }
    }
    if(((Gear->Pos == 1) && ((GameTicks & 0x1f) == 0)) && (Gear->Power < 255))
    {
        ++Gear->Power;
        if(((Gear->Power == 172) && (HH->Gear != NULL)) && (Gear->Tag == 0))
        {
            {
                (*HH->Gear).State = (*HH->Gear).State | gstAnimation;
                (*HH->Gear).Tag = 2;
                (*HH->Gear).Timer = 0;
                (*HH->Gear).Pos = 0;
            }
        }
    }
    if(((Gear->Pos == 3) && ((GameTicks & 0x1f) == 0)) && (Gear->Power > 0))
    {
        --Gear->Power;
    }
    if(((Gear->Pos == 1) && (Gear->Power == 255)) && ((GameTicks % 2000) == 1000))
    {
        Gear->Pos = 2;
    }
    if((Gear->Pos == 3) && (Gear->Power == 0))
    {
        usound_StopSoundChan_1(Gear->SoundChannel);
        Gear->SoundChannel = -1;
        if(HH->GearHidden == NULL)
        {
            ugearslist_DeleteGear(Gear);
            return;
        }
        Gear->Pos = 4;
        Gear->Timer = urandom_GetRandom(cHedgehogTurnTime * TeamsCount) + cHedgehogTurnTime;
    }
    if(Gear->Pos == 4)
    {
        cnt = 0;
        {j = 0;
         LongWord j__end__ = ((int)((*(*HH->Team).Clan).TeamsNumber) - 1);
         if (j <= j__end__) do {
                                   {
                                       {i = 0;
                                        LongWord i__end__ = ((int)((*(*(*HH->Team).Clan).Teams[j]).HedgehogsNumber) - 1);
                                        if (i <= i__end__) do {
                                                                  if((((*(*(*HH->Team).Clan).Teams[j]).Hedgehogs[i].Gear != NULL) && (((*(*(*(*HH->Team).Clan).Teams[j]).Hedgehogs[i].Gear).State & gstDrowning) == 0)) && ((*(*(*(*HH->Team).Clan).Teams[j]).Hedgehogs[i].Gear).Health > (*(*(*(*HH->Team).Clan).Teams[j]).Hedgehogs[i].Gear).Damage))
                                                                  {
                                                                      ++cnt;
                                                                  }
                                                              } while(i++ != i__end__);}
                                   }
                               } while(j++ != j__end__);}
        if(((cnt == 0) || SuddenDeathDmg) || (Gear->Timer == 0))
        {
            if(HH->GearHidden != NULL)
            {
                restoreBottomY = cWaterLine;
                ugearsutils_FindPlace_7(&(HH->GearHidden), false, 0, LAND_WIDTH, restoreBottomY, true, false);
                if(SuddenDeathActive && (cWaterRise > 0))
                {
                    restoreBottomY = uutils_Max(topY + (cHHRadius * 5), cWaterLine - (cWaterRise * (TeamsCount + 1)));
                    if((HH->GearHidden != NULL) && (ufloat_hwRound((*HH->GearHidden).Y) > restoreBottomY))
                    {
                        ugearsutils_FindPlace_7(&(HH->GearHidden), false, 0, LAND_WIDTH, restoreBottomY, true, false);
                    }
                    if((HH->GearHidden != NULL) && (ufloat_hwRound((*HH->GearHidden).Y) > restoreBottomY))
                    {
                        restoreBottomY = cWaterLine - ((cWaterLine - topY) / 3);
                        ugearsutils_FindPlace_7(&(HH->GearHidden), false, 0, LAND_WIDTH, restoreBottomY, true, false);
                    }
                }
            }
            if(HH->GearHidden != NULL)
            {
                Gear->X = (*HH->GearHidden).X;
                Gear->Y = (*HH->GearHidden).Y;
            }
            Gear->Timer = 0;
            if((HH->GearHidden != NULL) && (cnt == 0))
            {
                uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtExplosion);
                Gear->Pos = 2;
                Gear->Power = 255;
            }
            else
            {
                Gear->SoundChannel = usound_LoopSound_1(sndTardis);
                Gear->Pos = 1;
                Gear->Power = 0;
            }
        }
        else
        {
            if((*CurrentHedgehog->Team).Clan == (*(*Gear->Hedgehog).Team).Clan)
            {
                --Gear->Timer;
            }
        }
    }
};
void ugearshandlersmess_doStepTardis(PGear Gear)
{
    PHedgehog HH;
    HH = Gear->Hedgehog;
    if(!ugearsutils_CanUseTardis(HH->Gear))
    {
        (*HH->Gear).Message = (*HH->Gear).Message & ~gmAttack;
        (*HH->Gear).State = (*HH->Gear).State & ~gstAttacking;
        usound_PlaySound_1(sndDenied);
        ugearslist_DeleteGear(Gear);
        return;
    }
    Gear->SoundChannel = usound_LoopSound_1(sndTardis);
    Gear->doStep = &(ugearshandlersmess_doStepTardisWarp);
};
void ugearshandlersmess_updateFuel(PGear Gear)
{
    LongInt t;
    t = Gear->Health / 10;
    if((!cOnlyStats && (t != Gear->Damage)) && ((GameTicks & 0x3f) == 0))
    {
        Gear->Damage = t;
        utextures_FreeAndNilTexture(&(Gear->Tex));
        Gear->Tex = urenderutils_RenderStringTex(ulocale_FormatA_2(trmsg[sidFuel], fpcrtl_str2astr(uutils_IntToStr(t))), cWhiteColor, fntSmall);
    }
    if((Gear->Message & (gmUp | gmDown)) != 0)
    {
        if(Gear->Tag != 2)
        {
            usound_StopSoundChan_1(Gear->SoundChannel);
            Gear->SoundChannel = usound_LoopSound_1(sndIceBeamIdle);
            Gear->Tag = 2;
        }
        if((GameTicks % 40) == 0)
        {
            --Gear->Health;
        }
    }
    else
    {
        if(Gear->Tag != 1)
        {
            usound_StopSoundChan_1(Gear->SoundChannel);
            Gear->SoundChannel = usound_LoopSound_1(sndIceBeam);
            Gear->Tag = 1;
        }
        if((GameTicks % 10) == 0)
        {
            --Gear->Health;
        }
    }
};
void ugearshandlersmess_updateTarget(PGear Gear,hwFloat newX,hwFloat newY)
{
    {
        (*Gear).dX = newX;
        (*Gear).dY = newY;
        (*Gear).Pos = 0;
        (*Gear).Target.x = NoPointX;
        (*Gear).LastDamage = NULL;
        (*Gear).X = (*(*Gear).Hedgehog->Gear).X;
        (*Gear).Y = (*(*Gear).Hedgehog->Gear).Y;
    }
};
void ugearshandlersmess_doStepIceGun(PGear Gear)
{
    enum{iceWaitCollision = 0};
    enum{iceCollideWithGround = 1};
    enum{iceCollideWithWater = 5};
    enum{groundFreezingTime = 1000};
    enum{iceRadius = 32};
    enum{iceHeight = 40};
    PGear HHGear;
    PGear iter;
    TSDL_Rect landRect;
    hwFloat ndX;
    hwFloat ndY;
    LongInt i;
    LongInt t;
    LongInt gX;
    LongInt gY;
    PGearArrayS hogs;
    PVisualGear vg;
    HHGear = (*Gear->Hedgehog).Gear;
    if((((((Gear->Message & gmAttack) != 0) || (Gear->Health == 0)) || (HHGear == NULL)) || ((HHGear->State & gstHHDriven) == 0)) || (HHGear->dX.QWordValue > 4294967))
    {
        usound_StopSoundChan_1(Gear->SoundChannel);
        ugearslist_DeleteGear(Gear);
        ugearshedgehog_AfterAttack();
        return;
    }
    ugearshandlersmess_updateFuel(Gear);
    if(WorldEdge != weBounce)
    {
        if((ugearsutils_WorldWrap(&(Gear)) && (WorldEdge == weWrap)) && (Gear->Target.x == NoPointX))
        {
            ++Gear->FlightTime;
        }
    }
    {
        ugearshedgehog_HedgehogChAngle(HHGear);
        ndX = ufloat_hwFloat_hwFloat_op_mul(ufloat_SignAs(ufloat_AngleSin(HHGear->Angle), HHGear->dX), _4);
        ndY = ufloat_hwFloat_hwFloat_op_mul(ufloat_hwFloat_op_sub(ufloat_AngleCos(HHGear->Angle)), _4);
        if((((ufloat_hwFloat_hwFloat_op_neq(ndX, (*Gear).dX)) || (ufloat_hwFloat_hwFloat_op_neq(ndY, (*Gear).dY))) || ((Gear->Message & (gmUp | gmDown)) != 0)) || ((((((((*Gear).Target.x != NoPointX) && (((*Gear).Target.x & LAND_WIDTH_MASK) == 0)) && (((*Gear).Target.y & LAND_HEIGHT_MASK) == 0)) && (ulandutils_LandGet((*Gear).Target.y, (*Gear).Target.x) == 0)) && !ucollisions_CheckCoordInWater((*Gear).Target.x, (*Gear).Target.y)) && (ugearsutils_CheckGearNear_5(gtAirMine, ufloat_int2hwFloat((*Gear).Target.x), ufloat_int2hwFloat((*Gear).Target.y), Gear->Radius * 3, Gear->Radius * 3) == NULL)) && !((WorldEdge == weBounce) && (((*Gear).Target.x > rightX) || ((*Gear).Target.x < leftX)))))
        {
            ugearshandlersmess_updateTarget(Gear, ndX, ndY);
            (*Gear).Timer = iceWaitCollision;
            (*Gear).FlightTime = 0;
        }
        else
        {
            if(!((((ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add((*Gear).X, (*Gear).dX)) > (uutils_Max(LAND_WIDTH, 4096) * 2)) || (ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add((*Gear).X, (*Gear).dX)) < (-uutils_Max(LAND_WIDTH, 4096) * 2))) || (ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add((*Gear).Y, (*Gear).dY)) < (-uutils_Max(LAND_HEIGHT, 4096) * 2))) || (ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add((*Gear).Y, (*Gear).dY)) > (uutils_Max(LAND_HEIGHT, 4096) + 512))))
            {
                (*Gear).X = ufloat_hwFloat_hwFloat_op_add((*Gear).X, (*Gear).dX);
                (*Gear).Y = ufloat_hwFloat_hwFloat_op_add((*Gear).Y, (*Gear).dY);
                gX = ufloat_hwRound((*Gear).X);
                gY = ufloat_hwRound((*Gear).Y);
                if((*Gear).Target.x == NoPointX)
                {
                    t = ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ufloat_hwSqr(ufloat_hwFloat_hwFloat_op_sub((*Gear).X, HHGear->X)), ufloat_hwSqr(ufloat_hwFloat_hwFloat_op_sub((*Gear).Y, HHGear->Y))));
                }
                if((*Gear).Target.x != NoPointX)
                {
                    ugearsutils_CheckCollision(Gear);
                    if((((*Gear).State & gstCollision) != 0) || (ugearsutils_CheckGearNear_5(gtAirMine, ufloat_int2hwFloat((*Gear).Target.x), ufloat_int2hwFloat((*Gear).Target.y), Gear->Radius * 4, Gear->Radius * 4) != NULL))
                    {
                        if((*Gear).Timer == iceWaitCollision)
                        {
                            (*Gear).Timer = iceCollideWithGround;
                            (*Gear).Power = GameTicks;
                        }
                    }
                    else
                    {
                        if(ucollisions_CheckCoordInWater((*Gear).Target.x, (*Gear).Target.y) || ((((((*Gear).Target.x & LAND_WIDTH_MASK) == 0) && (((*Gear).Target.y & LAND_HEIGHT_MASK) == 0)) && (ulandutils_LandGet((*Gear).Target.y, (*Gear).Target.x) == lfIce)) && (((((*Gear).Target.y + iceHeight) + 5) > cWaterLine) || ((WorldEdge == weSea) && (((((*Gear).Target.x + iceHeight) + 5) > rightX) || ((((*Gear).Target.x - iceHeight) - 5) < leftX))))))
                        {
                            if((*Gear).Timer == iceWaitCollision)
                            {
                                (*Gear).Timer = iceCollideWithWater;
                                (*Gear).Power = GameTicks;
                            }
                        }
                    }
                    if((fpcrtl_abs(gX - (*Gear).Target.x) < 2) && (fpcrtl_abs(gY - (*Gear).Target.y) < 2))
                    {
                        (*Gear).X = HHGear->X;
                        (*Gear).Y = HHGear->Y;
                    }
                    if(((*Gear).Timer == iceCollideWithGround) && ((((int64_t) (GameTicks)) - ((int64_t) ((*Gear).Power))) > groundFreezingTime))
                    {
                        ulandgraphics_FillRoundInLandFT((*Gear).Target.x, (*Gear).Target.y, iceRadius, icePixel);
                        landRect.x = uutils_Min(uutils_Max((*Gear).Target.x - iceRadius, 0), LAND_WIDTH - 1);
                        landRect.y = uutils_Min(uutils_Max((*Gear).Target.y - iceRadius, 0), LAND_HEIGHT - 1);
                        landRect.w = uutils_Min(2 * iceRadius, (LAND_WIDTH - landRect.x) - 1);
                        landRect.h = uutils_Min(2 * iceRadius, (LAND_HEIGHT - landRect.y) - 1);
                        ulandtexture_UpdateLandTexture(landRect.x, landRect.w, landRect.y, landRect.h, true);
                        iter = GearsList;
                        while(iter != NULL)
                        {
                            if(((((iter->State & gstFrozen) == 0) && (((((iter->Kind == gtExplosives) || (iter->Kind == gtAirMine)) || (iter->Kind == gtCase)) || (iter->Kind == gtMine)) || (iter->Kind == gtSMine))) && (((fpcrtl_abs(ufloat_hwRound(iter->X) - (*Gear).Target.x) + fpcrtl_abs(ufloat_hwRound(iter->Y) - (*Gear).Target.y)) + 2) < (2 * iceRadius))) && (ufloat_hwFloat_hwFloat_op_lt(ufloat_Distance(ufloat_hwFloat_hwFloat_op_sub(iter->X, ufloat_int2hwFloat((*Gear).Target.x)), ufloat_hwFloat_hwFloat_op_sub(iter->Y, ufloat_int2hwFloat((*Gear).Target.y))), ufloat_int2hwFloat(iceRadius * 2))))
                            {
                                {t = 0;
                                 LongInt t__end__ = 5;
                                 if (t <= t__end__) do {
                                                           vg = uvisualgearslist_AddVisualGear_4((ufloat_hwRound(iter->X) + fpcrtl_random(4)) - 8, ufloat_hwRound(iter->Y) + fpcrtl_random(8), vgtDust, 1);
                                                           if(vg != NULL)
                                                           {
                                                               i = fpcrtl_random(100) + 155;
                                                               vg->Tint = (((i << 24) | (i << 16)) | (0xff << 8)) | (fpcrtl_random(200) + 55);
                                                               vg->Angle = fpcrtl_random(360);
                                                               vg->dX = 1.0e-3 * fpcrtl_random(80);
                                                               vg->dY = 1.0e-3 * fpcrtl_random(80);
                                                           }
                                                       } while(t++ != t__end__);}
                                usound_PlaySound_1(sndHogFreeze);
                                if(iter->Kind == gtMine)
                                {
                                    iter->State = iter->State | gstFrozen;
                                    vg = uvisualgearslist_AddVisualGear_3((ufloat_hwRound(iter->X) - 4) + fpcrtl_random(8), (ufloat_hwRound(iter->Y) - 4) - fpcrtl_random(4), vgtSmoke);
                                    if(vg != NULL)
                                    {
                                        vg->scale = 0.5;
                                    }
                                    usound_PlaySound_1(sndVaporize);
                                    iter->Health = 0;
                                    iter->Damage = 0;
                                    iter->State = iter->State & ~gstAttacking;
                                }
                                else
                                {
                                    if(iter->Kind == gtSMine)
                                    {
                                        iter->State = iter->State | gstFrozen;
                                        iter->CollisionMask = 0;
                                        vg = uvisualgearslist_AddVisualGear_3((ufloat_hwRound(iter->X) - 2) + fpcrtl_random(4), (ufloat_hwRound(iter->Y) - 2) - fpcrtl_random(2), vgtSmoke);
                                        if(vg != NULL)
                                        {
                                            vg->scale = 0.4;
                                        }
                                        usound_PlaySound_1(sndVaporize);
                                        iter->State = iter->State & ~gstAttacking;
                                    }
                                    else
                                    {
                                        if(iter->Kind == gtCase)
                                        {
                                            ucollisions_DeleteCI(iter);
                                            iter->State = iter->State | gstFrozen;
                                            ucollisions_AddCI(iter);
                                        }
                                        else
                                        {
                                            if(iter->Kind == gtAirMine)
                                            {
                                                iter->Damage = 0;
                                                iter->State = iter->State | gstFrozen;
                                                if((((ufloat_hwRound(iter->X) < (rightX - 16)) && (ufloat_hwRound(iter->X) > (leftX + 16))) && (ufloat_hwRound(iter->Y) > (topY + 16))) && (ufloat_hwRound(iter->Y) < (LAND_HEIGHT - 16)))
                                                {
                                                    ucollisions_AddCI(iter);
                                                    iter->X = ufloat_int2hwFloat(uutils_Min(rightX - 16, uutils_Max(ufloat_hwRound(iter->X), leftX + 16)));
                                                    iter->Y = ufloat_int2hwFloat(uutils_Min(LAND_HEIGHT - 16, uutils_Max(ufloat_hwRound(iter->Y), topY + 16)));
                                                    ulandgraphics_ForcePlaceOnLand(ufloat_hwRound(iter->X) - 16, ufloat_hwRound(iter->Y) - 16, sprFrozenAirMine, 0, lfIce, 0xffffffff, false, false, false);
                                                    iter->State = iter->State | gstInvisible;
                                                }
                                                else
                                                {
                                                    ugearshandlersmess_updateTarget(Gear, ndX, ndY);
                                                    (*Gear).FlightTime = 0;
                                                    (*Gear).Timer = iceWaitCollision;
                                                    (*Gear).Power = GameTicks;
                                                    iter->State = iter->State & ~gstNoGravity;
                                                }
                                            }
                                            else
                                            {
                                                iter->State = iter->State | gstFrozen;
                                                iter->Health = iter->Health + cBarrelHealth;
                                            }
                                        }
                                    }
                                }
                            }
                            iter = iter->NextGear;
                        }
                        ugearsutils_SetAllHHToActive_0();
                        (*Gear).Timer = iceWaitCollision;
                        (*Gear).Power = GameTicks;
                    }
                    if(((*Gear).Timer == iceCollideWithWater) && ((((int64_t) (GameTicks)) - ((int64_t) ((*Gear).Power))) > (groundFreezingTime / 2)))
                    {
                        usound_PlaySound_1(sndHogFreeze);
                        if(ucollisions_CheckCoordInWater((*Gear).Target.x, (*Gear).Target.y))
                        {
                            ulandgraphics_DrawIceBreak((*Gear).Target.x, (*Gear).Target.y, iceRadius, iceHeight);
                        }
                        else
                        {
                            if((((*Gear).Target.y + iceHeight) + 5) > cWaterLine)
                            {
                                ulandgraphics_DrawIceBreak((*Gear).Target.x, ((*Gear).Target.y + iceHeight) + 5, iceRadius, iceHeight);
                            }
                            else
                            {
                                if((((*Gear).Target.x + iceHeight) + 5) > rightX)
                                {
                                    ulandgraphics_DrawIceBreak(((*Gear).Target.x + iceHeight) + 5, (*Gear).Target.y, iceRadius, iceHeight);
                                }
                                else
                                {
                                    ulandgraphics_DrawIceBreak(((*Gear).Target.x - iceHeight) - 5, (*Gear).Target.y, iceRadius, iceHeight);
                                }
                            }
                        }
                        ugearsutils_SetAllHHToActive_0();
                        (*Gear).Timer = iceWaitCollision;
                    }
                    hogs = ugearsutils_GearsNear(ufloat_int2hwFloat((*Gear).Target.x), ufloat_int2hwFloat((*Gear).Target.y), gtHedgehog, Gear->Radius * 2);
                    if(hogs.size > 0)
                    {
                        {i = 0;
                         LongInt i__end__ = hogs.size - 1;
                         if (i <= i__end__) do {
                                                   if((*hogs.ar)[i] != HHGear)
                                                   {
                                                       if((GameTicks % 5) == 0)
                                                       {
                                                           (*(*hogs.ar)[i]).Active = true;
                                                           if((*(*(*hogs.ar)[i]).Hedgehog).Effects[heFrozen] < 256)
                                                           {
                                                               (*(*(*hogs.ar)[i]).Hedgehog).Effects[heFrozen] = (*(*(*hogs.ar)[i]).Hedgehog).Effects[heFrozen] + 1;
                                                           }
                                                           else
                                                           {
                                                               if((*(*(*hogs.ar)[i]).Hedgehog).Effects[heFrozen] == 256)
                                                               {
                                                                   (*(*(*hogs.ar)[i]).Hedgehog).Effects[heFrozen] = 200000 - 1;
                                                                   usound_PlaySound_1(sndHogFreeze);
                                                               }
                                                           }
                                                       }
                                                   }
                                               } while(i++ != i__end__);}
                    }
                    ++(*Gear).Pos;
                }
                else
                {
                    if((t > 400) && (ucollisions_CheckCoordInWater(gX, gY) || ((((gX & LAND_WIDTH_MASK) == 0) && ((gY & LAND_HEIGHT_MASK) == 0)) && (ulandutils_LandGet(gY, gX) != 0))))
                    {
                        (*Gear).Target.x = gX;
                        (*Gear).Target.y = gY;
                        (*Gear).X = HHGear->X;
                        (*Gear).Y = HHGear->Y;
                    }
                    else
                    {
                        if((WorldEdge == weBounce) && ((gX > rightX) || (gX < leftX)))
                        {
                            (*Gear).Target.x = gX;
                            (*Gear).Target.y = gY;
                            (*Gear).X = HHGear->X;
                            (*Gear).Y = HHGear->Y;
                        }
                        else
                        {
                            iter = ugearsutils_CheckGearNear_4(Gear, gtAirMine, Gear->Radius * 2, Gear->Radius * 2);
                            if((iter != NULL) && (iter->State != gstFrozen))
                            {
                                (*Gear).Target.x = gX;
                                (*Gear).Target.y = gY;
                                (*Gear).X = HHGear->X;
                                (*Gear).Y = HHGear->Y;
                            }
                        }
                    }
                }
            }
        }
    }
};
void ugearshandlersmess_doStepAddAmmo(PGear Gear)
{
    TAmmoType a;
    PGear gi;
    if(Gear->Timer > 0)
    {
        --Gear->Timer;
    }
    else
    {
        CheckSum = CheckSum ^ GameTicks;
        gi = GearsList;
        while(gi != NULL)
        {
            {
                CheckSum = (((((((CheckSum ^ (*gi).X.Round) ^ (*gi).X.Frac) ^ (*gi).dX.Round) ^ (*gi).dX.Frac) ^ (*gi).Y.Round) ^ (*gi).Y.Frac) ^ (*gi).dY.Round) ^ (*gi).dY.Frac;
            }
            urandom_AddRandomness(CheckSum);
            if((gi->Kind == gtGenericFaller) && (gi->Tag == 1))
            {
                gi->State = gi->State & ~gsttmpFlag;
            }
            gi = gi->NextGear;
        }
        if(Gear->Pos == posCaseUtility)
        {
            a = ugearsutils_GetUtility(Gear->Hedgehog);
        }
        else
        {
            a = ugearsutils_GetAmmo(Gear->Hedgehog);
        }
        ugearshedgehog_AddPickup((*Gear->Hedgehog), a, Gear->Power, ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y));
        ugearslist_DeleteGear(Gear);
    }
};
void ugearshandlersmess_doStepGenericFaller(PGear Gear)
{
    if(Gear->Timer < 0xffffffff)
    {
        if(Gear->Timer > 0)
        {
            --Gear->Timer;
        }
        else
        {
            ugearslist_DeleteGear(Gear);
            return;
        }
    }
    if(((Gear->State & gsttmpFlag) != 0) || ((GameTicks & 0x7) == 0))
    {
        ugearshandlersmess_doStepFallingGear(Gear);
        if(((((Gear->Tag == 1) && ((GameTicks & 0xff) == 0)) && (ufloat_hwRound(Gear->X) < leftX)) || (ufloat_hwRound(Gear->X) > rightX)) || (ufloat_hwRound(Gear->Y) < topY))
        {
            Gear->X = ufloat_int2hwFloat(urandom_GetRandom(rightX - leftX) + leftX);
            Gear->Y = ufloat_int2hwFloat(urandom_GetRandom(LAND_HEIGHT - topY) + topY);
            Gear->dX = ufloat_hwFloat_hwFloat_op_sub(_90, ufloat_hwFloat_hwFloat_op_mul(urandom_GetRandomf(), _360));
            Gear->dY = ufloat_hwFloat_hwFloat_op_sub(_90, ufloat_hwFloat_hwFloat_op_mul(urandom_GetRandomf(), _360));
        }
    }
};
void ugearshandlersmess_doStepCreeper(PGear Gear)
{
    LongWord i;
    LongWord t;
    LongWord targDist;
    LongWord tmpDist;
    PGear targ;
    PGear tmpG;
    hwFloat tX;
    hwFloat tY;
    PVisualGear vg;
    targ = NULL;
    ugearshandlersmess_doStepFallingGear(Gear);
    if((Gear->State & gstFrozen) != 0)
    {
        if(Gear->Damage > 0)
        {
            ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
            ugearslist_DeleteGear(Gear);
        }
        return;
    }
    if((((TurnTimeLeft == 0) || (Gear->Angle == 0)) || (Gear->Hedgehog == NULL)) || ((*Gear->Hedgehog).Gear == NULL))
    {
        Gear->Hedgehog = NULL;
        targ = NULL;
    }
    else
    {
        if(Gear->Hedgehog != NULL)
        {
            targ = (*Gear->Hedgehog).Gear;
        }
    }
    if(((targ != NULL) && ((GameTicks & 0x3f) == 0)) && (ucollisions_TestCollisionYKick(Gear, 1) != 0))
    {
        vg = uvisualgearslist_AddVisualGear_3(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtSmokeWhite);
        if(vg != NULL)
        {
            vg->Tint = 0xff0000ff;
        }
        if(ufloat_hwFloat_hwFloat_op_lt(Gear->X, targ->X))
        {
            if((WorldEdge == weWrap) && (ufloat_hwFloat_hwFloat_op_gt(ufloat_hwFloat_hwFloat_op_sub(targ->X, Gear->X), ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_sub(Gear->X, ufloat_int2hwFloat(leftX)), ufloat_hwFloat_hwFloat_op_sub(ufloat_int2hwFloat(rightX), targ->X)))))
            {
                Gear->dX = ufloat_hwFloat_op_sub(cLittle);
            }
            else
            {
                Gear->dX = cLittle;
            }
        }
        else
        {
            if(ufloat_hwFloat_hwFloat_op_gt(Gear->X, targ->X))
            {
                if((WorldEdge == weWrap) && (ufloat_hwFloat_hwFloat_op_gt(ufloat_hwFloat_hwFloat_op_sub(Gear->X, targ->X), ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_sub(targ->X, ufloat_int2hwFloat(leftX)), ufloat_hwFloat_hwFloat_op_sub(ufloat_int2hwFloat(rightX), Gear->X)))))
                {
                    Gear->dX = cLittle;
                }
                else
                {
                    Gear->dX = ufloat_hwFloat_op_sub(cLittle);
                }
            }
        }
        if(urandom_GetRandom(30) == 0)
        {
            Gear->dY = ufloat_hwFloat_op_sub(_0_15);
            Gear->dX = ufloat_SignAs(_0_15, Gear->dX);
        }
        ugearsutils_MakeHedgehogsStep(Gear);
    }
    if((TurnTimeLeft == 0) && ((Gear->dX.QWordValue + Gear->dY.QWordValue) > _0_02.QWordValue))
    {
        AllInactive = false;
    }
    if(targ != NULL)
    {
        tX = ufloat_hwFloat_hwFloat_op_sub(Gear->X, targ->X);
        tY = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, targ->Y);
        if((GameTicks > (Gear->FlightTime + 10000)) || (((tX.Round + tY.Round) > (Gear->Angle * 6)) && (ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ufloat_hwSqr(tX), ufloat_hwSqr(tY))) > fpcrtl_sqr(Gear->Angle * 6))))
        {
            targ = NULL;
        }
    }
    if(((((ReadyTimeLeft > 0) || (TurnTimeLeft == 0)) || ((TurnTimeLeft < cHedgehogTurnTime) && ((((int64_t) (cHedgehogTurnTime)) - ((int64_t) (TurnTimeLeft))) < 5000))) || ((Gear->State & gsttmpFlag) == 0)) || (Gear->Angle == 0))
    {
        Gear->State = Gear->State & ~gstChooseTarget;
    }
    else
    {
        if((((Gear->State & gstAttacking) == 0) && ((GameTicks & 0xff) == 17)) && (GameTicks > Gear->FlightTime))
        {
            Gear->State = Gear->State | gstChooseTarget;
            if(targ != NULL)
            {
                targDist = ufloat_Distance(ufloat_hwFloat_hwFloat_op_sub(Gear->X, targ->X), ufloat_hwFloat_hwFloat_op_sub(Gear->Y, targ->Y)).Round;
            }
            else
            {
                targDist = 0;
            }
            {t = 0;
             LongWord t__end__ = ((int)(TeamsCount) - 1);
             if (t <= t__end__) do {
                                       {
                                           {i = 0;
                                            LongWord i__end__ = cMaxHHIndex;
                                            if (i <= i__end__) do {
                                                                      if((*TeamsArray[t]).Hedgehogs[i].Gear != NULL)
                                                                      {
                                                                          tmpG = (*TeamsArray[t]).Hedgehogs[i].Gear;
                                                                          tX = ufloat_hwFloat_hwFloat_op_sub(Gear->X, tmpG->X);
                                                                          tY = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, tmpG->Y);
                                                                          if((Gear->Angle == 0xffffffff) || (((tX.Round + tY.Round) < Gear->Angle) && (ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ufloat_hwSqr(tX), ufloat_hwSqr(tY))) < fpcrtl_sqr(Gear->Angle))))
                                                                          {
                                                                              if(targ != NULL)
                                                                              {
                                                                                  tmpDist = ufloat_Distance(tX, tY).Round;
                                                                              }
                                                                              if((targ == NULL) || (tmpDist < targDist))
                                                                              {
                                                                                  if(targ == NULL)
                                                                                  {
                                                                                      targDist = ufloat_Distance(tX, tY).Round;
                                                                                  }
                                                                                  else
                                                                                  {
                                                                                      targDist = tmpDist;
                                                                                  }
                                                                                  Gear->Hedgehog = &((*TeamsArray[t]).Hedgehogs[i]);
                                                                                  targ = tmpG;
                                                                              }
                                                                          }
                                                                      }
                                                                  } while(i++ != i__end__);}
                                       }
                                   } while(t++ != t__end__);}
            if(targ != NULL)
            {
                Gear->FlightTime = GameTicks + 5000;
            }
        }
    }
    if(((Gear->State & gsttmpFlag) != 0) && (Gear->Health != 0))
    {
        if((Gear->State & gstAttacking) == 0)
        {
            if((GameTicks & 0x1f) == 0)
            {
                if(targ != NULL)
                {
                    tX = ufloat_hwFloat_hwFloat_op_sub(Gear->X, targ->X);
                    tY = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, targ->Y);
                    if(((tX.Round + tY.Round) < Gear->Boom) && (ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ufloat_hwSqr(tX), ufloat_hwSqr(tY))) < fpcrtl_sqr(Gear->Boom)))
                    {
                        Gear->State = Gear->State | gstAttacking;
                    }
                }
                else
                {
                    if((Gear->Angle > 0) && (ugearsutils_CheckGearNear_4(Gear, gtHedgehog, Gear->Boom, Gear->Boom) != NULL))
                    {
                        Gear->State = Gear->State | gstAttacking;
                    }
                }
            }
        }
        else
        {
            AllInactive = false;
            if((Gear->Timer & 0x1ff) == 0)
            {
                usound_PlaySound_1(sndVaporize);
            }
            if(Gear->Timer == 0)
            {
                if(targ != NULL)
                {
                    tX = ufloat_hwFloat_hwFloat_op_sub(Gear->X, targ->X);
                    tY = ufloat_hwFloat_hwFloat_op_sub(Gear->Y, targ->Y);
                    if(((tX.Round + tY.Round) < Gear->Boom) && (ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ufloat_hwSqr(tX), ufloat_hwSqr(tY))) < fpcrtl_sqr(Gear->Boom)))
                    {
                        Gear->Hedgehog = CurrentHedgehog;
                        tmpG = FollowGear;
                        ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
                        FollowGear = tmpG;
                        ugearslist_DeleteGear(Gear);
                        return;
                    }
                }
                else
                {
                    if((Gear->Angle > 0) && (ugearsutils_CheckGearNear_4(Gear, gtHedgehog, Gear->Boom, Gear->Boom) != NULL))
                    {
                        Gear->Hedgehog = CurrentHedgehog;
                        ugearsutils_doMakeExplosion_5(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Boom, Gear->Hedgehog, EXPLAutoSound);
                        ugearslist_DeleteGear(Gear);
                        return;
                    }
                }
                Gear->State = Gear->State & ~gstAttacking;
                Gear->Timer = Gear->WDTimer;
            }
            if(Gear->Timer > 0)
            {
                --Gear->Timer;
            }
        }
    }
    else
    {
        if(((TurnTimeLeft == 0) || (((GameFlags & gfInfAttack) != 0) && (GameTicks > Gear->FlightTime))) || (CurrentHedgehog->Gear == NULL))
        {
            Gear->FlightTime = GameTicks;
            Gear->State = Gear->State | gsttmpFlag;
        }
    }
};
void ugearshandlersmess_doStepKnife(PGear Gear)
{
    real a;
    if((Gear->Radius == 4) && (Gear->CollisionMask == lfAll))
    {
        Gear->Radius = 7;
    }
    if(Gear->Damage > 100)
    {
        Gear->CollisionMask = 0;
    }
    else
    {
        if(Gear->Damage > 30)
        {
            if(urandom_GetRandom(uutils_Max(4, 18 - (Gear->Damage / 10))) < 3)
            {
                Gear->CollisionMask = 0;
            }
        }
    }
    Gear->Damage = 0;
    if(Gear->Timer > 0)
    {
        --Gear->Timer;
    }
    if(((Gear->State & gstMoving) != 0) && ((Gear->State & gstCollision) == 0))
    {
        ucollisions_DeleteCI(Gear);
        Gear->Radius = 7;
        Gear->Health = ufloat_hwRound(ufloat_hwSqr(ufloat_hwFloat_LongInt_op_div(ufloat_hwFloat_LongInt_op_mul(ufloat_hwFloat_hwFloat_op_add(ufloat_hwAbs(Gear->dY), ufloat_hwAbs(Gear->dX)), Gear->Boom), 10000)));
        ugearshandlersmess_doStepFallingGear(Gear);
        AllInactive = false;
        a = Gear->DirAngle;
        ugearsutils_CalcRotationDirAngle(Gear);
        Gear->DirAngle = a + (((Gear->DirAngle - a) * 2) * ufloat_hwSign(Gear->dX));
    }
    else
    {
        if((Gear->CollisionIndex == -1) && (Gear->Timer == 0))
        {
            if(Gear->Health > 0)
            {
                usound_PlaySound_1(Gear->ImpactSound);
            }
            Gear->DirAngle = uutils_DxDy2Angle(Gear->dX, Gear->dY) + (fpcrtl_random(30) - 15);
            if((Gear->dX.isNegative && Gear->dY.isNegative) || (!Gear->dX.isNegative && !Gear->dY.isNegative))
            {
                Gear->DirAngle = Gear->DirAngle - 90;
            }
            Gear->dX = _0;
            Gear->dY = _0;
            Gear->State = (Gear->State & ~gstMoving) | gstCollision;
            Gear->Radius = 16;
            if(Gear->Health > 0)
            {
                ugearsutils_AmmoShove(Gear, Gear->Health, 0);
            }
            Gear->Health = 0;
            Gear->Timer = 500;
            ucollisions_AddCI(Gear);
        }
        else
        {
            if((GameTicks & 0x3f) == 0)
            {
                if((((ucollisions_TestCollisionYwithGear(Gear, -1) == 0) && (ucollisions_TestCollisionXwithGear(Gear, 1) == 0)) && (ucollisions_TestCollisionXwithGear(Gear, -1) == 0)) && (ucollisions_TestCollisionYwithGear(Gear, 1) == 0))
                {
                    Gear->State = (Gear->State & ~gstCollision) | gstMoving;
                }
            }
        }
    }
};
void ugearshandlersmess_doStepMinigunWork(PGear Gear)
{
    PGear HHGear;
    PGear bullet;
    hwFloat rx;
    hwFloat ry;
    LongInt gX;
    LongInt gY;
    AllInactive = false;
    HHGear = (*Gear->Hedgehog).Gear;
    if(HHGear == NULL)
    {
        ucollisions_ClearHitOrder();
        ugearslist_DeleteGear(Gear);
        return;
    }
    ugearshedgehog_HedgehogChAngle(HHGear);
    --Gear->Timer;
    if((Gear->Timer % 50) == 0)
    {
        Gear->Tag = ((Gear->Tag - 1) & 1) + 2;
        gX = ufloat_hwRound(Gear->X) + uutils_GetLaunchX(amMinigun, ufloat_hwSign(HHGear->dX), HHGear->Angle);
        gY = ufloat_hwRound(Gear->Y) + uutils_GetLaunchY(amMinigun, HHGear->Angle);
        rx = urandom_rndSign(ufloat_hwFloat_hwFloat_op_mul(urandom_GetRandomf(), _0_2));
        ry = urandom_rndSign(ufloat_hwFloat_hwFloat_op_mul(urandom_GetRandomf(), _0_2));
        bullet = ugearslist_AddGear_7(gX, gY, gtMinigunBullet, 0, ufloat_hwFloat_hwFloat_op_add(ufloat_SignAs(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleSin(HHGear->Angle), _0_8), HHGear->dX), rx), ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_mul(ufloat_AngleCos(HHGear->Angle), ufloat_hwFloat_op_sub(_0_8)), ry), 0);
        bullet->CollisionMask = lfNotCurHogCrate;
        bullet->WDTimer = Gear->WDTimer;
        ++Gear->WDTimer;
        ugearshandlersmess_CreateShellForGear(Gear, Gear->Tag & 1);
    }
    if((Gear->Timer == 0) || ((HHGear->State & gstHHDriven) == 0))
    {
        if((HHGear->State & gstHHDriven) == 0)
        {
            usound_StopSound_1(sndMinigun);
        }
        HHGear->State = HHGear->State & ~gstNotKickable;
        ucollisions_ClearHitOrder();
        ugearslist_DeleteGear(Gear);
        ugearshedgehog_AfterAttack();
    }
};
void ugearshandlersmess_doStepMinigun(PGear Gear)
{
    PGear HHGear;
    --Gear->Timer;
    if((Gear->Timer % 100) == 0)
    {
        Gear->Tag = (Gear->Tag + 1) & 1;
    }
    if(Gear->Timer == 0)
    {
        Gear->Tag = 2;
        HHGear = (*Gear->Hedgehog).Gear;
        HHGear->Message = HHGear->Message & ~(gmUp | gmDown);
        HHGear->State = HHGear->State | gstNotKickable;
        Gear->Timer = Gear->Karma;
        Gear->WDTimer = 0;
        ucollisions_ClearHitOrder();
        Gear->doStep = &(ugearshandlersmess_doStepMinigunWork);
    }
};
void ugearshandlersmess_doStepMinigunBullet(PGear Gear)
{
    if(Gear->Data == NULL)
    {
        if((Gear->Hedgehog != NULL) && ((*Gear->Hedgehog).Gear != NULL))
        {
            Gear->Data = ((pointer)(*Gear->Hedgehog).Gear);
        }
    }
    Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, ufloat_hwFloat_LongInt_op_mul(Gear->dX, 2));
    Gear->Y = ufloat_hwFloat_hwFloat_op_add(Gear->Y, ufloat_hwFloat_LongInt_op_mul(Gear->dY, 2));
    Gear->FlightTime = 0;
    Gear->doStep = &(ugearshandlersmess_doStepBulletWork);
};
boolean ugearshandlersmess_MakeSentryStep(PGear Sentry,LongInt maxYStep,boolean TestOnly)
{
    boolean makesentrystep_result;
    LongInt x;
    LongInt y;
    LongInt offset;
    LongInt direction;
    makesentrystep_result = false;
    x = ufloat_hwRound(Sentry->X);
    y = ufloat_hwRound(Sentry->Y);
    direction = ufloat_hwSign(Sentry->dX);
    {offset = -maxYStep - 1;
     LongInt offset__end__ = maxYStep + 1;
     if (offset <= offset__end__) do {
                                         if(ucollisions_TestCollisionYImpl(x + direction, y + offset, Sentry->Radius, 1, Sentry->CollisionMask) != 0)
                                         {
                                             break;
                                         }
                                     } while(offset++ != offset__end__);}
    if(((offset >= -maxYStep) && (offset <= maxYStep)) && (ucollisions_TestCollisionYImpl(x + direction, y + offset, Sentry->Radius, -1, Sentry->CollisionMask) == 0))
    {
        if(!TestOnly)
        {
            Sentry->X = ufloat_hwFloat_hwFloat_op_add(Sentry->X, ufloat_SignAs(_1, Sentry->dX));
            Sentry->Y = ufloat_hwFloat_hwFloat_op_add(Sentry->Y, ufloat_int2hwFloat(offset));
        }
        makesentrystep_result = true;
    }
    return makesentrystep_result;
};
boolean ugearshandlersmess_MakeSentryJump(PGear Sentry,LongInt maxXStep,LongInt maxYStep)
{
    boolean makesentryjump_result;
    LongInt x;
    LongInt y;
    LongInt offsetX;
    LongInt offsetY;
    LongInt direction;
    hwFloat jumpTime;
    makesentryjump_result = false;
    x = ufloat_hwRound(Sentry->X);
    y = ufloat_hwRound(Sentry->Y);
    offsetX = maxXStep - Sentry->Radius;
    direction = ufloat_hwSign(Sentry->dX);
    do {
           {offsetY = -maxYStep - 1;
            LongInt offsetY__end__ = maxYStep + 1;
            if (offsetY <= offsetY__end__) do {
                                                  if(ucollisions_TestCollisionYImpl(x + (offsetX * direction), y + offsetY, Sentry->Radius, 1, Sentry->CollisionMask) != 0)
                                                  {
                                                      break;
                                                  }
                                              } while(offsetY++ != offsetY__end__);}
           if((offsetY >= -maxYStep) && (offsetY <= maxYStep))
           {
               break;
           }
           offsetX -= Sentry->Radius;
       } while(!(offsetX <= 0));
    if((offsetX >= Sentry->Radius) && !cGravity.isNegative)
    {
        Sentry->dY = ufloat_hwFloat_op_sub(_0_25);
        jumpTime = ufloat_hwFloat_hwFloat_op_div(ufloat_hwFloat_hwFloat_op_mul(_2, Sentry->dY), cGravity);
        Sentry->dX = ufloat_SignAs(ufloat_hwFloat_hwFloat_op_div(ufloat_int2hwFloat(offsetX - Sentry->Radius), jumpTime), Sentry->dX);
        Sentry->State = Sentry->State | gstHHJumping;
        makesentryjump_result = true;
    }
    return makesentryjump_result;
};
LongWord ugearshandlersmess_TraceAttackPath(hwFloat fromX,hwFloat fromY,hwFloat toX,hwFloat toY,hwFloat step,Word mask)
{
    LongWord traceattackpath_result;
    hwFloat distX;
    hwFloat distY;
    hwFloat dist;
    hwFloat invDistance;
    LongInt i;
    LongInt count;
    traceattackpath_result = 0;
    if(((((ufloat_hwFloat_hwFloat_op_lt(step, _1)) || ((ufloat_hwRound(fromX) & LAND_WIDTH_MASK) != 0)) || ((ufloat_hwRound(toX) & LAND_WIDTH_MASK) != 0)) || ((ufloat_hwRound(fromY) & LAND_HEIGHT_MASK) != 0)) || ((ufloat_hwRound(toY) & LAND_HEIGHT_MASK) != 0))
    {
        return traceattackpath_result;
    }
    distX = ufloat_hwFloat_hwFloat_op_sub(toX, fromX);
    distY = ufloat_hwFloat_hwFloat_op_sub(toY, fromY);
    dist = ufloat_Distance(distX, distY);
    count = ufloat_hwRound(ufloat_hwFloat_hwFloat_op_div(dist, step));
    invDistance = ufloat_hwFloat_hwFloat_op_div(step, dist);
    distX = ufloat_hwFloat_hwFloat_op_mul(distX, invDistance);
    distY = ufloat_hwFloat_hwFloat_op_mul(distY, invDistance);
    {i = 0;
     LongInt i__end__ = count - 1;
     if (i <= i__end__) do {
                               if((ulandutils_LandGet(ufloat_hwRound(fromY), ufloat_hwRound(fromX)) & mask) != 0)
                               {
                                   ++traceattackpath_result;
                               }
                               fromX = ufloat_hwFloat_hwFloat_op_add(fromX, distX);
                               fromY = ufloat_hwFloat_hwFloat_op_add(fromY, distY);
                           } while(i++ != i__end__);}
    return traceattackpath_result;
};
boolean ugearshandlersmess_CheckSentryAttackRange(PGear Sentry,hwFloat targetX,hwFloat targetY)
{
    boolean checksentryattackrange_result;
    hwFloat distX;
    hwFloat distY;
    distX = ufloat_hwFloat_hwFloat_op_sub(targetX, Sentry->X);
    distY = ufloat_hwFloat_hwFloat_op_sub(targetY, Sentry->Y);
    checksentryattackrange_result = ((((distX.isNegative == Sentry->dX.isNegative) && (distX.Round > 24)) && (distX.Round < 500)) && (ufloat_hwFloat_hwFloat_op_lt(ufloat_hwAbs(distY), ufloat_hwAbs(ufloat_hwFloat_hwFloat_op_mul(distX, _1_5))))) && (ugearshandlersmess_TraceAttackPath(Sentry->X, Sentry->Y, targetX, targetY, _4, lfLandMask) <= 18);
    return checksentryattackrange_result;
};
void ugearshandlersmess_ResetSentryState(PGear Gear,LongInt state,LongInt timer)
{
    Gear->Timer = timer;
    Gear->Tag = state;
    Gear->Target.x = 0;
    Gear->Target.y = 0;
    if(Gear->Karma != 0)
    {
        ucollisions_ClearGlobalHitOrderLeq(Gear->Karma);
        Gear->Karma = 0;
    }
};
boolean ugearshandlersmess_CheckSentryDestroyed(PGear Sentry,LongInt damagedState)
{
    boolean checksentrydestroyed_result;
    checksentrydestroyed_result = false;
    if(Sentry->Damage > 0)
    {
        Sentry->Health -= Sentry->Damage;
        Sentry->Damage = 0;
        if(Sentry->Health <= 0)
        {
            ugearsutils_doMakeExplosion_5(ufloat_hwRound(Sentry->X), ufloat_hwRound(Sentry->Y), Sentry->Boom, Sentry->Hedgehog, EXPLAutoSound);
            ugearslist_DeleteGear(Sentry);
            checksentrydestroyed_result = true;
            return checksentrydestroyed_result;
        }
        else
        {
            ugearshandlersmess_ResetSentryState(Sentry, damagedState, 10000);
        }
    }
    if(((Sentry->Health * 100) < fpcrtl_random(cSentryHealth * 90)) && ((GameTicks & 0xff) == 0))
    {
        if((Sentry->Health * 2) < cSentryHealth)
        {
            uvisualgearslist_AddVisualGear_3((ufloat_hwRound(Sentry->X) - 8) + fpcrtl_random(16), ufloat_hwRound(Sentry->Y) - 2, vgtSmoke);
        }
        else
        {
            uvisualgearslist_AddVisualGear_3((ufloat_hwRound(Sentry->X) - 8) + fpcrtl_random(16), ufloat_hwRound(Sentry->Y) - 2, vgtSmokeWhite);
        }
    }
    return checksentrydestroyed_result;
};
void ugearshandlersmess_AimSentry(PGear Sentry)
{
    PGear HHGear;
    if(CurrentHedgehog != NULL)
    {
        HHGear = CurrentHedgehog->Gear;
        if(HHGear != NULL)
        {
            Sentry->Target.x = Sentry->Target.x + ufloat_hwSign(ufloat_hwFloat_hwFloat_op_sub(HHGear->X, ufloat_int2hwFloat(Sentry->Target.x)));
            Sentry->Target.y = Sentry->Target.y + ufloat_hwSign(ufloat_hwFloat_hwFloat_op_sub(HHGear->Y, ufloat_int2hwFloat(Sentry->Target.y)));
        }
    }
};
void ugearshandlersmess_MakeSentryShot(PGear Sentry)
{
    PGear bullet;
    hwFloat distX;
    hwFloat distY;
    hwFloat invDistance;
    distX = ufloat_hwFloat_hwFloat_op_sub(ufloat_int2hwFloat(Sentry->Target.x), Sentry->X);
    distY = ufloat_hwFloat_hwFloat_op_sub(ufloat_int2hwFloat(Sentry->Target.y), Sentry->Y);
    invDistance = ufloat_hwFloat_hwFloat_op_div(_1, ufloat_Distance(distX, distY));
    distX = ufloat_hwFloat_hwFloat_op_mul(distX, invDistance);
    distY = ufloat_hwFloat_hwFloat_op_mul(distY, invDistance);
    bullet = ugearslist_AddGear_7(ufloat_hwRound(Sentry->X), ufloat_hwRound(Sentry->Y), gtMinigunBullet, 0, ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_mul(distX, _0_9), urandom_rndSign(ufloat_hwFloat_hwFloat_op_mul(urandom_GetRandomf(), _0_1))), ufloat_hwFloat_hwFloat_op_add(ufloat_hwFloat_hwFloat_op_mul(distY, _0_9), urandom_rndSign(ufloat_hwFloat_hwFloat_op_mul(urandom_GetRandomf(), _0_1))), 0);
    bullet->Karma = 12;
    bullet->Pos = 1;
    bullet->WDTimer = GameTicks;
    bullet->PortalCounter = 1;
    bullet->Elasticity = Sentry->X;
    bullet->Friction = Sentry->Y;
    bullet->Data = ((pointer)Sentry);
    bullet->Hedgehog = Sentry->Hedgehog;
    ugearshandlersmess_CreateShellForGear(Sentry, Sentry->WDTimer & 1);
    usound_PlaySound_1(sndGun);
};
PGear ugearshandlersmess_GetSentryTarget(PGear sentry)
{
    PGear getsentrytarget_result;
    PGear HHGear;
    boolean friendlyTarget;
    getsentrytarget_result = NULL;
    friendlyTarget = false;
    if(CurrentHedgehog != NULL)
    {
        HHGear = CurrentHedgehog->Gear;
        if(HHGear != NULL)
        {
            if(((HHGear->State & gstHHDriven) != 0) && (HHGear->CollisionIndex < 0))
            {
                if(sentry->Hedgehog != NULL)
                {
                    friendlyTarget = (*(*sentry->Hedgehog).Team).Clan == (*CurrentHedgehog->Team).Clan;
                }
                if(!friendlyTarget)
                {
                    getsentrytarget_result = HHGear;
                }
            }
        }
    }
    return getsentrytarget_result;
};
void ugearshandlersmess_doStepSentryLand(PGear Gear)
{
    PGear HHGear;
    Word land;
    enum{sentry_Idle = 0};
    enum{sentry_Walking = 1};
    enum{sentry_Aiming = 2};
    enum{sentry_Attacking = 3};
    enum{sentry_Reloading = 4};
    HHGear = NULL;
    if(ugearsutils_CheckGearDrowning(&(Gear)))
    {
        return;
    }
    if(ugearshandlersmess_CheckSentryDestroyed(Gear, sentry_Reloading))
    {
        return;
    }
    land = ucollisions_TestCollisionYwithGear(Gear, 1);
    if((Gear->dY.isNegative || (land == 0)) || ((Gear->dY.QWordValue > _0_01.QWordValue) && ((Gear->State & gstHHJumping) == 0)))
    {
        ucollisions_DeleteCI(Gear);
        ugearshandlersmess_doStepFallingGear(Gear);
        if(!(((Gear->Tag == sentry_Idle) || (Gear->Tag == sentry_Reloading))))
        {
            ugearshandlersmess_ResetSentryState(Gear, sentry_Idle, 1000);
        }
        return;
    }
    else
    {
        ucollisions_AddCI(Gear);
        Gear->State = Gear->State & ~gstHHJumping;
        Gear->dX = ufloat_SignAs(_0, Gear->dX);
        Gear->dY = ufloat_SignAs(_0, Gear->dY);
    }
    if(Gear->Timer > 0)
    {
        --Gear->Timer;
    }
    if(Gear->Timer == 0)
    {
        ucollisions_DeleteCI(Gear);
        if(Gear->Tag == sentry_Idle)
        {
            Gear->Tag = sentry_Walking;
            Gear->Timer = 1000 + urandom_GetRandom(3000);
            if(urandom_GetRandom(4) == 0)
            {
                if(ugearshandlersmess_MakeSentryJump(Gear, 80, 60))
                {
                    Gear->Timer = 4000;
                }
                else
                {
                    Gear->Timer = 1000;
                }
                Gear->Tag = sentry_Idle;
            }
            else
            {
                Gear->dX.isNegative = urandom_GetRandom(2) == 1;
                if(ugearshandlersmess_MakeSentryStep(Gear, 6, true))
                {
                    if(urandom_GetRandom(4) == 0)
                    {
                        Gear->Timer = 2000;
                        Gear->Tag = sentry_Idle;
                    }
                }
                else
                {
                    Gear->dX.isNegative = !Gear->dX.isNegative;
                    if(!ugearshandlersmess_MakeSentryStep(Gear, 6, true))
                    {
                        if(urandom_GetRandom(2) == 0)
                        {
                            Gear->dY = ufloat_hwFloat_op_sub(_0_1);
                            if(ucollisions_TestCollisionYKick(Gear, -1) == 0)
                            {
                                Gear->dY = ufloat_hwFloat_op_sub(_0_25);
                            }
                            Gear->Timer = 3000;
                        }
                        else
                        {
                            Gear->Timer = 5000;
                        }
                        Gear->Tag = sentry_Idle;
                    }
                }
            }
        }
        else
        {
            if(((Gear->Tag == sentry_Walking) || (Gear->Tag == sentry_Reloading)))
            {
                Gear->Tag = sentry_Idle;
                Gear->Timer = 1000 + urandom_GetRandom(1000);
            }
            else
            {
                if(Gear->Tag == sentry_Aiming)
                {
                    if(ugearshandlersmess_CheckSentryAttackRange(Gear, ufloat_int2hwFloat(Gear->Target.x), ufloat_int2hwFloat(Gear->Target.y)))
                    {
                        Gear->WDTimer = 5 + urandom_GetRandom(3);
                        Gear->Tag = sentry_Attacking;
                        Gear->Timer = 100;
                    }
                    else
                    {
                        Gear->Target.x = 0;
                        Gear->Target.y = 0;
                        Gear->Tag = sentry_Idle;
                        Gear->Timer = 5000;
                    }
                }
                else
                {
                    if(Gear->Tag == sentry_Attacking)
                    {
                        ugearshandlersmess_MakeSentryShot(Gear);
                        if(Gear->WDTimer == 0)
                        {
                            ugearshandlersmess_ResetSentryState(Gear, sentry_Reloading, 6000 + urandom_GetRandom(2000));
                        }
                        else
                        {
                            --Gear->WDTimer;
                            Gear->Timer = 100;
                        }
                    }
                }
            }
        }
        ucollisions_AddCI(Gear);
    }
    if((Gear->Tag == sentry_Walking) && ((GameTicks & 0x1f) == 0))
    {
        ucollisions_DeleteCI(Gear);
        if(!ugearshandlersmess_MakeSentryStep(Gear, 6, false))
        {
            Gear->Timer = 0;
        }
        ucollisions_AddCI(Gear);
    }
    if(((GameTicks & 0x1f) == 0) && (Gear->Tag == sentry_Aiming))
    {
        ugearshandlersmess_AimSentry(Gear);
    }
    if(((GameTicks & 0xff) == 0) && (((Gear->Tag == sentry_Idle) || (Gear->Tag == sentry_Walking))))
    {
        HHGear = ugearshandlersmess_GetSentryTarget(Gear);
        if(HHGear != NULL)
        {
            if(ugearshandlersmess_CheckSentryAttackRange(Gear, HHGear->X, HHGear->Y))
            {
                Gear->Target.x = ufloat_hwRound(HHGear->X);
                Gear->Target.y = ufloat_hwRound(HHGear->Y);
                Gear->Karma = GameTicks;
                Gear->Tag = sentry_Aiming;
                Gear->Timer = 1800 + urandom_GetRandom(400);
            }
        }
    }
};
void ugearshandlersmess_doStepSentryWater(PGear Gear)
{
    PGear HHGear;
    enum{sentry_Idle = 0};
    enum{sentry_Walking = 1};
    enum{sentry_Aiming = 2};
    enum{sentry_Attacking = 3};
    enum{sentry_Reloading = 4};
    if(Gear->Tag < 0)
    {
        ugearsutils_CheckGearDrowning(&(Gear));
        return;
    }
    Gear->Y = ufloat_int2hwFloat(cWaterLine - (3 * Gear->Radius));
    if(ucollisions_TestCollisionYImpl(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), Gear->Radius - 1, -1, Gear->CollisionMask & lfLandMask) != 0)
    {
        Gear->Tag = -1;
        return;
    }
    if(ugearshandlersmess_CheckSentryDestroyed(Gear, sentry_Reloading))
    {
        return;
    }
    if(Gear->Timer > 0)
    {
        --Gear->Timer;
    }
    if(Gear->Timer == 0)
    {
        if(Gear->Tag == sentry_Idle)
        {
            Gear->Tag = sentry_Walking;
            Gear->Timer = 3000 + urandom_GetRandom(3000);
            Gear->dX.isNegative = urandom_GetRandom(2) == 1;
            if(ucollisions_TestCollisionXwithGear(Gear, ufloat_hwSign(Gear->dX)) != 0)
            {
                Gear->dX.isNegative = !Gear->dX.isNegative;
            }
        }
        else
        {
            if(((Gear->Tag == sentry_Walking) || (Gear->Tag == sentry_Reloading)))
            {
                Gear->Tag = sentry_Idle;
                Gear->Timer = 1000 + urandom_GetRandom(1000);
            }
            else
            {
                if(Gear->Tag == sentry_Aiming)
                {
                    if(ugearshandlersmess_CheckSentryAttackRange(Gear, ufloat_int2hwFloat(Gear->Target.x), ufloat_int2hwFloat(Gear->Target.y)))
                    {
                        Gear->WDTimer = 5 + urandom_GetRandom(3);
                        Gear->Tag = sentry_Attacking;
                        Gear->Timer = 100;
                    }
                    else
                    {
                        Gear->Target.x = 0;
                        Gear->Target.y = 0;
                        Gear->Tag = sentry_Idle;
                        Gear->Timer = 5000;
                    }
                }
                else
                {
                    if(Gear->Tag == sentry_Attacking)
                    {
                        ugearshandlersmess_MakeSentryShot(Gear);
                        if(Gear->WDTimer == 0)
                        {
                            ugearshandlersmess_ResetSentryState(Gear, sentry_Reloading, 6000 + urandom_GetRandom(2000));
                        }
                        else
                        {
                            --Gear->WDTimer;
                            Gear->Timer = 100;
                        }
                    }
                }
            }
        }
    }
    if((Gear->Tag == sentry_Walking) && ((GameTicks & 0x1f) == 0))
    {
        if(ucollisions_TestCollisionXwithGear(Gear, ufloat_hwSign(Gear->dX)) == 0)
        {
            Gear->dX = ufloat_SignAs(_1, Gear->dX);
            Gear->X = ufloat_hwFloat_hwFloat_op_add(Gear->X, Gear->dX);
            ugearsutils_WorldWrap(&(Gear));
        }
        else
        {
            Gear->Timer = 0;
        }
    }
    if(((GameTicks & 0x1f) == 0) && (Gear->Tag == sentry_Aiming))
    {
        ugearshandlersmess_AimSentry(Gear);
    }
    if(((GameTicks & 0xff) == 0) && (((Gear->Tag == sentry_Idle) || (Gear->Tag == sentry_Walking))))
    {
        HHGear = ugearshandlersmess_GetSentryTarget(Gear);
        if(HHGear != NULL)
        {
            if(ugearshandlersmess_CheckSentryAttackRange(Gear, HHGear->X, HHGear->Y))
            {
                Gear->Target.x = ufloat_hwRound(HHGear->X);
                Gear->Target.y = ufloat_hwRound(HHGear->Y);
                Gear->Karma = GameTicks;
                Gear->Tag = sentry_Aiming;
                Gear->Timer = 1800 + urandom_GetRandom(400);
            }
        }
    }
};
void ugearshandlersmess_doStepSentryDeploy(PGear Gear)
{
    Gear->Tag = -1;
    if((ufloat_hwRound(Gear->Y) + (3 * Gear->Radius)) >= cWaterLine)
    {
        Gear->Y = ufloat_int2hwFloat(cWaterLine - (3 * Gear->Radius));
        if(Gear->Timer > 0)
        {
            --Gear->Timer;
        }
        if(Gear->Timer == 0)
        {
            Gear->Tag = 0;
            Gear->doStep = &(ugearshandlersmess_doStepSentryWater);
        }
    }
    else
    {
        if(Gear->dY.isNegative || (ucollisions_TestCollisionYwithGear(Gear, 1) == 0))
        {
            ugearshandlersmess_doStepFallingGear(Gear);
        }
        else
        {
            if(Gear->Timer > 0)
            {
                --Gear->Timer;
            }
            if(Gear->Timer == 0)
            {
                Gear->Tag = 0;
                Gear->doStep = &(ugearshandlersmess_doStepSentryLand);
            }
        }
    }
};
