#pragma once

#include<stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ShaderProgram {

private:
    GLuint m_programId;
    GLuint m_vertexShaderId;
    GLuint m_fragmentShaderId;

protected:
    void bindAttribute(GLuint attribute, char* variable_name);
    virtual void bindAttributes();

public:
    ShaderProgram(char* vert_path, char* frag_path);
    void start();
    void stop();
    void cleanUp();

private:
    GLuint loadShader(char* filename, GLenum shader_type);

};
