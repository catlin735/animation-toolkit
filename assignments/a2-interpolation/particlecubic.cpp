#include "atkui/framework.h"
using namespace glm;

class ParticleCubic : public atkui::Framework {
 public:
  ParticleCubic() : atkui::Framework(atkui::Orthographic) {
  }

  vec3 B0 = vec3(100,  50, 0);
  vec3 B1 = vec3(150, 200, 0);
  vec3 B2 = vec3(250, 100, 0);
  vec3 B3 = vec3(300, 300, 0);


  void setup() {
  }


  void scene() {
    

     setColor(vec3(0,1,0));
      vec3 prev=B0;
      for(double t=0;t<1;t+=0.01) {
        vec3 newPos=castelCubic(B0,B1,B2,B3,t);
        drawLine(prev,newPos);
        prev=newPos;
      }

      float time=fmod(elapsedTime(),5)/5;
      setColor(vec3(1,0,0));
      drawSphere(castelCubic(B0,B1,B2,B3,time), 10);
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
};

int main(int argc, char** argv) {
  ParticleCubic viewer;
  viewer.run();
}

