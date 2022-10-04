/**
 * @file string.c
 * @author Antonin Nepras
 * @brief CString implementation
 * @version 0.1
 * @date 2022-09-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "string.h"


int
cstrlen(const char* s)
{
  if (s == NULL) {
    return -1;
  }

  int len = 0;
  for (int pos = 0; s[pos] != '\0'; ++pos) {
    len++;
  }

  return len;
}


int
cstrcmp(const char* s1, const char* s2)
{
  if (s1 == NULL || s2 == NULL) {
    return -1;
  }

  bool e1 = false;
  bool e2 = false;
  int i = 0;
  int diff = 0;
  while (true) {
    if (!e1) {
      if (s1[i] == '\0')
        e1 = true;
    }

    if (!e2) {
      if (s2[i] == '\0')
        e2 = true;
    }

    if (e1 && e2) {
      break;
    }

    if (e1 || e2) {
      ++i;
      ++diff;
      continue;
    }

    if (s1[i] != s2[i]) {
      ++diff;
    }
    ++i;
  }

  return diff;
}


String*
string_new(const char* s)
{
  int length = cstrlen(s);
  if (length < 0) {
    return NULL;
  }

  String* str = (String*)malloc(sizeof(String));
  str->string = (char*)malloc(sizeof(char) * length + 1);
  str->length = length;
  for (int i = 0; i < length + 1; ++i) {
    str->string[i] = s[i];
  }

  return str;
}


String*
string_new_length(int length)
{
  if (length < 0) {
    return NULL;
  }

  String* str = (String*)malloc(sizeof(String));
  str->string = (char*)calloc(sizeof(char), length + 1);
  str->length = length;

  return str;
}


void
string_del(String* str)
{
  if (str == NULL) {
    return;
  }

  free(str->string);
  free(str);
}


String*
string_load_line(FILE* file)
{
  if (file == NULL) {
    return NULL;
  }

  DynArr* line_arr = dyn_arr_new();
  char c;
  while (true) {
    c = getc(file);
    if (c == '\n') {
      char* tmp = (char*)malloc(sizeof(char));
      *tmp = c;
      dyn_arr_append(line_arr, tmp);
      break;
    }
    if (c == EOF) {
      break;
    }

    char* tmp = (char*)malloc(sizeof(char));
    *tmp = c;
    dyn_arr_append(line_arr, tmp);
  }

  if (line_arr->size == 0) {
    dyn_arr_del(line_arr);
    return NULL;
  }

  String* line = string_new_length(line_arr->size);
  for (int i = 0; i < line_arr->size; ++i) {
    line->string[i] = *(char*)line_arr->data[i];
  }

  line->string[line->length] = '\0';

  dyn_arr_del_all(line_arr, free);
  return line;
}


String*
string_load_file(const char* filename)
{
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    return NULL;
  }

  DynArr* line_arr = dyn_arr_new();
  char c;
  while (true) {
    c = getc(file);
    if (c == EOF) {
      break;
    }

    char* tmp = (char*)malloc(sizeof(char));
    *tmp = c;
    dyn_arr_append(line_arr, tmp);
  }

  fclose(file);

  if (line_arr->size == 0) {
    dyn_arr_del(line_arr);
    return NULL;
  }

  String* line = string_new_length(line_arr->size);
  for (int i = 0; i < line_arr->size; ++i) {
    line->string[i] = *(char*)line_arr->data[i];
  }

  line->string[line->length] = '\0';

  dyn_arr_del_all(line_arr, free);
  return line;
}


String*
string_add(String* str1, String* str2)
{
  if (str1 == NULL || str2 == NULL) {
    return NULL;
  }

  char tmp[str1->length + str2->length + 1];
  for (int i = 0; i < str1->length; ++i) {
    tmp[i] = str1->string[i];
  }
  for (int i = 0; i < str2->length; ++i) {
    tmp[str1->length + i] = str2->string[i];
  }
  tmp[str1->length + str2->length] = '\0';

  return string_new(tmp);
}


void
string_fprint(FILE* file, String* str)
{
  if (file == NULL || str == NULL) {
    return;
  }

  fprintf(file, "%s", str->string);
}


String*
string_range(String* str, int begin, int end)
{
  if (str == NULL || begin < 0 || end > str->length) {
    return NULL;
  }

  char tmp[end - begin + 1];
  for (int i = begin; i < end; ++i) {
    tmp[i - begin] = str->string[i];
  }

  tmp[end - begin] = '\0';

  return string_new(tmp);
}


bool
string_in_string(String* str, String* pattern)
{
  if (str == NULL || pattern == NULL) {
    return false;
  }

  if (str->length < pattern->length) {
    return false;
  }

  int l_diff = str->length - pattern->length;
  for (int i = 0; i < l_diff + 1; ++i) {
    bool equal = true;
    for (int j = 0; j < pattern->length; ++j) {
      if (str->string[i + j] != pattern->string[j]) {
        equal = false;
        break;
      }
    }

    if (equal) {
      return true;
    }
  }

  return false;
}


DynArr*
string_in_string_pos(String* str, String* pattern)
{
  if (str == NULL || pattern == NULL) {
    return NULL;
  }

  if (str->length < pattern->length) {
    return NULL;
  }

  DynArr* positions = dyn_arr_new();

  int l_diff = str->length - pattern->length;
  for (int i = 0; i < l_diff + 1; ++i) {
    bool equal = true;
    for (int j = 0; j < pattern->length; ++j) {
      if (str->string[i + j] != pattern->string[j]) {
        equal = false;
        break;
      }
    }

    if (equal) {
      int* tmp = (int*)malloc(sizeof(int));
      *tmp = i;
      dyn_arr_append(positions, tmp);
    }
  }

  if (positions->size == 0) {
    dyn_arr_del(positions);
    return NULL;
  }

  return positions;
}


String*
string_insert(String* str, String* pattern, int position)
{
  if (str == NULL || pattern == NULL || position < 0 ||
      position > str->length) {
    return NULL;
  }

  char tmp[str->length + pattern->length + 1];
  for (int i = 0; i < position; ++i) {
    tmp[i] = str->string[i];
  }
  for (int i = 0; i < pattern->length; ++i) {
    tmp[i + position] = pattern->string[i];
  }
  for (int i = position; i < str->length; ++i) {
    tmp[i + pattern->length] = str->string[i];
  }
  tmp[str->length + pattern->length] = '\0';

  return string_new(tmp);
}


String*
string_color_pattern(String* str,
                     String* pattern,
                     String* color,
                     String* decolor)
{
  DynArr* positions = string_in_string_pos(str, pattern);
  String* res = string_copy(str);
  for (int i = 0; i < positions->size; ++i) {
    String* tmp;
    tmp = string_insert(res,
                        decolor,
                        *(int*)positions->data[positions->size - i - 1] +
                          pattern->length);
    string_del(res);
    res = tmp;
    tmp = string_insert(
      res, color, *(int*)positions->data[positions->size - i - 1]);

    string_del(res);
    res = tmp;
  }

  dyn_arr_del_all(positions, free);

  return res;
}


String*
string_copy(String* str)
{
  String* copy = (String*)malloc(sizeof(String));
  copy->string = (char*)malloc(sizeof(char) * str->length + 1);
  copy->length = str->length;

  for (int i = 0; i < copy->length + 1; ++i) {
    copy->string[i] = str->string[i];
  }

  return copy;
}
