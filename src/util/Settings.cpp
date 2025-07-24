#include <util/Settings.h>

#include <INIReader.h>

#include <iostream>
#include <fstream>

Settings::Settings(const std::string &path)
    : path(path) {
    reload();
}

void Settings::save() {
    std::ofstream file(path);

    // Window
    file << "[Window]\n"
         << "width = " << width << "\n"
         << "height = " << height << "\n"
         << "vSync = " << boolToOnOff(vSync) << "\n";

    file.close();
}

void Settings::reload() {
    INIReader reader(path);
    if (reader.ParseError() < 0) {
        std::cerr << "ERROR::SETTINGS::INI_PARSE_FAILED (\"" << path << "\")\n";
        exit(-1);
    }

    // Window (default 800x800, VSync)
    width = reader.GetInteger("Window", "width", 800);
    height = reader.GetInteger("Window", "height", 800);
    vSync = reader.GetBoolean("Window", "vSync", true);
}

const std::string &Settings::boolToOnOff(bool value) {
    return value ? "on" : "off";
}