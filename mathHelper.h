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

struct dbVector2{
	Vector2 p;
	Vector2 v;
};
struct dbVector3{
	Vector3 p;
	Vector3 v;
};

#endif /* MATHHELPER_H_ */
