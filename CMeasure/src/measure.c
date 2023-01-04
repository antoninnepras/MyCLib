#include "measure.h"


clock_t*
new_time(clock_t time)
{
  clock_t* n_time = (clock_t*)malloc(sizeof(clock_t));
  *n_time = time;
  return n_time;
}

clock_t
measure_func_time(void (*func)(void))
{
  clock_t start = clock();
  func();
  clock_t end = clock();

  return end - start;
}


DynArr*
measure_func_times(void (*func)(void), size_t n)
{
  DynArr* times = dyn_arr_new();
  for (size_t i = 0; i < n; ++i) {
    dyn_arr_append(times, new_time(measure_func_time(func)));
  }

  return times;
}


clock_t
times_average(DynArr* times)
{
  double avg_d = 0;
  for (long i = 0; i < times->size; ++i) {
    avg_d += (double)(*(clock_t*)times->data[i]) / times->size;
  }

  return (clock_t)avg_d;
}


double
time_in_secs(clock_t time)
{
  return ((double)time) / CLOCKS_PER_SEC;
}
