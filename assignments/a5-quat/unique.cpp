#include "atkui/framework.h"
#include <cmath>
#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"
#include "atkmath/constants.h"

using atkmath::Quaternion;
using atkmath::Matrix3;
using atkmath::Vector3;
using namespace glm;
using glm::vec3;

class Unique : public atkui::Framework {
   public:
   Unique() : atkui::Framework(atkui::Orthographic) {
   }

  
   private:
      Vector3 centerPos;
      Vector3 particle;
      Vector3 direction;
      float speed=0.25;


   virtual void setup() {
      centerPos=Vector3(width()/2,height()/2,0);
      particle=Vector3(centerPos[0]+5*cos(M_PI_4),centerPos[1]+5*sin(M_PI_4),0);
      direction=centerPos-particle;
   
   }

   virtual void scene() {
      direction=centerPos-particle;
      Quaternion q;
      q.fromAxisAngle(Vector3(0,0,1), M_PI/4);
      direction=q*direction;
      float distance= speed * 10*sin(elapsedTime());
      particle+=(direction/sqrt(direction[0]*direction[0] +direction[1]*direction[1]))*distance;

      setColor(vec3(1,1,1));
      drawSphere(vec3(particle[0],particle[1],particle[2]),10);

     
  }
};

int main(int argc, char** argv) {
   Unique viewer;
   viewer.run();
   return 0;
}

