/**
 * @file svg_primitives.c
 * @author Antonin Nepras
 * @brief Primitives for CSVG implementation
 * @version 0.1
 * @date 2022-08-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "svg_primitives.h"


SVG_obj*
svg_obj_new_rect(double x, double y, double w, double h)
{
  SVG_obj* obj = svg_obj_new("rect");
  char sx[64];
  char sy[64];
  char sw[64];
  char sh[64];
  sprintf(sx, "%lf", x);
  sprintf(sy, "%lf", y);
  sprintf(sw, "%lf", w);
  sprintf(sh, "%lf", h);
  svg_obj_add_attr_new(obj, "x", sx);
  svg_obj_add_attr_new(obj, "y", sy);
  svg_obj_add_attr_new(obj, "width", sw);
  svg_obj_add_attr_new(obj, "height", sh);
  return obj;
}


SVG_obj*
svg_obj_new_rect_round(double x,
                       double y,
                       double w,
                       double h,
                       double rx,
                       double ry)
{
  SVG_obj* obj = svg_obj_new_rect(x, y, w, h);
  char srx[64];
  char sry[64];
  sprintf(srx, "%lf", rx);
  sprintf(sry, "%lf", ry);
  svg_obj_add_attr_new(obj, "rx", srx);
  svg_obj_add_attr_new(obj, "ry", sry);
  return obj;
}


SVG_obj*
svg_obj_new_circle(double cx, double cy, double r)
{
  SVG_obj* obj = svg_obj_new("circle");
  char scx[64];
  char scy[64];
  char sr[64];
  sprintf(scx, "%lf", cx);
  sprintf(scy, "%lf", cy);
  sprintf(sr, "%lf", r);
  svg_obj_add_attr_new(obj, "cx", scx);
  svg_obj_add_attr_new(obj, "cy", scy);
  svg_obj_add_attr_new(obj, "r", sr);
  return obj;
}


SVG_obj*
svg_obj_new_elipse(double cx, double cy, double rx, double ry)
{
  SVG_obj* obj = svg_obj_new("elipse");
  char scx[64];
  char scy[64];
  char srx[64];
  char sry[64];
  sprintf(scx, "%lf", cx);
  sprintf(scy, "%lf", cy);
  sprintf(srx, "%lf", rx);
  sprintf(sry, "%lf", ry);
  svg_obj_add_attr_new(obj, "cx", scx);
  svg_obj_add_attr_new(obj, "cy", scy);
  svg_obj_add_attr_new(obj, "rx", srx);
  svg_obj_add_attr_new(obj, "ry", sry);
  return obj;
}


SVG_obj*
svg_obj_new_line(double x1, double y1, double x2, double y2)
{
  SVG_obj* obj = svg_obj_new("line");
  char sx1[64];
  char sy1[64];
  char sx2[64];
  char sy2[64];
  sprintf(sx1, "%lf", x1);
  sprintf(sy1, "%lf", y1);
  sprintf(sx2, "%lf", x2);
  sprintf(sy2, "%lf", y2);
  svg_obj_add_attr_new(obj, "x1", sx1);
  svg_obj_add_attr_new(obj, "y1", sy1);
  svg_obj_add_attr_new(obj, "x2", sx2);
  svg_obj_add_attr_new(obj, "y2", sy2);
  return obj;
}


SVG_obj*
svg_obj_new_polygonv(Vec2* points, int count)
{
  int lens[count];
  char vals[count][64];
  long len = 1;
  for (int i = 0; i < count; ++i) {
    sprintf(vals[i], "%lf,%lf ", points[i].x, points[i].y);
    lens[i] = strlen(vals[i]);
    len += lens[i];
  }

  char attr[len];
  attr[0] = '\0';

  for (int i = 0; i < count; ++i) {
    strcat(attr, vals[i]);
  }

  SVG_obj* obj = svg_obj_new("polygon");
  svg_obj_add_attr_new(obj, "points", attr);
  return obj;
}


SVG_obj*
svg_obj_new_polylinev(Vec2* points, int count)
{
  int lens[count];
  char vals[count][64];
  long len = 1;
  for (int i = 0; i < count; ++i) {
    sprintf(vals[i], "%lf,%lf ", points[i].x, points[i].y);
    lens[i] = strlen(vals[i]);
    len += lens[i];
  }

  char attr[len];
  attr[0] = '\0';

  for (int i = 0; i < count; ++i) {
    strcat(attr, vals[i]);
  }

  SVG_obj* obj = svg_obj_new("polyline");
  svg_obj_add_attr_new(obj, "points", attr);
  return obj;
}


SVG_obj*
svg_obj_new_text(double x, double y, const char* text)
{
  SVG_obj* obj = svg_obj_new("text");
  char sx[64];
  char sy[64];
  sprintf(sx, "%lf", x);
  sprintf(sy, "%lf", y);
  svg_obj_add_attr_new(obj, "x", sx);
  svg_obj_add_attr_new(obj, "y", sy);
  svg_obj_add_text(obj, text);
  return obj;
}
