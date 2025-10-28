//
// Created by ju on 10/28/25.
//

#pragma once
#include <glad/glad.h>
#include <iostream>
#include "GLFW/glfw3.h"


class Window {
    public:
    GLFWwindow* window;
    Window();
    ~Window();
};
