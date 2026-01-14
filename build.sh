#!/usr/bin/env bash
set -e

echo "[1/3] Cleaning old artifacts..."
rm -rf build *.deb

echo "[2/3] Building project with CMake..."
mkdir -p build
cd build
cmake ..
cmake --build . -- -j$(nproc)
cd ..

OS="$(uname -s)"

if [[ "$OS" == "Linux" ]]; then
  echo "[3/3] Creating .deb package with CPack..."
  cd build
  cpack -G DEB
  cd ..
  echo "✔ Done: .deb package created"
elif [[ "$OS" == "Darwin" ]]; then
  echo "✔ Done: wiff binary built (macOS, skipping .deb)"
else
  echo "⚠ Unsupported OS: $OS"
  exit 1
fi
