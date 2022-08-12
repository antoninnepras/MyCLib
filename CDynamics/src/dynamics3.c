/**
 * @file dynamics3.c
 * @author Antonin Nepras
 * @brief 3D Dynamics Implementation
 * @version 0.1
 * @date 2022-08-12
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "dynamics3.h"


void
dyn3_apply_force(Dyn3* dyn, Vec3 force)
{
  dyn->kin.acc = vec3_add(dyn->kin.acc, vec3_div(force, dyn->mass));
}


void
dyn3_move(Dyn3* dyn, double time)
{
  kin3_move(&dyn->kin, time);
}


void
dyn3_move_dist(Dyn3* dyn, double time, double* dist)
{
  kin3_move_dist(&dyn->kin, time, dist);
}


void
dyn3_apply_ffcentral(Dyn3* dyn, FF3Central ff)
{
  Vec3 dir = vec3_sub(ff.pos, dyn->kin.pos);
  double dist = vec3_size(dir);
  
  double intensity = ff.intensity / pow(dist, ff.dpower);
  Vec3 force = vec3_mul(vec3_norm(dir), intensity);
  dyn3_apply_force(dyn, force);
}


