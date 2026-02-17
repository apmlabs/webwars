# WebWars - Quick Start Guide

**Goal**: Play Hedgewars with friends in the browser

## A) What Works ✅

- **Engine**: Fully compiled to WASM (4.8MB)
- **Assets**: 51MB essential game data packaged
- **Browser**: Engine loads, initializes, and executes
- **Infrastructure**: CORS servers, WebGL context, filesystem
- **Test URL**: http://54.80.204.92:8081/mvp.html

## B) What's Missing ⚠️

- **stdin not wired**: Messages queued but engine can't read them
- **Game setup**: Need correct protocol sequence to start a match
- **Multiplayer**: Need WebSocket gateway + hedgewars-server

## C) Shortest Path to Playable (Hotseat)

**Time**: 2-4 hours

1. **Fix stdin** (30 min)
   - Verify `FS.init(stdin, stdout, stderr)` in preRun works
   - Confirm engine drains message queue
   - Check console for engine responses

2. **Capture real setup sequence** (1 hour)
   - Run desktop Hedgewars
   - Log frontend→engine messages for "Start Local Game"
   - Replay exact byte sequence from JS

3. **Test hotseat** (30 min)
   - Click "Start Game" in browser
   - Verify rendering, physics, input
   - Confirm turn-based gameplay works

## D) Path to "Play with Friends" (Multiplayer)

**Time**: +4-6 hours after hotseat works

1. **Build hedgewars-server** (1 hour)
   - Compile server binary for Linux
   - Run on port 46631

2. **WebSocket Gateway** (2 hours)
   - Node.js relay: WebSocket ↔ TCP
   - Bridge browser to hedgewars-server
   - Handle message framing

3. **Lobby UI** (2 hours)
   - Host/join room
   - Room code or list
   - Start game button

4. **Test multiplayer** (1 hour)
   - Two browsers connect
   - Join same room
   - Play match together

## Current Status

**stdin wiring implemented but needs verification**. The latest build has `FS.init()` in preRun. Next step: reload page and check console to confirm engine reads from queue.

If stdin works → capture desktop protocol sequence  
If stdin broken → debug FS.init() call

## Files to Check

- `hedgewars/project_files/web/pre.js` - stdin/stdout wiring
- `hedgewars/project_files/web/post.js` - Runtime initialization
- `build/wasm/bin/hwengine-mvp.*` - Latest build with stdin

## Quick Commands

```bash
# Rebuild after changes
cd build/wasm
emcc project_files/hwc/CMakeFiles/hwengine.dir/*.o \
  bin/lib*.a \
  -o bin/hwengine-mvp.html \
  --preload-file assets/Data@/Data \
  --pre-js ../../hedgewars/project_files/web/pre.js \
  --post-js ../../hedgewars/project_files/web/post.js \
  -sUSE_SDL=2 -sUSE_SDL_MIXER=2 -sUSE_SDL_IMAGE=2 \
  -sUSE_SDL_TTF=2 -sUSE_SDL_NET=2 \
  -sFORCE_FILESYSTEM=1 \
  -sALLOW_MEMORY_GROWTH=1 \
  -sINITIAL_MEMORY=100007936

# Start CORS servers
cd /home/ubuntu/mcpprojects/webwars
python3 cors-server.py 8080 &  # Test pages
cd build/wasm/bin && python3 ../../../cors-server.py 8000 &  # WASM files
cd ../../web && python3 ../cors-server.py 8081 &  # MVP page
```

## Success Criteria

**Hotseat Working**:
- Game renders in canvas
- Two teams spawn
- Turn-based gameplay
- Weapons work

**Multiplayer Working**:
- Two players connect
- Join same room
- Play together
- Chat works

---

**Next action**: Reload http://54.80.204.92:8081/mvp.html and check console for stdin activity.
