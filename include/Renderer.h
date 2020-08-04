#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer {
    
public:
    void prepare();
    void render(RawModel model);

};
