#pragma once

#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include "RawModel.h"

class Loader {

private:
	std::vector<GLuint> vaos;
	std::vector<GLuint> vbos;
	std::vector<GLuint> textures;

    GLuint createVAO();
    void storeDataInAttributeList(GLuint attribute_number, GLuint coord_size, 
            std::vector<float> data);
    void bindIndicesBuffer(std::vector<GLuint> indices);
    void unbindVAO();

public:
    RawModel loadToVAO(std::vector<GLfloat> positions, std::vector<GLfloat> tex_coords, 
            std::vector<GLfloat> normals, std::vector<GLuint> indices);
    GLuint loadTexture(const char* filename);
    void cleanUp();

};
