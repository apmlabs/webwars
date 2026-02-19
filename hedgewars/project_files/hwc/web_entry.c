#include <emscripten/emscripten.h>

// External declaration of the engine entry point
extern int hwengine_RunEngine(int argc, char **argv);

// ============================================================
// emscripten_set_main_loop replacement for hwengine_MainLoop
// ============================================================
//
// The generated hwengine_MainLoop() is a blocking while-loop.
// With ASYNCIFY, every SDL_Delay and SDL_GL_SwapWindow triggers
// a full WASM stack save/restore (~2+ per frame). This is the
// primary performance bottleneck.
//
// We use --wrap=hwengine_MainLoop to intercept the call and
// replace it with emscripten_set_main_loop, which uses
// requestAnimationFrame — zero ASYNCIFY overhead on the hot path.
// ============================================================

#include "fpcrtl.h"
#include "hwengine.h"

// Wrapper that provides --internal flag without needing JS heap manipulation.
// Placed after includes so SDL_SetHint is declared (via SDLh.h).
EMSCRIPTEN_KEEPALIVE
int hwengine_RunEngine_internal(void) {
    // Disable SDL's emscripten_sleep in SwapWindow/Delay BEFORE engine init.
    // AddProgress() calls SwapBuffers during loading — with JSPI this causes
    // SuspendError because emscripten_sleep is a JS function.
    SDL_SetHint("SDL_EMSCRIPTEN_ASYNCIFY", "0");

    char *argv[] = {
        (char*)"--internal",
        (char*)"--prefix",
        (char*)"/Data",
        (char*)"--user-prefix",
        (char*)"/Data",
        NULL
    };
    return hwengine_RunEngine(5, argv);
}

// Forward declare the original (in case we ever need it)
extern void __real_hwengine_MainLoop(void);

// From hwengine.c (not in header but is a global symbol)
extern boolean hwengine_DoTimer(LongInt Lag);

// String constants (static in hwengine.c, so we define our own)
static const string255 ml_str_quit = STRINIT("quit");
static const string255 ml_str_fullscr = STRINIT("fullscr ");

// State persisted across frames
static LongWord ml_PrevTime;
static boolean ml_isTerminated;
static int ml_frameCount;
static TGameState ml_previousGameState;
static double ml_lastFrameTime;

// Debug timing (toggled via JS: Module.HWEngine.debugTiming = true)
EM_JS(int, hw_debug_timing, (), { return Module.HWEngine && Module.HWEngine.debugTiming ? 1 : 0; });

// Wrap RAF callback with error catching — if mainloop_frame throws,
// the browser silently stops calling requestAnimationFrame.
EM_JS(void, hw_install_error_catcher, (), {
    var origSetMainLoop = _emscripten_set_main_loop;
    if (Module._loopWrapped) return;
    Module._loopWrapped = true;
    // Patch the browser's RAF callback after emscripten_set_main_loop sets it up
    var origRAF = window.requestAnimationFrame;
    window.requestAnimationFrame = function(cb) {
        return origRAF.call(window, function(ts) {
            try { cb(ts); } catch(e) {
                console.error('[Engine] RAF EXCEPTION killed loop:', e);
                console.error('[Engine] Stack:', e.stack);
                throw e;
            }
        });
    };
    // Monitor for long tasks blocking the main thread
    if (window.PerformanceObserver) {
        try {
            new PerformanceObserver(function(list) {
                list.getEntries().forEach(function(entry) {
                    if (entry.duration > 50)
                        console.warn('[Engine] LONG TASK: ' + entry.duration.toFixed(0) + 'ms at ' + entry.startTime.toFixed(0));
                });
            }).observe({entryTypes: ['longtask']});
        } catch(e) {}
    }
});

