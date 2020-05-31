#ifndef PROJ_OPENGLAPP
#define PROJ_OPENGLAPP
#include <string>
#include "Window.hpp"
#include "Shader.hpp"
#include "MacierzGL.hpp"

class OpenGLApp : public Window {
public:
    OpenGLApp(int width, int height);
    bool PrepareBuffers();
    void LoadShaderFiles(const std::string &vertexShaderPath, 
                         const std::string &fragmentShaderPath);
    void setScene();
protected:
    void loop();
private:
    GLuint vao, vbo, ebo;
    Shader shader;
    Macierz4 world, view, projection;
};
#endif