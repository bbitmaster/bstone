#!/bin/bash
# Cross-compile BStone for Windows using MinGW-w64

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
BUILD_DIR="${REPO_ROOT}/build_windows"
TOOLCHAIN_FILE="${SCRIPT_DIR}/mingw-w64-toolchain.cmake"

mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"

echo "Configuring Windows cross-compile build..."
cmake "${REPO_ROOT}" \
    -DCMAKE_TOOLCHAIN_FILE="${TOOLCHAIN_FILE}" \
    -DCMAKE_BUILD_TYPE=Release \
    -DBSTONE_INTERNAL_SDL2=OFF \
    -DBSTONE_ENABLE_VULKAN=OFF \
    -DBSTONE_ENABLE_OPENAL=OFF

echo ""
echo "Building..."
cmake --build . -j$(nproc)

# Copy required DLLs next to the executable if build succeeded
if [ -f src/bstone/bstone.exe ]; then
    echo ""
    echo "Copying runtime DLLs..."
    cp /usr/x86_64-w64-mingw32/bin/SDL2.dll src/bstone/
    cp /usr/x86_64-w64-mingw32/bin/libgcc_s_seh-1.dll src/bstone/
    cp /usr/x86_64-w64-mingw32/bin/libstdc++-6.dll src/bstone/
    cp /usr/x86_64-w64-mingw32/bin/libwinpthread-1.dll src/bstone/
    echo ""
    echo "Build complete! Files are in: ${BUILD_DIR}/src/bstone/"
    ls -la src/bstone/*.exe src/bstone/*.dll
    echo ""
    echo "Run with Wine: ./run_wine.sh [data_dir]"
else
    echo ""
    echo "Build failed!"
    exit 1
fi
