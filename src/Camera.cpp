#include "Camera.h"

void Camera::move() {
    //m_position.z -= 0.02f;
    //m_position.x -= 0.002f;
}

glm::vec3 Camera::getRotation() {
    return m_rotation;
}

glm::vec3 Camera::getPosition() {
    return m_position;
}

