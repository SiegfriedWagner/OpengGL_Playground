#ifndef UTILS_H
#define UTILS_H
#include <GL/glew.h>
#include <string>

std::string readFile(const  std::string &path);
bool timePassThresholdCall(long long timeWindow);
bool animationTimePassThresholdCall(long long timeWindow);
#endif