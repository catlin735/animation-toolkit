#include "behaviors.h"
#include "steerable.h"
#include <cmath>
#include <algorithm>

using namespace glm;
using namespace atk;

//--------------------------------------------------------------
// Shared properties for all behaviors
ABehavior::ABehavior(const char* name) : _name(name)
{
   // TODO: set good values
   setParam("MaxSpeed", 10);
   setParam("AgentRadius", 100);
}

//--------------------------------------------------------------
// Seek behavior

ASeek::ASeek() : ABehavior("Seek") 
{ 
}

//
// Steer the actor TOWARDS a target at max speed
//
// @param actor: steerable character to move
// @return desired velocity
//
// @note: call actor.getPosition to get teh actor's position
// @note: call getParam("MaxSpeed") to get the max speed
vec3 ASeek::calculateDesiredVelocity(const ASteerable& actor,
   const AWorld& world, const vec3& target)
{
  
   float maxSpeed=getParam("MaxSpeed");
   vec3 pos=actor.getPosition();
   vec3 desiredVelocity=glm::normalize(target-pos)*maxSpeed;
   if(glm::length(target-pos)<10) {
      return glm::vec3(0,0,0);
   }
   return desiredVelocity;
}

//--------------------------------------------------------------
// Flee behavior

AFlee::AFlee() : ABehavior("Flee") 
{
}

//
// Steer the actor AWAY from a target at max speed
//
// @param actor: steerable character to move
// @return desired velocity
//
// @note: call actor.getPosition to get teh actor's position
// @note: call getParam("MaxSpeed") to get the max speed
vec3 AFlee::calculateDesiredVelocity(const ASteerable& actor,
   const AWorld& world, const vec3& targetPos)
{
   float maxSpeed=getParam("MaxSpeed");
   vec3 pos=actor.getPosition();
   vec3 desiredVelocity=glm::normalize(targetPos-pos)*maxSpeed*-1.0f;
   return desiredVelocity;
}

//--------------------------------------------------------------
// Arrival behavior

AArrival::AArrival() : ABehavior("Arrival") 
{
   // TODO: Set good parameters
   setParam("kArrival", 1);
   setParam("TargetRadius", 20);
}

//
// Returns a velocity whose speed is proportional to the actors distance
// from the target
//
// @param actor: steerable character to move
// @return desired velocity
vec3 AArrival::calculateDesiredVelocity(const ASteerable& actor,
   const AWorld& world, const vec3& targetPos)
{

   float maxSpeed=getParam("MaxSpeed");
   vec3 pos=actor.getPosition();
   vec3 desiredVelocity=glm::normalize(targetPos-pos)*maxSpeed;
   float distance=glm::length(targetPos-pos);
   float radius=getParam("TargetRadius");
   if(distance<radius) {
      float slowSpeed=maxSpeed*(distance/radius);
      return glm::normalize(targetPos-pos)*slowSpeed; 
   }
   return desiredVelocity;
}

//--------------------------------------------------------------
// Departure behavior

ADeparture::ADeparture() : ABehavior("Departure") 
{
   setParam("InnerRadius", 1);
   setParam("OuterRadius", 1);
   setParam("kDeparture", 1);
}

//
// Calculate a repelent velocity based on the actor's 
// distance from the target
vec3 ADeparture::calculateDesiredVelocity(const ASteerable& actor,
   const AWorld& world, const vec3& targetPos)
{
   float maxSpeed=getParam("MaxSpeed");
   vec3 pos=actor.getPosition();
   vec3 desiredVelocity=glm::normalize(targetPos-pos)*maxSpeed;
   float distance=glm::length(targetPos-pos);
   float innerR=getParam("InnerRadius");
   float outerR=getParam("OuterRadius");
   if(distance>outerR) {
      return desiredVelocity;
   }
   if(distance>innerR && distance<=outerR) {
         return desiredVelocity;
   }
   if(distance<innerR) {
      float fleeSpeed=-1.0*maxSpeed*(distance/innerR);
      return glm::normalize(targetPos-pos)*fleeSpeed; 
   }
   return desiredVelocity;
}

