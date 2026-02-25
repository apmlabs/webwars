#pragma once

#include "pas2c.h"

#include "uTypes.h"
enum{MAX_EVENT_STRINGS = 255};
void ulocale_LoadLocale(string255 FileName);
astring ulocale_GetEventString(TEventId e);
string255 ulocale_Format_11(string255 fmt,string255 arg1,string255 arg2,string255 arg3,string255 arg4,string255 arg5,string255 arg6,string255 arg7,string255 arg8,string255 arg9,Byte argCount);
string255 ulocale_Format_10(string255 fmt,string255 arg1,string255 arg2,string255 arg3,string255 arg4,string255 arg5,string255 arg6,string255 arg7,string255 arg8,string255 arg9);
string255 ulocale_Format_9(string255 fmt,string255 arg1,string255 arg2,string255 arg3,string255 arg4,string255 arg5,string255 arg6,string255 arg7,string255 arg8);
string255 ulocale_Format_8(string255 fmt,string255 arg1,string255 arg2,string255 arg3,string255 arg4,string255 arg5,string255 arg6,string255 arg7);
string255 ulocale_Format_7(string255 fmt,string255 arg1,string255 arg2,string255 arg3,string255 arg4,string255 arg5,string255 arg6);
string255 ulocale_Format_6(string255 fmt,string255 arg1,string255 arg2,string255 arg3,string255 arg4,string255 arg5);
string255 ulocale_Format_5(string255 fmt,string255 arg1,string255 arg2,string255 arg3,string255 arg4);
string255 ulocale_Format_4(string255 fmt,string255 arg1,string255 arg2,string255 arg3);
string255 ulocale_Format_3(string255 fmt,string255 arg1,string255 arg2);
string255 ulocale_Format_2(string255 fmt,string255 arg1);
astring ulocale_FormatA_11(astring fmt,astring arg1,astring arg2,astring arg3,astring arg4,astring arg5,astring arg6,astring arg7,astring arg8,astring arg9,Byte argCount);
astring ulocale_FormatA_10(astring fmt,astring arg1,astring arg2,astring arg3,astring arg4,astring arg5,astring arg6,astring arg7,astring arg8,astring arg9);
astring ulocale_FormatA_9(astring fmt,astring arg1,astring arg2,astring arg3,astring arg4,astring arg5,astring arg6,astring arg7,astring arg8);
astring ulocale_FormatA_8(astring fmt,astring arg1,astring arg2,astring arg3,astring arg4,astring arg5,astring arg6,astring arg7);
astring ulocale_FormatA_7(astring fmt,astring arg1,astring arg2,astring arg3,astring arg4,astring arg5,astring arg6);
astring ulocale_FormatA_6(astring fmt,astring arg1,astring arg2,astring arg3,astring arg4,astring arg5);
astring ulocale_FormatA_5(astring fmt,astring arg1,astring arg2,astring arg3,astring arg4);
astring ulocale_FormatA_4(astring fmt,astring arg1,astring arg2,astring arg3);
astring ulocale_FormatA_3(astring fmt,astring arg1,astring arg2);
astring ulocale_FormatA_2(astring fmt,astring arg1);

