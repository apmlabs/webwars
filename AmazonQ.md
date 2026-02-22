# Amazon Q - WebWars Context

**Last Updated**: 2026-02-22T04:58:00Z
**Working Directory**: `/home/ubuntu/mcpprojects/webwars/`
**Status**: ✅ Multiplayer WORKING — production deployed at webwars.link

## Project: WebWars (Hedgewars WASM Port)

Browser port of Hedgewars using pas2c → Emscripten pipeline with WebSocket multiplayer.

## Current Phase: Multiplayer Testing & Polish

### What Works
- ✅ Engine compiled to WebAssembly (5.15MB — reduced from 5.4MB via ASYNCIFY_REMOVE optimization)
- ✅ Assets load (187MB data file)
- ✅ IPC protocol working perfectly
- ✅ Map loading (Cake map with mask.png)
- ✅ Spawn system working (no FindPlace errors)
- ✅ Game loop runs (360+ ticks)
- ✅ Win detection works
- ✅ Sound playback works
- ✅ Build system reliable (.cargo/config.toml fix)
- ✅ **Rendering confirmed** - game renders on canvas
- ✅ **Optimized build** - switched from -O0 to -O2
- ✅ **emscripten_set_main_loop** - eliminated ASYNCIFY overhead on hot path
- ✅ **cOnlyStats multi-tick catch-up** - game logic runs at real-time speed, only last tick renders
- ✅ **Download progress bar** - shows MB downloaded during 187MB data fetch
- ✅ **Custom game page** - hwengine.html with controls overlay
- ✅ **etheme command** - theme textures now load (sky, water, clouds, sprites)
- ✅ **ASYNCIFY_REMOVE globs** - safe 5% WASM reduction (FreeType/PNG/Vorbis/dynCall excluded)
- ✅ **IPC logging removed** - no more console.log blocking in hot path
- ✅ **JSPI migration** - switched from ASYNCIFY to JSPI (-sJSPI), 23% smaller WASM (3.97MB vs 5.15MB)
- ✅ **invoke_* eliminated** - `-sSUPPORT_LONGJMP=wasm` + `-fwasm-exceptions` confirmed zero invoke_* trampolines
- ✅ **Init suspend eliminated** - IPCWaitPongEvent busy-polls without SDL_Delay in EMSCRIPTEN builds
- ✅ **SDL asyncify disabled** - SDL_SetHint("SDL_EMSCRIPTEN_ASYNCIFY", "0") before engine init
- ✅ **JSPI rendering confirmed** - game renders in browser with JSPI (3.97MB WASM)
- ✅ **GL_PREINITIALIZED_CONTEXT** - WebGL2 context created in JS with optimal attributes, passed to Emscripten
- ✅ **Context attributes locked** - antialias:false, alpha:false, desynchronized:true, powerPreference:high-performance
- ✅ **GPU timer queries working** - EXT_disjoint_timer_query_webgl2 confirmed on Intel Iris Plus
- ✅ **GL_UNSAFE_OPTS=1** - skip redundant WebGL validation in Emscripten glue
- ✅ **GL_POOL_TEMP_BUFFERS=1** - reuse temporary buffers
- ✅ **Pass counters added** - clears, FBO binds, tex uploads, program switches per frame
- ✅ **Sprite batch system** - BatchQuad/FlushBatch replaces per-sprite GL calls, GPU time 38-45ms → 1-9ms avg
- ✅ **CPU transforms** - DrawTextureRotatedF, DrawHedgehog, DrawTexture, DrawTexture2, DrawTextureFromRectDir, DrawTextureRotated, DrawSpriteRotatedF, DrawSpriteRotatedFReal, DrawSpritePivotedF all converted to CPU-side vertex transform + BatchQuad
- ✅ **GL_STREAM_DRAW** - ANGLE streaming ring buffer for per-frame batch uploads
- ✅ **Rotation fixed** - All CPU transforms now match original openglRotatef sign convention
- ✅ **No flicker** - desynchronized:false for proper double-buffered compositing
- ✅ **FlushBatch on all state changes** - Tint, untint, setTintAdd, BeginWater, DrawLine, etc.
- ✅ **Multiplayer lobby** - WebSocket gateway, rooms, chat, team config, game launch
- ✅ **Multiplayer gameplay** - Two players can play a full game, turns alternate, EM relay working
- ✅ **Admin panel** - Flask + Leaflet dashboard monitoring prod traffic, bot detection, geo map
- ✅ **Dev server secured** - nginx reverse proxy, HTTPS + basic auth, all direct ports closed
- ✅ **README expanded** - pas2c credit, "What I Built" technical section, Qt replacement documented, first person singular
- ✅ **Admin panel published** - Infra details extracted to .env (gitignored), code on GitHub
- ✅ **Admin panel filters** - "Show bots" and "Players only" filters for map, log, pages breakdown
- ✅ **Admin systemd service** - webwars-admin.service, proper restarts via systemctl
- ✅ **Dev IP hidden** - HIDDEN_IPS set excludes dev IP from all dashboard views
- ✅ **GitHub language stats fixed** - linguist-vendored on upstream tree, un-vendored new files
- ✅ **erdriven fix** - Only mark OTHER players' teams as externally driven (was marking all teams)
- ✅ **TN ordering** - Game type sent before config, matching Qt client order
- ✅ **IPCCheckSock timing** - Called before/between DoTimer ticks so EM messages are in headcmd queue
- ✅ **Background tab timer** - setInterval at 10Hz keeps processing EM when tab is hidden
- ✅ **WASM soft-exit** - Skip freeEverything in WASM builds, prevents RuntimeError: unreachable on shutdown
- ✅ **Quick play at root** - webwars.link/ serves hotseat game directly, lobby at /lobby.html
- ✅ **Gameplay hints** - Top bar shows "Right-click to pick a weapon · Space to fire · Arrow keys to move"
- ✅ **How-to-play in lobby** - Welcome area explains multiplayer flow and controls
- ✅ **Asset caching** - nginx Cache-Control: 7 days for .data/.wasm, 1h for .js, no-cache for .html
- ✅ **Auto-restart** - Quick play auto-reloads on game end (assets from disk cache, near-instant)

