#ifndef OPENGL_OPENGLAPP
#define OPENGL_OPENGLAPP
#include "Window.hpp"

class OpenGLApp : public Window {
public:
    OpenGLApp(int width, int height);
protected:
    void loop();
private:
    GLuint vao, vbo[3];
};
#endif