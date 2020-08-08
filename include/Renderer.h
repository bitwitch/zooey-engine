#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "RawModel.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "StaticShader.h"
#include "Maths.h"

class Renderer {
public:
    void prepare();
    void render(Entity& entity, StaticShader& shader);
};
