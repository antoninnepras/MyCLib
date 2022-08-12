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
 * @brief Export paths to svg
 * 
 * @param path1 
 * @param path2 
 * @param size 
 * @param file 
 * @param color1 
 * @param color2 
 */
void
exp_path2s_to_svg(Vec2* path1,
                  Vec2* path2,
                  int size,
                  const char* file,
                  const char* color1, 
                  const char* color2);


int
main(int argc, const char** argv)
{
  // prepare dynamics
  Dyn2 dyn1;
  dyn1.kin.pos = (Vec2){ 0l, 0l };
  dyn1.kin.vel = (Vec2){ 8l, 0l };
  dyn1.kin.acc = (Vec2){ 0l, 0l };
  dyn1.mass = 10l;

  Dyn2 dyn2;
  dyn2.kin.pos = (Vec2){ 30l, 5l };
  dyn2.kin.vel = (Vec2){ -3l, 0l };
  dyn2.kin.acc = (Vec2){ 0l, 0l };
  dyn2.mass = 7l;

  // prepare force fields
  FF2Central fc1;
  fc1.dpower = 2;
  fc1.intensity = 300 * dyn1.mass;
  fc1.pos = dyn1.kin.pos;

  FF2Central fc2;
  fc2.dpower = 2;
  fc2.intensity = 300 * dyn2.mass;
  fc2.pos = dyn2.kin.pos;

  int steps = 800;
  double step_time = 0.01;
  Vec2 path1[steps];
  Vec2 path2[steps];

  for (int i = 0; i < steps; ++i) {
    dyn1.kin.acc = (Vec2){ 0l, 0l };
    dyn2.kin.acc = (Vec2){ 0l, 0l };
    dyn2_apply_ffcentral(&dyn1, fc2);
    dyn2_apply_ffcentral(&dyn2, fc1);
    dyn2_move(&dyn1, step_time);
    dyn2_move(&dyn2, step_time);
    fc1.pos = dyn1.kin.pos;
    fc2.pos = dyn2.kin.pos;

    path1[i] = dyn1.kin.pos;
    path2[i] = dyn2.kin.pos;
  }

  exp_path2s_to_svg(path1, path2, steps, "path.svg", "red", "blue");

  return 0;
}


void
vec2_print(Vec2 v)
{
  printf("[%lf; %lf]\n", v.x, v.y);
}


void
exp_path2s_to_svg(Vec2* path1,
                  Vec2* path2,
                  int size,
                  const char* file,
                  const char* color1, 
                  const char* color2)
{
  if (path1 == NULL || path2 == NULL || size < 0 || file == NULL) {
    return;
  }

  const double border = 5;

  double maxx = -INFINITY;
  double minx = INFINITY;
  double maxy = -INFINITY;
  double miny = INFINITY;

  for (int i = 0; i < size; ++i) {
    if (path1[i].x > maxx)
      maxx = path1[i].x;
    if (path1[i].x < minx)
      minx = path1[i].x;
    if (path1[i].y > maxy)
      maxy = path1[i].y;
    if (path1[i].y < miny)
      miny = path1[i].y;
    if (path2[i].x > maxx)
      maxx = path2[i].x;
    if (path2[i].x < minx)
      minx = path2[i].x;
    if (path2[i].y > maxy)
      maxy = path2[i].y;
    if (path2[i].y < miny)
      miny = path2[i].y;
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
      fp, "%lf,%lf ", path1[i].x - minx + border, path1[i].y - miny + border);
  }
  fprintf(fp, "\"\n");
  fprintf(
    fp, "style=\"fill:transparent;stroke:%s;stroke-width:1\" />\n", color1);

  fprintf(fp, "<polyline points=\"");
  for (int i = 0; i < size; ++i) {
    fprintf(
      fp, "%lf,%lf ", path2[i].x - minx + border, path2[i].y - miny + border);
  }
  fprintf(fp, "\"\n");
  fprintf(
    fp, "style=\"fill:transparent;stroke:%s;stroke-width:1\" />\n", color2);
  fprintf(fp, "</svg>");

  fclose(fp);
}
