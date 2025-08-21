#include <util/Settings.h>

#include <INIReader.h>

#include <iostream>
#include <fstream>

namespace {
std::string path = "";

bool fullscreen = false;
glm::ivec2 size = glm::ivec2(800, 800); // ignored in fullscreen
float fov = 90.0f;
float sensitivity = 0.15f;
bool vSync = true;
bool printFPS = false;

std::string boolToOnOff(bool value) {
    return value ? "on" : "off";
}
} // namespace

namespace Settings {
void init(const std::string &settingsPath) {
    path = settingsPath;
    reload();
}

void save() {
    std::ofstream file(path);

    // Window
    file << "[Graphics]\n"
         << "fullscreen = " << boolToOnOff(fullscreen) << "\n"
         << "width = " << size.x << "\n"
         << "height = " << size.y << "\n"
         << "fov = " << fov << "\n"
         << "sensitivity = " << sensitivity << "\n"
         << "vSync = " << boolToOnOff(vSync) << "\n"
         << "printFPS = " << boolToOnOff(printFPS) << "\n";

    file.close();
}

void load(const std::string &settingsPath) {
    path = settingsPath;
    reload();
}

void reload() {
    if (path.empty()) {
        return;
    }

    INIReader reader(path);
    if (reader.ParseError() != 0) {
        std::cerr << "ERROR::INI_PARSE_FAILED (\"" << path << "\")\n";
        exit(-1);
    }

    // Graphics
    fullscreen = reader.GetBoolean("Graphics", "fullscreen", fullscreen);
    size.x = reader.GetInteger("Graphics", "width", size.x);
    size.y = reader.GetInteger("Graphics", "height", size.y);
    fov = reader.GetReal("Graphics", "fov", fov);
    sensitivity = reader.GetReal("Graphics", "sensitivity", sensitivity);
    vSync = reader.GetBoolean("Graphics", "vSync", vSync);
    printFPS = reader.GetBoolean("Graphics", "printFPS", printFPS);
}

bool isFullscreen() { return fullscreen; }
glm::ivec2 getSize() { return size; }
int getWidth() { return size.x; }
int getHeight() { return size.y; }
float getFOV() { return fov; }
float getSensitivity() { return sensitivity; }
bool isVSync() { return vSync; }
bool isPrintFPS() { return printFPS; }

void setFullscreen(bool state) { fullscreen = state; }
void setSize(const glm::ivec2 &newSize) { size = newSize; }
void setWidth(int width) { size.x = width; }
void setHeight(int height) { size.y = height; }
void setFOV(float newFOV) { fov = newFOV; }
void setSensitivity(float sensitivity) { sensitivity = sensitivity; }
void setVSync(bool state) { vSync = state; }
void setPrintFPS(bool state) { printFPS = state; }
} // namespace Settings