#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class RawModel;

RawModel load_to_vao(std::vector<GLfloat> positions, 
                     std::vector<GLfloat> tex_coords, 
                     std::vector<GLfloat> normals, 
                     std::vector<GLuint>  indices);

GLuint load_texture(const char* filename);

void delete_gl_buffers();

