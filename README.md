# WebWars — Hedgewars in Your Browser

A browser port of [**Hedgewars**](https://hedgewars.org/), the free turn-based artillery game. No downloads, no installs — just open a link and play.

This project is built on top of [Hedgewars](https://github.com/hedgewars/hw) (GPL v2), created by Andrey Korotaev (unC0Rr) and the Hedgewars community. The game engine is written in Free Pascal — a language with no native WebAssembly target. What makes this port possible is [**pas2c**](https://github.com/hedgewars/hw/tree/master/tools/pas2c), a Pascal-to-C transpiler written by unC0Rr specifically for the Hedgewars project. pas2c converts the entire engine (~40K lines of Pascal) into C, which we then compile to WebAssembly through Emscripten. Without pas2c, this project simply wouldn't exist — there's no other toolchain that can take a full Pascal game engine to the browser.

The game server is also theirs — a Haskell binary that handles lobby, rooms, and multiplayer relay. All game assets (graphics, sounds, fonts, maps, 117 Lua scripts) are from the Hedgewars project. We wrote the browser integration layer, the WebSocket gateway, and the web frontend — but the game itself is entirely their work. Huge thanks to unC0Rr and the Hedgewars team for building such a great game and releasing it as free software.

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

## What We Built

This isn't just "compile and ship." Hedgewars was designed as a desktop app with a Qt/C++ frontend (~95K lines), TCP socket IPC, and OpenGL rendering. None of that works in a browser. Here's what we had to build or rewrite:

### Web Frontend (replaces Qt desktop client)

The original Hedgewars client is a full Qt desktop application that handles the lobby, room management, team configuration, and game launch. We replaced all of it with a single-page web app (~730 lines). The lobby connects to the real Hedgewars server through our WebSocket gateway, implementing the same text-based protocol the Qt client speaks.

A key design decision: the game engine loads dynamically into the lobby page via `<script>` injection rather than opening a new window. This keeps the WebSocket connection alive during gameplay — engine messages (EM) relay directly through function calls in the same JS context. `window.open()` is blocked by popup blockers in incognito mode, and navigating away would kill the connection.

### Engine Modifications

We patched the Pascal engine source in several places to make it work in a browser:

- **IPC bridge** (`ipc_browser.c`): Replaces SDL_net TCP sockets with a C shim that routes through `EM_JS` calls to a JavaScript message queue. The engine's `IPCCheckSock` reads from JS, and `SendIPCRaw` writes to JS — same interface, completely different transport.

- **Main loop** (`web_entry.c`): The engine's `hwengine_MainLoop` is a blocking `while` loop — fatal in a browser. We intercept it with the `--wrap` linker flag and replace it with `emscripten_set_main_loop` (requestAnimationFrame). A multi-tick catch-up system uses the engine's `cOnlyStats` flag to run game logic at real-time speed while only rendering the final tick per frame.

- **WASM soft-exit** (`hwengine.pas`): SDL teardown (`SDL_Quit`, `SDL_GL_DeleteContext`) crashes Emscripten with `RuntimeError: unreachable`. We skip `freeEverything` in WASM builds entirely — page reload is the only clean reset in a browser.

- **JSPI migration**: Switched from ASYNCIFY (which instruments every function, ~50% overhead) to JavaScript Promise Integration (`-sJSPI`), cutting the WASM binary from 5.15MB to 3.97MB. This required eliminating all JS-frame suspends — `SDL_Delay` in init paths replaced with busy-polling, `SDL_EMSCRIPTEN_ASYNCIFY` hint disabled before engine init.

### Rendering Optimization

The engine's original renderer made one `glDrawArrays` call per sprite — ~200+ draw calls per frame. Through Chrome's ANGLE layer (WebGL → D3D11), each GL call becomes a D3D resource operation. This pushed GPU frame time to 40-55ms (well over the 16ms budget for 60fps).

We added a sprite batch system in `uRender.pas`: a 1024-quad buffer that accumulates vertices and flushes in a single draw call per texture. All sprite functions (`DrawTextureRotatedF`, `DrawHedgehog`, `DrawSpriteRotatedF`, etc.) were converted from matrix-stack transforms to CPU-side vertex math feeding into `BatchQuad`. GPU frame time dropped from 40-55ms to 1-9ms.

### Multiplayer Sync

Hedgewars multiplayer is deterministic — the server doesn't run game logic, it just relays player inputs. Each engine sends its actions as IPC messages, which get base64-encoded and sent as `EM` commands through the server to other players. The receiving engine injects them into its message queue and replays them identically.

The tricky parts: `IPCCheckSock` must run before and between `DoTimer` catch-up ticks (not just after), or incoming messages aren't parsed into the command queue in time and the engine enters lag mode. Background tabs throttle `requestAnimationFrame` to ~1fps, so we fall back to `setInterval` at 10Hz with rendering disabled to keep game logic in sync.

### Other Details

- **OpenGL compat** (`gl_emscripten_compat.h`): Maps desktop GL constants (`GL_QUADS`, `GL_CLAMP`) to GLES2/WebGL2 equivalents
- **Asset caching**: 187MB `.data` file served with 7-day `Cache-Control` — return visits load instantly from disk cache
- **WebGL2 context**: Created in JS with explicit attributes (`antialias:false`, `alpha:false`, `desynchronized:false`) and passed to Emscripten via `GL_PREINITIALIZED_CONTEXT` to prevent SDL from overriding them

## Known Issues

1. Some theme sprite masks fail to load (visual only, gameplay unaffected)
2. Game exit triggers page reload (SDL teardown not supported in Emscripten)
3. First load downloads ~190MB of game assets (cached after that)

## License

GPL v2 (same as [Hedgewars](https://hedgewars.org/))
