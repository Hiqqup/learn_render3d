//
// Created by ju on 10/28/25.
//

#pragma once
#include <filesystem>
#include <string>

#include "glm/fwd.hpp"


class Shader {
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;
    public:
    Shader(const std::filesystem::path& vertexShaderPath
        , const std::filesystem::path& fragmentShaderPath  );
    ~Shader();
    void use() const;

    void setMatrix(const std::string &uniformName, const glm::mat4 &matrix) const;
    void setVector(const std::string &uniformName, const glm::vec4 &vector) const;

};
