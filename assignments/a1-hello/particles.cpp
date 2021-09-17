#include "atkui/framework.h"

using namespace glm;


class Particles : public atkui::Framework
{
 public:
  Particles() : atkui::Framework(atkui::Orthographic) {

  }

struct Particle {

    vec3 currentPos;
    vec3 velocity;
    vec3 color;
    vec3 initial;

  public:
    Particle() {
      currentPos=vec3(0,0,1);
      velocity=vec3(0,0,0);
      color=vec3(0,1,0);
    }

    Particle(vec3 pos, vec3 vel, vec3 c) {
      currentPos=pos;
      velocity=vel;
      color=c;
      initial=pos;
    }

  vec3 getPosition() {
    
    return currentPos;

  }
  
  vec3 getVelocity() {
    return velocity;
  }

  vec3 getColor() {
    return color;
  }

  vec3 setPosition(vec3 pos) {
    
    currentPos=pos;
    return currentPos;

  }
  
  vec3 setVelocity(vec3 vel) {
    velocity=vel;
    return velocity;
  }

  vec3 setColor(vec3 c) {
    color=c;
    return color;
  }

};

 private:
    Particle* array[100] = {};
    vec3 stdvel;
     double radius;

  virtual void setup() {
    radius=10;
    stdvel=agl::randomUnitVector();


    for(int i=0;i<100;i++) {
   
      vec3 velocity=stdvel*((1+agl::random())*10);
     vec3 color=vec3(0.2,0.8,0.2)+vec3(agl::random(-0.2,0.2),agl::random(-0.2,0.2),agl::random(-0.2,0.2));
    array[i]=new Particle(vec3(width()*agl::random(),height()*agl::random(),1),velocity,color);
   
    

    }
  }

  virtual void scene() {

    
     for(int i=0;i<100;i++) {
      // setColor(vec3(1,0,1));
       setColor(array[i]->color);
      drawSphere(array[i]->currentPos, radius);
      
     move(*array[i]);

    }
  }

  vec3 move(Particle &particle) {
    vec3 newPos=particle.getPosition()+particle.getVelocity()*elapsedTime();
    if(newPos[0]>width() |newPos[1]>height()) {
       newPos=particle.initial;
      

    }
  
  
    particle.setPosition(newPos);
    return particle.getPosition();
  }
};

int main(int argc, char** argv) {
  Particles viewer;
  viewer.run();
  return 0;
}
