#include "Entity.h"

Entity::Entity(TexturedModel& model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :
    model(model), position(position), rotation(rotation), _scale(scale) { }

TexturedModel& Entity::getModel() {
    return model;
}

glm::vec3 Entity::getPosition() {
    return position;
}

glm::vec3 Entity::getRotation() {
    return rotation;
}

glm::vec3 Entity::getScale() {
    return _scale;
}

void Entity::move(glm::vec3 movement) {
    position += movement;
}

void Entity::move(float dx, float dy, float dz) {
    position.x += dx;
    position.y += dy;
    position.z += dz;
}

void Entity::rotate(float dx, float dy, float dz) {
    rotation.x += dx;
    rotation.y += dy;
    rotation.z += dz;
}

void Entity::scale(float dx, float dy, float dz) {
    _scale.x += dx;
    _scale.y += dy;
    _scale.z += dz;
}

