#include "entity_renderer.h"
#include "static_shader.h"
#include "Raw_Model.h"
#include "Model_Texture.h"
#include "Textured_Model.h"
#include "entity.h"

EntityRenderer::EntityRenderer (StaticShader& shader, glm::mat4 projection_matrix) 
    : shader(shader) 
{
    shader.start();
    shader.load_projection_matrix(projection_matrix);
    shader.stop();
}

void EntityRenderer::prepareTextured_Model(Textured_Model& model) {
    Raw_Model& raw_model = model.getRaw_Model();
    glBindVertexArray(raw_model.getVaoId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    Model_Texture& texture = model.getTexture();
    shader.load_shine_variables(texture.getShineDamper(), texture.getReflectivity());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model.getTexture().getId());
}

void EntityRenderer::unbindTextured_Model() {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void EntityRenderer::prepareInstance(Entity& entity) {
    glm::mat4 transformation_matrix = Maths::createTransformationMatrix(
            entity.getPosition(), entity.getRotation(), entity.getScale());
    shader.load_transformation_matrix(transformation_matrix);
}

void EntityRenderer::render(std::map<Textured_Model*, std::vector<Entity*>>& entities) {
    for (auto& entry: entities) {
        Textured_Model* model = entry.first;
        std::vector<Entity*> batch = entry.second;
        prepareTextured_Model(*model);
        for (auto& entity: batch) {
            prepareInstance(*entity);
            glDrawElements(GL_TRIANGLES, model->getRaw_Model().getVertexCount(), GL_UNSIGNED_INT, 0);
        }
        unbindTextured_Model();
    }
}

