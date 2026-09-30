#!/bin/bash
# SessionStart hook: make the Draconid Emerald build + tools work in Claude Code on the web.
# Installs the GBA toolchain, Pillow and Poryscript (see tools/hack/install_tools.sh).
# Porytiles is slow to build and only needed for custom tilesets:
#   tools/hack/install_tools.sh --porytiles
set -euo pipefail

if [ "${CLAUDE_CODE_REMOTE:-}" != "true" ]; then
    exit 0
fi

cd "${CLAUDE_PROJECT_DIR:-$(dirname "$0")/../..}"
tools/hack/install_tools.sh --quiet
