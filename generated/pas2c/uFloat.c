#include "fpcrtl.h"

#include "uFloat.h"
boolean ufloat_hwFloat_hwFloat_op_eq(hwFloat z1,hwFloat z2);
boolean ufloat_hwFloat_hwFloat_op_neq(hwFloat z1,hwFloat z2);
hwFloat ufloat_hwFloat_hwFloat_op_add(hwFloat z1,hwFloat z2);
hwFloat ufloat_hwFloat_hwFloat_op_sub(hwFloat z1,hwFloat z2);
hwFloat ufloat_hwFloat_op_sub(hwFloat z1);
hwFloat ufloat_hwFloat_hwFloat_op_mul(hwFloat z1,hwFloat z2);
hwFloat ufloat_hwFloat_LongInt_op_mul(hwFloat z1,LongInt z2);
hwFloat ufloat_hwFloat_hwFloat_op_div(hwFloat z1,hwFloat z2);
hwFloat ufloat_hwFloat_LongInt_op_div(hwFloat z1,LongInt z2);
boolean ufloat_hwFloat_hwFloat_op_lt(hwFloat z1,hwFloat z2);
boolean ufloat_hwFloat_hwFloat_op_gt(hwFloat z1,hwFloat z2);
hwFloat _1div1024 = {
                        .isNegative = false,
                        .QWordValue = 4194304
                    };
hwFloat _1div10000 = {
                         .isNegative = false,
                         .QWordValue = 429496
                     };
hwFloat _1div50000 = {
                         .isNegative = false,
                         .QWordValue = 85899
                     };
hwFloat _1div100000 = {
                          .isNegative = false,
                          .QWordValue = 42950
                      };
hwFloat _1div3 = {
                     .isNegative = false,
                     .QWordValue = 1431655766
                 };
hwFloat hwPi = {
                   .isNegative = false,
                   .QWordValue = 13493037704
               };
hwFloat _0_000004 = {
                        .isNegative = false,
                        .QWordValue = 17179
                    };
hwFloat _0_000064 = {
                        .isNegative = false,
                        .QWordValue = 274878
                    };
hwFloat _0_0002 = {
                      .isNegative = false,
                      .QWordValue = 858993
                  };
hwFloat _0_0005 = {
                      .isNegative = false,
                      .QWordValue = 2147484
                  };
hwFloat _0_001 = {
                     .isNegative = false,
                     .QWordValue = 4294967
                 };
hwFloat _0_003 = {
                     .isNegative = false,
                     .QWordValue = 12884902
                 };
hwFloat _0_0032 = {
                      .isNegative = false,
                      .QWordValue = 13743895
                  };
hwFloat _0_004 = {
                     .isNegative = false,
                     .QWordValue = 17179869
                 };
hwFloat _0_005 = {
                     .isNegative = false,
                     .QWordValue = 21474836
                 };
hwFloat _0_008 = {
                     .isNegative = false,
                     .QWordValue = 34359738
                 };
hwFloat _0_01 = {
                    .isNegative = false,
                    .QWordValue = 42949673
                };
hwFloat _0_0128 = {
                      .isNegative = false,
                      .QWordValue = 54975581
                  };
hwFloat _0_02 = {
                    .isNegative = false,
                    .QWordValue = 85899345
                };
hwFloat _0_03 = {
                    .isNegative = false,
                    .QWordValue = 128849018
                };
hwFloat _0_05 = {
                    .isNegative = false,
                    .QWordValue = 214748365
                };
hwFloat _0_07 = {
                    .isNegative = false,
                    .QWordValue = 300647710
                };
hwFloat _0_08 = {
                    .isNegative = false,
                    .QWordValue = 343597383
                };
hwFloat _0_1 = {
                   .isNegative = false,
                   .QWordValue = 429496730
               };
hwFloat _0_15 = {
                    .isNegative = false,
                    .QWordValue = 644245094
                };
hwFloat _0_2 = {
                   .isNegative = false,
                   .QWordValue = 858993459
               };
hwFloat _0_25 = {
                    .isNegative = false,
                    .QWordValue = 1073741824
                };
