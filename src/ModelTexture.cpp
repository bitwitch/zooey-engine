#include "ModelTexture.h"

ModelTexture::ModelTexture(GLuint id) {
    m_textureId = id;
}

GLuint ModelTexture::getId() {
    return m_textureId;
}
