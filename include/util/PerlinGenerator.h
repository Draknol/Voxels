#ifndef NOISE_H
#define NOISE_H

#include <glm/vec2.hpp>

#include <cstdint>

class PerlinGenerator {
private:
    float frequency;
    float amplitude;

    glm::vec2 getGradient(const glm::vec2 &corner) const;
    float calcDot(const glm::vec2 &corner, const glm::vec2 &position) const;
    float interp(float a, float b, float weight) const;

public:
    PerlinGenerator(float frequency, float amplitude);

    float sample(glm::vec2 position) const;
};

#endif