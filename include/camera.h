#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm_subset.h"

struct Camera {
    glm::vec3 position { 0, 5, 0 };
    glm::vec3 rotation { 10, 0, 0 };
    GLFWwindow* window;

    Camera(GLFWwindow* _window) { window = _window; }
    void move();
};



