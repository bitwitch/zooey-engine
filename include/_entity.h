#pragma once 

#include "glm_subset.h"

struct Textured_Model;

struct Entity {
    Textured_Model* model;
    glm::vec3 position = {0,0,0};
    glm::vec3 rotation = {0,0,0};
    glm::vec3 _scale   = {1,1,1}; // _ to avoid name collision with scale function

    Entity(Textured_Model& model, glm::vec3 position = { 0, 0, 0 }, 
                                 glm::vec3 rotation = { 0, 0, 0 }, 
                                 glm::vec3 scale    = { 1, 1, 1 });

    void move(glm::vec3 movement);
    void rotate(glm::vec3 rotation);
    void scale(glm::vec3 scale);
};

