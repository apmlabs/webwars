#pragma once

#include "pas2c.h"

static const string255 SDLLibName = STRINIT("libSDL2");
static const string255 SDL_TTFLibName = STRINIT("libSDL2_ttf");
static const string255 SDL_MixerLibName = STRINIT("libSDL2_mixer");
static const string255 SDL_ImageLibName = STRINIT("libSDL2_image");
static const string255 SDL_NetLibName = STRINIT("libSDL2_net");
enum{SDL_FALSE = 0};
enum{SDL_TRUE = 1};
enum{SDL_INIT_TIMER = 0x00000001};
enum{SDL_INIT_AUDIO = 0x00000010};
enum{SDL_INIT_VIDEO = 0x00000020};
enum{SDL_INIT_JOYSTICK = 0x00000200};
enum{SDL_INIT_HAPTIC = 0x00001000};
enum{SDL_INIT_GAMECONTROLLER = 0x00002000};
enum{SDL_INIT_EVENTS = 0x00004000};
enum{SDL_INIT_NOPARACHUTE = 0x00100000};
enum{SDL_ALLEVENTS = 0xffffffff};
enum{SDL_APPINPUTFOCUS = 0x02};
enum{AUDIO_S16LSB = 0x8010};
enum{AUDIO_S16MSB = 0x9010};
enum{AUDIO_S16SYS = AUDIO_S16LSB};
enum{MIX_DEFAULT_FORMAT = AUDIO_S16LSB};
enum{SDL_BUTTON_LEFT = 1};
enum{SDL_BUTTON_MIDDLE = 2};
enum{SDL_BUTTON_RIGHT = 3};
enum{SDL_BUTTON_X1 = 4};
enum{SDL_BUTTON_X2 = 5};
enum{SDL_QUERY = -1};
enum{SDL_DISABLE = 0};
enum{SDL_ENABLE = 1};
enum{SDL_TEXTEDITINGEVENT_TEXT_SIZE = 32};
enum{SDL_TEXTINPUTEVENT_TEXT_SIZE = 32};
enum{SDL_FIRSTEVENT = 0};
enum{SDL_COMMONDEVENT = 1};
enum{SDL_QUITEV = 0x100};
enum{SDL_APP_TERMINATING = 0x101};
enum{SDL_APP_LOWMEMORY = 0x102};
enum{SDL_APP_WILLENTERBACKGROUND = 0x103};
enum{SDL_APP_DIDENTERBACKGROUND = 0x104};
enum{SDL_APP_WILLENTERFOREGROUND = 0x105};
enum{SDL_APP_DIDENTERFOREGROUND = 0x106};
enum{SDL_WINDOWEVENT = 0x200};
enum{SDL_SYSWMEVENT = 0x201};
enum{SDL_KEYDOWN = 0x300};
enum{SDL_KEYUP = 0x301};
enum{SDL_TEXTEDITING = 0x302};
enum{SDL_TEXTINPUT = 0x303};
enum{SDL_MOUSEMOTION = 0x400};
enum{SDL_MOUSEBUTTONDOWN = 0x401};
enum{SDL_MOUSEBUTTONUP = 0x402};
enum{SDL_MOUSEWHEEL = 0x403};
enum{SDL_JOYAXISMOTION = 0x600};
enum{SDL_JOYBALLMOTION = 0x601};
enum{SDL_JOYHATMOTION = 0x602};
enum{SDL_JOYBUTTONDOWN = 0x603};
enum{SDL_JOYBUTTONUP = 0x604};
enum{SDL_JOYDEVICEADDED = 0x605};
enum{SDL_JOYDEVICEREMOVED = 0x606};
enum{SDL_CONTROLLERAXISMOTION = 0x650};
enum{SDL_CONTROLLERBUTTONDOWN = 0x651};
enum{SDL_CONTROLLERBUTTONUP = 0x652};
enum{SDL_CONTROLLERDEVICEADDED = 0x653};
enum{SDL_CONTROLLERDEVICEREMOVED = 0x654};
enum{SDL_CONTROLLERDEVICEREMAPPED = 0x655};
enum{SDL_FINGERDOWN = 0x700};
enum{SDL_FINGERUP = 0x701};
enum{SDL_FINGERMOTION = 0x702};
enum{SDL_DOLLARGESTURE = 0x800};
enum{SDL_DOLLARRECORD = 0x801};
enum{SDL_MULTIGESTURE = 0x802};
enum{SDL_CLIPBOARDUPDATE = 0x900};
enum{SDL_DROPFILE = 0x1000};
enum{SDL_USEREVENT = 0x8000};
enum{SDL_LASTEVENT = 0xffff};
enum{SDL_SWSURFACE = 0x00000000};
enum{SDL_PREALLOC = 0x00000001};
enum{SDL_RLEACCEL = 0x00000002};
enum{SDL_DONTFREE = 0x00000004};
enum{SDL_SRCCOLORKEY = 0x00020000};
enum{SDL_RENDERER_SOFTWARE = 0x00000001};
enum{SDL_RENDERER_ACCELERATED = 0x00000002};
enum{SDL_RENDERER_PRESENTVSYNC = 0x00000004};
enum{SDL_RENDERER_TARGETTEXTURE = 0x00000008};
enum{SDL_WINDOW_FULLSCREEN = 0x00000001};
enum{SDL_WINDOW_OPENGL = 0x00000002};
enum{SDL_WINDOW_SHOWN = 0x00000004};
enum{SDL_WINDOW_HIDDEN = 0x00000008};
enum{SDL_WINDOW_BORDERLESS = 0x00000010};
enum{SDL_WINDOW_RESIZABLE = 0x00000020};
enum{SDL_WINDOW_MINIMIZED = 0x00000040};
enum{SDL_WINDOW_MAXIMIZED = 0x00000080};
enum{SDL_WINDOW_INPUT_GRABBED = 0x00000100};
enum{SDL_WINDOW_INPUT_FOCUS = 0x00000200};
enum{SDL_WINDOW_MOUSE_FOCUS = 0x00000400};
enum{SDL_WINDOW_FULLSCREEN_DESKTOP = 0x00001001};
enum{SDL_WINDOW_FOREIGN = 0x00000800};
enum{SDL_WINDOWPOS_CENTERED_MASK = 0x2fff0000};
enum{SDL_WINDOWEVENT_NONE = 0};
enum{SDL_WINDOWEVENT_SHOWN = 1};
enum{SDL_WINDOWEVENT_HIDDEN = 2};
enum{SDL_WINDOWEVENT_EXPOSED = 3};
enum{SDL_WINDOWEVENT_MOVED = 4};
enum{SDL_WINDOWEVENT_RESIZED = 5};
enum{SDL_WINDOWEVENT_SIZE_CHANGED = 6};
enum{SDL_WINDOWEVENT_MINIMIZED = 7};
enum{SDL_WINDOWEVENT_MAXIMIZED = 8};
enum{SDL_WINDOWEVENT_RESTORED = 9};
enum{SDL_WINDOWEVENT_ENTER = 10};
enum{SDL_WINDOWEVENT_LEAVE = 11};
enum{SDL_WINDOWEVENT_FOCUS_GAINED = 12};
enum{SDL_WINDOWEVENT_FOCUS_LOST = 13};
enum{SDL_WINDOWEVENT_CLOSE = 14};
enum{RMask = 0x000000ff};
enum{GMask = 0x0000ff00};
enum{BMask = 0x00ff0000};
enum{AMask = 0xff000000};
enum{RShift = 0};
enum{GShift = 8};
enum{BShift = 16};
enum{AShift = 24};
enum{AByteIndex = 3};
enum{KMOD_NONE = 0x0000};
enum{KMOD_LSHIFT = 0x0001};
enum{KMOD_RSHIFT = 0x0002};
enum{KMOD_LCTRL = 0x0040};
enum{KMOD_RCTRL = 0x0080};
enum{KMOD_LALT = 0x0400};
enum{KMOD_RALT = 0x0800};
enum{KMOD_LMETA = 0x0400};
enum{KMOD_RMETA = 0x0800};
enum{KMOD_NUM = 0x1000};
enum{KMOD_CAPS = 0x2000};
enum{KMOD_MODE = 0x4000};
enum{MIX_MAX_VOLUME = 128};
enum{MIX_INIT_FLAC = 0x00000001};
enum{MIX_INIT_MOD = 0x00000002};
enum{MIX_INIT_MODPLUG = 0x00000004};
enum{MIX_INIT_MP3 = 0x00000008};
enum{MIX_INIT_OGG = 0x00000010};
enum{MIX_INIT_FLUIDSYNTH = 0x00000020};
enum{MIX_INIT_OPUS = 0x00000040};
enum{TTF_STYLE_NORMAL = 0};
enum{TTF_STYLE_BOLD = 1};
enum{TTF_STYLE_ITALIC = 2};
enum{SDL_HAT_CENTERED = 0x00};
enum{SDL_HAT_UP = 0x01};
enum{SDL_HAT_RIGHT = 0x02};
enum{SDL_HAT_DOWN = 0x04};
enum{SDL_HAT_LEFT = 0x08};
enum{SDL_HAT_RIGHTUP = (SDL_HAT_RIGHT | SDL_HAT_UP)};
enum{SDL_HAT_RIGHTDOWN = (SDL_HAT_RIGHT | SDL_HAT_DOWN)};
enum{SDL_HAT_LEFTUP = (SDL_HAT_LEFT | SDL_HAT_UP)};
enum{SDL_HAT_LEFTDOWN = (SDL_HAT_LEFT | SDL_HAT_DOWN)};
enum{IMG_INIT_JPG = 0x00000001};
enum{IMG_INIT_PNG = 0x00000002};
enum{IMG_INIT_TIF = 0x00000004};
enum{SDLK_UNKNOWN = 0};
enum{SDLK_BACKSPACE = 8};
enum{SDLK_RETURN = 13};
enum{SDLK_ESCAPE = 27};
enum{SDLK_a = 97};
enum{SDLK_c = 99};
enum{SDLK_q = 113};
enum{SDLK_v = 118};
enum{SDLK_w = 119};
enum{SDLK_x = 120};
enum{SDLK_DELETE = 127};
enum{SDLK_KP_ENTER = 271};
enum{SDLK_UP = 273};
enum{SDLK_DOWN = 274};
enum{SDLK_RIGHT = 275};
enum{SDLK_LEFT = 276};
enum{SDLK_HOME = 278};
enum{SDLK_END = 279};
enum{SDLK_PAGEUP = 280};
enum{SDLK_PAGEDOWN = 281};
enum{SDLK_SCANCODE_MASK = (1 << 30)};
enum{SDL_SCANCODE_UNKNOWN = 0};
enum{SDL_SCANCODE_A = 4};
enum{SDL_SCANCODE_B = 5};
enum{SDL_SCANCODE_C = 6};
enum{SDL_SCANCODE_D = 7};
enum{SDL_SCANCODE_E = 8};
enum{SDL_SCANCODE_F = 9};
enum{SDL_SCANCODE_G = 10};
enum{SDL_SCANCODE_H = 11};
enum{SDL_SCANCODE_I = 12};
enum{SDL_SCANCODE_J = 13};
enum{SDL_SCANCODE_K = 14};
enum{SDL_SCANCODE_L = 15};
enum{SDL_SCANCODE_M = 16};
enum{SDL_SCANCODE_N = 17};
enum{SDL_SCANCODE_O = 18};
enum{SDL_SCANCODE_P = 19};
enum{SDL_SCANCODE_Q = 20};
enum{SDL_SCANCODE_R = 21};
enum{SDL_SCANCODE_S = 22};
enum{SDL_SCANCODE_T = 23};
enum{SDL_SCANCODE_U = 24};
enum{SDL_SCANCODE_V = 25};
enum{SDL_SCANCODE_W = 26};
enum{SDL_SCANCODE_X = 27};
enum{SDL_SCANCODE_Y = 28};
enum{SDL_SCANCODE_Z = 29};
enum{SDL_SCANCODE_1 = 30};
enum{SDL_SCANCODE_2 = 31};
enum{SDL_SCANCODE_3 = 32};
enum{SDL_SCANCODE_4 = 33};
enum{SDL_SCANCODE_5 = 34};
enum{SDL_SCANCODE_6 = 35};
enum{SDL_SCANCODE_7 = 36};
enum{SDL_SCANCODE_8 = 37};
enum{SDL_SCANCODE_9 = 38};
enum{SDL_SCANCODE_0 = 39};
enum{SDL_SCANCODE_RETURN = 40};
enum{SDL_SCANCODE_ESCAPE = 41};
enum{SDL_SCANCODE_BACKSPACE = 42};
enum{SDL_SCANCODE_TAB = 43};
enum{SDL_SCANCODE_SPACE = 44};
enum{SDL_SCANCODE_MINUS = 45};
enum{SDL_SCANCODE_EQUALS = 46};
enum{SDL_SCANCODE_LEFTBRACKET = 47};
enum{SDL_SCANCODE_RIGHTBRACKET = 48};
enum{SDL_SCANCODE_BACKSLASH = 49};
enum{SDL_SCANCODE_NONUSHASH = 50};
enum{SDL_SCANCODE_SEMICOLON = 51};
enum{SDL_SCANCODE_APOSTROPHE = 52};
enum{SDL_SCANCODE_GRAVE = 53};
enum{SDL_SCANCODE_COMMA = 54};
enum{SDL_SCANCODE_PERIOD = 55};
enum{SDL_SCANCODE_SLASH = 56};
enum{SDL_SCANCODE_CAPSLOCK = 57};
enum{SDL_SCANCODE_F1 = 58};
enum{SDL_SCANCODE_F2 = 59};
enum{SDL_SCANCODE_F3 = 60};
enum{SDL_SCANCODE_F4 = 61};
enum{SDL_SCANCODE_F5 = 62};
enum{SDL_SCANCODE_F6 = 63};
enum{SDL_SCANCODE_F7 = 64};
enum{SDL_SCANCODE_F8 = 65};
enum{SDL_SCANCODE_F9 = 66};
enum{SDL_SCANCODE_F10 = 67};
enum{SDL_SCANCODE_F11 = 68};
enum{SDL_SCANCODE_F12 = 69};
enum{SDL_SCANCODE_PRINTSCREEN = 70};
enum{SDL_SCANCODE_SCROLLLOCK = 71};
enum{SDL_SCANCODE_PAUSE = 72};
enum{SDL_SCANCODE_INSERT = 73};
enum{SDL_SCANCODE_HOME = 74};
enum{SDL_SCANCODE_PAGEUP = 75};
enum{SDL_SCANCODE_DELETE = 76};
enum{SDL_SCANCODE_END = 77};
enum{SDL_SCANCODE_PAGEDOWN = 78};
enum{SDL_SCANCODE_RIGHT = 79};
enum{SDL_SCANCODE_LEFT = 80};
enum{SDL_SCANCODE_DOWN = 81};
enum{SDL_SCANCODE_UP = 82};
enum{SDL_SCANCODE_NUMLOCKCLEAR = 83};
enum{SDL_SCANCODE_KP_DIVIDE = 84};
enum{SDL_SCANCODE_KP_MULTIPLY = 85};
enum{SDL_SCANCODE_KP_MINUS = 86};
enum{SDL_SCANCODE_KP_PLUS = 87};
enum{SDL_SCANCODE_KP_ENTER = 88};
enum{SDL_SCANCODE_KP_1 = 89};
enum{SDL_SCANCODE_KP_2 = 90};
enum{SDL_SCANCODE_KP_3 = 91};
enum{SDL_SCANCODE_KP_4 = 92};
enum{SDL_SCANCODE_KP_5 = 93};
enum{SDL_SCANCODE_KP_6 = 94};
enum{SDL_SCANCODE_KP_7 = 95};
enum{SDL_SCANCODE_KP_8 = 96};
enum{SDL_SCANCODE_KP_9 = 97};
enum{SDL_SCANCODE_KP_0 = 98};
enum{SDL_SCANCODE_KP_PERIOD = 99};
enum{SDL_SCANCODE_NONUSBACKSLASH = 100};
enum{SDL_SCANCODE_APPLICATION = 101};
enum{SDL_SCANCODE_POWER = 102};
enum{SDL_SCANCODE_KP_EQUALS = 103};
enum{SDL_SCANCODE_F13 = 104};
enum{SDL_SCANCODE_F14 = 105};
enum{SDL_SCANCODE_F15 = 106};
enum{SDL_SCANCODE_F16 = 107};
enum{SDL_SCANCODE_F17 = 108};
enum{SDL_SCANCODE_F18 = 109};
enum{SDL_SCANCODE_F19 = 110};
enum{SDL_SCANCODE_F20 = 111};
enum{SDL_SCANCODE_F21 = 112};
enum{SDL_SCANCODE_F22 = 113};
enum{SDL_SCANCODE_F23 = 114};
enum{SDL_SCANCODE_F24 = 115};
enum{SDL_SCANCODE_EXECUTE = 116};
enum{SDL_SCANCODE_HELP = 117};
enum{SDL_SCANCODE_MENU = 118};
enum{SDL_SCANCODE_SELECT = 119};
enum{SDL_SCANCODE_STOP = 120};
enum{SDL_SCANCODE_AGAIN = 121};
enum{SDL_SCANCODE_UNDO = 122};
enum{SDL_SCANCODE_CUT = 123};
enum{SDL_SCANCODE_COPY = 124};
enum{SDL_SCANCODE_PASTE = 125};
enum{SDL_SCANCODE_FIND = 126};
enum{SDL_SCANCODE_MUTE = 127};
enum{SDL_SCANCODE_VOLUMEUP = 128};
enum{SDL_SCANCODE_VOLUMEDOWN = 129};
enum{SDL_SCANCODE_KP_COMMA = 133};
enum{SDL_SCANCODE_KP_EQUALSAS400 = 134};
enum{SDL_SCANCODE_INTERNATIONAL1 = 135};
enum{SDL_SCANCODE_INTERNATIONAL2 = 136};
enum{SDL_SCANCODE_INTERNATIONAL3 = 137};
enum{SDL_SCANCODE_INTERNATIONAL4 = 138};
enum{SDL_SCANCODE_INTERNATIONAL5 = 139};
enum{SDL_SCANCODE_INTERNATIONAL6 = 140};
enum{SDL_SCANCODE_INTERNATIONAL7 = 141};
enum{SDL_SCANCODE_INTERNATIONAL8 = 142};
enum{SDL_SCANCODE_INTERNATIONAL9 = 143};
enum{SDL_SCANCODE_LANG1 = 144};
enum{SDL_SCANCODE_LANG2 = 145};
enum{SDL_SCANCODE_LANG3 = 146};
enum{SDL_SCANCODE_LANG4 = 147};
enum{SDL_SCANCODE_LANG5 = 148};
enum{SDL_SCANCODE_LANG6 = 149};
enum{SDL_SCANCODE_LANG7 = 150};
enum{SDL_SCANCODE_LANG8 = 151};
enum{SDL_SCANCODE_LANG9 = 152};
enum{SDL_SCANCODE_ALTERASE = 153};
enum{SDL_SCANCODE_SYSREQ = 154};
enum{SDL_SCANCODE_CANCEL = 155};
enum{SDL_SCANCODE_CLEAR = 156};
enum{SDL_SCANCODE_PRIOR = 157};
enum{SDL_SCANCODE_RETURN2 = 158};
enum{SDL_SCANCODE_SEPARATOR = 159};
enum{SDL_SCANCODE_OUT = 160};
enum{SDL_SCANCODE_OPER = 161};
enum{SDL_SCANCODE_CLEARAGAIN = 162};
enum{SDL_SCANCODE_CRSEL = 163};
enum{SDL_SCANCODE_EXSEL = 164};
enum{SDL_SCANCODE_KP_00 = 176};
enum{SDL_SCANCODE_KP_000 = 177};
enum{SDL_SCANCODE_THOUSANDSSEPARATOR = 178};
enum{SDL_SCANCODE_DECIMALSEPARATOR = 179};
enum{SDL_SCANCODE_CURRENCYUNIT = 180};
enum{SDL_SCANCODE_CURRENCYSUBUNIT = 181};
enum{SDL_SCANCODE_KP_LEFTPAREN = 182};
enum{SDL_SCANCODE_KP_RIGHTPAREN = 183};
enum{SDL_SCANCODE_KP_LEFTBRACE = 184};
enum{SDL_SCANCODE_KP_RIGHTBRACE = 185};
enum{SDL_SCANCODE_KP_TAB = 186};
enum{SDL_SCANCODE_KP_BACKSPACE = 187};
enum{SDL_SCANCODE_KP_A = 188};
enum{SDL_SCANCODE_KP_B = 189};
enum{SDL_SCANCODE_KP_C = 190};
enum{SDL_SCANCODE_KP_D = 191};
enum{SDL_SCANCODE_KP_E = 192};
enum{SDL_SCANCODE_KP_F = 193};
enum{SDL_SCANCODE_KP_XOR = 194};
enum{SDL_SCANCODE_KP_PERCENT = 196};
enum{SDL_SCANCODE_KP_LESS = 197};
enum{SDL_SCANCODE_KP_GREATER = 198};
enum{SDL_SCANCODE_KP_AMPERSAND = 199};
enum{SDL_SCANCODE_KP_DBLAMPERSAND = 200};
enum{SDL_SCANCODE_KP_VERTICALBAR = 201};
enum{SDL_SCANCODE_KP_DBLVERTICALBAR = 202};
enum{SDL_SCANCODE_KP_COLON = 203};
enum{SDL_SCANCODE_KP_HASH = 204};
enum{SDL_SCANCODE_KP_SPACE = 205};
enum{SDL_SCANCODE_KP_AT = 206};
enum{SDL_SCANCODE_KP_EXCLAM = 207};
enum{SDL_SCANCODE_KP_MEMSTORE = 208};
enum{SDL_SCANCODE_KP_MEMRECALL = 209};
enum{SDL_SCANCODE_KP_MEMCLEAR = 210};
enum{SDL_SCANCODE_KP_MEMADD = 211};
enum{SDL_SCANCODE_KP_MEMSUBTRACT = 212};
enum{SDL_SCANCODE_KP_MEMMULTIPLY = 213};
enum{SDL_SCANCODE_KP_MEMDIVIDE = 214};
enum{SDL_SCANCODE_KP_PLUSMINUS = 215};
enum{SDL_SCANCODE_KP_CLEAR = 216};
enum{SDL_SCANCODE_KP_CLEARENTRY = 217};
enum{SDL_SCANCODE_KP_BINARY = 218};
enum{SDL_SCANCODE_KP_OCTAL = 219};
enum{SDL_SCANCODE_KP_DECIMAL = 220};
enum{SDL_SCANCODE_KP_HEXADECIMAL = 221};
enum{SDL_SCANCODE_LCTRL = 224};
enum{SDL_SCANCODE_LSHIFT = 225};
enum{SDL_SCANCODE_LALT = 226};
enum{SDL_SCANCODE_LGUI = 227};
enum{SDL_SCANCODE_RCTRL = 228};
enum{SDL_SCANCODE_RSHIFT = 229};
enum{SDL_SCANCODE_RALT = 230};
enum{SDL_SCANCODE_RGUI = 231};
enum{SDL_SCANCODE_MODE = 257};
enum{SDL_SCANCODE_AUDIONEXT = 258};
enum{SDL_SCANCODE_AUDIOPREV = 259};
enum{SDL_SCANCODE_AUDIOSTOP = 260};
enum{SDL_SCANCODE_AUDIOPLAY = 261};
enum{SDL_SCANCODE_AUDIOMUTE = 262};
enum{SDL_SCANCODE_MEDIASELECT = 263};
enum{SDL_SCANCODE_WWW = 264};
enum{SDL_SCANCODE_MAIL = 265};
enum{SDL_SCANCODE_CALCULATOR = 266};
enum{SDL_SCANCODE_COMPUTER = 267};
enum{SDL_SCANCODE_AC_SEARCH = 268};
enum{SDL_SCANCODE_AC_HOME = 269};
enum{SDL_SCANCODE_AC_BACK = 270};
enum{SDL_SCANCODE_AC_FORWARD = 271};
enum{SDL_SCANCODE_AC_STOP = 272};
enum{SDL_SCANCODE_AC_REFRESH = 273};
enum{SDL_SCANCODE_AC_BOOKMARKS = 274};
enum{SDL_SCANCODE_BRIGHTNESSDOWN = 275};
enum{SDL_SCANCODE_BRIGHTNESSUP = 276};
enum{SDL_SCANCODE_DISPLAYSWITCH = 277};
enum{SDL_SCANCODE_KBDILLUMTOGGLE = 278};
enum{SDL_SCANCODE_KBDILLUMDOWN = 279};
enum{SDL_SCANCODE_KBDILLUMUP = 280};
enum{SDL_SCANCODE_EJECT = 281};
enum{SDL_SCANCODE_SLEEP = 282};
enum{SDL_SCANCODE_APP1 = 283};
enum{SDL_SCANCODE_APP2 = 284};
typedef pointer PSDL_Window;
typedef pointer PSDL_Renderer;
typedef pointer PSDL_Texture;
typedef pointer PSDL_GLContext;
typedef Int64 TSDL_TouchId;
typedef Int64 TSDL_FingerId;
typedef LongInt TSDL_Keycode;
typedef LongInt TSDL_Scancode;
typedef LongInt TSDL_JoystickID;
typedef LongInt TSDL_bool;
typedef enum {SDL_ADDEVENT = 0x0,
              SDL_PEEPEVENT = 0x1,
              SDL_GETEVENT = 0x2} TSDL_eventaction;
