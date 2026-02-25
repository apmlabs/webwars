#include "fpcrtl.h"

#include "uChat.h"
#include "uConsts.h"
#include "uInputHandler.h"
#include "uTypes.h"
#include "uVariables.h"
#include "uCommands.h"
#include "uUtils.h"
#include "uTextures.h"
#include "uRender.h"
#include "uIO.h"
#include "uScript.h"
#include "uRenderUtils.h"
#include "uStore.h"
#include "uLocale.h"
static const string255 __str37 = STRINIT("chat");
static const string255 __str36 = STRINIT("history");
static const string255 __str35 = STRINIT("say");
static const string255 __str34 = STRINIT("chatmsg");
static const string255 __str33 = STRINIT("/clan ");
static const string255 __str32 = STRINIT("* ");
static const string255 __str31 = STRINIT("/me ");
static const string255 __str30 = STRINIT("quit");
static const string255 __str29 = STRINIT("/taunt ");
static const string255 __str28 = STRINIT("help");
static const string255 __str27 = STRINIT("/help");
static const string255 __str26 = STRINIT("help room");
static const string255 __str25 = STRINIT("help taunts");
static const string255 __str24 = STRINIT("[Lua] chat input string parsing disabled");
static const string255 __str23 = STRINIT("[Lua] chat input string parsing enabled");
static const string255 __str22 = STRINIT("/lua issued");
static const string255 __str21 = STRINIT("lua");
static const string255 __str20 = STRINIT("debugvl");
static const string255 __str19 = STRINIT("sff");
static const string255 __str18 = STRINIT("ff ");
static const string255 __str17 = STRINIT("togglechat");
static const string255 __str16 = STRINIT("me ");
static const string255 __str15 = STRINIT("team ");
static const string255 __str14 = STRINIT("clan ");
static const string255 __str13 = STRINIT("hya ");
static const string255 __str12 = STRINIT("hta ");
static const string255 __str11 = STRINIT("hsa ");
static const string255 __str10 = STRINIT("clan");
static const string255 __str9 = STRINIT("team");
static const string255 __str8 = STRINIT("hya");
static const string255 __str7 = STRINIT("hta");
static const string255 __str6 = STRINIT("hsa");
static const string255 __str5 = STRINIT("me");
static const string255 __str4 = STRINIT("/say ");
static const string255 __str3 = STRINIT("/hogsay ");
static const string255 __str2 = STRINIT("[Lua] >");
static const string255 __str1 = STRINIT("[...]");
static const string255 __str0 = STRINIT("");
enum{MaxStrIndex = 27};
enum{MaxStrPartial = 7};
enum{MaxInputStrLen = 200};
typedef struct __TChatLine {
            PTexture Tex;
            LongWord Time;
            LongInt Width;
            string255 s;
            TSDL_Color Color;
        } TChatLine;
typedef enum {ccQuit = 0x0,
              ccPause = 0x1,
              ccShowHistory = 0x2,
              ccFullScreen = 0x3} TChatCmd;
typedef TChatLine Strs_tt[(MaxStrIndex + 1)];
static Strs_tt Strs;
typedef string255 MStrs_tt[(MaxStrIndex + 1)];
static MStrs_tt MStrs;
typedef string255 LocalStrs_tt[(MaxStrIndex + 1)];
static LocalStrs_tt LocalStrs;
static string255 oldInput;
static LongWord missedCount;
static LongWord lastStr;
static LongInt localLastStr;
static LongInt history;
static LongWord visibleCount;
static TChatLine InputStr;
static boolean ChatReady;
static boolean showAll;
static boolean liveLua;
static boolean ChatHidden;
static boolean firstDraw;
static TChatLine InputLinePrefix;
static LongInt cursorPos;
static LongInt cursorX;
static LongInt selectedPos;
static LongInt selectionDx;
static LongWord LastKeyPressTick;
typedef TSDL_Color colors_tt[(9 + 1)];
static colors_tt colors = {{
                               .r = 0xff,
                               .g = 0xff,
                               .b = 0x00,
                               .a = 0xff
                           },
                           {
                               .r = 0xff,
                               .g = 0xff,
                               .b = 0xff,
                               .a = 0xff
                           },
                           {
                               .r = 0xff,
                               .g = 0x00,
                               .b = 0xff,
                               .a = 0xff
                           },
                           {
                               .r = 0x90,
                               .g = 0xff,
                               .b = 0x90,
                               .a = 0xff
                           },
                           {
                               .r = 0xff,
                               .g = 0xff,
                               .b = 0xa0,
                               .a = 0xff
                           },
                           {
                               .r = 0xff,
                               .g = 0x00,
                               .b = 0x00,
                               .a = 0xff
                           },
                           {
                               .r = 0x00,
                               .g = 0xff,
                               .b = 0xff,
                               .a = 0xff
                           },
                           {
                               .r = 0xff,
                               .g = 0x80,
                               .b = 0x80,
                               .a = 0xff
                           },
                           {
                               .r = 0xff,
                               .g = 0xd0,
                               .b = 0x80,
                               .a = 0xff
                           },
                           {
                               .r = 0xdf,
                               .g = 0xdf,
                               .b = 0xdf,
                               .a = 0xff
                           }};
typedef struct __ChatCommandz_tt {
            string255 ChatCmd;
            string255 ProcedureCallChatCmd;
        } ChatCommandz_tt[4];
static ChatCommandz_tt ChatCommandz = {{
                                           .ChatCmd = STRINIT("/quit"),
                                           .ProcedureCallChatCmd = STRINIT("halt")
                                       },
                                       {
                                           .ChatCmd = STRINIT("/pause"),
                                           .ProcedureCallChatCmd = STRINIT("pause")
                                       },
                                       {
                                           .ChatCmd = STRINIT("/history"),
                                           .ProcedureCallChatCmd = STRINIT("history")
                                       },
                                       {
                                           .ChatCmd = STRINIT("/fullscreen"),
                                           .ProcedureCallChatCmd = STRINIT("fullscr")
                                       }};
