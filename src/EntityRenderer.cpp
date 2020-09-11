#include "EntityRenderer.h"
#include "StaticShader.h"
#include "RawModel.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "Entity.h"

EntityRenderer::EntityRenderer (StaticShader& shader, glm::mat4 projection_matrix) 
    : shader(shader) 
{
    shader.start();
    shader.loadProjectionMatrix(projection_matrix);
    shader.stop();
}

void EntityRenderer::prepareTexturedModel(TexturedModel& model) {
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

void EntityRenderer::unbindTexturedModel() {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void EntityRenderer::prepareInstance(Entity& entity) {
    glm::mat4 transformation_matrix = Maths::createTransformationMatrix(
            entity.getPosition(), entity.getRotation(), entity.getScale());
    shader.loadTransformationMatrix(transformation_matrix);
}

void EntityRenderer::render(std::map<TexturedModel*, std::vector<Entity*>>& entities) {
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

