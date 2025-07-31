#include <render/Window.h>
#include <render/VoxelChunk.h>
#include <render/View.h>

#include <util/Settings.h>
#include <util/Clock.h>

#include <vector>

void setupKeyCallback(Window &window, View &view, Settings &settings);
void setupResizeCallback(Window &window, View &view);
void setupCursorCallback(Window &window, View &view);

int main() {
    Settings settings("config/settings.ini");

    View view(settings.getWidth(), settings.getHeight());

    Color skyBlue(0x8CB2FFFF);

    Window window(settings.getWidth(), settings.getHeight(), "voxels");
    window.setCursorVisable(false);
    window.setActive();

    Window::setDepthTest(true);
    Window::setBackFaceCull(true);
    Window::setClearColor(skyBlue);
    Window::setVsync(settings.isVSync());

    // Set callbacks
    setupKeyCallback(window, view, settings);
    setupResizeCallback(window, view);
    setupCursorCallback(window, view);

    Shader voxelShader("shader/voxel.vert", "shader/voxel.frag");
    voxelShader.setActive();

    // Add colors
    voxelShader.setUint("colorPalette[1]", Color::Red.toHex());
    voxelShader.setUint("colorPalette[2]", Color::Green.toHex());
    voxelShader.setUint("colorPalette[3]", Color::Blue.toHex());

    VoxelChunk chunk(0u, 0u, 0u);
    chunk.buildMesh();

    Clock clock;
    double deltaTime = clock.reset();

    while (window.isOpen()) {
        deltaTime = clock.reset();
        clock.updateFPS(deltaTime);

        Window::pollEvents();

        view.update(deltaTime);
        voxelShader.setMat4("projView", view.getProjView());

        Window::clear();

        chunk.drawMesh(voxelShader);

        window.display();
    }

    window.terminate();
    return 0;
}

void setupKeyCallback(Window &window, View &view, Settings &settings) {
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
}

void setupResizeCallback(Window &window, View &view) {
    window.setResizeCallback([&](int width, int height) {
        window.resize(width, height);
        view.resizeViewport(width, height);
    });
}

void setupCursorCallback(Window &window, View &view) {
    window.setCursorCallback([&](double xpos, double ypos) {
        glm::dvec2 offset = glm::dvec2(xpos, ypos) - window.getLastCursorPosition();
        offset.y *= -1;

        double sensitivity = 0.15f;
        offset *= sensitivity;

        view.rotate(offset.x, offset.y);
    });
}