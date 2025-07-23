#include <render/Window.h>
#include <util/Clock.h>

int main() {
    Window window(800, 800, "voxels");
    window.setActive();

    Window::setVsync(false);

    Color skyBlue(0x8CB2FFFF);
    Window::setClearColor(skyBlue);

    Clock clock;

    while (window.isOpen()) {
        double deltaTime = clock.reset();
        clock.updateFPS(deltaTime);

        Window::pollEvents();
        Window::clear();

        window.display();
    }
}