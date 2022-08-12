/**
 * @file main.c
 * @author Antonin Nepras
 * @brief CDynamics test main
 * @version 0.1
 * @date 2022-08-12
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "src/dynamics2.h"
#include <stdio.h>


/**
 * @brief Vector print
 *
 * @param v
 */
void
vec2_print(Vec2 v);


/**
 * @brief Export path to svg file
 *
 * @param path
 * @param size
 * @param file
 */
void
exp_path2_to_svg(Vec2* path, int size, const char* file, const char* color);


int
main(int argc, const char** argv)
{
  // prepare dynamics
  Dyn2 dyn;
  dyn.kin.pos = (Vec2){ 0l, 0l };
  dyn.kin.vel = (Vec2){ 10l, 0l };
  dyn.kin.acc = (Vec2){ 0l, 0l };
  dyn.mass = 5l;

  // prepare force field
  FF2Central fc;
  fc.dpower = 2;
  fc.intensity = 5000;
  fc.pos = (Vec2){ 20l, 5l };

  int steps = 200;
  double step_time = 0.01;
  Vec2 path[steps];

  for (int i = 0; i < steps; ++i) {
    dyn.kin.acc = (Vec2){ 0l, 0l };
    dyn2_apply_ffcentral(&dyn, fc);
    dyn2_move(&dyn, step_time);
    path[i] = dyn.kin.pos;
    vec2_print(path[i]);
  }

  exp_path2_to_svg(path, steps, "path.svg", "red");

  return 0;
}


void
vec2_print(Vec2 v)
{
  printf("[%lf; %lf]\n", v.x, v.y);
}


void
exp_path2_to_svg(Vec2* path, int size, const char* file, const char* color)
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
      fp, "%lf,%lf ", path[i].x + minx - border, path[i].y - miny + border);
  }
  fprintf(fp, "\"\n");
  fprintf(
    fp, "style=\"fill:transparent;stroke:%s;stroke-width:1\" />\n", color);
  fprintf(fp, "</svg>");

  fclose(fp);
}
