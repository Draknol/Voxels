#ifndef KEY_H
#define KEY_H

class Key {
public:
    enum Action {
        NONE = -1,
        HOT_RELOAD,
        EXIT,
        WALK_FORWARD,
        WALK_LEFT,
        WALK_BACK,
        WALK_RIGHT,
    };

    enum State {
        IDLE = -1,
        RELEASE,
        PRESS,
        REPEAT,
    };

    static int toGLFWKey(Action key);
    static int toGLFWState(State state);
    static Action fromGLFWKey(int key);
    static State fromGLFWState(int state);

private:
    Key() = delete;
};

#endif