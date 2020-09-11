#pragma once 

#include "glm_subset.h"
#include "Camera.h"

class Maths {

public:

    static glm::mat4 
    createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale);

    static glm::mat4 
    createViewMatrix(Camera& camera);

    static glm::vec3 
    lerp(glm::vec3 a, glm::vec3 b, float amount);

    static float 
    lerp(float a, float b, float amount);

};
