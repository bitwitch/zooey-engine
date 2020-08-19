#pragma once

#include "RawModel.h"
#include "ModelTexture.h"

class TexturedModel {

private:
    RawModel& raw_model;
    ModelTexture& model_texture;

public:
    TexturedModel(RawModel& model, ModelTexture& texture);
    RawModel& getRawModel();
    ModelTexture& getTexture();

};
