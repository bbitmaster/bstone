#!/bin/bash
# Serve BStone Emscripten build locally with cache disabled (for development)

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
BUILD_OUTPUT="${REPO_ROOT}/build_emscripten/src/bstone"

if [ ! -f "${BUILD_OUTPUT}/bstone.html" ]; then
    echo "Error: Emscripten build not found: ${BUILD_OUTPUT}"
    echo "Run ./build_emscripten.sh first."
    exit 1
fi

cd "${BUILD_OUTPUT}"

LOCAL_IP=$(ip route get 1 2>/dev/null | awk '{print $7; exit}' || echo "YOUR_IP")

echo "Serving BStone Emscripten build from: $(pwd)"
echo ""
echo "Local:  http://localhost:8000/bstone.html"
echo "LAN:    http://${LOCAL_IP}:8000/bstone.html"
echo ""
echo "Cache disabled - refresh will always load fresh files"
echo "Press Ctrl+C to stop"
echo ""

python3 -c "
from http.server import HTTPServer, SimpleHTTPRequestHandler
class NoCacheHandler(SimpleHTTPRequestHandler):
    def end_headers(self):
        self.send_header('Cache-Control', 'no-store, no-cache, must-revalidate, max-age=0')
        self.send_header('Pragma', 'no-cache')
        self.send_header('Expires', '0')
        super().end_headers()
HTTPServer(('0.0.0.0', 8000), NoCacheHandler).serve_forever()
"
