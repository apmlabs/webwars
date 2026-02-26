#include "fpcrtl.h"

#include "hwengine.h"
static const string255 __str43 = STRINIT("Preview sent, disconnect");
static const string255 __str42 = STRINIT("Sending preview...");
static const string255 __str41 = STRINIT("Freeing resources...");
static const string255 __str40 = STRINIT("WASM: skipping freeEverything (soft exit)");
static const string255 __str39 = STRINIT("Some parameters not set (flags = ");
static const string255 __str38 = STRINIT("eproto ");
static const string255 __str37 = STRINIT("[DEBUG] After config: isDeveloperMode=FALSE InitStepsFlags=");
static const string255 __str36 = STRINIT("[DEBUG] After config: isDeveloperMode=TRUE InitStepsFlags=");
static const string255 __str35 = STRINIT("C");
static const string255 __str34 = STRINIT("[DEBUG] Before InitIPC: isDeveloperMode=FALSE InitStepsFlags=");
static const string255 __str33 = STRINIT("[DEBUG] Before InitIPC: isDeveloperMode=TRUE InitStepsFlags=");
static const string255 __str32 = STRINIT("");
static const string255 __str31 = STRINIT("script ");
static const string255 __str30 = STRINIT("/settings.ini");
static const string255 __str29 = STRINIT(".txt");
static const string255 __str28 = STRINIT("en");
static const string255 __str27 = STRINIT("en.txt");
static const string255 __str26 = STRINIT("/en.txt");
static const string255 __str25 = STRINIT("fullscr 0");
static const string255 __str24 = STRINIT("fullscr 1");
static const string255 __str23 = STRINIT("TTF_Init");
static const string255 __str22 = STRINIT("Init SDL_ttf... ");
static const string255 __str21 = STRINIT("SDL_Init");
static const string255 __str20 = STRINIT("Init SDL... ");
static const string255 __str19 = STRINIT(": ");
static const string255 __str18 = STRINIT("UserPrefix: \"");
static const string255 __str17 = STRINIT("Prefix: \"");
static const string255 __str16 = STRINIT(") with protocol #");
static const string255 __str15 = STRINIT(" (");
static const string255 __str14 = STRINIT("-r");
static const string255 __str13 = STRINIT("Hedgewars engine ");
static const string255 __str12 = STRINIT("Generated using pas2c");
static const string255 __str11 = STRINIT(" (maximized)");
static const string255 __str10 = STRINIT(" x ");
static const string255 __str9 = STRINIT("window resize: ");
static const string255 __str8 = STRINIT("fullscr ");
static const string255 __str7 = STRINIT("screen capture failed (lack of memory or write permissions)");
static const string255 __str6 = STRINIT("Screenshot failed.");
static const string255 __str5 = STRINIT("Screenshot saved: ");
static const string255 __str4 = STRINIT("/Screenshots/hw_");
static const string255 __str3 = STRINIT("/Screenshots/mapdump_");
static const string255 __str2 = STRINIT("onGameStart");
static const string255 __str1 = STRINIT("sendlanddigest");
static const string255 __str0 = STRINIT("Underwater");
boolean hwengine_DoTimer(LongInt Lag)
{
    boolean dotimer_result;
    string255 s;
    LongWord t;
    dotimer_result = false;
    RealTicks += Lag;
    switch(GameState)
    {case gsLandGen:{
                        uland_GenMap();
                        ulandtexture_SetLandTexture();
                        ulandtexture_UpdateLandTexture(0, LAND_WIDTH, 0, LAND_HEIGHT, false);
                        uailandmarks_setAILandMarks();
                        GameState = gsStart;
                    }
                    break;
     case gsStart:{
                      uinputhandler_SetDefaultBinds();
                      if(hasBorder)
                      {
                          uammos_DisableSomeWeapons();
                      }
                      if((WorldEdge != weSea) || (_strncompare(Theme, __str0)))
                      {
                          uvisualgears_AddClouds();
                      }
                      uvisualgears_AddFlakes();
                      urandom_SetRandomSeed(cSeed, false);
                      ustore_StoreLoad(false);
                      ucommands_ParseCommand_2(__str1, true);
                      if(!allOK)
                      {
                          return dotimer_result;
                      }
                      ugears_AssignHHCoords();
                      ugears_AddMiscGears();
                      uworld_InitWorld();
                      uinputhandler_ResetKbd();
                      if(GameType == gmtSave)
                      {
                          usound_SetSound(false);
                      }
                      ustore_FinishProgress();
                      usound_PlayMusic();
                      ustore_InitZoom(zoom);
                      uscript_ScriptCall_1(__str2);
                      ugears_RandomizeHHAnim();
                      {t = 0;
                       LongWord t__end__ = ((int)(TeamsCount) - 1);
                       if (t <= t__end__) do {
                                                 {
                                                     MaxTeamHealth = (*TeamsArray[t]).TeamHealth;
                                                 }
                                             } while(t++ != t__end__);}
                      uteams_RecountAllTeamsHealth();
                      GameState = gsGame;
                  }
                  break;
     case gsConfirm:
     case gsGame:{
                     if(flagMakeCapture && (ScreenFade == sfFromWhite))
                     {
                         ScreenFade = sfNone;
                     }
                     if(!cOnlyStats)
                     {
                         uworld_DrawWorld(Lag);
                     }
                     ugame_DoGameTick(Lag);
                     if(!cOnlyStats)
                     {
                         uvisualgears_ProcessVisualGears(Lag);
                     }
                 }
                 break;
     case gsExit:{
                     dotimer_result = true;
                 }
                 break;
     case gsSuspend:return false;
                    break;
     default: break;}
    if(!cOnlyStats)
    {
        ustore_SwapBuffers();
    }
    if(flagMakeCapture)
    {
        flagMakeCapture = false;
        if(flagDumpLand)
        {
            s = __str3;
        }
        else
        {
            s = __str4;
        }
        s = _strconcat(s, uutils_IntToStr(GameTicks));
        usound_PlaySound_1(sndShutter);
        ScreenFade = sfFromWhite;
        ScreenFadeValue = sfMax;
        ScreenFadeSpeed = 5;
        if((!flagDumpLand && umisc_MakeScreenshot(s, 1, 0)) || ((flagDumpLand && umisc_MakeScreenshot(s, 1, 1)) && (((cReducedQuality & rqBlurryLand) != 0) || umisc_MakeScreenshot(s, 1, 2))))
        {
            uconsole_WriteLnToConsole(_strconcat(__str5, s));
        }
        else
        {
            uconsole_WriteLnToConsole(__str6);
            uchat_AddChatString(_strprepend(0x5, __str7));
        }
    }
    return dotimer_result;
};
void hwengine_MainLoop()
{
    TSDL_Event event;
    LongWord PrevTime;
    LongWord CurrTime;
    boolean isTerminated;
    TGameState previousGameState;
    boolean wheelEvent;
    previousGameState = gsStart;
    isTerminated = false;
    PrevTime = SDL_GetTicks();
    while(!isTerminated && allOK)
    {
        wheelEvent = false;
        SDL_PumpEvents();
        while(SDL_PeepEvents(&(event), 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT) > 0)
        {
            switch(event.type_)
            {case SDL_KEYDOWN:if(isInChatMode)
                              {
                                  uchat_KeyPressChat(event.key.keysym);
                              }
                              else
                              {
                                  if(GameState >= gsGame)
                                  {
                                      uinputhandler_ProcessKey_1(event.key);
                                  }
                              }
                              break;
             case SDL_KEYUP:if(!isInChatMode && (GameState >= gsGame))
                            {
                                uinputhandler_ProcessKey_1(event.key);
                            }
                            break;
             case SDL_TEXTINPUT:if(isInChatMode)
                                {
                                    uchat_TextInput(&(event.text));
                                }
                                break;
             case SDL_WINDOWEVENT:{
                                      switch(event.window.event)
                                      {case SDL_WINDOWEVENT_FOCUS_GAINED:{
                                                                             cHasFocus = true;
                                                                             uworld_onFocusStateChanged();
                                                                         }
                                                                         break;
                                       case SDL_WINDOWEVENT_FOCUS_LOST:{
                                                                           cHasFocus = false;
                                                                           uworld_onFocusStateChanged();
                                                                       }
                                                                       break;
                                       case SDL_WINDOWEVENT_RESTORED:{
                                                                         if(GameState == gsSuspend)
                                                                         {
                                                                             GameState = previousGameState;
                                                                         }
                                                                         cWindowedMaximized = false;
                                                                     }
                                                                     break;
                                       case SDL_WINDOWEVENT_MAXIMIZED:cWindowedMaximized = true;
                                                                      break;
                                       case SDL_WINDOWEVENT_RESIZED:{
                                                                        cNewScreenWidth = uutils_Max(2 * (event.window.data1 / 2), cMinScreenWidth);
                                                                        cNewScreenHeight = uutils_Max(2 * (event.window.data2 / 2), cMinScreenHeight);
                                                                        cScreenResizeDelay = RealTicks + 500;
                                                                    }
                                                                    break;
                                       default: break;}
                                  }
                                  break;
             case SDL_FINGERMOTION:utouch_onTouchMotion(event.tfinger.x, event.tfinger.y, event.tfinger.dx, event.tfinger.dy, event.tfinger.fingerId);
                                   break;
             case SDL_FINGERDOWN:utouch_onTouchDown(event.tfinger.x, event.tfinger.y, event.tfinger.fingerId);
                                 break;
             case SDL_FINGERUP:utouch_onTouchUp(event.tfinger.x, event.tfinger.y, event.tfinger.fingerId);
                               break;
             case SDL_JOYAXISMOTION:uinputhandler_ControllerAxisEvent(event.jaxis.which, event.jaxis.axis, event.jaxis.value);
                                    break;
             case SDL_JOYHATMOTION:uinputhandler_ControllerHatEvent(event.jhat.which, event.jhat.hat, event.jhat.value);
                                   break;
             case SDL_JOYBUTTONDOWN:uinputhandler_ControllerButtonEvent(event.jbutton.which, event.jbutton.button, true);
                                    break;
             case SDL_JOYBUTTONUP:uinputhandler_ControllerButtonEvent(event.jbutton.which, event.jbutton.button, false);
                                  break;
             case SDL_QUITEV:isTerminated = true;
                             break;
             default: break;}
        }
        if(!wheelEvent)
        {
            uinputhandler_ResetMouseWheel();
        }
        if((CursorMovementX != 0) || (CursorMovementY != 0))
        {
            ucursor_handlePositionUpdate(CursorMovementX, CursorMovementY);
        }
        if(((cScreenResizeDelay != 0) && (cScreenResizeDelay < RealTicks)) && ((cNewScreenWidth != cScreenWidth) || (cNewScreenHeight != cScreenHeight)))
        {
            cScreenResizeDelay = 0;
            cWindowedWidth = cNewScreenWidth;
            cWindowedHeight = cNewScreenHeight;
            cScreenWidth = cWindowedWidth;
            cScreenHeight = cWindowedHeight;
            ucommands_ParseCommand_2(_strconcat(__str8, uutils_IntToStr(((LongInt)cFullScreen))), true);
            if(cWindowedMaximized)
            {
                uconsole_WriteLnToConsole(_strconcat(_strconcat(_strconcat(_strconcat(__str9, uutils_IntToStr(cScreenWidth)), __str10), uutils_IntToStr(cScreenHeight)), __str11));
            }
            else
            {
                uconsole_WriteLnToConsole(_strconcat(_strconcat(_strconcat(__str9, uutils_IntToStr(cScreenWidth)), __str10), uutils_IntToStr(cScreenHeight)));
            }
            uscript_ScriptOnScreenResize();
            uworld_InitCameraBorders();
            uworld_InitTouchInterface();
            ustore_InitZoom(ZoomValue);
            if(cWindowedMaximized)
            {
                uio_SendIPC(_strappend(_strconcat(_strappend(_strprepend(0x57, uutils_IntToStr(cScreenWidth)), 0x78), uutils_IntToStr(cScreenHeight)), 0x4d));
            }
            else
            {
                uio_SendIPC(_strconcat(_strappend(_strprepend(0x57, uutils_IntToStr(cScreenWidth)), 0x78), uutils_IntToStr(cScreenHeight)));
            }
        }
        CurrTime = SDL_GetTicks();
        if((PrevTime + ((LongWord)cTimerInterval)) <= CurrTime)
        {
            isTerminated = isTerminated || hwengine_DoTimer(((int64_t) (CurrTime)) - ((int64_t) (PrevTime)));
            PrevTime = CurrTime;
        }
        else
        {
            SDL_Delay(1);
        }
        uio_IPCCheckSock();
    }
};
void hwengine_GameRoutine()
{
    string255 s;
    LongInt i;
    uutils_AddFileLog(__str12);
    uconsole_WriteLnToConsole(_strconcat(_strconcat(_strconcat(_strconcat(_strconcat(_strconcat(_strconcat(__str13, cVersionString), __str14), cRevisionString), __str15), cHashString), __str16), uutils_IntToStr(cNetProtoVersion)));
    uutils_AddFileLog(_strappend(_strconcat(__str17, fpcrtl_astr2str(PathPrefix)), 0x22));
    uutils_AddFileLog(_strappend(_strconcat(__str18, fpcrtl_astr2str(UserPathPrefix)), 0x22));
    {i = 0;
     LongInt i__end__ = fpcrtl_ParamCount();
     if (i <= i__end__) do {
                               uutils_AddFileLog(_strconcat(_strconcat(uutils_IntToStr(i), __str19), argparsers_ParamStr(i)));
                           } while(i++ != i__end__);}
    uconsole_WriteToConsole(__str20);
    if(!cOnlyStats)
    {
        udebug_SDLCheck(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE) >= 0, __str21, true);
    }
    uconsole_WriteLnToConsole(msgOK);
    if(!cOnlyStats)
    {
        uconsole_WriteToConsole(__str22);
        udebug_SDLCheck(TTF_Init() != -1, __str23, true);
        uconsole_WriteLnToConsole(msgOK);
    }
    if(!allOK)
    {
        return;
    }
    SDL_ShowCursor(SDL_DISABLE);
    {
        if(cFullScreen)
        {
            ucommands_ParseCommand_2(__str24, true);
        }
        else
        {
            ucommands_ParseCommand_2(__str25, true);
        }
    }
    uinputhandler_ControllerInit();
    uinputhandler_InitKbdKeyTable();
    if(!allOK)
    {
        return;
    }
    ulocale_LoadLocale(_strconcat(cPathz[ptLocale], __str26));
    if(_strncompare(cLanguageFName, __str27))
    {
        if((fpcrtl_Length(cLanguage) > 3) && (_strncompare(fpcrtl_copy(cLanguage, 1, 2), __str28)))
        {
            ulocale_LoadLocale(_strconcat(_strconcat(_strappend(cPathz[ptLocale], 0x2f), fpcrtl_copy(cLanguage, 1, 2)), __str29));
        }
        ulocale_LoadLocale(_strconcat(_strappend(cPathz[ptLocale], 0x2f), cLanguageFName));
    }
    else
    {
        cLanguage = __str28;
    }
    if(!allOK)
    {
        return;
    }
    uconsole_WriteLnToConsole(msgGettingConfig);
    ustore_LoadFonts();
    ustore_AddProgress();
    ustore_LoadDefaultClanColors(_strconcat(cPathz[ptConfig], __str30));
    if(cTestLua)
    {
        ucommands_ParseCommand_2(_strconcat(__str31, cScriptName), true);
    }
    else
    {
        if(_strcompare(recordFileName, __str32))
        {
            if(isDeveloperMode)
            {
                uutils_AddFileLog(_strconcat(__str33, uutils_IntToStr(InitStepsFlags)));
            }
            else
            {
                uutils_AddFileLog(_strconcat(__str34, uutils_IntToStr(InitStepsFlags)));
            }
            uio_InitIPC();
            uio_SendIPCAndWaitReply(__str35);
            if(isDeveloperMode)
            {
                uutils_AddFileLog(_strconcat(__str36, uutils_IntToStr(InitStepsFlags)));
            }
            else
            {
                uutils_AddFileLog(_strconcat(__str37, uutils_IntToStr(InitStepsFlags)));
            }
        }
        else
        {
            uio_LoadRecordFromFile(recordFileName);
        }
    }
    if(!allOK)
    {
        return;
    }
    uscript_ScriptOnGameInit();
    s = _strconcat(__str38, uutils_IntToStr(cNetProtoVersion));
    uio_SendIPCRaw(&(s.s[0]), fpcrtl_Length(s) + 1);
    uteams_InitTeams();
    uammos_AssignStores();
    if(GameType == gmtRecord)
    {
        usound_SetSound(false);
    }
    usound_InitSound();
    isDeveloperMode = false;
    if(udebug_checkFails(InitStepsFlags == cifAllInited, _strappend(_strconcat(__str39, uutils_IntToStr(InitStepsFlags)), 0x29), true))
    {
        return;
    }
    if(!allOK)
    {
        return;
    }
    hwengine_MainLoop();
};
void hwengine_Game()
{
    hwengine_initEverything(true);
    hwengine_GameRoutine();
    uconsole_WriteLnToConsole(__str40);
};
void hwengine_preInitEverything()
{
    allOK = true;
    fpcrtl_randomize();
    uvariables_preInitModule();
    usound_preInitModule();
};
void hwengine_initEverything(boolean complete)
{
    PathPrefix = _strappendA(PathPrefix, 0x0);
    UserPathPrefix = _strappendA(UserPathPrefix, 0x0);
    uphysfslayer_initModule(&(PathPrefix.s[1]), &(UserPathPrefix.s[1]));
    PathPrefix = fpcrtl_copyA(PathPrefix, 1, fpcrtl_LengthA(PathPrefix) - 1);
    UserPathPrefix = fpcrtl_copyA(UserPathPrefix, 1, fpcrtl_LengthA(UserPathPrefix) - 1);
    uutils_initModule(complete);
    uvariables_initModule();
    ucommands_initModule();
    ucommandhandlers_initModule();
    uland_initModule();
    ulandpainted_initModule();
    uio_initModule();
    uscript_initModule();
    if(complete)
    {
        utextures_initModule();
        utouch_initModule();
        uai_initModule();
        uaimisc_initModule();
        uailandmarks_initModule();
        uammos_initModule();
        ucaptions_initModule();
        ustore_initModule();
        uchat_initModule();
        ucollisions_initModule();
        ugears_initModule();
        uinputhandler_initModule();
        umisc_initModule();
        ulandtexture_initModule();
        usound_initModule();
        ustats_initModule();
        urender_initModule();
        uteams_initModule();
        uvisualgears_initModule();
        uvisualgearshandlers_initModule();
        uworld_initModule();
    }
};
void hwengine_freeEverything(boolean complete)
{
    if(complete)
    {
        uconsole_WriteLnToConsole(__str41);
        uai_freeModule();
        uaimisc_freeModule();
        uailandmarks_freeModule();
        ucaptions_freeModule();
        uworld_freeModule();
        uvisualgears_freeModule();
        uteams_freeModule();
        uinputhandler_freeModule();
        ustats_freeModule();
        usound_freeModule();
        umisc_freeModule();
        ulandtexture_freeModule();
        ugears_freeModule();
        ucollisions_freeModule();
        uchat_freeModule();
        uammos_freeModule();
        urender_freeModule();
        ustore_freeModule();
        utouch_freeModule();
        utextures_freeModule();
        SDL_GL_DeleteContext(SDLGLcontext);
        SDL_DestroyWindow(SDLwindow);
        SDL_Quit();
    }
    uio_freeModule();
    uland_freeModule();
    ulandpainted_freeModule();
    ucommandhandlers_freeModule();
    ucommands_freeModule();
    uvariables_freeModule();
    uutils_freeModule();
    uphysfslayer_freeModule();
    uscript_freeModule();
};
void hwengine_GenLandPreview()
{
    TPreviewAlpha Preview;
    hwengine_initEverything(false);
    uio_InitIPC();
    if(allOK)
    {
        uio_IPCWaitPongEvent();
        if(udebug_checkFails(InitStepsFlags == cifRandomize, _strappend(_strconcat(__str39, uutils_IntToStr(InitStepsFlags)), 0x29), true))
        {
            return;
        }
        uscript_ScriptOnPreviewInit();
        uland_GenPreviewAlpha(&(Preview));
        uconsole_WriteLnToConsole(__str42);
        uio_SendIPCRaw(&(Preview), sizeof(Preview));
        uio_SendIPCRaw(&(MaxHedgehogs), sizeof(Byte));
        uconsole_WriteLnToConsole(__str43);
    }
    hwengine_freeEverything(false);
};
LongInt hwengine_RunEngine(LongInt argc,PPChar argv)
{
    LongInt runengine_result;
    operatingsystem_parameter_argc = argc;
    operatingsystem_parameter_argv = argv;
    fpcrtl_init(argc, argv);
    hwengine_preInitEverything();
    argparsers_GetParams();
    if(GameType == gmtLandPreview)
    {
        hwengine_GenLandPreview();
    }
    else
    {
        if((GameType != gmtBadSyntax) && (GameType != gmtSyntaxHelp))
        {
            hwengine_Game();
        }
    }
    if(GameType == gmtBadSyntax)
    {
        return HaltUsageError;
    }
    if(cTestLua)
    {
        uconsole_WriteLnToConsole(errmsgLuaTestTerm);
        return HaltTestUnexpected;
    }
    return HaltNoError;
    return runengine_result;
};
