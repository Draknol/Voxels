#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

/// @brief Reads and writes settings to and from a .ini file.
/// Run save() after setting to update .ini
class Settings {
private:
    std::string path;

    int width;
    int height;
    bool vSync;

    std::string boolToOnOff(bool value);

public:
    Settings(const std::string &path);

    void save();
    void reload();

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    bool isVSync() const { return vSync; }

    void setWidth(int w) { width = w; }
    void setHeight(int h) { height = h; }
    void setVSync(bool v) { vSync = v; }
};

#endif