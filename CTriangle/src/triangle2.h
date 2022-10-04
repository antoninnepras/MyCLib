#ifndef __triangle2_h__
#define __triangle2_h__


#include <stdlib.h>

#include "mat22.h"


typedef struct
{
  Vec2 vertices[3];
} Triangle2;


Triangle2
triangle2_init(Vec2 v1, Vec2 v2, Vec2 v3);


Triangle2
triangle2_move(Triangle2 t, Vec2 v);


Triangle2
triangle2_tansform(Triangle2 t, Mat22 m);


#endif
