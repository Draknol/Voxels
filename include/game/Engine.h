#ifndef ENGINE_H
#define ENGINE_H

#include <game/World.h>
#include <render/Window.h>
#include <util/Settings.h>

class Engine {
private:
    // Keep track of the active window
    static inline Window *activeWindow = nullptr;
    std::shared_ptr<Settings> settings;

    Window window;

    // Sets this Engines window as the active window
    void setWindowActive();

public:
    Engine(const std::string &title, std::shared_ptr<Settings> settings);
    ~Engine();

    // Renders a frame to the screen
    void render(const World &world, const Shader &voxelShader);

    // Checks if the engine should continue running
    bool isRunning();

    // Mark the window for closing
    void close();

    void resize(int width, int height);
    void resize(const glm::ivec2 &size);

    glm::dvec2 getCursorDelta(double currentX, double currentY);
    glm::dvec2 getCursorDelta(const glm::dvec2 &currentPos);

    void setKeyCallback(std::function<void(Key::Action key, Key::State state)> callback);
    void setResizeCallback(std::function<void(int width, int height)> callback);
    void setCursorCallback(std::function<void(double xpos, double ypos)> callback);

    // Sets the clear color of the window
    void setSkyColor(const Color &color);
};

#endif