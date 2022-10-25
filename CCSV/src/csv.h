/**
 * @file csv.h
 * @author Antonin Nepras
 * @brief csv operations
 * @version 0.1
 * @date 2022-10-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __csv_h__
#define __csv_h__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"

#ifndef SUCCESS
#define SUCCESS 0
#endif
#ifndef ERROR
#define ERROR 1
#endif

typedef struct
{
  char* value;
} csv_value_t;


typedef struct
{
  csv_value_t*** table;
  size_t r;
  size_t c;
} csv_table_t;


/**
 * @brief create new csv value structure
 *
 * @param value
 * @return csv_value_t*
 */
csv_value_t*
csv_value_new(char* value);


/**
 * @brief delete csv value
 *
 * @param val     value
 */
void
csv_value_del(csv_value_t** val);


/**
 * @brief load new csv value from stream
 *
 * @param file        file stream
 * @param separator   ',' or ';'
 * @return csv_value_t*
 */
csv_value_t*
csv_value_fload(FILE* file, char separator);


/**
 * @brief write csv value to file - return number ow written bytes
 *
 * @param file
 * @return size_t
 */
size_t
csv_value_fwrite(FILE* file, csv_value_t* value);


/**
 * @brief create new csv table structure
 *
 * @param r     rows
 * @param c     columns
 * @return csv_table_t*
 */
csv_table_t*
csv_table_new(size_t r, size_t c);


/**
 * @brief delete csv table
 *
 * @param table
 */
void
csv_table_del(csv_table_t** table);


/**
 * @brief set value in csv table
 *
 * @param table     csv table
 * @param val       csv value
 * @param r         row
 * @param c         column
 * @return int      SUCCESS or ERROR
 */
int
csv_table_set_val(csv_table_t* table, csv_value_t* val, size_t r, size_t c);


/**
 * @brief get value from csv table
 *
 * @param table     csv table
 * @param r         row
 * @param c         column
 * @return csv_value_t*
 */
csv_value_t*
csv_table_get_val(csv_table_t* table, size_t r, size_t c);


/**
 * @brief resize csv table
 *
 * @param table     csv table
 * @param r         rows
 * @param c         columns
 * @return int      SUCCESS or ERROR
 */
int
csv_table_resize(csv_table_t* table, size_t r, size_t c);


/**
 * @brief load csv table from file
 *
 * @param file        file stream
 * @param separator   ',' or ';'
 * @return csv_table_t*
 */
csv_table_t*
csv_table_fload(FILE* file, char separator);


/**
 * @brief write table to file
 *
 * @param file      file stream
 * @param separator   ',' or ';'
 * @param table
 */
void
csv_table_fwrite(FILE* file, csv_table_t* table, char separator);


/**
 * @brief sort table rows
 *
 * @param table     csv table
 * @param func      sort function
 */
void
csv_table_sort_rows(csv_table_t* table, double (*func)(csv_value_t** row));


/**
 * @brief sort table rows by c-th column alphabetically (not thread safe)
 *
 * @param table     csv table
 * @param c         column
 * @param reverse   reversed
 */
void
csv_table_sort_by_column_alpha(csv_table_t* table, size_t c, bool reverse);


/**
 * @brief sort table rows by c-th column numerically (not thread safe)
 *
 * @param table     csv table
 * @param c         column
 * @param reverse   reversed
 */
void
csv_table_sort_by_column_num(csv_table_t* table, size_t c, bool reverse);

#endif
