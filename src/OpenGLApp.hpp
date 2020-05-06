#ifndef OPENGL_OPENGLAPP
#define OPENGL_OPENGLAPP
#include "Window.hpp"

class OpenGLApp : public Window {
public:
    OpenGLApp(int width, int height);
    bool PrepareBuffers();
protected:
    void loop();
private:
    GLuint vao, vbo, ebo, shaderProgram;
};
#endif