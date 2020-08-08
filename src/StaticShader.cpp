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
}

void StaticShader::loadTransformationMatrix(const glm::mat4& matrix) {
    loadMatrix(m_locationTransformationMatrix, matrix);
}
