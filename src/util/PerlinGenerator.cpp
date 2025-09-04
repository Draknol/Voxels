#include <util/PerlinGenerator.h>

#include <cmath>
#include <glm/geometric.hpp>
#include <glm/ext/scalar_constants.hpp>

PerlinGenerator::PerlinGenerator(float frequency, float amplitude)
    : frequency(frequency), amplitude(amplitude) {}

float PerlinGenerator::sample(glm::vec2 position) const {
    position *= frequency;

    float left = std::floor(position.x);
    float right = left + 1.0f;
    float bottom = std::floor(position.y);
    float top = bottom + 1.0f;

    glm::vec2 weights = position - glm::vec2(left, bottom);

    float bl = calcDot(glm::vec2(left, bottom), position);
    float br = calcDot(glm::vec2(right, bottom), position);
    float interpBottom = interp(bl, br, weights.x);

    float tl = calcDot(glm::vec2(left, top), position);
    float tr = calcDot(glm::vec2(right, top), position);
    float interpTop = interp(tl, tr, weights.x);

    return (interp(interpBottom, interpTop, weights.y) * 0.5f + 0.5f) * amplitude;
}

glm::vec2 PerlinGenerator::getGradient(const glm::vec2 &corner) const {
    const uint32_t SHIFT = 16u; // Half a uint32_t

    uint32_t seedX = (uint32_t)corner.x;
    uint32_t seedY = (uint32_t)corner.y;

    seedX *= 3284157443u;

    seedY ^= (seedX << SHIFT) | (seedX >> SHIFT);
    seedY *= 1911520717u;

    seedX ^= (seedY << SHIFT) | (seedY >> SHIFT);
    seedX *= 2048419325u;

    // Convert to float in range [0, 2π]
    float angle = (float)seedX * (glm::pi<float>() / (float)(1u << 31u));

    // Convert to gradient vector
    return glm::vec2(sin(angle), cos(angle));
}

float PerlinGenerator::calcDot(const glm::vec2 &corner, const glm::vec2 &position) const {
    glm::vec2 gradient = getGradient(corner);
    glm::vec2 distance = position - corner;
    return glm::dot(gradient, distance);
}

float PerlinGenerator::interp(float a, float b, float weight) const {
    return (a - b) * (2.0f * weight - 3.0f) * weight * weight + a;
}