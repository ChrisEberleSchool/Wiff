set -e

echo "[1/2] Cleaning old artifacts..."
rm -rf build wiff/usr/bin/wiff wiff.deb

echo "[2/2] Building binary with CMake..."
mkdir -p build
cd build
cmake ..
cmake --build .
cd ..

# Building depending on OS
# TODO:: create exe for win and macOS
if [[ "$PLATFORM" == "linux" ]]; then
    echo "[3/3] Building .deb..."
    dpkg-deb --build ./wiff
    echo "✔ Done: wiff.deb created"
else
    echo "✔ Done: wiff binary built (macOS, skipping .deb)"
fi

