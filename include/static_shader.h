#pragma once

#include "shader_program.h"
#include "maths.h"
#include "camera.h"
#include "light.h"

struct Static_Shader : public Shader_Program {

    GLuint location_transformation_matrix;
    GLuint location_projection_matrix;
    GLuint location_view_matrix;
    GLuint location_light_position;
    GLuint location_light_color;
    GLfloat location_shine_damper;
    GLfloat location_reflectivity;
    GLfloat location_sky_color;

    Static_Shader();
    void load_transformation_matrix(glm::mat4 matrix);
    void load_projection_matrix(glm::mat4 matrix);
    void load_view_matrix(Camera* camera);
    void load_light(Light* light);
    void load_sky_color(float r, float g, float b);
    void load_shine_variables(GLfloat damper, GLfloat reflectivity);

    void bind_attributes() override;
    void get_all_uniform_locations() override;

};
