/**
 * @file dyn_matrix.h
 * @author Antonin Nepras
 * @brief General purpose matrices of all sizes
 * @version 0.1
 * @date 2022-09-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __dyn_matrix_h__
#define __dyn_matrix_h__

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * @brief Variable size matrix structure
 *
 */
typedef struct
{
  int r;
  int c;
  double** data;
} Matrix;


/**
 * @brief Create new matrix structure
 *
 * @param r           rows
 * @param c           columns
 * @return Matrix*
 */
Matrix*
matrix_new(int r, int c);


/**
 * @brief Destroy matrix structure
 *
 * @param m
 */
void
matrix_del(Matrix* m);


/**
 * @brief Create identity matrix
 *
 * @param size
 * @return Matrix*
 */
Matrix*
matrix_eye(int size);


/**
 * @brief Add two matrices - new matrix is allocated
 *
 * @param m1
 * @param m2
 * @return Matrix*
 */
Matrix*
matrix_add(Matrix* m1, Matrix* m2);


/**
 * @brief Substract two matrices - new matrix is allocated
 *
 * @param m1
 * @param m2
 * @return Matrix*
 */
Matrix*
matrix_sub(Matrix* m1, Matrix* m2);


/**
 * @brief Multiply two matrices - new matrix is allocated
 *
 * @param m1
 * @param m2
 * @return Matrix*
 */
Matrix*
matrix_mul(Matrix* m1, Matrix* m2);


/**
 * @brief Scale matrix by s
 *
 * @param m
 * @param s
 * @return Matrix*
 */
Matrix*
matrix_scale(Matrix* m, double s);


/**
 * @brief Add other matrix to this matrix
 *
 * @param m_this
 * @param m_other
 */
void
matrix_this_add(Matrix* m_this, Matrix* m_other);


/**
 * @brief Sub other matrix from this matrix
 *
 * @param m_this
 * @param m_other
 */
void
matrix_this_sub(Matrix* m_this, Matrix* m_other);


/**
 * @brief Multiply other matrix with this matrix and write result to this matrix
 *
 * @param m_this
 * @param m_other
 */
void
matrix_this_mul(Matrix* m_this, Matrix* m_other);


/**
 * @brief Scale this matrix by s
 *
 * @param m_this
 * @param s
 */
void
matrix_this_scale(Matrix* m_this, double s);


/**
 * @brief Copy matrix to new matrix - new matrix is allocated
 *
 * @param m
 * @return Matrix*
 */
Matrix*
matrix_copy(Matrix* m);


/**
 * @brief Create matrix without r-th row and c-th column
 *
 * @param m
 * @param r
 * @param c
 * @return Matrix*
 */
Matrix*
matrix_rem_rc(Matrix* m, int r, int c);


/**
 * @brief Matrix determinant
 *
 * @param m
 * @return double
 */
double
matrix_det(Matrix* m);


/**
 * @brief Create transpose matrix
 *
 * @param m
 * @return Matrix*
 */
Matrix*
matrix_transpose(Matrix* m);


/**
 * @brief Transpose this matrix
 *
 * @param m_this
 */
void
matrix_this_transpose(Matrix* m_this);


/**
 * @brief Create adjung matrix of m
 *
 * @param m
 * @return Matrix*
 */
Matrix*
matrix_adj(Matrix* m);


/**
 * @brief Create inverse matrix
 *
 * @param m
 * @return Matrix*
 */
Matrix*
matrix_inverse(Matrix* m);

#endif
