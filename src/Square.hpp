#ifndef  SQUARE_H
#define SQUARE_H
#include "Actor.hpp"

class Square : public Actor {
private:
    float edgeLength;
    unsigned int CreateVertexArray(Vertex*& vertices);
public:
    Square(GLuint postitionAttrib, GLuint colorAttrib, float edgeLength=2.0f);
};

class SquareWithIndexBuffer : public ActorWithIndexBuffer {
 private:
  float edgesLength;
  unsigned int CreateVertexArray(Vertex*& vertices);
  unsigned int CreateIndexArray(GLuint*& indexes);
 public:
  SquareWithIndexBuffer(GLuint positionAttrib,
                        GLuint colorAttrib,
                        float edgesLength = 2.0f);
};
#endif