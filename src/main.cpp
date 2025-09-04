#include <game/Game.h>
#include <util/PerlinGenerator.h>

int main() {
    Game::init("Voxel");

    World world;
    Game::useWorld(&world);

    PerlinGenerator random(0.5f, 15.0f);

    // Placeholder terrain
    for (size_t x = 0u; x < 10u; x++) {
        for (size_t z = 0u; z < 10u; z++) {
            world.addVoxelChunk(x, 0u, z);

            for (size_t i = 0u; i < 16u; i++) {
                for (size_t j = 0u; j < 16u; j++) {
                    uint8_t val = rand() % 2 ? 2 : 10;
                    size_t height = (size_t)random.sample(glm::vec2(x + i / 16.0f, z + j / 16.0f)) + 1;
                    for (size_t h = 0u; h < height; h++) {
                        world.changeBlock(x, 0u, z, i, h, j, val);
                    }
                }
            }

            world.buildChunk(x, 0u, z);
        }
    }

    while (Game::isRunning()) {
        Game::render();
    }

    Game::close();
    return 0;
}