#ifndef CLOCK_H
#define CLOCK_H

/// @brief Clock for getting time and printing fps
class Clock {
private:
    double lastTime;
    double frameCounter = 0.0;
    double frameTimer = 0.0;

public:
    Clock();

    /// @brief Resets clock and returns time in seconds since last reset
    double reset();
    void updateFPS(double deltaTime);
};

#endif // CLOCK_H