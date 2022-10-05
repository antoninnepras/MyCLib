/**
 * @file Vec2.h
 * @author Antonin Nepras
 * @brief Vec2 structure
 * @version 0.1
 * @date 2022-08-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __vec2_h__
#define __vec2_h__

#include <math.h>


/**
 * @brief 2D Vector structure
 *
 */
typedef struct
{
  double x;
  double y;
} Vec2;


/**
 * @brief Init vector
 *
 * @param x
 * @param y
 * @return Vec2
 */
Vec2
vec2_init(double x, double y);


/**
 * @brief Vector addition
 *
 * @param v1
 * @param v2
 * @return Vec2
 */
Vec2
vec2_add(Vec2 v1, Vec2 v2);


/**
 * @brief Vector subtraction
 *
 * @param v1
 * @param v2
 * @return Vec2
 */
Vec2
vec2_sub(Vec2 v1, Vec2 v2);


/**
 * @brief Vector scalar multiplication
 *
 * @param v
 * @param m
 * @return Vec2
 */
Vec2
vec2_mul(Vec2 v, double m);


/**
 * @brief Vector scalar division
 *
 * @param v
 * @param d
 * @return Vec2
 */
Vec2
vec2_div(Vec2 v, double d);


/**
 * @brief Vector dot product
 *
 * @param v1
 * @param v2
 * @return double
 */
double
vec2_dot(Vec2 v1, Vec2 v2);


/**
 * @brief Vector size
 *
 * @param v
 * @return double
 */
double
vec2_size(Vec2 v);


/**
 * @brief Vector normalise
 *
 * @param v
 * @return Vec2
 */
Vec2
vec2_norm(Vec2 v);


/**
 * @brief Vector rotation
 *
 * @param v
 * @param rad
 * @return Vec2
 */
Vec2
vec2_rotate(Vec2 v, double rad);


#endif
