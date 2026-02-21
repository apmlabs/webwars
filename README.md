# WebWars — Hedgewars in Your Browser

A browser port of [**Hedgewars**](https://hedgewars.org/), the free turn-based artillery game. No downloads, no installs — just open a link and play.

This project is built on top of the [Hedgewars source code](https://github.com/hedgewars/hw) (GPL v2), created by Andrey Korotaev (unc0rr) and the Hedgewars community. We compile their Pascal engine to WebAssembly so it runs natively in the browser. All game assets, Lua scripts, maps, and sounds are theirs — we just made it playable on the web. Huge thanks to the Hedgewars team for building such a great game and releasing it as free software.

**🎮 Play now: [webwars.link](https://webwars.link)**

## Quick Start

**Solo (hotseat):** Open [webwars.link](https://webwars.link) — two teams on one keyboard, taking turns. Right-click to pick a weapon, Space to fire, Arrow keys to move.

**Multiplayer:** Open [webwars.link/lobby.html](https://webwars.link/lobby.html) in two browser tabs:
1. Enter a nickname and click Connect
2. One player creates a room, the other joins it
3. Both players add a team, then the room chief starts the game

## How It Works

Hedgewars is written in Pascal. We compile it to WebAssembly using this pipeline:

```
Pascal → pas2c (Pascal-to-C) → C → Emscripten → WebAssembly
```

The engine runs natively in the browser at 60fps. Multiplayer uses the real Hedgewars server — a WebSocket gateway bridges browsers to the TCP-based server protocol.

```
Browser (WASM engine) ←WebSocket→ Gateway (Node.js) ←TCP→ Hedgewars Server (Haskell)
```

| Component | Tech | Description |
|-----------|------|-------------|
| Game engine | WebAssembly (3.97MB) | Full Hedgewars engine compiled from Pascal via C |
| Game assets | Preloaded .data (187MB) | Graphics, sounds, fonts, maps, Lua scripts |
| WS gateway | Node.js | Bridges browser WebSocket to HW server TCP |
| Game server | Haskell | Official Hedgewars server (rooms, relay, protocol) |

## Building from Source

### Prerequisites

- Linux (tested on Ubuntu 22.04)
- [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html)
- Rust with `wasm32-unknown-emscripten` target
- Node.js 18+
- GHC 9.4+ and Cabal (for the game server)
- CMake 3.20+

### Build & Run

```bash
# 1. Build the WASM engine
source ~/emsdk/emsdk_env.sh
source ~/.cargo/env
mkdir -p build/wasm && cd build/wasm && rm -rf *
cmake ../../hedgewars -DBUILD_ENGINE_JS=ON -DNOSERVER=ON \
  -DCMAKE_TOOLCHAIN_FILE=$EMSDK/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake
make -j$(nproc)
cp ../../web/*.html bin/

# 2. Build the game server
cd ../../hedgewars/gameServer && cabal build

# 3. Run all three services
./bin/hedgewars-server &
cd gateway && npm install && WS_PORT=8080 HW_HOST=localhost HW_PORT=46631 node src/index.js &
cd build/wasm/bin && python3 -m http.server 8081 --bind 0.0.0.0
```

Open http://localhost:8081 in your browser.

## Project Structure

```
webwars/
├── hedgewars/                  # Hedgewars source (forked, with WASM patches)
│   ├── hedgewars/              # Pascal engine source
│   ├── project_files/hwc/      # C shims: IPC bridge, main loop wrapper
│   ├── project_files/web/      # pre.js / post.js (browser integration)
│   └── gameServer/             # Haskell multiplayer server
├── gateway/src/index.js        # WebSocket ↔ TCP bridge
├── web/                        # Browser frontend (lobby, quick play)
└── scripts/                    # Build scripts
```

## Technical Highlights

- **IPC bridge**: Custom C shim (`ipc_browser.c`) replaces SDL_net TCP sockets with JS message queues
- **Main loop**: `emscripten_set_main_loop` via `--wrap` linker flag avoids ASYNCIFY overhead on the hot path
- **Rendering**: Sprite batch system with CPU-side vertex transforms, WebGL2, `GL_STREAM_DRAW` for ANGLE
- **JSPI**: Uses JavaScript Promise Integration instead of ASYNCIFY — 23% smaller WASM binary
- **Multiplayer**: Engine messages are base64-encoded and relayed through the server to other players
- **Background tabs**: `setInterval` fallback at 10Hz keeps game logic running when the tab is hidden
- **Caching**: 187MB asset file cached for 7 days — return visits load instantly

## Known Issues

1. Some theme sprite masks fail to load (visual only, gameplay unaffected)
2. Game exit triggers page reload (SDL teardown not supported in Emscripten)
3. First load downloads ~190MB of game assets (cached after that)

## License

GPL v2 (same as [Hedgewars](https://hedgewars.org/))
