/**
 * @file dyn_matrix.c
 * @author Antonin Nepras
 * @brief DynMatrix implementation
 * @version 0.1
 * @date 2022-09-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "dyn_matrix.h"


Matrix*
matrix_new(int r, int c)
{
  Matrix* m = (Matrix*)malloc(sizeof(Matrix));
  if (m == NULL) {
    return NULL;
  }

  m->data = (double**)malloc(sizeof(double*) * r);
  if (m->data == NULL) {
    free(m);
    return NULL;
  }

  for (int i = 0; i < r; ++i) {
    m->data[i] = (double*)calloc(sizeof(double), c);
    if (m->data[i] == NULL) {
      for (int j = 0; j < i; ++j) {
        free(m->data[j]);
      }
      free(m->data);
      free(m);
      return NULL;
    }
  }

  m->r = r;
  m->c = c;
  return m;
}


void
matrix_del(Matrix* m)
{
  if (m == NULL) {
    return;
  }

  for (int i = 0; i < m->r; ++i) {
    free(m->data[i]);
  }

  free(m->data);
  free(m);
}


Matrix*
matrix_eye(int size)
{
  if (size < 1) {
    return NULL;
  }

  Matrix* eye = matrix_new(size, size);
  for (int i = 0; i < size; ++i) {
    eye->data[i][i] = 1;
  }

  return eye;
}


Matrix*
matrix_add(Matrix* m1, Matrix* m2)
{
  if (m1 == NULL || m2 == NULL) {
    return NULL;
  }

  if (m1->r != m2->r || m1->c != m2->c) {
    return NULL;
  }

  Matrix* res = matrix_new(m1->r, m1->c);
  for (int i = 0; i < m1->r; ++i) {
    for (int j = 0; j < m1->c; ++j) {
      res->data[i][j] = m1->data[i][j] + m2->data[i][j];
    }
  }

  return res;
}


Matrix*
matrix_sub(Matrix* m1, Matrix* m2)
{
  if (m1 == NULL || m2 == NULL) {
    return NULL;
  }

  if (m1->r != m2->r || m1->c != m2->c) {
    return NULL;
  }

  Matrix* res = matrix_new(m1->r, m1->c);
  for (int i = 0; i < m1->r; ++i) {
    for (int j = 0; j < m1->c; ++j) {
      res->data[i][j] = m1->data[i][j] - m2->data[i][j];
    }
  }

  return res;
}


Matrix*
matrix_mul(Matrix* m1, Matrix* m2)
{
  if (m1 == NULL || m2 == NULL) {
    return NULL;
  }

  if (m1->c != m2->r) {
    return NULL;
  }

  Matrix* res = matrix_new(m1->r, m2->c);
  for (int i = 0; i < m1->r; ++i) {
    for (int j = 0; j < m2->c; ++j) {
      int tmp = 0;
      for (int k = 0; k < m1->c; ++k) {
        tmp += m1->data[i][k] * m2->data[k][j];
      }
      res->data[i][j] = tmp;
    }
  }

  return res;
}


Matrix*
matrix_scale(Matrix* m, double s)
{
  if (m == NULL) {
    return NULL;
  }

  Matrix* res = matrix_copy(m);
  for (int i = 0; i < m->r; ++i) {
    for (int j = 0; j < m->c; ++j) {
      res->data[i][j] *= s;
    }
  }

  return res;
}


void
matrix_this_add(Matrix* m_this, Matrix* m_other)
{
  if (m_this == NULL || m_other == NULL) {
    return;
  }

  if (m_this->r != m_other->r || m_this->c != m_other->c) {
    return;
  }

  for (int i = 0; i < m_this->r; ++i) {
    for (int j = 0; j < m_this->c; ++j) {
      m_this->data[i][j] += m_other->data[i][j];
    }
  }
}


void
matrix_this_sub(Matrix* m_this, Matrix* m_other)
{
  if (m_this == NULL || m_other == NULL) {
    return;
  }

  if (m_this->r != m_other->r || m_this->c != m_other->c) {
    return;
  }

  for (int i = 0; i < m_this->r; ++i) {
    for (int j = 0; j < m_this->c; ++j) {
      m_this->data[i][j] -= m_other->data[i][j];
    }
  }
}


void
matrix_this_mul(Matrix* m_this, Matrix* m_other)
{
  if (m_this == NULL || m_other == NULL) {
    return;
  }

  Matrix* res = matrix_new(m_this->r, m_other->c);
  for (int i = 0; i < m_this->r; ++i) {
    for (int j = 0; j < m_other->c; ++j) {
      int tmp = 0;
      for (int k = 0; k < m_this->c; ++k) {
        tmp += m_this->data[i][k] * m_other->data[k][j];
      }
      res->data[i][j] = tmp;
    }
  }

  free(m_this->data);
  m_this->data = res->data;
  m_this->r = res->r;
  m_this->c = res->c;
  free(res);
}


void
matrix_this_scale(Matrix* m_this, double s)
{
  if (m_this == NULL) {
    return;
  }

  for (int i = 0; i < m_this->r; ++i) {
    for (int j = 0; j < m_this->c; ++j) {
      m_this->data[i][j] *= s;
    }
  }
}


Matrix*
matrix_copy(Matrix* m)
{
  if (m == NULL) {
    return NULL;
  }

  Matrix* copy = matrix_new(m->r, m->c);
  for (int i = 0; i < m->r; ++i) {
    for (int j = 0; j < m->c; ++j) {
      copy->data[i][j] = m->data[i][j];
    }
  }

  return copy;
}


Matrix*
matrix_rem_rc(Matrix* m, int r, int c)
{
  if (m == NULL) {
    return NULL;
  }

  if (r < 0 || r >= m->r || c < 0 || c >= m->c) {
    return NULL;
  }

  Matrix* res = matrix_new(m->r - 1, m->c - 1);
  int res_i = 0;
  int res_j = 0;
  for (int i = 0; i < m->r; ++i) {
    if (i == r) {
      continue;
    }
    res_j = 0;
    for (int j = 0; j < m->c; ++j) {
      if (j == c) {
        continue;
      }
      res->data[res_i][res_j] = m->data[i][j];
      res_j++;
    }
    res_i++;
  }

  return res;
}


double
matrix_det(Matrix* m)
{
  if (m == NULL) {
    return NAN;
  }

  if (m->r != m->c) {
    return NAN;
  }

  if (m->r == 1) {
    return m->data[0][0];
  }

  int sign = 1;
  double det = 0;
  for (int i = 0; i < m->r; ++i) {
    Matrix* tmp = matrix_rem_rc(m, i, 0);
    det += sign * m->data[i][0] * matrix_det(tmp);
    matrix_del(tmp);
    sign *= -1;
  }

  return det;
}


Matrix*
matrix_transpose(Matrix* m)
{
  if (m == NULL) {
    return NULL;
  }
  if (m->r != m->c) {
    return NULL;
  }

  Matrix* transp = matrix_new(m->r, m->c);
  for (int i = 0; i < m->r; ++i) {
    for (int j = 0; j < m->c; ++j) {
      transp->data[i][j] = m->data[j][i];
    }
  }

  return transp;
}


void
matrix_this_transpose(Matrix* m_this)
{
  if (m_this == NULL) {
    return;
  }
  if (m_this->r != m_this->c) {
    return;
  }

  for (int i = 1; i < m_this->r; ++i) {
    for (int j = i; j < m_this->c; ++j) {
      double tmp = m_this->data[i][j];
      m_this->data[i][j] = m_this->data[j][i];
      m_this->data[j][i] = tmp;
    }
  }
}


Matrix*
matrix_adj(Matrix* m)
{
  if (m == NULL) {
    return NULL;
  }

  Matrix* res = matrix_new(m->r, m->c);
  int sign = 1;
  for (int i = 0; i < m->r; ++i) {
    for (int j = 0; j < m->c; ++j) {
      Matrix* tmp = matrix_rem_rc(m, j, i);
      res->data[i][j] = matrix_det(tmp) * sign;
      matrix_del(tmp);
      sign *= -1;
    }
  }

  return res;
}


Matrix*
matrix_inverse(Matrix* m)
{
  if (m == NULL) {
    return NULL;
  }

  double det = matrix_det(m);
  if (det == 0) {
    return NULL;
  }

  Matrix* res = matrix_adj(m);
  matrix_this_scale(res, 1.0 / det);

  return res;
}
