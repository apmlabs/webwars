#include "fpcrtl.h"

#include "uVisualGearsHandlers.h"
doStepVGHandlers_tt doStepVGHandlers;
#include "uCollisions.h"
#include "uVariables.h"
#include "Math.h"
#include "uConsts.h"
#include "uVisualGearsList.h"
#include "uFloat.h"
#include "uSound.h"
#include "uRenderUtils.h"
#include "uWorld.h"
#include "uUtils.h"
void uvisualgearshandlers_doStepFlake(PVisualGear Gear,LongWord Steps)
{
    real sign;
    boolean moved;
    boolean rising;
    boolean outside;
    boolean fallingFadeIn;
    LongWord vfc;
    LongWord vft;
    LongWord diff;
    LongInt spawnMargin;
    enum{randMargin = 50};
    enum{maxFallSpeedForFadeIn = 750};
    if(SuddenDeathDmg)
    {
        if(vobSDCount == 0)
        {
            return;
        }
    }
    else
    {
        if(vobCount == 0)
        {
            return;
        }
    }
    sign = 1;
    {
        (*Gear).X = (*Gear).X + (((((cWindSpeedf * 400) + (*Gear).dX) + (*Gear).tdX) * Steps) * Gear->scale);
        if(SuddenDeathDmg)
        {
            (*Gear).Y = (*Gear).Y + (((((*Gear).dY + (*Gear).tdY) + (cGravityf * vobSDFallSpeed)) * Steps) * Gear->scale);
            vfc = vobSDFramesCount;
            vft = vobSDFrameTicks;
            fallingFadeIn = vobSDFallSpeed <= maxFallSpeedForFadeIn;
        }
        else
        {
            (*Gear).Y = (*Gear).Y + (((((*Gear).dY + (*Gear).tdY) + (cGravityf * vobFallSpeed)) * Steps) * Gear->scale);
            vfc = vobFramesCount;
            vft = vobFrameTicks;
            fallingFadeIn = vobFallSpeed <= maxFallSpeedForFadeIn;
        }
        if(vft > 0)
        {
            (*Gear).FrameTicks += Steps;
            if((*Gear).FrameTicks > vft)
            {
                (*Gear).FrameTicks -= vft;
                ++(*Gear).Frame;
                if((*Gear).Frame == vfc)
                {
                    (*Gear).Frame = 0;
                }
            }
        }
        (*Gear).Angle = (*Gear).Angle + ((*Gear).dAngle * Steps);
        if((*Gear).Angle > 360)
        {
            (*Gear).Angle = (*Gear).Angle - 360;
        }
        else
        {
            if((*Gear).Angle < -360)
            {
                (*Gear).Angle = (*Gear).Angle + 360;
            }
        }
        if(((((fpcrtl_round((*Gear).X) >= cLeftScreenBorder) && (fpcrtl_round((*Gear).X) <= cRightScreenBorder)) && ((fpcrtl_round((*Gear).Y) - 250) <= LAND_HEIGHT)) && ((*Gear).Timer > 0)) && ((((int64_t) ((*Gear).Timer)) - ((int64_t) (Steps))) > 0))
        {
            if((*Gear).tdX > 0)
            {
                sign = 1;
            }
            else
            {
                sign = -1;
            }
            (*Gear).tdX = (*Gear).tdX - ((5.0e-3 * Steps) * sign);
            if(((sign < 0) && ((*Gear).tdX > 0)) || ((sign > 0) && ((*Gear).tdX < 0)))
            {
                (*Gear).tdX = 0;
            }
            if((*Gear).tdX > 0)
            {
                sign = 1;
            }
            else
            {
                sign = -1;
            }
            (*Gear).tdY = (*Gear).tdY - ((5.0e-3 * Steps) * sign);
            if(((sign < 0) && ((*Gear).tdY > 0)) || ((sign > 0) && ((*Gear).tdY < 0)))
            {
                (*Gear).tdY = 0;
            }
            (*Gear).Timer -= Steps;
        }
        else
        {
            moved = false;
            if(fpcrtl_round((*Gear).X) < cLeftScreenBorder)
            {
                (*Gear).X = (*Gear).X + cScreenSpace;
                moved = true;
            }
            else
            {
                if(fpcrtl_round((*Gear).X) > cRightScreenBorder)
                {
                    (*Gear).X = (*Gear).X - cScreenSpace;
                    moved = true;
                }
            }
            if(SuddenDeathDmg)
            {
                rising = (cGravityf * vobSDFallSpeed) < 0;
            }
            else
            {
                rising = (cGravityf * vobFallSpeed) < 0;
            }
            if(Gear->Layer == 2)
            {
                spawnMargin = 400;
            }
            else
            {
                spawnMargin = 200;
            }
            outside = !rising && (((fpcrtl_round((*Gear).Y) - spawnMargin) + randMargin) > LAND_HEIGHT);
            outside = outside || (rising && (fpcrtl_round((*Gear).Y) < (LAND_HEIGHT - (cCloudOffset - 110))));
            if(outside)
            {
                if(rising)
                {
                    if((*Gear).State == 0)
                    {
                        diff = (LAND_HEIGHT - (cCloudOffset - 110)) - fpcrtl_round((*Gear).Y);
                        diff = uutils_Min(diff * 2, 0xff);
                        if(diff >= 0xff)
                        {
                            diff = 0xff;
                            (*Gear).State = 1;
                        }
                        (*Gear).Tint = ((*Gear).Tint & 0xffffff00) | (((int64_t) (0xff)) - ((int64_t) (diff)));
                    }
                    else
                    {
                        (*Gear).Y = (LAND_HEIGHT + spawnMargin) + fpcrtl_random(50);
                        moved = true;
                        (*Gear).State = 0;
                        (*Gear).Tint = (*Gear).Tint | 0xff;
                    }
                }
                else
                {
                    (*Gear).Y = (*Gear).Y - ((1024 + spawnMargin) + fpcrtl_random(50));
                    moved = true;
                    if(fallingFadeIn)
                    {
                        (*Gear).State = 0xff;
                        (*Gear).Tint = ((*Gear).Tint & 0xffffff00) | (((int64_t) (0xff)) - ((int64_t) ((*Gear).State)));
                    }
                }
                if(moved)
                {
                    (*Gear).X = cLeftScreenBorder + fpcrtl_random(cScreenSpace);
                }
            }
            else
            {
                if(!rising && ((*Gear).State > 0))
                {
                    if((*Gear).State > 16)
                    {
                        (*Gear).State -= 16;
                    }
                    else
                    {
                        (*Gear).State = 0;
                    }
                    (*Gear).Tint = ((*Gear).Tint & 0xffffff00) | (((int64_t) (0xff)) - ((int64_t) ((*Gear).State)));
                }
            }
            if(moved)
            {
                (*Gear).Angle = fpcrtl_random(360);
                (*Gear).dX = 3.8654705e-6 * fpcrtl_random(10000);
                (*Gear).dY = 3.506096e-6 * fpcrtl_random(7000);
                if(fpcrtl_random(2) == 0)
                {
                    (*Gear).dX = -(*Gear).dX;
                }
            }
            (*Gear).Timer = 0;
            (*Gear).tdX = 0;
            (*Gear).tdY = 0;
        }
    }
};
void uvisualgearshandlers_doStepBeeTrace(PVisualGear Gear,LongWord Steps)
{
    if(Gear->FrameTicks > Steps)
    {
        Gear->FrameTicks -= Steps;
    }
    else
    {
        uvisualgearslist_DeleteVisualGear(Gear);
    }
};
void uvisualgearshandlers_doStepCloud(PVisualGear Gear,LongWord Steps)
{
    LongWord s;
    real t;
    Gear->X = Gear->X + ((((cWindSpeedf * 750) * Gear->dX) * Gear->scale) * Steps);
    s = (GameTicks + Gear->Timer) % 4096;
    t = (8 * Gear->scale) * ufloat_hwFloat2Float(ufloat_AngleSin(s % 2048));
    if(s < 2048)
    {
        t = -t;
    }
    Gear->Y = ((LAND_HEIGHT - cCloudOffset) + ((LongInt)Gear->Timer % 8)) + t;
    if(fpcrtl_round(Gear->X) < cLeftScreenBorder)
    {
        Gear->X = Gear->X + cScreenSpace;
    }
    else
    {
        if(fpcrtl_round(Gear->X) > cRightScreenBorder)
        {
            Gear->X = Gear->X - cScreenSpace;
        }
    }
};
void uvisualgearshandlers_doStepExpl(PVisualGear Gear,LongWord Steps)
{
    LongInt s;
    s = uutils_Min(Steps, cExplFrameTicks);
    Gear->X = Gear->X + (Gear->dX * s);
    Gear->Y = Gear->Y + (Gear->dY * s);
    if(Gear->FrameTicks <= Steps)
    {
        if(Gear->Frame == 0)
        {
            uvisualgearslist_DeleteVisualGear(Gear);
        }
        else
        {
            --Gear->Frame;
            Gear->FrameTicks = cExplFrameTicks;
        }
    }
    else
    {
        Gear->FrameTicks -= Steps;
    }
};
void uvisualgearshandlers_doStepNote(PVisualGear Gear,LongWord Steps)
{
    Gear->X = Gear->X + (Gear->dX * Steps);
    Gear->Y = Gear->Y + (Gear->dY * Steps);
    Gear->dY = Gear->dY + ((cGravityf * Steps) /(float) 2);
    Gear->Angle = Gear->Angle + (((Gear->Frame + 1) * Steps) /(float) 10);
    while(Gear->Angle > cMaxAngle)
    {
        Gear->Angle = Gear->Angle - cMaxAngle;
    }
    if(Gear->FrameTicks <= Steps)
    {
        uvisualgearslist_DeleteVisualGear(Gear);
    }
    else
    {
        Gear->FrameTicks -= Steps;
    }
};
void uvisualgearshandlers_doStepLineTrail(PVisualGear Gear,LongWord Steps)
{
    if(Gear->Timer <= Steps)
    {
        uvisualgearslist_DeleteVisualGear(Gear);
    }
    else
    {
        Gear->Timer -= Steps;
    }
};
void uvisualgearshandlers_doStepEgg(PVisualGear Gear,LongWord Steps)
{
    Gear->X = Gear->X + (Gear->dX * Steps);
    Gear->Y = Gear->Y + (Gear->dY * Steps);
    Gear->dY = Gear->dY + (cGravityf * Steps);
    Gear->Angle = fpcrtl_round(Gear->Angle + Steps) % cMaxAngle;
    if(Gear->FrameTicks <= Steps)
    {
        uvisualgearslist_DeleteVisualGear(Gear);
        return;
    }
    else
    {
        Gear->FrameTicks -= Steps;
    }
    if(Gear->FrameTicks < 0xff)
    {
        Gear->Tint = (Gear->Tint & 0xffffff00) | Gear->FrameTicks;
    }
};
void uvisualgearshandlers_doStepFire(PVisualGear Gear,LongWord Steps)
{
    PVisualGear vgt;
    Gear->X = Gear->X + (Gear->dX * Steps);
    Gear->Y = Gear->Y + (Gear->dY * Steps);
    if((Gear->State & gsttmpFlag) == 0)
    {
        Gear->dY = Gear->dY + (cGravityf * Steps);
        if((GameTicks % 200) < (Steps + 1))
        {
            vgt = uvisualgearslist_AddVisualGear_3(fpcrtl_round(Gear->X), fpcrtl_round(Gear->Y), vgtFire);
            if(vgt != NULL)
            {
                vgt->dX = 0;
                vgt->dY = 0;
                vgt->State = gsttmpFlag;
            }
        }
    }
    else
    {
        Steps += Steps;
    }
    if(Gear->FrameTicks <= Steps)
    {
        uvisualgearslist_DeleteVisualGear(Gear);
    }
    else
    {
        Gear->FrameTicks -= Steps;
    }
};
void uvisualgearshandlers_doStepShell(PVisualGear Gear,LongWord Steps)
{
    Gear->X = Gear->X + (Gear->dX * Steps);
    Gear->Y = Gear->Y + (Gear->dY * Steps);
    Gear->dY = Gear->dY + (cGravityf * Steps);
    Gear->Angle = fpcrtl_round(Gear->Angle + Steps) % cMaxAngle;
    if(Gear->FrameTicks <= Steps)
    {
        uvisualgearslist_DeleteVisualGear(Gear);
    }
    else
    {
        Gear->FrameTicks -= Steps;
    }
};
void uvisualgearshandlers_doStepSmallDamageTag(PVisualGear Gear,LongWord Steps)
{
    string255 s;
    if(Gear->Tex == NULL)
    {
        s = uutils_IntToStr(Gear->State);
        Gear->Tex = urenderutils_RenderStringTex(fpcrtl_str2astr(s), cWhiteColor, fntSmall);
    }
    Gear->X = Gear->X + (Gear->dX * Steps);
    Gear->Y = Gear->Y + (Gear->dY * Steps);
    if(Gear->FrameTicks <= Steps)
    {
        uvisualgearslist_DeleteVisualGear(Gear);
    }
    else
    {
        Gear->FrameTicks -= Steps;
    }
};
void uvisualgearshandlers_doStepBubble(PVisualGear Gear,LongWord Steps)
{
    Gear->X = Gear->X + (Gear->dX * Steps);
    Gear->Y = Gear->Y + (Gear->dY * Steps);
    Gear->Y = Gear->Y - (cDrownSpeedf * Steps);
    Gear->dX = Gear->dX /(float) (1.001 * Steps);
    Gear->dY = Gear->dY /(float) (1.001 * Steps);
    if((Gear->FrameTicks <= Steps) || !ucollisions_CheckCoordInWater(fpcrtl_round(Gear->X), fpcrtl_round(Gear->Y)))
    {
        uvisualgearslist_DeleteVisualGear(Gear);
    }
    else
    {
        Gear->FrameTicks -= Steps;
    }
};
void uvisualgearshandlers_doStepSteam(PVisualGear Gear,LongWord Steps)
{
    if(((cWindSpeedf > 0) && (leftX > Gear->X)) || ((cWindSpeedf < 0) && (rightX < Gear->X)))
    {
        Gear->X = Gear->X + (((cWindSpeedf * 100) + Gear->dX) * Steps);
    }
    Gear->Y = Gear->Y - (cDrownSpeedf * Steps);
    if(Gear->FrameTicks <= Steps)
    {
        if(Gear->Frame == 0)
        {
            uvisualgearslist_DeleteVisualGear(Gear);
        }
        else
        {
            if(fpcrtl_random(2) == 0)
            {
                --Gear->Frame;
            }
            Gear->FrameTicks = cExplFrameTicks;
        }
    }
    else
    {
        Gear->FrameTicks -= Steps;
    }
};
void uvisualgearshandlers_doStepAmmo(PVisualGear Gear,LongWord Steps)
{
    Gear->Y = Gear->Y - (cDrownSpeedf * Steps);
    Gear->scale = Gear->scale + (2.5e-3 * Steps);
    Gear->alpha = Gear->alpha - (1.5e-3 * Steps);
    if(Gear->alpha < 0)
    {
        uvisualgearslist_DeleteVisualGear(Gear);
    }
};
void uvisualgearshandlers_doStepSmoke(PVisualGear Gear,LongWord Steps)
{
    Gear->X = Gear->X + ((cWindSpeedf + Gear->dX) * Steps);
    Gear->Y = Gear->Y - ((cDrownSpeedf + Gear->dY) * Steps);
    Gear->dX = Gear->dX + ((cWindSpeedf * 0.3) * Steps);
    if(Gear->FrameTicks <= Steps)
    {
        if(Gear->Frame == 0)
        {
            uvisualgearslist_DeleteVisualGear(Gear);
        }
        else
        {
            if(fpcrtl_random(2) == 0)
            {
                --Gear->Frame;
            }
            Gear->FrameTicks = cExplFrameTicks;
        }
    }
    else
    {
        Gear->FrameTicks -= Steps;
    }
};
void uvisualgearshandlers_doStepDust(PVisualGear Gear,LongWord Steps)
{
    Gear->X = Gear->X + (((cWindSpeedf + ((cWindSpeedf * 3.0e-2) * Steps)) + Gear->dX) * Steps);
    Gear->Y = Gear->Y - (Gear->dY * Steps);
    Gear->dX = Gear->dX - ((Gear->dX * 5.0e-3) * Steps);
    Gear->dY = Gear->dY - ((cDrownSpeedf * 1.0e-3) * Steps);
    if(Gear->FrameTicks <= Steps)
    {
        if(Gear->Frame == 0)
        {
            uvisualgearslist_DeleteVisualGear(Gear);
        }
        else
        {
            --Gear->Frame;
            Gear->FrameTicks = cExplFrameTicks;
        }
    }
    else
    {
        Gear->FrameTicks -= Steps;
    }
};
void uvisualgearshandlers_doStepSplash(PVisualGear Gear,LongWord Steps)
{
    if(Gear->FrameTicks <= Steps)
    {
        uvisualgearslist_DeleteVisualGear(Gear);
    }
    else
    {
        Gear->FrameTicks -= Steps;
    }
};
void uvisualgearshandlers_doStepDroplet(PVisualGear Gear,LongWord Steps)
{
    Gear->X = Gear->X + (Gear->dX * Steps);
    Gear->Y = Gear->Y + (Gear->dY * Steps);
    Gear->dY = Gear->dY + (cGravityf * Steps);
    if(ucollisions_CheckCoordInWater(fpcrtl_round(Gear->X), fpcrtl_round(Gear->Y)))
    {
        uvisualgearslist_DeleteVisualGear(Gear);
        usound_PlaySound_1(((TSound)(sndDroplet1) + fpcrtl_random(3)));
    }
};
void uvisualgearshandlers_doStepSmokeRing(PVisualGear Gear,LongWord Steps)
{
    Gear->Timer += Steps;
    if(Gear->Timer >= Gear->FrameTicks)
    {
        uvisualgearslist_DeleteVisualGear(Gear);
    }
    else
    {
        Gear->scale = (1.25 * (-fpcrtl_power(2, (-10 * ((int)Gear->Timer)) /(float) Gear->FrameTicks) + 1)) + 0.4;
        Gear->alpha = 1 - fpcrtl_power(Gear->Timer /(float) 350, 4);
        if(Gear->alpha < 0)
        {
            Gear->alpha = 0;
        }
    }
};
void uvisualgearshandlers_doStepFeather(PVisualGear Gear,LongWord Steps)
{
    Gear->X = Gear->X + (Gear->dX * Steps);
    Gear->Y = Gear->Y + (Gear->dY * Steps);
    Gear->dY = Gear->dY + (cGravityf * Steps);
    Gear->Angle = fpcrtl_round(Gear->Angle + Steps) % cMaxAngle;
    if(Gear->FrameTicks <= Steps)
    {
        uvisualgearslist_DeleteVisualGear(Gear);
    }
    else
    {
        Gear->FrameTicks -= Steps;
    }
};
enum{cSorterWorkTime = 640};
typedef struct __thexchar_tt {
            LongInt dy;
            LongInt ny;
            LongInt dw;
            PTeam team;
            QWord SortFactor;
            LongInt hdw[(cMaxHHIndex + 1)];
        } thexchar_tt[(cMaxTeams + 1)];
