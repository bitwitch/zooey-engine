#include "Entity.h"

Entity::Entity(TexturedModel& model, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :
    m_model(model), m_position(position), m_rotation(rotation), m_scale(scale) { }

TexturedModel& Entity::getModel() {
    return m_model;
}

glm::vec3 Entity::getPosition() {
    return m_position;
}

glm::vec3 Entity::getRotation() {
    return m_rotation;
}

glm::vec3 Entity::getScale() {
    return m_scale;
}

void Entity::move(float dx, float dy, float dz) {
    m_position.x += dx;
    m_position.y += dy;
    m_position.z += dz;
}

void Entity::rotate(float dx, float dy, float dz) {
    m_rotation.x += dx;
    m_rotation.y += dy;
    m_rotation.z += dz;
}

void Entity::scale(float dx, float dy, float dz) {
    m_scale.x += dx;
    m_scale.y += dy;
    m_scale.z += dz;
}

