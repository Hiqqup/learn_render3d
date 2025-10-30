//
// Created by ju on 10/29/25.
//

#include <glm/gtc/matrix_transform.hpp>

#include "CubeWithNormals.h"

#include "glad/glad.h"
#include "glm/vec3.hpp"

std::vector <float> getCubeVertices() {
    return {
        // positions         // normals
        // Back face (-Z)
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,

        // Front face (+Z)
        -0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, 0.5f,   0.0f, 0.0f, 1.0f,

        // Left face (-X)
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,

        // Right face (+X)
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,

        // Top face (+Y)
        -0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, 0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, 0.0f,

        // Bottom face (-Y)
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f
    };
 }
std::vector <unsigned int> getCubeIndices() {
    return {
        0, 1, 2, 2, 3, 0,       // back
        4, 5, 6, 6, 7, 4,       // front
        8, 9,10,10,11, 8,       // left
       12,13,14,14,15,12,       // right
       16,17,18,18,19,16,       // top
       20,21,22,22,23,20        // bottom
    };
}


template<typename T>
GLuint createBuffer(GLuint bufferType, const std::vector<T> &bufferData) {
    unsigned int buffer = 0;
    glGenBuffers(1, &buffer);
    glBindBuffer(bufferType, buffer);
    glBufferData(bufferType, bufferData.size() * sizeof(T), bufferData.data(), GL_STATIC_DRAW);
    return buffer;
}

Mesh::Mesh( const std::vector<float>& vertices, const std::vector<unsigned int>& indices ):
    VBO (createBuffer( GL_ARRAY_BUFFER,vertices)),
    EBO ((createBuffer(GL_ELEMENT_ARRAY_BUFFER, indices))),
    numberOfIndices(indices.size())
{

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Position attribute
    glVertexAttribPointer(
        0,                  // layout location 0
        3,                  // 3 floats for position
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),  // stride: 6 floats per vertex
        (void*)0            // offset 0
    );
    glEnableVertexAttribArray(0);

    // Normal attribute (optional for later)
    glVertexAttribPointer(
        1,                        // layout location 1
        3,                        // 3 floats for normal
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),        // stride: 6 floats per vertex
        (void*)(3 * sizeof(float)) // offset: after the first 3 floats
    );
    glEnableVertexAttribArray(1);
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Mesh::draw() const {
        glBindVertexArray(VAO);
        //glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        // Draw
        glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, nullptr);
}

glm::mat4 getTransformation(float rotation) {
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(rotation), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::rotate(trans, glm::radians(rotation/2), glm::vec3(0.0, 1.0, 0.0));
    trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(1.0, 0.0, 0.0));
    return trans;
}

glm::mat4 getNormalsTransformation(float rotation) {
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::rotate(model, glm::radians(rotation/2), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    return glm::transpose(glm::inverse(model));
}

void CubeWithNormals::draw() const {
        shader.use();
        shader.setVector("color", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        shader.setMatrix("transform", getTransformation(rotation) );
        shader.setMatrix("normalTransform", getNormalsTransformation(rotation));
        mesh.draw();
}

void CubeWithNormals::update() {
        rotation += 1;
        if (rotation >= 360.0) {
            rotation = 0;
        }
}

CubeWithNormals::CubeWithNormals() :
shader("shaders/my3d.vert", "shaders/my3d.frag")
{
}
