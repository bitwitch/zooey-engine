#include "Loader.h"

RawModel Loader::loadToVAO(std::vector<GLfloat> positions, 
                           std::vector<GLfloat> tex_coords, 
                           std::vector<GLfloat> normals, 
                           std::vector<GLuint> indices) 
{
    GLuint vao_id = createVAO();
    bindIndicesBuffer(indices);
    storeDataInAttributeList(0, 3, positions);
    storeDataInAttributeList(1, 2, tex_coords);
    storeDataInAttributeList(2, 3, normals);
    unbindVAO();
    return RawModel(vao_id, indices.size());
}

GLuint Loader::loadTexture(const char* filename) 
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
    int width, height, num_channels;
    unsigned char* data = stbi_load(filename, &width, &height, &num_channels, 0);

    if (!data) {
        printf("Failed to load texture\n");
        data = stbi_load("data/source_fail.png", &width, &height, &num_channels, 0);
    }

    GLenum pixel_format = GL_RGB;
    if (num_channels == 4) {
        pixel_format = GL_RGBA;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, pixel_format, width, height, 0, pixel_format, GL_UNSIGNED_BYTE, 
            data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    textures.push_back(texture_id);
    return texture_id;
}

GLuint Loader::createVAO() {
    GLuint vao_id;
    glGenVertexArrays(1, &vao_id);
    vaos.push_back(vao_id);
    glBindVertexArray(vao_id);
    return vao_id;
}

void Loader::storeDataInAttributeList(GLuint attribute_number, 
                                      GLuint coord_size, 
                                      std::vector<float> data) 
{ 
    GLuint vbo_id;
    size_t byte_length = sizeof(float) * data.size();
    glGenBuffers(1, &vbo_id);
    vbos.push_back(vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, byte_length, data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(attribute_number, coord_size, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO() {
    glBindVertexArray(0);
}

void Loader::bindIndicesBuffer(std::vector<GLuint> indices) {
    GLuint vbo_id;
    size_t byte_length = sizeof(GLuint) * indices.size();
    glGenBuffers(1, &vbo_id);
    vbos.push_back(vbo_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, byte_length, indices.data(), GL_STATIC_DRAW);
}

void Loader::cleanUp() {
    // NOTE(shaw): the docs for opengl says that the second arguments here is
    // an "array containing the n names of the objects to be deleted", i am
    // just using the ids here, is this correct?
    glDeleteVertexArrays(vaos.size(), vaos.data());
    glDeleteBuffers(vbos.size(), vbos.data());
    glDeleteTextures(textures.size(), textures.data());
}

