#ifndef SHADER_H
#define SHADER_H

#include <util/ColorPalette.h>

#include <glm/mat4x4.hpp>

#include <string>
#include <unordered_map>

class Shader {
private:
    uint32_t ID;
    std::unordered_map<std::string, uint32_t> uniformLocations;

    /// @brief Reads a shader file into a string
    /// @param path Path to the shader
    /// @param shaderCode string to store the shader code in
    void getShader(const std::string &path, std::string &shaderCode);

    /// @brief Load a shader from a file
    /// @param shaderType GLenum for type of shader (eg Gl_VERTEX_SHADER)
    /// @return Shader ID from glCreateShader
    uint32_t loadShader(const std::string &path, int shaderType);

public:
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    ~Shader();

    Shader(const Shader &) = delete;
    Shader &operator=(const Shader &) = delete;

    // Tells OpenGL to use this shader
    void setActive() const;

    // Set a uint uniform (call setActive first)
    void setUint(const std::string &name, uint32_t n) const;

    // Set a Color uniform (call setActive first)
    void setColor(const std::string &name, const Color &color) const;

    // Set a ColorPalette uniform (call setActive first)
    void setColorPalette(const std::string &name, const ColorPalette &colorPalette);

    // Set a vec3 uniform (call setActive first)
    void setVec3(const std::string &name, const glm::vec3 &vector) const;

    // Set a uvec3 uniform (call setActive first)
    void setUVec3(const std::string &name, const glm::uvec3 &vector) const;

    // Set a mat4 uniform (call setActive first)
    void setMat4(const std::string &name, const glm::mat4 &matrix) const;
};

#endif