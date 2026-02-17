# WebWars - Hedgewars in Your Browser

Browser port of [Hedgewars](https://hedgewars.org/) using WebAssembly. Play locally (hotseat) or online (WebSocket multiplayer).

## Status

**Build Complete: 100%** 🎉

The game engine has been successfully compiled to WebAssembly!

### Output Files
- ✅ `hwengine.html` - 22KB (loader page)
- ✅ `hwengine.js` - 464KB (JavaScript glue code)
- ✅ `hwengine.wasm` - 4.1MB (game engine)
- ✅ `hwengine.wasm.map` - 1.9MB (debug symbols)

### What Works
- ✅ Emscripten toolchain (emcc/em++)
- ✅ Rust wasm32-unknown-emscripten target
- ✅ pas2c: 60+ Pascal files → C
- ✅ OpenGL → WebGL2 compatibility layer
- ✅ All libraries built (Lua, PhysFS, SDL2, SDL_NET)
- ✅ All engine code compiled
- ✅ Final linking successful

### Next Steps
- Package game assets (~30-40MB essential)
- Test in browser
- Deploy MVP

## Architecture

```
Pascal → pas2c → C → Emscripten → WASM → Browser
Browser ⇄ WebSocket Gateway ⇄ hedgewars-server (TCP)
```

## Quick Start

```bash
# Clone Hedgewars
git clone https://github.com/hedgewars/hw.git hedgewars

# Build baseline
./scripts/build-native.sh

# Build with pas2c
./scripts/build-pas2c.sh

# Build WASM (requires Emscripten)
source ~/emsdk/emsdk_env.sh
./scripts/build-wasm.sh
```

## Project Structure

```
webwars/
├── AGENTS.md          # Status tracking
├── AmazonQ.md         # AI context
├── README.md          # This file
├── hedgewars/         # Cloned source
├── build/             # Build outputs
│   └── wasm/
│       └── bin/
│           ├── hwengine.html
│           ├── hwengine.js
│           └── hwengine.wasm
├── gateway/           # WebSocket gateway
├── web/               # Browser frontend
├── scripts/           # Build scripts
└── docs/              # Documentation
```

## Technical Highlights

- **pas2c → Emscripten**: Proven compilation path
- **WebGL2**: Full GLES2 compatibility layer
- **Rust Integration**: wasm32-unknown-emscripten staticlib
- **SDL2**: Via Emscripten ports (no native dependencies)
- **Assets**: 218MB total, ~30-40MB essential bundle

## Build Time

- **Configuration**: ~10 seconds
- **Full build**: ~3 minutes (clean)
- **Incremental**: ~30 seconds

## License

GPL v2 (same as Hedgewars)

## Links

- [Hedgewars](https://hedgewars.org/)
- [Hedgewars GitHub](https://github.com/hedgewars/hw)
- [pas2c Docs](https://hedgewars.org/kb/pas2c)
