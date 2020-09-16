#include "Loader.h"

#include <stdlib.h>
#include <algorithm>
#include "RawModel.h"
#include "stb_image.h"

// scope file
//

struct GL_Vertex_Data {
	std::vector<GLuint> vaos;
	std::vector<GLuint> vbos;
	std::vector<GLuint> textures;
};

static GL_Vertex_Data vertex_data;

GLuint create_vao() {
    GLuint vao_id;
    glGenVertexArrays(1, &vao_id);
    vertex_data.vaos.push_back(vao_id);
    glBindVertexArray(vao_id);
    return vao_id;
}

void store_data_in_attribute_list(GLuint attribute_number, 
                                  GLuint coord_size, 
                                  std::vector<float> data) 
{ 
    GLuint vbo_id;
    size_t byte_length = sizeof(float) * data.size();
    glGenBuffers(1, &vbo_id);
    vertex_data.vbos.push_back(vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, byte_length, data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(attribute_number, coord_size, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void unbind_vao() {
    glBindVertexArray(0);
}

void bind_indices_buffer(std::vector<GLuint> indices) {
    GLuint vbo_id;
    size_t byte_length = sizeof(GLuint) * indices.size();
    glGenBuffers(1, &vbo_id);
    vertex_data.vbos.push_back(vbo_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, byte_length, indices.data(), GL_STATIC_DRAW);
}

// scope export
// 
RawModel load_to_vao(std::vector<GLfloat> positions, 
                     std::vector<GLfloat> tex_coords, 
                     std::vector<GLfloat> normals, 
                     std::vector<GLuint> indices) 
{
    GLuint vao_id = create_vao();
    bind_indices_buffer(indices);
    store_data_in_attribute_list(0, 3, positions);
    store_data_in_attribute_list(1, 2, tex_coords);
    store_data_in_attribute_list(2, 3, normals);
    unbind_vao();
    return RawModel(vao_id, indices.size());
}

GLuint load_texture(const char* filename) 
{
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load image
    int width, height, nuchannels;
    char full_filename[100];
    sprintf(full_filename, "data/textures/%s", filename);

    unsigned char* data = stbi_load(full_filename, &width, &height, &nuchannels, 0);

    if (!data) {
        printf("Failed to load texture\n");
        data = stbi_load("data/textures/source_fail.png", &width, &height, &nuchannels, 0);
    }

    GLenum pixel_format = GL_RGB;
    if (nuchannels == 4) {
        pixel_format = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, pixel_format, width, height, 0, pixel_format, GL_UNSIGNED_BYTE, 
            data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    vertex_data.textures.push_back(texture_id);
    return texture_id;
}

void delete_gl_buffers() {
    // NOTE(shaw): the docs for opengl says that the second arguments here is
    // an "array containing the n names of the objects to be deleted", i am
    // just using the ids here, is this correct?
    glDeleteVertexArrays(vertex_data.vaos.size(), vertex_data.vaos.data());
    glDeleteBuffers(vertex_data.vbos.size(), vertex_data.vbos.data());
    glDeleteTextures(vertex_data.textures.size(), vertex_data.textures.data());
}

