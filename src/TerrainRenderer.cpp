#include "TerrainRenderer.h"


TerrainRenderer::TerrainRenderer(TerrainShader& shader, glm::mat4 projection_matrix)
    : shader(shader) 
{
    shader.start();
    shader.loadProjectionMatrix(projection_matrix);
    shader.stop();
}

void TerrainRenderer::render(std::vector<Terrain*> terrains) {
    for (const auto& terrain: terrains) {
        prepareTerrain(*terrain);
        loadModelMatrix(*terrain);
        glDrawElements(GL_TRIANGLES, terrain->getModel().getVertexCount(), GL_UNSIGNED_INT, 0);
        unbindTexturedModel();
    }
}


void TerrainRenderer::prepareTerrain(Terrain& terrain) {
    RawModel& raw_model = terrain.getModel();
    glBindVertexArray(raw_model.getVaoId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    ModelTexture& texture = terrain.getTexture();
    shader.loadShineVariables(texture.getShineDamper(), texture.getReflectivity());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.getId());
}

void TerrainRenderer::unbindTexturedModel() {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void TerrainRenderer::loadModelMatrix(Terrain& terrain) {
    glm::mat4 transformation_matrix = Maths::createTransformationMatrix(
            glm::vec3(terrain.getX(), 0, terrain.getZ()), // position
            glm::vec3(0.0f),                              // rotation
            glm::vec3(1.0f));                             // scale
    shader.loadTransformationMatrix(transformation_matrix);
}


