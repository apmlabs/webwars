#include "fpcrtl.h"

#include "uLandGenPerlin.h"
#include "uVariables.h"
#include "uConsts.h"
#include "uRandom.h"
#include "uUtils.h"
#include "uLandUtils.h"
typedef LongInt p_tt[(511 + 1)];
static p_tt p;
typedef LongInt fadear_tt[256];
static fadear_tt fadear = {0,
                           0,
                           0,
                           0,
                           0,
                           0,
                           0,
                           0,
                           1,
                           1,
                           2,
                           3,
                           3,
                           4,
                           6,
                           7,
                           9,
                           10,
                           12,
                           14,
                           17,
                           19,
                           22,
                           25,
                           29,
                           32,
                           36,
                           40,
                           45,
                           49,
                           54,
                           60,
                           65,
                           71,
                           77,
                           84,
                           91,
                           98,
                           105,
                           113,
                           121,
                           130,
                           139,
                           148,
                           158,
                           167,
                           178,
                           188,
                           199,
                           211,
                           222,
                           234,
                           247,
                           259,
                           273,
                           286,
                           300,
                           314,
                           329,
                           344,
                           359,
                           374,
                           390,
                           407,
                           424,
                           441,
                           458,
                           476,
                           494,
                           512,
                           531,
                           550,
                           570,
                           589,
                           609,
                           630,
                           651,
                           672,
                           693,
                           715,
                           737,
                           759,
                           782,
                           805,
                           828,
                           851,
                           875,
                           899,
                           923,
                           948,
                           973,
                           998,
                           1023,
                           1049,
                           1074,
                           1100,
                           1127,
                           1153,
                           1180,
                           1207,
                           1234,
                           1261,
                           1289,
                           1316,
                           1344,
                           1372,
                           1400,
                           1429,
                           1457,
                           1486,
                           1515,
                           1543,
                           1572,
                           1602,
                           1631,
                           1660,
                           1690,
                           1719,
                           1749,
                           1778,
                           1808,
                           1838,
                           1868,
                           1898,
                           1928,
                           1958,
                           1988,
                           2018,
                           2048,
                           2077,
                           2107,
                           2137,
                           2167,
                           2197,
                           2227,
                           2257,
                           2287,
                           2317,
                           2346,
                           2376,
                           2405,
                           2435,
                           2464,
                           2493,
                           2523,
                           2552,
                           2580,
                           2609,
                           2638,
                           2666,
                           2695,
                           2723,
                           2751,
                           2779,
                           2806,
                           2834,
                           2861,
                           2888,
                           2915,
                           2942,
                           2968,
                           2995,
                           3021,
                           3046,
                           3072,
                           3097,
                           3122,
                           3147,
                           3172,
                           3196,
                           3220,
                           3244,
                           3267,
                           3290,
                           3313,
                           3336,
                           3358,
                           3380,
                           3402,
                           3423,
                           3444,
                           3465,
                           3486,
                           3506,
                           3525,
                           3545,
                           3564,
                           3583,
                           3601,
                           3619,
                           3637,
                           3654,
                           3672,
                           3688,
                           3705,
                           3721,
                           3736,
                           3751,
                           3766,
                           3781,
                           3795,
                           3809,
                           3822,
                           3836,
                           3848,
                           3861,
                           3873,
                           3884,
                           3896,
                           3907,
                           3917,
                           3928,
                           3937,
                           3947,
                           3956,
                           3965,
                           3974,
                           3982,
                           3990,
                           3997,
                           4004,
                           4011,
                           4018,
                           4024,
                           4030,
                           4035,
                           4041,
                           4046,
                           4050,
                           4055,
                           4059,
                           4063,
                           4066,
                           4070,
                           4073,
                           4076,
                           4078,
                           4081,
                           4083,
                           4085,
                           4086,
                           4088,
                           4089,
                           4091,
                           4092,
                           4092,
                           4093,
                           4094,
                           4094,
                           4095,
                           4095,
                           4095,
                           4095,
                           4095,
                           4095,
                           4095};
