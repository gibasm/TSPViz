#include "instance.hpp"
#include <spdlog/spdlog.h>
#include <fstream>

TSPInstance::TSPInstance(const char* file_name) {
    this->load_from_file(file_name);
}

TSPInstance::~TSPInstance() {}

void TSPInstance::load_from_file(const char* file_name) {
    spdlog::info("Loading instance " + std::string(file_name) + " ...");
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