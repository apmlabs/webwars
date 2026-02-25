#pragma once

#include "pas2c.h"

#include "uFloat.h"
#include "uTypes.h"
enum{MAXACTIONS = 96};
enum{aia_none = 0};
enum{aia_Left = 1};
enum{aia_Right = 2};
enum{aia_Timer = 3};
enum{aia_attack = 4};
enum{aia_Up = 5};
enum{aia_Down = 6};
enum{aia_Switch = 7};
enum{aia_Precise = 8};
enum{aia_Weapon = 0x8000};
enum{aia_WaitXL = 0x8001};
enum{aia_WaitXR = 0x8002};
enum{aia_LookLeft = 0x8003};
enum{aia_LookRight = 0x8004};
enum{aia_AwareExpl = 0x8005};
enum{aia_HJump = 0x8006};
enum{aia_LJump = 0x8007};
enum{aia_Skip = 0x8008};
enum{aia_Wait = 0x8009};
enum{aia_Put = 0x800a};
enum{aia_waitAngle = 0x800b};
enum{aia_waitAmmoXY = 0x800c};
enum{aim_push = 0x8000};
enum{aim_release = 0x8001};
enum{ai_specmask = 0x8000};
typedef struct __TAction {
            LongWord Action;
            LongInt X;
            LongInt Y;
            LongInt Param;
            LongWord Time;
        } TAction;
typedef struct __TActions {
            LongWord Count;
            LongWord Pos;
            LongWord ticks;
            TAction actions[MAXACTIONS];
            LongInt Score;
            boolean isWalkingToABetterPlace;
        } TActions;
void uaiactions_AddAction(TActions (*Actions),LongWord Action,LongInt Param,LongWord TimeDelta,LongInt X,LongInt Y);
void uaiactions_ProcessAction(TActions (*Actions),PGear Me);

