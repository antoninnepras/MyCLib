#include "src/bin_tree.h"
#include <time.h>


int*
new_num(int num);


double
num_metric(void* data)
{
  return (double)(*(int*)data);
}


void
print_num(void* data)
{
  printf("data: %i", *(int*)data);
}


int
my_rand(int max)
{
  return ((double)rand() / RAND_MAX) * max;
}


int
metric_num(void* n1, void* n2)
{
  if (*(int*)n1 < *(int*)n2) {
    return -1;
  } else if (*(int*)n1 == *(int*)n2) {
    return 0;
  } else {
    return 1;
  }
}


int
main(int argc, const char** argv)
{
  srand(time(NULL));
  BinTree* tree = bin_tree_new();
  for (int i = 0; i < 10; ++i) {
    bin_tree_insert_sorted(tree, new_num(my_rand(40)), num_metric);
  }

  void* tmp;

  print_node(tree->root, 0, print_num);


  for (int i = 0; i < 5; ++i) {
    bin_tree_pop_left(tree, &tmp);
    printf("left: %i\n\n", *(int*)tmp);
    free(tmp);
  }

  for (int i = 0; i < 10; ++i) {
    bin_tree_insert_sorted(tree, new_num(my_rand(40)), num_metric);
  }


  for (int i = 0; i < 40; ++i) {
    if (bin_tree_in_sorted(tree, &i, metric_num)) {
      printf("%i\n", i);
    }
  }

  for (int i = 0; i < 40; ++i) {
    if (bin_tree_in(tree, &i, metric_num)) {
      printf("%i\n", i);
    }
  }

  while (bin_tree_pop_right(tree, &tmp) == EXIT_SUCCESS) {
    printf("right: %i\n\n", *(int*)tmp);
    free(tmp);
  }

  print_node(tree->root, 0, print_num);

  bin_tree_del_all(&tree, free);
  return EXIT_SUCCESS;
}


int*
new_num(int num)
{
  int* tmp = (int*)malloc(sizeof(int));
  *tmp = num;
  return tmp;
}
