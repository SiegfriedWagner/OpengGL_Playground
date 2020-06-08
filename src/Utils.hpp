#ifndef OPENGL_UTILS
#define OPENGL_UTILS
#include <GL/glew.h>
#include <string>

std::string readFile(const  std::string &path);
bool timePassThresholdCall(long long timeWindow);
#endif