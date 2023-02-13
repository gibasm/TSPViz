#include "ini_loader.hpp"
#include <fstream>
#include <algorithm>

static inline void trim(std::string &str); 

std::map<std::string, std::string> load_config(const std::string& file_name) {
    std::ifstream file(file_name);
    if(!file.is_open()) {
        throw std::runtime_error("Cannot open solver configuration file config.ini!");
    }

    std::string key, value;
    std::map<std::string, std::string> map;
    while(!file.eof()) {
        std::getline(file, key, '=');
        std::getline(file, value);
        trim(key);
        trim(value);
        map.insert(std::make_pair(key, value));
    }

    return map;
}


static inline void trim(std::string &str) {
    str.erase(0, str.find_first_not_of(" \n\r\t"));                                                                                               
    str.erase(str.find_last_not_of(" \n\r\t")+1);  
}