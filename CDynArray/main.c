/**
 * @file main.c
 * @author Antonin Nepras
 * @brief DynArr test file
 * @version 0.1
 * @date 2022-09-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "src/dyn_array.h"

int*
new_num(int num);

int
main(int argc, const char** argv)
{
  DynArr* array = dyn_arr_new();

  for (int i = 0; i < 10; ++i) {
    dyn_arr_append(array, new_num(i));
  }


  dyn_arr_del_all(array, free);
}


int*
new_num(int num)
{
  int* tmp = (int*)malloc(sizeof(int));
  *tmp = num;
  return tmp;
}
