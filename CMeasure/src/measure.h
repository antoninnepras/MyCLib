/**
 * @file measure.h
 * @author Antonin Nepras
 * @brief Simple funcitons measurement
 * @version 0.1
 * @date 2023-01-04
 *
 * @copyright Copyright (c) 2023
 *
 */


#ifndef __measure_h__
#define __measure_h__

#include "dyn_array.h"
#include <stdlib.h>
#include <time.h>


clock_t*
new_time(clock_t time);


clock_t
measure_func_time(void (*func)(void));


DynArr*
measure_func_times(void (*func)(void), size_t times);


clock_t
times_average(DynArr* times);


double
time_in_secs(clock_t time);


#endif
