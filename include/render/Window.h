#ifndef WINDOW_H
#define WINDOW_H

#include <util/Color.h>
#include <util/Key.h>

#include <glm/vec2.hpp>

#include <functional>
#include <string>
#include <map>

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
    Window(int width, int height, const std::string &title);
    ~Window();

    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

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

    /// @brief Set if cursor should be visable or hidden
    void setCursorVisable(bool state);

    /// @brief Callback for when a key is pressed
    /// @param callback Function to call
    void setKeyCallback(std::function<void(Key::Action key, Key::State state)> callback);

    /// @brief Callback for when the window is resized
    /// @param callback Function to call
    void setResizeCallback(std::function<void(int width, int height)> callback);

    /// @brief Callback for when the cursor is moved
    /// @param callback function to call
    void setCursorCallback(std::function<void(double xpos, double ypos)> callback);

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

    /// @brief Set active Windows depth testing to on or off
    static void setDepthTest(bool state);

    /// @brief Set active Windows back face culling to on or off.
    /// @brief Works with setFrontFaceCull;
    static void setBackFaceCull(bool state);

    /// @brief Set active Windows front face culling to on or off.
    /// @brief Works with setBackFaceCull;
    static void setFrontFaceCull(bool state);

    /// @brief Poll active Windows events
    static void pollEvents();

    /// @brief Terminate GLFW — call once before exit
    static void terminate();

    /// @brief Gets last cursor position (updated after cursor callback)
    glm::dvec2 getLastCursorPosition() { return lastCursorPosition; }
};

#endif