#include "Utils.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

std::string readFile(const std::string &path) {
    std::ifstream file;
    file.open(path);
     std::string retvalue((std::istreambuf_iterator<char>(file)),
                       (std::istreambuf_iterator<char>()));
    return retvalue;
}