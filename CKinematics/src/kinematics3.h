/**
 * @file kinematics2.h
 * @author Antonin Nepras
 * @brief 3D Kinematics
 * @version 0.1
 * @date 2022-08-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __kinematics2_h__
#define __kinematics2_h__

#include <stdlib.h>
#include "vec3.h"


/**
 * @brief 3D kinematics material point
 * 
 */
typedef struct
{
  Vec3 pos;
  Vec3 vel;
  Vec3 acc;
} Kin3;


/**
 * @brief Move material point
 * 
 * @param kin 
 * @param time
 */
void
kin3_move(Kin3* kin, double time);


/**
 * @brief Move material point and get moved distance
 * 
 * @param kin 
 * @param time 
 * @param dist 
 */
void 
kin3_move_dist(Kin3* kin, double time, double* dist);


#endif
