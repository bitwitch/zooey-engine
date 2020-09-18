#include "Player.h"

Player::Player(GLFWwindow* window, TexturedModel& model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : Entity(model, position, rotation, scale) 
{ 
    this->window = window;
};

void Player::move(float dt) {
    //check_inputs();
    //Entity::rotate(0, current_turn_speed * dt, 0);

    //float distance = current_speed * dt;
    //float rot_y = glm::radians(rotation.y);
    //float move_x = distance * sin(rot_y);
    //float move_z = distance * cos(rot_y);

    //Entity::move(move_x, 0, move_z);
}

void Player::check_inputs() {
    if (glfwGetKey(window, GLFW_KEY_W))
        current_speed = run_speed;
    else if (glfwGetKey(window, GLFW_KEY_S))
        current_speed = -run_speed;
    else
        current_speed = 0;

    if (glfwGetKey(window, GLFW_KEY_A))
        current_turn_speed = turn_speed;
    else if (glfwGetKey(window, GLFW_KEY_D))
        current_turn_speed = -turn_speed;
    else
        current_turn_speed = 0;
}

