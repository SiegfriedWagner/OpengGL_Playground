#include "Actor.hpp"

class Square : public Actor {
private:
    float edgeLength;
    unsigned int CreateVertexTable(Vertex*& vertices);
public:
    Square(GLuint postitionAttrib, GLuint colorAttrib, float edgeLength=2.0f);
};