#include "atkui/framework.h"
#include "atk/toolkit.h"
using namespace atk;
using glm::vec3;

class Tentacle : public atkui::Framework {
public:
   Tentacle() : atkui::Framework(atkui::Perspective) {}
   virtual ~Tentacle() {}
   float theta;
   double thetaRate;

   virtual void setup() {
      lookAt(vec3(200), vec3(0));
      theta = 0.0;
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
      joint4->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint4, joint3);

       Joint* joint5  = new Joint("joint5");
      joint5->setLocalTranslation(vec3(0,50,0));
      _tentacle.addJoint(joint5, joint4);

      _tentacle.fk(); // compute local2global transforms
   }

   virtual void scene()
   {
      // todo animate joints
      // hint: use glm::angleAxis(...) to compute quaternions for each joint
      _tentacle.fk(); // computes local2global transforms
      setColor(vec3(0,1,0));

      theta += thetaRate * sin(elapsedTime());
      float angle=M_PI*sin(theta);

      // todo: loop over all joints and draw
      for(int i=1;i<_tentacle.getNumJoints();i++) {
         Joint* parent=_tentacle.getByID(i)->getParent();
         float offset=i/M_PI;
         glm::quat Rot = glm::angleAxis(angle*0.1f+offset*0.1f, vec3(0,0,1));
         parent->setLocalRotation(Rot);
         Joint* child = _tentacle.getByID(i);
         vec3 globalParentPos = parent->getGlobalTranslation();
         vec3 globalPos = child->getGlobalTranslation();
         drawEllipsoid(globalParentPos, globalPos, 5);
         //std::cout<<globalPos;
      }
      /* Joint* parent = _tentacle.getByID(0);
      Joint* child = _tentacle.getByID(1);
      vec3 globalParentPos = parent->getGlobalTranslation();
      vec3 globalPos = child->getGlobalTranslation();
      drawEllipsoid(globalParentPos, globalPos, 5); */
   }

protected:
   Skeleton _tentacle;
};

int main(int argc, char** argv)
{
   Tentacle viewer;
   viewer.run();
} 

