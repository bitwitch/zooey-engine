#include "entity.h"

Entity::Entity(Textured_Model* model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :
    model(model), position(position), rotation(rotation), my_scale(scale) { }

void Entity::move(glm::vec3 movement) {
    position += movement;
}

void Entity::rotate(glm::vec3 _rotation) {
    rotation += _rotation;
}

void Entity::scale(glm::vec3 scale) {
    my_scale += scale;
}

