#include "atkui/framework.h"
#include <math.h>  

using namespace glm;

class Look : public atkui::Framework {
 public:
  Look() : atkui::Framework(atkui::Orthographic) {
  }

   private:
  int _mouseX;
  int _mouseY;
  double x;
  double y;
  double radius;
 
  virtual void setup() {
    _mouseX = width() * 0.5;
    _mouseY = height() * 0.5;
    x = width() * 0.5;
    y = height() * 0.5;
    radius=50;
  }

  virtual void scene() {

    if(mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
      mouseMove(mousePosition()[0],mousePosition()[1]);
      

    }
    vec3 target = vec3(_mouseX, _mouseY, 0);
    setColor(vec3(1,0,0));
    drawSphere(target, 5);

      setColor(vec3(1,1,1));
      drawSphere(vec3(x-100,y,-100), radius+120);
      drawSphere(vec3(x+100,y,-100), radius+120);

     setColor(vec3(1,0,0));


    float px=radius*cos(atan2(_mouseY-y,_mouseX-x-100));
    float py=radius*sin(atan2(_mouseY-y,_mouseX-x-100));

      drawSphere(vec3(x+100+px,y+py,1), radius-20);
      drawSphere(vec3(x-100+px,y+py,1), radius-20);

    
  }

  void mouseMove(int x, int y) {
    _mouseX = x;
    _mouseY = height() - y;
  }


};

int main(int argc, char** argv) {
  Look viewer;
  viewer.run();
  return 0;
}
