#include <util/ColorPalette.h>

#include <INIReader.h>

#include <iostream>
#include <fstream>
#include <sstream>

ColorPalette::ColorPalette(const std::string &path)
    : path(path) {
    reload();
}

Color ColorPalette::parseColor(const std::string &value) {
    std::stringstream ss(value);
    int r, g, b, a;
    ss >> r >> g >> b >> a;
    return Color(r, g, b, a);
}

void ColorPalette::reload() {
    INIReader reader(path);
    if (reader.ParseError() < 0) {
        std::cerr << "ERROR::COLOR_PALETTE::INI_PARSE_FAILED (\"" << path << "\")\n";
        exit(-1);
    }

    colors[0] = parseColor(reader.Get("Colors", "default", "0 0 0 255"));

    for (size_t i = 1; i < 16; i++) {
        std::string color = reader.Get("Colors", std::format("color{}", i), "");
        if (color == "") {
            colors[i] = colors[0]; // Default color
        } else {
            colors[i] = parseColor(color);
        }
    }
}

const Color &ColorPalette::operator[](size_t index) const {
    return colors[index];
}