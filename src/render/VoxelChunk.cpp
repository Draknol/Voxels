#include <render/VoxelChunk.h>

#include <gl/glew.h>

VoxelChunk::VoxelChunk(uint32_t x, uint32_t y, uint32_t z)
    : VoxelChunk(glm::uvec3(x, y, z)) {}

VoxelChunk::VoxelChunk(const glm::uvec3 &chunkPosition)
    : chunkOffset(static_cast<uint32_t>(CHUNK_SIZE) * chunkPosition) {

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(VoxelVertex), (void *)0);
    glEnableVertexAttribArray(0);

    // Solid cube
    for (size_t i = 0; i < MAX_CHUNK_SIZE; i++) {
        chunk[i] = rand() % 3 + 1;
    }

    // Sphere
    // glm::vec3 centrePoint(CHUNK_SIZE / 2.0f);
    // for (size_t z = 0; z < CHUNK_SIZE; z++) {
    //     for (size_t y = 0; y < CHUNK_SIZE; y++) {
    //         for (size_t x = 0; x < CHUNK_SIZE; x++) {
    //             glm::vec3 voxelPos(x, y, z);
    //             if (glm::distance(voxelPos, centrePoint) < CHUNK_SIZE / 2.0f) {
    //                 setVoxel(x, y, z, rand() % 3 + 1);
    //             } else {
    //                 setVoxel(x, y, z, 0u);
    //             }
    //         }
    //     }
    // }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

VoxelChunk::~VoxelChunk() {
    delete chunk;
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void VoxelChunk::buildMesh() {
    std::vector<VoxelVertex> vertices;

    for (size_t z = 0; z < CHUNK_SIZE; z++) {
        for (size_t y = 0; y < CHUNK_SIZE; y++) {
            for (size_t x = 0; x < CHUNK_SIZE; x++) {
                // Skip if there is no voxel
                uint8_t color = getVoxel(x, y, z);
                if (color == 0u) {
                    continue;
                }

                // Add voxels vertices
                for (size_t f = 0; f < 6u; ++f) {
                    for (size_t e = 0; e < 6u; e++) {
                        glm::u8vec3 offset(x, y, z);
                        const glm::u8vec3 &vert = cubeVerts[faceIndices[f][e]];
                        vertices.emplace_back(vert + offset, color);
                    }
                }
            }
        }
    }

    updateMesh(vertices);
}

void VoxelChunk::updateMesh(const std::vector<VoxelVertex> &verts) {
    vertCount = verts.size();

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Grow VBO if needed
    if (vertCount > vboCapacity) {
        vboCapacity = std::min(ceilPow2(vertCount), MAX_CHUNK_VERTS);
        glBufferData(GL_ARRAY_BUFFER, vboCapacity * sizeof(VoxelVertex), nullptr, GL_DYNAMIC_DRAW);
    }

    // Update VBO
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertCount * sizeof(VoxelVertex), verts.data());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void VoxelChunk::drawMesh(Shader &shader) const {

    shader.setUVec3("chunkOffset", chunkOffset);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glDrawArrays(GL_TRIANGLES, 0, vertCount);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

size_t VoxelChunk::ceilPow2(size_t size) const {
    size_t power = 1u;

    while (power < size) {
        power <<= 1u;
    }

    return power;
}

void VoxelChunk::setVoxel(uint8_t x, uint8_t y, uint8_t z, uint8_t val) {
    chunk[x + CHUNK_SIZE * y + CHUNK_SIZE * CHUNK_SIZE * z] = val;
}

uint8_t VoxelChunk::getVoxel(uint8_t x, uint8_t y, uint8_t z) const {
    return chunk[x + CHUNK_SIZE * y + CHUNK_SIZE * CHUNK_SIZE * z];
}