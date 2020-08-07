#pragma once

#include<stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm_subset.h"

class ShaderProgram {

private:
    GLuint m_programId;
    GLuint m_vertexShaderId;
    GLuint m_fragmentShaderId;

protected:
    virtual void bindAttributes() = 0;
    virtual void getAllUniformLocations() = 0;

    void bindAttribute(GLuint attribute, char* variable_name);
    GLuint getUniformLocation(char* uniformName);

    // loads uniforms into shaders
    void loadFloat(GLuint location, GLfloat value);
    void loadVector(GLuint location, glm::vec3 vector);
    void loadBool(GLuint location, bool value);
    void loadMatrix(GLuint location, glm::mat4 matrix);

public:
    ShaderProgram(char* vert_path, char* frag_path);
    ~ShaderProgram();
    void start();
    void stop();

private:
    GLuint loadShader(char* filename, GLenum shader_type);

};
