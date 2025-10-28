//
// Created by ju on 10/28/25.
//

#pragma once
#include <filesystem>
#include <string>



class Shader {
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;
    public:
    Shader(const std::filesystem::path& vertexShaderPath = "shaders/2d.vert"
        , const std::filesystem::path& fragmentShaderPath = "shaders/2d.frag");
    ~Shader();
};