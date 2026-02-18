# Agent Status Tracking - WebWars (Hedgewars WASM Port)

## 🎯 PROJECT GOAL

**Browser-based Hedgewars** - Full game engine compiled to WebAssembly, playable in any browser. Hotseat (local) and multiplayer (WebSocket) modes.

Compilation path: Pascal → pas2c → C → Emscripten → WebAssembly

---

## 📚 DOCUMENTATION STRUCTURE

### Core Files (NEVER DELETE)
- **AGENTS.md** (this file) - Permanent knowledge, architecture, lessons learned
- **AmazonQ.md** - Current status, session history, progress tracking
- **README.md** - User-facing quick start guide

---

## Current Status
Last updated: 2026-02-18T16:28:00Z

### Project Status
- **Phase**: JSPI Working — Game Renders in Browser
- **Last Action**: Fixed SuspendError by disabling SDL_EMSCRIPTEN_ASYNCIFY before engine init
- **Current Blocker**: Performance — game renders but runs slowly (same issue as pre-JSPI)
- **Target**: Playable frame rate in browser with JSPI

### Implementation Tracks
| Track | Component | Status | Next Action |
|-------|-----------|--------|-------------|
| A | Baseline Build | ✅ COMPLETE | Native hwengine builds successfully |
| A | pas2c Validation | ✅ COMPLETE | All Pascal→C conversion working |
| A | Emscripten Compile | ✅ COMPLETE | hwengine.wasm built and running |
| A | Asset Packaging | ✅ COMPLETE | 187MB assets packaged |
| A | Browser Loading | ✅ COMPLETE | Engine loads and executes |
| A | Boot Flow | ✅ COMPLETE | Auto-start with Module.arguments |
| A | IPC Transport | ✅ COMPLETE | Bidirectional IPC working |
| A | IPC Protocol | ✅ COMPLETE | All commands parsed and executed |
| A | Map Loading | ✅ COMPLETE | Cake map with mask.png loads |
| A | Spawn System | ✅ COMPLETE | Hedgehogs spawn successfully |
| A | Game Loop | ✅ COMPLETE | Runs 360+ ticks, sends state updates |
| A | Win Detection | ✅ COMPLETE | Detects winners, plays sounds |
| A | Browser MVP | 🟡 IN PROGRESS | Fix texture loading, improve perf |
| B | WebSocket Gateway | NOT STARTED | Gateway code ready |
| B | Server Integration | NOT STARTED | Need hedgewars-server binary |
| B | Multiplayer Test | NOT STARTED | Depends on server |
| C | Deployment | ✅ COMPLETE | Systemd service running |

### Current Issues
1. **Texture loading failures** - BlueWater, Clouds, SkyL/R, AmmoMenu, theme sprites (flags 5/21/44) all fail to load
2. **Cleanup crash** - `RuntimeError: unreachable` during shutdown
3. **Main loop timing** - ~~SDL vsync calls before Emscripten main loop exists~~ FIXED: using emscripten_set_main_loop
4. **Console spam** - ~~5000+ lines from debug mode~~ FIXED: switched to -O2
5. **Data file path warning** - `dependency: datafile_../../bin/hwengine.data` (non-fatal)

---

## 🏗️ ARCHITECTURE

### Compilation Pipeline
```
Pascal Source (.pas)
  → pas2c tool (Haskell)
    → C Code (60+ .c files)
      → Emscripten (emcc)
        → hwengine.wasm (4.2MB)
        → hwengine.js (470KB glue)
        → hwengine.data (187MB assets)
```

### IPC Architecture (Browser ↔ Engine)
```
JavaScript (pre.js)                    C Shim (ipc_browser.c)           Pascal Engine (uIO.pas)
┌─────────────────┐                   ┌──────────────────┐              ┌─────────────────┐
│ Module.HWEngine  │                   │                  │              │                 │
│  .sendMessage()  │──queue──→         │ hw_ipc_recv()    │──→           │ IPCCheckSock()  │
│  .readIPC()      │←─EM_JS──         │ SDLNet_TCP_Send()│←──           │ ParseIPCCommand │
│  .writeIPC()     │──EM_JS──→        │                  │              │ SendIPCRaw()    │
│  .startHotseat() │                   │ SDL_net stubs    │              │ IPCWaitPong()   │
└─────────────────┘                   └──────────────────┘              └─────────────────┘
```

