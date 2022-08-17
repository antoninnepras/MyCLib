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


/**
 * @brief Tag attribute
 * 
 */
typedef struct
{
  char name[64];
  char* value;
} Tag_attr;


/**
 * @brief Tag with attributes and childs
 * 
 */
typedef struct 
{
  char name[TAG_NAME_LEN];
  List* attrs;
  List* childs;
  char* text;
} Tag;


/**
 * @brief Create new attribute
 * 
 * @param name 
 * @param value 
 * @return Tag_attr* 
 */
Tag_attr*
tag_attr_new(const char* name, const char* value);


/**
 * @brief Destroy attribute
 * 
 * @param attr 
 */
void
tag_attr_del(Tag_attr* attr);


/**
 * @brief Create new tag
 * 
 * @param name 
 * @return Tag* 
 */
Tag*
tag_new(const char* name);


/**
 * @brief Destroy tag
 * 
 * @param tag 
 */
void
tag_del(Tag* tag);


/**
 * @brief Add attribute to tag
 * 
 * @param tag 
 * @param attr 
 */
void
tag_add_attr(Tag* tag, Tag_attr* attr);


/**
 * @brief Create attribute and add it to tag
 * 
 * @param tag 
 * @param name 
 * @param value 
 */
void
tag_add_attr_new(Tag* tag, const char* name, const char* value);


/**
 * @brief Add child to attribute
 * 
 * @param tag 
 * @param child 
 */
void
tag_add_child(Tag* tag, Tag* child);


/**
 * @brief Set tag text
 * 
 * @param tag 
 * @param text 
 */
void
tag_set_text(Tag* tag, const char* text);


/**
 * @brief Export tag to file
 * 
 * @param tag 
 * @param name 
 */
void
tag_export(Tag* tag, const char* name);


#endif