#define PaddingFactor (0.125)
;
static Integer Padding;
static Integer ClHeight;
static real LastChatScaleValue;
static real LastUIScaleValue;
static boolean SkipNextInput;
void uchat_UpdateInputLinePrefix_0();
void uchat_UpdateCursorCoords_0();
boolean uchat_IsFirstCharByte(char c)
{
    boolean isfirstcharbyte_result;
    isfirstcharbyte_result = (((Byte)c) & 0xc0) != 0x80;
    return isfirstcharbyte_result;
};
boolean uchat_charIsForHogSpeech(char c)
{
    return ((c == 0x22) || (c == 0x27)) || (c == 0x2d);
};
void uchat_ResetSelection()
{
    selectedPos = -1;
};
void uchat_AdjustToUIScale()
{
    Integer fntSize;
    Integer fntSizePx;
    if((ChatScaleValue == LastChatScaleValue) && (UIScaleValue == LastUIScaleValue))
    {
        return;
    }
    LastChatScaleValue = ChatScaleValue;
    LastUIScaleValue = UIScaleValue;
    fntSize = uutils_Max(1, fpcrtl_round((UIScaleValue * ChatScaleValue) * cBaseChatFontHeight));
    if(Fontz[fntChat].Height != fntSize)
    {
        Fontz[fntChat].Height = fntSize;
        Fontz[CJKfntChat].Height = fntSize;
        if(Fontz[fntChat].Handle != NULL)
        {
            ustore_LoadFont(fntChat);
        }
        if(Fontz[CJKfntChat].Handle != NULL)
        {
            ustore_LoadFont(CJKfntChat);
        }
    }
    fntSizePx = fpcrtl_round(cFontPxToPtRatio * fntSize);
    Padding = uutils_Max(1, fpcrtl_round(PaddingFactor * fntSizePx));
    ClHeight = (2 * Padding) + fntSizePx;
    uchat_ReloadLines();
    uchat_UpdateInputLinePrefix_0();
    uchat_UpdateCursorCoords_0();
};
void uchat_ChatSizeInc(boolean pxprecise)
{
    Integer fntSize;
    if(pxprecise)
    {
        fntSize = Fontz[fntChat].Height;
        ++fntSize;
        ChatScaleValue = (1.0 * fntSize) /(float) cBaseChatFontHeight;
    }
    else
    {
        ChatScaleValue = ChatScaleValue * (1.0 + cChatScaleRelDelta);
    }
    if(ChatScaleValue > cMaxChatScaleValue)
    {
        ChatScaleValue = cMaxChatScaleValue;
    }
    uchat_AdjustToUIScale();
};
void uchat_ChatSizeDec(boolean pxprecise)
{
    Integer fntSize;
    if(pxprecise)
    {
        fntSize = Fontz[fntChat].Height;
        --fntSize;
        ChatScaleValue = (1.0 * fntSize) /(float) cBaseChatFontHeight;
    }
    else
    {
        ChatScaleValue = ChatScaleValue /(float) (1.0 + cChatScaleRelDelta);
    }
    if(ChatScaleValue < cMinChatScaleValue)
    {
        ChatScaleValue = cMinChatScaleValue;
    }
    uchat_AdjustToUIScale();
};
void uchat_chatSizeReset()
{
    ChatScaleValue = cDefaultChatScale;
    uchat_AdjustToUIScale();
};
THWFont uchat_GetChatFont(string255 str)
{
    THWFont getchatfont_result;
    getchatfont_result = uutils_CheckCJKFont(fpcrtl_str2astr(str), fntChat);
    return getchatfont_result;
};
void uchat_UpdateCursorCoords_0()
{
    THWFont font;
    string255 str;
    LongInt coff;
    LongInt soff;
    if(SDLwindow != NULL)
    {
        uchat_AdjustToUIScale();
    }
    if(cursorPos == selectedPos)
    {
        uchat_ResetSelection();
    }
    str = InputStr.s;
    font = uchat_GetChatFont(str);
    str.s[0] = ((char)cursorPos);
    TTF_SizeUTF8(Fontz[font].Handle, uutils_Str2PChar(str), &(coff), NULL);
    cursorX = Padding + coff;
    if(selectedPos >= 0)
    {
        if(selectedPos > cursorPos)
        {
            str = InputStr.s;
        }
        str.s[0] = ((char)selectedPos);
        TTF_SizeUTF8(Fontz[font].Handle, uutils_Str2PChar(str), &(soff), NULL);
        selectionDx = soff - coff;
    }
    else
    {
        selectionDx = 0;
    }
};
void uchat_ResetCursor()
{
    uchat_ResetSelection();
    cursorPos = 0;
    uchat_UpdateCursorCoords_0();
};
void uchat_RenderChatLineTex(TChatLine (*cl),string255 (*str))
{
    PSDL_Surface strSurface;
    PSDL_Surface tmpSurface;
    PSDL_Surface resSurface;
    TSDL_Rect dstrect;
    THWFont font;
    enum{shadowint = (0x80 << AShift)};
    utextures_FreeAndNilTexture(&((*cl).Tex));
    font = uchat_GetChatFont((*str));
    TTF_SizeUTF8(Fontz[font].Handle, uutils_Str2PChar((*str)), &((*cl).Width), NULL);
    (*cl).Width = (*cl).Width + (2 * Padding);
    resSurface = SDL_CreateRGBSurface(0, uutils_toPowerOf2((*cl).Width), uutils_toPowerOf2(ClHeight), 32, RMask, GMask, BMask, AMask);
    dstrect.x = 0;
    dstrect.y = 0;
    dstrect.w = (*cl).Width;
    dstrect.h = ClHeight;
    SDL_FillRect(resSurface, &(dstrect), shadowint);
    tmpSurface = NULL;
    strSurface = TTF_RenderUTF8_Blended(Fontz[font].Handle, uutils_Str2PChar((*str)), (*cl).Color);
    if(strSurface != NULL)
    {
        tmpSurface = SDL_ConvertSurface(strSurface, resSurface->format, 0);
    }
    SDL_FreeSurface(strSurface);
    if(tmpSurface != NULL)
    {
        urenderutils_copyToXY(tmpSurface, resSurface, Padding, Padding);
    }
    SDL_FreeSurface(tmpSurface);
    (*cl).Tex = utextures_Surface2Tex(resSurface, false);
    SDL_FreeSurface(resSurface);
};
enum{ClDisplayDuration = 12500};
void uchat_SetLine(TChatLine (*cl),string255 str,boolean isInput)
{
    TSDL_Color color;
    if(isInput)
    {
        (*cl).s = str;
        color = colors[0x6];
        str = _strappend(str, 0x20);
    }
    else
    {
        if(str.s[1] <= 0x9)
        {
            color = colors[str.s[1]];
            fpcrtl_Delete(str, 1, 1);
        }
        else
        {
            color = colors[0];
        }
        (*cl).s = str;
    }
    (*cl).Color = color;
    uchat_RenderChatLineTex(&((*cl)), &(str));
    (*cl).Time = RealTicks + ClDisplayDuration;
};
void uchat_ReloadLines()
{
    LongWord i;
    uchat_SetLine(&(InputStr), InputStr.s, true);
    {i = 0;
     LongWord i__end__ = MaxStrIndex;
     if (i <= i__end__) do {
                               if(_strncompare(Strs[i].s, __str0))
                               {
                                   uchat_RenderChatLineTex(&(Strs[i]), &(Strs[i].s));
                               }
                           } while(i++ != i__end__);}
};
void uchat_AddChatString(string255 s)
{
    if(!ChatReady)
    {
        if(missedCount < (MaxStrIndex - 1))
        {
            MStrs[missedCount] = s;
        }
        else
        {
            if(missedCount < MaxStrIndex)
            {
                MStrs[missedCount] = _strprepend(0x5, __str1);
            }
        }
        ++missedCount;
        return;
    }
    lastStr = (lastStr + 1) % (MaxStrIndex + 1);
    uchat_SetLine(&(Strs[lastStr]), s, false);
    ++visibleCount;
};
void uchat_UpdateInputLinePrefix_0()
{
    if(liveLua)
    {
        InputLinePrefix.Color = colors[0x1];
        InputLinePrefix.s = __str2;
    }
    else
    {
        InputLinePrefix.Color = colors[0x6];
        InputLinePrefix.s = _strappend(UserNick, 0x3e);
    }
    utextures_FreeAndNilTexture(&(InputLinePrefix.Tex));
};
void uchat_DrawChat()
{
    LongInt i;
    LongInt t;
    LongInt left;
    LongInt top;
    LongInt cnt;
    TSDL_Rect selRect;
    char c;
    uchat_AdjustToUIScale();
    ChatReady = true;
    if(ChatHidden && !showAll)
    {
        visibleCount = 0;
    }
    left = 4 - (cScreenWidth / 2);
    i = 10;
    top = i + (visibleCount * ClHeight);
    if(top > ((cScreenHeight - ClHeight) - 60))
    {
        top = (cScreenHeight - ClHeight) - 60;
        top = (i + top) - (top % ClHeight);
    }
    if(isInChatMode && (InputStr.Tex != NULL))
    {
        if(InputLinePrefix.Tex == NULL)
        {
            uchat_RenderChatLineTex(&(InputLinePrefix), &(InputLinePrefix.s));
        }
        urender_DrawTexture_3(left, top, InputLinePrefix.Tex);
        left += InputLinePrefix.Width;
        urender_DrawTexture_3(left, top, InputStr.Tex);
        if(firstDraw)
        {
            uchat_UpdateCursorCoords_0();
            firstDraw = false;
        }
        if(selectedPos < 0)
        {
            if(((((int64_t) (RealTicks)) - ((int64_t) (LastKeyPressTick))) & 512) < 256)
            {
                urender_DrawLineOnScreen(left + cursorX, top + Padding, left + cursorX, (top + ClHeight) - Padding, uutils_Max(2, fpcrtl_round((UIScaleValue * ChatScaleValue) * 2.0)), 0x00, 0xff, 0xff, 0xff);
            }
        }
        else
        {
            selRect.y = top + Padding;
            selRect.h = ClHeight - (2 * Padding);
            if(selectionDx < 0)
            {
                selRect.x = (left + cursorX) + selectionDx;
                selRect.w = -selectionDx;
            }
            else
            {
                selRect.x = left + cursorX;
                selRect.w = selectionDx;
            }
            urender_DrawRect(selRect, 0xff, 0xff, 0xff, 0x40, true);
        }
        left -= InputLinePrefix.Width;
        if((fpcrtl_Length(InputStr.s) > 0) && ((cursorPos == 1) || (cursorPos == 2)))
        {
            c = InputStr.s.s[1];
            if(uchat_charIsForHogSpeech(c))
            {
                SpeechHogNumber = 0;
                if(fpcrtl_Length(InputStr.s) > 1)
                {
                    c = InputStr.s.s[2];
                    if((c > 0x30) && (c < 0x39))
                    {
                        SpeechHogNumber = ((Byte)c) - 48;
                    }
                }
                if(SpeechHogNumber == 0)
                {
                    if(!CurrentTeam->ExtDriven && !CurrentHedgehog->Unplaced)
                    {
                        SpeechHogNumber = CurrentTeam->CurrHedgehog + 1;
                    }
                    else
                    {
                        SpeechHogNumber = 1;
                    }
                }
            }
        }
        else
        {
            SpeechHogNumber = -1;
        }
    }
    else
    {
        SpeechHogNumber = -1;
    }
    if((!ChatHidden || showAll) && (UIDisplay != uiNone))
    {
        if(missedCount != 0)
        {
            {i = 0;
             LongInt i__end__ = missedCount - 1;
             if (i <= i__end__) do {
                                       uchat_AddChatString(MStrs[i]);
                                   } while(i++ != i__end__);}
            missedCount = 0;
        }
        i = lastStr;
        cnt = 0;
        t = 1;
        while((((t < MaxStrPartial) && (Strs[i].Time > RealTicks)) || ((t <= (MaxStrIndex + 1)) && showAll)) && (Strs[i].Tex != NULL))
        {
            top = top - ClHeight;
            if(top > 0)
            {
                urender_DrawTexture_3(left, top, Strs[i].Tex);
            }
            if(i == 0)
            {
                i = MaxStrIndex;
            }
            else
            {
                --i;
            }
            ++cnt;
            ++t;
        }
        visibleCount = cnt;
    }
};
void uchat_SendHogSpeech(string255 s)
{
    uio_SendIPC(_strprepend(0x68, s));
    ucommands_ParseCommand_2(_strconcat(__str3, s), true);
};
void uchat_SendConsoleCommand(string255 s)
{
    fpcrtl_Delete(s, 1, 1);
    uio_SendIPC(_strprepend(0x7e, s));
};
void uchat_AcceptChatString(string255 s)
{
    TWave i;
    TChatCmd j;
    LongInt c;
    LongInt t;
    Byte x;
    if(_strncompare(s, LocalStrs[localLastStr]))
    {
        localLastStr = (localLastStr + 1) % MaxStrIndex;
        LocalStrs[localLastStr] = s;
    }
    t = LocalTeam;
    x = 0;
    if((s.s[1] == 0x22) && (s.s[fpcrtl_Length(s)] == 0x22))
    {
        x = 1;
    }
    else
    {
        if((s.s[1] == 0x27) && (s.s[fpcrtl_Length(s)] == 0x27))
        {
            x = 2;
        }
        else
        {
            if((s.s[1] == 0x2d) && (s.s[fpcrtl_Length(s)] == 0x2d))
            {
                x = 3;
            }
        }
    }
    if(!CurrentTeam->ExtDriven && (x != 0))
    {
        {c = 0;
         LongInt c__end__ = ((int)(TeamsCount) - 1);
         if (c <= c__end__) do {
                                   if(TeamsArray[c] == CurrentTeam)
                                   {
                                       t = c;
                                   }
                               } while(c++ != c__end__);}
    }
    if(x != 0)
    {
        if(t == -1)
        {
            ucommands_ParseCommand_2(_strconcat(__str4, fpcrtl_copy(s, 2, fpcrtl_Length(s) - 2)), true);
        }
        else
        {
            uchat_SendHogSpeech(_strconcat(_chrconcat(((char)x), ((char)t)), fpcrtl_copy(s, 2, fpcrtl_Length(s) - 2)));
        }
        return;
    }
    if(s.s[1] == 0x2f)
    {
        if(fpcrtl_Length(s) <= 1)
        {
            uchat_AddChatString(_strprepend(0x0, fpcrtl_astr2str(trcmd[sidCmdUnknown])));
            return;
        }
        if((_strcompare(fpcrtl_copy(s, 2, 2), __str5)) && (fpcrtl_Length(s) == 3))
        {
            return;
        }
        if((((_strcompare(fpcrtl_copy(s, 2, 3), __str6)) || (_strcompare(fpcrtl_copy(s, 2, 3), __str7))) || (_strcompare(fpcrtl_copy(s, 2, 3), __str8))) && (fpcrtl_Length(s) == 4))
        {
            return;
        }
        if(((_strcompare(fpcrtl_copy(s, 2, 4), __str9)) || (_strcompare(fpcrtl_copy(s, 2, 4), __str10))) && (fpcrtl_Length(s) == 5))
        {
            return;
        }
        if(_strcompare(fpcrtl_copy(s, 2, 4), __str11))
        {
            if(CurrentTeam->ExtDriven)
            {
                ucommands_ParseCommand_2(_strconcat(__str4, fpcrtl_copy(s, 6, fpcrtl_Length(s) - 5)), true);
            }
            else
            {
                uchat_SendHogSpeech(_strprepend(0x4, fpcrtl_copy(s, 6, fpcrtl_Length(s) - 5)));
            }
            return;
        }
        if(_strcompare(fpcrtl_copy(s, 2, 4), __str12))
        {
            if(CurrentTeam->ExtDriven)
            {
                ucommands_ParseCommand_2(_strconcat(__str4, fpcrtl_copy(s, 6, fpcrtl_Length(s) - 5)), true);
            }
            else
            {
                uchat_SendHogSpeech(_strprepend(0x5, fpcrtl_copy(s, 6, fpcrtl_Length(s) - 5)));
            }
            return;
        }
        if(_strcompare(fpcrtl_copy(s, 2, 4), __str13))
        {
            if(CurrentTeam->ExtDriven)
            {
                ucommands_ParseCommand_2(_strconcat(__str4, fpcrtl_copy(s, 6, fpcrtl_Length(s) - 5)), true);
            }
            else
            {
                uchat_SendHogSpeech(_strprepend(0x6, fpcrtl_copy(s, 6, fpcrtl_Length(s) - 5)));
            }
            return;
        }
        if((_strcompare(fpcrtl_copy(s, 2, 5), __str14)) || (_strcompare(fpcrtl_copy(s, 2, 5), __str15)))
        {
            if(fpcrtl_Length(s) > 6)
            {
                ucommands_ParseCommand_2(_strconcat(__str15, fpcrtl_copy(s, 7, fpcrtl_Length(s) - 6)), true);
            }
            return;
        }
        if(_strcompare(fpcrtl_copy(s, 2, 3), __str16))
        {
            ucommands_ParseCommand_2(_strconcat(__str4, s), true);
            return;
        }
        if(_strcompare(fpcrtl_copy(s, 2, 10), __str17))
        {
            ChatHidden = !ChatHidden;
            if(ChatHidden)
            {
                showAll = false;
            }
            return;
        }
        if(_strcompare(fpcrtl_copy(s, 2, 3), __str18))
        {
            ucommands_ParseCommand_2(s, true);
            return;
        }
        if(_strcompare(fpcrtl_copy(s, 2, 3), __str19))
        {
            ucommands_ParseCommand_2(s, true);
            return;
        }
        if(_strcompare(fpcrtl_copy(s, 2, 7), __str20))
        {
            cViewLimitsDebug = !cViewLimitsDebug;
            urender_UpdateViewLimits();
            return;
        }
        if(_strcompare(fpcrtl_copy(s, 2, 3), __str21))
        {
            LuaCmdUsed = true;
            uutils_AddFileLog(__str22);
            if(GameType != gmtNet)
            {
                liveLua = !liveLua;
                if(liveLua)
                {
                    uutils_AddFileLog(__str23);
                    uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trmsg[sidLuaParsingOn])));
                }
                else
                {
                    uutils_AddFileLog(__str24);
                    uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trmsg[sidLuaParsingOff])));
                }
                uchat_UpdateInputLinePrefix_0();
            }
            else
            {
                uchat_AddChatString(_strprepend(0x5, fpcrtl_astr2str(trmsg[sidLuaParsingDenied])));
            }
            return;
        }
        if(_strcompare(fpcrtl_copy(s, 2, 11), __str25))
        {
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdHeaderTaunts])));
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdSpeech])));
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdThink])));
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdYell])));
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdSpeechNumberHint])));
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdHsa])));
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdHta])));
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdHya])));
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdHappy])));
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdWave])));
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdHurrah])));
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdShrug])));
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdSad])));
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdIlovelotsoflemonade])));
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdJuggle])));
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdRollup])));
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdBubble])));
            return;
        }
        if(_strcompare(fpcrtl_copy(s, 2, 9), __str26))
        {
            if(GameType == gmtNet)
            {
                uchat_SendConsoleCommand(__str27);
            }
            else
            {
                uchat_AddChatString(_strprepend(0x0, fpcrtl_astr2str(trcmd[sidCmdHelpRoomFail])));
            }
            return;
        }
        if(_strcompare(fpcrtl_copy(s, 2, 4), __str28))
        {
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdHeaderBasic])));
            if(GameType == gmtNet)
            {
                uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdPauseNet])));
            }
            else
            {
                uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdPause])));
            }
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdFullscreen])));
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdQuit])));
            if(GameType != gmtNet)
            {
                uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidLua])));
            }
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdTeam])));
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdMe])));
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdTogglechat])));
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdHistory])));
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdHelp])));
            uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdHelpTaunts])));
            if(GameType == gmtNet)
            {
                uchat_AddChatString(_strprepend(0x3, fpcrtl_astr2str(trcmd[sidCmdHelpRoom])));
            }
            return;
        }
        {i = 0;
         TWave i__end__ = 8;
         if (i <= i__end__) do {
                                   if(_strcompare(s, Wavez[i].cmd))
                                   {
                                       if(!CurrentTeam->ExtDriven && (CurrentTeam->Hedgehogs[0].BotLevel == 0))
                                       {
                                           ucommands_ParseCommand_2(_strappend(__str29, ((char)i)), true);
                                       }
                                       return;
                                   }
                               } while(i++ != i__end__);}
        {j = 0;
         TChatCmd j__end__ = 3;
         if (j <= j__end__) do {
                                   if(_strcompare(s, ChatCommandz[j].ChatCmd))
                                   {
                                       ucommands_ParseCommand_2(ChatCommandz[j].ProcedureCallChatCmd, true);
                                       return;
                                   }
                               } while(j++ != j__end__);}
        if(GameType == gmtNet)
        {
            uchat_SendConsoleCommand(s);
        }
        else
        {
            uchat_AddChatString(_strprepend(0x0, fpcrtl_astr2str(trcmd[sidCmdUnknown])));
        }
    }
    else
    {
        if(liveLua)
        {
            uscript_LuaParseString(s);
        }
        else
        {
            ucommands_ParseCommand_2(_strconcat(__str4, s), true);
        }
    }
};
void uchat_CleanupInput()
{
    uinputhandler_FreezeEnterKey();
    history = 0;
    SDL_StopTextInput();
    isInChatMode = false;
    uinputhandler_ResetKbd();
};
void uchat_OpenChat(string255 s)
{
    Integer i;
    if(GameState == gsConfirm)
    {
        ucommands_ParseCommand_2(__str30, true);
    }
    isInChatMode = true;
    SDL_StopTextInput();
    SDL_StartTextInput();
    {i = 1;
     Integer i__end__ = 2;
     if (i <= i__end__) do {
                               SDL_PumpEvents();
                               SDL_FlushEvent(SDL_TEXTINPUT);
                           } while(i++ != i__end__);}
    if(fpcrtl_Length(s) == 0)
    {
        uchat_SetLine(&(InputStr), __str0, true);
    }
    else
    {
        uchat_SetLine(&(InputStr), s, true);
        cursorPos = fpcrtl_Length(s);
        uchat_UpdateCursorCoords_0();
    }
};
void uchat_CloseChat()
{
    oldInput = InputStr.s;
    uchat_SetLine(&(InputStr), __str0, true);
    uchat_ResetCursor();
    uchat_CleanupInput();
};
void uchat_RestoreChat()
{
    if(fpcrtl_Length(oldInput) > 0)
    {
        uchat_OpenChat(oldInput);
    }
    oldInput = __str0;
};
void uchat_DelBytesFromInputStrBack(Integer endIdx,Byte count)
{
    Integer startIdx;
    if(count == 0)
    {
        return;
    }
    startIdx = endIdx - (count - 1);
    fpcrtl_Delete(InputStr.s, startIdx, count);
    uchat_SetLine(&(InputStr), InputStr.s, true);
};
void uchat_MoveCursorToPreviousChar()
{
    if(cursorPos > 0)
    {
        do {
               --cursorPos;
           } while(!((cursorPos == 0) || uchat_IsFirstCharByte(InputStr.s.s[cursorPos + 1])));
    }
};
void uchat_MoveCursorToNextChar()
{
    Integer len;
    len = fpcrtl_Length(InputStr.s);
    if(cursorPos < len)
    {
        do {
               ++cursorPos;
           } while(!((cursorPos == len) || uchat_IsFirstCharByte(InputStr.s.s[cursorPos + 1])));
    }
};
void uchat_DeleteLastUTF8CharFromStr(string255 (*s))
{
    Byte l;
    l = fpcrtl_Length((*s));
    while((l > 1) && !uchat_IsFirstCharByte((*s).s[l]))
    {
        --l;
    }
    if(l > 0)
    {
        --l;
    }
    (*s).s[0] = ((char)l);
};
void uchat_DeleteSelected()
{
    if((selectedPos >= 0) && (cursorPos != selectedPos))
    {
        uchat_DelBytesFromInputStrBack(uutils_Max(cursorPos, selectedPos), fpcrtl_abs(selectedPos - cursorPos));
        cursorPos = uutils_Min(cursorPos, selectedPos);
    }
    uchat_ResetSelection();
    uchat_UpdateCursorCoords_0();
};
void uchat_HandleSelection(boolean enabled)
{
    if(enabled)
    {
        if(selectedPos < 0)
        {
            selectedPos = cursorPos;
        }
    }
    else
    {
        uchat_ResetSelection();
    }
};
typedef enum {none = 0x0,
              wspace = 0x1,
              numalpha = 0x2,
              special = 0x3} TCharSkip;
