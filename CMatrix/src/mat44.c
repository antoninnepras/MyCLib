/**
 * @file mat44.c
 * @author yAntonin Nepras
 * @brief 4x4 matrices implementaion
 * @version 0.1
 * @date 2022-10-05
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "mat44.h"


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
           double m33)
{
  Mat44 m;
  m.data[0][0] = m00;
  m.data[0][1] = m01;
  m.data[0][2] = m02;
  m.data[0][3] = m03;
  m.data[1][0] = m10;
  m.data[1][1] = m11;
  m.data[1][2] = m12;
  m.data[1][3] = m13;
  m.data[2][0] = m20;
  m.data[2][1] = m21;
  m.data[2][2] = m22;
  m.data[2][3] = m23;
  m.data[3][0] = m30;
  m.data[3][1] = m31;
  m.data[3][2] = m32;
  m.data[3][3] = m33;
  return m;
}


Vec4
mat44_rvec(Mat44 m, int r)
{
  if (r < 0 || r > 3) {
    return (Vec4){ 0l, 0l, 0l, 0l };
  }

  return (Vec4){ m.data[r][0], m.data[r][1], m.data[r][2], m.data[r][4] };
}


Vec4
mat44_cvec(Mat44 m, int c)
{
  if (c < 0 || c > 3) {
    return (Vec4){ 0l, 0l, 0l, 0l };
  }

  return (Vec4){ m.data[0][c], m.data[1][c], m.data[2][c], m.data[3][c] };
}


Mat44
mat44_add(Mat44 m1, Mat44 m2)
{
  Mat44 mr;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      mr.data[i][j] = m1.data[i][j] + m2.data[i][j];
    }
  }

  return mr;
}


Mat44
mat44_sub(Mat44 m1, Mat44 m2)
{
  Mat44 mr;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      mr.data[i][j] = m1.data[i][j] - m2.data[i][j];
    }
  }

  return mr;
}


Mat44
mat44_mul(Mat44 m, double s)
{
  Mat44 mr;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      mr.data[i][j] = m.data[i][j] * s;
    }
  }

  return mr;
}


Mat44
mat44_div(Mat44 m, double s)
{
  Mat44 mr;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      mr.data[i][j] = m.data[i][j] / s;
    }
  }

  return mr;
}


Mat44
mat44_mul_mat(Mat44 m1, Mat44 m2)
{
  Mat44 mr;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      mr.data[i][j] = vec4_dot(mat44_rvec(m1, i), mat44_cvec(m2, j));
    }
  }

  return mr;
}


Mat44
mat44_transp(Mat44 m)
{
  Mat44 mr = m;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (i == j) {
        continue;
      }

      mr.data[i][j] = m.data[j][i];
    }
  }

  return mr;
}


double
mat44_det(Mat44 m)
{
  double det = 0;
  int sign = 1;
  for (int i = 0; i < 4; ++i) {
    det += sign * m.data[0][i] * mat33_det(mat44_mat33_withoutrc(m, 0, i));
    sign *= -1;
  }

  return det;
}


Mat33
mat44_mat33_withoutrc(Mat44 m, int r, int c)
{
  Mat33 mr;
  int i = 0;
  int k = 0;
  while (i < 3) {
    if (k == r) {
      ++k;
      continue;
    }

    int j = 0;
    int l = 0;
    while (j < 3) {
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


Mat44
mat44_adjoint(Mat44 m)
{
  Mat44 mr;
  int sign = 1;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      mr.data[i][j] = sign * mat33_det(mat44_mat33_withoutrc(m, j, i));
      sign *= -1;
    }
  }

  return mr;
}


Mat44
mat44_inverse(Mat44 m)
{
  double det = mat44_det(m);
  if (det == 0) {
    return mat44_init(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  }

  return mat44_div(mat44_adjoint(m), det);
}


Vec4
mat44_mul_vec(Mat44 m, Vec4 v)
{
  Vec4 vr;
  vr.x = vec4_dot(v, mat44_rvec(m, 0));
  vr.y = vec4_dot(v, mat44_rvec(m, 1));
  vr.z = vec4_dot(v, mat44_rvec(m, 2));
  vr.w = vec4_dot(v, mat44_rvec(m, 3));
  return vr;
}
