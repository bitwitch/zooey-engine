#pragma once

#include <vector> 
#include "glm_subset.h"
#include "Terrain.h"
#include "TerrainShader.h"
#include "TexturedModel.h"
#include "Entity.h"

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
