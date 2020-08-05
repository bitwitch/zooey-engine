#include "Renderer.h"

void Renderer::prepare() {
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(TexturedModel* textured_model) {
    RawModel* model = textured_model->m_rawModel;
    glBindVertexArray(model->m_vaoId);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textured_model->m_modelTexture->getId());
    glDrawElements(GL_TRIANGLES, (GLsizei)model->m_vertexCount, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}
