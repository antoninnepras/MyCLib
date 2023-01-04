#include "src/measure.h"

#include <stdio.h>

#define TARGET_NUM 10000000

void
func1()
{
  FILE* f = fopen("tmp1", "w");

  for (long i = 0; i < TARGET_NUM; ++i) {
    putc('a', f);
    putc('b', f);
  }

  fclose(f);
}


void
func2()
{
  FILE* f = fopen("tmp2", "w");

  for (long i = 0; i < TARGET_NUM; ++i) {
    fprintf(f, "%s", "a");
    fprintf(f, "%s", "b");
  }

  fclose(f);
}


int
main(int argc, const char** argv)
{
  DynArr* times1 = measure_func_times(func1, 10);
  DynArr* times2 = measure_func_times(func2, 10);
  clock_t avg1 = times_average(times1);
  clock_t avg2 = times_average(times2);
  printf("%8lfs\n", time_in_secs(avg1));
  printf("%8lfs\n", time_in_secs(avg2));

  dyn_arr_del_all(times1, free);
  dyn_arr_del_all(times2, free);
}
