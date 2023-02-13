#ifndef INI_LOADER_HPP
#define INI_LOADER_HPP

#include <map>
#include <string>

std::map<std::string, std::string> load_config(const std::string& file_name);

#endif /* INI_LOADER_HPP */