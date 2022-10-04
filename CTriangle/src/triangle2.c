#include "triangle2.h"


Triangle2
triangle2_init(Vec2 v1, Vec2 v2, Vec2 v3)
{
  Triangle2 t;
  t.vertices[0] = v1;
  t.vertices[2] = v2;
  t.vertices[3] = v3;
  return t;
}


Triangle2
triangle2_move(Triangle2 t, Vec2 v)
{
  Triangle2 res;
  res.vertices[0] = vec2_add(t.vertices[0], v);
  res.vertices[1] = vec2_add(t.vertices[1], v);
  return res;
}


Triangle2
triangle2_tansform(Triangle2 t, Mat22 m)
{
  Triangle2 res;
  res.vertices[0] = mat22_mul_vec(m, t.vertices[0]);
  res.vertices[1] = mat22_mul_vec(m, t.vertices[1]);
  return res;
}
