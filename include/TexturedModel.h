#pragma once

#include "RawModel.h"
#include "ModelTexture.h"

class TexturedModel {

public:
    RawModel* m_rawModel;
    ModelTexture* m_modelTexture;

public:
    TexturedModel(RawModel* model, ModelTexture* texture);


};
