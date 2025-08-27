#include <game/World.h>

uint32_t World::makeKey(uint8_t x, uint8_t y, uint8_t z) {
    return ((uint32_t)x << 16) | ((uint32_t)y << 8) | (uint32_t)z;
}

uint32_t World::makeKey(const glm::u8vec3 &chunkPosition) {
    return makeKey(chunkPosition.x, chunkPosition.y, chunkPosition.z);
}

void World::addVoxelChunk(uint8_t x, uint8_t y, uint8_t z) {
    chunks.emplace_back(x, y, z);

    uint32_t key = makeKey(x, y, z);
    if (chunkLocations.count(key)) {
        chunks.erase(chunkLocations.at(key));
    }

    chunkLocations[key] = --chunks.end();
}

void World::addVoxelChunk(const glm::u8vec3 &chunkPosition) {
    addVoxelChunk(chunkPosition.x, chunkPosition.y, chunkPosition.z);
}

void World::changeBlock(uint8_t chunkX, uint8_t chunkY, uint8_t chunkZ, uint8_t voxelX, uint8_t voxelY, uint8_t voxelZ, uint8_t val) {
    chunkLocations.at(makeKey(chunkX, chunkY, chunkZ))->setVoxel(voxelX, voxelY, voxelZ, val);
}

void World::changeBlock(const glm::u8vec3 &chunkPosition, const glm::u8vec3 &voxelPosition, uint8_t val) {
    chunkLocations.at(makeKey(chunkPosition))->setVoxel(voxelPosition, val);
}

void World::buildChunk(uint8_t x, uint8_t y, uint8_t z) {
    chunkLocations.at(makeKey(x, y, z))->buildMesh();
}

void World::buildChunk(const glm::u8vec3 &chunkPosition) {
    chunkLocations.at(makeKey(chunkPosition))->buildMesh();
}