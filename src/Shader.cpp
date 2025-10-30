//
// Created by ju on 10/28/25.
//

#include "Shader.h"

#include <fstream>
#include <stdexcept>
#include <glad/glad.h>
#include <string>
#include <unistd.h>

#include "Assets.h"
#include "glm/gtc/type_ptr.hpp"

struct glStatusData {
    int success;
    const char *shaderName;
    char infoLog[GL_INFO_LOG_LENGTH];
};
unsigned int loadAndCompileShader(GLuint shaderType, const std::string & shaderSource) {
    auto source = shaderSource.c_str();
    unsigned int shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, &source, nullptr);
    glCompileShader(shaderID);

    glStatusData compilationStatus{};
    compilationStatus.shaderName = shaderType == GL_VERTEX_SHADER ? "Vertex" : "Fragment";
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilationStatus.success);
    if(compilationStatus.success == GL_FALSE) {
        glGetShaderInfoLog(shaderID, GL_INFO_LOG_LENGTH, nullptr, compilationStatus.infoLog);
        throw std::runtime_error("ERROR: " + std::string(compilationStatus.shaderName) + " shader compilation failed.\n" +
        std::string(compilationStatus.infoLog));
    }
    return shaderID;
}
std::string readText(const std::filesystem::path &filePath) {
    std::ifstream sourceFile(resolveAssetPath(filePath));
    std::stringstream buffer;
    buffer << sourceFile.rdbuf();
    return buffer.str();
}



Shader::Shader(const std::filesystem::path &vertexShaderPath, const std::filesystem::path &fragmentShaderPath) {
    const std::string vertexShaderSource = readText(vertexShaderPath);
    const std::string fragmentShaderSource = readText(fragmentShaderPath);
    vertexShader = loadAndCompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    fragmentShader = loadAndCompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
}

Shader::~Shader() {
    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() const {
    glUseProgram(shaderProgram);
}

void Shader::setMatrix(const std::string &uniformName, const glm::mat4 &matrix) const {
    const int uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setVector(const std::string &uniformName,const  glm::vec4& vector)const {
    const int uniformLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniform4fv(uniformLocation, 1, glm::value_ptr(vector));
}
