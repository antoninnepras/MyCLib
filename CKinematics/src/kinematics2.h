/**
 * @file kinematics2.h
 * @author Antonin Nepras
 * @brief 2D Kinematics
 * @version 0.1
 * @date 2022-08-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __kinematics2_h__
#define __kinematics2_h__

#include <stdlib.h>
#include "vec2.h"


/**
 * @brief 2D kinematics material point
 * 
 */
typedef struct
{
  Vec2 pos;
  Vec2 vel;
  Vec2 acc;
} Kin2;


/**
 * @brief Move material point
 * 
 * @param kin 
 * @param time
 */
void
kin2_move(Kin2* kin, double time);


/**
 * @brief Move material point and get moved distance
 * 
 * @param kin 
 * @param time 
 * @param dist 
 */
void 
kin2_move_dist(Kin2* kin, double time, double* dist);


#endif
