#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class RawModel {

private:
    GLuint vao_id;
    GLuint vertex_count;

public:
    RawModel(GLuint vao_id, GLuint vertex_count);
    GLuint getVaoId();
    GLuint getVertexCount();

};