typedef struct __TSDL_Rect * PSDL_Rect;
typedef struct __TSDL_Rect {
            LongInt x;
            LongInt y;
            LongInt w;
            LongInt h;
        } TSDL_Rect;
typedef struct __TPoint {
            LongInt x;
            LongInt y;
        } TPoint;
typedef struct __TSDL_PixelFormat * PSDL_PixelFormat;
typedef struct __TSDL_PixelFormat {
            LongWord format;
            pointer palette;
            Byte BitsPerPixel;
            Byte BytesPerPixel;
            Byte padding[(1 + 1)];
            LongWord RMask;
            LongWord GMask;
            LongWord BMask;
            LongWord AMask;
            Byte Rloss;
            Byte Gloss;
            Byte Bloss;
            Byte Aloss;
            Byte Rshift;
            Byte Gshift;
            Byte Bshift;
            Byte Ashift;
            LongInt refcount;
            PSDL_PixelFormat next;
        } TSDL_PixelFormat;
typedef struct __TSDL_Surface * PSDL_Surface;
typedef struct __TSDL_Surface {
            LongWord flags;
            PSDL_PixelFormat format;
            LongInt w;
            LongInt h;
            LongInt pitch;
            pointer pixels;
            pointer hwdata;
            TSDL_Rect clip_rect;
            LongWord unsed1;
            LongWord locked;
            pointer map;
            LongWord format_version;
            LongInt refcount;
            LongInt offset;
        } TSDL_Surface;
