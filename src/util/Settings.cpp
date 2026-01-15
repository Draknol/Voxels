#include <util/Settings.h>

#include <INIReader.h>

#include <iostream>
#include <fstream>

namespace {
std::string userPath = "";
std::string worldPath = "";

// Graphics
bool fullscreen = false;
glm::ivec2 size = glm::ivec2(800, 800); // ignored in fullscreen
float fov = 90.0f;
float sensitivity = 0.15f;
bool vSync = true;
bool printFPS = false;

// World Size
size_t xChunks = 1u;
size_t yChunks = 1u;
size_t zChunks = 1u;

// Perlin
float amplitude = 128.0f;
float frequency = 0.007f;
float octCount = 4u;

// Materials
Material materials[16];

std::string boolToOnOff(bool value) {
    return value ? "on" : "off";
}
} // namespace

namespace Settings {
void load(const std::string &userSettingsPath, const std::string &worldSettingsPath) {
    userPath = userSettingsPath;
    worldPath = worldSettingsPath;
    reload();
}

void save() {
    std::ofstream userFile(userPath);

    userFile << "[Graphics]\n"
             << "fullscreen = " << boolToOnOff(fullscreen) << "\n"
             << "width = " << size.x << "\n"
             << "height = " << size.y << "\n"
             << "fov = " << fov << "\n"
             << "sensitivity = " << sensitivity << "\n"
             << "vSync = " << boolToOnOff(vSync) << "\n"
             << "printFPS = " << boolToOnOff(printFPS) << "\n";

    userFile.close();

    std::ofstream worldFile(worldPath);

    worldFile << "[WorldSize]\n"
              << "xChunks = " << xChunks << "\n"
              << "yChunks = " << yChunks << "\n"
              << "zChunks = " << zChunks << "\n"

              << "[Perlin]\n"
              << "amplitude = " << amplitude << "\n"
              << "frequency = " << frequency << "\n"
              << "octCount = " << octCount << "\n"

              << "[Materials]\n"
              << "# Used for invalid materials"
              << "default = " << materials[0].color.toHex() << "\n ";

    for (size_t i = 1u; i < 16u; i++) {
        const Material &mat = materials[i];
        const Color &color = materials[i].color;

        worldFile << "\n# " << mat.name << "\n"
                  << "mat" << i << "FillDirection = " << mat.fillDirection << "\n"
                  << "mat" << i << "Offset = " << mat.offset << "\n"
                  << "mat" << i << "MinDepth = " << mat.minDepth << "\n"
                  << "mat" << i << "MaxDepth = " << mat.maxDepth << "\n"
                  << "mat" << i << "Color = " << mat.color.toHex() << "\n";
    }

    worldFile.close();
}

void reload() {
    if (!userPath.empty()) {
        INIReader reader(userPath);
        if (reader.ParseError() != 0) {
            std::cerr << "ERROR::INI_PARSE_FAILED (\"" << userPath << "\")\n";
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

    if (!worldPath.empty()) {
        INIReader reader(worldPath);
        if (reader.ParseError() != 0) {
            std::cerr << "ERROR::INI_PARSE_FAILED (\"" << worldPath << "\")\n";
            exit(-1);
        }

        // World Size
        xChunks = reader.GetInteger("WorldSize", "xChunks", 1u);
        yChunks = reader.GetInteger("WorldSize", "yChunks", 1u);
        zChunks = reader.GetInteger("WorldSize", "zChunks", 1u);

        // Perlin
        amplitude = reader.GetReal("Perlin", "amplitude", 128.0f);
        frequency = reader.GetReal("Perlin", "frequency", 0.007f);
        octCount = reader.GetInteger("Perlin", "octCount", 4u);

        // Materials
        materials[0] = Material();
        materials[0].name = "default";
        materials[0].color = Color(reader.GetInteger("Materials", "default", 0x000000FF));

        for (size_t i = 1u; i < 15u; i++) {
            materials[i].name = reader.GetString("Materials", "mat" + std::to_string(i) + "Name", materials[0].name);
            materials[i].fillDirection = (FillDirection)reader.GetInteger("Materials", "mat" + std::to_string(i) + "FillDirection", materials[0].fillDirection);
            materials[i].offset = reader.GetInteger("Materials", "mat" + std::to_string(i) + "Offset", materials[0].offset);
            materials[i].minDepth = reader.GetInteger("Materials", "mat" + std::to_string(i) + "MinDepth", materials[0].minDepth);
            materials[i].maxDepth = reader.GetInteger("Materials", "mat" + std::to_string(i) + "MaxDepth", materials[0].maxDepth);
            materials[i].color = reader.GetUnsigned("Materials", "mat" + std::to_string(i) + "Color", materials[0].color.toHex());
            materials[i].isBound = reader.GetBoolean("Materials", "mat" + std::to_string(i) + "IsBound", true);
        }
    }
}

// Graphics
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

// World Size
size_t getXChunks() { return xChunks; }
size_t getYChunks() { return yChunks; }
size_t getZChunks() { return zChunks; }

void setXChunks(size_t size) { xChunks = size; }
void setYChunks(size_t size) { yChunks = size; }
void setZChunks(size_t size) { zChunks = size; }

// Perlin
float getAmplitude() { return amplitude; }
float getFrequency() { return frequency; }
float getOctCount() { return octCount; }

void setAmplitude(float a) { amplitude = a; }
void setFrequency(float f) { frequency = f; }
void setOctCount(float o) { octCount = o; }

// Materials
const Material &getMaterial(size_t index) { return materials[index]; }

void setMaterial(size_t index, const Material &material) { materials[index] = material; }

} // namespace Settings