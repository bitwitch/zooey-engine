#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm_subset.h"

class Camera {

private:
    glm::vec3 position { 0, 5, 0 };
    glm::vec3 rotation { 10, 0, 0 };
    GLFWwindow* window;

public:
    Camera(GLFWwindow* window);
    glm::vec3 getRotation();
    glm::vec3 getPosition();
    void move();

};
