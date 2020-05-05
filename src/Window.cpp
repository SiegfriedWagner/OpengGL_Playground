#include "Window.hpp"

Window::Window(int width, int height) 
    : width(width), height(height), state(ready), windowTitle("Test title")  {
    std::cout << "[Info] Window contructor" << std::endl;
    // GLFW init
    if (!glfwInit()) {
        throw std::runtime_error("Couldn't init GLFW");
    }
    // GLEW init
    int major = 3, minor = 2;
    // setting attribs
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GL_ACTIVE_TEXTURE_ARB, GL_TRUE);
    // GLFW window
    window = glfwCreateWindow(width, height, windowTitle.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Couldn't create a window");
    }
    glfwMakeContextCurrent(window); // required to init glew
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err) 
    {
        throw std::runtime_error(std::string("GLEW initialization failed, with error")
        + (const char*) glewGetErrorString(err));
    }
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    const GLint major_min = 3, minor_min = 2;
    if (major<major_min || (major == major_min && minor<minor_min))
		throw std::runtime_error("OpenGL version is not sufficient");
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
}

void Window::run() {
    if(state != ready)
        throw std::runtime_error("Application is not prepared for run");
    state = running;
    // Make the window's context current
    glfwMakeContextCurrent(window);
    while (state == running)
    {
        bool shouldClose = glfwWindowShouldClose(window);
        if (shouldClose)
            state = closing;
        loop();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
}

void Window::loop() {
    std::cout << "[Info] Window::loop" << std::endl;
}