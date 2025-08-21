#ifndef SHADER_H
#define SHADER_H

#include <unordered_map>
#include <string>

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

    uint32_t getLocation(const std::string &name);

    // Tells OpenGL to use this shader
    void setActive() const;
};

#endif