#include <render/Window.h>
#include <render/Voxel.h>
#include <render/View.h>

#include <util/Settings.h>
#include <util/Clock.h>

#include <iostream>
#include <vector>

int main() {
    Settings settings("config/settings.ini");

    Window window(settings.getWidth(), settings.getHeight(), "voxels");
    window.setActive();
    window.setCursorVisable(false);

    Window::setVsync(settings.isVSync());

    Color skyBlue(0x8CB2FFFF);
    Window::setClearColor(skyBlue);

    Shader voxelShader("shader/voxel.vert", "shader/voxel.frag");
    voxelShader.setActive();

    // 100x100 plane of cubes
    std::vector<Voxel> cubes;
    for (int i = 0; i < 10000; i++) {
        cubes.emplace_back(glm::vec3(i / 100, -2.0f, i % 100));
    }

    View view(settings.getWidth(), settings.getHeight());

    Clock clock;
    double deltaTime = clock.reset();

    // Set callbacks
    window.setKeyCallback([&](Key::Action key, Key::State state) {
        if (state == Key::State::PRESS) {
            switch (key) {
            case Key::HOT_RELOAD:
                settings.reload();
                Window::setVsync(settings.isVSync());
                window.resize(settings.getWidth(), settings.getHeight());
                view.resizeViewport(settings.getWidth(), settings.getHeight());
                break;
            case Key::EXIT:
                window.close();
                break;
            case Key::WALK_FORWARD:
                view.setMovingForward(true);
                break;
            case Key::WALK_BACK:
                view.setMovingBackward(true);
                break;
            case Key::WALK_LEFT:
                view.setMovingLeft(true);
                break;
            case Key::WALK_RIGHT:
                view.setMovingRight(true);
                break;
            default:
                break;
            }
        } else if (state == Key::State::RELEASE) {
            switch (key) {
            case Key::WALK_FORWARD:
                view.setMovingForward(false);
                break;
            case Key::WALK_BACK:
                view.setMovingBackward(false);
                break;
            case Key::WALK_LEFT:
                view.setMovingLeft(false);
                break;
            case Key::WALK_RIGHT:
                view.setMovingRight(false);
                break;
            default:
                break;
            }
        }
    });

    window.setResizeCallback([&](int width, int height) {
        window.resize(width, height);
        view.resizeViewport(width, height);
    });

    window.setCursorCallback([&](double xpos, double ypos) {
        glm::dvec2 offset = glm::dvec2(xpos, ypos) - window.getLastCursorPosition();
        offset.y *= -1;

        double sensitivity = 0.15f;
        offset *= sensitivity;

        view.rotate(offset.x, offset.y);
    });

    while (window.isOpen()) {
        deltaTime = clock.reset();
        clock.updateFPS(deltaTime);

        Window::pollEvents();

        view.update(deltaTime);
        voxelShader.setMat4("projView", view.getProjView());

        Window::clear();

        for (auto &cube : cubes) {
            cube.draw(voxelShader);
        }

        window.display();
    }

    window.terminate();
    return 0;
}