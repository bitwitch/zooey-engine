#include "Textured_Model.h"

Textured_Model::Textured_Model(Raw_Model& model, Model_Texture& texture) 
    : raw_model(model) , model_texture(texture) { }

Model_Texture& Textured_Model::getTexture() {
    return model_texture;
}

Raw_Model& Textured_Model::getRaw_Model() {
    return raw_model;
}
