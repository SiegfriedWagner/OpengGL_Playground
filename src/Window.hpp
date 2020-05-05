#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct GLFWwindow;
enum State { ready, running, closing, closed };
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
    State state;
    std::string windowTitle;
    GLFWwindow* window;
};
#endif