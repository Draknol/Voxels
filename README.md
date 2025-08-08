# Voxels
A project for learning voxels in OpenGL.
Currently able to render voxels one at a time with keyboard and mouse controls.

## Install instructions
1. Install [CMake](https://cmake.org/download) (3.15 or later)
2. Install [vcpkg](https://github.com/microsoft/vcpkg) (2021.05 or later)
3. Clone the repository: `git clone https://github.com/Draknol/Voxels`
4. From root, run: `cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=[vcpkg-path]/scripts/buildsystems/vcpkg.cmake`
5. To build: `cmake --build build --config release`

## Features
* Minimal voxel rendering (position and color)
* Batch drawing (chunks)
* Color palettes
* Depth testing
* Back face culling
* Interior face culling
* 2D movement
* Camera controls
* Hot reloadable settings & color palettes in `.ini`s

## Planned
* Fullscreen toggle on F11
* MSAA
* Jumping / flying
* Keybind settings in a .ini