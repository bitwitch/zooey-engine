#include "Loader.h"

RawModel Loader::loadToVAO(std::vector<float> positions, std::vector<int> indices) {
    GLuint vao_id = createVAO();
    bindIndicesBuffer(indices);
    storeDataInAttributeList(0, positions);
    unbindVAO();
    return RawModel(vao_id, indices.size());
}

GLuint Loader::loadTexture(const char* filename) {
    // load image
    int width, height, num_channels;
    unsigned char* data = stbi_load(filename, &width, &height, &num_channels, 0);
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    textures.push_back(texture_id);
    return texture_id;
}

GLuint Loader::createVAO() {
    GLuint vao_id;
    glGenVertexArrays(1, &vao_id);
    vaos.push_back(vao_id);
    glBindVertexArray(vao_id);
    return vao_id;
}

void Loader::storeDataInAttributeList(GLuint attribute_number, std::vector<float> data) { 
    GLuint vbo_id;
    size_t byte_length = sizeof(float) * data.size();
    glGenBuffers(1, &vbo_id);
    vbos.push_back(vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, byte_length, data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(attribute_number, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO() {
    glBindVertexArray(0);
}

void Loader::bindIndicesBuffer(std::vector<int> indices) {
    GLuint vbo_id;
    size_t byte_length = sizeof(int) * indices.size();
    glGenBuffers(1, &vbo_id);
    vbos.push_back(vbo_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, byte_length, indices.data(), GL_STATIC_DRAW);
}

void Loader::cleanUp() {
    // NOTE(shaw): the docs for opengl says that the second arguments here is
    // an "array containing the n names of the objects to be deleted", i am
    // just using the ids here, is this correct?
    glDeleteVertexArrays(vaos.size(), vaos.data());
    glDeleteBuffers(vbos.size(), vbos.data());
    glDeleteTextures(textures.size(), textures.data());
}

