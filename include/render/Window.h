#ifndef WINDOW_H
#define WINDOW_H

#include <util/Color.h>
#include <util/Key.h>

#include <glm/vec2.hpp>

#include <functional>
#include <string>

struct GLFWwindow;

class Window {
private:
    GLFWwindow *window;

    std::function<void(Key::Action key, Key::State state)> keyCallbackFunc;
    std::function<void(int width, int height)> resizeCallbackFunc;
    std::function<void(double xpos, double ypos)> cursorCallbackFunc;

    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void resizeCallback(GLFWwindow *window, int width, int height);
    static void cursorCallback(GLFWwindow *window, double xpos, double ypos);

    glm::dvec2 lastCursorPosition;

public:
    Window(const glm::ivec2 &size, const std::string &title);
    Window(int width, int height, const std::string &title);
    ~Window();

    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

    // Checks if the Window is marked for closing
    bool isOpen();

    // Marks the Window for closing
    void close();

    // Swap buffers to display updated window
    void display();

    // Set as active Window for static calls
    void setActive();

    void resize(int width, int height);
    void resize(const glm::ivec2 &size);

    void setCursorVisable(bool state);

    void setKeyCallback(std::function<void(Key::Action key, Key::State state)> callback);
    void setResizeCallback(std::function<void(int width, int height)> callback);
    void setCursorCallback(std::function<void(double xpos, double ypos)> callback);

    static void clear();
    static void setClearColor(float red, float green, float blue, float alpha);
    static void setClearColor(const Color &color);
    static void setClearColor(uint32_t rgba);

    static void setVsync(bool isVSync);
    static void setDepthTest(bool state);
    static void setBackFaceCull(bool state);
    static void setFrontFaceCull(bool state);

    static void pollEvents();

    // Terminate GLFW — call once before exit
    static void terminate();

    // Gets last cursor position (updated after cursor callback)
    glm::dvec2 getLastCursorPosition() { return lastCursorPosition; }
};

#endif