#include <game/Input.h>

#include <game/Game.h>
#include <game/Engine.h>
#include <util/Settings.h>

namespace Input {
void setupKeyCallback(Player &player) {
    Engine::setKeyCallback([&](Key::Action key, Key::State state) {
        // Ignore repeats
        if (state == Key::State::REPEAT) {
            return;
        }

        bool pressed = (state == Key::State::PRESS);

        switch (key) {
        case Key::HOT_RELOAD:
            if (pressed) {
                Settings::reload();
                Game::updateFromSettings();
                if (Settings::isFullscreen() != Engine::isFullscreen()) {
                    Engine::toggleFullscreen();
                }
            }
            break;
        case Key::EXIT:
            if (pressed) {
                Engine::close();
            }
            break;
        case Key::TOGGLE_FULLSCREEN:
            if (pressed) {
                Engine::toggleFullscreen();
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
        case Key::JUMP:
            player.setJumping(pressed);
            break;
        case Key::CROUCH:
            player.setCrouching(pressed);
            break;
        case Key::SPRINT:
            player.setSprinting(pressed);
        default:
            break;
        }
    });
}

void setupResizeCallback(Player &player) {
    Engine::setResizeCallback([&](int width, int height) {
        Engine::resize(width, height);
        player.updateViewport(width, height);
    });
}

void setupCursorCallback(Player &player) {
    Engine::setCursorCallback([&](double xpos, double ypos) {
        glm::dvec2 cursorDelta = Engine::getCursorDelta(xpos, ypos);
        cursorDelta.y *= -1;

        cursorDelta *= player.getSensitivity();

        player.rotate(cursorDelta.x, cursorDelta.y);
    });
}

} // namespace Input