#ifndef __map_h__
#define __map_h__

#include "list.h"
#include <stdio.h>

typedef struct
{
  int r;
  int c;
  List* data;
} Map;


Map*
map_new(int r, int c);


void
map_del(Map* map);


void
map_append_row(Map* map);


void
map_prepend_row(Map* map);


void
map_append_column(Map* map);


void
map_prepend_column(Map* map);


List*
map_pop_back_row(Map* map);


List*
map_pop_front_row(Map* map);


List*
map_pop_back_column(Map* map);


List*
map_pop_front_column(Map* map);


List*
map_remove_row(Map* map, int r);


List*
map_remove_column(Map* map, int c);


void*
map_get(Map* map, int r, int c);


void
map_set(Map* map, int r, int c, void* data);


void
map_insert_row(Map* map, int r);


void
map_insert_column(Map* map, int c);


void***
map_to_2d_array(Map* map);


#endif
