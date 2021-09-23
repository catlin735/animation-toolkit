#include "atkui/framework.h"
#include <list>
#include <iterator>
using namespace glm;
using namespace std;

class Screensaver : public atkui::Framework {
 public:
  Screensaver() : atkui::Framework(atkui::Orthographic) {
  }

 

  struct Curve {

    vec3 B0;
    vec3 B1;
    vec3 B2;
    vec3 B3;
    vec3 color;

  public:
    Curve() {
        vec3 B0 = vec3(100,  50, 0);
        vec3 B1 = vec3(150, 200, 0);
        vec3 B2 = vec3(250, 100, 0);
        vec3 B3 = vec3(300, 300, 0);
    }

    Curve(vec3 b1, vec3 b2, vec3 b3,vec3 b4, vec3 c) {
        vec3 B0;
        vec3 B1;
        vec3 B2;
        vec3 B3;
        vec3 color;
    }

};

 private:
  Curve init;
  Curve final;
  Curve current;
  float time;
  list<Curve>list;

  void setup() {
   
    init.B0=vec3(width()*agl::random(),height()*agl::random(),1);
    init.B1=vec3(width()*agl::random(),height()*agl::random(),1);
    init.B2=vec3(width()*agl::random(),height()*agl::random(),1);
    init.B3=vec3(width()*agl::random(),height()*agl::random(),1);
    init.color=vec3(agl::random(),agl::random(),agl::random());

    final.B0=vec3(width()*agl::random(),height()*agl::random(),1);
    final.B1=vec3(width()*agl::random(),height()*agl::random(),1);
    final.B2=vec3(width()*agl::random(),height()*agl::random(),1);
    final.B3=vec3(width()*agl::random(),height()*agl::random(),1);
    final.color=vec3(agl::random(),agl::random(),agl::random());

    current.color=randColor();
    
   // final=randomCurve();

    
    time=0;
  }

  void scene() {

    drawCurve(init);
     drawCurve(final);

      time+=0.01;

   
    current.B0=lerp(init.B0,final.B0,time);
    current.B1=lerp(init.B1,final.B1,time);
    current.B2=lerp(init.B2,final.B2,time);
    current.B3=lerp(init.B3,final.B3,time);
    current.color=lerp(init.color,final.color,time); 
    drawCurve(current);

    if(fmod(time*100,3)==0) {
       // list.push_front(current);
    }
  
    if(list.size()>20) {
      list.pop_back();
    }
    std::list <Curve> :: iterator iter;
    for(iter=list.begin(); iter!=list.end(); ++iter) {
      drawCurve(*iter);

    }

    
  

    

     if(time>1) {
     init.B0=final.B0;
      init.B1=final.B1;
      init.B2=final.B2;
      init.B3=final.B3;
      randomCurve(final); 
      time=0; 
    } 


  }

  vec3 lerp(vec3 a, vec3 b, float t) {
    
    return a*(1-t)+b*t;
  }


  vec3 castel2(vec3 a, vec3 b, vec3 c, float t) {
    return lerp(lerp(a,b,t),lerp(b,c,t),t);
  }

  vec3 castelCubic(vec3 a, vec3 b, vec3 c, vec3 d, float t) {

      return lerp(castel2(a,b,c,t),castel2(b,c,d,t),t);
  }

  void drawCurve(Curve curve) {
    setColor(curve.color);
    vec3 prev=curve.B0;
      for(double i=0;i<1;i+=0.01) {
        vec3 newPos=castelCubic(curve.B0,curve.B1,curve.B2,curve.B3,i);
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
  Screensaver viewer;
  viewer.run();
}

