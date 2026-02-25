#!/bin/bash
# Package game data into core.data + individual asset files for dynamic loading
set -e

PROJECT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
DATA_DIR="$PROJECT_DIR/hedgewars/share/hedgewars/Data"
OUT_DIR="$PROJECT_DIR/build/wasm/bin"
FP="$HOME/emsdk/upstream/emscripten/tools/file_packager.py"

echo "=== Building core.data ==="

PRELOAD=()

# Core graphics (top-level PNGs + essential subdirs)
for f in "$DATA_DIR"/Graphics/*.png; do
    bn=$(basename "$f")
    # Escape @ in filenames (file_packager uses @ as src@dst separator, @@ to escape)
    src="${f//@/@@}"
    dst="/Data/Graphics/${bn//@/@@}"
    PRELOAD+=("${src}@${dst}")
done
for sub in Hedgehog AmmoMenu SuddenDeath Buttons; do
    [ -d "$DATA_DIR/Graphics/$sub" ] && PRELOAD+=("$DATA_DIR/Graphics/$sub@/Data/Graphics/$sub")
done

# Shaders, Tiles, Names, misc, Scripts
PRELOAD+=("$DATA_DIR/Shaders@/Data/Shaders")
PRELOAD+=("$DATA_DIR/Tiles@/Data/Tiles")
PRELOAD+=("$DATA_DIR/Names@/Data/Names")
PRELOAD+=("$DATA_DIR/misc@/Data/misc")
PRELOAD+=("$DATA_DIR/Scripts@/Data/Scripts")

# Latin font only
PRELOAD+=("$DATA_DIR/Fonts/DejaVuSans-Bold.ttf@/Data/Fonts/DejaVuSans-Bold.ttf")

# Sound effects (top-level only) + Default voice
for f in "$DATA_DIR"/Sounds/*.ogg; do
    PRELOAD+=("$f@/Data/Sounds/$(basename "$f")")
done
PRELOAD+=("$DATA_DIR/Sounds/voices/Default@/Data/Sounds/voices/Default")

# Nature theme (default fallback)
PRELOAD+=("$DATA_DIR/Themes/Nature@/Data/Themes/Nature")

# English locale + templates
PRELOAD+=("$DATA_DIR/Locale/en.txt@/Data/Locale/en.txt")
PRELOAD+=("$DATA_DIR/map_templates.yaml@/Data/map_templates.yaml")
PRELOAD+=("$DATA_DIR/maze_templates.yaml@/Data/maze_templates.yaml")
PRELOAD+=("$DATA_DIR/wfc_templates.toml@/Data/wfc_templates.toml")

python3 "$FP" "$OUT_DIR/hwengine.data" --preload "${PRELOAD[@]}" \
    --js-output="$OUT_DIR/hwengine-data.js" --lz4

CORE_SIZE=$(stat -c%s "$OUT_DIR/hwengine.data")
echo "core.data: $(awk "BEGIN{printf \"%.1fMB\", $CORE_SIZE/1048576}")"

echo ""
echo "=== Copying assets for dynamic loading ==="
ASSETS="$OUT_DIR/assets"
rm -rf "$ASSETS"

# Music
mkdir -p "$ASSETS/Music"
cp "$DATA_DIR"/Music/*.ogg "$ASSETS/Music/"

# Themes (excl Nature — already in core)
for d in "$DATA_DIR"/Themes/*/; do
    t=$(basename "$d"); [ "$t" = "Nature" ] && continue
    mkdir -p "$ASSETS/Themes/$t" && cp -r "$d"* "$ASSETS/Themes/$t/"
done

# Voice packs (excl Default — already in core)
for d in "$DATA_DIR"/Sounds/voices/*/; do
    v=$(basename "$d"); [ "$v" = "Default" ] && continue
    mkdir -p "$ASSETS/Sounds/voices/$v" && cp -r "$d"* "$ASSETS/Sounds/voices/$v/"
done

# Cosmetics
mkdir -p "$ASSETS/Graphics/Hats" "$ASSETS/Graphics/Flags" "$ASSETS/Graphics/Graves"
cp "$DATA_DIR"/Graphics/Hats/*.png "$ASSETS/Graphics/Hats/" 2>/dev/null || true
cp "$DATA_DIR"/Graphics/Flags/*.png "$ASSETS/Graphics/Flags/" 2>/dev/null || true
cp "$DATA_DIR"/Graphics/Graves/*.png "$ASSETS/Graphics/Graves/" 2>/dev/null || true

# Maps, Forts, Missions
cp -r "$DATA_DIR/Maps" "$ASSETS/"
cp -r "$DATA_DIR/Forts" "$ASSETS/"
cp -r "$DATA_DIR/Missions" "$ASSETS/"

# CJK font + extra locales
mkdir -p "$ASSETS/Fonts" "$ASSETS/Locale"
cp "$DATA_DIR/Fonts/wqy-zenhei.ttc" "$ASSETS/Fonts/" 2>/dev/null || true
for f in "$DATA_DIR"/Locale/*.txt; do
    [ "$(basename "$f")" = "en.txt" ] && continue
    cp "$f" "$ASSETS/Locale/"
done

echo "Music: $(du -sh "$ASSETS/Music" | cut -f1)"
echo "Themes: $(du -sh "$ASSETS/Themes" | cut -f1)"
echo "Voices: $(du -sh "$ASSETS/Sounds/voices" | cut -f1)"
echo "Maps: $(du -sh "$ASSETS/Maps" | cut -f1)"
echo "Forts: $(du -sh "$ASSETS/Forts" | cut -f1)"
echo "Cosmetics: $(du -sh "$ASSETS/Graphics" | cut -f1)"
echo ""
echo "=== Done ==="
echo "core.data: $(awk "BEGIN{printf \"%.1fMB\", $CORE_SIZE/1048576}")"
echo "assets/: $(du -sh "$ASSETS" | cut -f1)"
