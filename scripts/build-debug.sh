#!/bin/bash

echo "Building the project..."

rm -rf build
west build -p -b chessboard app -DCMAKE_BUILD_TYPE=Debug -DBUILD_UNIT_TESTS=ON -DBUILD_COVERAGE=ON

# If the build fails, exit the script
if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo "Build successful!"
