#ifndef CLOCK_H
#define CLOCK_H

class Clock {
private:
    double lastTime;
    double frameCounter = 0.0;
    double frameTimer = 0.0;

public:
    Clock();

    // Resets clock and returns time in seconds since last reset
    double reset();

    void updateFPS(double deltaTime);
};

#endif