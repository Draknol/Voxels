#ifndef VOXEL_VERTEX_H
#define VOXEL_VERTEX_H

#include <glm/vec3.hpp>

#include <cstdint>

enum Normal {
    Left,   // -X
    Right,  // +X
    Back,   // -Y
    Front,  // +Y
    Bottom, // -Z
    Top,    // +Z
    None
};

class VoxelVertex {
private:
    static const uint8_t POS_BIT_COUNT = 5u;
    static const uint8_t NORM_BIT_COUNT = 3u;
    static const uint8_t MAX_POSITION = 0b1 << (POS_BIT_COUNT - 1u);

    static const uint8_t X_POS = 32u - POS_BIT_COUNT;
    static const uint8_t Y_POS = X_POS - POS_BIT_COUNT;
    static const uint8_t Z_POS = Y_POS - POS_BIT_COUNT;
    static const uint8_t NORMAL_POS = Z_POS - NORM_BIT_COUNT;

    public : uint32_t data = 0u;
    VoxelVertex(const glm::u8vec3 &position, uint8_t color, Normal normal);

    void setPosition(const glm::u8vec3 &position);
    void setColor(uint8_t color);
    void setNormal(Normal normal);

    glm::u8vec3 getPosition();
    uint8_t getColor();
    uint8_t getNormal();
};

#endif