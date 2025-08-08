#include <game/Input.h>

#include <iostream>

void Input::setupKeyCallback(Game *game, Engine &engine, Player &player, std::shared_ptr<Settings> settings) {
    engine.setKeyCallback([&, game, settings](Key::Action key, Key::State state) {
        // Ignore repeats
        if (state == Key::State::REPEAT) {
            return;
        }

        bool pressed = (state == Key::State::PRESS);

        switch (key) {
        case Key::HOT_RELOAD:
            if (pressed) {
                settings->reload();
                game->updateFromSettings(settings);
            }
            break;
        case Key::EXIT:
            if (pressed) {
                engine.close();
            }
            break;
        case Key::WALK_FORWARD:
            player.setMovingForward(pressed);
            break;
        case Key::WALK_BACK:
            player.setMovingBackward(pressed);
            break;
        case Key::WALK_LEFT:
            player.setMovingLeft(pressed);
            break;
        case Key::WALK_RIGHT:
            player.setMovingRight(pressed);
            break;
        default:
            break;
        }
    });
}

void Input::setupResizeCallback(Engine &engine, Player &player) {
    engine.setResizeCallback([&](int width, int height) {
        engine.resize(width, height);
        player.resizeView(width, height);
    });
}

void Input::setupCursorCallback(Engine &engine, Player &player) {
    engine.setCursorCallback([&](double xpos, double ypos) {
        glm::dvec2 cursorDelta = engine.getCursorDelta(xpos, ypos);
        cursorDelta.y *= -1;

        cursorDelta *= player.getSensitivity();

        player.rotateView(cursorDelta.x, cursorDelta.y);
    });
}
