#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

class Color {
private:
    float r, g, b, a;

    /// @brief Clamps a float to be between 0 and 1
    static float clamp(float x);

    /// @brief Converts a float to a uint8
    static uint8_t normalize(float x);

public:
    constexpr Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}
    constexpr Color(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) {}
    Color(uint32_t hex) : Color(((hex >> 24) & 0xFF) / 255.0f, ((hex >> 16) & 0xFF) / 255.0f, ((hex >> 8) & 0xFF) / 255.0f, (hex & 0xFF) / 255.0f) {}

    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Black;
    static const Color White;

    float getRed() const { return r; }
    float getGreen() const { return g; }
    float getBlue() const { return b; }
    float getAlpha() const { return a; }

    void setRed(float r) { this->r = clamp(r); }
    void setGreen(float g) { this->g = clamp(g); }
    void setBlue(float b) { this->b = clamp(b); }
    void setAlpha(float a) { this->a = clamp(a); }

    /// @brief Converts 4 floats to a uint32 in the form 0xRRGGBBAA
    static uint32_t toHex(float r, float g, float b, float a = 1.0f);

    /// @brief Converts Color to a uint32 in the form 0xRRGGBBAA
    uint32_t toHex() const;
};

#endif
