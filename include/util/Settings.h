#ifndef SETTINGS_H
#define SETTINGS_H

#include <glm/vec2.hpp>

#include <memory>
#include <string>

// Reads and writes settings to and from a .ini file.
// Run save() after setting to update .ini
class Settings {
private:
    std::string path;

    glm::ivec2 size;
    float fov;
    bool vSync;
    bool printFPS;

    std::string boolToOnOff(bool value);

public:
    Settings(const std::string &path);

    void save();
    void reload();

    glm::ivec2 getSize() const { return size; }
    int getWidth() const { return size.x; }
    int getHeight() const { return size.y; }
    float getFOV() const { return fov; }
    bool isVSync() const { return vSync; }
    bool isPrintFPS() const { return printFPS; }

    void setSize(const glm::ivec2 &size) { this->size = size; }
    void setWidth(int width) { size.x = width; }
    void setHeight(int height) { size.y = height; }
    void setFOV(float fov) { this->fov = fov; }
    void setVSync(bool state) { vSync = state; }
    void setPrintFPS(bool state) { printFPS = state; }
};

#endif