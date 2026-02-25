#include "fpcrtl.h"

#include "uGearsRender.h"
RopePoints_tt RopePoints;
#include "uRender.h"
#include "uRenderUtils.h"
#include "uGearsUtils.h"
#include "uUtils.h"
#include "uVariables.h"
#include "uAmmos.h"
#include "Math.h"
#include "uVisualGearsList.h"
#include "uLandUtils.h"
static const string255 __str1 = STRINIT("NoHat");
static const string255 __str0 = STRINIT("en");
void ugearsrender_DrawRopeLinesRQ(PGear Gear)
{
    LongInt n;
    {
        RopePoints.rounded[RopePoints.Count].X = ufloat_hwRound(Gear->X);
        RopePoints.rounded[RopePoints.Count].Y = ufloat_hwRound(Gear->Y);
        RopePoints.rounded[RopePoints.Count + 1].X = ufloat_hwRound((*(*Gear->Hedgehog).Gear).X);
        RopePoints.rounded[RopePoints.Count + 1].Y = ufloat_hwRound((*(*Gear->Hedgehog).Gear).Y);
    }
    if((RopePoints.Count > 0) || (Gear->Elasticity.QWordValue > 0))
    {
        urender_EnableTexture(false);
        urender_Tint_4((Gear->Tint >> 24) / 3, ((Gear->Tint >> 16) & 0xff) / 3, ((Gear->Tint >> 8) & 0xff) / 3, Gear->Tint & 0xff);
        n = RopePoints.Count + 2;
        urender_SetVertexPointer(&(RopePoints.rounded[0]), n);
        urender_openglPushMatrix();
        urender_openglTranslatef(WorldDx, WorldDy, 0);
        glLineWidth(3.0 * cScaleFactor);
        glDrawArrays(GL_LINE_STRIP, 0, n);
        urender_Tint_1(Gear->Tint);
        glLineWidth(2.0 * cScaleFactor);
        glDrawArrays(GL_LINE_STRIP, 0, n);
        urender_untint();
        urender_openglPopMatrix();
        urender_EnableTexture(true);
    }
};
void ugearsrender_DrawRopeLine(real X1,real Y1,real X2,real Y2,LongWord LayerIndex,real (*linesLength),real (*ropeLength))
{
    real dX;
    real dY;
    real angle;
    real lineLength;
    LongWord FrameIndex;
    if((X1 == X2) && (Y1 == Y2))
    {
        return;
    }
    dX = X2 - X1;
    dY = Y2 - Y1;
    lineLength = sqrt(fpcrtl_sqr(dX) + fpcrtl_sqr(dY));
    angle = ((fpcrtl_arctan2(dY, dX) * 180) /(float) pi) - 90;
    dX = dX /(float) lineLength;
    dY = dY /(float) lineLength;
    while(((*ropeLength) - (*linesLength)) <= lineLength)
    {
        FrameIndex = fpcrtl_round((*ropeLength) /(float) cRopeNodeStep);
        if((FrameIndex % cRopeLayers) == LayerIndex)
        {
            urender_DrawSpriteRotatedFReal(sprRopeNode, X1 + (((*ropeLength) - (*linesLength)) * dX), Y1 + (((*ropeLength) - (*linesLength)) * dY), FrameIndex, 1, angle);
        }
        (*ropeLength) = (*ropeLength) + cRopeNodeStep;
    }
    (*linesLength) = (*linesLength) + lineLength;
};
void ugearsrender_DrawRopeLayer(PGear Gear,LongWord LayerIndex)
{
    LongInt i;
    real linesLength;
    real ropeLength;
    linesLength = 0;
    ropeLength = cRopeNodeStep;
    if(RopePoints.Count > 0)
    {
        i = 0;
        while(i < ((int)(RopePoints.Count) - 1))
        {
            ugearsrender_DrawRopeLine(ufloat_hwFloat2Float(RopePoints.ar[i].X) + WorldDx, ufloat_hwFloat2Float(RopePoints.ar[i].Y) + WorldDy, ufloat_hwFloat2Float(RopePoints.ar[(i + 1)].X) + WorldDx, ufloat_hwFloat2Float(RopePoints.ar[(i + 1)].Y) + WorldDy, LayerIndex, &(linesLength), &(ropeLength));
            ++i;
        }
        ugearsrender_DrawRopeLine(ufloat_hwFloat2Float(RopePoints.ar[i].X) + WorldDx, ufloat_hwFloat2Float(RopePoints.ar[i].Y) + WorldDy, ufloat_hwFloat2Float(Gear->X) + WorldDx, ufloat_hwFloat2Float(Gear->Y) + WorldDy, LayerIndex, &(linesLength), &(ropeLength));
        ugearsrender_DrawRopeLine(ufloat_hwFloat2Float(Gear->X) + WorldDx, ufloat_hwFloat2Float(Gear->Y) + WorldDy, ufloat_hwFloat2Float((*(*Gear->Hedgehog).Gear).X) + WorldDx, ufloat_hwFloat2Float((*(*Gear->Hedgehog).Gear).Y) + WorldDy, LayerIndex, &(linesLength), &(ropeLength));
    }
    else
    {
        if(Gear->Elasticity.QWordValue > 0)
        {
            ugearsrender_DrawRopeLine(ufloat_hwFloat2Float(Gear->X) + WorldDx, ufloat_hwFloat2Float(Gear->Y) + WorldDy, ufloat_hwFloat2Float((*(*Gear->Hedgehog).Gear).X) + WorldDx, ufloat_hwFloat2Float((*(*Gear->Hedgehog).Gear).Y) + WorldDy, LayerIndex, &(linesLength), &(ropeLength));
        }
    }
};
void ugearsrender_DrawRope(PGear Gear)
{
    LongInt i;
    if((*Gear->Hedgehog).Gear == NULL)
    {
        return;
    }
    if((Gear->Tag == 1) || ((cReducedQuality & rqSimpleRope) != 0))
    {
        ugearsrender_DrawRopeLinesRQ(Gear);
    }
    else
    {
        {i = 0;
         LongInt i__end__ = cRopeLayers - 1;
         if (i <= i__end__) do {
                                   ugearsrender_DrawRopeLayer(Gear, i);
                               } while(i++ != i__end__);}
    }
    if(RopePoints.Count > 0)
    {
        urender_DrawSpriteRotated(sprRopeHook, ufloat_hwRound(RopePoints.ar[0].X) + WorldDx, ufloat_hwRound(RopePoints.ar[0].Y) + WorldDy, 1, RopePoints.HookAngle);
    }
    else
    {
        if(Gear->Elasticity.QWordValue > 0)
        {
            urender_DrawSpriteRotated(sprRopeHook, ufloat_hwRound(Gear->X) + WorldDx, ufloat_hwRound(Gear->Y) + WorldDy, 0, uutils_DxDy2Angle(Gear->dY, Gear->dX));
        }
    }
};
void ugearsrender_DrawSelectedWeapon(PGear Gear,LongInt sx,LongInt sy,boolean isAltWeapon)
{
    {
        if(((*Gear->Hedgehog).Gear->State & gstAttacked) != 0)
        {
            return;
        }
        if(isAltWeapon && ((Ammoz[(*Gear->Hedgehog).CurAmmoType].Ammo.Propz & ammoprop_AltUse) == 0))
        {
            return;
        }
        if(!isAltWeapon && (((Ammoz[(*Gear->Hedgehog).CurAmmoType].Ammo.Propz & ammoprop_ShowSelIcon) == 0) || (((Ammoz[(*Gear->Hedgehog).CurAmmoType].Ammo.Propz & ammoprop_AttackInMove) == 0) && (((*Gear->Hedgehog).Gear->State & gstMoving) != 0))))
        {
            return;
        }
        if(!isAltWeapon)
        {
            sy = sy - 64;
            if(ugearsutils_IsHogFacingLeft((*Gear->Hedgehog).Gear))
            {
                sx = sx - 61;
            }
        }
        urender_DrawTexture_3(sx + 16, sy + 16, ropeIconTex);
        urender_DrawTextureF(SpritesData[sprAMAmmos].Texture, 0.75, sx + 30, sy + 30, ((*Gear->Hedgehog).CurAmmoType) - 1, 1, 32, 32);
    }
};
void ugearsrender_DrawHHOrder()
{
    PGear HHGear;
    PHedgehog hh;
    LongInt c;
    LongInt i;
    LongInt t;
    LongInt x;
    LongInt y;
    LongInt sprH;
    LongInt sprW;
    LongInt fSprOff;
    t = LocalTeam;
    if(!CurrentTeam->ExtDriven)
    {
        {i = 0;
         LongInt i__end__ = ((int)(TeamsCount) - 1);
         if (i <= i__end__) do {
                                   if(TeamsArray[i] == CurrentTeam)
                                   {
                                       t = i;
                                   }
                               } while(i++ != i__end__);}
    }
    if(t < 0)
    {
        return;
    }
    if(TeamsArray[t] != NULL)
    {
        sprH = SpritesData[sprBigDigit].Height;
        sprW = SpritesData[sprBigDigit].Width;
        fSprOff = ((sprW / 4) + (SpritesData[sprFrame].Width / 4)) - 1;
        i = 0;
        c = 0;
        do {
               hh = &(TeamsArray[t]->Hedgehogs[i]);
               ++i;
               if(((hh != NULL) && (hh->Gear != NULL)) && !hh->Unplaced)
               {
                   ++c;
                   HHGear = hh->Gear;
                   x = ufloat_hwRound(HHGear->X) + WorldDx;
                   y = (ufloat_hwRound(HHGear->Y) + WorldDy) - 2;
                   urender_DrawTextureF(SpritesData[sprFrame].Texture, 0.5, x - fSprOff, y, 0, 1, SpritesData[sprFrame].Width, SpritesData[sprFrame].Height);
                   urender_DrawTextureF(SpritesData[sprFrame].Texture, 0.5, x + fSprOff, y, 1, 1, SpritesData[sprFrame].Width, SpritesData[sprFrame].Height);
                   urender_DrawTextureF(SpritesData[sprBigDigit].Texture, 0.5, x, y, c, 1, sprW, sprH);
                   if(SpeechHogNumber == c)
                   {
                       urender_DrawCircle_8(x, y, 20, 3, 0, 0xff, 0xff, 0x80);
                   }
               }
           } while(!(i > cMaxHHIndex));
    }
};
void ugearsrender_RenderFinger(PGear Gear,LongInt ox,LongInt oy)
{
    PHedgehog HH;
    LongInt tx;
    LongInt ty;
    LongInt t;
    real dAngle;
    HH = Gear->Hedgehog;
    if(HH->Unplaced)
    {
        return;
    }
    if((Gear->State & gstHHDeath) != 0)
    {
        return;
    }
    if((Gear->State & gstHHGone) != 0)
    {
        return;
    }
    if(CinematicScript)
    {
        return;
    }
    if(bShowFinger && ((Gear->State & gstHHDriven) != 0))
    {
        ty = oy - 32;
        if((cTagsMask & htTeamName) != 0)
        {
            ty = (ty - (*(*HH->Team).NameTagTex).h) - 2;
        }
        if((cTagsMask & htName) != 0)
        {
            ty = (ty - (*HH->NameTagTex).h) - 2;
        }
        if((cTagsMask & htHealth) != 0)
        {
            ty = (ty - (*HH->HealthTagTex).h) - 2;
        }
        if(bShowSwitcher)
        {
            ty = (ty - SpritesData[sprSwitch].Height) - 4;
        }
        tx = ox;
        t = 32;
        tx = uutils_Min(uutils_Max(tx, ViewLeftX + t), ViewRightX - t);
        ty = uutils_Min(ty, ViewBottomY - 96);
        if(ty < (ViewTopY + t))
        {
            if(fpcrtl_abs(tx - ox) < fpcrtl_abs(ty - oy))
            {
                ty = uutils_Max(ViewTopY + t, oy + t);
            }
            else
            {
                ty = uutils_Max(ViewTopY + t, ty);
            }
        }
        dAngle = uutils_DxDy2Angle(ufloat_int2hwFloat(ty - oy), ufloat_int2hwFloat(tx - ox)) + 90;
        if(urenderutils_IsTooDarkToRead((*(*HH->Team).Clan).Color))
        {
            urender_DrawSpriteRotatedF(sprFingerBackInv, tx, ty, (RealTicks / 32) % 16, 1, dAngle);
        }
        else
        {
            urender_DrawSpriteRotatedF(sprFingerBack, tx, ty, (RealTicks / 32) % 16, 1, dAngle);
        }
        urender_Tint_1(((*(*HH->Team).Clan).Color << 8) | 0xff);
        urender_DrawSpriteRotatedF(sprFinger, tx, ty, (RealTicks / 32) % 16, 1, dAngle);
        urender_untint();
    }
};
void ugearsrender_RenderHHGuiExtras(PGear Gear,LongInt ox,LongInt oy)
{
    PHedgehog HH;
    LongInt sx;
    LongInt sy;
    LongInt hogLR;
    HH = Gear->Hedgehog;
    sx = ox + 1;
    sy = oy - 3;
    if(HH->Unplaced)
    {
        return;
    }
    if((Gear->State & gstHHDeath) != 0)
    {
        return;
    }
    if((Gear->State & gstHHGone) != 0)
    {
        return;
    }
    if(CinematicScript)
    {
        return;
    }
    if((CrosshairGear != NULL) && (Gear == CrosshairGear))
    {
        hogLR = 1;
        if(ugearsutils_IsHogFacingLeft(Gear))
        {
            hogLR = -1;
        }
        urender_setTintAdd(true);
        urender_Tint_1(((*(*HH->Team).Clan).Color << 8) | 0xff);
        urender_DrawTextureRotated(CrosshairTexture, 12, 12, CrosshairX + WorldDx, CrosshairY + WorldDy, 0, (hogLR * (Gear->Angle * 180.0)) /(float) cMaxAngle);
        urender_untint();
        urender_setTintAdd(false);
    }
    if(((Gear->State & gstHHDriven) != 0) && (CurAmmoGear != NULL))
    {
        switch(CurAmmoGear->Kind)
        {case gtJetpack:{
                            if(((!SuddenDeathDmg && (WaterOpacity > cGearContourThreshold)) || (SuddenDeathDmg && (SDWaterOpacity > cGearContourThreshold))) && ((cWaterLine < ((ufloat_hwRound(Gear->Y) + Gear->Radius) - 16)) || ((WorldEdge == weSea) && ((ufloat_hwRound(Gear->X) < leftX) || (ufloat_hwRound(Gear->X) > rightX)))))
                            {
                                urender_DrawSprite_4(sprJetpack, sx - 32, sy - 32, 4);
                            }
                            if(CurAmmoGear->Tex != NULL)
                            {
                                urender_DrawTextureCentered(sx, sy - 40, CurAmmoGear->Tex);
                            }
                            ugearsrender_DrawSelectedWeapon(Gear, sx, sy, true);
                        }
                        break;
         case gtRope:ugearsrender_DrawSelectedWeapon(Gear, sx, sy, true);
                     break;
         case gtParachute:ugearsrender_DrawSelectedWeapon(Gear, sx, sy, true);
                          break;
         case gtLandGun:if(CurAmmoGear->Tex != NULL)
                        {
                            urender_DrawTextureCentered(sx, sy - 40, CurAmmoGear->Tex);
                        }
                        break;
         case gtFlamethrower:if(CurAmmoGear->Tex != NULL)
                             {
                                 urender_DrawTextureCentered(sx, sy - 40, CurAmmoGear->Tex);
                             }
                             break;
         case gtIceGun:if(CurAmmoGear->Tex != NULL)
                       {
                           urender_DrawTextureCentered(sx, sy - 40, CurAmmoGear->Tex);
                       }
                       break;
         default: break;}
    }
    else
    {
        if((Gear->State & gstHHDriven) != 0)
        {
            ugearsrender_DrawSelectedWeapon(Gear, sx, sy, false);
        }
    }
};
void ugearsrender_RenderAirMineGuiExtras(PGear Gear,LongInt ox,LongInt oy)
{
    boolean tinted;
    if(((!SuddenDeathDmg && (WaterOpacity > cGearContourThreshold)) || (SuddenDeathDmg && (SDWaterOpacity > cGearContourThreshold))) && ((cWaterLine < ((ufloat_hwRound(Gear->Y) + Gear->Radius) + 16)) || ((WorldEdge == weSea) && ((ufloat_hwRound(Gear->X) < (leftX + 24)) || (ufloat_hwRound(Gear->X) > (rightX - 24))))))
    {
        tinted = true;
        if((((Gear->State & gstFrozen) != 0) || ((Gear->State & gsttmpFlag) == 0)) || (Gear->Tag != 0))
        {
            urender_Tint_4(0xff, 0xff, 0xff, 0x80);
        }
        else
        {
            if((Gear->Hedgehog != NULL) && ((*Gear->Hedgehog).Gear != NULL))
            {
                urender_Tint_4(0xff, 0x30, 0x30, 0xff);
            }
            else
            {
                if((Gear->State & gstChooseTarget) == 0)
                {
                    urender_Tint_4(0xff, 0xff, 0xff, 0x80);
                }
                else
                {
                    tinted = false;
                }
            }
        }
        urender_DrawSprite_4(sprAirMine, ox - 16, oy - 16, 32);
        if(tinted)
        {
            urender_untint();
        }
    }
};
void ugearsrender_DrawHH(PGear Gear,LongInt ox,LongInt oy)
{
    LongInt i;
    LongInt t;
    TAmmoType amt;
    LongInt sign;
    LongInt hx;
    LongInt hy;
    LongInt tx;
    LongInt ty;
    LongInt sx;
    LongInt sy;
    LongInt hogLR;
    real dx;
    real dy;
    real ax;
    real ay;
    real aAngle;
    real dAngle;
    real hAngle;
    real lx;
    real ly;
    LongWord wraps;
    boolean defaultPos;
    boolean HatVisible;
    boolean inWorldBounds;
    PHedgehog HH;
    PAmmo CurWeapon;
    LongInt iceOffset;
    TSDL_Rect r;
    PTexture curhat;
    HH = Gear->Hedgehog;
    CrosshairGear = NULL;
    if(HH->Unplaced)
    {
        return;
    }
    if((HH->CurAmmoType == amKnife) && (HH == CurrentHedgehog))
    {
        curhat = ChefHatTexture;
    }
    else
    {
        curhat = HH->HatTex;
    }
    sx = ox + 1;
    sy = oy - 3;
    sign = ufloat_hwSign(Gear->dX);
    if(ugearsutils_IsHogFacingLeft(Gear))
    {
        hogLR = -1;
    }
    else
    {
        hogLR = 1;
    }
    if((Gear->State & gstHHDeath) != 0)
    {
        urender_DrawSprite_4(sprHHDeath, ox - 16, oy - 26, Gear->Pos);
        urender_Tint_1(((*(*HH->Team).Clan).Color << 8) | 0xff);
        urender_DrawSprite_4(sprHHDeath, ox - 16, oy - 26, Gear->Pos + 8);
        urender_untint();
        return;
    }
    else
    {
        if((Gear->State & gstHHGone) != 0)
        {
            urender_DrawSpriteRotatedF(sprTeleport, sx, sy, Gear->Pos, sign, 0);
            return;
        }
    }
    defaultPos = true;
    HatVisible = false;
    if(HH->Effects[heFrozen] > 0)
    {
        if(HH->Effects[heFrozen] < 150000)
        {
            urender_DrawHedgehog(sx, sy, sign, 0, 0, 0);
            defaultPos = false;
            if(HH->Effects[heFrozen] < 256)
            {
                HatVisible = true;
            }
            else
            {
                HatVisible = false;
            }
        }
        else
        {
            urender_DrawHedgehog(sx, sy, sign, 2, 4, 0);
            defaultPos = false;
            HatVisible = false;
        }
    }
    if(HH->Effects[hePoisoned] != 0)
    {
        urender_Tint_4(0x00, 0xff, 0x40, 0x40);
        urender_DrawTextureRotatedF(SpritesData[sprSmokeWhite].Texture, 2, 0, 0, sx, sy, 0, 1, 22, 22, (RealTicks >> 4) % 360);
        urender_untint();
    }
    if(((Gear->State & gstWinner) != 0) && ((CurAmmoGear == NULL) || (CurAmmoGear->Kind != gtPickHammer)))
    {
        urender_DrawHedgehog(sx, sy, sign, 2, 0, 0);
        defaultPos = false;
    }
    if((Gear->State & gstDrowning) != 0)
    {
        urender_DrawHedgehog(sx, sy, sign, 1, 7, 0);
        defaultPos = false;
    }
    else
    {
        if((Gear->State & gstLoser) != 0)
        {
            urender_DrawHedgehog(sx, sy, sign, 2, 3, 0);
            defaultPos = false;
        }
        else
        {
            if((Gear->State & gstHHDriven) != 0)
            {
                if(((Gear->State & (gstHHThinking | gstAnimation)) == 0) && ((((CurAmmoGear != NULL) && ((CurAmmoGear->AmmoType != amKamikaze) || ((Gear->State & gstAttacking) == 0))) && ((Ammoz[CurAmmoGear->AmmoType].Ammo.Propz & ammoprop_NoCrosshair) == 0)) || (((CurAmmoGear == NULL) && ((Ammoz[HH->CurAmmoType].Ammo.Propz & ammoprop_NoCrosshair) == 0)) && ((Gear->State & gstAttacked) == 0))))
                {
                    dx = hogLR * sin((Gear->Angle * pi) /(float) cMaxAngle);
                    dy = -cos((Gear->Angle * pi) /(float) cMaxAngle);
                    if(cLaserSighting || cLaserSightingSniper)
                    {
                        lx = uutils_GetLaunchX(HH->CurAmmoType, hogLR, Gear->Angle);
                        ly = uutils_GetLaunchY(HH->CurAmmoType, Gear->Angle);
                        while(fpcrtl_abs((lx * lx) + (ly * ly)) < (Gear->Radius * Gear->Radius))
                        {
                            lx = lx + dx;
                            ly = ly + dy;
                        }
                        lx = (lx + ox) - WorldDx;
                        ly = (ly + oy) - WorldDy;
                        ax = dx * 4;
                        ay = dy * 4;
                        tx = fpcrtl_round(lx);
                        ty = fpcrtl_round(ly);
                        hx = tx;
                        hy = ty;
                        wraps = 0;
                        inWorldBounds = ((ty & LAND_HEIGHT_MASK) | (tx & LAND_WIDTH_MASK)) == 0;
                        while((inWorldBounds && ((ulandutils_LandGet(ty, tx) & lfAll) == 0)) || !inWorldBounds)
                        {
                            if(wraps > cMaxLaserSightWraps)
                            {
                                break;
                            }
                            lx = lx + ax;
                            ly = ly + ay;
                            tx = fpcrtl_round(lx);
                            ty = fpcrtl_round(ly);
                            if((((WorldEdge != weBounce) && (WorldEdge != weWrap)) && ((ty & LAND_HEIGHT_MASK) != 0)) && (((ty < LAND_HEIGHT) && (ay < 0)) || ((ty >= topY) && (ay > 0))))
                            {
                                tx = fpcrtl_round(lx + (ax * (uutils_Max(LAND_WIDTH, 4096) / 2)));
                                ty = fpcrtl_round(ly + (ay * (uutils_Max(LAND_WIDTH, 4096) / 2)));
                                break;
                            }
                            if(((WorldEdge == weWrap) || (WorldEdge == weBounce)) && ((ty < -cCamLimitY) || (ty >= (topY + cCamLimitY))))
                            {
                                break;
                            }
                            if(((hogLR < 0) && (tx < leftX)) || ((hogLR > 0) && (tx >= rightX)))
                            {
                                if(WorldEdge == weWrap)
                                {
                                    if(hogLR < 0)
                                    {
                                        lx = rightX - (ax - (lx - leftX));
                                    }
                                    else
                                    {
                                        lx = leftX + (-ax - (rightX - lx));
                                    }
                                    tx = fpcrtl_round(lx);
                                    ++wraps;
                                }
                                else
                                {
                                    if(WorldEdge == weBounce)
                                    {
                                        break;
                                    }
                                }
                            }
                            if(((((tx & LAND_WIDTH_MASK) != 0) && (((ax > 0) && (tx >= rightX)) || ((ax < 0) && (tx <= leftX)))) && (WorldEdge != weWrap)) && (WorldEdge != weBounce))
                            {
                                tx = fpcrtl_round(lx + (ax * (uutils_Max(LAND_WIDTH, 4096) / 2)));
                                ty = fpcrtl_round(ly + (ay * (uutils_Max(LAND_WIDTH, 4096) / 2)));
                                break;
                            }
                            inWorldBounds = ((ty & LAND_HEIGHT_MASK) | (tx & LAND_WIDTH_MASK)) == 0;
                        }
                        urender_DrawLineWrapped_11(hx, hy, tx, ty, 1.0, hogLR < 0, wraps, 0xff, 0x00, 0x00, 0xc0);
                    }
                    CrosshairX = fpcrtl_round((ufloat_hwRound(Gear->X) + (dx * 80)) + uutils_GetLaunchX(HH->CurAmmoType, hogLR, Gear->Angle));
                    CrosshairY = fpcrtl_round((ufloat_hwRound(Gear->Y) + (dy * 80)) + uutils_GetLaunchY(HH->CurAmmoType, Gear->Angle));
                    CrosshairGear = Gear;
                }
                hx = ox + (8 * sign);
                hy = oy - 2;
                aAngle = ((Gear->Angle * 180) /(float) cMaxAngle) - 90;
                if((CurAmmoGear != NULL) && (CurAmmoGear->Kind != gtTardis))
                {
                    switch(CurAmmoGear->Kind)
                    {case gtShotgunShot:{
                                            if((CurAmmoGear->State & gstAnimation) != 0)
                                            {
                                                urender_DrawSpriteRotated(sprShotgun, hx, hy, sign, aAngle);
                                            }
                                            else
                                            {
                                                urender_DrawSpriteRotated(sprHandShotgun, hx, hy, sign, aAngle);
                                            }
                                        }
                                        break;
                     case gtDEagleShot:urender_DrawSpriteRotated(sprDEagle, hx, hy, sign, aAngle);
                                       break;
                     case gtSniperRifleShot:{
                                                if((CurAmmoGear->State & gstAnimation) != 0)
                                                {
                                                    urender_DrawSpriteRotatedF(sprSniperRifle, hx, hy, 1, sign, aAngle);
                                                }
                                                else
                                                {
                                                    urender_DrawSpriteRotatedF(sprSniperRifle, hx, hy, 0, sign, aAngle);
                                                }
                                            }
                                            break;
                     case gtBallGun:urender_DrawSpriteRotated(sprHandBallgun, hx, hy, sign, aAngle);
                                    break;
                     case gtRCPlane:{
                                        urender_DrawSpriteRotated(sprHandPlane, hx + 1, hy, sign, 0);
                                        defaultPos = false;
                                    }
                                    break;
                     case gtRope:{
                                     if(ufloat_hwFloat_hwFloat_op_lt(Gear->X, CurAmmoGear->X))
                                     {
                                         dAngle = 0;
                                         hAngle = 180;
                                         i = 1;
                                     }
                                     else
                                     {
                                         dAngle = 180;
                                         hAngle = 0;
                                         i = -1;
                                     }
                                     if((Gear->State & gstWinner) == 0)
                                     {
                                         urender_DrawHedgehog(ox, oy, i, 1, 0, uutils_DxDy2Angle(CurAmmoGear->dY, CurAmmoGear->dX) + dAngle);
                                         {
                                             if(curhat != NULL)
                                             {
                                                 urender_DrawTextureRotatedF(curhat, 1.0, -1.0, -6.0, ox, oy, 0, i, 32, 32, (i * uutils_DxDy2Angle(CurAmmoGear->dY, CurAmmoGear->dX)) + hAngle);
                                                 if((curhat->w > 64) || ((curhat->w == 64) && (curhat->h == 32)))
                                                 {
                                                     if((curhat->w == 64) && (curhat->h == 32))
                                                     {
                                                         tx = 1;
                                                     }
                                                     else
                                                     {
                                                         tx = 32;
                                                     }
                                                     urender_Tint_1(((*(*HH->Team).Clan).Color << 8) | 0xff);
                                                     urender_DrawTextureRotatedF(curhat, 1.0, -1.0, -6.0, ox, oy, tx, i, 32, 32, (i * uutils_DxDy2Angle(CurAmmoGear->dY, CurAmmoGear->dX)) + hAngle);
                                                     urender_untint();
                                                 }
                                             }
                                         }
                                     }
                                     defaultPos = false;
                                 }
                                 break;
                     case gtBlowTorch:{
                                          urender_DrawSpriteRotated(sprBlowTorch, ox + (8 * sign), oy - 2, sign, aAngle);
                                          urender_DrawHedgehog(ox + 1, oy - 3, sign, 3, HH->visStepPos / 2, 0);
                                          {
                                              if(curhat != NULL)
                                              {
                                                  urender_DrawTextureF(curhat, 1, ox + 1, oy - 8, 0, sign, 32, 32);
                                                  if((curhat->w > 64) || ((curhat->w == 64) && (curhat->h == 32)))
                                                  {
                                                      if((curhat->w == 64) && (curhat->h == 32))
                                                      {
                                                          tx = 1;
                                                      }
                                                      else
                                                      {
                                                          tx = 32;
                                                      }
                                                      urender_Tint_1(((*(*HH->Team).Clan).Color << 8) | 0xff);
                                                      urender_DrawTextureF(curhat, 1, ox + 1, oy - 8, tx, sign, 32, 32);
                                                      urender_untint();
                                                  }
                                              }
                                          }
                                          defaultPos = false;
                                          sign = ufloat_hwSign(Gear->dX);
                                      }
                                      break;
                     case gtFirePunch:{
                                          urender_DrawHedgehog(sx, sy, sign, 1, 4, 0);
                                          defaultPos = false;
                                      }
                                      break;
                     case gtPickHammer:{
                                           defaultPos = false;
                                           sy -= 20;
                                       }
                                       break;
                     case gtTeleport:defaultPos = false;
                                     break;
                     case gtParachute:{
                                          urender_DrawSpriteRotatedF(sprHHIdle, sx, sy, 0, CurAmmoGear->Tag, 0);
                                          HatVisible = true;
                                          defaultPos = false;
                                      }
                                      break;
                     case gtWhip:{
                                     urender_DrawSpriteRotatedF(sprWhip, sx, sy, 1, sign, 0);
                                     defaultPos = false;
                                 }
                                 break;
                     case gtHammer:{
                                       urender_DrawSpriteRotatedF(sprHammer, sx, sy, 1, sign, 0);
                                       defaultPos = false;
                                   }
                                   break;
                     case gtResurrector:{
                                            urender_DrawSpriteRotated(sprHandResurrector, sx, sy, 0, 0);
                                            defaultPos = false;
                                        }
                                        break;
                     case gtKamikaze:{
                                         if(CurAmmoGear->Pos == 0)
                                         {
                                             urender_DrawHedgehog(sx, sy, sign, 1, 6, 0);
                                         }
                                         else
                                         {
                                             urender_DrawSpriteRotatedF(sprKamikaze, ox, oy, CurAmmoGear->Pos - 1, sign, aAngle);
                                         }
                                         defaultPos = false;
                                     }
                                     break;
                     case gtSeduction:{
                                          if(CurAmmoGear->Pos >= 6)
                                          {
                                              urender_DrawHedgehog(sx, sy, sign, 2, 2, 0);
                                          }
                                          else
                                          {
                                              urender_DrawSpriteRotatedF(sprDress, ox, oy, CurAmmoGear->Pos, sign, 0);
                                              if(_strcompare(fpcrtl_copy(cLanguage, 1, 2), __str0))
                                              {
                                                  urender_DrawSprite_4(sprCensored, ox - 32, oy - 20, 0);
                                              }
                                          }
                                          defaultPos = false;
                                      }
                                      break;
                     case gtFlamethrower:urender_DrawSpriteRotatedF(sprHandFlamethrower, hx, hy, (RealTicks / 125) % 4, sign, aAngle);
                                         break;
                     case gtLandGun:urender_DrawSpriteRotated(sprHandLandGun, hx, hy, sign, aAngle);
                                    break;
                     case gtIceGun:urender_DrawSpriteRotated(sprIceGun, hx, hy, sign, aAngle);
                                   break;
                     default: break;}
                    switch(CurAmmoGear->Kind)
                    {case gtShotgunShot:
                     case gtDEagleShot:
                     case gtSniperRifleShot:{
                                                urender_DrawHedgehog(sx, sy, sign, 0, 4, 0);
                                                defaultPos = false;
                                                HatVisible = true;
                                            }
                                            break;
                     case gtShover:
                     case gtMinigun:{
                                        urender_DrawHedgehog(sx, sy, sign, 0, 5, 0);
                                        defaultPos = false;
                                        HatVisible = true;
                                    }
                                    break;
                     default: break;}
                }
                else
                {
                    if((Gear->State & gstHHJumping) != 0)
                    {
                        urender_DrawHedgehog(sx, sy, hogLR, 1, 1, 0);
                        HatVisible = true;
                        defaultPos = false;
                    }
                    else
                    {
                        if(((Gear->Message & (gmLeft | gmRight)) != 0) && !isCursorVisible)
                        {
                            urender_DrawHedgehog(sx, sy, sign, 0, HH->visStepPos / 2, 0);
                            defaultPos = false;
                            HatVisible = true;
                        }
                        else
                        {
                            if((Gear->State & gstAnimation) != 0)
                            {
                                if((Gear->Tag < ((LongInt)(0))) || (Gear->Tag > ((LongInt)(8))))
                                {
                                    Gear->State = Gear->State & ~gstAnimation;
                                }
                                else
                                {
                                    urender_DrawSpriteRotatedF(Wavez[((TWave)Gear->Tag)].Sprite, sx, sy, Gear->Pos, sign, 0.0);
                                    defaultPos = false;
                                }
                            }
                            else
                            {
                                if((Gear->State & gstAttacked) == 0)
                                {
                                    if(HH->Timer > 0)
                                    {
                                        if(aAngle <= 90)
                                        {
                                            aAngle = aAngle + 360;
                                        }
                                        if(ufloat_hwFloat_hwFloat_op_gt(Gear->dX, _0))
                                        {
                                            aAngle = aAngle - (((aAngle - 240) * HH->Timer) /(float) 10);
                                        }
                                        else
                                        {
                                            aAngle = aAngle + (((240 - aAngle) * HH->Timer) /(float) 10);
                                        }
                                        --HH->Timer;
                                    }
                                    amt = CurrentHedgehog->CurAmmoType;
                                    CurWeapon = uammos_GetCurAmmoEntry(&((*HH)));
                                    switch(amt)
                                    {case amBazooka:urender_DrawSpriteRotated(sprHandBazooka, hx, hy, sign, aAngle);
                                                    break;
                                     case amSnowball:urender_DrawSpriteRotated(sprHandSnowball, hx, hy, sign, aAngle);
                                                     break;
                                     case amMortar:urender_DrawSpriteRotated(sprHandMortar, hx, hy, sign, aAngle);
                                                   break;
                                     case amMolotov:urender_DrawSpriteRotated(sprHandMolotov, hx, hy, sign, aAngle);
                                                    break;
                                     case amBallgun:urender_DrawSpriteRotated(sprHandBallgun, hx, hy, sign, aAngle);
                                                    break;
                                     case amDrill:urender_DrawSpriteRotated(sprHandDrill, hx, hy, sign, aAngle);
                                                  break;
                                     case amRope:urender_DrawSpriteRotated(sprHandRope, hx, hy, sign, aAngle);
                                                 break;
                                     case amShotgun:urender_DrawSpriteRotated(sprHandShotgun, hx, hy, sign, aAngle);
                                                    break;
                                     case amDEagle:urender_DrawSpriteRotated(sprHandDEagle, hx, hy, sign, aAngle);
                                                   break;
                                     case amSineGun:urender_DrawSpriteRotatedF(sprHandSineGun, hx, hy, 73 + ((sign * ((LongInt)RealTicks / 73)) % 8), sign, aAngle);
                                                    break;
                                     case amPortalGun:if((CurWeapon->Timer & 2) != 0)
                                                      {
                                                          urender_DrawSpriteRotatedF(sprPortalGun, hx, hy, 0, sign, aAngle);
                                                      }
                                                      else
                                                      {
                                                          urender_DrawSpriteRotatedF(sprPortalGun, hx, hy, 1 + CurWeapon->Pos, sign, aAngle);
                                                      }
                                                      break;
                                     case amSniperRifle:urender_DrawSpriteRotatedF(sprSniperRifle, hx, hy, 0, sign, aAngle);
                                                        break;
                                     case amBlowTorch:urender_DrawSpriteRotated(sprHandBlowTorch, hx, hy, sign, aAngle);
                                                      break;
                                     case amCake:urender_DrawSpriteRotated(sprHandCake, hx, hy, sign, aAngle);
                                                 break;
                                     case amGrenade:urender_DrawSpriteRotated(sprHandGrenade, hx, hy, sign, aAngle);
                                                    break;
                                     case amWatermelon:urender_DrawSpriteRotated(sprHandMelon, hx, hy, sign, aAngle);
                                                       break;
                                     case amSkip:urender_DrawSpriteRotated(sprHandSkip, hx, hy, sign, aAngle);
                                                 break;
                                     case amClusterBomb:urender_DrawSpriteRotated(sprHandCluster, hx, hy, sign, aAngle);
                                                        break;
                                     case amDynamite:urender_DrawSpriteRotated(sprHandDynamite, hx, hy, sign, aAngle);
                                                     break;
                                     case amCreeper:urender_DrawSpriteRotatedF(sprHandCreeper, hx, hy, 0, sign, aAngle);
                                                    break;
                                     case amSentry:urender_DrawSpriteRotated(sprHandSentry, hx, hy, sign, aAngle);
                                                   break;
                                     case amHellishBomb:urender_DrawSpriteRotated(sprHandHellish, hx, hy, sign, aAngle);
                                                        break;
                                     case amGasBomb:urender_DrawSpriteRotated(sprHandCheese, hx, hy, sign, aAngle);
                                                    break;
                                     case amMine:urender_DrawSpriteRotated(sprHandMine, hx, hy, sign, aAngle);
                                                 break;
                                     case amAirMine:urender_DrawSpriteRotated(sprHandAirMine, hx, hy, sign, aAngle);
                                                    break;
                                     case amSMine:urender_DrawSpriteRotated(sprHandSMine, hx, hy, sign, aAngle);
                                                  break;
                                     case amKnife:urender_DrawSpriteRotatedF(sprHandKnife, hx, hy, 0, sign, aAngle);
                                                  break;
                                     case amSeduction:if((Gear->State & gstMoving) == 0)
                                                      {
                                                          urender_DrawSpriteRotated(sprHandSeduction, hx, hy, sign, aAngle);
                                                          urender_DrawCircle_8(ox, oy, cSeductionDist - 2, 4, 0xff, 0x00, 0x00, 0xaa);
                                                      }
                                                      break;
                                     case amVampiric:urender_DrawSpriteRotatedF(sprHandVamp, hx, hy, (RealTicks / 125) % 4, sign, aAngle);
                                                     break;
                                     case amRubber:
                                     case amGirder:if((Gear->State & gstMoving) == 0)
                                                   {
                                                       urender_DrawSpriteRotated(sprHandConstruction, hx, hy, sign, aAngle);
                                                       if(cBuildMaxDist == cDefaultBuildMaxDist)
                                                       {
                                                           if(WorldEdge == weWrap)
                                                           {
                                                               if(ufloat_hwRound(Gear->X) < (leftX + 256))
                                                               {
                                                                   urender_DrawSpriteClipped(sprGirder, (rightX + (ox - leftX)) - 256, oy - 256, topY + WorldDy, rightX + WorldDx, cWaterLine + WorldDy, leftX + WorldDx);
                                                               }
                                                               if(ufloat_hwRound(Gear->X) > (rightX - 256))
                                                               {
                                                                   urender_DrawSpriteClipped(sprGirder, (leftX - (rightX - ox)) - 256, oy - 256, topY + WorldDy, rightX + WorldDx, cWaterLine + WorldDy, leftX + WorldDx);
                                                               }
                                                           }
                                                           urender_DrawSpriteClipped(sprGirder, ox - 256, oy - 256, topY + WorldDy, rightX + WorldDx, cWaterLine + WorldDy, leftX + WorldDx);
                                                       }
                                                       else
                                                       {
                                                           if(cBuildMaxDist > 0)
                                                           {
                                                               urender_DrawCircle_8(hx, hy, cBuildMaxDist, 3, 0xff, 0, 0, 0x80);
                                                           }
                                                       }
                                                   }
                                                   break;
                                     case amBee:urender_DrawSpriteRotatedF(sprHandBee, hx, hy, (RealTicks / 125) % 4, sign, aAngle);
                                                break;
                                     case amFlamethrower:urender_DrawSpriteRotatedF(sprHandFlamethrower, hx, hy, (RealTicks / 125) % 4, sign, aAngle);
                                                         break;
                                     case amLandGun:urender_DrawSpriteRotated(sprHandLandGun, hx, hy, sign, aAngle);
                                                    break;
                                     case amIceGun:urender_DrawSpriteRotated(sprIceGun, hx, hy, sign, aAngle);
                                                   break;
                                     case amResurrector:if((Gear->State & gstMoving) == 0)
                                                        {
                                                            urender_DrawCircle_8(ox, oy, cResurrectorDist - 2, 4, 0xf5, 0xdb, 0x35, 0xaa);
                                                        }
                                                        break;
                                     case amFirePunch:urender_DrawSpriteRotatedF(sprFirePunch, (hx + (6 * sign)) + 1, hy - 5, (RealTicks / 50) % 16, sign, 0);
                                                      break;
                                     default: break;}
                                    switch(amt)
                                    {case amAirAttack:
                                     case amNapalm:
                                     case amMineStrike:
                                     case amDrillStrike:urender_DrawSpriteRotated(sprHandAirAttack, sx, oy, sign, 0);
                                                        break;
                                     case amPickHammer:urender_DrawHedgehog(sx, sy, sign, 1, 2, 0);
                                                       break;
                                     case amTeleport:
                                     case amPiano:urender_DrawSpriteRotatedF(sprTeleport, sx, sy, 0, sign, 0);
                                                  break;
                                     case amKamikaze:urender_DrawHedgehog(sx, sy, sign, 1, 5, 0);
                                                     break;
                                     case amWhip:urender_DrawSpriteRotatedF(sprWhip, sx, sy, 0, sign, 0);
                                                 break;
                                     case amHammer:urender_DrawSpriteRotatedF(sprHammer, sx + sign, sy, 0, sign, 0);
                                                   break;
                                     case amRCPlane:{
                                                        urender_DrawSpriteRotated(sprHandPlane, hx + 1, hy, sign, 0);
                                                        defaultPos = false;
                                                    }
                                                    break;
                                     case amBaseballBat:
                                     case amMinigun:{
                                                        HatVisible = true;
                                                        urender_DrawHedgehog(sx, sy, sign, 0, 5, 0);
                                                    }
                                                    break;
                                     default: if((((_strcompare(HH->Hat, __str1)) || (HH->HatTex == NULL)) && ((Gear->State & (gstMoving | gstAttacking)) == 0)) && ((Ammoz[amt].Ammo.Propz & ammoprop_ShowSelIcon) != 0))
                                              {
                                                  urender_DrawHedgehog(sx, sy, sign, 0, 6, 0);
                                              }
                                              else
                                              {
                                                  urender_DrawHedgehog(sx, sy, sign, 0, 4, 0);
                                                  HatVisible = true;
                                              }}
                                    defaultPos = false;
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                if(((Gear->Damage > 0) && (HH->Effects[heFrozen] == 0)) && (ufloat_hwFloat_hwFloat_op_gt(ufloat_hwFloat_hwFloat_op_add(ufloat_hwSqr(Gear->dX), ufloat_hwSqr(Gear->dY)), _0_003)))
                {
                    defaultPos = false;
                    urender_DrawHedgehog(sx, sy, sign, 2, 1, Gear->DirAngle);
                    if((sx % 8) == 0)
                    {
                        if(Gear->dX.isNegative)
                        {
                            tx = ufloat_hwRound(Gear->X) + cHHRadius;
                        }
                        else
                        {
                            tx = ufloat_hwRound(Gear->X) - cHHRadius;
                        }
                        ty = (ufloat_hwRound(Gear->Y) + cHHRadius) + 2;
                        if((((tx & LAND_WIDTH_MASK) == 0) && ((ty & LAND_HEIGHT_MASK) == 0)) && (ulandutils_LandGet(ty, tx) != 0))
                        {
                            uvisualgearslist_AddVisualGear_3((tx - 2) + fpcrtl_random(4), ty - 8, vgtDust);
                        }
                    }
                    if(AprilOne && (curhat != NULL))
                    {
                        urender_DrawTextureRotatedF(curhat, 1.0, -1.0, 0, sx, sy, 18, sign, 32, 32, sign * Gear->DirAngle);
                    }
                }
                if((Gear->State & gstHHJumping) != 0)
                {
                    urender_DrawHedgehog(sx, sy, hogLR, 1, 1, 0);
                    defaultPos = false;
                }
            }
        }
    }
    {
        if(defaultPos)
        {
            if((*HH->Team).hasGone)
            {
                urender_Tint_1(0xffffff80);
            }
            urender_DrawSpriteRotatedF(sprHHIdle, sx, sy, ((RealTicks / 128) + (*HH).Gear->Pos) % 19, sign, 0);
            HatVisible = true;
        }
        if(HatVisible)
        {
            if((*HH).HatVisibility < 1.0)
            {
                (*HH).HatVisibility = (*HH).HatVisibility + 0.2;
            }
            else
            {
                ;
            }
        }
        else
        {
            if((*HH).HatVisibility > 0.0)
            {
                (*HH).HatVisibility = (*HH).HatVisibility - 0.2;
            }
        }
        if((curhat != NULL) && ((*HH).HatVisibility > 0))
        {
            if(defaultPos)
            {
                if((curhat->h == 32) && ((curhat->w == 32) || (curhat->w == 64)))
                {
                    tx = ((RealTicks / 128) + (*HH).Gear->Pos) % 19;
                    ty = 0;
                    if(((tx == 2) || (tx == 7)) || (tx == 12))
                    {
                        ty = 1;
                    }
                    else
                    {
                        if(tx == 16)
                        {
                            ty = -1;
                        }
                    }
                    urender_DrawTextureF(curhat, (*HH).HatVisibility, sx, (sy - 5) + ty, 0, sign, 32, 32);
                    if(curhat->w == 64)
                    {
                        urender_Tint_1(((*(*HH->Team).Clan).Color << 8) | 0xff);
                        urender_DrawTextureF(curhat, (*HH).HatVisibility, sx, (sy - 5) + ty, 1, sign, 32, 32);
                        urender_untint();
                    }
                }
                else
                {
                    urender_DrawTextureF(curhat, (*HH).HatVisibility, sx, sy - 5, ((RealTicks / 128) + (*HH).Gear->Pos) % 19, sign, 32, 32);
                    if(curhat->w > 64)
                    {
                        urender_Tint_1(((*(*HH->Team).Clan).Color << 8) | 0xff);
                        urender_DrawTextureF(curhat, (*HH).HatVisibility, sx, sy - 5, (((RealTicks / 128) + (*HH).Gear->Pos) % 19) + 32, sign, 32, 32);
                        urender_untint();
                    }
                }
                if((*HH->Team).hasGone)
                {
                    urender_untint();
                }
            }
            else
            {
                urender_DrawTextureF(curhat, (*HH).HatVisibility, sx, sy - 5, 0, hogLR, 32, 32);
                if((curhat->w > 64) || ((curhat->w == 64) && (curhat->h == 32)))
                {
                    if((curhat->w == 64) && (curhat->h == 32))
                    {
                        tx = 1;
                    }
                    else
                    {
                        tx = 32;
                    }
                    urender_Tint_1(((*(*HH->Team).Clan).Color << 8) | 0xff);
                    urender_DrawTextureF(curhat, (*HH).HatVisibility, sx, sy - 5, tx, hogLR, 32, 32);
                    urender_untint();
                }
            }
        }
    }
    if((Gear->State & gstHHDriven) != 0)
    {
        if(CurAmmoGear == NULL)
        {
            if(((Gear->State & ((gstAttacked | gstAnimation) | gstHHJumping)) == 0) && ((Gear->Message & (gmLeft | gmRight)) == 0))
            {
                amt = CurrentHedgehog->CurAmmoType;
                switch(amt)
                {case amBaseballBat:urender_DrawSpritePivotedF(sprHandBaseball, sx + (9 * sign), sy + 2, 0, sign, -8, 1, aAngle);
                                    break;
                 case amMinigun:urender_DrawSpritePivotedF(sprMinigun, sx + (20 * sign), sy + 4, 0, sign, -18, -2, aAngle);
                                break;
                 default: break;}
            }
        }
        else
        {
            aAngle = ((Gear->Angle * 180) /(float) cMaxAngle) - 90;
            switch(CurAmmoGear->Kind)
            {case gtJetpack:{
                                urender_DrawSprite_4(sprJetpack, sx - 32, sy - 32, 0);
                                if(cWaterLine > (ufloat_hwRound(Gear->Y) + Gear->Radius))
                                {
                                    if((CurAmmoGear->MsgParam & gmUp) != 0)
                                    {
                                        urender_DrawSprite_4(sprJetpack, sx - 32, sy - 28, 1);
                                    }
                                    if((CurAmmoGear->MsgParam & gmLeft) != 0)
                                    {
                                        urender_DrawSprite_4(sprJetpack, sx - 28, sy - 28, 2);
                                    }
                                    if((CurAmmoGear->MsgParam & gmRight) != 0)
                                    {
                                        urender_DrawSprite_4(sprJetpack, sx - 36, sy - 28, 3);
                                    }
                                }
                            }
                            break;
             case gtShover:urender_DrawSpritePivotedF(sprHandBaseball, sx + (9 * sign), sy + 2, CurAmmoGear->Tag, sign, -8, 1, aAngle);
                           break;
             case gtMinigun:urender_DrawSpritePivotedF(sprMinigun, sx + (20 * sign), sy + 4, CurAmmoGear->Tag, sign, -18, -2, aAngle);
                            break;
             default: break;}
        }
    }
    {
        if(((((*HH).Gear->State & ~gstWinner) == 0) || (((*HH).Gear->State == gstWait) && ((*HH).Gear->dY.QWordValue == 0))) || (bShowFinger && (((*HH).Gear->State & gstHHDriven) != 0)))
        {
            t = (sy - cHHRadius) - 9;
            if((cTagsMask & htTransparent) != 0)
            {
                urender_Tint_4(0xff, 0xff, 0xff, 0x80);
            }
            if((cTagsMask & htHealth) != 0)
            {
                t -= (*HH).HealthTagTex->h + 2;
                urender_DrawTextureCentered(ox, t, (*HH).HealthTagTex);
            }
            if((cTagsMask & htName) != 0)
            {
                t -= (*HH).NameTagTex->h + 2;
                urender_DrawTextureCentered(ox, t, (*HH).NameTagTex);
            }
            if((cTagsMask & htTeamName) != 0)
            {
                t -= (*(*HH).Team->NameTagTex).h + 2;
                urender_DrawTextureCentered(ox, t, (*HH).Team->NameTagTex);
            }
            if((cTagsMask & htTransparent) != 0)
            {
                urender_untint();
            }
        }
        if(((*HH).Gear->State & gstHHDriven) != 0)
        {
            if((CurAmmoGear != NULL) && (CurAmmoGear->Kind == gtResurrector))
            {
                urender_DrawTextureCentered(ox, ((sy - cHHRadius) - 7) - (*HH).HealthTagTex->h, (*HH).HealthTagTex);
            }
            if(((*HH).Gear->State & gstDrowning) == 0)
            {
                if((((*HH).Gear->State & gstHHThinking) != 0) && !CinematicScript)
                {
                    urender_DrawSprite_4(sprQuestion, ox - 10, (oy - cHHRadius) - 34, (RealTicks >> 9) % 8);
                }
            }
        }
    }
    if(HH->Effects[hePoisoned] != 0)
    {
        urender_Tint_4(0x00, 0xff, 0x40, 0x80);
        urender_DrawTextureRotatedF(SpritesData[sprSmokeWhite].Texture, 1.5, 0, 0, sx, sy, 0, 1, 22, 22, 360 - ((RealTicks >> 5) % 360));
    }
    if(HH->Effects[heResurrected] != 0)
    {
        urender_Tint_4(0xf5, 0xdb, 0x35, 0x20);
        urender_DrawSprite_4(sprVampiric, sx - 24, sy - 24, 0);
    }
    if((*Gear->Hedgehog).Effects[heInvulnerable] != 0)
    {
        urender_Tint_4(0xff, 0xff, 0xff, uutils_Max(0x40, fpcrtl_round(0xff * fpcrtl_abs(1 - ((((RealTicks / 2) + (Gear->uid * 491)) % 1500) /(float) 750)))));
        urender_DrawSprite_4(sprInvulnerable, sx - 24, sy - 24, 0);
    }
    if(HH->Effects[heFrozen] < 150000)
    {
        if(HH->Effects[heFrozen] < 150000)
        {
            urender_Tint_4(0xff, 0xff, 0xff, uutils_Min(255, 127 + (HH->Effects[heFrozen] / 800)));
        }
        iceOffset = uutils_Min(32, HH->Effects[heFrozen] / 8);
        r.x = 128;
        r.y = 96 - iceOffset;
        r.w = 32;
        r.h = iceOffset;
        urender_DrawTextureFromRectDir((sx - 16) + (sign * 2), (sy + 16) - iceOffset, r.w, r.h, &(r), HHTexture, sign);
        if(HH->Effects[heFrozen] < 150000)
        {
            urender_untint();
        }
    }
    if((cVampiric && (CurrentHedgehog->Gear != NULL)) && (CurrentHedgehog->Gear == Gear))
    {
        urender_Tint_4(0xff, 0, 0, uutils_Max(0x40, fpcrtl_round(0xff * fpcrtl_abs(1 - ((RealTicks % 1500) /(float) 750)))));
        urender_DrawSprite_4(sprVampiric, sx - 24, sy - 24, 0);
    }
    urender_untint();
};
void ugearsrender_RenderGear(PGear Gear,LongInt x,LongInt y)
{
    PGear HHGear;
    PVisualGear vg;
    LongWord i;
    real aAngle;
    LongInt startX;
    LongInt endX;
    LongInt startY;
    LongInt endY;
    LongInt ty;
    if(((Gear->State & gstFrozen) != 0) && (Gear->Kind != gtAirMine))
    {
        urender_Tint_4(0xa0, 0xa0, 0xff, 0xff);
    }
    if(Gear->Target.x != NoPointX)
    {
        if(Gear->AmmoType == amBee)
        {
            urender_DrawSpriteRotatedF(sprTargetBee, Gear->Target.x + WorldDx, Gear->Target.y + WorldDy, 0, 0, (RealTicks >> 3) % 360);
        }
        else
        {
            if(Gear->AmmoType == amIceGun)
            {
                urender_DrawTextureRotatedF(SpritesData[sprSnowDust].Texture, 1 /(float) (1 + ((RealTicks >> 8) % 5)), 0, 0, Gear->Target.x + WorldDx, Gear->Target.y + WorldDy, (RealTicks >> 2) % 8, 1, 22, 22, (RealTicks >> 3) % 360);
            }
            else
            {
                if(CurrentHedgehog != NULL)
                {
                    if(urenderutils_IsTooDarkToRead((*(*CurrentHedgehog->Team).Clan).Color))
                    {
                        urender_DrawSpriteRotatedF(sprTargetPBackInv, Gear->Target.x + WorldDx, Gear->Target.y + WorldDy, 0, 0, (RealTicks >> 3) % 360);
                    }
                    else
                    {
                        urender_DrawSpriteRotatedF(sprTargetPBack, Gear->Target.x + WorldDx, Gear->Target.y + WorldDy, 0, 0, (RealTicks >> 3) % 360);
                    }
                    urender_Tint_1(((*(*CurrentHedgehog->Team).Clan).Color << 8) | 0xff);
                }
                urender_DrawSpriteRotatedF(sprTargetP, Gear->Target.x + WorldDx, Gear->Target.y + WorldDy, 0, 0, (RealTicks >> 3) % 360);
                if(CurrentHedgehog != NULL)
                {
                    urender_untint();
                }
            }
        }
    }
    switch(Gear->Kind)
    {case gtGrenade:urender_DrawSpriteRotated(sprBomb, x, y, 0, Gear->DirAngle);
                    break;
     case gtSnowball:urender_DrawSpriteRotated(sprSnowball, x, y, 0, Gear->DirAngle);
                     break;
     case gtGasBomb:urender_DrawSpriteRotated(sprCheese, x, y, 0, Gear->DirAngle);
                    break;
     case gtMolotov:if((Gear->State & gstDrowning) == 0)
                    {
                        urender_DrawSpriteRotatedF(sprMolotov, x, y, (RealTicks / 125) % 8, ufloat_hwSign(Gear->dX), Gear->DirAngle * ufloat_hwSign(Gear->dX));
                    }
                    else
                    {
                        urender_DrawSprite_4(sprMolotov, x, y, 8);
                    }
                    break;
     case gtRCPlane:{
                        aAngle = (Gear->Angle * 360) /(float) 4096;
                        if(Gear->Tag < 0)
                        {
                            aAngle = 360 - aAngle;
                        }
                        urender_Tint_1(Gear->Tint);
                        urender_DrawSpriteRotatedF(sprPlane, x, y, 0, Gear->Tag, aAngle - 90);
                        urender_untint();
                        urender_DrawSpriteRotatedF(sprPlane, x, y, 1, Gear->Tag, aAngle - 90);
                    }
                    break;
     case gtBall:urender_DrawSpriteRotatedF(sprBalls, x, y, Gear->Tag, 0, Gear->DirAngle);
                 break;
     case gtPortal:{
                       if(((((Gear->Tag & 1) == 0) || (Gear->LinkedGear == NULL)) || ((*Gear->LinkedGear).LinkedGear != Gear)) || (((*Gear->LinkedGear).Tag & 1) == 0))
                       {
                           urender_DrawSpriteRotatedF(sprPortal, x, y, Gear->Tag, ufloat_hwSign(Gear->dX), Gear->DirAngle);
                       }
                       else
                       {
                           urender_DrawSpriteRotatedF(sprPortal, x, y, 4 + (Gear->Tag / 2), ufloat_hwSign(Gear->dX), Gear->DirAngle);
                       }
                       if((((Gear->Tag & 1) == 0) && ((GameTicks % 4) == 0)) && !isPaused)
                       {
                           vg = uvisualgearslist_AddVisualGear_4(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtDust, 1);
                           if(vg != NULL)
                           {
                               if(Gear->Tag == 0)
                               {
                                   vg->Tint = 0xfab02ab0;
                               }
                               else
                               {
                                   if(Gear->Tag == 2)
                                   {
                                       vg->Tint = 0x364df7b0;
                                   }
                               }
                           }
                       }
                   }
                   break;
     case gtDrill:{
                      if(Gear->Pos == 1)
                      {
                          i = ((RealTicks >> 5) + Gear->uid) % 4;
                      }
                      else
                      {
                          i = Gear->uid % 4;
                      }
                      if((Gear->State & gsttmpFlag) != 0)
                      {
                          urender_DrawTextureRotatedF(SpritesData[sprAirDrill].Texture, 0.5, 0, 0, x, y, i, 0, 64, 64, uutils_DxDy2Angle(Gear->dY, Gear->dX));
                      }
                      else
                      {
                          urender_DrawTextureRotatedF(SpritesData[sprDrill].Texture, 0.5, 0, 0, x, y, i, 0, 64, 64, uutils_DxDy2Angle(Gear->dY, Gear->dX));
                      }
                  }
                  break;
     case gtHedgehog:ugearsrender_DrawHH(Gear, x, y);
                     break;
     case gtShell:urender_DrawSpriteRotated(sprBazookaShell, x, y, 0, uutils_DxDy2Angle(Gear->dY, Gear->dX));
                  break;
     case gtGrave:{
                      urender_DrawTextureF((*(*Gear->Hedgehog).Team).GraveTex, 1, x, y, ((RealTicks >> 7) + Gear->uid) & 15, 1, 32, 32);
                      if(Gear->Health > 0)
                      {
                          urender_Tint_4(0xf5, 0xdb, 0x35, uutils_Max(0x40, fpcrtl_round(0xff * fpcrtl_abs(1 - ((RealTicks % 1500) /(float) (750 + Gear->Health))))));
                          urender_DrawSprite_4(sprVampiric, x - 24, y - 24, 0);
                          urender_untint();
                      }
                  }
                  break;
     case gtBee:urender_DrawSpriteRotatedF(sprBee, x, y, (RealTicks >> 5) % 2, 0, uutils_DxDy2Angle(Gear->dY, Gear->dX));
                break;
     case gtPickHammer:urender_DrawSprite_4(sprPHammer, x - 16, (y - 50) + ((LongInt)((GameTicks >> 5) & 1) * 2), 0);
                       break;
     case gtRope:ugearsrender_DrawRope(Gear);
                 break;
     case gtMine:{
                     if((((Gear->State & gstAttacking) == 0) || ((Gear->Timer & 0x3ff) < 420)) && (Gear->Health != 0))
                     {
                         urender_DrawSpriteRotated(sprMineOff, x, y, 0, Gear->DirAngle);
                     }
                     else
                     {
                         if(Gear->Health != 0)
                         {
                             urender_DrawSpriteRotated(sprMineOn, x, y, 0, Gear->DirAngle);
                         }
                         else
                         {
                             urender_DrawSpriteRotated(sprMineDead, x, y, 0, Gear->DirAngle);
                         }
                     }
                 }
                 break;
     case gtAirMine:if((Gear->State & gstFrozen) != 0)
                    {
                        urender_DrawSprite_4(sprFrozenAirMine, x - 16, y - 16, 0);
                    }
                    else
                    {
                        if(Gear->Tag != 0)
                        {
                            urender_DrawSprite_4(sprAirMine, x - 16, y - 16, 16 + (((RealTicks / 50) + Gear->uid) % 16));
                        }
                        else
                        {
                            if((Gear->State & gsttmpFlag) == 0)
                            {
                                urender_Tint_4(150, 150, 150, 255);
                                urender_DrawSprite_4(sprAirMine, x - 16, y - 16, 15);
                                urender_untint();
                            }
                            else
                            {
                                if((Gear->Hedgehog != NULL) && ((*Gear->Hedgehog).Gear != NULL))
                                {
                                    urender_DrawSprite_4(sprAirMine, x - 16, y - 16, ((RealTicks / 25) + Gear->uid) % 16);
                                }
                                else
                                {
                                    if((Gear->State & gstChooseTarget) != 0)
                                    {
                                        urender_DrawSprite_4(sprAirMine, x - 16, y - 16, 3);
                                    }
                                    else
                                    {
                                        urender_DrawSprite_4(sprAirMine, x - 16, y - 16, 15);
                                    }
                                }
                            }
                        }
                    }
                    break;
     case gtSMine:if((((Gear->State & gstAttacking) == 0) || ((Gear->Timer & 0x3ff) < 420)) && (Gear->Health != 0))
                  {
                      urender_DrawSpriteRotated(sprSMineOff, x, y, 0, Gear->DirAngle);
                  }
                  else
                  {
                      if(Gear->Health != 0)
                      {
                          urender_DrawSpriteRotated(sprSMineOn, x, y, 0, Gear->DirAngle);
                      }
                      else
                      {
                          urender_DrawSpriteRotated(sprMineDead, x, y, 0, Gear->DirAngle);
                      }
                  }
                  break;
     case gtKnife:urender_DrawSpriteRotatedF(sprKnife, x, y, 0, ufloat_hwSign(Gear->dX), Gear->DirAngle);
                  break;
     case gtCase:{
                     if(Gear->Timer > 1000)
                     {
                         if((Gear->Pos & posCaseAmmo) != 0)
                         {
                             if((Gear->State & gstFrozen) != 0)
                             {
                                 urender_DrawSprite_4(sprCase, x - 24, y - 28, 0);
                             }
                             else
                             {
                                 i = (RealTicks >> 6) % 64;
                                 if(i > 18)
                                 {
                                     i = 0;
                                 }
                                 urender_DrawSprite_4(sprCase, x - 24, y - 24, i);
                             }
                         }
                         else
                         {
                             if((Gear->Pos & posCaseHealth) != 0)
                             {
                                 if((Gear->State & gstFrozen) != 0)
                                 {
                                     urender_DrawSprite_4(sprFAid, x - 24, y - 28, 0);
                                 }
                                 else
                                 {
                                     i = ((RealTicks >> 6) + 38) % 64;
                                     if(i > 13)
                                     {
                                         i = 0;
                                     }
                                     urender_DrawSprite_4(sprFAid, x - 24, y - 24, i);
                                 }
                             }
                             else
                             {
                                 if((Gear->Pos & posCaseUtility) != 0)
                                 {
                                     if((Gear->State & gstFrozen) != 0)
                                     {
                                         urender_DrawSprite_4(sprUtility, x - 24, y - 28, 0);
                                     }
                                     else
                                     {
                                         i = (RealTicks >> 6) % 70;
                                         if(i > 23)
                                         {
                                             i = 0;
                                         }
                                         i = i % 12;
                                         urender_DrawSprite_4(sprUtility, x - 24, y - 24, i);
                                     }
                                 }
                             }
                         }
                     }
                     if(Gear->Timer < 1833)
                     {
                         urender_DrawTextureRotatedF(SpritesData[sprPortal].Texture, uutils_MinD(fpcrtl_abs(1.25 - ((Gear->Timer % 1333) /(float) 400)), 1.25), 0, 0, x, (((LongInt)Gear->Angle) + WorldDy) - 16, 4 + Gear->Tag, 1, 32, 32, 270);
                     }
                 }
                 break;
     case gtExplosives:{
                           if((Gear->State & gstDrowning) != 0)
                           {
                               urender_DrawSprite_4(sprExplosivesRoll, x - 24, y - 24, 0);
                           }
                           else
                           {
                               if((Gear->State & gstAnimation) == 0)
                               {
                                   i = ((RealTicks >> 6) + (Gear->uid * 3)) % 64;
                                   if(i > 18)
                                   {
                                       i = 0;
                                   }
                                   urender_DrawSprite_4(sprExplosives, x - 24, y - 24, i);
                               }
                               else
                               {
                                   if((Gear->State & gsttmpFlag) == 0)
                                   {
                                       urender_DrawSpriteRotatedF(sprExplosivesRoll, x, y + 4, 0, 0, Gear->DirAngle);
                                   }
                                   else
                                   {
                                       urender_DrawSpriteRotatedF(sprExplosivesRoll, x, y + 4, 1, 0, Gear->DirAngle);
                                   }
                               }
                           }
                       }
                       break;
     case gtDynamite:{
                         if((Gear->State & gstDrowning) == 0)
                         {
                             urender_DrawSprite_5(sprDynamite, x - 16, y - 25, Gear->Tag & 1, Gear->Tag >> 1);
                         }
                         else
                         {
                             urender_DrawSprite_5(sprDynamiteDefused, x - 16, y - 25, Gear->Tag & 1, Gear->Tag >> 1);
                         }
                         if((fpcrtl_random(3) == 0) && ((Gear->State & gstDrowning) == 0))
                         {
                             vg = uvisualgearslist_AddVisualGear_3((ufloat_hwRound(Gear->X) + 12) - (Gear->Tag >> 1), ufloat_hwRound(Gear->Y) - 16, vgtStraightShot);
                             if(vg != NULL)
                             {
                                 {
                                     (*vg).Tint = 0xffcc00ff;
                                     (*vg).Angle = fpcrtl_random(360);
                                     (*vg).dX = 5.0e-4 * fpcrtl_random(200);
                                     (*vg).dY = 5.0e-4 * fpcrtl_random(200);
                                     if(fpcrtl_random(2) == 0)
                                     {
                                         (*vg).dX = -(*vg).dX;
                                     }
                                     if(fpcrtl_random(2) == 0)
                                     {
                                         (*vg).dY = -(*vg).dY;
                                     }
                                     (*vg).FrameTicks = 100 + fpcrtl_random(300);
                                     (*vg).scale = 0.1 + (1 /(float) (fpcrtl_random(3) + 3));
                                     (*vg).State = (sprStar);
                                 }
                             }
                         }
                     }
                     break;
     case gtClusterBomb:urender_DrawSpriteRotated(sprClusterBomb, x, y, 0, Gear->DirAngle);
                        break;
     case gtCluster:urender_DrawSprite_4(sprClusterParticle, x - 8, y - 8, 0);
                    break;
     case gtFlame:if((Gear->Tag & 1) == 0)
                  {
                      urender_DrawTextureF(SpritesData[sprFlame].Texture, 2 /(float) ((Gear->Tag % 3) + 2), x, y, ((RealTicks >> 7) + ((LongWord)Gear->Tag)) % 8, 1, 16, 16);
                  }
                  else
                  {
                      urender_DrawTextureF(SpritesData[sprFlame].Texture, 2 /(float) ((Gear->Tag % 3) + 2), x, y, ((RealTicks >> 7) + ((LongWord)Gear->Tag)) % 8, -1, 16, 16);
                  }
                  break;
     case gtParachute:{
                          urender_DrawSprite_4(sprParachute, x - 24, y - 48, 0);
                      }
                      break;
     case gtAirAttack:{
                          urender_Tint_1(Gear->Tint);
                          urender_DrawSpriteRotatedF(sprAirplane, x, y, 0, Gear->Tag, 0);
                          urender_untint();
                          urender_DrawSpriteRotatedF(sprAirplane, x, y, 1, Gear->Tag, 0);
                          if(WorldEdge != weSea)
                          {
                              urender_DrawSpriteRotatedF(sprAirplane, x, y, 2, Gear->Tag, 0);
                          }
                          else
                          {
                              urender_DrawSpriteRotatedF(sprAirplane, x, y, 3, Gear->Tag, 0);
                          }
                      }
                      break;
     case gtAirBomb:urender_DrawSpriteRotated(sprAirBomb, x, y, 0, uutils_DxDy2Angle(Gear->dY, Gear->dX));
                    break;
     case gtTeleport:{
                         HHGear = (*Gear->Hedgehog).Gear;
                         if(HHGear != NULL)
                         {
                             if((Gear->State & gstAnimation) != 0)
                             {
                                 urender_DrawSpriteRotatedF(sprTeleport, x + 1, y - 3, Gear->Pos, ufloat_hwSign(Gear->dX), 0);
                             }
                             urender_DrawSpriteRotatedF(sprTeleport, (ufloat_hwRound(HHGear->X) + 1) + WorldDx, (ufloat_hwRound(HHGear->Y) - 3) + WorldDy, 11 - Gear->Pos, ufloat_hwSign(HHGear->dX), 0);
                         }
                     }
                     break;
     case gtSwitcher:{
                         urender_setTintAdd(true);
                         if(urenderutils_IsTooDarkToRead((*(*(*Gear->Hedgehog).Team).Clan).Color))
                         {
                             urender_Tint_1(0xffffffff);
                         }
                         else
                         {
                             urender_Tint_1(0x000000ff);
                         }
                         ty = y - SpritesData[sprSwitch].Height;
                         if(bShowFinger)
                         {
                             if((cTagsMask & htTeamName) != 0)
                             {
                                 ty = (ty - (*(*(*Gear->Hedgehog).Team).NameTagTex).h) - 2;
                             }
                             if((cTagsMask & htName) != 0)
                             {
                                 ty = (ty - (*(*Gear->Hedgehog).NameTagTex).h) - 2;
                             }
                             if((cTagsMask & htHealth) != 0)
                             {
                                 ty = (ty - (*(*Gear->Hedgehog).HealthTagTex).h) - 2;
                             }
                             if((cTagsMask & ((htTeamName | htName) | htHealth)) != 0)
                             {
                                 ty = ty - 4;
                             }
                         }
                         urender_DrawSpriteRotatedF(sprSwitch, x + 1, ty, 1, 0, (RealTicks / 5) % 360);
                         urender_Tint_1(((*(*(*Gear->Hedgehog).Team).Clan).Color << 8) | 0xff);
                         urender_DrawSpriteRotatedF(sprSwitch, x + 1, ty, 0, 0, (RealTicks / 5) % 360);
                         urender_untint();
                         urender_setTintAdd(false);
                     }
                     break;
     case gtTarget:{
                       urender_Tint_4(0xff, 0xff, 0xff, fpcrtl_round((0xff * Gear->Timer) /(float) 1000));
                       urender_DrawSprite_4(sprTarget, x - 16, y - 16, 0);
                       urender_untint();
                   }
                   break;
     case gtMortar:urender_DrawSpriteRotated(sprMortar, x, y, 0, uutils_DxDy2Angle(Gear->dY, Gear->dX));
                   break;
     case gtCake:if(Gear->Pos == 6)
                 {
                     urender_DrawSpriteRotatedF(sprCakeWalk, x, y, (GameTicks / 40) % 6, ufloat_hwSign(Gear->dX), (Gear->DirAngle * ufloat_hwSign(Gear->dX)) + 90);
                 }
                 else
                 {
                     urender_DrawSpriteRotatedF(sprCakeDown, x, y, 5 - Gear->Pos, ufloat_hwSign(Gear->dX), (Gear->DirAngle * ufloat_hwSign(Gear->dX)) + 90);
                 }
                 break;
     case gtSeduction:if(Gear->Pos >= 14)
                      {
                          urender_DrawSprite_4(sprSeduction, x - 16, y - 16, 0);
                      }
                      break;
     case gtWatermelon:urender_DrawSpriteRotatedF(sprWatermelon, x, y, 0, 0, Gear->DirAngle);
                       break;
     case gtMelonPiece:urender_DrawSpriteRotatedF(sprWatermelon, x, y, 1, 0, Gear->DirAngle);
                       break;
     case gtHellishBomb:urender_DrawSpriteRotated(sprHellishBomb, x, y, 0, Gear->DirAngle);
                        break;
     case gtBirdy:{
                      if((Gear->State & gstAnimation) == gstAnimation)
                      {
                          if((Gear->State & gsttmpFlag) == 0)
                          {
                              endX = x - WorldDx;
                              endY = y - WorldDy;
                              if(Gear->Tag < 0)
                              {
                                  startX = uutils_Max(uutils_Max(LAND_WIDTH, 4096) + 1024, endX + 2048);
                              }
                              else
                              {
                                  startX = uutils_Max(-uutils_Max(LAND_WIDTH, 4096) - 1024, endX - 2048);
                              }
                              startY = endY - 1024;
                              urender_DrawTextureF(SpritesData[sprBirdy].Texture, uutils_Min(Gear->Timer /(float) 750, 1), (startX + WorldDx) + ((LongInt)fpcrtl_round((endX - startX) * (-fpcrtl_power(2, (-10 * ((LongInt)Gear->Timer)) /(float) 2000) + 1))), (startY + WorldDy) + ((LongInt)fpcrtl_round((endY - startY) * sqrt(1 - fpcrtl_power((((LongInt)Gear->Timer) /(float) 2000) - 1, 2)))), ((Gear->Pos >> 6) | (RealTicks >> 8)) % 2, Gear->Tag, 75, 75);
                          }
                          else
                          {
                              startX = x - WorldDx;
                              startY = y - WorldDy;
                              if(Gear->Tag > 0)
                              {
                                  endX = uutils_Max(uutils_Max(LAND_WIDTH, 4096) + 1024, startX + 2048);
                              }
                              else
                              {
                                  endX = uutils_Max(-uutils_Max(LAND_WIDTH, 4096) - 1024, startX - 2048);
                              }
                              endY = startY + 1024;
                              urender_DrawTextureF(SpritesData[sprBirdy].Texture, uutils_Min((2000 - Gear->Timer) /(float) 750, 1), ((startX + WorldDx) + ((LongInt)fpcrtl_round((endX - startX) * fpcrtl_power(2, 10 * ((((LongInt)Gear->Timer) /(float) 2000) - 1))))) + ufloat_hwRound(ufloat_hwFloat_LongInt_op_mul(Gear->dX, Gear->Timer)), ((startY + WorldDy) + ((LongInt)fpcrtl_round(((endY - startY) * cos((((LongInt)Gear->Timer) /(float) 2000) * (pi /(float) 2))) - (endY - startY)))) + ufloat_hwRound(ufloat_hwFloat_LongInt_op_mul(Gear->dY, Gear->Timer)), ((Gear->Pos >> 6) | (RealTicks >> 8)) % 2, Gear->Tag, 75, 75);
                          }
                      }
                      else
                      {
                          if(Gear->Health < 250)
                          {
                              urender_DrawTextureF(SpritesData[sprBirdy].Texture, 1, x, y, ((Gear->Pos >> 6) | (RealTicks >> 7)) % 2, Gear->Tag, 75, 75);
                          }
                          else
                          {
                              urender_DrawTextureF(SpritesData[sprBirdy].Texture, 1, x, y, ((Gear->Pos >> 6) | (RealTicks >> 8)) % 2, Gear->Tag, 75, 75);
                          }
                      }
                  }
                  break;
     case gtEgg:urender_DrawTextureRotatedF(SpritesData[sprEgg].Texture, 1, 0, 0, x, y, 0, 1, 16, 16, Gear->DirAngle);
                break;
     case gtPiano:{
                      if((Gear->State & gstDrowning) == 0)
                      {
                          urender_Tint_4(0xff, 0xff, 0xff, 0x10);
                          {i = 8;
                           LongWord i__end__ = 1;
                           if (i >= i__end__) do {
                                                     urender_DrawTextureF(SpritesData[sprPiano].Texture, 1, x, y - ufloat_hwRound(ufloat_hwFloat_LongInt_op_mul(ufloat_hwFloat_LongInt_op_mul(Gear->dY, 4), i)), 0, 1, 128, 128);
                                                 } while(i-- != i__end__);}
                          urender_untint();
                      }
                      urender_DrawTextureF(SpritesData[sprPiano].Texture, 1, x, y, 0, 1, 128, 128);
                  }
                  break;
     case gtPoisonCloud:{
                            if(Gear->Timer < 1020)
                            {
                                urender_Tint_1((Gear->Tint & 0xffffff00) | (Gear->Timer / 8));
                            }
                            else
                            {
                                if((Gear->Timer > (Gear->WDTimer - 1020)) && (Gear->WDTimer > 2040))
                                {
                                    urender_Tint_1((Gear->Tint & 0xffffff00) | ((((int64_t) (Gear->WDTimer)) - ((int64_t) (Gear->Timer))) / 8));
                                }
                                else
                                {
                                    urender_Tint_1(Gear->Tint);
                                }
                            }
                            urender_DrawTextureRotatedF(SpritesData[sprSmokeWhite].Texture, 3, 0, 0, x, y, 0, 1, 22, 22, ((RealTicks >> 4) + (Gear->uid * 100)) % 360);
                            urender_untint();
                        }
                        break;
     case gtResurrector:{
                            urender_DrawSpriteRotated(sprCross, x, y, 0, 0);
                            urender_Tint_1((Gear->Tint & 0xffffff00) | uutils_Max(0x00, fpcrtl_round(0xc0 * fpcrtl_abs(1 - ((GameTicks % 6000) /(float) 3000)))));
                            urender_DrawTexture_4(x - 108, y - 108, SpritesData[sprVampiric].Texture, 4.5);
                            urender_untint();
                        }
                        break;
     case gtNapalmBomb:urender_DrawSpriteRotated(sprNapalmBomb, x, y, 0, uutils_DxDy2Angle(Gear->dY, Gear->dX));
                       break;
     case gtFlake:if((Gear->State & (gstDrowning | gsttmpFlag)) != 0)
                  {
                      urender_Tint_1(Gear->Tint);
                      urender_DrawTextureRotatedF(SpritesData[sprSnowDust].Texture, 1, 0, 0, x, y, 0, 1, 8, 8, Gear->DirAngle);
                      urender_untint();
                  }
                  else
                  {
                      if(isInLag && (Gear->FlightTime < 256))
                      {
                          Gear->FlightTime += 8;
                      }
                      else
                      {
                          if(!isInLag && (Gear->FlightTime > 0))
                          {
                              Gear->FlightTime -= 8;
                          }
                      }
                      if(Gear->FlightTime > 0)
                      {
                          urender_Tint_4(0xff, 0xff, 0xff, 0xff - uutils_Min(255, Gear->FlightTime));
                      }
                      if(vobVelocity == 0)
                      {
                          urender_DrawSprite_4(sprFlake, x, y, Gear->Timer);
                      }
                      else
                      {
                          urender_DrawSpriteRotatedF(sprFlake, x, y, Gear->Timer, 1, Gear->DirAngle);
                      }
                      if(Gear->FlightTime > 0)
                      {
                          urender_untint();
                      }
                  }
                  break;
     case gtTardis:if(Gear->Pos != 4)
                   {
                       if(Gear->Pos == 2)
                       {
                           urender_Tint_1(((*(*(*Gear->Hedgehog).Team).Clan).Color << 8) | 0xff);
                       }
                       else
                       {
                           urender_Tint_1(((*(*(*Gear->Hedgehog).Team).Clan).Color << 8) | uutils_Max(0x00, fpcrtl_round(Gear->Power * (1 - fpcrtl_abs(0.5 - ((GameTicks % 2000) /(float) 2000))))));
                       }
                       urender_DrawSprite_4(sprTardis, x - 25, y - 64, 0);
                       if(Gear->Pos == 2)
                       {
                           urender_untint();
                       }
                       else
                       {
                           urender_Tint_4(0xff, 0xff, 0xff, uutils_Max(0x00, fpcrtl_round(Gear->Power * (1 - fpcrtl_abs(0.5 - ((GameTicks % 2000) /(float) 2000))))));
                       }
                       urender_DrawSprite_4(sprTardis, x - 25, y - 64, 1);
                       if(Gear->Pos != 2)
                       {
                           urender_untint();
                       }
                   }
                   break;
     case gtIceGun:{
                       HHGear = (*Gear->Hedgehog).Gear;
                       if(HHGear != NULL)
                       {
                           i = ufloat_hwRound(ufloat_hwFloat_hwFloat_op_add(ufloat_hwSqr(ufloat_hwFloat_hwFloat_op_sub(Gear->X, HHGear->X)), ufloat_hwSqr(ufloat_hwFloat_hwFloat_op_sub(Gear->Y, HHGear->Y))));
                           if((RealTicks % uutils_Max(1, 50 - (fpcrtl_round(sqrt(i)) / 4))) == 0)
                           {
                               vg = uvisualgearslist_AddVisualGear_4(ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), vgtDust, 1);
                               if(vg != NULL)
                               {
                                   i = fpcrtl_random(100) + 155;
                                   vg->Tint = (((i << 24) | (i << 16)) | (0xff << 8)) | ((LongWord)fpcrtl_random(200) + 55);
                                   vg->Angle = fpcrtl_random(360);
                                   vg->dX = 1.0e-3 * fpcrtl_random(80);
                                   vg->dY = 1.0e-3 * fpcrtl_random(80);
                               }
                           }
                           if((RealTicks % 2) == 0)
                           {
                               i = fpcrtl_random(100) + 100;
                               if(Gear->Target.x != NoPointX)
                               {
                                   urender_DrawLineWrapped_11(ufloat_hwRound(HHGear->X), ufloat_hwRound(HHGear->Y), Gear->Target.x, Gear->Target.y, 4.0, ufloat_hwSign(HHGear->dX) < 0, Gear->FlightTime, i, i, 0xff, 0x40);
                               }
                               else
                               {
                                   urender_DrawLineWrapped_11(ufloat_hwRound(HHGear->X), ufloat_hwRound(HHGear->Y), ufloat_hwRound(Gear->X), ufloat_hwRound(Gear->Y), 4.0, ufloat_hwSign(HHGear->dX) < 0, Gear->FlightTime, i, i, 0xff, 0x40);
                               }
                           }
                       }
                   }
                   break;
     case gtCreeper:if((Gear->Hedgehog != NULL) && ((*Gear->Hedgehog).Gear != NULL))
                    {
                        urender_DrawSpriteRotatedF(sprCreeper, x, y, 1, ufloat_hwRound(ufloat_SignAs(_1, ufloat_hwFloat_hwFloat_op_sub((*(*Gear->Hedgehog).Gear).X, Gear->X))), 0);
                    }
                    else
                    {
                        urender_DrawSpriteRotatedF(sprCreeper, x, y, 1, ufloat_hwRound(ufloat_SignAs(_1, Gear->dX)), 0);
                    }
                    break;
     case gtSentry:{
                       urender_DrawSpriteRotated(sprSentry, x, y, ufloat_hwSign(Gear->dX), 0);
                       if(Gear->Hedgehog != NULL)
                       {
                           urender_DrawCircle_5(x, y, Gear->Radius, 2, ((*(*(*Gear->Hedgehog).Team).Clan).Color << 8) | 0xff);
                       }
                   }
                   break;
     case gtGenericFaller:{
                              if(Gear->Tag != 0)
                              {
                                  urender_DrawCircle_8(x, y, uutils_Max(3, Gear->Radius), 3, 0xff, 0x00, 0x00, 0xff);
                              }
                              else
                              {
                                  urender_DrawCircle_8(x, y, uutils_Max(3, Gear->Radius), 3, 0x80, 0xff, 0x80, 0x8f);
                              }
                          }
                          break;
     default: break;}
    if((Gear->State & gstFrozen) != 0)
    {
        urender_untint();
    }
};
void ugearsrender_RenderGearTimer(PGear Gear,LongInt x,LongInt y)
{
    if((Gear->RenderTimer && (Gear->Tex != NULL)) && (isShowGearInfo || !(((Gear->Kind == gtMine) || (Gear->Kind == gtSMine) || (Gear->Kind == gtAirMine)))))
    {
        urender_DrawTextureCentered(x + 8, y + 8, Gear->Tex);
    }
};
void ugearsrender_RenderGearHealth(PGear Gear,LongInt x,LongInt y)
{
    if((isShowGearInfo && Gear->RenderHealth) && (Gear->Tex != NULL))
    {
        if((Gear->Kind == gtCase) && ((Gear->Pos & posCaseHealth) != 0))
        {
            urender_DrawTextureCentered(x, y - 38, Gear->Tex);
        }
        if(Gear->Kind == gtExplosives)
        {
            urender_DrawTextureCentered(x, y - 38, Gear->Tex);
        }
    }
};
