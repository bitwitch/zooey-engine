#pragma once

#include <vector> 
#include "glm_subset.h"

struct Terrain;
struct Terrain_Shader;

struct Terrain_Renderer {

    Terrain_Shader *shader;

    void prepare_terrain(Terrain *terrain);
    void unbind_textured_model();
    void load_model_matrix(Terrain *terrain);

    Terrain_Renderer(Terrain_Shader *shader, glm::mat4 projection_matrix);
    void render(std::vector<Terrain*> &terrains);

};

