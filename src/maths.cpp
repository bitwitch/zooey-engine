#include "maths.h"
#include "camera.h"

glm::mat4 Maths::create_transformation_matrix(
        glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
{
    glm::mat4 matrix = glm::mat4(1.0);
    matrix = glm::translate(matrix, translation);
    matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1.0f,0.0f,0.0f));
    matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0.0f,1.0f,0.0f));
    matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0.0f,0.0f,1.0f));
    matrix = glm::scale(matrix, scale);
    return matrix;
}

glm::mat4 Maths::create_view_matrix(Camera* camera)
{
    glm::mat4 matrix = glm::mat4(1.0);
    matrix = glm::rotate(matrix, glm::radians(camera->rotation.x), glm::vec3(1.0f,0.0f,0.0f));
    matrix = glm::rotate(matrix, glm::radians(camera->rotation.y), glm::vec3(0.0f,1.0f,0.0f));
    matrix = glm::rotate(matrix, glm::radians(camera->rotation.z), glm::vec3(0.0f,0.0f,1.0f));
    matrix = glm::translate(matrix, -camera->position);
    return matrix;
}


float Maths::lerp(float a, float b, float amount) {
    return a + (b - a) * amount;
}

glm::vec3 Maths::lerp(glm::vec3 a, glm::vec3 b, float amount) {
    glm::vec3 result;
    result.x = lerp(a.x, b.x, amount);
    result.y = lerp(a.y, b.y, amount);
    result.z = lerp(a.z, b.z, amount);
    return result;
}
