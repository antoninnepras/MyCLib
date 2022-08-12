/**
 * @file list_sort.c
 * @author Antonin Nepras
 * @brief List sort implementation
 * @version 0.1
 * @date 2022-08-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "list_sort.h"


void
list_sort(List* list, double (*metric)(void*))
{
  if (list == NULL || metric == NULL) {
    return;
  }

  int array_size;
  void** array = list_to_array_dyn(list, &array_size);
  if (sort(algr_quick_sort, array, array_size, metric) != 0) {
    return;
  }

  while(list->size > 0) {
    list_pop_back(list);
  }

  for (int i = 0 ; i < array_size; ++i) {
    list_append(list, array[i]);
  }

  free(array);
}
