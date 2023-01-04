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
bin_node_count_down(BinNode* node)
{
  if (node == NULL) {
    return EXIT_FAILURE;
  }

  if (node->parent == NULL) {
    return EXIT_SUCCESS;
  }

  switch (node->pos) {
    case BIN_NODE_LEFT:
      --((BinNode*)node->parent)->left_size;
      break;
    case BIN_NODE_RIGHT:
      --((BinNode*)node->parent)->right_size;
      break;
    default:
      break;
  }

  bin_node_count_down((BinNode*)node->parent);

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


BinTree*
bin_tree_new(void)
{
  BinTree* tree = (BinTree*)malloc(sizeof(BinTree));
  if (tree == NULL) {
    return NULL;
  }

  tree->root = NULL;
  tree->size = 0;
  return tree;
}


int
bin_tree_del(BinTree** tree)
{
  if (tree == NULL || *tree == NULL) {
    return EXIT_FAILURE;
  }

  if ((*tree)->root != NULL) {
    bin_node_del(&(*tree)->root);
  }

  free(*tree);
  *tree = NULL;

  return EXIT_SUCCESS;
}


int
bin_tree_del_all(BinTree** tree, void (*data_del)(void*))
{
  if (tree == NULL || *tree == NULL || data_del == NULL) {
    return EXIT_FAILURE;
  }

  if ((*tree)->root != NULL) {
    bin_node_del_all(&(*tree)->root, data_del);
  }

  free(*tree);
  *tree = NULL;

  return EXIT_SUCCESS;
}


int
bin_tree_insert(BinTree* tree, void* data)
{
  if (tree == NULL) {
    return EXIT_FAILURE;
  }

  if (tree->root == NULL) {
    tree->root = bin_node_new(data, NULL, BIN_NODE_ROOT);
  } else {
    bin_node_insert(tree->root, data);
  }

  ++tree->size;

  return EXIT_SUCCESS;
}


int
bin_tree_insert_sorted(BinTree* tree, void* data, double (*metric)(void*))
{
  if (tree == NULL || metric == NULL) {
    return EXIT_FAILURE;
  }

  if (tree->root == NULL) {
    tree->root = bin_node_new(data, NULL, BIN_NODE_ROOT);
  } else {
    bin_node_insert_sorted(tree->root, data, metric);
  }

  ++tree->size;

  return EXIT_SUCCESS;
}


int
bin_tree_get_left(BinTree* tree, void** data)
{
  if (tree == NULL) {
    return EXIT_FAILURE;
  }

  if (tree->size == 0) {
    return EXIT_FAILURE;
  }

  BinNode* tmp = tree->root;
  while (tmp->left != NULL) {
    tmp = (BinNode*)tmp->left;
  }

  *data = tmp->data;

  return EXIT_SUCCESS;
}


int
bin_tree_get_right(BinTree* tree, void** data)
{
  if (tree == NULL) {
    return EXIT_FAILURE;
  }

  if (tree->size == 0) {
    return EXIT_FAILURE;
  }

  BinNode* tmp = tree->root;
  while (tmp->right != NULL) {
    tmp = (BinNode*)tmp->right;
  }

  *data = tmp->data;

  return EXIT_SUCCESS;
}


int
bin_tree_pop_left(BinTree* tree, void** data)
{
  if (tree == NULL) {
    return EXIT_FAILURE;
  }

  if (tree->size == 0) {
    return EXIT_FAILURE;
  }

  BinNode* tmp = tree->root;
  while (tmp->left != NULL) {
    tmp = (BinNode*)tmp->left;
  }

  bin_node_count_down(tmp);

  if (tmp->right != NULL) {
    if (tmp->pos != BIN_NODE_ROOT) {
      ((BinNode*)tmp->parent)->left_size = tmp->right_size;
      ((BinNode*)tmp->parent)->left = (BinNode*)tmp->right;
      ((BinNode*)tmp->right)->parent = (BinNode*)tmp->parent;
      ((BinNode*)tmp->right)->pos = BIN_NODE_LEFT;
    } else {
      tree->root = tmp->right;
      ((BinNode*)tmp->right)->pos = BIN_NODE_ROOT;
      ((BinNode*)tmp->right)->parent = NULL;
    }
  } else {
    if (tmp->pos != BIN_NODE_ROOT) {
      ((BinNode*)tmp->parent)->left = NULL;
    } else {
      tree->root = NULL;
    }
  }

  *data = tmp->data;

  free(tmp);

  --tree->size;

  return EXIT_SUCCESS;
}


int
bin_tree_pop_right(BinTree* tree, void** data)
{
  if (tree == NULL) {
    return EXIT_FAILURE;
  }

  if (tree->size == 0) {
    return EXIT_FAILURE;
  }

  BinNode* tmp = tree->root;
  while (tmp->right != NULL) {
    tmp = (BinNode*)tmp->right;
  }

  bin_node_count_down(tmp);

  if (tmp->left != NULL) {
    if (tmp->pos != BIN_NODE_ROOT) {
      ((BinNode*)tmp->parent)->right_size = tmp->left_size;
      ((BinNode*)tmp->parent)->right = (BinNode*)tmp->left;
      ((BinNode*)tmp->left)->parent = (BinNode*)tmp->parent;
      ((BinNode*)tmp->left)->pos = BIN_NODE_RIGHT;
    } else {
      tree->root = tmp->left;
      ((BinNode*)tmp->left)->pos = BIN_NODE_ROOT;
      ((BinNode*)tmp->left)->parent = NULL;
    }
  } else {
    if (tmp->pos != BIN_NODE_ROOT) {
      ((BinNode*)tmp->parent)->right = NULL;
    } else {
      tree->root = NULL;
    }
  }

  *data = tmp->data;

  free(tmp);

  --tree->size;

  return EXIT_SUCCESS;
}
