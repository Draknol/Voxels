#include <game/Game.h>
#include <level/WorldGenerator.h>
#include <util/Random.h>

#include <algorithm>
#include <iostream>

uint8_t colorDecider(float currentHeight, float maxHeight, uint64_t id) {
    if (currentHeight > 80 - Random::inRangeHash(0, 4, id)) {
        return 1;
    }
    if (currentHeight >= (size_t)maxHeight - Random::inRangeHash(1, 2, id)) {
        return 2;
    }
    if (currentHeight > maxHeight - Random::inRangeHash(2, 5, id)) {
        return 3;
    }
    return 15;
}

int main() {
    Game::init("Voxel");

    World world;
    Game::useWorld(&world);

    WorldGenerator::generatePerlin(&world, 30u, 8u, 30u, 128.0f, 0.007f, 4u, 60, 4, colorDecider);

    while (Game::isRunning()) {
        Game::render();
    }

    Game::close();
    return 0;
}