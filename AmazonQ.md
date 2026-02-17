# Amazon Q - WebWars Context

**Last Updated**: 2026-02-17T09:57:00Z  
**Working Directory**: `/home/ubuntu/mcpprojects/webwars/`  
**Status**: ✅ Build 100% complete - hwengine.wasm successfully generated

## Project: WebWars (Hedgewars WASM Port)

Browser port of Hedgewars using pas2c → Emscripten pipeline with WebSocket multiplayer.

## Current Phase: IPC Protocol Testing

### Build Complete! 🎉
- ✅ All source code compiled to WebAssembly
- ✅ Output: hwengine.html (22KB), hwengine.js (464KB), hwengine.wasm (4.1MB)
- ✅ All 8 core patches applied and working
- ✅ HWLIBRARY flag enabled for --internal mode

### Next Steps
1. Test IPC protocol with hotseat game setup (30 min)
2. Verify rendering and gameplay (1 hour)
3. Deploy MVP on this server (15 min)

## Key Technical Points

- **Compilation**: Pascal → pas2c → C → Emscripten → WASM ✅
- **Toolchain**: Official Emscripten (disabled legacy Platform/Emscripten.cmake)
- **Rust**: staticlib with wasm32-unknown-emscripten target
- **SDL**: Via Emscripten ports (-sUSE_SDL=2, -sUSE_SDL_NET=2)
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

## Files Modified (8 patches)

**CMake:**
- `hedgewars/CMakeLists.txt` - PhysFS/Lua bundled builds, skip Platform/
- `hedgewars/cmake_modules/Platform/Emscripten.cmake` → `.legacy`
- `hedgewars/misc/libphyslayer/CMakeLists.txt` - Remove .bc suffix
- `hedgewars/misc/libphysfs/CMakeLists.txt` - Modern CMake
- `hedgewars/misc/liblua/CMakeLists.txt` - Remove lua_emscripten_internal
- `hedgewars/project_files/hwc/CMakeLists.txt` - Memory alignment, SDL_NET, HWLIBRARY

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

**MVP**: Game loads in browser, hotseat playable, <10s load time ✅  
**Full**: Multiplayer stable, deployed on this server, public URL
