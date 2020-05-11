#include <string.h>
#include "Window.hpp"

Window::Window(int width, int height) 
    : windowTitle("Test title")  {
    std::cout << "[Info] Window contructor" << std::endl;
    // GLFW init
    if (!glfwInit()) {
        throw std::runtime_error("[Error] Couldn't init GLFW");
    }
    int major = 3, minor = 2;
    // setting attribs
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // GLFW window
    window = glfwCreateWindow(width, height, windowTitle.c_str(), nullptr, nullptr);
    // GLEW init
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("[Error] Couldn't create a window");
    }
    glfwMakeContextCurrent(window); // required to init glew
    GLenum err = glewInit();
    if (GLEW_OK != err) 
    {
        throw std::runtime_error(
            std::string("[Error] GLEW initialization failed, with error")
        + (const char*) glewGetErrorString(err));
    }
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    const GLint major_min = 3, minor_min = 2;
    if (major<major_min || (major == major_min && minor<minor_min))
		throw std::runtime_error("OpenGL version is not sufficient");
    glViewport(0, 0, width, height);
    glGetIntegerv(GL_VIEWPORT, m_viewport);
    // callbacks
    glfwSetFramebufferSizeCallback(window, resizeCallBack);  
}
void Window::setEnvInfoOnTitleBar() {
    char bufor[256];
    bufor[0] = '\0';
    const GLubyte* wersja = glGetString(GL_VERSION);
	strcat(bufor, " OpenGL "); 
	strcat(bufor, (char*)wersja);
	const GLubyte* dostawca = glGetString(GL_VENDOR);
	strcat(bufor, " | "); 
    strcat(bufor, (char*)dostawca);
	const GLubyte* kartaGraficzna = glGetString(GL_RENDERER);
	strcat(bufor, " | "); 
    strcat(bufor, (char*)kartaGraficzna);
	const GLubyte* wersjaGLEW = glewGetString(GLEW_VERSION);
	strcat(bufor, " | GLEW ");
	strcat(bufor, (char*)wersjaGLEW);
    const GLubyte* GLSLversion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    strcat(bufor, " | GLSL ");
    strcat(bufor, (char*)GLSLversion);
    glfwSetWindowTitle(window, bufor);
}
void Window::run() {
    while (!glfwWindowShouldClose(window))
    {
        loop();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}
int Window::getWidth() { // TODO: Maybe simplify to single glGetIntegrev call
    glGetIntegerv(GL_VIEWPORT, m_viewport); 
    return m_viewport[2];
}
int Window::getHeight() {
    glGetIntegerv(GL_VIEWPORT, m_viewport); 
    return m_viewport[3];
}
void Window::loop() {
    std::cout << "[Info] Window::loop" << std::endl;
}
void resizeCallBack(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}