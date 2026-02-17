# Amazon Q - WebWars Context

**Last Updated**: 2026-02-17T21:26:00Z  
**Working Directory**: `/home/ubuntu/mcpprojects/webwars/`  
**Status**: 🎉 Game Loop Running - Debugging Rendering & Cleanup

## Project: WebWars (Hedgewars WASM Port)

Browser port of Hedgewars using pas2c → Emscripten pipeline with WebSocket multiplayer.

## Current Phase: Game Loop Functional, Debugging Issues

### Breakthrough Achieved! 🎉
- ✅ Engine compiled to WebAssembly (4.2MB)
- ✅ Assets load (187MB data file)
- ✅ IPC protocol working perfectly
- ✅ Map loading (Cake map with mask.png)
- ✅ Spawn system working (no FindPlace errors)
- ✅ Game loop runs (360+ ticks)
- ✅ Win detection works
- ✅ Sound playback works
- 🟡 **Current**: Rendering status unknown, cleanup crash

### Known Issues

1. **Data File Path Warning** (Non-Fatal)
   - Warning: `dependency: datafile_../../bin/hwengine.data`
   - File loads successfully via fallback mechanism
   - Assets work (fonts, sounds, maps)
   - Need to verify `Module.locateFile()` is called

2. **Main Loop Integration** (Real Issue)
   - Error: `emscripten_set_main_loop_timing: Cannot set timing mode`
   - SDL trying to set vsync without Emscripten main loop
   - Can cause inconsistent rendering cadence
   - Needs proper `emscripten_set_main_loop()` integration

3. **Cleanup Crash** (Deterministic)
   - `RuntimeError: unreachable` during shutdown
   - Happens after "Freeing resources..."
   - Likely abort() during cleanup
   - Prevents game restart

4. **Output Volume** (Debug Mode)
   - 5000+ console lines per run
   - Caused by `-g4 -sASSERTIONS=2`
   - Every log = 1 message + 15-line stack trace
   - Attempted fix broke build (Rust linking)

5. **Build Currently Broken**
   - CMake reconfiguration broke Rust target libraries
   - Error: `unable to find library -lgcc_s -lutil`
   - Need clean rebuild with original flags

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
./scripts/build-wasm.sh
```

## Files Modified (15 patches)

**CMake:**
- `hedgewars/CMakeLists.txt` - PhysFS/Lua bundled builds, skip Platform/
- `hedgewars/cmake_modules/Platform/Emscripten.cmake` → `.legacy`
- `hedgewars/misc/libphyslayer/CMakeLists.txt` - Remove .bc suffix
- `hedgewars/misc/libphysfs/CMakeLists.txt` - Modern CMake
- `hedgewars/misc/liblua/CMakeLists.txt` - Remove lua_emscripten_internal
- `hedgewars/project_files/hwc/CMakeLists.txt` - Memory alignment, SDL_NET, HWLIBRARY, link dependencies

**Source:**
- `hedgewars/rust/lib-hwengine-future/Cargo.toml` - staticlib
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
- `hedgewars/project_files/web/pre.js` - NEW (Message queue, Module.locateFile, data logging, 2 teams)
- `hedgewars/project_files/web/post.js` - NEW (Runtime init)

**Scripts:**
- `scripts/build-wasm.sh` - Complete config

## Success Criteria

**MVP**: Game loads in browser, hotseat playable, <10s load time ✅  
**Current**: Game runs, needs rendering verification and cleanup fix
**Full**: Multiplayer stable, deployed on this server, public URL
