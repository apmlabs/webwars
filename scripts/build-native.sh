#!/bin/bash
set -e

echo "=== Building Hedgewars (Native Baseline) ==="

if [ ! -d "hedgewars" ]; then
    echo "Error: hedgewars/ not found"
    echo "Run: git clone https://github.com/hedgewars/hw.git hedgewars"
    exit 1
fi

mkdir -p build/native
cd build/native

echo "Configuring..."
cmake ../../hedgewars -DNOSERVER=ON -DCMAKE_BUILD_TYPE=Release

echo "Building..."
make -j$(nproc)

echo "=== Build complete ==="
echo "Binary: build/native/bin/hwengine"
