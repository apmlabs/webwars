#pragma once

#include "pas2c.h"

#include "uTypes.h"
#include "uFloat.h"
string255 uutils_Trim(string255 s);
LongInt uutils_CountChar(string255 s,char c);
void uutils_SplitBySpace(string255 (*a),string255 (*b));
void uutils_SplitByChar(string255 (*a),string255 (*b),char c);
void uutils_SplitByCharA(astring (*a),astring (*b),char c);
void uutils_EscapeCharA(astring (*a),char e);
void uutils_UnEscapeCharA(astring (*a),char e);
void uutils_ReplaceChars(string255 (*a),char c1,char c2);
void uutils_ReplaceCharsA(astring (*a),char c1,char c2);
string255 uutils_ExtractFileDir(string255 s);
string255 uutils_ExtractFileName(string255 s);
string255 __attribute__((overloadable)) uutils_EnumToStr_1(TGearType en);
string255 __attribute__((overloadable)) uutils_EnumToStr_1(TVisualGearType en);
string255 __attribute__((overloadable)) uutils_EnumToStr_1(TSound en);
string255 __attribute__((overloadable)) uutils_EnumToStr_1(TAmmoType en);
string255 __attribute__((overloadable)) uutils_EnumToStr_1(TStatInfoType en);
string255 __attribute__((overloadable)) uutils_EnumToStr_1(THogEffect en);
string255 __attribute__((overloadable)) uutils_EnumToStr_1(TCapGroup en);
string255 __attribute__((overloadable)) uutils_EnumToStr_1(TSprite en);
string255 __attribute__((overloadable)) uutils_EnumToStr_1(TMapGen en);
string255 __attribute__((overloadable)) uutils_EnumToStr_1(TWorldEdge en);
string255 __attribute__((overloadable)) uutils_EnumToStr_1(TMsgStrId en);
string255 __attribute__((overloadable)) uutils_EnumToStr_1(TGoalStrId en);
LongInt uutils_Min(LongInt a,LongInt b);
double uutils_MinD(double a,double b);
LongInt uutils_Max(LongInt a,LongInt b);
string255 uutils_IntToStr(LongInt n);
LongInt uutils_StrToInt(string255 s);
string255 uutils_FloatToStr(hwFloat n);
real uutils_DxDy2Angle(hwFloat _dY,hwFloat _dX);
LongInt uutils_DxDy2Angle32(hwFloat _dY,hwFloat _dX);
LongInt uutils_DxDy2AttackAngle(hwFloat _dY,hwFloat _dX);
LongInt uutils_DxDy2AttackAnglef(extended _dY,extended _dX);
void uutils_SetLittle(hwFloat (*r));
PChar uutils_Str2PChar(string255 s);
string255 uutils_DecodeBase64(string255 s);
boolean uutils_isPowerOf2(LongWord i);
LongWord uutils_toPowerOf2(LongWord i);
LongWord uutils_endian(LongWord independent);
THWFont uutils_CheckCJKFont(astring s,THWFont font);
void uutils_AddFileLog(string255 s);
void uutils_AddFileLogRaw(PChar s);
boolean uutils_CheckNoTeamOrHH();
LongInt uutils_GetLaunchX(TAmmoType at,LongInt dir,LongInt angle);
LongInt uutils_GetLaunchY(TAmmoType at,LongInt angle);
LongInt uutils_CalcWorldWrap(LongInt X,LongInt radius);
void uutils_updateVolumeDelta(boolean precise);
void uutils_updateCursorMovementDelta(boolean precise,LongInt dir,LongInt (*cursorVar));
string255 uutils_read1stLn(string255 filePath);
string255 uutils_readValueFromINI(string255 key,string255 filePath);
boolean uutils_isPhone();
string255 uutils_sanitizeForLog(string255 s);
string255 uutils_sanitizeCharForLog(char c);
void uutils_initModule(boolean isNotPreview);
void uutils_freeModule();

