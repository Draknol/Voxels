#ifndef WORLD_GENERATOR_H
#define WORLD_GENERATOR_H

#include <game/World.h>

#include <functional>

namespace WorldGenerator {
/// @brief Generates a perlin world using the given settings
/// @param world World to write generated world to
/// @param chunksX Number of chunks wanted in the x direction
/// @param chunksY Number of chunks wanted in the y direction
/// @param chunksZ Number of chunks wanted in the z direction
/// @param amplitude Adjusts the height of the terrain
/// @param frequency Adjusts the bumpyness of the terrain
/// @param octCount Adjusts the detail of the terrain
/// @param waterHeight Sets the water level for the world
/// @param waterColor Sets the color id to use for water
/// @param colorDecider Decides what color to use for a given block
/// @param currentHeight The height of the block being colored
/// @param maxHeight The height of the top block above the current block
/// @param id A hashed number, consistent for a whole column (intended as seed)
void generatePerlin(
    World *world,
    size_t chunksX, size_t chunksY, size_t chunksZ,
    float amplitude, float frequency, size_t octCount,
    size_t waterHeight, uint8_t waterColor,
    std::function<uint8_t(float currentHeight, float maxHeight, uint64_t id)> colorDecider
);
} // namespace WorldGenerator

#endif