/**
 * @file Vec2.c
 * @author Antonin Nepras
 * @brief Vec2 structure implementation
 * @version 0.1
 * @date 2022-08-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "vec2.h"


Vec2
vec2_add(Vec2 v1, Vec2 v2)
{
  return (Vec2){ v1.x + v2.x, v1.y + v2.y };
}


Vec2
vec2_sub(Vec2 v1, Vec2 v2)
{
  return (Vec2){ v1.x - v2.x, v1.y - v2.y };
}


Vec2
vec2_mul(Vec2 v, double m)
{
  return (Vec2){ v.x * m, v.y * m };
}


Vec2
vec2_div(Vec2 v, double d)
{
  return (Vec2){ v.x / d, v.y / d };
}


double
vec2_dot(Vec2 v1, Vec2 v2)
{
  return v1.x * v2.x + v1.y * v2.y;
}


double
vec2_size(Vec2 v)
{
  return sqrt(vec2_dot(v, v));
}


Vec2
vec2_norm(Vec2 v)
{
  return vec2_div(v, vec2_size(v));
}


Vec2
vec2_rotate(Vec2 v, double rad)
{
  Vec2 rot;
  rot.x = cos(rad) * v.x - sin(rad) * v.y;
  rot.y = sin(rad) * v.x + cos(rad) * v.y;
  return rot;
}