typedef struct __TSDL_Color * PSDL_Color;
typedef struct __TSDL_Color {
            Byte r;
            Byte g;
            Byte b;
            Byte a;
        } TSDL_Color;
typedef struct __TSDL_RWops * PSDL_RWops;
typedef Int64(*sdlh_TSize)(PSDL_RWops context);
typedef Int64(*sdlh_TSeek)(PSDL_RWops context,Int64 offset,LongInt whence);
typedef LongInt(*sdlh_TRead)(PSDL_RWops context,pointer Ptr,LongInt size,LongInt maxnum);
typedef LongInt(*sdlh_TWrite)(PSDL_RWops context,pointer Ptr,LongInt size,LongInt num);
typedef LongInt(*sdlh_TClose)(PSDL_RWops context);
typedef struct __TStdio {
            boolean autoclose;
            pointer fp;
        } TStdio;
typedef struct __TMem {
            PByte base;
            PByte here;
            PByte stop;
        } TMem;
typedef struct __TUnknown {
            pointer data1;
            pointer data2;
        } TUnknown;
typedef struct __TSDL_RWops {
            sdlh_TSize size;
            sdlh_TSeek seek;
            sdlh_TRead read;
            sdlh_TWrite write;
            sdlh_TClose close;
            LongWord type_;
            union
            {struct
             {TStdio stdio;};
             struct
             {TMem mem;};
             struct
             {TUnknown unknown;};};
        } TSDL_RWops;
