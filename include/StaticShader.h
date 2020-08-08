#pragma once

#include "ShaderProgram.h"

class StaticShader : public ShaderProgram 
{
private:
    GLuint m_locationTransformationMatrix;
    GLuint m_locationProjectionMatrix;

public:
    StaticShader();
    void loadTransformationMatrix(glm::mat4 matrix);
    void loadProjectionMatrix(glm::mat4 matrix);

protected:
    void bindAttributes() override;
    void getAllUniformLocations() override;
};
