#include "TexturedModel.h"
#include "glm_subset.h"

class Entity {

private:
    TexturedModel& m_model;
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;

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
