#include <level/WorldGenerator.h>

#include <util/PerlinGenerator.h>

#include <glm/vec2.hpp>

namespace WorldGenerator {
void generatePerlin(
    World *world,
    size_t maxChunkX, size_t maxChunkY, size_t maxChunkZ,
    float amplitude, float frequency, size_t octCount,
    size_t waterHeight, uint8_t waterColor,
    std::function<uint8_t(float currentHeight, float maxHeight, uint64_t id)> colorDecider) {

    for (size_t chunkX = 0u; chunkX < maxChunkX; chunkX++) {
        for (size_t chunkZ = 0u; chunkZ < maxChunkZ; chunkZ++) {

            // Create Chunks
            for (size_t chunkY = 0u; chunkY < maxChunkY; chunkY++) {
                world->addVoxelChunk(chunkX, chunkY, chunkZ);
            }

            // Loop over voxles
            for (size_t voxelX = 0u; voxelX < 16u; voxelX++) {
                for (size_t voxelZ = 0u; voxelZ < 16u; voxelZ++) {
                    // Pick random green
                    uint8_t greenColor = rand() % 2 ? 2 : 10;
                    uint8_t greyColor = 7;

                    // Sample height
                    glm::vec2 position(chunkX * 16.0f + voxelX, chunkZ * 16.0f + voxelZ);
                    float sampleHeight = PerlinGenerator::sample(position, amplitude, frequency, octCount);

                    // Force atleast 1 high
                    sampleHeight = std::max(sampleHeight, 1.0f);

                    // Create ID from x and z
                    uint64_t xLoc = (uint64_t)(chunkX * 16u + voxelX);
                    uint64_t zLoc = (uint64_t)(chunkZ * 16u + voxelZ);
                    uint64_t id = (xLoc << 32u) | zLoc;

                    // Update chunks
                    for (size_t chunkY = 1u; chunkY < maxChunkY; chunkY++) {
                        size_t h = 0u;
                        while (h < std::min(sampleHeight - 1 - (16.0f * chunkY), 16.0f)) {
                            uint32_t currentHeight = h + (16.0f * chunkY);
                            uint8_t color = colorDecider(currentHeight, sampleHeight, id);
                            world->changeBlock(chunkX, chunkY, chunkZ, voxelX, h, voxelZ, color);
                            h++;
                        }
                        while (h < std::min(waterHeight - 1 - (16.0f * chunkY), 16.0f)) {
                            uint32_t currentHeight = h + (16.0f * chunkY);
                            uint8_t color = waterColor;
                            world->changeBlock(chunkX, chunkY, chunkZ, voxelX, h, voxelZ, color);
                            h++;
                        }
                    }
                }
            }

            // Build chunk
            for (size_t chunkY = 0u; chunkY < maxChunkY; chunkY++) {
                world->buildChunk(chunkX, chunkY, chunkZ);
            }
        }
    }
}
} // namespace WorldGenerator
