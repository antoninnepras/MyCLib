/**
 * @file tag.h
 * @author Antonin Nepras
 * @brief Tag languages
 * @version 0.1
 * @date 2022-08-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef __tag_h__
#define __tag_h__

#include <stdio.h>
#include <string.h>

#include "list.h"

#define TAG_NAME_LEN 64
#define TAG_ATTR_NAME_LEN 64


typedef struct
{
  char name[64];
  char* value;
} Tag_attr;



typedef struct 
{
  char name[TAG_NAME_LEN];
  List* attrs;
  List* childs;
  char* text;
} Tag;


Tag_attr*
tag_attr_new(const char* name, const char* value);


void
tag_attr_del(Tag_attr* attr);


Tag*
tag_new(const char* name);


void
tag_del(Tag* tag);


void
tag_add_attr(Tag* tag, Tag_attr* attr);


void
tag_add_attr_new(Tag* tag, const char* name, const char* value);


void
tag_add_child(Tag* tag, Tag* child);


void
tag_set_text(Tag* tag, const char* text);


void
tag_export(Tag* tag, const char* name);



#endif
