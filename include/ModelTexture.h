#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ModelTexture {

private:
    GLuint texture_id;
    GLfloat shine_damper = 1;
    GLfloat reflectivity = 0;

public:
    ModelTexture(GLuint id);
    GLuint getId();
    GLfloat getShineDamper();
    GLfloat getReflectivity();
    void setShineDamper(GLfloat damper);
    void setReflectivity(GLfloat reflectivity);

};