TCharSkip uchat_GetInputCharSkipClass(LongInt index)
{
    TCharSkip getinputcharskipclass_result;
    char c;
    c = InputStr.s.s[index];
    if(c > 0x7f)
    {
        return numalpha;
    }
    if((c < 0x21) || (c == 0x7f))
    {
        return wspace;
    }
    if(c < 0x30)
    {
        return special;
    }
    if(c < 0x3a)
    {
        return numalpha;
    }
    if(c > 0x60)
    {
        c = ((char)((Byte)c) - 32);
    }
    if((c > 0x40) && (c < 0x5a))
    {
        return numalpha;
    }
    return special;
    return getinputcharskipclass_result;
};
void uchat_SkipInputChars(TCharSkip skip,boolean backwards)
{
    if(backwards)
    {
        while((skip == wspace) && (cursorPos > 0))
        {
            skip = uchat_GetInputCharSkipClass(cursorPos);
            if(skip == wspace)
            {
                uchat_MoveCursorToPreviousChar();
            }
        }
        while((cursorPos > 0) && (uchat_GetInputCharSkipClass(cursorPos) == skip))
        {
            uchat_MoveCursorToPreviousChar();
        }
    }
    else
    {
        while(cursorPos < fpcrtl_Length(InputStr.s))
        {
            uchat_MoveCursorToNextChar();
            if(uchat_GetInputCharSkipClass(cursorPos) != skip)
            {
                uchat_MoveCursorToPreviousChar();
                break;
            }
        }
        while(cursorPos < fpcrtl_Length(InputStr.s))
        {
            uchat_MoveCursorToNextChar();
            if(uchat_GetInputCharSkipClass(cursorPos) != wspace)
            {
                uchat_MoveCursorToPreviousChar();
                break;
            }
        }
    }
};
void uchat_CopyToClipboard(string255 (*newContent))
{
    SDL_SetClipboardText(uutils_Str2PChar((*newContent)));
};
void uchat_CopySelectionToClipboard()
{
    string255 selection;
    if(selectedPos >= 0)
    {
        selection = fpcrtl_copy(InputStr.s, uutils_Min(cursorPos, selectedPos) + 1, fpcrtl_abs(cursorPos - selectedPos));
        uchat_CopyToClipboard(&(selection));
    }
};
void uchat_InsertIntoInputStr(string255 s)
{
    Integer limit;
    limit = uutils_Max(cursorPos, MaxInputStrLen - fpcrtl_Length(s));
    while(fpcrtl_Length(InputStr.s) > limit)
    {
        uchat_DeleteLastUTF8CharFromStr(&(InputStr.s));
    }
    limit = uutils_Max(0, MaxInputStrLen - cursorPos);
    if(limit == 0)
    {
        s = __str0;
    }
    else
    {
        while(fpcrtl_Length(s) > limit)
        {
            uchat_DeleteLastUTF8CharFromStr(&(s));
        }
    }
    if(fpcrtl_Length(s) > 0)
    {
        fpcrtl_Insert(s, InputStr.s, cursorPos + 1);
        if(fpcrtl_Length(InputStr.s) > MaxInputStrLen)
        {
            InputStr.s.s[0] = ((char)MaxInputStrLen);
        }
        uchat_SetLine(&(InputStr), InputStr.s, true);
        cursorPos += fpcrtl_Length(s);
        uchat_UpdateCursorCoords_0();
    }
};
void uchat_PasteFromClipboard()
{
    PChar clip;
    if(SDL_HasClipboardText())
    {
        clip = SDL_GetClipboardText();
        if(clip != NULL)
        {
            uchat_InsertIntoInputStr(fpcrtl_pchar2str(clip));
            SDL_free(((pointer)clip));
        }
    }
};
void uchat_KeyPressChat(TSDL_Keysym keysym)
{
    enum{nonStateMask = ~(KMOD_NUM | KMOD_CAPS)};
    Integer i;
    Integer index;
    boolean selMode;
    boolean ctrl;
    boolean ctrlonly;
    TCharSkip skip;
    TSDL_Scancode Scancode;
    Word Modifier;
    Scancode = keysym.scancode;
    Modifier = keysym.modifier;
    LastKeyPressTick = RealTicks;
    selMode = (Modifier & (KMOD_LSHIFT | KMOD_RSHIFT)) != 0;
    ctrl = (Modifier & (KMOD_LCTRL | KMOD_RCTRL)) != 0;
    ctrlonly = ctrl && (((Modifier & nonStateMask) & ~(KMOD_LCTRL | KMOD_RCTRL)) == 0);
    skip = none;
    switch(Scancode)
    {case SDL_SCANCODE_BACKSPACE:{
                                     if(selectedPos < 0)
                                     {
                                         uchat_HandleSelection(true);
                                         if(ctrl)
                                         {
                                             uchat_SkipInputChars(uchat_GetInputCharSkipClass(cursorPos), true);
                                         }
                                         else
                                         {
                                             uchat_MoveCursorToPreviousChar();
                                         }
                                     }
                                     uchat_DeleteSelected();
                                     uchat_UpdateCursorCoords_0();
                                 }
                                 break;
     case SDL_SCANCODE_DELETE:{
                                  if(selectedPos < 0)
                                  {
                                      uchat_HandleSelection(true);
                                      if(ctrl)
                                      {
                                          uchat_SkipInputChars(uchat_GetInputCharSkipClass(cursorPos), false);
                                      }
                                      else
                                      {
                                          uchat_MoveCursorToNextChar();
                                      }
                                  }
                                  uchat_DeleteSelected();
                                  uchat_UpdateCursorCoords_0();
                              }
                              break;
     case SDL_SCANCODE_ESCAPE:{
                                  if(fpcrtl_Length(InputStr.s) > 0)
                                  {
                                      uchat_SetLine(&(InputStr), __str0, true);
                                      uchat_ResetCursor();
                                  }
                                  else
                                  {
                                      uchat_CleanupInput();
                                  }
                                  oldInput = __str0;
                              }
                              break;
     case SDL_SCANCODE_RETURN:
     case SDL_SCANCODE_KP_ENTER:{
                                    if(fpcrtl_Length(InputStr.s) > 0)
                                    {
                                        uchat_AcceptChatString(InputStr.s);
                                        uchat_SetLine(&(InputStr), __str0, false);
                                        uchat_ResetCursor();
                                    }
                                    uchat_CleanupInput();
                                }
                                break;
     case SDL_SCANCODE_UP:
     case SDL_SCANCODE_DOWN:{
                                if((Scancode == SDL_SCANCODE_UP) && (history < localLastStr))
                                {
                                    ++history;
                                }
                                if((Scancode == SDL_SCANCODE_DOWN) && (history > 0))
                                {
                                    --history;
                                }
                                index = (localLastStr - history) + 1;
                                if(index > localLastStr)
                                {
                                    uchat_SetLine(&(InputStr), __str0, true);
                                }
                                else
                                {
                                    uchat_SetLine(&(InputStr), LocalStrs[index], true);
                                }
                                cursorPos = fpcrtl_Length(InputStr.s);
                                uchat_ResetSelection();
                                uchat_UpdateCursorCoords_0();
                            }
                            break;
     case SDL_SCANCODE_HOME:{
                                if(cursorPos > 0)
                                {
                                    uchat_HandleSelection(selMode);
                                    cursorPos = 0;
                                }
                                else
                                {
                                    if(!selMode)
                                    {
                                        uchat_ResetSelection();
                                    }
                                }
                                uchat_UpdateCursorCoords_0();
                            }
                            break;
     case SDL_SCANCODE_END:{
                               i = fpcrtl_Length(InputStr.s);
                               if(cursorPos < i)
                               {
                                   uchat_HandleSelection(selMode);
                                   cursorPos = i;
                               }
                               else
                               {
                                   if(!selMode)
                                   {
                                       uchat_ResetSelection();
                                   }
                               }
                               uchat_UpdateCursorCoords_0();
                           }
                           break;
     case SDL_SCANCODE_LEFT:{
                                if(cursorPos > 0)
                                {
                                    if(ctrl)
                                    {
                                        skip = uchat_GetInputCharSkipClass(cursorPos);
                                    }
                                    if(selMode || (selectedPos < 0))
                                    {
                                        uchat_HandleSelection(selMode);
                                        uchat_MoveCursorToPreviousChar();
                                    }
                                    else
                                    {
                                        cursorPos = uutils_Min(cursorPos, selectedPos);
                                        uchat_ResetSelection();
                                    }
                                    if(ctrl)
                                    {
                                        uchat_SkipInputChars(skip, true);
                                    }
                                }
                                else
                                {
                                    if(!selMode)
                                    {
                                        uchat_ResetSelection();
                                    }
                                }
                                uchat_UpdateCursorCoords_0();
                            }
                            break;
     case SDL_SCANCODE_RIGHT:{
                                 if(cursorPos < fpcrtl_Length(InputStr.s))
                                 {
                                     if(selMode || (selectedPos < 0))
                                     {
                                         uchat_HandleSelection(selMode);
                                         uchat_MoveCursorToNextChar();
                                     }
                                     else
                                     {
                                         cursorPos = uutils_Max(cursorPos, selectedPos);
                                         uchat_ResetSelection();
                                     }
                                     if(ctrl)
                                     {
                                         uchat_SkipInputChars(uchat_GetInputCharSkipClass(cursorPos), false);
                                     }
                                 }
                                 else
                                 {
                                     if(!selMode)
                                     {
                                         uchat_ResetSelection();
                                     }
                                 }
                                 uchat_UpdateCursorCoords_0();
                             }
                             break;
     case SDL_SCANCODE_PAGEUP:
     case SDL_SCANCODE_PAGEDOWN:{
                                }
                                break;
     case SDL_SCANCODE_A:{
                             if(ctrlonly)
                             {
                                 uchat_ResetSelection();
                                 cursorPos = 0;
                                 uchat_HandleSelection(true);
                                 cursorPos = fpcrtl_Length(InputStr.s);
                                 uchat_UpdateCursorCoords_0();
                             }
                         }
                         break;
     case SDL_SCANCODE_C:{
                             if(ctrlonly)
                             {
                                 uchat_CopySelectionToClipboard();
                             }
                         }
                         break;
     case SDL_SCANCODE_V:{
                             if(ctrlonly)
                             {
                                 uchat_DeleteSelected();
                                 uchat_PasteFromClipboard();
                             }
                         }
                         break;
     case SDL_SCANCODE_X:{
                             if(ctrlonly)
                             {
                                 uchat_CopySelectionToClipboard();
                                 uchat_DeleteSelected();
                             }
                         }
                         break;
     case SDL_SCANCODE_KP_PLUS:
     case SDL_SCANCODE_EQUALS:{
                                  if(ctrl)
                                  {
                                      uchat_ChatSizeInc(selMode);
                                      SkipNextInput = true;
                                  }
                              }
                              break;
     case SDL_SCANCODE_KP_MINUS:
     case SDL_SCANCODE_MINUS:{
                                 if(ctrl)
                                 {
                                     uchat_ChatSizeDec(selMode);
                                     SkipNextInput = true;
                                 }
                             }
                             break;
     case SDL_SCANCODE_KP_0:
     case SDL_SCANCODE_0:{
                             if(ctrl)
                             {
                                 uchat_chatSizeReset();
                                 SkipNextInput = true;
                             }
                         }
                         break;
     default: break;}
};
void uchat_TextInput(TSDL_TextInputEvent (*event))
{
    string255 s;
    Byte l;
    Integer isl;
    if(SkipNextInput)
    {
        SkipNextInput = false;
        return;
    }
    uchat_DeleteSelected();
    s = __str0;
    l = 0;
    while((*event).text[l] != 0x0)
    {
        if(fpcrtl_Length(s) < 255)
        {
            s.s[l + 1] = (*event).text[l];
            ++l;
        }
    }
    if(l > 0)
    {
        isl = fpcrtl_Length(InputStr.s);
        if((((((l == 1) && (isl >= 2)) && (cursorPos == (isl - 1))) && uchat_charIsForHogSpeech(s.s[1])) && (s.s[1] == InputStr.s.s[1])) && (s.s[1] == InputStr.s.s[isl]))
        {
            uchat_MoveCursorToNextChar();
            uchat_UpdateCursorCoords_0();
        }
        else
        {
            if((isl + l) > MaxInputStrLen)
            {
                return;
            }
            s.s[0] = ((char)l);
            uchat_InsertIntoInputStr(s);
            if(((l == 1) && (fpcrtl_Length(InputStr.s) == 1)) && uchat_charIsForHogSpeech(s.s[1]))
            {
                uchat_InsertIntoInputStr(s);
                uchat_MoveCursorToPreviousChar();
                uchat_UpdateCursorCoords_0();
            }
        }
    }
};
void uchat_chChatMessage(string255 (*s))
{
    uchat_AddChatString((*s));
};
void uchat_chSay(string255 (*s))
{
    uio_SendIPC(_strprepend(0x73, (*s)));
    if(_strcompare(fpcrtl_copy((*s), 1, 4), __str31))
    {
        (*s) = _strconcat(_strappend(_strconcat(_strprepend(0x2, __str32), UserNick), 0x20), fpcrtl_copy((*s), 5, fpcrtl_Length((*s)) - 4));
    }
    else
    {
        (*s) = _strprepend(0x1, ulocale_Format_3(fpcrtl_astr2str(trmsg[sidChat]), UserNick, (*s)));
    }
    uchat_AddChatString((*s));
};
void uchat_chTeamSay(string255 (*s))
{
    uio_SendIPC(_strprepend(0x62, (*s)));
    (*s) = _strprepend(0x4, ulocale_Format_3(fpcrtl_astr2str(trmsg[sidChatTeam]), UserNick, (*s)));
    uchat_AddChatString((*s));
};
void uchat_chHistory(string255 (*s))
{
    LongInt i;
    UNUSED ((*s));
    showAll = !showAll;
    visibleCount = 0;
    if(showAll || !ChatHidden)
    {
        {i = 0;
         LongInt i__end__ = MaxStrIndex;
         if (i <= i__end__) do {
                                   if((Strs[i].Tex != NULL) && (showAll || (Strs[i].Time > RealTicks)))
                                   {
                                       ++visibleCount;
                                   }
                               } while(i++ != i__end__);}
    }
};
void uchat_chChat(string255 (*s))
{
    UNUSED ((*s));
    if(fpcrtl_Length((*s)) == 0)
    {
        uchat_OpenChat(__str0);
    }
    else
    {
        uchat_OpenChat(__str33);
    }
};
void uchat_initModule()
{
    ShortInt i;
    ucommands_RegisterVariable_3(__str34, &(uchat_chChatMessage), true);
    ucommands_RegisterVariable_3(__str35, &(uchat_chSay), true);
    ucommands_RegisterVariable_3(__str9, &(uchat_chTeamSay), true);
    ucommands_RegisterVariable_3(__str36, &(uchat_chHistory), true);
    ucommands_RegisterVariable_3(__str37, &(uchat_chChat), true);
    lastStr = 0;
    localLastStr = 0;
    history = 0;
    visibleCount = 0;
    showAll = false;
    ChatReady = false;
    missedCount = 0;
    liveLua = false;
    ChatHidden = false;
    firstDraw = true;
    LastChatScaleValue = 0;
    LastUIScaleValue = 0;
    SkipNextInput = false;
    InputLinePrefix.Tex = NULL;
    uchat_UpdateInputLinePrefix_0();
    InputStr.s = __str0;
    InputStr.Tex = NULL;
    {i = 0;
     ShortInt i__end__ = MaxStrIndex;
     if (i <= i__end__) do {
                               Strs[i].Tex = NULL;
                           } while(i++ != i__end__);}
    LastKeyPressTick = 0;
    uchat_ResetCursor();
    SDL_StopTextInput();
};
void uchat_freeModule()
{
    ShortInt i;
    utextures_FreeAndNilTexture(&(InputLinePrefix.Tex));
    utextures_FreeAndNilTexture(&(InputStr.Tex));
    {i = 0;
     ShortInt i__end__ = MaxStrIndex;
     if (i <= i__end__) do {
                               utextures_FreeAndNilTexture(&(Strs[i].Tex));
                           } while(i++ != i__end__);}
};
