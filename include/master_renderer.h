#pragma once

#include <map>
#include <vector>

struct Textured_Model;
struct Entity;
struct Terrain;
struct Display;
struct Camera;
struct Light;


#include "static_shader.h"
#include "entity_renderer.h"
#include "terrain_shader.h"
#include "terrain_renderer.h"


struct Master_Renderer {

    constexpr static GLfloat FOV = 80;
    constexpr static GLfloat NEAR_PLANE = 0.1f;
    constexpr static GLfloat FAR_PLANE = 1000;

    constexpr static GLfloat SKY_R = 11/255.0f;
    constexpr static GLfloat SKY_G = 39/255.0f;
    constexpr static GLfloat SKY_B = 34/255.0f;

    glm::mat4 projection_matrix;

    Static_Shader entity_shader;
    Entity_Renderer entity_renderer;

    Terrain_Shader terrain_shader;
    Terrain_Renderer terrain_renderer;

    std::map<Textured_Model*, std::vector<Entity*>> entities;

    std::vector<Terrain*> terrains;

    glm::mat4 create_projection_matrix(int width, int height);

    Master_Renderer(Display* display);
    void render(Light* light, Camera* camera);
    void process_entity(Entity* entity);
    void process_terrain(Terrain* terrain);
    void clear();
};
