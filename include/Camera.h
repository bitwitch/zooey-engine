#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm_subset.h"

class Camera {

private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    GLFWwindow* m_window;

public:
    Camera(GLFWwindow* window);
    glm::vec3 getRotation();
    glm::vec3 getPosition();
    void move();

};
