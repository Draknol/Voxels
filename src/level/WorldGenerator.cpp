#include <level/WorldGenerator.h>

#include <util/Settings.h>
#include <util/Random.h>
#include <util/PerlinSampler.h>
#include <util/HeightMapSampler.h>

#include <glm/vec2.hpp>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace {
void generate(World *world, const char *imagePath) {
    size_t maxChunkX = Settings::getXChunks();
    size_t maxChunkY = Settings::getYChunks();
    size_t maxChunkZ = Settings::getZChunks();
    size_t bottomTrim = Settings::getBottomTrim();
    size_t topTrim = Settings::getTopTrim();
    size_t chunkSize = Settings::CHUNK_SIZE;
    size_t worldHeight = chunkSize * maxChunkY;

    float amplitude = Settings::getAmplitude();
    float frequency = Settings::getFrequency();
    float octCount = Settings::getOctCount();

    int x,y,c;
    unsigned char* image = nullptr;
    
    if (imagePath) {
        printf(imagePath);
        image = stbi_load(imagePath, &x, &y, &c, 0);
        if (!image) std::cout << "WARNING::WORLD_GENERATOR::PERLIN_FALLBACK";
    }

    for (size_t chunkX = 0u; chunkX < maxChunkX; chunkX++) {
        for (size_t chunkZ = 0u; chunkZ < maxChunkZ; chunkZ++) {

            // Create Chunks
            for (size_t chunkY = bottomTrim; chunkY < maxChunkY - topTrim; chunkY++) {
                world->addVoxelChunk(chunkX, chunkY, chunkZ);
            }

            // Loop over voxles
            for (size_t voxelX = 0u; voxelX < chunkSize; voxelX++) {
                for (size_t voxelZ = 0u; voxelZ < chunkSize; voxelZ++) {
                    // Sample height
                    glm::vec2 position(chunkX * chunkSize + voxelX, chunkZ * chunkSize + voxelZ);

                    float sampleHeight;
                    if (imagePath) {
                        sampleHeight = HeightMapSampler::sample(position, amplitude, image, x, y);
                    }
                    else {
                       sampleHeight = PerlinSampler::sample(position, amplitude, frequency, octCount);
                    }

                    // Force atleast 1 high
                    sampleHeight = std::max(sampleHeight, 1.0f);

                    // Create ID from x and z
                    uint64_t xLoc = (uint64_t)(chunkX * chunkSize + voxelX);
                    uint64_t zLoc = (uint64_t)(chunkZ * chunkSize + voxelZ);
                    uint64_t id = (xLoc << 32u) | zLoc;

                    // Update chunks
                    for (uint8_t materialID = 15u; materialID > 0u; materialID--) {
                        const Material &material = Settings::getMaterial(materialID);

                        if (material.name == "default") {
                            continue;
                        }

                        size_t offset = material.offset;
                        size_t isBound = material.isBound;
                        size_t depth = Random::inRange(material.minDepth, material.maxDepth);

                        size_t bottomHeight = 0u;
                        size_t topHeight = 0u;

                        switch (material.fillDirection) {
                        case FillDirection::BOTTOM_UP:
                            bottomHeight = offset;
                            topHeight = bottomHeight + depth;
                            break;
                        case FillDirection::TOP_DOWN:
                            topHeight = worldHeight - offset;
                            bottomHeight = topHeight - depth;
                            break;
                        case FillDirection::SURFACE_UP:
                            bottomHeight = (size_t)sampleHeight + offset;
                            topHeight = bottomHeight + depth;
                            break;
                        case FillDirection::SURFACE_DOWN:
                            topHeight = (size_t)sampleHeight - offset;
                            bottomHeight = topHeight - depth;
                            break;
                        default:
                            break;
                        }

                        for (size_t chunkY = bottomTrim; chunkY < maxChunkY - topTrim; chunkY++) {
                            for (size_t h = 0u; h < chunkSize; h++) {
                                uint32_t currentHeight = h + (chunkSize * chunkY);
                                if (currentHeight >= bottomHeight && currentHeight <= topHeight) {
                                    if (!isBound || currentHeight <= sampleHeight) {
                                        size_t totalHeight = chunkY * chunkSize + h;
                                        if (totalHeight > material.maxHeight || totalHeight < material.minHeight) continue;
                                        world->addBlock(chunkX, chunkY, chunkZ, voxelX, h, voxelZ, materialID);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // Build chunk
            for (size_t chunkY = bottomTrim; chunkY < maxChunkY - topTrim; chunkY++) {
                world->buildChunk(chunkX, chunkY, chunkZ);
            }
        }
    }
}
}

namespace WorldGenerator {
void fromPerlin(World *world) {
    generate(world, nullptr);
}

void fromHeightMap(World *world) {
    const char *image_path = Settings::getHeightMapPath();
    generate(world, image_path);
}
} // namespace WorldGenerator