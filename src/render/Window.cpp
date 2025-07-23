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
}

Window::~Window() {
    if (window) {
        glfwDestroyWindow(window);
    }
}

bool Window::isOpen() {
    return !glfwWindowShouldClose(window);
}

void Window::display() {
    glfwSwapBuffers(window);
}

void Window::setActive() {
    glfwMakeContextCurrent(window);
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