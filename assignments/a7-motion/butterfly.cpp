#include <iostream>
#include "atkui/framework.h"
#include "atk/toolkit.h"

using namespace glm;
using namespace atk;

class Butterfly : public atkui::Framework
{
public:
   Butterfly() : atkui::Framework(atkui::Perspective) {
   }

   void setup() {
      Joint* body = new Joint("Body");
      body->setLocalTranslation(vec3(1,2,1)*100.0f);
      body->setLocalRotation(glm::angleAxis(glm::radians<float>(45.0f), vec3(0,1,0)));
      skeleton.addJoint(body);

      Joint* lwing = new Joint("LWing");
      lwing->setLocalTranslation(vec3(0.1,0,0.1)*100.0f);
      skeleton.addJoint(lwing, body);

      Joint* lwing2=new Joint("LWing2");
      lwing2->setLocalTranslation(vec3(0.1,0,0.1)*100.0f);
      skeleton.addJoint(lwing2, body);

      Joint* rwing = new Joint("RWing");
      rwing->setLocalTranslation(vec3(-0.1,0,0)*100.0f);
      skeleton.addJoint(rwing, body);

      Joint* rwing2 = new Joint("RWing2");
      rwing->setLocalTranslation(vec3(-0.1,0,0)*100.0f);
      skeleton.addJoint(rwing2, body);

      skeleton.fk();
   }

   void scene() {
      Joint* body = skeleton.getByName("Body");
      double x=20*cos(elapsedTime());
      double y=20*sin(elapsedTime());
      
      body->setLocalTranslation(glm::vec3(x,250,y));
      Joint* lwing = skeleton.getByName("LWing");
      lwing->setLocalRotation(glm::angleAxis(sin(elapsedTime()), vec3(0,0,1)));
      Joint* lwing2 = skeleton.getByName("LWing2");
      lwing2->setLocalRotation(glm::angleAxis(sin(elapsedTime()), vec3(0,0,1)));

      Joint* rwing = skeleton.getByName("RWing");
      rwing->setLocalRotation(glm::angleAxis(-sin(elapsedTime()), vec3(0,0,1))); 
      Joint* rwing2 = skeleton.getByName("RWing2");
      rwing->setLocalRotation(glm::angleAxis(-sin(elapsedTime()), vec3(0,0,1))); 
      skeleton.fk();
      
      // attach geometry to skeleton 
      Transform B = body->getLocal2Global(); 
      Transform LT = lwing->getLocal2Global(); 
      Transform LT2= lwing2->getLocal2Global(); 
      Transform RT = rwing->getLocal2Global(); 
      Transform RT2 = rwing->getLocal2Global(); 

      // draw body
      Transform bodyGeometry(
         glm::angleAxis(glm::pi<float>()*0.5f, vec3(1,0,0)), // rotation
         vec3(0), vec3(25, 200, 25)); // position, scale
      
     
      

      Transform lwingGeometry(
         eulerAngleRO(XYZ, vec3(0,0,0)),
         vec3(-50,0,40), 
         vec3(80,20,80));
      
      Transform lwing2Geometry(
         eulerAngleRO(XYZ, vec3(0,0,0)),
         vec3(-50,0,-40), 
         vec3(80,20,80));

      Transform rwingGeometry(
         eulerAngleRO(XYZ, vec3(0,0,0)),
         vec3(50,0,40), 
         vec3(80,20,80));
      
      Transform rwing2Geometry(
         eulerAngleRO(XYZ, vec3(0,0,0)),
         vec3(50,0,-40), 
         vec3(80,20,80));
      

    
      push();
        
         transform(B);
         setColor(vec3(1, 1, 1));
         
         drawEllipsoid(vec3(0,-30,0), vec3(0,30,0), 10);
         drawEllipsoid(vec3(40,0,0), vec3(-40,0,0), 10);
         drawEllipsoid(vec3(0,0,100), vec3(0,0,-100), 10);
      pop(); 
     
     
      push();
      setColor(vec3(0.4, 0.4, 0.8));
      transform(B * bodyGeometry);
      drawSphere(vec3(0), 1);
      pop(); 

      setColor(vec3(0.8, 0, 0.0));
      push();
      transform(LT * lwingGeometry);
      drawSphere(vec3(0), 1);
      pop();

      setColor(vec3(0.8, 0, 0.0));
      push();
      transform(LT2 * lwing2Geometry);
      drawSphere(vec3(0), 1);
      pop();

      setColor(vec3(0, 0.8, 0.0));
      push();
      transform(RT * rwingGeometry);
      drawSphere(vec3(0), 1);
      pop();

      setColor(vec3(0, 0.8, 0.0));
      push();
      transform(RT2 * rwing2Geometry);
      drawSphere(vec3(0), 1);
      pop();
   }

private:
   Skeleton skeleton;
   bool axes = false;
};


int main(int argc, char** argv) {
   Butterfly viewer;
   viewer.run();
}
