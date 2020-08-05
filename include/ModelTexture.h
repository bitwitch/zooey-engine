#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ModelTexture {

private:
    GLuint m_textureId;

public:
    ModelTexture(GLuint id);
    GLuint getId();

};
