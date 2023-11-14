#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int err = SUCCESS;
  if (!A || !B || A->matrix == NULL || B->matrix == NULL) {
    err = FAILURE;
  } else if (A->rows < 1 || A->columns < 1 || B->rows < 1 || B->columns < 1) {
    err = FAILURE;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    err = FAILURE;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
          err = FAILURE;
        }
      }
    }
  }

  return err;
}