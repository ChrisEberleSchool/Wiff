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
cmake .. -DPROJECT_VERSION="${WIFF_VERSION:-1.0.0}"

# Use nproc on Linux, fallback to 2 cores otherwise
cmake --build . -- -j$(nproc 2>/dev/null || echo 2)

# Package only if Linux
if [[ "$BUILD_OS" == "linux" ]]; then
    cpack -G DEB
else
    echo "Skipping .deb package: not on Linux"
fi