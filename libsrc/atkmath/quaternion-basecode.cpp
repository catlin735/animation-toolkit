#include "atkmath/quaternion.h"
#include "atkmath/matrix3.h"
#include "atkmath/vector3.h"
#include <algorithm>
using namespace std;

namespace atkmath {

Quaternion Quaternion::Slerp(const Quaternion& q0, const Quaternion& q1, double t)
{
	double omega=0;
	double dot=Dot(q0,q1);
	if(Dot(q0,q1)<-1) {
		dot=-1;
	}
	if(Dot(q0,q1)>1) {
		dot=1;
	}

	if(dot>=0) {
		omega=acos(dot);
	}
	else {
		double dot=Dot(operator *(q0,-1),q1);
		if(Dot(q0,q1)<-1) {
			dot=-1;
		}
		if(Dot(q0,q1)>1) {
			dot=1;
		}
		omega=acos(dot);
	}

	if(omega==0) {
		return q0;
	}
	std::cout<<dot;
	std::cout<<omega;
	return operator *(q0,sin(omega*(1-t))/sin(omega))+operator *(q1,sin(omega*t)/sin(omega));
}

void Quaternion::toAxisAngle (Vector3& axis, double& angleRad) const
{
	// TODO
	double x=this->mX;
	double y=this->mY;
	double z=this->mZ;
	double w=this->mW;

	if(acos(w)<0.01) {
		angleRad=0;
	} 
	else {
		angleRad=2*acos(this->mW);
	}

	axis[0]=this->mX/sin(angleRad/2);
	axis[1]=this->mY/sin(angleRad/2);
	axis[2]=this->mZ/sin(angleRad/2);

	if(isnan(axis[0])) {
		axis[0]=0.01;
	}
	if(isinf(axis[0])) {
		axis[0]=1;
	}
	if(isnan(axis[1])) {
		axis[1]=0.01;
	}
	if(isinf(axis[1])) {
		axis[1]=1;
	}
	if(isnan(axis[2])) {
		axis[2]=0.01;
	}
	if(isinf(axis[2])) {
		axis[2]=1;
	}
	

}

void Quaternion::fromAxisAngle (const Vector3& axis, double angleRad)
{
	// TODO
	double x=axis[0];
	double y=axis[1];
	double z=axis[2];
	if(isnan(axis[0])) {
		x=0.01;
	}
	if(isinf(axis[0])) {
		x=1;
	}
	if(isnan(axis[1])) {
		y=0.01;
	}
	if(isinf(axis[1])) {
		y=1;
	}
	if(isnan(axis[2])) {
		z=0.01;
	}
	if(isinf(axis[2])) {
		z=1;
	}

	this->mW = cos(angleRad/2);

	if(acos(this->mW)<0.01) {
		angleRad=0;
	} 
	else {
		angleRad=2*acos(this->mW);
	}

	this->mX = x*sin(angleRad/2);
    this->mY = y*sin(angleRad/2);
    this->mZ = z*sin(angleRad/2);


    normalize();
}

Matrix3 Quaternion::toMatrix () const
{
	// TODO
	


	
	/* double x=this->mX;
	double y=this->mY;
	double z=this->mZ;
	double w=this->mW;
	double ct=cos(angle);
	double st=sin(angle);
	double vt=1-cos(angle);
 */
/* 	this->mX = kx*sin(angle/2);
    this->mY = ky*sin(angle/2);
    this->mZ = kz*sin(angle/2);
	this->mW = cos(angleRad/2); */
	
	Vector3 axis=Vector3(0,0,0);
	double angle=0;
	Quaternion::toAxisAngle(axis,angle);
	
	double kx=axis[0];
	double ky=axis[1];
	double kz=axis[2];

	double x=kx*sin(angle/2);
	double y=ky*sin(angle/2);
	double z=kz*sin(angle/2);
	double w=cos(angle/2);

	Matrix3* rot=new Matrix3();

	rot->m11=1.0f-(2.0f*((y*y)+(z*z)));
	rot->m12=2.0f*(x*y-w*z);
	rot->m13=2.0f*(x*z+w*y);

	rot->m21=2.0f*(x*y+w*z);
	rot->m22=1.0f-(2.0f*((x*x)+(z*z)));
	rot->m23=2.0f*(y*z-w*x);

	rot->m31=2.0f*(x*z-w*y);
	rot->m32=2.0f*(y*z+w*x);
	rot->m33=1.0f-(2.0f*((y*y)+(x*x)));  





/* 	rot->m11=kx*kx*vt+ct;
	rot->m12=kx*ky*vt-kz*st;
	rot->m13=kx*kz*vt+ky*st;

	rot->m21=kx*ky*vt-kz*st;
	rot->m22=ky*ky*vt+ct;
	rot->m23=ky*kz*vt-kx*st;

	rot->m31=kx*ky*vt+ky*st;
	rot->m32=ky*kz*vt-kx*st;
	rot->m33=ky*ky*vt+ct; */
	return *rot;
}

void Quaternion::fromMatrix(const Matrix3& rot)
{
	// TODO
	double m11=rot.m11;
	double m22=rot.m22;
	double m33=rot.m33;

	double w_squared=0.25*(m11+m22+m33+1);
	double x_squared=0.25*(m11-m22-m33+1);
	double y_squared=0.25*(1-m11+m22-m33);
	double z_squared=0.25*(1-m11-m22+m33);

	double wx=0.25*(rot.m32-rot.m23);
	double wy=0.25*(rot.m13-rot.m31);
	double xy=0.25*(rot.m21+rot.m12);
	double xz=0.25*(rot.m13+rot.m31);
	double yz=0.25*(rot.m23+rot.m32);
	double wz=0.25*(rot.m21-rot.m12);
	
	double arr[]={w_squared,x_squared,y_squared,z_squared};


	std::sort(std::begin(arr), std::end(arr));
	double max=arr[3];
	double w=0;
	double x=0;
	double y=0;
	double z=0;


	if(max==w_squared) {

		w=sqrt(w_squared);
		x=wx/w;
		y=wy/w;
		z=wz/w;
	}
	if(max==x_squared) {
		x=sqrt(x_squared);
		w=wx/x;
		y=xy/x;
		z=xz/x;
	}
	if(max==y_squared) {
		y=sqrt(y_squared);
		w=wy/y;
		x=xy/y;
		z=yz/y;
	}
	if(max==z_squared) {
		z=sqrt(z_squared);
		x=xz/z;
		y=yz/z;
		w=wz/z;
	}

	this->mW = w;
	this->mX = x;
    this->mY = y;
    this->mZ = z;

	Vector3 axis=Vector3(0,0,0);
	double angle=0;
	Quaternion::toAxisAngle(axis,angle);
	
	double kx=axis[0];
	double ky=axis[1];
	double kz=axis[2];

	x=kx*sin(angle/2);
	y=ky*sin(angle/2);
	z=kz*sin(angle/2);
	w=cos(angle/2);

	this->mW = w;
	this->mX = x;
    this->mY = y;
    this->mZ = z;

	
	
	
}

}