typedef struct __TSDL_Keysym {
            TSDL_Scancode scancode;
            TSDL_Keycode sym;
            Word modifier;
            LongWord unused;
        } TSDL_Keysym;
typedef struct __TSDL_WindowEvent {
            LongWord type_;
            LongWord timestamp;
            LongWord windowID;
            Byte event;
            Byte padding1;
            Byte padding2;
            Byte padding3;
            LongInt data1;
            LongInt data2;
        } TSDL_WindowEvent;
typedef struct __TSDL_TextEditingEvent {
            LongWord type_;
            LongWord timestamp;
            LongWord windowID;
            char text[((SDL_TEXTEDITINGEVENT_TEXT_SIZE - 1) + 1)];
            LongInt start;
            LongInt length;
        } TSDL_TextEditingEvent;
typedef struct __TSDL_TextInputEvent {
            LongWord type_;
            LongWord timestamp;
            LongWord windowID;
            char text[((SDL_TEXTINPUTEVENT_TEXT_SIZE - 1) + 1)];
        } TSDL_TextInputEvent;
typedef struct __TSDL_TouchFingerEvent {
            LongWord type_;
            LongWord timestamp;
            TSDL_TouchId touchId;
            TSDL_FingerId fingerId;
            single x;
            single y;
            single dx;
            single dy;
            single pressure;
        } TSDL_TouchFingerEvent;
