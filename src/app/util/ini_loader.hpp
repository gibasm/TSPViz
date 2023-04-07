#ifndef INI_LOADER_HPP
#define INI_LOADER_HPP

#include <map>
#include <string>

/**
 * @brief Performs rough *.ini file parsing 
 * (WARNING: it does not support comments starting with '#' character!!)
 * 
 * @param file_name config file name (*.ini) 
 * @return std::map<std::string, std::string> key value pairs read from the *.ini file 
 */
std::map<std::string, std::string> load_config(const std::string& file_name);

#endif /* INI_LOADER_HPP */