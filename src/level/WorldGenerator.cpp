#include <level/WorldGenerator.h>

#include <util/Settings.h>
#include <util/Random.h>
#include <util/PerlinGenerator.h>

#include <glm/vec2.hpp>

namespace WorldGenerator {
void generatePerlin(World *world) {
    size_t maxChunkX = Settings::getXChunks();
    size_t maxChunkY = Settings::getYChunks();
    size_t maxChunkZ = Settings::getZChunks();
    size_t chunkSize = Settings::CHUNK_SIZE;
    size_t worldHeight = chunkSize * maxChunkY;

    float amplitude = Settings::getAmplitude();
    float frequency = Settings::getFrequency();
    float octCount = Settings::getOctCount();

    for (size_t chunkX = 0u; chunkX < maxChunkX; chunkX++) {
        for (size_t chunkZ = 0u; chunkZ < maxChunkZ; chunkZ++) {

            // Create Chunks
            for (size_t chunkY = 0u; chunkY < maxChunkY; chunkY++) {
                world->addVoxelChunk(chunkX, chunkY, chunkZ);
            }

            // Loop over voxles
            for (size_t voxelX = 0u; voxelX < chunkSize; voxelX++) {
                for (size_t voxelZ = 0u; voxelZ < chunkSize; voxelZ++) {
                    // Pick random green
                    uint8_t greenColor = rand() % 2 ? 2 : 10;
                    uint8_t greyColor = 7;

                    // Sample height
                    glm::vec2 position(chunkX * chunkSize + voxelX, chunkZ * chunkSize + voxelZ);
                    float sampleHeight = PerlinGenerator::sample(position, amplitude, frequency, octCount);

                    // Force atleast 1 high
                    sampleHeight = std::max(sampleHeight, 1.0f);

                    // Create ID from x and z
                    uint64_t xLoc = (uint64_t)(chunkX * chunkSize + voxelX);
                    uint64_t zLoc = (uint64_t)(chunkZ * chunkSize + voxelZ);
                    uint64_t id = (xLoc << 32u) | zLoc;

                    // Update chunks
                    for (size_t chunkY = 1u; chunkY < maxChunkY; chunkY++) {
                        ;
                        for (size_t h = 0u; h < chunkSize; h++) {
                            uint32_t currentHeight = h + (chunkSize * chunkY);
                            uint8_t color = materialDecider(currentHeight, sampleHeight, id, worldHeight);
                            if (color != 0u) {
                                world->changeBlock(chunkX, chunkY, chunkZ, voxelX, h, voxelZ, color);
                            }
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

uint8_t materialDecider(uint32_t currentHeight, float sampleHeight, uint64_t id, size_t worldHeight) {
    // Use first valid material
    for (size_t i = 15; i > 0; i--) {
        const Material &material = Settings::getMaterial(i);
        uint32_t depth = Random::inRangeHash(material.minDepth, material.maxDepth, id + i);

        if (material.isBound && currentHeight > sampleHeight) {
            continue;
        }

        switch (material.fillDirection) {
        case FillDirection::BOTTOM_UP:
            if (currentHeight >= material.offset && currentHeight <= material.offset + depth) {
                return i;
            }
            break;
        case FillDirection::TOP_DOWN:
            if (currentHeight >= worldHeight - material.offset - depth && currentHeight <= worldHeight - material.offset) {
                return i;
            }
            break;
        case FillDirection::SURFACE_UP:
            if (currentHeight <= (uint32_t)sampleHeight + material.offset + depth) {
                return i;
            }
            break;
        case FillDirection::SURfACE_DOWN:
            if (currentHeight >= (uint32_t)sampleHeight - material.offset - depth) {
                return i;
            }
            break;
        default:
            break;
        }
    }

    return 0;
}
} // namespace WorldGenerator
