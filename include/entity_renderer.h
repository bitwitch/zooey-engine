#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <map>

#include "glm_subset.h"

struct Static_Shader;
struct Textured_Model;
struct Entity;

struct Entity_Renderer {

    Static_Shader* shader;

    Entity_Renderer(Static_Shader* shader, glm::mat4 projection_matrix);
    void prepare_textured_model(Textured_Model* model);
    void unbind_textured_model();
    void prepare_instance(Entity* entity);
    void render(std::map<Textured_Model*, std::vector<Entity*>>& entities);
};
