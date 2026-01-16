#ifndef VOXEL_CHUNK_H
#define VOXEL_CHUNK_H

#include <glm/vec3.hpp>

#include <render/VoxelVertex.h>
#include <util/Settings.h>

#include <vector>
#include <memory>

class VoxelChunk {
private:
    static constexpr size_t CHUNK_SIZE = Settings::CHUNK_SIZE;
    static constexpr size_t MAX_CHUNK_SIZE = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;
    static constexpr size_t MAX_CHUNK_VERTS = 36u * MAX_CHUNK_SIZE;

    bool empty = true; // Used to skip fully empty chunks

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

    enum Face {
        Left,   // -X
        Right,  // +X
        Back,   // -Y
        Front,  // +Y
        Bottom, // -Z
        Top     // +Z
    };

    static constexpr uint32_t faceIndices[6][6] = {
        {0b011u, 0b010u, 0b001u, 0b000u, 0b001u, 0b010u}, // Left
        {0b101u, 0b110u, 0b111u, 0b110u, 0b101u, 0b100u}, // Right
        {0b001u, 0b100u, 0b101u, 0b100u, 0b001u, 0b000u}, // Back
        {0b111u, 0b110u, 0b011u, 0b010u, 0b011u, 0b110u}, // Front
        {0b100u, 0b010u, 0b110u, 0b010u, 0b100u, 0b000u}, // Bottom
        {0b111u, 0b011u, 0b101u, 0b001u, 0b101u, 0b011u}, // Top
    };

    void updateMesh(const std::vector<VoxelVertex> &vertices);

    // Rounds size up to a power of 2
    size_t ceilPow2(size_t size) const;

    uint8_t getVoxel(uint8_t x, uint8_t y, uint8_t z) const;

    void appendCulledVoxel(std::vector<VoxelVertex> &vertices, uint8_t x, uint8_t y, uint8_t z) const;

public:
    VoxelChunk(uint32_t x, uint32_t y, uint32_t z);
    VoxelChunk(const glm::uvec3 &chunkPosition);
    ~VoxelChunk();

    void setVoxel(uint8_t x, uint8_t y, uint8_t z, uint8_t val);
    void setVoxel(const glm::u8vec3 &position, uint8_t val);

    void addVoxel(uint8_t x, uint8_t y, uint8_t z, uint8_t val);
    void addVoxel(const glm::u8vec3 &position, uint8_t val);

    void buildMesh();

    void drawMesh() const;
};

#endif