#pragma once

// forward decl
struct Raw_Model;
struct Model_Texture;

struct Textured_Model {

    Raw_Model* raw_model;
    Model_Texture* texture;

    Textured_Model(Raw_Model* model, Model_Texture* texture) {
        this->raw_model = model;
        this->texture = texture;
    }

};
