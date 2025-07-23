#include <util/Color.h>

constexpr Color Color::Red = Color(1.0f, 0.0f, 0.0f, 1.0f);
constexpr Color Color::Green = Color(0.0f, 1.0f, 0.0f, 1.0f);
constexpr Color Color::Blue = Color(0.0f, 0.0f, 1.0f, 1.0f);
constexpr Color Color::Black = Color(0.0f, 0.0f, 0.0f, 1.0f);
constexpr Color Color::White = Color(1.0f, 1.0f, 1.0f, 1.0f);

float Color::clamp(float x) {
    if (x < 0.0f) {
        return 0.0f;
    }
    if (x > 1.0f) {
        return 1.0f;
    }
    return x;
}

uint8_t Color::normalize(float x) {
    return static_cast<uint8_t>((clamp(x) * 255.0f) + 0.5f);
}

uint32_t Color::toHex(float r, float g, float b, float a) {
    return (normalize(r) << 24) | (normalize(g) << 16) | (normalize(b) << 8) | normalize(a);
}

uint32_t Color::toHex() const {
    return toHex(r, g, b, a);
}
