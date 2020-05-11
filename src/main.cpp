#include "OpenGLApp.hpp"
#include <iostream>
#include "Utils.hpp"
int main(int argc, const char* argv[]) {
  OpenGLApp window(640, 480);
  window.setEnvInfoOnTitleBar();
  window.LoadShaderFiles("../shader/vertex.glsl", "../shader/fragment.glsl");
  window.PrepareBuffers();
  window.run();
  return 0;
}
