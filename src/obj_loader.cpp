#include "obj_loader.h"

#include "glm_subset.h"
#include <sstream>
#include <vector>
#include <array>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream> 

#include "loader.h"
#include "raw_model.h"

Raw_Model load_obj_model(std::string filename, Loader *loader) {

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texture_coords;
    std::vector<glm::vec3> normals;
    std::vector<std::string> faces;

    // VBO Arrays
    std::vector<GLfloat> vertices_array;
    std::vector<GLfloat> normals_array;
    std::vector<GLfloat> texture_coords_array;
    std::vector<GLuint> indices_array;

    std::ifstream obj_file;
    std::stringstream obj;
    obj_file.exceptions( std::ifstream::badbit );

    // Attempt to read file, if error occurs it returns a nullptr
    try {
        obj_file.open("data/models/" + filename + ".obj");
        obj << obj_file.rdbuf();
        obj_file.close();

    } catch (std::ios_base::failure e) {
        std::cout << "Error loading " << filename << std::endl;
    }

    std::string line;

    while(std::getline(obj, line)) 
    {
        std::istringstream ss(line);

        if (ss.peek() == 'v') {
            ss.seekg(1);

            // vertex
            if (ss.peek() == ' ') {
                ss.seekg(2);
                glm::vec3 vertex;
                ss >> vertex.x >> vertex.y >> vertex.z;
                vertices.push_back(vertex);

            // texture coord
            } else if (ss.peek() == 't') {
                ss.seekg(2);
                glm::vec2 tex_coord;
                ss >> tex_coord.x >> tex_coord.y;
                texture_coords.push_back(tex_coord);

            // normal
            } else if (ss.peek() == 'n') {
                ss.seekg(2);
                glm::vec3 normal;
                ss >> normal.x >> normal.y >> normal.z;
                normals.push_back(normal);
            }

        // face
        } else if (ss.peek() == 'f') {
            ss.seekg(2);
            std::array<std::string, 3> face;
            ss >> face[0] >> face[1] >> face[2];
            for(int i = 0; i < 3; i++)
                faces.push_back(face[i]);
        }
    }

    //
    // fill flat arrays of vertices, texture coords, and normals for opengl
    //
    int ids[3]; // ids = [ v_id, vt_id, vn_id ]
    int i, index_number = 0;
    std::string nustr;
    for (const auto& face: faces) {
        std::istringstream ss(face);

        i = 0;
        while(std::getline(ss, nustr, '/'))
            ids[i++] = std::stoi(nustr);

        glm::vec3 current_vertex = vertices.at(ids[0] - 1);
        vertices_array.push_back(current_vertex.x);
        vertices_array.push_back(current_vertex.y);
        vertices_array.push_back(current_vertex.z);

        glm::vec2 current_tex_coord = texture_coords.at(ids[1] - 1);
        texture_coords_array.push_back(current_tex_coord.x);
        texture_coords_array.push_back(current_tex_coord.y);

        glm::vec3 current_norm = normals.at(ids[2] - 1);
        normals_array.push_back(current_norm.x);
        normals_array.push_back(current_norm.y);
        normals_array.push_back(current_norm.z);

        for (int v=0; v<3; v++) 
            indices_array.push_back(index_number++);
    }

    return loader->load_to_vao(vertices_array, texture_coords_array, normals_array, indices_array);
}

