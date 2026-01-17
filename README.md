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
![Screenshot of improved terrain](/gallery/Improved%20Terrain.png)

## Features
* Perlin terrain
* Minimal lighting
* Up to 15 materials
* Batch drawing (chunks)
* Depth testing
* Back face culling
* Interior face culling
* MSAA (always on for now)
* Toggleable fullscreen
* Flying movement
* Sprinting
* Camera controls
* Hot reloadable `user-settings.ini`
* `world-settings.ini` for easy world gen adjustments

## Planned
* Blinn-Phong lighting (priority)
* Keybind settings in a .ini