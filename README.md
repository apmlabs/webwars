# WebWars - Hedgewars in Your Browser

Browser port of [Hedgewars](https://hedgewars.org/) using WebAssembly. Play locally (hotseat) or online (WebSocket multiplayer).

## Status

**Phase**: Initial scaffolding complete. See [AGENTS.md](AGENTS.md) for detailed tracking.

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
├── gateway/           # WebSocket gateway
├── web/               # Browser frontend
├── scripts/           # Build scripts
└── docs/              # Documentation
```

## License

GPL v2 (same as Hedgewars)

## Links

- [Hedgewars](https://hedgewars.org/)
- [Hedgewars GitHub](https://github.com/hedgewars/hw)
- [pas2c Docs](https://hedgewars.org/kb/pas2c)
=======
# webwars
Browser port of Hedgewars using WebAssembly - Play with friends online
>>>>>>> f6780b39b2fb356318274a4bc5d2e978b7285c7e
