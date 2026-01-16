#ifndef WORLD_GENERATOR_H
#define WORLD_GENERATOR_H

#include <game/World.h>

#include <functional>

namespace WorldGenerator {
/// @brief Generates a perlin world using settings from .ini file
/// @param world World to write generated world to
void generatePerlin(World *world);
} // namespace WorldGenerator

#endif