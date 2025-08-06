#include <game/Game.h>

int main() {
    Game game("Voxel");

    while (game.isRunning()) {
        game.render();
    }

    return 0;
}