typedef struct __TSDL_MultiGestureEvent {
            LongWord type_;
            LongWord timestamp;
            TSDL_TouchId touchId;
            single dTheta;
            single dDist;
            single x;
            single y;
            Word numFingers;
            Word padding;
        } TSDL_MultiGestureEvent;
typedef struct __TSDL_DollarGestureEvent {
            LongWord type_;
            LongWord timestamp;
            Int64 touchId;
            Int64 gesturedId;
            LongWord numFingers;
            single error;
            single x;
            single y;
        } TSDL_DollarGestureEvent;
typedef struct __TSDL_DropEvent {
            LongWord type_;
            LongWord timestamp;
            PChar filename;
        } TSDL_DropEvent;
typedef struct __TSDL_SysWMEvent {
            LongWord type_;
            LongWord timestamp;
            pointer msg;
        } TSDL_SysWMEvent;
typedef struct __TSDL_ControllerAxisEvent {
            LongWord type_;
            LongWord timestamp;
            TSDL_JoystickID which;
            Byte axis;
            Byte padding1;
            Byte padding2;
            Byte padding3;
            SmallInt value;
            Word padding4;
        } TSDL_ControllerAxisEvent;
typedef struct __TSDL_ControllerButtonEvent {
            LongWord type_;
            LongWord timestamp;
            TSDL_JoystickID which;
            Byte button;
            Byte states;
            Byte padding1;
            Byte padding2;
        } TSDL_ControllerButtonEvent;
typedef struct __TSDL_ControllerDeviceEvent {
            LongWord type_;
            LongWord timestamp;
            LongInt which;
        } TSDL_ControllerDeviceEvent;
typedef TSDL_ControllerDeviceEvent TSDL_JoyDeviceEvent;
typedef struct __TSDL_CommonEvent {
            LongWord type_;
            LongWord timestamp;
        } TSDL_CommonEvent;
typedef TSDL_CommonEvent TSDL_OSEvent;
typedef struct __TSDL_KeyboardEvent {
            LongWord type_;
            LongWord timestamp;
            LongWord windowID;
            Byte state;
            Byte repeat_;
            Byte padding2;
            Byte padding3;
            TSDL_Keysym keysym;
        } TSDL_KeyboardEvent;
typedef struct __TSDL_MouseMotionEvent {
            LongWord type_;
            LongWord timestamp;
            LongWord windowID;
            LongWord which;
            LongWord state;
            LongInt x;
            LongInt y;
            LongInt xrel;
            LongInt yrel;
        } TSDL_MouseMotionEvent;
typedef struct __TSDL_MouseButtonEvent {
            LongWord type_;
            LongWord timestamp;
            LongWord windowID;
            LongWord which;
            Byte button;
            Byte state;
            Byte padding1;
            Byte padding2;
            LongInt x;
            LongInt y;
        } TSDL_MouseButtonEvent;
typedef struct __TSDL_MouseWheelEvent {
            LongWord type_;
            LongWord timestamp;
            LongWord windowID;
            LongWord which;
            LongInt x;
            LongInt y;
        } TSDL_MouseWheelEvent;
typedef struct __TSDL_JoyAxisEvent {
            LongWord type_;
            LongWord timestamp;
            TSDL_JoystickID which;
            Byte axis;
            Byte padding1;
            Byte padding2;
            Byte padding3;
            SmallInt value;
            Word padding4;
        } TSDL_JoyAxisEvent;
typedef struct __TSDL_JoyBallEvent {
            LongWord type_;
            LongWord timestamp;
            TSDL_JoystickID which;
            Byte ball;
            Byte padding1;
            Byte padding2;
            Byte padding3;
            SmallInt xrel;
            SmallInt yrel;
        } TSDL_JoyBallEvent;
