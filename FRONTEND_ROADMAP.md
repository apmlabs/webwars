# WebWars - Frontend Integration Roadmap

## Current Achievement: Engine Running in Browser! 🎉

**Date**: 2026-02-17  
**Status**: Engine compiles, loads, and executes successfully  
**Test URL**: http://54.80.204.92:8081/mvp.html

### What Works

✅ **Complete WASM Build Pipeline**
- Pascal → pas2c → C → Emscripten → WASM
- All 60+ source files compiled
- All dependencies resolved (Lua, PhysFS, SDL2, Rust)
- 4.8MB engine + 51MB assets

✅ **Browser Integration**
- Engine loads and initializes
- WebGL context created
- Assets unpack successfully
- CORS-enabled serving
- Message queue system implemented

✅ **Engine Execution**
- `_hwengine_RunEngine()` callable
- Engine responds with error messages
- Confirms: "You must specify a demo file"
- Command-line argument parsing works

### What's Needed: Frontend/Protocol Layer

The engine is **waiting for game configuration**. Hedgewars engine is designed to be controlled by a frontend that sends it setup messages.

## Implementation Options

### Option 1: Demo File Playback (Fastest - 1-2 hours)

**Goal**: Watch a recorded game play back in browser

**Steps**:
1. Get a `.hwd` demo/replay file from desktop Hedgewars
2. Add to assets: `--preload-file demos/game.hwd@/game.hwd`
3. Set arguments: `Module.arguments = ['--prefix', '/Data', '/game.hwd']`
4. Engine will play the replay automatically

**Pros**:
- Fastest path to seeing gameplay
- Proves rendering, physics, audio work
- No protocol implementation needed

**Cons**:
- Can't create new games
- Limited interactivity

**Files to modify**:
- `hedgewars/project_files/web/pre.js` - Add demo file argument
- Rebuild with demo file packaged

---

### Option 2: IPC Protocol Implementation (Proper - 4-8 hours)

**Goal**: Send game setup messages to start a new match

**Protocol Overview**:
- Length-prefixed binary messages: `[length_byte][payload...]`
- Max payload: 254 bytes
- Commands documented in Hedgewars Knowledge Base

**Required Messages** (minimum for hotseat):
```
eseed {random_seed}           # Map generation seed
e$template_filter 0           # Map template
e$mapgen 0                    # Map generator type
e$maze_size 0                 # Maze size (if applicable)

eaddteam <hash> <color> Name  # Add team
eaddhh <level> <health> Name  # Add hedgehog to team

# Repeat for second team

?                             # Start game
```

**Implementation**:
1. Research exact message format from HWKB or source
2. Implement message framing in JavaScript
3. Wire stdin to feed messages to engine
4. Wire stdout to capture engine responses
5. Create minimal UI to trigger game start

**Pros**:
- Can create new games
- Full control over game setup
- Foundation for complete frontend

**Cons**:
- Requires protocol research
- More complex implementation
- Need to handle engine responses

**Files to modify**:
- `hedgewars/project_files/web/pre.js` - Enhance message queue
- `hedgewars/project_files/web/post.js` - Wire stdin/stdout properly
- Create `web/protocol.js` - Protocol implementation
- Create `web/game-setup.js` - Game configuration logic

---

### Option 3: Full Web Frontend (Complete - 1-2 days)

**Goal**: Complete browser-based Hedgewars experience

**Components**:
1. **Game Setup UI**
   - Map selection
   - Team configuration
   - Hedgehog customization
   - Game scheme selection

2. **In-Game UI**
   - Weapon selection
   - Turn timer
   - Team health display
   - Chat (for multiplayer)

3. **Protocol Handler**
   - Bidirectional message handling
   - State synchronization
   - Error handling

4. **Input Mapping**
   - Keyboard controls
   - Mouse/touch controls
   - Weapon selection

**Pros**:
- Complete game experience
- Ready for multiplayer
- Production-ready

**Cons**:
- Significant development time
- Requires UI/UX design
- Complex state management

---

## Recommended Path

### Phase 1: Demo Playback (Now)
Get a demo file and prove the engine works end-to-end.

### Phase 2: Minimal Protocol (Next)
Implement basic IPC to start a simple hotseat game.

### Phase 3: Full Frontend (Later)
Build complete UI for production deployment.

---

## Technical Notes

### Message Queue System (Already Implemented)

```javascript
// In pre.js
var HWEngine = {
    messageQueue: [],
    sendMessage: function(msg) {
        // Adds length-prefixed message to queue
    },
    readByte: function() {
        // Returns next byte for engine stdin
    }
};
```

### Current Arguments

```javascript
Module.arguments = [
    '--prefix', '/Data',
    '--user-prefix', '/Data'
];
```

### Engine Functions Available

- `Module._hwengine_RunEngine()` - Main entry point
- `Module._hwengine_MainLoop()` - Main loop (if needed)
- `Module.FS` - Filesystem access

---

## Resources

**Hedgewars Documentation**:
- Engine Protocol: https://hedgewars.org/kb/EngineProtocol
- Demo File Format: https://hedgewars.org/kb/DemoFormat
- Source Code: https://github.com/hedgewars/hw

**Current Build**:
- Repository: https://github.com/apmlabs/webwars
- Test URL: http://54.80.204.92:8081/mvp.html
- Build artifacts: `build/wasm/bin/hwengine-mvp.*`

---

## Success Criteria

**MVP (Demo Playback)**:
- [ ] Demo file loads
- [ ] Game renders in canvas
- [ ] Physics simulation runs
- [ ] Audio plays

**Hotseat Game**:
- [ ] Can start new game
- [ ] Two teams spawn
- [ ] Turn-based gameplay works
- [ ] Weapons fire correctly
- [ ] Win/lose conditions work

**Full Game**:
- [ ] Complete UI
- [ ] All game modes work
- [ ] Multiplayer via WebSocket
- [ ] Deployed and accessible

---

## Next Session Checklist

1. Decide on implementation path (demo vs protocol)
2. If demo: Obtain `.hwd` file and package it
3. If protocol: Research message format and implement
4. Test and iterate
5. Document findings

**Current blocker**: Need either demo file OR protocol implementation  
**Estimated time to playable**: 1-8 hours depending on path chosen
