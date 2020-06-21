#include "../Actor.hpp"
#include <assert.h>
ActorWithIndexBuffer::ActorWithIndexBuffer() : Actor(), indexNum(-1), vbo_index(0) {}
ActorWithIndexBuffer::~ActorWithIndexBuffer() {
  Actor::~Actor();
  DeleteIndexArray();
}
void ActorWithIndexBuffer::Initialize(GLuint positionAttrib, GLuint colorAttrib) {
  Actor::Initialize(positionAttrib, colorAttrib);
  InitializeIndexArray();
}
void ActorWithIndexBuffer::InitializeIndexArray() {
  glGenBuffers(1, &vbo_index);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_index);
  GLuint* indeksy = NULL;
  indexNum = CreateIndexArray(indeksy);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexNum * sizeof(GLuint),
               indeksy, GL_STATIC_DRAW);
  delete[] indeksy;
}
void ActorWithIndexBuffer::DeleteIndexArray() {
  glDeleteBuffers(1, &vbo_index);
}
void ActorWithIndexBuffer::Draw() {
  assert(indexNum > 0);
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_index);
  glDrawElements(GL_TRIANGLE_STRIP, indexNum, GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ARRAY_BUFFER, NULL);
  glBindVertexArray(NULL);
}