### Known Issues

1. **Data File Path Warning** (Non-Fatal)
   - Warning: `dependency: datafile_../../bin/hwengine.data`
   - File loads successfully via fallback mechanism

2. **Texture Loading Failures** (Visual Issue)
   - BlueWater, Clouds, SkyL/R, AmmoMenu, theme sprites (flags 5/21/44)
   - Game renders but missing sky, water, clouds, decorations

3. **Cleanup Crash** (FIXED — WASM soft-exit)
   - Was: `RuntimeError: unreachable` during `freeEverything` shutdown
   - Fix: Skip `freeEverything(true)` in EMSCRIPTEN builds; page reload handles cleanup
   - Engine loop exit now notifies JS via `hw_notify_engine_exit()`

### Deployment
- **Production**: `webwars.link` (HTTPS, nginx, Let's Encrypt)
- **Dev**: See `INFRA.md` (gitignored) for all server IPs, SSH keys, and AWS resource IDs
- **Agent docs repo**: `github.com/apmlabs/webwars-agent` (private) — sync with `cd /home/ubuntu/mcpprojects/webwars-agent && ./sync.sh`
- **Commands**:
  - Status: `sudo systemctl status webwars-server`
  - Logs: `sudo journalctl -u webwars-server -f`
  - Restart: `sudo systemctl restart webwars-server`

## Key Technical Points

- **Compilation**: Pascal → pas2c → C → Emscripten → WASM ✅
- **Toolchain**: Official Emscripten (disabled legacy Platform/Emscripten.cmake)
- **Rust**: staticlib with wasm32-unknown-emscripten target
- **SDL**: Via Emscripten ports (-sUSE_SDL=2, no SDL_NET)
- **OpenGL**: GLES2/WebGL2 with gl_emscripten_compat.h
- **IPC**: Custom browser shim replaces TCP sockets
- **Assets**: ~187MB (Graphics, Shaders, Fonts, Maps, Sounds)

## Build Commands

```bash
# Clean WASM build
source ~/emsdk/emsdk_env.sh
source ~/.cargo/env
cd build/wasm && rm -rf *
cmake ../../hedgewars -DBUILD_ENGINE_JS=ON -DNOSERVER=ON \
  -DCMAKE_TOOLCHAIN_FILE=$EMSDK/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake
make -j$(nproc)

# Quick rebuild
cd build/wasm && make -j$(nproc)

# Using build script
./scripts/build-wasm.sh
```

## Files Modified (18 patches + .cargo/config.toml)

**CMake:**
- `hedgewars/CMakeLists.txt` - PhysFS/Lua bundled builds, skip Platform/
- `hedgewars/cmake_modules/Platform/Emscripten.cmake` → `.legacy`
- `hedgewars/misc/libphyslayer/CMakeLists.txt` - Remove .bc suffix
- `hedgewars/misc/libphysfs/CMakeLists.txt` - Modern CMake
- `hedgewars/misc/liblua/CMakeLists.txt` - Remove lua_emscripten_internal
- `hedgewars/project_files/hwc/CMakeLists.txt` - Memory alignment, SDL_NET, HWLIBRARY, link deps

**Source:**
- `hedgewars/rust/lib-hwengine-future/Cargo.toml` - staticlib
- `hedgewars/rust/lib-hwengine-future/.cargo/config.toml` - Force wasm32-unknown-emscripten target
- `hedgewars/hedgewars/uConsts.pas` - Guard initialization
- `hedgewars/hedgewars/uMatrix.pas` - Guard legacy GL
- `hedgewars/hedgewars/uSound.pas` - Disable music for EMSCRIPTEN
- `hedgewars/hedgewars/uStore.pas` - Suppress asset loading spam
- `hedgewars/hedgewars/uIO.pas` - Browser IPC, buffer overflow fix, IPC logging
- `hedgewars/hedgewars/uCommands.pas` - IPC Level 3 logging
- `hedgewars/hedgewars/uCommandHandlers.pas` - Handler logging, uConsole import

**Headers:**
- `hedgewars/project_files/hwc/rtl/GL.h` - GLES2
- `hedgewars/project_files/hwc/rtl/gl_emscripten_compat.h` - NEW
- `hedgewars/project_files/hwc/rtl/misc.h` - glShaderSource

**JavaScript:**
- `hedgewars/project_files/web/pre.js` - NEW (Message queue, Module.locateFile, 2 teams)
- `hedgewars/project_files/web/post.js` - NEW (Runtime init)

**C Shims:**
- `hedgewars/project_files/hwc/web_entry.c` - NEW (emscripten_set_main_loop wrapper, --wrap entry)
- `hedgewars/project_files/hwc/ipc_browser.c` - NEW (Browser IPC shim, SDL_net stubs)

**Scripts:**
- `scripts/build-wasm.sh` - Complete config

## Session History

### Session 35 - February 22, 2026 (04:05-04:58 UTC)

**README engine modifications rewrite, admin panel filters, systemd service.**

**Phase 1: README Cleanup**
- Rewrote Engine Modifications section into three clear subsections: Pascal changes, C shims, JSPI
- Removed all ASYNCIFY mentions (was a wrong path, only JSPI should be referenced)
- Rewrote all "we" → "I" (solo project, 13 replacements)
- Removed inaccurate claim about pas2c being the only toolchain

**Phase 2: Admin Panel — "Show bots" filter for Pages (7 days)**
- Backend now returns per-page `{total, human, player}` counts (was just flat count)
- Frontend `renderPages()` respects both "Show bots" and "Players only" checkboxes

**Phase 3: Admin Panel — Hide dev IP**
- Added `HIDDEN_IPS` set with dev IP (90.174.10.182)
- All 4 API endpoints filter out hidden IPs from display (data still ingested)

**Phase 4: Admin Panel — "Players only" filter**
- Added green "Players only" checkbox (default checked) next to "Show bots"
- Player = any IP that downloaded `.data` file (187MB game assets)
- Filters map, visitor log, and pages breakdown by player status
- Investigated tracking: `.data` downloads ARE logged correctly via nginx access log

**Phase 5: Admin Panel — systemd service**
- Created `/etc/systemd/system/webwars-admin.service`
- Enabled and started — survives reboots, restarts via `sudo systemctl restart webwars-admin`

### Session 31 - February 21, 2026 (14:50-15:33 UTC)

**Quick play at root, gameplay hints, asset caching, auto-restart.**

**Phase 1: Page Restructure**
- Replaced stale `index.html` (old "in development" placeholder) with quick play page
- `webwars.link/` now serves hotseat game directly (same engine UI as hwengine.html)
- `webwars.link/lobby.html` stays as multiplayer lobby
- Changed nginx `index` directive from `lobby.html` to `index.html`

**Phase 2: Gameplay Hints**
- Added hint text to top bar on both index.html and hwengine.html: "Right-click to pick a weapon · Space to fire · Arrow keys to move"
- Added "🌐 Multiplayer" link button in quick play top bar
- Added "How to Play" box in lobby welcome area explaining multiplayer flow and controls
- Removed backdrop-filter blur from click-prompt overlay (was causing blue flash from engine init frames)

**Phase 3: Asset Caching**
- nginx Cache-Control headers: `.data`/`.wasm` → 7 days (public, immutable), `.js` → 1 hour, `.html` → no-cache
- After first visit, 187MB .data file loads from disk cache — reloads are near-instant

**Phase 4: Auto-Restart**
- Quick play page sets `_webwars_roundFinished` callback
- When engine exits: shows "Game Over — Reloading..." overlay, reloads after 1.5s
- With cache headers, the reload is instant (no re-download)

### Session 30 - February 21, 2026 (12:57-14:40 UTC)

**Production deployment: webwars.link live with HTTPS.**

**Phase 1: Domain Registration**
- Registered `webwars.link` via Route 53 ($5/year)
- Hosted zone auto-created, A records pointing to Elastic IP

**Phase 2: Production Server**
- Launched t3a.micro in us-east-2 (1GB RAM, 10GB gp3)
- Elastic IP allocated and associated
- SSH key created and saved locally (not in git)

**Phase 3: Deployment**
- Built statically-linked hedgewars-server (GLIBC mismatch fix)
- Deployed WASM build output, gateway, server binary via rsync/scp
- Created systemd services for hedgewars-server and webwars-gateway
- Installed Node.js 20, nginx, certbot

**Phase 4: HTTPS + nginx**
- nginx reverse proxy: static files + WebSocket at /ws
- Let's Encrypt certificate for webwars.link + www.webwars.link
- HTTP auto-redirects to HTTPS
- Fixed MIME types (missing `include mime.types` caused HTML downloads)

**Phase 5: Lobby WS URL Detection**
- lobby.html auto-detects: dev uses `:8080` directly, prod uses `/ws` through nginx

**Phase 6: Doc Cleanup**
- Deleted 7 stale MD files (SCAFFOLDING_COMPLETE, MODIFICATIONS, STATUS_REPORT, BUILD_SUCCESS, QUICKSTART, FRONTEND_ROADMAP, HEDGEWARS_UPSTREAM)
- Rewrote README.md for humans
- Created INFRA.md (gitignored) with all server details, SSH keys, AWS resource IDs
- Moved all infra details out of AGENTS.md and AmazonQ.md into INFRA.md

### Session 29 - February 20, 2026 (21:02-21:23 UTC)

**WASM soft-exit: eliminated cleanup crash on game end.**

**Analysis**
- Traced crash path: `Game()` → `freeEverything(true)` → `uStore.freeModule` → `SDL_GL_DeleteContext`/`SDL_DestroyWindow`/`SDL_Quit` → RuntimeError: unreachable
- Found double-destroy: both `uStore.freeModule` and `freeEverything` call SDL_GL_DeleteContext/SDL_DestroyWindow/SDL_Quit
- Confirmed Emscripten SDL doesn't support re-init after SDL_Quit — restart requires page reload regardless

**Fix: WASM Soft-Exit**
- `hwengine.pas`: Skip `freeEverything(true)` in `{$IFDEF EMSCRIPTEN}` builds
- `web_entry.c`: Added `hw_notify_engine_exit()` — calls `_webwars_roundFinished()` in JS when loop exits
- Flow: game ends → cancel main loop → notify JS → JS sends ROUNDFINISHED → location.reload()
- No SDL/GL teardown in WASM — page reload handles cleanup

### Session 28 - February 20, 2026 (20:00-20:48 UTC)

**Multiplayer fully playable! Fixed erdriven, IPCCheckSock timing, and background tab sync.**

**Phase 1: erdriven Fix (from session 27)**
- Root cause confirmed: `erdriven` was sent for ALL teams including local player's own team
- Engine treated all teams as network-controlled → no team responded to local input
- Fix: `if (t.owner !== cfg.myNick) this.sendMessage('erdriven')` — only mark OTHER players' teams
- Also moved `TN` before config to match Qt client ordering

**Phase 2: Deep Multiplayer Flow Analysis**
- Traced full EM relay path: Engine → writeIPC → base64 → WS → server → WS → handleEngineMsg → messageQueue → IPCCheckSock → headcmd → NetGetNextCmd
- Analyzed Qt client reference: `game.cpp` ParseMessage default case buffers engine output, `flushNetBuffer()` sends as `EM <base64>` to server
- Server `checkNetCmd` validates messages, relays to `roomOthersChans`
- Qt client `FromNet(em)` → `RawSendIPC(msg)` injects raw bytes into engine IPC
- Confirmed our relay matches Qt client behavior

**Phase 3: IPCCheckSock Timing Fix (Critical)**
- `IPCCheckSock` was called ONCE per frame, AFTER all DoTimer catch-up ticks
- `DoTimer` calls `NetGetNextCmd` which reads from `headcmd` queue
- Incoming EM messages were in JS messageQueue but not yet parsed into `headcmd`
- Engine saw `headcmd=nil` → `isInLag=true` → game paused waiting for network
- Fix: call `IPCCheckSock` BEFORE tick loop, BETWEEN catch-up ticks, and BEFORE final render tick

**Phase 4: Background Tab Timer**
- Browsers throttle `requestAnimationFrame` to ~1fps for background tabs
- EM messages piled up (qLen growing from 5 → 511), causing 10+ second resync on tab switch
- Fix: `setInterval` at 10Hz when `document.hidden`, running game logic with `cOnlyStats=true`
- Exported `mainloop_frame_bg` for JS to call from the background timer
- When tab becomes visible, interval stops and RAF resumes

**Phase 5: EM Diagnostic Logging**
- Added `_emStats` counters: sent, recv, qLen logged every 3 seconds
- Confirmed bidirectional EM flow: both players sending and receiving
- Gateway logs showed EM messages relayed correctly (keepalives, turn-ends, cursor positions)

**Testing Results:**
- Two players can play a full multiplayer game in the browser
- Turns alternate correctly between players
- Actions are synced (weapon selection, movement, shooting, damage)
- Health bars and game state update properly
- Tab switching causes brief resync (background timer should reduce this)

### Session 25 - February 20, 2026 (17:42-18:40 UTC)

**Multiplayer Phase 3-4: Team config sync, single-page engine architecture, EM relay.**

**Phase 1: Team Config & CFG Sync**
- Fixed ADD_TEAM protocol: name, color, grave, fort, voicepack, flag, difficulty, 8×(hogname, hoghat)
- Handle server responses: TEAM_ACCEPTED, TEAM_COLOR, HH_NUM, ADD_TEAM (from others), REMOVE_TEAM
- CFG sync: chief sends SEED/MAPGEN/THEME/TEMPLATE/AMMO/SCHEME on room create
- Non-chief receives CFG updates and applies to UI
- Player ready/inGame state tracking from CLIENT_FLAGS (+r/-r, +g/-g)

**Phase 2: Rate Limiter Fix**
- All WS clients appear as localhost through gateway — HW server's JoinsMonitor rejected 2nd player
- Relaxed limits: 5/30s, 10/2min, 20/10min (was 2/3/5)
- Rebuilt hedgewars-server binary, redeployed

**Phase 3: Multiplayer Engine Integration (pre.js)**
- Added `startMultiplayerGame()` — reads config from mpConfig, generates IPC matching EngineInteraction.hs
- Sends TN (network game) instead of TL (local)
- EM relay: engine game messages base64-encoded and sent to server via direct function calls
- Incoming EM from server injected directly into engine message queue

**Phase 4: Single-Page Architecture (Critical Design Decision)**
- Problem: `window.open()` blocked by popup blocker in incognito; navigation kills WS connection
- Solution: Engine loads dynamically in lobby page via `<script>` injection
- Lobby DOM hidden, fullscreen canvas shown over it
- WebSocket stays alive (same JS context) — EM relay is direct function calls
- Exit game = `location.reload()` (clean reset, WS auto-reconnects)

**Phase 5: Bug Fixes**
- Canvas ID must be `canvas` — SDL2 WASM has `#canvas` hardcoded via `emscripten_set_canvas_element_size`
- Auto-add team when entering room (no manual button needed for MVP)
- Room list polls every 3s for auto-refresh

**Phase 6: Gateway Protocol Logging**
- Added bidirectional message logging to gateway (WS→HW and HW→WS)
- Confirmed: RUN_GAME sent to both players, EM messages relayed correctly
- Identified issues: canvas ID mismatch, popup blocker, timing

**Testing Results:**
- Lobby, rooms, chat, team sync all working between two browser windows
- Both players receive RUN_GAME from server
- Engine loads in-page for host player (one frame rendered)
- Guest player gets black screen — canvas ID fix should resolve this
- EM messages flow through server relay correctly

### Session 24 - February 20, 2026 (15:50-17:36 UTC)

**Deep dive into project scope, then Phase 1-2 of multiplayer: server + gateway deployed.**

**Phase 0: Project Scope Analysis**
- Audited all 117 Lua scripts (6MB) — all packaged in WASM .data file, ready to load via `escript` IPC
- Catalogued: 21 multiplayer game styles, 58 missions, 25 campaign missions, 12 library scripts
- Analyzed Qt frontend (22 pages, ~95K lines C++) — cannot port, must rebuild as web UI
- Mapped HW server protocol: text-based, newline-delimited TCP, NICK→PROTO→lobby→rooms→EM relay
- Confirmed engine is deterministic — multiplayer just relays inputs, no server-side game logic

**Phase 1: Hedgewars Server**
- Compiled hedgewars-server from Haskell source (`cabal build`, GHC 9.4.7)
- 31MB binary, copied to `bin/hedgewars-server`
- Created systemd service `hedgewars-server.service` on port 46631
- Tested: NICK + PROTO handshake → LOBBY:JOINED, ROOMS list

**Phase 2: WebSocket Gateway**
- Rewrote `gateway/src/index.js` with proper HW protocol framing
- Browser sends JSON arrays (`["NICK","player"]`) → gateway converts to `NICK\nplayer\n\n`
- Server responses parsed at `\n\n` boundaries → sent back as JSON arrays
- Created systemd service `webwars-gateway.service` on port 8080
- Full round-trip tested: WS connect → NICK → PROTO → LOBBY:JOINED → ROOMS → PING

### Session 22 - February 19, 2026 (13:57-17:20 UTC)

**Fixed inverted rotation, blinking, and black frame flicker. Game fully playable at 60fps.**

**Phase 1: Deep Analysis — Rotation Sign Bug**
- Compared all CPU-transform functions against original Hedgewars source (fetched from GitHub raw)
- Found all 6 converted functions used `cos(-Angle * ...)` instead of `cos(Angle * ...)`
- Root cause: `hglRotatef(Angle, 0, 0, 1)` rotates CCW by Angle, but `cos(-Angle)` gives CW rotation
- This inverted gun aiming (up→down), hedgehog body rotation, and made UFO/jetpack feel wrong
- Fixed: DrawSpriteRotatedF, DrawSpriteRotatedFReal, DrawSpritePivotedF, DrawHedgehog, DrawTextureRotatedF, DrawTextureRotated

**Phase 2: Missing FlushBatch in untint/setTintAdd**
- `untint()` changed tint uniform without flushing pending batched quads
- `setTintAdd()` changed blend mode uniform without flushing
- Added FlushBatch() to both functions in GL2 path

**Phase 3: Black Frame Flicker — desynchronized Context**
- `desynchronized:true` uses single-buffer (front buffer) rendering
- Display controller reads directly from the buffer being drawn to
- `glClear` at frame start wipes buffer to black — display can scan it out before scene is drawn
- First tried `preserveDrawingBuffer:true` — still flickered (preserveDrawingBuffer only prevents browser clearing, not our own glClear)
- Fix: `desynchronized:false` — standard double-buffering, display only sees complete frames
- 16ms latency cost is imperceptible for a turn-based game

**Final Performance (Cave map, 905x715)**
- GPU: 0-1ms calm, 7-9ms with water (well under 16ms budget)
- CPU: render=0.2-0.5ms, total=0.3-0.8ms
- Frame pacing: solid 16-17ms rafDelta (60fps)
- Full game played to completion: Red Team wins, allOK=1

### Session 21 - February 19, 2026 (11:19-13:47 UTC)

**Sprite batch system implemented and deployed — GPU time down 80-95%. Fixed rendering correctness bugs.**

**Phase 1: GL Call Profiling**
- Enhanced performance probe with per-frame counters for glBindTexture, glBufferData, glBufferSubData, glUniformMatrix4fv
- Added MAX_ARRAY_TEXTURE_LAYERS and MAX_TEXTURE_SIZE queries
- Results: ~463 GL state changes per frame (83 draws, 83 binds, 166 bufferData, 131 uniformMatrix)
- Each GL call becomes a D3D11 resource operation through ANGLE — root cause of 38-45ms GPU time

**Phase 2: Sprite Batch System (uRender.pas)**
- Added BatchQuad/FlushBatch system: 1024-quad capacity, interleaved pos+uv VBO, GL_TRIANGLES
- Converted DrawTextureRotatedF, DrawTexture, DrawTexture2, DrawTextureFromRectDir, DrawTextureRotated, DrawHedgehog to CPU-transform + BatchQuad
- Added GL_STREAM_DRAW and GL_TRIANGLES constants to pas2cSystem.pas
- GL_STREAM_DRAW tells ANGLE to use shared streaming ring buffer (optimal for per-frame uploads)
- Added FlushBatch at all state-change boundaries: Tint, BeginWater, DrawLine, DrawCircle, DrawWaves, FinishRender

**Phase 3: Performance Results**
- GPU time: 38-45ms → 1-9ms average (80-95% reduction)
- bufD ≈ draws (was 2× draws before — no more double buffer uploads per sprite)
- Steady state: gpu=0-9ms avg, calm frames as low as 1ms

**Phase 4: Rendering Correctness Fixes**
- Found critical bug: DrawSpriteRotatedF/DrawSpriteRotatedFReal used matrix stack + BatchQuad without flushing
  - Vertices queued in local space, but batch flushed later with camera MVP → sprites drawn at wrong position
  - This caused hedgehogs to be invisible (drawn at screen origin) and blinking
- Converted DrawSpriteRotatedF to CPU transform: rotate → mirror → translate → BatchQuad
- Converted DrawSpriteRotatedFReal to CPU transform (same approach, Real coordinates)
- Converted DrawSpritePivotedF to CPU transform: offset from pivot → rotate → offset back → mirror → translate → BatchQuad (eliminates 2 flush points per call)
- Added missing FlushBatch before DrawLineWrapped matrix push

**Key Insight**: Any function that pushes the matrix stack and then calls a function that uses BatchQuad will produce incorrect results — the batch accumulates vertices in local space but flushes later with whatever MVP is current. All such functions must either: (a) be converted to CPU transforms, or (b) have FlushBatch brackets around the push/pop.

### Session 20 - February 19, 2026 (09:29-10:19 UTC)

**GPU timer queries working, context ownership locked, fill-rate diagnosis in progress.**

**Phase 1: Clean Build + Deploy (GPU timer probe + MSAA fix)**
- Deployed clean build with reverted pre.js + uStore.pas MSAA attributes + GPU timer probe
- First results: context attributes showed antialias:false but GPU-PROBE never fired
- Identified probe bug: `getContext('webgl2')` in probe was polling before engine created context

**Phase 2: Fixed GPU Timer Probe**
- Rewrote probe to try both `EXT_disjoint_timer_query_webgl2` and `EXT_disjoint_timer_query`
- Used RAF-aligned frame boundaries with pending query queue
- Timer ext confirmed available on Intel Iris Plus via ANGLE/D3D11
- GPU-PROBE now fires correctly every 30 samples

**Phase 3: Context Attribute Regression Discovered**
- After clean rebuild, context attributes reverted to `antialias:true, alpha:true, desynchronized:false`
- Root cause: SDL/EGL creates context with defaults, probe's `getContext` call may have created default context first
- Previous "working" attributes were from a build that had the monkey-patch residue

**Phase 4: GL_PREINITIALIZED_CONTEXT Implementation**
- Create WebGL2 context in JS with explicit attributes BEFORE Emscripten loads
- Pass via `Module.preinitializedWebGLContext` + `-sGL_PREINITIALIZED_CONTEXT` linker flag
- Probe uses same `hwGL` variable directly — no `getContext` calls anywhere
- Result: `canvas===Module.canvas: true`, attributes confirmed correct
- One canvas, one context, one set of attributes — impossible to mismatch

**Phase 5: GL Optimization Flags**
- `GL_UNSAFE_OPTS=1` — skip redundant WebGL validation in Emscripten glue
- `GL_POOL_TEMP_BUFFERS=1` — reuse temporary buffers

**Phase 6: Pass Counter Analysis (Ground Truth)**
- Added counters: clears, FBO binds, texImage2D/texSubImage2D, program switches
- Results per ~100ms interval: `draws=222 clears=2 fboBinds=0 texUploads=0 progSwitch=0`
- This is a single-pass, single-program, single-FBO renderer
- GPU time is purely fill/overdraw + blending

**Phase 7: GPU Timer Ground Truth (Correct Context)**
- Calm: GPU avg=49-56ms, p50=52-57ms, draws=188-222, px=647075
- Explosion: GPU avg=111ms, p50=103ms, p95=201ms, draws=630-793
- Post-explosion: GPU avg=40-65ms, draws=248-350

**Phase 8: Fill-Rate Test (In Progress)**
- Set canvas to 0.5x resolution (quarter pixels) to test fill-bound hypothesis
- Also testing depth:false (2D game likely doesn't need depth buffer)
- Awaiting results from user

**Key Findings:**
- GPU is genuinely spending 50ms on calm frames with ~200 draws through ANGLE/D3D11
- Single-pass renderer: no multipass, no FBO switches, no texture churn, no program switches
- Fill/overdraw + alpha blending is the primary suspect
- Resolution scale test will confirm fill-bound vs draw-bound

### Session 10 - February 18, 2026 (13:13-13:35 UTC)

**JSPI SuspendError deep diagnosis and init suspend elimination.**

**Phase 1: Browser Test — SuspendError Confirmed**
- Browser showed: `SuspendError: trying to suspend without WebAssembly.promising` at "Getting game config..."
- Diagnostic `[HW] Async exports: []` was a false negative — JSPI wrapping IS present in generated JS
- `exportPattern=/^(_hwengine_RunEngine_internal|main|__main_argc_argv)$/` wraps with `WebAssembly.promising`
- `importPattern=/^(emscripten_sleep|invoke_.*|__asyncjs__.*)$/` wraps with `WebAssembly.Suspending`

**Phase 2: invoke_* Trampolines — Eliminated (Not the Cause)**
- Confirmed zero `invoke_*` functions in generated JS — `-sSUPPORT_LONGJMP=wasm` + `-fwasm-exceptions` working
- Lua's setjmp/longjmp fully handled in WASM, no JS trampolines

**Phase 3: Root Cause Found — `_emscripten_sleep` Is a JS Function**
- `var _emscripten_sleep = function(ms) { ... return Asyncify.handleAsync(innerFunc) }`
- `Asyncify.handleAsync` is `async startAsync => { try { return await startAsync() } finally {} }`
- Even though `instrumentWasmImports` wraps it with `WebAssembly.Suspending`, the internal JS async execution creates frames JSPI can't suspend through
- This is a fundamental Emscripten limitation with JSPI — `emscripten_sleep` is JS, not WASM

**Phase 4: Fix — Eliminate Init Suspend (Option C)**
- Modified `uIO.pas`: `{$IFNDEF EMSCRIPTEN} SDL_Delay(1) {$ENDIF}` in `IPCWaitPongEvent`
- IPC messages are pre-queued in JS before `RunEngine_internal` — pong is already available
- Busy-poll finds pong immediately, zero suspends needed during init
- Rebuilt and deployed with JSPI (3.97MB WASM)

**Phase 5: Still Failing — Found Real Root Cause (AddProgress → SwapBuffers)**
- IPCWaitPongEvent fix was necessary but not sufficient — SuspendError persisted
- Traced init path: after font loading, `AddProgress()` calls `SwapBuffers()` → `SDL_GL_SwapWindow()`
- SDL2's Emscripten backend calls `emscripten_sleep(0)` inside SwapWindow when `SDL_EMSCRIPTEN_ASYNCIFY` hint is enabled (default)
- The hint was only set to "0" in `__wrap_hwengine_MainLoop` — too late, init already called SwapBuffers
- Fix: moved `SDL_SetHint("SDL_EMSCRIPTEN_ASYNCIFY", "0")` to top of `hwengine_RunEngine_internal()`
- Had to restructure web_entry.c — moved function after fpcrtl.h/hwengine.h includes to access SDL_SetHint
- **Result: JSPI working! Game renders in browser with 3.97MB WASM**

**Remaining**: Performance is still slow (same as pre-JSPI). AI `SDL_Delay` in uAI.pas will need treatment when AI runs.

### Session 9 - February 18, 2026 (09:06-11:02 UTC)

**Full project analysis, bug fixes, clean rebuild.**

- Deep research: upstream repo, pas2c pipeline, Rust mapgen, SDL2 Emscripten docs, ASYNCIFY vs JSPI
- Confirmed all resource files exist in source AND .data package — texture issues were never about missing files
- Found and fixed IPC console.log in writeIPC hot path (blocked main thread on every message)
- Found and fixed pre.js overwriting HTML's Module.setStatus (broke progress bar)
- Removed -O2/-O3 conflict, increased INITIAL_MEMORY to 256MB
- Clean rebuild with consistent -O3, deployed and restarted server
- Noted linker warnings: ai_add_team_hedgehog/ai_have_plan FFI signature mismatches (upstream issue)

### Session 1 - February 17, 2026 (01:00-03:35 UTC)

**Initial scaffolding through complete WASM build.**

Commits: f6780b3 → 4e758aa (8 commits)

**Phase 1: Scaffolding & Research**
- Created project structure (scripts, gateway, web, docs)
- Cloned Hedgewars source, validated native build works
- Confirmed pas2c conversion produces C code from Pascal

**Phase 2: Emscripten Setup**
- Installed emsdk, configured toolchain
- Fixed GL.h to use GLES2/gl2.h instead of desktop GL
- Created gl_emscripten_compat.h for GL_QUADS → GL_TRIANGLES mapping
- Configured Rust crate as staticlib for wasm32-unknown-emscripten

**Phase 3: Build Fixes**
- Discovered legacy Platform/Emscripten.cmake overriding official toolchain → renamed to .legacy
- Fixed PhysFS, Lua, PhysLayer CMakeLists for Emscripten compatibility
- Resolved all 60+ C file compilation issues
- Final linking produced hwengine.wasm (4.2MB), hwengine.js (470KB), hwengine.data (187MB)

**Key insight**: Hedgewars ships its own Emscripten.cmake that conflicts with modern Emscripten. Must be disabled.

### Session 2 - February 17, 2026 (03:35-12:33 UTC)

**Browser integration: from "engine running" to "boot flow working".**

Commits: b4b3829 → a3a6abc (6 commits)

**Phase 1: Frontend Integration**
- Created web/launcher.html, web/mvp.html, cors-server.py
- Engine loaded in browser but needed boot flow work

**Phase 2: Boot Flow Debugging**
- Discovered `callMain()` doesn't exist in Emscripten output → switched to `Module.run()`
- Discovered `noInitialRun` flag gets stripped by optimizer → used Module.run() approach
- Added HWLIBRARY flag for --internal mode (no TCP sockets)
- Fixed Emscripten flag syntax (comma-separated form)

**Phase 3: Deployment**
- Created systemd service `webwars-server.service`
- Deployed to http://54.80.204.92:8081/hwengine.html
- Engine boots and initializes in browser

**Key insight**: `callMain()` and `noInitialRun` are unreliable in Emscripten. Use `Module.run()` directly.

### Session 3 - February 17, 2026 (15:00-21:00 UTC)

**IPC transport → full game loop → build fix.**

Commits: 9ac6a51 → 672b3b0 (4 commits)

**Phase 1: IPC Transport (BREAKTHROUGH)**
- Created ipc_browser.c - C shim stubbing SDL_net, routing through EM_JS to JavaScript
- Created pre.js - message queue with sendMessage(), readIPC(), writeIPC()
- Engine successfully read 149 bytes from JavaScript message queue
- Bidirectional IPC confirmed working

**Phase 2: Game Loop Running**
- Implemented hotseat game setup sequence in pre.js (seed, teams, hedgehogs, pong)
- Engine parsed all IPC commands, loaded Cake map, spawned hedgehogs
- Game loop ran 360+ ticks, detected winners, played victory sounds
- Modified uSound.pas (disable music), uStore.pas (suppress spam)

**Phase 3: Build System Fix**
- Build broke during CMake reconfiguration
- Root cause: Corrosion detected x86_64-unknown-linux-gnu instead of wasm32-unknown-emscripten
- This injected native libs (-lgcc_s, -lutil) into WASM link line
- Fix: Created `.cargo/config.toml` forcing Cargo to always target wasm32-unknown-emscripten
- Clean rebuild succeeded, server restarted with new build

**Key insight**: Corrosion queries `rustc -vV` for host target, ignoring Cargo's configured target. The .cargo/config.toml is the only reliable fix.

### Session 4 - February 17, 2026 (22:00-22:11 UTC)

**Fix fatal ammo store crash, correct IPC protocol, remove debug spam.**

Commits: 9a8203b → 355da49 (3 commits)

**Phase 1: Diagnosis**
- User reported "Invalid ammo store number" fatal error, engine exit code 52
- Traced through uAmmos.pas: `AssignStores()` → `GetAmmoByNum(hedgehog.AmmoStore)` → `num < StoreCnt` fails
- Root cause: pre.js sent ONE ammo store then BOTH teams. Team 2 hedgehogs got AmmoStore=1 but StoreCnt=1

**Phase 2: Protocol Fix**
- Read `gameServer/EngineInteraction.hs` `teamSetup` function — ammo is prepended BEFORE each team
- Rewrote pre.js: `sendAmmoAndTeam()` sends ammo store + team + hedgehogs as a unit
- Added missing game config: `e$gmflags`, `e$turntime`, `e$damagepct`, all scheme params
- Fixed team colors (real hex values instead of 0/1), added `efort`/`ehat` commands

**Phase 3: Debug Spam Removal**
- Removed IPC LEVEL1/2/3 logging from uCommands.pas, uIO.pas (was generating 5000+ lines)
- Removed PROBE loop tick logging from hwengine.pas MainLoop
- Kept ammo debug output in uAmmos.pas for verification
- Fixed .gitignore to exclude Rust target/ directory (was accidentally committed)

**Key insight**: The Hedgewars IPC protocol requires ammo stores per-team, not global. Always read EngineInteraction.hs, never guess the protocol.

### Session 5 - February 17, 2026 (22:11-23:16 UTC)

**Rendering confirmed, performance optimization: -O2 + emscripten_set_main_loop.**

Commits: 8b07650, fabf08a

**Phase 1: Diagnosis**
- User confirmed rendering works but "super slow and literally unplayable"
- Console showed hundreds of `WebGL: INVALID_ENUM: texParameter` errors from GL_TEXTURE_PRIORITY
- Build was compiled with `-O0 -g4 -sASSERTIONS=2` (full debug mode)
- ASYNCIFY save/restore on every SDL_Delay and SDL_GL_SwapWindow (2+ per frame)

**Phase 2: Quick Wins**
- Switched from `-O0 -g4 -sASSERTIONS=2` to `-O2` in hwc/CMakeLists.txt
- Guarded `glTexParameterf(GL_TEXTURE_PRIORITY)` with `{$IFNDEF EMSCRIPTEN}` in uStore.pas
- Doubled ASYNCIFY_STACK_SIZE from 64KB to 128KB

**Phase 3: Main Loop Rewrite (Major)**
- Identified ASYNCIFY as primary bottleneck: 120+ stack unwind/rewind cycles per second
- Created `__wrap_hwengine_MainLoop` in web_entry.c using `emscripten_set_main_loop`
- Used `--wrap=hwengine_MainLoop` linker flag to intercept generated C function
- Set `SDL_SetHint("SDL_EMSCRIPTEN_ASYNCIFY", "0")` to prevent SDL from calling emscripten_sleep
- Included generated headers via `fpcrtl.h` then `hwengine.h` (order matters)
- Added `${CMAKE_CURRENT_BINARY_DIR}` to include paths for generated .h files
- Fixed gitignore to track web_entry.c and ipc_browser.c

**Key insight**: ASYNCIFY is catastrophically slow for main loops. Use `emscripten_set_main_loop` + `--wrap` to intercept generated code. Set `SDL_EMSCRIPTEN_ASYNCIFY=0` to prevent SDL from adding its own emscripten_sleep calls.

### Session 6 - February 18, 2026 (00:00-00:28 UTC)

**Performance diagnosis and multi-tick catch-up with cOnlyStats.**

**Phase 1: Performance Diagnosis**
- Game rendered but ran at 3-6 FPS, unplayable
- Identified two root causes:
  1. Debug `emscripten_log` calls producing ~480 console.log/sec — browser console logging is synchronous and blocks main thread
  2. Each DoTimer call includes full rendering (DrawWorld + SwapBuffers), so 4 ticks/frame = 4 renders with only last visible
- First fix attempt (1 tick/frame) fixed wasted renders but game time crawled — only 8ms game time per 16ms real frame

**Phase 2: Engine Analysis**
- Analyzed `hwengine.c` DoTimer function: rendering (DrawWorld, SwapBuffers) is inseparable from game logic within a single call
- Discovered `cOnlyStats` boolean in `uVariables.h` — engine's built-in mechanism to skip rendering
- When `cOnlyStats=true`: `DrawWorld`, `ProcessVisualGears`, and `SwapBuffers` are all skipped

**Phase 3: Multi-Tick Solution**
- Implemented cOnlyStats-based catch-up in web_entry.c:
  - Calculate ticksNeeded from elapsed time vs cTimerInterval (8ms)
  - Set `cOnlyStats=true` for N-1 catch-up ticks (game logic only, no GPU work)
  - Set `cOnlyStats=false` for final tick (with rendering)
  - Cap at 128 ticks to prevent runaway after tab-away
- Fixed download progress bar: updated `Module.setStatus` regex to parse Emscripten's `(loaded/total)` byte format, display as MB

**Status**: Code written but not yet built/deployed — build was interrupted

**Key insight**: Console logging in browsers is synchronous and extremely expensive. Also, `cOnlyStats` is the engine's built-in rendering skip flag — perfect for WASM catch-up ticks where only the last frame needs to be drawn.

### Session 7 - February 18, 2026 (00:41-00:58 UTC)

**Deep project analysis, texture fix, ASYNCIFY optimization.**

**Phase 1: Full Project Research**
- Read official Hedgewars repo (github.com/hedgewars/hw): their `BUILD_ENGINE_JS` flag exists but pre.js/post.js are empty — they started but never finished the browser port
- Read `EngineInteraction.hs` to understand exact server message ordering
- Read Emscripten optimization docs (WebGL, ASYNCIFY, SDL2 porting)
- Analyzed the full Pascal→C→WASM pipeline and confirmed architecture is sound

**Phase 2: Root Cause — Missing Textures**
- Verified ALL texture files exist in the data package (BlueWater.png, Clouds.png, Sky.png etc.)
- Discovered `pre.js` never sends `etheme` command — engine doesn't know which theme to use
- Without `etheme`, `InitStepsFlags` never gets `cifTheme` bit, `ptCurrTheme` stays as `/Themes/Nature`
- Server protocol (EngineInteraction.hs line 109): `etheme` is mandatory, sent before seed/config
- Fix: Added map→theme mapping and `etheme` command to pre.js
- Fixed message ordering to match real server: emap → etheme → eseed → config → teams → !

**Phase 3: ASYNCIFY Optimization**
- Bare `-sASYNCIFY` instruments EVERY function (~50% overhead per Emscripten docs)
- Only 3 call sites actually need ASYNCIFY: IPCWaitPongEvent, SendIPCAndWaitReply, AI SDL_Delay
- Added `ASYNCIFY_IGNORE_INDIRECT` + `ASYNCIFY_ADD` whitelist for just those functions
- WASM binary: 5.4MB → 4.1MB (24% reduction)

**Phase 4: IPC Hot-Path Cleanup**
- Removed `fprintf(stderr, ...)` from `ipc_browser.c` read/write functions
- These were synchronous console.log calls firing on every IPC operation

**Phase 5: Debug Timing**
- Added optional per-frame timing to web_entry.c (toggle via `Module.HWEngine.debugTiming = true`)
- Reports: event processing time, tick count, logic time, total frame time

**Key insight**: The texture "failures" were never about missing files — the assets were always there. The engine just didn't know which theme directory to look in because we never told it.

### Session 8 - February 18, 2026 (01:02-01:19 UTC)

**Fix broken ASYNCIFY, restore custom HTML, deep ASYNCIFY analysis.**

**Phase 1: Diagnosis**
- Browser showed generic Emscripten HTML (green spinner) — build overwrote custom hwengine.html
- Engine returned 0 immediately after "Getting game config..." — ASYNCIFY chain was broken
- `ASYNCIFY_IGNORE_INDIRECT` + `ASYNCIFY_ADD` from session 7 was the cause

**Phase 2: ASYNCIFY Deep Analysis**
- Used `ASYNCIFY_ADVISE` to get full list: 2867 functions need instrumentation
- Checked our original ASYNCIFY_ADD list against ADVISE output: 4 of 7 functions were MISSING (inlined at -O2)
  - `hwengine_GameRoutine`, `hwengine_Game`, `hwengine_GenLandPreview`, `uio_IPCWaitPongEvent` — all inlined away
  - `uai_ProcessBot` — wrong name (real name: `uai_Think`)
- Traced actual call chains: `hwengine_RunEngine_internal` → `hwengine_RunEngine` → `uio_SendIPCAndWaitReply` → `SDL_Delay` → `emscripten_sleep`
- Categorized all 2867 functions: 596 Pascal engine, 385 Rust, 312 FreeType, 266 SDL, 149 Lua, etc.

**Phase 3: Correct ASYNCIFY Optimization**
- Replaced `ASYNCIFY_IGNORE_INDIRECT` + `ASYNCIFY_ADD` with `ASYNCIFY_REMOVE` glob patterns
- Removed safe categories: `FT_*,ft_*,tt_*,cff_*,af_*,ps_*,pfr_*,bdf_*,pcf_*,dynCall_*,png_*,vorbis_*,ov_*,ogg_*`
- WASM: 5.4MB → 5.15MB (5% reduction — modest but correct, no broken unwind chains)

**Phase 4: Custom HTML Fix**
- Copied `web/hwengine.html` back to `build/wasm/bin/` after build
- Added lesson 19: always copy custom HTML after build (Emscripten regenerates it)

**Key insight**: `ASYNCIFY_IGNORE_INDIRECT` + `ASYNCIFY_ADD` is fundamentally fragile with `-O2` because the compiler inlines functions, removing them as symbols. ASYNCIFY silently ignores missing names. `ASYNCIFY_REMOVE` with globs is the safe approach — keeps default instrumentation but excludes known-safe library code.

## Success Criteria

**MVP**: ✅ Game loads in browser, hotseat playable, 60fps
**Current**: Multiplayer lobby + rooms + teams working, engine loads in-page, testing rendering sync
**Full**: Multiplayer stable, deployed on this server, public URL
