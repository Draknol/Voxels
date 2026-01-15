#ifndef WORLD_GENERATOR_H
#define WORLD_GENERATOR_H

#include <game/World.h>

#include <functional>

namespace WorldGenerator {
/// @brief Generates a perlin world using settings from .ini file
/// @param world World to write generated world to
void generatePerlin(World *world);

uint8_t materialDecider(uint32_t currentHeight, float sampleHeight, uint64_t id, size_t maxChunkY);
} // namespace WorldGenerator

#endif