### Key Files in the Chain
| Step | File | Function |
|------|------|----------|
| JS Message Queue | `hedgewars/project_files/web/pre.js` | sendMessage(), readIPC(), writeIPC(), startHotseatGame() |
| JS Runtime Init | `hedgewars/project_files/web/post.js` | Runtime initialization |
| C IPC Shim | `hedgewars/project_files/hwc/ipc_browser.c` | hw_ipc_recv(), SDLNet_TCP_Send() stubs |
| C Main Loop | `hedgewars/project_files/hwc/web_entry.c` | __wrap_hwengine_MainLoop(), emscripten_set_main_loop |
| Pascal IPC | `hedgewars/hedgewars/uIO.pas` | IPCCheckSock(), ParseIPCCommand(), SendIPCAndWaitReply() |
| Pascal Commands | `hedgewars/hedgewars/uCommands.pas` | Command registration and dispatch |
| Pascal Handlers | `hedgewars/hedgewars/uCommandHandlers.pas` | Individual command handlers |
| Pascal Engine | `hedgewars/hedgewars/hwengine.pas` | Main engine entry point |
| CMake Main | `hedgewars/CMakeLists.txt` | Build configuration, PhysFS/Lua bundled |
| CMake hwc | `hedgewars/project_files/hwc/CMakeLists.txt` | Emscripten flags, memory, linking |
| Rust Config | `hedgewars/rust/lib-hwengine-future/.cargo/config.toml` | Force wasm32-unknown-emscripten |
| Build Script | `scripts/build-wasm.sh` | Complete Emscripten configuration |

### IPC Protocol (Length-Prefixed Messages)
```
Byte 0: Length (1 byte, max 255)
Bytes 1-N: Message content

Message types:
  'e' + seed        → Set random seed (e.g., "eseed_value")
  'T' + count       → Set team count
  'e$...'           → Game config commands
  'H' + name        → Add hedgehog
  '!'               → Pong response
  '?'               → Ping request
  'i' + stats       → Game statistics
  'q' + reason      → Quit with reason
```

### Hotseat Game Setup Sequence (pre.js)
```javascript
// 1. Config
sendMessage("TL")           // Local game
sendMessage("e$seed " + seed)
sendMessage("e$mapgen 0")   // Random map
sendMessage("e$template_filter 1")
sendMessage("e$feature_size 12")

// 2. Teams (2 teams, 4 hedgehogs each)
sendMessage("eaddteam <color> Team1")
sendMessage("ename hog1") // x4
sendMessage("eaddteam <color> Team2")
sendMessage("ename hog1") // x4

// 3. Start
sendMessage("!")            // Pong to start
```

---

## 📁 FILE STRUCTURE

