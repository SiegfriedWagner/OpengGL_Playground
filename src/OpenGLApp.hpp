#ifndef PROJ_OPENGLAPP
#define PROJ_OPENGLAPP
#include <string>
#include "Window.hpp"
#include "Shader.hpp"
#include "MacierzGL.hpp"
enum CamerControlMode {
    FPP,
    TPP,
    ArcBall,
    Model
};
class OpenGLApp : public Window {
public:
  OpenGLApp(int width, int height);
  bool PrepareBuffers();
  void LoadShaderFiles(const std::string &vertexShaderPath, 
                       const std::string &fragmentShaderPath);
  void setScene(bool izometricProjection);
  void changeCameraPostion(Matrix4 transformMatrix);
  float getCameraDistanceFromCenter() const;
  Wektor3 getCameraPosition(bool ignoreRotation) const;
  void resizeEventHandler(int width, int height) override;
  void keyEventHandler(int key, int scancode, int action, int mods) override;
  void cursorPostitionCallback(double xpos, double ypos) override;
  void mouseButtonEventHandler(int button, int action, int mods) override;
  void mouseScrollEventHandler(double xoffset, double yoffset) override;
 protected:
  void loop();
  void changeCameraControlMode();
  void inertialMovesCalculation(bool init, float init_dx, float init_dy, float damping);
 private:
  CamerControlMode controlMode;
  GLuint vao, vbo, ebo;
  Shader shader;
  Matrix4 world, view, projection;
  bool mousePressedFlag;
};
#endif