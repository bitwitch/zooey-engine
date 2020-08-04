#pragma once 

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class RawModel {

public:
    GLuint m_vaoID;
    int m_vertexCount;

public:
    RawModel(GLuint vao_id, int vertex_count);

};
