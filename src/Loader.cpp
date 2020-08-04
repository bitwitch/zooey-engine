#include "Loader.h"

GLuint Loader::createVAO() {
    GLuint vao_id;
    glGenVertexArrays(1, &vao_id);
    vaos.push_back(vao_id);
    glBindVertexArray(vao_id);
    return vao_id;
}

void Loader::storeDataInAttributeList(int attribute_number, std::vector<float> data) { 
    GLuint vbo_id;
    size_t byte_length = sizeof(float) * data.size();
    glGenBuffers(1, &vbo_id);
    vbos.push_back(vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, byte_length, data.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribPointer(attribute_number, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO() {
    glBindVertexArray(0);
}

RawModel Loader::loadToVAO(std::vector<float> positions) {
    GLuint vao_id = createVAO();
    storeDataInAttributeList(0, positions);
    unbindVAO();
    return RawModel(vao_id, positions.size()/3);
}

void Loader::cleanUp() {
    // NOTE(shaw): the docs for opengl says that the second arguments here is
    // an "array containing the n names of the objects to be deleted", i am
    // just using the ids here, is this correct?
    glDeleteVertexArrays(vaos.size(), vaos.data());
    glDeleteBuffers(vbos.size(), vbos.data());
}
