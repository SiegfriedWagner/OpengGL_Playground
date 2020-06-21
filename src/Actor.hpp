#ifndef ACTOR_H
#define ACTOR_H
#include "MacierzGL.hpp"
#include "Vertex.hpp"
#include <GL/glew.h>
class Actor {
protected:
    GLuint vao, vbo;
    unsigned int vertexNum;
private:
    void InitializeIndexArray();
    void DeleteIndexArray();
protected:
    virtual unsigned int CreateVertexArray(Vertex*& vertices) = 0;
public:
    Matrix4 worldMatrix;
    virtual void Initialize(GLuint postitionAttrib, GLuint colorAttirb);
    virtual void Draw();
    Actor();
    virtual ~Actor();
};
class ActorWithIndexBuffer : public Actor {
 protected:
  unsigned int indexNum;
  unsigned int vbo_index;
 private:
  void InitializeIndexArray();
  void DeleteIndexArray();
 protected:
  virtual unsigned int CreateIndexArray(GLuint*& indexes) = 0;
 public:
  virtual void Initialize(GLuint positionAttirb, GLuint colorAttirb);
  void Draw();
  ActorWithIndexBuffer();
  virtual ~ActorWithIndexBuffer();
};
#endif