//
// Created by ju on 10/28/25.
//

#pragma once



class Mesh {
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    int numberOfIndices;
public:
    Mesh();
    ~Mesh();

    void draw() const;


};