#include <util/Clock.h>

#include <GLFW/glfw3.h>

#include <iostream>

Clock::Clock() {
    lastTime = glfwGetTime();
}

double Clock::reset() {
    double deltaTime = glfwGetTime() - lastTime;
    lastTime += deltaTime;
    return deltaTime;
}

void Clock::updateFPS(double deltaTime) {
    frameTimer += deltaTime;
    frameCounter++;

    // Print deltaTime info every second
    if (frameTimer >= 1.0) {
        double fps = frameCounter / frameTimer;

        std::cout << "FPS: " << fps << "\t";
        std::cout << "ms: " << 1000.0 / fps << "\n";
        frameTimer = 0.0;
        frameCounter = 0.0;
    }
}