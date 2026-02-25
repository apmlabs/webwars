#pragma once

#include "pas2c.h"

#include "SDLh.h"
#include "uTypes.h"
void uinputhandler_initModule();
void uinputhandler_freeModule();
LongInt uinputhandler_KeyNameToCode_1(string255 name);
LongInt uinputhandler_KeyNameToCode_2(string255 name,string255 Modifier);
LongInt uinputhandler_KeyBindToCode(string255 bind);
string255 uinputhandler_KeyBindToName(string255 bind);
void uinputhandler_MaskModifier(string255 Modifier,LongInt (*code));
void uinputhandler_ProcessMouseButton(TSDL_MouseButtonEvent event,boolean ButtonDown);
void uinputhandler_ProcessMouseMotion(LongInt xrel,LongInt yrel);
void uinputhandler_ProcessMouseWheel(LongInt y);
void uinputhandler_ProcessKey_1(TSDL_KeyboardEvent event);
void uinputhandler_ProcessKey_2(LongInt code,boolean KeyDown);
boolean uinputhandler_CheckDefaultSlotKeys();
void uinputhandler_ResetKbd();
void uinputhandler_ResetMouseWheel();
void uinputhandler_FreezeEnterKey();
void uinputhandler_InitKbdKeyTable();
void uinputhandler_SetBinds(TBinds (*binds));
void uinputhandler_SetDefaultBinds();
void uinputhandler_chDefaultBind(string255 (*id));
void uinputhandler_loadBinds(string255 cmd,string255 s);
void uinputhandler_addBind(TBinds (*binds),string255 (*id));
void uinputhandler_ControllerInit();
void uinputhandler_ControllerAxisEvent(Byte joy,Byte axis,Integer value);
void uinputhandler_ControllerHatEvent(Byte joy,Byte hat,Byte value);
void uinputhandler_ControllerButtonEvent(Byte joy,Byte button,boolean pressed);

