# WebWars - Hedgewars in Your Browser

Browser port of [Hedgewars](https://hedgewars.org/) using WebAssembly. Play locally (hotseat) or online (WebSocket multiplayer).

## Status

**Game Loop Running** - Engine runs complete gameplay sessions in the browser.

### What Works
- ✅ Engine compiles to WebAssembly (4.2MB)
- ✅ All assets load (187MB data file)
- ✅ SDL2, OpenGL, shaders initialize
- ✅ IPC protocol working (bidirectional)
- ✅ Map loading (Cake map with spawn zones)
- ✅ Hedgehogs spawn successfully
- ✅ Game loop runs (360+ ticks)
- ✅ Win detection and sound playback
- 🟡 Rendering not yet verified on canvas
- ❌ Cleanup crashes on shutdown

### Live Demo
http://54.80.204.92:8081/hwengine.html

Open browser console to see engine output.

## How It Works

```
Pascal Source → pas2c → C Code → Emscripten → WebAssembly
                                                    ↓
Browser ← JavaScript Glue ← IPC Shim ← Engine (WASM)
```

The engine communicates via a custom IPC protocol:
1. **pre.js** queues game commands (seed, teams, hedgehogs)
2. **ipc_browser.c** replaces SDL_net with browser-friendly EM_JS calls
3. **uIO.pas** reads IPC using `{$IFDEF EMSCRIPTEN}` conditional compilation

## Quick Start

```bash
# Prerequisites: emsdk, Rust with wasm32-unknown-emscripten target

# Build
source ~/emsdk/emsdk_env.sh
source ~/.cargo/env
cd build/wasm && rm -rf *
cmake ../../hedgewars -DBUILD_ENGINE_JS=ON -DNOSERVER=ON \
  -DCMAKE_TOOLCHAIN_FILE=$EMSDK/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake
make -j$(nproc)

# Serve
cd bin && python3 -m http.server 8081
# Open http://localhost:8081/hwengine.html
```

## Output Files
| File | Size | Description |
|------|------|-------------|
| hwengine.html | 22KB | Loader page |
| hwengine.js | 470KB | JavaScript glue |
| hwengine.wasm | 4.2MB | Game engine |
| hwengine.data | 187MB | Assets (graphics, fonts, shaders, maps, sounds) |

## Build Time
- Configuration: ~10 seconds
- Full build: ~3 minutes (clean)
- Incremental: ~30 seconds

## Known Issues
1. Data file path warning (non-fatal)
2. SDL vsync incompatibility with Emscripten main loop
3. RuntimeError during shutdown
4. 5000+ console lines from debug mode
5. Canvas rendering not yet confirmed

## License

GPL v2 (same as Hedgewars)

## Links
- [Hedgewars](https://hedgewars.org/)
- [Hedgewars GitHub](https://github.com/hedgewars/hw)
