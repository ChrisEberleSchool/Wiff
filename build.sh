#!/usr/bin/env bash
set -e

echo "[1/2] Cleaning old artifacts..."
rm -rf build wiff/usr/bin/wiff wiff.deb

echo "[2/2] Building binary with CMake..."
mkdir -p build
cd build
cmake ..
cmake --build .
cd ..

OS="$(uname -s)"

if [[ "$OS" == "Linux" ]]; then
  echo "[3/3] Building .deb..."
  dpkg-deb --build ./wiff
  echo "✔ Done: wiff.deb created"
elif [[ "$OS" == "Darwin" ]]; then
  echo "✔ Done: wiff binary built (macOS, skipping .deb)"
else
  echo "⚠ Unsupported OS: $OS"
  exit 1
fi
