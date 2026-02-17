# Hedgewars Upstream Source

This project is based on the official Hedgewars source code with modifications for WebAssembly compilation.

## Upstream Repository
- **URL**: https://github.com/hedgewars/hw.git
- **Base Commit**: `1bbc396d3` - "Fix erroneous initialization of net game scheme"
- **Branch**: main (as of 2026-02-17)

## How to Update from Upstream

```bash
cd hedgewars/
git fetch origin
git log HEAD..origin/main  # Review changes
git merge origin/main       # Merge updates (may require conflict resolution)
```

## Our Fork Strategy

We maintain the full Hedgewars source tree with our WASM-specific patches applied directly. This allows us to:
- Track all modifications in version control
- Easily diff against upstream
- Merge upstream updates when needed
- Maintain a complete, buildable codebase

See `MODIFICATIONS.md` for a detailed list of our changes.
