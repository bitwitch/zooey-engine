#include "Camera.h"

Camera::Camera(GLFWwindow* window) : window(window) {}

void Camera::move() {
    float multiplier = 5.0f;
    if (glfwGetKey(window, GLFW_KEY_W))
        position.y += 0.2f * multiplier;
    if (glfwGetKey(window, GLFW_KEY_A))
        position.x -= 0.2f * multiplier;
    if (glfwGetKey(window, GLFW_KEY_S))
        position.y -= 0.2f * multiplier;
    if (glfwGetKey(window, GLFW_KEY_D))
        position.x += 0.2f * multiplier;
    if (glfwGetKey(window, GLFW_KEY_Q))
        position.z -= 0.2f * multiplier;
    if (glfwGetKey(window, GLFW_KEY_E))
        position.z += 0.2f * multiplier;
}

glm::vec3 Camera::getRotation() {
    return rotation;
}

glm::vec3 Camera::getPosition() {
    return position;
}

