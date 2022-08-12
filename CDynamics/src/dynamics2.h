/**
 * @file dynamics2.h
 * @author Antonin Nepras
 * @brief 2D Dynamics
 * @version 0.1
 * @date 2022-08-12
 *
 * @copyright Copyright (c) 2022
 *
 */


#ifndef __dynamics2_h__
#define __dynamics2_h__


#include <stdlib.h>

#include "kinematics2.h"
#include "vec2.h"


/**
 * @brief 2D dynamics material point
 *
 */
typedef struct
{
  Kin2 kin;
  double mass;
} Dyn2;


/**
 * @brief 2D central force field
 *
 */
typedef struct
{
  Vec2 pos;
  double intensity;
  int dpower;
} FF2Central;


/**
 * @brief 2D homogeneous force field
 *
 */
typedef struct
{
  Vec2 pos;
  Vec2 norm;
  double intensity;
  int dpower;
} FF2Homogeneous;


/**
 * @brief Apply force to the material point
 * 
 * @param dyn 
 * @param force 
 */
void
dyn2_apply_force(Dyn2* dyn, Vec2 force);


/**
 * @brief Move dynamics
 * 
 * @param dyn 
 * @param time 
 */
void
dyn2_move(Dyn2* dyn, double time);


/**
 * @brief Move dynamics and get moved distance
 * 
 * @param dyn 
 * @param time 
 * @param dist 
 */
void
dyn2_move_dist(Dyn2* dyn, double time, double* dist);


/**
 * @brief Apply central force field to the dynamics
 * 
 * @param dyn 
 * @param ff 
 */
void
dyn2_apply_ffcentral(Dyn2* dyn, FF2Central ff);


#endif
