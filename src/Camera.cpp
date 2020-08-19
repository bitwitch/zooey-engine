#include "Camera.h"

Camera::Camera(GLFWwindow* window) : window(window) {}

void Camera::move() {
    if (glfwGetKey(window, GLFW_KEY_W))
        position.y += 0.2f;
    if (glfwGetKey(window, GLFW_KEY_A))
        position.x -= 0.2f;
    if (glfwGetKey(window, GLFW_KEY_S))
        position.y -= 0.2f;
    if (glfwGetKey(window, GLFW_KEY_D))
        position.x += 0.2f;
    if (glfwGetKey(window, GLFW_KEY_Q))
        position.z -= 0.2f;
    if (glfwGetKey(window, GLFW_KEY_E))
        position.z += 0.2f;
}

glm::vec3 Camera::getRotation() {
    return rotation;
}

glm::vec3 Camera::getPosition() {
    return position;
}

