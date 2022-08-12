/**
 * @file svg_primitives.h
 * @author Antonin Nepras
 * @brief Primitives for CSVG
 * @version 0.1
 * @date 2022-08-12
 *
 * @copyright Copyright (c) 2022
 *
 */


#ifndef __svg_primitives_h__
#define __svg_primitives_h__


#include "svg.h"
#include "vec2.h"


SVG_obj*
svg_obj_new_rect(double x, double y, double w, double h);


SVG_obj*
svg_obj_new_rect_round(double x,
                       double y,
                       double w,
                       double h,
                       double rx,
                       double ry);


SVG_obj*
svg_obj_new_circle(double cx, double cy, double r);


SVG_obj*
svg_obj_new_elipse(double cx, double cy, double rx, double ry);


SVG_obj*
svg_obj_new_line(double x1, double y1, double x2, double y2);


SVG_obj*
svg_obj_new_polygonv(Vec2* points, int count);


SVG_obj*
svg_obj_new_polylinev(Vec2* points, int count);


SVG_obj*
svg_obj_new_text(double x, double y, const char* text);

#endif
