#include "StaticShader.h"

StaticShader::StaticShader() : ShaderProgram("data/vertexShader.txt", "data/fragmentShader.txt") 
{ 
}

void StaticShader::bindAttributes() {
    ShaderProgram::bindAttribute(0, "position");
}
