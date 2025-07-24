# Voxels
A project for learning voxels in OpenGL.

## Install instructions
1. Install [CMake](https://cmake.org/download) (3.15 or later)
2. Install [vcpkg](https://github.com/microsoft/vcpkg) (2021.05 or later)
3. Clone the repository: `git clone https://github.com/Draknol/Voxels`
4. From root, run: `cmake -B build -S . cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=[vcpkg-path]/scripts/buildsystems/vcpkg.cmake`
5. To build: `cmake --build build --config release`

## Features
* Hot reloadable settings in a .ini

## Planned
* Keybind settings in a .ini