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


/**
 * @brief Dynamic array structure
 *
 */
typedef struct
{
  void** data;
  long size;
  long capacity;
} DynArr;


/**
 * @brief Create new dynamic array structure
 *
 * @return DynArr*
 */
DynArr*
dyn_arr_new(void);


/**
 * @brief Delete dynamic array structure
 *
 * @param arr       dynamic array structure
 * @return int
 */
int
dyn_arr_del(DynArr* arr);


/**
 * @brief Delete dynamic array structure and int content
 *
 * @param arr         dynamic array
 * @param clear_func  funciton to use for cleaning array elements
 * @return int        SUCCESS or ERROR
 */
int
dyn_arr_del_all(DynArr* arr, void (*clear_func)(void*));


/**
 * @brief Add data to the end of dynamic array
 *
 * @param arr         dyamic array structure
 * @param value       data
 * @return int        SUCCESS or ERROR
 */
int
dyn_arr_append(DynArr* arr, void* value);


/**
 * @brief Add data to the front of dynamic array
 *
 * @param arr       dyamic array structure
 * @param value     data
 * @return int      SUCCESS or ERROR
 */
int
dyn_arr_prepend(DynArr* arr, void* value);


/**
 * @brief Insert data into dynamic array
 *
 * @param arr       dyamic array structure
 * @param value     data
 * @param position  position on which insert
 * @return int      SUCCESS or ERROR
 */
int
dyn_arr_insert(DynArr* arr, void* value, long position);


/**
 * @brief Insert data into dynamic array, smaller metric value first
 *
 * @param arr       dynamic array structure
 * @param value     data
 * @param metric    metric to determine, what insert first
 * @return int      SUCCESS or ERROR
 */
int
dyn_arr_insert_sorted(DynArr* arr, void* value, double (*metric)(void*));


/**
 * @brief Remove data from back of the dynamic array
 *
 * @param arr       dynamic array structure
 * @return void*    data or NULL on error
 */
void*
dyn_arr_pop_back(DynArr* arr);


/**
 * @brief Remove data from front of the dynamic array (slow)
 *
 * @param arr       dynamic array structure
 * @return void*    data or NULL on error
 */
void*
dyn_arr_pop_front(DynArr* arr);


/**
 * @brief Remove data fron dynamic array
 *
 * @param arr         dynamic array
 * @param position    position to remove from
 * @return void*      data or NULL on error
 */
void*
dyn_arr_remove(DynArr* arr, long position);


#endif
