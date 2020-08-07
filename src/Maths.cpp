#include "Maths.h"

glm::mat4 Math::createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, float scale)
{
    glm::mat4 matrix;
    matrix = glm::translate(matrix, translation);
    matrix = glm::rotate(matrix, rotation.x, glm::vec3(1.0f,0.0f,0.0f));
    matrix = glm::rotate(matrix, rotation.y, glm::vec3(0.0f,1.0f,0.0f));
    matrix = glm::rotate(matrix, rotation.z, glm::vec3(0.0f,0.0f,1.0f));
    matrix = glm::scale(matrix, glm::vec3(scale));
    return matrix;
}
