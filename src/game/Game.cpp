#include <game/Game.h>

#include <game/Engine.h>
#include <game/Input.h>
#include <render/ShaderManager.h>
#include <util/Settings.h>
#include <util/Clock.h>

namespace {
uint32_t voxelShader;
Player player;
const World *worldPtr = nullptr;
Clock gameClock;
float deltaTime = 0.0f;
bool printFPS = false;
} // namespace

namespace Game {
void init(const std::string &title, const std::string &userSettingsPath, const std::string &worldSettingsPath) {
    Settings::load(userSettingsPath, worldSettingsPath);

    Engine::init(title);

    ShaderManager::init();
    voxelShader = ShaderManager::addShader("shader/voxel.vert", "shader/voxel.frag");
    ShaderManager::setActiveShader(voxelShader);
    ShaderManager::updateMaterials();

    if (Settings::isFullscreen()) {
        player.updateViewport(Engine::getFullscreenSize());
    } else {
        player.updateViewport(Settings::getSize(), Settings::getFOV());
    }

    player.setSensitivity(Settings::getSensitivity());

    Input::setupKeyCallback(player);
    Input::setupResizeCallback(player);
    Input::setupCursorCallback(player);

    // Initialise delta time
    deltaTime = gameClock.reset();
    printFPS = Settings::isPrintFPS();
}

void useWorld(const World *world) {
    worldPtr = world;
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
    ShaderManager::setVec3("viewPos", player.getPosition());

    if (worldPtr) {
        Engine::render(*worldPtr);
    }
}

bool isRunning() {
    return Engine::isRunning();
}

void updateFromSettings() {
    printFPS = Settings::isPrintFPS();

    Engine::resize(Settings::getSize());
    Engine::setVSync(Settings::isVSync());

    player.updateViewport(Settings::getSize(), Settings::getFOV());
    player.setSensitivity(Settings::getSensitivity());

    ShaderManager::setActiveShader(voxelShader);
}
} // namespace Game