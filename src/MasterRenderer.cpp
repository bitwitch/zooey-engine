#include "MasterRenderer.h"

MasterRenderer::MasterRenderer(Display& display) : shader(), renderer(display, shader) { }

void MasterRenderer::render(Light& light, Camera& camera) {
    renderer.clear();
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


