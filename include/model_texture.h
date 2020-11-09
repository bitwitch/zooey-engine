#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Model_Texture {

    GLuint id;
    GLfloat shine_damper = 1;
    GLfloat reflectivity = 0;

    Model_Texture(GLuint texture_id) { id = texture_id; }

};
