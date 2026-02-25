#include "fpcrtl.h"

#include "uInputHandler.h"
#include "uKeyNames.h"
#include "uConsole.h"
#include "uCommands.h"
#include "uVariables.h"
#include "uConsts.h"
#include "uUtils.h"
#include "uDebug.h"
#include "uPhysFSLayer.h"
#include "uCursor.h"
static const string255 __str118 = STRINIT("too many binds");
static const string255 __str117 = STRINIT("binds registry inconsistency");
static const string255 __str116 = STRINIT(" \"");
static const string255 __str115 = STRINIT("mod:");
static const string255 __str114 = STRINIT("[BINDS] file not found");
static const string255 __str113 = STRINIT("default");
static const string255 __str112 = STRINIT("[Binds]");
static const string255 __str111 = STRINIT("[BINDS] Loading binds from: ");
static const string255 __str110 = STRINIT("Not using any game controller");
static const string255 __str109 = STRINIT("* Number of buttons: ");
static const string255 __str108 = STRINIT("* Number of hats: ");
static const string255 __str107 = STRINIT("* Number of axes: ");
static const string255 __str106 = STRINIT("* Failed to open game controller no. ");
static const string255 __str105 = STRINIT("\":");
static const string255 __str104 = STRINIT(", name \"");
static const string255 __str103 = STRINIT("Game controller no. ");
static const string255 __str102 = STRINIT("Number of game controllers: ");
static const string255 __str101 = STRINIT("/settings.ini");
static const string255 __str100 = STRINIT("dbind");
static const string255 __str99 = STRINIT("left_shift");
static const string255 __str98 = STRINIT("+right");
static const string255 __str97 = STRINIT("right");
static const string255 __str96 = STRINIT("+left");
static const string255 __str95 = STRINIT("left");
static const string255 __str94 = STRINIT("+down");
static const string255 __str93 = STRINIT("down");
static const string255 __str92 = STRINIT("+up");
static const string255 __str91 = STRINIT("up");
static const string255 __str90 = STRINIT("+attack");
static const string255 __str89 = STRINIT("space");
static const string255 __str88 = STRINIT("ljump");
static const string255 __str87 = STRINIT("return");
static const string255 __str86 = STRINIT("tab");
static const string255 __str85 = STRINIT("hjump");
static const string255 __str84 = STRINIT("backspace");
static const string255 __str83 = STRINIT("/put");
static const string255 __str82 = STRINIT("timer_u");
static const string255 __str81 = STRINIT("n");
static const string255 __str80 = STRINIT("timer ");
static const string255 __str79 = STRINIT("slot ");
static const string255 __str78 = STRINIT("fullscr");
static const string255 __str77 = STRINIT("f12");
static const string255 __str76 = STRINIT("zoomout");
static const string255 __str75 = STRINIT("wheeldown");
static const string255 __str74 = STRINIT("zoomin");
static const string255 __str73 = STRINIT("wheelup");
static const string255 __str72 = STRINIT("zoomreset");
static const string255 __str71 = STRINIT("confirm");
static const string255 __str70 = STRINIT("y");
static const string255 __str69 = STRINIT("chat team");
static const string255 __str68 = STRINIT("u");
static const string255 __str67 = STRINIT("chat");
static const string255 __str66 = STRINIT("t");
static const string255 __str65 = STRINIT("+speedup");
static const string255 __str64 = STRINIT("f");
static const string255 __str63 = STRINIT("pause");
static const string255 __str62 = STRINIT("p");
static const string255 __str61 = STRINIT("findhh");
static const string255 __str60 = STRINIT("h");
static const string255 __str59 = STRINIT("record");
static const string255 __str58 = STRINIT("r");
static const string255 __str57 = STRINIT("capture");
static const string255 __str56 = STRINIT("c");
static const string255 __str55 = STRINIT("mute");
static const string255 __str54 = STRINIT("8");
static const string255 __str53 = STRINIT("+voldown");
static const string255 __str52 = STRINIT("9");
static const string255 __str51 = STRINIT("+volup");
static const string255 __str50 = STRINIT("0");
static const string255 __str49 = STRINIT("keypad_2");
static const string255 __str48 = STRINIT("keypad_4");
static const string255 __str47 = STRINIT("keypad_6");
static const string255 __str46 = STRINIT("keypad_8");
static const string255 __str45 = STRINIT("gearinfo");
static const string255 __str44 = STRINIT("o");
static const string255 __str43 = STRINIT("+mission");
static const string255 __str42 = STRINIT("m");
static const string255 __str41 = STRINIT("rottags");
static const string255 __str40 = STRINIT("home");
static const string255 __str39 = STRINIT("rotmask");
static const string255 __str38 = STRINIT("delete");
static const string255 __str37 = STRINIT("history");
static const string255 __str36 = STRINIT("`");
static const string255 __str35 = STRINIT("quit");
static const string255 __str34 = STRINIT("escape");
static const string255 __str33 = STRINIT("unknown key");
static const string255 __str32 = STRINIT("Too many key bindings");
static const string255 __str31 = STRINIT("mousex2");
static const string255 __str30 = STRINIT("mousex1");
static const string255 __str29 = STRINIT("mouser");
static const string255 __str28 = STRINIT("mousem");
static const string255 __str27 = STRINIT("mousel");
static const string255 __str26 = STRINIT("gencmd R");
static const string255 __str25 = STRINIT("+precise");
static const string255 __str24 = STRINIT("switch");
static const string255 __str23 = STRINIT("ammomenu");
static const string255 __str22 = STRINIT("put");
static const string255 __str21 = STRINIT("+cur_r");
static const string255 __str20 = STRINIT("+cur_l");
static const string255 __str19 = STRINIT("+cur_d");
static const string255 __str18 = STRINIT("+cur_u");
static const string255 __str17 = STRINIT("forcequit");
static const string255 __str16 = STRINIT("halt");
static const string255 __str15 = STRINIT("right_ctrl");
static const string255 __str14 = STRINIT("left_ctrl");
static const string255 __str13 = STRINIT("rmeta");
static const string255 __str12 = STRINIT("rctrl");
static const string255 __str11 = STRINIT("lmeta");
static const string255 __str10 = STRINIT("lctrl");
static const string255 __str9 = STRINIT("ralt");
static const string255 __str8 = STRINIT("lalt");
static const string255 __str7 = STRINIT("rshift");
static const string255 __str6 = STRINIT("lshift");
static const string255 __str5 = STRINIT("): Hedgewars does not have internal key name for given bind!");
static const string255 __str4 = STRINIT("Error: KeyBindToName(");
static const string255 __str3 = STRINIT("Esc");
static const string255 __str2 = STRINIT("Escape");
static const string255 __str1 = STRINIT("Inconsistency in key binding registry");
static const string255 __str0 = STRINIT("");
enum{LSHIFT = 0x0200};
enum{RSHIFT = 0x0400};
enum{LALT = 0x0800};
enum{RALT = 0x1000};
enum{LCTRL = 0x2000};
enum{RCTRL = 0x4000};
typedef boolean tkbd_tt[(cKbdMaxIndex + 1)];
static tkbd_tt tkbd;
static TKeyNames KeyNames;
static TBinds CurrentBinds;
static Integer ControllerNumControllers;
static Integer ControllerEnabled;
typedef Integer ControllerNumAxes_tt[(5 + 1)];
static ControllerNumAxes_tt ControllerNumAxes;
typedef Integer ControllerNumHats_tt[(5 + 1)];
static ControllerNumHats_tt ControllerNumHats;
typedef Integer ControllerNumButtons_tt[(5 + 1)];
static ControllerNumButtons_tt ControllerNumButtons;
LongInt uinputhandler_KeyNameToCode_1(string255 name)
{
    LongInt keynametocode_result;
    keynametocode_result = uinputhandler_KeyNameToCode_2(name, __str0);
    return keynametocode_result;
};
LongInt uinputhandler_KeyNameToCode_2(string255 name,string255 Modifier)
{
    LongInt keynametocode_result;
    LongInt code;
    name = fpcrtl_LowerCase(name);
    code = 0;
    while((code <= cKeyMaxIndex) && (_strncompare(KeyNames[code], name)))
    {
        ++code;
    }
    uinputhandler_MaskModifier(Modifier, &(code));
    keynametocode_result = code;
    return keynametocode_result;
};
LongInt uinputhandler_KeyBindToCode(string255 bind)
{
    LongInt keybindtocode_result;
    LongInt code;
    LongInt index;
    index = 0;
    while((index <= 255) && (_strncompare(CurrentBinds.binds[index], bind)))
    {
        ++index;
    }
    if(index > 255)
    {
        keybindtocode_result = -1;
    }
    else
    {
        code = 0;
        while((code <= cKbdMaxIndex) && (CurrentBinds.indices[code] != index))
        {
            ++code;
        }
        udebug_checkFails(code <= cKbdMaxIndex, __str1, true);
        keybindtocode_result = code;
    }
    return keybindtocode_result;
};
string255 uinputhandler_KeyBindToName(string255 bind)
{
    string255 keybindtoname_result;
    LongInt code;
    string255 name;
    code = uinputhandler_KeyBindToCode(bind);
    if(code == -1)
    {
        keybindtoname_result = fpcrtl_astr2str(trmsg[sidUnknownKey]);
    }
    else
    {
        name = fpcrtl_pchar2str(SDL_GetKeyName(SDL_GetKeyFromScancode(code)));
        if(_strcompare(name, __str2))
        {
            keybindtoname_result = __str3;
        }
        else
        {
            if(fpcrtl_Length(name) != 0)
            {
                keybindtoname_result = name;
            }
            else
            {
                if(_strncompare(KeyNames[code], __str0))
                {
                    keybindtoname_result = KeyNames[code];
                }
                else
                {
                    uconsole_WriteLnToConsole(_strconcat(_strconcat(__str4, bind), __str5));
                    keybindtoname_result = fpcrtl_astr2str(trmsg[sidUnknownKey]);
                }
            }
        }
    }
    return keybindtoname_result;
};
void uinputhandler_MaskModifier(string255 Modifier,LongInt (*code))
{
    string255 mod_ = STRINIT("");
    LongInt ModifierCount;
    LongInt i;
    if(_strcompare(Modifier, __str0))
    {
        return;
    }
    ModifierCount = 0;
    {i = 1;
     LongInt i__end__ = fpcrtl_Length(Modifier);
     if (i <= i__end__) do {
                               if(Modifier.s[i] == 0x3a)
                               {
                                   ++ModifierCount;
                               }
                           } while(i++ != i__end__);}
    uutils_SplitByChar(&(Modifier), &(mod_), 0x3a);
    Modifier = mod_;
    {i = 0;
     LongInt i__end__ = ModifierCount;
     if (i <= i__end__) do {
                               mod_ = __str0;
                               uutils_SplitByChar(&(Modifier), &(mod_), 0x3a);
                               if(_strcompare(Modifier, __str6))
                               {
                                   (*code) = (*code) | LSHIFT;
                               }
                               if(_strcompare(Modifier, __str7))
                               {
                                   (*code) = (*code) | RSHIFT;
                               }
                               if(_strcompare(Modifier, __str8))
                               {
                                   (*code) = (*code) | LALT;
                               }
                               if(_strcompare(Modifier, __str9))
                               {
                                   (*code) = (*code) | RALT;
                               }
                               if((_strcompare(Modifier, __str10)) || (_strcompare(mod_, __str11)))
                               {
                                   (*code) = (*code) | LCTRL;
                               }
                               if((_strcompare(Modifier, __str12)) || (_strcompare(mod_, __str13)))
                               {
                                   (*code) = (*code) | RCTRL;
                               }
                               Modifier = mod_;
                           } while(i++ != i__end__);}
};
void uinputhandler_ProcessKey_2(LongInt code,boolean KeyDown)
{
    boolean Trusted;
    string255 curBind;
    string255 s;
    boolean readyAborter;
    if(!(tkbd[code] ^ KeyDown))
    {
        return;
    }
    tkbd[code] = KeyDown;
    Trusted = ((CurrentTeam != NULL) && !CurrentTeam->ExtDriven) && (CurrentHedgehog->BotLevel == 0);
    if(KeyDown && (code == SDLK_q))
    {
        if(tkbd[uinputhandler_KeyNameToCode_1(__str14)] || tkbd[uinputhandler_KeyNameToCode_1(__str15)])
        {
            ucommands_ParseCommand_2(__str16, true);
        }
    }
    if(KeyDown && (code == SDLK_w))
    {
        if(tkbd[uinputhandler_KeyNameToCode_1(__str14)] || tkbd[uinputhandler_KeyNameToCode_1(__str15)])
        {
            if(((CurrentBinds.indices[uinputhandler_KeyNameToCode_1(__str14)] == 0) || (CurrentBinds.indices[uinputhandler_KeyNameToCode_1(__str15)] == 0)) && (CurrentBinds.indices[SDLK_w] == 0))
            {
                ucommands_ParseCommand_2(__str17, true);
            }
        }
    }
    if(CurrentBinds.indices[code] > 0)
    {
        curBind = CurrentBinds.binds[CurrentBinds.indices[code]];
        readyAborter = (((_strncompare(curBind, __str18)) && (_strncompare(curBind, __str19))) && (_strncompare(curBind, __str20))) && (_strncompare(curBind, __str21));
        if(((((code < (cKeyMaxIndex - 2)) && KeyDown) && !((((((_strcompare(curBind, __str22)) || (_strcompare(curBind, __str23))) || (_strcompare(curBind, __str18))) || (_strcompare(curBind, __str19))) || (_strcompare(curBind, __str20))) || (_strcompare(curBind, __str21)))) && (CurrentTeam != NULL)) && !CurrentTeam->ExtDriven)
        {
            bShowAmmoMenu = false;
        }
        if(KeyDown)
        {
            Trusted = Trusted && !isPaused;
            if(_strcompare(curBind, __str24))
            {
                LocalMessage = LocalMessage | gmSwitch;
            }
            else
            {
                if(_strcompare(curBind, __str25))
                {
                    LocalMessage = LocalMessage | gmPrecise;
                    uutils_updateVolumeDelta(true);
                    uutils_updateCursorMovementDelta(true, CursorMovementX, &(CursorMovementX));
                    uutils_updateCursorMovementDelta(true, CursorMovementY, &(CursorMovementY));
                }
            }
            ucommands_ParseCommand_2(curBind, Trusted);
            if(((readyAborter && (CurrentTeam != NULL)) && !CurrentTeam->ExtDriven) && (ReadyTimeLeft > 1))
            {
                ucommands_ParseCommand_2(__str26, true);
            }
        }
        else
        {
            if(curBind.s[1] == 0x2b)
            {
                if(_strcompare(curBind, __str25))
                {
                    LocalMessage = LocalMessage & ~gmPrecise;
                    uutils_updateVolumeDelta(false);
                    uutils_updateCursorMovementDelta(false, CursorMovementX, &(CursorMovementX));
                    uutils_updateCursorMovementDelta(false, CursorMovementY, &(CursorMovementY));
                }
                s = curBind;
                s.s[1] = 0x2d;
                ucommands_ParseCommand_2(s, Trusted);
                if(((readyAborter && (CurrentTeam != NULL)) && !CurrentTeam->ExtDriven) && (ReadyTimeLeft > 1))
                {
                    ucommands_ParseCommand_2(__str26, true);
                }
            }
            else
            {
                if(_strcompare(curBind, __str24))
                {
                    LocalMessage = LocalMessage & ~gmSwitch;
                }
            }
        }
    }
};
void uinputhandler_ProcessKey_1(TSDL_KeyboardEvent event)
{
    LongInt code;
    code = ((LongInt)event.keysym.scancode);
    uinputhandler_ProcessKey_2(code, event.type_ == SDL_KEYDOWN);
};
void uinputhandler_ProcessMouseButton(TSDL_MouseButtonEvent event,boolean ButtonDown)
{
    switch(event.button)
    {case SDL_BUTTON_LEFT:uinputhandler_ProcessKey_2(uinputhandler_KeyNameToCode_1(__str27), ButtonDown);
                          break;
     case SDL_BUTTON_MIDDLE:uinputhandler_ProcessKey_2(uinputhandler_KeyNameToCode_1(__str28), ButtonDown);
                            break;
     case SDL_BUTTON_RIGHT:uinputhandler_ProcessKey_2(uinputhandler_KeyNameToCode_1(__str29), ButtonDown);
                           break;
     case SDL_BUTTON_X1:uinputhandler_ProcessKey_2(uinputhandler_KeyNameToCode_1(__str30), ButtonDown);
                        break;
     case SDL_BUTTON_X2:uinputhandler_ProcessKey_2(uinputhandler_KeyNameToCode_1(__str31), ButtonDown);
                        break;
     default: break;}
};
void uinputhandler_ProcessMouseMotion(LongInt xrel,LongInt yrel)
{
    ucursor_updatePositionDelta(xrel, yrel);
};
static Integer mwheelupCode;
static Integer mwheeldownCode;
void uinputhandler_ProcessMouseWheel(LongInt y)
{
    if(y > 0)
    {
        if(tkbd[mwheeldownCode])
        {
            uinputhandler_ProcessKey_2(mwheeldownCode, false);
        }
        if(!tkbd[mwheelupCode])
        {
            uinputhandler_ProcessKey_2(mwheelupCode, true);
        }
    }
    else
    {
        if(y < 0)
        {
            if(tkbd[mwheelupCode])
            {
                uinputhandler_ProcessKey_2(mwheelupCode, false);
            }
            if(!tkbd[mwheeldownCode])
            {
                uinputhandler_ProcessKey_2(mwheeldownCode, true);
            }
        }
    }
};
void uinputhandler_ResetMouseWheel()
{
    if(tkbd[mwheelupCode])
    {
        uinputhandler_ProcessKey_2(mwheelupCode, false);
    }
    if(tkbd[mwheeldownCode])
    {
        uinputhandler_ProcessKey_2(mwheeldownCode, false);
    }
};
void uinputhandler_ResetKbd()
{
    LongInt t;
    {t = 0;
     LongInt t__end__ = cKbdMaxIndex;
     if (t <= t__end__) do {
                               if(tkbd[t])
                               {
                                   uinputhandler_ProcessKey_2(t, false);
                               }
                           } while(t++ != t__end__);}
};
void uinputhandler_RegisterBind(TBinds (*binds),string255 key,string255 value)
{
    LongInt code;
    udebug_checkFails((*binds).lastIndex < 255, __str32, true);
    code = uinputhandler_KeyNameToCode_1(key);
    udebug_checkFails(code >= 0, __str33, true);
    if((*binds).indices[code] > 0)
    {
        (*binds).binds[(*binds).indices[code]] = value;
    }
    else
    {
        ++(*binds).lastIndex;
        (*binds).indices[code] = (*binds).lastIndex;
        (*binds).binds[(*binds).indices[code]] = value;
    }
};
void uinputhandler_InitDefaultBinds()
{
    LongWord i;
    uinputhandler_RegisterBind(&(DefaultBinds), __str34, __str35);
    uinputhandler_RegisterBind(&(DefaultBinds), __str36, __str37);
    uinputhandler_RegisterBind(&(DefaultBinds), __str38, __str39);
    uinputhandler_RegisterBind(&(DefaultBinds), __str40, __str41);
    uinputhandler_RegisterBind(&(DefaultBinds), __str42, __str43);
    uinputhandler_RegisterBind(&(DefaultBinds), __str44, __str45);
    uinputhandler_RegisterBind(&(DefaultBinds), __str46, __str18);
    uinputhandler_RegisterBind(&(DefaultBinds), __str47, __str21);
    uinputhandler_RegisterBind(&(DefaultBinds), __str48, __str20);
    uinputhandler_RegisterBind(&(DefaultBinds), __str49, __str19);
    uinputhandler_RegisterBind(&(DefaultBinds), __str50, __str51);
    uinputhandler_RegisterBind(&(DefaultBinds), __str52, __str53);
    uinputhandler_RegisterBind(&(DefaultBinds), __str54, __str55);
    uinputhandler_RegisterBind(&(DefaultBinds), __str56, __str57);
    uinputhandler_RegisterBind(&(DefaultBinds), __str58, __str59);
    uinputhandler_RegisterBind(&(DefaultBinds), __str60, __str61);
    uinputhandler_RegisterBind(&(DefaultBinds), __str62, __str63);
    uinputhandler_RegisterBind(&(DefaultBinds), __str64, __str65);
    uinputhandler_RegisterBind(&(DefaultBinds), __str66, __str67);
    uinputhandler_RegisterBind(&(DefaultBinds), __str68, __str69);
    uinputhandler_RegisterBind(&(DefaultBinds), __str70, __str71);
    uinputhandler_RegisterBind(&(DefaultBinds), __str28, __str72);
    uinputhandler_RegisterBind(&(DefaultBinds), __str73, __str74);
    uinputhandler_RegisterBind(&(DefaultBinds), __str75, __str76);
    uinputhandler_RegisterBind(&(DefaultBinds), __str77, __str78);
    {i = 1;
     LongWord i__end__ = 10;
     if (i <= i__end__) do {
                               uinputhandler_RegisterBind(&(DefaultBinds), _strprepend(0x66, uutils_IntToStr(i)), _strappend(__str79, ((char)48 + i)));
                           } while(i++ != i__end__);}
    {i = 1;
     LongWord i__end__ = 5;
     if (i <= i__end__) do {
                               uinputhandler_RegisterBind(&(DefaultBinds), uutils_IntToStr(i), _strconcat(__str80, uutils_IntToStr(i)));
                           } while(i++ != i__end__);}
    uinputhandler_RegisterBind(&(DefaultBinds), __str81, __str82);
    uinputhandler_RegisterBind(&(DefaultBinds), __str27, __str83);
    uinputhandler_RegisterBind(&(DefaultBinds), __str29, __str23);
    uinputhandler_RegisterBind(&(DefaultBinds), __str84, __str85);
    uinputhandler_RegisterBind(&(DefaultBinds), __str86, __str24);
    uinputhandler_RegisterBind(&(DefaultBinds), __str87, __str88);
    uinputhandler_RegisterBind(&(DefaultBinds), __str89, __str90);
    uinputhandler_RegisterBind(&(DefaultBinds), __str91, __str92);
    uinputhandler_RegisterBind(&(DefaultBinds), __str93, __str94);
    uinputhandler_RegisterBind(&(DefaultBinds), __str95, __str96);
    uinputhandler_RegisterBind(&(DefaultBinds), __str97, __str98);
    uinputhandler_RegisterBind(&(DefaultBinds), __str99, __str25);
    uinputhandler_loadBinds(__str100, _strconcat(cPathz[ptConfig], __str101));
};
void uinputhandler_InitKbdKeyTable()
{
    LongInt i;
    LongInt j;
    LongInt k;
    KeyNames[cKeyMaxIndex] = __str27;
    KeyNames[cKeyMaxIndex - 1] = __str28;
    KeyNames[cKeyMaxIndex - 2] = __str29;
    KeyNames[cKeyMaxIndex - 3] = __str30;
    KeyNames[cKeyMaxIndex - 4] = __str31;
    mwheelupCode = cKeyMaxIndex - 5;
    KeyNames[mwheelupCode] = __str73;
    mwheeldownCode = cKeyMaxIndex - 6;
    KeyNames[mwheeldownCode] = __str75;
    ukeynames_populateKeyNames(&(KeyNames));
    SDL_GetKeyboardState(&(k));
    {j = 0;
     LongInt j__end__ = ((int)(ControllerNumControllers) - 1);
     if (j <= j__end__) do {
                               {i = 0;
                                LongInt i__end__ = ((int)(ControllerNumAxes[j]) - 1);
                                if (i <= i__end__) do {
                                                          KeyNames[k + 0] = _strappend(_strconcat(_strappend(_strprepend(0x6a, uutils_IntToStr(j)), 0x61), uutils_IntToStr(i)), 0x75);
                                                          KeyNames[k + 1] = _strappend(_strconcat(_strappend(_strprepend(0x6a, uutils_IntToStr(j)), 0x61), uutils_IntToStr(i)), 0x64);
                                                          k += 2;
                                                      } while(i++ != i__end__);}
                               {i = 0;
                                LongInt i__end__ = ((int)(ControllerNumHats[j]) - 1);
                                if (i <= i__end__) do {
                                                          KeyNames[k + 0] = _strappend(_strconcat(_strappend(_strprepend(0x6a, uutils_IntToStr(j)), 0x68), uutils_IntToStr(i)), 0x75);
                                                          KeyNames[k + 1] = _strappend(_strconcat(_strappend(_strprepend(0x6a, uutils_IntToStr(j)), 0x68), uutils_IntToStr(i)), 0x72);
                                                          KeyNames[k + 2] = _strappend(_strconcat(_strappend(_strprepend(0x6a, uutils_IntToStr(j)), 0x68), uutils_IntToStr(i)), 0x64);
                                                          KeyNames[k + 3] = _strappend(_strconcat(_strappend(_strprepend(0x6a, uutils_IntToStr(j)), 0x68), uutils_IntToStr(i)), 0x6c);
                                                          k += 4;
                                                      } while(i++ != i__end__);}
                               {i = 0;
                                LongInt i__end__ = ((int)(ControllerNumButtons[j]) - 1);
                                if (i <= i__end__) do {
                                                          KeyNames[k] = _strconcat(_strappend(_strprepend(0x6a, uutils_IntToStr(j)), 0x62), uutils_IntToStr(i));
                                                          k += 1;
                                                      } while(i++ != i__end__);}
                           } while(j++ != j__end__);}
    uinputhandler_InitDefaultBinds();
};
boolean uinputhandler_CheckDefaultSlotKeys()
{
    boolean checkdefaultslotkeys_result;
    LongInt i;
    LongInt code;
    {i = 1;
     LongInt i__end__ = cMaxSlotIndex;
     if (i <= i__end__) do {
                               code = uinputhandler_KeyNameToCode_1(_strprepend(0x66, uutils_IntToStr(i)));
                               if(_strncompare(CurrentBinds.binds[CurrentBinds.indices[code]], _strappend(__str79, ((char)i + 48))))
                               {
                                   checkdefaultslotkeys_result = false;
                                   return checkdefaultslotkeys_result;
                               }
                           } while(i++ != i__end__);}
    checkdefaultslotkeys_result = true;
    return checkdefaultslotkeys_result;
};
void uinputhandler_SetBinds(TBinds (*binds))
{
    LongInt t;
    {t = 0;
     LongInt t__end__ = cKbdMaxIndex;
     if (t <= t__end__) do {
                               if((_strncompare(CurrentBinds.binds[CurrentBinds.indices[t]], (*binds).binds[(*binds).indices[t]])) && tkbd[t])
                               {
                                   uinputhandler_ProcessKey_2(t, false);
                               }
                           } while(t++ != t__end__);}
    CurrentBinds = (*binds);
};
void uinputhandler_SetDefaultBinds()
{
    CurrentBinds = DefaultBinds;
};
void uinputhandler_FreezeEnterKey()
{
    tkbd[3] = true;
    tkbd[13] = true;
    tkbd[27] = true;
    tkbd[271] = true;
};
typedef PSDL_Joystick Controller_tt[(5 + 1)];
static Controller_tt Controller;
void uinputhandler_ControllerInit()
{
    Integer j;
    ControllerEnabled = 0;
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    ControllerNumControllers = SDL_NumJoysticks();
    if(ControllerNumControllers > 6)
    {
        ControllerNumControllers = 6;
    }
    uconsole_WriteLnToConsole(_strconcat(__str102, uutils_IntToStr(ControllerNumControllers)));
    if(ControllerNumControllers > 0)
    {
        {j = 0;
         Integer j__end__ = ((int)(ControllerNumControllers) - 1);
         if (j <= j__end__) do {
                                   uconsole_WriteLnToConsole(_strconcat(_strconcat(_strconcat(_strconcat(__str103, uutils_IntToStr(j)), __str104), fpcrtl_pchar2str(SDL_JoystickNameForIndex(j))), __str105));
                                   Controller[j] = SDL_JoystickOpen(j);
                                   if(Controller[j] == NULL)
                                   {
                                       uconsole_WriteLnToConsole(_strappend(_strconcat(__str106, uutils_IntToStr(j)), 0x21));
                                   }
                                   else
                                   {
                                       ControllerNumAxes[j] = SDL_JoystickNumAxes(Controller[j]);
                                       ControllerNumHats[j] = SDL_JoystickNumHats(Controller[j]);
                                       ControllerNumButtons[j] = SDL_JoystickNumButtons(Controller[j]);
                                       uconsole_WriteLnToConsole(_strconcat(__str107, uutils_IntToStr(ControllerNumAxes[j])));
                                       uconsole_WriteLnToConsole(_strconcat(__str108, uutils_IntToStr(ControllerNumHats[j])));
                                       uconsole_WriteLnToConsole(_strconcat(__str109, uutils_IntToStr(ControllerNumButtons[j])));
                                       ControllerEnabled = 1;
                                       if(ControllerNumAxes[j] > 20)
                                       {
                                           ControllerNumAxes[j] = 20;
                                       }
                                       if(ControllerNumHats[j] > 20)
                                       {
                                           ControllerNumHats[j] = 20;
                                       }
                                       if(ControllerNumButtons[j] > 20)
                                       {
                                           ControllerNumButtons[j] = 20;
                                       }
                                   }
                               } while(j++ != j__end__);}
        SDL_JoystickEventState(1);
    }
    else
    {
        uconsole_WriteLnToConsole(__str110);
    }
};
void uinputhandler_ControllerAxisEvent(Byte joy,Byte axis,Integer value)
{
    LongInt k;
    SDL_GetKeyboardState(&(k));
    k = k + (joy * (((ControllerNumAxes[joy] * 2) + (ControllerNumHats[joy] * 4)) + (ControllerNumButtons[joy] * 2)));
    uinputhandler_ProcessKey_2(k + (axis * 2), value > 20000);
    uinputhandler_ProcessKey_2((k + (axis * 2)) + 1, value < -20000);
};
void uinputhandler_ControllerHatEvent(Byte joy,Byte hat,Byte value)
{
    LongInt k;
    SDL_GetKeyboardState(&(k));
    k = k + (joy * (((ControllerNumAxes[joy] * 2) + (ControllerNumHats[joy] * 4)) + (ControllerNumButtons[joy] * 2)));
    uinputhandler_ProcessKey_2(((k + (ControllerNumAxes[joy] * 2)) + (hat * 4)) + 0, (value & SDL_HAT_UP) != 0);
    uinputhandler_ProcessKey_2(((k + (ControllerNumAxes[joy] * 2)) + (hat * 4)) + 1, (value & SDL_HAT_RIGHT) != 0);
    uinputhandler_ProcessKey_2(((k + (ControllerNumAxes[joy] * 2)) + (hat * 4)) + 2, (value & SDL_HAT_DOWN) != 0);
    uinputhandler_ProcessKey_2(((k + (ControllerNumAxes[joy] * 2)) + (hat * 4)) + 3, (value & SDL_HAT_LEFT) != 0);
};
void uinputhandler_ControllerButtonEvent(Byte joy,Byte button,boolean pressed)
{
    LongInt k;
    SDL_GetKeyboardState(&(k));
    k = k + (joy * (((ControllerNumAxes[joy] * 2) + (ControllerNumHats[joy] * 4)) + (ControllerNumButtons[joy] * 2)));
    uinputhandler_ProcessKey_2(((k + (ControllerNumAxes[joy] * 2)) + (ControllerNumHats[joy] * 4)) + button, pressed);
};
void uinputhandler_loadBinds(string255 cmd,string255 s)
{
    LongInt i;
    PFSFile f;
    string255 p;
    string255 l;
    Byte b;
    if(cOnlyStats)
    {
        return;
    }
    uutils_AddFileLog(_strconcat(__str111, s));
    l = __str0;
    if(uphysfslayer_pfsExists(s))
    {
        f = uphysfslayer_pfsOpenRead(s);
        while(!uphysfslayer_pfsEOF(f) && (_strncompare(l, __str112)))
        {
            uphysfslayer_pfsReadLn(f, &(l));
        }
        while(!uphysfslayer_pfsEOF(f) && (_strncompare(l, __str0)))
        {
            uphysfslayer_pfsReadLn(f, &(l));
            p = __str0;
            i = 1;
            while((i <= fpcrtl_Length(l)) && (l.s[i] != 0x3d))
            {
                if(l.s[i] == 0x25)
                {
                    l.s[i] = 0x24;
                    fpcrtl_val(fpcrtl_copy(l, i, 3), b);
                    p = _strappend(p, ((char)b));
                    i += 3;
                }
                else
                {
                    p = _strappend(p, l.s[i]);
                    ++i;
                }
            }
            if(i < fpcrtl_Length(l))
            {
                l = fpcrtl_copy(l, i + 1, fpcrtl_Length(l) - i);
                if(_strncompare(l, __str113))
                {
                    if((fpcrtl_Length(l) == 2) && (l.s[1] == 0x5c))
                    {
                        l = _strprepend(l.s[1], __str0);
                    }
                    else
                    {
                        if((l.s[1] == 0x22) && (l.s[fpcrtl_Length(l)] == 0x22))
                        {
                            l = fpcrtl_copy(l, 2, fpcrtl_Length(l) - 2);
                        }
                    }
                    p = _strconcat(_strappend(_strconcat(_strappend(cmd, 0x20), l), 0x20), p);
                    ucommands_ParseCommand_2(p, true);
                }
            }
        }
        uphysfslayer_pfsClose(f);
    }
    else
    {
        uutils_AddFileLog(__str114);
    }
};
void uinputhandler_addBind(TBinds (*binds),string255 (*id))
{
    string255 KeyName;
    string255 Modifier;
    string255 tmp;
    LongInt i;
    LongInt newCode;
    LongInt code;
    LongInt b;
    KeyName = __str0;
    Modifier = __str0;
    if(fpcrtl_pos(__str115, (*id)) != 0)
    {
        tmp = __str0;
        uutils_SplitBySpace(&((*id)), &(tmp));
        Modifier = (*id);
        (*id) = tmp;
    }
    uutils_SplitBySpace(&((*id)), &(KeyName));
    if(KeyName.s[1] == 0x22)
    {
        fpcrtl_Delete(KeyName, 1, 1);
    }
    if(KeyName.s[((Byte)KeyName.s[0])] == 0x22)
    {
        fpcrtl_Delete(KeyName, ((Byte)KeyName.s[0]), 1);
    }
    b = uinputhandler_KeyNameToCode_2((*id), Modifier);
    if(b == 0)
    {
        udebug_OutError(_strappend(_strconcat(_strconcat(errmsgUnknownVariable, __str116), (*id)), 0x22), false);
    }
    else
    {
        i = 0;
        while((i <= 255) && (_strncompare((*binds).binds[i], KeyName)))
        {
            ++i;
        }
        if(i <= 255)
        {
            code = 0;
            while((code <= cKbdMaxIndex) && ((*binds).indices[code] != i))
            {
                ++code;
            }
            udebug_checkFails(code <= cKbdMaxIndex, __str117, true);
            (*binds).indices[code] = 0;
            (*binds).binds[i] = __str0;
        }
        if((*binds).indices[b] > 0)
        {
            newCode = (*binds).indices[b];
        }
        else
        {
            if(i >= 255)
            {
                ++(*binds).lastIndex;
                udebug_checkFails((*binds).lastIndex < 255, __str118, true);
                newCode = (*binds).lastIndex;
            }
            else
            {
                newCode = i;
            }
        }
        (*binds).indices[b] = newCode;
        (*binds).binds[(*binds).indices[b]] = KeyName;
    }
};
void uinputhandler_chDefaultBind(string255 (*id))
{
    uinputhandler_addBind(&(DefaultBinds), &((*id)));
};
void uinputhandler_initModule()
{
    mwheelupCode = 0;
    mwheeldownCode = 0;
    ucommands_RegisterVariable_3(__str100, &(uinputhandler_chDefaultBind), true);
};
void uinputhandler_freeModule()
{
    LongInt j;
    if(ControllerEnabled > 0)
    {
        {j = 0;
         LongInt j__end__ = ((int)(ControllerNumControllers) - 1);
         if (j <= j__end__) do {
                                   SDL_JoystickClose(Controller[j]);
                               } while(j++ != j__end__);}
    }
};
