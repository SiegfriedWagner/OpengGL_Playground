#include "Square.hpp"

Square::Square(GLuint positionAttrib, GLuint colorAttrib, float edgeLength) : Actor(), edgeLength(edgeLength) {
    Initialize(positionAttrib, colorAttrib);
}
unsigned int Square::CreateVertexTable(Vertex*& vertices) {
    const float x0 = edgeLength / 2.0f;
    const float y0 = edgeLength / 2.0f;
    vertices = new Vertex[4];
    vertices[0] = Vertex(-x0, -y0, 0.0f, 1, 1, 0, 1);//dolny lewy
    vertices[1] = Vertex(x0, -y0, 0.0f, 1, 0, 1, 1); //dolny prawy
    vertices[2] = Vertex(-x0, y0, 0.0f, 0, 1, 1, 1);//górny lewy
    vertices[3] = Vertex(x0, y0, 0.0f, 1, 1, 1, 1);
    return 4;
}