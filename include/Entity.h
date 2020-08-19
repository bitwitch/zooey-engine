#include "TexturedModel.h"
#include "glm_subset.h"

class Entity {

private:
    TexturedModel& model;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 _scale;

public:
    Entity(TexturedModel& model, glm::vec3 position = { 0, 0, 0 }, 
                                 glm::vec3 rotation = { 0, 0, 0 }, 
                                 glm::vec3 scale    = { 1, 1, 1 });

    TexturedModel& getModel();
    glm::vec3 getPosition();
    glm::vec3 getRotation();
    glm::vec3 getScale();

    void move(float dx, float dy, float dz);
    void rotate(float dx, float dy, float dz);
    void scale(float dx, float dy, float dz);

};
