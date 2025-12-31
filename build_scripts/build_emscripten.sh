#!/bin/bash
# Build BStone for WebAssembly/Emscripten

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
BUILD_DIR="${REPO_ROOT}/build_emscripten"

# Get data directory from argument or environment variable
DATA_DIR="${1:-${BSTONE_DATA_DIR}}"

if [ -z "${DATA_DIR}" ]; then
    echo "Error: Game data directory not specified."
    echo ""
    echo "Usage: $0 <data_dir>"
    echo "   or: BSTONE_DATA_DIR=/path/to/data $0"
    echo ""
    echo "The data directory should contain Blake Stone WAD files."
    exit 1
fi

if [ ! -d "${DATA_DIR}" ]; then
    echo "Error: Data directory does not exist: ${DATA_DIR}"
    exit 1
fi

# Check if emcmake is available
if ! command -v emcmake &> /dev/null; then
    echo "Error: emcmake not found. Please install and activate Emscripten SDK."
    echo "See: https://emscripten.org/docs/getting_started/downloads.html"
    exit 1
fi

mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"

echo "Configuring Emscripten build..."
echo "Data directory: ${DATA_DIR}"
emcmake cmake "${REPO_ROOT}" \
    -DBSTONE_EMSCRIPTEN_ASSERTIONS=ON \
    -DBSTONE_INTERNAL_SDL2=ON \
    -DBSTONE_ENABLE_VULKAN=OFF \
    -DBSTONE_ENABLE_OPENAL=OFF \
    -DBSTONE_TESTS=OFF \
    -DBSTONE_EMSCRIPTEN_PRELOAD_DIR="${DATA_DIR}" \
    -DBSTONE_EMSCRIPTEN_PRELOAD_MOUNT=/data \
    -DCMAKE_BUILD_TYPE=Release

echo ""
echo "Building..."
emmake make -j$(nproc)

if [ $? -eq 0 ]; then
    echo ""
    echo "Build successful!"
    echo "Output: ${BUILD_DIR}/src/bstone/"
    echo "  - bstone.html"
    echo "  - bstone.js"
    echo "  - bstone.wasm"
    echo "  - bstone.data"
    echo ""
    echo "Host with: ./host_emscripten.sh"
else
    echo ""
    echo "Build failed!"
    exit 1
fi