typedef struct __TSDL_JoyHatEvent {
            LongWord type_;
            LongWord timestamp;
            TSDL_JoystickID which;
            Byte hat;
            Byte value;
            Byte padding1;
            Byte padding2;
        } TSDL_JoyHatEvent;
typedef struct __TSDL_JoyButtonEvent {
            LongWord type_;
            LongWord timestamp;
            TSDL_JoystickID which;
            Byte button;
            Byte state;
            Byte padding1;
            Byte padding2;
        } TSDL_JoyButtonEvent;
typedef struct __TSDL_QuitEvent {
            LongWord type_;
            LongWord timestamp;
        } TSDL_QuitEvent;
typedef struct __TSDL_UserEvent {
            LongWord type_;
            LongWord timestamp;
            LongWord windowID;
            LongInt code;
            pointer data1;
            pointer data2;
        } TSDL_UserEvent;
typedef struct __TSDL_Event * PSDL_Event;
typedef struct __TSDL_Event {
            union
            {struct
             {LongWord type_;};
             struct
             {TSDL_CommonEvent common;};
             struct
             {TSDL_WindowEvent window;};
             struct
             {TSDL_KeyboardEvent key;};
             struct
             {TSDL_TextEditingEvent edit;};
             struct
             {TSDL_TextInputEvent text;};
             struct
             {TSDL_MouseMotionEvent motion;};
             struct
             {TSDL_MouseButtonEvent button;};
             struct
             {TSDL_MouseWheelEvent wheel;};
             struct
             {TSDL_JoyAxisEvent jaxis;};
             struct
             {TSDL_JoyBallEvent jball;};
             struct
             {TSDL_JoyHatEvent jhat;};
             struct
             {TSDL_JoyButtonEvent jbutton;};
             struct
             {TSDL_JoyDeviceEvent jdevice;};
             struct
             {TSDL_ControllerAxisEvent caxis;};
             struct
             {TSDL_ControllerButtonEvent cbutton;};
             struct
             {TSDL_ControllerDeviceEvent cdevice;};
             struct
             {TSDL_QuitEvent quit;};
             struct
             {TSDL_UserEvent user;};
             struct
             {TSDL_SysWMEvent syswm;};
             struct
             {TSDL_TouchFingerEvent tfinger;};
             struct
             {TSDL_MultiGestureEvent mgesture;};
             struct
             {TSDL_DollarGestureEvent dgesture;};
             struct
             {TSDL_DropEvent drop;};
             struct
             {string255 foo;};};
        } TSDL_Event;
typedef Integer(*sdlh_TSDL_EventFilter)(PSDL_Event event);
typedef Byte TByteArray[(65535 + 1)];
typedef TByteArray * PByteArray;
typedef LongWord TLongWordArray[(16383 + 1)];
typedef TLongWordArray * PLongWordArray;
typedef Word TWordArray[(16383 + 1)];
typedef TWordArray * PWordArray;
typedef pointer PSDL_Thread;
typedef pointer PSDL_mutex;
typedef pointer PSDL_sem;
typedef enum {SDL_GL_RED_SIZE = 0x0,
              SDL_GL_GREEN_SIZE = 0x1,
              SDL_GL_BLUE_SIZE = 0x2,
              SDL_GL_ALPHA_SIZE = 0x3,
              SDL_GL_BUFFER_SIZE = 0x4,
              SDL_GL_DOUBLEBUFFER = 0x5,
              SDL_GL_DEPTH_SIZE = 0x6,
              SDL_GL_STENCIL_SIZE = 0x7,
              SDL_GL_ACCUM_RED_SIZE = 0x8,
              SDL_GL_ACCUM_GREEN_SIZE = 0x9,
              SDL_GL_ACCUM_BLUE_SIZE = 0xa,
              SDL_GL_ACCUM_ALPHA_SIZE = 0xb,
              SDL_GL_STEREO = 0xc,
              SDL_GL_MULTISAMPLEBUFFERS = 0xd,
              SDL_GL_MULTISAMPLESAMPLES = 0xe,
              SDL_GL_ACCELERATED_VISUAL = 0xf,
              SDL_GL_RETAINED_BACKING = 0x10,
              SDL_GL_CONTEXT_MAJOR_VERSION = 0x11,
              SDL_GL_CONTEXT_MINOR_VERSION = 0x12,
              SDL_GL_CONTEXT_EGL = 0x13,
              SDL_GL_CONTEXT_FLAGS = 0x14,
              SDL_GL_CONTEXT_PROFILE_MASK = 0x15,
              SDL_GL_SHARE_WITH_CURRENT_CONTEXT = 0x16} TSDL_GLattr;
typedef enum {SDL_ARRAYORDER_NONE = 0x0,
              SDL_ARRAYORDER_RGB = 0x1,
              SDL_ARRAYORDER_RGBA = 0x2,
              SDL_ARRAYORDER_ARGB = 0x3,
              SDL_ARRAYORDER_BGR = 0x4,
              SDL_ARRAYORDER_BGRA = 0x5,
              SDL_ARRAYORDER_ABGR = 0x6} TSDL_ArrayByteOrder;
typedef struct __TSDL_Joystick * PSDL_Joystick;
typedef struct __TSDL_Joystick {
        } TSDL_Joystick;
typedef struct __TTTF_font * PTTF_Font;
typedef struct __TTTF_Font {
        } TTTF_Font;
typedef struct __TMixChunk * PMixChunk;
typedef struct __TMixChunk {
            LongWord allocated;
            PByte abuf;
            LongWord alen;
            PByte volume;
        } TMixChunk;
typedef enum {MUS_CMD = 0x0,
              MUS_WAV = 0x1,
              MUS_MOD = 0x2,
              MUS_MID = 0x3,
              MUS_OGG = 0x4,
              MUS_MP3 = 0x5} TMusic;
typedef enum {MIX_NO_FADING = 0x0,
              MIX_FADING_OUT = 0x1,
              MIX_FADING_IN = 0x2} TMix_Fading;
typedef struct __TMidiSong {
            LongInt samples;
            pointer events;
        } TMidiSong;
typedef struct __TMusicUnion {
            union
            {struct
             {TMidiSong midi;};
             struct
             {pointer ogg;};};
        } TMusicUnion;
typedef struct __TMixMusic * PMixMusic;
typedef struct __TMixMusic {
        } TMixMusic;
typedef void(*sdlh_TPostMix)(pointer udata,PByte stream,LongInt len);
typedef struct __TIPAddress {
            LongWord host;
            Word port;
        } TIPAddress;
typedef struct __TTCPSocket * PTCPSocket;
typedef struct __TTCPSocket {
            LongInt ready;
            LongInt channel;
            TIPAddress remoteAddress;
            TIPAddress localAddress;
            LongInt sflag;
        } TTCPSocket;
