#include "Actor.hpp"
class SphereWithIndexBuffer : public ActorWithIndexBuffer {
 private:
  float radius;
  unsigned int latitudeSectionNum, longitudeSectionNum;
  unsigned int CreateVertexArray(Vertex*& werteksy);
  unsigned int CreateIndexArray(GLuint*& indeksy);

 public:
  SphereWithIndexBuffer(GLuint positionAttrib,
                        GLuint colorAttrib,
                        float radius,
                        unsigned int latitudeSectionNum = 20,
                        unsigned int longitudeSectionNum = 20)
      : ActorWithIndexBuffer(),
        radius(radius),
        latitudeSectionNum(latitudeSectionNum),
        longitudeSectionNum(longitudeSectionNum) {
    Initialize(positionAttrib, colorAttrib);
  }
};