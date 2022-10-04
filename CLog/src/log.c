/**
 * @file log.c
 * @author Antonin Nepras
 * @brief Logging implementation
 * @version 0.1
 * @date 2022-10-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "log.h"


int
log_start(const char* filename)
{
  FILE* fp = fopen(filename, "w");
  if (fp == NULL) {
    return ERROR;
  }
  time_t t = time(NULL);
  fprintf(fp, "Log time: %s", ctime(&t));
  for (int i = 0; i < 80; ++i) {
    putc('-', fp);
  }
  putc('\n', fp);

  fclose(fp);

  return SUCCESS;
}


int
log_add(const char* filename, const char* msg, ...)
{
  FILE* fp = fopen(filename, "a");
  if (fp == NULL) {
    return ERROR;
  }

  va_list argptr;
  va_start(argptr, msg);
  vfprintf(fp, msg, argptr);
  va_end(argptr);

  fclose(fp);

  return SUCCESS;
}


int
log_add_err(const char* filename, const char* msg, ...)
{
  FILE* fp = fopen(filename, "a");
  if (fp == NULL) {
    return ERROR;
  }

  va_list argptr;
  va_start(argptr, msg);
  vfprintf(fp, msg, argptr);
  vfprintf(stderr, msg, argptr);
  va_end(argptr);

  fclose(fp);

  return SUCCESS;
}
