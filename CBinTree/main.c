#include "src/bin_tree.h"

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
main(int argc, const char** argv)
{
  BinNode* root = bin_node_new(new_num(0), NULL, BIN_NODE_ROOT);
  for (int i = 0; i < 10; ++i) {
    bin_node_insert_sorted(root, new_num(my_rand(100)), num_metric);
  }

  print_node(root, 0, print_num);

  bin_node_del_all(&root, free);

  return EXIT_SUCCESS;
}


int*
new_num(int num)
{
  int* tmp = (int*)malloc(sizeof(int));
  *tmp = num;
  return tmp;
}
