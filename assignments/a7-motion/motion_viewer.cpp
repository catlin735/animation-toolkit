#include <iostream>
#include "atkui/framework.h"
#include "atk/toolkit.h"

using namespace glm;
using namespace atk;

class MotionViewer : public atkui::Framework
{
public:
   MotionViewer() : atkui::Framework(atkui::Perspective) {
   }

   void setup() {
      BVHReader reader;
      //"../motions/Beta/jump.bvh"
      reader.load(bvh, skeleton, motion);
      motion.update(skeleton, 0);
   }

   void scene() {

      if(!paused) {
         time += dt()*pow(2,timeScale);
         motion.update(skeleton, time);
         currentFrame=motion.getKeyID(time);
      }
      
      setColor(vec3(0,0,0.8));
      for (int i = 0; i < skeleton.getNumJoints(); i++) {
         Joint* joint = skeleton.getByID(i);
         if (joint->getParent() == 0) continue;

         vec3 p1 = joint->getGlobalTranslation();
         vec3 p2 = joint->getParent()->getGlobalTranslation();
         drawEllipsoid(p1, p2, 5);
      }

      drawText(paused? "Paused" : "Playing", 10, 15);
      drawText("Current frame: "+std::to_string(currentFrame), 10, 35);
      drawText("Time scale: "+std::to_string(timeScale), 10, 55);
   }

   virtual void keyUp(int key, int mods) {
      if(key=='P') {
         paused=!paused;
      }
      if(key=='0') {
         currentFrame=0;
         time=0;
      }
      if(key=='.') {
         if(paused) {
            currentFrame++;
   
            if(currentFrame<0) {
               currentFrame=motion.getNumKeys()-1+currentFrame;
            }
            if(currentFrame>motion.getNumKeys()-1) {
               currentFrame=0;
            }
            skeleton.setPose(motion.getKey(currentFrame));
         }
      }

       if(key==',') {
         if(paused) {
            currentFrame=currentFrame-1;
             if(currentFrame<0) {
               currentFrame=motion.getNumKeys()-1+currentFrame;
            }
            if(currentFrame>motion.getNumKeys()-1) {
               currentFrame=0;
            }
            skeleton.setPose(motion.getKey(currentFrame));
         }
      }

      if(key==']') {
         timeScale++;
      }

       if(key=='[') {
         timeScale--;
      }
   }
   void setBVH(std::string file) {
      bvh=file;
   }

private:
   Skeleton skeleton;
   Motion motion;
   std::string bvh;
   float timeScale = 1.0f;
   int currentFrame = 0; 
   bool paused = false;
   float time = 0;
};


int main(int argc, char *argv[]) {
   MotionViewer viewer;
   if(argc>1) {
       viewer.setBVH(argv[1]);
   }
   else {
      viewer.setBVH("../motions/Beta/jump.bvh");
   }
  
   viewer.run();
}
