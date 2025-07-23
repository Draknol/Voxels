#ifndef WINDOW_H
#define WINDOW_H

#include <util/Color.h>

#include <string>

struct GLFWwindow;

class Window {
private:
    GLFWwindow *window;

public:
    Window(int width, int height, const std::string &title);
    ~Window();

    bool isOpen();

    /// @brief Swap buffers to display updated window
    void display();

    /// @brief Set as active Window for static calls
    void setActive();

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