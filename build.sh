#!/usr/bin/env bash
set -e

echo "[1/3] Cleaning old artifacts..."
rm -rf build wiff/usr/bin/wiff wiff.deb

echo "[2/3] Building binary with CMake..."
mkdir build
cd build
cmake ..
cmake --build .
cd ..

echo "[3/3] Building .deb..."
dpkg-deb --build ./wiff

echo "✔ Done: wiff.deb created"