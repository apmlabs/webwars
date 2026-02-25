#include "fpcrtl.h"

#include "uAIActions.h"
#include "uAIMisc.h"
#include "uAI.h"
#include "uAmmos.h"
#include "uVariables.h"
#include "uCommands.h"
#include "uConsts.h"
#include "uUtils.h"
#include "uIO.h"
static const string255 __str6 = STRINIT("skip");
static const string255 __str5 = STRINIT("ljump");
static const string255 __str4 = STRINIT("hjump");
static const string255 __str3 = STRINIT("-right");
static const string255 __str2 = STRINIT("+right");
static const string255 __str1 = STRINIT("-left");
static const string255 __str0 = STRINIT("+left");
static LongInt PrevX = 0;
static LongWord timedelta = 0;
typedef string255 ActionIdToStr_tt[(8 + 1)];
static ActionIdToStr_tt ActionIdToStr = {STRINIT(""),
                                         STRINIT("left"),
                                         STRINIT("right"),
                                         STRINIT("timer"),
                                         STRINIT("attack"),
                                         STRINIT("up"),
                                         STRINIT("down"),
                                         STRINIT("switch"),
                                         STRINIT("precise")};
void uaiactions_AddAction(TActions (*Actions),LongWord Action,LongInt Param,LongWord TimeDelta,LongInt X,LongInt Y)
{
    LongWord t;
    if(((Action == aia_LookLeft) || (Action == aia_LookRight)) && ((*Actions).Count > 0))
    {
        t = (*Actions).actions[(*Actions).Count - 1].Action;
        if((t == aia_LookLeft) || (t == aia_LookRight))
        {
            --(*Actions).Count;
        }
    }
    if((*Actions).Count < MAXACTIONS)
    {
        {
            (*Actions).actions[(*Actions).Count].Action = Action;
            (*Actions).actions[(*Actions).Count].Param = Param;
            (*Actions).actions[(*Actions).Count].X = X;
            (*Actions).actions[(*Actions).Count].Y = Y;
            if((*Actions).Count > 0)
            {
                (*Actions).actions[(*Actions).Count].Time = TimeDelta;
            }
            else
            {
                (*Actions).actions[(*Actions).Count].Time = GameTicks + TimeDelta;
            }
            ++(*Actions).Count;
        }
    }
};
void uaiactions_CheckHang(PGear Me,boolean fromLeft)
{
    LongInt newX;
    newX = ufloat_hwRound(Me->X);
    if(newX != PrevX)
    {
        if((newX < PrevX) == fromLeft)
        {
            uai_FreeActionsList();
        }
        PrevX = newX;
        timedelta = 0;
    }
    else
    {
        ++timedelta;
        if(timedelta > 900)
        {
            timedelta = 0;
            uai_FreeActionsList();
        }
    }
};
void uaiactions_ProcessAction(TActions (*Actions),PGear Me)
{
    string255 s;
    do {
           if((*Actions).Pos >= (*Actions).Count)
           {
               return;
           }
           {
               if((*Actions).actions[(*Actions).Pos].Time > GameTicks)
               {
                   return;
               }
               if(((*Actions).actions[(*Actions).Pos].Action & ai_specmask) != 0)
               {
                   switch((*Actions).actions[(*Actions).Pos].Action)
                   {case aia_Weapon:uammos_SetWeapon(((TAmmoType)(*Actions).actions[(*Actions).Pos].Param));
                                    break;
                    case aia_WaitXL:if(ufloat_hwRound(Me->X) == (*Actions).actions[(*Actions).Pos].Param)
                                    {
                                        (*Actions).actions[(*Actions).Pos].Action = aia_LookLeft;
                                        (*Actions).actions[(*Actions).Pos].Time = GameTicks;
                                        return;
                                    }
                                    else
                                    {
                                        if(ufloat_hwRound(Me->X) < (*Actions).actions[(*Actions).Pos].Param)
                                        {
                                            uai_FreeActionsList();
                                            return;
                                        }
                                        else
                                        {
                                            uaiactions_CheckHang(Me, false);
                                            return;
                                        }
                                    }
                                    break;
                    case aia_WaitXR:if(ufloat_hwRound(Me->X) == (*Actions).actions[(*Actions).Pos].Param)
                                    {
                                        (*Actions).actions[(*Actions).Pos].Action = aia_LookRight;
                                        (*Actions).actions[(*Actions).Pos].Time = GameTicks;
                                        return;
                                    }
                                    else
                                    {
                                        if(ufloat_hwRound(Me->X) > (*Actions).actions[(*Actions).Pos].Param)
                                        {
                                            uai_FreeActionsList();
                                            return;
                                        }
                                        else
                                        {
                                            uaiactions_CheckHang(Me, true);
                                            return;
                                        }
                                    }
                                    break;
                    case aia_LookLeft:{
                                          if((Me->State & gstMoving) != 0)
                                          {
                                              return;
                                          }
                                          if(!Me->dX.isNegative)
                                          {
                                              if((Me->Message & gmLeft) == 0)
                                              {
                                                  ucommands_ParseCommand_2(__str0, true);
                                              }
                                              return;
                                          }
                                          else
                                          {
                                              ucommands_ParseCommand_2(__str1, true);
                                          }
                                      }
                                      break;
                    case aia_LookRight:{
                                           if((Me->State & gstMoving) != 0)
                                           {
                                               return;
                                           }
                                           if(Me->dX.isNegative)
                                           {
                                               if((Me->Message & gmRight) == 0)
                                               {
                                                   ucommands_ParseCommand_2(__str2, true);
                                               }
                                               return;
                                           }
                                           else
                                           {
                                               ucommands_ParseCommand_2(__str3, true);
                                           }
                                       }
                                       break;
                    case aia_AwareExpl:uaimisc_AwareOfExplosion((*Actions).actions[(*Actions).Pos].X, (*Actions).actions[(*Actions).Pos].Y, (*Actions).actions[(*Actions).Pos].Param);
                                       break;
                    case aia_HJump:ucommands_ParseCommand_2(__str4, true);
                                   break;
                    case aia_LJump:ucommands_ParseCommand_2(__str5, true);
                                   break;
                    case aia_Skip:ucommands_ParseCommand_2(__str6, true);
                                  break;
                    case aia_Put:uio_doPut((*Actions).actions[(*Actions).Pos].X, (*Actions).actions[(*Actions).Pos].Y, true);
                                 break;
                    case aia_waitAngle:if(((LongInt)Me->Angle) != fpcrtl_abs((*Actions).actions[(*Actions).Pos].Param))
                                       {
                                           return;
                                       }
                                       break;
                    case aia_waitAmmoXY:if((CurAmmoGear != NULL) && ((ufloat_hwRound(CurAmmoGear->X) != (*Actions).actions[(*Actions).Pos].X) || (ufloat_hwRound(CurAmmoGear->Y) != (*Actions).actions[(*Actions).Pos].Y)))
                                        {
                                            return;
                                        }
                                        break;
                    default: break;}
               }
               else
               {
                   s = ActionIdToStr[(*Actions).actions[(*Actions).Pos].Action];
                   if(((*Actions).actions[(*Actions).Pos].Param & ai_specmask) != 0)
                   {
                       switch((*Actions).actions[(*Actions).Pos].Param)
                       {case aim_push:s = _strprepend(0x2b, s);
                                      break;
                        case aim_release:s = _strprepend(0x2d, s);
                                         break;
                        default: break;}
                   }
                   else
                   {
                       if((*Actions).actions[(*Actions).Pos].Param != 0)
                       {
                           s = _strconcat(_strappend(s, 0x20), uutils_IntToStr((*Actions).actions[(*Actions).Pos].Param));
                       }
                   }
                   ucommands_ParseCommand_2(s, true);
               }
           }
           ++(*Actions).Pos;
           if((*Actions).Pos <= (*Actions).Count)
           {
               (*Actions).actions[(*Actions).Pos].Time += GameTicks;
           }
       } while(!(false));
};
