/**
 * @file Vec3.h
 * @author Antonin Nepras
 * @brief Vec3 structure
 * @version 0.1
 * @date 2022-08-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __vec3_h__
#define __vec3_h__

#include <math.h>


/**
 * @brief 3D Vector structure
 * 
 */
typedef struct
{
  double x;
  double y;
  double z;
} Vec3;


/**
 * @brief Vector addition
 * 
 * @param v1 
 * @param v2 
 * @return Vec3 
 */
Vec3 
vec3_add(Vec3 v1, Vec3 v2);


/**
 * @brief Vector subtraction
 * 
 * @param v1 
 * @param v2 
 * @return Vec3 
 */
Vec3
vec3_sub(Vec3 v1, Vec3 v2);


/**
 * @brief Vector scalar multiplication
 * 
 * @param v 
 * @param m 
 * @return Vec3 
 */
Vec3
vec3_mul(Vec3 v, double m);


/**
 * @brief Vector scalar division
 * 
 * @param v 
 * @param d 
 * @return Vec3 
 */
Vec3
vec3_div(Vec3 v, double d);


/**
 * @brief Vector dot product
 * 
 * @param v1 
 * @param v2 
 * @return double 
 */
double
vec3_dot(Vec3 v1, Vec3 v2);


/**
 * @brief Vector cross product
 * 
 * @param v1 
 * @param v2 
 * @return Vec3 
 */
Vec3
vec3_cross(Vec3 v1, Vec3 v2);


/**
 * @brief Vector size
 * 
 * @param v 
 * @return double 
 */
double
vec3_size(Vec3 v);


/**
 * @brief Vector normalise
 * 
 * @param v 
 * @return Vec3 
 */
Vec3
vec3_norm(Vec3 v);



#endif
