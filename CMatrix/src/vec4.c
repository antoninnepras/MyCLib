/**
 * @file vec4.c
 * @author Antonin Nepras
 * @brief Vec4 structure implementation
 * @version 0.1
 * @date 2022-10-05
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "vec4.h"


Vec4
vec4_init(double x, double y, double z, double w)
{
  return (Vec4){ x, y, z, w };
}


Vec4
vec4_add(Vec4 v1, Vec4 v2)
{
  return (Vec4){ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w };
}


Vec4
vec4_sub(Vec4 v1, Vec4 v2)
{
  return (Vec4){ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w };
}


Vec4
vec4_mul(Vec4 v, double m)
{
  return (Vec4){ v.x * m, v.y * m, v.z * m, v.w * m };
}


Vec4
vec4_div(Vec4 v, double d)
{
  return (Vec4){ v.x / d, v.y / d, v.z / d, v.w / d };
}


double
vec4_dot(Vec4 v1, Vec4 v2)
{
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}


double
vec4_size(Vec4 v)
{
  return sqrt(vec4_dot(v, v));
}


Vec4
vec4_norm(Vec4 v)
{
  return vec4_div(v, vec4_size(v));
}
