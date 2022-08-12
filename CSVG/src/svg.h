/**
 * @file svg.h
 * @author Antonin Nepras
 * @brief CSVG
 * @version 0.1
 * @date 2022-08-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __svg_h__
#define __svg_h__


#include <stdio.h>
#include <string.h>

#include "list.h"


typedef struct
{
  char name[64];
  char* value;
} SVG_attr;


typedef struct
{
  char name[16];
  List* attrs;
  char* text;
} SVG_obj;


typedef struct
{
  List* attrs;
  List* objs;
} SVG;


SVG_attr*
svg_attr_new(const char* name, const char* value);


void
svg_attr_del(SVG_attr* attr);


SVG_obj*
svg_obj_new(const char* name);


void
svg_obj_del(SVG_obj* obj);


void
svg_obj_add_attr(SVG_obj* obj, SVG_attr* attr);


void
svg_obj_add_attr_new(SVG_obj* obj, const char* name, const char* value);


void
svg_obj_add_text(SVG_obj* obj, const char* text);


SVG*
svg_new(double width, double heigth);


void
svg_del(SVG* svg);


void
svg_add_attr(SVG* svg, SVG_attr* attr);


void
svg_add_attr_new(SVG* svg, const char* name, const char* value);


void
svg_add_obj(SVG* svg, SVG_obj* obj);


void
svg_export(SVG* svg, const char* name);


#endif
