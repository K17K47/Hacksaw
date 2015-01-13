/*
 * mathHelper.h
 *
 *  Created on: 29/05/2014
 *      Author: K17K47
 */

#ifndef MATHHELPER_H_
#define MATHHELPER_H_
#include <math.h>
#include <float.h>
#include <vector>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

#define real_sqrt sqrtl
#define real_pow powl
#define real_abs fabsl
#define real_sin sinl
#define real_cos cosl
#define real_exp expl

#define REAL_MAX DBL_MAX
typedef double real;

typedef Eigen::Matrix<real, 2, 1> Vector2;
typedef Eigen::Matrix<real, 3, 1> Vector3;
typedef Eigen::Matrix<real, 3, 3> Matrix33;
typedef Eigen::Matrix<real, 3, 4> Matrix34;
typedef Eigen::Matrix<real, 4, 4> Matrix44;
typedef Eigen::Quaternion<real> Quaternion;
typedef Eigen::Translation3d Translation3d;

static inline real degToRad(real degrees){return (degrees*M_PI)/180;}
static inline real radToDeg(real radians){return (radians*180)/M_PI;}

template<class T>
Eigen::Matrix<T,4,4> perspective
(
   double fovy,
   double aspect,
   double zNear,
   double zFar
)
{
   typedef Eigen::Matrix<T,4,4> Matrix4;

   assert(aspect > 0);
   assert(zFar > zNear);

   double radf = degToRad(fovy);

   double tanHalfFovy = tan(radf / 2.0);
   Matrix4 res = Matrix4::Zero();
   res(0,0) = 1.0 / (aspect * tanHalfFovy);
   res(1,1) = 1.0 / (tanHalfFovy);
   res(2,2) = - (zFar + zNear) / (zFar - zNear);
   res(3,2) = - 1.0;
   res(2,3) = - (2.0 * zFar * zNear) / (zFar - zNear);
   return res;
}

template<class T>
Eigen::Matrix<T,4,4> lookAt
(
   Eigen::Matrix<T,3,1> const & eye,
   Eigen::Matrix<T,3,1> const & center,
   Eigen::Matrix<T,3,1> const & up
)
{
   typedef Eigen::Matrix<T,4,4> Matrix4;
   typedef Eigen::Matrix<T,3,1> Vector3;

   Vector3 f = (center - eye).normalized();
   Vector3 u = up.normalized();
   Vector3 s = f.cross(u).normalized();
   u = s.cross(f);

   Matrix4 res;
   res <<  s.x(),s.y(),s.z(),-s.dot(eye),
           u.x(),u.y(),u.z(),-u.dot(eye),
           -f.x(),-f.y(),-f.z(),f.dot(eye),
           0,0,0,1;

   return res;
}

struct dbVector2{
	Vector2 p;
	Vector2 v;
};
struct dbVector3{
	Vector3 p;
	Vector3 v;
};

#endif /* MATHHELPER_H_ */
