/**
 * @file main.c
 * @author Antonin Nepras
 * @brief
 * @version 0.1
 * @date 2022-10-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "src/triangle2.h"
#include "src/triangle3.h"

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


/**
 * @brief Triangle print
 *
 * @param t
 */
void
triagle2_print(Triangle2 t);


/**
 * @brief Triangle print
 *
 * @param t
 */
void
triagle3_print(Triangle3 t);


int
main(int argc, const char** argv)
{
  Triangle3 t = triangle3_init(
    (Vec3){ 0.0, 0.0, 0.0 }, (Vec3){ 0.0, 1.0, 0.0 }, (Vec3){ 0.0, 0.0, 1.0 });

  Vec3 n = triangle3_normal(t);
  vec3_print(n);
  Mat33 m = mat33_init(1, 0, 1, 0, 1, 1, 0, -2, 2);
  triagle3_print(t);
  t = triangle3_tansform(t, m);
  triagle3_print(t);


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


void
triagle2_print(Triangle2 t)
{
  printf("{\n");
  for (int i = 0; i < 2; ++i) {
    printf("  ");
    vec2_print(t.vertices[i]);
  }
  printf("}\n");
}


void
triagle3_print(Triangle3 t)
{
  printf("{\n");
  for (int i = 0; i < 3; ++i) {
    printf("  ");
    vec3_print(t.vertices[i]);
  }
  printf("}\n");
}
