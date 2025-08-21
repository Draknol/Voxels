#include <render/Shader.h>

#include <GL/glew.h>

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
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

    char name[256];
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

uint32_t Shader::getLocation(const std::string &name) {
    return uniformLocations.at(name);
}

void Shader::setActive() const {
    glUseProgram(ID);
}