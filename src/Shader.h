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
    Shader(const std::filesystem::path& vertexShaderPath =  "shaders/3d.vert"
        , const std::filesystem::path& fragmentShaderPath = "shaders/3d.frag");
    ~Shader();

    void setMatrix(const std::string &uniformName, const glm::mat4 &matrix) const;
    void setVector(const std::string &uniformName, const glm::vec4 &vector) const;

};
