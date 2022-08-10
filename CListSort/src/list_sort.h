/**
 * @file list_sort.h
 * @author Antonin Nepras
 * @brief Sort for lists
 * @version 0.1
 * @date 2022-08-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __list_sort_h__
#define __list_sort_h__

#include "list.h"
#include "sort.h"


/**
 * @brief sort list using quick sort algorithm
 * 
 * @param list 
 * @param metric 
 */
void
list_sort(List* list, double (*metric)(void*));


#endif
