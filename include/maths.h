#pragma once 

#include "glm_subset.h"

struct Camera; 

struct Maths {

    static glm::mat4 
    create_transformation_matrix(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale);

    static glm::mat4 
    create_view_matrix(Camera* camera);

    static glm::vec3 
    lerp(glm::vec3 a, glm::vec3 b, float amount);

    static float 
    lerp(float a, float b, float amount);

};
