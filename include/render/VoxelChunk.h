#ifndef VOXEL_CHUNK_H
#define VOXEL_CHUNK_H

#include <glm/vec3.hpp>

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
        {1u, 1u, 1u},
        {1u, 1u, 0u},
        {1u, 0u, 1u},
        {1u, 0u, 0u},
        {0u, 1u, 1u},
        {0u, 1u, 0u},
        {0u, 0u, 1u},
        {0u, 0u, 0u},
    };

    static constexpr uint32_t faceIndices[6][6] = {
        {1u, 5u, 4u, 1u, 4u, 0u},
        {2u, 0u, 4u, 2u, 4u, 6u},
        {6u, 4u, 5u, 6u, 5u, 3u},
        {7u, 3u, 2u, 7u, 2u, 6u},
        {3u, 1u, 0u, 3u, 0u, 2u},
        {7u, 5u, 1u, 7u, 1u, 3u},
    };

    /// @brief Updates the VBO with new vertices.
    /// @brief Grows the VBO if needed.
    /// @param vertices
    void updateMesh(const std::vector<glm::u8vec3> &vertices);

    /// @brief Rounds size up to a power of 2
    size_t ceilPow2(size_t size);

    void setVoxel(uint8_t x, uint8_t y, uint8_t z, uint8_t val);
    uint8_t getVoxel(uint8_t x, uint8_t y, uint8_t z);

public:
    /// @brief Creates a chunk of voxels
    /// @param chunkPosition Position on chunk sized grid
    VoxelChunk(const glm::uvec3 &chunkPosition);
    ~VoxelChunk();

    /// @brief Creates a chunk of voxels
    /// @param x x position on chunk sized grid
    /// @param z y position on chunk sized grid
    /// @param y z position on chunk sized grid
    VoxelChunk(uint32_t x, uint32_t y, uint32_t z);

    /// @brief Build voxel array into a single mesh and updates the GPU
    void buildMesh();

    /// @brief Draw build mesh to the active window
    /// @param shader Shader to render with
    void drawMesh(Shader &shader);
};

#endif