#pragma once

#include "ShaderProgram.h"
#include "Maths.h"
#include "Camera.h"

class StaticShader : public ShaderProgram 
{
private:
    GLuint m_locationTransformationMatrix;
    GLuint m_locationProjectionMatrix;
    GLuint m_locationViewMatrix;

public:
    StaticShader();
    void loadTransformationMatrix(glm::mat4 matrix);
    void loadProjectionMatrix(glm::mat4 matrix);
    void loadViewMatrix(Camera& camera);

protected:
    void bindAttributes() override;
    void getAllUniformLocations() override;
};
