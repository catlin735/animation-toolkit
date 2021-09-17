#include "atkui/framework.h"

using namespace glm;
class Eyes : public atkui::Framework
{
  public:
    Eyes() : atkui::Framework(atkui::Orthographic) {
    }

     virtual void setup() {
      
  }

    virtual void scene() {
      
      setColor(vec3(1,0,0));

    
      double x = width() * 0.5;
      double y = height() * 0.5;
      double radius = 50; 
      drawSphere(vec3(x-100+20*sin(elapsedTime()),y,1), radius);
       drawSphere(vec3(x+100+20*sin(elapsedTime()),y,1), radius);

      setColor(vec3(1,1,1));
      drawSphere(vec3(x-100,y,-100), radius+100);
      drawSphere(vec3(x+100,y,-100), radius+100);


      
    }
};

int main(int argc, char** argv) {
  Eyes viewer;
  viewer.run();
  return 0;
}
