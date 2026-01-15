#include <game/Game.h>
#include <level/WorldGenerator.h>
#include <util/Random.h>

int main() {
    Game::init("Voxel");

    World world;
    Game::useWorld(&world);

    WorldGenerator::generatePerlin(&world);

    while (Game::isRunning()) {
        Game::render();
    }

    Game::close();
    return 0;
}