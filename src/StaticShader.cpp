#include "StaticShader.h"

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

void StaticShader::loadTransformationMatrix(glm::mat4 matrix) {
    loadMatrix(m_locationTransformationMatrix, matrix);
}
