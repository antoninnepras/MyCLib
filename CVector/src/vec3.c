/**
 * @file Vec3.h
 * @author Antonin Nepras
 * @brief Vec3 structure implementation
 * @version 0.1
 * @date 2022-08-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "vec3.h"


Vec3
vec3_add(Vec3 v1, Vec3 v2)
{
  return (Vec3){ v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}


Vec3
vec3_sub(Vec3 v1, Vec3 v2)
{
  return (Vec3){ v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}


Vec3
vec3_mul(Vec3 v, double m)
{
  return (Vec3){ v.x * m, v.y * m, v.z * m };
}


Vec3
vec3_div(Vec3 v, double d)
{
  return (Vec3){ v.x / d, v.y / d, v.z / d };
}


double
vec3_dot(Vec3 v1, Vec3 v2)
{
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


Vec3
vec3_cross(Vec3 v1, Vec3 v2)
{
  return (Vec3){
    v1.y * v2.z - v1.z * v2.y,
    v1.z * v2.x - v1.x * v2.z,
    v1.x * v2.y - v1.y * v2.x
  };
}


double
vec3_size(Vec3 v)
{
  return sqrt(vec3_dot(v, v));
}


Vec3
vec3_norm(Vec3 v)
{
  return vec3_div(v, vec3_size(v));
}
