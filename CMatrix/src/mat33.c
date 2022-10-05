/**
 * @file mat33.c
 * @author Antonin Nepras
 * @brief 3x3 matrices
 * @version 0.1
 * @date 2022-08-16
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "mat33.h"


Mat33
mat33_init(double m00,
           double m01,
           double m02,
           double m10,
           double m11,
           double m12,
           double m20,
           double m21,
           double m22)
{
  Mat33 mr;
  mr.data[0][0] = m00;
  mr.data[0][1] = m01;
  mr.data[0][2] = m02;
  mr.data[1][0] = m10;
  mr.data[1][1] = m11;
  mr.data[1][2] = m12;
  mr.data[2][0] = m20;
  mr.data[2][1] = m21;
  mr.data[2][2] = m22;
  return mr;
}


Vec3
mat33_rvec(Mat33 m, int r)
{
  if (r < 0 || r > 2) {
    return (Vec3){ 0l, 0l, 0l };
  }

  return (Vec3){ m.data[r][0], m.data[r][1], m.data[r][2] };
}


Vec3
mat33_cvec(Mat33 m, int c)
{
  if (c < 0 || c > 2) {
    return (Vec3){ 0l, 0l, 0l };
  }

  return (Vec3){ m.data[0][c], m.data[1][c], m.data[2][c] };
}


Mat33
mat33_add(Mat33 m1, Mat33 m2)
{
  Mat33 mr;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      mr.data[i][j] = m1.data[i][j] + m2.data[i][j];
    }
  }

  return mr;
}


Mat33
mat33_sub(Mat33 m1, Mat33 m2)
{
  Mat33 mr;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      mr.data[i][j] = m1.data[i][j] - m2.data[i][j];
    }
  }

  return mr;
}


Mat33
mat33_mul(Mat33 m, double s)
{
  Mat33 mr;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      mr.data[i][j] = m.data[i][j] * s;
    }
  }

  return mr;
}


Mat33
mat33_div(Mat33 m, double s)
{
  Mat33 mr;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      mr.data[i][j] = m.data[i][j] / s;
    }
  }

  return mr;
}


Mat33
mat33_mul_mat(Mat33 m1, Mat33 m2)
{
  Mat33 mr;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      mr.data[i][j] = vec3_dot(mat33_rvec(m1, i), mat33_cvec(m2, j));
    }
  }

  return mr;
}


Mat33
mat33_transp(Mat33 m)
{
  Mat33 mr = m;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (i == j) {
        continue;
      }

      mr.data[i][j] = m.data[j][i];
    }
  }

  return mr;
}


double
mat33_det(Mat33 m)
{
  double det = 0;
  double sign = 1;
  for (int i = 0; i < 3; ++i) {
    det += sign * m.data[0][i] * mat22_det(mat33_mat22_withoutrc(m, 0, i));
    sign *= -1;
  }

  return det;
}


Mat22
mat33_mat22_withoutrc(Mat33 m, int r, int c)
{
  Mat22 mr;
  int i = 0;
  int k = 0;
  while (i < 2) {
    if (k == r) {
      ++k;
      continue;
    }

    int j = 0;
    int l = 0;
    while (j < 2) {
      if (l == c) {
        ++l;
        continue;
      }
      mr.data[i][j] = m.data[k][l];
      ++l;
      ++j;
    }

    ++k;
    ++i;
  }

  return mr;
}


Mat33
mat33_adjoint(Mat33 m)
{
  Mat33 mr;
  int sign = 1;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      mr.data[i][j] = sign * mat22_det(mat33_mat22_withoutrc(m, j, i));
      sign *= -1;
    }
  }

  return mr;
}


Mat33
mat33_inverse(Mat33 m)
{
  double det = mat33_det(m);
  if (det == 0) {
    return mat33_init(0, 0, 0, 0, 0, 0, 0, 0, 0);
  }

  return mat33_div(mat33_adjoint(m), det);
}


Vec3
mat33_mul_vec(Mat33 m, Vec3 v)
{
  Vec3 vr;
  vr.x = vec3_dot(v, mat33_rvec(m, 0));
  vr.y = vec3_dot(v, mat33_rvec(m, 1));
  vr.z = vec3_dot(v, mat33_rvec(m, 2));
  return vr;
}
