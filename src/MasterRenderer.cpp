#include "MasterRenderer.h"

MasterRenderer::MasterRenderer(Display& display) : m_shader(), m_renderer(display, m_shader) { }

void MasterRenderer::render(Light& light, Camera& camera) {
    m_renderer.clear();
    m_shader.start();
    m_shader.loadLight(light);
    m_shader.loadViewMatrix(camera);
    m_renderer.render(m_entities);
    m_shader.stop();
    m_entities.clear();
}

void MasterRenderer::processEntity(Entity& entity) {
    TexturedModel& model = entity.getModel();

    if (m_entities.count(&model)) {
        m_entities[&model].push_back(&entity);
    } else {
        std::vector<Entity*> new_batch;
        new_batch.push_back(&entity);
        m_entities[&model] = new_batch;
    } 
}


