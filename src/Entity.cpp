#include "entity.h"

Entity::Entity(Textured_Model& model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :
    model(model), position(position), rotation(rotation), _scale(scale) { }

void move(glm::vec3 movement) {
    position += movement;
}

void rotate(glm::vec3 _rotation) {
    rotation += rotation;
}

void scale(glm::vec3 scale) {
    _scale += scale;
}

