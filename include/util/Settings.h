#ifndef SETTINGS_H
#define SETTINGS_H

#include <glm/vec2.hpp>

#include <memory>
#include <string>

// Reads and writes settings to and from a .ini file.
// Run save() after setting to update .ini
namespace Settings {
void init(const std::string &settingsPath);

void save();
void load(const std::string &settingsPath);
void reload();

bool isFullscreen();
glm::ivec2 getSize();
int getWidth();
int getHeight();
float getFOV();
float getSensitivity();
bool isVSync();
bool isPrintFPS();

void setFullscreen(bool state);
void setSize(const glm::ivec2 &newSize);
void setWidth(int width);
void setHeight(int height);
void setFOV(float newFOV);
void setSensitivity(float sensitivity);
void setVSync(bool state);
void setPrintFPS(bool state);
} // namespace Settings

#endif