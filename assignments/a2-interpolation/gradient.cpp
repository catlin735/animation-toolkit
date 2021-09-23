#include <iostream>
#include "atkui/framework.h"
using namespace glm;

class Gradient : public atkui::Framework {

private:

const vec3 nw=vec3(1,1,0);
const vec3 ne=vec3(0,1,1);
const vec3 sw=vec3(1,0,0);
const vec3 se=vec3(1,0,1);
int n=12;
vec3 size=vec3(50,50,1);
int window=600;


 public:
  Gradient() : atkui::Framework(atkui::Orthographic) {
  }

 virtual void setup() {

   setWindowSize(window, window);
  
      
  }

  virtual void scene() {

   

    int xPos=(size[0]/2)*-1;
   for(int i=0;i<n;i++) {
     xPos+=size[0];
    int yPos=(size[1]/2)*-1;
     
      for(int j=0;j<n;j++) {

         yPos+=size[1];
         vec3 position=vec3(xPos,yPos,1);
        setColor(getGradient(getT(position)));
         drawCube(position,size);

      }
   }
    
  }

  vec3 lerp(vec3 a, vec3 b, float t) {
    
    return a*(1-t)+b*t;
  }

  vec3 getT(vec3 position) {
    return vec3(position[0]/window,position[1]/window,position[2]);
  }

  vec3 getGradient(vec3 t) {
    float x=t[0];
    float y=t[1];
    vec3 color1=lerp(nw,ne,x);
    vec3 color2=lerp(sw,se,x);

    return lerp(color1,color2,y);
  }
};

int main(int argc, char **argv) {
  Gradient viewer;
  viewer.run();
}
