#include <render/VoxelVertex.h>

#include <algorithm>

VoxelVertex::VoxelVertex(const glm::u8vec3 &position, uint8_t color) {
    setPosition(position);
    setColor(color);
}

void VoxelVertex::setPosition(const glm::u8vec3 &position) {
    // Clear old position
    uint32_t mask = 0b11111111111111111;
    data &= mask;

    // Add x, y then z, pushing everything along after
    data |= std::min(position.x, MAX_POSITION) << X_POS;
    data |= std::min(position.y, MAX_POSITION) << Y_POS;
    data |= std::min(position.z, MAX_POSITION) << Z_POS;
}

void VoxelVertex::setColor(uint8_t color) {
    // Clear old color
    uint32_t mask = 0b11111111111111100000000000000000;
    data &= mask;

    data |= color;
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