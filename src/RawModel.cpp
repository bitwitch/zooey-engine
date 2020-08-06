#include "RawModel.h"

RawModel::RawModel(GLuint vao_id, GLuint vertex_count) {
    m_vaoId = vao_id;
    m_vertexCount = vertex_count;
}

GLuint RawModel::getVaoId() {
    return m_vaoId;
}

GLuint RawModel::getVertexCount() {
    return m_vertexCount;
}
