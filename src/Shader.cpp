#include "Shader.hpp"
#include <iostream>

Shader::Shader() : handle(0) { };
Shader::Shader(const std::string &vertexShaderSource, const std::string &fragmentShaderSource) 
    : handle(glCreateProgram()) {
	// create vertex shader
    if (vertexShaderSource != "") {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const char * c_str = vertexShaderSource.c_str();
	    glShaderSource(vertexShader, 1, &c_str, nullptr);
	    glCompileShader(vertexShader);
	    if(!checkShader(vertexShader, true))
		    throw std::runtime_error("[Error] Compiling vertex shader failed");
	    glAttachShader(handle, vertexShader);
	    //glDeleteShader(vertexShader);
    }
	// create fragment shader
    if(fragmentShaderSource != "")
    {
	    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char * c_str = fragmentShaderSource.c_str();
	    glShaderSource(fragmentShader, 1, &c_str, nullptr);
	    glCompileShader(fragmentShader);
	    if(!checkShader(fragmentShader, true))
            throw std::runtime_error("[Error] Compiling fragment shader failed");
	    glAttachShader(handle, fragmentShader);
	    //glDeleteShader(fragmentShader);
    }
	// link all in shader program
	glLinkProgram(handle);
	if(!checkShaderProgram(handle, true))
		throw std::runtime_error("[Error] Linking shader program failed");
}
Shader::~Shader() {
    // glDeleteProgram(handle);
}
Shader::operator GLuint() const {
    return handle;
}
bool Shader::checkShader(GLuint shader, bool verbose) {
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success && verbose)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "[Error] Shader compilation failed with message\n"; std::cout << infoLog << std::endl;
    }
    return success;
}

bool Shader::checkShaderProgram(GLuint shaderProgram, bool verbose) {
    int  success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success && verbose)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "[Error] Program linking failed\n"; std::cout << infoLog << std::endl;
    }
    return success;
}