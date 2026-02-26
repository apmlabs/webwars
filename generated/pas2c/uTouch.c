#include "fpcrtl.h"

#include "uTouch.h"
static const string255 __str20 = STRINIT("-precise");
static const string255 __str19 = STRINIT(" not found");
static const string255 __str18 = STRINIT("finger ");
static const string255 __str17 = STRINIT("hjump");
static const string255 __str16 = STRINIT("ljump");
static const string255 __str15 = STRINIT("switch");
static const string255 __str14 = STRINIT("put");
static const string255 __str13 = STRINIT("-attack");
static const string255 __str12 = STRINIT("-right");
static const string255 __str11 = STRINIT("-left");
static const string255 __str10 = STRINIT("-down");
static const string255 __str9 = STRINIT("-up");
static const string255 __str8 = STRINIT("timer ");
static const string255 __str7 = STRINIT("+precise");
static const string255 __str6 = STRINIT("/timer ");
static const string255 __str5 = STRINIT("pause");
static const string255 __str4 = STRINIT("+down");
static const string255 __str3 = STRINIT("+up");
static const string255 __str2 = STRINIT("+right");
static const string255 __str1 = STRINIT("+left");
static const string255 __str0 = STRINIT("+attack");
enum{clickTime = 200};
enum{kNoFinger = 9223372036854775807};
enum{baseRectSize = 96};
enum{maxFingers = 16};
static LongInt rectSize;
static LongInt halfRectSize;
static LongWord pointerCount;
typedef TTouch_Data fingers_tt[maxFingers];
static fingers_tt fingers;
static boolean moveCursor;
static boolean invertCursor;
static LongInt pinchSize;
static GLfloat baseZoomValue;
static boolean aimingCrosshair;
static boolean aimingUp;
static boolean aimingDown;
static LongInt targetAngle;
static LongWord buttonsDown;
static boolean targetting;
static boolean targetted;
void utouch_onTouchDown(single x,single y,Int64 pointerId)
{
    PTouch_Data finger;
    LongWord xr;
    LongWord yr;
    LongWord tmp;
    xr = fpcrtl_round(x * cScreenWidth);
    yr = fpcrtl_round(y * cScreenHeight);
    finger = utouch_addFinger(xr, yr, pointerId);
    ++buttonsDown;
    if(utouch_isOnCrosshair((*finger)))
    {
        aimingCrosshair = true;
        utouch_aim((*finger));
        moveCursor = false;
        return;
    }
    if(utouch_isOnWidget(firebutton, (*finger)))
    {
        ucommands_ParseTeamCommand(__str0);
        moveCursor = false;
        finger->pressedWidget = &(firebutton);
        return;
    }
    if(utouch_isOnWidget(arrowLeft, (*finger)))
    {
        ucommands_ParseTeamCommand(__str1);
        moveCursor = false;
        finger->pressedWidget = &(arrowLeft);
        return;
    }
    if(utouch_isOnWidget(arrowRight, (*finger)))
    {
        ucommands_ParseTeamCommand(__str2);
        moveCursor = false;
        finger->pressedWidget = &(arrowRight);
        return;
    }
    if(utouch_isOnWidget(arrowUp, (*finger)))
    {
        ucommands_ParseTeamCommand(__str3);
        aimingUp = true;
        moveCursor = false;
        finger->pressedWidget = &(arrowUp);
        return;
    }
    if(utouch_isOnWidget(arrowDown, (*finger)))
    {
        ucommands_ParseTeamCommand(__str4);
        aimingDown = true;
        moveCursor = false;
        finger->pressedWidget = &(arrowDown);
        return;
    }
    if(utouch_isOnWidget(pauseButton, (*finger)))
    {
        ucommands_ParseTeamCommand(__str5);
        moveCursor = false;
        finger->pressedWidget = &(pauseButton);
        return;
    }
    if(utouch_isOnWidget(utilityWidget, (*finger)))
    {
        finger->pressedWidget = &(utilityWidget);
        moveCursor = false;
        if(CurrentHedgehog != NULL)
        {
            if((Ammoz[CurrentHedgehog->CurAmmoType].Ammo.Propz & ammoprop_Timerable) != 0)
            {
                tmp = ugearshedgehog_HHGetTimerMsg(CurrentHedgehog->Gear);
                if(tmp != MSGPARAM_INVALID)
                {
                    ucommands_ParseTeamCommand(_strconcat(__str6, uutils_IntToStr((tmp % 5) + 1)));
                }
            }
        }
        return;
    }
    if(utouch_isOnWidget(utilityWidget2, (*finger)))
    {
        finger->pressedWidget = &(utilityWidget2);
        moveCursor = false;
        if(CurrentHedgehog != NULL)
        {
            if((Ammoz[CurrentHedgehog->CurAmmoType].Ammo.Propz & ammoprop_SetBounce) != 0)
            {
                tmp = ugearshedgehog_HHGetBouncinessMsg(CurrentHedgehog->Gear);
                if(tmp != MSGPARAM_INVALID)
                {
                    ucommands_ParseTeamCommand(__str7);
                    ucommands_ParseTeamCommand(_strconcat(__str8, uutils_IntToStr((tmp % 5) + 1)));
                    bounceButtonPressed = true;
                }
            }
        }
        return;
    }
    --buttonsDown;
    if(buttonsDown == 0)
    {
        moveCursor = true;
        switch(pointerCount)
        {case 1:targetting = (!targetted && (CurrentHedgehog != NULL)) && ((Ammoz[CurrentHedgehog->CurAmmoType].Ammo.Propz & ammoprop_NeedTarget) != 0);
                break;
         case 2:{
                    moveCursor = false;
                    pinchSize = utouch_calculateDelta((*finger), (*utouch_getSecondFinger((*finger))));
                    baseZoomValue = ZoomValue;
                }
                break;
         default: break;}
    }
};
void utouch_onTouchMotion(single x,single y,single dx,single dy,Int64 pointerId)
{
    PTouch_Data finger;
    PTouch_Data secondFinger;
    single currentPinchDelta;
    single zoom;
    LongWord xr;
    LongWord yr;
    LongWord dxr;
    LongWord dyr;
    xr = fpcrtl_round(x * cScreenWidth);
    yr = fpcrtl_round(y * cScreenHeight);
    dxr = fpcrtl_round(dx * cScreenWidth);
    dyr = fpcrtl_round(dy * cScreenHeight);
    finger = utouch_updateFinger(xr, yr, dxr, dyr, pointerId);
    if(finger == NULL)
    {
        return;
    }
    if(moveCursor)
    {
        if(invertCursor)
        {
            CursorPoint.x = CursorPoint.x - finger->dx;
            CursorPoint.y = CursorPoint.y + finger->dy;
        }
        else
        {
            CursorPoint.x = CursorPoint.x + finger->dx;
            CursorPoint.y = CursorPoint.y - finger->dy;
        }
        return;
    }
    if(aimingCrosshair)
    {
        utouch_aim((*finger));
        return;
    }
    if((buttonsDown == 0) && (pointerCount == 2))
    {
        secondFinger = utouch_getSecondFinger((*finger));
        currentPinchDelta = utouch_calculateDelta((*finger), (*secondFinger)) - pinchSize;
        zoom = currentPinchDelta /(float) cScreenWidth;
        ZoomValue = baseZoomValue - (zoom * cMinMaxZoomLevelDelta);
        if(ZoomValue < cMaxZoomLevel)
        {
            ZoomValue = cMaxZoomLevel;
        }
        if(ZoomValue > cMinZoomLevel)
        {
            ZoomValue = cMinZoomLevel;
        }
    }
};
void utouch_onTouchUp(single x,single y,Int64 pointerId)
{
    PTouch_Data finger;
    POnScreenWidget widget;
    LongWord xr;
    LongWord yr;
    xr = fpcrtl_round(x * cScreenWidth);
    yr = fpcrtl_round(y * cScreenHeight);
    finger = utouch_updateFinger(xr, yr, 0, 0, pointerId);
    if(finger == NULL)
    {
        return;
    }
    if(!utouch_fingerHasMoved((*finger)))
    {
        if((((int64_t) (RealTicks)) - ((int64_t) (finger->timeSinceDown))) < clickTime)
        {
            utouch_onTouchClick((*finger));
        }
        else
        {
            utouch_onTouchLongClick((*finger));
        }
    }
    if(aimingCrosshair)
    {
        aimingCrosshair = false;
        ucommands_ParseTeamCommand(__str9);
        ucommands_ParseTeamCommand(__str10);
        --buttonsDown;
    }
    widget = finger->pressedWidget;
    if((buttonsDown > 0) && (widget != NULL))
    {
        --buttonsDown;
        if(widget == &(arrowLeft))
        {
            ucommands_ParseTeamCommand(__str11);
        }
        if(widget == &(arrowRight))
        {
            ucommands_ParseTeamCommand(__str12);
        }
        if(widget == &(arrowUp))
        {
            ucommands_ParseTeamCommand(__str9);
        }
        if(widget == &(arrowDown))
        {
            ucommands_ParseTeamCommand(__str10);
        }
        if(widget == &(firebutton))
        {
            ucommands_ParseTeamCommand(__str13);
        }
        if(widget == &(utilityWidget))
        {
            if(CurrentHedgehog != NULL)
            {
                if((Ammoz[CurrentHedgehog->CurAmmoType].Ammo.Propz & ammoprop_NeedTarget) != 0)
                {
                    ucommands_ParseTeamCommand(__str14);
                    targetted = true;
                }
                else
                {
                    if((CurAmmoGear != NULL) && (CurAmmoGear->AmmoType == amSwitch))
                    {
                        ucommands_ParseTeamCommand(__str15);
                    }
                    else
                    {
                        uconsole_WriteLnToConsole(_strconcat(_strappend(uutils_IntToStr((Ammoz[CurrentHedgehog->CurAmmoType].NameId)), 0x20), uutils_IntToStr((sidSwitch))));
                    }
                }
            }
        }
    }
    if(targetting)
    {
        ucaptions_AddCaption(trmsg[sidPressTarget], capcolDefault, capgrpAmmoinfo);
    }
    utouch_deleteFinger(pointerId);
};
void utouch_onTouchDoubleClick(TTouch_Data finger)
{
    UNUSED (finger);
};
void utouch_onTouchLongClick(TTouch_Data finger)
{
    if(utouch_isOnWidget(jumpWidget, finger))
    {
        ucommands_ParseTeamCommand(__str16);
        return;
    }
};
void utouch_onTouchClick(TTouch_Data finger)
{
    if(bShowAmmoMenu)
    {
        if(utouch_isOnRect_2(AmmoRect, finger))
        {
            CursorPoint.x = finger.x;
            CursorPoint.y = finger.y;
            ucommands_ParseTeamCommand(__str14);
        }
        else
        {
            bShowAmmoMenu = false;
        }
        return;
    }
    if(utouch_isOnCurrentHog(finger) || utouch_isOnWidget(AMWidget, finger))
    {
        bShowAmmoMenu = true;
        return;
    }
    if(utouch_isOnWidget(jumpWidget, finger))
    {
        ucommands_ParseTeamCommand(__str17);
        return;
    }
};
PTouch_Data utouch_addFinger(LongWord x,LongWord y,Int64 id)
{
    PTouch_Data addfinger_result;
    LongInt xCursor;
    LongInt yCursor;
    LongInt index;
    if(pointerCount >= maxFingers)
    {
        return NULL;
    }
    xCursor = utouch_convertToCursorX(x);
    yCursor = utouch_convertToCursorY(y);
    fingers[pointerCount].id = id;
    fingers[pointerCount].historicalX = xCursor;
    fingers[pointerCount].historicalY = yCursor;
    fingers[pointerCount].x = xCursor;
    fingers[pointerCount].y = yCursor;
    fingers[pointerCount].dx = 0;
    fingers[pointerCount].dy = 0;
    fingers[pointerCount].timeSinceDown = RealTicks;
    fingers[pointerCount].pressedWidget = NULL;
    addfinger_result = &(fingers[pointerCount]);
    ++pointerCount;
    return addfinger_result;
};
PTouch_Data utouch_updateFinger(LongWord x,LongWord y,LongWord dx,LongWord dy,Int64 id)
{
    PTouch_Data updatefinger_result;
    PTouch_Data finger;
    finger = utouch_findFinger(id);
    if(finger != NULL)
    {
        finger->x = utouch_convertToCursorX(x);
        finger->y = utouch_convertToCursorY(y);
        finger->dx = dx;
        finger->dy = dy;
    }
    else
    {
        uconsole_WriteLnToConsole(_strconcat(_strconcat(__str18, uutils_IntToStr(id)), __str19));
    }
    updatefinger_result = finger;
    return updatefinger_result;
};
void utouch_deleteFinger(Int64 id)
{
    LongWord index;
    --pointerCount;
    {index = 0;
     LongWord index__end__ = pointerCount;
     if (index <= index__end__) do {
                                       if(fingers[index].id == id)
                                       {
                                           if(pointerCount != index)
                                           {
                                               fingers[index].id = fingers[pointerCount].id;
                                               fingers[index].x = fingers[pointerCount].x;
                                               fingers[index].y = fingers[pointerCount].y;
                                               fingers[index].historicalX = fingers[pointerCount].historicalX;
                                               fingers[index].historicalY = fingers[pointerCount].historicalY;
                                               fingers[index].timeSinceDown = fingers[pointerCount].timeSinceDown;
                                               fingers[index].pressedWidget = fingers[pointerCount].pressedWidget;
                                               fingers[pointerCount].id = kNoFinger;
                                           }
                                           else
                                           {
                                               fingers[index].id = kNoFinger;
                                           }
                                           break;
                                       }
                                   } while(index++ != index__end__);}
};
void utouch_NewTurnBeginning()
{
    targetted = false;
    targetting = false;
    uworld_SetUtilityWidgetState(amNothing);
};
void utouch_ProcessTouch()
{
    LongInt deltaAngle;
    invertCursor = !(bShowAmmoMenu || targetting);
    if(aimingCrosshair)
    {
        if(CurrentHedgehog->Gear != NULL)
        {
            deltaAngle = (*CurrentHedgehog->Gear).Angle - targetAngle;
            if((deltaAngle > -5) && (deltaAngle < 5))
            {
                if(aimingUp)
                {
                    aimingUp = false;
                    ucommands_ParseTeamCommand(__str9);
                }
                if(aimingDown)
                {
                    aimingDown = false;
                    ucommands_ParseTeamCommand(__str10);
                }
            }
            else
            {
                if(deltaAngle < 0)
                {
                    if(aimingUp)
                    {
                        aimingUp = false;
                        ucommands_ParseTeamCommand(__str9);
                    }
                    if(aimingDown)
                    {
                        aimingDown = true;
                        ucommands_ParseTeamCommand(__str10);
                    }
                }
                else
                {
                    if(aimingDown)
                    {
                        ucommands_ParseTeamCommand(__str10);
                        aimingDown = false;
                    }
                    if(aimingUp)
                    {
                        aimingUp = true;
                        ucommands_ParseTeamCommand(__str3);
                    }
                }
            }
        }
        else
        {
            if(aimingUp)
            {
                ucommands_ParseTeamCommand(__str9);
                aimingUp = false;
            }
            if(aimingDown)
            {
                ucommands_ParseTeamCommand(__str10);
                aimingDown = false;
            }
        }
    }
    if(bounceButtonPressed)
    {
        ucommands_ParseTeamCommand(__str20);
        bounceButtonPressed = false;
    }
};
PTouch_Data utouch_findFinger(Int64 id)
{
    PTouch_Data findfinger_result;
    LongWord index;
    {index = 0;
     LongWord index__end__ = maxFingers - 1;
     if (index <= index__end__) do {
                                       if(fingers[index].id == id)
                                       {
                                           findfinger_result = &(fingers[index]);
                                           return findfinger_result;
                                       }
                                   } while(index++ != index__end__);}
    findfinger_result = NULL;
    return findfinger_result;
};
void utouch_aim(TTouch_Data finger)
{
    LongInt hogX;
    LongInt hogY;
    LongInt touchX;
    LongInt touchY;
    LongInt deltaX;
    LongInt deltaY;
    if(CurrentHedgehog->Gear != NULL)
    {
        touchX = 0;
        touchY = 0;
        hogX = ufloat_hwRound((*CurrentHedgehog->Gear).X);
        hogY = ufloat_hwRound((*CurrentHedgehog->Gear).Y);
        utouch_convertToWorldCoord(&(touchX), &(touchY), finger);
        deltaX = fpcrtl_abs(touchX - hogX);
        deltaY = touchY - hogY;
        targetAngle = (fpcrtl_round((deltaY /(float) sqrt(fpcrtl_sqr(deltaX) + fpcrtl_sqr(deltaY))) * 2048) + 2048) / 2;
    }
};
LongInt utouch_convertToCursorX(LongInt x)
{
    LongInt converttocursorx_result;
    converttocursorx_result = x - (cScreenWidth >> 1);
    return converttocursorx_result;
};
LongInt utouch_convertToCursorY(LongInt y)
{
    LongInt converttocursory_result;
    converttocursory_result = cScreenHeight - y;
    return converttocursory_result;
};
boolean utouch_isOnCrosshair(TTouch_Data finger)
{
    boolean isoncrosshair_result;
    LongInt x;
    LongInt y;
    x = 0;
    y = 0;
    utouch_convertToFingerCoord(&(x), &(y), CrosshairX, CrosshairY);
    isoncrosshair_result = utouch_isOnRect_5(x - halfRectSize, y - halfRectSize, rectSize, rectSize, finger);
    return isoncrosshair_result;
};
boolean utouch_isOnCurrentHog(TTouch_Data finger)
{
    boolean isoncurrenthog_result;
    LongInt x;
    LongInt y;
    x = 0;
    y = 0;
    utouch_convertToFingerCoord(&(x), &(y), ufloat_hwRound((*CurrentHedgehog->Gear).X), ufloat_hwRound((*CurrentHedgehog->Gear).Y));
    isoncurrenthog_result = utouch_isOnRect_5(x - halfRectSize, y - halfRectSize, rectSize, rectSize, finger);
    return isoncurrenthog_result;
};
void utouch_convertToFingerCoord(LongInt (*x),LongInt (*y),LongInt oldX,LongInt oldY)
{
    (*x) = oldX + WorldDx;
    (*y) = (cScreenHeight - oldY) - WorldDy;
};
void utouch_convertToWorldCoord(LongInt (*x),LongInt (*y),TTouch_Data finger)
{
    (*x) = finger.x - WorldDx;
    (*y) = (cScreenHeight - finger.y) - WorldDy;
};
boolean utouch_fingerHasMoved(TTouch_Data finger)
{
    boolean fingerhasmoved_result;
    fingerhasmoved_result = fpcrtl_trunc(sqrt(fpcrtl_sqr(finger.x - finger.historicalX) + fpcrtl_sqr(finger.y - finger.historicalY))) > 30;
    return fingerhasmoved_result;
};
LongInt utouch_calculateDelta(TTouch_Data finger1,TTouch_Data finger2)
{
    LongInt calculatedelta_result;
    calculatedelta_result = fpcrtl_round(sqrt(fpcrtl_sqr(finger2.x - finger1.x) + fpcrtl_sqr(finger2.y - finger1.y)));
    return calculatedelta_result;
};
PTouch_Data utouch_getSecondFinger(TTouch_Data finger)
{
    PTouch_Data getsecondfinger_result;
    if(fingers[0].id == finger.id)
    {
        getsecondfinger_result = &(fingers[1]);
    }
    else
    {
        getsecondfinger_result = &(fingers[0]);
    }
    return getsecondfinger_result;
};
boolean utouch_isOnRect_2(TSDL_Rect rect,TTouch_Data finger)
{
    boolean isonrect_result;
    isonrect_result = utouch_isOnRect_5(rect.x, rect.y, rect.w, rect.h, finger);
    return isonrect_result;
};
boolean utouch_isOnRect_5(LongInt x,LongInt y,LongInt w,LongInt h,TTouch_Data finger)
{
    boolean isonrect_result;
    isonrect_result = (((finger.x > x) && (finger.x < (x + w))) && ((cScreenHeight - finger.y) > y)) && ((cScreenHeight - finger.y) < (y + h));
    return isonrect_result;
};
boolean utouch_isOnWidget(TOnScreenWidget widget,TTouch_Data finger)
{
    boolean isonwidget_result;
    isonwidget_result = widget.show && utouch_isOnRect_2(widget.active, finger);
    return isonwidget_result;
};
void utouch_printFinger(TTouch_Data finger)
{
    UNUSED (finger);
};
void utouch_initModule()
{
    LongWord index;
    buttonsDown = 0;
    pointerCount = 0;
    bounceButtonPressed = false;
    {index = 0;
     LongWord index__end__ = maxFingers - 1;
     if (index <= index__end__) do {
                                       fingers[index].id = kNoFinger;
                                   } while(index++ != index__end__);}
    rectSize = baseRectSize;
    halfRectSize = baseRectSize >> 1;
};
void utouch_freeModule()
{
};
