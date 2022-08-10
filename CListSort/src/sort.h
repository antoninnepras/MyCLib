/**
 * @file sort.h
 * @author Antonin Nepras
 * @brief simple general purpose sort functions
 * @version 0.1
 * @date 2022-08-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __sort_h__
#define __sort_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief Sort elements
 *
 * @param algorithm      algorithm to use (algr_quick_sort)
 * @param elements       elements to sort
 * @param size           size of the elements array
 * @param metric         metric to evaluate each element
 * @return int           0 OK or 1 ERROR
 */
int
sort(int (*algorithm)(void**, double*, int),
     void** elements,
     int size,
     double (*metric)(void*));


/**
 * @brief Swap two elements in the elements and values arrays
 *
 * @param elements       elements array
 * @param values         values arrey
 * @param el1            index of 1st element to swap
 * @param el2            index of 2nd element to swap
 */
void
swap_elements(void** elements, double* values, int el1, int el2);


/**
 * @brief Bubble sort algorithm for sort
 * 
 * @param elements       elements to sort
 * @param values         values for the elements
 * @param size           size of the arrays
 * @return int           0 OK or 1 ERROR
 */
int
algr_bubble_sort(void** elements, double* values, int size);


/**
 * @brief Insertion sort algorithm for sort
 * 
 * @param elements       elements to sort
 * @param values         values for the elements
 * @param size           size of the arrays
 * @return int           0 OK or 1 ERROR
 */
int
algr_insertion_sort(void** elements, double* values, int size);


/**
 * @brief Quick sort algorithm for sort
 * 
 * @param elements       elements to sort
 * @param values         values for the elements
 * @param size           size of the arrays
 * @return int           0 OK or 1 ERROR
 */
int
algr_quick_sort(void** elements, double* values, int size);


/**
 * @brief Evaluate string for sorting purposes
 * 
 * @param string         string to assign value
 * @return double        value of the string
 */
double
string_get_alpha_value(const char* string);


#endif
