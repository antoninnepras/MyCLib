/**
 * @file vec4.h
 * @author Antonin Nepras
 * @brief Vec4 structure
 * @version 0.1
 * @date 2022-10-05
 *
 * @copyright Copyright (c) 2022
 *
 */


#ifndef __vec4_h__
#define __vec4_h__

#include <math.h>


/**
 * @brief 4D Vector structure
 *
 */
typedef struct
{
  double x;
  double y;
  double z;
  double w;
} Vec4;


/**
 * @brief Init vector
 *
 * @param x
 * @param y
 * @param z
 * @param w
 * @return Vec2
 */
Vec4
vec4_init(double x, double y, double z, double w);


/**
 * @brief Vector addition
 *
 * @param v1
 * @param v2
 * @return Vec4
 */
Vec4
vec4_add(Vec4 v1, Vec4 v2);


/**
 * @brief Vector subtraction
 *
 * @param v1
 * @param v2
 * @return Vec4
 */
Vec4
vec4_sub(Vec4 v1, Vec4 v2);


/**
 * @brief Vector scalar multiplication
 *
 * @param v
 * @param m
 * @return Vec4
 */
Vec4
vec4_mul(Vec4 v, double m);


/**
 * @brief Vector scalar division
 *
 * @param v
 * @param d
 * @return Vec4
 */
Vec4
vec4_div(Vec4 v, double d);


/**
 * @brief Vector dot product
 *
 * @param v1
 * @param v2
 * @return double
 */
double
vec4_dot(Vec4 v1, Vec4 v2);


/**
 * @brief Vector size
 *
 * @param v
 * @return double
 */
double
vec4_size(Vec4 v);


/**
 * @brief Vector normalise
 *
 * @param v
 * @return Vec4
 */
Vec4
vec4_norm(Vec4 v);


#endif
