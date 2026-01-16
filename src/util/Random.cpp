#include <util/Random.h>

#include <iostream>
#include <cstdlib>

namespace Random {
bool boolean() {
    return rand() % 2;
}

uint32_t inRange(uint32_t min, uint32_t max) {
    if (max < min) {
        std::cerr << "ERROR::RANDOM::inRange: max < min\n";
        return 0;
    }
    if (max == min) {
        return max;
    }
    return rand() % (max - min + 1) + min;
}
} // namespace Random
