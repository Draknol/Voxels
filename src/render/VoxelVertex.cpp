#include <render/VoxelVertex.h>

#include <algorithm>

VoxelVertex::VoxelVertex(const glm::u8vec3 &position, uint8_t color, Normal normal = None) {
    setPosition(position);
    setColor(color);
    setNormal(normal);
}

void VoxelVertex::setPosition(const glm::u8vec3 &position) {
    // Clear old position
    uint32_t mask = 0b00000000000000011111111111111111;
    data &= mask;

    // Add x, y then z, pushing everything along after
    data |= std::min(position.x, MAX_POSITION) << X_POS;
    data |= std::min(position.y, MAX_POSITION) << Y_POS;
    data |= std::min(position.z, MAX_POSITION) << Z_POS;
}

void VoxelVertex::setColor(uint8_t color) {
    // Clear old color
    uint32_t mask = 0b11111111111111111111111100000000;
    data &= mask;

    data |= color;
}

void VoxelVertex::setNormal(Normal normal) {
    // Clear old normal
    uint32_t mask = 0b11111111111111100000000011111111;
    data &= mask;

    data |= std::min((uint32_t)normal, (uint32_t)Normal::None) << NORMAL_POS;
}

glm::u8vec3 VoxelVertex::getPosition() {
    uint8_t mask = 0b11111;

    // Get x, y and z with the bit mask
    glm::u8vec3 position;
    position.x = (data >> X_POS) & mask;
    position.y = (data >> Y_POS) & mask;
    position.z = (data >> Z_POS) & mask;

    return position;
}

uint8_t VoxelVertex::getColor() {
    uint8_t mask = 0b11111111;

    return data & mask;
}

uint8_t VoxelVertex::getNormal() {
    uint8_t mask = 0b111;

    return (data >> NORM_BIT_COUNT) & mask;
}