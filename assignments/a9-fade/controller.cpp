#include "atkui/framework.h"
#include "atkui/skeleton_drawer.h"
#include "atk/toolkit.h"
#include <iostream>
#include <cmath>

using namespace glm;
using namespace std;
using namespace atk;

class WASDSimple : public atkui::Framework
{
public:
  WASDSimple() : atkui::Framework(atkui::Perspective) {}

  virtual void setup()
  {
    BVHReader reader;
    reader.load("../motions/Beta/walking.bvh", _skeleton, _walk);
    _drawer.showAxes = true;
  }

  virtual void scene()
  {
    update();
    _drawer.draw(_skeleton, *this);

    // draw heading
    vec3 p = _skeleton.getRoot()->getGlobalTranslation();
    p[1] = 10; // set height close above the floor

    setColor(vec3(0, 1, 1));
    push();
    translate(p);
    rotate(_heading, vec3(0, 1, 0));
    translate(vec3(0,0,25));
    scale(vec3(10, 10, 50));
    drawCylinder(vec3(0), 1.0f);
    pop();
  }

  virtual void update()
  {
  
    _walk.update(_skeleton, elapsedTime());
  
    // TODO: Your code here
  

   
  Pose pose = _walk.getKey(_walk.getKeyID(elapsedTime()));
 // pose.rootPos=_walk.getKey(0).rootPos;
  pose.rootPos=_walk.getKey(0).rootPos+vec3(sin(_heading),0,cos(_heading))+vec3(0, 0, 30);
   pose.jointRots[0]=glm::angleAxis(_heading,vec3(0,1,0));
  _walk.editKey(_walk.getKeyID(elapsedTime()),pose); 

    // TODO: Override the default camera to follow the character
  vec3 headPos=_skeleton.getByID(6)->getGlobalTranslation();
  vec3 globalLookPos=headPos;
  vec3 globalCameraPos=headPos-vec3(300*sin(_heading),pose.rootPos[1],300*cos(_heading)); 
  
  lookAt(globalCameraPos, globalLookPos, glm::vec3(0, 1, 0));
  
    // update heading when key is down
    if (keyIsDown('D')) _heading -= 0.05;
    if (keyIsDown('A')) _heading += 0.05;
	
  }

protected:
  float _heading;

  Motion _walk;
  Skeleton _skeleton;
  atkui::SkeletonDrawer _drawer;
};

int main(int argc, char **argv)
{
  WASDSimple viewer;
  viewer.run();
}
