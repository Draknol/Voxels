#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <util/ColorPalette.h>

#include <glm/mat4x4.hpp>

namespace ShaderManager {
void init();

/// @brief Loads a new Shader
/// @return Index to use in setActiveShader
uint32_t addShader(const std::string &vertexPath, const std::string &fragmentPath);

/// @brief Sets which Shader to use
/// @param index Index returned on addShader
void setActiveShader(uint32_t index);

// Set a uint uniform for the active shader
void setUint(const std::string &name, uint32_t n);

// Set a Color uniform for the active shader
void setColor(const std::string &name, const Color &color);

// Set a ColorPalette uniform for the active shader
void setColorPalette(const std::string &name, const ColorPalette &colorPalette);

// Set a vec3 uniform for the active shader
void setVec3(const std::string &name, const glm::vec3 &vector);

// Set a uvec3 uniform for the active shader
void setUVec3(const std::string &name, const glm::uvec3 &vector);

// Set a mat4 uniform for the active shader
void setMat4(const std::string &name, const glm::mat4 &matrix);
} // namespace ShaderManager

#endif