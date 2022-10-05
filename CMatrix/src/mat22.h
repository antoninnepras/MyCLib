/**
 * @file mat22.h
 * @author Antonin Nepras
 * @brief 2x2 matrices
 * @version 0.1
 * @date 2022-08-14
 *
 * @copyright Copyright (c) 2022
 *
 */


#ifndef __mat22_h__
#define __mat22_h__


#include "vec2.h"


typedef struct
{
  double data[2][2];
} Mat22;


Mat22
mat22_init(double m00, double m01, double m10, double m11);


Mat22
mat22_id(void);


Vec2
mat22_rvec(Mat22 m, int r);


Vec2
mat22_cvec(Mat22 m, int c);


Mat22
mat22_add(Mat22 m1, Mat22 m2);


Mat22
mat22_sub(Mat22 m1, Mat22 m2);


Mat22
mat22_mul(Mat22 m, double s);


Mat22
mat22_div(Mat22 m, double s);


Mat22
mat22_mul_mat(Mat22 m1, Mat22 m2);


Mat22
mat22_transp(Mat22 m);


double
mat22_det(Mat22 m);


Mat22
mat22_adjoint(Mat22 m);


Mat22
mat22_inverse(Mat22 m);


Vec2
mat22_mul_vec(Mat22 m, Vec2 v);


#endif
