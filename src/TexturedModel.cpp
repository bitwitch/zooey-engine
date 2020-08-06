#include "TexturedModel.h"

TexturedModel::TexturedModel(RawModel& model, ModelTexture& texture) 
    : m_rawModel(model) , m_modelTexture(texture) { }

ModelTexture& TexturedModel::getTexture() {
    return m_modelTexture;
}

RawModel& TexturedModel::getRawModel() {
    return m_rawModel;
}
