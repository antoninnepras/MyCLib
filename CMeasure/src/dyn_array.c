/**
 * @file dyn_array.c
 * @author Antonin Nepras
 * @brief Simple Dynamic array implementation
 * @version 0.1
 * @date 2022-09-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "dyn_array.h"


DynArr*
dyn_arr_new(void)
{
  DynArr* array = (DynArr*)malloc(sizeof(DynArr));
  array->data = (void**)malloc(sizeof(void*) * DYN_ARR_MIN_CAP);
  array->capacity = DYN_ARR_MIN_CAP;
  array->size = 0;

  return array;
}


int
dyn_arr_del(DynArr* arr)
{
  if (arr == NULL) {
    return ERROR;
  }

  free(arr->data);
  free(arr);
  return SUCCESS;
}


int
dyn_arr_del_all(DynArr* arr, void (*clear_func)(void*))
{
  if (arr == NULL) {
    return ERROR;
  }

  for (int i = 0; i < arr->size; ++i) {
    clear_func(arr->data[i]);
  }

  return dyn_arr_del(arr);
}


int
dyn_arr_resize(DynArr* arr, long size)
{
  if (arr == NULL || arr->size > size) {
    return ERROR;
  }

  void** tmp = (void**)realloc(arr->data, sizeof(void*) * size);
  if (tmp == NULL) {
    return ERROR;
  }

  arr->data = tmp;
  arr->capacity = size;
  return SUCCESS;
}


int
dyn_arr_append(DynArr* arr, void* value)
{
  if (arr == NULL) {
    return ERROR;
  }

  if (arr->capacity <= arr->size) {
    if (dyn_arr_resize(arr, arr->capacity * 2) == ERROR) {
      return ERROR;
    }
  }

  arr->data[arr->size] = value;
  arr->size++;

  return SUCCESS;
}


int
dyn_arr_prepend(DynArr* arr, void* value)
{
  return dyn_arr_insert(arr, value, 0);
}


int
dyn_arr_insert(DynArr* arr, void* value, long position)
{
  if (arr == NULL) {
    return ERROR;
  }

  if (arr->capacity <= arr->size) {
    if (dyn_arr_resize(arr, arr->capacity * 2) == ERROR) {
      return ERROR;
    }
  }

  for (long i = arr->size; i > position; --i) {
    arr->data[i] = arr->data[i - 1];
  }

  arr->data[position] = value;
  arr->size++;

  return SUCCESS;
}


int
dyn_arr_insert_sorted(DynArr* arr, void* value, double (*metric)(void*))
{
  if (arr == NULL || metric == NULL) {
    return ERROR;
  }

  double value_metric = metric(value);
  long position = 0;
  while (position < arr->size && value_metric > metric(arr->data[position])) {
    ++position;
  }


  return dyn_arr_insert(arr, value, position);
}


void*
dyn_arr_pop_back(DynArr* arr)
{
  if (arr == NULL || arr->size == 0) {
    return NULL;
  }

  arr->size--;
  void* value = arr->data[arr->size];

  if (arr->capacity > 2 * arr->size && arr->capacity != DYN_ARR_MIN_CAP) {
    if (arr->capacity > 3 * DYN_ARR_MIN_CAP) {
      dyn_arr_resize(arr, arr->size / 3);
    } else {
      dyn_arr_remove(arr, DYN_ARR_MIN_CAP);
    }
  }

  return value;
}


void*
dyn_arr_pop_front(DynArr* arr)
{
  return dyn_arr_remove(arr, 0);
}


void*
dyn_arr_remove(DynArr* arr, long position)
{
  if (arr == NULL || arr->size <= position) {
    return NULL;
  }

  void* value = arr->data[position];
  arr->size--;

  for (int i = position; i < arr->size; ++i) {
    arr->data[i] = arr->data[i + 1];
  }

  if (arr->capacity > 2 * arr->size && arr->capacity != DYN_ARR_MIN_CAP) {
    if (arr->capacity > 3 * DYN_ARR_MIN_CAP) {
      dyn_arr_resize(arr, arr->size / 3);
    } else {
      dyn_arr_remove(arr, DYN_ARR_MIN_CAP);
    }
  }

  return value;
}
