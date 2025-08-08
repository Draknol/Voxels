#include <render/Shader.h>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
    glewInit();

    uint32_t vertex = loadShader(vertexPath, GL_VERTEX_SHADER);
    uint32_t fragment = loadShader(fragmentPath, GL_FRAGMENT_SHADER);

    // Create shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    // Check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED";
    }

    GLint count;
    glGetProgramiv(ID, GL_ACTIVE_UNIFORMS, &count);

    char name[256]; // Increase size if needed
    for (GLint i = 0; i < count; ++i) {
        GLsizei length;
        GLint size;
        GLenum type;
        glGetActiveUniform(ID, i, sizeof(name), &length, &size, &type, name);

        std::string baseName(name);
        if (size > 1) {
            for (GLint j = 0; j < size; ++j) {
                std::string elementName = baseName;
                elementName = elementName.substr(0, elementName.size() - 3) + "[" + std::to_string(j) + "]";
                uniformLocations.insert_or_assign(elementName, glGetUniformLocation(ID, elementName.c_str()));
            }
        } else {
            uniformLocations.insert_or_assign(baseName, glGetUniformLocation(ID, baseName.c_str()));
        }
    }

    // Delete shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(ID);
}

uint32_t Shader::loadShader(const std::string &fileName, int shaderType) {
    std::ifstream file(fileName);

    // Check if file failed to open
    if (!file.is_open()) {
        std::cout << "ERROR::SHADER::FILE_OPEN_FAILED (" << fileName << ")\n";
        exit(1);
    }

    std::stringstream ssBuffer;
    ssBuffer << file.rdbuf();
    std::string strBuffer = ssBuffer.str();
    const char *code = strBuffer.c_str();

    uint32_t shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);

    // Check for compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        exit(1);
    }

    return shader;
}

void Shader::setActive() const {
    glUseProgram(ID);
}

void Shader::setUint(const std::string &name, uint32_t n) const {
    try {
        glUniform1ui(uniformLocations.at(name), n);
    } catch (const std::exception &e) {
        std::cout << "ERROR::SHADER::GET_UNIFORM_FAILED (" + name + ")\n";
    }
}

void Shader::setColor(const std::string &name, const Color &color) const {
    setUint(name, color.toHex());
}

void Shader::setColorPalette(const std::string &name, const ColorPalette &colorPalette) {
    for (size_t i = 0; i < 16u; i++) {
        setColor(std::format("{}[{}]", name, i), colorPalette[i]);
    }
}

void Shader::setVec3(const std::string &name, const glm::vec3 &vector) const {
    try {
        glUniform3fv(uniformLocations.at(name), 1, &vector.x);
    } catch (const std::exception &e) {
        std::cout << "ERROR::SHADER::GET_UNIFORM_FAILED (" + name + ")\n";
    }
}

void Shader::setUVec3(const std::string &name, const glm::uvec3 &vector) const {
    try {
        glUniform3uiv(uniformLocations.at(name), 1, &vector.x);
    } catch (const std::exception &e) {
        std::cout << "ERROR::SHADER::GET_UNIFORM_FAILED (" + name + ")\n";
    }
}

void Shader::setMat4(const std::string &name, const glm::mat4 &matrix) const {
    try {
        glUniformMatrix4fv(uniformLocations.at(name), 1, false, &matrix[0].x);
    } catch (const std::exception &e) {
        std::cout << "ERROR::SHADER::GET_UNIFORM_FAILED (" + name + ")\n";
    }
}