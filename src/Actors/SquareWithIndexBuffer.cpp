#include "../Square.hpp"

SquareWithIndexBuffer::SquareWithIndexBuffer(GLuint positionAttrib,
    GLuint colorAttrib,
    float edgesLength)
    : ActorWithIndexBuffer(), edgesLength(edgesLength) {
  Initialize(positionAttrib, colorAttrib);
}
unsigned int SquareWithIndexBuffer::CreateVertexArray(Vertex*& vertices) {
  const float x0 = edgesLength / 2.0f;
  const float y0 = edgesLength / 2.0f;
  vertices = new Vertex[5];
  vertices[0] = Vertex(-x0, -y0, 0.0f, 1, 0, 0, 1);  // dolny lewy
  vertices[1] = Vertex(x0, -y0, 0.0f, 0, 1, 0, 1);  // dolny prawydsadasdas
  vertices[2] = Vertex(0, y0, 0.0f, 0, 0, 1, 1);  // górny
  vertices[3] = Vertex(-x0, y0, 0.0f, 0, 0, 1, 1);  // górny lewy
  vertices[4] = Vertex(x0, y0, 0.0f, 0, 0, 1, 1);  // górny prawy
  return 5;
}
unsigned int SquareWithIndexBuffer::CreateIndexArray(GLuint*& indexes)
{
  indexes = new GLuint[4];
  indexes[0] = 0;
  indexes[1] = 1;
  indexes[2] = 3;
  indexes[3] = 4;
  return 4;
}
