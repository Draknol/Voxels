#ifndef WORLD_H
#define WORLD_H

#include <render/VoxelChunk.h>

#include <list>

class World {
private:
    std::list<VoxelChunk> chunks;

public:
    void addVoxelChunk(uint8_t x, uint8_t y, uint8_t z);
    void addVoxelChunk(const glm::uvec3 &chunkPosition);

    std::list<VoxelChunk>::const_iterator begin() const { return chunks.begin(); }
    std::list<VoxelChunk>::const_iterator end() const { return chunks.end(); }
};

#endif