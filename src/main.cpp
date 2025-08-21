#include <game/Game.h>

int main() {
    Game::init("Voxel");

    while (Game::isRunning()) {
        Game::render();
    }

    return 0;
}