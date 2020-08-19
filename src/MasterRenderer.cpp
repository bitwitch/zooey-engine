#include "MasterRenderer.h"

MasterRenderer::MasterRenderer(Display& display) 
    : projection_matrix(createProjectionMatrix(display.getWidth(), display.getHeight()))
    , renderer(shader, projection_matrix) 
{ 
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void MasterRenderer::render(Light& light, Camera& camera) {
    clear();
    shader.start();
    shader.loadLight(light);
    shader.loadViewMatrix(camera);
    renderer.render(entities);
    shader.stop();
    entities.clear();
}

void MasterRenderer::processEntity(Entity& entity) {
    TexturedModel& model = entity.getModel();

    if (entities.count(&model)) {
        entities[&model].push_back(&entity);
    } else {
        std::vector<Entity*> new_batch;
        new_batch.push_back(&entity);
        entities[&model] = new_batch;
    } 
}

glm::mat4 MasterRenderer::createProjectionMatrix(int width, int height) {
    glm::mat4 projection_matrix = glm::mat4(1.0);
    float aspect = (float)width / (float)height;
    float y_scale = (float)((1.0f / tan(glm::radians(0.5f * FOV))) * aspect);
    float x_scale = y_scale / aspect;
    float frustulength = FAR_PLANE - NEAR_PLANE;

    projection_matrix[0] = glm::vec4(x_scale, 0, 0, 0);
    projection_matrix[1] = glm::vec4(0, y_scale, 0, 0);
    projection_matrix[2] = glm::vec4(0, 0, -(FAR_PLANE + NEAR_PLANE)/frustulength, -1);
    projection_matrix[3] = glm::vec4(0, 0, -(2 * NEAR_PLANE * FAR_PLANE)/frustulength, 0);
    return projection_matrix;
}

void MasterRenderer::clear() {
    glEnable(GL_DEPTH_TEST);
    //glClearColor(0, 0, 0, 1);
    glClearColor(59/255.0f, 0/255.0f, 0/255.0f, 1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}


