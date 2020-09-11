#pragma once

#include <vector> 
#include "glm_subset.h"

class Terrain;
class TerrainShader;

class TerrainRenderer {

private:
    TerrainShader& shader;

    void prepareTerrain(Terrain& terrain);
    void unbindTexturedModel();
    void loadModelMatrix(Terrain& terrain);

public:
    TerrainRenderer(TerrainShader& shader, glm::mat4 projection_matrix);
    void render(std::vector<Terrain*> terrains);

};
