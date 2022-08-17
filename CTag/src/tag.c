/**
 * @file tag.c
 * @author Antonin Nepras
 * @brief Tag languages implementation
 * @version 0.1
 * @date 2022-08-17
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "tag.h"


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


Tag_attr*
tag_attr_new(const char* name, const char* value)
{
  Tag_attr* attr = (Tag_attr*)malloc(sizeof(Tag_attr));
  strcpy(attr->name, name);

  long vlen = slen(value);

  attr->value = (char*)malloc(sizeof(char) * vlen);
  strcpy(attr->value, value);

  return attr;
}


void
tag_attr_del(Tag_attr* attr)
{
  free(attr->value);
  free(attr);
}


Tag*
tag_new(const char* name)
{
  Tag* tag = (Tag*)malloc(sizeof(Tag));
  strcpy(tag->name, name);
  tag->attrs = list_new();
  tag->childs = list_new();
  tag->text = NULL;
  return tag;
}


void
tag_del(Tag* tag)
{
  while (tag->attrs->size > 0) {
    tag_attr_del((Tag_attr*)list_pop_back(tag->attrs));
  }
  while (tag->childs->size > 0) {
    tag_del((Tag*)list_pop_back(tag->childs));
  }
  list_del(tag->attrs);
  list_del(tag->childs);

  if (tag->text != NULL) {
    free(tag->text);
  }
  free(tag);
}


void
tag_add_attr(Tag* tag, Tag_attr* attr)
{
  list_append(tag->attrs, (void*)attr);
}


void
tag_add_attr_new(Tag* tag, const char* name, const char* value)
{
  list_append(tag->attrs, (void*)tag_attr_new(name, value));
}


void
tag_add_child(Tag* tag, Tag* child)
{
  list_append(tag->childs, (void*)child);
}


void
tag_set_text(Tag* tag, const char* text)
{
  if (tag->text != NULL) {
    free(tag->text);
  }

  long tlen = slen(text);
  tag->text = (char*)malloc(tlen * sizeof(char));
  strcpy(tag->text, text);
}


void
tag_fprint(FILE* fp, Tag* tag)
{
  // opening
  fprintf(fp, "<%s", tag->name);
  for (int i = 0; i < tag->attrs->size; ++i) {
    fprintf(fp, " %s=", ((Tag_attr*)list_get(tag->attrs, i))->name);
    fprintf(fp, "\"%s\"", ((Tag_attr*)list_get(tag->attrs, i))->value);
  }
  fprintf(fp, ">\n");

  // text
  if (tag->text != NULL) {
    fprintf(fp, "%s\n", tag->text);
  }

  // childs
  for (int i = 0; i < tag->childs->size; ++i) {
    tag_fprint(fp, (Tag*)list_get(tag->childs, i));
  }

  // closing
  fprintf(fp, "</%s>\n", tag->name);
}


void
tag_export(Tag* tag, const char* name)
{
  FILE* fp = fopen(name, "w");
  if (fp == NULL) {
    return;
  }

  tag_fprint(fp, tag);
  fclose(fp);
}
