#ifndef PROJ_OPENGLAPP
#define PROJ_OPENGLAPP
#include <string>
#include "Window.hpp"
#include "Shader.hpp"

class OpenGLApp : public Window {
public:
    OpenGLApp(int width, int height);
    bool PrepareBuffers();
    void LoadShaderFiles(const std::string &vertexShaderPath, 
                         const std::string &fragmentShaderPath);
protected:
    void loop();
private:
    GLuint vao, vbo, ebo;
    Shader shader;
};
#endif