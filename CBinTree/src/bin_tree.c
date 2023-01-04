/**
 * @file bin_tree.c
 * @author Antonin Nepras
 * @brief Binary tree implementation
 * @version 0.1
 * @date 2023-01-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "bin_tree.h"


BinNode*
bin_node_new(void* data, void* parent, int pos)
{
  BinNode* node = (BinNode*)malloc(sizeof(BinNode));
  if (node == NULL) {
    return NULL;
  }

  node->pos = pos;
  node->data = data;
  node->parent = parent;
  node->left = NULL;
  node->right = NULL;
  node->left_size = 0;
  node->right_size = 0;

  return node;
}


int
bin_node_del(BinNode** node)
{
  if (node == NULL || *node == NULL) {
    return EXIT_FAILURE;
  }

  if ((*node)->left != NULL) {
    bin_node_del((BinNode**)&(*node)->left);
  }

  if ((*node)->right != NULL) {
    bin_node_del((BinNode**)&(*node)->right);
  }

  free(*node);
  *node = NULL;

  return EXIT_SUCCESS;
}


int
bin_node_del_all(BinNode** node, void (*data_del)(void*))
{
  if (node == NULL || *node == NULL) {
    return EXIT_FAILURE;
  }

  if ((*node)->left != NULL) {
    bin_node_del_all((BinNode**)&(*node)->left, data_del);
  }

  if ((*node)->right != NULL) {
    bin_node_del_all((BinNode**)&(*node)->right, data_del);
  }

  data_del((*node)->data);
  free(*node);
  *node = NULL;

  return EXIT_SUCCESS;
}


int
bin_node_add_left(BinNode* node, void* data)
{
  if (node == NULL) {
    return EXIT_FAILURE;
  }

  BinNode* new_node = bin_node_new(data, node, BIN_NODE_LEFT);
  if (new_node == NULL) {
    return EXIT_FAILURE;
  }

  node->left = new_node;
  bin_node_count_up((BinNode*)node->left);

  return EXIT_SUCCESS;
}


int
bin_node_add_right(BinNode* node, void* data)
{
  if (node == NULL) {
    return EXIT_FAILURE;
  }

  BinNode* new_node = bin_node_new(data, node, BIN_NODE_RIGHT);
  if (new_node == NULL) {
    return EXIT_FAILURE;
  }

  node->right = new_node;
  bin_node_count_up((BinNode*)node->right);

  return EXIT_SUCCESS;
}


int
bin_node_insert(BinNode* node, void* data)
{
  if (node == NULL) {
    return EXIT_FAILURE;
  }

  if (node->left_size == 0) {
    bin_node_add_left(node, data);
  } else if (node->right_size == 0) {
    bin_node_add_right(node, data);
  } else if (node->left_size <= node->right_size) {
    bin_node_insert((BinNode*)node->left, data);
  } else {
    bin_node_insert((BinNode*)node->right, data);
  }

  return EXIT_SUCCESS;
}


int
bin_node_insert_sorted(BinNode* node, void* data, double (*metric)(void*))
{
  if (node == NULL) {
    return EXIT_FAILURE;
  }

  double data_val = metric(data);
  if (data_val < metric(node->data)) {
    if (node->left_size == 0) {
      bin_node_add_left(node, data);
    } else {
      bin_node_insert_sorted((BinNode*)node->left, data, metric);
    }
  } else {
    if (node->right_size == 0) {
      bin_node_add_right(node, data);
    } else {
      bin_node_insert_sorted((BinNode*)node->right, data, metric);
    }
  }

  return EXIT_SUCCESS;
}


int
bin_node_count_up(BinNode* node)
{
  if (node == NULL) {
    return EXIT_FAILURE;
  }

  if (node->parent == NULL) {
    return EXIT_SUCCESS;
  }

  switch (node->pos) {
    case BIN_NODE_LEFT:
      ++((BinNode*)node->parent)->left_size;
      break;
    case BIN_NODE_RIGHT:
      ++((BinNode*)node->parent)->right_size;
      break;
    default:
      break;
  }

  bin_node_count_up((BinNode*)node->parent);

  return EXIT_SUCCESS;
}


int
print_node(BinNode* node, int indent, void (*print_data)(void*))
{
  if (node == NULL || print_data == NULL) {
    return EXIT_FAILURE;
  }

  for (int i = 0; i < indent; ++i) {
    printf("\t");
  }
  print_data(node->data);
  printf("\n");
  for (int i = 0; i < indent; ++i) {
    printf("\t");
  }
  printf("L: %li", node->left_size);
  printf("\n");
  if (node->left != NULL) {
    print_node((BinNode*)node->left, indent + 1, print_data);
  }

  for (int i = 0; i < indent; ++i) {
    printf("\t");
  }
  printf("R: %li", node->right_size);
  printf("\n");
  if (node->right != NULL) {
    print_node((BinNode*)node->right, indent + 1, print_data);
  }

  return EXIT_SUCCESS;
}
