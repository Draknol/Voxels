#ifndef KEY_H
#define KEY_H

class Key {
public:
    enum Action {
        HOT_RELOAD,
        EXIT
    };

    enum State {
        IDLE,
        PRESSED,
        HELD,
        RELEASED
    };

    static int toGLFWKey(Action key);

private:
    Key() = delete;
};

#endif