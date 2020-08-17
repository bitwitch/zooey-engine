#include "ModelTexture.h"

ModelTexture::ModelTexture(GLuint id) {
    m_textureId = id;
}

GLuint ModelTexture::getId() {
    return m_textureId;
}

GLfloat ModelTexture::getShineDamper() {
    return m_shineDamper;
}

GLfloat ModelTexture::getReflectivity() {
    return m_reflectivity;
}

void ModelTexture::setReflectivity(GLfloat reflectivity) {
    m_reflectivity = reflectivity;
}

void ModelTexture::setShineDamper(GLfloat damper) {
    m_shineDamper = damper;
}


