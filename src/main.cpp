#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Mesh.h"
#include "Shader.h"
#include "tiny_gltf.h"
#include "Window.h"


int main() {

    Window window;
    Mesh mesh;
    Shader shader;


    while(!glfwWindowShouldClose(window.window)) {
        glClearColor(0.172f, 0.243f, 0.313f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        mesh.draw();

        glfwSwapBuffers(window.window);
        glfwPollEvents();
    }



    return 0;
}
