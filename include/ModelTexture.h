#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ModelTexture {

private:
    GLuint texture_id;
    GLfloat shine_damper;
    GLfloat reflectivity;

public:
    ModelTexture(GLuint id);
    GLuint getId();
    GLfloat getShineDamper();
    GLfloat getReflectivity();
    void setShineDamper(GLfloat damper);
    void setReflectivity(GLfloat reflectivity);

};
