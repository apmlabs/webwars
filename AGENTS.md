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
Last updated: 2026-02-17T21:52:00Z

### Project Status
- **Phase**: Game Loop Running - Build Fixed, Testing Deployment
- **Last Action**: Fixed Rust target detection with .cargo/config.toml
- **Current Blocker**: None - build working again
- **Target**: Verify rendering on canvas, fix cleanup crash

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
| A | Browser MVP | 🟡 IN PROGRESS | Need rendering verification |
| B | WebSocket Gateway | NOT STARTED | Gateway code ready |
| B | Server Integration | NOT STARTED | Need hedgewars-server binary |
| B | Multiplayer Test | NOT STARTED | Depends on server |
| C | Deployment | ✅ COMPLETE | Systemd service running |

### Current Issues
1. **Rendering unknown** - Canvas display not confirmed yet
2. **Cleanup crash** - `RuntimeError: unreachable` during shutdown
3. **Main loop timing** - SDL vsync calls before Emscripten main loop exists
4. **Console spam** - 5000+ lines from debug mode (-g4 -sASSERTIONS=2)
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

### After EVERY Coding Session
1. ✅ Update **AmazonQ.md** with session summary and timestamp
2. ✅ Update **AGENTS.md** if new permanent lesson learned
3. ✅ Update **README.md** if user-facing changes
4. ✅ Git commit with clear message

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

### 1. Corrosion Detects Host, Not Cargo Target
Corrosion queries `rustc -vV` for host target (x86_64-unknown-linux-gnu), not Cargo's configured target. This caused native libs (-lgcc_s, -lutil) to be injected into the WASM link line. Fix: `.cargo/config.toml` forces Cargo to always build for wasm32-unknown-emscripten, regardless of what Corrosion detects.

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

---

## 🐛 KEY BUG PATTERNS

### Never Do This

| Bug Pattern | Why It's Bad | Fix |
|-------------|--------------|-----|
| Skip .cargo/config.toml | Corrosion injects native libs into WASM link | Always have config.toml |
| Use legacy Platform/Emscripten.cmake | Overrides official toolchain, breaks everything | Rename to .legacy |
| Forget HWLIBRARY flag | Engine tries TCP sockets in browser | Add -DHWLIBRARY to compile flags |
| Pipe build output | User can't see progress | Run commands directly |
| Incremental build after CMake change | Stale cache causes mysterious failures | Clean build: rm -rf build/wasm/* |
| callMain() in Emscripten | Doesn't exist in output | Use Module.run() instead |
| noInitialRun flag | Gets stripped by Emscripten optimizer | Use Module.run() approach |
| Forget to commit | Next session loses all context | Always git commit |

---

## 🎯 NEXT STEPS

### Immediate (Rendering Verification)
1. Open http://54.80.204.92:8081/hwengine.html in browser
2. Check if canvas shows game graphics
3. If no rendering: check WebGL context, shader compilation
4. If rendering works: test input controls

### Short Term (Polish)
1. Fix cleanup crash (RuntimeError: unreachable)
2. Reduce console output (remove -g4 -sASSERTIONS=2)
3. Proper emscripten_set_main_loop() integration
4. Add input handling (keyboard/mouse → engine)

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
- ⏳ Game renders on canvas
- ⏳ Input controls work
- ⏳ Game restart without crash
- ⏳ Multiplayer via WebSocket
