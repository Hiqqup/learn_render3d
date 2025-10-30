//
// Created by ju on 10/28/25.
//

#include "Mesh2D.h"
#include <glad/glad.h>
#include <vector>

std::vector<float> vertices = {
        -0.4f, 0.4f, 0.0f, // v1
        0.4f, 0.4f, 0.0f, // v2
        0.4f, -0.4f, 0.0f, // v3
        -0.4f, -0.4f, 0.0f, // v4
};
std::vector<unsigned int> indices = {
    0, 1, 2, // triangle1: v1, v2, v3
    0, 2, 3, // triangle2: v1, v3, v4
};

template<typename T>
GLuint createBuffer(GLuint bufferType, const std::vector<T> &bufferData) {
    unsigned int buffer = 0;
    glGenBuffers(1, &buffer);
    glBindBuffer(bufferType, buffer);
    glBufferData(bufferType, bufferData.size() * sizeof(T), bufferData.data(), GL_STATIC_DRAW);
    return buffer;
}

Mesh2D::Mesh2D():
    VBO (createBuffer( GL_ARRAY_BUFFER,vertices)),
    EBO ((createBuffer(GL_ELEMENT_ARRAY_BUFFER, indices))),
    numberOfIndices(indices.size())
{

    //idk if this belongs here
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) nullptr);
    glEnableVertexAttribArray(0);
}

Mesh2D::~Mesh2D() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Mesh2D::draw() const {
        // Bind VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        // Bind EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        // Draw
        glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, nullptr);
}
