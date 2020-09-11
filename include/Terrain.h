#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "RawModel.h"

class ModelTexture;
class Loader;


class Terrain {
    
private:
    constexpr static GLfloat SIZE = 800;
    constexpr static GLuint VERTEX_COUNT = 128;
    GLfloat x;
    GLfloat z;
    RawModel model;
    ModelTexture& texture;
    RawModel generateTerrain(Loader& loader);

public:
    Terrain(int grid_x, int grid_y, Loader& loader, ModelTexture& texture);
    GLfloat getX();
    GLfloat getZ();
    RawModel& getModel();
    ModelTexture& getTexture();
    
};
