/**
 * @file list.h
 * @author Antonin Nepras
 * @brief simple linked list implementation
 * @version 0.1
 * @date 2022-08-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __list_h__
#define __list_h__


#include <stdlib.h>


/**
 * @brief List node
 * 
 */
typedef struct
{
  void* data;
  void* next;
  void* prev;
} LNode;


/**
 * @brief Double linked list
 * 
 */
typedef struct
{
  LNode* begin;
  LNode* end;
  int size;
} List;


/**
 * @brief Create new list node
 * 
 * @param data    node data
 * @param prev    previous node
 * @param next    next node
 * @return LNode* 
 */
LNode*
lnode_new(void* data, void* prev, void* next);


/**
 * @brief Create new list
 * 
 * @return List* 
 */
List*
list_new(void);


/**
 * @brief Delete list
 * 
 * @param list 
 */
void
list_del(List* list);


/**
 * @brief Add data to the end of the list
 * 
 * @param list 
 * @param data 
 */
void
list_append(List* list, void* data);


/**
 * @brief Add data to the front of the list
 * 
 * @param list 
 * @param data 
 */
void
list_prepend(List* list, void* data);


/**
 * @brief Remove data form end of the list
 * 
 * @param list 
 * @return void* 
 */
void*
list_pop_back(List* list);


/**
 * @brief Remove data from the front of the list
 * 
 * @param list 
 * @return void* 
 */
void*
list_pop_front(List* list);


/**
 * @brief Insert data to the list
 * 
 * @param list 
 * @param data 
 * @param index 
 */
void
list_insert(List* list, void* data, int index);


/**
 * @brief Get data from the list
 * 
 * @param list 
 * @param index 
 * @return void* 
 */
void*
list_get(List* list, int index);


/**
 * @brief Remove data from the list
 * 
 * @param list 
 * @param index 
 * @return void* 
 */
void*
list_remove(List* list, int index);


/**
 * @brief Get data from the list as dynamicaly allocated array
 * 
 * @param list 
 * @return void** 
 */
void**
list_to_array_dyn(List* list, int* size);


/**
 * @brief Fill array with list data (assumes that array is big enough)
 * 
 * @param list 
 * @param array 
 */
void
list_fill_array(List* list, void** array);


/**
 * @brief Create list from array
 * 
 * @param data_array 
 * @param size 
 * @return List* 
 */
List*
list_from_array(void** data_array, int size);


#endif
