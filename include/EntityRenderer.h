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

class EntityRenderer {

private:
    StaticShader& shader;

    void prepareTexturedModel(TexturedModel& model);
    void unbindTexturedModel();
    void prepareInstance(Entity& entity);

public:
    EntityRenderer(StaticShader& shader, glm::mat4 projection_matrix);
    void render(std::map<TexturedModel*, std::vector<Entity*>>& entities);
};