```
webwars/
├── AGENTS.md                    # Permanent knowledge (NEVER DELETE)
├── AmazonQ.md                   # Current state + history (NEVER DELETE)
├── README.md                    # Quick start (NEVER DELETE)
├── .gitignore
│
├── hedgewars/                   # Cloned + modified Hedgewars source
│   ├── CMakeLists.txt           # Main build config (MODIFIED)
│   ├── hedgewars/               # Pascal source files
│   │   ├── hwengine.pas         # Engine entry point (MODIFIED)
│   │   ├── uIO.pas              # IPC implementation (MODIFIED)
│   │   ├── uCommands.pas        # Command dispatch (MODIFIED)
│   │   ├── uCommandHandlers.pas # Command handlers (MODIFIED)
│   │   ├── uSound.pas           # Sound system (MODIFIED - disable music)
│   │   ├── uStore.pas           # Asset loading (MODIFIED - suppress spam)
│   │   ├── uConsts.pas          # Constants (MODIFIED - guard init)
│   │   └── uMatrix.pas          # GL matrix (MODIFIED - guard legacy)
│   ├── project_files/
│   │   ├── hwc/                 # C compilation target
│   │   │   ├── CMakeLists.txt   # Emscripten flags (MODIFIED)
│   │   │   ├── ipc_browser.c    # Browser IPC shim (NEW)
│   │   │   ├── web_entry.c      # emscripten_set_main_loop wrapper (NEW)
│   │   │   └── rtl/
│   │   │       ├── GL.h         # GLES2 headers (MODIFIED)
│   │   │       ├── gl_emscripten_compat.h  # WebGL compat (NEW)
│   │   │       └── misc.h       # fpcrtl (MODIFIED)
│   │   └── web/
│   │       ├── pre.js           # Message queue + Module setup (NEW)
│   │       └── post.js          # Runtime init (NEW)
│   ├── rust/lib-hwengine-future/
│   │   ├── Cargo.toml           # staticlib (MODIFIED)
│   │   └── .cargo/config.toml   # Force wasm32 target (NEW)
│   ├── misc/
│   │   ├── libphyslayer/CMakeLists.txt  # (MODIFIED)
│   │   ├── libphysfs/CMakeLists.txt     # (MODIFIED)
│   │   └── liblua/CMakeLists.txt        # (MODIFIED)
│   ├── cmake_modules/Platform/
│   │   └── Emscripten.cmake.legacy      # Renamed from .cmake
│   └── tools/corrosion/         # Rust-CMake integration
│
├── build/                       # Build outputs (gitignored)
│   └── wasm/bin/
│       ├── hwengine.html        # 22KB loader
│       ├── hwengine.js          # 470KB glue
│       ├── hwengine.wasm        # 4.2MB engine
│       └── hwengine.data        # 187MB assets
│
├── gateway/                     # WebSocket gateway (NOT STARTED)
│   └── src/index.js             # Gateway code ready
├── web/                         # Browser frontend
│   ├── index.html               # Landing page
│   ├── launcher.html            # Game launcher
│   └── mvp.html                 # MVP test page
├── scripts/
│   ├── build-wasm.sh            # Complete Emscripten build
│   ├── build-native.sh          # Native build
│   ├── build-pas2c.sh           # pas2c conversion
│   ├── package-assets.sh        # Asset packaging
│   └── analyze-assets.sh        # Asset analysis
├── cors-server.py               # CORS-enabled HTTP server
└── docs/                        # Documentation
```

---

## 🧠 AGENT WORKFLOW

### ⚠️ MANDATORY: Update Docs BEFORE Ending Session
**DO NOT wait for the user to ask. DO NOT forget. DO NOT skip this.**
The user has had to remind the agent MULTIPLE TIMES. This is unacceptable.

