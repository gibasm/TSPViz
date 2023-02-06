#include "instance.hpp"
#include <fstream>
#include <cmath>

TSPInstance::TSPInstance(const char* file_name) {
    this->load_from_file(file_name);
}

TSPInstance::TSPInstance(std::vector<std::array<float, 2>> vertices) {
    this->vertices = vertices;
}

TSPInstance::~TSPInstance() {}

void TSPInstance::load_from_file(const char* file_name) {
    std::ifstream file(file_name);

    if(!file.is_open()) {
        throw std::runtime_error("Cannot open a file: " + std::string(file_name));
    }
    std::string str_buffer;

    while(!file.eof()) {
        file >> str_buffer;
        if(str_buffer.compare("EDGE_WEIGHT_TYPE") == 0) {
            file >> str_buffer >> str_buffer;
            if(str_buffer.compare("EUC_2D") != 0) {
                throw std::runtime_error("Only EUC_2D tsp format allowed!");
            }
        }

        if(str_buffer.compare("NODE_COORD_SECTION") == 0) {
            break;
        }
    }
    
    while(!file.eof()) {
        file >> str_buffer;
        if(str_buffer.compare("EOF") == 0) {
            break;
        }
        
        float x, y;
        
        file >> str_buffer;
        x = std::atof(str_buffer.c_str());
        file >> str_buffer;
        y = std::atof(str_buffer.c_str());

        vertices.push_back(std::array<float, 2>());
        vertices.back().at(0) = x;
        vertices.back().at(1) = y;
    }

}

GraphMatrix TSPInstance::get_neighborhood_matrix() {
    if(matrix.size() > 0) {
        return matrix;
    }

    for(size_t i = 0; i < vertices.size(); ++i) {
        matrix.push_back(std::vector<float>());
        matrix.at(i).resize(vertices.size());
    }

    for(size_t i = 0; i < vertices.size(); ++i) {
        for(size_t j = i+1; j < vertices.size(); ++j) {
            auto u = vertices[i];
            auto v = vertices[j];
            float x = u[0] - v[0];
            float y = u[1] - v[1];
            float d = sqrtf(x*x + y*y);
            matrix[i][j] = d;
            matrix[j][i] = d;
        }
    }

    return matrix;
}