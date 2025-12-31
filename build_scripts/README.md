# BStone Build Scripts

Helper scripts for building BStone on Linux. These scripts were tested on **Arch-based CachyOS**.

## Game Data Directory

All scripts that need game data support the `BSTONE_DATA_DIR` environment variable:

```bash
export BSTONE_DATA_DIR=/path/to/your/game/data
./run_native.sh
```

Or pass it as the first argument:

```bash
./run_native.sh /path/to/your/game/data
```

The game data directory should contain the Blake Stone WAD files (e.g., `AUDIOHED.BS6`, `MAPHEAD.BS6`, etc.).

## Scripts

| Script | Description |
|--------|-------------|
| `build_native.sh` | Build native Linux binary |
| `build_windows.sh` | Cross-compile Windows 64-bit binary |
| `build_emscripten.sh` | Build WebAssembly/Emscripten version |
| `run_native.sh` | Run the native Linux build |
| `run_wine.sh` | Run the Windows build under Wine |
| `host_emscripten.sh` | Serve the Emscripten build locally |

## Dependencies

### Arch Linux / CachyOS (tested)

**Native build:**
```bash
sudo pacman -S base-devel cmake sdl2
```

**Windows cross-compile:**
```bash
sudo pacman -S mingw-w64-toolchain
yay -S mingw-w64-sdl2  # From AUR
```

**Emscripten build:**
```bash
sudo pacman -S emscripten
```

**Running Windows build under Wine:**
```bash
sudo pacman -S wine
```

### Ubuntu 24.04 (untested)

**Native build:**
```bash
sudo apt install build-essential cmake libsdl2-dev
```

**Windows cross-compile:**
```bash
sudo apt install mingw-w64 cmake
# SDL2 for MinGW may need to be downloaded manually from libsdl.org
# or built from source with the MinGW toolchain
```

**Emscripten build:**
```bash
# Install Emscripten SDK from https://emscripten.org/docs/getting_started/downloads.html
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
```

**Running Windows build under Wine:**
```bash
sudo apt install wine64
```

## Build Output Locations

| Build Type | Output Directory |
|------------|------------------|
| Native | `build_native/src/bstone/bstone` |
| Windows | `build_windows/src/bstone/bstone.exe` + DLLs |
| Emscripten | `build_emscripten/src/bstone/bstone.html` + .js/.wasm/.data |

## Notes

- The Windows build requires MinGW-w64 SDL2 development libraries
- The Emscripten build embeds game data into the .data file at build time
- All builds are Release builds by default
- Build directories are created inside the repository root (sibling to `src/`)