hwFloat _0_3 = {
                   .isNegative = false,
                   .QWordValue = 1288490189
               };
hwFloat _0_35 = {
                    .isNegative = false,
                    .QWordValue = 1503238553
                };
hwFloat _0_375 = {
                     .isNegative = false,
                     .QWordValue = ((4294967296 * 3) / 8)
                 };
hwFloat _0_39 = {
                    .isNegative = false,
                    .QWordValue = 1675037245
                };
hwFloat _0_4 = {
                   .isNegative = false,
                   .QWordValue = 1717986918
               };
hwFloat _0_45 = {
                    .isNegative = false,
                    .QWordValue = 1932735283
                };
hwFloat _0_5 = {
                   .isNegative = false,
                   .QWordValue = 2147483648
               };
hwFloat _0_55 = {
                    .isNegative = false,
                    .QWordValue = 2362232012
                };
hwFloat _0_6 = {
                   .isNegative = false,
                   .QWordValue = 2576980377
               };
hwFloat _0_64 = {
                    .isNegative = false,
                    .QWordValue = 2748779064
                };
hwFloat _0_7 = {
                   .isNegative = false,
                   .QWordValue = 3006477107
               };
hwFloat _0_8 = {
                   .isNegative = false,
                   .QWordValue = 3435973837
               };
hwFloat _0_84 = {
                    .isNegative = false,
                    .QWordValue = 3607772528
                };
hwFloat _0_87 = {
                    .isNegative = false,
                    .QWordValue = 3736621547
                };
hwFloat _0_9 = {
                   .isNegative = false,
                   .QWordValue = 3865470566
               };
hwFloat _0_93 = {
                    .isNegative = false,
                    .QWordValue = 3994319585
                };
hwFloat _0_96 = {
                    .isNegative = false,
                    .QWordValue = 4123168604
                };
hwFloat _0_995 = {
                     .isNegative = false,
                     .QWordValue = 4273492459
                 };
hwFloat _0_999 = {
                     .isNegative = false,
                     .QWordValue = 4290672328
                 };
hwFloat _0 = {
                 .isNegative = false,
                 .QWordValue = 0
             };
hwFloat _1 = {
                 .isNegative = false,
                 .QWordValue = 4294967296
             };
hwFloat _1_2 = {
                   .isNegative = false,
                   .QWordValue = (((4294967296 * 6) / 5) + 1)
               };
hwFloat _1_5 = {
                   .isNegative = false,
                   .QWordValue = ((4294967296 * 3) / 2)
               };
hwFloat _1_6 = {
                   .isNegative = false,
                   .QWordValue = ((4294967296 * 8) / 5)
               };
hwFloat _1_9 = {
                   .isNegative = false,
                   .QWordValue = 8160437862
               };
hwFloat _2 = {
                 .isNegative = false,
                 .QWordValue = (4294967296 * 2)
             };
hwFloat _2_4 = {
                   .isNegative = false,
                   .QWordValue = ((4294967296 * 12) / 5)
               };
hwFloat _3 = {
                 .isNegative = false,
                 .QWordValue = (4294967296 * 3)
             };
hwFloat _3_2 = {
                   .isNegative = false,
                   .QWordValue = ((4294967296 * 16) / 5)
               };
hwFloat _PI = {
                  .isNegative = false,
                  .QWordValue = 13493037704
              };
hwFloat _4 = {
                 .isNegative = false,
                 .QWordValue = (4294967296 * 4)
             };
hwFloat _4_5 = {
                   .isNegative = false,
                   .QWordValue = ((4294967296 * 9) / 2)
               };
hwFloat _5 = {
                 .isNegative = false,
                 .QWordValue = (4294967296 * 5)
             };
hwFloat _6 = {
                 .isNegative = false,
                 .QWordValue = (4294967296 * 6)
             };
hwFloat _6_4 = {
                   .isNegative = false,
                   .QWordValue = ((4294967296 * 32) / 5)
               };
hwFloat _7 = {
                 .isNegative = false,
                 .QWordValue = (4294967296 * 7)
             };
