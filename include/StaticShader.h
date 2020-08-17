#pragma once

#include "ShaderProgram.h"
#include "Maths.h"
#include "Camera.h"
#include "Light.h"

class StaticShader : public ShaderProgram 
{
private:
    GLuint m_locationTransformationMatrix;
    GLuint m_locationProjectionMatrix;
    GLuint m_locationViewMatrix;
    GLuint m_locationLightPosition;
    GLuint m_locationLightColor;
    GLfloat m_locationShineDamper;
    GLfloat m_locationReflectivity;

public:
    StaticShader();
    void loadTransformationMatrix(glm::mat4 matrix);
    void loadProjectionMatrix(glm::mat4 matrix);
    void loadViewMatrix(Camera& camera);
    void loadLight(Light& light);
    void loadShineVariables(GLfloat damper, GLfloat reflectivity);

protected:
    void bindAttributes() override;
    void getAllUniformLocations() override;
};
