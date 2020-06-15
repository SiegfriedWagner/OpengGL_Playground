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
    void InitializeVertexBuffer();
    void DeleteVertexBuffer();
protected:
    virtual unsigned int CreateVertexTable(Vertex*& vertices) = 0;
public:
    Matrix4 worldMatrix;
    virtual void Initialize(GLuint postitionAttrib, GLuint colorAttirb);
    virtual void Draw();
    Actor();
    virtual ~Actor();
};
#endif