#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include <algorithm>
#include <string>

using namespace glm;
using namespace atk;
using namespace atkui;

class Unique : public atkui::Framework {
public:
   Unique() : atkui::Framework(atkui::Perspective) {}
   virtual ~Unique() {}

   void setup() {
      BVHReader reader;
      reader.load("../motions/Beta/walking.bvh", _skeleton, _original);
      reader.load("../motions/Beta/walking.bvh", _skeleton, _lower);
      reader.load("../motions/Beta/samba_dancing.bvh", _skeleton, _upper);
      _splice = spliceUpperBody(_lower, _upper, 1);

      _zombieFreeze = ComputeArmFreeze(_original);
      _zombieOffset = ComputeArmOffset(_original);
   }

    Motion spliceUpperBody(const Motion& lower, const Motion& upper, float alpha)
   {
      Motion result;
      result.setFramerate(lower.getFramerate());
      
      Joint* spine=_skeleton.getByID(2);
      
      
      // todo: your code here
      for(int i=0;i<lower.getNumKeys();i++) {
      
         Pose currLower=lower.getKey(i);
         Pose currUpper=upper.getKey(i);
         result.appendKey(currLower);
      }

     for(int i=0;i<result.getNumKeys();i++) {
         Pose currLower=lower.getKey(i);
         Pose currUpper=upper.getKey(i);
         Pose newPose=lower.getKey(i);
         /* for(int i=0;i<newPose.jointRots.size();i++) {
           newPose.jointRots[i]=glm::slerp(currLower.jointRots[i], currUpper.jointRots[i],alpha);
         } */
        for(int j=2;j<=55;j++) {
           double id=j;
           /*  double id=spine->getChildAt(i)->getID();
            std::cout<<spine->getNumChildren(); */
           newPose.jointRots[id]=glm::slerp(currLower.jointRots[id], currUpper.jointRots[id],alpha);
            
         } 
         result.editKey(i,newPose);
      } 
    
      return result;
   }

   Motion ComputeArmOffset(const Motion& motion) {
      Joint* leftArm = _skeleton.getByName("Beta:LeftArm");
      Joint* rightArm = _skeleton.getByName("Beta:RightArm");
     
      Joint* leftElbow = _skeleton.getByName("Beta:LeftForeArm");
      Joint* rightElbow = _skeleton.getByName("Beta:RightForeArm");


      quat leftLocalRot = eulerAngleRO(XYZ, radians(vec3(-53, -88, -33)));
      quat rightLocalRot = eulerAngleRO(XYZ, radians(vec3(14, 88, -33)));
      quat elbowLocalRot = eulerAngleRO(XYZ, radians(vec3(0, 23, 0)));

      quat leftOffset=leftLocalRot*inverse(leftArm->getLocalRotation());
      quat rightOffset=rightLocalRot*inverse(rightArm->getLocalRotation());


      Motion result;
      result.setFramerate(motion.getFramerate());
      // todo: your code here
       for(int i=0;i<motion.getNumKeys();i++) {
          result.appendKey(motion.getKey(i));
      }
      for(int i=0;i<result.getNumKeys();i++) {
         Pose prevPose=result.getKey(i);
         Pose newPose=result.getKey(i);
         newPose.jointRots[leftArm->getID()]=prevPose.jointRots[leftArm->getID()]*leftOffset;
         newPose.jointRots[rightArm->getID()]=prevPose.jointRots[rightArm->getID()]*rightOffset;
         newPose.jointRots[leftElbow->getID()]=prevPose.jointRots[leftElbow->getID()]*elbowLocalRot;
         newPose.jointRots[rightElbow->getID()]=prevPose.jointRots[rightElbow->getID()]*elbowLocalRot;
         result.editKey(i,newPose);
      }

      return result;
   }

   Motion ComputeArmFreeze(const Motion& motion) {
      quat leftRot = eulerAngleRO(XYZ, radians(vec3(-53, -88, -33)));
      quat rightRot = eulerAngleRO(XYZ, radians(vec3(14, 88, -33)));
      quat elbowRot = eulerAngleRO(XYZ, radians(vec3(0, 23, 0)));

      Joint* leftArm = _skeleton.getByName("Beta:LeftArm");
      Joint* rightArm = _skeleton.getByName("Beta:RightArm");

      Joint* leftElbow = _skeleton.getByName("Beta:LeftForeArm");
      Joint* rightElbow = _skeleton.getByName("Beta:RightForeArm");
      leftArm->setLocalRotation(leftRot);
      Motion result;
      result.setFramerate(motion.getFramerate());

      for(int i=0;i<motion.getNumKeys();i++) {
         result.appendKey(motion.getKey(i));
      }


      for(int i=0;i<result.getNumKeys();i++) {
         Pose newPose=result.getKey(i);
         newPose.jointRots[leftArm->getID()]=leftRot;
         newPose.jointRots[rightArm->getID()]=rightRot;
         newPose.jointRots[leftElbow->getID()]=elbowRot;
         newPose.jointRots[rightElbow->getID()]=elbowRot;
         result.editKey(i,newPose);
      }
      // todo: your code here
     

      return result;
   }

   void update() {
      double t =  elapsedTime() * 0.5;
      if (_currentMotion == 1) {
         _zombieFreeze.update(_skeleton, t);
         drawText("Freeze", 10, 15);

      } else if (_currentMotion == 2) {
         _zombieOffset.update(_skeleton, t);
         drawText("Offset", 10, 15);

      } else if(_currentMotion == 3) {
         _splice.update(_skeleton, t);
         drawText("Samba walk", 10, 15);
      }else {
         _original.update(_skeleton, t);
         drawText("Joint edit type: none", 10, 15);
      }
   }

   void scene() {  
      update();
      _drawer.draw(_skeleton, *this);
   }

   void keyUp(int key, int mods) {
      if (key == '1') {
          _currentMotion = 1;
      } else if (key == '2') {
          _currentMotion = 2;
      } else if (key == '0') {
          _currentMotion = 0;
      } else if (key=='3') {
         _currentMotion=3;
      }
   }

   SkeletonDrawer _drawer;
   Skeleton _skeleton;
   Motion _original;
   Motion _zombieFreeze;
   Motion _zombieOffset;
   Motion _lower;
   Motion _upper;
   Motion _splice;
   int _currentMotion = 0;
};

int main(int argc, char** argv) {
   Unique viewer;
   viewer.run();
   return 0;
}

