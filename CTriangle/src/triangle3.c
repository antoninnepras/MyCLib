/**
 * @file triangle3.c
 * @author Antonin Nepras
 * @brief 3D triangles implementation
 * @version 0.1
 * @date 2022-10-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "triangle3.h"


Triangle3
triangle3_init(Vec3 v1, Vec3 v2, Vec3 v3)
{
  Triangle3 t;
  t.vertices[0] = v1;
  t.vertices[1] = v2;
  t.vertices[2] = v3;
  return t;
}


Triangle3
triangle3_move(Triangle3 t, Vec3 v)
{
  Triangle3 res;
  for (int i = 0; i < 3; ++i) {
    res.vertices[i] = vec3_add(t.vertices[i], v);
  }

  return res;
}


Triangle3
triangle3_tansform(Triangle3 t, Mat33 m)
{
  Triangle3 res;
  for (int i = 0; i < 3; ++i) {
    res.vertices[i] = mat33_mul_vec(m, t.vertices[i]);
  }

  return res;
}


Vec3
triangle3_normal(Triangle3 t)
{
  Vec3 tmp1 = vec3_sub(t.vertices[1], t.vertices[0]);
  Vec3 tmp2 = vec3_sub(t.vertices[2], t.vertices[1]);
  return vec3_norm(vec3_cross(tmp1, tmp2));
}
