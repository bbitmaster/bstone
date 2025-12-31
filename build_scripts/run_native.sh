#!/bin/bash
# Run native Linux build of BStone

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
BINARY="${REPO_ROOT}/build_native/src/bstone/bstone"

# Get data directory from argument or environment variable
DATA_DIR="${1:-${BSTONE_DATA_DIR}}"
shift 2>/dev/null || true  # Remove first arg if it was data dir

if [ ! -f "${BINARY}" ]; then
    echo "Error: Binary not found: ${BINARY}"
    echo "Run ./build_native.sh first."
    exit 1
fi

if [ -z "${DATA_DIR}" ]; then
    echo "Error: Game data directory not specified."
    echo ""
    echo "Usage: $0 <data_dir> [additional args...]"
    echo "   or: BSTONE_DATA_DIR=/path/to/data $0 [additional args...]"
    exit 1
fi

exec "${BINARY}" --data_dir "${DATA_DIR}" "$@"
