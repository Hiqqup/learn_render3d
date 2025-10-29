#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Mesh.h"
#include "Shader.h"
#include "tiny_gltf.h"
#include "Window.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh3d.h"


glm::mat4 calculateMvpMatrix(glm::vec3 position,  glm::vec3 scale, glm::vec3 rotation) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));


    glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 90.0f),
                                 glm::vec3(0.0f, 0.0f, 0.0),
                                 glm::vec3(0.0, 1.0, 0.0));

    glm::mat4 projection = glm::perspective(glm::radians(2.0f), 1000.0f/600.0f, 0.1f, 100.0f);

    return projection * view * model;
}
glm::mat4 calculateModelToWorldNormal(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    return glm::transpose(glm::inverse(model));
}

Window window;
glm::vec2 getMousePosition() {
    double xpos, ypos;
    glfwGetCursorPos(window.window, &xpos, &ypos);
    return {xpos, ypos};
}

auto position = glm::vec3(0.0f);
auto scale = glm::vec3(1.0f);
auto color =  glm::vec4(0.4f);
auto rotation = glm::vec3(0.0f);

auto mousePosition = getMousePosition();

void processInput() {
    auto newMousePosition = getMousePosition();
    glm::vec2 deltaMousePosition = mousePosition - newMousePosition;
    mousePosition = newMousePosition;

    int state = glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS)
    {
        rotation.y -= deltaMousePosition.x;
        rotation.x -= deltaMousePosition.y;
    }

}

int main() {

    Mesh3d mesh = Mesh3d("models/monkey.glb") ;
    Shader shader;
    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(window.window)) {

        processInput();

        glClearColor(0.172f, 0.243f, 0.313f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.setMatrix("mvp", calculateMvpMatrix(position,   scale, rotation));
        shader.setMatrix("modelToWorldNormal", calculateModelToWorldNormal(position,  scale , rotation));
        shader.setVector("color", color);
        mesh.draw();

        glfwSwapBuffers(window.window);
        glfwPollEvents();
    }



    return 0;
}
