#include "atkui/framework.h"

using glm::vec3;

class Sphere3D : public atkui::Framework {
  vec3 velocity;
  vec3 position;
 public:
  Sphere3D() : atkui::Framework(atkui::Perspective) {

  }

  virtual void setup() {
    position=vec3(0,0,0);
    velocity=vec3(0,0,0);
  }


  virtual void scene() {
    // colors are RGB triplets in range [0,1]
    setColor(vec3(0,1,0));

    // draw a sphere at center of the world
    float radius = 50.0;
    position=position+(velocity * dt());
    drawSphere(position, radius);

  }

  void keyUp(int key, int mods) {

    if(key == GLFW_KEY_SPACE) {
      velocity=vec3(agl::random(-1,1),agl::random(),agl::random(-1,1))*vec3(10,10,10);
      //velocity=vec3(10,10,10);
    

    }

    if(key == GLFW_KEY_R) {
      position=vec3(0,0,0);
     
     // velocity=vec3(100,1,1);
      //position=velocity * dt();
      //drawSphere(velocity, 50.0);

    }

  }

};

int main(int argc, char** argv)
{
  Sphere3D viewer;
  viewer.run();
  return 0;
}
