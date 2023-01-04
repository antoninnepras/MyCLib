/**
 * @file bin_tree.h
 * @author Antonin Nepras
 * @brief Binary tree definition
 * @version 0.1
 * @date 2023-01-04
 *
 * @copyright Copyright (c) 2023
 *
 */


#ifndef __bin_tree_h__
#define __bin_tree_h__


#include <stdio.h>
#include <stdlib.h>


/**
 * @brief Positions of node in relationship to parent node
 *
 */
enum BinNodePos
{
  BIN_NODE_LEFT,
  BIN_NODE_RIGHT,
  BIN_NODE_ROOT
};


/**
 * @brief Structure representing binary node - node of binary tree
 *
 */
typedef struct
{
  int pos;
  void* data;
  void* parent;
  void* left;
  void* right;
  size_t right_size;
  size_t left_size;
} BinNode;


/**
 * @brief Create new binary node structure
 *
 * @param data        data
 * @param parent      parent node
 * @param pos         position in relation to parent
 * @return BinNode*   NULL on ERROR
 */
BinNode*
bin_node_new(void* data, void* parent, int pos);


/**
 * @brief Delete binary node
 *
 * @param node    node to delete
 * @return int    SUCCESS or ERROR
 */
int
bin_node_del(BinNode** node);


/**
 * @brief Delete binary node and its data
 *
 * @param node      node to delete
 * @param data_del  data delete function
 * @return int      SUCCESS or ERROR
 */
int
bin_node_del_all(BinNode** node, void (*data_del)(void*));


/**
 * @brief Add data to the left of the node
 *
 * @param node    node to add data to
 * @param data    data to add
 * @return int    SUCCESS or ERROR
 */
int
bin_node_add_left(BinNode* node, void* data);


/**
 * @brief Add data to the right of the node
 *
 * @param node    node to add data to
 * @param data    data to add
 * @return int    SUCCESS or ERROR
 */
int
bin_node_add_right(BinNode* node, void* data);


/**
 * @brief Insert data to the node evenly distibuted
 *
 * @param node    node to insert data to
 * @param data    data to insert
 * @return int    SUCCESS or ERROR
 */
int
bin_node_insert(BinNode* node, void* data);


/**
 * @brief Insert data to the node sorted - smaller values are on the left
 *
 * @param node    node to insert data to
 * @param data    data to insert
 * @param metric  metric to evaluate data
 * @return int    SUCCESS or ERROR
 */
int
bin_node_insert_sorted(BinNode* node, void* data, double (*metric)(void*));


/**
 * @brief Update child count up the chain
 *
 * @param node    node to update from
 * @return int    SUCCESS or ERROR
 */
int
bin_node_count_up(BinNode* node);


/**
 * @brief Print node tree
 *
 * @param node        node to print from
 * @param indent      node indentation
 * @param print_data  data print function
 * @return int        SUCCESS or ERROR
 */
int
print_node(BinNode* node, int indent, void (*print_data)(void*));


#endif
