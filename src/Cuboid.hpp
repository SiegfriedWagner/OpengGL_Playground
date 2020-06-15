#ifndef CUBOID_H
#define CUBOID_H
#include "Actor.hpp"

class Cuboid : public Actor {
private:
    float edgeX, edgeY, edgeZ;
    bool color;
    unsigned int CreateVertexTable(Vertex*& vertices);

    int firstVertexSubset[6];
    int vertexNumberInSubsets[6];
public:
    void Draw();
    Cuboid(GLuint positionAttrib, GLuint colorAttrib, float edgeX, float edgeY, float edgeZ, bool color);
    static Cuboid* CreateCube(GLuint postionAttrib, GLuint colorAttrib, float edgeLength, bool color);
};
#endif