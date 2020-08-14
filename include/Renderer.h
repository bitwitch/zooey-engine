#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

#include "RawModel.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "StaticShader.h"
#include "Maths.h"
#include "Display.h"

class Renderer {

private:
    constexpr static GLfloat FOV = 80;
    constexpr static GLfloat NEAR_PLANE = 0.1f;
    constexpr static GLfloat FAR_PLANE = 1000;
    glm::mat4 m_projectionMatrix;
    void createProjectionMatrix(int width, int height);

public:
    Renderer(Display& display, StaticShader& shader);
    void clear();
    void render(Entity& entity, StaticShader& shader);
};
