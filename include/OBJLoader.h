#pragma once

#include <string>
#include "RawModel.h"
#include "Loader.h"

class OBJLoader {

public:
    static RawModel loadObjModel(std::string filename, Loader loader);

private:

};
