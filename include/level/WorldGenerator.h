#ifndef WORLD_GENERATOR_H
#define WORLD_GENERATOR_H

#include <game/World.h>

#include <functional>

namespace WorldGenerator {
/// @brief Generates a perlin world using settings from .ini file
/// @param world World to write generated world to
void fromPerlin(World *world);

/// @brief Read a world from a height map using settings from .ini file
/// @param world World to write generated world to
void fromHeightMap(World *world);
} // namespace WorldGenerator

#endif