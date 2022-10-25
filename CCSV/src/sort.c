/**
 * @file sort.c
 * @author Antonin Nepras
 * @brief sort function implementation
 * @version 0.1
 * @date 2022-08-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "sort.h"

int
sort(int (*algorithm)(void**, double*, int),
     void** elements,
     int size,
     double (*metric)(void*))
{
  double* values = (double*)malloc(sizeof(double) * size);
  for (int i = 0; i < size; ++i) {
    values[i] = metric(elements[i]);
  }

  int ret = algorithm(elements, values, size);
  free(values);

  return ret;
}


void
swap_elements(void** elements, double* values, int el1, int el2)
{
  void* tmpel = elements[el1];
  double tmpv = values[el1];
  elements[el1] = elements[el2];
  values[el1] = values[el2];
  elements[el2] = tmpel;
  values[el2] = tmpv;
}


int
algr_insertion_sort(void** elements, double* values, int size)
{
  if (elements == NULL || values == NULL || size <= 0) {
    return 1;
  }

  for (int i = 1; i < size; ++i) {
    for (int j = i; j > 0 && values[j - 1] > values[j]; --j) {
      swap_elements(elements, values, j, j - 1);
    }
  }

  return 0;
}


int
algr_bubble_sort(void** elements, double* values, int size)
{
  if (elements == NULL || values == NULL || size <= 0) {
    return 1;
  }

  int swaps;
  do {
    swaps = 0;
    for (int i = 1; i < size; ++i) {
      if (values[i - 1] > values[i]) {
        swap_elements(elements, values, i, i - 1);
        swaps++;
      }
    }
  } while (swaps > 0);

  return 0;
}


double
quick_get_pivot(double* values, int size)
{
  if (size == 2) {
    return values[0];
  } else {
    return (values[0] + values[size - 1] + values[size / 2]) / 3.0;
  }
}

void
quick_sort(void** elements, double* values, int size)
{

  // sorted
  if (size < 2) {
    return;
  } else if (size == 2) {
    if (values[0] > values[1]) {
      swap_elements(elements, values, 0, 1);
    }
    return;
  }

  double pivot = quick_get_pivot(values, size);
  void** lower_e = (void**)malloc(sizeof(void*) * size);
  void** higher_e = (void**)malloc(sizeof(void*) * size);
  double* lower_v = (double*)malloc(sizeof(double) * size);
  double* higher_v = (double*)malloc(sizeof(double) * size);
  int lower_size = 0;
  int higher_size = 0;
  for (int i = 0; i < size; ++i) {
    if (values[i] < pivot) {
      lower_e[lower_size] = elements[i];
      lower_v[lower_size] = values[i];
      lower_size++;
    } else {
      higher_e[higher_size] = elements[i];
      higher_v[higher_size] = values[i];
      higher_size++;
    }
  }

  quick_sort(lower_e, lower_v, lower_size);
  quick_sort(higher_e, higher_v, higher_size);

  for (int i = 0; i < lower_size; ++i) {
    elements[i] = lower_e[i];
    values[i] = lower_v[i];
  }

  for (int i = 0; i < higher_size; ++i) {
    elements[i + lower_size] = higher_e[i];
    values[i + lower_size] = higher_v[i];
  }

  free(lower_e);
  free(higher_e);
  free(lower_v);
  free(higher_v);
}

int
algr_quick_sort(void** elements, double* values, int size)
{
  if (elements == NULL || values == NULL || size <= 0) {
    return 1;
  }

  quick_sort(elements, values, size);

  return 0;
}


double
string_get_alpha_value(const char* string)
{
  if (string == NULL) {
    return -1;
  }

  int len = strlen(string);
  double val = 0;
  double div = 1;
  for (int i = 0; i < len; ++i) {
    val += (double)string[i] / div;
    div *= 128;
  }

  return val;
}
