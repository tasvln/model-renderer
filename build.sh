#!/bin/bash

# Run CMake and make
echo "Configuring project with CMake..."
cmake . || { echo "CMake configuration failed!"; exit 1; }

echo "Creating executable file..."
make || { echo "Build failed!"; exit 1; }
