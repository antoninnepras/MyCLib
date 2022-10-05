/**
 * @file mat44.h
 * @author Antonin Nepras
 * @brief 4x4 matrices
 * @version 0.1
 * @date 2022-10-05
 *
 * @copyright Copyright (c) 2022
 *
 */


#ifndef __mat44_h__
#define __mat44_h__

#include <stdio.h>

#include "mat33.h"
#include "vec4.h"


typedef struct
{
  double data[4][4];
} Mat44;


Mat44
mat44_init(double m00,
           double m01,
           double m02,
           double m03,
           double m10,
           double m11,
           double m12,
           double m13,
           double m20,
           double m21,
           double m22,
           double m23,
           double m30,
           double m31,
           double m32,
           double m33);


Mat44
mat44_id(void);


Vec4
mat44_rvec(Mat44 m, int r);


Vec4
mat44_cvec(Mat44 m, int c);


Mat44
mat44_add(Mat44 m1, Mat44 m2);


Mat44
mat44_sub(Mat44 m1, Mat44 m2);


Mat44
mat44_mul(Mat44 m, double s);


Mat44
mat44_div(Mat44 m, double s);


Mat44
mat44_mul_mat(Mat44 m1, Mat44 m2);


Mat44
mat44_transp(Mat44 m);


double
mat44_det(Mat44 m);


Mat33
mat44_mat33_withoutrc(Mat44 m, int r, int c);


Mat44
mat44_adjoint(Mat44 m);


Mat44
mat44_inverse(Mat44 m);


Vec4
mat44_mul_vec(Mat44 m, Vec4 v);

#endif
