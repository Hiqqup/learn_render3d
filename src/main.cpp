#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "tiny_gltf.h"
#include "Window.h"
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include "oldMeshAndEntityClasses/CubeWithNormals.h"
#include "oldMeshAndEntityClasses/Entity3dFromModel.h"


int main() {


    Window window;
    glEnable(GL_DEPTH_TEST);

    //CubeWithNormals entity;
    Entity3dFromModel entity;
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );//wireframe mode

    while(!glfwWindowShouldClose(window.window)) {

        entity.update(window.window);
        glClearColor(0.172f, 0.243f, 0.313f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        entity.draw();
//e

        glfwSwapBuffers(window.window);
        glfwPollEvents();
    }



    return 0;
}
