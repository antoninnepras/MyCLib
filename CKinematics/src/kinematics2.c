/**
 * @file kinematics2.c
 * @author Antonin Nepras
 * @brief 2D Kinematics implementation
 * @version 0.1
 * @date 2022-08-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "kinematics2.h"


void
kin2_move(Kin2* kin, double time)
{
  kin->pos = vec2_add(kin->pos, vec2_mul(kin->vel, time));
  kin->vel = vec2_add(kin->vel, vec2_mul(kin->acc, time));
}


void 
kin2_move_dist(Kin2* kin, double time, double* dist)
{
  if (dist != NULL) {
    *dist = vec2_size(vec2_mul(kin->vel, time));
  }

  kin->pos = vec2_add(kin->pos, vec2_mul(kin->vel, time));
  kin->vel = vec2_add(kin->vel, vec2_mul(kin->acc, time));
}
