#!/bin/bash

echo "Building the project..."

rm -rf build
west build -p -b chessboard app -t partition_manager_report -DBOARD_ROOT=$(pwd) -DCMAKE_BUILD_TYPE=Release

# If the build fails, exit the script
if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo "Build successful!"
