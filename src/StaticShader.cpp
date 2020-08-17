#include "StaticShader.h"

StaticShader::StaticShader() : ShaderProgram("data/vertexShader.glsl", "data/fragmentShader.glsl") 
{ 
    bindAttributes();
    getAllUniformLocations();
}

void StaticShader::bindAttributes() {
    bindAttribute(0, "position");
    bindAttribute(1, "tex_coords");
    bindAttribute(2, "normal");
}

void StaticShader::getAllUniformLocations() {
    m_locationTransformationMatrix = getUniformLocation("transform");
    m_locationProjectionMatrix = getUniformLocation("projection");
    m_locationViewMatrix = getUniformLocation("view");
    m_locationLightPosition = getUniformLocation("light_position");
    m_locationLightColor = getUniformLocation("light_color");
    m_locationShineDamper = getUniformLocation("shine_damper");
    m_locationReflectivity = getUniformLocation("reflectivity");
}

void StaticShader::loadTransformationMatrix(glm::mat4 matrix) {
    loadMatrix(m_locationTransformationMatrix, matrix);
}

void StaticShader::loadProjectionMatrix(glm::mat4 matrix) {
    loadMatrix(m_locationProjectionMatrix, matrix);
}

void StaticShader::loadViewMatrix(Camera& camera) {
    glm::mat4 view_matrix = Maths::createViewMatrix(camera);
    loadMatrix(m_locationViewMatrix, view_matrix);
}

void StaticShader::loadLight(Light& light) {
    loadVector(m_locationLightPosition, light.getPosition());
    loadVector(m_locationLightColor, light.getColor());
}

void StaticShader::loadShineVariables(GLfloat damper, GLfloat reflectivity) {
    loadFloat(m_locationShineDamper, damper);
    loadFloat(m_locationReflectivity, reflectivity);
}
