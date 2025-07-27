#ifndef SHADER_H
#define SHADER_H

#include <glm/mat4x4.hpp>

#include <string>
#include <unordered_map>

class Shader {
private:
    unsigned int ID;
    std::unordered_map<std::string, unsigned int> uniformLocations;

    /// @brief Reads a shader file into a string
    /// @param path Path to the shader
    /// @param shaderCode string to store the shader code in
    void getShader(const std::string &path, std::string &shaderCode);

    /// @brief Load a shader from a file
    /// @param path Path to the shader
    /// @param shaderType GLenum for type of shader (eg Gl_VERTEX_SHADER)
    /// @return Shader ID from glCreateShader
    unsigned int loadShader(const std::string &path, int shaderType);

public:
    /// @brief Initialises a shader program with a vertex and fragment shader
    /// @param vertexPath Path to the vertex shader
    /// @param fragmentPath Path to the fragment shader
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    ~Shader();

    Shader(const Shader &) = delete;
    Shader &operator=(const Shader &) = delete;

    /// @brief Tells OpenGL to use this shader
    void setActive() const;

    /// @brief Set a vec3 uniform (call setActive first)
    void setVec3(const std::string &name, const glm::vec3 &vector);

    /// @brief Set a mat4 uniform (call setActive first)
    void setMat4(const std::string &name, const glm::mat4 &matrix);
};

#endif