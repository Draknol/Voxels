#include <game/Game.h>

#include <game/Input.h>

#include <glfw/glfw3.h>

Game::Game(const std::string &title, const std::string &settingsPath)
    : settings(std::make_shared<Settings>(settingsPath)), engine(title, settings), player(settings), voxelShader("shader/voxel.vert", "shader/voxel.frag") {

    Input::setupKeyCallback(engine, player, settings);
    Input::setupResizeCallback(engine, player);
    Input::setupCursorCallback(engine, player);

    voxelShader.setActive();

    voxelShader.setUint("colorPalette[1]", Color::Red.toHex());
    voxelShader.setUint("colorPalette[2]", Color::Green.toHex());
    voxelShader.setUint("colorPalette[3]", Color::Blue.toHex());

    world.addVoxelChunk(0u, 0u, 0u);

    // Initialise delta time
    deltaTime = clock.reset();
    printFPS = settings->isPrintFPS();
}

void Game::render() {
    deltaTime = clock.reset();

    if (printFPS) {
        clock.updateFPS(deltaTime);
    }

    player.update(deltaTime);

    voxelShader.setMat4("projView", player.getProjView());

    engine.render(world, voxelShader);
}

bool Game::isRunning() {
    return engine.isRunning();
}