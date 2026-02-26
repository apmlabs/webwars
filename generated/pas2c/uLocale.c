#include "fpcrtl.h"

#include "uLocale.h"
#include "SysUtils.h"
#include "uRandom.h"
#include "uUtils.h"
#include "uVariables.h"
#include "uDebug.h"
#include "uPhysFSLayer.h"
static const string255 __str6 = STRINIT("*missing translation*");
static const string255 __str5 = STRINIT("Too many event strings in ");
static const string255 __str4 = STRINIT("Load locale: \"=\" expected");
static const string255 __str3 = STRINIT("Load locale: \":\" expected");
static const string255 __str2 = STRINIT("Load locale: empty string");
static const string255 __str1 = STRINIT("");
static const string255 __str0 = STRINIT("Cannot load locale \"");
typedef astring trevt_tt[18][MAX_EVENT_STRINGS];
static trevt_tt trevt;
typedef Integer trevt_n_tt[18];
static trevt_n_tt trevt_n;
void ulocale_LoadLocale(string255 FileName)
{
    astring s;
    PFSFile f;
    LongInt a;
    LongInt b;
    LongInt c;
    typedef boolean first_tt[18];
    first_tt first;
    TEventId e;
    {e = 0;
     TEventId e__end__ = 17;
     if (e <= e__end__) do {
                               first[e] = true;
                           } while(e++ != e__end__);}
    f = uphysfslayer_pfsOpenRead(FileName);
    udebug_checkFails(f != NULL, _strappend(_strconcat(__str0, FileName), 0x22), false);
    s = fpcrtl_str2astr(__str1);
    if(f != NULL)
    {
        while(!uphysfslayer_pfsEOF(f))
        {
            uphysfslayer_pfsReadLnA(f, &(s));
            if(fpcrtl_LengthA(s) == 0)
            {
                continue;
            }
            if((s.s[1] < 0x30) || (s.s[1] > 0x39))
            {
                continue;
            }
            udebug_checkFails(fpcrtl_LengthA(s) > 6, __str2, true);
            fpcrtl_val(_chrconcat(s.s[1], s.s[2]), a);
            fpcrtl_val(_chrconcat(s.s[4], s.s[5]), b);
            udebug_checkFails(s.s[3] == 0x3a, __str3, true);
            udebug_checkFails(s.s[6] == 0x3d, __str4, true);
            if(!allOK)
            {
                return;
            }
            fpcrtl_Delete(s, 1, 6);
            switch(a)
            {case 0:if((b >= 0) && (b <= (61)))
                    {
                        trammo[((TAmmoStrId)b)] = s;
                    }
                    break;
             case 1:if((b >= 0) && (b <= (49)))
                    {
                        trmsg[((TMsgStrId)b)] = s;
                    }
                    break;
             case 2:if((b >= 0) && (b <= (17)))
                    {
                        udebug_checkFails(trevt_n[((TEventId)b)] < MAX_EVENT_STRINGS, _strconcat(_strappend(_strconcat(__str5, uutils_IntToStr(a)), 0x3a), uutils_IntToStr(b)), false);
                        if(first[((TEventId)b)])
                        {
                            trevt_n[((TEventId)b)] = 0;
                            first[((TEventId)b)] = false;
                        }
                        trevt[((TEventId)b)][trevt_n[((TEventId)b)]] = s;
                        ++trevt_n[((TEventId)b)];
                    }
                    break;
             case 3:if((b >= 0) && (b <= (61)))
                    {
                        trammoc[((TAmmoStrId)b)] = s;
                    }
                    break;
             case 4:if((b >= 0) && (b <= (61)))
                    {
                        trammod[((TAmmoStrId)b)] = s;
                    }
                    break;
             case 5:if((b >= 0) && (b <= (22)))
                    {
                        trgoal[((TGoalStrId)b)] = s;
                    }
                    break;
             case 6:if((b >= 0) && (b <= (31)))
                    {
                        trcmd[((TCmdHelpStrId)b)] = s;
                    }
                    break;
             default: break;}
        }
        uphysfslayer_pfsClose(f);
    }
};
astring ulocale_GetEventString(TEventId e)
{
    astring geteventstring_result;
    if(trevt_n[e] == 0)
    {
        geteventstring_result = fpcrtl_str2astr(__str6);
    }
    else
    {
        geteventstring_result = trevt[e][urandom_GetRandom(trevt_n[e])];
    }
    return geteventstring_result;
};
string255 ulocale_Format_11(string255 fmt,string255 arg1,string255 arg2,string255 arg3,string255 arg4,string255 arg5,string255 arg6,string255 arg7,string255 arg8,string255 arg9,Byte argCount)
{
    string255 format_result;
    LongInt i;
    LongInt p;
    string255 tempstr;
    string255 curArg;
    tempstr = fmt;
    {i = 0;
     LongInt i__end__ = argCount - 1;
     if (i <= i__end__) do {
                               switch(i)
                               {case 0:curArg = arg1;
                                       break;
                                case 1:curArg = arg2;
                                       break;
                                case 2:curArg = arg3;
                                       break;
                                case 3:curArg = arg4;
                                       break;
                                case 4:curArg = arg5;
                                       break;
                                case 5:curArg = arg6;
                                       break;
                                case 6:curArg = arg7;
                                       break;
                                case 7:curArg = arg8;
                                       break;
                                case 8:curArg = arg9;
                                       break;
                                default: break;}
                               uutils_ReplaceChars(&(curArg), 0x25, ((char)0x1b));
                               do {
                                      p = fpcrtl_pos(_strprepend(0x25, uutils_IntToStr(i + 1)), tempstr);
                                      if(p != 0)
                                      {
                                          fpcrtl_Delete(tempstr, p, 2);
                                          fpcrtl_Insert(curArg, tempstr, p);
                                      }
                                  } while(!(p == 0));
                           } while(i++ != i__end__);}
    uutils_ReplaceChars(&(tempstr), ((char)0x1b), 0x25);
    format_result = tempstr;
    return format_result;
};
astring ulocale_FormatA_11(astring fmt,astring arg1,astring arg2,astring arg3,astring arg4,astring arg5,astring arg6,astring arg7,astring arg8,astring arg9,Byte argCount)
{
    astring formata_result;
    LongInt i;
    LongInt p;
    astring tempstr;
    astring curArg;
    tempstr = fmt;
    {i = 0;
     LongInt i__end__ = argCount - 1;
     if (i <= i__end__) do {
                               switch(i)
                               {case 0:curArg = arg1;
                                       break;
                                case 1:curArg = arg2;
                                       break;
                                case 2:curArg = arg3;
                                       break;
                                case 3:curArg = arg4;
                                       break;
                                case 4:curArg = arg5;
                                       break;
                                case 5:curArg = arg6;
                                       break;
                                case 6:curArg = arg7;
                                       break;
                                case 7:curArg = arg8;
                                       break;
                                case 8:curArg = arg9;
                                       break;
                                default: break;}
                               uutils_ReplaceCharsA(&(curArg), 0x25, ((char)0x1b));
                               do {
                                      p = fpcrtl_pos(_strprepend(0x25, uutils_IntToStr(i + 1)), tempstr);
                                      if(p != 0)
                                      {
                                          fpcrtl_Delete(tempstr, p, 2);
                                          fpcrtl_Insert(curArg, tempstr, p);
                                      }
                                  } while(!(p == 0));
                           } while(i++ != i__end__);}
    uutils_ReplaceCharsA(&(tempstr), ((char)0x1b), 0x25);
    formata_result = tempstr;
    return formata_result;
};
string255 ulocale_Format_2(string255 fmt,string255 arg1)
{
    string255 format_result;
    format_result = ulocale_Format_11(fmt, arg1, __str1, __str1, __str1, __str1, __str1, __str1, __str1, __str1, 1);
    return format_result;
};
string255 ulocale_Format_3(string255 fmt,string255 arg1,string255 arg2)
{
    string255 format_result;
    format_result = ulocale_Format_11(fmt, arg1, arg2, __str1, __str1, __str1, __str1, __str1, __str1, __str1, 2);
    return format_result;
};
string255 ulocale_Format_4(string255 fmt,string255 arg1,string255 arg2,string255 arg3)
{
    string255 format_result;
    format_result = ulocale_Format_11(fmt, arg1, arg2, arg3, __str1, __str1, __str1, __str1, __str1, __str1, 3);
    return format_result;
};
string255 ulocale_Format_5(string255 fmt,string255 arg1,string255 arg2,string255 arg3,string255 arg4)
{
    string255 format_result;
    format_result = ulocale_Format_11(fmt, arg1, arg2, arg3, arg4, __str1, __str1, __str1, __str1, __str1, 4);
    return format_result;
};
string255 ulocale_Format_6(string255 fmt,string255 arg1,string255 arg2,string255 arg3,string255 arg4,string255 arg5)
{
    string255 format_result;
    format_result = ulocale_Format_11(fmt, arg1, arg2, arg3, arg4, arg5, __str1, __str1, __str1, __str1, 5);
    return format_result;
};
string255 ulocale_Format_7(string255 fmt,string255 arg1,string255 arg2,string255 arg3,string255 arg4,string255 arg5,string255 arg6)
{
    string255 format_result;
    format_result = ulocale_Format_11(fmt, arg1, arg2, arg3, arg4, arg5, arg6, __str1, __str1, __str1, 6);
    return format_result;
};
string255 ulocale_Format_8(string255 fmt,string255 arg1,string255 arg2,string255 arg3,string255 arg4,string255 arg5,string255 arg6,string255 arg7)
{
    string255 format_result;
    format_result = ulocale_Format_11(fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7, __str1, __str1, 7);
    return format_result;
};
string255 ulocale_Format_9(string255 fmt,string255 arg1,string255 arg2,string255 arg3,string255 arg4,string255 arg5,string255 arg6,string255 arg7,string255 arg8)
{
    string255 format_result;
    format_result = ulocale_Format_11(fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, __str1, 8);
    return format_result;
};
string255 ulocale_Format_10(string255 fmt,string255 arg1,string255 arg2,string255 arg3,string255 arg4,string255 arg5,string255 arg6,string255 arg7,string255 arg8,string255 arg9)
{
    string255 format_result;
    format_result = ulocale_Format_11(fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, 9);
    return format_result;
};
astring ulocale_FormatA_2(astring fmt,astring arg1)
{
    astring formata_result;
    formata_result = ulocale_FormatA_11(fmt, arg1, fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), 1);
    return formata_result;
};
astring ulocale_FormatA_3(astring fmt,astring arg1,astring arg2)
{
    astring formata_result;
    formata_result = ulocale_FormatA_11(fmt, arg1, arg2, fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), 2);
    return formata_result;
};
astring ulocale_FormatA_4(astring fmt,astring arg1,astring arg2,astring arg3)
{
    astring formata_result;
    formata_result = ulocale_FormatA_11(fmt, arg1, arg2, arg3, fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), 3);
    return formata_result;
};
astring ulocale_FormatA_5(astring fmt,astring arg1,astring arg2,astring arg3,astring arg4)
{
    astring formata_result;
    formata_result = ulocale_FormatA_11(fmt, arg1, arg2, arg3, arg4, fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), 4);
    return formata_result;
};
astring ulocale_FormatA_6(astring fmt,astring arg1,astring arg2,astring arg3,astring arg4,astring arg5)
{
    astring formata_result;
    formata_result = ulocale_FormatA_11(fmt, arg1, arg2, arg3, arg4, arg5, fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), 5);
    return formata_result;
};
astring ulocale_FormatA_7(astring fmt,astring arg1,astring arg2,astring arg3,astring arg4,astring arg5,astring arg6)
{
    astring formata_result;
    formata_result = ulocale_FormatA_11(fmt, arg1, arg2, arg3, arg4, arg5, arg6, fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), 6);
    return formata_result;
};
astring ulocale_FormatA_8(astring fmt,astring arg1,astring arg2,astring arg3,astring arg4,astring arg5,astring arg6,astring arg7)
{
    astring formata_result;
    formata_result = ulocale_FormatA_11(fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7, fpcrtl_str2astr(__str1), fpcrtl_str2astr(__str1), 7);
    return formata_result;
};
astring ulocale_FormatA_9(astring fmt,astring arg1,astring arg2,astring arg3,astring arg4,astring arg5,astring arg6,astring arg7,astring arg8)
{
    astring formata_result;
    formata_result = ulocale_FormatA_11(fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, fpcrtl_str2astr(__str1), 8);
    return formata_result;
};
astring ulocale_FormatA_10(astring fmt,astring arg1,astring arg2,astring arg3,astring arg4,astring arg5,astring arg6,astring arg7,astring arg8,astring arg9)
{
    astring formata_result;
    formata_result = ulocale_FormatA_11(fmt, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, 9);
    return formata_result;
};
void ulocale_LoadLocaleWrapper(PChar path,PChar userpath,PChar filename)
{
    PathPrefix = fpcrtl_str2astr(fpcrtl_StrPas(path));
    UserPathPrefix = fpcrtl_str2astr(fpcrtl_StrPas(userpath));
    allOK = true;
    uvariables_initModule();
    PathPrefix = _strappendA(PathPrefix, 0x0);
    UserPathPrefix = _strappendA(UserPathPrefix, 0x0);
    uphysfslayer_initModule(&(PathPrefix.s[1]), &(UserPathPrefix.s[1]));
    PathPrefix = fpcrtl_copyA(PathPrefix, 1, fpcrtl_LengthA(PathPrefix) - 1);
    UserPathPrefix = fpcrtl_copyA(UserPathPrefix, 1, fpcrtl_LengthA(UserPathPrefix) - 1);
    ulocale_LoadLocale(fpcrtl_StrPas(filename));
    uphysfslayer_freeModule();
    uvariables_freeModule();
};
