#ifndef _interpolator_linear_H_
#define _interpolator_linear_H_

#include <string>
#include <vector>
#include "interpolator.h"

//--------------------------------
// Linear 
//--------------------------------

class InterpolatorLinear : public Interpolator
{
public:
   
    InterpolatorLinear() : Interpolator("Linear") {}
    virtual glm::vec3 interpolate(int segment, double u) const {
       // todo: your code here
     return getControlPoint(segment)*(float)(1-u)+getControlPoint(segment+1)*(float)u;
     // return glm::vec3(segment,u,100);
    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {
       // todo: your code here
       mCtrlPoints=keys;
    }
};

#endif
