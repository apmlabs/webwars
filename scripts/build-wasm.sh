#!/bin/bash
set -e

echo "=== Building Hedgewars for WebAssembly ==="

if ! command -v emcc &> /dev/null; then
    echo "Error: Emscripten not found"
    echo "Run: source ~/emsdk/emsdk_env.sh"
    exit 1
fi

if [ ! -d "hedgewars" ]; then
    echo "Error: hedgewars/ not found"
    exit 1
fi

mkdir -p build/wasm
cd build/wasm

echo "=== TOOLCHAIN SANITY CHECK ==="
emcmake cmake ../../hedgewars \
    -DCMAKE_C_COMPILER=emcc \
    -DCMAKE_CXX_COMPILER=em++ \
    -DNOSERVER=ON \
    -DNOVIDEOREC=ON \
    -DBUILD_ENGINE_C=ON \
    -DBUILD_ENGINE_JS=ON \
    -DLUA_SYSTEM=OFF \
    -DPHYSFS_SYSTEM=OFF \
    -DHW_USE_RUST_MAPGEN=ON \
    -DRust_CARGO_TARGET=wasm32-unknown-emscripten \
    -DCMAKE_BUILD_TYPE=Release

echo ""
echo "=== TOOLCHAIN VERIFICATION ==="
echo "C Compiler:   $(grep '^CMAKE_C_COMPILER:' CMakeCache.txt | cut -d= -f2)"
echo "CXX Compiler: $(grep '^CMAKE_CXX_COMPILER:' CMakeCache.txt | cut -d= -f2)"
echo "AR:           $(grep '^CMAKE_AR:' CMakeCache.txt | cut -d= -f2)"
echo "RANLIB:       $(grep '^CMAKE_RANLIB:' CMakeCache.txt | cut -d= -f2)"
echo "Rust Target:  $(grep '^Rust_CARGO_TARGET:' CMakeCache.txt | cut -d= -f2)"
echo ""

if grep -q '/usr/bin/clang\|/usr/bin/gcc' CMakeCache.txt | grep -E 'CMAKE_C_COMPILER:|CMAKE_CXX_COMPILER:'; then
    echo "❌ TOOLCHAIN FAILURE: System compiler detected!"
    grep -E 'CMAKE_C_COMPILER:|CMAKE_CXX_COMPILER:' CMakeCache.txt
    exit 1
fi

if ! grep -q 'emcc' CMakeCache.txt || ! grep -q 'em++' CMakeCache.txt; then
    echo "❌ TOOLCHAIN FAILURE: emcc/em++ not detected!"
    exit 1
fi

echo "✅ Emscripten toolchain verified"
echo ""

echo ""
echo "=== BUILDING (VERBOSE) ==="
cmake --build . --verbose

echo "=== WASM build complete ==="
ls -lh bin/*.{wasm,js,data} 2>/dev/null || echo "Check build/wasm/bin/ for output"