LongInt ulandgenperlin_fade(LongInt t)
{
    LongInt fade_result;
    LongInt t0;
    LongInt t1;
    t0 = fadear[t >> 8];
    if(t0 == fadear[255])
    {
        t1 = t0;
    }
    else
    {
        t1 = fadear[(t >> 8) + 1];
    }
    fade_result = t0 + (((t & 255) * (t1 - t0)) >> 8);
    return fade_result;
};
LongInt ulandgenperlin_lerp(LongInt t,LongInt a,LongInt b)
{
    LongInt lerp_result;
    lerp_result = a + (((((Int64)b) - a) * t) >> 12);
    return lerp_result;
};
LongInt ulandgenperlin_grad(LongInt hash,LongInt x,LongInt y)
{
    LongInt grad_result;
    LongInt h;
    LongInt v;
    LongInt u;
    h = hash & 15;
    if(h < 8)
    {
        u = x;
    }
    else
    {
        u = y;
    }
    if(h < 4)
    {
        v = y;
    }
    else
    {
        if((h == 12) || (h == 14))
        {
            v = x;
        }
        else
        {
            v = 0;
        }
    }
    if((h & 1) != 0)
    {
        u = -u;
    }
    if((h & 2) != 0)
    {
        v = -v;
    }
    grad_result = u + v;
    return grad_result;
};
LongInt ulandgenperlin_inoise(LongInt x,LongInt y)
{
    LongInt inoise_result;
    enum{N = 0x10000};
    LongInt xx;
    LongInt yy;
    LongInt u;
    LongInt v;
    LongInt A;
    LongInt AA;
    LongInt AB;
    LongInt B;
    LongInt BA;
    LongInt BB;
    xx = (x >> 16) & 255;
    yy = (y >> 16) & 255;
    x = x & 0xffff;
    y = y & 0xffff;
    u = ulandgenperlin_fade(x);
    v = ulandgenperlin_fade(y);
    A = p[xx] + yy;
    AA = p[A];
    AB = p[A + 1];
    B = p[xx + 1] + yy;
    BA = p[B];
    BB = p[B + 1];
    inoise_result = ulandgenperlin_lerp(v, ulandgenperlin_lerp(u, ulandgenperlin_grad(p[AA], x, y), ulandgenperlin_grad(p[BA], x - N, y)), ulandgenperlin_lerp(u, ulandgenperlin_grad(p[AB], x, y - N), ulandgenperlin_grad(p[BB], x - N, y - N)));
    return inoise_result;
};
void ulandgenperlin_inoise_setup()
{
    LongWord i;
    LongWord ii;
    LongWord t;
    {i = 0;
     LongWord i__end__ = 254;
     if (i <= i__end__) do {
                               p[i] = i + 1;
                           } while(i++ != i__end__);}
    p[255] = 0;
    {i = 0;
     LongWord i__end__ = 254;
     if (i <= i__end__) do {
                               ii = urandom_GetRandom(256 - i) + i;
                               t = p[i];
                               p[i] = p[ii];
                               p[ii] = t;
                           } while(i++ != i__end__);}
    {i = 0;
     LongWord i__end__ = 255;
     if (i <= i__end__) do {
                               p[256 + i] = p[i];
                           } while(i++ != i__end__);}
};
enum{width = 4096};
enum{height = 2048};
enum{minY = 500};
enum{margin = 200};
void ulandgenperlin_GenPerlin()
{
    LongInt y;
    LongInt x;
    LongInt di;
    LongInt dj;
    LongInt r;
    LongInt param1;
    LongInt param2;
    LongInt rCutoff;
    LongInt detail;
    Int64 df;
    param1 = cTemplateFilter / 3;
    param2 = cTemplateFilter % 3;
    rCutoff = uutils_Min(uutils_Max((26 - cFeatureSize) * 4, 15), 85);
    detail = ((26 - cFeatureSize) * 16000) + 50000;
    df = detail * (6 - (param2 * 2));
    if(param1 == 0)
    {
        if(param2 == 0)
        {
            MaxHedgehogs = 12 + (1 * (cFeatureSize - 1));
        }
        else
        {
            if(param2 == 1)
            {
                MaxHedgehogs = 14 + uutils_Max(0, 1 * (cFeatureSize - 3));
            }
            else
            {
                if(param2 == 2)
                {
                    MaxHedgehogs = 16 + uutils_Max(0, 1 * (cFeatureSize - 5));
                }
            }
        }
        if(MaxHedgehogs > 24)
        {
            MaxHedgehogs = 24;
        }
    }
    else
    {
        if((param1 == 1) && (cFeatureSize <= 25))
        {
            if(param2 == 0)
            {
                MaxHedgehogs = 32 + (((((25 - (cFeatureSize - 1)) * 1000000) / 24) * 32) / 1000000);
            }
            else
            {
                if(param2 == 1)
                {
                    MaxHedgehogs = 28 + (((((25 - (cFeatureSize - 1)) * 1000000) / 24) * 28) / 1000000);
                }
                else
                {
                    if(param2 == 2)
                    {
                        MaxHedgehogs = 24 + (((((25 - (cFeatureSize - 1)) * 1000000) / 24) * 24) / 1000000);
                    }
                }
            }
        }
    }
    if((MaxHedgehogs > 0) && ((MaxHedgehogs % 2) == 1))
    {
        MaxHedgehogs = MaxHedgehogs - 1;
    }
    ulandgenperlin_inoise_setup();
    {y = minY;
     LongInt y__end__ = ((int)(height) - 1);
     if (y <= y__end__) do {
                               di = (df * y) / height;
                               {x = 0;
                                LongInt x__end__ = ((int)(width) - 1);
                                if (x <= x__end__) do {
                                                          dj = (df * x) / width;
                                                          r = (((fpcrtl_abs(ulandgenperlin_inoise(di, dj)) + (y * 4)) % 65536) - ((height - y) * 8)) / 256;
                                                          if((x < margin) || (x > (width - margin)))
                                                          {
                                                              r = ((r - fpcrtl_abs(x - (width / 2))) + (width / 2)) - margin;
                                                          }
                                                          if(r < rCutoff)
                                                          {
                                                              ulandutils_LandSet(y, x, 0);
                                                          }
                                                          else
                                                          {
                                                              if(param1 == 0)
                                                              {
                                                                  ulandutils_LandSet(y, x, lfObjMask);
                                                              }
                                                              else
                                                              {
                                                                  ulandutils_LandSet(y, x, lfBasic);
                                                              }
                                                          }
                                                      } while(x++ != x__end__);}
                           } while(y++ != y__end__);}
    if(param1 == 0)
    {
        {x = 0;
         LongInt x__end__ = width;
         if (x <= x__end__) do {
                                   if(ulandutils_LandGet(height - 1, x) == lfObjMask)
                                   {
                                       ulandutils_FillLand(x, height - 1, 0, lfBasic);
                                   }
                               } while(x++ != x__end__);}
        {y = minY;
         LongInt y__end__ = LAND_HEIGHT - 1;
         if (y <= y__end__) do {
                                   {x = 0;
                                    LongInt x__end__ = LAND_WIDTH - 1;
                                    if (x <= x__end__) do {
                                                              if(ulandutils_LandGet(y, x) == lfObjMask)
                                                              {
                                                                  ulandutils_LandSet(y, x, 0);
                                                              }
                                                          } while(x++ != x__end__);}
                               } while(y++ != y__end__);}
    }
    playWidth = width;
    playHeight = height;
    leftX = 0;
    rightX = playWidth - 1;
    topY = 0;
    hasBorder = false;
};
