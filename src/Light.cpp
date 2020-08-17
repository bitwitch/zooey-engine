#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 color) : m_position(position), m_color(color) {}

glm::vec3 Light::getPosition() {
    return m_position;
}

glm::vec3 Light::getColor() {
    return m_color;
}

void Light::setPosition(glm::vec3 position) {
    m_position = position;
}

void Light::setColor(glm::vec3 color) {
    m_color = color;
}

