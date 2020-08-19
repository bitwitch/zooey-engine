#include "TexturedModel.h"

TexturedModel::TexturedModel(RawModel& model, ModelTexture& texture) 
    : raw_model(model) , model_texture(texture) { }

ModelTexture& TexturedModel::getTexture() {
    return model_texture;
}

RawModel& TexturedModel::getRawModel() {
    return raw_model;
}
