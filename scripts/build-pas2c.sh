#!/bin/bash
set -e

echo "=== Building Hedgewars with pas2c ==="

if [ ! -d "hedgewars" ]; then
    echo "Error: hedgewars/ not found"
    exit 1
fi

mkdir -p build/pas2c
cd build/pas2c

echo "Configuring with pas2c..."
cmake ../../hedgewars -DNOSERVER=ON -DNOVIDEOREC=ON -DBUILD_ENGINE_C=ON -DCMAKE_BUILD_TYPE=Release

echo "Building..."
make -j$(nproc)

echo "=== Build complete ==="
echo "Generated C code: hedgewars/hedgewars/*.c"
echo "Binary: build/pas2c/bin/hwengine"

if [ -d "../../hedgewars/hedgewars" ]; then
    echo ""
    echo "=== C Code Analysis ==="
    find ../../hedgewars/hedgewars -name "*.c" -type f | wc -l | xargs echo "C files:"
    find ../../hedgewars/hedgewars -name "*.c" -exec wc -l {} + 2>/dev/null | tail -1 | awk '{print $1}' | xargs echo "Total lines:"
fi
