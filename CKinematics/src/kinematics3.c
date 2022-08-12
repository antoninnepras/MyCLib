/**
 * @file kinematics2.h
 * @author Antonin Nepras
 * @brief 3D Kinematics implementation
 * @version 0.1
 * @date 2022-08-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "kinematics3.h"


void
kin3_move(Kin3* kin, double time)
{
  kin->pos = vec3_add(kin->pos, vec3_mul(kin->vel, time));
  kin->vel = vec3_add(kin->vel, vec3_mul(kin->acc, time));
}


void 
kin3_move_dist(Kin3* kin, double time, double* dist)
{
  if (dist != NULL) {
    *dist = vec3_size(vec3_mul(kin->vel, time));
  }
  
  kin->pos = vec3_add(kin->pos, vec3_mul(kin->vel, time));
  kin->vel = vec3_add(kin->vel, vec3_mul(kin->acc, time));
}
