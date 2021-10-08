#include "atkmath/matrix3.h"
#include "atkmath/quaternion.h"

namespace atkmath {

Vector3 Matrix3::toEulerAnglesXYZ() const
{
   

    if(this->m13==1) {
      double x=atan2(this->m21,this->m22);
      double z=0;
      double y=(PI/2);
      return Vector3(x,y,z);
   }
    if(this->m13==-1) {
      double x=-1*atan2(this->m21,this->m22);
      double z=0;
      double y=-1*(PI/2);
      return Vector3(x,y,z);
   }
   double x=-1*atan2(this->m23,this->m33);
   double z=-1*atan2(this->m12,this->m11);
   double y=asin(this->m13);
   return Vector3(x,y,z);
}

Vector3 Matrix3::toEulerAnglesXZY() const
{
   if(this->m12==-1) {
      double x=atan2(this->m31,this->m21);
      double y=0;
       double z=(PI/2);
      return Vector3(x,y,z);
   }
    if(this->m12==1) {
      double x=atan2(-1*this->m31,-1*this->m21);
      double y=0;
      double z=-1*(PI/2);
      return Vector3(x,y,z);
   }
   double y=atan2(this->m13,this->m11);
   double x=atan2(this->m32,this->m22);
   double z=asin(-1*this->m12);
   return Vector3(x,y,z);
}

Vector3 Matrix3::toEulerAnglesYXZ() const
{
     if(this->m23==-1) {
      double y=atan2(this->m12,this->m11);
      double z=0;
      double x=(PI/2);
      return Vector3(x,y,z);
   }

   if(this->m23==1) {
      double y=0;
      double z=atan2(-1*this->m12,this->m11);
      double x=-1*(PI/2);
      return Vector3(x,y,z);
   }

   double y=atan2(this->m13,this->m33);
   double z=atan2(this->m21,this->m22);
   double x=asin(-1*this->m23);
   return Vector3(x,y,z);
}

Vector3 Matrix3::toEulerAnglesYZX() const
{
  
    if(this->m21==1) {
      double y=atan2(this->m32,this->m33);
      double z=(PI/2);
      double x=0;
      return Vector3(x,y,z);
   }

   if(this->m21==-1) {
      double y=-1*atan2(this->m32,this->m33);
      double z=-1*(PI/2);
      double x=0;
      return Vector3(x,y,z);
   }

   double x=-1*atan2(this->m23,this->m22);
   double y=-1*atan2(this->m31,this->m11);
   double z=asin(this->m21);
   return Vector3(x,y,z);
}

Vector3 Matrix3::toEulerAnglesZXY() const
{
      if(this->m32==1) {
      double y=atan2(this->m21,this->m11);
      double z=0;
      double x=(PI/2);
      return Vector3(x,y,z);
   }

   if(this->m32==-1) {
      double y=-1*atan2(this->m21,this->m11);
      double z=0;
      double x=-1*(PI/2);
      return Vector3(x,y,z);
   }

   double z=-1*atan2(this->m12,this->m22);
   double y=-1*atan2(this->m31,this->m33);
   double x=asin(this->m32);
   return Vector3(x,y,z);
}

Vector3 Matrix3::toEulerAnglesZYX() const
{
  


     if(this->m31==-1) {
      double x=atan2(this->m12,this->m13);
      double z=0;
      double y=(PI/2);
      return Vector3(x,y,z);
   }

    if(this->m31==1) {
      double x=atan2(-1*this->m12,-1*this->m13);
      double z=0;
      double y=-1*(PI/2);
      return Vector3(x,y,z);
   }

   double x=atan2(this->m32,this->m33);
   double z=atan2(this->m21,this->m11);
   double y=asin(-1*this->m31);
   return Vector3(x,y,z);
}

void Matrix3::fromEulerAnglesXYZ(const Vector3& angleRad)
{
   if(angleRad[1]==PI/2) {
      *this=operator*(operator*(*this->Rx(angleRad),*this->Rz(angleRad)),*this->Ry(angleRad));
   }
   else if(angleRad[1]==PI/-2){
     *this=operator*(operator*(*this->Rx(angleRad),*this->Rz(angleRad)),*this->Ry(angleRad));
   }
   else {
   *this=operator*(*this->Rx(angleRad),operator*(*this->Ry(angleRad),*this->Rz(angleRad)));
   }
    
}

void Matrix3::fromEulerAnglesXZY(const Vector3& angleRad)
{


    if(angleRad[1]==PI/2) {
      *this=operator*(operator*(*this->Rx(angleRad),*this->Rz(angleRad)),*this->Ry(angleRad));
   }
   else if(angleRad[1]==PI/-2){
      *this=operator*(operator*(*this->Rx(angleRad),*this->Rz(angleRad)),*this->Ry(angleRad));
   }
   else {
   *this=operator*(operator*(*this->Rx(angleRad),*this->Rz(angleRad)),*this->Ry(angleRad));
   }
  
}

void Matrix3::fromEulerAnglesYXZ(const Vector3& angleRad)
{
 *this=operator*(operator*(*this->Ry(angleRad),*this->Rx(angleRad)),*this->Rz(angleRad));
}

void Matrix3::fromEulerAnglesYZX(const Vector3& angleRad)
{
   *this=operator*(operator*(*this->Ry(angleRad),*this->Rz(angleRad)),*this->Rx(angleRad));
}

void Matrix3::fromEulerAnglesZXY(const Vector3& angleRad)
{
    *this=operator*(operator*(*this->Rz(angleRad),*this->Rx(angleRad)),*this->Ry(angleRad));
}

void Matrix3::fromEulerAnglesZYX(const Vector3& angleRad)
{
   *this=operator*(operator*(*this->Rz(angleRad),*this->Ry(angleRad)),*this->Rx(angleRad));
}

void Matrix3::toAxisAngle(Vector3& axis, double& angleRad) const
{
   // TODO
}

void Matrix3::fromAxisAngle(const Vector3& axis, double angleRad)
{
   // TODO
   *this = Identity;
}

Matrix3* Matrix3::Rx(const Vector3& angleRad) {
   Matrix3* rx=new Matrix3();
   double theta=angleRad[0];
   rx->m11=1;
   rx->m12=0;
   rx->m13=0;
   rx->m21=0;
   rx->m22=cos(theta);
   rx->m23=-1*sin(theta);
   rx->m31=0;
   rx->m32=sin(theta);
   rx->m33=cos(theta);

   return rx;
}

Matrix3* Matrix3::Ry(const Vector3& angleRad) {
   Matrix3* ry=new Matrix3();
   double theta=angleRad[1];
   ry->m11=cos(theta);
   ry->m12=0;
   ry->m13=sin(theta);
   ry->m21=0;
   ry->m22=1;
   ry->m23=0;
   ry->m31=-1*sin(theta);
   ry->m32=0;
   ry->m33=cos(theta);

   return ry;

}

Matrix3* Matrix3::Rz(const Vector3& angleRad) {
   Matrix3* rz=new Matrix3();
   double theta=angleRad[2];
   rz->m11=cos(theta);
   rz->m12=-1*sin(theta);
   rz->m13=0;
   rz->m21=sin(theta);
   rz->m22=cos(theta);
   rz->m23=0;
   rz->m31=0;
   rz->m32=0;
   rz->m33=1;

   return rz;

}

Matrix3* Matrix3::Ry90(const Vector3& angleRad) {
   Matrix3* ry=new Matrix3();
   double x=angleRad[0];
   double y=angleRad[1];
   double z=angleRad[2];
   ry->m11=0;
   ry->m12=0;
   ry->m13=1;
   ry->m21=sin(x)*cos(z)+cos(x)*sin(z);
   ry->m22=cos(x)*cos(z)-sin(x)*sin(z);
   ry->m23=0;
   ry->m31=sin(x)*sin(z)-cos(x)*cos(z);
   ry->m32=sin(x)*cos(z)+cos(x)*sin(z);
   ry->m33=0;

   return ry;

}

Matrix3* Matrix3::Ryn90(const Vector3& angleRad) {
   Matrix3* ry=new Matrix3();
   double theta=angleRad[1];
   ry->m11=0;
   ry->m12=0;
   ry->m13=-1;
   ry->m21=0;
   ry->m22=1;
   ry->m23=0;
   ry->m31=1;
   ry->m32=0;
   ry->m33=0;

   return ry;

}





}