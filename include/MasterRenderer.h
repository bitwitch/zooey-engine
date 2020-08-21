#pragma once

#include <map>
#include <vector>
#include "TexturedModel.h"
#include "EntityRenderer.h"
#include "StaticShader.h"
#include "Terrain.h"
#include "TerrainRenderer.h"
#include "TerrainShader.h"
#include "Light.h"
#include "Camera.h"
#include "Display.h"

class MasterRenderer {

private:
    constexpr static GLfloat FOV = 80;
    constexpr static GLfloat NEAR_PLANE = 0.1f;
    constexpr static GLfloat FAR_PLANE = 1000;

    glm::mat4 projection_matrix;

    StaticShader shader;
    EntityRenderer renderer;

    TerrainShader terrain_shader;
    TerrainRenderer terrain_renderer;

    std::map<TexturedModel*, std::vector<Entity*>> entities;

    std::vector<Terrain*> terrains;

    glm::mat4 createProjectionMatrix(int width, int height);

public:
    MasterRenderer(Display& display);
    void render(Light& light, Camera& camera);
    void processEntity(Entity& entity);
    void processTerrain(Terrain& terrain);
    void clear();
};
