#!/bin/bash

echo "Building the test..."

rm -rf build
cmake -B build -S lib -DCMAKE_BUILD_TYPE=Debug -DBUILD_UNIT_TESTS=ON -DBUILD_COVERAGE=ON

case "$OSTYPE" in
  linux*)   cmake --build build -j $(grep -c ^processor /proc/cpuinfo) ;;
  darwin*)  cmake --build build -j $(sysctl -n hw.ncpu) ;;
  *)        cmake --build build ;;
esac


# If the build fails, exit the script
if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo "Build successful!"
