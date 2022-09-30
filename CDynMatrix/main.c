/**
 * @file main.c
 * @author Antonin Nepras
 * @brief
 * @version 0.1
 * @date 2022-09-29
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "src/dyn_matrix.h"


#define SUCCESS 0
#define ERROR 1

void
matrix_fprint(FILE* file, Matrix* m);


int
main(int argc, const char** argv)
{
  /*
  Matrix* m = matrix_new(2, 2);
  m->data[0][0] = 1;
  m->data[0][1] = 2;
  m->data[1][0] = 3;
  m->data[1][1] = 4;
  */

  Matrix* m = matrix_new(3, 3);
  m->data[0][0] = 2;
  m->data[0][1] = 6;
  m->data[0][2] = 8;
  m->data[1][0] = 5;
  m->data[1][1] = 6;
  m->data[1][2] = 7;
  m->data[2][0] = 5;
  m->data[2][1] = 9;
  m->data[2][2] = 10;

  /*
  matrix_fprint(stdout, m);

  printf("det m = %f\n", matrix_det(m));

  Matrix* m_adj = matrix_adj(m);
  matrix_fprint(stdout, m_adj);

  Matrix* m_inv = matrix_inverse(m);
  matrix_fprint(stdout, m_inv);

  Matrix* m_inv_inv = matrix_inverse(m_inv);
  matrix_fprint(stdout, m_inv_inv);


  matrix_del(m);
  matrix_del(m_inv);
  matrix_del(m_inv_inv);
  matrix_del(m_adj);
  */

  // test
  for (int i = 0; i < 100000; ++i) {

    Matrix* m_adj = matrix_adj(m);

    Matrix* m_inv = matrix_inverse(m);

    Matrix* m_inv_inv = matrix_inverse(m_inv);


    matrix_del(m_inv);
    matrix_del(m_inv_inv);
    matrix_del(m_adj);
  }

  matrix_del(m);

  return SUCCESS;
}


void
matrix_fprint(FILE* file, Matrix* m)
{
  if (file == NULL || m == NULL) {
    return;
  }
  putc('[', file);
  for (int i = 0; i < m->r; ++i) {
    for (int j = 0; j < m->c; ++j) {
      if (j != 0) {
        fprintf(file, " ");
      }
      fprintf(file, "%lf", m->data[i][j]);
    }
    if (i != m->r - 1)
      fprintf(file, "; ");
  }
  putc(']', file);
  putc('\n', file);
}
