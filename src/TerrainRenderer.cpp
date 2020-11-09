#include "terrain_renderer.h"
#include "terrain_shader.h"
#include "terrain.h"
#include "model_texture.h"

Terrain_Renderer::Terrain_Renderer(Terrain_Shader& shader, glm::mat4 projection_matrix)
    : shader(shader) 
{
    shader.start();
    shader.load_projection_matrix(projection_matrix);
    shader.stop();
}

void Terrain_Renderer::render(std::vector<Terrain*> terrains) {
    for (const auto& terrain: terrains) {
        prepare_terrain(*terrain);
        load_model_matrix(*terrain);
        glDrawElements(GL_TRIANGLES, terrain->getModel().getVertexCount(), GL_UNSIGNED_INT, 0);
        unbind_textured_model();
    }
}


void Terrain_Renderer::prepare_terrain(Terrain& terrain) {
    Raw_Model& raw_model = terrain.getModel();
    glBindVertexArray(raw_model.getVaoId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    Model_Texture& texture = terrain.getTexture();
    shader.load_shine_variables(texture.getShineDamper(), texture.getReflectivity());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.getId());
}

void Terrain_Renderer::unbind_textured_model() {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void Terrain_Renderer::load_model_matrix(Terrain& terrain) {
    glm::mat4 transformation_matrix = Maths::createTransformationMatrix(
            glm::vec3(terrain.getX(), 0, terrain.getZ()), // position
            glm::vec3(0.0f),                              // rotation
            glm::vec3(1.0f));                             // scale
    shader.load_transformation_matrix(transformation_matrix);
}


