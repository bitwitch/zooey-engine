#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 color) : position(position), color(color) {}

glm::vec3 Light::getPosition() {
    return position;
}

glm::vec3 Light::getColor() {
    return color;
}

void Light::setPosition(glm::vec3 position) {
    this->position = position;
}

void Light::setColor(glm::vec3 color) {
    this->color = color;
}

