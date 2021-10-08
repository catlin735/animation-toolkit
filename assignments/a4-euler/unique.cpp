#include "atkui/framework.h"
#include "teapots.h"
#include "atkmath/constants.h"
#include "atkmath/vector3.h"
#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace glm;
using glm::vec3;
using atkmath::Deg2Rad;
using atkmath::Rad2Deg;
using atkmath::Matrix3;
using atkmath::Vector3;

class Triangle : public atkui::Framework {
 public:
  Triangle() : atkui::Framework(atkui::Orthographic) {
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
  
    double theta;
    double r;
  Particle* array[100] = {};
   Vector3 pos1=Vector3((width()/2)+10,(height()/2)+30,0);
   Vector3 pos2=Vector3((width()/2)-20,(height()/2)-20,0);
  // Vector3 pos3=Vector3((width()/2)+30,height()/2,0);



  virtual void setup() {
     theta=0;
     r=0;
   
  }

  virtual void scene() {

      Matrix3 rot;
      Matrix3 rot2;
     
      theta+=0.001;

   
     
      
      Vector3 radius(100,100,0);
      Vector3 translate(200,200,0);
       Vector3 radius2(20,20,0);
        Vector3 euler(theta, theta, theta);
        Vector3 euler2(theta*10, theta*10, theta*10);
          rot.fromEulerAnglesXYZ(euler);
          rot2.fromEulerAnglesXYZ(euler2);
         pos1=operator*(rot,radius)+translate;
         pos2=operator*(rot2,radius2)+pos1;
         //  pos3=operator*(rot,radius)+translate;
           
             setColor(vec3(1,1,0));
           drawSphere(vec3(230,230,translate[2]),50);
              setColor(vec3(0.7,0.9,1));
         drawSphere(vec3(pos1[0],pos1[1],pos1[2]),20);
          setColor(vec3(1,1,1));
         drawSphere(vec3(pos2[0],pos2[1],pos2[2]),10);
        //     drawSphere(vec3(pos3[0],pos3[1],pos3[2]),10);
      
     

   if(theta>6.28) {
      theta=0;
   }
     
   
      
 
  } 
};

int main(int argc, char** argv) {
  Triangle viewer;
  viewer.run();
  return 0;
}

