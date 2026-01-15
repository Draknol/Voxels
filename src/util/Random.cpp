#include <util/Random.h>

#include <iostream>
#include <cstdlib>

namespace {
uint64_t hash(uint64_t x) {
    x ^= x >> 30;
    x *= 0xbf58476d1ce4e5b9ULL;
    x ^= x >> 27;
    x *= 0x94d049bb133111ebULL;
    x ^= x >> 31;
    return x;
}
} // namespace

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

uint32_t inRangeHash(uint32_t min, uint32_t max, uint64_t seed) {
    if (max < min) {
        std::cerr << "ERROR::RANDOM::inRangeHash: max < min\n";
        return 0;
    }
    if (max == min) {
        return max;
    }
    return (uint32_t)(hash(seed) % (uint64_t)(max - min + 1) + (uint64_t)min);
}
} // namespace Random
