#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <vector>

class Loader {

private:
	std::vector<GLuint> vaos;
	std::vector<GLuint> vbos;

    int createVAO();
    void storeDataInAttributeList(int attribute_number, float[] data);
    void unbindVAO();

public:
    RawModel loadToVAO(float[] positions);
    void cleanUp();

};
