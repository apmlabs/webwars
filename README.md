# WebWars — Hedgewars in Your Browser

Play [Hedgewars](https://hedgewars.org/) directly in your browser. No downloads, no installs — just open a link and play.

The full game engine is compiled to WebAssembly. Multiplayer works via WebSocket through the official Hedgewars server protocol.

## Play Now

**Multiplayer lobby**: https://webwars.link/lobby.html

1. Open the link in two browser tabs (or two different browsers/devices)
2. Enter a nickname and click Connect
3. One player creates a room, the other joins it
4. Both players add a team, then the room chief starts the game

**Solo (hotseat)**: https://webwars.link/hwengine.html — two teams on one keyboard, taking turns.

## How It Works

Hedgewars is written in Pascal. We compile it to WebAssembly using this pipeline:

```
Pascal → pas2c (Pascal-to-C) → C → Emscripten → WebAssembly
```

The engine runs natively in the browser at 60fps. Multiplayer uses the real Hedgewars server — a WebSocket gateway bridges browsers to the TCP-based server protocol.

```
Browser (WASM engine) ←WebSocket→ Gateway (Node.js) ←TCP→ Hedgewars Server (Haskell)
```

### Architecture

| Component | Tech | Port | Description |
|-----------|------|------|-------------|
| Game engine | WASM (3.97MB) | — | Full Hedgewars engine in the browser |
| Game assets | .data file (187MB) | — | Graphics, sounds, fonts, maps, shaders |
| HTTP server | Python | 8081 | Serves WASM, assets, and lobby page |
| WS gateway | Node.js | 8080 | Bridges browser WebSocket to HW server TCP |
| HW server | Haskell | 46631 | Official Hedgewars server (rooms, relay, protocol) |

## Building from Source

### Prerequisites

- Linux (tested on Ubuntu 22.04)
- [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html) (emsdk)
- Rust with `wasm32-unknown-emscripten` target
- Node.js (for the WebSocket gateway)
- GHC + Cabal (to build the Hedgewars server)
- CMake, make

### Build the WASM Engine

```bash
# Set up toolchains
source ~/emsdk/emsdk_env.sh
source ~/.cargo/env

# Clean build
cd build/wasm && rm -rf *
cmake ../../hedgewars -DBUILD_ENGINE_JS=ON -DNOSERVER=ON \
  -DCMAKE_TOOLCHAIN_FILE=$EMSDK/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake
make -j$(nproc)

# Copy lobby page into build output
cp ../../web/lobby.html bin/lobby.html
```

Incremental rebuilds after code changes:
```bash
source ~/emsdk/emsdk_env.sh
cd build/wasm && make -j$(nproc)
```

Build time: ~3 minutes clean, ~30 seconds incremental.

### Build the Hedgewars Server

```bash
cd hedgewars/gameServer
cabal build
cp $(cabal list-bin hedgewars-server) ../../bin/hedgewars-server
```

### Run Everything

Three services need to be running:

```bash
# 1. Hedgewars server (TCP game server)
./bin/hedgewars-server

# 2. WebSocket gateway (browser ↔ server bridge)
cd gateway && npm install && WS_PORT=8080 HW_HOST=localhost HW_PORT=46631 node src/index.js

# 3. HTTP server (serves WASM + lobby)
cd build/wasm/bin && python3 -m http.server 8081 --bind 0.0.0.0
```

Then open http://localhost:8081/lobby.html in your browser.

### Systemd Services (Production)

For persistent deployment, create systemd services. See the existing configs:
```bash
cat /etc/systemd/system/hedgewars-server.service
cat /etc/systemd/system/webwars-gateway.service
cat /etc/systemd/system/webwars-server.service
```

Manage with:
```bash
sudo systemctl start hedgewars-server webwars-gateway webwars-server
sudo systemctl status hedgewars-server webwars-gateway webwars-server
sudo journalctl -u webwars-gateway -f  # View gateway logs
```

## Project Structure

```
webwars/
├── hedgewars/              # Hedgewars source (forked from github.com/hedgewars/hw)
│   ├── hedgewars/          # Pascal engine source (modified for WASM)
│   ├── project_files/hwc/  # WASM-specific C shims and build config
│   ├── project_files/web/  # pre.js / post.js (browser integration)
│   ├── gameServer/         # Haskell server source
│   └── ...
├── gateway/                # WebSocket ↔ TCP bridge (Node.js)
│   └── src/index.js
├── web/                    # Browser frontend
│   └── lobby.html          # Multiplayer lobby UI
├── build/wasm/bin/         # Build output (WASM, JS, assets)
├── scripts/                # Build automation scripts
├── AGENTS.md               # Technical architecture & lessons learned
├── AmazonQ.md              # Development session history & status
└── README.md               # This file
```

## Key Technical Details

- **Base commit**: Hedgewars `1bbc396d3` with WASM patches applied directly
- **IPC**: Custom browser shim (`ipc_browser.c`) replaces SDL_net TCP sockets with JS message queues
- **Main loop**: Uses `emscripten_set_main_loop` via `--wrap=hwengine_MainLoop` to avoid ASYNCIFY overhead
- **Rendering**: Sprite batch system with CPU-side transforms, WebGL2, GL_STREAM_DRAW for ANGLE
- **Multiplayer**: Engine messages (EM) are base64-encoded and relayed through the server to other players
- **Background tabs**: `setInterval` fallback at 10Hz keeps game logic running when tab is hidden

## Known Issues

1. Some theme sprite masks fail to load (visual only, gameplay unaffected)
2. Game exit triggers page reload (WASM soft-exit — SDL teardown not supported in Emscripten)
3. Data file path warning on load (non-fatal)

## License

GPL v2 (same as [Hedgewars](https://hedgewars.org/))
