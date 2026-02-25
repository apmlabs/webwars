#include "fpcrtl.h"

#include "uUtils.h"
#include "Math.h"
#include "uConsts.h"
#include "uVariables.h"
#include "uPhysFSLayer.h"
#include "uDebug.h"
static const string255 __str10 = STRINIT(" ticks. TurnTimeLeft = ");
static const string255 __str9 = STRINIT("halt at ");
static const string255 __str8 = STRINIT("[WARNING] Could not open log file for writing. Log will be written to stdout!");
static const string255 __str7 = STRINIT(".log");
static const string255 __str6 = STRINIT("/Logs/");
static const string255 __str5 = STRINIT("/Logs");
static const string255 __str4 = STRINIT("preview_pas2c");
static const string255 __str3 = STRINIT("game_pas2c");
static const string255 __str2 = STRINIT("rec");
static const string255 __str1 = STRINIT(": ");
static const string255 __str0 = STRINIT("");
static PFSFile logFile;
typedef char CharArray_tt[(255 + 1)];
static CharArray_tt CharArray;
string255 uutils_Trim(string255 s)
{
    string255 trim_result;
    Integer len;
    Integer left;
    Integer right;
    len = fpcrtl_Length(s);
    if(len == 0)
    {
        return s;
    }
    left = 1;
    while(left <= len)
    {
        if(s.s[left] > 0x20)
        {
            break;
        }
        ++left;
    }
    right = len;
    while(right >= 1)
    {
        if(s.s[right] > 0x20)
        {
            break;
        }
        --right;
    }
    if(left > right)
    {
        return __str0;
    }
    len = (right - left) + 1;
    trim_result = fpcrtl_copy(s, left, len);
    return trim_result;
};
Integer uutils_GetLastSlashPos(shortstring (*s))
{
    Integer getlastslashpos_result;
    Integer lslash;
    char c;
    lslash = fpcrtl_Length((*s));
    while(lslash >= 1)
    {
        c = (*s).s[lslash];
        if((c == 0x2f) || (c == 0x5c))
        {
            break;
        }
        --lslash;
    }
    getlastslashpos_result = lslash;
    return getlastslashpos_result;
};
string255 uutils_ExtractFileDir(string255 s)
{
    string255 extractfiledir_result;
    Byte lslash;
    if(fpcrtl_Length(s) == 0)
    {
        return s;
    }
    lslash = uutils_GetLastSlashPos(&(s));
    if(lslash <= 1)
    {
        return __str0;
    }
    s.s[0] = ((char)lslash - 1);
    extractfiledir_result = s;
    return extractfiledir_result;
};
string255 uutils_ExtractFileName(string255 s)
{
    string255 extractfilename_result;
    Byte lslash;
    Byte len;
    len = fpcrtl_Length(s);
    if(len == 0)
    {
        return s;
    }
    lslash = uutils_GetLastSlashPos(&(s));
    if(lslash < 1)
    {
        return s;
    }
    if(lslash == len)
    {
        return __str0;
    }
    len = len - lslash;
    extractfilename_result = fpcrtl_copy(s, lslash + 1, len);
    return extractfilename_result;
};
LongInt uutils_CountChar(string255 s,char c)
{
    LongInt countchar_result;
    LongInt i;
    LongInt res;
    res = 0;
    {i = 1;
     LongInt i__end__ = fpcrtl_Length(s);
     if (i <= i__end__) do {
                               if(s.s[i] == c)
                               {
                                   ++res;
                               }
                           } while(i++ != i__end__);}
    countchar_result = res;
    return countchar_result;
};
void uutils_SplitBySpace(string255 (*a),string255 (*b))
{
    uutils_SplitByChar(&((*a)), &((*b)), 0x20);
};
void uutils_SplitByChar(string255 (*a),string255 (*b),char c)
{
    LongInt i;
    i = fpcrtl_pos(c, (*a));
    if(i > 0)
    {
        (*b) = fpcrtl_copy((*a), i + 1, fpcrtl_Length((*a)) - i);
        (*a).s[0] = ((char)((int)(i) - 1));
        (*a).s[i] = 0;
    }
    else
    {
        (*b) = __str0;
    }
};
void uutils_SplitByCharA(astring (*a),astring (*b),char c)
{
    LongInt i;
    i = fpcrtl_pos(c, (*a));
    if(i > 0)
    {
        (*b) = fpcrtl_copyA((*a), i + 1, fpcrtl_LengthA((*a)) - i);
        fpcrtl_SetLengthA((*a), ((int)(i) - 1));
    }
    else
    {
        (*b) = fpcrtl_str2astr(__str0);
    }
};
void uutils_EscapeCharA(astring (*a),char e)
{
    LongInt i;
    do {
           i = fpcrtl_pos(e, (*a));
           if((i > 1) && ((*a).s[i - 1] == 0x5c))
           {
               (*a).s[i] = ((char)0x1b);
               fpcrtl_Delete((*a), i - 1, 1);
           }
           else
           {
               break;
           }
       } while(!(i <= 0));
};
void uutils_UnEscapeCharA(astring (*a),char e)
{
    LongInt i;
    do {
           i = fpcrtl_pos(((char)0x1b), (*a));
           if(i > 0)
           {
               (*a).s[i] = e;
           }
           else
           {
               break;
           }
       } while(!(i <= 0));
};
void uutils_ReplaceChars(string255 (*a),char c1,char c2)
{
    LongInt i;
    do {
           i = fpcrtl_pos(c1, (*a));
           if(i > 0)
           {
               (*a).s[i] = c2;
           }
       } while(!(i <= 0));
};
void uutils_ReplaceCharsA(astring (*a),char c1,char c2)
{
    LongInt i;
    do {
           i = fpcrtl_pos(c1, (*a));
           if(i > 0)
           {
               (*a).s[i] = c2;
           }
       } while(!(i <= 0));
};
string255 __attribute__((overloadable)) uutils_EnumToStr_1(TGearType en)
{
    string255 enumtostr_result;
    enumtostr_result = fpcrtl_GetEnumName(fpcrtl_TypeInfo(TGearType), (en));
    return enumtostr_result;
};
string255 __attribute__((overloadable)) uutils_EnumToStr_1(TVisualGearType en)
{
    string255 enumtostr_result;
    enumtostr_result = fpcrtl_GetEnumName(fpcrtl_TypeInfo(TVisualGearType), (en));
    return enumtostr_result;
};
string255 __attribute__((overloadable)) uutils_EnumToStr_1(TSound en)
{
    string255 enumtostr_result;
    enumtostr_result = fpcrtl_GetEnumName(fpcrtl_TypeInfo(TSound), (en));
    return enumtostr_result;
};
string255 __attribute__((overloadable)) uutils_EnumToStr_1(TAmmoType en)
{
    string255 enumtostr_result;
    enumtostr_result = fpcrtl_GetEnumName(fpcrtl_TypeInfo(TAmmoType), (en));
    return enumtostr_result;
};
string255 __attribute__((overloadable)) uutils_EnumToStr_1(TStatInfoType en)
{
    string255 enumtostr_result;
    enumtostr_result = fpcrtl_GetEnumName(fpcrtl_TypeInfo(TStatInfoType), (en));
    return enumtostr_result;
};
string255 __attribute__((overloadable)) uutils_EnumToStr_1(THogEffect en)
{
    string255 enumtostr_result;
    enumtostr_result = fpcrtl_GetEnumName(fpcrtl_TypeInfo(THogEffect), (en));
    return enumtostr_result;
};
string255 __attribute__((overloadable)) uutils_EnumToStr_1(TCapGroup en)
{
    string255 enumtostr_result;
    enumtostr_result = fpcrtl_GetEnumName(fpcrtl_TypeInfo(TCapGroup), (en));
    return enumtostr_result;
};
string255 __attribute__((overloadable)) uutils_EnumToStr_1(TSprite en)
{
    string255 enumtostr_result;
    enumtostr_result = fpcrtl_GetEnumName(fpcrtl_TypeInfo(TSprite), (en));
    return enumtostr_result;
};
string255 __attribute__((overloadable)) uutils_EnumToStr_1(TMapGen en)
{
    string255 enumtostr_result;
    enumtostr_result = fpcrtl_GetEnumName(fpcrtl_TypeInfo(TMapGen), (en));
    return enumtostr_result;
};
string255 __attribute__((overloadable)) uutils_EnumToStr_1(TWorldEdge en)
{
    string255 enumtostr_result;
    enumtostr_result = fpcrtl_GetEnumName(fpcrtl_TypeInfo(TWorldEdge), (en));
    return enumtostr_result;
};
string255 __attribute__((overloadable)) uutils_EnumToStr_1(TMsgStrId en)
{
    string255 enumtostr_result;
    enumtostr_result = fpcrtl_GetEnumName(fpcrtl_TypeInfo(TMsgStrId), (en));
    return enumtostr_result;
};
string255 __attribute__((overloadable)) uutils_EnumToStr_1(TGoalStrId en)
{
    string255 enumtostr_result;
    enumtostr_result = fpcrtl_GetEnumName(fpcrtl_TypeInfo(TGoalStrId), (en));
    return enumtostr_result;
};
LongInt uutils_Min(LongInt a,LongInt b)
{
    LongInt min_result;
    if(a < b)
    {
        min_result = a;
    }
    else
    {
        min_result = b;
    }
    return min_result;
};
double uutils_MinD(double a,double b)
{
    double mind_result;
    if(a < b)
    {
        mind_result = a;
    }
    else
    {
        mind_result = b;
    }
    return mind_result;
};
LongInt uutils_Max(LongInt a,LongInt b)
{
    LongInt max_result;
    if(a > b)
    {
        max_result = a;
    }
    else
    {
        max_result = b;
    }
    return max_result;
};
string255 uutils_IntToStr(LongInt n)
{
    string255 inttostr_result;
    fpcrtl_str(n, inttostr_result);
    return inttostr_result;
};
LongInt uutils_StrToInt(string255 s)
{
    LongInt strtoint_result;
    fpcrtl_val(s, strtoint_result);
    return strtoint_result;
};
string255 uutils_FloatToStr(hwFloat n)
{
    string255 floattostr_result;
    floattostr_result = _strconcat(_strappend(ufloat_cstr(n), 0x5f), uutils_IntToStr(fpcrtl_lo(n.QWordValue)));
    return floattostr_result;
};
real uutils_DxDy2Angle(hwFloat _dY,hwFloat _dX)
{
    real dxdy2angle_result;
    extended dY;
    extended dX;
    dY = ufloat_hwFloat2Float(_dY);
    dX = ufloat_hwFloat2Float(_dX);
    dxdy2angle_result = (fpcrtl_arctan2(dY, dX) * 180) /(float) pi;
    return dxdy2angle_result;
};
LongInt uutils_DxDy2Angle32(hwFloat _dY,hwFloat _dX)
{
    LongInt dxdy2angle32_result;
    extended _16divPI = (16 /(float) pi);
    extended dY;
    extended dX;
    dY = ufloat_hwFloat2Float(_dY);
    dX = ufloat_hwFloat2Float(_dX);
    dxdy2angle32_result = fpcrtl_trunc(fpcrtl_arctan2(dY, dX) * _16divPI) & 0x1f;
    return dxdy2angle32_result;
};
LongInt uutils_DxDy2AttackAngle(hwFloat _dY,hwFloat _dX)
{
    LongInt dxdy2attackangle_result;
    extended MaxAngleDivPI = (cMaxAngle /(float) pi);
    extended dY;
    extended dX;
    dY = ufloat_hwFloat2Float(_dY);
    dX = ufloat_hwFloat2Float(_dX);
    dxdy2attackangle_result = fpcrtl_trunc(fpcrtl_arctan2(dY, dX) * MaxAngleDivPI);
    return dxdy2attackangle_result;
};
LongInt uutils_DxDy2AttackAnglef(extended _dY,extended _dX)
{
    LongInt dxdy2attackanglef_result;
    dxdy2attackanglef_result = fpcrtl_trunc(fpcrtl_arctan2(_dY, _dX) * (cMaxAngle /(float) pi));
    return dxdy2attackanglef_result;
};
void uutils_SetLittle(hwFloat (*r))
{
    (*r) = ufloat_SignAs(cLittle, (*r));
};
boolean uutils_isPowerOf2(LongWord i)
{
    boolean ispowerof2_result;
    ispowerof2_result = (i & (i - 1)) == 0;
    return ispowerof2_result;
};
LongWord uutils_toPowerOf2(LongWord i)
{
    LongWord topowerof2_result;
    topowerof2_result = 1;
    while(topowerof2_result < i)
    {
        topowerof2_result = topowerof2_result << 1;
    }
    return topowerof2_result;
};
string255 uutils_DecodeBase64(string255 s)
{
    string255 decodebase64_result;
    static const string255 table = STRINIT("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
    LongInt i;
    LongInt t;
    LongInt c;
    c = 0;
    {i = 1;
     LongInt i__end__ = fpcrtl_Length(s);
     if (i <= i__end__) do {
                               t = fpcrtl_pos(s.s[i], table);
                               if(s.s[i] == 0x3d)
                               {
                                   ++c;
                               }
                               if(t > 0)
                               {
                                   s.s[i] = ((char)t - 1);
                               }
                               else
                               {
                                   s.s[i] = 0x0;
                               }
                           } while(i++ != i__end__);}
    i = 1;
    t = 1;
    while(i <= fpcrtl_Length(s))
    {
        decodebase64_result.s[t] = ((char)(((Byte)s.s[i]) << 2) | (((Byte)s.s[i + 1]) >> 4));
        decodebase64_result.s[t + 1] = ((char)(((Byte)s.s[i + 1]) << 4) | (((Byte)s.s[i + 2]) >> 2));
        decodebase64_result.s[t + 2] = ((char)(((Byte)s.s[i + 2]) << 6) | ((Byte)s.s[i + 3]));
        t += 3;
        i += 4;
    }
    if(c < 3)
    {
        t = t - c;
    }
    decodebase64_result.s[0] = ((char)t - 1);
    return decodebase64_result;
};
PChar uutils_Str2PChar(string255 s)
{
    PChar str2pchar_result;
    Integer i;
    {i = 1;
     Integer i__end__ = fpcrtl_Length(s);
     if (i <= i__end__) do {
                               CharArray[i - 1] = s.s[i];
                           } while(i++ != i__end__);}
    CharArray[fpcrtl_Length(s)] = 0x0;
    str2pchar_result = &(CharArray[0]);
    return str2pchar_result;
};
LongWord uutils_endian(LongWord independent)
{
    LongWord endian_result;
    endian_result = independent;
    return endian_result;
};
void uutils_AddFileLog(string255 s)
{
    if(logFile != NULL)
    {
        uphysfslayer_pfsWriteLn(logFile, _strconcat(_strconcat(uutils_IntToStr(GameTicks), __str1), s));
    }
    else
    {
        fpcrtl_writeLn(stdout, _strconcat(_strconcat(uutils_IntToStr(GameTicks), __str1), s));
    }
};
void uutils_AddFileLogRaw(PChar s)
{
    PChar msgLine;
    UNUSED (s);
};
THWFont uutils_CheckCJKFont(astring s,THWFont font)
{
    THWFont checkcjkfont_result;
    LongInt l;
    LongInt i;
    widechar u;
    typedef widechar tmpstr_tt[(256 + 1)];
    tmpstr_tt tmpstr;
    checkcjkfont_result = font;
    if((font >= CJKfnt16) || (fpcrtl_LengthA(s) == 0))
    {
        return checkcjkfont_result;
    }
    l = fpcrtl_UTF8ToUnicode(((PWideChar)&(tmpstr)), fpcrtl__pcharA(s), uutils_Min((256 + 1), fpcrtl_LengthA(s))) - 1;
    i = 0;
    while(i < l)
    {
        u = tmpstr[i];
        if((0x1100 <= u) && ((((((((((u <= 0x11ff) || ((0x2e80 <= u) && (u <= 0x2fdf))) || ((0x2ff0 <= u) && (u <= 0x31ff))) || ((0x31c0 <= u) && (u <= 0x31ef))) || ((0x3200 <= u) && (u <= 0x4dbf))) || ((0x4e00 <= u) && (u <= 0x9fff))) || ((0xac00 <= u) && (u <= 0xd7af))) || ((0xf900 <= u) && (u <= 0xfaff))) || ((0xfe30 <= u) && (u <= 0xfe4f))) || ((0xff00 <= u) && (u <= 0xffef))))
        {
            checkcjkfont_result = ((THWFont)(font) + (((7) + 1) / 2));
            return checkcjkfont_result;
        }
        ++i;
    }
    return checkcjkfont_result;
};
LongInt uutils_GetLaunchX(TAmmoType at,LongInt dir,LongInt angle)
{
    LongInt getlaunchx_result;
    UNUSED (at);
    UNUSED (dir);
    UNUSED (angle);
    getlaunchx_result = 0;
    return getlaunchx_result;
};
LongInt uutils_GetLaunchY(TAmmoType at,LongInt angle)
{
    LongInt getlaunchy_result;
    UNUSED (at);
    UNUSED (angle);
    getlaunchy_result = 0;
    return getlaunchy_result;
};
LongInt uutils_CalcWorldWrap(LongInt X,LongInt radius)
{
    LongInt calcworldwrap_result;
    if(WorldEdge == weWrap)
    {
        if(X < leftX)
        {
            X = X + (rightX - leftX);
        }
        else
        {
            if(X > rightX)
            {
                X = X - (rightX - leftX);
            }
        }
    }
    else
    {
        if(WorldEdge == weBounce)
        {
            if((X + radius) < leftX)
            {
                X = leftX + radius;
            }
            else
            {
                if((X - radius) > rightX)
                {
                    X = rightX - radius;
                }
            }
        }
    }
    calcworldwrap_result = X;
    return calcworldwrap_result;
};
boolean uutils_CheckNoTeamOrHH()
{
    boolean checknoteamorhh_result;
    checknoteamorhh_result = (CurrentTeam == NULL) || (CurrentHedgehog->Gear == NULL);
    return checknoteamorhh_result;
};
boolean uutils_isPhone()
{
    boolean isphone_result;
    isphone_result = false;
    return isphone_result;
};
string255 uutils_sanitizeForLog(string255 s)
{
    string255 sanitizeforlog_result;
    Byte i;
    string255 r;
    r.s[0] = s.s[0];
    {i = 1;
     Byte i__end__ = fpcrtl_Length(s);
     if (i <= i__end__) do {
                               if((s.s[i] < 0x20) || (s.s[i] > 0x7f))
                               {
                                   r.s[i] = 0x3f;
                               }
                               else
                               {
                                   r.s[i] = s.s[i];
                               }
                           } while(i++ != i__end__);}
    sanitizeforlog_result = r;
    return sanitizeforlog_result;
};
string255 uutils_sanitizeCharForLog(char c)
{
    string255 sanitizecharforlog_result;
    string255 r;
    if((c < 0x20) || (c > 0x7f))
    {
        r = _strprepend(0x23, uutils_IntToStr(((Byte)c)));
    }
    else
    {
        r.s[0] = 0x1;
        r.s[1] = c;
    }
    sanitizecharforlog_result = r;
    return sanitizecharforlog_result;
};
void uutils_updateVolumeDelta(boolean precise)
{
    if(cVolumeUpKey && !cVolumeDownKey)
    {
        if(precise)
        {
            cVolumeDelta = 1;
        }
        else
        {
            cVolumeDelta = 3;
        }
    }
    else
    {
        if(cVolumeDownKey && !cVolumeUpKey)
        {
            if(precise)
            {
                cVolumeDelta = -1;
            }
            else
            {
                cVolumeDelta = -3;
            }
        }
        else
        {
            cVolumeDelta = 0;
        }
    }
};
void uutils_updateCursorMovementDelta(boolean precise,LongInt dir,LongInt (*cursorVar))
{
    if(dir > 0)
    {
        if(precise)
        {
            (*cursorVar) = cameraKeyboardSpeedSlow;
        }
        else
        {
            (*cursorVar) = cameraKeyboardSpeed;
        }
    }
    else
    {
        if(dir < 0)
        {
            if(precise)
            {
                (*cursorVar) = -cameraKeyboardSpeedSlow;
            }
            else
            {
                (*cursorVar) = -cameraKeyboardSpeed;
            }
        }
        else
        {
            (*cursorVar) = 0;
        }
    }
};
string255 uutils_read1stLn(string255 filePath)
{
    string255 read1stln_result;
    PFSFile f;
    read1stln_result = __str0;
    if(uphysfslayer_pfsExists(filePath))
    {
        f = uphysfslayer_pfsOpenRead(filePath);
        if(!uphysfslayer_pfsEOF(f) && allOK)
        {
            uphysfslayer_pfsReadLn(f, &(read1stln_result));
        }
        uphysfslayer_pfsClose(f);
        f = NULL;
    }
    return read1stln_result;
};
string255 uutils_readValueFromINI(string255 key,string255 filePath)
{
    string255 readvaluefromini_result;
    PFSFile f;
    string255 s;
    LongInt i;
    s = __str0;
    readvaluefromini_result = __str0;
    if(uphysfslayer_pfsExists(filePath))
    {
        f = uphysfslayer_pfsOpenRead(filePath);
        while(!uphysfslayer_pfsEOF(f) && allOK)
        {
            uphysfslayer_pfsReadLn(f, &(s));
            if(fpcrtl_Length(s) == 0)
            {
                continue;
            }
            if(s.s[1] == 0x3b)
            {
                continue;
            }
            i = fpcrtl_pos(0x3d, s);
            if(_strcompare(uutils_Trim(fpcrtl_copy(s, 1, ((int)(i) - 1))), key))
            {
                fpcrtl_Delete(s, 1, i);
                readvaluefromini_result = s;
            }
        }
        uphysfslayer_pfsClose(f);
        f = NULL;
    }
    return readvaluefromini_result;
};
void uutils_initModule(boolean isNotPreview)
{
    string255 logfileBase;
    LongInt i;
    if(isNotPreview)
    {
        if(GameType == gmtRecord)
        {
            logfileBase = __str2;
        }
        else
        {
            logfileBase = __str3;
        }
    }
    else
    {
        logfileBase = __str4;
    }
    if(!uphysfslayer_pfsExists(__str5))
    {
        uphysfslayer_pfsMakeDir(__str5);
    }
    i = 0;
    while(i < 7)
    {
        logFile = uphysfslayer_pfsOpenWrite(_strconcat(_strconcat(_strconcat(__str6, logfileBase), uutils_IntToStr(i)), __str7));
        if(logFile != NULL)
        {
            break;
        }
        ++i;
    }
    if(logFile == NULL)
    {
        fpcrtl_writeLn(stdout, __str8);
    }
    mobileRecord.PerformRumble = NULL;
    mobileRecord.GameLoading = NULL;
    mobileRecord.GameLoaded = NULL;
    mobileRecord.SaveLoadingEnded = NULL;
};
void uutils_freeModule()
{
    if(logFile != NULL)
    {
        uphysfslayer_pfsWriteLn(logFile, _strconcat(_strconcat(_strconcat(__str9, uutils_IntToStr(GameTicks)), __str10), uutils_IntToStr(TurnTimeLeft)));
        uphysfslayer_pfsFlush(logFile);
        uphysfslayer_pfsClose(logFile);
    }
    else
    {
        fpcrtl_writeLn(stdout, _strconcat(_strconcat(_strconcat(__str9, uutils_IntToStr(GameTicks)), __str10), uutils_IntToStr(TurnTimeLeft)));
    }
};
