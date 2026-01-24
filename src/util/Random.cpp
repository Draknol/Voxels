#include <util/Random.h>

#include <iostream>
#include <random>

namespace Random {
static std::mt19937 rnd(std::random_device{}());

bool boolean() {
    std::bernoulli_distribution distribution(0.5f);
    return distribution(rnd);
}

uint32_t inRange(uint32_t min, uint32_t max) {
    if (max < min) {
        std::cerr << "ERROR::RANDOM::inRange: max < min\n";
        return 0;
    }
    if (max == min) {
        return max;
    }
    std::uniform_int_distribution distribution(min, max);
    return distribution(rnd);
}
} // namespace Random
