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
 * @brief Binary tree structure
 *
 */
typedef struct
{
  BinNode* root;
  size_t size;
} BinTree;


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
 * @brief Update child count down the chain
 *
 * @param node    node to update from
 * @return int    SUCCESS or ERROR
 */
int
bin_node_count_down(BinNode* node);


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


/**
 * @brief Create new binary tree structure
 *
 * @return BinTree*
 */
BinTree*
bin_tree_new(void);


/**
 * @brief Delete binary tree structure
 *
 * @param tree    binary tree
 * @return int    SUCCESS or ERROR
 */
int
bin_tree_del(BinTree** tree);


/**
 * @brief Delete binary tree structure and its data
 *
 * @param tree      binary tree
 * @param data_del  data delete function
 * @return int      SUCCESS or ERROR
 */
int
bin_tree_del_all(BinTree** tree, void (*data_del)(void*));


/**
 * @brief Insert data to binary tree evenly distributed
 *
 * @param tree    binary tree
 * @param data    data to insert
 * @return int    SUCCESS or ERROR
 */
int
bin_tree_insert(BinTree* tree, void* data);


/**
 * @brief Insert data to binary tree based on metric - smaller on the left
 *
 * @param tree    binary tree
 * @param data    data to insert
 * @param metric  metric to use for data
 * @return int    SUCCESS or ERROR
 */
int
bin_tree_insert_sorted(BinTree* tree, void* data, double (*metric)(void*));


/**
 * @brief Get the most left data in binary tree
 *
 * @param tree    binary tree
 * @param data    found data from binary tree
 * @return int    SUCCESS or ERROR
 */
int
bin_tree_get_left(BinTree* tree, void** data);


/**
 * @brief Get the most right data in binary tree
 *
 * @param tree    binary tree
 * @param data    found data from binary tree
 * @return int    SUCCESS or ERROR
 */
int
bin_tree_get_right(BinTree* tree, void** data);


/**
 * @brief Pop the most left data in binary tree
 *
 * @param tree    binary tree
 * @param data    found data from binary tree
 * @return int    SUCCESS or ERROR
 */
int
bin_tree_pop_left(BinTree* tree, void** data);


/**
 * @brief Pop the most right data in binary tree
 *
 * @param tree    binary tree
 * @param data    found dta from binary tree
 * @return int    SUCCESS or ERROR
 */
int
bin_tree_pop_right(BinTree* tree, void** data);


#endif
