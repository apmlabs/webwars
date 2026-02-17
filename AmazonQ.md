# Amazon Q - WebWars Context

**Last Updated**: 2026-02-17T01:04:00Z  
**Working Directory**: `/home/ubuntu/mcpprojects/webwars/`  
**Status**: Scaffolding complete, ready for implementation

## Project: WebWars (Hedgewars WASM Port)

Browser port of Hedgewars using pas2c → Emscripten pipeline with WebSocket multiplayer.

## Current Phase: Validation

### Next Steps
1. Clone Hedgewars: `git clone https://github.com/hedgewars/hw.git hedgewars`
2. Build baseline: `./scripts/build-native.sh`
3. Test pas2c: `./scripts/build-pas2c.sh`
4. Analyze assets: `du -sh hedgewars/share/hedgewars/Data/`

## Key Technical Points

- **Compilation**: Pascal → pas2c → C → Emscripten → WASM
- **Multiplayer**: WebSocket gateway bridges browser to TCP server (port 46631)
- **Assets**: ~100-300MB, need lazy-loading strategy
- **Proven Path**: Hedgewars had working browser build historically

## Build Commands

```bash
# Native baseline
cmake -DNOSERVER=ON ..
make

# pas2c (generates C code)
cmake -DNOSERVER=ON -DBUILD_ENGINE_C=ON ..
make

# Emscripten (generates WASM)
emcmake cmake -DNOSERVER=ON -DBUILD_ENGINE_C=ON ..
emmake make
```

## WebSocket Gateway (Minimal)

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

**MVP**: Game loads in browser, hotseat playable, <10s load time  
**Full**: Multiplayer stable, deployed on this server, public URL
