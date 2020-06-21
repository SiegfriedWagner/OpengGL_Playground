#ifndef QUADRID_H
#define QUADRIC_H
#include "Actor.hpp"
class Quadric : public Actor {
private:
	int stripeNum, sectionNum, vertexPerStripe;
	float bottomDiameter, topDiameter, polozeniePodstawy, height;
    int* firstVertexStripes;
    int* verticesInEachStripe;
    static unsigned int CreateFrustrumVertexesArray(Vertex*& vertexArray,
                                                    float bottomDiameter,
                                                    float topDiameter,
                                                    float polozeniePodstawy,
                                                    float height,
                                                    float sectionNum);
    Quadric(GLuint positionAttrib,
            GLuint colorAttrib,
            float bottomDiameter,
            float topDiameter,
            float polozeniePodstawy,
            float height,
            float sectionNum,
            float stripeNum)
        : Actor(),
          stripeNum(stripeNum),
          sectionNum(sectionNum),
          vertexPerStripe(2 * (sectionNum + 1)),
          bottomDiameter(bottomDiameter),
          topDiameter(topDiameter),
          polozeniePodstawy(polozeniePodstawy),
          height(height) {
      Initialize(positionAttrib, colorAttrib);
    };
    unsigned int CreateVertexArray(Vertex*& vertices);

public:
    void Draw();
    static Quadric* CreateFustrumCone(GLuint postionAttrib,
                                   GLuint colorAttirb,
                                   float bottomDiameter,
                                   float topDiameter,
                                   float height,
                                   int sectionNum = 20) {
        return new Quadric(postionAttrib, colorAttirb, bottomDiameter, topDiameter,
                      0.0f, height, sectionNum, 1);
    }
    static Quadric* CreateCylinder(GLuint positionAttrib,
        GLuint colorAttrib,
        float radius,
        float height,
        int sectionNum = 20) {
        return new Quadric(positionAttrib, colorAttrib, radius, radius, 0.0f,
                         height, sectionNum, 1);
    }
    static Quadric* CreateCone(GLuint positionAttrib,
        GLuint colorAttrib,
        float bottomDiameter,
        float height,
        int sectionNum = 20) {
        return new Quadric(positionAttrib, colorAttrib, bottomDiameter, 0.0f,
                         0.0f, height, sectionNum, 1);
    }
    static Quadric* CreateDisc(GLuint positionAttrib,
        GLuint colorAttirb,
        float innerDiameter,
        float outerDiameter,
        int sectionNum = 20) {
      return new Quadric(positionAttrib, colorAttirb, outerDiameter,
                         innerDiameter, 0.0f, 0.0f, sectionNum, 1);
    }
    static Quadric* CreateCircle(GLuint positionAttrib,
        GLuint colorAttrib,
        float diameter,
        float sectionNum) {
      return new Quadric(positionAttrib, colorAttrib, diameter, 0.0f, 0.0f, 0.0f, sectionNum, 1);
    }
    static Quadric* CreateSphere(GLuint postionAttrib,
        GLuint colorAttrib,
        float radius,
        int latitudeSectionsNum = 20,
        int longitudeSectionsNum = 20) {
      return new Quadric(postionAttrib, colorAttrib, radius, 0.0f, 0.0f, 0.0f,
                         latitudeSectionsNum, longitudeSectionsNum);
    }
};

#endif