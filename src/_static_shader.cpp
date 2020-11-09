#include "static_shader.h"

Static_Shader::Static_Shader() 
    : Shader_Program("data/shaders/vertex_shader.glsl", "data/shaders/fragment_shader.glsl") 
{ 
    bind_attributes();
    get_all_uniform_locations();
}

void Static_Shader::bind_attributes() {
    bind_attribute(0, "position");
    bind_attribute(1, "tex_coords");
    bind_attribute(2, "normal");
}

void Static_Shader::get_all_uniform_locations() {
    location_transformation_matrix = get_uniform_location("transform");
    location_projection_matrix = get_uniform_location("projection");
    location_view_matrix = get_uniform_location("view");
    location_light_position = get_uniform_location("light_position");
    location_light_color = get_uniform_location("light_color");
    location_shine_damper = get_uniform_location("shine_damper");
    location_reflectivity = get_uniform_location("reflectivity");
    location_sky_color = get_uniform_location("sky_color");
}

void Static_Shader::load_transformation_matrix(glm::mat4 matrix) {
    load_matrix(location_transformation_matrix, matrix);
}

void Static_Shader::load_projection_matrix(glm::mat4 matrix) {
    load_matrix(location_projection_matrix, matrix);
}

void Static_Shader::load_view_matrix(Camera* camera) {
    glm::mat4 view_matrix = Maths::create_view_matrix(camera);
    load_matrix(location_view_matrix, view_matrix);
}

void Static_Shader::load_light(Light* light) {
    load_vector(location_light_position, light->position);
    load_vector(location_light_color, light->color);
}

void Static_Shader::load_sky_color(glm::vec3 color) {
    load_vector(location_sky_color, color);
}

void Static_Shader::load_shine_variables(GLfloat damper, GLfloat reflectivity) {
    load_float(location_shine_damper, damper);
    load_float(location_reflectivity, reflectivity);
}

