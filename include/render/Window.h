#ifndef WINDOW_H
#define WINDOW_H

#include <util/Color.h>
#include <util/Key.h>

#include <string>
#include <map>

struct GLFWwindow;

class Window {
private:
    GLFWwindow *window;

    std::map<int, Key::State> glfwKeyStates;

    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

public:
    Window(int width, int height, const std::string &title);
    ~Window();

    /// @brief Checks if the Window is marked for closing
    bool isOpen();

    /// @brief Marks the Window for closing
    void close();

    /// @brief Swap buffers to display updated window
    void display();

    /// @brief Set as active Window for static calls
    void setActive();

    /// @brief Update width and height
    void resize(int width, int height);

    /// @brief Returns current state of given key (eg PRESSED)
    Key::State getKeyState(Key::Action key);

    /// @brief Clear active Windows color buffer
    static void clear();

    /// @brief Enable / disable active Windows VSync
    static void setVsync(bool isVSync);

    /// @brief Set active Windows clear color using RGBA floats
    static void setClearColor(float red, float green, float blue, float alpha);

    /// @brief Set active Windows clear color using Color class
    static void setClearColor(const Color &color);

    /// @brief Set active Windows clear color using 0xRRGGBBAA hex
    static void setClearColor(uint32_t rgba);

    /// @brief Poll active Windows events
    static void pollEvents();

    /// @brief Terminate GLFW — call once before exit
    static void terminate();
};

#endif