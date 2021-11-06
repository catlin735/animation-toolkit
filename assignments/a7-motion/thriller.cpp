#include <random>
#include <functional>
#include "atkui/framework.h"
#include "atk/toolkit.h"
#include "agl/renderer.h"
#include "devil.h"

using namespace atk;
using namespace glm;

class Thriller : public atkui::Framework
{
public:
   Thriller() : atkui::Framework(atkui::Perspective) {}
   virtual ~Thriller() {}

   virtual void setup() {
      BVHReader reader;
      reader.load("../motions/Warrok/WarrokThriller.bvh", _skeleton, _motion);

      int count=0;
       for(int r=0;r<4;r++) {
            for(int c=0;c<3;c++) {
               vec3 position = vec3(r*60+agl::random(-20,20),1,c*60+agl::random(-20,20));
               float size=agl::random();
               vec3 color=vec3(0.2,0.8,0.2)+vec3(agl::random(-0.2,1.2),agl::random(-0.2,0.2),agl::random(-0.2,0.2));
               array[count]=new Devil(position, color, size);
               count++;
            }
         }

     
      //vec3 position = vec3(0);
     // vec3 color = vec3(1,0,0);
      //float size = 1.0f;
     // _devil = Devil(position, color, size);
   }

   virtual void scene() {
      if (!_paused) _motion.update(_skeleton, elapsedTime());
      for(int i=0;i<12;i++) {
         array[i]->draw(_skeleton, *this);
      }
   }

   virtual void keyUp(int key, int mods) {
      if (key == 'P') _paused = !_paused;
   }

protected:
   Motion _motion;
   Skeleton _skeleton;
   bool _paused = false;
   Devil _devil;
   Devil* array[12] = {};
};

int main(int argc, char** argv) {
   Thriller viewer;
   viewer.run();
}

