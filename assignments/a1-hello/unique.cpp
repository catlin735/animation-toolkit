#include "atkui/framework.h"

using namespace glm;

class Unique : public atkui::Framework {
 public:
  Unique() : atkui::Framework(atkui::Orthographic) {
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
  float moon1_theta;
  float moon1_thetaRate;
  float moon2_theta;
  float moon2_thetaRate;
  Particle* array[100] = {};
    vec3 stdvel;
     double radius;



  virtual void setup() {
    // your code here!
    moon1_theta=0.0;
    moon1_thetaRate=0.5;

    moon2_theta=0.0;
    moon2_thetaRate=0.005;

     radius=5;
    stdvel=agl::randomUnitVector();


    for(int i=0;i<100;i++) {
   
      vec3 velocity=stdvel*((1+agl::random())*10);
     vec3 color=vec3(0.98,0.98,1);
    array[i]=new Particle(vec3(width()*agl::random(),height()*agl::random(),1),velocity,color);
  }
  }

    vec3 move(Particle &particle) {
    vec3 newPos=particle.getPosition()+particle.getVelocity()*elapsedTime();

     if(newPos[0]>width() |newPos[1]>height()) {
       newPos=particle.initial;
    }
  
    particle.setPosition(newPos);
    return vec3(particle.getPosition()[0],particle.getPosition()[1],2000);
  }

  virtual void scene() {

   
  
  setColor(vec3(0,0,0.140+0.1*sin(moon1_theta-0.1)));
     drawSphere(vec3(width()/2, height()/2,-1000),2*height());

      setColor(vec3(1,1,1));
    moon1_theta+= moon1_thetaRate*dt();
    moon2_theta+= moon2_thetaRate*dt();
    float  moon1_px=0.0+0.5*width();
    float  moon1_py=550.0f*sin( moon1_theta)-0.25*height();
      float  moon2_px=300*sin(moon2_theta)+0.28*width();
   //drawSphere(vec3( moon1_px, height()/2,0),100);
   drawSphere(vec3( moon1_px, moon1_py,0),100);
     setColor(vec3(0,0,0.140-0.1*sin(moon1_theta-0.1)));
  drawSphere(vec3( moon2_px, moon1_py,100),100);
  //drawSphere(vec3( moon2_px, height()/2,100),100);

   for(int i=0;i<100;i++) {
     
       setColor(array[i]->color);
      drawSphere(array[i]->currentPos, radius);

    }

  if(elapsedTime()>30) {

   setColor(vec3(0,0,0));
     drawSphere(vec3(width()/2, height()/2,100),2*height());

  } 
  } 
};

int main(int argc, char** argv) {
  Unique viewer;
  viewer.run();
  return 0;
}

