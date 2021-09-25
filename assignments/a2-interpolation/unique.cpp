#include "atkui/framework.h"
#include <list>
#include <iterator>
using namespace glm;
using namespace std;

class Unique : public atkui::Framework {
 public:
  Unique() : atkui::Framework(atkui::Orthographic) {
  }

 

  struct Curve {

    vec3 B0;
    vec3 B1;
    vec3 B2;
    vec3 B3;
    vec3 B4;
    vec3 color;

  public:
    Curve() {
       
    }

    Curve(vec3 b1, vec3 b2, vec3 b3,vec3 b4, vec3 c) {
        vec3 B0;
        vec3 B1;
        vec3 B2;
        vec3 B3;
        vec3 B4;
        vec3 color;
    }

};

 private:
  Curve init;
  Curve final;
  Curve current;
  float time;
  list<Curve>list;
   int _mouseX;
  int _mouseY;

  void setup() {
   
    init.B0=vec3(width()*agl::random(),height()*agl::random(),1);
    init.B1=vec3(width()*agl::random(),height()*agl::random(),1);
    init.B2=vec3(width()*agl::random(),height()*agl::random(),1);
    init.B3=vec3(width()*agl::random(),height()*agl::random(),1);
    init.B4=vec3(width()*agl::random(),height()*agl::random(),1);
    init.color=vec3(agl::random(),agl::random(),agl::random());

    final.B0=vec3(width()*agl::random(),height()*agl::random(),1);
    final.B1=vec3(width()*agl::random(),height()*agl::random(),1);
    final.B2=vec3(width()*agl::random(),height()*agl::random(),1);
    final.B3=vec3(width()*agl::random(),height()*agl::random(),1);
   final.B4=vec3(width()*agl::random(),height()*agl::random(),1);
    final.color=vec3(agl::random(),agl::random(),agl::random());

    current.color=randColor();
   _mouseX = width() * 0.5;
    _mouseY = height() * 0.5;
    

    
    time=0;
  }

  void scene() {

   if(mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
      mouseMove(mousePosition()[0],mousePosition()[1]);
      
    }
mouseMove(mousePosition()[0],mousePosition()[1]);
    

      if(mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)&&abs(_mouseX-init.B1[0])<=10&&abs(_mouseY-init.B1[1])<=10) {
         vec3 target = vec3(_mouseX, _mouseY, 0);
         init.B1=target;
      }

       if(mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)&&abs(_mouseX-init.B2[0])<=10&&abs(_mouseY-init.B2[1])<=10) {
         vec3 target = vec3(_mouseX, _mouseY, 0);
         init.B2=target;
      }

      if(mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)&&abs(_mouseX-init.B3[0])<=10&&abs(_mouseY-init.B3[1])<=10) {
         vec3 target = vec3(_mouseX, _mouseY, 0);
         init.B3=target;
      }
      if(mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)&&abs(_mouseX-init.B4[0])<=10&&abs(_mouseY-init.B4[1])<=10) {
         vec3 target = vec3(_mouseX, _mouseY, 0);
         init.B4=target;
      }
   
    setColor(vec3(1,0,1));
   drawSphere(init.B1,10);
       setColor(vec3(1,1,1));
    drawSphere(init.B2,10);
      setColor(vec3(1,0,0));
     drawSphere(init.B3,10);
     setColor(vec3(1,1,0));
      drawSphere(init.B4,10);
    

  
  drawCurve(init);

   
  }

  void mouseMove(int x, int y) {
    _mouseX = x;
    _mouseY = height() - y;
  }




  vec3 lerp(vec3 a, vec3 b, float t) {
    
    return a*(1-t)+b*t;
  }


  vec3 castel2(vec3 a, vec3 b, vec3 c, float t) {
    return lerp(lerp(a,b,t),lerp(b,c,t),t);
  }

  vec3 castel3(vec3 a, vec3 b, vec3 c, vec3 d, float t) {

      return lerp(castel2(a,b,c,t),castel2(b,c,d,t),t);
  }

  vec3 castel4(vec3 a, vec3 b, vec3 c, vec3 d, vec3 e, float t) {
     return lerp(castel3(a,b,c,d,t),castel3(b,c,d,e,t),t);
  }

  void drawCurve(Curve curve) {
    setColor(curve.color);
    vec3 prev=curve.B0;
      for(double i=0;i<1;i+=0.01) {
        vec3 newPos=castel4(curve.B0,curve.B1,curve.B2,curve.B3,curve.B4,i);
        drawLine(prev,newPos);
        prev=newPos;
      }
  }

  vec3 randColor() {
    return vec3(agl::random(),agl::random(),agl::random());
}

  void randomCurve(Curve& curve) {

      curve.B0=vec3(width()*agl::random(),height()*agl::random(),1);
      curve.B1=vec3(width()*agl::random(),height()*agl::random(),1);
      curve.B2=vec3(width()*agl::random(),height()*agl::random(),1);
      curve.B3=vec3(width()*agl::random(),height()*agl::random(),1);
      curve.color=vec3(agl::random(),agl::random(),agl::random());
  }
};

int main(int argc, char** argv) {
  Unique viewer;
  viewer.run();
}

