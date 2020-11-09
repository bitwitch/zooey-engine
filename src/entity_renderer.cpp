#include "entity_renderer.h"
#include "static_shader.h"
#include "raw_model.h"
#include "model_texture.h"
#include "textured_model.h"
#include "entity.h"

Entity_Renderer::Entity_Renderer (Static_Shader* shader, glm::mat4 projection_matrix) 
    : shader(shader) 
{
    shader->start();
    shader->load_projection_matrix(projection_matrix);
    shader->stop();
}

void Entity_Renderer::prepare_textured_model(Textured_Model* model) {
    Raw_Model* raw_model = model->raw_model;

    glBindVertexArray(raw_model->vao_id);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    Model_Texture* texture = model->texture;
    shader->load_shine_variables(texture->shine_damper, texture->reflectivity);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model->texture->id);
}

void Entity_Renderer::unbind_textured_model() {
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void Entity_Renderer::prepare_instance(Entity* entity) {
    glm::mat4 transformation_matrix = Maths::create_transformation_matrix(
            entity->position, entity->rotation, entity->my_scale);
    shader->load_transformation_matrix(transformation_matrix);
}

// TODO(shaw): research a little, passing vectors as parameters
void Entity_Renderer::render(std::map<Textured_Model*, std::vector<Entity*>>& entities) {
    for (auto& entry: entities) {
        Textured_Model* model = entry.first;
        std::vector<Entity*> batch = entry.second;
        prepare_textured_model(model);
        for (auto& entity: batch) {
            prepare_instance(entity);
            glDrawElements(GL_TRIANGLES, model->raw_model->vertex_count, GL_UNSIGNED_INT, 0);
        }
        unbind_textured_model();
    }
}

