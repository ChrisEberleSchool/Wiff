#!/usr/bin/env bash
set -e

# Detect OS
BUILD_OS="unknown"
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    BUILD_OS="linux"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    BUILD_OS="macos"
elif [[ "$OS" == "Windows_NT" ]]; then
    BUILD_OS="windows"
fi

echo "Detected OS: $BUILD_OS"

# Strip leading 'v' if present
CMAKE_VERSION="${WIFF_VERSION#v}"
CMAKE_VERSION="${CMAKE_VERSION:-1.0.0}"

echo "Using CMake project version: $CMAKE_VERSION"

# Build directory
rm -rf build
mkdir build
cd build

# Configure (EXPORT compile_commands.json for clangd)
cmake .. \
    -DPROJECT_VERSION="$CMAKE_VERSION" \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Build
cmake --build . -- -j$(nproc 2>/dev/null || echo 2)

# Symlink compile_commands.json to project root for clangd
if [[ -f compile_commands.json ]]; then
    ln -sf "$(pwd)/compile_commands.json" ../compile_commands.json
    echo "compile_commands.json linked to project root"
fi

# GTesting
ctest --verbose

# Package only if Linux
if [[ "$BUILD_OS" == "linux" ]]; then
    cpack -G DEB
else
    echo "Skipping .deb package: not on Linux"
fi
