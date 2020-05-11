#ifndef PROJ_WINDOW
#define PROJ_WINDOW
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct GLFWwindow;
class Window {
public:
    Window(int, int);
    void setEnvInfoOnTitleBar();
    void run();
    int getWidth();
    int getHeight();
protected:
    Window(const Window&){};
    virtual void loop(); 
private:
    GLint m_viewport[4];
    std::string windowTitle;
    GLFWwindow* window;
};
void resizeCallBack(GLFWwindow* window, int width, int height);
#endif