hwFloat _10 = {
                  .isNegative = false,
                  .QWordValue = (4294967296 * 10)
              };
hwFloat _12 = {
                  .isNegative = false,
                  .QWordValue = (4294967296 * 12)
              };
hwFloat _16 = {
                  .isNegative = false,
                  .QWordValue = (4294967296 * 16)
              };
hwFloat _19 = {
                  .isNegative = false,
                  .QWordValue = (4294967296 * 19)
              };
hwFloat _20 = {
                  .isNegative = false,
                  .QWordValue = (4294967296 * 20)
              };
hwFloat _25 = {
                  .isNegative = false,
                  .QWordValue = (4294967296 * 25)
              };
hwFloat _30 = {
                  .isNegative = false,
                  .QWordValue = (4294967296 * 30)
              };
hwFloat _40 = {
                  .isNegative = false,
                  .QWordValue = (4294967296 * 40)
              };
hwFloat _41 = {
                  .isNegative = false,
                  .QWordValue = (4294967296 * 41)
              };
hwFloat _49 = {
                  .isNegative = false,
                  .QWordValue = (4294967296 * 49)
              };
hwFloat _50 = {
                  .isNegative = false,
                  .QWordValue = (4294967296 * 50)
              };
hwFloat _70 = {
                  .isNegative = false,
                  .QWordValue = (4294967296 * 70)
              };
hwFloat _90 = {
                  .isNegative = false,
                  .QWordValue = (4294967296 * 90)
              };
hwFloat _128 = {
                   .isNegative = false,
                   .QWordValue = (4294967296 * 128)
               };
hwFloat _180 = {
                   .isNegative = false,
                   .QWordValue = (4294967296 * 180)
               };
hwFloat _250 = {
                   .isNegative = false,
                   .QWordValue = (4294967296 * 250)
               };
hwFloat _256 = {
                   .isNegative = false,
                   .QWordValue = (4294967296 * 256)
               };
hwFloat _300 = {
                   .isNegative = false,
                   .QWordValue = (4294967296 * 300)
               };
hwFloat _360 = {
                   .isNegative = false,
                   .QWordValue = (4294967296 * 360)
               };
hwFloat _450 = {
                   .isNegative = false,
                   .QWordValue = (4294967296 * 450)
               };
hwFloat _900 = {
                   .isNegative = false,
                   .QWordValue = (4294967296 * 900)
               };
hwFloat _1000 = {
                    .isNegative = false,
                    .QWordValue = (4294967296 * 1000)
                };
hwFloat _1024 = {
                    .isNegative = false,
                    .QWordValue = (4294967296 * 1024)
                };
hwFloat _2048 = {
                    .isNegative = false,
                    .QWordValue = (4294967296 * 2048)
                };
hwFloat _4096 = {
                    .isNegative = false,
                    .QWordValue = (4294967296 * 4096)
                };
hwFloat _10000 = {
                     .isNegative = false,
                     .QWordValue = (4294967296 * 10000)
                 };
hwFloat cLittle = {
                      .isNegative = false,
                      .QWordValue = 1
                  };
hwFloat cHHKick = {
                      .isNegative = false,
                      .QWordValue = 42949673
                  };
