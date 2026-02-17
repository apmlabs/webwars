# Amazon Q - WebWars Context

**Last Updated**: 2026-02-17T16:00:00Z  
**Working Directory**: `/home/ubuntu/mcpprojects/webwars/`  
**Status**: 🎉 IPC Transport Working - Engine reads from JS!

## Project: WebWars (Hedgewars WASM Port)

Browser port of Hedgewars using pas2c → Emscripten pipeline with WebSocket multiplayer.

## Current Phase: IPC Protocol Handshake

### Breakthrough Achieved! 🎉
- ✅ Engine compiled to WebAssembly (4.1MB)
- ✅ SDL_net removed, browser IPC shim created
- ✅ Pascal conditionals working with `-d EMSCRIPTEN`
- ✅ Engine reads 149 bytes from JS callback
- 🟡 **Current**: Engine waiting for IPC reply (blocking)

### The Journey (Step by Step)

#### Phase 1: WASM Compilation (Complete)
1. Set up Emscripten SDK 5.0.1
2. Configured Rust wasm32-unknown-emscripten target
3. Fixed GL headers (GLES2/gl2.h)
4. Built all dependencies (Lua, PhysFS, SDL2)
5. Generated C from Pascal via pas2c (60+ files)
6. Created OpenGL compatibility layer
7. **Result**: hwengine.wasm (4.1MB) successfully built

#### Phase 2: Asset Loading (Complete)
8. Packaged 51MB essential assets (Graphics, Shaders, Fonts)
9. Used `--preload-file` with LZ4 compression
10. Removed `--use-preload-plugins` (caused browser audio limits)
11. **Result**: Assets load cleanly in browser

#### Phase 3: Boot Flow (Complete)
12. Tried `callMain()` - doesn't exist in Emscripten output
13. Tried `Module.run()` - caused re-entry assertion
14. **Solution**: Auto-run with `Module.arguments`
15. Created web_entry.c wrapper with static argv
16. **Result**: Engine starts and initializes SDL

#### Phase 4: IPC Transport (Complete) ✅
17. **Problem**: Engine hardcoded to use TCP sockets (SDL_net)
18. **Solution Path A**: Remove SDL_net, create browser shim
19. Added `-d EMSCRIPTEN` to pas2c flags in CMakeLists.txt
20. Patched uIO.pas with `{$IFDEF EMSCRIPTEN}` conditionals
21. Created ipc_browser.c with SDL_net stubs + `hw_ipc_recv()`
22. Implemented `Module.HWEngine.readIPC()` in pre.js
23. Exported HEAPU8 to EXPORTED_RUNTIME_METHODS
24. **Result**: Engine reads all 149 bytes from JS queue! 🎉

#### Phase 5: IPC Protocol (In Progress) 🟡
25. Engine successfully reads: seed, teams, hedgehogs, start command
26. **Current blocker**: Engine stuck in `SendIPCAndWaitReply()`
27. **Next**: Implement reply mechanism or complete protocol sequence

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
