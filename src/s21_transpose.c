#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int err = OK;
  if (!A || A->matrix == NULL) {
    err = INVALID_MATRIX;
  } else if (A->rows < 1 || A->columns < 1) {
    err = INVALID_MATRIX;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    // ВЫЧИСЛЕНИЕ
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return err;
}