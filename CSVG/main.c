/**
 * @file main.c
 * @author Antonin Nepras
 * @brief Test file for CSVG
 * @version 0.1
 * @date 2022-08-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "src/svg.h"
#include "src/svg_primitives.h"


int
main(int argc, const char** argv)
{
  // svg canvas
  SVG* canvas = svg_new(500, 500);

  // manual set object
  SVG_obj* tmp = svg_obj_new("circle");
  svg_obj_add_attr_new(tmp, "cx", "300");
  svg_obj_add_attr_new(tmp, "cy", "200");
  svg_obj_add_attr_new(tmp, "r", "150");

  // add object
  svg_add_obj(canvas, tmp);

  // rounded rectangle primitive
  svg_add_obj(canvas, svg_obj_new_rect_round(20, 60, 100, 200, 50, 50));

  // prepare path
  Vec2 points[30];
  for (int i = 0; i < 30; ++i) {
    points[i] = (Vec2){ (double)(5 * i + 5), (double)(i * i) };
  }

  // polyline primitive
  tmp = svg_obj_new_polylinev(points, 30);
  svg_obj_add_attr_new(tmp, "style", "fill:none;stroke:red;stroke-width:5");
  svg_add_obj(canvas, tmp);

  // text primitive
  tmp = svg_obj_new_text(50, 50, "Hello world!");
  svg_obj_add_attr_new(tmp, "style", "fill:blue;font-size:40");
  svg_add_obj(canvas, tmp);

  // export canvas to file 
  svg_export(canvas, "canvas.svg");

  // delete svg
  svg_del(canvas);
  return 0;
}
