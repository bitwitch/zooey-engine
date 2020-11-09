#include "Terrain_Shader.h"

Terrain_Shader::Terrain_Shader() 
    : Shader_Program("data/shaders/terrain_vertex_shader.glsl", 
                    "data/shaders/terrain_fragment_shader.glsl") 
{ 
    bind_attributes();
    get_all_uniform_locations();
}

void Terrain_Shader::bind_attributes() {
    bindAttribute(0, "position");
    bindAttribute(1, "tex_coords");
    bindAttribute(2, "normal");
}

void Terrain_Shader::get_all_uniform_locations() {
    location_transformation_matrix = getUniformLocation("transform");
    location_projection_matrix = getUniformLocation("projection");
    location_view_matrix = getUniformLocation("view");
    location_light_position = getUniformLocation("light_position");
    location_light_color = getUniformLocation("light_color");
    location_shine_damper = getUniformLocation("shine_damper");
    location_reflectivity = getUniformLocation("reflectivity");
    location_sky_color = getUniformLocation("sky_color");
}

void Terrain_Shader::load_transformation_matrix(glm::mat4 matrix) {
    loadMatrix(location_transformation_matrix, matrix);
}

void Terrain_Shader::load_projection_matrix(glm::mat4 matrix) {
    loadMatrix(location_projection_matrix, matrix);
}

void Terrain_Shader::load_view_matrix(Camera& camera) {
    glm::mat4 view_matrix = Maths::createViewMatrix(camera);
    loadMatrix(location_view_matrix, view_matrix);
}

void Terrain_Shader::load_light(Light& light) {
    loadVector(location_light_position, light.getPosition());
    loadVector(location_light_color, light.getColor());
}

void Terrain_Shader::load_sky_color(float r, float g, float b) {
    loadVector(location_sky_color, glm::vec3(r, g, b));
}

void Terrain_Shader::load_shine_variables(GLfloat damper, GLfloat reflectivity) {
    loadFloat(location_shine_damper, damper);
    loadFloat(location_reflectivity, reflectivity);
}
