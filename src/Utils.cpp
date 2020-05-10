#include "Utils.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

bool checkShader(GLuint shader) {
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "[Error] Shader compilation failed\n"; std::cout << infoLog << std::endl;
    }
    return success;
}

bool checkShaderProgram(GLuint shaderProgram) {
    int  success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "[Error] Program linking failed\n"; std::cout << infoLog << std::endl;
    }
    return success;
}

std::string readFile(const std::string &path) {
    std::ifstream file;
    file.open(path);
     std::string retvalue((std::istreambuf_iterator<char>(file)),
                       (std::istreambuf_iterator<char>()));
    return retvalue;
}