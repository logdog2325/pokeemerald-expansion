#!/usr/bin/env bash
# install_tools.sh - set up everything needed to build and edit Draconid Emerald.
#
#   tools/hack/install_tools.sh               # toolchain + python deps + poryscript
#   tools/hack/install_tools.sh --porytiles   # also build porytiles (slow, ~10 min)
#   tools/hack/install_tools.sh --quiet       # less output (used by the SessionStart hook)
#
# Idempotent: every step is skipped when its result is already present.
# Linux (Debian/Ubuntu) is the supported host; on other systems install the
# equivalents by hand (see INSTALL.md and docs/hack_tools.md).

set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
TOOLS_SRC="${TOOLS_SRC:-$HOME/.cache/draconid-tools}"
PORYSCRIPT_TAG="3.6.1"
# Porytiles develop snapshot 2026-09-05 (v2.0.0+); needs C++23 (clang + libc++ >= 17).
PORYTILES_REF="4c244d587c3daf16447366d0d8398b84a28370fe"

WANT_PORYTILES=0
QUIET=0
for arg in "$@"; do
    case "$arg" in
        --porytiles) WANT_PORYTILES=1 ;;
        --quiet) QUIET=1 ;;
        *) echo "unknown option: $arg" >&2; exit 2 ;;
    esac
done

log() { if [ "$QUIET" = 0 ]; then echo "[install_tools] $*"; fi; }

SUDO=""
if [ "$(id -u)" != 0 ]; then
    if command -v sudo >/dev/null && sudo -n true 2>/dev/null; then SUDO="sudo"; fi
fi

apt_install() {
    if ! command -v apt-get >/dev/null; then
        log "apt-get not available; install manually: $*"
        return 0
    fi
    if [ "$(id -u)" != 0 ] && [ -z "$SUDO" ]; then
        log "no root/sudo; install manually: $*"
        return 0
    fi
    $SUDO apt-get install -y --no-install-recommends "$@" >/dev/null 2>&1 || {
        $SUDO apt-get update >/dev/null 2>&1
        $SUDO apt-get install -y --no-install-recommends "$@" >/dev/null 2>&1
    }
}

# 1. GBA toolchain (INSTALL.md / docs/install/linux/UBUNTU.md)
if ! command -v arm-none-eabi-gcc >/dev/null; then
    log "installing arm-none-eabi toolchain"
    apt_install build-essential binutils-arm-none-eabi gcc-arm-none-eabi libnewlib-arm-none-eabi libpng-dev git python3
fi

# 2. Python packages for tools/hack (Pillow for map previews and art tools)
if ! python3 -c "import PIL" 2>/dev/null; then
    log "installing Pillow"
    python3 -m pip install --quiet pillow 2>/dev/null || python3 -m pip install --quiet --break-system-packages pillow
fi

# 3. Poryscript -> tools/poryscript/poryscript
PORYSCRIPT_BIN="$ROOT/tools/poryscript/poryscript"
if [ ! -x "$PORYSCRIPT_BIN" ] || [ "$("$PORYSCRIPT_BIN" -v 2>/dev/null)" != "$PORYSCRIPT_TAG" ]; then
    log "building poryscript $PORYSCRIPT_TAG"
    if ! command -v go >/dev/null; then apt_install golang-go; fi
    mkdir -p "$TOOLS_SRC"
    if [ ! -d "$TOOLS_SRC/poryscript/.git" ]; then
        git -c advice.detachedHead=false clone --quiet --depth 1 --branch "$PORYSCRIPT_TAG" https://github.com/huderlem/poryscript "$TOOLS_SRC/poryscript"
    fi
    (cd "$TOOLS_SRC/poryscript" && go build -o "$PORYSCRIPT_BIN" .)
fi

# 4. Headless emulator runner (libmgba) -> tools/hack/emu/gbarun, used for screenshot smoke tests
GBARUN_BIN="$ROOT/tools/hack/emu/gbarun"
if [ ! -x "$GBARUN_BIN" ] || [ "$ROOT/tools/hack/emu/gbarun.c" -nt "$GBARUN_BIN" ]; then
    if [ ! -f /usr/include/mgba/core/core.h ]; then apt_install libmgba-dev; fi
    if [ -f /usr/include/mgba/core/core.h ]; then
        log "building gbarun"
        gcc -O2 -Wall -o "$GBARUN_BIN" "$ROOT/tools/hack/emu/gbarun.c" -lmgba -lpng
    else
        log "libmgba-dev missing; skipping tools/hack/emu/gbarun"
    fi
fi

# 5. Porytiles (optional) -> tools/porytiles/porytiles
PORYTILES_BIN="$ROOT/tools/porytiles/porytiles"
if [ "$WANT_PORYTILES" = 1 ] && [ ! -x "$PORYTILES_BIN" ]; then
    log "building porytiles (this takes a while)"
    command -v cmake >/dev/null || apt_install cmake
    command -v clang++ >/dev/null || apt_install clang
    apt_install libc++-dev libc++abi-dev || true
    command -v uv >/dev/null || python3 -m pip install --quiet uv 2>/dev/null || python3 -m pip install --quiet --break-system-packages uv
    uv python install 3.14 >/dev/null 2>&1 || true
    mkdir -p "$TOOLS_SRC"
    if [ ! -d "$TOOLS_SRC/porytiles/.git" ]; then
        git clone --quiet https://github.com/grunt-lucas/porytiles "$TOOLS_SRC/porytiles"
    fi
    (
        cd "$TOOLS_SRC/porytiles"
        git fetch --quiet --depth 1 origin "$PORYTILES_REF" 2>/dev/null || true
        git checkout --quiet "$PORYTILES_REF"
        # The Doxygen docs target is not needed for the CLI.
        sed -i 's/^add_subdirectory(docs)/# add_subdirectory(docs)/' CMakeLists.txt
        cmake -S . -B build-rel -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang >/dev/null
        cmake --build build-rel -j"$(nproc)" --target PorytilesDriver >/dev/null
    )
    mkdir -p "$ROOT/tools/porytiles"
    cp "$(find "$TOOLS_SRC/porytiles/build-rel" -type f -name porytiles -perm -u+x | head -n1)" "$PORYTILES_BIN"
fi

log "done"
