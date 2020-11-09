#pragma once

#include <string>

struct Raw_Model;
struct Loader;

Raw_Model load_obj_model(std::string filename, Loader *loader);
