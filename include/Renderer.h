#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <map>


#include "RawModel.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "StaticShader.h"
#include "Maths.h"
#include "Display.h"

class Renderer {

private:
    glm::mat4 m_projectionMatrix;
    StaticShader& m_shader;

    constexpr static GLfloat FOV = 80;
    constexpr static GLfloat NEAR_PLANE = 0.1f;
    constexpr static GLfloat FAR_PLANE = 1000;

    void createProjectionMatrix(int width, int height);
    void prepareTexturedModel(TexturedModel& model);
    void unbindTexturedModel();
    void prepareInstance(Entity& entity);

public:
    Renderer(Display& display, StaticShader& shader);
    void render(std::map<TexturedModel*, std::vector<Entity*>>& entities);
    void clear();
};
