#include "../Sphere.hpp"
#include <iostream>

unsigned int SphereWithIndexBuffer::CreateVertexArray(Vertex*& vertices) {
  const unsigned int totalVertexNumber =
      latitudeSectionNum * (longitudeSectionNum - 1) + 2;
  vertices = new Vertex[totalVertexNumber];
  const double przyrostK�taTheta = M_PI / longitudeSectionNum;
  const double przyrostK�taPhi = 2 * M_PI / latitudeSectionNum;
  const float r = 1, g = 1, b = 1, a = 1;
  for (unsigned int i = 0; i < longitudeSectionNum-1; i++)

  {
    double k�tTheta = i * przyrostK�taTheta;
    float _height = (float)(radius * cos(k�tTheta));
    float _radius = (float)(radius * sin(k�tTheta));
    // werteksy[0] = Vertex(0, 0, radius, r, g, b, a); //biegun p�nocny
    for (unsigned int j = 0; j < latitudeSectionNum; j++) {
      double k�tPhi = j * przyrostK�taPhi;
      int indeks = 1 + j + i * latitudeSectionNum;
      vertices[indeks].x = _radius * (float)cos(k�tPhi);
      vertices[indeks].y = _radius * (float)sin(k�tPhi);
      vertices[indeks].z = _height;
      /*vertices[indeks].r = 1.0f * rand() / RAND_MAX;
      vertices[indeks].g = 1.0f * rand() / RAND_MAX;
      vertices[indeks].b = 1.0f * rand() / RAND_MAX;*/
      vertices[indeks].r = r;
      vertices[indeks].g = g;
      vertices[indeks].b = b;
      vertices[indeks].a = 1;
    }
  }
  vertices[0].x = 0;
  vertices[0].y = 0;
  vertices[0].z = radius;
  vertices[0].r = 0;
  vertices[0].g = 0;
  vertices[0].b = 0;
  unsigned int index = 1 + (longitudeSectionNum - 1) * latitudeSectionNum;
  vertices[index].x = 0;
  vertices[index].y = 0;
  vertices[index].z = -radius;
  vertices[index].r = 0;
  vertices[index].g = 0;
  vertices[index].b = 0;
  return totalVertexNumber;
}

unsigned int SphereWithIndexBuffer::CreateIndexArray(GLuint*& indexes)
{
  const unsigned int liczbaIndeks�wWPa�mie =
      2 * (latitudeSectionNum + 1);
  const unsigned int totalIndexNum =
      liczbaIndeks�wWPa�mie * longitudeSectionNum;

  indexes = new GLuint[totalIndexNum];

  for (unsigned int i = 0; i < longitudeSectionNum; i++)
  {
    for (unsigned int j = 0; j <= latitudeSectionNum; j++)
    {
      unsigned int index = j + i * (latitudeSectionNum + 1);
      indexes[2 * index] =
          (i == 0) ? 0 : (1 + j + (i - 1) * latitudeSectionNum);

      indexes[2 * index + 1] =
          (i == longitudeSectionNum - 1)
              ? (vertexNum - 1)
              : (1 + j + i * latitudeSectionNum); 
    }
    unsigned int _indeks =
        latitudeSectionNum + i * (latitudeSectionNum + 1);
    indexes[2 * _indeks] = (i == 0) ? 0 : (i * latitudeSectionNum);
    indexes[2 * _indeks + 1] =
        (i == longitudeSectionNum - 1)
            ? (vertexNum - 1)
            : (indexes[2 * _indeks] + latitudeSectionNum); 
  }
  return totalIndexNum;
}
