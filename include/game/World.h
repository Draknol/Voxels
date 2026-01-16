#ifndef WORLD_H
#define WORLD_H

#include <render/VoxelChunk.h>

#include <list>
#include <unordered_map>

class World {
private:
    std::unordered_map<uint32_t, std::list<VoxelChunk>::iterator> chunkLocations;

    std::list<VoxelChunk> chunks;

    uint32_t makeKey(uint8_t x, uint8_t y, uint8_t z);
    uint32_t makeKey(const glm::u8vec3 &chunkPosition);

public:
    void addVoxelChunk(uint8_t x, uint8_t y, uint8_t z);
    void addVoxelChunk(const glm::u8vec3 &chunkPosition);

    void changeBlock(uint8_t chunkX, uint8_t chunkY, uint8_t chunkZ, uint8_t voxelX, uint8_t voxelY, uint8_t voxelZ, uint8_t val);
    void changeBlock(const glm::u8vec3 &chunkPosition, const glm::u8vec3 &voxelPosition, uint8_t val);

    void addBlock(uint8_t chunkX, uint8_t chunkY, uint8_t chunkZ, uint8_t voxelX, uint8_t voxelY, uint8_t voxelZ, uint8_t val);
    void addBlock(const glm::u8vec3 &chunkPosition, const glm::u8vec3 &voxelPosition, uint8_t val);

    void buildChunk(uint8_t x, uint8_t y, uint8_t z);
    void buildChunk(const glm::u8vec3 &chunkPosition);

    std::list<VoxelChunk>::const_iterator begin() const { return chunks.begin(); }
    std::list<VoxelChunk>::const_iterator end() const { return chunks.end(); }
};

#endif