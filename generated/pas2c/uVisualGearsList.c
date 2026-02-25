#include "fpcrtl.h"

#include "uVisualGearsList.h"
LongWord VGCounter;
VisualGearLayersStart_tt VisualGearLayersStart;
VisualGearLayersEnd_tt VisualGearLayersEnd;
#include "uCollisions.h"
#include "uFloat.h"
#include "uVariables.h"
#include "uConsts.h"
#include "uTextures.h"
#include "uVisualGearsHandlers.h"
#include "uScript.h"
static const string255 __str1 = STRINIT("onVisualGearDelete");
static const string255 __str0 = STRINIT("onVisualGearAdd");
PVisualGear uvisualgearslist_AddVisualGear_3(LongInt X,LongInt Y,TVisualGearType Kind)
{
    PVisualGear addvisualgear_result;
    if(ucollisions_CheckCoordInWater(X, Y) && (((Kind == vgtBeeTrace) || (Kind == vgtSmokeTrace)) || (Kind == vgtEvilTrace)))
    {
        Kind = vgtBubble;
    }
    addvisualgear_result = uvisualgearslist_AddVisualGear_6(X, Y, Kind, 0, false, -1);
    return addvisualgear_result;
};
PVisualGear uvisualgearslist_AddVisualGear_4(LongInt X,LongInt Y,TVisualGearType Kind,LongWord State)
{
    PVisualGear addvisualgear_result;
    addvisualgear_result = uvisualgearslist_AddVisualGear_6(X, Y, Kind, State, false, -1);
    return addvisualgear_result;
};
PVisualGear uvisualgearslist_AddVisualGear_5(LongInt X,LongInt Y,TVisualGearType Kind,LongWord State,boolean Critical)
{
    PVisualGear addvisualgear_result;
    addvisualgear_result = uvisualgearslist_AddVisualGear_6(X, Y, Kind, State, Critical, -1);
    return addvisualgear_result;
};
PVisualGear uvisualgearslist_AddVisualGear_6(LongInt X,LongInt Y,TVisualGearType Kind,LongWord State,boolean Critical,LongInt Layer)
{
    PVisualGear addvisualgear_result;
    PVisualGear gear;
    LongWord t;
    real sp;
    addvisualgear_result = NULL;
    if(fastUntilLag && !Critical)
    {
        return addvisualgear_result;
    }
    if((GameType != gmtRecord) && ((((GameType == gmtSave) || (fastUntilLag && (GameType == gmtNet))) || fastScrolling) && !Critical))
    {
        return addvisualgear_result;
    }
    if((((cReducedQuality & rqAntiBoom) != 0) && !Critical) && !(((Kind == vgtTeamHealthSorter) || (Kind == vgtSmallDamageTag) || (Kind == vgtSpeechBubble) || (Kind == vgtHealthTag) || (Kind == vgtExplosion) || (Kind == vgtBigExplosion) || (Kind == vgtSmokeTrace) || (Kind == vgtEvilTrace) || (Kind == vgtNote) || (Kind == vgtFeather) || (Kind == vgtSmoothWindBar))))
    {
        return addvisualgear_result;
    }
    ++VGCounter;
    fpcrtl_new(gear);
    fpcrtl_FillChar((*gear), sizeof(TVisualGear), 0);
    gear->X = ((real)X);
    gear->Y = ((real)Y);
    gear->Kind = Kind;
    gear->doStep = doStepVGHandlers[Kind];
    gear->Tint = 0xffffffff;
    gear->uid = VGCounter;
    {
        switch((*gear).Kind)
        {case vgtFlake:{
                           (*gear).State = 0;
                           (*gear).Timer = 0;
                           (*gear).tdX = 0;
                           (*gear).tdY = 0;
                           (*gear).scale = 1.0;
                           if(SuddenDeathDmg)
                           {
                               if(vobSDFrameTicks > 0)
                               {
                                   (*gear).FrameTicks = fpcrtl_random(vobSDFrameTicks);
                               }
                               (*gear).Frame = fpcrtl_random(vobSDFramesCount);
                           }
                           else
                           {
                               if(vobFrameTicks > 0)
                               {
                                   (*gear).FrameTicks = fpcrtl_random(vobFrameTicks);
                               }
                               (*gear).Frame = fpcrtl_random(vobFramesCount);
                           }
                           (*gear).Angle = fpcrtl_random(360);
                           (*gear).dX = 3.8654705e-6 * fpcrtl_random(10000);
                           (*gear).dY = 3.506096e-6 * fpcrtl_random(7000);
                           if(fpcrtl_random(2) == 0)
                           {
                               (*gear).dX = -(*gear).dX;
                           }
                           if(SuddenDeathDmg)
                           {
                               (*gear).dAngle = (((fpcrtl_random(2) * 2) - 1) * (vobSDVelocity + fpcrtl_random(vobSDVelocity))) /(float) 1000;
                           }
                           else
                           {
                               (*gear).dAngle = (((fpcrtl_random(2) * 2) - 1) * (vobVelocity + fpcrtl_random(vobVelocity))) /(float) 1000;
                           }
                       }
                       break;
         case vgtCloud:{
                           (*gear).Frame = fpcrtl_random(4);
                           (*gear).dX = 0.5 + (0.1 * fpcrtl_random(5));
                           (*gear).Timer = fpcrtl_random(4096);
                           (*gear).scale = 1.0;
                       }
                       break;
         case vgtExplPart:
         case vgtExplPart2:{
                               t = fpcrtl_random(1024);
                               sp = 1.0e-3 * (fpcrtl_random(95) + 70);
                               (*gear).dX = ufloat_hwFloat2Float(ufloat_AngleSin(t)) * sp;
                               (*gear).dY = ufloat_hwFloat2Float(ufloat_AngleCos(t)) * sp;
                               if(fpcrtl_random(2) == 0)
                               {
                                   (*gear).dX = -(*gear).dX;
                               }
                               if(fpcrtl_random(2) == 0)
                               {
                                   (*gear).dY = -(*gear).dY;
                               }
                               (*gear).Frame = 7 - fpcrtl_random(3);
                               (*gear).FrameTicks = cExplFrameTicks;
                           }
                           break;
         case vgtFire:{
                          t = fpcrtl_random(1024);
                          sp = 1.0e-3 * (fpcrtl_random(85) + 95);
                          (*gear).dX = ufloat_hwFloat2Float(ufloat_AngleSin(t)) * sp;
                          (*gear).dY = ufloat_hwFloat2Float(ufloat_AngleCos(t)) * sp;
                          if(fpcrtl_random(2) == 0)
                          {
                              (*gear).dX = -(*gear).dX;
                          }
                          if(fpcrtl_random(2) == 0)
                          {
                              (*gear).dY = -(*gear).dY;
                          }
                          (*gear).FrameTicks = 650 + fpcrtl_random(250);
                          (*gear).Frame = fpcrtl_random(8);
                      }
                      break;
         case vgtEgg:{
                         t = fpcrtl_random(1024);
                         sp = 1.0e-3 * (fpcrtl_random(85) + 95);
                         (*gear).dX = ufloat_hwFloat2Float(ufloat_AngleSin(t)) * sp;
                         (*gear).dY = ufloat_hwFloat2Float(ufloat_AngleCos(t)) * sp;
                         if(fpcrtl_random(2) == 0)
                         {
                             (*gear).dX = -(*gear).dX;
                         }
                         if(fpcrtl_random(2) == 0)
                         {
                             (*gear).dY = -(*gear).dY;
                         }
                         (*gear).FrameTicks = 650 + fpcrtl_random(250);
                         (*gear).Frame = 1;
                     }
                     break;
         case vgtShell:(*gear).FrameTicks = 500;
                       break;
         case vgtSmallDamageTag:{
                                    gear->Frame = 0;
                                    gear->FrameTicks = 1100;
                                    gear->dX = 0;
                                    gear->dY = -2.0e-2;
                                }
                                break;
         case vgtBubble:{
                            (*gear).dX = 3.8654705e-6 * fpcrtl_random(10000);
                            (*gear).dY = 0;
                            if(fpcrtl_random(2) == 0)
                            {
                                (*gear).dX = -(*gear).dX;
                            }
                            (*gear).FrameTicks = 250 + fpcrtl_random(1751);
                            (*gear).Frame = fpcrtl_random(5);
                        }
                        break;
         case vgtSteam:{
                           (*gear).dX = 3.8654705e-6 * fpcrtl_random(10000);
                           (*gear).dY = 1.0e-3 * (fpcrtl_random(85) + 95);
                           if(fpcrtl_random(2) == 0)
                           {
                               (*gear).dX = -(*gear).dX;
                           }
                           (*gear).Frame = 7 - fpcrtl_random(3);
                           (*gear).FrameTicks = cExplFrameTicks * 2;
                       }
                       break;
         case vgtAmmo:{
                          (*gear).alpha = 1.0;
                          (*gear).scale = 1.0;
                      }
                      break;
         case vgtSmokeWhite:
         case vgtSmoke:{
                           (*gear).scale = 1.0;
                           (*gear).dX = 2.0e-4 * (fpcrtl_random(45) + 10);
                           (*gear).dY = 2.0e-4 * (fpcrtl_random(45) + 10);
                           if(fpcrtl_random(2) == 0)
                           {
                               (*gear).dX = -(*gear).dX;
                           }
                           (*gear).Frame = 7 - fpcrtl_random(2);
                           (*gear).FrameTicks = cExplFrameTicks * 2;
                       }
                       break;
         case vgtDust:{
                          (*gear).dX = 5.0e-3 * (fpcrtl_random(15) + 10);
                          (*gear).dY = 1.0e-3 * (fpcrtl_random(40) + 20);
                          if(fpcrtl_random(2) == 0)
                          {
                              (*gear).dX = -(*gear).dX;
                          }
                          if(fpcrtl_random(2) == 0)
                          {
                              (*gear).Tag = 1;
                          }
                          else
                          {
                              (*gear).Tag = -1;
                          }
                          (*gear).Frame = 7 - fpcrtl_random(2);
                          (*gear).FrameTicks = fpcrtl_random(20) + 15;
                      }
                      break;
         case vgtSplash:{
                            (*gear).dX = 0;
                            (*gear).dY = 0;
                            (*gear).FrameTicks = 740;
                            (*gear).Frame = 19;
                            (*gear).scale = 0.75;
                            (*gear).Timer = 1;
                        }
                        break;
         case vgtDroplet:{
                             (*gear).dX = 1.0e-3 * (98 + fpcrtl_random(121));
                             (*gear).Frame = 129 + fpcrtl_random(1791);
                             (*gear).dY = -(*gear).dX * ufloat_hwFloat2Float(ufloat_AngleSin((*gear).Frame));
                             (*gear).dX = ((*gear).dX * ufloat_hwFloat2Float(ufloat_AngleCos((*gear).Frame))) /(float) 2;
                             (*gear).FrameTicks = 250 + fpcrtl_random(1751);
                             (*gear).Frame = fpcrtl_random(3);
                         }
                         break;
         case vgtBeeTrace:{
                              (*gear).FrameTicks = 1000;
                              (*gear).Frame = fpcrtl_random(16);
                          }
                          break;
         case vgtSmokeRing:{
                               (*gear).dX = 0;
                               (*gear).dY = 0;
                               (*gear).FrameTicks = 600;
                               (*gear).Timer = 0;
                               (*gear).Frame = 0;
                               (*gear).scale = 0.6;
                               (*gear).alpha = 1;
                               (*gear).Angle = fpcrtl_random(360);
                           }
                           break;
         case vgtFeather:{
                             t = fpcrtl_random(1024);
                             sp = 1.0e-3 * (fpcrtl_random(85) + 95);
                             (*gear).dX = ufloat_hwFloat2Float(ufloat_AngleSin(t)) * sp;
                             (*gear).dY = ufloat_hwFloat2Float(ufloat_AngleCos(t)) * sp;
                             if(fpcrtl_random(2) == 0)
                             {
                                 (*gear).dX = -(*gear).dX;
                             }
                             if(fpcrtl_random(2) == 0)
                             {
                                 (*gear).dY = -(*gear).dY;
                             }
                             (*gear).FrameTicks = 650 + fpcrtl_random(250);
                             (*gear).Frame = 1;
                         }
                         break;
         case vgtHealthTag:{
                               (*gear).Frame = 0;
                               (*gear).FrameTicks = 0;
                               (*gear).Timer = 1500;
                               (*gear).dY = -8.0e-2;
                               (*gear).dX = 0;
                           }
                           break;
         case vgtSmokeTrace:
         case vgtEvilTrace:{
                               gear->X = gear->X - 16;
                               gear->Y = gear->Y - 16;
                               gear->State = 8;
                           }
                           break;
         case vgtBigExplosion:{
                                  gear->Angle = fpcrtl_random(360);
                              }
                              break;
         case vgtChunk:{
                           gear->Frame = fpcrtl_random(4);
                           t = fpcrtl_random(1024);
                           sp = 1.0e-3 * (fpcrtl_random(85) + 47);
                           (*gear).dX = ufloat_hwFloat2Float(ufloat_AngleSin(t)) * sp;
                           (*gear).dY = (ufloat_hwFloat2Float(ufloat_AngleCos(t)) * sp) * -2;
                           if(fpcrtl_random(2) == 0)
                           {
                               (*gear).dX = -(*gear).dX;
                           }
                       }
                       break;
         case vgtNote:{
                          (*gear).dX = 5.0e-3 * (fpcrtl_random(15) + 10);
                          (*gear).dY = -1.0e-3 * (fpcrtl_random(40) + 20);
                          if(fpcrtl_random(2) == 0)
                          {
                              (*gear).dX = -(*gear).dX;
                          }
                          (*gear).Frame = fpcrtl_random(4);
                          (*gear).FrameTicks = fpcrtl_random(2000) + 1500;
                      }
                      break;
         case vgtBulletHit:{
                               (*gear).dX = 0;
                               (*gear).dY = 0;
                               (*gear).FrameTicks = 350;
                               (*gear).Frame = 7;
                               (*gear).Angle = 0;
                           }
                           break;
         case vgtSmoothWindBar:{
                                   (*gear).Angle = (ufloat_hwFloat2Float(cMaxWindSpeed) * 2) /(float) 1440;
                                   (*gear).Tag = ufloat_hwRound(ufloat_hwFloat_hwFloat_op_div(ufloat_hwFloat_LongInt_op_mul(cWindSpeed, 72), cMaxWindSpeed));
                               }
                               break;
         case vgtStraightShot:{
                                  (*gear).Angle = 0;
                                  (*gear).scale = 1.0;
                                  (*gear).dX = 1.0e-3 * fpcrtl_random(45);
                                  (*gear).dY = 1.0e-3 * (fpcrtl_random(20) + 25);
                                  (*gear).State = (sprHealth);
                                  if(fpcrtl_random(2) == 0)
                                  {
                                      (*gear).dX = -(*gear).dX;
                                  }
                                  (*gear).Frame = 0;
                                  (*gear).FrameTicks = fpcrtl_random(750) + 1250;
                                  (*gear).State = (sprSnowDust);
                              }
                              break;
         case vgtNoPlaceWarn:{
                                 (*gear).FrameTicks = 2000;
                                 (*gear).Tint = 0xff0000ff;
                                 (*gear).scale = 1.0;
                             }
                             break;
         default: break;}
    }
    if(State != 0)
    {
        gear->State = State;
    }
    switch(gear->Kind)
    {case vgtFlake:if(fpcrtl_random(3) == 0)
                   {
                       gear->scale = 0.5;
                       gear->Layer = 0;
                   }
                   else
                   {
                       if(fpcrtl_random(3) == 0)
                       {
                           gear->scale = 0.8;
                           gear->Layer = 4;
                       }
                       else
                       {
                           if(fpcrtl_random(3) != 0)
                           {
                               gear->Layer = 5;
                           }
                           else
                           {
                               if(!cFlattenFlakes && (fpcrtl_random(2) == 0))
                               {
                                   gear->Layer = 6;
                               }
                               else
                               {
                                   if(!cFlattenFlakes)
                                   {
                                       gear->scale = 1.5;
                                       gear->Layer = 2;
                                   }
                                   else
                                   {
                                       gear->Layer = 0;
                                       gear->scale = 0.5;
                                   }
                               }
                           }
                       }
                   }
                   break;
     case vgtCloud:if(cFlattenClouds)
                   {
                       gear->Layer = 5;
                   }
                   else
                   {
                       if(fpcrtl_random(3) == 0)
                       {
                           gear->scale = 0.25;
                           gear->Layer = 0;
                       }
                       else
                       {
                           if(fpcrtl_random(2) == 0)
                           {
                               gear->Layer = 5;
                           }
                           else
                           {
                               gear->scale = 0.4;
                               gear->Layer = 4;
                           }
                       }
                   }
                   break;
     case vgtNoPlaceWarn:gear->Layer = 6;
                         break;
     case vgtTeamHealthSorter:
     case vgtSmoothWindBar:gear->Layer = 0;
                           break;
     case vgtSmokeTrace:
     case vgtEvilTrace:
     case vgtLineTrail:
     case vgtSmoke:
     case vgtSmokeWhite:
     case vgtDust:
     case vgtFire:
     case vgtSplash:
     case vgtDroplet:
     case vgtBubble:gear->Layer = 1;
                    break;
     case vgtSpeechBubble:
     case vgtSmallDamageTag:
     case vgtHealthTag:
     case vgtStraightShot:
     case vgtFeather:
     case vgtChunk:gear->Layer = 3;
                   break;
     case vgtExplosion:
     case vgtBigExplosion:
     case vgtExplPart:
     case vgtExplPart2:
     case vgtSteam:
     case vgtAmmo:
     case vgtShell:
     case vgtEgg:
     case vgtBeeTrace:
     case vgtSmokeRing:
     case vgtNote:
     case vgtBulletHit:
     case vgtCircle:gear->Layer = 2;
                    break;
     default: break;}
    if(Layer != -1)
    {
        gear->Layer = Layer;
    }
    if(VisualGearLayersStart[gear->Layer] == NULL)
    {
        VisualGearLayersStart[gear->Layer] = gear;
    }
    if(VisualGearLayersEnd[gear->Layer] != NULL)
    {
        VisualGearLayersEnd[gear->Layer]->NextGear = gear;
        gear->PrevGear = VisualGearLayersEnd[gear->Layer];
    }
    VisualGearLayersEnd[gear->Layer] = gear;
    addvisualgear_result = gear;
    uscript_ScriptCall_2(__str0, gear->uid);
    return addvisualgear_result;
};
void uvisualgearslist_DeleteVisualGear(PVisualGear Gear)
{
    uscript_ScriptCall_2(__str1, Gear->uid);
    utextures_FreeAndNilTexture(&(Gear->Tex));
    if((Gear->NextGear == NULL) && (Gear->PrevGear == NULL))
    {
        VisualGearLayersStart[Gear->Layer] = NULL;
        VisualGearLayersEnd[Gear->Layer] = NULL;
    }
    if(Gear->PrevGear != NULL)
    {
        (*Gear->PrevGear).NextGear = Gear->NextGear;
    }
    else
    {
        if(Gear->NextGear != NULL)
        {
            VisualGearLayersStart[Gear->Layer] = Gear->NextGear;
        }
    }
    if(Gear->NextGear != NULL)
    {
        (*Gear->NextGear).PrevGear = Gear->PrevGear;
    }
    else
    {
        if(Gear->PrevGear != NULL)
        {
            VisualGearLayersEnd[Gear->Layer] = Gear->PrevGear;
        }
    }
    if(lastVisualGearByUID == Gear)
    {
        lastVisualGearByUID = NULL;
    }
    fpcrtl_dispose(Gear);
};
PVisualGear uvisualgearslist_VisualGearByUID(LongWord uid)
{
    PVisualGear visualgearbyuid_result;
    PVisualGear vg;
    LongWord i;
    visualgearbyuid_result = NULL;
    if(uid == 0)
    {
        return visualgearbyuid_result;
    }
    if((lastVisualGearByUID != NULL) && (lastVisualGearByUID->uid == uid))
    {
        visualgearbyuid_result = lastVisualGearByUID;
        return visualgearbyuid_result;
    }
    {i = 2;
     LongWord i__end__ = 5;
     if (i <= i__end__) do {
                               vg = VisualGearLayersStart[i % 4];
                               while(vg != NULL)
                               {
                                   if(vg->uid == uid)
                                   {
                                       lastVisualGearByUID = vg;
                                       visualgearbyuid_result = vg;
                                       return visualgearbyuid_result;
                                   }
                                   vg = vg->NextGear;
                               }
                           } while(i++ != i__end__);}
    return visualgearbyuid_result;
};
