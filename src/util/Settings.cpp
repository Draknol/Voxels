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
    file << "[Graphics]\n"
         << "width = " << size.x << "\n"
         << "height = " << size.y << "\n"
         << "fov = " << fov << "\n"
         << "vSync = " << boolToOnOff(vSync) << "\n"
         << "printFPS = " << boolToOnOff(printFPS) << "\n";

    file.close();
}

void Settings::reload() {
    INIReader reader(path);
    if (reader.ParseError() < 0) {
        std::cerr << "ERROR::SETTINGS::INI_PARSE_FAILED (\"" << path << "\")\n";
        exit(-1);
    }

    // Window (default 800x800, VSync)
    size.x = reader.GetInteger("Graphics", "width", 800);
    size.y = reader.GetInteger("Graphics", "height", 800);
    fov = reader.GetReal("Graphics", "fov", 90.0);
    vSync = reader.GetBoolean("Graphics", "vSync", true);
    printFPS = reader.GetBoolean("Graphics", "printFPS", false);
}

std::string Settings::boolToOnOff(bool value) {
    return value ? "on" : "off";
}