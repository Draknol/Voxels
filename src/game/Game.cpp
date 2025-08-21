#include <game/Game.h>

#include <game/Engine.h>
#include <game/Input.h>
#include <render/ShaderManager.h>
#include <util/Settings.h>
#include <util/ColorPalette.h>
#include <util/Clock.h>

namespace {
ColorPalette colorPalette;
uint32_t voxelShader;
Player player;
World world;
Clock gameClock;
float deltaTime = 0.0f;
bool printFPS = false;
} // namespace

namespace Game {
void init(const std::string &title, const std::string &settingsPath, const std::string &colorPalletePath) {
    Settings::init(settingsPath);
    colorPalette.load(colorPalletePath);

    Engine::init(title);

    ShaderManager::init();
    voxelShader = ShaderManager::addShader("shader/voxel.vert", "shader/voxel.frag");
    ShaderManager::setActiveShader(voxelShader);
    ShaderManager::setColorPalette("colorPalette", colorPalette);

    if (Settings::isFullscreen()) {
        player.updateViewport(Engine::getFullscreenSize());
    } else {
        player.updateViewport(Settings::getSize(), Settings::getFOV());
    }

    player.setSensitivity(Settings::getSensitivity());

    Input::setupKeyCallback(player);
    Input::setupResizeCallback(player);
    Input::setupCursorCallback(player);

    world.addVoxelChunk(1u, 0u, 0u);

    // Initialise delta time
    deltaTime = gameClock.reset();
    printFPS = Settings::isPrintFPS();
}

void close() {
    Engine::terminate();
}

void render() {
    deltaTime = gameClock.reset();

    if (printFPS) {
        gameClock.updateFPS(deltaTime);
    }

    player.update(deltaTime);

    ShaderManager::setActiveShader(voxelShader);
    ShaderManager::setMat4("projView", player.getProjView());

    Engine::render(world);
}

bool isRunning() {
    return Engine::isRunning();
}

void updateFromSettings() {
    colorPalette.reload();
    printFPS = Settings::isPrintFPS();

    Engine::resize(Settings::getSize());
    Engine::setVSync(Settings::isVSync());

    player.updateViewport(Settings::getSize(), Settings::getFOV());
    player.setSensitivity(Settings::getSensitivity());

    ShaderManager::setActiveShader(voxelShader);
    ShaderManager::setColorPalette("colorPalette", colorPalette);
}
} // namespace Game