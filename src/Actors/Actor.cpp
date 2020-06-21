#include "../Actor.hpp"
#include "../Vertex.hpp"
#include "GL\glew.h"

void Actor::InitializeIndexArray() {
    //Vertex Array Object (VAO)
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    //Vertex Buffer Object (VBO)
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    Vertex* vertices = nullptr;
    vertexNum = CreateVertexArray(vertices);
    glBufferData(GL_ARRAY_BUFFER, vertexNum*sizeof(Vertex), vertices, GL_STATIC_DRAW);
    delete[] vertices;
}
void Actor::Initialize(GLuint positionAttrib, GLuint colorAttrib){
    InitializeIndexArray();
    glVertexAttribPointer(positionAttrib, Vertex::colorVectorLength, GL_FLOAT, GL_FALSE,Vertex::vertexSize, 0);
    glEnableVertexAttribArray(positionAttrib);
    glVertexAttribPointer(colorAttrib, Vertex::colorVectorLength ,GL_FLOAT, GL_FALSE, Vertex::vertexSize,(const GLvoid*) Vertex::positionVectorSize);
    glEnableVertexAttribArray(colorAttrib);
}
Actor::Actor() : vertexNum(-1), worldMatrix(Matrix4::Jednostkowa) {}
void Actor::DeleteIndexArray() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}
Actor::~Actor() {
    DeleteIndexArray();
}
void Actor::Draw() {
    assert(vertexNum > 0);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexNum);
}