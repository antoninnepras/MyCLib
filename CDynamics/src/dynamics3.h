/**
 * @file dynamics3.h
 * @author Antonin Nepras
 * @brief 3D Dynamics
 * @version 0.1
 * @date 2022-08-12
 *
 * @copyright Copyright (c) 2022
 *
 */


#include <stdlib.h>

#include "kinematics3.h"
#include "vec3.h"


/**
 * @brief 3D dynamics material point
 *
 */
typedef struct
{
  Kin3 kin;
  double mass;
} Dyn3;


/**
 * @brief 3D central force field
 *
 */
typedef struct
{
  Vec3 pos;
  double intensity;
  int dpower;
} FF3Central;


/**
 * @brief Apply force to the material point
 * 
 * @param dyn 
 * @param force 
 */
void
dyn3_apply_force(Dyn3* dyn, Vec3 force);


/**
 * @brief Move dynamics
 * 
 * @param dyn 
 * @param time 
 */
void
dyn3_move(Dyn3* dyn, double time);


/**
 * @brief Move dynamics and get moved distance
 * 
 * @param dyn 
 * @param time 
 * @param dist 
 */
void
dyn3_move_dist(Dyn3* dyn, double time, double* dist);


/**
 * @brief Apply central force field to the dynamics
 * 
 * @param dyn 
 * @param ff 
 */
void
dyn3_apply_ffcentral(Dyn3* dyn, FF3Central ff);