static void mainloop_frame(void) {
    TSDL_Event event;
    boolean wheelEvent = false;
    double t0 = 0, t1 = 0, t2 = 0, t3 = 0;
    int doDebug = 1;
    t0 = emscripten_get_now();
    double frameDelta = t0 - ml_lastFrameTime;
    ml_lastFrameTime = t0;

    if (ml_isTerminated || !allOK) {
        emscripten_log(0, "PERF LOOP EXIT f=%d terminated=%d allOK=%d", ml_frameCount, (int)ml_isTerminated, (int)allOK);
        emscripten_cancel_main_loop();
        return;
    }

    SDL_PumpEvents();
    while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT) > 0) {
        switch (event.type_) {
        case SDL_KEYDOWN:
            if (isInChatMode)
                uchat_KeyPressChat(event.key.keysym);
            else if (GameState >= gsGame)
                uinputhandler_ProcessKey_1(event.key);
            break;
        case SDL_KEYUP:
            if (!isInChatMode && GameState >= gsGame)
                uinputhandler_ProcessKey_1(event.key);
            break;
        case SDL_TEXTINPUT:
            if (isInChatMode)
                uchat_TextInput(&event.text);
            break;
        case SDL_WINDOWEVENT:
            switch (event.window.event) {
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                cHasFocus = true;
                uworld_onFocusStateChanged();
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                cHasFocus = false;
                uworld_onFocusStateChanged();
                break;
            case SDL_WINDOWEVENT_RESTORED:
                if (GameState == gsSuspend)
                    GameState = ml_previousGameState;
                cWindowedMaximized = false;
                break;
            case SDL_WINDOWEVENT_MAXIMIZED:
                cWindowedMaximized = true;
                break;
            case SDL_WINDOWEVENT_RESIZED:
                cNewScreenWidth = uutils_Max(2 * (event.window.data1 / 2), cMinScreenWidth);
                cNewScreenHeight = uutils_Max(2 * (event.window.data2 / 2), cMinScreenHeight);
                cScreenResizeDelay = RealTicks + 500;
                break;
            }
            break;
        case SDL_MOUSEMOTION:
            uinputhandler_ProcessMouseMotion(event.motion.xrel, event.motion.yrel);
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (GameState == gsConfirm)
                ucommands_ParseCommand_2(ml_str_quit, true);
            else if (GameState >= gsGame)
                uinputhandler_ProcessMouseButton(event.button, true);
            break;
        case SDL_MOUSEBUTTONUP:
            if (GameState >= gsGame)
                uinputhandler_ProcessMouseButton(event.button, false);
            break;
        case SDL_MOUSEWHEEL:
            wheelEvent = true;
            uinputhandler_ProcessMouseWheel(event.wheel.y);
            break;
        case SDL_JOYAXISMOTION:
            uinputhandler_ControllerAxisEvent(event.jaxis.which, event.jaxis.axis, event.jaxis.value);
            break;
        case SDL_JOYHATMOTION:
            uinputhandler_ControllerHatEvent(event.jhat.which, event.jhat.hat, event.jhat.value);
            break;
        case SDL_JOYBUTTONDOWN:
            uinputhandler_ControllerButtonEvent(event.jbutton.which, event.jbutton.button, true);
            break;
        case SDL_JOYBUTTONUP:
            uinputhandler_ControllerButtonEvent(event.jbutton.which, event.jbutton.button, false);
            break;
        case SDL_QUITEV:
            ml_isTerminated = true;
            break;
        }
    }

    if (!wheelEvent)
        uinputhandler_ResetMouseWheel();

    if (CursorMovementX != 0 || CursorMovementY != 0)
        ucursor_handlePositionUpdate(CursorMovementX, CursorMovementY);

    if (cScreenResizeDelay != 0 && cScreenResizeDelay < RealTicks &&
        (cNewScreenWidth != cScreenWidth || cNewScreenHeight != cScreenHeight)) {
        cScreenResizeDelay = 0;
        cWindowedWidth = cNewScreenWidth;
        cWindowedHeight = cNewScreenHeight;
        cScreenWidth = cWindowedWidth;
        cScreenHeight = cWindowedHeight;
        ucommands_ParseCommand_2(_strconcat(ml_str_fullscr, uutils_IntToStr((LongInt)cFullScreen)), true);
        uscript_ScriptOnScreenResize();
        uworld_InitCameraBorders();
        uworld_InitTouchInterface();
        ustore_InitZoom(ZoomValue);
    }

    LongWord CurrTime = SDL_GetTicks();
    ml_frameCount++;
    if (doDebug) t1 = emscripten_get_now();
    // Count how many ticks we need to catch up
    int ticksNeeded = 0;
    LongWord tmpTime = ml_PrevTime;
    while (tmpTime + (LongWord)cTimerInterval <= CurrTime) {
        ticksNeeded++;
        tmpTime += (LongWord)cTimerInterval;
    }
    // Cap to avoid runaway (e.g. after tab-away or loading)
    if (ticksNeeded > 128)
        ticksNeeded = 128;

    // Run catch-up ticks with rendering disabled (game logic only)
    // Skip optimization for first 32 frames to let land textures generate
    if (ticksNeeded > 1 && ml_frameCount > 32) {
        cOnlyStats = true;
        for (int i = 0; i < ticksNeeded - 1 && !ml_isTerminated; i++) {
            ml_isTerminated = ml_isTerminated || hwengine_DoTimer((LongInt)cTimerInterval);
            ml_PrevTime += (LongWord)cTimerInterval;
        }
        cOnlyStats = false;
    }
    t2 = emscripten_get_now();
    // Final tick with rendering enabled
    if (ticksNeeded > 0 && !ml_isTerminated) {
        ml_isTerminated = ml_isTerminated || hwengine_DoTimer((LongInt)cTimerInterval);
        ml_PrevTime += (LongWord)cTimerInterval;
    }
    t3 = emscripten_get_now();
    // If still behind, skip ahead
    if (ml_PrevTime + (LongWord)cTimerInterval <= CurrTime)
        ml_PrevTime = CurrTime;

    uio_IPCCheckSock();
    double frameEnd = emscripten_get_now();
    // Log every frame for first 300, then every 60th or when slow
    if (ml_frameCount < 300 || ml_frameCount % 60 == 0 || frameDelta > 50) {
        emscripten_log(0, "PERF f=%d rafDelta=%.0fms ticks=%d catchup=%.1fms render=%.1fms total=%.1fms",
            ml_frameCount, frameDelta, ticksNeeded, t2-t1, t3-t2, frameEnd-t0);
    }
}

void __wrap_hwengine_MainLoop(void) {
    ml_previousGameState = gsStart;
    ml_isTerminated = false;
    ml_PrevTime = SDL_GetTicks();

    // Catch silent exceptions that kill the RAF loop
    hw_install_error_catcher();

    // fps=0 means use requestAnimationFrame, simulate_infinite_loop=1
    emscripten_set_main_loop(mainloop_frame, 0, 1);
}
