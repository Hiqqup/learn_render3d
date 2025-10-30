//
// Created by ju on 10/29/25.
//

#pragma once

#include <vector>

#include "../Shader.h"

std::vector <float> getCubeVertices();
std::vector <unsigned int> getCubeIndices();


class Mesh {
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    int numberOfIndices;
public:
    Mesh(
        const std::vector<float>& vertices = getCubeVertices(),
        const std::vector<unsigned int>& indices = getCubeIndices());
    ~Mesh();

    void draw() const;
};
class CubeWithNormals {
    Mesh mesh;
    Shader shader;
    float rotation = 0.0f;
    public:
    CubeWithNormals();
    void draw() const ;
    void update();
};
