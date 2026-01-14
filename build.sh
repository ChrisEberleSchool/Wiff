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

# Build directory
rm -rf build
mkdir build
cd build

# Build the project
cmake .. -DPROJECT_VERSION="$WIFF_VERSION"
cmake --build . -- -j$(nproc || echo 2)

# Package appropriately
case "$BUILD_OS" in
  linux)
    cpack -G DEB
    ;;
  macos)
    cpack -G TGZ
    ;;
  windows)
    cpack -G ZIP
    ;;
esac

echo "Build and package complete for $BUILD_OS"
