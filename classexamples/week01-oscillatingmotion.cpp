#include "atkui/framework.h"

using glm::vec3;

class Sphere2D : public atkui::Framework {

private:
    float theta;
    float thetaRate;
    float r;
    
 public:
  Sphere2D() : atkui::Framework(atkui::Orthographic) {
  }

  virtual void setup() {
      theta=0.0;
      thetaRate=0.5;
  }

  virtual void scene() {
    // colors are RGB triplets in range [0,1]
    setColor(vec3(0,1,0));
    theta+=thetaRate*dt();
    float px=0.0+0.5*width();
    float py=200.0f*sin(theta)+0.5*height();
    drawSphere(vec3(px,py,0),100);

  }
};



int main(int argc, char** argv)
{
  Sphere2D viewer;
  viewer.run();
  return 0;
}
