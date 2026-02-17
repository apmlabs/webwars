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

echo "Configuring with Emscripten..."
emcmake cmake ../../hedgewars \
    -DNOSERVER=ON \
    -DBUILD_ENGINE_C=ON \
    -DCMAKE_BUILD_TYPE=Release

echo "Building..."
emmake make -j$(nproc)

echo "=== WASM build complete ==="
ls -lh bin/*.{wasm,js,data} 2>/dev/null || echo "Check build/wasm/bin/ for output"
