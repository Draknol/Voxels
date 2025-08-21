#include <render/ShaderManager.h>

#include <render/Shader.h>

#include <util/ColorPalette.h>

#include <GL/glew.h>

#include <iostream>
#include <vector>
#include <memory>

namespace {
static inline uint32_t activeID = 0;
static inline std::vector<std::unique_ptr<Shader>> shaders;
} // namespace

namespace ShaderManager {
void init() {
    glewInit();
}

uint32_t ShaderManager::addShader(const std::string &vertexPath, const std::string &fragmentPath) {
    shaders.emplace_back(std::make_unique<Shader>(vertexPath, fragmentPath));
    return shaders.size() - 1u;
}

void ShaderManager::setActiveShader(uint32_t index) {
    activeID = index;
    shaders.at(activeID)->setActive();
}

void ShaderManager::setUint(const std::string &name, uint32_t n) {
    try {
        glUniform1ui(shaders.at(activeID)->getLocation(name), n);
    } catch (const std::exception &e) {
        std::cout << "ERROR::SHADER::GET_UNIFORM_FAILED (" + name + ")\n";
    }
}

void ShaderManager::setColor(const std::string &name, const Color &color) {
    setUint(name, color.toHex());
}

void ShaderManager::setColorPalette(const std::string &name, const ColorPalette &colorPalette) {
    for (size_t i = 0; i < 16u; i++) {
        setColor(std::format("{}[{}]", name, i), colorPalette[i]);
    }
}

void ShaderManager::setVec3(const std::string &name, const glm::vec3 &vector) {
    try {
        glUniform3fv(shaders.at(activeID)->getLocation(name), 1, &vector.x);
    } catch (const std::exception &e) {
        std::cout << "ERROR::SHADER::GET_UNIFORM_FAILED (" + name + ")\n";
    }
}

void ShaderManager::setUVec3(const std::string &name, const glm::uvec3 &vector) {
    try {
        glUniform3uiv(shaders.at(activeID)->getLocation(name), 1, &vector.x);
    } catch (const std::exception &e) {
        std::cout << "ERROR::SHADER::GET_UNIFORM_FAILED (" + name + ")\n";
    }
}

void ShaderManager::setMat4(const std::string &name, const glm::mat4 &matrix) {
    try {
        glUniformMatrix4fv(shaders.at(activeID)->getLocation(name), 1, false, &matrix[0].x);
    } catch (const std::exception &e) {
        std::cout << "ERROR::SHADER::GET_UNIFORM_FAILED (" + name + ")\n";
    }
}
} // namespace ShaderManager