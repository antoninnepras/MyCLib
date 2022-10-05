/**
 * @file mat33.h
 * @author Antonin Nepras
 * @brief 3x3 matrices
 * @version 0.1
 * @date 2022-08-16
 *
 * @copyright Copyright (c) 2022
 *
 */


#ifndef __mat33_h__
#define __mat33_h__

#include <stdio.h>

#include "mat22.h"
#include "vec3.h"


typedef struct
{
  double data[3][3];
} Mat33;


Mat33
mat33_init(double m00,
           double m01,
           double m02,
           double m10,
           double m11,
           double m12,
           double m20,
           double m21,
           double m22);


Mat33
mat33_id(void);


Vec3
mat33_rvec(Mat33 m, int r);


Vec3
mat33_cvec(Mat33 m, int c);


Mat33
mat33_add(Mat33 m1, Mat33 m2);


Mat33
mat33_sub(Mat33 m1, Mat33 m2);


Mat33
mat33_mul(Mat33 m, double s);


Mat33
mat33_div(Mat33 m, double s);


Mat33
mat33_mul_mat(Mat33 m1, Mat33 m2);


Mat33
mat33_transp(Mat33 m);


double
mat33_det(Mat33 m);


Mat22
mat33_mat22_withoutrc(Mat33 m, int r, int c);


Mat33
mat33_adjoint(Mat33 m);


Mat33
mat33_inverse(Mat33 m);


Vec3
mat33_mul_vec(Mat33 m, Vec3 v);


#endif
