#include "Terrain.h"
#include <vector>

Terrain::Terrain(int grid_x, int grid_y, Loader& loader, ModelTexture& texture) 
:   x         ( grid_x * SIZE )
,   z         ( grid_y * SIZE )
,   model     ( generateTerrain(loader) )
,   texture   ( texture )
{ }

RawModel Terrain::generateTerrain(Loader& loader) {
    int count = VERTEX_COUNT * VERTEX_COUNT;
    std::vector<GLfloat> vertices(count * 3);
    std::vector<GLfloat> tex_coords(count * 2);
    std::vector<GLfloat> normals(count * 3);
    std::vector<GLuint> indices(6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1));

    int vertex_pointer = 0;
    for (int i=0; i<VERTEX_COUNT; i++) {
        for (int j=0; j<VERTEX_COUNT; j++) {
            vertices[vertex_pointer*3]   = -(float)j / ((float)VERTEX_COUNT - 1) * SIZE;
            vertices[vertex_pointer*3+1] = 0;
            vertices[vertex_pointer*3+2] = -(float)i / ((float)VERTEX_COUNT - 1) * SIZE;

            tex_coords[vertex_pointer*2]   = (float)j / ((float)VERTEX_COUNT - 1);
            tex_coords[vertex_pointer*2+1] = (float)i / ((float)VERTEX_COUNT - 1);

            normals[vertex_pointer*3]   = 0;
            normals[vertex_pointer*3+1] = 1;
            normals[vertex_pointer*3+2] = 0;
            vertex_pointer++;
        }
    }

    int pointer = 0;
    for (int gz=0; gz<VERTEX_COUNT-1; gz++) {
        for (int gx=0; gx<VERTEX_COUNT-1; gx++) {
            int top_left = gz * VERTEX_COUNT + gx;
            int top_right = top_left + 1; 
            int bottom_left = ((gz+1) * VERTEX_COUNT) + gx;
            int bottom_right = bottom_left + 1; 
            indices[pointer++] = top_left;
            indices[pointer++] = bottom_left;
            indices[pointer++] = top_right;
            indices[pointer++] = top_right;
            indices[pointer++] = bottom_left;
            indices[pointer++] = bottom_right;
        }
    }

    return loader.loadToVAO(vertices, tex_coords, normals, indices);
}

GLfloat Terrain::getX() {
    return x;
}

GLfloat Terrain::getZ() {
    return z;
}

RawModel& Terrain::getModel() {
    return model;
}

ModelTexture& Terrain::getTexture() {
    return texture;
}
