#ifndef NOISE_H
#define NOISE_H

#include <glm/vec2.hpp>

namespace PerlinGenerator {
/// @brief Sample a position once
/// @return Value in range [-1, 1]
float sample(glm::vec2 position);

/// @brief Sample a position at multiple octaves
/// @param amplitude Streches terrain vertically
/// @param frequency Compresses detail horizontally
/// @param octaves Increases detail
/// @return Value in range [0, amplitude]
float sample(glm::vec2 position, float amplitude, float frequency, size_t octaves);
} // namespace PerlinGenerator

#endif