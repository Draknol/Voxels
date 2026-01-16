#ifndef SETTINGS_H
#define SETTINGS_H

#include <util/Material.h>

#include <glm/vec2.hpp>

#include <memory>
#include <string>

// Reads and writes settings to and from a .ini file.
// Run save() after setting to update .ini
namespace Settings {
void load(const std::string &userSettingsPath, const std::string &worldSettingsPath);
void save();
void reload();

// Constants
static constexpr size_t CHUNK_SIZE = 16u;

// Graphics
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

// World Size
size_t getXChunks();
size_t getYChunks();
size_t getZChunks();
size_t getBottomTrim();
size_t getTopTrim();

void setXChunks(size_t size);
void setYChunks(size_t size);
void setZChunks(size_t size);
void setBottomTrim(size_t size);
void setTopTrim(size_t size);

// Perlin
float getAmplitude();
float getFrequency();
float getOctCount();

void setAmplitude(float a);
void setFrequency(float f);
void setOctCount(float o);

// Materials
const Material &getMaterial(size_t index);

void setMaterial(size_t index, const Material &material);

} // namespace Settings

#endif