typedef struct __TSDLNet_SocketSet * PSDLNet_SocketSet;
typedef struct __TSDLNet_SocketSet {
            LongInt numsockets;
            LongInt maxsockets;
            PTCPSocket sockets;
        } TSDLNet_SocketSet;
LongInt SDL_Init(LongWord flags);
LongInt SDL_InitSubSystem(LongWord flags);
void SDL_Quit();
void SDL_free(pointer mem);
void SDL_Delay(LongWord msec);
LongWord SDL_GetTicks();
boolean sdlh_SDL_MustLock(PSDL_Surface Surface);
LongInt SDL_LockSurface(PSDL_Surface Surface);
void SDL_UnlockSurface(PSDL_Surface Surface);
PChar SDL_GetError();
PSDL_Surface SDL_CreateRGBSurface(LongWord flags,LongInt Width,LongInt Height,LongInt Depth,LongWord RMask,LongWord GMask,LongWord BMask,LongWord AMask);
PSDL_Surface SDL_CreateRGBSurfaceFrom(pointer pixels,LongInt width,LongInt height,LongInt depth,LongInt pitch,LongWord RMask,LongWord GMask,LongWord BMask,LongWord AMask);
void SDL_FreeSurface(PSDL_Surface Surface);
LongInt SDL_SetColorKey(PSDL_Surface surface,LongWord flag,LongWord key);
LongInt SDL_SetAlpha(PSDL_Surface surface,LongWord flag,LongWord key);
PSDL_Surface SDL_ConvertSurface(PSDL_Surface src,PSDL_PixelFormat fmt,LongWord flags);
LongInt SDL_UpperBlit(PSDL_Surface src,PSDL_Rect srcrect,PSDL_Surface dst,PSDL_Rect dstrect);
LongInt SDL_FillRect(PSDL_Surface dst,PSDL_Rect dstrect,LongWord color);
void SDL_UpdateRect(PSDL_Surface Screen,LongInt x,LongInt y,LongWord w,LongWord h);
LongInt SDL_Flip(PSDL_Surface Screen);
void SDL_GetRGB(LongWord pixel,PSDL_PixelFormat fmt,PByte r,PByte g,PByte b);
void SDL_GetRGBA(LongWord pixel,PSDL_PixelFormat fmt,PByte r,PByte g,PByte b,PByte a);
LongWord SDL_MapRGB(PSDL_PixelFormat format,Byte r,Byte g,Byte b);
LongWord SDL_MapRGBA(PSDL_PixelFormat format,Byte r,Byte g,Byte b,Byte a);
PSDL_Surface SDL_DisplayFormat(PSDL_Surface Surface);
PSDL_Surface SDL_DisplayFormatAlpha(PSDL_Surface Surface);
PSDL_RWops SDL_RWFromFile(PChar filename,PChar mode);
LongInt SDL_SaveBMP_RW(PSDL_Surface surface,PSDL_RWops dst,LongInt freedst);
PSDL_Window SDL_CreateWindow(PChar title,LongInt x,LongInt y,LongInt w,LongInt h,LongWord flags);
void SDL_SetWindowIcon(PSDL_Window window,PSDL_Surface icon);
PSDL_Renderer SDL_CreateRenderer(PSDL_Window window,LongInt index,LongWord flags);
LongInt SDL_DestroyWindow(PSDL_Window window);
LongInt SDL_DestroyRenderer(PSDL_Renderer renderer);
void SDL_SetWindowPosition(PSDL_Window window,LongInt w,LongInt h);
void SDL_SetWindowSize(PSDL_Window window,LongInt w,LongInt h);
void SDL_SetWindowFullscreen(PSDL_Window window,LongWord flags);
PChar SDL_GetCurrentVideoDriver();
PSDL_GLContext SDL_GL_CreateContext(PSDL_Window window);
void SDL_GL_DeleteContext(PSDL_GLContext context);
void SDL_GL_SwapWindow(PSDL_Window window);
LongInt SDL_GL_SetSwapInterval(LongInt interval);
void SDL_VideoQuit();
LongInt SDL_GetNumVideoDisplays();
void SDL_ShowWindow(PSDL_Window window);
LongInt SDL_SetRenderDrawColor(PSDL_Renderer renderer,Byte r,Byte g,Byte b,Byte a);
PSDL_Renderer SDL_GetRenderer(PSDL_Window window);
LongInt SDL_RenderFillRect(PSDL_Renderer renderer,PSDL_Rect rect);
LongInt SDL_RenderClear(PSDL_Renderer renderer);
void SDL_RenderPresent(PSDL_Renderer renderer);
LongInt SDL_RenderReadPixels(PSDL_Renderer renderer,PSDL_Rect rect,LongInt format,pointer pixels,LongInt pitch);
LongInt SDL_RenderSetViewport(PSDL_Window window,PSDL_Rect rect);
LongInt SDL_SetRelativeMouseMode(TSDL_bool enabled);
Byte SDL_GetRelativeMouseState(PLongInt x,PLongInt y);
boolean SDL_PixelFormatEnumToMasks(TSDL_ArrayByteOrder format,PLongInt bpp,PLongInt Rmask,PLongInt Gmask,PLongInt Bmask,PLongInt Amask);
void SDL_WarpMouseInWindow(PSDL_Window window,LongInt x,LongInt y);
boolean SDL_SetHint(PChar name,PChar value);
void SDL_StartTextInput();
void SDL_StopTextInput();
void SDL_FlushEvent(LongWord eventType);
LongInt SDL_PeepEvents(PSDL_Event event,LongInt numevents,TSDL_eventaction action,LongWord minType,LongWord maxType);
PSDL_PixelFormat SDL_AllocFormat(LongWord format);
void SDL_FreeFormat(PSDL_PixelFormat pixelformat);
Byte SDL_GetMouseState(PLongInt x,PLongInt y);
PChar SDL_GetKeyName(TSDL_Keycode key);
PChar SDL_GetScancodeName(TSDL_Scancode key);
TSDL_Keycode SDL_GetKeyFromScancode(TSDL_Scancode key);
void SDL_PumpEvents();
LongInt SDL_PollEvent(PSDL_Event event);
LongInt SDL_WaitEvent(PSDL_Event event);
void SDL_SetEventFilter(sdlh_TSDL_EventFilter sdlh_filter);
LongInt SDL_ShowCursor(LongInt toggle);
void sdlh_SDL_WarpMouse(Word x,Word y);
PByteArray SDL_GetKeyboardState(PLongInt numkeys);
void SDL_WM_SetIcon(PSDL_Surface icon,Byte mask);
void SDL_WM_SetCaption(PChar title,PChar icon);
LongInt SDL_WM_ToggleFullScreen(PSDL_Surface surface);
PSDL_Thread SDL_CreateThread(pointer fn,PChar name,pointer data);
void SDL_WaitThread(PSDL_Thread thread,PLongInt status);
void SDL_DetachThread(PSDL_Thread thread);
void SDL_KillThread(PSDL_Thread thread);
PSDL_mutex SDL_CreateMutex();
void SDL_DestroyMutex(PSDL_mutex mutex);
LongInt SDL_LockMutex(PSDL_mutex mutex);
LongInt SDL_UnlockMutex(PSDL_mutex mutex);
PSDL_sem SDL_CreateSemaphore(LongWord initial_value);
void SDL_DestroySemaphore(PSDL_sem sem);
LongInt SDL_SemWait(PSDL_sem sem);
LongInt SDL_SemPost(PSDL_sem sem);
LongInt SDL_GL_SetAttribute(TSDL_GLattr attr,LongInt value);
void SDL_GL_SwapBuffers();
void SDL_LockAudio();
void SDL_UnlockAudio();
LongInt SDL_NumJoysticks();
PChar SDL_JoystickNameForIndex(LongInt idx);
PSDL_Joystick SDL_JoystickOpen(LongInt idx);
LongInt SDL_JoystickOpened(LongInt idx);
LongInt SDL_JoystickIndex(PSDL_Joystick joy);
LongInt SDL_JoystickNumAxes(PSDL_Joystick joy);
LongInt SDL_JoystickNumBalls(PSDL_Joystick joy);
LongInt SDL_JoystickNumHats(PSDL_Joystick joy);
LongInt SDL_JoystickNumButtons(PSDL_Joystick joy);
void SDL_JoystickUpdate();
LongInt SDL_JoystickEventState(LongInt state);
LongInt SDL_JoystickGetAxis(PSDL_Joystick joy,LongInt axis);
Word SDL_JoystickGetBall(PSDL_Joystick joy,LongInt ball,PInteger dx,PInteger dy);
Byte SDL_JoystickGetHat(PSDL_Joystick joy,LongInt hat);
Byte SDL_JoystickGetButton(PSDL_Joystick joy,LongInt button);
void SDL_JoystickClose(PSDL_Joystick joy);
LongInt TTF_Init();
void TTF_Quit();
LongInt TTF_SizeUTF8(PTTF_Font font,PChar text,PLongInt w,PLongInt h);
PSDL_Surface TTF_RenderUTF8_Solid(PTTF_Font font,PChar text,TSDL_Color fg);
PSDL_Surface TTF_RenderUTF8_Blended(PTTF_Font font,PChar text,TSDL_Color fg);
PSDL_Surface TTF_RenderUTF8_Shaded(PTTF_Font font,PChar text,TSDL_Color fg,TSDL_Color bg);
PTTF_Font TTF_OpenFontRW(PSDL_RWops src,LongBool freesrc,LongInt size);
void TTF_SetFontStyle(PTTF_Font font,LongInt style);
void TTF_CloseFont(PTTF_Font font);
LongInt Mix_Init(LongInt flags);
void Mix_Quit();
LongInt Mix_OpenAudio(LongInt frequency,Word format,LongInt channels,LongInt chunksize);
void Mix_CloseAudio();
LongInt Mix_QuerySpec(PLongInt frequency,PWord format,PLongInt channels);
LongInt Mix_Volume(LongInt channel,LongInt volume);
LongInt Mix_SetDistance(LongInt channel,Byte distance);
LongInt Mix_VolumeMusic(LongInt volume);
LongInt Mix_AllocateChannels(LongInt numchans);
void Mix_FreeChunk(PMixChunk chunk);
void Mix_FreeMusic(PMixMusic music);
PMixChunk Mix_LoadWAV_RW(PSDL_RWops src,LongInt freesrc);
PMixMusic Mix_LoadMUS_RW(PSDL_RWops src);
LongInt Mix_Playing(LongInt channel);
LongInt Mix_PlayingMusic();
LongInt Mix_FadeInMusic(PMixMusic music,LongInt loops,LongInt ms);
LongInt Mix_PlayChannelTimed(LongInt channel,PMixChunk chunk,LongInt loops,LongInt ticks);
LongInt Mix_PlayMusic(PMixMusic music,LongInt loops);
LongInt Mix_PausedMusic(PMixMusic music);
LongInt Mix_PauseMusic(PMixMusic music);
LongInt Mix_ResumeMusic(PMixMusic music);
LongInt Mix_HaltChannel(LongInt channel);
LongInt Mix_HaltMusic();
LongInt Mix_FadeInChannelTimed(LongInt channel,PMixChunk chunk,LongInt loops,LongInt fadems,LongInt ticks);
LongInt Mix_FadeOutChannel(LongInt channel,LongInt fadems);
void Mix_SetPostMix(sdlh_TPostMix sdlh_mix_func,pointer arg);
LongInt IMG_Init(LongInt flags);
void IMG_Quit();
PSDL_Surface IMG_Load(PChar _file);
PSDL_Surface IMG_Load_RW(PSDL_RWops rwop,LongBool freesrc);
PSDL_Surface IMG_LoadPNG_RW(PSDL_RWops rwop);
PSDL_Surface IMG_LoadTyped_RW(PSDL_RWops rwop,LongBool freesrc,PChar type_);
LongInt IMG_SavePNG(PSDL_Surface surface,PChar _file);
LongInt SDLNet_Init();
void SDLNet_Quit();
PSDLNet_SocketSet SDLNet_AllocSocketSet(LongInt maxsockets);
LongInt SDLNet_ResolveHost(TIPAddress (*address),PChar host,Word port);
PTCPSocket SDLNet_TCP_Accept(PTCPSocket server);
PTCPSocket SDLNet_TCP_Open(TIPAddress (*ip));
LongInt SDLNet_TCP_Send(PTCPSocket sock,pointer data,LongInt len);
LongInt SDLNet_TCP_Recv(PTCPSocket sock,pointer data,LongInt len);
void SDLNet_TCP_Close(PTCPSocket sock);
void SDLNet_FreeSocketSet(PSDLNet_SocketSet _set);
LongInt SDLNet_AddSocket(PSDLNet_SocketSet _set,PTCPSocket sock);
LongInt SDLNet_CheckSockets(PSDLNet_SocketSet _set,LongInt timeout);
boolean SDL_HasClipboardText();
PChar SDL_GetClipboardText();
LongInt SDL_SetClipboardText(PChar text);
void sdlh_SDLNet_Write16(Word value,pointer buf);
void sdlh_SDLNet_Write32(LongWord value,pointer buf);
Word sdlh_SDLNet_Read16(pointer buf);
LongWord sdlh_SDLNet_Read32(pointer buf);

string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TMix_Fading enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TMusic enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TSDL_ArrayByteOrder enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TSDL_GLattr enumvar);
string255 __attribute__((overloadable)) fpcrtl_GetEnumName(int dummy, const TSDL_eventaction enumvar);