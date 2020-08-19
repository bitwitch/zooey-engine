#include "Camera.h"

Camera::Camera(GLFWwindow* window) : window(window) {}

void Camera::move() {
    if (glfwGetKey(window, GLFW_KEY_W))
        position.z -= 1.0f;
    if (glfwGetKey(window, GLFW_KEY_A))
        position.x -= 1.0f;
    if (glfwGetKey(window, GLFW_KEY_S))
        position.z += 1.0f;
    if (glfwGetKey(window, GLFW_KEY_D))
        position.x += 1.0f;
}

glm::vec3 Camera::getRotation() {
    return rotation;
}

glm::vec3 Camera::getPosition() {
    return position;
}

