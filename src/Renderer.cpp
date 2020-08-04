#include "Renderer.h"

void Renderer::prepare() {
    glClearColor(1, 0, 0, 1);
}

void Renderer::render(RawModel model) {
    glBindVertexArray(model.vao_id);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, model.vertex_count);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}
