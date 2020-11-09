#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Raw_Model {

    GLuint vao_id;
    GLuint vertex_count;

    Raw_Model(GLuint vao_id, GLuint vertex_count) { 
        this->vao_id = vao_id;
        this->vertex_count = vertex_count;
    }
};
