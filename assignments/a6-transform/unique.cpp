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
      theta = M_PI/3;
      thetaRate = 0.1;
      
      Joint* root  = new Joint("root");
      root->setLocalTranslation(vec3(0,0,0));
      _tentacle.addJoint(root);

      Joint* joint1  = new Joint("joint1");
      joint1->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint1, root);

      // todo: add more joints
      Joint* joint2  = new Joint("joint2");
      joint2->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint2, joint1);

       Joint* joint3  = new Joint("joint3");
      joint3->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint3, joint2);

      Joint* joint4  = new Joint("joint4");
      joint4->setLocalTranslation(vec3(10,0,0));
      float angle4=1.0f*M_PI/3;
      joint4->setLocalRotation(glm::angleAxis(angle4, vec3(0, 0, 1)));
      _tentacle.addJoint(joint4, joint2);

       Joint* joint5  = new Joint("joint5");
      joint5->setLocalTranslation(vec3(50,0,0));
      _tentacle.addJoint(joint5, joint4);
      
      Joint* joint6  = new Joint("joint6");
      joint6->setLocalTranslation(vec3(-10,0,0));
      float angle5=-1.0f*M_PI/3;
      joint6->setLocalRotation(glm::angleAxis(angle5, vec3(0, 0, 1)));
      _tentacle.addJoint(joint6, joint2);

       Joint* joint7  = new Joint("joint7");
      joint7->setLocalTranslation(vec3(-50,0,0));
      _tentacle.addJoint(joint7, joint6);

      _tentacle.fk(); // compute local2global transforms
   }

   virtual void scene()
   {
      // todo animate joints
      // hint: use glm::angleAxis(...) to compute quaternions for each joint
      _tentacle.fk(); // computes local2global transforms
      setColor(vec3(0,1,0));

      theta += thetaRate * sin(elapsedTime());
    
      Joint* wave=_tentacle.getByName("joint4");
      wave->setLocalRotation(glm::angleAxis(theta, vec3(0, 0, 1)));

      

      // todo: loop over all joints and draw
      for(int i=1;i<_tentacle.getNumJoints();i++) {
         Joint* parent=_tentacle.getByID(i)->getParent();
         Joint* child = _tentacle.getByID(i);
         vec3 globalParentPos = parent->getGlobalTranslation();
         vec3 globalPos = child->getGlobalTranslation();
         drawEllipsoid(globalParentPos, globalPos, 5);
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
