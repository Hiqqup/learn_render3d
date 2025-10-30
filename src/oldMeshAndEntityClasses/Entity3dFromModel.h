//
// Created by ju on 10/29/25.
//

#pragma once
#include "Mesh3dFromModel.h"
#include "../Shader.h"
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "GLFW/glfw3.h"

class Entity3dFromModel {
    Mesh3dFromModel mesh;
    Shader shader;

    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(0.1f);
    glm::vec4 color =  glm::vec4(0.4f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec2 mousePosition;
public:
    Entity3dFromModel();
    void draw() const;
    void rotateWithMouse(GLFWwindow* window);
    glm::vec2 getDeltaMousePosition(GLFWwindow* window);
    void update(GLFWwindow* window);
};
