/**
 * @file main.c
 * @author Antonin Nepras
 * @brief
 * @version 0.1
 * @date 2022-08-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>

#include "src/kinematics2.h"
#include "src/kinematics3.h"
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


/**
 * @brief Export path to svg file
 *
 * @param path
 * @param size
 * @param file
 */
void
exp_path2_to_svg(Vec2* path, int size, const char* file);


int
main(int argc, const char** argv)
{
  // prepare position and velocity
  Kin2 k2;
  k2.pos = (Vec2){ 0l, 0l };
  k2.vel = (Vec2){ 0l, 0l };

  double time_step = 1;
  double dist = 0;
  double dist_step;

  Vec2 path[15];

  k2.acc = (Vec2){ 10l, 0l };
  for (int i = 0; i < 5; ++i) {
    kin2_move_dist(&k2, time_step, &dist_step);
    dist += dist_step;

    printf("pos: ");
    vec2_print(k2.pos);
    path[i] = k2.pos;
  }

  k2.acc = (Vec2){ -10l, 10l };
  for (int i = 0; i < 5; ++i) {
    kin2_move_dist(&k2, time_step, &dist_step);
    dist += dist_step;

    printf("pos: ");
    vec2_print(k2.pos);
    path[i + 5] = k2.pos;
  }

  k2.acc = (Vec2){ -20l, -20l };
  for (int i = 0; i < 5; ++i) {
    kin2_move_dist(&k2, time_step, &dist_step);
    dist += dist_step;

    printf("pos: ");
    vec2_print(k2.pos);
    path[i + 10] = k2.pos;
  }

  exp_path2_to_svg(path, 15, "path.svg");

  printf("dist: %lf\n", dist);
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
exp_path2_to_svg(Vec2* path, int size, const char* file)
{
  if (path == NULL || size < 0 || file == NULL) {
    return;
  }

  const double border = 5;

  double maxx = -INFINITY;
  double minx = INFINITY;
  double maxy = -INFINITY;
  double miny = INFINITY;

  for (int i = 0; i < size; ++i) {
    if (path[i].x > maxx)
      maxx = path[i].x;
    if (path[i].x < minx)
      minx = path[i].x;
    if (path[i].y > maxy)
      maxy = path[i].y;
    if (path[i].y < miny)
      miny = path[i].y;
  }

  FILE* fp = fopen(file, "w");
  if (fp == NULL) {
    return;
  }

  double heigth = maxy - miny + 2 * border;
  double width = maxx - minx + 2 * border;
  fprintf(fp, "<svg height=\"%lf\" width=\"%lf\">\n", heigth, width);
  fprintf(fp, "<rect width=\"100%%\" height=\"100%%\" fill=\"black\" />\n");
  fprintf(fp, "<polyline points=\"");
  for (int i = 0; i < size; ++i) {
    fprintf(
      fp, "%lf,%lf ", path[i].x - minx + border, path[i].y - miny + border);
  }
  fprintf(fp, "\"\n");
  fprintf(fp, "style=\"fill:transparent;stroke:red;stroke-width:1\" />\n");
  fprintf(fp, "</svg>");

  fclose(fp);
}
