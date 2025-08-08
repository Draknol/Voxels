#ifndef COLOR_PALETTE_H
#define COLOR_PALETTE_H

#include <util/Color.h>

#include <string>

class ColorPalette {
private:
    std::string path;

    Color colors[16];

    Color parseColor(const std::string &value);

public:
    ColorPalette(const std::string &path);

    void reload();

    const Color &operator[](size_t index) const;
};

#endif