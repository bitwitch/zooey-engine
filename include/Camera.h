#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm_subset.h"

class Camera {

private:
    glm::vec3 position;
    glm::vec3 rotation;
    GLFWwindow* window;

public:
    Camera(GLFWwindow* window);
    glm::vec3 getRotation();
    glm::vec3 getPosition();
    void move();

};
