/**
 * @file log.h
 * @author Antonin Nepras
 * @brief Logging
 * @version 0.1
 * @date 2022-10-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __log_h__
#define __log_h__


#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef SUCCESS
#define SUCCESS 0
#endif
#ifndef ERROR
#define ERROR 1
#endif


/**
 * @brief Create clean log file with time header
 *
 * @param filename
 * @return int
 */
int
log_start(const char* filename);


/**
 * @brief Log message to the log file
 *
 * @param file
 * @param msg
 * @param ...
 * @return int
 */
int
log_add(const char* file, const char* msg, ...);


/**
 * @brief Log message to the log file and print it to stderr
 *
 * @param file
 * @param msg
 * @param ...
 * @return int
 */
int
log_add_err(const char* file, const char* msg, ...);


#endif
