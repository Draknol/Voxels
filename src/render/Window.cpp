#include <render/Window.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace {
GLFWwindow *window = nullptr;
GLFWmonitor *monitor = nullptr;
const GLFWvidmode *mode = nullptr;
glm::ivec2 windowedSize;
glm::ivec2 fullscreenSize;
glm::ivec2 windowPosition;

std::function<void(Key::Action key, Key::State state)> keyCallbackFunc;
std::function<void(int width, int height)> resizeCallbackFunc;
std::function<void(double xpos, double ypos)> cursorCallbackFunc;

glm::dvec2 lastCursorPosition;

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (keyCallbackFunc) {
        keyCallbackFunc(Key::fromGLFWKey(key), Key::fromGLFWState(action));
    }
}

void resizeCallback(GLFWwindow *window, int width, int height) {
    if (resizeCallbackFunc) {
        resizeCallbackFunc(width, height);
    }
}

void cursorCallback(GLFWwindow *window, double xpos, double ypos) {
    if (cursorCallbackFunc) {
        cursorCallbackFunc(xpos, ypos);
    }

    // update cursor position
    lastCursorPosition.x = xpos;
    lastCursorPosition.y = ypos;
}
} // namespace

namespace Window {
void init(const glm::ivec2 &size, const std::string &title) {
    init(size.x, size.y, title);
}

void init(int width, int height, const std::string &title) {
    if (glfwInit() == GL_FALSE) {
        std::cerr << "ERROR::GLFW_INIT_FAILED\n";
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
        std::cerr << "ERROR::CREATE_WINDOW_FAILED\n";
        exit(-1);
    }

    glfwMakeContextCurrent(window);

    monitor = glfwGetPrimaryMonitor();
    mode = glfwGetVideoMode(monitor);
    fullscreenSize.x = mode->width;
    fullscreenSize.y = mode->height;
    windowedSize.x = width;
    windowedSize.y = height;

    // Set callbacks
    glfwSetKeyCallback(window, keyCallback);
    glfwSetFramebufferSizeCallback(window, resizeCallback);
    glfwSetCursorPosCallback(window, cursorCallback);

    // Get cursor position
    glfwGetCursorPos(window, &lastCursorPosition.x, &lastCursorPosition.y);
}

void terminate() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void setCursorVisible(bool state) {
    int glfwState = state ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
    glfwSetInputMode(window, GLFW_CURSOR, glfwState);
}

void setFullscreen(bool state) {
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

bool isOpen() {
    return !glfwWindowShouldClose(window);
}

void close() {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void display() {
    glfwSwapBuffers(window);
}

void resize(int width, int height) {
    glfwSetWindowSize(window, width, height);
}

void resize(const glm::ivec2 &size) {
    glfwSetWindowSize(window, size.x, size.y);
}

void setKeyCallback(std::function<void(Key::Action key, Key::State state)> callback) {
    keyCallbackFunc = callback;
}

void setResizeCallback(std::function<void(int width, int height)> callback) {
    resizeCallbackFunc = callback;
}

void setCursorCallback(std::function<void(double xpos, double ypos)> callback) {
    cursorCallbackFunc = callback;
}

void clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void setVsync(bool isVsync) {
    glfwSwapInterval(isVsync);
}

void setClearColor(float red, float green, float blue, float alpha) {
    glClearColor(red, green, blue, alpha);
}

void setClearColor(const Color &color) {
    glClearColor(color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
}

void setClearColor(uint32_t rgba) {
    setClearColor(Color(rgba));
}

void setDepthTest(bool state) {
    if (state) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
}

void setBackFaceCull(bool state) {
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

void setFrontFaceCull(bool state) {
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

glm::dvec2 getLastCursorPosition() {
    return lastCursorPosition;
}

const glm::ivec2 &getFullscreenSize() {
    return fullscreenSize;
}

void pollEvents() {
    glfwPollEvents();
}
} // namespace Window