#include "ModelTexture.h"

ModelTexture::ModelTexture(GLuint id) {
    texture_id = id;
}

GLuint ModelTexture::getId() {
    return texture_id;
}

GLfloat ModelTexture::getShineDamper() {
    return shine_damper;
}

GLfloat ModelTexture::getReflectivity() {
    return reflectivity;
}

void ModelTexture::setReflectivity(GLfloat reflectivity) {
    this->reflectivity = reflectivity;
}

void ModelTexture::setShineDamper(GLfloat damper) {
    shine_damper = damper;
}


