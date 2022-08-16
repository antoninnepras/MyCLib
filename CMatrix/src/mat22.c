/**
 * @file mat22.c
 * @author Antonin Nepras
 * @brief 2x2 matrices implementation
 * @version 0.1
 * @date 2022-08-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "mat22.h"


Mat22
mat22_init(double m00, double m01, double m10, double m11)
{
  Mat22 mr;
  mr.data[0][0] = m00;
  mr.data[0][1] = m01;
  mr.data[1][0] = m10;
  mr.data[1][1] = m11;
  return mr;
}


Vec2
mat22_rvec(Mat22 m, int r)
{
  if (r < 0 || r > 1) {
    return (Vec2){ 0l, 0l };
  }

  return (Vec2){ m.data[r][0], m.data[r][1] };
}


Vec2
mat22_cvec(Mat22 m, int c)
{
  if (c < 0 || c > 1) {
    return (Vec2){ 0l, 0l };
  }

  return (Vec2){ m.data[0][c], m.data[1][c] };
}


Mat22
mat22_add(Mat22 m1, Mat22 m2)
{
  Mat22 mr;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      mr.data[i][j] = m1.data[i][j] + m2.data[i][j];
    }
  }

  return mr;
}


Mat22
mat22_sub(Mat22 m1, Mat22 m2)
{
  Mat22 mr;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      mr.data[i][j] = m1.data[i][j] - m2.data[i][j];
    }
  }

  return mr;
}


Mat22
mat22_mul(Mat22 m, double s)
{
  Mat22 mr;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      mr.data[i][j] = m.data[i][j] * s;
    }
  }

  return mr;
}


Mat22
mat22_div(Mat22 m, double s)
{
  Mat22 mr;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      mr.data[i][j] = m.data[i][j] / s;
    }
  }

  return mr;
}


Mat22
mat22_mul_mat(Mat22 m1, Mat22 m2)
{
  Mat22 mr;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      mr.data[i][j] = vec2_dot(mat22_rvec(m1, i), mat22_cvec(m2, j));
    }
  }

  return mr;
}


Mat22
mat22_transp(Mat22 m)
{
  Mat22 mr = m;
  double tmp = mr.data[0][0];
  mr.data[0][0] = mr.data[1][1];
  mr.data[1][1] = tmp;
  return mr;
}


double
mat22_det(Mat22 m)
{
  return m.data[0][0] * m.data[1][1] - m.data[0][1] * m.data[1][0];
}


Mat22
mat22_adjoint(Mat22 m)
{
  Mat22 mr;
  mr.data[0][0] = m.data[1][1];
  mr.data[0][1] = -m.data[0][1];
  mr.data[1][0] = -m.data[1][0];
  mr.data[1][1] = m.data[0][0];
  return mr;
}


Mat22
mat22_inverse(Mat22 m)
{
  double det = mat22_det(m);
  if (det == 0) {
    return mat22_init(0, 0, 0, 0);
  }

  return mat22_div(mat22_adjoint(m), det);
}


Vec2 
mat22_mul_vec(Mat22 m, Vec2 v)
{
  Vec2 vr;
  vr.x = vec2_dot(v, mat22_rvec(m, 0));
  vr.y = vec2_dot(v, mat22_rvec(m, 1));
  return vr;
}
