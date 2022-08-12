/**
 * @file dynamics2.h
 * @author Antonin Nepras
 * @brief 2D Dynamics implementation
 * @version 0.1
 * @date 2022-08-12
 *
 * @copyright Copyright (c) 2022
 *
 */


#include <stdio.h>
#include "dynamics2.h"


void
dyn2_apply_force(Dyn2* dyn, Vec2 force)
{
  dyn->kin.acc = vec2_add(dyn->kin.acc, vec2_div(force, dyn->mass));
}


void
dyn2_move(Dyn2* dyn, double time)
{
  kin2_move(&dyn->kin, time);
}


void
dyn2_move_dist(Dyn2* dyn, double time, double* dist)
{
  kin2_move_dist(&dyn->kin, time, dist);
}


void
dyn2_apply_ffcentral(Dyn2* dyn, FF2Central ff)
{
  Vec2 dir = vec2_sub(ff.pos, dyn->kin.pos);
  double dist = vec2_size(dir);
  
  double intensity = ff.intensity / pow(dist, ff.dpower);
  Vec2 force = vec2_mul(vec2_norm(dir), intensity);
  dyn2_apply_force(dyn, force);
}
