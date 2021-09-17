#include "atkui/framework.h"

using namespace glm;
class Circles : public atkui::Framework
{
public:
   Circles() : atkui::Framework(atkui::Orthographic) {
   }

  struct Circle {

   float pathr;
   float theta;
   float thetaRate;
    vec3 color;

  public:
    Circle() {
      pathr=10;
      thetaRate=0.1;
      color=vec3(0,1,0);
    
    }

    Circle(float r, float t, float tr, vec3 c) {
      theta=t;
      pathr=r;
      thetaRate=tr;
      color=c;
    }


   float setTheta(float t) {
    
    thetaRate=t;
    return  theta;

  }

   float setThetaRate(float tr) {
    
    thetaRate=tr;
    return  thetaRate;

  }

  float setRadius(float r) {
    
    pathr=r;
    return  pathr;

  }



  float getX(float theta) {
     return pathr*cos(theta);
      
  }

  float getY(float theta) {
     return pathr*sin(theta);
      
  }
  
 

  vec3 setColor(vec3 c) {
    color=c;
    return color;
  }

};



 private:

   Circle* concentric[5]={};
   double theta;

   float particlesEven[36]={};
   float particlesOdd[36]={};
  
    
   

  virtual void setup() {
   
  theta=0;

   float rad=70;
   float t=0;
   float tr=0.1;

   for(int j=0;j<5;j++) {
       vec3 color=vec3(0.2,0.8,0.2)+vec3(0.1*j,0.2*j,0.2*j);

      concentric[j]=new Circle(rad,t, tr, color);
     
      rad+=20;
      tr+=0.05;
      tr*=-1;

   }

   double initial=0;
   double initialOdd=2*M_PI;
    for(int i=0;i<36;i++) {
         particlesEven[i]=initial;
         particlesOdd[i]=initial;
         initial+=(2*M_PI)/36; 
         initialOdd-=(2*M_PI)/36;

   }

  
   
  }

  virtual void scene() {

   float radius=10;

   for(int j=0;j<5;j++) {
      Circle circle=*concentric[j];
      setColor(concentric[j]->color);



   for(int i=0;i<36;i++) {
      
   if(circle.thetaRate<0) {
        particlesEven[i]+=circle.thetaRate*dt()+circle.theta;
          float px=circle.pathr*cos(particlesEven[i]);
    float py=circle.pathr*sin(particlesEven[i]);
     drawSphere(vec3(px+width()/2,py+height()/2,0),radius);

   }
   else {
      particlesOdd[i]+=circle.thetaRate*dt()+circle.theta;
        float px=circle.pathr*cos(particlesOdd[i]);
    float py=circle.pathr*sin(particlesOdd[i]);
     drawSphere(vec3(px+width()/2,py+height()/2,0),radius);
   }

   }

   }
      
   
    
    

     
  }
};


int main(int argc, char** argv)
{
   Circles viewer;
   viewer.run();
   return 0;
}
