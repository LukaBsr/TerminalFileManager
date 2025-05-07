#!/bin/bash

echo ">> Script lancé !"

set -e

# Cleanup function to delete the build directory
cleanup() {
    echo ">> Suppression du répertoire build..."
    rm -rf build
}
trap cleanup EXIT

# Create the build directory and generate the build files
echo ">> Génération du build..."
mkdir -p build
cd build
cmake ..
make

# Copy the binary to the root directory
echo ">> Copie du binaire à la racine..."
cp fman ../

# Return to the root directory and delete the build directory
cd ..
cleanup
echo ">> Script terminé !"