#include "uSinTable.h"
hwFloat ufloat_int2hwFloat(LongInt i)
{
    hwFloat int2hwfloat_result;
    int2hwfloat_result.isNegative = i < 0;
    int2hwfloat_result.Round = fpcrtl_abs(i);
    int2hwfloat_result.Frac = 0;
    return int2hwfloat_result;
};
extended ufloat_hwFloat2Float(hwFloat i)
{
    extended hwfloat2float_result;
    hwfloat2float_result = (i.Frac /(float) 0x100000000) + i.Round;
    if(i.isNegative)
    {
        hwfloat2float_result = -hwfloat2float_result;
    }
    return hwfloat2float_result;
};
boolean ufloat_hwFloat_hwFloat_op_eq(hwFloat z1,hwFloat z2)
{
    boolean z_result;
    z_result = (z1.isNegative == z2.isNegative) && (z1.QWordValue == z2.QWordValue);
    return z_result;
};
boolean ufloat_hwFloat_hwFloat_op_neq(hwFloat z1,hwFloat z2)
{
    boolean z_result;
    z_result = (z1.isNegative != z2.isNegative) || (z1.QWordValue != z2.QWordValue);
    return z_result;
};
hwFloat ufloat_hwFloat_hwFloat_op_add(hwFloat z1,hwFloat z2)
{
    hwFloat z_result;
    if(z1.isNegative == z2.isNegative)
    {
        z_result.isNegative = z1.isNegative;
        z_result.QWordValue = z1.QWordValue + z2.QWordValue;
    }
    else
    {
        if(z1.QWordValue > z2.QWordValue)
        {
            z_result.isNegative = z1.isNegative;
            z_result.QWordValue = ((int64_t) (z1.QWordValue)) - ((int64_t) (z2.QWordValue));
        }
        else
        {
            z_result.isNegative = z2.isNegative;
            z_result.QWordValue = ((int64_t) (z2.QWordValue)) - ((int64_t) (z1.QWordValue));
        }
    }
    return z_result;
};
hwFloat ufloat_hwFloat_hwFloat_op_sub(hwFloat z1,hwFloat z2)
{
    hwFloat z_result;
    if(z1.isNegative == z2.isNegative)
    {
        if(z1.QWordValue > z2.QWordValue)
        {
            z_result.isNegative = z1.isNegative;
            z_result.QWordValue = ((int64_t) (z1.QWordValue)) - ((int64_t) (z2.QWordValue));
        }
        else
        {
            z_result.isNegative = !z2.isNegative;
            z_result.QWordValue = ((int64_t) (z2.QWordValue)) - ((int64_t) (z1.QWordValue));
        }
    }
    else
    {
        z_result.isNegative = z1.isNegative;
        z_result.QWordValue = z1.QWordValue + z2.QWordValue;
    }
    return z_result;
};
boolean ufloat_isZero(hwFloat z)
{
    boolean iszero_result;
    iszero_result = z.QWordValue == 0;
    return iszero_result;
};
boolean ufloat_hwFloat_hwFloat_op_lt(hwFloat z1,hwFloat z2)
{
    boolean b_result;
    if(z1.isNegative ^ z2.isNegative)
    {
        b_result = z1.isNegative;
    }
    else
    {
        if(z1.QWordValue == z2.QWordValue)
        {
            b_result = false;
        }
        else
        {
            b_result = (z2.QWordValue < z1.QWordValue) == z1.isNegative;
        }
    }
    return b_result;
};
boolean ufloat_hwFloat_hwFloat_op_gt(hwFloat z1,hwFloat z2)
{
    boolean b_result;
    if(z1.isNegative ^ z2.isNegative)
    {
        b_result = z2.isNegative;
    }
    else
    {
        if(z1.QWordValue == z2.QWordValue)
        {
            b_result = false;
        }
        else
        {
            b_result = (z1.QWordValue > z2.QWordValue) != z2.isNegative;
        }
    }
    return b_result;
};
hwFloat ufloat_hwFloat_op_sub(hwFloat z1)
{
    hwFloat z_result;
    z_result = z1;
    z_result.isNegative = !z_result.isNegative;
    return z_result;
};
hwFloat ufloat_hwFloat_hwFloat_op_mul(hwFloat z1,hwFloat z2)
{
    hwFloat z_result;
    z_result.isNegative = z1.isNegative ^ z2.isNegative;
    if((z1.Round == 0) && (z2.Round == 0))
    {
        z_result.QWordValue = (((QWord)z1.Frac) * z2.Frac) >> 32;
    }
    else
    {
        z_result.QWordValue = ((((QWord)z1.Round) * z2.Frac) + (((QWord)z1.Frac) * z2.Round)) + ((((QWord)z1.Frac) * z2.Frac) >> 32);
        z_result.Round = z_result.Round + (((QWord)z1.Round) * z2.Round);
    }
    return z_result;
};
hwFloat ufloat_hwFloat_LongInt_op_mul(hwFloat z1,LongInt z2)
{
    hwFloat z_result;
    z_result.isNegative = z1.isNegative ^ (z2 < 0);
    z_result.QWordValue = z1.QWordValue * fpcrtl_abs(z2);
    return z_result;
};
hwFloat ufloat_hwFloat_hwFloat_op_div(hwFloat z1,hwFloat z2)
{
    hwFloat z_result;
    QWord t;
    z_result.isNegative = z1.isNegative ^ z2.isNegative;
    z_result.Round = z1.QWordValue / z2.QWordValue;
    t = ((int64_t) (z1.QWordValue)) - ((int64_t) ((z2.QWordValue * z_result.Round)));
    z_result.Frac = 0;
    if(t != 0)
    {
        while(((t & 0xff00000000000000) == 0) && ((z2.QWordValue & 0xff00000000000000) == 0))
        {
            t = t << 8;
            z2.QWordValue = z2.QWordValue << 8;
        }
        if(z2.Round > 0)
        {
            z_result.QWordValue += t / z2.Round;
        }
    }
    return z_result;
};
hwFloat ufloat_hwFloat_LongInt_op_div(hwFloat z1,LongInt z2)
{
    hwFloat z_result;
    z_result.isNegative = z1.isNegative ^ (z2 < 0);
    z_result.QWordValue = z1.QWordValue / fpcrtl_abs(z2);
    return z_result;
};
string255 ufloat_cstr(hwFloat z)
{
    string255 cstr_result;
    string255 tmpstr;
    fpcrtl_str(z.Round, cstr_result);
    if(z.Frac != 0)
    {
        fpcrtl_str(z.Frac /(float) 0x100000000, tmpstr);
        fpcrtl_Delete(tmpstr, 1, 2);
        cstr_result = _strconcat(_strappend(cstr_result, 0x2e), fpcrtl_copy(tmpstr, 1, 10));
    }
    if(z.isNegative)
    {
        cstr_result = _strprepend(0x2d, cstr_result);
    }
    return cstr_result;
};
LongInt ufloat_hwRound(hwFloat t)
{
    LongInt hwround_result;
    if(t.isNegative)
    {
        hwround_result = -(t.Round & 0x7fffffff);
    }
    else
    {
        hwround_result = t.Round & 0x7fffffff;
    }
    return hwround_result;
};
hwFloat ufloat_hwAbs(hwFloat t)
{
    hwFloat hwabs_result;
    hwabs_result = t;
    hwabs_result.isNegative = false;
    return hwabs_result;
};
hwFloat ufloat_hwSqr(hwFloat t)
{
    hwFloat hwsqr_result;
    hwsqr_result.isNegative = false;
    hwsqr_result.QWordValue = (((((QWord)t.Round) * t.Round) << 32) + ((((QWord)t.Round) * t.Frac) * 2)) + ((((QWord)t.Frac) * t.Frac) >> 32);
    return hwsqr_result;
};
hwFloat ufloat_hwSqrt1(hwFloat t)
{
    hwFloat hwsqrt1_result;
    enum{pwr = 8};
    QWord rThreshold = (((QWord)1) << (pwr + 32));
    QWord lThreshold = (((QWord)1) << ((pwr / 2) + 32));
    QWord l;
    QWord r;
    hwFloat c;
    hwsqrt1_result.isNegative = false;
    if(t.Round == 0)
    {
        l = t.QWordValue;
        r = 0x100000000;
    }
    else
    {
        if(t.QWordValue > 0xffffffffffff)
        {
            l = 0x10000000000;
            r = 0xffffffffffff;
        }
        else
        {
            if(t.QWordValue >= rThreshold)
            {
                l = lThreshold;
                r = 0x10000000000;
            }
            else
            {
                l = 0x100000000;
                r = lThreshold;
            }
        }
    }
    do {
           c.QWordValue = (l + r) >> 1;
           if(ufloat_hwSqr(c).QWordValue > t.QWordValue)
           {
               r = c.QWordValue;
           }
           else
           {
               l = c.QWordValue;
           }
       } while(!((((int64_t) (r)) - ((int64_t) (l))) <= 1));
    hwsqrt1_result.QWordValue = l;
    return hwsqrt1_result;
};
hwFloat ufloat_hwSqrt(hwFloat x)
{
    hwFloat hwsqrt_result;
    QWord r;
    QWord t;
    QWord s;
    QWord q;
    Integer i;
    hwsqrt_result.isNegative = false;
    t = 0x4000000000000000;
    r = 0;
    q = x.QWordValue;
    {i = 0;
     Integer i__end__ = 31;
     if (i <= i__end__) do {
                               s = r + t;
                               r = r >> 1;
                               if(s <= q)
                               {
                                   q -= s;
                                   r += t;
                               }
                               t = t >> 2;
                           } while(i++ != i__end__);}
    hwsqrt_result.QWordValue = r << 16;
    return hwsqrt_result;
};
hwFloat ufloat_Distance(hwFloat dx,hwFloat dy)
{
    hwFloat distance_result;
    QWord r;
    r = dx.QWordValue | dy.QWordValue;
    if(r < 0x10000)
    {
        distance_result.QWordValue = r;
        distance_result.isNegative = false;
    }
    else
    {
        distance_result = ufloat_hwSqrt(ufloat_hwFloat_hwFloat_op_add(ufloat_hwSqr(dx), ufloat_hwSqr(dy)));
    }
    return distance_result;
};
hwFloat ufloat_DistanceI(LongInt dx,LongInt dy)
{
    hwFloat distancei_result;
    distancei_result = ufloat_hwSqrt(ufloat_int2hwFloat(fpcrtl_sqr(dx) + fpcrtl_sqr(dy)));
    return distancei_result;
};
hwFloat ufloat_SignAs(hwFloat num,hwFloat signum)
{
    hwFloat signas_result;
    signas_result.QWordValue = num.QWordValue;
    signas_result.isNegative = signum.isNegative;
    return signas_result;
};
LongInt ufloat_hwSign(hwFloat r)
{
    LongInt hwsign_result;
    if(r.isNegative)
    {
        hwsign_result = -1;
    }
    else
    {
        hwsign_result = 1;
    }
    return hwsign_result;
};
LongInt ufloat_hwSignf(real r)
{
    LongInt hwsignf_result;
    if(r < 0)
    {
        hwsignf_result = -1;
    }
    else
    {
        hwsignf_result = 1;
    }
    return hwsignf_result;
};
hwFloat ufloat_AngleSin(LongWord Angle)
{
    hwFloat anglesin_result;
    anglesin_result.isNegative = false;
    if(Angle < 1024)
    {
        anglesin_result.QWordValue = SinTable[Angle];
    }
    else
    {
        anglesin_result.QWordValue = SinTable[2048 - Angle];
    }
    return anglesin_result;
};
hwFloat ufloat_AngleCos(LongWord Angle)
{
    hwFloat anglecos_result;
    anglecos_result.isNegative = Angle > 1024;
    if(Angle < 1024)
    {
        anglecos_result.QWordValue = SinTable[1024 - Angle];
    }
    else
    {
        anglecos_result.QWordValue = SinTable[Angle - 1024];
    }
    return anglecos_result;
};
LongInt ufloat_vector2Angle(hwFloat x,hwFloat y)
{
    LongInt vector2angle_result;
    hwFloat d;
    hwFloat nf;
    LongWord l;
    LongWord r;
    LongWord c;
    LongWord oc;
    QWord n;
    d = ufloat_hwFloat_hwFloat_op_div(_1, ufloat_Distance(x, y));
    nf = ufloat_hwFloat_hwFloat_op_mul(y, d);
    n = nf.QWordValue;
    l = 0;
    r = 1024;
    c = 0;
    do {
           oc = c;
           c = (l + r) >> 1;
           if(n >= SinTable[c])
           {
               l = c;
           }
           else
           {
               r = c;
           }
       } while(!(oc == c));
    if(x.isNegative)
    {
        c = 2048 - c;
    }
    if(y.isNegative)
    {
        c = -c;
    }
    vector2angle_result = c;
    return vector2angle_result;
};
