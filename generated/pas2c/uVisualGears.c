#include "fpcrtl.h"

#include "uVisualGears.h"
#include "uVariables.h"
#include "uRender.h"
#include "Math.h"
#include "uRenderUtils.h"
#include "uUtils.h"
#include "uVisualGearsList.h"
void uvisualgears_AddDamageTag(LongWord X,LongWord Y,LongWord Damage,LongWord Color)
{
    PVisualGear Gear;
    if(cAltDamage)
    {
        Gear = uvisualgearslist_AddVisualGear_4(X, Y, vgtSmallDamageTag, Damage);
        if(Gear != NULL)
        {
            {
                (*Gear).Tex = urenderutils_RenderStringTex(fpcrtl_str2astr(uutils_IntToStr(Damage)), Color, fntSmall);
            }
        }
    }
};
void uvisualgears_ProcessVisualGears(LongWord Steps)
{
    PVisualGear Gear;
    PVisualGear t;
    LongWord i;
    if(Steps == 0)
    {
        return;
    }
    {i = 0;
     LongWord i__end__ = 6;
     if (i <= i__end__) do {
                               t = VisualGearLayersStart[i];
                               while(t != NULL)
                               {
                                   Gear = t;
                                   t = Gear->NextGear;
                                   Gear->doStep(Gear, Steps);
                               }
                           } while(i++ != i__end__);}
};
void uvisualgears_KickFlakes(LongInt Radius,LongInt X,LongInt Y)
{
    PVisualGear Gear;
    PVisualGear t;
    LongInt dmg;
    LongInt i;
    if((vobCount == 0) || (vobCount > 200))
    {
        return;
    }
    {i = 2;
     LongInt i__end__ = 6;
     if (i <= i__end__) do {
                               if(i != 3)
                               {
                                   t = VisualGearLayersStart[i];
                                   while(t != NULL)
                                   {
                                       Gear = t;
                                       if(Gear->Kind == vgtFlake)
                                       {
                                           dmg = uutils_Min(101, (Radius + (cHHRadius / 2)) - (((LongInt)fpcrtl_abs(fpcrtl_round(Gear->X) - X) + fpcrtl_abs(fpcrtl_round(Gear->Y) - Y)) / 5));
                                           if(dmg > 1)
                                           {
                                               Gear->tdX = (2.0e-2 * dmg) + 1.0e-2;
                                               if((Gear->X - X) < 0)
                                               {
                                                   Gear->tdX = -Gear->tdX;
                                               }
                                               Gear->tdY = (2.0e-2 * dmg) + 1.0e-2;
                                               if((Gear->Y - Y) < 0)
                                               {
                                                   Gear->tdY = -Gear->tdY;
                                               }
                                               Gear->Timer = 200;
                                           }
                                       }
                                       t = Gear->NextGear;
                                   }
                               }
                           } while(i++ != i__end__);}
};
TSprite uvisualgears_GetSprite(TSprite sprite,TSprite SDsprite)
{
    TSprite getsprite_result;
    if(SuddenDeathDmg)
    {
        return SDsprite;
    }
    else
    {
        return sprite;
    }
    return getsprite_result;
};
TSprite uvisualgears_GetSpriteByWind(TSprite sprite,TSprite Lsprite)
{
    TSprite getspritebywind_result;
    if((SpritesData[Lsprite].Texture != NULL) && (cWindSpeedf < 0))
    {
        return Lsprite;
    }
    else
    {
        return sprite;
    }
    return getspritebywind_result;
};
PSpriteData uvisualgears_GetSpriteData(TSprite sprite,TSprite SDsprite)
{
    return &(SpritesData[uvisualgears_GetSprite(sprite, SDsprite)]);
};
void uvisualgears_DrawVisualGears(LongWord Layer,boolean worldIsShifted)
{
    PVisualGear Gear;
    boolean tinted;
    boolean speedlessFlakes;
    real tmp;
    LongInt i;
    TSprite sprite;
    PSpriteData spriteData;
    if(SuddenDeathDmg)
    {
        speedlessFlakes = vobSDVelocity == 0;
    }
    else
    {
        speedlessFlakes = vobVelocity == 0;
    }
    switch(Layer)
    {case 0:{
                Gear = VisualGearLayersStart[0];
                while(Gear != NULL)
                {
                    if(Gear->Tint != 0xffffffff)
                    {
                        urender_Tint_1(Gear->Tint);
                    }
                    switch(Gear->Kind)
                    {case vgtCloud:{
                                       spriteData = uvisualgears_GetSpriteData(uvisualgears_GetSpriteByWind(sprCloud, sprCloudL), uvisualgears_GetSpriteByWind(sprSDCloud, sprSDCloudL));
                                       urender_DrawTextureF(spriteData->Texture, Gear->scale, fpcrtl_round(Gear->X) + WorldDx, (fpcrtl_round(Gear->Y) + WorldDy) + SkyOffset, Gear->Frame, 1, spriteData->Width, spriteData->Height);
                                   }
                                   break;
                     case vgtFlake:if(!worldIsShifted)
                                   {
                                       sprite = uvisualgears_GetSpriteByWind(uvisualgears_GetSprite(sprFlake, sprSDFlake), uvisualgears_GetSprite(sprFlakeL, sprSDFlakeL));
                                       if(cFlattenFlakes)
                                       {
                                           if(speedlessFlakes)
                                           {
                                               urender_DrawSprite_4(sprite, fpcrtl_round(Gear->X) + WorldDx, (fpcrtl_round(Gear->Y) + WorldDy) + SkyOffset, Gear->Frame);
                                           }
                                           else
                                           {
                                               urender_DrawSpriteRotatedF(sprite, fpcrtl_round(Gear->X) + WorldDx, (fpcrtl_round(Gear->Y) + WorldDy) + SkyOffset, Gear->Frame, 1, Gear->Angle);
                                           }
                                       }
                                       else
                                       {
                                           if(speedlessFlakes)
                                           {
                                               urender_DrawTextureF(SpritesData[sprite].Texture, Gear->scale, fpcrtl_round(Gear->X) + WorldDx, (fpcrtl_round(Gear->Y) + WorldDy) + SkyOffset, Gear->Frame, 1, SpritesData[sprFlake].Width, SpritesData[sprFlake].Height);
                                           }
                                           else
                                           {
                                               urender_DrawTextureRotatedF(SpritesData[sprite].Texture, Gear->scale, 0, 0, fpcrtl_round(Gear->X) + WorldDx, (fpcrtl_round(Gear->Y) + WorldDy) + SkyOffset, Gear->Frame, 1, SpritesData[sprFlake].Width, SpritesData[sprFlake].Height, Gear->Angle);
                                           }
                                       }
                                   }
                                   break;
                     default: break;}
                    if(Gear->Tint != 0xffffffff)
                    {
                        urender_untint();
                    }
                    Gear = Gear->NextGear;
                }
            }
            break;
     case 1:{
                Gear = VisualGearLayersStart[1];
                while(Gear != NULL)
                {
                    if(Gear->Tint != 0xffffffff)
                    {
                        urender_Tint_1(Gear->Tint);
                    }
                    switch(Gear->Kind)
                    {case vgtFlake:if(!worldIsShifted)
                                   {
                                       sprite = uvisualgears_GetSpriteByWind(uvisualgears_GetSprite(sprFlake, sprSDFlake), uvisualgears_GetSprite(sprFlakeL, sprSDFlakeL));
                                       if(speedlessFlakes)
                                       {
                                           urender_DrawSprite_4(sprite, fpcrtl_round(Gear->X) + WorldDx, (fpcrtl_round(Gear->Y) + WorldDy) + SkyOffset, Gear->Frame);
                                       }
                                       else
                                       {
                                           urender_DrawSpriteRotatedF(sprite, fpcrtl_round(Gear->X) + WorldDx, (fpcrtl_round(Gear->Y) + WorldDy) + SkyOffset, Gear->Frame, 1, Gear->Angle);
                                       }
                                   }
                                   break;
                     case vgtSmokeTrace:if(Gear->State < 8)
                                        {
                                            urender_DrawSprite_4(sprSmokeTrace, fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, Gear->State);
                                        }
                                        break;
                     case vgtEvilTrace:if(Gear->State < 8)
                                       {
                                           urender_DrawSprite_4(sprEvilTrace, fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, Gear->State);
                                       }
                                       break;
                     case vgtLineTrail:urender_DrawLine_9(Gear->X, Gear->Y, Gear->dX, Gear->dY, 1.0, 0xff, uutils_Min(Gear->Timer, 0xc0), uutils_Min(Gear->Timer, 0x80), uutils_Min(Gear->Timer, Gear->Tint & 0xff));
                                       break;
                     default: break;}
                    if((cReducedQuality & rqAntiBoom) == 0)
                    {
                        switch(Gear->Kind)
                        {case vgtSmoke:urender_DrawTextureF(SpritesData[sprSmoke].Texture, Gear->scale, fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, 7 - Gear->Frame, 1, SpritesData[sprSmoke].Width, SpritesData[sprSmoke].Height);
                                       break;
                         case vgtSmokeWhite:urender_DrawSprite_4(sprSmokeWhite, (fpcrtl_round(Gear->X) + WorldDx) - 11, (fpcrtl_round(Gear->Y) + WorldDy) - 11, 7 - Gear->Frame);
                                            break;
                         case vgtDust:if(Gear->State == 1)
                                      {
                                          urender_DrawSpriteRotatedF(sprSnowDust, fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, 7 - Gear->Frame, Gear->Tag, Gear->Angle);
                                      }
                                      else
                                      {
                                          urender_DrawSpriteRotatedF(sprDust, fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, 7 - Gear->Frame, Gear->Tag, Gear->Angle);
                                      }
                                      break;
                         case vgtFire:if((Gear->State & gsttmpFlag) == 0)
                                      {
                                          urender_DrawSprite_4(sprFlame, (fpcrtl_round(Gear->X) + WorldDx) - 8, fpcrtl_round(Gear->Y) + WorldDy, ((RealTicks >> 6) + Gear->Frame) % 8);
                                      }
                                      else
                                      {
                                          urender_DrawTextureF(SpritesData[sprFlame].Texture, Gear->FrameTicks /(float) 900, fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, ((RealTicks >> 7) + Gear->Frame) % 8, 1, 16, 16);
                                      }
                                      break;
                         case vgtSplash:{
                                            spriteData = uvisualgears_GetSpriteData(sprSplash, sprSDSplash);
                                            if(Gear->Angle != 0)
                                            {
                                                urender_DrawTextureRotatedF(spriteData->Texture, Gear->scale, 0, 0, fpcrtl_round((Gear->X + WorldDx) + ((((spriteData->Height + 8) * Gear->scale) /(float) 2) * (Gear->Angle /(float) fpcrtl_abs(Gear->Angle)))), fpcrtl_round(Gear->Y + WorldDy), 19 - ((Gear->FrameTicks / Gear->Timer) / 37), 1, spriteData->Width, spriteData->Height, Gear->Angle);
                                            }
                                            else
                                            {
                                                urender_DrawTextureF(spriteData->Texture, Gear->scale, fpcrtl_round(Gear->X + WorldDx), fpcrtl_round((Gear->Y + WorldDy) - (((spriteData->Height + 8) * Gear->scale) /(float) 2)), 19 - ((Gear->FrameTicks / Gear->Timer) / 37), 1, spriteData->Width, spriteData->Height);
                                            }
                                        }
                                        break;
                         case vgtDroplet:{
                                             sprite = uvisualgears_GetSprite(sprDroplet, sprSDDroplet);
                                             urender_DrawSprite_4(sprite, (fpcrtl_round(Gear->X) + WorldDx) - 8, (fpcrtl_round(Gear->Y) + WorldDy) - 8, Gear->Frame);
                                         }
                                         break;
                         case vgtBubble:urender_DrawSprite_4(sprBubbles, (fpcrtl_round(Gear->X) + WorldDx) - 8, (fpcrtl_round(Gear->Y) + WorldDy) - 8, Gear->Frame);
                                        break;
                         case vgtStraightShot:{
                                                  if(Gear->dX < 0)
                                                  {
                                                      i = -1;
                                                  }
                                                  else
                                                  {
                                                      i = 1;
                                                  }
                                                  urender_DrawTextureRotatedF(SpritesData[((TSprite)Gear->State)].Texture, Gear->scale, 0, 0, fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, Gear->Frame, i, SpritesData[((TSprite)Gear->State)].Width, SpritesData[((TSprite)Gear->State)].Height, Gear->Angle);
                                              }
                                              break;
                         default: break;}
                    }
                    if(Gear->Tint != 0xffffffff)
                    {
                        urender_untint();
                    }
                    Gear = Gear->NextGear;
                }
            }
            break;
     case 3:{
                Gear = VisualGearLayersStart[3];
                while(Gear != NULL)
                {
                    tinted = false;
                    if(Gear->Tint != 0xffffffff)
                    {
                        urender_Tint_1(Gear->Tint);
                    }
                    switch(Gear->Kind)
                    {case vgtSpeechBubble:if(Gear->Angle != 0)
                                          {
                                              if((Gear->Tex != NULL) && ((((Gear->State == 0) && (Gear->Hedgehog != NULL)) && ((*Gear->Hedgehog).Team != CurrentTeam)) || (Gear->State == 1)))
                                              {
                                                  tinted = true;
                                                  urender_Tint_4(0xff, 0xff, 0xff, 0x66);
                                                  urender_DrawTextureCentered(fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, Gear->Tex);
                                              }
                                              else
                                              {
                                                  if((Gear->Tex != NULL) && (((Gear->State == 0) && ((Gear->Hedgehog == NULL) || ((*Gear->Hedgehog).Team == CurrentTeam))) || (Gear->State == 2)))
                                                  {
                                                      urender_DrawTextureCentered(fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, Gear->Tex);
                                                  }
                                              }
                                          }
                                          break;
                     case vgtSmallDamageTag:if(Gear->Tex != NULL)
                                            {
                                                if(Gear->Frame == 0)
                                                {
                                                    urender_DrawTextureCentered(fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, Gear->Tex);
                                                }
                                                else
                                                {
                                                    urender_SetScale(cDefaultZoomLevel);
                                                    urender_DrawTexture_3(fpcrtl_round(Gear->X), fpcrtl_round(Gear->Y), Gear->Tex);
                                                    urender_SetScale(zoom);
                                                }
                                            }
                                            break;
                     case vgtHealthTag:if(Gear->Tex != NULL)
                                       {
                                           if(Gear->Frame == 0)
                                           {
                                               urender_DrawTextureCentered(fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, Gear->Tex);
                                           }
                                           else
                                           {
                                               urender_SetScale(cDefaultZoomLevel);
                                               if(Gear->Angle == 0)
                                               {
                                                   urender_DrawTexture_3(fpcrtl_round(Gear->X), fpcrtl_round(Gear->Y), Gear->Tex);
                                               }
                                               else
                                               {
                                                   urender_DrawTexture_4(fpcrtl_round(Gear->X), fpcrtl_round(Gear->Y), Gear->Tex, Gear->Angle);
                                               }
                                               urender_SetScale(zoom);
                                           }
                                       }
                                       break;
                     case vgtStraightShot:{
                                              if(Gear->dX < 0)
                                              {
                                                  i = -1;
                                              }
                                              else
                                              {
                                                  i = 1;
                                              }
                                              urender_DrawTextureRotatedF(SpritesData[((TSprite)Gear->State)].Texture, Gear->scale, 0, 0, fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, Gear->Frame, i, SpritesData[((TSprite)Gear->State)].Width, SpritesData[((TSprite)Gear->State)].Height, Gear->Angle);
                                          }
                                          break;
                     case vgtFeather:{
                                         if(Gear->FrameTicks < 255)
                                         {
                                             urender_Tint_4(0xff, 0xff, 0xff, Gear->FrameTicks);
                                             tinted = true;
                                         }
                                         urender_DrawSpriteRotatedF(sprFeather, fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, Gear->Frame, 1, Gear->Angle);
                                     }
                                     break;
                     default: break;}
                    if((cReducedQuality & rqAntiBoom) == 0)
                    {
                        switch(Gear->Kind)
                        {case vgtChunk:urender_DrawSpriteRotatedF(sprChunk, fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, Gear->Frame, 1, Gear->Angle);
                                       break;
                         default: break;}
                    }
                    if((Gear->Tint != 0xffffffff) || tinted)
                    {
                        urender_untint();
                    }
                    Gear = Gear->NextGear;
                }
            }
            break;
     case 2:{
                Gear = VisualGearLayersStart[2];
                while(Gear != NULL)
                {
                    tinted = false;
                    if(Gear->Tint != 0xffffffff)
                    {
                        urender_Tint_1(Gear->Tint);
                    }
                    switch(Gear->Kind)
                    {case vgtExplosion:urender_DrawSprite_4(sprExplosion50, (fpcrtl_round(Gear->X) - 32) + WorldDx, (fpcrtl_round(Gear->Y) - 32) + WorldDy, Gear->State);
                                       break;
                     case vgtBigExplosion:{
                                              tinted = true;
                                              urender_Tint_4(0xff, 0xff, 0xff, fpcrtl_round(0xff * (1 - fpcrtl_power(Gear->Timer /(float) 250, 4))));
                                              urender_DrawTextureRotatedF(SpritesData[sprBigExplosion].Texture, (0.85 * (-fpcrtl_power(2, (-10 * ((int)Gear->Timer)) /(float) 250) + 1)) + 0.4, 0, 0, fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, 0, 1, 385, 385, Gear->Angle);
                                          }
                                          break;
                     default: break;}
                    if((cReducedQuality & rqAntiBoom) == 0)
                    {
                        switch(Gear->Kind)
                        {case vgtExplPart:urender_DrawSprite_4(sprExplPart, (fpcrtl_round(Gear->X) + WorldDx) - 16, (fpcrtl_round(Gear->Y) + WorldDy) - 16, 7 - Gear->Frame);
                                          break;
                         case vgtExplPart2:urender_DrawSprite_4(sprExplPart2, (fpcrtl_round(Gear->X) + WorldDx) - 16, (fpcrtl_round(Gear->Y) + WorldDy) - 16, 7 - Gear->Frame);
                                           break;
                         case vgtSteam:urender_DrawSprite_4(sprSmokeWhite, (fpcrtl_round(Gear->X) + WorldDx) - 11, (fpcrtl_round(Gear->Y) + WorldDy) - 11, 7 - Gear->Frame);
                                       break;
                         case vgtAmmo:{
                                          tinted = true;
                                          urender_Tint_4(0xff, 0xff, 0xff, fpcrtl_round(Gear->alpha * 0xff));
                                          urender_DrawTextureF(ropeIconTex, Gear->scale, fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, 0, 1, 32, 32);
                                          if(Gear->Frame != (amNothing))
                                          {
                                              urender_DrawTextureF(SpritesData[sprAMAmmos].Texture, Gear->scale * 0.9, fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, Gear->Frame - 1, 1, 32, 32);
                                          }
                                      }
                                      break;
                         case vgtShell:{
                                           if(Gear->FrameTicks < 0xff)
                                           {
                                               urender_Tint_4(0xff, 0xff, 0xff, Gear->FrameTicks);
                                               tinted = true;
                                           }
                                           urender_DrawSpriteRotatedF(sprShell, fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, Gear->Frame, 1, Gear->Angle);
                                       }
                                       break;
                         case vgtEgg:urender_DrawSpriteRotatedF(sprEgg, fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, Gear->Frame, 1, Gear->Angle);
                                     break;
                         case vgtBeeTrace:{
                                              if(Gear->FrameTicks < 0xff)
                                              {
                                                  urender_Tint_4(0xff, 0xff, 0xff, Gear->FrameTicks / 2);
                                              }
                                              else
                                              {
                                                  urender_Tint_4(0xff, 0xff, 0xff, 0x80);
                                              }
                                              tinted = true;
                                              urender_DrawSpriteRotatedF(sprBeeTrace, fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, Gear->Frame, 1, (RealTicks >> 4) % cMaxAngle);
                                          }
                                          break;
                         case vgtSmokeRing:{
                                               tinted = true;
                                               urender_Tint_4(0xff, 0xff, 0xff, fpcrtl_round(Gear->alpha * 0xff));
                                               urender_DrawTextureRotatedF(SpritesData[sprSmokeRing].Texture, Gear->scale, 0, 0, fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, 0, 1, 200, 200, Gear->Angle);
                                           }
                                           break;
                         case vgtNote:urender_DrawSpriteRotatedF(sprNote, fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, Gear->Frame, 1, Gear->Angle);
                                      break;
                         case vgtBulletHit:urender_DrawSpriteRotatedF(sprBulletHit, (fpcrtl_round(Gear->X) + WorldDx) - 0, (fpcrtl_round(Gear->Y) + WorldDy) - 0, 7 - (Gear->FrameTicks / 50), 1, Gear->Angle);
                                           break;
                         default: break;}
                    }
                    switch(Gear->Kind)
                    {case vgtFlake:if(!worldIsShifted)
                                   {
                                       spriteData = uvisualgears_GetSpriteData(uvisualgears_GetSpriteByWind(sprFlake, sprFlakeL), uvisualgears_GetSpriteByWind(sprSDFlake, sprSDFlakeL));
                                       if(speedlessFlakes)
                                       {
                                           urender_DrawTextureF(spriteData->Texture, Gear->scale, fpcrtl_round(Gear->X) + WorldDx, (fpcrtl_round(Gear->Y) + WorldDy) + SkyOffset, Gear->Frame, 1, spriteData->Width, spriteData->Height);
                                       }
                                       else
                                       {
                                           urender_DrawTextureRotatedF(spriteData->Texture, Gear->scale, 0, 0, fpcrtl_round(Gear->X) + WorldDx, (fpcrtl_round(Gear->Y) + WorldDy) + SkyOffset, Gear->Frame, 1, spriteData->Width, spriteData->Height, Gear->Angle);
                                       }
                                   }
                                   break;
                     case vgtCircle:if(Gear->Angle == 1)
                                    {
                                        tmp = Gear->State /(float) 100;
                                        urender_DrawTexture_4(fpcrtl_round(Gear->X - (24 * tmp)) + WorldDx, fpcrtl_round(Gear->Y - (24 * tmp)) + WorldDy, SpritesData[sprVampiric].Texture, tmp);
                                    }
                                    else
                                    {
                                        urender_DrawCircle_4(fpcrtl_round(Gear->X) + WorldDx, fpcrtl_round(Gear->Y) + WorldDy, Gear->State, Gear->Timer);
                                    }
                                    break;
                     default: break;}
                    if((Gear->Tint != 0xffffffff) || tinted)
                    {
                        urender_untint();
                    }
                    Gear = Gear->NextGear;
                }
            }
            break;
     case 4:{
                Gear = VisualGearLayersStart[4];
                while(Gear != NULL)
                {
                    if(Gear->Tint != 0xffffffff)
                    {
                        urender_Tint_1(Gear->Tint);
                    }
                    switch(Gear->Kind)
                    {case vgtCloud:{
                                       spriteData = uvisualgears_GetSpriteData(uvisualgears_GetSpriteByWind(sprCloud, sprCloudL), uvisualgears_GetSpriteByWind(sprSDCloud, sprSDCloudL));
                                       urender_DrawTextureF(spriteData->Texture, Gear->scale, fpcrtl_round(Gear->X) + WorldDx, (fpcrtl_round(Gear->Y) + WorldDy) + SkyOffset, Gear->Frame, 1, spriteData->Width, spriteData->Height);
                                   }
                                   break;
                     case vgtFlake:if(!worldIsShifted)
                                   {
                                       spriteData = uvisualgears_GetSpriteData(uvisualgears_GetSpriteByWind(sprFlake, sprFlakeL), uvisualgears_GetSpriteByWind(sprSDFlake, sprSDFlakeL));
                                       if(speedlessFlakes)
                                       {
                                           urender_DrawTextureF(spriteData->Texture, Gear->scale, fpcrtl_round(Gear->X) + WorldDx, (fpcrtl_round(Gear->Y) + WorldDy) + SkyOffset, Gear->Frame, 1, spriteData->Width, spriteData->Height);
                                       }
                                       else
                                       {
                                           urender_DrawTextureRotatedF(spriteData->Texture, Gear->scale, 0, 0, fpcrtl_round(Gear->X) + WorldDx, (fpcrtl_round(Gear->Y) + WorldDy) + SkyOffset, Gear->Frame, 1, spriteData->Width, spriteData->Height, Gear->Angle);
                                       }
                                   }
                                   break;
                     default: break;}
                    if(Gear->Tint != 0xffffffff)
                    {
                        urender_untint();
                    }
                    Gear = Gear->NextGear;
                }
            }
            break;
     case 5:{
                Gear = VisualGearLayersStart[5];
                while(Gear != NULL)
                {
                    if(Gear->Tint != 0xffffffff)
                    {
                        urender_Tint_1(Gear->Tint);
                    }
                    switch(Gear->Kind)
                    {case vgtCloud:{
                                       sprite = uvisualgears_GetSpriteByWind(uvisualgears_GetSprite(sprCloud, sprSDCloud), uvisualgears_GetSprite(sprCloudL, sprSDCloudL));
                                       urender_DrawSprite_4(sprite, fpcrtl_round(Gear->X) + WorldDx, (fpcrtl_round(Gear->Y) + WorldDy) + SkyOffset, Gear->Frame);
                                   }
                                   break;
                     case vgtFlake:if(!worldIsShifted)
                                   {
                                       sprite = uvisualgears_GetSpriteByWind(uvisualgears_GetSprite(sprFlake, sprSDFlake), uvisualgears_GetSprite(sprFlakeL, sprSDFlakeL));
                                       if(speedlessFlakes)
                                       {
                                           urender_DrawSprite_4(sprite, fpcrtl_round(Gear->X) + WorldDx, (fpcrtl_round(Gear->Y) + WorldDy) + SkyOffset, Gear->Frame);
                                       }
                                       else
                                       {
                                           urender_DrawSpriteRotatedF(sprite, fpcrtl_round(Gear->X) + WorldDx, (fpcrtl_round(Gear->Y) + WorldDy) + SkyOffset, Gear->Frame, 1, Gear->Angle);
                                       }
                                   }
                                   break;
                     default: break;}
                    if(Gear->Tint != 0xffffffff)
                    {
                        urender_untint();
                    }
                    Gear = Gear->NextGear;
                }
            }
            break;
     case 6:{
                Gear = VisualGearLayersStart[6];
                while(Gear != NULL)
                {
                    if(Gear->Tint != 0xffffffff)
                    {
                        urender_Tint_1(Gear->Tint);
                    }
                    switch(Gear->Kind)
                    {case vgtFlake:if(!worldIsShifted)
                                   {
                                       sprite = uvisualgears_GetSpriteByWind(uvisualgears_GetSprite(sprFlake, sprSDFlake), uvisualgears_GetSprite(sprFlakeL, sprSDFlakeL));
                                       if(speedlessFlakes)
                                       {
                                           urender_DrawSprite_4(sprite, fpcrtl_round(Gear->X) + WorldDx, (fpcrtl_round(Gear->Y) + WorldDy) + SkyOffset, Gear->Frame);
                                       }
                                       else
                                       {
                                           urender_DrawSpriteRotatedF(sprite, fpcrtl_round(Gear->X) + WorldDx, (fpcrtl_round(Gear->Y) + WorldDy) + SkyOffset, Gear->Frame, 1, Gear->Angle);
                                       }
                                   }
                                   break;
                     case vgtNoPlaceWarn:urender_DrawTexture_4((fpcrtl_round(Gear->X) + WorldDx) - (fpcrtl_round((*Gear->Tex).w * Gear->scale) / 2), (fpcrtl_round(Gear->Y) + WorldDy) - (fpcrtl_round((*Gear->Tex).h * Gear->scale) / 2), Gear->Tex, Gear->scale);
                                         break;
                     default: break;}
                    if(Gear->Tint != 0xffffffff)
                    {
                        urender_untint();
                    }
                    Gear = Gear->NextGear;
                }
            }
            break;
     default: break;}
};
void uvisualgears_AddClouds()
{
    LongInt i;
    {i = 0;
     LongInt i__end__ = cCloudsNumber - 1;
     if (i <= i__end__) do {
                               uvisualgearslist_AddVisualGear_5(cLeftScreenBorder + (i * ((LongInt)cScreenSpace / (cCloudsNumber + 1))), LAND_HEIGHT - cCloudOffset, vgtCloud, 0, true);
                           } while(i++ != i__end__);}
};
void uvisualgears_ChangeToSDClouds()
{
    LongInt i;
    LongInt j;
    PVisualGear vg;
    PVisualGear tmp;
    if(cCloudsNumber == cSDCloudsNumber)
    {
        return;
    }
    {i = 0;
     LongInt i__end__ = 6;
     if (i <= i__end__) do {
                               vg = VisualGearLayersStart[i];
                               while(vg != NULL)
                               {
                                   if(vg->Kind == vgtCloud)
                                   {
                                       tmp = vg->NextGear;
                                       uvisualgearslist_DeleteVisualGear(vg);
                                       vg = tmp;
                                   }
                                   else
                                   {
                                       vg = vg->NextGear;
                                   }
                               }
                               {j = 0;
                                LongInt j__end__ = cSDCloudsNumber - 1;
                                if (j <= j__end__) do {
                                                          uvisualgearslist_AddVisualGear_5(cLeftScreenBorder + (j * ((LongInt)cScreenSpace / (cSDCloudsNumber + 1))), LAND_HEIGHT - cCloudOffset, vgtCloud, 0, true);
                                                      } while(j++ != j__end__);}
                           } while(i++ != i__end__);}
};
void uvisualgears_AddFlake()
{
    uvisualgearslist_AddVisualGear_3(cLeftScreenBorder + fpcrtl_random(cScreenSpace), (LAND_HEIGHT - cCloudOffset) + fpcrtl_random(cCloudOffset), vgtFlake);
};
void uvisualgears_AddFlakes()
{
    LongInt i;
    if((cReducedQuality & rqKillFlakes) != 0)
    {
        return;
    }
    if(hasBorder || !cSnow)
    {
        {i = 0;
         LongInt i__end__ = ((int)((vobCount * cScreenSpace) / 4096) - 1);
         if (i <= i__end__) do {
                                   uvisualgears_AddFlake();
                               } while(i++ != i__end__);}
    }
    else
    {
        {i = 0;
         LongInt i__end__ = ((int)(((vobCount * cScreenSpace) / 4096) / 3) - 1);
         if (i <= i__end__) do {
                                   uvisualgears_AddFlake();
                               } while(i++ != i__end__);}
    }
};
void uvisualgears_ChangeToSDFlakes()
{
    LongInt i;
    PVisualGear vg;
    PVisualGear tmp;
    if((cReducedQuality & rqKillFlakes) != 0)
    {
        return;
    }
    if(((((vobCount == vobSDCount) && (vobFrameTicks == vobSDFrameTicks)) && (vobFramesCount == vobSDFramesCount)) && (vobVelocity == vobSDVelocity)) && (vobFallSpeed == vobSDFallSpeed))
    {
        return;
    }
    {i = 0;
     LongInt i__end__ = 6;
     if (i <= i__end__) do {
                               vg = VisualGearLayersStart[i];
                               while(vg != NULL)
                               {
                                   if(vg->Kind == vgtFlake)
                                   {
                                       tmp = vg->NextGear;
                                       uvisualgearslist_DeleteVisualGear(vg);
                                       vg = tmp;
                                   }
                                   else
                                   {
                                       vg = vg->NextGear;
                                   }
                               }
                           } while(i++ != i__end__);}
    if(hasBorder || !cSnow)
    {
        {i = 0;
         LongInt i__end__ = ((int)((vobSDCount * cScreenSpace) / 4096) - 1);
         if (i <= i__end__) do {
                                   uvisualgears_AddFlake();
                               } while(i++ != i__end__);}
    }
    else
    {
        {i = 0;
         LongInt i__end__ = ((int)(((vobSDCount * cScreenSpace) / 4096) / 3) - 1);
         if (i <= i__end__) do {
                                   uvisualgears_AddFlake();
                               } while(i++ != i__end__);}
    }
};
void uvisualgears_initModule()
{
    LongWord i;
    VGCounter = 0;
    {i = 0;
     LongWord i__end__ = 6;
     if (i <= i__end__) do {
                               VisualGearLayersStart[i] = NULL;
                               VisualGearLayersEnd[i] = NULL;
                           } while(i++ != i__end__);}
};
void uvisualgears_freeModule()
{
    LongWord i;
    VGCounter = 0;
    {i = 0;
     LongWord i__end__ = 6;
     if (i <= i__end__) do {
                               while(VisualGearLayersStart[i] != NULL)
                               {
                                   uvisualgearslist_DeleteVisualGear(VisualGearLayersStart[i]);
                               }
                           } while(i++ != i__end__);}
};
