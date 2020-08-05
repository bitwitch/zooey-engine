#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "RawModel.h"
#include "ModelTexture.h"
#include "TexturedModel.h"

class Renderer {
    
public:
    void prepare();
    void render(TexturedModel* textured_model);

};
