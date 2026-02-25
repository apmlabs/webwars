#include "fpcrtl.h"

#include "adler32.h"
LongInt adler32_Adler32Update(LongInt adler,pointer Msg,LongInt Len)
{
    LongInt adler32update_result;
    enum{BASE = 65521};
    enum{NMAX = 3854};
    LongInt s1;
    LongInt s2;
    Integer i;
    Integer n;
    PByte m;
    m = ((PByte)Msg);
    s1 = ((LongWord)adler) & 0xffff;
    s2 = ((LongWord)adler) >> 16;
    while(Len > 0)
    {
        if(Len < NMAX)
        {
            n = Len;
        }
        else
        {
            n = NMAX;
        }
        {i = 1;
         Integer i__end__ = n;
         if (i <= i__end__) do {
                                   s1 += (*m);
                                   ++m;
                                   s2 += s1;
                               } while(i++ != i__end__);}
        s1 = s1 % BASE;
        s2 = s2 % BASE;
        Len -= n;
    }
    adler32update_result = (s2 << 16) | s1;
    return adler32update_result;
};
