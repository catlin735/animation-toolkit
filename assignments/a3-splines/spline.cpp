#include <cmath>
#include "spline.h"
#include "math.h"
#include "spline.h"
#include "interpolator_hermite.h"
#include "interpolator_catmullrom.h"
#include "interpolator_linear.h"

// global interpolator to use as default
static InterpolatorLinear gDefaultInterpolator; 

Spline::Spline() : 
  mDirty(true),
  mInterpolator(&gDefaultInterpolator) {
}

Spline::~Spline() {
}

void Spline::addInterpolationType(const std::string& name, Interpolator* interp) {
  mInterpolators[name] = interp;
}

void Spline::setInterpolationType(const std::string& name) {
  assert(mInterpolators.count(name) != 0);
  mInterpolator = mInterpolators[name];
  mDirty = true;
}

const std::string& Spline::getInterpolationType() const {
  return mInterpolator->getType();
}

void Spline::editKey(int keyID, const glm::vec3& value) {
  assert(keyID >= 0 && keyID < (int) mKeys.size());
  mKeys[keyID] = value;
  mDirty = true;
}

int Spline::appendKey(float time, const glm::vec3& value) {
  mKeys.push_back(value);
  mTimes.push_back(time);
  mDirty = true;
  return mKeys.size();
}

void Spline::deleteKey(int keyID) {
  assert(keyID >= 0 && keyID < (int) mKeys.size());
  mKeys.erase(mKeys.begin() + keyID);
  mTimes.erase(mTimes.begin() + keyID);
  mDirty = true;
}

glm::vec3 Spline::getKey(int keyID) const {
  assert(keyID >= 0 && keyID < (int) mKeys.size());
  return mKeys[keyID];
}

float Spline::getTime(int keyID) const {
  assert(keyID >= 0 && keyID < (int) mKeys.size());
  return mTimes[keyID];
}

int Spline::getNumKeys() const {
  return (int) mKeys.size();
}

void Spline::clear() {
  mKeys.clear();
  mTimes.clear();
  mInterpolator->clearControlPoints();
}

float Spline::getDuration() const {
  if (mKeys.size() == 0) return 0;
  int lastIdx = mKeys.size() - 1;
  return mTimes[lastIdx];
}

int Spline::getNumControlPoints() const {
  return mInterpolator->getNumControlPoints();
}

const glm::vec3& Spline::getControlPoint(int id) const {
  return mInterpolator->getControlPoint(id);
}

int Spline::getNumSegments() const {
  if (mKeys.size() > 1) return mKeys.size()-1;
  return 0;
}

void Spline::computeControlPoints() {
  mInterpolator->computeControlPoints(mKeys);
}

void Spline::editControlPoint(int id, const glm::vec3& v) {
  mInterpolator->editControlPoint(id, v);
}

glm::vec3 Spline::getValue(float t) const {
  glm::vec3 result=glm::vec3(0);
  if (mDirty) {
    mInterpolator->computeControlPoints(mKeys);
    mDirty = false;
  }

  if(mKeys.size()>1) {
     double u=0;
      int segment=0;
    if(t<getKey(0)[0]) {
      u=0;
      segment=0;
    }
    else if(t>getKey(getNumKeys()-1)[0]) {
      u=1;
      segment=getNumSegments()-1;
    }

    else {
       
      for(int i=0;i<getNumKeys()-2;i++) {
        if(t>=getKey(i)[0]) {
          segment++;
          u=(t-getKey(i+1)[0])/(getKey(i+2)[0]-getKey(i+1)[0]);
        }
      }
     
    }
     std::string type=getInterpolationType();
      if(type=="Linear") {
        InterpolatorLinear* test=new InterpolatorLinear();
        test->computeControlPoints(mKeys);
        result=test->interpolate(segment,u);

      }
      else if(type=="Hermite") {
        InterpolatorHermite* test=new InterpolatorHermite();
        test->computeControlPoints(mKeys);
        result=test->interpolate(segment,u);
      }
      else {
        InterpolatorCatmullRom* test=new InterpolatorCatmullRom();
        test->computeControlPoints(mKeys);
        result=test->interpolate(segment,u);
      }
  }
    return result; 

}



