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


/**
 * @brief String structure
 *
 */
typedef struct
{
  char* string;
  int length;
} String;


/**
 * @brief Length of c string
 *
 * @param s         c string
 * @return int      length or -1 on error
 */
int
cstrlen(const char* s);


/**
 * @brief Compare two c strings
 *
 * @param s1        c string 1
 * @param s2        c string 2
 * @return int      number of differences between two strings
 */
int
cstrcmp(const char* s1, const char* s2);


/**
 * @brief Create new string structure
 *
 * @param s         c string
 * @return String*
 */
String*
string_new(const char* s);


/**
 * @brief Create new empty string structure
 *
 * @param length      length of the empty string
 * @return String*
 */
String*
string_new_length(int length);


/**
 * @brief Delete string structure
 *
 * @param str     string
 */
void
string_del(String* str);


/**
 * @brief Load line to string structure
 *
 * @param file    file to load line from
 * @return String*
 */
String*
string_load_line(FILE* file);


/**
 * @brief Add two strings, new string is created
 *
 * @param str1    string 1
 * @param str2    string 2
 * @return String*
 */
String*
string_add(String* str1, String* str2);


/**
 * @brief Print string to file
 *
 * @param file    file to print to
 * @param str     string to print
 */
void
string_fprint(FILE* file, String* str);


/**
 * @brief String cut
 *
 * @param str     string to cut
 * @param begin   begin of new string
 * @param end     endif new string
 * @return String*
 */
String*
string_range(String* str, int begin, int end);


/**
 * @brief Find if string is in string
 *
 * @param str     string to look in
 * @param pattern string to look for
 * @return true
 * @return false
 */
bool
string_in_string(String* str, String* pattern);


/**
 * @brief Find string in string and return positions of occurences
 *
 * @param str     string to look in
 * @param pattern string to look for
 * @return DynArr* (int*)
 */
DynArr*
string_in_string_pos(String* str, String* pattern);


/**
 * @brief Insert string to string, new string is created
 *
 * @param str     string to insert to
 * @param pattern string to insert
 * @param position position on which insert
 * @return String*
 */
String*
string_insert(String* str, String* pattern, int position);


/**
 * @brief Create new string with same text
 *
 * @param str     string to copy
 * @return String*
 */
String*
string_copy(String* str);


/**
 * @brief Color pattern in string, new string is created
 *
 * @param str     string to look in
 * @param pattern string to look for
 * @param color   string inserted before occurence
 * @param decolor string inserted after occurence
 * @return String*
 */
String*
string_color_pattern(String* str,
                     String* pattern,
                     String* color,
                     String* decolor);

#endif
