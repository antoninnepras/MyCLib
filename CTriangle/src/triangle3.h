/**
 * @file triangle3.h
 * @author Antonin Nepras
 * @brief 3D triangles
 * @version 0.1
 * @date 2022-10-04
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __triangle3_h__
#define __triangle3_h__


#include <stdlib.h>

#include "mat33.h"


typedef struct
{
  Vec3 vertices[3];
} Triangle3;


Triangle3
triangle3_init(Vec3 v1, Vec3 v2, Vec3 v3);


Triangle3
triangle3_move(Triangle3 t, Vec3 v);


Triangle3
triangle3_tansform(Triangle3 t, Mat33 m);


Vec3
triangle3_normal(Triangle3 t);

#endif
