#include "OpenGLApp.hpp"
#include <iostream>
int main(int argc, const char* argv[]) {
  OpenGLApp window(640, 480);
  if(!window.PrepareBuffers()) {
    std::cout << "[Error] Preparing buffers failed" << std::endl;
    return 1;
  }
  window.run();
  return 0;
}
