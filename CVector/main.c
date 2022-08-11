/**
 * @file main.c
 * @author Antonin Nepras
 * @brief CVector test file
 * @version 0.1
 * @date 2022-08-11
 *
 * @copyright Copyright (c) 2022
 *
 */


#include <stdio.h>

#include "src/vec2.h"
#include "src/vec3.h"


/**
 * @brief Vector print
 *
 * @param v
 */
void
vec2_print(Vec2 v);


/**
 * @brief Vector print
 *
 * @param v
 */
void
vec3_print(Vec3 v);


int
main(int argc, const char** argv)
{
  Vec2 a2 = (Vec2){ 2l, 4l };
  Vec2 b2 = (Vec2){ -3l, 5l };
  vec2_print(a2);
  vec2_print(b2);

  printf("add: \t");
  vec2_print(vec2_add(a2, b2));

  printf("sub: \t");
  vec2_print(vec2_sub(a2, b2));

  printf("mul: \t");
  vec2_print(vec2_mul(a2, 3));

  printf("div: \t");
  vec2_print(vec2_div(a2, 3));

  printf("dot: \t");
  printf("%lf\n", vec2_dot(a2, b2));

  printf("size: \t");
  printf("%lf\n", vec2_size(a2));

  printf("norm: \t");
  vec2_print(vec2_norm(a2));

  printf("rot: \t");
  vec2_print(vec2_rotate(a2, M_PI / 2));


  Vec3 a3 = (Vec3){ 2l, 4l, -3l};
  Vec3 b3 = (Vec3){ -3l, 5l, 2l };
  vec3_print(a3);
  vec3_print(b3);

  printf("add: \t");
  vec3_print(vec3_add(a3, b3));

  printf("sub: \t");
  vec3_print(vec3_sub(a3, b3));

  printf("mul: \t");
  vec3_print(vec3_mul(a3, 3));

  printf("div: \t");
  vec3_print(vec3_div(a3, 3));

  printf("dot: \t");
  printf("%lf\n", vec3_dot(a3, b3));

  printf("cross: \t");
  vec3_print(vec3_cross(a3, b3));

  printf("size: \t");
  printf("%lf\n", vec3_size(a3));

  printf("norm: \t");
  vec3_print(vec3_norm(a3));


  return 0;
}


void
vec2_print(Vec2 v)
{
  printf("[%lf; %lf]\n", v.x, v.y);
}

void
vec3_print(Vec3 v)
{
  printf("[%lf; %lf; %lf]\n", v.x, v.y, v.z);
}
