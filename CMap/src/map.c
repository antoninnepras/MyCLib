#include "map.h"


Map*
map_new(int r, int c)
{
  Map* map = (Map*)malloc(sizeof(Map));
  map->r = r;
  map->c = c;
  map->data = list_new();
  for (int i = 0; i < r; ++i) {
    List* tmp = list_new();
    for (int j = 0; j < c; ++j) {
      list_append(tmp, NULL);
    }

    list_append(map->data, (void*)tmp);
  }

  return map;
}


void
map_del(Map* map)
{
  if (map == NULL) {
    return;
  }

  while (map->data->size > 0) {
    list_del(list_pop_back(map->data));
  }
  list_del(map->data);

  free(map);
}


void
map_append_row(Map* map)
{
  if (map == NULL) {
    return;
  }

  List* tmp = list_new();
  for (int i = 0; i < map->c; ++i) {
    list_append(tmp, NULL);
  }

  list_append(map->data, (void*)tmp);
}


void
map_prepend_row(Map* map)
{
  if (map == NULL) {
    return;
  }

  List* tmp = list_new();
  for (int i = 0; i < map->c; ++i) {
    list_append(tmp, NULL);
  }

  list_prepend(map->data, (void*)tmp);
}


void
map_append_column(Map* map)
{
  if (map == NULL) {
    return;
  }

  for (int i = 0; i < map->r; ++i) {
    list_append((List*)list_get(map->data, i), NULL);
  }
}


void
map_prepend_column(Map* map)
{
  if (map == NULL) {
    return;
  }

  for (int i = 0; i < map->r; ++i) {
    list_prepend((List*)list_get(map->data, i), NULL);
  }
}


List*
map_pop_back_row(Map* map)
{
  if (map == NULL) {
    return NULL;
  }

  return (List*)list_pop_back(map->data);
}


List*
map_pop_front_row(Map* map)
{
  if (map == NULL) {
    return NULL;
  }

  return (List*)list_pop_front(map->data);
}


List*
map_pop_back_column(Map* map)
{
  if (map == NULL) {
    return NULL;
  }

  List* tmp = list_new();

  for (int i = 0; i < map->r; ++i) {
    list_append(tmp, list_pop_back((List*)list_get(map->data, i)));
  }

  return tmp;
}


List*
map_pop_front_column(Map* map)
{
  if (map == NULL) {
    return NULL;
  }

  List* tmp = list_new();

  for (int i = 0; i < map->r; ++i) {
    list_append(tmp, list_pop_front((List*)list_get(map->data, i)));
  }

  return tmp;
}


List*
map_remove_row(Map* map, int r)
{
  if (map == NULL) {
    return NULL;
  }

  return (List*)list_remove(map->data, r);
}


List*
map_remove_column(Map* map, int c)
{
  if (map == NULL) {
    return NULL;
  }

  List* tmp = list_new();

  for (int i = 0; i < map->r; ++i) {
    list_append(tmp, list_remove((List*)list_get(map->data, i), c));
  }

  return tmp;
}


void*
map_get(Map* map, int r, int c)
{
  if (map == NULL) {
    return NULL;
  }

  return list_get((List*)list_get(map->data, r), c);
}


void
map_set(Map* map, int r, int c, void* data)
{
  if (map == NULL) {
    return;
  }

  List* row = (List*)list_get(map->data, r);

  LNode* node = row->begin;
  for (int i = 0; i < c; ++i) {
    node = node->next;
  }

  node->data = data;
}


void
map_insert_row(Map* map, int r)
{
  if (map == NULL) {
    return;
  }

  List* tmp = list_new();
  for (int i = 0; i < map->c; ++i) {
    list_append(tmp, NULL);
  }

  list_insert(map->data, (void*)tmp, r);
}


void
map_insert_column(Map* map, int c)
{
  if (map == NULL) {
    return;
  }

  for (int i = 0; i < map->r; ++i) {
    list_insert((List*)list_get(map->data, i), NULL, c);
  }
}
