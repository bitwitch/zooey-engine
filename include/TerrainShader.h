#pragma once

#include "ShaderProgram.h"
#include "Maths.h"
#include "Camera.h"
#include "Light.h"

class TerrainShader : public ShaderProgram 
{
private:
    GLuint location_transformation_matrix;
    GLuint location_projection_matrix;
    GLuint location_view_matrix;
    GLuint location_light_position;
    GLuint location_light_color;
    GLfloat location_shine_damper;
    GLfloat location_reflectivity;

public:
    TerrainShader();
    void loadTransformationMatrix(glm::mat4 matrix);
    void loadProjectionMatrix(glm::mat4 matrix);
    void loadViewMatrix(Camera& camera);
    void loadLight(Light& light);
    void loadShineVariables(GLfloat damper, GLfloat reflectivity);

protected:
    void bindAttributes() override;
    void getAllUniformLocations() override;
};

