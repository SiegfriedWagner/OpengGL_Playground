#include "../Quadric.hpp"

unsigned int Quadric::CreateFrustrumVertexesArray(Vertex*& vertexArray,
                                                  float bottomDiameter,
                                                  float topDiameter,
                                                  float polozeniePodstawy,
                                                  float height,
                                                  float sectionNum) {
  const unsigned int vertexNum = 2 * (sectionNum + 1);
  const double angleIncrement = 2 * M_PI / sectionNum;
  const float r = 1, g = 1, b = 1, a = 1;
  vertexArray = new Vertex[vertexNum];
  for (int i = 0; i <= sectionNum; i++) {
    double angle = i * angleIncrement;
    vertexArray[2 * i].x = topDiameter * (float)cos(angle);
    vertexArray[2 * i].y = topDiameter * (float)sin(angle);
    vertexArray[2 * i].z = polozeniePodstawy + height;
    vertexArray[2 * i].r = r;
    vertexArray[2 * i].g = g;
    vertexArray[2 * i].b = b;
    vertexArray[2 * i].a = a;
    vertexArray[2 * i + 1].x = bottomDiameter * (float)cos(angle);
    vertexArray[2 * i + 1].y = bottomDiameter * (float)sin(angle);
    vertexArray[2 * i + 1].z = polozeniePodstawy;
    vertexArray[2 * i + 1].r = r;
    vertexArray[2 * i + 1].g = g;
    vertexArray[2 * i + 1].b = b;
    vertexArray[2 * i + 1].a = a;
  }
  return vertexNum;
};
unsigned int Quadric::CreateVertexArray(Vertex*& vertices) {
    if (stripeNum == 1) {
    return CreateFrustrumVertexesArray(vertices, bottomDiameter, topDiameter,
                                       polozeniePodstawy, height, sectionNum);
    } 
    else {
        firstVertexStripes = new int[stripeNum];
        verticesInEachStripe = new int[stripeNum];
        unsigned int totalVertexNum = vertexPerStripe * stripeNum;
        const float radius = bottomDiameter;
        vertices = new Vertex[totalVertexNum];
        double thetaIncrement = M_PI / stripeNum;
        for (int i = 0; i < stripeNum; i++) {
          double topTheta = i * thetaIncrement;
          double bottomTheta = (i + 1) * thetaIncrement;
          float topHeight = (float)(radius * cos(topTheta));
          float bottomHeight = (float)(radius * cos(bottomTheta));
          float _topRadius = (float)(radius * sin(topTheta));
          float _bottomRadius = (float)(radius * sin(bottomTheta));
          Vertex* vertexStripeArray;
          unsigned int vertexInEachStripe = CreateFrustrumVertexesArray(
              vertexStripeArray, _bottomRadius, _topRadius, bottomHeight,
              topHeight - bottomHeight, sectionNum);
          Vertex* beginingOfStripeVertex =
              vertices + vertexInEachStripe * i;  // ??? - to jest jakiœ offset, ale dlaczego to siê tak liczy?
          std::copy(vertexStripeArray, vertexStripeArray + vertexInEachStripe,
                    beginingOfStripeVertex);
          delete[] vertexStripeArray;
          firstVertexStripes[i] = i * vertexInEachStripe;
          verticesInEachStripe[i] = vertexInEachStripe; 
        }
        return totalVertexNum;
    }
}
void Quadric::Draw() {
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  if (stripeNum == 1)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, vertexPerStripe);
  else {
    glMultiDrawArrays(GL_TRIANGLE_STRIP, firstVertexStripes,
                      verticesInEachStripe, stripeNum);  
  }
}