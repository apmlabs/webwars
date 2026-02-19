# WebWars - Hedgewars in Your Browser

Browser port of [Hedgewars](https://hedgewars.org/) using WebAssembly. Play locally (hotseat) or online (WebSocket multiplayer).

## Status

**Game Renders & Runs Fast** - Engine runs in the browser with sprite batching (GPU time 1-9ms).

### What Works
- ✅ Engine compiles to WebAssembly (3.97MB with JSPI)
- ✅ All assets load (187MB data file)
- ✅ SDL2, OpenGL, shaders initialize
- ✅ IPC protocol working (bidirectional)
- ✅ Map loading with theme textures (sky, water, clouds, sprites)
- ✅ Hedgehogs spawn successfully
- ✅ Game loop runs (360+ ticks)
- ✅ Win detection and sound playback
- ✅ Rendering works on canvas
- ✅ Sprite batch system — GPU time down 80-95% (38-45ms → 1-9ms)
- ✅ JSPI (no ASYNCIFY overhead on main loop)
- ✅ Correct rotation and rendering — no flicker
- ✅ Full game plays to completion (allOK=1)
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
| hwengine.wasm | 5.2MB | Game engine |
| hwengine.data | 187MB | Assets (graphics, fonts, shaders, maps, sounds) |

## Build Time
- Configuration: ~10 seconds
- Full build: ~3 minutes (clean)
- Incremental: ~30 seconds

## Known Issues
1. Data file path warning (non-fatal)
2. RuntimeError during shutdown
3. Some theme sprite masks fail to load (flags 44)

## License

GPL v2 (same as Hedgewars)

## Links
- [Hedgewars](https://hedgewars.org/)
- [Hedgewars GitHub](https://github.com/hedgewars/hw)
