#pragma once

#include "ShaderProgram.h"

class StaticShader : public ShaderProgram 
{
private:
    //TODO(shaw): figure this bullshit out
    //char* VERTEX_FILE = "data/vertexShader.txt";
    //char* FRAGMENT_FILE = "data/fragmentShader.txt";

public:
    StaticShader();

protected:
    void bindAttributes() override;
};
