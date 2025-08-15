#include <game/Game.h>

#include <game/Input.h>

Game::Game(const std::string &title, const std::string &settingsPath, const std::string &colorPalletePath)
    : settings(std::make_shared<Settings>(settingsPath)),
      colorPalette(colorPalletePath),
      engine(title, settings),
      player(settings),
      voxelShader("shader/voxel.vert", "shader/voxel.frag") {

    // Update player view if using fullscreen
    if (settings->isFullscreen()) {
        player.resizeView(engine.getFullscreenSize());
    }

    Input::setupKeyCallback(this, engine, player, settings);
    Input::setupResizeCallback(engine, player);
    Input::setupCursorCallback(engine, player);

    voxelShader.setActive();

    voxelShader.setColorPalette("colorPalette", colorPalette);

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

void Game::updateFromSettings(std::shared_ptr<Settings> settings) {
    colorPalette.reload();
    printFPS = settings->isPrintFPS();
    engine.resize(settings->getSize());
    engine.setVSync(settings->isVSync());
    player.resizeView(settings->getSize(), settings->getFOV());
    player.setSensitivity(settings->getSensitivity());
    voxelShader.setColorPalette("colorPalette", colorPalette);
}