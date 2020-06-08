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
    // callbacks
    glfwSetWindowUserPointer(window, this);
    auto key_callback = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
      static_cast<Window*>(glfwGetWindowUserPointer(window))
          ->keyEventHandler(key, scancode, action, mods);
    };
    glfwSetKeyCallback(window, key_callback);

    auto mouse_postion_callback = [](GLFWwindow* window, double xpos, double ypos) {
      static_cast<Window*>(glfwGetWindowUserPointer(window))
          ->cursorPostitionCallback(xpos, ypos);
    };
    glfwSetCursorPosCallback(window, mouse_postion_callback);

    auto mouse_click_callback = [](GLFWwindow* window, int button, int action,
                                   int mods) {
      static_cast<Window*>(glfwGetWindowUserPointer(window))
          ->mouseButtonEventHandler(button, action, mods);
    };
    glfwSetMouseButtonCallback(window, mouse_click_callback);

    auto resize_callback = [](GLFWwindow* window, int width, int height) {
      static_cast<Window*>(glfwGetWindowUserPointer(window))
          ->resizeEventHandler(width, height);
    };
    glfwSetFramebufferSizeCallback(window, resize_callback);

    auto scroll_callback = [](GLFWwindow* window, double xoffset,
                              double yoffset) {
      static_cast<Window*>(glfwGetWindowUserPointer(window))
          ->mouseScrollEventHandler(xoffset, yoffset);
    };
    glfwSetScrollCallback(window, scroll_callback);
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
int Window::getWidth() {
  return width;
}
int Window::getHeight() {
  return height;
}
void Window::loop() {
  std::cout << "[Info] Window::loop" << std::endl;
}
void Window::keyEventHandler(int key, int scancode, int action, int mods) {
  std::cout << "Callback keycode[" << key <<"]" << std::endl;
}
void Window::resizeEventHandler(int width, int height) {
  glViewport(0, 0, width, height);
  this->width = width;
  this->height = height;
}
void Window::mouseButtonEventHandler(int button, int action, int mods) {
  std::cout << "Mouse clicked: [" << action << "]";
}
void Window::cursorPostitionCallback(double xpos, double ypos) {
  std::cout << "Mouse postion: [" << xpos << "," << ypos << "]" << std::endl;
}
void Window::mouseScrollEventHandler(double xoffset, double yoffset) {
  std::cout << "Mouse scroll: [" << xoffset << "," << yoffset << "]" << std::endl;
}