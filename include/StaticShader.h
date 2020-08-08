#pragma once

#include "ShaderProgram.h"

class StaticShader : public ShaderProgram 
{
private:
    GLuint m_locationTransformationMatrix;

public:
    StaticShader();
    void loadTransformationMatrix(const glm::mat4& matrix);

protected:
    void bindAttributes() override;
    void getAllUniformLocations() override;
};
