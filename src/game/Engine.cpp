#include <game/Engine.h>

#include <render/Window.h>
#include <util/Settings.h>

namespace {
uint32_t cursorSkips = 0u;
bool fullscreen = false;
} // namespace

namespace Engine {
void init(const std::string &title) {
    Window::init(Settings::getSize(), title);

    // Enable fullscreen if needed
    if (Settings::isFullscreen()) {
        toggleFullscreen();
    }

    // Set skyColor to a light-blue
    Color skyColor(0x8CB2FFFF);

    // Set window properties
    Window::setCursorVisible(false);
    Window::setDepthTest(true);
    Window::setBackFaceCull(true);
    Window::setClearColor(skyColor);
    Window::setVsync(Settings::isVSync());
}

void terminate() {
    Window::terminate();
}

void render(const World &world) {
    Window::pollEvents();
    Window::clear();

    for (const VoxelChunk &chunk : world) {
        chunk.drawMesh();
    }

    Window::display();
}

bool isRunning() {
    return Window::isOpen();
}

void close() {
    Window::close();
}

void resize(int width, int height) {
    Window::resize(width, height);
}

void resize(const glm::ivec2 &size) {
    Window::resize(size);
}

glm::dvec2 getCursorDelta(double currentX, double currentY) {
    return getCursorDelta(glm::dvec2(currentX, currentY));
}

glm::dvec2 getCursorDelta(const glm::dvec2 &currentPos) {
    if (cursorSkips == 0u) {
        return currentPos - Window::getLastCursorPosition();
    } else {
        cursorSkips--;
        return glm::dvec2(0.0);
    }
}

bool isFullscreen() {
    return fullscreen;
}

const glm::ivec2 &getFullscreenSize() {
    return Window::getFullscreenSize();
}

void setKeyCallback(std::function<void(Key::Action key, Key::State state)> callback) {
    Window::setKeyCallback(callback);
}

void setResizeCallback(std::function<void(int width, int height)> callback) {
    Window::setResizeCallback(callback);
}

void setCursorCallback(std::function<void(double xpos, double ypos)> callback) {
    Window::setCursorCallback(callback);
}

void setVSync(bool state) {
    Window::setVsync(state);
}

void toggleFullscreen() {
    fullscreen = !fullscreen;

    // Skip mouse movement due to toggle.
    if (fullscreen) {
        cursorSkips += 1;
    } else {
        cursorSkips += 2;
    }

    Window::setFullscreen(fullscreen);
}

void setSkyColor(const Color &color) {
    Window::setClearColor(color);
}
} // namespace Engine