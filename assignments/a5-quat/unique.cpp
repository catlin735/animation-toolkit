#include "atkui/framework.h"
#include "atk/toolkit.h"
using namespace atk;
using glm::vec3;

class Unique : public atkui::Framework {
public:
   Unique() : atkui::Framework(atkui::Perspective) {}
   virtual ~Unique() {}
   float theta;
   float thetaRate;

   virtual void setup() {
      lookAt(vec3(200), vec3(0));
      theta = 0.0f;
      thetaRate = 0.1;
      
      Joint* root  = new Joint("root");
      root->setLocalTranslation(vec3(0,0,0)); 
      _tentacle.addJoint(root);

      float angle=M_PI/8;
      Joint* joint1  = new Joint("joint1");
      joint1->setLocalTranslation(vec3(0,50,0));
      
      _tentacle.addJoint(joint1, root);

      // todo: add more joints
      Joint* joint2  = new Joint("joint2");
      joint2->setLocalTranslation(vec3(0,50,0));
      joint2->setLocalRotation(glm::angleAxis(angle, vec3(0, 0, 1)));
      _tentacle.addJoint(joint2, joint1);

       Joint* joint3  = new Joint("joint3");
      joint3->setLocalTranslation(vec3(0,50,0));
      joint3->setLocalRotation(glm::angleAxis(angle, vec3(0, 0, 1)));
      _tentacle.addJoint(joint3, joint2);

      Joint* joint4  = new Joint("joint4");
      joint4->setLocalTranslation(vec3(50,0,0));
      joint4->setLocalRotation(glm::angleAxis(angle, vec3(0, 0, 1)));
      _tentacle.addJoint(joint4, joint3);

       Joint* joint5  = new Joint("joint5");
      joint5->setLocalTranslation(vec3(50,0,0));
      joint5->setLocalRotation(glm::angleAxis(angle, vec3(0, 0, 1)));
      _tentacle.addJoint(joint5, joint4);
      
      Joint* joint6  = new Joint("joint6");
      joint6->setLocalTranslation(vec3(50,0,0));
      joint6->setLocalRotation(glm::angleAxis(angle, vec3(0, 0, 1)));
      _tentacle.addJoint(joint6, joint5);

      Joint* joint7  = new Joint("joint7");
      joint7->setLocalTranslation(vec3(50,0,0));
      joint4->setLocalRotation(glm::angleAxis(angle, vec3(0, 0, 1)));
      _tentacle.addJoint(joint7, joint6);

      Joint* joint8  = new Joint("joint8");
      joint7->setLocalTranslation(vec3(50,0,0));
      _tentacle.addJoint(joint8, joint7);

      _tentacle.fk(); // compute local2global transforms
   }

   virtual void scene()
   {
      // todo animate joints
      // hint: use glm::angleAxis(...) to compute quaternions for each joint
     // computes local2global transforms
      setColor(vec3(0,1,0));

     // theta += thetaRate * sin(elapsedTime());
      theta += thetaRate;
      Joint* wave=_tentacle.getByName("joint4");
      wave->setLocalRotation(glm::angleAxis(theta, vec3(0, 0, 1)));

       _tentacle.fk();

      // todo: loop over all joints and draw
      for(int i=1;i<_tentacle.getNumJoints();i++) {
         Joint* parent=_tentacle.getByID(i)->getParent();
         Joint* child = _tentacle.getByID(i);
         vec3 globalParentPos = parent->getGlobalTranslation();
         vec3 globalPos = child->getGlobalTranslation();
         drawCube(globalPos, vec3(20,20,20));
      }
   }

protected:
   Skeleton _tentacle;
};

int main(int argc, char** argv)
{
   Unique viewer;
   viewer.run();
} 
