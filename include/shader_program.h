#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm_subset.h"

struct Shader_Program {

    GLuint program_id;
    GLuint vertex_shader_id;
    GLuint fragment_shader_id;

    virtual void bind_attributes() = 0;
    virtual void get_all_uniform_locations() = 0;

    void bind_attribute(GLuint attribute, const char* name);
    GLuint get_uniform_location(const char* uniform_name);

    // loads uniforms into shaders
    void load_float(GLuint location, GLfloat value);
    void load_vector(GLuint location, glm::vec3 vector);
    void load_bool(GLuint location, bool value);
    void load_matrix(GLuint location, const glm::mat4 &matrix);

    Shader_Program(const char* vert_path, const char* frag_path);
    ~Shader_Program();
    void start();
    void stop();

    GLuint load_shader(const char* filename, GLenum shader_type);

};
