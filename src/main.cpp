#include "OpenGLApp.hpp"
#include <iostream>
#include "Utils.hpp"
#include "Matrix.hpp"

int main(int argc, const char* argv[]) {
  OpenGLApp window(640, 480);
  window.setEnvInfoOnTitleBar();
  window.LoadShaderFiles("../shaders/vertex/vertex.glsl", "../shaders/fragment/fragment.glsl");
  window.setScene(false);
  window.run();
  return 0;
}
