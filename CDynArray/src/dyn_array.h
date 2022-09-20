/**
 * @file dyn_array.h
 * @author Antonin Nepras
 * @brief Simple Dynamic array
 * @version 0.1
 * @date 2022-09-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __dyn_array_h__
#define __dyn_array_h__

#include <stdlib.h>

#define DYN_ARR_MIN_CAP 16

#ifndef ERROR
#define ERROR 1
#endif

#ifndef SUCCESS
#define SUCCESS 0
#endif

typedef struct
{
  void** data;
  long size;
  long capacity;
} DynArr;


DynArr*
dyn_arr_new(void);


int
dyn_arr_del(DynArr* arr);


int
dyn_arr_del_all(DynArr* arr, void (*clear_func)(void*));


int
dyn_arr_append(DynArr* arr, void* value);


int
dyn_arr_prepend(DynArr* arr, void* value);


int
dyn_arr_insert(DynArr* arr, void* value, long position);


void*
dyn_arr_pop_back(DynArr* arr);


void*
dyn_arr_pop_front(DynArr* arr);


void*
dyn_arr_remove(DynArr* arr, long position);


#endif
