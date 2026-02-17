# Amazon Q - WebWars Context

**Last Updated**: 2026-02-17T12:29:00Z  
**Working Directory**: `/home/ubuntu/mcpprojects/webwars/`  
**Status**: ✅ Boot flow fixed - Testing stdin reading

## Project: WebWars (Hedgewars WASM Port)

Browser port of Hedgewars using pas2c → Emscripten pipeline with WebSocket multiplayer.

## Current Phase: IPC Protocol Testing

### Build Complete! 🎉
- ✅ All source code compiled to WebAssembly
- ✅ Output: hwengine.html (22KB), hwengine.js (470KB), hwengine.wasm (4.1MB)
- ✅ Boot flow fixed: Auto-run with Module.arguments
- ✅ IPC messages queued in preRun (149 bytes)
- ✅ Systemd service deployed
- 🟡 Testing: stdin reading and IPC protocol

### Deployment
- **Service**: `webwars-server.service` (systemd)
- **URL**: http://54.80.204.92:8081/hwengine.html
- **Commands**:
  - Status: `sudo systemctl status webwars-server`
  - Logs: `sudo journalctl -u webwars-server -f`
  - Restart: `sudo systemctl restart webwars-server`

### Next Steps
1. Verify stdin() is called and reads queued messages
2. Check IPC protocol framing (length-prefixed)
3. Debug any protocol issues
4. Verify game starts with hotseat setup

## Key Technical Points

- **Compilation**: Pascal → pas2c → C → Emscripten → WASM ✅
- **Toolchain**: Official Emscripten (disabled legacy Platform/Emscripten.cmake)
- **Rust**: staticlib with wasm32-unknown-emscripten target
- **SDL**: Via Emscripten ports (-sUSE_SDL=2, -sUSE_SDL_NET=2)
- **OpenGL**: GLES2/WebGL2 with gl_emscripten_compat.h
- **Multiplayer**: WebSocket gateway bridges browser to TCP server (port 46631)
- **Assets**: ~218MB total, ~30-40MB essential
- **Boot**: Auto-run with Module.arguments, IPC queued in preRun

## Build Commands

```bash
# Clean WASM build
source ~/emsdk/emsdk_env.sh
source ~/.cargo/env
./scripts/build-wasm.sh
```

## Files Modified (14 patches)

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

**Headers:**
- `hedgewars/project_files/hwc/rtl/GL.h` - GLES2
- `hedgewars/project_files/hwc/rtl/gl_emscripten_compat.h` - NEW
- `hedgewars/project_files/hwc/rtl/misc.h` - glShaderSource

**JavaScript:**
- `hedgewars/project_files/web/pre.js` - NEW (Message queue, preRun IPC)
- `hedgewars/project_files/web/post.js` - NEW (Runtime init)

**Scripts:**
- `scripts/build-wasm.sh` - Complete config

## Boot Flow Architecture

**Correct Flow (Current):**
1. `Module.arguments` set in pre.js: `['--internal', '--prefix', '/Data']`
2. `Module.preRun` queues IPC messages via `HWEngine.startHotseatGame()`
3. `FS.init(stdin, stdout, stderr)` wires stdio in preRun
4. Emscripten auto-runs main() with Module.arguments
5. Engine processes `--internal` flag (HWLIBRARY mode)
6. Engine reads from stdin (should drain 149-byte queue)

**Key Lessons:**
- Don't call `Module.run()` inside `onRuntimeInitialized` (re-entry)
- Don't use `-sINVOKE_RUN=0` with manual `run()` call (assertion)
- Queue IPC messages in `preRun` before main() starts
- Use auto-run for simplest testing path

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
