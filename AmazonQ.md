# Amazon Q - WebWars Context

**Last Updated**: 2026-02-17T02:28:00Z  
**Working Directory**: `/home/ubuntu/mcpprojects/webwars/`  
**Status**: Build 99% complete, final linking in progress

## Project: WebWars (Hedgewars WASM Port)

Browser port of Hedgewars using pas2c → Emscripten pipeline with WebSocket multiplayer.

## Current Phase: Build (99% Complete)

### Completed
- ✅ Emscripten toolchain configured (emcc/em++, no system clang)
- ✅ Rust wasm32-unknown-emscripten target built
- ✅ pas2c: All 60+ Pascal files converted to C
- ✅ OpenGL compatibility layer for WebGL2
- ✅ All C libraries compiled (Lua, PhysFS, physlayer, fpcrtl)
- ✅ All engine C files compiled (60+ files)

### Current Blocker
- PhysFS linking configuration (CMake can't find built library)
- **Fix**: Need to set correct PHYSFS_LIBRARY path or use bundled properly

### Next Steps
1. Fix PhysFS linking (5 min)
2. Complete final link → hwengine.html + .wasm + .js (2 min)
3. Test in browser with `python3 -m http.server` (5 min)
4. Package assets with `--preload-file` (30 min)

## Key Technical Points

- **Compilation**: Pascal → pas2c → C → Emscripten → WASM ✅
- **Toolchain**: Official Emscripten (disabled legacy Platform/Emscripten.cmake)
- **Rust**: staticlib with wasm32-unknown-emscripten target
- **SDL**: Via Emscripten ports (-sUSE_SDL=2)
- **OpenGL**: GLES2/WebGL2 with gl_emscripten_compat.h
- **Multiplayer**: WebSocket gateway bridges browser to TCP server (port 46631)
- **Assets**: ~218MB total, ~30-40MB essential

## Build Commands

```bash
# Clean WASM build
source ~/emsdk/emsdk_env.sh
source ~/.cargo/env
./scripts/build-wasm.sh
```

## Files Modified (11 patches)

**CMake:**
- `hedgewars/CMakeLists.txt` - Rust toggle, Platform module skip
- `hedgewars/cmake_modules/Platform/Emscripten.cmake` → `.legacy`
- `hedgewars/misc/libphyslayer/CMakeLists.txt` - SDL2/PhysFS
- `hedgewars/project_files/hwc/CMakeLists.txt` - Emscripten flags

**Source:**
- `hedgewars/rust/lib-hwengine-future/Cargo.toml` - staticlib
- `hedgewars/hedgewars/uConsts.pas` - Guard initialization
- `hedgewars/hedgewars/uMatrix.pas` - Guard legacy GL

**Headers:**
- `hedgewars/project_files/hwc/rtl/GL.h` - GLES2
- `hedgewars/project_files/hwc/rtl/gl_emscripten_compat.h` - NEW
- `hedgewars/project_files/hwc/rtl/misc.h` - glShaderSource

**Scripts:**
- `scripts/build-wasm.sh` - Complete config

## WebSocket Gateway (Ready)

```javascript
const WebSocket = require('ws');
const net = require('net');
const wss = new WebSocket.Server({ port: 8080 });

wss.on('connection', (ws) => {
  const tcp = net.connect(46631, 'localhost');
  ws.on('message', (d) => tcp.write(d));
  tcp.on('data', (d) => ws.send(d));
  ws.on('close', () => tcp.end());
  tcp.on('close', () => ws.close());
});
```

## Success Criteria

**MVP**: Game loads in browser, hotseat playable, <10s load time  
**Full**: Multiplayer stable, deployed on this server, public URL
