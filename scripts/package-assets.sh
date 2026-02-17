#!/bin/bash
set -e

echo "=== Packaging Essential Assets for WebWars ==="

# Create minimal Data directory
ASSET_DIR="build/wasm/assets/Data"
rm -rf build/wasm/assets
mkdir -p "$ASSET_DIR"

SOURCE_DATA="hedgewars/share/hedgewars/Data"

# Copy essential files
echo "Copying essential assets..."

# Graphics (required)
cp -r "$SOURCE_DATA/Graphics" "$ASSET_DIR/"

# One theme (Nature - smallest)
mkdir -p "$ASSET_DIR/Themes"
cp -r "$SOURCE_DATA/Themes/Nature" "$ASSET_DIR/Themes/" 2>/dev/null || echo "Nature theme not found, using first available"
cp -r "$SOURCE_DATA/Themes/$(ls $SOURCE_DATA/Themes | head -1)" "$ASSET_DIR/Themes/" 2>/dev/null || true

# Fonts (required)
cp -r "$SOURCE_DATA/Fonts" "$ASSET_DIR/"

# Sounds (minimal)
mkdir -p "$ASSET_DIR/Sounds"
cp -r "$SOURCE_DATA/Sounds/voices" "$ASSET_DIR/Sounds/" 2>/dev/null || true

# Scripts (required for game logic)
cp -r "$SOURCE_DATA/Scripts" "$ASSET_DIR/"

# Shaders (required for rendering)
cp -r "$SOURCE_DATA/Shaders" "$ASSET_DIR/"

# Config files
cp "$SOURCE_DATA"/*.yaml "$ASSET_DIR/" 2>/dev/null || true
cp "$SOURCE_DATA"/*.toml "$ASSET_DIR/" 2>/dev/null || true

# One map
mkdir -p "$ASSET_DIR/Maps"
cp -r "$SOURCE_DATA/Maps/$(ls $SOURCE_DATA/Maps | head -1)" "$ASSET_DIR/Maps/" 2>/dev/null || true

echo "Asset package size:"
du -sh "$ASSET_DIR"

echo "✅ Assets packaged to build/wasm/assets/"
