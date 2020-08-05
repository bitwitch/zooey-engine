#include "Renderer.h"

void Renderer::prepare() {
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(TexturedModel* textured_model) {
    RawModel* model = textured_model->m_rawModel;
    glBindVertexArray(model->m_vaoId);
    glEnableVertexAttribArray(0);
    glDrawElements(GL_TRIANGLES, (GLsizei)model->m_vertexCount, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}
