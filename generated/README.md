# Generated C Source (pas2c output)

These files are the C output of [pas2c](https://github.com/hedgewars/hw/tree/master/tools/pas2c), which converts the Hedgewars Pascal engine into C. They are checked in for reference — the build system regenerates them automatically.

## Files

- `pas2c/*.c` — 62 C source files (~70K lines) converted from the Pascal engine
- `pas2c/*.h` — 64 corresponding headers

## How they're generated

During `cmake` configure, the `pas2c` tool (a Haskell binary in `hedgewars/tools/pas2c/`) converts every `.pas` file in `hedgewars/hedgewars/` into C. The output lands in `build/wasm/project_files/hwc/`. These are then compiled by Emscripten (`emcc`) into WebAssembly.

## Build dependencies

To compile the generated C to WASM, you need:

- [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html) (provides `emcc`, SDL2, SDL_net via ports)
- Rust with `wasm32-unknown-emscripten` target (for the map generator)
- CMake 3.20+

The C code depends on:
- **SDL2** — windowing, input, audio (via Emscripten ports: `-sUSE_SDL=2`)
- **SDL_net** — stubbed out for browser builds (replaced by `ipc_browser.c`)
- **PhysFS** — virtual filesystem (bundled in `hedgewars/misc/libphysfs/`)
- **Lua 5.1** — game scripting (bundled in `hedgewars/misc/liblua/`)
- **FreeType** — font rendering (via Emscripten ports)
- **libpng, zlib, libogg, libvorbis** — assets (via Emscripten ports)

See the main [README](../README.md) for full build instructions.
