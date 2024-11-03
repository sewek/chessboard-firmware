#!/bin/bash

echo "Running test..."

cd build

case "$OSTYPE" in
  linux*)   make coverage -j $(grep -c ^processor /proc/cpuinfo) ;;
  darwin*)  make coverage -j $(sysctl -n hw.ncpu) ;;
  *)        make coverage ;;
esac

cp chess_logic/coverage.xml ../coverage.xml

# If the build fails, exit the script
if [ $? -ne 0 ]; then
    echo "Run failed!"
    exit 1
fi

echo "Runned successful!"
