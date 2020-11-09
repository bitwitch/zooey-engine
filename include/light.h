#pragma once 

#include "glm_subset.h"

struct Light {
    glm::vec3 position;
    glm::vec3 color;
    Light(glm::vec3 position, glm::vec3 color) {
        this->position = position;
        this->color = color;
    }
};
