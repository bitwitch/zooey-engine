#include "Camera.h"

Camera::Camera(GLFWwindow* window) : m_window(window) {}

void Camera::move() {
    if (glfwGetKey(m_window, GLFW_KEY_W))
        m_position.z -= 1.0f;
    if (glfwGetKey(m_window, GLFW_KEY_A))
        m_position.x -= 1.0f;
    if (glfwGetKey(m_window, GLFW_KEY_S))
        m_position.z += 1.0f;
    if (glfwGetKey(m_window, GLFW_KEY_D))
        m_position.x += 1.0f;
}

glm::vec3 Camera::getRotation() {
    return m_rotation;
}

glm::vec3 Camera::getPosition() {
    return m_position;
}

