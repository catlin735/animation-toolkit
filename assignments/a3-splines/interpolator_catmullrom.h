#ifndef _interpolator_catmullrom_
#define _interpolator_catmullrom_

#include <string>
#include <vector>
#include "interpolator.h"

//--------------------------------
// Catmull-Rom 
//--------------------------------

class InterpolatorCatmullRom : public Interpolator
{
public:
    InterpolatorCatmullRom() : Interpolator("Catmull-Rom") {}

    virtual glm::vec3 interpolate(int segment, double u) const {
       // todo: your code here
       // see: interpolator.h and writeup for details
       int i=segment*3;
      
       return castelCubic(getControlPoint(i),getControlPoint(i+1),getControlPoint(i+2),getControlPoint(i+3),(float)u);
    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {
       // todo: your code here
       // see: interpolator.h and writeup for details

      clearControlPoints();
      float k=(float)1/(float)6;

       //Compute first segment
       //b0=p(i)
       //b1=p(i)+(1/6)[p(i+1)-p(i)]
       //b2=p(i+1)-(1/6)[p(i+2)-p(i)]
       //b3=p(i+1)
      mCtrlPoints.push_back(keys[0]);
      mCtrlPoints.push_back(keys[0]+k*(keys[1]-keys[0]));
      mCtrlPoints.push_back(computeB2(0,keys));


      //Compute regular segment
       //b0=p(i)
       //b1=p(i)+(1/6)[p(i+1)-p(i-1)]
       //b2=p(i+1)-(1/6)[p(i+2)-p(i)]
       //b3=p(i+1)
      for(int i=1;i<keys.size()-2;i++) {
         mCtrlPoints.push_back(keys[i]);
         mCtrlPoints.push_back(computeB1(i,keys));
         mCtrlPoints.push_back(computeB2(i,keys));
      }
       //Compute last segment 
       //b0=p(i)
       //b1=p(i)+(1/6)[p(i+1)-p(i-1)]
       //b2=p(i+1)-(1/6)[p(i+1)-p(i)]
       //b3=p(i+1)
      mCtrlPoints.push_back(keys[keys.size()-2]);
      mCtrlPoints.push_back(computeB1(keys.size()-2,keys));
      mCtrlPoints.push_back(keys[keys.size()-1]-k*(keys[keys.size()-1]-keys[keys.size()-2]));
      mCtrlPoints.push_back(keys[keys.size()-1]); 

    }

      glm::vec3 computeB1(int i,const std::vector<glm::vec3>& keys) {
       //b1=p(i)+(1/6)[p(i+1)-p(i-1)]
         float k=(float)1/(float)6;
       return keys[i]+k*(keys[i+1]-keys[i-1]);
    }

     glm::vec3 computeB2(int i,const std::vector<glm::vec3>& keys) {
       //b2=p(i+1)-(1/6)[p(i+2)-p(i)]
          float k=(float)1/(float)6;
       return keys[i+1]-k*(keys[i+2]-keys[i]);
    }

      glm::vec3 lerp(glm::vec3 a, glm::vec3 b, float t)  const {
    
      return a*(1-t)+b*t;
      }


  glm::vec3 castel2(glm::vec3 a, glm::vec3 b, glm::vec3 c, float t)  const {
    return lerp(lerp(a,b,t),lerp(b,c,t),t);
  }

   glm::vec3 castelCubic(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, float t) const {

      return lerp(castel2(a,b,c,t),castel2(b,c,d,t),t);
  }


    
};

#endif
