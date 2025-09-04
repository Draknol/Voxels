# Voxels
The start of a Voxel game.
Currently able to render basic terrain and fly around with keyboard and mouse controls.

## Install instructions
1. Install [CMake](https://cmake.org/download) (3.15 or later)
2. Install [vcpkg](https://github.com/microsoft/vcpkg) (2021.05 or later)
3. Clone the repository: `git clone https://github.com/Draknol/Voxels`
4. From root, run: `cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=[vcpkg-path]/scripts/buildsystems/vcpkg.cmake`
5. To build: `cmake --build build --config release`

## Gallery
![Screenshot of a voxel chunk](/gallery/Voxel%20Chunk.png)

## Features
* Minimal voxel rendering (position and color)
* Voxels can be added / removed manually
* Placeholder perlin terrain
* Batch drawing (chunks)
* Color palettes
* Depth testing
* Back face culling
* Interior face culling
* MSAA (always on for now)
* Toggleable fullscreen
* Flying movement
* Sprinting
* Camera controls
* Hot reloadable settings & color palettes in `.ini`s

## Planned
* Keybind settings in a .ini
* Move world gen into World
* Improve terrain detail (octaves)