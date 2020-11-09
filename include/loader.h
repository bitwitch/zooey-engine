#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Raw_Model;

struct Loader {

	std::vector<GLuint> vaos;
	std::vector<GLuint> vbos;
	std::vector<GLuint> textures;

    GLuint create_vao();
    void store_data_in_attributes_list(GLuint attribute_number, GLuint coord_size, 
            std::vector<float> data);
    void bind_indices_buffer(std::vector<GLuint> indices);
    void unbind_vao();

    Raw_Model load_to_vao(std::vector<GLfloat> positions, std::vector<GLfloat> tex_coords, 
            std::vector<GLfloat> normals, std::vector<GLuint> indices);
    GLuint load_texture(const char* filename);
    void clean_up();

};
