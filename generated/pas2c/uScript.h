#pragma once

#include "pas2c.h"

void uscript_ScriptPrintStack();
void uscript_ScriptClearStack();
boolean uscript_ScriptLoad(string255 name,boolean mustExist);
void uscript_ScriptOnPreviewInit();
void uscript_ScriptOnGameInit();
void uscript_ScriptOnScreenResize();
void uscript_ScriptSetInteger(string255 name,LongInt value);
void uscript_ScriptSetString(string255 name,string255 value);
void uscript_ScriptSetMapGlobals();
void uscript_ScriptCall_1(string255 fname);
LongInt uscript_ScriptCall_2(string255 fname,LongInt par1);
LongInt uscript_ScriptCall_3(string255 fname,LongInt par1,LongInt par2);
LongInt uscript_ScriptCall_4(string255 fname,LongInt par1,LongInt par2,LongInt par3);
LongInt uscript_ScriptCall_5(string255 fname,LongInt par1,LongInt par2,LongInt par3,LongInt par4);
boolean uscript_ScriptExists(string255 fname);
void uscript_LuaParseString(shortstring s);
void uscript_initModule();
void uscript_freeModule();

