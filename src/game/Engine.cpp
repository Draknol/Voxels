#include <game/Engine.h>

#include <game/Input.h>

#include <iostream>

Engine::Engine(const std::string &title, std::shared_ptr<Settings> settings)
    : settings(settings), window(settings->getSize(), title) {

    // Set skyColor to a light-blue
    Color skyColor(0x8CB2FFFF);

    // Set window properties
    setWindowActive();
    window.setCursorVisable(false);
    Window::setDepthTest(true);
    Window::setBackFaceCull(true);
    Window::setClearColor(skyColor);
    Window::setVsync(settings->isVSync());
}

Engine::~Engine() {
    window.terminate();
}

void Engine::render(const World &world, const Shader &voxelShader) {
    setWindowActive();

    Window::pollEvents();

    Window::clear();

    for (const VoxelChunk &chunk : world) {
        chunk.drawMesh(voxelShader);
    }

    window.display();
}

bool Engine::isRunning() {
    return window.isOpen();
}

void Engine::close() {
    window.close();
}

void Engine::resize(int width, int height) {
    window.resize(width, height);
}

void Engine::resize(const glm::ivec2 &size) {
    window.resize(size);
}

glm::dvec2 Engine::getCursorDelta(double currentX, double currentY) {
    return getCursorDelta(glm::dvec2(currentX, currentY));
}

glm::dvec2 Engine::getCursorDelta(const glm::dvec2 &currentPos) {
    return currentPos - window.getLastCursorPosition();
}

void Engine::setKeyCallback(std::function<void(Key::Action key, Key::State state)> callback) {
    window.setKeyCallback(callback);
}

void Engine::setResizeCallback(std::function<void(int width, int height)> callback) {
    window.setResizeCallback(callback);
}

void Engine::setCursorCallback(std::function<void(double xpos, double ypos)> callback) {
    window.setCursorCallback(callback);
}

void Engine::setWindowActive() {
    if (activeWindow != &window) {
        activeWindow = &window;
        window.setActive();
    }
}

void Engine::setVSync(bool state) {
    setWindowActive();
    Window::setVsync(state);
}

void Engine::setSkyColor(const Color &color) {
    window.setClearColor(color);
}