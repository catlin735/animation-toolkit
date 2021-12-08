#include "atkui/framework.h"
#include "atk/toolkit.h"
#include "atkui/skeleton_drawer.h"
#include <stdio.h>
#include <string.h>

using namespace atk;
using namespace atkui;
using namespace glm;

class Unique : public atkui::Framework
{
public:
  Unique() : atkui::Framework(atkui::Perspective) {}
  virtual ~Unique() {}

  void loadMotion1(const std::string &filename)
  {
    BVHReader reader;
    reader.load(filename, skeleton_, motion1_);
  }

  void loadMotion2(const std::string &filename)
  {
    BVHReader reader;
    reader.load(filename, skeleton_, motion2_);
  }

  void loadMotion3(const std::string &filename)
  {
    BVHReader reader;
    reader.load(filename, skeleton_, motion3_);
  }

  void crossfade(int numBlendFrames)
  {
    assert(motion1_.getNumKeys() > 0);
    assert(motion2_.getNumKeys() > 0);
    assert(numBlendFrames > 0);
    assert(numBlendFrames <= motion1_.getNumKeys());
    assert(numBlendFrames <= motion2_.getNumKeys());
    blend_.setFramerate(motion1_.getFramerate());
    int start1 = motion1_.getNumKeys() - numBlendFrames-1;
    int start2 = 0;

     
    Transform t1;
    vec3 pos=motion1_.getKey(start1).rootPos;
    glm::quat rotation=motion1_.getKey(start1).jointRots[0];

		for (int i = 0; i < motion2_.getNumKeys(); i++) {
			Pose pose = motion2_.getKey(i);
			Transform tDesired(rotation, pos);
			Transform tOrig(pose.jointRots[0], pose.rootPos);
		
			if (i == 0) {
				t1 = Transform::Translate(-1.0f*pose.rootPos);
			}
			Transform correct = tDesired * t1 * tOrig;
			pose.rootPos = correct.t();
			pose.jointRots[0] = correct.r();
			motion2_.editKey(i,pose);
		} 
 

	


  
    for(int i=0;i<start1-1;i++) {
      blend_.appendKey(motion1_.getKey(i));
    } 
    float alpha=0;
    double increment=0.25;
    while(alpha<1) {
      blend_.appendKey(Pose::Lerp(motion1_.getKey(start1),motion2_.getKey(start2),alpha));
      alpha+=increment;
      start1++;
      start2++;
    }
  

    for(int i=numBlendFrames;i<motion2_.getNumKeys();i++) {
      blend_.appendKey(motion2_.getKey(i));
    } 


    // TODO: Your code here */
  }

  void crossfadeAgain(int numBlendFrames)
  {
    assert(blend_.getNumKeys() > 0);
    assert(motion3_.getNumKeys() > 0);
    assert(numBlendFrames > 0);
    assert(numBlendFrames <= blend_.getNumKeys());
    assert(numBlendFrames <= motion3_.getNumKeys());
    blend2_.setFramerate(blend_.getFramerate());
    int start1 = blend_.getNumKeys() - numBlendFrames-1;
    int start2 = 0;

     
    Transform t1;
    vec3 pos=blend_.getKey(start1).rootPos;
    glm::quat rotation=blend_.getKey(start1).jointRots[0];

		for (int i = 0; i < motion3_.getNumKeys(); i++) {
			Pose pose = motion3_.getKey(i);
			Transform tDesired(rotation, pos);
			Transform tOrig(pose.jointRots[0], pose.rootPos);
		
			if (i == 0) {
				t1 = Transform::Translate(-1.0f*pose.rootPos);
			}
			Transform correct = tDesired * t1 * tOrig;
			pose.rootPos = correct.t();
			pose.jointRots[0] = correct.r();
			motion3_.editKey(i,pose);
		} 
 

	


  
    for(int i=0;i<start1-1;i++) {
      blend2_.appendKey(blend_.getKey(i));
    } 
    float alpha=0;
    double increment=0.25;
    while(alpha<1) {
      blend2_.appendKey(Pose::Lerp(blend_.getKey(start1),motion3_.getKey(start2),alpha));
      alpha+=increment;
      start1++;
      start2++;
    }
  

    for(int i=numBlendFrames;i<motion3_.getNumKeys();i++) {
      blend2_.appendKey(motion3_.getKey(i));
    } 

  }

  void save(const std::string &filename)
  {
    BVHWriter writer;
    writer.save(filename, skeleton_, blend_);
  }

  void scene()
  {
    blend2_.update(skeleton_, elapsedTime());
    drawer_.draw(skeleton_, *this);
  }

private:
  Skeleton skeleton_;
  SkeletonDrawer drawer_;
  Motion motion1_;
  Motion motion2_;
  Motion motion3_;
  Motion blend_;
  Motion blend2_;
};

std::string PruneName(const std::string &name)
{
  int idx1 = name.find_last_of("/");
  int idx2 = name.find_last_of(".");
  return name.substr(idx1 + 1, idx2 - idx1 - 1);
}

int main(int argc, char **argv)
{
  std::string motion1 = "../motions/Beta/walking.bvh";
  std::string motion2 = "../motions/Beta/jump.bvh";
  std::string motion3 ="../motions/Beta/back_flip_to_uppercut.bvh";

  int numFrames = 10;


  Unique viewer;
  viewer.loadMotion1(motion1);
  viewer.loadMotion2(motion2);
  viewer.loadMotion3(motion3);
  viewer.crossfade(numFrames);
  viewer.crossfadeAgain(numFrames);
  std::string saveName = "blend-" + PruneName(motion1) + PruneName(motion2);
  saveName += "-" + std::to_string(numFrames) + ".bvh";
  viewer.save(saveName);

  viewer.run();
  return 0;
}

