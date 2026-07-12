#ifndef HEIGHT_MAP_H
#define HEIGHT_MAP_H

#include <glm/vec2.hpp>

#include <stb_image.h>

namespace HeightMapSampler {
/// @brief Sample a position in an image
/// @param image Greyscale image to sample from
/// @param width Width of the image
/// @param height Height of the image
/// @return Value in range [0, 255]
float sample(glm::vec2 position, unsigned char* image, int width, int height);

/// @brief Sample a scaled position in an image
/// @param image Greyscale image to sample from
/// @param width Width of the image
/// @param height Height of the image
/// @return Value in range [0, amplitude]
float sample(glm::vec2 position, float amplitude, unsigned char* image, int width, int height);
} // namespace HeightMapSampler

#endif