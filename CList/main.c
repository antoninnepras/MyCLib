/**
 * @file main.c
 * @author Antonin Nepras
 * @brief CList example
 * @version 0.1
 * @date 2022-08-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "src/list.h"
#include <stdio.h>


double
metric(void* data)
{
  return (*(int*)data);
}


int
main(int argc, const char** argv)
{
  // create list
  List* list = list_new();

  // append data to the list
  for (int i = 0; i < 10; ++i) {
    int* data = malloc(sizeof(int));
    *data = i;
    list_append(list, data);
  }

  // prepend data to the list
  for (int i = 0; i < 10; ++i) {
    int* data = malloc(sizeof(int));
    *data = i;
    list_prepend(list, data);
  }

  // insert data to the list
  for (int i = 0; i < 5; ++i) {
    int* data = malloc(sizeof(int));
    *data = -1;
    list_insert_sorted(list, data, metric);
  }

  // remove data from the list
  for (int i = 0; i < 5; ++i) {
    free(list_remove(list, 4));
  }

  // get data from the list
  for (int i = 0; i < list->size; ++i) {
    printf("%i\n", *(int*)list_get(list, i));
  }

  // create array from list data
  int array_size;
  int** array = (int**)list_to_array_dyn(list, &array_size);
  for (int i = 0; i < array_size; ++i) {
    printf("%i\n", *array[i]);
  }

  // crate list from array
  List* list2 = list_from_array((void**)array, array_size);
  for (int i = 0; i < list2->size; ++i) {
    printf("list2: %i | %i\n", i, *(int*)list_get(list2, i));
  }

  // delete list
  list_del(list2);

  free(array);

  // free all elements of list
  list_do_for_all(list, free);

  // delete empty list
  list_del(list);
}
