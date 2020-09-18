#include "Camera.h"
#include "Display.h"

Camera::Camera(GLFWwindow* window) : window(window) {}

void Camera::move(float dt) {
    float speed = 20;

    //  up & down
    if (glfwGetKey(window, GLFW_KEY_SPACE))
        position.y += speed * dt;
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
        position.y -= speed * dt;

    //  strafe left & right
    float current_strafe_speed = 0;
    if (glfwGetKey(window, GLFW_KEY_A))
        current_strafe_speed = -speed;
    else if (glfwGetKey(window, GLFW_KEY_D))
        current_strafe_speed = speed;

    // forward & back
    float current_speed = 0;
    if (glfwGetKey(window, GLFW_KEY_W))
        current_speed = -speed;
    else if (glfwGetKey(window, GLFW_KEY_S))
        current_speed = speed;

    // rotation
    float current_rot_speed = 0;
    float rot_speed = 140;
    if (glfwGetKey(window, GLFW_KEY_Q))
        current_rot_speed = -rot_speed;
    else if (glfwGetKey(window, GLFW_KEY_E))
        current_rot_speed = rot_speed;

    rotation.y += current_rot_speed * dt;

    // forward & back movement
    float distance = current_speed * dt;
    float rot_y = -glm::radians(rotation.y);
    float move_x = distance * sin(rot_y);
    float move_z = distance * cos(rot_y);

    // strafe movement
    float strafe_dist = current_strafe_speed * dt;
    float strafe_x = strafe_dist * sin(rot_y + 3.14159/2.0f);
    float strafe_z = strafe_dist * cos(rot_y + 3.14159/2.0f);

    position.x += move_x + strafe_x;
    position.z += move_z + strafe_z;
}

glm::vec3 Camera::getRotation() {
    return rotation;
}

glm::vec3 Camera::getPosition() {
    return position;
}

