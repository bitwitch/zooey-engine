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
    void storeDataInAttributeList(GLuint attribute_number, std::vector<float> data);
    void bindIndicesBuffer(std::vector<int> indices);
    void unbindVAO();

public:
    RawModel loadToVAO(std::vector<float> positions, std::vector<int> indices);
    GLuint loadTexture(const char* filename);
    void cleanUp();

};
