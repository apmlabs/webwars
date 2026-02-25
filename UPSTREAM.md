# Upstream Tracking

## Source
- **Repo**: https://github.com/hedgewars/hw
- **Base commit**: `1bbc396d3` — "Fix erroneous initialization of net game scheme"
- **Remote**: `git remote add upstream https://github.com/hedgewars/hw.git`
- **Last synced**: 2026-02-25 (Rust server + protocol crate updated to `940b95b70`)

## How to update from upstream

```bash
git fetch upstream

# See what changed upstream since our base:
git log --oneline 1bbc396d3..upstream/master

# For files we DON'T modify (server, assets, etc) — just overwrite:
git checkout upstream/master -- rust/hedgewars-server/ rust/hedgewars-network-protocol/

# For files we DO modify (Pascal, CMake) — merge carefully:
git diff upstream/master -- hedgewars/hedgewars/uIO.pas  # check for conflicts first
```

## Files we created (100% ours)

| File | Purpose |
|------|---------|
| `project_files/hwc/ipc_browser.c` | Browser IPC shim replacing SDL_net |
| `project_files/hwc/web_entry.c` | emscripten_set_main_loop wrapper |
| `project_files/hwc/physfs_probe.c` | PhysFS visibility test |
| `project_files/hwc/rtl/gl_emscripten_compat.h` | GL_QUADS → GLES2 mapping |
| `project_files/web/pre.js` | JS message queue, game setup, theme loading |
| `project_files/web/post.js` | Runtime init |
| `rust/lib-hwengine-future/.cargo/config.toml` | Force wasm32-unknown-emscripten target |

## Files we modified (our patches on their code)

All patches use `{$IFDEF EMSCRIPTEN}` / `{$IFNDEF EMSCRIPTEN}` guards where possible.

| File | What we changed |
|------|----------------|
| `CMakeLists.txt` | PhysFS/Lua bundled builds, Rust target override, skip Platform/ |
| `project_files/hwc/CMakeLists.txt` | Emscripten flags, memory, JSPI, linking, exported functions |
| `project_files/hwc/rtl/GL.h` | Include GLES2/gl2.h instead of desktop GL |
| `project_files/hwc/rtl/misc.h` | glShaderSource compat |
| `misc/libphyslayer/CMakeLists.txt` | Remove .bc suffix for Emscripten |
| `misc/libphysfs/CMakeLists.txt` | Modern CMake for Emscripten |
| `misc/liblua/CMakeLists.txt` | Remove lua_emscripten_internal |
| `rust/lib-hwengine-future/Cargo.toml` | Changed crate-type to staticlib |
| `cmake_modules/Platform/Emscripten.cmake` | Renamed to .legacy (conflicts with official toolchain) |
| `hedgewars/hwengine.pas` | Skip freeEverything in WASM, engine exit notification |
| `hedgewars/uIO.pas` | Browser IPC, skip SDL_Delay in WASM, buffer overflow fix |
| `hedgewars/uSound.pas` | Fixed SDL2_mixer bindings (upstream bug), EMSCRIPTEN guards |
| `hedgewars/uStore.pas` | Suppress asset loading spam, guard GL_TEXTURE_PRIORITY |
| `hedgewars/uConsts.pas` | Guard initialization for WASM |
| `hedgewars/uMatrix.pas` | Guard legacy GL calls |
| `hedgewars/uCommands.pas` | IPC logging (debug, can be removed) |
| `hedgewars/uCommandHandlers.pas` | Handler logging (debug, can be removed) |
| `hedgewars/uRender.pas` | Sprite batch system (BatchQuad/FlushBatch), CPU transforms |
| `hedgewars/uTypes.pas` | Exclude CJK font variants in WASM |
| `hedgewars/uVariables.pas` | Exclude CJK font entries in WASM |
| `hedgewars/uUtils.pas` | Skip CJK font check in WASM |
| `hedgewars/uChat.pas` | Skip CJK font references in WASM |
| `hedgewars/SDLh.pas` | Fixed SDL2_mixer declarations (upstream bug) |

## Files we never modify (safe to overwrite from upstream)

- `rust/hedgewars-server/` — Game server (Rust)
- `rust/hedgewars-network-protocol/` — Protocol crate (Rust)
- `gameServer/` — Game server (Haskell, legacy)
- `QTfrontend/` — Desktop client (Qt/C++, we don't use)
- `share/hedgewars/Data/` — All game assets
- `tools/` — Build tools, pas2c
- All other `rust/` crates (mapgen, physics, engine, etc)
