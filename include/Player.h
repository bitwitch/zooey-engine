#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm_subset.h"
#include "Entity.h"

struct Player : public Entity {
    float run_speed          = 20; 
    float turn_speed         = 160;
    float gravity            = -50;
    float jump_power         = 30;
    float current_speed      = 0;
    float current_turn_speed = 0;
    float current_jump_speed = 0;

    // TODO(shaw): Currently needed for input, should figure out a system to handle input
    GLFWwindow* window; 

    Player(GLFWwindow* window, TexturedModel& model, 
           glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    void move(float dt);
    void check_inputs();

};




