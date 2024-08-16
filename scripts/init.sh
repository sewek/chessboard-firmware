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
cp ./app/src/lvgl/lvgl.c ./external/zephyr/modules/lvgl/lvgl.c

echo "Initialization finished!"
