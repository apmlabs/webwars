#include "fpcrtl.h"

#include "uRandom.h"
typedef LongWord cirbuf_tt[(63 + 1)];
static cirbuf_tt cirbuf;
static Byte n;
void urandom_AddRandomness(LongWord r)
{
    n = (n + 1) & 0x3f;
    cirbuf[n] = cirbuf[n] ^ r;
};
LongWord urandom_GetNext()
{
    LongWord getnext_result;
    n = (n + 1) & 0x3f;
    cirbuf[n] = (cirbuf[(n + 40) & 0x3f] + cirbuf[(n + 9) & 0x3f]) & 0x7fffffff;
    getnext_result = cirbuf[n];
    return getnext_result;
};
void urandom_SetRandomSeed(string255 Seed,boolean dropAdditionalPart)
{
    LongWord i;
    LongWord t;
    LongWord l;
    n = 54;
    if(fpcrtl_Length(Seed) > 54)
    {
        Seed = fpcrtl_copy(Seed, 1, 54);
    }
    t = 0;
    l = fpcrtl_Length(Seed);
    while((t < l) && (!dropAdditionalPart || (Seed.s[t + 1] != 0x7c)))
    {
        cirbuf[t] = ((Byte)Seed.s[t + 1]);
        ++t;
    }
    {i = t;
     LongWord i__end__ = 54;
     if (i <= i__end__) do {
                               cirbuf[i] = 0xa98765 + 68;
                           } while(i++ != i__end__);}
    {i = 0;
     LongWord i__end__ = 2047;
     if (i <= i__end__) do {
                               urandom_GetNext();
                           } while(i++ != i__end__);}
};
hwFloat urandom_GetRandomf()
{
    hwFloat getrandomf_result;
    urandom_GetNext();
    getrandomf_result.isNegative = false;
    getrandomf_result.QWordValue = urandom_GetNext();
    return getrandomf_result;
};
LongWord urandom_GetRandom(LongWord m)
{
    LongWord getrandom_result;
    urandom_GetNext();
    getrandom_result = urandom_GetNext() % m;
    return getrandom_result;
};
hwFloat urandom_rndSign(hwFloat num)
{
    hwFloat rndsign_result;
    num.isNegative = fpcrtl_odd(urandom_GetNext());
    rndsign_result = num;
    return rndsign_result;
};
