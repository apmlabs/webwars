# Modifications to Hedgewars Source

This document lists all modifications made to the upstream Hedgewars source for WebAssembly compilation.

## Modified Files (13 files)

### Build System (6 files)

#### 1. `hedgewars/CMakeLists.txt`
- Added Rust toggle for conditional compilation
- Configured PhysFS and Lua as bundled builds
- Skip legacy Platform/Emscripten.cmake for Emscripten builds
- **Why**: Modern Emscripten toolchain compatibility

#### 2. `hedgewars/cmake_modules/Platform/Emscripten.cmake` → `.legacy`
- Renamed to disable legacy Emscripten configuration
- **Why**: Conflicts with official Emscripten toolchain

#### 3. `hedgewars/misc/libphyslayer/CMakeLists.txt`
- Use Emscripten ports for SDL2 (`-sUSE_SDL=2`)
- Remove `.bc` suffix from output
- **Why**: Modern Emscripten doesn't use .bc files

#### 4. `hedgewars/misc/libphysfs/CMakeLists.txt`
- Modern CMake target-based linking
- **Why**: Compatibility with bundled build

#### 5. `hedgewars/misc/liblua/CMakeLists.txt`
- Removed `lua_emscripten_internal` override
- **Why**: Caused linking conflicts

#### 6. `hedgewars/project_files/hwc/CMakeLists.txt`
- Added Emscripten flags: `-sINVOKE_RUN=0`, `-sEXPORTED_RUNTIME_METHODS=['callMain']`
- Memory alignment: `-sINITIAL_MEMORY=100007936`
- SDL_NET support: `-sUSE_SDL_NET=2`
- Enabled HWLIBRARY flag for `--internal` mode
- Added `--pre-js` and `--post-js` for browser integration
- **Why**: Core WASM build configuration

### Source Code (2 files)

#### 7. `hedgewars/hedgewars/uConsts.pas`
- Guard initialization section
- **Why**: pas2c compatibility

#### 8. `hedgewars/hedgewars/uMatrix.pas`
- Guard legacy GL test code
- **Why**: WebGL compatibility

### Runtime Headers (3 files)

#### 9. `hedgewars/project_files/hwc/rtl/GL.h`
- Changed to GLES2/gl2.h headers
- **Why**: WebGL2 uses GLES2 API

#### 10. `hedgewars/project_files/hwc/rtl/misc.h`
- Added `fpcrtl_glShaderSource` declaration
- **Why**: WebGL shader compilation

#### 11. `hedgewars/project_files/hwc/rtl/gl_emscripten_compat.h` ⭐ NEW
- Desktop GL constants compatibility layer
- Maps GL_QUADS, GL_POLYGON, etc. to WebGL equivalents
- **Why**: Bridge desktop OpenGL to WebGL2

### Browser Integration (2 files)

#### 12. `hedgewars/project_files/web/pre.js` ⭐ NEW
- Module configuration and setup
- Command-line arguments: `['--internal', '--prefix', '/Data']`
- stdin/stdout/stderr wiring via `FS.init()`
- Message queue system for IPC protocol
- **Why**: Browser-to-engine communication

#### 13. `hedgewars/project_files/web/post.js` ⭐ NEW
- Runtime initialization handler
- Boot flow with `Module.callMain()`
- Double-start guard
- IPC message queueing
- **Why**: Proper engine startup in browser

### Rust Integration (1 file)

#### 14. `hedgewars/rust/lib-hwengine-future/Cargo.toml`
- Changed crate-type to `["staticlib"]`
- **Why**: Link Rust code into WASM binary

## New Files (2 files)

- `project_files/hwc/rtl/gl_emscripten_compat.h` - OpenGL compatibility layer
- `rust/lib-hwengine-future/Cargo.lock` - Rust dependency lock (auto-generated)

## Key Technical Decisions

1. **pas2c → Emscripten**: Use proven Pascal-to-C-to-WASM pipeline
2. **Official Toolchain**: Disable legacy Platform/Emscripten.cmake
3. **Bundled Dependencies**: Build PhysFS and Lua from source
4. **SDL via Ports**: Use Emscripten's `-sUSE_SDL=2` instead of system SDL
5. **WebGL2/GLES2**: Full compatibility layer for desktop GL
6. **IPC Protocol**: Message queue for stdin/stdout communication
7. **callMain Boot**: Proper argument parsing via `Module.callMain()`

## Testing Modifications

To verify all modifications are present:

```bash
cd hedgewars/
git diff 1bbc396d3 --name-only | sort
```

Should show all 13 modified files listed above.
