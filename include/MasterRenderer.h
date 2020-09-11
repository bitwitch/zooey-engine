#pragma once

#include <map>
#include <vector>

class TexturedModel;
class Entity;
class Terrain;
class Display;
class Camera;
class Light;


#include "StaticShader.h"
#include "EntityRenderer.h"
#include "TerrainShader.h"
#include "TerrainRenderer.h"


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
