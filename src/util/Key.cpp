#include <util/Key.h>

#include <GLFW/glfw3.h>

int Key::toGLFWKey(Key::Action key) {
    switch (key) {
    case HOT_RELOAD:
        return GLFW_KEY_F5;
    case EXIT:
        return GLFW_KEY_ESCAPE;
    case WALK_FORWARD:
        return GLFW_KEY_W;
    case WALK_LEFT:
        return GLFW_KEY_A;
    case WALK_BACK:
        return GLFW_KEY_S;
    case WALK_RIGHT:
        return GLFW_KEY_D;
    case JUMP:
        return GLFW_KEY_SPACE;
    case CROUCH:
        return GLFW_KEY_LEFT_CONTROL;
    case SPRINT:
        return GLFW_KEY_LEFT_SHIFT;
    case TOGGLE_FULLSCREEN:
        return GLFW_KEY_F11;
    default:
        return -1;
    }
}

int Key::toGLFWState(Key::State state) {
    switch (state) {
    case RELEASE:
        return GLFW_RELEASE;
    case PRESS:
        return GLFW_PRESS;
    case REPEAT:
        return GLFW_REPEAT;
    default:
        return -1;
    }
}

Key::Action Key::fromGLFWKey(int key) {
    switch (key) {
    case GLFW_KEY_F5:
        return HOT_RELOAD;
    case GLFW_KEY_ESCAPE:
        return EXIT;
    case GLFW_KEY_W:
        return WALK_FORWARD;
    case GLFW_KEY_A:
        return WALK_LEFT;
    case GLFW_KEY_S:
        return WALK_BACK;
    case GLFW_KEY_D:
        return WALK_RIGHT;
    case GLFW_KEY_SPACE:
        return JUMP;
    case GLFW_KEY_LEFT_CONTROL:
        return CROUCH;
    case GLFW_KEY_LEFT_SHIFT:
        return SPRINT;
    case GLFW_KEY_F11:
        return TOGGLE_FULLSCREEN;
    default:
        return NONE;
    }
}

Key::State Key::fromGLFWState(int state) {
    switch (state) {
    case GLFW_RELEASE:
        return RELEASE;
    case GLFW_PRESS:
        return PRESS;
    case GLFW_REPEAT:
        return REPEAT;
    default:
        return IDLE;
    }
}