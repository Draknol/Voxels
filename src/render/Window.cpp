#include <render/Window.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

Window::Window(const glm::ivec2 &size, const std::string &title)
    : Window(size.x, size.y, title) {}

Window::Window(int width, int height, const std::string &title) {
    if (glfwInit() == GL_FALSE) {
        std::cerr << "ERROR::WINDOW::GLFW_INIT_FAILED\n";
        exit(-1);
    }

    // Using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // MSAA - fixed for now
    glEnable(GL_MULTISAMPLE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    if (!(window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL))) {
        std::cerr << "ERROR::WINDOW::CREATE_WINDOW_FAILED\n";
        exit(-1);
    }

    monitor = glfwGetPrimaryMonitor();
    mode = glfwGetVideoMode(monitor);
    fullscreenSize.x = mode->width;
    fullscreenSize.y = mode->height;
    windowedSize.x = width;
    windowedSize.y = height;

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

void Window::setFullscreen(bool state) {
    if (state) {
        // Save windowed info
        glfwGetWindowPos(window, &windowPosition.x, &windowPosition.y);
        glfwGetWindowSize(window, &windowedSize.x, &windowedSize.y);

        // Make borderless
        glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
        glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);

        // Fullscreen
        glfwSetWindowSize(window, fullscreenSize.x, fullscreenSize.y);
        glfwSetWindowPos(window, 0, 0);
    } else {
        // Make bordered
        glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_TRUE);
        glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);

        // Windowed
        glfwSetWindowSize(window, windowedSize.x, windowedSize.y);
        glfwSetWindowPos(window, windowPosition.x, windowPosition.y);
    }
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

void Window::resize(const glm::ivec2 &size) {
    glfwSetWindowSize(window, size.x, size.y);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

void Window::setDepthTest(bool state) {
    if (state) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
}

void Window::setBackFaceCull(bool state) {
    GLint currentState;
    glGetIntegerv(GL_CULL_FACE_MODE, &currentState);

    if (state) {
        glEnable(GL_CULL_FACE);
        glCullFace((currentState == GL_FRONT) ? GL_FRONT_AND_BACK : GL_BACK);
    } else {
        if (currentState == GL_FRONT_AND_BACK) {
            glCullFace(GL_FRONT);
        } else if (currentState == GL_BACK) {
            glDisable(GL_CULL_FACE);
        }
    }
}

void Window::setFrontFaceCull(bool state) {
    GLint currentState;
    glGetIntegerv(GL_CULL_FACE_MODE, &currentState);

    if (state) {
        glEnable(GL_CULL_FACE);
        glCullFace((currentState == GL_BACK) ? GL_FRONT_AND_BACK : GL_FRONT);
    } else {
        if (currentState == GL_FRONT_AND_BACK) {
            glCullFace(GL_BACK);
        } else if (currentState == GL_FRONT) {
            glDisable(GL_CULL_FACE);
        }
    }
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::terminate() {
    glfwTerminate();
}