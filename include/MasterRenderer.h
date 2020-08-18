#pragma once

#include <map>
#include <vector>
#include "TexturedModel.h"
#include "Renderer.h"
#include "StaticShader.h"
#include "Light.h"
#include "Camera.h"
#include "Display.h"

class MasterRenderer {

private:
    StaticShader m_shader;
    Renderer m_renderer;
    std::map<TexturedModel*, std::vector<Entity*>> m_entities;

public:
    MasterRenderer(Display& display);
    void render(Light& light, Camera& camera);
    void processEntity(Entity& entity);

};
