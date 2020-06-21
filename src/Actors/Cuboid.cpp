#include "../Cuboid.hpp"

Cuboid::Cuboid(GLuint postionAttirb, GLuint colorAttrib, float edgeX, float edgeY, float edgeZ, bool color) 
    : Actor(), edgeX(edgeX), edgeY(edgeY), edgeZ(edgeZ), color(color) {
    Initialize(postionAttirb, colorAttrib);
}
unsigned int Cuboid::CreateVertexArray(Vertex*& vertices) {
    const float x0 = edgeX / 2.0f;
    const float y0 = edgeY / 2.0f;
    const float z0 = edgeZ / 2.0f;

    for (int i = 0; i< 6; ++i) {
        firstVertexSubset[i] = i *4;
        vertexNumberInSubsets[i] = 4;
    }

    vertices = new Vertex[24];
    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;
    if (color) {
        r = 1.0f;
        g = 0.0f;
        b = 0.0f;
    }
    //tylna
    vertices[0] = Vertex(x0, -y0, -z0, r, g, b);
    vertices[1] = Vertex(-x0, -y0, -z0, r, g, b);
    vertices[2] = Vertex(x0, y0, -z0, r, g, b);
    vertices[3] = Vertex(-x0, y0, -z0, r, g, b);
    //przednia
    vertices[4] = Vertex(-x0, -y0, z0, r, g, b);
    vertices[5] = Vertex(x0, -y0, z0, r, g, b);
    vertices[6] = Vertex(-x0, y0, z0, r, g, b);
    vertices[7] = Vertex(x0, y0, z0, r, g, b);
    if(color) { 
        r = 0.0f; 
        g = 1.0f; 
        b = 0.0f; 
    }//prawa
    vertices[8] = Vertex(x0, -y0, z0, r, g, b);
    vertices[9] = Vertex(x0, -y0, -z0, r, g, b);
    vertices[10] = Vertex(x0, y0, z0, r, g, b);
    vertices[11] = Vertex(x0, y0, -z0, r, g, b);
    //lewa
    vertices[12] = Vertex(-x0, -y0, -z0, r, g, b);
    vertices[13] = Vertex(-x0, -y0, z0, r, g, b);
    vertices[14] = Vertex(-x0, y0, -z0, r, g, b);
    vertices[15] = Vertex(-x0, y0, z0, r, g, b);
    if(color) { 
        r = 0.0f; 
        g = 0.0f; 
        b = 1.0f; }
    //górna
    vertices[16] = Vertex(-x0, y0, z0, r, g, b);
    vertices[17] = Vertex(x0, y0, z0, r, g, b);
    vertices[18] = Vertex(-x0, y0, -z0, r, g, b);
    vertices[19] = Vertex(x0, y0, -z0, r, g, b);
    //dolna
    vertices[20] = Vertex(-x0, -y0, -z0, r, g, b);
    vertices[21] = Vertex(x0, -y0, -z0, r, g, b);
    vertices[22] = Vertex(-x0, -y0, z0, r, g, b);
    vertices[23] = Vertex(x0, -y0, z0, r, g, b);
    return 24;
}
void Cuboid::Draw() {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glMultiDrawArrays(GL_TRIANGLE_STRIP, firstVertexSubset, vertexNumberInSubsets, 6);
}
Cuboid* Cuboid::CreateCube(GLuint postionAttrib, GLuint colorAttrib, float edgeLenght, bool color) {
    return new Cuboid(postionAttrib, colorAttrib, edgeLenght, edgeLenght, edgeLenght, color);
}