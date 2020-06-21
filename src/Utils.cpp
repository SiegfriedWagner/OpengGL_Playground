#include "Utils.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include<chrono>

std::string readFile(const std::string &path) {
    std::ifstream file;
    file.open(path);
     std::string retvalue((std::istreambuf_iterator<char>(file)),
                       (std::istreambuf_iterator<char>()));
    return retvalue;
}
// TODO: Replace both timers with more clever solution
bool timePassThresholdCall(long long timeWindow) {
  using namespace std::chrono;
  static milliseconds ms =
      duration_cast<milliseconds>(system_clock::now().time_since_epoch());
  milliseconds curr =
      duration_cast<milliseconds>(system_clock::now().time_since_epoch());
  if ((curr - ms).count() > timeWindow) {
    ms = curr;
    return true;
  }
  return false;
}
bool animationTimePassThresholdCall(long long timeWindow) {
  using namespace std::chrono;
  static milliseconds ms =
      duration_cast<milliseconds>(system_clock::now().time_since_epoch());
  milliseconds curr =
      duration_cast<milliseconds>(system_clock::now().time_since_epoch());
  if ((curr - ms).count() > timeWindow) {
    ms = curr;
    return true;
  }
  return false;
}