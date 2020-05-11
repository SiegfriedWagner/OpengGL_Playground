#ifndef PROJ_SHADER
#define PROJ_SHADER
#include <string>
#include <fstream>
#include <GL/glew.h>
// TODO: Write assignment operator, copy constructor and move constructor and destructor 
class Shader {
public:
    Shader();
    Shader(const std::string &vectorShaderProgram, 
           const std::string &fragmentShaderProgram);
    ~Shader();
    operator GLuint() const;
    static bool checkShader(GLuint shader, bool verbose);
    static bool checkShaderProgram(GLuint shaderProgram, bool verbose);
private:
    GLuint handle;
};
#endif