#include <string>
#include "OpenGLApp.hpp"
#include "Utils.hpp"
#include <ctime>
#include <math.h>
#include "Vertex.hpp"
#include "Actor.hpp"
#include "Square.hpp"
#include "Cuboid.hpp"
#include "Quadric.hpp"
#include "Sphere.hpp"

OpenGLApp::OpenGLApp(int width, int height) 
    : Window(width, height), controlMode(CamerControlMode::ArcBall), world(Matrix4::Jednostkowa), 
    view(Matrix4::Jednostkowa), projection(Matrix4::Jednostkowa), mousePressedFlag(false), animationEnabled(false) { 
      actorsNum = prepareActors();
    }
OpenGLApp::~OpenGLApp() {
  deleteActors();
}
unsigned int OpenGLApp::prepareActors() {
  GLuint postitionAttrib = 0;
  GLuint colorAttrib = 1;
  unsigned int actorNumber = 5;
  actors = new Actor*[actorNumber];
  /*actors[0] = Quadric::CreateFustrumCone(postitionAttrib, colorAttrib,
                                            0.3f, 0.1f, 1.0f, 20);
  actors[0]->worldMatrix = Matrix4::Move(-0.6f, -0.6f, 0);
  actors[1] =
      Quadric::CreateCylinder(postitionAttrib, colorAttrib, 0.2f, 1.0f, 20);
  actors[1]->worldMatrix = Matrix4::Move(0.6f, -0.6f, 0);
  actors[2] =
      Quadric::CreateCone(postitionAttrib, colorAttrib, 0.3f, 1.0f, 20);
  actors[2]->worldMatrix = Matrix4::Move(0.6f, 0.6f, 0);
  actors[3] =
      Quadric::CreateDisc(postitionAttrib, colorAttrib, 0.1f, 0.3f, 20);
  actors[3]->worldMatrix = Matrix4::Move(-0.6f, 0.6f, 0);
  actors[4] =
      new SphereWithIndexBuffer(postitionAttrib, colorAttrib, 0.5f, 20, 20);
      
  actors[4]->worldMatrix = Matrix4::Move(0.0f, 0.0f, 0.0f);*/
  //sphere
  actors[0] =
      new SphereWithIndexBuffer(postitionAttrib, colorAttrib, 0.5f, 20, 20);
  actors[0]->worldMatrix = Matrix4::Move(-1.0f, 0, 0);
  //cylinder
  actors[1] =
      Quadric::CreateCylinder(postitionAttrib, colorAttrib, 0.3f, 1.0f, 20);
  actors[1]->worldMatrix = Matrix4::Move(0, 0.5f, 0) * Matrix4::RotationX(90);
  actors[2] = Quadric::CreateCircle(postitionAttrib, colorAttrib, 0.3f, 20);
  actors[2]->worldMatrix = Matrix4::Move(0, 0.5f, 0) * Matrix4::RotationX(-90);
  actors[3] = Quadric::CreateCircle(postitionAttrib, colorAttrib, 0.3f, 20);
  actors[3]->worldMatrix = Matrix4::Move(0, -0.5f, 0) * Matrix4::RotationX(90);
  // cube
  actors[4] = Cuboid::CreateCube(postitionAttrib, colorAttrib, 0.75f, false);
  actors[4]->worldMatrix = Matrix4::Move(1.0f, 0, 0);
  return actorNumber;
}
void OpenGLApp::drawActors() {
  Matrix4 worldCopy = world;
  for(unsigned int i = 0; i < actorsNum; ++i) {
    world.Ustaw(actors[i]->worldMatrix);
    world.setValues();
    actors[i]->Draw();
  }
  world.Ustaw(worldCopy);
}
void OpenGLApp::deleteActors() {
  for (unsigned int i = 0; i < actorsNum; ++i) {
    delete actors[i];
  }
  delete[] actors;
  actorsNum = 0;
}
void OpenGLApp::setScene(bool izometricProjection=false) {
	GLint matrixWorldParam = glGetUniformLocation((GLuint) shader, "matrixWorld"); 
	world.setGLMatrixId(matrixWorldParam, true);

	GLint matrixViewParam = glGetUniformLocation((GLuint) shader, "matrixView");
  view.UstawJednostkow();
	view *= Matrix4::Move(0, 0, -3);
	view.setGLMatrixId(matrixViewParam, true);

	GLint matrixProjectionParam = glGetUniformLocation((GLuint) shader, "matrixProjection");
    float wsp = getHeight() / (float) getWidth();
    if(!izometricProjection) {
        projection.UstawRzutPerspektywiczny(-1.0f, 1.0f, wsp * -1.0f,
                                                    wsp * 1.0f, 1.0f, 10.0f);
    }
    else {
        projection.UstawRzutIzometryczny(-1.0f, 1.0f, wsp * -1.0f,
                                                wsp * 1.0f, 1.0f, 10.0f);
    }
	projection.setGLMatrixId(matrixProjectionParam, true);
    /// DEPTH_TEST - widzenie wnętrza sześcianu lub tła sceny
    glEnable(GL_DEPTH_TEST);
    //glDisable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    //glPolygonMode(GL_FRONT, GL_FILL);
    //glPolygonMode(GL_BACK, GL_LINE);
    /// CULL - wycinanie pierwszoplanowych ścian
    //glCullFace(GL_BACK);
    //glCullFace(GL_FRONT);
    //glEnable(GL_CULL_FACE);
}
void OpenGLApp::LoadShaderFiles(const std::string &vertexShaderPath, 
                                const std::string &fragmentShaderPath) {
	std::string vertexContent = readFile(vertexShaderPath);
	std::string fragmentContent = readFile(fragmentShaderPath);
	if(vertexContent == "" || fragmentContent == "")
		throw std::runtime_error("[Error] Vertex shader or fragment shader is empty");
	shader = Shader(vertexContent, fragmentContent);
    glUseProgram((GLuint)shader);
}
void OpenGLApp::loop() {
  if (timePassThresholdCall(50)) {
    inertialMovesCalculation(false, 0, 0, 0);
  }
  if (animationEnabled && animationTimePassThresholdCall(50)) { // animations
    animateScene();
  }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
  drawActors();
}
void OpenGLApp::resizeEventHandler(int width, int height) {
  Window::resizeEventHandler(width, height);
  GLint screenWidthParam = glGetUniformLocation((GLuint)shader, "screenWidth");
  GLint screenHeightParam =
  glGetUniformLocation((GLuint)shader, "screenHeight");
  glUniform1f(screenWidthParam, getWidth());
  glUniform1f(screenHeightParam, getHeight());
}
void OpenGLApp::keyEventHandler(int key, int scancode, int action, int mods) {
  const float angle = 5.0f;
  Matrix4 m = Matrix4::Jednostkowa;
  if (action & (GLFW_PRESS | GLFW_REPEAT)) {
    switch (key) {
      case GLFW_KEY_LEFT:
      case GLFW_KEY_A:
        m = Matrix4::RotationY(angle);
        break;
      case GLFW_KEY_RIGHT:
      case GLFW_KEY_D:
        m = Matrix4::RotationY(-angle);
        break;
      case GLFW_KEY_DOWN:
      case GLFW_KEY_S:
        m = Matrix4::RotationX(angle);
        break;
      case GLFW_KEY_UP:
      case GLFW_KEY_W:
        m = Matrix4::RotationX(-angle);
        break;
      case GLFW_KEY_COMMA:
        m = Matrix4::RotationZ(angle);
        break;
      case GLFW_KEY_PERIOD:
        m = Matrix4::RotationZ(-angle);
        break;
      case GLFW_KEY_MINUS:
        m = Matrix4::Move(0, 0, 0.1f);
        break;
      case GLFW_KEY_EQUAL:
        m = Matrix4::Move(0, 0, -0.1f);
        break;
      case GLFW_KEY_F5:
        changeCameraControlMode();
        return;
      case GLFW_KEY_F6:
        animationEnabled = !animationEnabled;
        break;
      default:
        break;
    }
    changeCameraPostion(m);
  }
}
void OpenGLApp::changeCameraControlMode() {
  switch (controlMode) {
    case FPP:
      std::cout << "Changing control mode to TPP" << std::endl;
      controlMode = TPP;
      break;
    case TPP:
      std::cout << "Changing control mode to ArcBall" << std::endl;
      controlMode = ArcBall;
      break;
    case ArcBall:
      std::cout << "Changing control mode to Model" << std::endl;
      controlMode = Model;
      break;
    case Model:
      std::cout << "Changing control mode to FPP" << std::endl;
      controlMode = FPP;
      break;
    default:
      break;
  }
}
Wektor3 OpenGLApp::getCameraPosition(bool ignoreRotation) const {
  Wektor3 w3;
  if (ignoreRotation) {
    Wektor4 w4 = view.KopiaKolumny(3);
    for (int i = 0; i < 3; ++i)
      w3[i] = -w4[i];
  }
  else {
    Wektor4 w4 = view.Odwrotna().KopiaKolumny(3);
    for (int i = 0; i < 3; ++i)
      w3[i] = w4[i];
  }
  return w3;
}
float OpenGLApp::getCameraDistanceFromCenter() const {
  return getCameraPosition(true).magnitude();
}
void OpenGLApp::changeCameraPostion(Matrix4 transformMatrix) {
  
  switch (controlMode) {
    case FPP:
      view.lmul(transformMatrix);
      break;
    case TPP: {
      const float tppDistanceFromCenter = 3.0f;
      view.lmul(Matrix4::Move(0, 0, -tppDistanceFromCenter) * transformMatrix *
                Matrix4::Move(0, 0, tppDistanceFromCenter));
      break;
    }
    case ArcBall: {
      Wektor3 cameraPostion = getCameraPosition(true);
      view.lmul(Matrix4::Move(-cameraPostion[0], -cameraPostion[1], -cameraPostion[2]) * transformMatrix *
                Matrix4::Move(cameraPostion[0], cameraPostion[1],
                              cameraPostion[2]));
      break;
    }
    case Model:
      view.rmul(transformMatrix);
      break;
  }
  view.setValues();
}
void OpenGLApp::cursorPostitionCallback(double xpos, double ypos) {
  static double xprev = 0;
  static double yprev = 0;
  const double treshold = 20;
  if (mousePressedFlag) {
    double xdiff = xpos - xprev;
    double ydiff = ypos - yprev;
    double magni = (float)sqrt(xdiff * xdiff + ydiff * ydiff);
    if (magni > treshold) {
      // rotation handling - consider moving to separate function ???
      //std::cout << "[" << xpos - xprev << "," << ypos - yprev << "]" << std::endl;
      const float xfactor = 360.0f / getWidth();
      const float yfactor = 360.0f / getHeight();
      const float dx = xdiff * xfactor;
      const float dy = ydiff * yfactor;
      Matrix4 m = Matrix4::RotationXYZ(dy, dx, 0);
      changeCameraPostion(m);
      inertialMovesCalculation(true, dx, dy, 0.95f);
      xprev = xpos;
      yprev = ypos;
    }
  }
  else {
    xprev = xpos;
    yprev = ypos;
  }
}
void OpenGLApp::mouseButtonEventHandler(int button, int action, int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    mousePressedFlag = true;
  else
    mousePressedFlag = false;
}
void OpenGLApp::mouseScrollEventHandler(double xoffset, double yoffset) {
  // yoffset are vertical movements
  const float sensitivity = 10.0f;
  const float diff = yoffset / abs(yoffset) / sensitivity;
  changeCameraPostion(Matrix4::Move(0, 0, diff));
}
void OpenGLApp::inertialMovesCalculation(bool init, float init_dx, float init_dy, float damping) {
  static float dx = 0;
  static float dy = 0;
  static float factor = 0;
  static bool inertialMovesEnabled = false;
  if (init) {
    inertialMovesEnabled = true;
    dx = init_dx;
    dy = init_dy;
    factor = damping;
    if (factor < 0)
      factor = 0;
    else if (factor > 1)
      factor = 1;
    return;
  } 
  if (inertialMovesEnabled) {
    dx *= factor;
    dy *= factor;
    if (fabs(dx) < 0.001f && fabs(dy) < 0.001f)
      inertialMovesEnabled = true;
    changeCameraPostion(Matrix4::RotationXYZ(dy, dx, 0));
  }
}
void OpenGLApp::animateScene() {
  std::cout << "Animating scene" << std::endl;
}