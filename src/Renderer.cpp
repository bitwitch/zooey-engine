#include "Renderer.h"


Renderer::Renderer (Display& display, StaticShader& shader) {
    createProjectionMatrix(display.getWidth(), display.getHeight());
    shader.start();
    shader.loadProjectionMatrix(m_projectionMatrix);
    shader.stop();
}

void Renderer::clear() {
    glEnable(GL_DEPTH_TEST);
    //glClearColor(0, 0, 0, 1);
    glClearColor(59/255.0f, 0/255.0f, 0/255.0f, 1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(Entity& entity, StaticShader& shader) {
    TexturedModel& textured_model = entity.getModel();
    RawModel& raw_model = textured_model.getRawModel();
    glBindVertexArray(raw_model.getVaoId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glm::mat4 transformation_matrix = Maths::createTransformationMatrix(
            entity.getPosition(), entity.getRotation(), entity.getScale());

    shader.loadTransformationMatrix(transformation_matrix);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textured_model.getTexture().getId());
    glDrawElements(GL_TRIANGLES, raw_model.getVertexCount(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void Renderer::createProjectionMatrix(int width, int height) {
    float aspect = (float)width / (float)height;
    float y_scale = (float)((1.0f / tan(glm::radians(0.5f * FOV))) * aspect);
    float x_scale = y_scale / aspect;
    float frustum_length = FAR_PLANE - NEAR_PLANE;

    m_projectionMatrix[0] = glm::vec4(x_scale, 0, 0, 0);
    m_projectionMatrix[1] = glm::vec4(0, y_scale, 0, 0);
    m_projectionMatrix[2] = glm::vec4(0, 0, -(FAR_PLANE + NEAR_PLANE)/frustum_length, -1);
    m_projectionMatrix[3] = glm::vec4(0, 0, -(2 * NEAR_PLANE * FAR_PLANE)/frustum_length, 0);
}
