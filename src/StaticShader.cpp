#include "StaticShader.h"
#include <stdio.h>

StaticShader::StaticShader() : ShaderProgram("data/vertexShader.glsl", "data/fragmentShader.glsl") 
{ 
    bindAttributes();
    getAllUniformLocations();
}

void StaticShader::bindAttributes() {
    bindAttribute(0, "position");
    bindAttribute(1, "tex_coords");
}

void StaticShader::getAllUniformLocations() {
    m_locationTransformationMatrix = getUniformLocation("transform");
    m_locationProjectionMatrix = getUniformLocation("projection");
}

void StaticShader::loadTransformationMatrix(glm::mat4 matrix) {
    loadMatrix(m_locationTransformationMatrix, matrix);
}

void StaticShader::loadProjectionMatrix(glm::mat4 matrix) {
    loadMatrix(m_locationProjectionMatrix, matrix);
}
