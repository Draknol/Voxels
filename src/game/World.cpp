#include <game/World.h>

void World::addVoxelChunk(uint8_t x, uint8_t y, uint8_t z) {
    chunks.emplace_back(x, y, z);
    chunks.back().buildMesh();
}

void World::addVoxelChunk(const glm::uvec3 &chunkPosition) {
    chunks.emplace_back(chunkPosition);
    chunks.back().buildMesh();
}