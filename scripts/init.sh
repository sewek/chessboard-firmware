#!/bin/bash

echo "Initializing the project..."

# Update the submodules
west update

# If the update fails, exit the script
if [ $? -ne 0 ]; then
    echo "Initialization failed!"
    exit 1
fi

# Copy zephyr modified files
mv ./external/zephyr/modules/lvgl/CMakeLists.txt ./external/zephyr/modules/lvgl/_CMakeLists.txt

echo "Initialization finished!"
