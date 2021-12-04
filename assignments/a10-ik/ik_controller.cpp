#include "ik_controller.h"
#include <cmath>
#include <iostream>

using namespace atk;
using namespace glm;
using namespace std;

bool IKController::solveIKAnalytic(Skeleton& skeleton, 
    int jointid, const vec3& goalPos, float epsilon) {
  if (jointid == -1) return true;

  Joint* ankle = skeleton.getByID(jointid);
  if (!ankle->getParent()) {
    std::cout << "Warning: solveIKAnalytic() needs joint "
      "with parent and grandparent\n";
    return false;
  }

  Joint* knee = ankle->getParent();
  if (!knee->getParent()) {
    std::cout << "Warning: solveIKAnalytic() needs joint "
      "with parent and grandparent\n";
    return false;
  }

  Joint* hip = knee->getParent();

  // TODO: Your code here
  return true;
}

bool IKController::solveIKCCD(Skeleton& skeleton, int jointid, 
    const vec3& goalPos, const std::vector<Joint*>& chain, 
    float threshold, int maxIters, float nudgeFactor) {
  // There are no joints in the IK chain for manipulation
  if (chain.size() == 0) return true;

  // TODO: Your code here
 vec3 d=skeleton.getByID(jointid)->getGlobalTranslation();

  /* vec3 p2=skeleton.getByID(jointid)->getParent()->getGlobalTranslation();
  vec3 p1=skeleton.getByID(jointid)->getParent()->getParent()->getGlobalTranslation();  */
 
  /* vec3 r=p3-p1;
  vec3 e=goalPos-p3;
  Joint* head=skeleton.getByID(jointid)->getParent();
  quat curr=head->getGlobalRotation();
  float phi=atan2(glm::length(glm::cross(r,e)),dot(r,e)+dot(r,r));
  vec3 axis=glm::cross(r,e)/glm::length(glm::cross(r,e));
  Transform tDesired(glm::angleAxis(phi, axis)*curr, head->getGlobalTranslation());
  Transform toLocal=head->getLocal2Global().inverse()*tDesired;
  head->setLocalRotation(toLocal.r()); */
 
 /*  
  vec3 r1=p3-p1;
  vec3 e=goalPos-p3;
  float phi1=atan2(glm::length(glm::cross(r1,e)),dot(r1,e)+dot(r1,r1));
  vec3 axis1=glm::cross(r1,e)/glm::length(glm::cross(r1,e)); */
  
  

   
  float iters=0;
  float distanceFromGoal=glm::length(goalPos-d);
  while(distanceFromGoal>threshold && iters<maxIters) {
    for(int i=0;i<chain.size();i++) {
      Joint* head=skeleton.getByID(jointid);
      vec3 globalHeadPos = head->getGlobalTranslation();
      vec3 globalForward = head->getGlobalRotation() * vec3(0,0,1);
      vec3 p1=globalHeadPos;
      vec3 p3=globalHeadPos + globalForward;
      vec3 r=p3-p1;
      vec3 e=goalPos-p3;
      quat curr=head->getGlobalRotation();
      float phi=atan2(glm::length(glm::cross(r,e)),dot(r,e)+dot(r,r));
      vec3 axis=glm::cross(r,e)/glm::length(glm::cross(r,e));
      Transform tDesired(glm::angleAxis(phi, axis)*curr, head->getGlobalTranslation());
      Transform toLocal=head->getLocal2Global().inverse()*tDesired;
      head->setLocalRotation(toLocal.r());
      head->fk();
    } 
  } 
    
  return false;
}
