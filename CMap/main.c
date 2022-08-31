#include "src/map.h"
#include <stdio.h>
#include <string.h>

typedef char Name[16];

Name*
name_new(const char* name);


int
main(int argc, const char** argv)
{
  Map* map = map_new(3, 2);
  map_set(map, 0, 0, name_new("Ivan"));
  map_set(map, 1, 1, name_new("Frank"));
  map_set(map, 2, 1, name_new("George"));
  map_insert_row(map, 1);
  map_set(map, 1, 1, name_new("Ludvig"));

  printf("%s\n", *(Name*)map_get(map, 3, 1));
  printf("%s\n", *(Name*)map_get(map, 0, 0));
  printf("%s\n", *(Name*)map_get(map, 1, 1));

  map_insert_column(map, 0);
  map_set(map, 0, 0, name_new("Olivia"));
  printf("%s\n", *(Name*)map_get(map, 0, 1));


  // free map items
  for (int i = 0; i < map->r; ++i) {
    for (int j = 0; j < map->c; ++j) {
      void* tmp = map_get(map, i, j);
      if (tmp != NULL)
        free(tmp);
    }
  }
  map_del(map);
}


Name*
name_new(const char* name_or)
{
  Name* name = (Name*)malloc(sizeof(Name));
  strncpy(*name, name_or, 15);
  return name;
}
