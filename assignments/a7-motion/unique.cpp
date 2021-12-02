#include <iostream>
#include "atkui/framework.h"
#include "atk/toolkit.h"
using namespace atk;
using namespace glm;



class Unique : public atkui::Framework
{
public:
   Unique() : atkui::Framework(atkui::Perspective) {
   }

   void setup() {
      BVHReader reader;
      //"../motions/Beta/jump.bvh"
      reader.load("../motions/Beta/idle.bvh", skeleton, motion);
      motion.update(skeleton, 0);

     
   }

   void scene() {
      Joint* leftFoot = skeleton.getByID(58);
      leftFoot->setLocalRotation(glm::angleAxis(-0.25f*sin(elapsedTime()), vec3(0,0,1))); 
      skeleton.fk();
      setColor(vec3(0,0,0.8));
      for (int i = 0; i < skeleton.getNumJoints(); i++) {
         Joint* joint = skeleton.getByID(i);
         if (joint->getParent() == 0) continue;

         vec3 p1 = joint->getGlobalTranslation();
         vec3 p2 = joint->getParent()->getGlobalTranslation();
         drawEllipsoid(p1, p2, 5);
      }

    
   }

  

private:
   Skeleton skeleton;
   Motion motion;
   float timeScale = 1.0f;
   int currentFrame = 0; 
   float time = 0;
};


int main(int argc, char *argv[]) {
   Unique viewer;
   
  
   viewer.run();
}
