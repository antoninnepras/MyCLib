/**
 * @file svg.c
 * @author Antonin Nepras
 * @brief CSVG implementation
 * @version 0.1
 * @date 2022-08-12
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "svg.h"


long
slen(const char* str)
{
  long len = 1;
  long i = 0;
  while (str[i] != '\0') {
    ++len;
    ++i;
  }

  return len;
}


SVG_attr*
svg_attr_new(const char* name, const char* value)
{
  SVG_attr* attr = (SVG_attr*)malloc(sizeof(SVG_attr));
  strcpy(attr->name, name);

  long vlen = slen(value);

  attr->value = (char*)malloc(sizeof(char) * vlen);
  strcpy(attr->value, value);

  return attr;
}


void
svg_attr_del(SVG_attr* attr)
{
  free(attr->value);
  free(attr);
}


SVG_obj*
svg_obj_new(const char* name)
{
  SVG_obj* obj = (SVG_obj*)malloc(sizeof(SVG_obj));
  strcpy(obj->name, name);
  obj->attrs = list_new();
  obj->text = NULL;
  return obj;
}


void
svg_obj_del(SVG_obj* obj)
{
  while (obj->attrs->size > 0) {
    svg_attr_del((SVG_attr*)list_pop_back(obj->attrs));
  }
  list_del(obj->attrs);
  if(obj->text != NULL) {
    free(obj->text);
  }

  free(obj);
}


void
svg_obj_add_attr(SVG_obj* obj, SVG_attr* attr)
{
  list_append(obj->attrs, (void*)attr);
}


void
svg_obj_add_attr_new(SVG_obj* obj, const char* name, const char* value)
{
  list_append(obj->attrs, (void*)svg_attr_new(name, value));
}


void
svg_obj_add_text(SVG_obj* obj, const char* text)
{
  if (obj->text != NULL) {
    free(obj->text);
  }

  long tlen = slen(text);
  obj->text = (char*)malloc(tlen * sizeof(char));
  strcpy(obj->text, text);
}


SVG*
svg_new(double width, double heigth)
{
  SVG* svg = (SVG*)malloc(sizeof(SVG));
  svg->attrs = list_new();
  svg->objs = list_new();
  char sbox[64];
  sprintf(sbox, "0 0 %lf %lf", width, heigth);
  svg_add_attr_new(svg, "viewBox", sbox);

  return svg;
}


void
svg_del(SVG* svg)
{
  while (svg->attrs->size > 0) {
    svg_attr_del((SVG_attr*)list_pop_back(svg->attrs));
  }
  list_del(svg->attrs);

  while (svg->objs->size > 0) {
    svg_obj_del((SVG_obj*)list_pop_back(svg->objs));
  }
  list_del(svg->objs);

  free(svg);
}


void
svg_add_attr(SVG* svg, SVG_attr* attr)
{
  list_append(svg->attrs, (void*)attr);
}


void
svg_add_attr_new(SVG* svg, const char* name, const char* value)
{
  list_append(svg->attrs, (void*)svg_attr_new(name, value));
}


void
svg_add_obj(SVG* svg, SVG_obj* obj)
{
  list_append(svg->objs, (void*)obj);
}


void
svg_obj_fprint(FILE* fp, SVG_obj* obj)
{
  fprintf(fp, "<%s", obj->name);
  for (int i = 0; i < obj->attrs->size; ++i) {
    fprintf(fp, " %s=", ((SVG_attr*)list_get(obj->attrs, i))->name);
    fprintf(fp, "\"%s\"", ((SVG_attr*)list_get(obj->attrs, i))->value);
  }
  if (obj->text == NULL) {
    fprintf(fp, "/>\n");
  } else {
    fprintf(fp, ">\n");
    fprintf(fp, "%s\n", obj->text);
    fprintf(fp, "</%s>\n", obj->name);
  }
}


void
svg_export(SVG* svg, const char* name)
{
  FILE* fp = fopen(name, "w");
  if (fp == NULL) {
    return;
  }

  // svg open
  fprintf(fp, "<svg");
  for (int i = 0; i < svg->attrs->size; ++i) {
    fprintf(fp, " %s=", ((SVG_attr*)list_get(svg->attrs, i))->name);
    fprintf(fp, "\"%s\"", ((SVG_attr*)list_get(svg->attrs, i))->value);
  }
  fprintf(fp, ">\n");

  for (int i = 0; i < svg->objs->size; ++i) {
    svg_obj_fprint(fp, ((SVG_obj*)list_get(svg->objs, i)));
  }

  // svg clone
  fprintf(fp, "</svg>\n");

  fclose(fp);
}