//--------------------------------------------------------------
// Avoid behavior

AAvoid::AAvoid() : ABehavior("Avoid") 
{
   setParam("kAvoid", 1);
}

// If an actor is near an obstacle, avoid adds either a tangential or
// normal response velocity
//  Obstacles are in getWorld()->getObstacle(i) and have class type AObstacle
vec3 AAvoid::calculateDesiredVelocity(const ASteerable& actor,
   const AWorld& world, const vec3& targetPos)
{
   float maxSpeed=getParam("MaxSpeed");
   vec3 pos=actor.getPosition();
   float distances[world.getNumObstacles()];
   for(int i=0;i<world.getNumObstacles();i++) {
      AObstacle obstacle=world.getObstacle(i);
      vec3 opos=obstacle.position;
      distances[i]=glm::length(opos-pos);
   }
   float *min=std::min_element(distances,distances+world.getNumObstacles()-1);
   int index=distances[min-distances];
   if(*min<world.getObstacle(index).radius+10) {
      vec3 direction=world.getObstacle(index).position-pos;
      return glm::normalize(direction)*maxSpeed*-1.0f;
   }
    return glm::normalize(targetPos-pos)*maxSpeed;
}
//--------------------------------------------------------------
// Wander behavior

AWander::AWander() : ABehavior("Wander")
{
   setParam("kWander", 1);
}

// Wander returns a velocity whose direction changes randomly (and smoothly)
vec3 AWander::calculateDesiredVelocity(const ASteerable& actor,
   const AWorld& world, const vec3& target)
{
   return vec3(0,0,0);
}

//--------------------------------------------------------------
// Separation behavior

ASeparation::ASeparation() : ABehavior("Separation")
{
   setParam("Neighborhood", 1);
   setParam("kSeparation", 1);
}


// Separation tries to maintain a constant distance between all agents
// within the neighborhood of the agent
// getWorld()->getAgent(i) returns the ith agent in the environment
// you can check whether two agents are the same with ==
vec3 ASeparation::calculateDesiredVelocity(const ASteerable& actor,
   const AWorld& world, const vec3& target)
{
   return vec3(0,0,0);
}


//--------------------------------------------------------------
// Cohesion behavior

ACohesion::ACohesion() : ABehavior("Cohesion")
{
   setParam("Neighborhood", 1);
   setParam("kCohesion", 1);
}

// Cohesion moves actors towards the center of a group of agents
vec3 ACohesion::calculateDesiredVelocity(const ASteerable& actor,
   const AWorld& world, const vec3& target)
{
    return vec3(0,0,0);
}

//--------------------------------------------------------------
// Alignment behavior
AAlignment::AAlignment() : ABehavior("Alignment")
{
   setParam("Neighborhood", 1);
   setParam("kAlignment", 1);
}

// Alignment returns an average velocity of all active agents
vec3 AAlignment::calculateDesiredVelocity(const ASteerable& actor,
   const AWorld& world, const vec3& target)
{
    return vec3(0);
}

//--------------------------------------------------------------
// Flocking behavior
AFlocking::AFlocking() : ABehavior("Flocking")
{
}

// Flocking combines separation, cohesion, and alignment
vec3 AFlocking::calculateDesiredVelocity(const ASteerable& actor,
   const AWorld& world, const vec3& target)
{
   return vec3(0,0,0);
}

//--------------------------------------------------------------
// Leader
ALeader::ALeader() : ABehavior("Leader")
{
   setParam("CSeparation", 1);
   setParam("CCohesion", 1);
   setParam("CAlignment", 1);
   setParam("CArrival", 1);
}

// You need to find the leader, who is always the first agent in agents
// If the actor is the leader, move towards the target; otherwise, 
// follow the leader as a flock
vec3 ALeader::calculateDesiredVelocity(const ASteerable& actor,
   const AWorld& world, const vec3& target)
{
   return vec3(0,0,0);
}


