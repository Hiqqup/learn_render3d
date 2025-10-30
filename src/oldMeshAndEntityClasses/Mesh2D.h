//
// Created by ju on 10/28/25.
//

#pragma once



class Mesh2D {
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    int numberOfIndices;
public:
    Mesh2D();
    ~Mesh2D();

    void draw() const;
};