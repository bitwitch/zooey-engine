#include "Loader.h"

int Loader::createVAO() {
    GLuint vao_id;
    glGenVertexArrays(1, &vao_id);
    vaos.push_back(vao_id);
    glBindVertexArray(vao_id);
    return vao_id;
}

void Loader::storeDataInAttributeList(int attribute_number, float[] data) { 
    int vbo_id;
    glGenBuffers(1, &vbo_id);
    vbos.push_back(vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribPointer(attribute_number, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO() {
    glBindVertexArray(0);
}

public:

RawModel Loader::loadToVAO(float[] positions) {
    int vao_id = createVAO();
    storeDataInAttributeList(0, positions);
    unbindVAO();
    return new RawModel(vao_id, positions.length/3);
}

void Loader::cleanUp() {
    std::for_each(vaos.begin(), vaos.end(), glDeleteVertexArrays);
    std::for_each(vbos.begin(), vbos.end(), glDeleteBuffers);
}
