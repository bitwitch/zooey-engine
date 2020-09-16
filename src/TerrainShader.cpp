#include "TerrainShader.h"

TerrainShader::TerrainShader() 
    : ShaderProgram("data/shaders/terrain_vertex_shader.glsl", 
                    "data/shaders/terrain_fragment_shader.glsl") 
{ 
    bindAttributes();
    getAllUniformLocations();
}

void TerrainShader::bindAttributes() {
    bindAttribute(0, "position");
    bindAttribute(1, "tex_coords");
    bindAttribute(2, "normal");
}

void TerrainShader::getAllUniformLocations() {
    location_transformation_matrix = getUniformLocation("transform");
    location_projection_matrix = getUniformLocation("projection");
    location_view_matrix = getUniformLocation("view");
    location_light_position = getUniformLocation("light_position");
    location_light_color = getUniformLocation("light_color");
    location_shine_damper = getUniformLocation("shine_damper");
    location_reflectivity = getUniformLocation("reflectivity");
    location_sky_color = getUniformLocation("sky_color");
}

void TerrainShader::loadTransformationMatrix(glm::mat4 matrix) {
    loadMatrix(location_transformation_matrix, matrix);
}

void TerrainShader::loadProjectionMatrix(glm::mat4 matrix) {
    loadMatrix(location_projection_matrix, matrix);
}

void TerrainShader::loadViewMatrix(Camera& camera) {
    glm::mat4 view_matrix = Maths::createViewMatrix(camera);
    loadMatrix(location_view_matrix, view_matrix);
}

void TerrainShader::loadLight(Light& light) {
    loadVector(location_light_position, light.getPosition());
    loadVector(location_light_color, light.getColor());
}

void TerrainShader::loadSkyColor(float r, float g, float b) {
    loadVector(location_sky_color, glm::vec3(r, g, b));
}

void TerrainShader::loadShineVariables(GLfloat damper, GLfloat reflectivity) {
    loadFloat(location_shine_damper, damper);
    loadFloat(location_reflectivity, reflectivity);
}
