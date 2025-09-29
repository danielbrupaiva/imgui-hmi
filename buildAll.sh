#!/bin/bash
set -e
# Detect and set up the default Conan profile
#conan profile detect --force
# Conan install command with specified profiles and output folder
conan install . --build=missing --output-folder=output/x86_64/Debug --profile:build=profiles/debug_x86_64 --profile:host=profiles/debug_x86_64
cmake -B output/x86_64/Debug -S .   -G "Ninja"  -DCMAKE_TOOLCHAIN_FILE=output/x86_64/Debug/conan_toolchain.cmake  -DCMAKE_BUILD_TYPE=Debug
cmake --build output/x86_64/Debug --parallel
## Conan install command with specified profiles and output folder
conan install . --build=missing --output-folder=output/x86_64/Release --profile:build=profiles/release_x86_64 --profile:host=profiles/release_x86_64
cmake -B output/x86_64/Release -S .   -G "Ninja"  -DCMAKE_TOOLCHAIN_FILE=output/x86_64/Release/conan_toolchain.cmake  -DCMAKE_BUILD_TYPE=Release
cmake --build output/x86_64/Release --parallel
## Conan install command for aarch64-beagleplay target
#conan install . --build=missing --output-folder=output/aarch64-beagleplay/Debug --profile:build=profiles/release_x86_64 --profile:host=profiles/aarch64-beagleplay
#cmake -B output/target/Debug -S .   -G "Ninja"   -DCMAKE_TOOLCHAIN_FILE=cmake/beagleplay.cmake   -DCMAKE_BUILD_TYPE=Debug
#cmake --build output/target/Debug --parallel
