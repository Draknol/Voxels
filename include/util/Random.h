#ifndef RANDOM_H
#define RANDOM_H

#include <cstdint>

namespace Random {
bool boolean();
uint32_t inRange(uint32_t min, uint32_t max);
uint32_t inRangeHash(uint32_t min, uint32_t max, uint64_t seed);
} // namespace Random

#endif