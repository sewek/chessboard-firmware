#!/bin/bash

echo "Generating the key..."

BASE_DIR=$(pwd)
IMGTOOL_DIR="${BASE_DIR}/external/bootloader/mcuboot/scripts"
IMGTOOL_PATH="${IMGTOOL_DIR}/imgtool.py"

if ! [ -f "${IMGTOOL_PATH}" ]; then
    echo "The mcuboot submodule is not initialized. Please run the following commands:"
    echo "./scripts/init.sh"
    exit 1
fi

if ! [ -d "${BASE_DIR}/keys" ]; then
    mkdir keys
fi

if [ -f "${BASE_DIR}/keys/root-rsa-2048.pem" ]; then
    echo "The ${BASE_DIR}/keys/root-rsa-2048.pem key already exists."
    echo "If you want to generate a new key, please delete the existing key."
    exit 1
fi

${IMGTOOL_PATH} keygen -t rsa-2048 -k ${BASE_DIR}/keys/root-rsa-2048.pem
${IMGTOOL_PATH} getpub -e pem -k ${BASE_DIR}/keys/root-rsa-2048.pem -o ${BASE_DIR}/keys/root-rsa-2048.pub

# If the build fails, exit the script
if [ $? -ne 0 ]; then
    echo "Failed!"
    exit 1
fi

echo "Successfully generated the key!"
