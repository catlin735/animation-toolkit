#include <iostream>
#include <stdio.h>
#include "atkui/framework.h"
using namespace glm;

class DrawCubic : public atkui::Framework
{
 public:
  DrawCubic() : atkui::Framework(atkui::Orthographic, 400, 400) {
  }

   private:
  vec3 B0 = vec3(100,  50, 0);
  vec3 B1 = vec3(150, 200, 0);
  vec3 B2 = vec3(250, 100, 0);
  vec3 B3 = vec3(300, 300, 0);


  virtual void scene()
  {
    setColor(vec3(0,0,1));
    drawSphere(B0, 10);
    drawSphere(B3, 10);

    setColor(vec3(1,1,0));
    drawSphere(B1, 10);
    drawSphere(B2, 10);

     setColor(vec3(0,1,0));
      vec3 prev=B0;
      for(double t=0;t<1;t+=0.01) {
       // vec3 newPos=bernstein(B0,B1,B2,B3,t);
        vec3 newPos=castelCubic(B0,B1,B2,B3,t);
        drawLine(prev,newPos);
        prev=newPos;
      }
  }

  float cube(int x) {
    return x*x*x;
  }

  float square(int x) {
    return x*x;
  }

  vec3 lerp(vec3 a, vec3 b, float t) {
    
    return a*(1-t)+b*t;
  }


  vec3 castel2(vec3 a, vec3 b, vec3 c, float t) {
    return lerp(lerp(a,b,t),lerp(b,c,t),t);
  }

  vec3 castelCubic(vec3 a, vec3 b, vec3 c, vec3 d, float t) {

      return lerp(castel2(a,b,c,t),castel2(b,c,d,t),t);
  }

  vec3 bernstein(vec3 a, vec3 b, vec3 c, vec3 d, float t) {
    return (cube(1-t)*a)+(3*t*square(1-t)*b)+(3*square(t)*(1-t)*c);
  }

  void keyUp(int key, int mod) {
    if (key == GLFW_KEY_1) {
      // draw Bernstein
    
    }
    else if (key == GLFW_KEY_2) {
      // draw Casteljau

    }
  }

};

int main(int argc, char **argv) {
  DrawCubic viewer;
  viewer.run();
}
