#include <render/Window.h>

#include <GLFW/glfw3.h>

#include <iostream>

Window::Window(int width, int height, const std::string &title) {
    if (glfwInit() == GL_FALSE) {
        std::cerr << "ERROR::WINDOW::GLFW_INIT_FAILED\n";
        exit(-1);
    }

    // Using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!(window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL))) {
        std::cerr << "ERROR::WINDOW::CREATE_WINDOW_FAILED\n";
        exit(-1);
    }

    // Set callbacks
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, Window::keyCallback);
}

Window::~Window() {
    if (window) {
        glfwDestroyWindow(window);
    }
}

void Window::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    Window *win = (Window *)glfwGetWindowUserPointer(window);

    if (action == GLFW_PRESS) {
        win->glfwKeyStates[key] = Key::State::PRESSED;
    } else if (action == GLFW_RELEASE) {
        win->glfwKeyStates[key] = Key::State::RELEASED;
    }
}

bool Window::isOpen() {
    return !glfwWindowShouldClose(window);
}

void Window::close() {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Window::display() {
    glfwSwapBuffers(window);
}

void Window::setActive() {
    glfwMakeContextCurrent(window);
}

void Window::resize(int width, int height) {
    glfwSetWindowSize(window, width, height);
}

Key::State Window::getKeyState(Key::Action key) {
    int glfwKey = Key::toGLFWKey(key);
    Key::State &state = glfwKeyStates[glfwKey];

    switch (state) {
    case Key::State::PRESSED:
        // Update to HELD for next time
        state = Key::State::HELD;
        return Key::State::PRESSED;
    case Key::State::HELD:
        return Key::State::HELD;
    case Key::State::RELEASED:
        // Update to IDLE for next time
        state = Key::State::IDLE;
        return Key::State::RELEASED;
    default:
        return Key::State::IDLE;
    }
}

void Window::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::setVsync(bool isVsync) {
    glfwSwapInterval(isVsync);
}

void Window::setClearColor(float red, float green, float blue, float alpha) {
    glClearColor(red, green, blue, alpha);
}

void Window::setClearColor(const Color &color) {
    glClearColor(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
}

void Window::setClearColor(uint32_t rgba) {
    setClearColor(Color(rgba));
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::terminate() {
    glfwTerminate();
}