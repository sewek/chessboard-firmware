#!/bin/bash

echo "Running test..."

./build/chess_logic/tests --reporter junit -o test-results.xml

# If the build fails, exit the script
if [ $? -ne 0 ]; then
    echo "Run failed!"
    exit 1
fi

echo "Runned successful!"
