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
    glfwSetKeyCallback(window, keyCallback);
    glfwSetFramebufferSizeCallback(window, resizeCallback);
    glfwSetCursorPosCallback(window, cursorCallback);

    // Get cursor position
    glfwGetCursorPos(window, &lastCursorPosition.x, &lastCursorPosition.y);
}

Window::~Window() {
    if (window) {
        glfwDestroyWindow(window);
    }
}

void Window::setCursorVisable(bool state) {
    int glfwState = state ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
    glfwSetInputMode(window, GLFW_CURSOR, glfwState);
}

void Window::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    Window *win = (Window *)glfwGetWindowUserPointer(window);
    if (win->keyCallbackFunc) {
        win->keyCallbackFunc(Key::fromGLFWKey(key), Key::fromGLFWState(action));
    }
}

void Window::resizeCallback(GLFWwindow *window, int width, int height) {
    Window *win = (Window *)glfwGetWindowUserPointer(window);
    if (win->resizeCallbackFunc) {
        win->resizeCallbackFunc(width, height);
    }
}

void Window::cursorCallback(GLFWwindow *window, double xpos, double ypos) {
    Window *win = (Window *)glfwGetWindowUserPointer(window);
    if (win->cursorCallbackFunc) {
        win->cursorCallbackFunc(xpos, ypos);
    }

    // update cursor position
    win->lastCursorPosition.x = xpos;
    win->lastCursorPosition.y = ypos;
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

void Window::setKeyCallback(std::function<void(Key::Action key, Key::State state)> callback) {
    keyCallbackFunc = callback;
}

void Window::setResizeCallback(std::function<void(int width, int height)> callback) {
    resizeCallbackFunc = callback;
}

void Window::setCursorCallback(std::function<void(double xpos, double ypos)> callback) {
    cursorCallbackFunc = callback;
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