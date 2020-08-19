#include "RawModel.h"

RawModel::RawModel(GLuint vao_id, GLuint vertex_count) {
    this->vao_id = vao_id;
    this->vertex_count = vertex_count;
}

GLuint RawModel::getVaoId() {
    return vao_id;
}

GLuint RawModel::getVertexCount() {
    return vertex_count;
}
