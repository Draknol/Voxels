#include <util/Color.h>

constexpr Color Color::Red = Color(1.0f, 0.0f, 0.0f, 1.0f);
constexpr Color Color::Green = Color(0.0f, 1.0f, 0.0f, 1.0f);
constexpr Color Color::Blue = Color(0.0f, 0.0f, 1.0f, 1.0f);
constexpr Color Color::Yellow = Color(1.0f, 1.0f, 0.0f, 1.0f);
constexpr Color Color::Teal = Color(0.0f, 1.0f, 1.0f, 1.0f);
constexpr Color Color::Purple = Color(1.0f, 0.0f, 1.0f, 1.0f);
constexpr Color Color::Black = Color(0.0f, 0.0f, 0.0f, 1.0f);
constexpr Color Color::White = Color(1.0f, 1.0f, 1.0f, 1.0f);

float Color::clampFloat(float x) {
    if (x < 0.0f) {
        return 0.0f;
    }
    if (x > 1.0f) {
        return 1.0f;
    }
    return x;
}

int Color::clampInt(int x) {
    if (x < 0.0f) {
        return 0.0f;
    }
    if (x > 255.0f) {
        return 255.0f;
    }
    return x;
}

uint8_t Color::floatToUint8(float x) {
    return static_cast<uint8_t>((clampFloat(x) * 255.0f) + 0.5f);
}

float Color::intToFloat(int x) {
    return static_cast<float>(clampInt(x)) / 255.0f;
}

uint32_t Color::toHex(float r, float g, float b, float a) {
    return (floatToUint8(r) << 24) | (floatToUint8(g) << 16) | (floatToUint8(b) << 8) | floatToUint8(a);
}

uint32_t Color::toHex() const {
    return toHex(r, g, b, a);
}
