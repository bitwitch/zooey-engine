#include "Maths.h"

glm::mat4 Maths::createTransformationMatrix(
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

glm::mat4 Maths::createViewMatrix(Camera& camera)
{
    glm::mat4 matrix = glm::mat4(1.0);
    matrix = glm::rotate(matrix, glm::radians(camera.getRotation().x), glm::vec3(1.0f,0.0f,0.0f));
    matrix = glm::rotate(matrix, glm::radians(camera.getRotation().y), glm::vec3(0.0f,1.0f,0.0f));
    matrix = glm::rotate(matrix, glm::radians(camera.getRotation().z), glm::vec3(0.0f,0.0f,1.0f));
    matrix = glm::translate(matrix, -camera.getPosition());
    return matrix;
}
