#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "raw_model.h"

struct Model_Texture;
struct Loader;


struct Terrain {
    
    constexpr static GLfloat SIZE = 800;
    constexpr static GLuint VERTEX_COUNT = 128;
    GLfloat x;
    GLfloat z;
    Raw_Model model;
    Model_Texture* texture;
    Raw_Model generate_terrain(Loader* loader);

    Terrain(int grid_x, int grid_y, Loader* loader, Model_Texture* texture);
};
