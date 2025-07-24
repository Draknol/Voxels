#include <util/Key.h>

#include <GLFW/glfw3.h>

int Key::toGLFWKey(Action key) {
    switch (key) {
    case HOT_RELOAD:
        return GLFW_KEY_F5;
    case EXIT:
        return GLFW_KEY_ESCAPE;
    default:
        return -1;
    }
}