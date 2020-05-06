#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct GLFWwindow;
class Window {
public:
    Window(int, int);
    void run();
protected:
    Window(const Window&){};
    virtual void loop(); 
private:
    int width;
    int height;
    std::string windowTitle;
    GLFWwindow* window;
};
#endif