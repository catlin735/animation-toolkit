#include "steerable.h"
#include "behaviors.h"

using namespace glm;
using namespace atk;

float ASteerable::kVelKv = 150.0; 
float ASteerable::kOriKv = 150.0;  
float ASteerable::kOriKp = 150.0;

// Given a desired velocity, veld, and dt, compute a transform holding 
// the new orientation and change in position
//
// rotation control: tau = I * (-Kv1 * thetaDot + Kp1 * (thetaD - theta))
// translation control: f = m * Kv0 * (vd - v)
void ASteerable::senseControlAct(const vec3& veld, float dt)
{
    /*  _time(0), _state{0,0,0,0}, _derivative{0,0,0,0}, _mass(1), _inertia(1),
   _force(0), _torque(0), _vd(0), _thetad(0), 
   _veld(0, 0, 0), _vel(0, 0, 0) 
   state={x,v,theta,thetadot}
    _derivative{vel,f/m,thetadot,torque/m}
   */
   // Compute _vd and _thetad

   _vd=glm::length(veld);
   _thetad=atan2(veld.x,veld.z);
   std::cout<<_thetad;
   // compute _force and _torque
   _force=_mass * kOriKv *(_vd - glm::length(_vel));
  // _force=_mass * kOriKv *(v - glm::length(_vel));

   _torque=_inertia *(-1.0f*kVelKv*_thetad + kOriKp * ( _thetad - _state[ORI]));
   // find derivative
   _derivative[0]=_vd;
   _derivative[1]= _force/_mass;
   _derivative[2]=_thetad;
   _derivative[3]= _torque/_mass;
   // update state
   _state[0]= _state[0]+dt* _derivative[0];
   _state[1]= _state[1]+dt*_derivative[1];
   _state[2]= _state[2]+dt*_derivative[2];
   _state[3]= _state[3]+dt*_derivative[3];
   // compute global position and orientation and update _characterRoot
   
   quat rot = glm::angleAxis(_state[ORI], vec3(0,1,0));
   vec3 localPos(0,0,_state[POS]);
   _characterRoot.setT(rot * localPos + _characterRoot.t());
   _characterRoot.setR(rot); 
     
}
  



// randomize the colors, characters, and animation times here
void ASteerable::randomizeAppearance()
{
   // to randomize the walking animations, compute different initial values 
   // for _time

   // to randomize color, call _drawer.setColor

   // to randomize shape, compute random values for _drawer.setJointRadius
   // or randomly assign different drawers to have a mix of characters
}

