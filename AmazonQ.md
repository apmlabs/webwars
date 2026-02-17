# Amazon Q - WebWars Context

**Last Updated**: 2026-02-17T21:52:00Z
**Working Directory**: `/home/ubuntu/mcpprojects/webwars/`
**Status**: Game Loop Running - Build Fixed, Testing Deployment

## Project: WebWars (Hedgewars WASM Port)

Browser port of Hedgewars using pas2c → Emscripten pipeline with WebSocket multiplayer.

## Current Phase: Game Loop Functional, Verifying Rendering

### What Works
- ✅ Engine compiled to WebAssembly (4.2MB)
- ✅ Assets load (187MB data file)
- ✅ IPC protocol working perfectly
- ✅ Map loading (Cake map with mask.png)
- ✅ Spawn system working (no FindPlace errors)
- ✅ Game loop runs (360+ ticks)
- ✅ Win detection works
- ✅ Sound playback works
- ✅ Build system reliable (.cargo/config.toml fix)
- 🟡 **Current**: Rendering status unknown, cleanup crash

### Known Issues

1. **Data File Path Warning** (Non-Fatal)
   - Warning: `dependency: datafile_../../bin/hwengine.data`
   - File loads successfully via fallback mechanism

2. **Main Loop Integration** (Real Issue)
   - Error: `emscripten_set_main_loop_timing: Cannot set timing mode`
   - SDL trying to set vsync without Emscripten main loop

3. **Cleanup Crash** (Deterministic)
   - `RuntimeError: unreachable` during shutdown
   - Happens after "Freeing resources..."
   - Prevents game restart

4. **Output Volume** (Debug Mode)
   - 5000+ console lines per run
   - Caused by `-g4 -sASSERTIONS=2`

5. **Build System Fixed** ✅
   - Was broken: CMake detected wrong Rust target
   - Error was: `unable to find library -lgcc_s -lutil`
   - Fixed with: `.cargo/config.toml` forcing wasm32-unknown-emscripten

### Deployment
- **Service**: `webwars-server.service` (systemd)
- **URL**: http://54.80.204.92:8081/hwengine.html
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

## Files Modified (16 patches + .cargo/config.toml)

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

**Scripts:**
- `scripts/build-wasm.sh` - Complete config

## Session History

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

## Success Criteria

**MVP**: Game loads in browser, hotseat playable, <10s load time
**Current**: Game runs, needs rendering verification and cleanup fix
**Full**: Multiplayer stable, deployed on this server, public URL
