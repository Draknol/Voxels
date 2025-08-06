#ifndef VOXEL_CHUNK_H
#define VOXEL_CHUNK_H

#include <glm/vec3.hpp>

#include <render/VoxelVertex.h>
#include <render/Shader.h>

#include <vector>

class VoxelChunk {
private:
    static constexpr size_t CHUNK_SIZE = 16u;
    static constexpr size_t MAX_CHUNK_SIZE = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;
    static constexpr size_t MAX_CHUNK_VERTS = 36u * MAX_CHUNK_SIZE;

    glm::uvec3 chunkOffset;

    uint8_t *chunk = new uint8_t[MAX_CHUNK_SIZE];

    unsigned int vao;
    unsigned int vbo;
    size_t vboCapacity = 0;
    size_t vertCount = 0;

    static constexpr glm::u8vec3 cubeVerts[8] = {
        {0u, 0u, 0u},
        {0u, 0u, 1u},
        {0u, 1u, 0u},
        {0u, 1u, 1u},
        {1u, 0u, 0u},
        {1u, 0u, 1u},
        {1u, 1u, 0u},
        {1u, 1u, 1u},
    };

    static constexpr uint32_t faceIndices[6][6] = {
        {0b011u, 0b010u, 0b001u, 0b000u, 0b001u, 0b010u}, // -X
        {0b101u, 0b110u, 0b111u, 0b110u, 0b101u, 0b100u}, // +X
        {0b001u, 0b100u, 0b101u, 0b100u, 0b001u, 0b000u}, // -Y
        {0b111u, 0b110u, 0b011u, 0b010u, 0b011u, 0b110u}, // +Y
        {0b100u, 0b010u, 0b110u, 0b010u, 0b100u, 0b000u}, // -Z
        {0b111u, 0b011u, 0b101u, 0b001u, 0b101u, 0b011u}, // +Z
    };

    void updateMesh(const std::vector<VoxelVertex> &vertices);

    // Rounds size up to a power of 2
    size_t ceilPow2(size_t size) const;

    void setVoxel(uint8_t x, uint8_t y, uint8_t z, uint8_t val);
    uint8_t getVoxel(uint8_t x, uint8_t y, uint8_t z) const;

public:
    VoxelChunk(uint32_t x, uint32_t y, uint32_t z);
    VoxelChunk(const glm::uvec3 &chunkPosition);
    ~VoxelChunk();

    void buildMesh();

    void drawMesh(Shader &shader) const;
};

#endif