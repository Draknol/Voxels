#include <util/HeightMapSampler.h>

namespace HeightMapSampler {
float sample(glm::vec2 position, unsigned char* image, int width, int height) {
    return (float)image[(int)position.y * width + (int)position.x];
}

float sample(glm::vec2 position, float amplitude, unsigned char* image, int width, int height) {
    // [0, 255] --> [0, 1] --> [0, amplitude]
    return sample(position, image, width, height) / 255.0f * amplitude;
}
} // namespace HeightMapSampler
