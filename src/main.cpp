/**
 * Main.cpp skeleton
 * Contributors:
 *      * Arthur Sonzogni
 * Licence:
 *      * MIT
 */

#include "OpenGLApp.hpp"
#include <iostream>
/* int main(int argc, const char* argv[]) {
  MyApplication app;
  app.run();
  return 0;
}
 */
int main(int argc, const char* argv[]) {
  OpenGLApp window(640, 480);
  window.run();
  return 0;
}
