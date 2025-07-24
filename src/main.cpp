#include <render/Window.h>

#include <util/Settings.h>
#include <util/Clock.h>

int main() {
    Settings settings("config/settings.ini");

    Window window(settings.getWidth(), settings.getHeight(), "voxels");
    window.setActive();

    Window::setVsync(settings.isVSync());

    Color skyBlue(0x8CB2FFFF);
    Window::setClearColor(skyBlue);

    Clock clock;

    while (window.isOpen()) {
        double deltaTime = clock.reset();
        clock.updateFPS(deltaTime);

        Window::pollEvents();

        // Handle events
        if (window.getKeyState(Key::HOT_RELOAD) == Key::State::PRESSED) {
            settings.reload();
            Window::setVsync(settings.isVSync());
            window.resize(settings.getWidth(), settings.getHeight());
        }
        if (window.getKeyState(Key::EXIT) == Key::State::PRESSED) {
            window.close();
        }

        Window::clear();

        window.display();
    }

    window.terminate();
    return 0;
}