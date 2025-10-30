//
// Created by ju on 10/29/25.
//

#include "Entity3dFromModel.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Entity3dFromModel::Entity3dFromModel():
mesh(Mesh3dFromModel("models/monkey.glb")),
shader("shaders/3d.vert" , "shaders/3d.frag"){
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


glm::vec2 getMousePosition(GLFWwindow* window) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return {xpos, ypos};
}
void Entity3dFromModel::rotateWithMouse(GLFWwindow *window) {
    auto deltaMousePosition = getDeltaMousePosition(window);

    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS)
    {
        rotation.y -= deltaMousePosition.x;
        rotation.x -= deltaMousePosition.y;
    }
}

bool firstMousePos = true;
glm::vec2 Entity3dFromModel::getDeltaMousePosition(GLFWwindow *window) {
    if (firstMousePos) {
        firstMousePos = false;
        mousePosition = getMousePosition(window);
        return {0,0};
    }
    auto newMousePosition = getMousePosition(window);
    glm::vec2 deltaMousePosition = mousePosition - newMousePosition;
    mousePosition = newMousePosition;
    return deltaMousePosition;
}
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

glm::mat4 calculateMvpMatrix(glm::vec3 position,  glm::vec3 scale, glm::vec3 rotation) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));


   // const float radius = 90.0f;
   // float camX = sin(glfwGetTime()) * radius;
   // float camZ = cos(glfwGetTime()) * radius;
    glm::mat4 view;

    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    //view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    //glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 90.0f),
    //                             glm::vec3(0.0f, 0.0f, 0.0),
    //                             glm::vec3(0.0, 1.0, 0.0));

    glm::mat4 projection = glm::perspective(glm::radians(30.f), 1000.0f/600.0f, 0.1f, 100.0f);

    return projection * view * model;
}
float yaw   = -90.0f;
float pitch = 0.0f;

void  Entity3dFromModel::update(GLFWwindow* window) {

glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  const float cameraSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += glm::normalize( cameraFront) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= glm::normalize( cameraFront) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    //rotateWithMouse(window);

    glm::vec2 mouseDelta = getDeltaMousePosition(window);
    float sensitivity = 0.02f;
    mouseDelta*= sensitivity;

    yaw   -= mouseDelta.x;
    pitch += mouseDelta.y;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);

}
void Entity3dFromModel::draw() const {

    shader.use();
    shader.setMatrix("mvp", calculateMvpMatrix(position,   scale, rotation));
    shader.setMatrix("modelToWorldNormal", calculateModelToWorldNormal(position,  scale , rotation));
    shader.setVector("color", color);
    mesh.draw();
}
