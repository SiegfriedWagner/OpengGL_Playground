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
    virtual void keyEventHandler(int key, int scancode, int action, int mods);
    virtual void resizeEventHandler(int width, int height);
    virtual void mouseButtonEventHandler(int button, int action, int mods);
    virtual void cursorPostitionCallback(double xpos, double ypos);
    virtual void mouseScrollEventHandler(double xoffset, double yoffset);
   protected:
    virtual void loop();
private:
    int width, height;
    std::string windowTitle;
    GLFWwindow* window;
};

#endif