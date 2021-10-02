#ifndef _interpolator_hermite_
#define _interpolator_hermite_

#include <string>
#include <vector>
#include <Eigen/Dense>
#include "interpolator.h"

//--------------------------------
// Hermite 
//--------------------------------

class InterpolatorHermite : public Interpolator
{
public:
    InterpolatorHermite() : Interpolator("Hermite"), mClampDir(glm::vec3(1,0,0)) {}

    virtual glm::vec3 interpolate(int segment, double u) const {
        float t=(float)u;
        int i=segment*2;
       float h0=1.0f-3.0f*t*t+2.0f*t*t*t;
       float h1=t-2.0f*t*t+t*t*t;
       float h2=-1.0f*t*t+t*t*t;
        float h3=3.0f*t*t+(-2.0f)*t*t*t;

       glm::vec3 p0=getControlPoint(i);
        glm::vec3 p0Prime=getControlPoint(i+1);
        glm::vec3 p1=getControlPoint(i+2);
        glm::vec3 p1Prime=getControlPoint(i+3); 

        
       // return glm::vec3(segment,u,200);

        return p0*h0+p0Prime*h1+p1Prime*h2+p1*h3;
    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {
    
     
       if(!isClamped()) {
            int size=keys.size();
        Eigen::MatrixXd A(size, size);
       
        for(int j=0;j<size;j++) {
            A(0,j)=0;
            A(size-1,j)=0;
        }
        for(int i=1;i<size-1;i++) {

            for(int j=0;j<size;j++) {
               if(j==i-1) {
                    A(i,j)=1;
               }
               else if(j==i) {
                    A(i,j)=4;
               }
                else if(j==i+1) {
                    A(i,j)=1;
               }
               else {
                   A(i,j)=0;
               }
            }
        }
        A(0,0)=2;
        A(0,1)=1;
        A(size-1,size-2)=1;
        A(size-1,size-1)=2;

           //Make P
        Eigen::MatrixXd p(size,2);
        glm::vec3 vector1=3.0f*(keys[1]-keys[0]);
        p(0,0)=vector1[0];
        p(0,1)=vector1[1];
       
         for(int i=1;i<keys.size()-1;i++) {
             glm::vec3 vector=3.0f*(keys[i+1]-keys[i-1]);
             p(i,0)=vector[0];
             p(i,1)=vector[1];

         }
        glm::vec3 vectorLast=3.0f*(keys[size-1]-keys[size-2]);
        p(size-1,0)=vectorLast[0];
        p(size-1,1)=vectorLast[1];

        //Make pPrime
        Eigen::MatrixXd pPrime(size, 2); // slopes for each control point
        pPrime = A.inverse() * p;
      
        for (int i = 0; i < size; i++) {
            mCtrlPoints.push_back(keys[i]);
            glm::vec3 slope=glm::vec3(pPrime(i,0),pPrime(i,1),0);
            mCtrlPoints.push_back(slope);
        }  
       }
       else {
              int size=keys.size();
       // todo: your code here
        Eigen::MatrixXd A(size, size);
       
        for(int j=0;j<size;j++) {
            A(0,j)=0;
            A(size-1,j)=0;
        }
        for(int i=1;i<size-1;i++) {

            for(int j=0;j<size;j++) {
               if(j==i-1) {
                    A(i,j)=1;
               }
               else if(j==i) {
                    A(i,j)=4;
               }
                else if(j==i+1) {
                    A(i,j)=1;
               }
               else {
                   A(i,j)=0;
               }
            }
        }
        A(0,0)=1;
        A(size-1,size-1)=1;

           //Make P
        Eigen::MatrixXd p(size,2);
        glm::vec3 vector1=3.0f*(keys[1]-keys[0]);
        p(0,0)=vector1[0];
        p(0,1)=vector1[1];
       
         for(int i=1;i<keys.size()-1;i++) {
             glm::vec3 vector=3.0f*(keys[i+1]-keys[i-1]);
             p(i,0)=vector[0];
             p(i,1)=vector[1];

         }
        glm::vec3 vectorLast=3.0f*(keys[size-1]-keys[size-2]);
        p(size-1,0)=vectorLast[0];
        p(size-1,1)=vectorLast[1];

        //Make pPrime
        Eigen::MatrixXd pPrime(size, 2); // slopes for each control point
        pPrime = A.inverse() * p;
        for (int i = 0; i < size; i++) {
             mCtrlPoints.push_back(keys[i]);
            glm::vec3 slope=glm::vec3(pPrime(i,0),pPrime(i,1),0);
            mCtrlPoints.push_back(slope);
        }

       }
    }

  
    

    virtual void makeClampedSlopes(const std::vector<glm::vec3>& keys) {
        //Make A
        int size=keys.size();
        Eigen::MatrixXd A(size, size);
       
        for(int j=0;j<size;j++) {
            A(0,j)=0;
            A(size-1,j)=0;
        }
        for(int i=1;i<size-1;i++) {

            for(int j=0;j<size;j++) {
               if(j==i-1) {
                    A(i,j)=1;
               }
               else if(j==i) {
                    A(i,j)=4;
               }
                else if(j==i+1) {
                    A(i,j)=1;
               }
               else {
                   A(i,j)=0;
               }
            }
        }
         A(0,0)=1;
        A(size-1,size-1)=1;
          //Make P
        Eigen::MatrixXd p(size,2);
        glm::vec3 vector1=getClampDirection();
        p(0,0)=vector1[0];
        p(0,1)=vector1[1];
       
         for(int i=1;i<keys.size()-1;i++) {
             glm::vec3 vector=3.0f*(keys[i+1]-keys[i-1]);
             p(i,0)=vector[0];
             p(i,1)=vector[1];

         }
        p(size-1,0)=vector1[0];
        p(size-1,1)=vector1[1];

        //Make pPrime
        Eigen::MatrixXd pPrime(size, 2); // slopes for each control point
        pPrime = A.inverse() * p;
        for (int i = 0; i < size; i++) {
            mCtrlPoints.push_back(keys[i]);
            glm::vec3 slope=glm::vec3(pPrime(i,0),pPrime(i,1),0);
            mCtrlPoints.push_back(slope);
        }
        
    }

      virtual void makeNaturalSlopes(const std::vector<glm::vec3>& keys) {
        int size=keys.size();
       // todo: your code here
        Eigen::MatrixXd A(size, size);
       
        for(int j=0;j<size;j++) {
            A(0,j)=0;
            A(size-1,j)=0;
        }
        for(int i=1;i<size-1;i++) {

            for(int j=0;j<size;j++) {
               if(j==i-1) {
                    A(i,j)=1;
               }
               else if(j==i) {
                    A(i,j)=4;
               }
                else if(j==i+1) {
                    A(i,j)=1;
               }
               else {
                   A(i,j)=0;
               }
            }
        }
        A(0,0)=2;
        A(0,1)=1;
        A(size-1,size-2)=1;
        A(size-1,size-1)=2;

           //Make P
        Eigen::MatrixXd p(size,2);
        glm::vec3 vector1=3.0f*(keys[1]-keys[0]);
        p(0,0)=vector1[0];
        p(0,1)=vector1[1];
       
         for(int i=1;i<keys.size()-1;i++) {
             glm::vec3 vector=3.0f*(keys[i+1]-keys[i-1]);
             p(i,0)=vector[0];
             p(i,1)=vector[1];

         }
        glm::vec3 vectorLast=3.0f*(keys[size-1]-keys[size-2]);
        p(size-1,0)=vectorLast[0];
        p(size-1,1)=vectorLast[1];

        //Make pPrime
        Eigen::MatrixXd pPrime(size, 2); // slopes for each control point
        pPrime = A.inverse() * p;
        for (int i = 0; i < size; i++) {
        std::cout << "slope " << i << " = " << pPrime(i,0) << " " << pPrime(i,1) << std::endl;
        }
      
    }



    

    void setClamped(bool c) { mIsClamped = c; }
    bool isClamped() const { return mIsClamped; }

    void setClampedDirection(const glm::vec3& v) { mClampDir = v; }
    glm::vec3 getClampDirection() const { return mClampDir; }

/* vec2 p0(0,0); // Z will just be zero
    vec2 p1(1,2);
    vec2 p2(3,3);
    vec2 p3(6,3);
    vec2 p4(8,0);

    // Solve the system of linear equations
    Eigen::MatrixXd A(5, 5);
    Eigen::MatrixXd p(5, 2);
    Eigen::MatrixXd pPrime(5, 2); // slopes for each control point

    // natural endpoints
    A(0,0) =  2; A(0,1) = 1; A(0,2) = 0; A(0,3) = 0; A(0,4) = 0;
    A(1,0) =  1; A(1,1) = 4; A(1,2) = 1; A(1,3) = 0; A(1,4) = 0;
    A(2,0) =  0; A(2,1) = 1; A(2,2) = 4; A(2,3) = 1; A(2,4) = 0;
    A(3,0) =  0; A(3,1) = 0; A(3,2) = 1; A(3,3) = 4; A(3,4) = 1;
    A(4,0) =  0; A(4,1) = 0; A(4,2) = 0; A(4,3) = 1; A(4,4) = 2;

    vec2 v0 = 3.0f *(p1 - p0);
    vec2 v1 = 3.0f *(p2 - p0);
    vec2 v2 = 3.0f *(p3 - p1);
    vec2 v3 = 3.0f *(p4 - p2);
    vec2 v4 = 3.0f *(p4 - p3);
    p(0,0) = v0[0]; p(0,1) = v0[1];
    p(1,0) = v1[0]; p(1,1) = v1[1]; 
    p(2,0) = v2[0]; p(2,1) = v2[1]; 
    p(3,0) = v3[0]; p(3,1) = v3[1]; 
    p(4,0) = v4[0]; p(4,1) = v4[1]; 

    pPrime = A.inverse() * p;
    for (int i = 0; i < 5; i++)
    {
        std::cout << "slope " << i << " = " << pPrime(i,0) << " " << pPrime(i,1) << std::endl;
    } */
private:
    bool mIsClamped = true;
    glm::vec3 mClampDir;
};

#endif
