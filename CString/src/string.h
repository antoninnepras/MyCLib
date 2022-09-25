/**
 * @file string.h
 * @author Antonin Nepras
 * @brief simple string
 * @version 0.1
 * @date 2022-09-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __string_h__
#define __string_h__

#include "dyn_array.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct
{
  char* string;
  int length;
} String;


int
cstrlen(const char* s);


int
cstrcmp(const char* s1, const char* s2);


String*
string_new(const char* s);


String*
string_new_length(int length);


void
string_del(String* str);


String*
string_load_line(FILE* file);


String*
string_add(String* str1, String* str2);


void
string_fprint(FILE* file, String* str);


String*
string_range(String* str, int begin, int end);


bool
string_in_string(String* str, String* pattern);


DynArr*
string_in_string_pos(String* str, String* pattern);


String*
string_insert(String* str, String* pattern, int position);


String*
string_copy(String* str);


String*
string_color_pattern(String* str,
                     String* pattern,
                     String* color,
                     String* decolor);

#endif
