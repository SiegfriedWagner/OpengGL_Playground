#ifndef PROJ_OPENGLAPP
#define PROJ_OPENGLAPP
#include <string>
#include "Window.hpp"
#include "Shader.hpp"
#include "MacierzGL.hpp"
#include "Actor.hpp"
enum CamerControlMode {
    FPP,
    TPP,
    ArcBall,
    Model
};
class OpenGLApp : public Window {
public:
  OpenGLApp(int width, int height);
  ~OpenGLApp();
  void LoadShaderFiles(const std::string &vertexShaderPath, 
                       const std::string &fragmentShaderPath);
  void setScene(bool isometricProjection);
  void changeCameraPostion(Matrix4 transformMatrix);
  float getCameraDistanceFromCenter() const;
  Wektor3 getCameraPosition(bool ignoreRotation) const;
  void resizeEventHandler(int width, int height) override;
  void keyEventHandler(int key, int scancode, int action, int mods) override;
  void cursorPostitionCallback(double xpos, double ypos) override;
  void mouseButtonEventHandler(int button, int action, int mods) override;
  void mouseScrollEventHandler(double xoffset, double yoffset) override;
  virtual void animateScene();
 protected:
  Actor** actors;
  unsigned int actorsNum;
  virtual unsigned int prepareActors();
  virtual void drawActors();
  virtual void deleteActors();
  void loop();
  void changeCameraControlMode();
  void inertialMovesCalculation(bool init, float init_dx, float init_dy, float damping);
 private:
  CamerControlMode controlMode;
  Shader shader;
  Matrix4 world, view, projection;
  bool mousePressedFlag, animationEnabled;
};
#endif