static thexchar_tt thexchar;
static PVisualGear currsorter = NULL;
boolean uvisualgearshandlers_isSorterActive()
{
    boolean issorteractive_result;
    issorteractive_result = currsorter != NULL;
    return issorteractive_result;
};
void uvisualgearshandlers_doStepTeamHealthSorterWork(PVisualGear Gear,LongWord Steps)
{
    LongInt i;
    LongInt t;
    LongInt h;
    if(currsorter == Gear)
    {
        {t = 1;
         LongInt t__end__ = uutils_Min(Steps, Gear->Timer);
         if (t <= t__end__) do {
                                   --Gear->Timer;
                                   if((Gear->Timer & 15) == 0)
                                   {
                                       {i = 0;
                                        LongInt i__end__ = ((int)(TeamsCount) - 1);
                                        if (i <= i__end__) do {
                                                                  {
                                                                      thexchar[i].team->DrawHealthY = thexchar[i].ny + ((thexchar[i].dy * ((LongInt)Gear->Timer)) / cSorterWorkTime);
                                                                      thexchar[i].team->TeamHealthBarHealth = thexchar[i].team->TeamHealth + ((thexchar[i].dw * ((LongInt)Gear->Timer)) / cSorterWorkTime);
                                                                      {h = 0;
                                                                       LongInt h__end__ = cMaxHHIndex;
                                                                       if (h <= h__end__) do {
                                                                                                 if(thexchar[i].team->Hedgehogs[h].Gear != NULL)
                                                                                                 {
                                                                                                     thexchar[i].team->Hedgehogs[h].HealthBarHealth = (*thexchar[i].team->Hedgehogs[h].Gear).Health + ((thexchar[i].hdw[h] * ((LongInt)Gear->Timer)) / cSorterWorkTime);
                                                                                                 }
                                                                                                 else
                                                                                                 {
                                                                                                     thexchar[i].team->Hedgehogs[h].HealthBarHealth = (thexchar[i].hdw[h] * ((LongInt)Gear->Timer)) / cSorterWorkTime;
                                                                                                 }
                                                                                             } while(h++ != h__end__);}
                                                                  }
                                                              } while(i++ != i__end__);}
                                   }
                               } while(t++ != t__end__);}
    }
    if((Gear->Timer == 0) || (currsorter != Gear))
    {
        if(currsorter == Gear)
        {
            currsorter = NULL;
        }
        uvisualgearslist_DeleteVisualGear(Gear);
        return;
    }
};
void uvisualgearshandlers_doStepTeamHealthSorter(PVisualGear Gear,LongWord Steps)
{
    LongWord i;
    boolean b;
    boolean noHogs;
    LongInt t;
    LongInt h;
    {t = 0;
     LongInt t__end__ = ((int)(TeamsCount) - 1);
     if (t <= t__end__) do {
                               {
                                   thexchar[t].team = TeamsArray[t];
                                   thexchar[t].dy = thexchar[t].team->DrawHealthY;
                                   thexchar[t].dw = thexchar[t].team->TeamHealthBarHealth - thexchar[t].team->TeamHealth;
                                   if(thexchar[t].team->TeamHealth > 0)
                                   {
                                       thexchar[t].SortFactor = (*thexchar[t].team->Clan).ClanHealth;
                                       thexchar[t].SortFactor = (thexchar[t].SortFactor << 3) + (*thexchar[t].team->Clan).ClanIndex;
                                       thexchar[t].SortFactor = (thexchar[t].SortFactor << 30) + thexchar[t].team->TeamHealth;
                                   }
                                   else
                                   {
                                       thexchar[t].SortFactor = 0;
                                   }
                                   {h = 0;
                                    LongInt h__end__ = cMaxHHIndex;
                                    if (h <= h__end__) do {
                                                              if(thexchar[t].team->Hedgehogs[h].Gear != NULL)
                                                              {
                                                                  thexchar[t].hdw[h] = thexchar[t].team->Hedgehogs[h].HealthBarHealth - (*thexchar[t].team->Hedgehogs[h].Gear).Health;
                                                              }
                                                              else
                                                              {
                                                                  thexchar[t].hdw[h] = thexchar[t].team->Hedgehogs[h].HealthBarHealth;
                                                              }
                                                          } while(h++ != h__end__);}
                               }
                           } while(t++ != t__end__);}
    if(TeamsCount > 1)
    {
        do {
               b = true;
               {t = 0;
                LongInt t__end__ = TeamsCount - 2;
                if (t <= t__end__) do {
                                          if(thexchar[t].SortFactor > thexchar[(t + 1)].SortFactor)
                                          {
                                              thexchar[cMaxTeams] = thexchar[t];
                                              thexchar[t] = thexchar[(t + 1)];
                                              thexchar[(t + 1)] = thexchar[cMaxTeams];
                                              b = false;
                                          }
                                      } while(t++ != t__end__);}
           } while(!(b));
    }
    t = -4;
    {i = 0;
     LongWord i__end__ = ((int)(TeamsCount) - 1);
     if (i <= i__end__) do {
                               {
                                   noHogs = true;
                                   {h = 0;
                                    LongInt h__end__ = cMaxHHIndex;
                                    if (h <= h__end__) do {
                                                              if(thexchar[i].team->Hedgehogs[h].Gear != NULL)
                                                              {
                                                                  noHogs = false;
                                                              }
                                                          } while(h++ != h__end__);}
                                   if((thexchar[i].team->TeamHealth > 0) && (noHogs == false))
                                   {
                                       t -= (*(*thexchar[i].team->Clan).HealthTex).h + 2;
                                       thexchar[i].ny = t;
                                       thexchar[i].dy = thexchar[i].dy - thexchar[i].ny;
                                   }
                               }
                           } while(i++ != i__end__);}
    Gear->Timer = cSorterWorkTime;
    Gear->doStep = &(uvisualgearshandlers_doStepTeamHealthSorterWork);
    currsorter = Gear;
};
void uvisualgearshandlers_doStepSpeechBubbleWork(PVisualGear Gear,LongWord Steps)
{
    PGear realgear;
    if(Gear->Timer > Steps)
    {
        Gear->Timer -= Steps;
    }
    else
    {
        Gear->Timer = 0;
    }
    realgear = NULL;
    if(Gear->Frame != 0)
    {
        realgear = ugears_GearByUID(Gear->Frame);
        if(realgear != NULL)
        {
            Gear->X = ufloat_hwFloat2Float(realgear->X) + (((*Gear->Tex).w / 2) - Gear->Tag);
            Gear->Y = ufloat_hwFloat2Float(realgear->Y) - (realgear->Radius + (*Gear->Tex).h);
            Gear->Angle = 1;
        }
    }
    else
    {
        if((*Gear->Hedgehog).Gear != NULL)
        {
            Gear->X = ufloat_hwFloat2Float((*(*Gear->Hedgehog).Gear).X) + (((*Gear->Tex).w / 2) - Gear->Tag);
            Gear->Y = ufloat_hwFloat2Float((*(*Gear->Hedgehog).Gear).Y) - (cHHRadius + (*Gear->Tex).h);
            Gear->Angle = 1;
        }
    }
    if((Gear->Timer == 0) || ((realgear == NULL) && (Gear->Frame != 0)))
    {
        if((Gear->Hedgehog != NULL) && ((*Gear->Hedgehog).SpeechGear == Gear))
        {
            (*Gear->Hedgehog).SpeechGear = NULL;
        }
        uvisualgearslist_DeleteVisualGear(Gear);
    }
};
void uvisualgearshandlers_doStepSpeechBubble(PVisualGear Gear,LongWord Steps)
{
    PGear realgear;
    if(Gear->Frame != 0)
    {
        realgear = ugears_GearByUID(Gear->FrameTicks);
    }
    else
    {
        {
            if((*Gear->Hedgehog).SpeechGear != NULL)
            {
                (*Gear->Hedgehog).SpeechGear->Timer = 0;
            }
        }
        realgear = (*Gear->Hedgehog).Gear;
        (*Gear->Hedgehog).SpeechGear = Gear;
    }
    if(realgear != NULL)
    {
        switch(Gear->FrameTicks)
        {case 1:Gear->Tag = (SpritesData[sprSpeechTail].Width - 37) + realgear->Radius;
                break;
         case 2:Gear->Tag = (SpritesData[sprThoughtTail].Width - 29) + realgear->Radius;
                break;
         case 3:Gear->Tag = (SpritesData[sprShoutTail].Width - 19) + realgear->Radius;
                break;
         default: break;}
    }
    Gear->Timer = uutils_Max(((LongInt)fpcrtl_Length(Gear->Text)) * 150, 3000);
    Gear->Tex = urenderutils_RenderSpeechBubbleTex(fpcrtl_str2astr(Gear->Text), Gear->FrameTicks, fnt16);
    Gear->doStep = &(uvisualgearshandlers_doStepSpeechBubbleWork);
    Gear->Y = Gear->Y - (*Gear->Tex).h;
};
void uvisualgearshandlers_doStepHealthTagWork(PVisualGear Gear,LongWord Steps)
{
    if(Steps > Gear->Timer)
    {
        uvisualgearslist_DeleteVisualGear(Gear);
    }
    else
    {
        Gear->Timer -= Steps;
        Gear->Y = Gear->Y + (Gear->dY * Steps);
        Gear->X = Gear->X + (Gear->dX * Steps);
    }
};
void uvisualgearshandlers_doStepHealthTagWorkUnderWater(PVisualGear Gear,LongWord Steps)
{
    if((fpcrtl_round(Gear->Y) - 10) < cWaterLine)
    {
        uvisualgearslist_DeleteVisualGear(Gear);
    }
    else
    {
        Gear->X = Gear->X + (Gear->dX * Steps);
        Gear->Y = Gear->Y + (Gear->dY * Steps);
    }
};
void uvisualgearshandlers_doStepHealthTag(PVisualGear Gear,LongWord Steps)
{
    string255 s;
    s = uutils_IntToStr(Gear->State);
    if(Gear->Hedgehog != NULL)
    {
        Gear->Tex = urenderutils_RenderStringTex(fpcrtl_str2astr(s), (*(*(*Gear->Hedgehog).Team).Clan).Color, fnt16);
    }
    else
    {
        Gear->Tex = urenderutils_RenderStringTex(fpcrtl_str2astr(s), cWhiteColor, fnt16);
    }
    Gear->doStep = &(uvisualgearshandlers_doStepHealthTagWork);
    if(((fpcrtl_round(Gear->Y) > cWaterLine) && (Gear->Frame == 0)) && (Gear->FrameTicks == 0))
    {
        Gear->doStep = &(uvisualgearshandlers_doStepHealthTagWorkUnderWater);
    }
    Gear->Y = Gear->Y - (*Gear->Tex).h;
    if(Steps > 1)
    {
        Gear->doStep(Gear, Steps - 1);
    }
};
void uvisualgearshandlers_doStepSmokeTrace(PVisualGear Gear,LongWord Steps)
{
    Gear->Timer += Steps;
    if(Gear->Timer > 64)
    {
        if(Gear->State == 0)
        {
            uvisualgearslist_DeleteVisualGear(Gear);
            return;
        }
        Gear->State -= Gear->Timer / 65;
        Gear->Timer = Gear->Timer % 65;
    }
    Gear->dX = Gear->dX + (cWindSpeedf * Steps);
    Gear->X = Gear->X + Gear->dX;
};
void uvisualgearshandlers_doStepExplosionWork(PVisualGear Gear,LongWord Steps)
{
    Gear->Timer += Steps;
    if(Gear->Timer > 75)
    {
        Gear->State += Gear->Timer / 76;
        Gear->Timer = Gear->Timer % 76;
        if(Gear->State > 5)
        {
            uvisualgearslist_DeleteVisualGear(Gear);
        }
    }
};
void uvisualgearshandlers_doStepExplosion(PVisualGear Gear,LongWord Steps)
{
    LongWord i;
    LongInt gX;
    LongInt gY;
    PVisualGear vg;
    gX = fpcrtl_round(Gear->X);
    gY = fpcrtl_round(Gear->Y);
    {i = 0;
     LongWord i__end__ = 31;
     if (i <= i__end__) do {
                               vg = uvisualgearslist_AddVisualGear_3(gX, gY, vgtFire);
                               if(vg != NULL)
                               {
                                   vg->State = gsttmpFlag;
                                   vg->FrameTicks += vg->FrameTicks;
                               }
                           } while(i++ != i__end__);}
    {i = 0;
     LongWord i__end__ = 8;
     if (i <= i__end__) do {
                               uvisualgearslist_AddVisualGear_3(gX, gY, vgtExplPart);
                           } while(i++ != i__end__);}
    {i = 0;
     LongWord i__end__ = 8;
     if (i <= i__end__) do {
                               uvisualgearslist_AddVisualGear_3(gX, gY, vgtExplPart2);
                           } while(i++ != i__end__);}
    Gear->doStep = &(uvisualgearshandlers_doStepExplosionWork);
    if(Steps > 1)
    {
        Gear->doStep(Gear, Steps - 1);
    }
};
void uvisualgearshandlers_doStepBigExplosionWork(PVisualGear Gear,LongWord Steps)
{
    LongInt maxMovement;
    Gear->Timer += Steps;
    if((Gear->Timer & 5) == 0)
    {
        maxMovement = uutils_Max(1, 13 - ((Gear->Timer * 15) / 250));
        uworld_ShakeCamera(maxMovement);
    }
    if(Gear->Timer > 250)
    {
        uvisualgearslist_DeleteVisualGear(Gear);
    }
};
void uvisualgearshandlers_doStepBigExplosion(PVisualGear Gear,LongWord Steps)
{
    LongWord i;
    LongInt gX;
    LongInt gY;
    PVisualGear vg;
    gX = fpcrtl_round(Gear->X);
    gY = fpcrtl_round(Gear->Y);
    uvisualgearslist_AddVisualGear_3(gX, gY, vgtSmokeRing);
    {i = 0;
     LongWord i__end__ = 46;
     if (i <= i__end__) do {
                               vg = uvisualgearslist_AddVisualGear_3(gX, gY, vgtFire);
                               if(vg != NULL)
                               {
                                   vg->State = gsttmpFlag;
                                   vg->FrameTicks += vg->FrameTicks;
                               }
                           } while(i++ != i__end__);}
    {i = 0;
     LongWord i__end__ = 15;
     if (i <= i__end__) do {
                               uvisualgearslist_AddVisualGear_3(gX, gY, vgtExplPart);
                           } while(i++ != i__end__);}
    {i = 0;
     LongWord i__end__ = 15;
     if (i <= i__end__) do {
                               uvisualgearslist_AddVisualGear_3(gX, gY, vgtExplPart2);
                           } while(i++ != i__end__);}
    Gear->doStep = &(uvisualgearshandlers_doStepBigExplosionWork);
    if(Steps > 1)
    {
        Gear->doStep(Gear, Steps - 1);
    }
};
void uvisualgearshandlers_doStepChunk(PVisualGear Gear,LongWord Steps)
{
    Gear->X = Gear->X + (Gear->dX * Steps);
    Gear->Y = Gear->Y + (Gear->dY * Steps);
    Gear->dY = Gear->dY + (cGravityf * Steps);
    Gear->Angle = fpcrtl_round(Gear->Angle + Steps) % cMaxAngle;
    if(ucollisions_CheckCoordInWater(fpcrtl_round(Gear->X), fpcrtl_round(Gear->Y)))
    {
        if((cReducedQuality & rqPlainSplash) == 0)
        {
            uvisualgearslist_AddVisualGear_3(fpcrtl_round(Gear->X), fpcrtl_round(Gear->Y), vgtDroplet);
        }
        uvisualgearslist_DeleteVisualGear(Gear);
    }
};
void uvisualgearshandlers_doStepBulletHit(PVisualGear Gear,LongWord Steps)
{
    if(Gear->FrameTicks <= Steps)
    {
        uvisualgearslist_DeleteVisualGear(Gear);
    }
    else
    {
        Gear->FrameTicks -= Steps;
    }
};
void uvisualgearshandlers_doStepCircle(PVisualGear Gear,LongWord Steps)
{
    LongInt tmp;
    LongWord i;
    {
        if((*Gear).Frame != 0)
        {
            {i = 1;
             LongWord i__end__ = Steps;
             if (i <= i__end__) do {
                                       ++(*Gear).FrameTicks;
                                       if(((*Gear).FrameTicks % (*Gear).Frame) == 0)
                                       {
                                           tmp = Gear->Tint & 0xff;
                                           if((*Gear).tdY >= 0)
                                           {
                                               ++tmp;
                                           }
                                           else
                                           {
                                               --tmp;
                                           }
                                           if(tmp < fpcrtl_round((*Gear).dX))
                                           {
                                               (*Gear).tdY = 1;
                                           }
                                           if(tmp > fpcrtl_round((*Gear).dY))
                                           {
                                               (*Gear).tdY = -1;
                                           }
                                           if(tmp > 255)
                                           {
                                               tmp = 255;
                                           }
                                           if(tmp < 0)
                                           {
                                               tmp = 0;
                                           }
                                           Gear->Tint = (Gear->Tint & 0xffffff00) | ((LongWord)tmp);
                                       }
                                   } while(i++ != i__end__);}
        }
    }
};
static PVisualGear currwindbar = NULL;
void uvisualgearshandlers_doStepSmoothWindBarWork(PVisualGear Gear,LongWord Steps)
{
    enum{maxWindBarWidth = 73};
    if(currwindbar == Gear)
    {
        Gear->Timer += Steps;
        while(Gear->Timer >= 10)
        {
            Gear->Timer -= 10;
            if(WindBarWidth < Gear->Tag)
            {
                ++WindBarWidth;
            }
            else
            {
                if(WindBarWidth > Gear->Tag)
                {
                    --WindBarWidth;
                }
            }
            if(WindBarWidth > maxWindBarWidth)
            {
                WindBarWidth = maxWindBarWidth;
            }
            if(WindBarWidth < -maxWindBarWidth)
            {
                WindBarWidth = -maxWindBarWidth;
            }
        }
        if(cWindSpeedf > Gear->dAngle)
        {
            cWindSpeedf = cWindSpeedf - (Gear->Angle * Steps);
            if(cWindSpeedf < Gear->dAngle)
            {
                cWindSpeedf = Gear->dAngle;
            }
        }
        else
        {
            if(cWindSpeedf < Gear->dAngle)
            {
                cWindSpeedf = cWindSpeedf + (Gear->Angle * Steps);
                if(cWindSpeedf > Gear->dAngle)
                {
                    cWindSpeedf = Gear->dAngle;
                }
            }
        }
    }
    if((((WindBarWidth == Gear->Tag) || (fpcrtl_abs(WindBarWidth) >= maxWindBarWidth)) && (cWindSpeedf == Gear->dAngle)) || (currwindbar != Gear))
    {
        if(currwindbar == Gear)
        {
            currwindbar = NULL;
        }
        uvisualgearslist_DeleteVisualGear(Gear);
    }
};
void uvisualgearshandlers_doStepSmoothWindBar(PVisualGear Gear,LongWord Steps)
{
    currwindbar = Gear;
    Gear->doStep = &(uvisualgearshandlers_doStepSmoothWindBarWork);
    uvisualgearshandlers_doStepSmoothWindBarWork(Gear, Steps);
};
void uvisualgearshandlers_doStepStraightShot(PVisualGear Gear,LongWord Steps)
{
    Gear->X = Gear->X + (Gear->dX * Steps);
    Gear->Y = Gear->Y - (Gear->dY * Steps);
    Gear->dY = Gear->dY + (Gear->tdY * Steps);
    Gear->dX = Gear->dX + (Gear->tdX * Steps);
    if(Gear->FrameTicks <= Steps)
    {
        uvisualgearslist_DeleteVisualGear(Gear);
    }
    else
    {
        Gear->FrameTicks -= Steps;
        if((Gear->FrameTicks < 501) && ((Gear->FrameTicks % 5) == 0))
        {
            Gear->Tint = (Gear->Tint & 0xffffff00) | (((Gear->Tint & 0x000000ff) * Gear->FrameTicks) / 500);
        }
    }
};
void uvisualgearshandlers_doStepNoPlaceWarn(PVisualGear Gear,LongWord Steps)
{
    if(Gear->FrameTicks <= Steps)
    {
        uvisualgearslist_DeleteVisualGear(Gear);
    }
    else
    {
        Gear->FrameTicks -= Steps;
        if(((Gear->FrameTicks / 256) % 2) == 0)
        {
            Gear->Tint = 0xff400000;
        }
        else
        {
            Gear->Tint = 0xff000000;
        }
        Gear->Tint = (Gear->Tint & ~0xff) | ((255 * Gear->FrameTicks) / 3000);
    }
};
typedef utypes_TVGearStepProcedure handlers_tt[34];
static handlers_tt handlers = {&uvisualgearshandlers_doStepFlake,
                               &uvisualgearshandlers_doStepCloud,
                               &uvisualgearshandlers_doStepExpl,
                               &uvisualgearshandlers_doStepExpl,
                               &uvisualgearshandlers_doStepFire,
                               &uvisualgearshandlers_doStepSmallDamageTag,
                               &uvisualgearshandlers_doStepTeamHealthSorter,
                               &uvisualgearshandlers_doStepSpeechBubble,
                               &uvisualgearshandlers_doStepBubble,
                               &uvisualgearshandlers_doStepSteam,
                               &uvisualgearshandlers_doStepAmmo,
                               &uvisualgearshandlers_doStepSmoke,
                               &uvisualgearshandlers_doStepSmoke,
                               &uvisualgearshandlers_doStepShell,
                               &uvisualgearshandlers_doStepDust,
                               &uvisualgearshandlers_doStepSplash,
                               &uvisualgearshandlers_doStepDroplet,
                               &uvisualgearshandlers_doStepSmokeRing,
                               &uvisualgearshandlers_doStepBeeTrace,
                               &uvisualgearshandlers_doStepEgg,
                               &uvisualgearshandlers_doStepFeather,
                               &uvisualgearshandlers_doStepHealthTag,
                               &uvisualgearshandlers_doStepSmokeTrace,
                               &uvisualgearshandlers_doStepSmokeTrace,
                               &uvisualgearshandlers_doStepExplosion,
                               &uvisualgearshandlers_doStepBigExplosion,
                               &uvisualgearshandlers_doStepChunk,
                               &uvisualgearshandlers_doStepNote,
                               &uvisualgearshandlers_doStepLineTrail,
                               &uvisualgearshandlers_doStepBulletHit,
                               &uvisualgearshandlers_doStepCircle,
                               &uvisualgearshandlers_doStepSmoothWindBar,
                               &uvisualgearshandlers_doStepStraightShot,
                               &uvisualgearshandlers_doStepNoPlaceWarn};
void uvisualgearshandlers_initModule()
{
    fpcrtl_memcpy(doStepVGHandlers, handlers, sizeof(handlers));
};
