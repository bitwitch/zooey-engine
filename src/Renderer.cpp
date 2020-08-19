#include "Renderer.h"

Renderer::Renderer (Display& display, StaticShader& shader) : shader(shader) {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    createProjectionMatrix(display.getWidth(), display.getHeight());
    shader.start();
    shader.loadProjectionMatrix(projection_matrix);
    shader.stop();
}

void Renderer::clear() {
    glEnable(GL_DEPTH_TEST);
    //glClearColor(0, 0, 0, 1);
    glClearColor(59/255.0f, 0/255.0f, 0/255.0f, 1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void Renderer::prepareTexturedModel(TexturedModel& model) {
    RawModel& raw_model = model.getRawModel();
    glBindVertexArray(raw_model.getVaoId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    ModelTexture& texture = model.getTexture();
    shader.loadShineVariables(texture.getShineDamper(), texture.getReflectivity());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model.getTexture().getId());
}

void Renderer::unbindTexturedModel() {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void Renderer::prepareInstance(Entity& entity) {
    glm::mat4 transformation_matrix = Maths::createTransformationMatrix(
            entity.getPosition(), entity.getRotation(), entity.getScale());
    shader.loadTransformationMatrix(transformation_matrix);
}

void Renderer::render(std::map<TexturedModel*, std::vector<Entity*>>& entities) {
    for (auto& entry: entities) {
        TexturedModel* model = entry.first;
        std::vector<Entity*> batch = entry.second;
        prepareTexturedModel(*model);
        for (auto& entity: batch) {
            prepareInstance(*entity);
            glDrawElements(GL_TRIANGLES, model->getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
        }
        unbindTexturedModel();
    }
}

void Renderer::createProjectionMatrix(int width, int height) {
    float aspect = (float)width / (float)height;
    float y_scale = (float)((1.0f / tan(glm::radians(0.5f * FOV))) * aspect);
    float x_scale = y_scale / aspect;
    float frustulength = FAR_PLANE - NEAR_PLANE;

    projection_matrix[0] = glm::vec4(x_scale, 0, 0, 0);
    projection_matrix[1] = glm::vec4(0, y_scale, 0, 0);
    projection_matrix[2] = glm::vec4(0, 0, -(FAR_PLANE + NEAR_PLANE)/frustulength, -1);
    projection_matrix[3] = glm::vec4(0, 0, -(2 * NEAR_PLANE * FAR_PLANE)/frustulength, 0);
}