After EVERY coding session, BEFORE saying "done" or wrapping up:
1. ✅ Update **AmazonQ.md** with session summary and timestamp
2. ✅ Update **AGENTS.md** if new permanent lesson learned
3. ✅ Update **README.md** if user-facing changes
4. ✅ Git commit with clear message
5. ✅ **TELL THE USER** you updated docs (don't make them ask)

### Before STARTING New Work
1. ✅ Review **AmazonQ.md** for current status
2. ✅ Review **AGENTS.md** for relevant lessons and architecture
3. ✅ Check recent git commits for changes since last session

### Red Flags (I'm Failing)
- ⚠️ User asks "did you update docs?" → I forgot
- ⚠️ I suggest something already tried → Didn't read context
- ⚠️ I repeat a mistake → AGENTS.md wasn't updated
- ⚠️ User has to remind me twice → I failed first time
- ⚠️ I make changes without committing → CRITICAL WORKFLOW ERROR
- ⚠️ I pipe long command output through head/tail → User can't see real-time progress

**Context files are my only memory. Without them, I start from scratch every time.**

---

## 📋 FILE RULES

- **NEVER delete**: AGENTS.md, AmazonQ.md, README.md
- **Can delete other .md files IF**: knowledge is incorporated into main files first
- **Always commit** after making changes - don't tell user to test without pushing first

---

## ⚙️ TECHNICAL NOTES

### Build Commands
```bash
# Full clean build
source ~/emsdk/emsdk_env.sh
source ~/.cargo/env
cd build/wasm
rm -rf *
cmake ../../hedgewars -DBUILD_ENGINE_JS=ON -DNOSERVER=ON \
  -DCMAKE_TOOLCHAIN_FILE=$EMSDK/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake
make -j$(nproc)

# Quick rebuild after changes
cd build/wasm && make -j$(nproc)

# Using build script
./scripts/build-wasm.sh
```

### Deployment
```bash
# Service management
sudo systemctl status webwars-server
sudo systemctl restart webwars-server
sudo journalctl -u webwars-server -f

# URL
http://54.80.204.92:8081/hwengine.html
```

### Emscripten Flags (in hwc/CMakeLists.txt)
```
-sUSE_SDL=2              # SDL2 via Emscripten ports
-sUSE_SDL_NET=2          # SDL_net via ports
-sALLOW_MEMORY_GROWTH=1  # Dynamic memory
-sINITIAL_MEMORY=268435456  # 256MB initial
-sSTACK_SIZE=1048576     # 1MB stack
-sFORCE_FILESYSTEM=1     # Virtual filesystem
-sEXPORTED_FUNCTIONS     # _main, _malloc, _free
-sEXPORTED_RUNTIME_METHODS  # ccall, cwrap, etc.
--preload-file Data@/Data  # Asset packaging
--pre-js pre.js          # Message queue
--post-js post.js        # Runtime init
```

### Rust Integration
- Target: `wasm32-unknown-emscripten` (forced via .cargo/config.toml)
- Crate type: `staticlib` (produces .a file linked by Emscripten)
- Linker: `emcc`, AR: `emar`
- Corrosion (CMake tool) detects host target, NOT Cargo target - this is why .cargo/config.toml is needed

### OpenGL Compatibility
- Engine uses desktop OpenGL constants (GL_QUADS, GL_CLAMP, etc.)
- `gl_emscripten_compat.h` maps these to GLES2/WebGL2 equivalents
- `GL.h` includes GLES2/gl2.h instead of desktop GL

---

## 🔑 CRITICAL LESSONS

### 1. Corrosion Detects Host, Not Cargo Target (PERMANENT FIX IN CMakeLists.txt)
Corrosion's FindRust.cmake has NO Emscripten handling. It falls back to the host target (x86_64-unknown-linux-gnu), which sets `Rust_CARGO_TARGET_LINK_NATIVE_LIBS=gcc_s;util;rt;pthread;m;dl;c` in CMakeCache.txt. These propagate via INTERFACE_LINK_LIBRARIES to the WASM link line, causing `wasm-ld: unable to find -lutil`. The `.cargo/config.toml` only affects `cargo build` at runtime — it does NOT fix the CMake configure-time detection. Every `rm -rf build/wasm/*` would re-trigger the bug. **Permanent fix**: `set(Rust_CARGO_TARGET "wasm32-unknown-emscripten" CACHE STRING "Target triple" FORCE)` BEFORE `add_subdirectory(tools/corrosion)` in hedgewars/CMakeLists.txt.

### 2. Legacy Platform/Emscripten.cmake Overrides Everything
Hedgewars ships its own `cmake_modules/Platform/Emscripten.cmake` that overrides the official Emscripten toolchain. This breaks modern Emscripten. Fix: Rename to `.legacy` and let the official toolchain work.

### 3. pas2c Initialization Order Matters
Pascal units have initialization sections that run at startup. `uConsts.pas` had unguarded initialization that crashed in WASM. Fix: Guard with `{$IFNDEF EMSCRIPTEN}` or conditional compilation.

### 4. SDL_net Must Be Stubbed for Browser
The engine uses SDL_net for IPC (TCP sockets). In browser, we replace with EM_JS calls to JavaScript. The C shim (`ipc_browser.c`) stubs all SDL_net functions and routes through the JS message queue.

### 5. Emscripten Main Loop Integration
SDL's vsync calls `emscripten_set_main_loop_timing` before the main loop exists. This causes warnings but doesn't crash. Proper fix would be to use `emscripten_set_main_loop()` but the engine's game loop is deeply embedded in Pascal code.

### 6. Asset Path Resolution
Emscripten's `--preload-file Data@/Data` creates a virtual filesystem. The engine expects assets at `/Data/`. The `Module.locateFile()` callback helps resolve the `.data` file URL, but path warnings still appear (non-fatal).

### 7. Don't Pipe Long Command Output
Never use `| head`, `| tail`, `| grep` on build commands. User can't see real-time progress. Run commands directly and let output stream.

### 8. Context Files Are Memory
Without AGENTS.md and AmazonQ.md, agent starts from scratch every session. These files ARE the agent's long-term memory. Update them religiously.

### 9. Clean Build After CMake Changes
After modifying any CMakeLists.txt, always `rm -rf build/wasm/*` and reconfigure. Incremental builds after CMake changes cause mysterious failures.

### 10. HWLIBRARY Flag is Critical
The engine must be built with `-DHWLIBRARY` flag for `--internal` mode (no TCP sockets). Without it, the engine tries to open TCP connections which fail in browser.

### 11. Ammo Stores Must Be Sent Per-Team
The real Hedgewars server (EngineInteraction.hs `teamSetup`) sends ammo config (eammloadt/eammprob/eammdelay/eammreinf/eammstore) BEFORE EACH team, not once globally. Without per-team stores, `AssignStores()` fails with "Invalid ammo store number" because hedgehog.AmmoStore = TeamsCount-1 but StoreCnt is only 1.

### 12. Read the Real Server Code, Don't Guess IPC Protocol
The Hedgewars IPC protocol is complex. Always reference `gameServer/EngineInteraction.hs` for the exact message sequence. Guessing leads to subtle bugs like the ammo store ordering issue.

### 13. ASYNCIFY Is Catastrophically Slow for Main Loops
ASYNCIFY saves/restores the entire WASM stack on every `emscripten_sleep`, `SDL_Delay`, and `SDL_GL_SwapWindow`. In a 60fps game loop that's 120+ stack unwind/rewind cycles per second. Fix: use `emscripten_set_main_loop` with `--wrap=hwengine_MainLoop` linker flag to intercept the generated C function. Set `SDL_SetHint("SDL_EMSCRIPTEN_ASYNCIFY", "0")` to prevent SDL from calling `emscripten_sleep` in SwapWindow/Delay. ASYNCIFY is still needed for initialization (IPCWaitPongEvent) and AI delays, but NOT on the hot rendering path.

### 14. Use --wrap for Generated Code Interception
When pas2c generates C code you can't modify (regenerated on every build), use the linker `--wrap=symbol_name` flag. Define `__wrap_symbol_name()` in your own C file as the replacement, and `__real_symbol_name()` to call the original. Include the generated headers via `#include "fpcrtl.h"` then `#include "hwengine.h"` (order matters — fpcrtl.h defines types used by generated headers). Add `${CMAKE_CURRENT_BINARY_DIR}` to include paths for generated .h files.

### 15. Console Logging Blocks the Browser Main Thread
`console.log` / `emscripten_log` in browsers is synchronous and extremely expensive. At 480 calls/sec it can drop frame rate from 60fps to 3-6fps. Remove all debug logging from hot paths.

### 16. Use cOnlyStats for Multi-Tick Catch-Up in WASM
The engine's `cOnlyStats` boolean (in `uVariables.h`) skips `DrawWorld`, `ProcessVisualGears`, and `SwapBuffers`. For WASM frame pacing: set `cOnlyStats=true` for N-1 catch-up ticks (game logic only), then `cOnlyStats=false` for the final tick (with rendering). This avoids wasting GPU work on frames that will never be displayed.

### 17. etheme Is Mandatory — Textures Depend on Theme Path
The engine loads sky, water, clouds, and sprites from `ptCurrTheme` (e.g. `/Themes/Cake/`). This path is ONLY set when the `etheme` command is received via IPC. Without it, `InitStepsFlags` lacks `cifTheme` and textures load from the wrong path. The real server (EngineInteraction.hs:109) always sends `etheme` before seed/config. For preset maps, the map.cfg contains the theme name on line 1, but the engine only reads line 2 (MaxHedgehogs) — the theme must still be sent via IPC.

### 18. ASYNCIFY_IGNORE_INDIRECT + ASYNCIFY_ADD Is Fragile at -O2
`ASYNCIFY_IGNORE_INDIRECT` requires listing every function in the async call chain via `ASYNCIFY_ADD`. But `-O2` inlines functions, removing them as symbols — `ASYNCIFY_ADD` silently ignores missing names, breaking the unwind chain. Use `ASYNCIFY_ADVISE` to discover the real symbol names. Safer alternative: `ASYNCIFY_REMOVE` with glob patterns for known-safe categories (FreeType, PNG, Vorbis, dynCall). Result: 5.4MB → 5.15MB (5% reduction, modest but correct).

### 19. Always Copy Custom HTML After Build
Emscripten regenerates `hwengine.html` on every build (because target suffix is `.html`). The custom dark-themed HTML in `web/hwengine.html` must be copied to `build/wasm/bin/` after each build. Without it, the generic Emscripten shell loads — which lacks the Module setup needed for the game to start.

### 20. JSPI Cannot Suspend Through JS Frames — Unlike ASYNCIFY
JSPI (JavaScript Promise Integration, `-sJSPI`, ASYNCIFY=2) is the modern replacement for ASYNCIFY. It's faster (no stack instrumentation, ~23% smaller WASM) but has a hard constraint: **the entire call chain between a `WebAssembly.promising()` export and a `WebAssembly.Suspending()` import must be pure WASM — no JS frames allowed.** ASYNCIFY tolerated JS trampolines because it rewrites the whole stack machine; JSPI cannot. Key implications:
- `invoke_*` JS trampolines (from setjmp/longjmp) break JSPI → fix with `-sSUPPORT_LONGJMP=wasm` + `-fwasm-exceptions`
- `SDL_Delay` → `emscripten_sleep` is a JS function that calls `Asyncify.handleAsync` (async JS) → creates JS frames in the suspend path
- Any `EM_JS` function on the stack when a suspend happens will break JSPI
- **Best fix**: eliminate suspends entirely where possible (e.g., busy-poll instead of sleep when data is already available)
- Use `-sSUPPORT_LONGJMP=wasm` and `-fwasm-exceptions` to eliminate `invoke_*` trampolines
- Verify with: `grep 'function invoke_' hwengine.js` — must return zero results for JSPI safety

### 21. Eliminate SDL_Delay from IPCWaitPongEvent in EMSCRIPTEN Builds
`IPCWaitPongEvent` loops with `SDL_Delay(1)` waiting for pong. In browser, IPC messages are pre-queued in JS before `RunEngine_internal` is called, so the pong is already available. `SDL_Delay` triggers `emscripten_sleep` which requires ASYNCIFY/JSPI suspend machinery. Fix: `{$IFNDEF EMSCRIPTEN} SDL_Delay(1) {$ENDIF}` — busy-poll is fine since data is already there. This eliminates the need for any suspend during engine init.

### 22. JSPI SuspendError Root Cause: `_emscripten_sleep` Is a JS Function
Even with zero `invoke_*` trampolines (`-sSUPPORT_LONGJMP=wasm` + `-fwasm-exceptions` confirmed working), JSPI still fails with SuspendError during init. Root cause: Emscripten's `_emscripten_sleep` is implemented as a **JS function** that calls `Asyncify.handleAsync()` (an async JS function). Even though `instrumentWasmImports` wraps it with `WebAssembly.Suspending`, the internal JS execution creates frames that JSPI cannot suspend through. The fix is to eliminate the need to call `emscripten_sleep` entirely during init (Option C: busy-poll). For gameplay suspends (AI `SDL_Delay`), JSPI may still fail — those will need either: (a) the same busy-poll treatment, (b) a pure-WASM sleep implementation, or (c) fallback to ASYNCIFY for those code paths. Key diagnostic: check `var _emscripten_sleep=` in generated JS — if it contains `Asyncify.handleAsync`, it's a JS function, not a WASM import, and JSPI will fail when it tries to suspend through it.

### 23. SDL_GL_SwapWindow Calls emscripten_sleep During Init (AddProgress)
The engine's `AddProgress()` function renders a loading progress bar and calls `SwapBuffers()` → `SDL_GL_SwapWindow()`. SDL2's Emscripten backend checks the `SDL_EMSCRIPTEN_ASYNCIFY` hint — when enabled (default), `SDL_GL_SwapWindow` calls `emscripten_sleep(0)` to yield to the browser. This creates a JS-frame suspend that breaks JSPI. Fix: call `SDL_SetHint("SDL_EMSCRIPTEN_ASYNCIFY", "0")` at the very start of `hwengine_RunEngine_internal()`, before any engine initialization. This must happen before `SDL_Init` and before any `AddProgress` calls. The hint was previously set only in `__wrap_hwengine_MainLoop` (too late — init already called SwapBuffers multiple times by then).

---

## 🐛 KEY BUG PATTERNS

### Never Do This

| Bug Pattern | Why It's Bad | Fix |
|-------------|--------------|-----|
| Skip .cargo/config.toml | Corrosion injects native libs into WASM link | Always have config.toml |
| Missing Rust_CARGO_TARGET set | .cargo/config.toml only fixes cargo build, NOT CMake configure-time detection | set(Rust_CARGO_TARGET "wasm32-unknown-emscripten") BEFORE add_subdirectory(corrosion) |
| Use legacy Platform/Emscripten.cmake | Overrides official toolchain, breaks everything | Rename to .legacy |
| Forget HWLIBRARY flag | Engine tries TCP sockets in browser | Add -DHWLIBRARY to compile flags |
| Pipe build output | User can't see progress | Run commands directly |
| Incremental build after CMake change | Stale cache causes mysterious failures | Clean build: rm -rf build/wasm/* |
| callMain() in Emscripten | Doesn't exist in output | Use Module.run() instead |
| noInitialRun flag | Gets stripped by Emscripten optimizer | Use Module.run() approach |
| Forget to commit | Next session loses all context | Always git commit |
| Send ammo store once globally | Team 2+ hedgehogs get invalid AmmoStore index | Send ammo per-team before each eaddteam |
| Guess IPC protocol | Subtle ordering bugs | Read EngineInteraction.hs |
| Use ASYNCIFY for main loop | 120+ stack save/restore per second | emscripten_set_main_loop + --wrap |
| Include hwengine.h before fpcrtl.h | fpcrtl_dimension_t undefined | Always include fpcrtl.h first |
| console.log in hot path | Synchronous, blocks main thread, kills FPS | Remove all debug logging from frame loop |
| Multiple DoTimer calls per frame | Each call renders (DrawWorld+SwapBuffers) | Use cOnlyStats=true for catch-up ticks |
| Skip etheme in IPC | Engine can't find theme textures (sky, water, clouds) | Always send etheme before seed/config |
| Bare -sASYNCIFY without whitelist | Instruments ALL functions, ~50% overhead | Use ASYNCIFY_REMOVE with glob patterns for safe categories |
| ASYNCIFY_IGNORE_INDIRECT + ASYNCIFY_ADD at -O2 | Inlined functions vanish as symbols, silently breaks unwind chain | Use ASYNCIFY_REMOVE instead; or use ASYNCIFY_ADVISE to verify names |
| Build without copying custom HTML | Emscripten overwrites hwengine.html with generic shell | Always `cp web/hwengine.html build/wasm/bin/` after build |
| Use JSPI without eliminating JS-frame suspends | `_emscripten_sleep` is a JS function, JSPI can't suspend through it | Remove `SDL_Delay` from init paths; busy-poll instead |
| Assume invoke_* is the only JSPI blocker | Even with zero invoke_*, `_emscripten_sleep` JS impl breaks JSPI | Check `var _emscripten_sleep=` in generated JS for `Asyncify.handleAsync` |

---

## 🎯 NEXT STEPS

### Immediate (Texture & Performance)
1. Debug texture loading failures (flags 5/21/44) — missing sky, water, clouds, sprites
2. Verify emscripten_set_main_loop performance improvement in browser
3. Test input controls (keyboard/mouse → engine)

### Short Term (Polish)
1. Fix cleanup crash (RuntimeError: unreachable)
2. Fix remaining texture loading (may be SDL_image format or path issue)
3. Add proper game restart support

### Medium Term (Multiplayer)
1. Build WebSocket gateway (gateway/src/index.js)
2. Compile hedgewars-server for the host
3. Bridge WebSocket ↔ TCP for server communication
4. Test 2-player game

### Long Term (Production)
1. Optimize asset loading (lazy-load music, optional maps)
2. Reduce initial download (51MB essential vs 187MB full)
3. Add proper web UI for game configuration
4. HTTPS + domain name

---

## Success Metrics

**Achieved:**
- ✅ Engine compiles to WASM (4.2MB)
- ✅ All dependencies resolved (Lua, PhysFS, SDL2, Rust)
- ✅ Assets package and load (187MB)
- ✅ Engine executes in browser
- ✅ WebGL context created
- ✅ IPC bidirectional communication
- ✅ Game loop runs (360+ ticks)
- ✅ Win detection works
- ✅ Sound playback works
- ✅ Build system reliable

**Remaining:**
- ✅ Game renders on canvas
- ⏳ Input controls work
- ⏳ Game restart without crash
- ⏳ Multiplayer via WebSocket
