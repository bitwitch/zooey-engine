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
    location_transformation_matrix = getUniformLocation("transform");
    location_projection_matrix = getUniformLocation("projection");
    location_view_matrix = getUniformLocation("view");
    location_light_position = getUniformLocation("light_position");
    location_light_color = getUniformLocation("light_color");
    location_shine_damper = getUniformLocation("shine_damper");
    location_reflectivity = getUniformLocation("reflectivity");
}

void StaticShader::loadTransformationMatrix(glm::mat4 matrix) {
    loadMatrix(location_transformation_matrix, matrix);
}

void StaticShader::loadProjectionMatrix(glm::mat4 matrix) {
    loadMatrix(location_projection_matrix, matrix);
}

void StaticShader::loadViewMatrix(Camera& camera) {
    glm::mat4 view_matrix = Maths::createViewMatrix(camera);
    loadMatrix(location_view_matrix, view_matrix);
}

void StaticShader::loadLight(Light& light) {
    loadVector(location_light_position, light.getPosition());
    loadVector(location_light_color, light.getColor());
}

void StaticShader::loadShineVariables(GLfloat damper, GLfloat reflectivity) {
    loadFloat(location_shine_damper, damper);
    loadFloat(location_reflectivity, reflectivity);
}
