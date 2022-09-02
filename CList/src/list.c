/**
 * @file list.c
 * @author Antonin Nepras
 * @brief CList functions implementation
 * @version 0.1
 * @date 2022-08-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "list.h"


LNode*
lnode_new(void* data, void* prev, void* next)
{
  LNode* node = (LNode*)malloc(sizeof(LNode));
  node->data = data;
  node->prev = prev;
  node->next = next;
  return node;
}


List*
list_new(void)
{
  List* list = (List*)malloc(sizeof(List));
  list->begin = NULL;
  list->end = NULL;
  list->size = 0;
  return list;
}


void
list_del(List* list)
{
  if (list == NULL) {
    return;
  }

  while (list->size > 0) {
    list_pop_back(list);
  }

  free(list);
}


void
list_append(List* list, void* data)
{
  if (list == NULL) {
    return;
  }

  if (list->size == 0) {
    list->begin = lnode_new(data, NULL, NULL);
    list->end = list->begin;
  } else {
    list->end->next = lnode_new(data, list->end, NULL);
    list->end = list->end->next;
  }

  list->size++;
}


void
list_prepend(List* list, void* data)
{
  if (list == NULL) {
    return;
  }

  if (list->size == 0) {
    list->begin = lnode_new(data, NULL, NULL);
    list->end = list->begin;
  } else {
    list->begin->prev = lnode_new(data, NULL, list->begin);
    list->begin = list->begin->prev;
  }

  list->size++;
}


void*
list_pop_back(List* list)
{
  if (list == NULL || list->size == 0) {
    return NULL;
  }

  void* data = list->end->data;
  LNode* tmp = list->end->prev;
  free(list->end);
  list->end = tmp;

  if (tmp == NULL) {
    list->begin = NULL;
  } else {
    list->end->next = NULL;
  }

  list->size--;

  return data;
}


void*
list_pop_front(List* list)
{
  if (list == NULL || list->size == 0) {
    return NULL;
  }

  void* data = list->begin->data;
  LNode* tmp = list->begin->next;
  free(list->begin);
  list->begin = tmp;
  list->begin->prev = NULL;
  list->size--;

  return data;
}


void
list_insert(List* list, void* data, int index)
{
  if (list == NULL || index < 0) {
    return;
  }

  if (index > list->size) {
    return;
  }


  LNode* tmp;
  tmp = list->begin;
  for (int i = 0; i < index; ++i) {
    tmp = tmp->next;
  }

  if (tmp != NULL) {
    LNode* tmpn = lnode_new(data, tmp->prev, tmp);
    tmp->prev = tmpn;

    if (tmpn->prev != NULL) {
      ((LNode*)tmpn->prev)->next = tmpn;
    } else {
      list->begin = tmpn;
    }
    list->size++;
  } else {
    list_append(list, data);
  }
}


void*
list_get(List* list, int index)
{
  if (list == NULL || index < 0 || index >= list->size) {
    return NULL;
  }

  LNode* tmp = list->begin;
  for (int i = 0; i < index; ++i) {
    tmp = tmp->next;
  }

  return tmp->data;
}


void*
list_remove(List* list, int index)
{
  if (list == NULL || index < 0 || index >= list->size) {
    return NULL;
  }

  LNode* tmp = list->begin;
  for (int i = 0; i < index; ++i) {
    tmp = tmp->next;
  }

  void* data = tmp->data;

  if (tmp->prev != NULL) {
    ((LNode*)tmp->prev)->next = tmp->next;
  } else {
    list->begin = tmp->next;
  }

  if (tmp->next != NULL) {
    ((LNode*)tmp->next)->prev = tmp->prev;
  } else {
    list->end = tmp->prev;
  }

  free(tmp);

  list->size--;

  return data;
}


void**
list_to_array_dyn(List* list, int* size)
{
  if (list == NULL || list->size == 0) {
    if (size != NULL)
      *size = -1;
    return NULL;
  }

  void** data_array = (void**)malloc(sizeof(void*) * list->size);
  if (data_array == NULL) {
    if (size != NULL)
      *size = 0;
    return NULL;
  }

  LNode* tmp = list->begin;
  for (int i = 0; i < list->size; ++i) {
    data_array[i] = tmp->data;
    tmp = tmp->next;
  }

  if (size != NULL)
    *size = list->size;
  return data_array;
}


void
list_fill_array(List* list, void** array)
{
  if (list == NULL || array == NULL) {
    return;
  }

  LNode* tmp = list->begin;
  for (int i = 0; i < list->size; ++i) {
    array[i] = tmp->data;
    tmp = tmp->next;
  }
}


List*
list_from_array(void** data_array, int size)
{
  if (data_array == NULL) {
    return NULL;
  }

  List* list = list_new();
  for (int i = 0; i < size; ++i) {
    list_append(list, data_array[i]);
  }

  return list;
}


void
list_do_for_all(List* list, void (*action)(void* data))
{
  if (list == NULL || action == NULL) {
    return;
  }

  LNode* tmp = list->begin;
  while (tmp != NULL) {
    action(tmp->data);
    tmp = tmp->next;
  }

  return;
}
