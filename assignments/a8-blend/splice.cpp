#include "atk/toolkit.h"
#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include <algorithm>
#include <string>

using namespace atk;
using namespace atkui;
using namespace glm;

class ASplice : public atkui::Framework
{
public:
   ASplice() : atkui::Framework(atkui::Perspective) {}
   virtual ~ASplice() {}

   void setup()
   {
      _alpha = 0;

      BVHReader reader;
      reader.load("../motions/Beta/walking.bvh", _skeleton, _lower);
      reader.load("../motions/Beta/gangnam_style.bvh", _skeleton, _upper);
      _splice = spliceUpperBody(_lower, _upper, _alpha);
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

   void scene()
   {  
      _splice.update(_skeleton, elapsedTime() * 0.5);
      SkeletonDrawer drawer;
      drawer.draw(_skeleton, *this);
      drawText("alpha: "+std::to_string(_alpha), 10, 15);
   }

   

   void keyUp(int key, int mods) 
   {
      if (key == GLFW_KEY_UP)
      {
         _alpha = std::min(_alpha+0.05, 1.0);
         _splice = spliceUpperBody(_lower, _upper, _alpha);
      }
      else if (key == GLFW_KEY_DOWN)
      {
         _alpha = std::max(_alpha-0.05, 0.0);
         _splice = spliceUpperBody(_lower, _upper, _alpha);
      }
   }

   Skeleton _skeleton;
   Motion _upper;
   Motion _lower;
   Motion _splice;
   float _alpha;
};

int main(int argc, char** argv)
{
   ASplice viewer;
   viewer.run();
   return 0;
}

