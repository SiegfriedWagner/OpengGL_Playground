#ifndef VERTEX_H
#define VERTEX_H
struct Vertex
{
	float x, y, z;
	float r, g, b, a; 
	static const int positionVectorLength = 3;
	static const int positionVectorSize = positionVectorLength * sizeof(float);
	static const int colorVectorLength = 4;
	static const int colorVectorSize = colorVectorLength * sizeof(float);
	static const int vertexSize = colorVectorSize + positionVectorSize;
	Vertex(float x, float y, float z, float r, float g, float b, float a = 1.0f) : x(x), y(y), z(z), r(r), g(g), b(b), a(a) { }
    Vertex(): x(0), y(0), z(0), r(0), g(0), b(0), a(1.0f) { }
};
#endif