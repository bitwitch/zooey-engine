#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ModelTexture {

private:
    GLuint m_textureId;
    GLfloat m_shineDamper;
    GLfloat m_reflectivity;

public:
    ModelTexture(GLuint id);
    GLuint getId();
    GLfloat getShineDamper();
    GLfloat getReflectivity();
    void setShineDamper(GLfloat damper);
    void setReflectivity(GLfloat reflectivity);

};
