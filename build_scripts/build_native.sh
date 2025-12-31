#!/bin/bash
# Build native Linux binary for BStone

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
BUILD_DIR="${REPO_ROOT}/build_native"

mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"

echo "Configuring native build..."
cmake "${REPO_ROOT}" -DCMAKE_BUILD_TYPE=Release

echo ""
echo "Building..."
cmake --build . --target bstone -j$(nproc)

if [ $? -eq 0 ]; then
    echo ""
    echo "Build successful!"
    echo "Binary: ${BUILD_DIR}/src/bstone/bstone"
    echo "Run with: ./run_native.sh [data_dir]"
else
    echo ""
    echo "Build failed!"
    exit 1
fi
